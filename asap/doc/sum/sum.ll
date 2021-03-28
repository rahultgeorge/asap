; ModuleID = 'sum.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = internal unnamed_addr constant { [35 x i8], [61 x i8] } { [35 x i8] c"How many numbers should I sum up? \00", [61 x i8] zeroinitializer }, align 32
@.str.1 = internal unnamed_addr constant { [3 x i8], [61 x i8] } { [3 x i8] c"%d\00", [61 x i8] zeroinitializer }, align 32
@.str.2 = internal unnamed_addr constant { [9 x i8], [55 x i8] } { [9 x i8] c"sum >= 0\00", [55 x i8] zeroinitializer }, align 32
@.str.3 = internal unnamed_addr constant { [6 x i8], [58 x i8] } { [6 x i8] c"sum.c\00", [58 x i8] zeroinitializer }, align 32
@__PRETTY_FUNCTION__.main = internal unnamed_addr constant { [11 x i8], [53 x i8] } { [11 x i8] c"int main()\00", [53 x i8] zeroinitializer }, align 32
@.str.4 = internal unnamed_addr constant { [16 x i8], [48 x i8] } { [16 x i8] c"The sum is: %d\0A\00", [48 x i8] zeroinitializer }, align 32
@llvm.global_ctors = appending global [1 x { i32, void ()* }] [{ i32, void ()* } { i32 1, void ()* @asan.module_ctor }]
@__asan_option_detect_stack_use_after_return = external global i32
@__asan_gen_ = private unnamed_addr constant [31 x i8] c"2 32 400 1 a 496 4 9 n_numbers\00", align 1
@__asan_gen_.5 = private constant [6 x i8] c"sum.c\00", align 1
@__asan_gen_.6 = private unnamed_addr constant [17 x i8] c"<string literal>\00", align 1
@__asan_gen_.7 = private unnamed_addr constant [6 x i8] c"sum.c\00", align 1
@__asan_gen_.8 = private unnamed_addr constant { [6 x i8]*, i32, i32 } { [6 x i8]* @__asan_gen_.7, i32 13, i32 12 }
@__asan_gen_.9 = private unnamed_addr constant [17 x i8] c"<string literal>\00", align 1
@__asan_gen_.10 = private unnamed_addr constant [6 x i8] c"sum.c\00", align 1
@__asan_gen_.11 = private unnamed_addr constant { [6 x i8]*, i32, i32 } { [6 x i8]* @__asan_gen_.10, i32 14, i32 11 }
@__asan_gen_.12 = private unnamed_addr constant [17 x i8] c"<string literal>\00", align 1
@__asan_gen_.13 = private unnamed_addr constant [6 x i8] c"sum.c\00", align 1
@__asan_gen_.14 = private unnamed_addr constant { [6 x i8]*, i32, i32 } { [6 x i8]* @__asan_gen_.13, i32 21, i32 5 }
@__asan_gen_.15 = private unnamed_addr constant [17 x i8] c"<string literal>\00", align 1
@__asan_gen_.16 = private unnamed_addr constant [6 x i8] c"sum.c\00", align 1
@__asan_gen_.17 = private unnamed_addr constant { [6 x i8]*, i32, i32 } { [6 x i8]* @__asan_gen_.16, i32 21, i32 5 }
@__asan_gen_.18 = private unnamed_addr constant [17 x i8] c"<string literal>\00", align 1
@__asan_gen_.19 = private unnamed_addr constant [6 x i8] c"sum.c\00", align 1
@__asan_gen_.20 = private unnamed_addr constant { [6 x i8]*, i32, i32 } { [6 x i8]* @__asan_gen_.19, i32 21, i32 5 }
@__asan_gen_.21 = private unnamed_addr constant [17 x i8] c"<string literal>\00", align 1
@__asan_gen_.22 = private unnamed_addr constant [6 x i8] c"sum.c\00", align 1
@__asan_gen_.23 = private unnamed_addr constant { [6 x i8]*, i32, i32 } { [6 x i8]* @__asan_gen_.22, i32 22, i32 12 }
@0 = internal global [6 x { i64, i64, i64, i64, i64, i64, i64 }] [{ i64, i64, i64, i64, i64, i64, i64 } { i64 ptrtoint ({ [35 x i8], [61 x i8] }* @.str to i64), i64 35, i64 96, i64 ptrtoint ([17 x i8]* @__asan_gen_.6 to i64), i64 ptrtoint ([6 x i8]* @__asan_gen_.5 to i64), i64 0, i64 ptrtoint ({ [6 x i8]*, i32, i32 }* @__asan_gen_.8 to i64) }, { i64, i64, i64, i64, i64, i64, i64 } { i64 ptrtoint ({ [3 x i8], [61 x i8] }* @.str.1 to i64), i64 3, i64 64, i64 ptrtoint ([17 x i8]* @__asan_gen_.9 to i64), i64 ptrtoint ([6 x i8]* @__asan_gen_.5 to i64), i64 0, i64 ptrtoint ({ [6 x i8]*, i32, i32 }* @__asan_gen_.11 to i64) }, { i64, i64, i64, i64, i64, i64, i64 } { i64 ptrtoint ({ [9 x i8], [55 x i8] }* @.str.2 to i64), i64 9, i64 64, i64 ptrtoint ([17 x i8]* @__asan_gen_.12 to i64), i64 ptrtoint ([6 x i8]* @__asan_gen_.5 to i64), i64 0, i64 ptrtoint ({ [6 x i8]*, i32, i32 }* @__asan_gen_.14 to i64) }, { i64, i64, i64, i64, i64, i64, i64 } { i64 ptrtoint ({ [6 x i8], [58 x i8] }* @.str.3 to i64), i64 6, i64 64, i64 ptrtoint ([17 x i8]* @__asan_gen_.15 to i64), i64 ptrtoint ([6 x i8]* @__asan_gen_.5 to i64), i64 0, i64 ptrtoint ({ [6 x i8]*, i32, i32 }* @__asan_gen_.17 to i64) }, { i64, i64, i64, i64, i64, i64, i64 } { i64 ptrtoint ({ [11 x i8], [53 x i8] }* @__PRETTY_FUNCTION__.main to i64), i64 11, i64 64, i64 ptrtoint ([17 x i8]* @__asan_gen_.18 to i64), i64 ptrtoint ([6 x i8]* @__asan_gen_.5 to i64), i64 0, i64 ptrtoint ({ [6 x i8]*, i32, i32 }* @__asan_gen_.20 to i64) }, { i64, i64, i64, i64, i64, i64, i64 } { i64 ptrtoint ({ [16 x i8], [48 x i8] }* @.str.4 to i64), i64 16, i64 64, i64 ptrtoint ([17 x i8]* @__asan_gen_.21 to i64), i64 ptrtoint ([6 x i8]* @__asan_gen_.5 to i64), i64 0, i64 ptrtoint ({ [6 x i8]*, i32, i32 }* @__asan_gen_.23 to i64) }]
@llvm.global_dtors = appending global [1 x { i32, void ()* }] [{ i32, void ()* } { i32 1, void ()* @asan.module_dtor }]

