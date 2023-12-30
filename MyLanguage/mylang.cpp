//
// Created by Егор Шириков on 30.12.2023.
//

#include "mylangBaseVisitor.h"
#include "mylangLexer.h"
#include "mylangParser.h"
#include "ANTLRInputStream.h"
#include "CommonTokenStream.h"

#include <any>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Metadata.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>


using namespace llvm;

static LLVMContext context;
static IRBuilder<> builder(context);
static Module *module = new Module("life.cpp", context);

Type* int32Ty = builder.getInt32Ty();
Type* voidTy = builder.getVoidTy();

//simMain
FunctionType *simMainTy = FunctionType::get(int32Ty, false);
Function *simMain = Function::Create(simMainTy, Function::ExternalLinkage, "main", module);

//simFlush
ArrayRef<Type*> simFlushParams = {};
FunctionType* simFlushType = FunctionType::get(VoidType, simFlushParams, false);
FunctionCallee simFlush = module.getOrInsertFunction("simFlush", simFlushType);

//simSetPixel
ArrayRef<Type*> simSetPixelParams = {Int32Type, Int32Type, Int32Type};
FunctionType* simSetPixelType = FunctionType::get(VoidType, simSetPixelParams, false);
FunctionCallee simSetPixel = module.getOrInsertFunction("simSetPixel", simSetPixelType);

//simRand
ArrayRef<Type*> simRandParams = {};
FunctionType* simRandType = FunctionType::get(Int32Type, simFlushParams, false);
FunctionCallee simRand = module.getOrInsertFunction("simRand", simRandType);

//simInit
ArrayRef<Type*> simInitParams = {};
FunctionType* simInitType = FunctionType::get(VoidType, simInitParams, false);
FunctionCallee simInit = module.getOrInsertFunction("simInit", simInitType);

//simInit
ArrayRef<Type*> simExitParams = {};
FunctionType* simExitType = FunctionType::get(VoidType, simExitParams, false);
FunctionCallee simExit = module.getOrInsertFunction("simExit", simExitType);

class MyVisitor : public mylangBaseVisitor {
  std::unordered_map<std::string, AllocaInst *> arrays;
public:
  std::any visitProgram(mylangParser::ProgramContext *ctx) override{
    module->setTargetTriple("arm64-apple-macosx13.0.0");
    BasicBlock *bb0 = BasicBlock::Create(context, "", fnMain);
    builder.SetInsertPoint(bb0);
    visitChildren(ctx);
    builder.CreateRet(ConstantInt::get(intTy, 0, true));
    return {};
  }

  std::any visitBeginSimulation(mylangParser::ProgramContext *ctx) override{
    for (auto arr : ctx->arryDeclaration()){
      visitArrayDeclaration(ar);
    }
    visit(ctx->children[4]);
    builder.CreateCall(simInit);
    visit(ctx->children[6]);
    return {};
  }

  std::any visitArrayDeclaration(mylangParser::ProgramContext *ctx) override{
    int siz = std::stoi(ctx->children[3]->getText);
    Type* i32 = ArrayType::get(Type::getInt32Ty(context), siz);
    AllocaInst *value1 = builder.CreateAlloca(i32, nullptr);
    arrays[ctx->children[3]->getText] = value1;
  }

  std::any visitPointerDeclaration(mylangParser::ProgramContext *ctx) override{
    AllocaInst *value = arrays[ctx->children[0]];
    if (value == arrays.end()) {
     throw std::runtime_error("Unknown value" + ctx->children[0]);
    }
    Value* value1 = builder.CreateInBoundsGEP(builder.getInt32Ty(),value);
  }

  std::any visitId(mylangParser::ProgramContext *ctx) override {
    return static_cast<Value *>(getInt(std::stoi(ctx->children[0]->getText())));
  }

  std::any visitFactor(mylangParser::ProgramContext *ctx) override {
    if (ctx -> children.length() == 3) {
      return static_cast<Value *>(getInt(std::stoi(ctx->children[1]->getText())));
    } else {
      return static_cast<Value *>(getInt(std::stoi(ctx->children[0]->getText())));
    }
  }

