#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Verifier.h"
#include "../Conway-Game-Of-Life/sim.h"

using namespace llvm;

void declareFunctions(Module& module) {
    LLVMContext &context = module.getContext();
    IRBuilder<> builder(context);

    Type *VoidType = Type::getVoidTy(context);
    Type *Int32Type = Type::getInt32Ty(context);
    Type *BoolType = Type::getInt1Ty(context);
    Type *Int64Type = Type::getInt64Ty(context);
    Type *Int8PtType = Type::getInt8PtrTy(context);

    // calcNeighbours
    ArrayRef<Type*> calcNeighboursParams = {builder.getInt32Ty()->getPointerTo(),
                                            builder.getInt32Ty(),
                                            builder.getInt32Ty()};
    FunctionType* calNeighboursType = FunctionType::get(Int32Type, calcNeighboursParams, false);
    FunctionCallee calcNeighbours = module.getOrInsertFunction("calcNeighbours", calNeighboursType);

    //calcGen
    ArrayRef<Type*> calcGenParams = {builder.getInt32Ty()->getPointerTo(),
                               builder.getInt32Ty()->getPointerTo()};
    FunctionType* calcGenType = FunctionType::get(VoidType, calcGenParams, false);
    FunctionCallee calcGen = module.getOrInsertFunction("calcGen", calcGenType);

    //drawGen
    ArrayRef<Type*> drawGenParams = {builder.getInt32Ty()->getPointerTo()};
    FunctionType* drawGenType = FunctionType::get(VoidType, drawGenParams, false);
    FunctionCallee drawGen = module.getOrInsertFunction("drawGen", drawGenType);

    //initGen
    ArrayRef<Type*> initGenParams = {builder.getInt32Ty()->getPointerTo()};
    FunctionType* initGenType = FunctionType::get(VoidType, initGenParams, false);
    FunctionCallee initGen = module.getOrInsertFunction("initGen", initGenType);

    //main
    ArrayRef<Type*> mainParams = {};
    FunctionType* mainType = FunctionType::get(Int32Type, mainParams, false);
    FunctionCallee main = module.getOrInsertFunction("main", mainType);

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

    //simExit
    ArrayRef<Type*> simEventParams = {};
    FunctionType* simEventType = FunctionType::get(BoolType, simEventParams, false);
    FunctionCallee simEvent = module.getOrInsertFunction("simEvent", simEventType);

    //lifetimeStart
    ArrayRef<Type*> lifetimeStartParams = {Int64Type, Int8PtType};
    FunctionType* lifetimeStartType = FunctionType::get(VoidType, lifetimeStartParams, false);
    FunctionCallee lifeTimeStart = module.getOrInsertFunction("llvm.lifetime.start.p0i8", lifetimeStartType);

    //lifetimeEnd
    ArrayRef<Type*> lifetimeEndParams = {Int64Type, Int8PtType};
    FunctionType* lifetimeEndType = FunctionType::get(VoidType, lifetimeEndParams, false);
    FunctionCallee lifeTimeEnd = module.getOrInsertFunction("llvm.lifetime.end.p0i8", lifetimeEndType);



}