; Function Attrs: nounwind sanitize_address uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %MAX_SIZE = alloca i32, align 4
  %0 = load i32, i32* @__asan_option_detect_stack_use_after_return
  %1 = icmp ne i32 %0, 0
  br i1 %1, label %2, label %4

; <label>:2                                       ; preds = %entry
  %3 = call i64 @__asan_stack_malloc_3(i64 512)
  br label %4

; <label>:4                                       ; preds = %entry, %2
  %5 = phi i64 [ 0, %entry ], [ %3, %2 ]
  %6 = icmp eq i64 %5, 0
  br i1 %6, label %7, label %9

; <label>:7                                       ; preds = %4
  %MyAlloca = alloca i8, i64 512, align 32
  %8 = ptrtoint i8* %MyAlloca to i64
  br label %9

; <label>:9                                       ; preds = %4, %7
  %10 = phi i64 [ %5, %4 ], [ %8, %7 ]
  %11 = add i64 %10, 32
  %12 = inttoptr i64 %11 to [100 x i32]*
  %13 = add i64 %10, 496
  %14 = inttoptr i64 %13 to i32*
  %15 = inttoptr i64 %10 to i64*
  store i64 1102416563, i64* %15
  %16 = add i64 %10, 8
  %17 = inttoptr i64 %16 to i64*
  store i64 ptrtoint ([31 x i8]* @__asan_gen_ to i64), i64* %17
  %18 = add i64 %10, 16
  %19 = inttoptr i64 %18 to i64*
  store i64 ptrtoint (i32 ()* @main to i64), i64* %19
  %20 = lshr i64 %10, 3
  %21 = add i64 %20, 2147450880
  %22 = add i64 %21, 0
  %23 = inttoptr i64 %22 to i64*
  store i64 4059165169, i64* %23
  %24 = add i64 %21, 48
  %25 = inttoptr i64 %24 to i64*
  store i64 -940689372167012352, i64* %25
  %26 = add i64 %21, 56
  %27 = inttoptr i64 %26 to i64*
  store i64 -935355697314204942, i64* %27
  %i = alloca i32, align 4
  %sum = alloca i32, align 4
  %i2 = alloca i32, align 4
  store i32 0, i32* %retval
  store i32 100, i32* %MAX_SIZE, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %9
  %28 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %28, 100
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %29 = load i32, i32* %i, align 4
  %30 = load i32, i32* %i, align 4
  %mul = mul nsw i32 %29, %30
  %add = add nsw i32 %mul, 4
  %31 = load i32, i32* %i, align 4
  %idxprom = sext i32 %31 to i64
  %arrayidx = getelementptr inbounds [100 x i32], [100 x i32]* %12, i32 0, i64 %idxprom
  %32 = ptrtoint i32* %arrayidx to i64
  %33 = lshr i64 %32, 3
  %34 = add i64 %33, 2147450880
  %35 = inttoptr i64 %34 to i8*
  %36 = load i8, i8* %35
  %37 = icmp ne i8 %36, 0
  br i1 %37, label %38, label %44, !prof !11

