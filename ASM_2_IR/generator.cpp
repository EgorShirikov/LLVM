//
// Created by Егор Шириков on 26.11.2023.
//
#include "../Conway-Game-Of-Life/sim.h"

#include "fstream"
#include "map"
#include <sstream>

#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

static LLVMContext context;
static IRBuilder<> builder(context);
static Module *module = new Module("life.cpp", context);

Type* int32Ty = builder.getInt32Ty();
Type* voidTy = builder.getVoidTy();

const size_t REG_FILE_SIZE = 36;
uint32_t REG_FILE[REG_FILE_SIZE];

FunctionType *simMainTy = FunctionType::get(int32Ty, false);
Function *simMain = Function::Create(simMainTy, Function::ExternalLinkage, "main", module);

void doXor(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] ^ REG_FILE[arg3];
}

void doMuli(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] * arg3;
}

void doDivi(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] / arg3;
}

void doOr(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] or REG_FILE[arg3];
}

void doAnd_eq(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] and REG_FILE[arg3];
  REG_FILE[arg1] = REG_FILE[arg1] == REG_FILE[arg3];
}

void doAddi_eq(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] + arg3;
  REG_FILE[arg1] = REG_FILE[arg1] == REG_FILE[arg3];
}

void doSub(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] - REG_FILE[arg3];
}

void doEq(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] == REG_FILE[arg3];
}

void doPutPixel(int arg1, int arg3) {
  simSetPixel(REG_FILE[arg1], REG_FILE[arg3]);
}

void doInc_eq(int arg1, int arg2, int arg3) {
  REG_FILE[arg2]++;
  REG_FILE[arg1] = REG_FILE[arg2] == arg3;
}

void doEqi(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] == arg3;
}

void doAndi(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] and arg3;
}

void doSgt(int arg1, int arg2, int arg3) {
  REG_FILE[arg1] = REG_FILE[arg2] > REG_FILE[arg3];
}

void doSimInit() {
  simInit();
}

void doSimFlush() {
  simFlush();
}

void doSimExit() {
  simExit();
}

void doSimEvent(int arg){
  REG_FILE[arg] = simEvent();
}

void doSimRand(int arg){
  REG_FILE[arg] = simRand();
}