void createCalcNeighbours(Module& module) {
    Function *calcNeighbours = module.getFunction("calcNeighbours");
    IRBuilder<> builder(module.getContext());
    //define BasicBlocks
    BasicBlock *basicBlock3 = BasicBlock::Create(module.getContext(),"", calcNeighbours);
    BasicBlock *basicBlock7 = BasicBlock::Create(module.getContext(), "", calcNeighbours);
    BasicBlock *basicBlock11 = BasicBlock::Create(module.getContext(), "", calcNeighbours);
    BasicBlock *basicBlock13 = BasicBlock::Create(module.getContext(), "", calcNeighbours);
    BasicBlock* basicBlock16 = BasicBlock::Create(module.getContext(), "", calcNeighbours);
    BasicBlock* basicBlock20 = BasicBlock::Create(module.getContext(), "", calcNeighbours);
    BasicBlock* basicBlock24 = BasicBlock::Create(module.getContext(), "", calcNeighbours);
    BasicBlock* basicBlock32 = BasicBlock::Create(module.getContext(), "", calcNeighbours);
    BasicBlock* basicBlock38 = BasicBlock::Create(module.getContext(), "", calcNeighbours);

    builder.SetInsertPoint(basicBlock3);
    Value* value1 = calcNeighbours->getArg(1);
    Value* value2 = calcNeighbours->getArg(2);
    Value* value4 = builder.CreateAdd(value1, ConstantInt::get(builder.getInt32Ty(), -1, true));
    Value* value5 = builder.CreateAdd(value1, ConstantInt::get(builder.getInt32Ty(), 1, true));
    Value* value6 = builder.CreateICmpUGT(value4, value5);
    builder.CreateCondBr(value6, basicBlock11, basicBlock7);

    builder.SetInsertPoint(basicBlock7);
    Value* value8 = builder.CreateAdd(value2, ConstantInt::get(builder.getInt32Ty(), -1, true));
    Value* value9 = builder.CreateAdd(value2, ConstantInt::get(builder.getInt32Ty(), 1, true));
    Value* value10 = builder.CreateICmpUGT(value8, value9);
    builder.CreateBr(basicBlock13);

    builder.SetInsertPoint(basicBlock11);
    PHINode* value12 = builder.CreatePHI(builder.getInt32Ty(), 1);
    builder.CreateRet(value12);

    builder.SetInsertPoint(basicBlock13);
    PHINode* value14 = builder.CreatePHI(builder.getInt32Ty(), 0);
    PHINode* value15 = builder.CreatePHI(builder.getInt32Ty(), 1);
    builder.CreateCondBr(value10, basicBlock20, basicBlock16);

    builder.SetInsertPoint(basicBlock16);
    Value* value17 = builder.CreateICmpUGT(value14, ConstantInt::get(builder.getInt32Ty(), 59, true));
    Value* value18 = builder.CreateICmpEQ(value14, value1);
    Value* value19 = builder.CreateMul(value14, ConstantInt::get(builder.getInt32Ty(), 80, true));
    builder.CreateBr(basicBlock24);

    builder.SetInsertPoint(basicBlock20);
    PHINode* value21 = builder.CreatePHI(builder.getInt32Ty(), 0);
    Value* value22 = builder.CreateAdd(value14, ConstantInt::get(builder.getInt32Ty(), 1, true));
    Value* value23 = builder.CreateICmpUGT(value22, value5);
    builder.CreateCondBr(value23, basicBlock11, basicBlock13);

    builder.SetInsertPoint(basicBlock24);
    PHINode* value25 = builder.CreatePHI(builder.getInt32Ty(), 0);
    PHINode* value26 = builder.CreatePHI(builder.getInt32Ty(), 0);

    Value* value27 = builder.CreateICmpUGT(value25, ConstantInt::get(builder.getInt32Ty(), 79, true));
    Value* value28 = builder.CreateOr(value17, value27);
    Value* value29 = builder.CreateICmpEQ(value25, value2);
    Value* value30 = builder.CreateAnd(value18, value29);
    Value* value31 = builder.CreateOr(value28, value30);
    builder.CreateCondBr(value31, basicBlock32, basicBlock38);

    builder.SetInsertPoint(basicBlock32);
    Value* value33 = builder.CreateAdd(value25, value19);
    Value* value34 = builder.CreateZExt(value33, builder.getInt64Ty());
    Value* value35 = builder.CreateInBoundsGEP(builder.getInt32Ty(), calcNeighbours->getArg(0), value34);
    Value* value36 = builder.CreateLoad(builder.getInt32Ty(), value35);
    Value* value37 = builder.CreateAdd(value36, value26);
    builder.CreateBr(basicBlock38);

    builder.SetInsertPoint(basicBlock38);
    PHINode* value39 = builder.CreatePHI(builder.getInt32Ty(), 0);

    Value* value40 = builder.CreateAdd(value25, ConstantInt::get(builder.getInt32Ty(), 1, true));
    Value* value41 = builder.CreateICmpUGT(value40, value9);
    builder.CreateCondBr(value41, basicBlock20, basicBlock24);

    value12 -> addIncoming(ConstantInt::get(builder.getInt32Ty(), 0, true), basicBlock3);
    value12 -> addIncoming(value21, basicBlock20);

    value14->addIncoming(value4, basicBlock7);
    value14->addIncoming(value22, basicBlock20);

    value15->addIncoming(ConstantInt::get(builder.getInt32Ty(), 0, true), basicBlock7);
    value15->addIncoming(value21, basicBlock20);

    value21->addIncoming(value15, basicBlock13);
    value21->addIncoming(value39, basicBlock38);

    value25->addIncoming(value8, basicBlock16);
    value25->addIncoming(value40, basicBlock38);

    value26->addIncoming(value15, basicBlock16);
    value26->addIncoming(value39, basicBlock38);

    value39->addIncoming(value37, basicBlock32);
    value39->addIncoming(value26, basicBlock24);
}

