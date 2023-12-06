; ModuleID = 'life.cpp'
source_filename = "life.cpp"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx13.0.0"

; Function Attrs: norecurse optsize ssp uwtable mustprogress
define dso_local i32 @main() local_unnamed_addr #0 {
  %1 = alloca [1200 x i32], align 8
  %2 = alloca [1200 x i32], align 8
  %3 = getelementptr inbounds [1200 x i32], [1200 x i32]* %2, i64 0, i64 0
  tail call void @simInit() #2
  br label %4

4:                                                ; preds = %4, %0
  %5 = phi i64 [ 0, %0 ], [ %8, %4 ]
  %6 = tail call i32 @simRand() #2
  %7 = getelementptr inbounds [1200 x i32], [1200 x i32]* %2, i64 0, i64 %5
  store i32 %6, i32* %7, align 4, !tbaa !7
  %8 = add nuw nsw i64 %5, 1
  %9 = icmp eq i64 %8, 4800
  br i1 %9, label %10, label %4, !llvm.loop !11

10:                                               ; preds = %4
  %11 = tail call zeroext i1 @simEvent() #2
  br i1 %11, label %12, label %80

12:                                               ; preds = %10
  %13 = getelementptr inbounds [1200 x i32], [1200 x i32]* %1, i64 0, i64 0
  br label %14

14:                                               ; preds = %12, %78
  %15 = phi i32* [ %16, %78 ], [ %13, %12 ]
  %16 = phi i32* [ %15, %78 ], [ %3, %12 ]
  br label %17

17:                                               ; preds = %14, %56
  %18 = phi i64 [ %66, %56 ], [ 0, %14 ]
  %19 = phi i32 [ %67, %56 ], [ 0, %14 ]
  %20 = trunc i32 %19 to i16

  %21 = freeze i16 %20
  %22 = udiv i16 %21, 80
  %23 = zext i16 %22 to i32
  %24 = mul i16 %22, 80

  %25 = sub i16 %21, %24
  %26 = zext i16 %25 to i32
  %27 = add nsw i32 %23, -1
  %28 = add nsw i32 %26, -1
  br label %29

29:                                               ; preds = %35, %17
  %30 = phi i32 [ %27, %17 ], [ %36, %35 ]
  %31 = phi i32 [ 0, %17 ], [ %53, %35 ]
  %32 = icmp ugt i32 %30, 59
  %33 = icmp eq i32 %30, %23
  %34 = mul nuw nsw i32 %30, 80
  br label %38

35:                                               ; preds = %52
  %36 = add nsw i32 %30, 1
  %37 = icmp sgt i32 %30, %23
  br i1 %37, label %56, label %29, !llvm.loop !13

38:                                               ; preds = %52, %29
  %39 = phi i32 [ %28, %29 ], [ %54, %52 ]
  %40 = phi i32 [ %31, %29 ], [ %53, %52 ]
  %41 = icmp ugt i32 %39, 79
  %42 = or i1 %32, %41
  %43 = icmp eq i32 %39, %26
  %44 = and i1 %33, %43
  %45 = or i1 %42, %44
  br i1 %45, label %52, label %46

46:                                               ; preds = %38
  %47 = add nuw nsw i32 %39, %34
  %48 = zext i32 %47 to i64
  %49 = getelementptr inbounds i32, i32* %16, i64 %48
  %50 = load i32, i32* %49, align 4, !tbaa !7
  %51 = add nsw i32 %50, %40
  br label %52

52:                                               ; preds = %46, %38
  %53 = phi i32 [ %51, %46 ], [ %40, %38 ]
  %54 = add nsw i32 %39, 1
  %55 = icmp sgt i32 %39, %26
  br i1 %55, label %35, label %38, !llvm.loop !14

56:                                               ; preds = %35
  %57 = getelementptr inbounds i32, i32* %16, i64 %18
  %58 = load i32, i32* %57, align 4, !tbaa !7
  %59 = icmp eq i32 %58, 0
  %60 = icmp eq i32 %53, 3
  %61 = and i32 %53, -2
  %62 = icmp eq i32 %61, 2
  %63 = select i1 %59, i1 %60, i1 %62
  %64 = zext i1 %63 to i32
  %65 = getelementptr inbounds i32, i32* %15, i64 %18
  store i32 %64, i32* %65, align 4
  %66 = add nuw nsw i64 %18, 1
  %67 = add nuw nsw i32 %19, 1
  %68 = icmp eq i64 %66, 4800
  br i1 %68, label %69, label %17, !llvm.loop !15

69:                                               ; preds = %56, %69
  %70 = phi i64 [ %76, %69 ], [ 0, %56 ]
  %71 = getelementptr inbounds i32, i32* %16, i64 %70
  %72 = load i32, i32* %71, align 4, !tbaa !7
  %73 = mul nsw i32 %72, 65280
  %74 = add i32 %73, -16777216
  %75 = trunc i64 %70 to i32
  tail call void @simSetPixel(i32 %75, i32 %74) #2
  %76 = add nuw nsw i64 %70, 1
  %77 = icmp eq i64 %76, 4800
  br i1 %77, label %78, label %69, !llvm.loop !16

78:                                               ; preds = %69
  tail call void @simFlush() #2
  %79 = tail call zeroext i1 @simEvent() #2
  br i1 %79, label %14, label %80, !llvm.loop !17

80:                                               ; preds = %78, %10
  tail call void @simExit() #2
  ret i32 0
}

; Function Attrs: optsize
declare void @simInit() local_unnamed_addr #1

; Function Attrs: optsize
declare zeroext i1 @simEvent() local_unnamed_addr #1

; Function Attrs: optsize
declare void @simExit() local_unnamed_addr #1

; Function Attrs: optsize
declare i32 @simRand() local_unnamed_addr #1

; Function Attrs: optsize
declare void @simSetPixel(i32, i32) local_unnamed_addr #1

; Function Attrs: optsize
declare void @simFlush() local_unnamed_addr #1

attributes #0 = { norecurse optsize ssp uwtable mustprogress "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { optsize "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { optsize }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5}
!llvm.ident = !{!6}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 1, !"branch-target-enforcement", i32 0}
!2 = !{i32 1, !"sign-return-address", i32 0}
!3 = !{i32 1, !"sign-return-address-all", i32 0}
!4 = !{i32 1, !"sign-return-address-with-bkey", i32 0}
!5 = !{i32 7, !"PIC Level", i32 2}
!6 = !{!"Homebrew clang version 12.0.1"}
!7 = !{!8, !8, i64 0}
!8 = !{!"int", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C++ TBAA"}
!11 = distinct !{!11, !12}
!12 = !{!"llvm.loop.mustprogress"}
!13 = distinct !{!13, !12}
!14 = distinct !{!14, !12}
!15 = distinct !{!15, !12}
!16 = distinct !{!16, !12}
!17 = distinct !{!17, !12}