; <label>:38                                      ; preds = %for.body
  %39 = and i64 %32, 7
  %40 = add i64 %39, 3
  %41 = trunc i64 %40 to i8
  %42 = icmp sge i8 %41, %36
  br i1 %42, label %43, label %44

; <label>:43                                      ; preds = %38
  call void @__asan_report_store4(i64 %32)
  call void asm sideeffect "", ""()
  unreachable

; <label>:44                                      ; preds = %38, %for.body
  store i32 %add, i32* %arrayidx, align 4
  br label %for.inc

for.inc:                                          ; preds = %44
  %45 = load i32, i32* %i, align 4
  %inc = add nsw i32 %45, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ({ [35 x i8], [61 x i8] }, { [35 x i8], [61 x i8] }* @.str, i32 0, i32 0, i32 0))
  %call1 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ({ [3 x i8], [61 x i8] }, { [3 x i8], [61 x i8] }* @.str.1, i32 0, i32 0, i32 0), i32* %14)
  store i32 0, i32* %sum, align 4
  store i32 0, i32* %i2, align 4
  br label %for.cond.3

for.cond.3:                                       ; preds = %for.inc.9, %for.end
  %46 = load i32, i32* %i2, align 4
  %47 = ptrtoint i32* %14 to i64
  %48 = lshr i64 %47, 3
  %49 = add i64 %48, 2147450880
  %50 = inttoptr i64 %49 to i8*
  %51 = load i8, i8* %50
  %52 = icmp ne i8 %51, 0
  br i1 %52, label %53, label %59, !prof !11

; <label>:53                                      ; preds = %for.cond.3
  %54 = and i64 %47, 7
  %55 = add i64 %54, 3
  %56 = trunc i64 %55 to i8
  %57 = icmp sge i8 %56, %51
  br i1 %57, label %58, label %59

; <label>:58                                      ; preds = %53
  call void @__asan_report_load4(i64 %47)
  call void asm sideeffect "", ""()
  unreachable