void createCalcGen(Module& module) {
    LLVMContext& context = module.getContext();
    Function *calcGen = module.getFunction("calcGen");
    IRBuilder<> builder(context);

    Value* value0 = calcGen->getArg(0);
    Value* value1 = calcGen->getArg(1);

    BasicBlock* basicBlock2 = BasicBlock::Create(context, "", calcGen);
    BasicBlock* basicBlock3 = BasicBlock::Create(context, "", calcGen);
    BasicBlock* basicBlock6 = BasicBlock::Create(context, "", calcGen);
    BasicBlock* basicBlock7 = BasicBlock::Create(context, "", calcGen);
    BasicBlock* basicBlock10 = BasicBlock::Create(context, "", calcGen);


    builder.SetInsertPoint(basicBlock2);
    builder.CreateBr(basicBlock3);

    builder.SetInsertPoint(basicBlock3);
    //TODO
    PHINode* value4 = builder.CreatePHI(builder.getInt64Ty(), 1);
    Value* value5 = builder.CreateNUWMul(value4, ConstantInt::get(builder.getInt64Ty(), 80, true));
    builder.CreateBr(basicBlock10);

    builder.SetInsertPoint(basicBlock6);
    builder.CreateRetVoid();

    builder.SetInsertPoint(basicBlock7);
    Value* value8 = builder.CreateNUWAdd(value4, ConstantInt::get(builder.getInt64Ty(), 1, true));
    Value* value9 = builder.CreateICmpEQ(value8, ConstantInt::get(builder.getInt64Ty(), 60, true));
    builder.CreateCondBr(value9, basicBlock6, basicBlock3);

    builder.SetInsertPoint(basicBlock10);
    //TODO
    PHINode* value11 = builder.CreatePHI(builder.getInt64Ty(), 1);
    Value* value12 = builder.CreateTrunc(value11, builder.getInt32Ty());
    Value* value13 = builder.CreateTrunc(value4, builder.getInt32Ty());
    ArrayRef<Type*> calcNeighboursParams = {builder.getInt32Ty()->getPointerTo(),
                                            builder.getInt32Ty(),
                                            builder.getInt32Ty()};
    Type *int32Ty = Type::getInt32Ty(context);
    FunctionType* calNeighboursType = FunctionType::get(int32Ty, calcNeighboursParams, false);
    FunctionCallee calcNeighbours = module.getOrInsertFunction("calcNeighbours", calNeighboursType);
    ArrayRef<Value*> calcNeighboursArgs= {value0, value13, value12};
    Value* value14 = builder.CreateCall(calcNeighbours, calcNeighboursArgs);
    Value* value15 = builder.CreateNUWAdd(value11, value5);
    Value* value16 = builder.CreateInBoundsGEP(builder.getInt32Ty(), value0, value15);
    Value* value17 = builder.CreateLoad(builder.getInt32Ty(), value16);
    Value* value18 = builder.CreateICmpEQ(value17,
                                          ConstantInt::get(builder.getInt32Ty(), 0,true));
    Value* value19 = builder.CreateAnd(value14,
                                       ConstantInt::get(builder.getInt32Ty(), -2, true));
    Value* value20 = builder.CreateICmpEQ(value19,
                                          ConstantInt::get(builder.getInt32Ty(), 2, true));
    Value* value21 = builder.CreateICmpEQ(value14,
                                          ConstantInt::get(builder.getInt32Ty(), 3, true));
    Value* value22 = builder.CreateSelect(value18, value21, value20);
    Value* value23 = builder.CreateZExt(value22, builder.getInt32Ty());
    Value* value24 = builder.CreateInBoundsGEP(value1, value15);
    builder.CreateStore(value23, value24);
    Value* value25 = builder.CreateNSWAdd(value11,
                                          ConstantInt::get(builder.getInt64Ty(), 1, true));
    Value* value26 = builder.CreateICmpEQ(value25,
                                          ConstantInt::get(builder.getInt64Ty(), 80, true));
    builder.CreateCondBr(value26, basicBlock7, basicBlock10);

    value4->addIncoming(ConstantInt::get(builder.getInt64Ty(), 0, true), basicBlock2);
    value4->addIncoming(value8, basicBlock7);

    value11->addIncoming(ConstantInt::get(builder.getInt64Ty(), 0, true), basicBlock3);
    value11->addIncoming(value25, basicBlock10);
}

