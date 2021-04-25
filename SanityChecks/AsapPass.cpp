// This file is part of ASAP.
// Please see LICENSE.txt for copyright and licensing information.

#include "AsapPass.h"

#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/MemoryBuiltins.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/raw_ostream.h"
#define DEBUG_TYPE "asap"

using namespace llvm;

static cl::opt<double>
    SanityLevel("sanity-level",
                cl::desc("Fraction of static checks to be preserved"),
                cl::init(-1.0));

static cl::opt<double>
    CostLevel("cost-level",
              cl::desc("Fraction of dynamic checks to be preserved"),
              cl::init(-1.0));

static cl::opt<unsigned long long>
    CostThreshold("asap-cost-threshold",
                  cl::desc("Remove checks costing this or more"),
                  cl::init((unsigned long long)(-1)));

static cl::opt<bool>
    PrintRemovedChecks("print-removed-checks",
                       cl::desc("Should a list of removed checks be printed?"),
                       cl::init(false));

bool AsapPass::runOnModule(Module &M) {
  SCC = &getAnalysis<SanityCheckCostPass>();
  SCI = &getAnalysis<SanityCheckInstructionsPass>();

  // PDQ:  Fetch program name
  programName = M.getModuleIdentifier();
  programName = programName.substr(0, programName.length() - 3);

  // Check whether we got the right amount of parameters
  int nParams = 0;
  if (SanityLevel >= 0.0)
    nParams += 1;
  if (CostLevel >= 0.0)
    nParams += 1;
  if (CostThreshold != (unsigned long long)(-1))
    nParams += 1;
  if (nParams != 1) {
    report_fatal_error("Please specify exactly one of -cost-level, "
                       "-sanity-level or -asap-cost-threshold");
  }

  size_t TotalChecks = SCC->getCheckCosts().size();
  if (TotalChecks == 0) {
    dbgs() << "Removed 0 out of 0 static checks (nan%)\n";
    dbgs() << "Removed 0 out of 0 dynamic checks (nan%)\n";
    return false;
  }

  uint64_t TotalCost = 0;
  for (const SanityCheckCostPass::CheckCost &I : SCC->getCheckCosts()) {
    TotalCost += I.second;
  }

  // Start removing checks. They are given in order of decreasing cost, so we
  // simply remove the first few.
  uint64_t RemovedCost = 0;
  size_t NChecksRemoved = 0;

  //PDQ: New variables to remove statically proven safe operations as these do ot incur any cost (sanity level)
  uint64_t safeChecksRemovedCost = 0;
  size_t safeNChecksRemoved = 0;
    errs()<<"Initial sanity level:"<<SanityLevel<<"\n";  

  // PDQ: We simulate the ASAP run without actually removing the checks just to
  // record the # checks removed
  // PDQ: We could also measure the impact of the checks removed
  for (const SanityCheckCostPass::CheckCost &I : SCC->getCheckCosts()) {

    // Elision based on sanity level and
    if (SanityLevel >= 0.0) {
      if ((NChecksRemoved + 1) > TotalChecks * (1.0 - SanityLevel)) {
        break;
      }
    }

    else if (CostLevel >= 0.0) {
      // Make sure we get the boundary conditions right... it's important
      // that at cost level 0.0, we don't remove checks that cost zero.
      if (RemovedCost >= TotalCost * (1.0 - CostLevel) ||
          (RemovedCost + I.second) > TotalCost * (1.0 - CostLevel)) {
        break;
      }
    }

    else if (CostThreshold != (unsigned long long)(-1)) {
      if (I.second < CostThreshold) {
        break;
      }
    }

    if (canOptimizeCheckAway(I.first)) {
      RemovedCost += I.second;
      NChecksRemoved += 1;
    }
  }

  errs() << "ASAP:"
         << "\n\t# checks removed:" << NChecksRemoved
         << "\n\tRemoved cost:" << RemovedCost
         << "\n\t Total # checks:" << TotalChecks << "\n";

  dbgs() << "Removed " << NChecksRemoved << " out of " << TotalChecks
         << " static checks ("
         << format("%0.2f", (100.0 * NChecksRemoved / TotalChecks)) << "%)\n";
  dbgs() << "Removed " << RemovedCost << " out of " << TotalCost
         << " dynamic checks ("
         << format("%0.2f", (100.0 * RemovedCost / TotalCost)) << "%)\n";

  // PDQ: Resetting these variables and therefore we can actually use PDQ to
  // remove checks
  
  
  RemovedCost = 0;
  NChecksRemoved = 0;
  errs()<<"PDQ Sanity level"<<SanityLevel<<"\n";  
  for (const SanityCheckCostPass::CheckCost &I : SCC->getCheckCosts()) {
    if (isSafeOperation(I.first)) {
      if (optimizeCheckAway(I.first)) {
        errs()<<"Safe operation found"<<safeNChecksRemoved<<"\n";
        safeChecksRemovedCost += I.second;
        safeNChecksRemoved += 1;
      }
    }
    // PDQ: Based on our AG computation and other logic we've decided we need to
    // monitor. PDQ: Here on we use ASAP logic that is we incur the cost and
    // remove the check as per the budget
    else {
      errs()<<"Unsafe operation found"<<NChecksRemoved<<RemovedCost << "\n";
      // Elision based on sanity level and
      if (SanityLevel >= 0.0) {
        if ((NChecksRemoved + 1) > TotalChecks * (1.0 - SanityLevel)) {
          break;
        }
      }

      else if (CostLevel >= 0.0) {
        // Make sure we get the boundary conditions right... it's important
        // that at cost level 0.0, we don't remove checks that cost zero.
        if (RemovedCost >= TotalCost * (1.0 - CostLevel) ||
            (RemovedCost + I.second) > TotalCost * (1.0 - CostLevel)) {
          break;
        }
      }

      else if (CostThreshold != (unsigned long long)(-1)) {
        if (I.second < CostThreshold) {
          break;
        }
      }

      if (optimizeCheckAway(I.first)) {
        RemovedCost += I.second;
        NChecksRemoved += 1;
        // TODO - New method to add new checks
        // PDQ: We should handle hot checks/important checks
        handleHotCheckRemoved(I.first);
      }
      else
         errs()<<"Unable to remove check\n";
    }
  }
 errs()<<"Safe objects checks removed:"<<safeNChecksRemoved<<","<<safeChecksRemovedCost<<"\n";
 errs()<<"un safe objects checks removed:"<<NChecksRemoved<<","<<RemovedCost<<"\n";

  NChecksRemoved += safeNChecksRemoved;
  RemovedCost +=safeChecksRemovedCost;
 errs()<<"un safe objects checks removed:"<<NChecksRemoved<<","<<RemovedCost<<"\n";

  errs() << "PDQ:"
         << "\n\t# checks removed:" << NChecksRemoved
         << "\n\tRemoved cost:" << RemovedCost
         << "\n\t Total # checks:" << TotalChecks << "\n";

  dbgs() << "Removed " << NChecksRemoved << " out of " << TotalChecks
         << " static checks ("
         << format("%0.2f", (100.0 * NChecksRemoved / TotalChecks)) << "%)\n";
  dbgs() << "Removed " << RemovedCost << " out of " << TotalCost
         << " dynamic checks ("
         << format("%0.2f", (100.0 * RemovedCost / TotalCost)) << "%)\n";
  return false;
}

