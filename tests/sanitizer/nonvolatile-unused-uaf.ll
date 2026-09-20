target triple = "arm64-apple-macosx26.0.0"
declare ptr @malloc(i64)
declare void @free(ptr)
define internal i8 @read_freed(ptr %p) sanitize_address {
 %v = load i8, ptr %p
 ret i8 %v
}
define i32 @main() sanitize_address {
 %p = call ptr @malloc(i64 8)
 call void @free(ptr %p)
 %unused = call i8 @read_freed(ptr %p)
 ret i32 0
}