void createDrawGen(Module& module) {
    LLVMContext& context = module.getContext();
    IRBuilder<> builder(context);
    Function *drawGen = module.getFunction("drawGen");

    BasicBlock* basicBlock1 = BasicBlock::Create(context, "", drawGen);
    BasicBlock* basicBlock2 = BasicBlock::Create(context, "", drawGen);
    BasicBlock* basicBlock5 = BasicBlock::Create(context, "", drawGen);
    BasicBlock* basicBlock6 = BasicBlock::Create(context, "", drawGen);
    BasicBlock* basicBlock9 = BasicBlock::Create(context, "", drawGen);

    builder.SetInsertPoint(basicBlock1);
    builder.CreateBr(basicBlock2);

    builder.SetInsertPoint(basicBlock2);
    //TODO
    PHINode* value3 = builder.CreatePHI(builder.getInt64Ty(), 1);
    Value* value4 = builder.CreateNUWMul(value3, ConstantInt::get(builder.getInt64Ty(), 80, false));
    builder.CreateBr(basicBlock9);

    builder.SetInsertPoint(basicBlock5);
    ArrayRef<Type*> simFlushParams = {};
    FunctionType* simFlushType = FunctionType::get(Type::getVoidTy(context), simFlushParams, false);
    FunctionCallee simFlush = module.getOrInsertFunction("simFlush", simFlushType);
    builder.CreateCall(simFlush);
    builder.CreateRetVoid();

    builder.SetInsertPoint(basicBlock6);
    Value* value7 = builder.CreateNUWAdd(value3, ConstantInt::get(builder.getInt64Ty(), 1, true));
    Value* value8 = builder.CreateICmpEQ(value7, ConstantInt::get(builder.getInt64Ty(), 60, true));
    builder.CreateCondBr(value8, basicBlock5, basicBlock2);

    builder.SetInsertPoint(basicBlock9);
    PHINode* value10 = builder.CreatePHI(builder.getInt64Ty(), 1);
    Value* value11 = builder.CreateNUWAdd(value10, value4);
    Value* value12 = builder.CreateInBoundsGEP(builder.getInt32Ty(), drawGen->getArg(0), value11);
    Value* value13 = builder.CreateLoad(builder.getInt32Ty(), value12);
    Value* value14 = builder.CreateMul(value13, ConstantInt::get(builder.getInt32Ty(), 65280, true));
    Value* value15 = builder.CreateAdd(value14,ConstantInt::get(builder.getInt32Ty(), -16777216, true));
    Value* value16 = builder.CreateTrunc(value10, builder.getInt32Ty());
    Value* value17 = builder.CreateTrunc(value3, builder.getInt32Ty());
    Type *Int32Type = Type::getInt32Ty(context);
    Type *VoidType = Type::getVoidTy(context);
    ArrayRef<Type*> simSetPixelParams = {Int32Type, Int32Type, Int32Type};
    FunctionType* simSetPixelType = FunctionType::get(VoidType, simSetPixelParams, false);
    FunctionCallee simSetPixel = module.getOrInsertFunction("simSetPixel", simSetPixelType);
    ArrayRef<Value*> simSetPixelArgs = {value16, value17, value15};
    builder.CreateCall(simSetPixel, simSetPixelArgs);
    Value* value18 = builder.CreateNUWAdd(value10, ConstantInt::get(builder.getInt64Ty(), 1, true));
    Value* value19 = builder.CreateICmpEQ(value18, ConstantInt::get(builder.getInt64Ty(), 80, true));
    builder.CreateCondBr(value19, basicBlock6, basicBlock9);

    value3->addIncoming(ConstantInt::get(builder.getInt64Ty(), 0, true), basicBlock1);
    value3->addIncoming(value7, basicBlock6);

    value10->addIncoming(ConstantInt::get(builder.getInt64Ty(), 0, true), basicBlock2);
    value10->addIncoming(value18, basicBlock9);
}