; <label>:59                                      ; preds = %53, %for.cond.3
  %60 = load i32, i32* %14, align 4
  %cmp4 = icmp slt i32 %46, %60
  br i1 %cmp4, label %for.body.5, label %for.end.11

for.body.5:                                       ; preds = %59
  %61 = load i32, i32* %i2, align 4
  %idxprom6 = sext i32 %61 to i64
  %arrayidx7 = getelementptr inbounds [100 x i32], [100 x i32]* %12, i32 0, i64 %idxprom6
  %62 = ptrtoint i32* %arrayidx7 to i64
  %63 = lshr i64 %62, 3
  %64 = add i64 %63, 2147450880
  %65 = inttoptr i64 %64 to i8*
  %66 = load i8, i8* %65
  %67 = icmp ne i8 %66, 0
  br i1 %67, label %68, label %74, !prof !11

; <label>:68                                      ; preds = %for.body.5
  %69 = and i64 %62, 7
  %70 = add i64 %69, 3
  %71 = trunc i64 %70 to i8
  %72 = icmp sge i8 %71, %66
  br i1 %72, label %73, label %74

; <label>:73                                      ; preds = %68
  call void @__asan_report_load4(i64 %62)
  call void asm sideeffect "", ""()
  unreachable

; <label>:74                                      ; preds = %68, %for.body.5
  %75 = load i32, i32* %arrayidx7, align 4
  %76 = load i32, i32* %sum, align 4
  %add8 = add nsw i32 %76, %75
  store i32 %add8, i32* %sum, align 4
  br label %for.inc.9

for.inc.9:                                        ; preds = %74
  %77 = load i32, i32* %i2, align 4
  %inc10 = add nsw i32 %77, 1
  store i32 %inc10, i32* %i2, align 4
  br label %for.cond.3

for.end.11:                                       ; preds = %59
  %78 = load i32, i32* %sum, align 4
  %cmp12 = icmp sge i32 %78, 0
  br i1 %cmp12, label %cond.true, label %cond.false

cond.true:                                        ; preds = %for.end.11
  br label %cond.end

cond.false:                                       ; preds = %for.end.11
  call void @__asan_handle_no_return()
  call void @__assert_fail(i8* getelementptr inbounds ({ [9 x i8], [55 x i8] }, { [9 x i8], [55 x i8] }* @.str.2, i32 0, i32 0, i32 0), i8* getelementptr inbounds ({ [6 x i8], [58 x i8] }, { [6 x i8], [58 x i8] }* @.str.3, i32 0, i32 0, i32 0), i32 21, i8* getelementptr inbounds ({ [11 x i8], [53 x i8] }, { [11 x i8], [53 x i8] }* @__PRETTY_FUNCTION__.main, i32 0, i32 0, i32 0)) #3
  unreachable
                                                  ; No predecessors!
  br label %cond.end

cond.end:                                         ; preds = %79, %cond.true
  %80 = load i32, i32* %sum, align 4
  %call13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ({ [16 x i8], [48 x i8] }, { [16 x i8], [48 x i8] }* @.str.4, i32 0, i32 0, i32 0), i32 %80)
  store i64 1172321806, i64* %15
  %81 = icmp ne i64 %5, 0
  br i1 %81, label %82, label %103

; <label>:82                                      ; preds = %cond.end
  %83 = add i64 %21, 0
  %84 = inttoptr i64 %83 to i64*
  store i64 -723401728380766731, i64* %84
  %85 = add i64 %21, 8
  %86 = inttoptr i64 %85 to i64*
  store i64 -723401728380766731, i64* %86
  %87 = add i64 %21, 16
  %88 = inttoptr i64 %87 to i64*
  store i64 -723401728380766731, i64* %88
  %89 = add i64 %21, 24
  %90 = inttoptr i64 %89 to i64*
  store i64 -723401728380766731, i64* %90
  %91 = add i64 %21, 32
  %92 = inttoptr i64 %91 to i64*
  store i64 -723401728380766731, i64* %92
  %93 = add i64 %21, 40
  %94 = inttoptr i64 %93 to i64*
  store i64 -723401728380766731, i64* %94
  %95 = add i64 %21, 48
  %96 = inttoptr i64 %95 to i64*
  store i64 -723401728380766731, i64* %96
  %97 = add i64 %21, 56
  %98 = inttoptr i64 %97 to i64*
  store i64 -723401728380766731, i64* %98
  %99 = add i64 %5, 504
  %100 = inttoptr i64 %99 to i64*
  %101 = load i64, i64* %100
  %102 = inttoptr i64 %101 to i8*
  store i8 0, i8* %102
  br label %110

