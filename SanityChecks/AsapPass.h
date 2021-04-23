// This file is part of ASAP.
// Please see LICENSE.txt for copyright and licensing information.

#include "SanityCheckCostPass.h"
#include "SanityCheckInstructionsPass.h"
#include "utils.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include <neo4j-client.h>

namespace sanitychecks {
class GCOVFile;
}

namespace llvm {
class Instruction;
}

struct SanityCheckCostPass;
struct SanityCheckInstructionsPass;

struct AsapPass : public llvm::ModulePass {
  static char ID;

  AsapPass() : ModulePass(ID), SCC(0), SCI(0) {}

  virtual bool runOnModule(llvm::Module &M);

  virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const;

private:
  SanityCheckCostPass *SCC;
  SanityCheckInstructionsPass *SCI;
  std::string programName;

  // Tries to remove a sanity check; returns true if it worked.
  bool optimizeCheckAway(llvm::Instruction *Inst);

  // Method for simulating ASAP, just checks if it can remove a check
  bool canOptimizeCheckAway(llvm::Instruction *Inst);

  // Method to add other checks to handle hot check removed
  bool handleHotCheckRemoved(llvm::Instruction *Inst);

  // Method to check the operation is safe (Should be sound - unsafe should be complete)
  bool isSafeOperation(llvm::BranchInst *branchInst);

  bool checkIfUnsafePointerAction(llvm::Instruction *instruction);
};