void createInitGen(Module& module) {
    LLVMContext& context = module.getContext();
    IRBuilder<> builder(context);
    Function *initGen = module.getFunction("initGen");

    BasicBlock* basicBlock1 = BasicBlock::Create(context, "", initGen);
    BasicBlock* basicBlock2 = BasicBlock::Create(context, "", initGen);
    BasicBlock* basicBlock5 = BasicBlock::Create(context, "", initGen);
    BasicBlock* basicBlock6 = BasicBlock::Create(context, "", initGen);
    BasicBlock* basicBlock9 = BasicBlock::Create(context, "", initGen);

    builder.SetInsertPoint(basicBlock1);
    builder.CreateBr(basicBlock2);

    builder.SetInsertPoint(basicBlock2);
    PHINode* value3 = builder.CreatePHI(builder.getInt64Ty(), 1);
    Value* value4 = builder.CreateNUWMul(value3,
                                         ConstantInt::get(builder.getInt64Ty(), 80, true));
    builder.CreateBr(basicBlock9);

    builder.SetInsertPoint(basicBlock5);
    builder.CreateRetVoid();

    builder.SetInsertPoint(basicBlock6);
    Value* value7 = builder.CreateNUWAdd(value3,
                                         ConstantInt::get(builder.getInt64Ty(), 1, true));
    Value* value8 = builder.CreateICmpEQ(value7,
                                         ConstantInt::get(builder.getInt64Ty(), 60, true));
    builder.CreateCondBr(value8, basicBlock5, basicBlock2);

    builder.SetInsertPoint(basicBlock9);
    PHINode* value10 = builder.CreatePHI(builder.getInt64Ty(), 1);
    ArrayRef<Type*> simRandParams = {};
    Type *Int32Type = Type::getInt32Ty(context);
    FunctionType* simRandType = FunctionType::get(Int32Type, simRandParams, false);
    FunctionCallee simRand = module.getOrInsertFunction("simRand", simRandType);
    Value* value11 = builder.CreateCall(simRand);
    Value* value12 = builder.CreateNUWAdd(value10, value4);
    Value* value13 = builder.CreateInBoundsGEP(builder.getInt32Ty(), initGen->getArg(0), value12);
    builder.CreateStore(value11, value13);
    Value* value14 = builder.CreateNUWAdd(value10,ConstantInt::get(builder.getInt64Ty(), 1, true));
    Value* value15 = builder.CreateICmpEQ(value14, ConstantInt::get(builder.getInt64Ty(), 80, true));
    builder.CreateCondBr(value15, basicBlock6, basicBlock9);

    value3->addIncoming(ConstantInt::get(builder.getInt64Ty(), 0, true), basicBlock1);
    value3->addIncoming(value7, basicBlock6);

    value10->addIncoming(ConstantInt::get(builder.getInt64Ty(), 0, true), basicBlock2);
    value10->addIncoming(value14, basicBlock9);
}

