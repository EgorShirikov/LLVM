; ModuleID = 'life.cpp'
source_filename = "life.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx13.0.0"

; Function Attrs: norecurse nounwind readonly ssp uwtable willreturn mustprogress
define dso_local i32 @calcNeighbours(i32* nocapture readonly %0, i32 %1, i32 %2) local_unnamed_addr #0 {
  %4 = add i32 %1, -1
  %5 = add i32 %1, 1
  %6 = icmp ugt i32 %4, %5
  br i1 %6, label %11, label %7

7:                                                ; preds = %3
  %8 = add i32 %2, -1
  %9 = add i32 %2, 1
  %10 = icmp ugt i32 %8, %9
  br label %13

11:                                               ; preds = %20, %3
  %12 = phi i32 [ 0, %3 ], [ %21, %20 ]
  ret i32 %12

13:                                               ; preds = %7, %20
  %14 = phi i32 [ %4, %7 ], [ %22, %20 ]
  %15 = phi i32 [ 0, %7 ], [ %21, %20 ]
  br i1 %10, label %20, label %16

16:                                               ; preds = %13
  %17 = icmp ugt i32 %14, 59
  %18 = icmp eq i32 %14, %1
  %19 = mul i32 %14, 80
  br label %24

20:                                               ; preds = %38, %13
  %21 = phi i32 [ %15, %13 ], [ %39, %38 ]
  %22 = add i32 %14, 1
  %23 = icmp ugt i32 %22, %5
  br i1 %23, label %11, label %13, !llvm.loop !7

24:                                               ; preds = %16, %38
  %25 = phi i32 [ %8, %16 ], [ %40, %38 ]
  %26 = phi i32 [ %15, %16 ], [ %39, %38 ]
  %27 = icmp ugt i32 %25, 79
  %28 = or i1 %17, %27
  %29 = icmp eq i32 %25, %2
  %30 = and i1 %18, %29
  %31 = or i1 %28, %30
  br i1 %31, label %38, label %32

32:                                               ; preds = %24
  %33 = add i32 %25, %19
  %34 = zext i32 %33 to i64
  %35 = getelementptr inbounds i32, i32* %0, i64 %34
  %36 = load i32, i32* %35, align 4, !tbaa !10
  %37 = add i32 %36, %26
  br label %38

38:                                               ; preds = %24, %32
  %39 = phi i32 [ %37, %32 ], [ %26, %24 ]
  %40 = add i32 %25, 1
  %41 = icmp ugt i32 %40, %9
  br i1 %41, label %20, label %24, !llvm.loop !14
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: nofree norecurse nounwind ssp uwtable mustprogress
define dso_local void @calcGen(i32* nocapture readonly %0, i32* nocapture %1) local_unnamed_addr #2 {
  br label %3

3:                                                ; preds = %2, %7
  %4 = phi i64 [ 0, %2 ], [ %8, %7 ]
  %5 = mul nuw nsw i64 %4, 80
  br label %10

6:                                                ; preds = %7
  ret void

7:                                                ; preds = %10
  %8 = add nuw nsw i64 %4, 1
  %9 = icmp eq i64 %8, 60
  br i1 %9, label %6, label %3, !llvm.loop !15

10:                                               ; preds = %3, %10
  %11 = phi i64 [ 0, %3 ], [ %25, %10 ]
  %12 = trunc i64 %11 to i32
  %13 = trunc i64 %4 to i32
  %14 = call i32 @calcNeighbours(i32* %0, i32 %13, i32 %12)
  %15 = add nuw nsw i64 %11, %5
  %16 = getelementptr inbounds i32, i32* %0, i64 %15
  %17 = load i32, i32* %16, align 4, !tbaa !10
  %18 = icmp eq i32 %17, 0
  %19 = and i32 %14, -2
  %20 = icmp eq i32 %19, 2
  %21 = icmp eq i32 %14, 3
  %22 = select i1 %18, i1 %21, i1 %20
  %23 = zext i1 %22 to i32
  %24 = getelementptr inbounds i32, i32* %1, i64 %15
  store i32 %23, i32* %24, align 4, !tbaa !10
  %25 = add nuw nsw i64 %11, 1
  %26 = icmp eq i64 %25, 80
  br i1 %26, label %7, label %10, !llvm.loop !16
}

; Function Attrs: ssp uwtable mustprogress
define dso_local void @drawGen(i32* nocapture readonly %0) local_unnamed_addr #3 {
  br label %2

2:                                                ; preds = %1, %6
  %3 = phi i64 [ 0, %1 ], [ %7, %6 ]
  %4 = mul nuw nsw i64 %3, 80
  br label %9

5:                                                ; preds = %6
  call void @simFlush()
  ret void

6:                                                ; preds = %9
  %7 = add nuw nsw i64 %3, 1
  %8 = icmp eq i64 %7, 60
  br i1 %8, label %5, label %2, !llvm.loop !17