int main() {
    module->setTargetTriple("arm64-apple-macosx13.0.0");
    std::map<std::string, BasicBlock*> basicBlocks;
    FunctionType *voidFuncType = FunctionType::get(voidTy, {voidTy}, false);
    ArrayRef<Type*> int32x3Types = {Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context)};
    FunctionType *int32x3FuncType = FunctionType::get(voidTy, int32x3Types, false);
    ArrayRef<Type*> int32x2Types = { Type::getInt32Ty(context), Type::getInt32Ty(context)};
    FunctionType *int32x2FuncType = FunctionType::get(voidFuncType, int32x2Types, false);
    FunctionType *int32FuncType = FunctionType::get(int32Ty, {Type::getInt32Ty(context)}, false);


    FunctionCallee do_Xor_func = module->getOrInsertFunction("doXor", int32x3FuncType);
    FunctionCallee do_Muli_func = module->getOrInsertFunction("doMuli", int32x3FuncType);
    FunctionCallee do_Divi_func = module->getOrInsertFunction("doDivi", int32x3FuncType);
    FunctionCallee do_Or_func = module->getOrInsertFunction("doOr", int32x3FuncType);
    FunctionCallee do_And_eq_func = module->getOrInsertFunction("doAnd_eq", int32x3FuncType);
    FunctionCallee do_Addi_func = module->getOrInsertFunction("doAddi", int32x3FuncType);
    FunctionCallee do_Sub_func = module->getOrInsertFunction("doSub", int32x3FuncType);
    FunctionCallee do_Eq_func = module->getOrInsertFunction("doEq", int32x3FuncType);
    FunctionCallee do_Sgt_func = module->getOrInsertFunction("doSgt", int32x3FuncType);
    FunctionCallee do_Inc_eq_func = module->getOrInsertFunction("doInc_eq", int32x3FuncType);
    FunctionCallee do_Eqi_func = module->getOrInsertFunction("doEqi", int32x3FuncType);
    FunctionCallee do_Andi_func = module->getOrInsertFunction("doAndi", int32x3FuncType);

    FunctionCallee do_store_func = module->getOrInsertFunction("doStore", int32x3FuncType);

    FunctionCallee do_SimInit_func = module->getOrInsertFunction("doSimInit", voidFuncType);
    FunctionCallee do_SimFlush_func = module->getOrInsertFunction("doSimFlush", voidFuncType);
    FunctionCallee do_SimExit_func = module->getOrInsertFunction("doSimExit", voidFuncType);

    FunctionCallee doSimRand_func = module->getOrInsertFunction("doSimRand", int32FuncType);
    FunctionCallee doSimEvent_func = module->getOrInsertFunction("doSimEvent", int32FuncType);

    FunctionCallee do_PutPixe_func = module->getOrInsertFunction("doPutPixel", int32x2FuncType);
    std::ifstream in("game.s");
    if (in.is_open()) {
      std::string s;
      while (std::getline(in, s)) {
        std::istringstream is(s);
        std::string instrName;
        is >> instrName;
        if (instrName == "bb0" || instrName == "bb1" || instrName == "bb2"
            || instrName == "bb3" || instrName == "bb4" || instrName == "bb5"
            || instrName == "bb6" || instrName == "bb7" || instrName == "bb8"
            || instrName == "bb9" || instrName == "bb10" || instrName == "bb11" || instrName == "bb12"
            || instrName == "bb13") {
          basicBlocks[instrName] = BasicBlock::Create(context, "", simMain);
          if (instrName == "bb0") {
            builder.SetInsertPoint(basicBlocks["bb0"]);
          }
        } else if (instrName == "geti") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
        } else if (instrName == "simInit") {
          builder.CreateCall(do_SimInit_func);
        } else if (instrName == "xor") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(1)));
          builder.CreateCall(do_Xor_func, {arg1, arg2, arg3});
        } else if (instrName == "simRand") {
          std::string arg;
          is >> arg;
          Value  *arg1 = builder.getInt32(std::stoi(arg.substr(1)));
          builder.CreateCall(doSimRand_func, arg1);
        }  else if (instrName == "store") {
          std::string dstReg, fisrtOperand;
          is >> dstReg >> fisrtOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          builder.CreateCall(do_store_func, {arg1, arg2});
        } else if (instrName == "inc_eq") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(0)));
          builder.CreateCall(do_Inc_eq_func, {arg1, arg2, arg3});
        } else if (instrName == "bnz") {
          std::string condition, fisrtBlock, secondBlock;
          is >> condition >> fisrtBlock >> secondBlock;
          if (REG_FILE[std::stoi(condition.substr(1))] == 1) {
            builder.SetInsertPoint(basicBlocks[fisrtBlock]);
          } else {
            builder.SetInsertPoint(basicBlocks[secondBlock]);
          }
        } else if (instrName == "divi") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(0)));
          builder.CreateCall(do_Divi_func, {arg1, arg2, arg3});
        } else if (instrName == "muli") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(0)));
          builder.CreateCall(do_Muli_func, {arg1, arg2, arg3});
        } else if (instrName == "sub") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(1)));
          builder.CreateCall(do_Sub_func, {arg1, arg2, arg3});
        } else if (instrName == "addi") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(0)));
          builder.CreateCall(do_Addi_func, {arg1, arg2, arg3});
        } else if (instrName == "eq") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(1)));
          builder.CreateCall(do_Eq_func, {arg1, arg2, arg3});
        } else if (instrName == "sgt") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(1)));
          builder.CreateCall(do_Sgt_func, {arg1, arg2, arg3});
        } else if (instrName == "or") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(1)));
          builder.CreateCall(do_Or_func, {arg1, arg2, arg3});
        } else if (instrName == "and") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(1)));
          builder.CreateCall(do_And_eq_func, {arg1, arg2, arg3});
        }  else if (instrName == "eqi") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(0)));
          builder.CreateCall(do_Eqi_func, {arg1, arg2, arg3});
        } else if (instrName == "andi") {
          std::string dstReg, fisrtOperand, secondOperand;
          is >> dstReg >> fisrtOperand >> secondOperand;
          Value  *arg1 = builder.getInt32(std::stoi(dstReg.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(fisrtOperand.substr(1)));
          Value  *arg3 = builder.getInt32(std::stoi(secondOperand.substr(0)));
          builder.CreateCall(do_Andi_func, {arg1, arg2, arg3});
        } else if (instrName == "simSetPixel") {
          std::string fst, scnd;
          is >> fst >> scnd;
          Value  *arg1 = builder.getInt32(std::stoi(fst.substr(1)));
          Value  *arg2 = builder.getInt32(std::stoi(scnd.substr(1)));
          builder.CreateCall(do_PutPixe_func, {arg1, arg2});
        } else if (instrName == "simFlush") {
          builder.CreateCall(do_SimFlush_func);
        } else if (instrName == "simEvent") {
          std::string arg;
          is >> arg;
          Value  *arg1 = builder.getInt32(std::stoi(arg.substr(1)));
          builder.CreateCall(doSimEvent_func, arg1);
        } else if (instrName == "simExit") {
          builder.CreateCall(do_SimExit_func);
        } else if (instrName == "ret") {
          builder.CreateRet(ConstantInt::get(builder.getInt32Ty(), 0, true));
        }
      }
    }
    outs() << "\n#[LLVM IR]:\n";
    module->print(outs(), nullptr);

    verifyFunction(*simMain);
    outs() << "\n#[Running code]\n";
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
    ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
      if (fnName == "doXor") {
        return reinterpret_cast<void *>(doXor);
      }
      if (fnName == "doAndi") {
        return reinterpret_cast<void *>(doAndi);
      }
      if (fnName == "doAddi_eq") {
        return reinterpret_cast<void *>(doAddi_eq);
      }
      if (fnName == "doMuli") {
        return reinterpret_cast<void *>(doMuli);
      }
      if (fnName == "doDivi") {
        return reinterpret_cast<void *>(doDivi);
      }
      if (fnName == "doOr") {
        return reinterpret_cast<void *>(doOr);
      }
      if (fnName == "doSub") {
        return reinterpret_cast<void *>(doSub);
      }
      if (fnName == "doEq") {
        return reinterpret_cast<void *>(doEq);
      }
      if (fnName =="doSgt") {
        return reinterpret_cast<void *>(doSgt);
      }
      if (fnName == "doInt_eq") {
        return reinterpret_cast<void *>(doInc_eq);
      }
      if (fnName == "doEqi") {
        return reinterpret_cast<void *>(doEqi);
      }
      if (fnName == "doAndi") {
        return reinterpret_cast<void *>(doAndi);
      }
      if (fnName == "doSimInit") {
        return reinterpret_cast<void *>(doSimInit);
      }
      if (fnName == "doSimExit") {
        return reinterpret_cast<void *>(doSimExit);
      }
      if (fnName == "doSimFlush") {
        return reinterpret_cast<void *>(doSimFlush);
      }
      if (fnName == "doPutPixel") {
        return reinterpret_cast<void *>(doPutPixel);
      }
      if (fnName == "doAnd_eq") {
        return reinterpret_cast<void *>(doAnd_eq);
      }
      if (fnName == "doSimEvent") {
        return reinterpret_cast<void *>(doSimEvent);
      }
      if (fnName == "doSimRand") {
        return reinterpret_cast<void *>(doSimRand);
      }
      return nullptr;
    });
    ArrayType *regFileType = ArrayType::get(builder.getInt32Ty(), REG_FILE_SIZE);
    module->getOrInsertGlobal("regFile", regFileType);
    GlobalVariable *regFile = module->getNamedGlobal("regFile");

    ee->addGlobalMapping(regFile, (void *)REG_FILE);
    ee->finalizeObject();
    ArrayRef<GenericValue> noargs;
    ee->runFunction(simMain, noargs);
    outs() << "#[Code was run]\n";
    for (int i = 0; i < REG_FILE_SIZE; i++) {
      outs() << "[" << i << "] " << REG_FILE[i] << "\n";
    }
}




