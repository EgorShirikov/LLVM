; ModuleID = '../Conway-Game-Of-Life/life.cpp'
source_filename = "../Conway-Game-Of-Life/life.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"

define i32 @calcNeighbours(i32* %0, i32 %1, i32 %2) {
  %4 = add i32 %1, -1
  %5 = add i32 %1, 1
  %6 = icmp ugt i32 %4, %5
  br i1 %6, label %13, label %7

7:                                                ; preds = %3
  %8 = add i32 %2, -1
  %9 = add i32 %2, 1
  %10 = mul i32 %1, 80
  %11 = add i32 %2, %10
  %12 = add i32 %11, -81
  br label %15

13:                                               ; preds = %20, %3
  %14 = phi i32 [ 0, %3 ], [ %21, %20 ]
  ret i32 %14

15:                                               ; preds = %20, %7
  %lsr.iv2 = phi i32 [ %lsr.iv.next3, %20 ], [ %12, %7 ]
  %16 = phi i32 [ %4, %7 ], [ %22, %20 ]
  %17 = phi i32 [ 0, %7 ], [ %21, %20 ]
  %18 = icmp ugt i32 %8, %9
  br i1 %18, label %20, label %19

19:                                               ; preds = %15
  br label %24

20:                                               ; preds = %40, %15
  %21 = phi i32 [ %17, %15 ], [ %41, %40 ]
  %22 = add i32 %16, 1
  %lsr.iv.next3 = add i32 %lsr.iv2, 80
  %23 = icmp ugt i32 %22, %5
  br i1 %23, label %13, label %15

24:                                               ; preds = %40, %19
  %lsr.iv = phi i32 [ %lsr.iv.next, %40 ], [ 0, %19 ]
  %25 = phi i32 [ %17, %19 ], [ %41, %40 ]
  %26 = icmp eq i32 %16, %1
  %27 = icmp ugt i32 %16, 59
  %28 = add i32 %8, %lsr.iv
  %29 = icmp ugt i32 %28, 79
  %30 = or i1 %27, %29
  %31 = icmp eq i32 %lsr.iv, 1
  %32 = and i1 %26, %31
  %33 = or i1 %30, %32
  br i1 %33, label %34, label %40

34:                                               ; preds = %24
  %35 = add i32 %lsr.iv2, %lsr.iv
  %36 = zext i32 %35 to i64
  %37 = getelementptr inbounds i32, i32* %0, i64 %36
  %38 = load i32, i32* %37, align 4
  %39 = add i32 %38, %25
  br label %40

40:                                               ; preds = %34, %24
  %41 = phi i32 [ %39, %34 ], [ %25, %24 ]
  %lsr.iv.next = add i32 %lsr.iv, 1
  %42 = add i32 %8, %lsr.iv.next
  %43 = icmp ugt i32 %42, %9
  br i1 %43, label %20, label %24
}

define void @calcGen(i32* %0, i32* %1) {
  br label %3

3:                                                ; preds = %6, %2
  %lsr.iv2 = phi i32* [ %scevgep3, %6 ], [ %0, %2 ]
  %lsr.iv = phi i32* [ %scevgep, %6 ], [ %1, %2 ]
  %4 = phi i64 [ 0, %2 ], [ %7, %6 ]
  br label %9

5:                                                ; preds = %6
  ret void

6:                                                ; preds = %9
  %7 = add nuw i64 %4, 1
  %scevgep = getelementptr i32, i32* %lsr.iv, i64 80
  %scevgep3 = getelementptr i32, i32* %lsr.iv2, i64 80
  %8 = icmp eq i64 %7, 60
  br i1 %8, label %5, label %3

9:                                                ; preds = %9, %3
  %10 = phi i64 [ 0, %3 ], [ %20, %9 ]
  %11 = trunc i64 %4 to i32
  %tmp = trunc i64 %10 to i32
  %12 = call i32 @calcNeighbours(i32* %0, i32 %11, i32 %tmp)
  %scevgep4 = getelementptr i32, i32* %lsr.iv2, i64 %10
  %13 = load i32, i32* %scevgep4, align 4
  %14 = icmp eq i32 %13, 0
  %15 = and i32 %12, -2
  %16 = icmp eq i32 %15, 2
  %17 = icmp eq i32 %12, 3
  %18 = select i1 %14, i1 %17, i1 %16
  %19 = zext i1 %18 to i32
  %scevgep1 = getelementptr i32, i32* %lsr.iv, i64 %10
  store i32 %19, i32* %scevgep1, align 4
  %20 = add nsw i64 %10, 1
  %21 = icmp eq i64 %20, 80
  br i1 %21, label %6, label %9
}