; <label>:103                                     ; preds = %cond.end
  %104 = add i64 %21, 0
  %105 = inttoptr i64 %104 to i64*
  store i64 0, i64* %105
  %106 = add i64 %21, 48
  %107 = inttoptr i64 %106 to i64*
  store i64 0, i64* %107
  %108 = add i64 %21, 56
  %109 = inttoptr i64 %108 to i64*
  store i64 0, i64* %109
  br label %110

; <label>:110                                     ; preds = %103, %82
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

declare i32 @__isoc99_scanf(i8*, ...) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

define internal void @asan.module_ctor() {
  call void @__asan_init_v5()
  call void @__asan_register_globals(i64 ptrtoint ([6 x { i64, i64, i64, i64, i64, i64, i64 }]* @0 to i64), i64 6)
  ret void
}

declare void @__asan_init_v5()

declare void @__asan_report_load_n(i64, i64)

declare void @__asan_loadN(i64, i64)

declare void @__asan_report_load1(i64)

declare void @__asan_load1(i64)

declare void @__asan_report_load2(i64)

declare void @__asan_load2(i64)

declare void @__asan_report_load4(i64)

declare void @__asan_load4(i64)

declare void @__asan_report_load8(i64)

declare void @__asan_load8(i64)

declare void @__asan_report_load16(i64)

declare void @__asan_load16(i64)

declare void @__asan_report_store_n(i64, i64)

declare void @__asan_storeN(i64, i64)

declare void @__asan_report_store1(i64)

declare void @__asan_store1(i64)

declare void @__asan_report_store2(i64)

declare void @__asan_store2(i64)

declare void @__asan_report_store4(i64)

declare void @__asan_store4(i64)

declare void @__asan_report_store8(i64)

declare void @__asan_store8(i64)

declare void @__asan_report_store16(i64)

declare void @__asan_store16(i64)

declare void @__asan_report_exp_load_n(i64, i64, i32)

declare void @__asan_exp_loadN(i64, i64, i32)

declare void @__asan_report_exp_load1(i64, i32)

declare void @__asan_exp_load1(i64, i32)

declare void @__asan_report_exp_load2(i64, i32)

declare void @__asan_exp_load2(i64, i32)

declare void @__asan_report_exp_load4(i64, i32)

declare void @__asan_exp_load4(i64, i32)

declare void @__asan_report_exp_load8(i64, i32)

declare void @__asan_exp_load8(i64, i32)

declare void @__asan_report_exp_load16(i64, i32)

declare void @__asan_exp_load16(i64, i32)

declare void @__asan_report_exp_store_n(i64, i64, i32)

declare void @__asan_exp_storeN(i64, i64, i32)

declare void @__asan_report_exp_store1(i64, i32)

declare void @__asan_exp_store1(i64, i32)

declare void @__asan_report_exp_store2(i64, i32)

declare void @__asan_exp_store2(i64, i32)

declare void @__asan_report_exp_store4(i64, i32)

declare void @__asan_exp_store4(i64, i32)

declare void @__asan_report_exp_store8(i64, i32)

declare void @__asan_exp_store8(i64, i32)

declare void @__asan_report_exp_store16(i64, i32)

declare void @__asan_exp_store16(i64, i32)

declare i8* @__asan_memmove(i8*, i8*, i64)

declare i8* @__asan_memcpy(i8*, i8*, i64)

declare i8* @__asan_memset(i8*, i32, i64)

declare void @__asan_handle_no_return()

declare void @__sanitizer_ptr_cmp(i64, i64)

declare void @__sanitizer_ptr_sub(i64, i64)

declare i64 @__asan_stack_malloc_0(i64)

declare void @__asan_stack_free_0(i64, i64)