void AsapPass::getAnalysisUsage(AnalysisUsage &AU) const {
  AU.addRequired<SanityCheckCostPass>();
  AU.addRequired<SanityCheckInstructionsPass>();
  // PDQ
  AU.addRequired<TargetLibraryInfoWrapperPass>();
}

// Tries to remove a sanity check; returns true if it worked.
bool AsapPass::optimizeCheckAway(llvm::Instruction *Inst) {
  BranchInst *BI = cast<BranchInst>(Inst);
  assert(BI->isConditional() && "Sanity check must be conditional branch.");

  unsigned int RegularBranch = getRegularBranch(BI, SCI);

  bool Changed = false;
  if (RegularBranch == 0) {
    BI->setCondition(ConstantInt::getTrue(Inst->getContext()));
    Changed = true;
  } else if (RegularBranch == 1) {
    BI->setCondition(ConstantInt::getFalse(Inst->getContext()));
    Changed = true;
  } else {
    // This can happen, e.g., in the following case:
    //     array[-1] = a + b;
    // is transformed into
    //     if (a + b overflows)
    //         report_overflow()
    //     else
    //         report_index_out_of_bounds();
    // In this case, removing the sanity check does not help much, so we
    // just do nothing.
    // Thanks to Will Dietz for his explanation at
    // http://lists.cs.uiuc.edu/pipermail/llvmdev/2014-April/071958.html
    dbgs() << "Warning: Sanity check with no regular branch found.\n";
    dbgs() << "The sanity check has been kept intact.\n";
  }

  if (PrintRemovedChecks && Changed) {
    DebugLoc DL = getSanityCheckDebugLoc(BI, RegularBranch);
    printDebugLoc(DL, BI->getContext(), dbgs());
    dbgs() << ": SanityCheck with cost ";
    dbgs() << *BI->getMetadata("cost")->getOperand(0);

    if (MDNode *IA = DL.getInlinedAt()) {
      dbgs() << " (inlined at ";
      printDebugLoc(DebugLoc(IA), BI->getContext(), dbgs());
      dbgs() << ")";
    }

    BasicBlock *Succ = BI->getSuccessor(RegularBranch == 0 ? 1 : 0);
    if (const CallInst *CI = SCI->findSanityCheckCall(Succ)) {
      dbgs() << " " << CI->getCalledFunction()->getName();
    }
    dbgs() << "\n";
  }

  return Changed;
}