  std::any visitFactor(mylangParser::ProgramContext *ctx) override {
    if (ctx -> children.length() == 1) {
      return visit(ctx->children[0]);
    } else {
      Value *lhs = std::any_cast<Value *>(visit(ctx->children[0]));
      Value *rhs = std::any_cast<Value *>(visit(ctx->children[2]));
      Value *res;
      if (ctx->children[1].getText() == '/') {
          res = builder.CreateDiv(lhs, rhs);
      } else {
        res = builder.CreateMul(lhs, rhs);
      }
    }
    return res;
  }

  std::any visitExpression(mylangParser::ProgramContext *ctx) override {
    if (ctx -> children.length() == 1) {
      return visit(ctx->children[0]);
    } else {
      Value *lhs = std::any_cast<Value *>(visit(ctx->children[0]));
      Value *rhs = std::any_cast<Value *>(visit(ctx->children[2]));
      Value *res;
      if (ctx->children[1].getText() == '+') {
        res = builder.CreateAdd(lhs, rhs);
      } else {
        res = builder.CreateSub(lhs, rhs);
      }
    }
    return res;
  }

  std::any visitExitSimulation(mylangParser::ProgramContext *ctx) override {
    builder.CreateCall(simExit);
    return {};
  }

  std::any visitFlushSimulation(mylangParser::ProgramContext *ctx) override {
    builder.CreateCall(simFlush);
    return {};
  }

  std::any visitSetSimulationPixel(mylangParser::ProgramContext *ctx) override {
    Value *col = std::any_cast<Value *>(visit(ctx->children[2]));
    Value *row = std::any_cast<Value *>(visit(ctx->children[4]));
    builder.CreateCall(fnSimSetPixel, {col, row});
    return {};
  }

  std::any visitAssigment(mylangParser::ProgramContext *ctx) override {
    Value *val = std::any_cast<Value *>(visit(ctx->children[2]));
    return val;
  }

  std::any visitStmtWhileLoop(MyLanguageParser::StmtWhileContext *ctx) override {
    BasicBlock *condBB = BasicBlock::Create(context, "", simMain);
    BasicBlock *bodyBB = BasicBlock::Create(context, "", simMain);
    BasicBlock *exitBB = BasicBlock::Create(context, "", simMain);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);
    Value *val = std::any_cast<Value *>(visit(ctx->children[1]));
    builder.CreateCondBr(val, bodyBB, exitBB);
    builder.SetInsertPoint(bodyBB);
    visit(ctx->children[2]);
    builder.CreateBr(condBB);
    builder.SetInsertPoint(exitBB);
    return visitChildren(ctx);
  }

  std::any visitIfStatement(MyLanguageParser::IfStmtContext *ctx) override {
    BasicBlock *thenBB = BasicBlock::Create(context, "", simMain);
    BasicBlock *elseBB = BasicBlock::Create(context, "", simMain);
    BasicBlock *exitBB = BasicBlock::Create(context, "", simMain);
    Value *val = std::any_cast<Value *>(visit(ctx->children[1]));
    builder.CreateCondBr(val, thenBB, elseBB);
    builder.SetInsertPoint(thenBB);
    visit(ctx->children[2]);
    builder.CreateBr(exitBB);
    builder.SetInsertPoint(elseBB);
    if (ctx->children.size() > 4)
      visit(ctx->children[4]);
    builder.CreateBr(exitBB);
    builder.SetInsertPoint(exitBB);
    return {};
  }

  std::any visitForLoop(MyLanguageParser::IfStmtContext *ctx) override {
    Value *val1 = visit(ctx->children[5]);
    Value *val2 = visit(ctx->children[9]);
    Value* val3 = builder.CreateAdd(value14,
                                       ConstantInt::get(builder.getInt32Ty(), 1, true));
    Value* value3 = builder.CreateICmpUGT(val1, val2);
    BasicBlock *loop = BasicBlock::Create(context, "", simMain);
    BasicBlock *exitBB = BasicBlock::Create(context, "", simMain);
    builder.CreateCondBr(value3, loop, exitBB);
    builder.SetInsertPoint(loop);
    visit(ctx->children[13]);
    builder.CreateBr(exitBB);
    builder.SetInsertPoint(exitBB);
    return{};
  }
}

int main() {
  antlr4::ANTLRInputStream inputStream(std::cin);
  MyLanguageLexer lexer(&inputStream);
  antlr4::CommonTokenStream tokenStream(&lexer);
  MyLanguageParser parser(&tokenStream);
  MyLanguageParser::ProgramContext *tree = parser.program();
  MyVisitor visitor;
  visitor.visitProgram(tree);
  return 0;
}

