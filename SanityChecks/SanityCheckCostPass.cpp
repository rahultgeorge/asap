// This file is part of ASAP.
// Please see LICENSE.txt for copyright and licensing information.
// Rahul - This pass must be changed.

/*  In this pass we use the SanityCheckInstructionPass to identify the checks
 *  They use the cost model for the cost
 *  TODO - Read attack graph and then elide checks based on cost and traces
 *  TODO - Will probably need to do something about hot checks for which there
 * are attack traces using the attack graph. Probably need to move ASAN checks
 * from that point to some other point
 */

#include "SanityCheckCostPass.h"
#include "CostModel.h"
#include "SanityCheckInstructionsPass.h"
#include "utils.h"

#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Module.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/Errc.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/Path.h"

#include <algorithm>
#include <memory>
#include <system_error>
#define DEBUG_TYPE "sanity-check-cost"

using namespace llvm;

static cl::opt<std::string> InputGCNO("gcno", cl::desc("<input gcno file>"),
                                      cl::init(""), cl::Hidden);

static cl::opt<std::string> InputGCDA("gcda", cl::desc("<input gcda file>"),
                                      cl::init(""), cl::Hidden);

namespace {
bool largerCost(const SanityCheckCostPass::CheckCost &a,
                const SanityCheckCostPass::CheckCost &b) {
  return a.second > b.second;
}
} // anonymous namespace

bool SanityCheckCostPass::runOnModule(Module &M) {
  SanityCheckInstructionsPass &SCI = getAnalysis<SanityCheckInstructionsPass>();
  TargetTransformInfoWrapperPass &TTIWP =
      getAnalysis<TargetTransformInfoWrapperPass>();
  std::unique_ptr<GCOVFile> GF(createGCOVFile());

  for (Function &F : M) {
    if (F.isIntrinsic() || F.empty())
      continue;
    errs() << "SanityCheckCostPass on " << F.getName() << "\n";
    const TargetTransformInfo &TTI = TTIWP.getTTI(F);

    for (Instruction *Inst : SCI.getSanityCheckBranches(&F)) {
      assert(Inst->getParent()->getParent() == &F &&
             "SCI must only contain instructions of the current function.");

      BranchInst *BI = dyn_cast<BranchInst>(Inst);
      assert(BI && BI->isConditional() &&
             "SanityCheckBranches must not contain instructions that aren't "
             "conditional branches.");
      errs() << *BI << "\n";
#ifndef NDEBUG
      int nInstructions = 0;
      int nFreeInstructions = 0;
#endif

      // The cost of a check is the sum of the cost of all instructions
      // that this check uses.
      // TODO: If an instruction is used by multiple checks, we need an
      // intelligent way to handle the non linearity.
      uint64_t Cost = 0;
      for (Instruction *CI : SCI.getInstructionsBySanityCheck(BI)) {
        unsigned CurrentCost = sanitychecks::getInstructionCost(CI, &TTI);
        errs() << "\t" << *CI << "\n";
        // Assume a default cost of 1 for unknown instructions
        if (CurrentCost == (unsigned)(-1)) {
          CurrentCost = 1;
        }

        LLVM_DEBUG(if (CurrentCost == 0) { nFreeInstructions += 1; });

        assert(CurrentCost <= 100 && "Outlier cost value?");

        Cost += CurrentCost * GF->getCount(CI);
        LLVM_DEBUG(nInstructions += 1);
      }

      APInt CountInt = APInt(64, Cost);
      MDNode *MD = MDNode::get(
          M.getContext(), {ConstantAsMetadata::get(ConstantInt::get(
                              Type::getInt64Ty(M.getContext()), CountInt))});
      Inst->setMetadata("cost", MD);
      CheckCosts.push_back(std::make_pair(BI, Cost));

      LLVM_DEBUG(dbgs() << "Sanity check: " << *BI << "\n";
                 unsigned int RegularBranch = getRegularBranch(BI, &SCI);
                 DebugLoc DL = getSanityCheckDebugLoc(BI, RegularBranch);
                 printDebugLoc(DL, M.getContext(), dbgs());
                 dbgs() << "\n nInstructions: " << nInstructions << "\n";
                 dbgs() << "nFreeInstructions: " << nFreeInstructions << "\n";
                 dbgs() << "Count: " << GF->getCount(BI) << "\n";
                 dbgs() << "Cost: " << Cost << "\n";);
    }
  }

  std::sort(CheckCosts.begin(), CheckCosts.end(), largerCost);
  return false;
}

void SanityCheckCostPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<TargetTransformInfoWrapperPass>();
  AU.addRequired<SanityCheckInstructionsPass>();
  AU.setPreservesAll();
}

void SanityCheckCostPass::print(raw_ostream &O, const Module *M) const {
  SanityCheckInstructionsPass &SCI = getAnalysis<SanityCheckInstructionsPass>();
  O << "                Cost Location\n";
  for (const CheckCost &I : CheckCosts) {
    O << format("%20llu ", I.second);
    unsigned int RegularBranch = getRegularBranch(I.first, &SCI);
    DebugLoc DL = getSanityCheckDebugLoc(I.first, RegularBranch);
    printDebugLoc(DL, M->getContext(), O);
    O << '\n';
  }
}

GCOVFile *SanityCheckCostPass::createGCOVFile() {
  GCOVFile *GF = new GCOVFile;

  if (InputGCNO.empty()) {
    report_fatal_error("Need to specify --gcno!");
  }
  ErrorOr<std::unique_ptr<MemoryBuffer>> GCNO_Buff =
      MemoryBuffer::getFileOrSTDIN(InputGCNO);
  if (std::error_code EC = GCNO_Buff.getError()) {
    report_fatal_error(InputGCNO + ":" + EC.message());
  }

  GCOVBuffer GCNO_GB(GCNO_Buff.get().get());

  if (!GF->readGCNO(GCNO_GB)) {
    errs() << "Invalid .gcno File!\n";
    // report_fatal_error(InputGCNO + ": Invalid .gcno file!");
  }

  if (InputGCDA.empty()) {
    report_fatal_error("Need to specify --gcda!");
  }

  ErrorOr<std::unique_ptr<MemoryBuffer>> GCDA_Buff =
      MemoryBuffer::getFileOrSTDIN(InputGCDA);
  if (std::error_code EC = GCDA_Buff.getError()) {
    errs() << "Invalid gcda file\n";
    report_fatal_error(InputGCDA + ":" + EC.message());
  }

  GCOVBuffer GCDA_GB(GCDA_Buff.get().get());
  if (!GF->readGCDA(GCDA_GB)) {
    errs() << "Invalid gcda file\n";
    report_fatal_error(InputGCDA + ": Invalid .gcda file!");
  }

  return GF;
}

char SanityCheckCostPass::ID = 0;
static RegisterPass<SanityCheckCostPass>
    X("sanity-check-cost", "Finds costs of sanity checks", false, false);