void createMainFunc(Module& module) {
    LLVMContext& context = module.getContext();
    IRBuilder<> builder(context);
    Function* mainFunc = module.getFunction("main");

    Type *VoidType = Type::getVoidTy(context);
    Type *BoolType = Type::getInt1Ty(context);
    Type *Int64Type = Type::getInt64Ty(context);
    Type *Int8PtType = Type::getInt8PtrTy(context);

    BasicBlock* basicBlock0 = BasicBlock::Create(context, "", mainFunc);
    BasicBlock* basicBlock7 = BasicBlock::Create(context, "", mainFunc);
    BasicBlock* basicBlock9 = BasicBlock::Create(context, "", mainFunc);
    BasicBlock* basicBlock13 = BasicBlock::Create(context, "", mainFunc);

    builder.SetInsertPoint(basicBlock0);
    Type* i32 = ArrayType::get(Type::getInt32Ty(context), 4800);
    AllocaInst *value1 = builder.CreateAlloca(i32, nullptr);
    AllocaInst *value2 = builder.CreateAlloca(i32, nullptr);
    Value* value3 = builder.CreateBitCast(value1,
                                          PointerType::get(Type::getInt8Ty(context), 0));
    Value* value4 = builder.CreateBitCast(value2,
                                          PointerType::get(Type::getInt8Ty(context), 0));
    // Вызов llvm.lifetime.start.p0i8
    ArrayRef<Type*> lifetimeStartParams = {Int64Type, Int8PtType};
    FunctionType* lifetimeStartType = FunctionType::get(VoidType, lifetimeStartParams, false);
    FunctionCallee lifeTimeStart = module.getOrInsertFunction("llvm.lifetime.start.p0i8", lifetimeStartType);
    ArrayRef<Value*> lifetimeArgs= {ConstantInt::get(builder.getInt64Ty(), 19200, true), value3};
    ArrayRef<Value*> lifetimeStartArgs = {ConstantInt::get(builder.getInt64Ty(), 19200, true), value4};
    builder.CreateCall(lifeTimeStart, lifetimeArgs);
    builder.CreateCall(lifeTimeStart, lifetimeStartArgs);
    //
    Value* zero = ConstantInt::get(Type::getInt64Ty(context), 0);
    Value* indices[] = {zero, zero};
    Value* value5 = builder.CreateInBoundsGEP(value2, indices);
    ArrayRef<Type*> simInitParams = {};
    FunctionType* simInitType = FunctionType::get(VoidType, simInitParams, false);
    FunctionCallee simInit = module.getOrInsertFunction("simInit", simInitType);
    builder.CreateCall(simInit);
    //initGen
    ArrayRef<Type*> initGenParams = {builder.getInt32Ty()->getPointerTo()};
    FunctionType* initGenType = FunctionType::get(VoidType, initGenParams, false);
    FunctionCallee initGen = module.getOrInsertFunction("initGen", initGenType);
    builder.CreateCall(initGen, {value5});
    //
    //simEvent
    ArrayRef<Type*> simEventParams = {};
    FunctionType* simEventType = FunctionType::get(BoolType, simEventParams, false);
    FunctionCallee simEvent = module.getOrInsertFunction("simEvent", simEventType);
    Value* value6 = builder.CreateCall(simEvent);
    builder.CreateCondBr(value6, basicBlock7, basicBlock13);
    //

    builder.SetInsertPoint(basicBlock7);
    Value* value8 = builder.CreateInBoundsGEP(value1, indices);
    builder.CreateBr(basicBlock9);

    builder.SetInsertPoint(basicBlock9);
    PHINode* value10 = builder.CreatePHI(Type::getInt32PtrTy(context), 0);
    PHINode* value11 = builder.CreatePHI(Type::getInt32PtrTy(context), 0);
    ArrayRef<Type*> calcGenParams = {builder.getInt32Ty()->getPointerTo(),
                                     builder.getInt32Ty()->getPointerTo()};
    FunctionType* calcGenType = FunctionType::get(VoidType, calcGenParams, false);
    FunctionCallee calcGen = module.getOrInsertFunction("calcGen", calcGenType);
    builder.CreateCall(calcGen, {value10, value10});
    ArrayRef<Type*> drawGenParams = {builder.getInt32Ty()->getPointerTo()};
    FunctionType* drawGenType = FunctionType::get(VoidType, drawGenParams, false);
    FunctionCallee drawGen = module.getOrInsertFunction("drawGen", drawGenType);
    builder.CreateCall(drawGen, {value11});
    Value* value12 = builder.CreateCall(simEvent);
    builder.CreateCondBr(value12, basicBlock9, basicBlock13);

    builder.SetInsertPoint(basicBlock13);
    //simExit
    ArrayRef<Type*> simExitParams = {};
    FunctionType* simExitType = FunctionType::get(VoidType, simExitParams, false);
    FunctionCallee simExit = module.getOrInsertFunction("simExit", simExitType);
    builder.CreateCall(simExit);
    //lifetimeEnd
    ArrayRef<Type*> lifetimeEndParams = {Int64Type, Int8PtType};
    FunctionType* lifetimeEndType = FunctionType::get(VoidType, lifetimeEndParams, false);
    FunctionCallee lifetimeEnd = module.getOrInsertFunction("llvm.lifetime.end.p0i8", lifetimeEndType);
    builder.CreateCall(lifetimeEnd,
                       {ConstantInt::get(builder.getInt64Ty(), 19200, true), value4});
    builder.CreateCall(lifetimeEnd,
                       {ConstantInt::get(builder.getInt64Ty(), 19200, true), value3});
    builder.CreateRet(ConstantInt::get(builder.getInt32Ty(), 0, true));

    value10->addIncoming(value11, basicBlock9);
    value10->addIncoming(value8, basicBlock7);

    value11->addIncoming(value10, basicBlock9);
    value11->addIncoming(value5,basicBlock7);

}



