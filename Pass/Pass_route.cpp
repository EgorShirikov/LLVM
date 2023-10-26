#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

using namespace llvm;

namespace {
    struct MyPass : public FunctionPass {
        static char ID;
        MyPass() : FunctionPass(ID) {}

        bool isFuncLogger(StringRef name) {
            return name == "routeLogger";
        }

        virtual bool runOnFunction(Function &F) {
            if (isFuncLogger(F.getName())) {
                return false;
            }

            // Prepare builder for IR modification
            LLVMContext &Ctx = F.getContext();
            IRBuilder<> builder(Ctx);
            Type *retType = Type::getVoidTy(Ctx);

            // Prepare routeLogget function
            ArrayRef<Type *> routePararamTypes = {builder.getInt8Ty()->getPointerTo(),
                                                  builder.getInt8Ty()->getPointerTo()};
            FunctionType *funcStartLogFuncType =
                    FunctionType::get(retType, routePararamTypes, false);
            FunctionCallee routeLogFunc = F.getParent()->getOrInsertFunction(
                    "routeLogger", funcStartLogFuncType);

            // Insert routeLogger
            for (auto &B : F) {
                for (auto &I : B) {
                    if (dyn_cast<PHINode>(&I)) {
                        continue;
                    }
                    for (auto *U : I.users()) {
                        if (auto *caller = dyn_cast<Instruction>(U)) {
                            if (dyn_cast<PHINode>(caller)) {
                                continue;
                            }
                            // Insert before call
                            builder.SetInsertPoint(&I);

                            Value* opNum1 =
                                    builder.CreateGlobalStringPtr(I.getOpcodeName());
                            Value* opNum2 =
                                    builder.CreateGlobalStringPtr(caller ->getOpcodeName());
                            Value* args[] = {opNum2, opNum1};
                            builder.CreateCall(routeLogFunc, args);
                        }
                    }
                }
            }
            return true;
        }
    };
} // namespace

char MyPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerMyPass(const PassManagerBuilder &,
                           legacy::PassManagerBase &PM) {
    PM.add(new MyPass());
}
static RegisterStandardPasses
        RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                       registerMyPass);