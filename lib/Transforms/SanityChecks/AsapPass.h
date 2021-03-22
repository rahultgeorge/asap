// This file is part of ASAP.
// Please see LICENSE.txt for copyright and licensing information.

#include "SanityCheckCostPass.h"
#include "SanityCheckInstructionsPass.h"
#include "utils.h"
#include "llvm/Pass.h"
#include <neo4j-client.h>
#include "llvm/IR/Module.h"

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

  // Method to add other checks to handle hot check removed
  bool handleHotCheckRemoved(llvm::Instruction *Inst);

  // Method to check if the object is a safe stack object
  bool isSafeStackObject(llvm::BranchInst *branchInst);

  bool checkIfUnsafePointerAction(llvm::Instruction *instruction);
};