define void @drawGen(i32* %0) {
  br label %2

2:                                                ; preds = %5, %1
  %lsr.iv = phi i32* [ %scevgep, %5 ], [ %0, %1 ]
  %3 = phi i64 [ 0, %1 ], [ %6, %5 ]
  br label %8

4:                                                ; preds = %5
  call void @simFlush()
  ret void

5:                                                ; preds = %8
  %6 = add nuw i64 %3, 1
  %scevgep = getelementptr i32, i32* %lsr.iv, i64 80
  %7 = icmp eq i64 %6, 60
  br i1 %7, label %4, label %2

8:                                                ; preds = %8, %2
  %9 = phi i64 [ 0, %2 ], [ %14, %8 ]
  %scevgep1 = getelementptr i32, i32* %lsr.iv, i64 %9
  %10 = load i32, i32* %scevgep1, align 4
  %11 = mul i32 %10, 65280
  %12 = add i32 %11, -16777216
  %13 = trunc i64 %3 to i32
  %tmp = trunc i64 %9 to i32
  call void @simSetPixel(i32 %tmp, i32 %13, i32 %12)
  %14 = add nuw i64 %9, 1
  %15 = icmp eq i64 %14, 80
  br i1 %15, label %5, label %8
}

define void @initGen(i32* %0) {
  br label %2

2:                                                ; preds = %5, %1
  %lsr.iv1 = phi i32* [ %scevgep, %5 ], [ %0, %1 ]
  %3 = phi i64 [ 0, %1 ], [ %6, %5 ]
  br label %8

4:                                                ; preds = %5
  ret void

5:                                                ; preds = %8
  %6 = add nuw i64 %3, 1
  %scevgep = getelementptr i32, i32* %lsr.iv1, i64 80
  %7 = icmp eq i64 %6, 60
  br i1 %7, label %4, label %2

8:                                                ; preds = %8, %2
  %lsr.iv = phi i64 [ %lsr.iv.next, %8 ], [ 0, %2 ]
  %9 = bitcast i32* %lsr.iv1 to i8*
  %10 = call i32 @simRand()
  %uglygep = getelementptr i8, i8* %9, i64 %lsr.iv
  %uglygep3 = bitcast i8* %uglygep to i32*
  store i32 %10, i32* %uglygep3, align 4
  %lsr.iv.next = add nuw nsw i64 %lsr.iv, 4
  %11 = icmp eq i64 %lsr.iv.next, 320
  br i1 %11, label %5, label %8
}

define i32 @main() {
  %1 = alloca [4800 x i32], align 4
  %2 = alloca [4800 x i32], align 4
  %3 = bitcast [4800 x i32]* %1 to i8*
  %4 = bitcast [4800 x i32]* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 19200, i8* %3)
  call void @llvm.lifetime.start.p0i8(i64 19200, i8* %4)
  %5 = bitcast [4800 x i32]* %2 to i32*
  call void @simInit()
  call void @initGen(i32* %5)
  %6 = call i1 @simEvent()
  br i1 %6, label %7, label %14

7:                                                ; preds = %0
  %8 = bitcast [4800 x i32]* %2 to i32*
  %9 = bitcast [4800 x i32]* %1 to i32*
  br label %10

10:                                               ; preds = %10, %7
  %11 = phi i32* [ %12, %10 ], [ %9, %7 ]
  %12 = phi i32* [ %11, %10 ], [ %8, %7 ]
  call void @calcGen(i32* %11, i32* %11)
  call void @drawGen(i32* %12)
  %13 = call i1 @simEvent()
  br i1 %13, label %10, label %14

14:                                               ; preds = %10, %0
  %15 = bitcast [4800 x i32]* %2 to i8*
  %16 = bitcast [4800 x i32]* %1 to i8*
  call void @simExit()
  call void @llvm.lifetime.end.p0i8(i64 19200, i8* %15)
  call void @llvm.lifetime.end.p0i8(i64 19200, i8* %16)
  ret i32 0
}

declare void @simFlush()

declare void @simSetPixel(i32, i32, i32)

declare i32 @simRand()

declare void @simInit()

declare void @simExit()

declare i1 @simEvent()

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #0

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #0

attributes #0 = { argmemonly nofree nosync nounwind willreturn }