int main() {
    LLVMContext context;
    Module* module = new Module("../Conway-Game-Of-Life/life.cpp", context);
    IRBuilder<> builder(context);
    declareFunctions(*module);
    createCalcNeighbours(*module);
    createCalcGen(*module);
    createDrawGen(*module);
    createInitGen(*module);
    createMainFunc(*module);

    verifyModule(*module, &outs());
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    ExecutionEngine* executionEngine = EngineBuilder(std::unique_ptr<Module>(module)).create();
    executionEngine->InstallLazyFunctionCreator([&](const std::string &fnName) -> void *{
        if (fnName == "simSetPixel") {
            return reinterpret_cast<void *>(simSetPixel);
        } else if (fnName == "simInit") {
            return reinterpret_cast<void *>(simInit);
        } else if (fnName == "simExit") {
            return reinterpret_cast<void *>(simExit);
        } else if (fnName == "simEvent") {
            return reinterpret_cast<void *>(simEvent);
        } else if (fnName == "simFlush") {
            return reinterpret_cast<void *>(simFlush);
        } else if (fnName == "simRand") {
            return reinterpret_cast<void *>(simRand);
        }
        return nullptr;
    });

    executionEngine->finalizeObject();
    ArrayRef<GenericValue> noargs;
    executionEngine->runFunction(module->getFunction("main"), noargs);

    outs() << *module;
    return 0;
}