9:                                                ; preds = %2, %9
  %10 = phi i64 [ 0, %2 ], [ %18, %9 ]
  %11 = add nuw nsw i64 %10, %4
  %12 = getelementptr inbounds i32, i32* %0, i64 %11
  %13 = load i32, i32* %12, align 4, !tbaa !10
  %14 = mul i32 %13, 65280
  %15 = add i32 %14, -16777216
  %16 = trunc i64 %10 to i32
  %17 = trunc i64 %3 to i32
  call void @simSetPixel(i32 %16, i32 %17, i32 %15)
  %18 = add nuw nsw i64 %10, 1
  %19 = icmp eq i64 %18, 80
  br i1 %19, label %6, label %9, !llvm.loop !18
}

declare void @simSetPixel(i32, i32, i32) local_unnamed_addr #4

declare void @simFlush() local_unnamed_addr #4

; Function Attrs: ssp uwtable mustprogress
define dso_local void @initGen(i32* nocapture %0) local_unnamed_addr #3 {
  br label %2

2:                                                ; preds = %1, %6
  %3 = phi i64 [ 0, %1 ], [ %7, %6 ]
  %4 = mul nuw nsw i64 %3, 80
  br label %9

5:                                                ; preds = %6
  ret void

6:                                                ; preds = %9
  %7 = add nuw nsw i64 %3, 1
  %8 = icmp eq i64 %7, 60
  br i1 %8, label %5, label %2, !llvm.loop !19

9:                                                ; preds = %2, %9
  %10 = phi i64 [ 0, %2 ], [ %14, %9 ]
  %11 = call i32 @simRand()
  %12 = add nuw nsw i64 %10, %4
  %13 = getelementptr inbounds i32, i32* %0, i64 %12
  store i32 %11, i32* %13, align 4, !tbaa !10
  %14 = add nuw nsw i64 %10, 1
  %15 = icmp eq i64 %14, 80
  br i1 %15, label %6, label %9, !llvm.loop !20
}

declare i32 @simRand() local_unnamed_addr #4

; Function Attrs: norecurse ssp uwtable mustprogress
define dso_local i32 @main() local_unnamed_addr #5 {
  %1 = alloca [4800 x i32], align 4
  %2 = alloca [4800 x i32], align 4
  %3 = bitcast [4800 x i32]* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 19200, i8* nonnull %3) #6
  %4 = bitcast [4800 x i32]* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 19200, i8* nonnull %4) #6
  %5 = getelementptr inbounds [4800 x i32], [4800 x i32]* %2, i64 0, i64 0
  call void @simInit()
  call void @initGen(i32* nonnull %5)
  %6 = call zeroext i1 @simEvent()
  br i1 %6, label %7, label %13

7:                                                ; preds = %0
  %8 = getelementptr inbounds [4800 x i32], [4800 x i32]* %1, i64 0, i64 0
  br label %9

9:                                                ; preds = %7, %9
  %10 = phi i32* [ %11, %9 ], [ %8, %7 ]
  %11 = phi i32* [ %10, %9 ], [ %5, %7 ]
  call void @calcGen(i32* %11, i32* %10)
  call void @drawGen(i32* %11)
  %12 = call zeroext i1 @simEvent()
  br i1 %12, label %9, label %13, !llvm.loop !21

13:                                               ; preds = %9, %0
  call void @simExit()
  call void @llvm.lifetime.end.p0i8(i64 19200, i8* nonnull %4) #6
  call void @llvm.lifetime.end.p0i8(i64 19200, i8* nonnull %3) #6
  ret i32 0
}

declare void @simInit() local_unnamed_addr #4

declare zeroext i1 @simEvent() local_unnamed_addr #4

declare void @simExit() local_unnamed_addr #4

attributes #0 = { norecurse nounwind readonly ssp uwtable willreturn mustprogress "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { nofree norecurse nounwind ssp uwtable mustprogress "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { ssp uwtable mustprogress "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { norecurse ssp uwtable mustprogress "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5}
!llvm.ident = !{!6}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"branch-target-enforcement", i32 0}
!2 = !{i32 1, !"sign-return-address", i32 0}
!3 = !{i32 1, !"sign-return-address-all", i32 0}
!4 = !{i32 1, !"sign-return-address-with-bkey", i32 0}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{!"Homebrew clang version 12.0.1"}
!7 = distinct !{!7, !8, !9}
!8 = !{!"llvm.loop.mustprogress"}
!9 = !{!"llvm.loop.unroll.disable"}
!10 = !{!11, !11, i64 0}
!11 = !{!"int", !12, i64 0}
!12 = !{!"omnipotent char", !13, i64 0}
!13 = !{!"Simple C++ TBAA"}
!14 = distinct !{!14, !8, !9}
!15 = distinct !{!15, !8, !9}
!16 = distinct !{!16, !8, !9}
!17 = distinct !{!17, !8, !9}
!18 = distinct !{!18, !8, !9}
!19 = distinct !{!19, !8, !9}
!20 = distinct !{!20, !8, !9}
!21 = distinct !{!21, !8, !9}