declare i64 @__asan_stack_malloc_1(i64)

declare void @__asan_stack_free_1(i64, i64)

declare i64 @__asan_stack_malloc_2(i64)

declare void @__asan_stack_free_2(i64, i64)

declare i64 @__asan_stack_malloc_3(i64)

declare void @__asan_stack_free_3(i64, i64)

declare i64 @__asan_stack_malloc_4(i64)

declare void @__asan_stack_free_4(i64, i64)

declare i64 @__asan_stack_malloc_5(i64)

declare void @__asan_stack_free_5(i64, i64)

declare i64 @__asan_stack_malloc_6(i64)

declare void @__asan_stack_free_6(i64, i64)

declare i64 @__asan_stack_malloc_7(i64)

declare void @__asan_stack_free_7(i64, i64)

declare i64 @__asan_stack_malloc_8(i64)

declare void @__asan_stack_free_8(i64, i64)

declare i64 @__asan_stack_malloc_9(i64)

declare void @__asan_stack_free_9(i64, i64)

declare i64 @__asan_stack_malloc_10(i64)

declare void @__asan_stack_free_10(i64, i64)

declare void @__asan_poison_stack_memory(i64, i64)

declare void @__asan_unpoison_stack_memory(i64, i64)

declare void @__asan_alloca_poison(i64, i64)

declare void @__asan_allocas_unpoison(i64, i64)

declare void @__asan_before_dynamic_init(i64)

declare void @__asan_after_dynamic_init()

declare void @__asan_register_globals(i64, i64)

declare void @__asan_unregister_globals(i64, i64)

define internal void @asan.module_dtor() {
  call void @__asan_unregister_globals(i64 ptrtoint ([6 x { i64, i64, i64, i64, i64, i64, i64 }]* @0 to i64), i64 6)
  ret void
}

attributes #0 = { nounwind sanitize_address uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind }

!llvm.asan.globals = !{!0, !2, !4, !6, !7, !8}
!llvm.ident = !{!10}

!0 = !{[35 x i8]* getelementptr inbounds ({ [35 x i8], [61 x i8] }, { [35 x i8], [61 x i8] }* @.str, i32 0, i32 0), !1, !"<string literal>", i1 false, i1 false}
!1 = !{!"sum.c", i32 13, i32 12}
!2 = !{[3 x i8]* getelementptr inbounds ({ [3 x i8], [61 x i8] }, { [3 x i8], [61 x i8] }* @.str.1, i32 0, i32 0), !3, !"<string literal>", i1 false, i1 false}
!3 = !{!"sum.c", i32 14, i32 11}
!4 = !{[9 x i8]* getelementptr inbounds ({ [9 x i8], [55 x i8] }, { [9 x i8], [55 x i8] }* @.str.2, i32 0, i32 0), !5, !"<string literal>", i1 false, i1 false}
!5 = !{!"sum.c", i32 21, i32 5}
!6 = !{[6 x i8]* getelementptr inbounds ({ [6 x i8], [58 x i8] }, { [6 x i8], [58 x i8] }* @.str.3, i32 0, i32 0), !5, !"<string literal>", i1 false, i1 false}
!7 = !{[11 x i8]* getelementptr inbounds ({ [11 x i8], [53 x i8] }, { [11 x i8], [53 x i8] }* @__PRETTY_FUNCTION__.main, i32 0, i32 0), !5, !"<string literal>", i1 false, i1 false}
!8 = !{[16 x i8]* getelementptr inbounds ({ [16 x i8], [48 x i8] }, { [16 x i8], [48 x i8] }* @.str.4, i32 0, i32 0), !9, !"<string literal>", i1 false, i1 false}
!9 = !{!"sum.c", i32 22, i32 12}
!10 = !{!"clang version 3.7.0 (https://github.com/llvm-mirror/clang 0dbefa1b83eb90f7a06b5df5df254ce32be3db4b) (https://github.com/rahultgeorge/asap.git 25b7d2a6bc77f5794d21d72c33a51886c12b2c35)"}
!11 = !{!"branch_weights", i32 1, i32 100000}