// PDQ: Used for simulating ASAP. Just checks if the check can be removed
bool AsapPass::canOptimizeCheckAway(llvm::Instruction *Inst) {
  BranchInst *BI = cast<BranchInst>(Inst);
  assert(BI->isConditional() && "Sanity check must be conditional branch.");

  unsigned int RegularBranch = getRegularBranch(BI, SCI);

  bool canChange = false;
  if (RegularBranch == 0 || RegularBranch == 1) {
    canChange = true;
  } else {
    // This can happen, e.g., in the following case:
    //     array[-1] = a + b;
    // is transformed into
    //     if (a + b overflows)
    //         report_overflow()
    //     else
    //         report_index_out_of_bounds();
    // In this case, removing the sanity check does not help much, so we
    // just do nothing.
    // Thanks to Will Dietz for his explanation at
    // http://lists.cs.uiuc.edu/pipermail/llvmdev/2014-April/071958.html
    dbgs() << "Warning: Sanity check with no regular branch found.\n";
    dbgs() << "The sanity check has been kept intact.\n";
  }

  return canChange;
}

bool AsapPass::handleHotCheckRemoved(llvm::Instruction *Inst) {
  dbgs() << "Check removed:" << *Inst << "\n";
  return false;
}

// Explicit only for now
bool AsapPass::isSafeOperation(BranchInst *branchInst) {
  unsigned int RegularBranch;
  BasicBlock *memoryAccessBasicBlock;
  Instruction *memoryAccessInstruction = NULL;
  Value *value;
  bool isDeclaredOnStack=true;
  const TargetLibraryInfo *TLI = NULL;

  // Step 1: Find the regular branch
  RegularBranch = getRegularBranch(branchInst, SCI);

  // Step 2 - Find the actual memory access operation
  if (RegularBranch != (unsigned)(-1)) {
    memoryAccessBasicBlock = branchInst->getSuccessor(RegularBranch);
    for (auto it = memoryAccessBasicBlock->begin();
         it != memoryAccessBasicBlock->end(); it++) {
      errs() << *it << " inst in memory access BB\n";
      // TODO Should this be more robust
      if (LoadInst *loadInst = dyn_cast<LoadInst>(it)) {
        value = loadInst->getOperand(0);
        errs() << "\t" << *value << "\n";
        errs() << "\t type:" << *(value->getType()) << "\n";
        if (dyn_cast<GetElementPtrInst>(value))
          memoryAccessInstruction = loadInst;
      } else if (StoreInst *storeInst = dyn_cast<StoreInst>(it)) {
        value = storeInst->getPointerOperand();
        errs() << "\t" << *value << "\n";
        errs() << "\t type:" << *(value->getType()) << "\n";
        if (dyn_cast<GetElementPtrInst>(value))
          memoryAccessInstruction = storeInst;
      }
      if (memoryAccessInstruction) {
        errs() << "\t Memory access instruction:" << *memoryAccessInstruction
               << "\n";
      }
    }
  }

  // Step 3 - Check the actual operation
  if (memoryAccessInstruction) {
    errs() << "Memory access instruction:" << *memoryAccessInstruction << "\n";

    TLI = &getAnalysis<TargetLibraryInfoWrapperPass>().getTLI();

    // PDQ: Check if it is declared on the stack as we do not handle global
    // currently
    if (LoadInst *loadInst = dyn_cast<LoadInst>(memoryAccessInstruction)) {
      if (isAllocationFn(loadInst->getOperand(0), TLI) ||
          isa<GlobalVariable>(loadInst->getOperand(0)))
        isDeclaredOnStack = false;
    } else if (StoreInst *storeInst =
                   dyn_cast<StoreInst>(memoryAccessInstruction)) {
      if (isAllocationFn(storeInst->getOperand(1), TLI) ||
          isa<GlobalVariable>(storeInst->getOperand(1)))
        isDeclaredOnStack = false;
    }
    if (isDeclaredOnStack)
      return !checkIfUnsafePointerAction(memoryAccessInstruction);
  }

  // PDQ: Conservative - if we can't figure out the memory access operation
  // let's classify it as unsafe (NEEDED). Also, if it is not declared on the
  // stack (Conservative-Unsafe)
  return false;
}

bool AsapPass::checkIfUnsafePointerAction(Instruction *instruction) {
  // TODO - Deal with uses of unsafe pointers that can be triggered by control flow
  std::string statement;
  std::string programNodeLabel = "";
  std::string instructionString = "";
  std::string functionName;
  // Set a hard character limit on any field returned from the query
  char *field = (char *)malloc(sizeof(char) * 500);
  raw_string_ostream rso(instructionString);
  neo4j_connection_t *connection;
  neo4j_value_t functionNameValue;
  neo4j_value_t actionTypeValue;
  neo4j_value_t instructionValue;
  neo4j_value_t programNameValue;
  neo4j_map_entry_t mapEntries[4];
  neo4j_value_t params;
  neo4j_result_t *record;
  neo4j_result_stream_t *results;

  rso << *instruction;
  if (instruction->getParent()->getParent())
    functionName = instruction->getParent()->getParent()->getName();
  else
    functionName = std::string("NULL");

  programNameValue = neo4j_string(programName.c_str());
  actionTypeValue = neo4j_string("AttackAction");
  instructionValue = neo4j_string(instructionString.c_str());
  functionNameValue = neo4j_string(functionName.c_str());

  mapEntries[0] = neo4j_map_entry("program_name", programNameValue);
  mapEntries[1] = neo4j_map_entry("action_type", actionTypeValue);
  mapEntries[2] = neo4j_map_entry("instruction", instructionValue);
  mapEntries[3] = neo4j_map_entry("function_name", functionNameValue);

  statement = " MATCH (a:AttackGraphNode)-[:EDGE]->(p:ProgramInstruction) "
              "WHERE a.program_name=p.program_name=$program_name AND "
              "a.type=$action_type AND p.instruction CONTAINS $instruction AND "
              "p.function_name=$function_name RETURN p.label";
  params = neo4j_map(mapEntries, 4);
  connection = neo4j_connect("neo4j://neo4j:secret@localhost:7687", NULL,
                             NEO4J_INSECURE);
  results = neo4j_run(connection, statement.c_str(), params);
  // There should only be one record
  if ((record = neo4j_fetch_next(results)) != NULL) {
    neo4j_ntostring(neo4j_result_field(record, 0), field, 500);
    programNodeLabel = std::string(field);
    programNodeLabel =
        programNodeLabel.substr(1, programNodeLabel.length() - 2);
  }
  neo4j_close_results(results);
  neo4j_close(connection);
  if (programNodeLabel.empty())
    return false;
  errs()<<"*** PDQ: FOUND AN UNSAFE POINTER ACTION:"<<*instruction<< ","<< programNodeLabel <<"\n";
  return true;
}

char AsapPass::ID = 0;
static RegisterPass<AsapPass> X("asap", "Removes too costly sanity checks",
                                false, false);

