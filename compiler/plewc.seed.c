#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef struct { const char* data; long long len; } PlewString;
__attribute__((unused)) static void* plew_arc_alloc(long long bytes) { long long* p = (long long*)malloc(sizeof(long long) + (size_t)bytes); p[0] = 1; return (void*)(p + 1); }
__attribute__((unused)) static void plew_arc_retain(long long* rc) { if (rc) (*rc) += 1; }
__attribute__((unused)) static void plew_arc_release(long long* rc) { if (rc && (--(*rc)) == 0) free((void*)rc); }
__attribute__((unused)) static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (long long i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }
__attribute__((unused)) static PlewString plew_read_stdin(void) { size_t cap = 4096, len = 0; char* buf = (char*)malloc(cap); int ch; while ((ch = getchar()) != EOF) { if (len + 1 >= cap) { cap *= 2; buf = (char*)realloc(buf, cap); } buf[len++] = (char)ch; } PlewString s; s.data = buf; s.len = (long long)len; return s; }
__attribute__((unused)) static void plew_write(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stdout); }
__attribute__((unused)) static void plew_eprint(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stderr); }
__attribute__((noreturn)) static void plew_panic(PlewString m) { fputs("panic: ", stderr); fwrite(m.data, 1, (size_t)m.len, stderr); fputc('\n', stderr); exit(1); }
__attribute__((unused)) static long long plew_div(long long a, long long b) { if (b == 0) plew_panic((PlewString){"division by zero", 16}); if (b == -1 && a == INT64_MIN) plew_panic((PlewString){"integer overflow", 16}); return a / b; }
__attribute__((unused)) static long long plew_mod(long long a, long long b) { if (b == 0) plew_panic((PlewString){"remainder by zero", 17}); if (b == -1) return 0; return a % b; }
static int plew_argc = 0;
static char** plew_argv = 0;
__attribute__((unused)) static long long plew_arg_count(void) { return (long long)plew_argc; }
__attribute__((unused)) static PlewString plew_arg_at(long long i) { PlewString s; if (i < 0 || i >= plew_argc) { s.data = ""; s.len = 0; return s; } s.data = plew_argv[i]; s.len = (long long)strlen(plew_argv[i]); return s; }
__attribute__((unused)) static PlewString plew_read_file(PlewString path) { FILE* f = fopen(path.data, "rb"); PlewString s; if (!f) { s.data = ""; s.len = 0; return s; } fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET); char* buf = (char*)malloc((size_t)sz + 1); size_t n = fread(buf, 1, (size_t)sz, f); fclose(f); buf[n] = 0; s.data = buf; s.len = (long long)n; return s; }
typedef struct Tok Tok;
typedef struct Lexer Lexer;
typedef struct PType PType;
typedef struct TypeRef TypeRef;
typedef struct Local Local;
typedef struct TypeInfo TypeInfo;
typedef struct MakeField MakeField;
typedef struct Bind Bind;
typedef struct Arg Arg;
typedef struct MatchArm MatchArm;
typedef struct PatInfo PatInfo;
typedef struct Block Block;
typedef struct Param Param;
typedef struct FieldDef FieldDef;
typedef struct StructDef StructDef;
typedef struct Variant Variant;
typedef struct EnumDef EnumDef;
typedef struct Func Func;
typedef struct Comp Comp;
typedef struct ConstInt ConstInt;
typedef struct IntTy IntTy;
typedef struct Kind Kind;
typedef struct Expr Expr;
typedef struct Stmt Stmt;
typedef struct { unsigned char* data; long long len; long long cap; long long* rc; } PlewArray_U8;
__attribute__((unused)) static PlewString plew_read_file_bytes(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; PlewString r = plew_read_file((PlewString){path, p.len}); free(path); return r; }
__attribute__((unused)) static long long plew_file_exists(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; FILE* f = fopen(path, "rb"); free(path); if (f) { fclose(f); return 1; } return 0; }
typedef struct { Bind* data; long long len; long long cap; long long* rc; } PlewArray_Bind;
typedef struct { Tok* data; long long len; long long cap; long long* rc; } PlewArray_Tok;
typedef struct { uint64_t* data; long long len; long long cap; long long* rc; } PlewArray_U64;
typedef struct { Arg* data; long long len; long long cap; long long* rc; } PlewArray_Arg;
typedef struct { MakeField* data; long long len; long long cap; long long* rc; } PlewArray_MakeField;
typedef struct { MatchArm* data; long long len; long long cap; long long* rc; } PlewArray_MatchArm;
typedef struct { Param* data; long long len; long long cap; long long* rc; } PlewArray_Param;
typedef struct { FieldDef* data; long long len; long long cap; long long* rc; } PlewArray_FieldDef;
typedef struct { Variant* data; long long len; long long cap; long long* rc; } PlewArray_Variant;
typedef struct { Expr* data; long long len; long long cap; long long* rc; } PlewArray_Expr;
typedef struct { Stmt* data; long long len; long long cap; long long* rc; } PlewArray_Stmt;
typedef struct { Block* data; long long len; long long cap; long long* rc; } PlewArray_Block;
typedef struct { Func* data; long long len; long long cap; long long* rc; } PlewArray_Func;
typedef struct { StructDef* data; long long len; long long cap; long long* rc; } PlewArray_StructDef;
typedef struct { EnumDef* data; long long len; long long cap; long long* rc; } PlewArray_EnumDef;
typedef struct { TypeRef* data; long long len; long long cap; long long* rc; } PlewArray_TypeRef;
typedef struct { Local* data; long long len; long long cap; long long* rc; } PlewArray_Local;
typedef struct { PatInfo* data; long long len; long long cap; long long* rc; } PlewArray_PatInfo;
struct Kind {
    long long tag;
    union {
        struct { char _u; } Eof;
        struct { char _u; } Newline;
        struct { char _u; } Int;
        struct { char _u; } Str;
        struct { char _u; } Char;
        struct { char _u; } Ident;
        struct { char _u; } KwFn;
        struct { char _u; } KwStruct;
        struct { char _u; } KwEnum;
        struct { char _u; } KwMatch;
        struct { char _u; } KwIf;
        struct { char _u; } KwElse;
        struct { char _u; } KwWhile;
        struct { char _u; } KwFor;
        struct { char _u; } KwBreak;
        struct { char _u; } KwContinue;
        struct { char _u; } KwReturn;
        struct { char _u; } KwGive;
        struct { char _u; } KwVal;
        struct { char _u; } KwMut;
        struct { char _u; } KwIn;
        struct { char _u; } KwAs;
        struct { char _u; } KwInout;
        struct { char _u; } KwTrue;
        struct { char _u; } KwFalse;
        struct { char _u; } LParen;
        struct { char _u; } RParen;
        struct { char _u; } LBracket;
        struct { char _u; } RBracket;
        struct { char _u; } LBrace;
        struct { char _u; } RBrace;
        struct { char _u; } Comma;
        struct { char _u; } Colon;
        struct { char _u; } Dot;
        struct { char _u; } Eq;
        struct { char _u; } EqEq;
        struct { char _u; } Ne;
        struct { char _u; } Lt;
        struct { char _u; } Le;
        struct { char _u; } Gt;
        struct { char _u; } Ge;
        struct { char _u; } Plus;
        struct { char _u; } Minus;
        struct { char _u; } Star;
        struct { char _u; } Slash;
        struct { char _u; } Percent;
        struct { char _u; } AmpAmp;
        struct { char _u; } PipePipe;
        struct { char _u; } Bang;
        struct { char _u; } Amp;
        struct { char _u; } Pipe;
        struct { char _u; } Caret;
        struct { char _u; } Shl;
        struct { char _u; } Shr;
        struct { char _u; } Tilde;
        struct { char _u; } Arrow;
        struct { char _u; } FatArrow;
        struct { char _u; } SlashGt;
        struct { char _u; } PlusEq;
        struct { char _u; } MinusEq;
        struct { char _u; } StarEq;
        struct { char _u; } SlashEq;
        struct { char _u; } PercentEq;
        struct { char _u; } AmpEq;
        struct { char _u; } PipeEq;
        struct { char _u; } CaretEq;
        struct { char _u; } ShlEq;
        struct { char _u; } ShrEq;
        struct { char _u; } DotDotLt;
        struct { char _u; } DotDotEq;
        struct { char _u; } Coalesce;
        struct { char _u; } Unknown;
    } data;
};
struct Expr {
    long long tag;
    union {
        struct { int64_t value; uint64_t offset; long long isBool; uint64_t tyStart; uint64_t tyLen; } Int;
        struct { uint64_t start; uint64_t len; } Ident;
        struct { int64_t op; uint64_t operand; } Unary;
        struct { int64_t op; uint64_t lhs; uint64_t rhs; } Binary;
        struct { uint64_t nameStart; uint64_t nameLen; PlewArray_Arg args; } Call;
        struct { uint64_t base; uint64_t nameStart; uint64_t nameLen; } Field;
        struct { uint64_t typeStart; uint64_t typeLen; uint64_t variantStart; uint64_t variantLen; long long isEnum; uint64_t ty; PlewArray_MakeField fields; } Make;
        struct { uint64_t start; uint64_t len; } Str;
        struct { PlewArray_U64 elems; } Array;
        struct { uint64_t base; uint64_t index; } Index;
        struct { uint64_t recv; uint64_t nameStart; uint64_t nameLen; PlewArray_Arg args; } Method;
        struct { uint64_t operand; uint64_t tyStart; uint64_t tyLen; uint64_t ty; } Cast;
        struct { uint64_t scrut; PlewArray_MatchArm arms; } MatchExpr;
        struct { uint64_t cond; uint64_t thenBlk; uint64_t elseBlk; } IfExpr;
        struct { uint64_t opt; uint64_t deflt; } Coalesce;
        struct { uint64_t expr; } Try;
        struct { uint64_t base; uint64_t nameStart; uint64_t nameLen; } Arrow;
        struct { PlewArray_Param params; long long hasRet; uint64_t retStart; uint64_t retLen; long long retIsArray; uint64_t retTy; uint64_t body; } Closure;
    } data;
};
struct Stmt {
    long long tag;
    union {
        struct { long long mutable; uint64_t nameStart; uint64_t nameLen; uint64_t tyStart; uint64_t tyLen; long long tyIsArray; uint64_t ty; uint64_t init; } Let;
        struct { int64_t op; uint64_t target; uint64_t value; } Assign;
        struct { uint64_t expr; uint64_t offset; } Print;
        struct { uint64_t expr; } ExprStmt;
        struct { uint64_t value; long long hasValue; } Return;
        struct { uint64_t cond; uint64_t thenBlk; uint64_t elseBlk; long long hasElse; } If;
        struct { uint64_t cond; uint64_t body; } While;
        struct { uint64_t varStart; uint64_t varLen; long long isRange; long long inclusive; uint64_t iter; uint64_t rangeHi; uint64_t body; } For;
        struct { uint64_t scrut; PlewArray_MatchArm arms; } Match;
        struct { uint64_t msg; uint64_t offset; } Panic;
        struct { uint64_t value; } Give;
        struct { char _u; } Break;
        struct { char _u; } Continue;
    } data;
};
struct Tok {
    Kind kind;
    uint64_t start;
    uint64_t len;
};
struct Lexer {
    PlewArray_U8 bytes;
    uint64_t pos;
    PlewArray_Tok toks;
    int64_t depth;
};
struct PType {
    uint64_t start;
    uint64_t len;
    long long isArray;
    uint64_t ref;
};
struct TypeRef {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_U64 args;
};
struct Local {
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t tyStart;
    uint64_t tyLen;
    long long isArray;
    uint64_t ty;
    long long isInout;
    long long isMut;
    long long owned;
};
struct TypeInfo {
    int64_t kind;
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t ref;
};
struct MakeField {
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t value;
};
struct Bind {
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t fieldStart;
    uint64_t fieldLen;
};
struct Arg {
    uint64_t expr;
    long long isInout;
    uint64_t labelStart;
    uint64_t labelLen;
    long long hasLabel;
};
struct MatchArm {
    long long isWildcard;
    uint64_t enumStart;
    uint64_t enumLen;
    uint64_t variantStart;
    uint64_t variantLen;
    PlewArray_Bind binds;
    uint64_t body;
};
struct PatInfo {
    long long isWildcard;
    uint64_t enumStart;
    uint64_t enumLen;
    uint64_t variantStart;
    uint64_t variantLen;
    PlewArray_Bind binds;
};
struct Block {
    PlewArray_U64 stmts;
};
struct Param {
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t tyStart;
    uint64_t tyLen;
    long long tyIsArray;
    uint64_t ty;
    long long isInout;
    long long noLabel;
    long long hasDefault;
    uint64_t defaultExpr;
};
struct FieldDef {
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t tyStart;
    uint64_t tyLen;
    long long tyIsArray;
    uint64_t ty;
    long long isMut;
};
struct StructDef {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_Bind typeParams;
    PlewArray_FieldDef fields;
};
struct Variant {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_FieldDef fields;
};
struct EnumDef {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_Bind typeParams;
    PlewArray_Variant variants;
};
struct Func {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_Bind typeParams;
    PlewArray_Param params;
    long long hasRet;
    uint64_t retStart;
    uint64_t retLen;
    long long retIsArray;
    uint64_t retTy;
    uint64_t body;
    long long hasRecv;
    uint64_t recvStart;
    uint64_t recvLen;
    long long selfInout;
};
struct Comp {
    PlewArray_U8 bytes;
    PlewArray_Tok toks;
    uint64_t pos;
    PlewArray_Expr exprs;
    PlewArray_Stmt stmts;
    PlewArray_Block blocks;
    PlewArray_Func funcs;
    PlewArray_StructDef structs;
    PlewArray_EnumDef enums;
    PlewArray_TypeRef types;
    PlewArray_U64 genInsts;
    PlewArray_U64 fnTypes;
    PlewArray_Bind arrayElems;
    PlewArray_Local locals;
    uint64_t tmp;
    long long curIsMain;
    long long curRetVoid;
    uint64_t curRetStart;
    uint64_t curRetLen;
    long long curRetIsArray;
    uint64_t curRetTy;
    long long curHasRecv;
    uint64_t curRecvStart;
    uint64_t curRecvLen;
    long long curSelfInout;
    PlewArray_Bind curTypeParams;
    PlewArray_U64 curTypeArgs;
    uint64_t curRecvInstRef;
    uint64_t curGiveTmp;
    long long impPrint;
    long long impWrite;
    long long impWriteByte;
    long long impReadStdin;
    long long impReadFile;
    long long impArgCount;
    long long impArgAt;
    long long impEprint;
    long long impExit;
    long long impReadFileBytes;
    long long impFileExists;
};
struct ConstInt {
    long long isConst;
    int64_t value;
};
struct IntTy {
    long long known;
    uint64_t bits;
    long long sgn;
};
Lexer Lexer_copy(Lexer s);
Lexer Lexer_share(Lexer s);
void Lexer_release(Lexer s);
TypeRef TypeRef_copy(TypeRef s);
TypeRef TypeRef_share(TypeRef s);
void TypeRef_release(TypeRef s);
MatchArm MatchArm_copy(MatchArm s);
MatchArm MatchArm_share(MatchArm s);
void MatchArm_release(MatchArm s);
PatInfo PatInfo_copy(PatInfo s);
PatInfo PatInfo_share(PatInfo s);
void PatInfo_release(PatInfo s);
Block Block_copy(Block s);
Block Block_share(Block s);
void Block_release(Block s);
StructDef StructDef_copy(StructDef s);
StructDef StructDef_share(StructDef s);
void StructDef_release(StructDef s);
Variant Variant_copy(Variant s);
Variant Variant_share(Variant s);
void Variant_release(Variant s);
EnumDef EnumDef_copy(EnumDef s);
EnumDef EnumDef_share(EnumDef s);
void EnumDef_release(EnumDef s);
Func Func_copy(Func s);
Func Func_share(Func s);
void Func_release(Func s);
Comp Comp_copy(Comp s);
Comp Comp_share(Comp s);
void Comp_release(Comp s);
__attribute__((unused)) static PlewArray_U8 PlewArray_U8_new(void) { PlewArray_U8 a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static unsigned char PlewArray_U8_get(PlewArray_U8 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_U8 PlewArray_U8_copy(PlewArray_U8 a) { PlewArray_U8 r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (unsigned char*)plew_arc_alloc(sizeof(unsigned char) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_U8_release(PlewArray_U8 a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_U8 PlewArray_U8_share(PlewArray_U8 a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_U8_unique(PlewArray_U8* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_U8 nc = PlewArray_U8_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_U8_set(PlewArray_U8* a, long long i, unsigned char v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_U8_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_U8_push(PlewArray_U8* a, unsigned char v) { PlewArray_U8_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; unsigned char* nd = (unsigned char*)plew_arc_alloc(sizeof(unsigned char) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Bind PlewArray_Bind_new(void) { PlewArray_Bind a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Bind PlewArray_Bind_get(PlewArray_Bind a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Bind PlewArray_Bind_copy(PlewArray_Bind a) { PlewArray_Bind r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Bind*)plew_arc_alloc(sizeof(Bind) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Bind_release(PlewArray_Bind a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_Bind PlewArray_Bind_share(PlewArray_Bind a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Bind_unique(PlewArray_Bind* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Bind nc = PlewArray_Bind_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Bind_set(PlewArray_Bind* a, long long i, Bind v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Bind_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Bind_push(PlewArray_Bind* a, Bind v) { PlewArray_Bind_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Bind* nd = (Bind*)plew_arc_alloc(sizeof(Bind) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Tok PlewArray_Tok_new(void) { PlewArray_Tok a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Tok PlewArray_Tok_get(PlewArray_Tok a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Tok PlewArray_Tok_copy(PlewArray_Tok a) { PlewArray_Tok r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Tok*)plew_arc_alloc(sizeof(Tok) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Tok_release(PlewArray_Tok a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_Tok PlewArray_Tok_share(PlewArray_Tok a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Tok_unique(PlewArray_Tok* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Tok nc = PlewArray_Tok_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Tok_set(PlewArray_Tok* a, long long i, Tok v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Tok_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Tok_push(PlewArray_Tok* a, Tok v) { PlewArray_Tok_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Tok* nd = (Tok*)plew_arc_alloc(sizeof(Tok) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_U64 PlewArray_U64_new(void) { PlewArray_U64 a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static uint64_t PlewArray_U64_get(PlewArray_U64 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_U64 PlewArray_U64_copy(PlewArray_U64 a) { PlewArray_U64 r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (uint64_t*)plew_arc_alloc(sizeof(uint64_t) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_U64_release(PlewArray_U64 a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_U64 PlewArray_U64_share(PlewArray_U64 a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_U64_unique(PlewArray_U64* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_U64 nc = PlewArray_U64_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_U64_set(PlewArray_U64* a, long long i, uint64_t v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_U64_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_U64_push(PlewArray_U64* a, uint64_t v) { PlewArray_U64_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; uint64_t* nd = (uint64_t*)plew_arc_alloc(sizeof(uint64_t) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Arg PlewArray_Arg_new(void) { PlewArray_Arg a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Arg PlewArray_Arg_get(PlewArray_Arg a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Arg PlewArray_Arg_copy(PlewArray_Arg a) { PlewArray_Arg r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Arg*)plew_arc_alloc(sizeof(Arg) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Arg_release(PlewArray_Arg a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_Arg PlewArray_Arg_share(PlewArray_Arg a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Arg_unique(PlewArray_Arg* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Arg nc = PlewArray_Arg_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Arg_set(PlewArray_Arg* a, long long i, Arg v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Arg_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Arg_push(PlewArray_Arg* a, Arg v) { PlewArray_Arg_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Arg* nd = (Arg*)plew_arc_alloc(sizeof(Arg) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_MakeField PlewArray_MakeField_new(void) { PlewArray_MakeField a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static MakeField PlewArray_MakeField_get(PlewArray_MakeField a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_MakeField PlewArray_MakeField_copy(PlewArray_MakeField a) { PlewArray_MakeField r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (MakeField*)plew_arc_alloc(sizeof(MakeField) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_MakeField_release(PlewArray_MakeField a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_MakeField PlewArray_MakeField_share(PlewArray_MakeField a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_MakeField_unique(PlewArray_MakeField* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_MakeField nc = PlewArray_MakeField_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_MakeField_set(PlewArray_MakeField* a, long long i, MakeField v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_MakeField_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_MakeField_push(PlewArray_MakeField* a, MakeField v) { PlewArray_MakeField_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MakeField* nd = (MakeField*)plew_arc_alloc(sizeof(MakeField) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_MatchArm PlewArray_MatchArm_new(void) { PlewArray_MatchArm a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static MatchArm PlewArray_MatchArm_get(PlewArray_MatchArm a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_MatchArm PlewArray_MatchArm_copy(PlewArray_MatchArm a) { PlewArray_MatchArm r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (MatchArm*)plew_arc_alloc(sizeof(MatchArm) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = MatchArm_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_MatchArm_release(PlewArray_MatchArm a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) MatchArm_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_MatchArm PlewArray_MatchArm_share(PlewArray_MatchArm a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_MatchArm_unique(PlewArray_MatchArm* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_MatchArm nc = PlewArray_MatchArm_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_MatchArm_set(PlewArray_MatchArm* a, long long i, MatchArm v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_MatchArm_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_MatchArm_push(PlewArray_MatchArm* a, MatchArm v) { PlewArray_MatchArm_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MatchArm* nd = (MatchArm*)plew_arc_alloc(sizeof(MatchArm) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Param PlewArray_Param_new(void) { PlewArray_Param a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Param PlewArray_Param_get(PlewArray_Param a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Param PlewArray_Param_copy(PlewArray_Param a) { PlewArray_Param r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Param*)plew_arc_alloc(sizeof(Param) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Param_release(PlewArray_Param a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_Param PlewArray_Param_share(PlewArray_Param a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Param_unique(PlewArray_Param* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Param nc = PlewArray_Param_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Param_set(PlewArray_Param* a, long long i, Param v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Param_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Param_push(PlewArray_Param* a, Param v) { PlewArray_Param_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Param* nd = (Param*)plew_arc_alloc(sizeof(Param) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_FieldDef PlewArray_FieldDef_new(void) { PlewArray_FieldDef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static FieldDef PlewArray_FieldDef_get(PlewArray_FieldDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_FieldDef PlewArray_FieldDef_copy(PlewArray_FieldDef a) { PlewArray_FieldDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (FieldDef*)plew_arc_alloc(sizeof(FieldDef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_FieldDef_release(PlewArray_FieldDef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_FieldDef PlewArray_FieldDef_share(PlewArray_FieldDef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_FieldDef_unique(PlewArray_FieldDef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_FieldDef nc = PlewArray_FieldDef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_FieldDef_set(PlewArray_FieldDef* a, long long i, FieldDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_FieldDef_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_FieldDef_push(PlewArray_FieldDef* a, FieldDef v) { PlewArray_FieldDef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; FieldDef* nd = (FieldDef*)plew_arc_alloc(sizeof(FieldDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_new(void) { PlewArray_Variant a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Variant PlewArray_Variant_get(PlewArray_Variant a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_copy(PlewArray_Variant a) { PlewArray_Variant r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Variant*)plew_arc_alloc(sizeof(Variant) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = Variant_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Variant_release(PlewArray_Variant a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) Variant_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_share(PlewArray_Variant a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Variant_unique(PlewArray_Variant* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Variant nc = PlewArray_Variant_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Variant_set(PlewArray_Variant* a, long long i, Variant v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Variant_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Variant_push(PlewArray_Variant* a, Variant v) { PlewArray_Variant_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Variant* nd = (Variant*)plew_arc_alloc(sizeof(Variant) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Expr PlewArray_Expr_new(void) { PlewArray_Expr a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Expr PlewArray_Expr_get(PlewArray_Expr a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Expr PlewArray_Expr_copy(PlewArray_Expr a) { PlewArray_Expr r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Expr*)plew_arc_alloc(sizeof(Expr) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Expr_release(PlewArray_Expr a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_Expr PlewArray_Expr_share(PlewArray_Expr a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Expr_unique(PlewArray_Expr* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Expr nc = PlewArray_Expr_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Expr_set(PlewArray_Expr* a, long long i, Expr v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Expr_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Expr_push(PlewArray_Expr* a, Expr v) { PlewArray_Expr_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Expr* nd = (Expr*)plew_arc_alloc(sizeof(Expr) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Stmt PlewArray_Stmt_new(void) { PlewArray_Stmt a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Stmt PlewArray_Stmt_get(PlewArray_Stmt a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Stmt PlewArray_Stmt_copy(PlewArray_Stmt a) { PlewArray_Stmt r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Stmt*)plew_arc_alloc(sizeof(Stmt) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Stmt_release(PlewArray_Stmt a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_Stmt PlewArray_Stmt_share(PlewArray_Stmt a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Stmt_unique(PlewArray_Stmt* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Stmt nc = PlewArray_Stmt_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Stmt_set(PlewArray_Stmt* a, long long i, Stmt v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Stmt_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Stmt_push(PlewArray_Stmt* a, Stmt v) { PlewArray_Stmt_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Stmt* nd = (Stmt*)plew_arc_alloc(sizeof(Stmt) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Block PlewArray_Block_new(void) { PlewArray_Block a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Block PlewArray_Block_get(PlewArray_Block a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Block PlewArray_Block_copy(PlewArray_Block a) { PlewArray_Block r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Block*)plew_arc_alloc(sizeof(Block) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = Block_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Block_release(PlewArray_Block a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) Block_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_Block PlewArray_Block_share(PlewArray_Block a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Block_unique(PlewArray_Block* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Block nc = PlewArray_Block_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Block_set(PlewArray_Block* a, long long i, Block v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Block_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Block_push(PlewArray_Block* a, Block v) { PlewArray_Block_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Block* nd = (Block*)plew_arc_alloc(sizeof(Block) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_new(void) { PlewArray_Func a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Func PlewArray_Func_get(PlewArray_Func a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_copy(PlewArray_Func a) { PlewArray_Func r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Func*)plew_arc_alloc(sizeof(Func) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = Func_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Func_release(PlewArray_Func a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) Func_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_share(PlewArray_Func a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Func_unique(PlewArray_Func* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Func nc = PlewArray_Func_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Func_set(PlewArray_Func* a, long long i, Func v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Func_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Func_push(PlewArray_Func* a, Func v) { PlewArray_Func_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Func* nd = (Func*)plew_arc_alloc(sizeof(Func) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_new(void) { PlewArray_StructDef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static StructDef PlewArray_StructDef_get(PlewArray_StructDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_copy(PlewArray_StructDef a) { PlewArray_StructDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (StructDef*)plew_arc_alloc(sizeof(StructDef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = StructDef_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_StructDef_release(PlewArray_StructDef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) StructDef_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_share(PlewArray_StructDef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_StructDef_unique(PlewArray_StructDef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_StructDef nc = PlewArray_StructDef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_StructDef_set(PlewArray_StructDef* a, long long i, StructDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_StructDef_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_StructDef_push(PlewArray_StructDef* a, StructDef v) { PlewArray_StructDef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; StructDef* nd = (StructDef*)plew_arc_alloc(sizeof(StructDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_new(void) { PlewArray_EnumDef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static EnumDef PlewArray_EnumDef_get(PlewArray_EnumDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_copy(PlewArray_EnumDef a) { PlewArray_EnumDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (EnumDef*)plew_arc_alloc(sizeof(EnumDef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = EnumDef_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_EnumDef_release(PlewArray_EnumDef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) EnumDef_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_share(PlewArray_EnumDef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_EnumDef_unique(PlewArray_EnumDef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_EnumDef nc = PlewArray_EnumDef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_EnumDef_set(PlewArray_EnumDef* a, long long i, EnumDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_EnumDef_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_EnumDef_push(PlewArray_EnumDef* a, EnumDef v) { PlewArray_EnumDef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; EnumDef* nd = (EnumDef*)plew_arc_alloc(sizeof(EnumDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_new(void) { PlewArray_TypeRef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static TypeRef PlewArray_TypeRef_get(PlewArray_TypeRef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_copy(PlewArray_TypeRef a) { PlewArray_TypeRef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (TypeRef*)plew_arc_alloc(sizeof(TypeRef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = TypeRef_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_TypeRef_release(PlewArray_TypeRef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) TypeRef_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_share(PlewArray_TypeRef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_TypeRef_unique(PlewArray_TypeRef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_TypeRef nc = PlewArray_TypeRef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_TypeRef_set(PlewArray_TypeRef* a, long long i, TypeRef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_TypeRef_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_TypeRef_push(PlewArray_TypeRef* a, TypeRef v) { PlewArray_TypeRef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; TypeRef* nd = (TypeRef*)plew_arc_alloc(sizeof(TypeRef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Local PlewArray_Local_new(void) { PlewArray_Local a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Local PlewArray_Local_get(PlewArray_Local a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Local PlewArray_Local_copy(PlewArray_Local a) { PlewArray_Local r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Local*)plew_arc_alloc(sizeof(Local) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Local_release(PlewArray_Local a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_Local PlewArray_Local_share(PlewArray_Local a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Local_unique(PlewArray_Local* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Local nc = PlewArray_Local_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Local_set(PlewArray_Local* a, long long i, Local v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Local_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Local_push(PlewArray_Local* a, Local v) { PlewArray_Local_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Local* nd = (Local*)plew_arc_alloc(sizeof(Local) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_PatInfo PlewArray_PatInfo_new(void) { PlewArray_PatInfo a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static PatInfo PlewArray_PatInfo_get(PlewArray_PatInfo a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_PatInfo PlewArray_PatInfo_copy(PlewArray_PatInfo a) { PlewArray_PatInfo r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (PatInfo*)plew_arc_alloc(sizeof(PatInfo) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = PatInfo_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_PatInfo_release(PlewArray_PatInfo a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) PatInfo_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_PatInfo PlewArray_PatInfo_share(PlewArray_PatInfo a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_PatInfo_unique(PlewArray_PatInfo* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_PatInfo nc = PlewArray_PatInfo_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_PatInfo_set(PlewArray_PatInfo* a, long long i, PatInfo v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_PatInfo_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_PatInfo_push(PlewArray_PatInfo* a, PatInfo v) { PlewArray_PatInfo_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; PatInfo* nd = (PatInfo*)plew_arc_alloc(sizeof(PatInfo) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
Lexer Lexer_copy(Lexer s) { Lexer r = s; r.bytes = PlewArray_U8_copy(s.bytes); r.toks = PlewArray_Tok_copy(s.toks); return r; }
Lexer Lexer_share(Lexer s) { plew_arc_retain(s.bytes.rc); plew_arc_retain(s.toks.rc); return s; }
void Lexer_release(Lexer s) { PlewArray_U8_release(s.bytes); PlewArray_Tok_release(s.toks); }
TypeRef TypeRef_copy(TypeRef s) { TypeRef r = s; r.args = PlewArray_U64_copy(s.args); return r; }
TypeRef TypeRef_share(TypeRef s) { plew_arc_retain(s.args.rc); return s; }
void TypeRef_release(TypeRef s) { PlewArray_U64_release(s.args); }
MatchArm MatchArm_copy(MatchArm s) { MatchArm r = s; r.binds = PlewArray_Bind_copy(s.binds); return r; }
MatchArm MatchArm_share(MatchArm s) { plew_arc_retain(s.binds.rc); return s; }
void MatchArm_release(MatchArm s) { PlewArray_Bind_release(s.binds); }
PatInfo PatInfo_copy(PatInfo s) { PatInfo r = s; r.binds = PlewArray_Bind_copy(s.binds); return r; }
PatInfo PatInfo_share(PatInfo s) { plew_arc_retain(s.binds.rc); return s; }
void PatInfo_release(PatInfo s) { PlewArray_Bind_release(s.binds); }
Block Block_copy(Block s) { Block r = s; r.stmts = PlewArray_U64_copy(s.stmts); return r; }
Block Block_share(Block s) { plew_arc_retain(s.stmts.rc); return s; }
void Block_release(Block s) { PlewArray_U64_release(s.stmts); }
StructDef StructDef_copy(StructDef s) { StructDef r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.fields = PlewArray_FieldDef_copy(s.fields); return r; }
StructDef StructDef_share(StructDef s) { plew_arc_retain(s.typeParams.rc); plew_arc_retain(s.fields.rc); return s; }
void StructDef_release(StructDef s) { PlewArray_Bind_release(s.typeParams); PlewArray_FieldDef_release(s.fields); }
Variant Variant_copy(Variant s) { Variant r = s; r.fields = PlewArray_FieldDef_copy(s.fields); return r; }
Variant Variant_share(Variant s) { plew_arc_retain(s.fields.rc); return s; }
void Variant_release(Variant s) { PlewArray_FieldDef_release(s.fields); }
EnumDef EnumDef_copy(EnumDef s) { EnumDef r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.variants = PlewArray_Variant_copy(s.variants); return r; }
EnumDef EnumDef_share(EnumDef s) { plew_arc_retain(s.typeParams.rc); plew_arc_retain(s.variants.rc); return s; }
void EnumDef_release(EnumDef s) { PlewArray_Bind_release(s.typeParams); PlewArray_Variant_release(s.variants); }
Func Func_copy(Func s) { Func r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.params = PlewArray_Param_copy(s.params); return r; }
Func Func_share(Func s) { plew_arc_retain(s.typeParams.rc); plew_arc_retain(s.params.rc); return s; }
void Func_release(Func s) { PlewArray_Bind_release(s.typeParams); PlewArray_Param_release(s.params); }
Comp Comp_copy(Comp s) { Comp r = s; r.bytes = PlewArray_U8_copy(s.bytes); r.toks = PlewArray_Tok_copy(s.toks); r.exprs = PlewArray_Expr_copy(s.exprs); r.stmts = PlewArray_Stmt_copy(s.stmts); r.blocks = PlewArray_Block_copy(s.blocks); r.funcs = PlewArray_Func_copy(s.funcs); r.structs = PlewArray_StructDef_copy(s.structs); r.enums = PlewArray_EnumDef_copy(s.enums); r.types = PlewArray_TypeRef_copy(s.types); r.genInsts = PlewArray_U64_copy(s.genInsts); r.fnTypes = PlewArray_U64_copy(s.fnTypes); r.arrayElems = PlewArray_Bind_copy(s.arrayElems); r.locals = PlewArray_Local_copy(s.locals); r.curTypeParams = PlewArray_Bind_copy(s.curTypeParams); r.curTypeArgs = PlewArray_U64_copy(s.curTypeArgs); return r; }
Comp Comp_share(Comp s) { plew_arc_retain(s.bytes.rc); plew_arc_retain(s.toks.rc); plew_arc_retain(s.exprs.rc); plew_arc_retain(s.stmts.rc); plew_arc_retain(s.blocks.rc); plew_arc_retain(s.funcs.rc); plew_arc_retain(s.structs.rc); plew_arc_retain(s.enums.rc); plew_arc_retain(s.types.rc); plew_arc_retain(s.genInsts.rc); plew_arc_retain(s.fnTypes.rc); plew_arc_retain(s.arrayElems.rc); plew_arc_retain(s.locals.rc); plew_arc_retain(s.curTypeParams.rc); plew_arc_retain(s.curTypeArgs.rc); return s; }
void Comp_release(Comp s) { PlewArray_U8_release(s.bytes); PlewArray_Tok_release(s.toks); PlewArray_Expr_release(s.exprs); PlewArray_Stmt_release(s.stmts); PlewArray_Block_release(s.blocks); PlewArray_Func_release(s.funcs); PlewArray_StructDef_release(s.structs); PlewArray_EnumDef_release(s.enums); PlewArray_TypeRef_release(s.types); PlewArray_U64_release(s.genInsts); PlewArray_U64_release(s.fnTypes); PlewArray_Bind_release(s.arrayElems); PlewArray_Local_release(s.locals); PlewArray_Bind_release(s.curTypeParams); PlewArray_U64_release(s.curTypeArgs); }
unsigned char Lexer_at(Lexer self, uint64_t off);
void Lexer_emit(Lexer* self, Kind k, uint64_t start, uint64_t len);
long long Lexer_lastWasNewline(Lexer self);
long long Lexer_lastCanEnd(Lexer self);
long long isDigit(unsigned char b);
long long isAlpha(unsigned char b);
long long isAlnum(unsigned char b);
long long rangeEquals(PlewArray_U8 bytes, uint64_t start, uint64_t len, PlewString kw);
Kind identKind(PlewArray_U8 bytes, uint64_t start, uint64_t len);
void lex(Lexer* lx);
int64_t kindCode(Kind k);
Kind Comp_curKind(Comp* self);
Tok Comp_cur(Comp* self);
Kind Comp_peekKind(Comp* self, uint64_t off);
void Comp_advance(Comp* self);
void Comp_skipNewlines(Comp* self);
long long Comp_identIs(Comp* self, PlewString kw);
uint64_t Comp_pushExpr(Comp* self, Expr e);
uint64_t Comp_pushStmt(Comp* self, Stmt s);
uint64_t Comp_pushType(Comp* self, TypeRef t);
int64_t Comp_tokenValue(Comp* self, Tok t);
int64_t binPrec(Kind k);
int64_t charValue(Comp* c, Tok t);
uint64_t parsePrimary(Comp* c);
uint64_t parseUnary(Comp* c);
uint64_t parsePostfix(Comp* c);
uint64_t parseMake(Comp* c);
uint64_t parseBin(Comp* c, int64_t minPrec);
uint64_t parseExpr(Comp* c);
PlewArray_Arg parseCallArgs(Comp* c);
long long isAssignOp(Kind k);
PType parseTypeTok(Comp* c);
PlewArray_Bind parseTypeParams(Comp* c);
void recordArrayElem(Comp* c, PType ty);
uint64_t parseLet(Comp* c, long long mutable);
uint64_t parsePrint(Comp* c);
uint64_t parsePanic(Comp* c);
uint64_t parseReturn(Comp* c);
uint64_t parseIf(Comp* c);
uint64_t parseIfExpr(Comp* c);
uint64_t parseGive(Comp* c);
uint64_t parseWhile(Comp* c);
uint64_t parseFor(Comp* c);
uint64_t parseExprOrAssign(Comp* c);
PatInfo parsePattern(Comp* c);
long long bindNamesMatch(Comp* c, PlewArray_Bind a, PlewArray_Bind b);
PlewArray_PatInfo parseArmPatterns(Comp* c);
uint64_t parseMatch(Comp* c);
uint64_t parseMatchExpr(Comp* c);
uint64_t parseStmt(Comp* c);
uint64_t parseBlock(Comp* c);
PlewArray_Param parseParamList(Comp* c);
void parseFuncCommon(Comp* c, long long hasRecv, uint64_t recvStart, uint64_t recvLen, long long selfInout, PlewArray_Bind implParams);
void parseFunc(Comp* c);
void parseImpl(Comp* c);
void parseStruct(Comp* c);
void parseEnum(Comp* c);
void markImport(Comp* c, uint64_t segStart, uint64_t segLen, uint64_t nameStart, uint64_t nameLen);
void parseImport(Comp* c);
void parseProgram(Comp* c);
PlewString digitStr(int64_t d);
void writeInt(int64_t n);
PlewString digitStrU(uint64_t d);
void writeU64(uint64_t n);
void writeSpan(Comp* c, uint64_t start, uint64_t len);
void eprintInt(int64_t n);
void compileError(PlewString msg);
void compileErrorAt(int64_t line, PlewString msg);
long long isPrimType(Comp* c, uint64_t start, uint64_t len);
long long isIntType(Comp* c, uint64_t start, uint64_t len);
uint64_t intBits(Comp* c, uint64_t start, uint64_t len);
long long intSigned(Comp* c, uint64_t start, uint64_t len);
long long losslessInt(Comp* c, uint64_t srcStart, uint64_t srcLen, uint64_t dstStart, uint64_t dstLen);
long long litFitsType(Comp* c, int64_t value, uint64_t dstStart, uint64_t dstLen);
long long litFitsBits(int64_t value, uint64_t bits, long long sgn);
void genCElem(Comp* c, uint64_t start, uint64_t len);
void genCTypeRef(Comp* c, uint64_t start, uint64_t len, long long isArray);
void genCType(Comp* c, uint64_t start, uint64_t len);
void genTypeInfoCType(Comp* c, TypeInfo ti);
long long spansEqual(Comp* c, uint64_t aStart, uint64_t aLen, uint64_t bStart, uint64_t bLen);
int64_t lineOf(Comp* c, uint64_t offset);
uint64_t exprOffset(Comp* c, uint64_t id);
uint64_t findFunc(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t findMethod(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen);
long long paramsLabelsOk(Comp* c, PlewArray_Param params, PlewArray_Arg args);
long long callLabelsOk(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
long long armCovers(Comp* c, PlewArray_MatchArm arms, uint64_t variantStart, uint64_t variantLen);
long long matchExhaustive(Comp* c, PlewArray_MatchArm arms);
uint64_t variantIndex(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen);
TypeInfo scalarInfo(void);
TypeInfo typeInfoOfName(Comp* c, uint64_t start, uint64_t len, long long isArray);
void addLocal(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned);
uint64_t scopeMark(Comp* c);
void emitScopeDrops(Comp* c, uint64_t mark);
long long structLocalReleasable(Comp* c, uint64_t start, uint64_t len);
void popLocals(Comp* c, uint64_t mark);
void scopeExit(Comp* c, uint64_t mark);
long long localIsMutable(Comp* c, uint64_t start, uint64_t len);
long long isSelfRef(Comp* c, uint64_t start, uint64_t len);
long long isInoutLocal(Comp* c, uint64_t start, uint64_t len);
TypeInfo fieldType(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen);
long long fieldDeclaredMut(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen);
long long placeIsMutable(Comp* c, uint64_t id);
TypeInfo exprType(Comp* c, uint64_t id);
uint64_t blockGiveExpr(Comp* c, uint64_t blkId);
void addBindLocal(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen);
void genBindType(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen);
PlewString binOpStr(int64_t op);
PlewString unaryOpStr(int64_t op);
int64_t strDecodedLen(Comp* c, uint64_t start, uint64_t len);
long long isCheckedArith(int64_t op);
int64_t compoundCheckedBin(int64_t op);
PlewString overflowBuiltin(int64_t op);
TypeInfo arithIntType(Comp* c, uint64_t lhs, uint64_t rhs);
void genCheckedArith(Comp* c, int64_t op, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen);
void genArrayGet(Comp* c, uint64_t base, uint64_t index, uint64_t elemStart, uint64_t elemLen);
PlewString intMinMacro(Comp* c, uint64_t start, uint64_t len);
void genCheckedNeg(Comp* c, uint64_t operand, uint64_t tyStart, uint64_t tyLen);
void genCheckedDiv(Comp* c, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen, long long isMod);
PlewString assignOpStr(int64_t op);
long long isCompoundDiv(int64_t op);
PlewString compoundDivFn(int64_t op);
PlewString assignToBinStr(int64_t op);
ConstInt notConst(void);
ConstInt foldConst(Comp* c, uint64_t id);
long long tiIsInt(Comp* c, TypeInfo ti);
void checkLitLeaf(Comp* c, int64_t value, uint64_t offset, long long isBool, uint64_t tyStart, uint64_t tyLen, uint64_t eKind, uint64_t eBits, long long eSgn);
void checkLitCtx(Comp* c, uint64_t id, uint64_t eKind, uint64_t eBits, long long eSgn);
IntTy exprIntTy(Comp* c, uint64_t id);
void checkArithNoCtx(Comp* c, uint64_t lhs, uint64_t rhs);
void checkLitTi(Comp* c, uint64_t id, TypeInfo ti);
void checkLitSpan(Comp* c, uint64_t id, uint64_t tyStart, uint64_t tyLen, long long isArray);
void checkLitArray(Comp* c, uint64_t id, uint64_t elemStart, uint64_t elemLen);
void checkCallArgs(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
void checkMethodArgs(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
TypeInfo makeFieldType(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen);
void checkMakeFields(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t ty, PlewArray_MakeField fields);
void genExpr(Comp* c, uint64_t id);
long long isPlaceExpr(Comp* c, uint64_t id);
void genArrayValue(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen);
void genArrayLiteral(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen);
long long isStringEq(Comp* c, int64_t op, uint64_t lhs);
long long isEnumName(Comp* c, uint64_t start, uint64_t len);
long long isAllNullary(Comp* c, uint64_t start, uint64_t len);
long long isEnumEq(Comp* c, int64_t op, uint64_t lhs);
long long compareNeedsTrait(Comp* c, int64_t op, uint64_t lhs);
void emitEnumOperand(Comp* c, uint64_t id, uint64_t enStart, uint64_t enLen);
void emitEnumTagCmp(Comp* c, uint64_t lhs, uint64_t rhs, int64_t op, long long outer);
void genCond(Comp* c, uint64_t id);
void genStmt(Comp* c, uint64_t id);
void genBlock(Comp* c, uint64_t id);
long long nameIsMain(Comp* c, Func f);
uint64_t structIndexByName(Comp* c, uint64_t start, uint64_t len);
long long structNeedsCopy(Comp* c, uint64_t start, uint64_t len);
void emitStructCopyProto(Comp* c, uint64_t si);
void emitStructCopyDef(Comp* c, uint64_t si);
void emitStructShareProto(Comp* c, uint64_t si);
void emitStructShareDef(Comp* c, uint64_t si);
void emitStructReleaseProto(Comp* c, uint64_t si);
void emitStructReleaseDef(Comp* c, uint64_t si);
long long monoStructNeedsCopy(Comp* c, uint64_t instRef);
void emitMonoStructCopyProto(Comp* c, uint64_t instRef);
void emitMonoStructCopyDef(Comp* c, uint64_t instRef);
long long monoEnumNeedsCopy(Comp* c, uint64_t instRef);
void emitMonoEnumCopyProto(Comp* c, uint64_t instRef);
void emitMonoEnumCopyDef(Comp* c, uint64_t instRef);
void genStructValue(Comp* c, uint64_t exprId, uint64_t structStart, uint64_t structLen);
void genCopyValue(Comp* c, uint64_t exprId, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray);
void genStructDef(Comp* c, uint64_t si);
void genSignature(Comp* c, Func f);
void genFunc(Comp* c, uint64_t fi);
void genClosure(Comp* c, uint64_t id, long long proto);
void emitClosures(Comp* c, long long proto);
void genEnumDef(Comp* c, uint64_t ei);
uint64_t genericStructIndex(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t genericEnumIndex(Comp* c, uint64_t nameStart, uint64_t nameLen);
long long isGenericInst(Comp* c, uint64_t ref);
long long isFnType(Comp* c, uint64_t ref);
long long isRefInst(Comp* c, uint64_t ref);
long long isGenericEnumInst(Comp* c, uint64_t ref);
long long typeRefEq(Comp* c, uint64_t a, uint64_t b);
void emitMangle(Comp* c, uint64_t ref);
void emitConcreteCType(Comp* c, uint64_t ref);
void emitFieldCType(Comp* c, uint64_t ref, PlewArray_Bind params, PlewArray_U64 args);
uint64_t resolveTy(Comp* c, uint64_t tyRef);
void genCTypeOf(Comp* c, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray);
long long isTypeParamName(Comp* c, uint64_t start, uint64_t len);
long long tyRefIsGround(Comp* c, uint64_t ref);
void registerArrayElemRef(Comp* c, uint64_t elemRef);
void scanType(Comp* c, uint64_t ref);
void collectGenInsts(Comp* c);
TypeInfo typeInfoOfRef(Comp* c, uint64_t ref);
TypeInfo substTypeInfo(Comp* c, uint64_t instRef, PlewArray_Bind params, uint64_t tyRef);
TypeInfo genericFieldTypeInfo(Comp* c, uint64_t instRef, uint64_t fieldStart, uint64_t fieldLen);
TypeInfo genericEnumFieldTypeInfo(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen);
void genBindTypeInst(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen);
void emitFnTypedef(Comp* c, uint64_t fnRef);
void emitMonoForward(Comp* c, uint64_t instRef);
void emitMonoStruct(Comp* c, uint64_t instRef);
void emitMonoEnum(Comp* c, uint64_t instRef);
long long methodMatchesInst(Comp* c, Func f, uint64_t instRef);
void emitMonoMethod(Comp* c, uint64_t fi, uint64_t instRef, long long proto);
void emitMonoMethods(Comp* c, long long proto);
void wPA(Comp* c, uint64_t elemStart, uint64_t elemLen);
void genArrayTypedef(Comp* c, uint64_t elemStart, uint64_t elemLen);
void genArrayRuntimeFns(Comp* c, uint64_t elemStart, uint64_t elemLen);
long long isU8Elem(Comp* c, uint64_t elemStart, uint64_t elemLen);
void genU8ArrayTypedef(void);
void genU8ArrayRuntime(void);
long long isPathTokKind(Kind k);
PlewArray_Bind collectParts(PlewArray_U8 rootBytes, PlewArray_Tok toks);
uint64_t stripParents(PlewArray_U8 path, uint64_t baseLen, uint64_t n);
PlewArray_U8 resolveImport(PlewArray_U8 src, uint64_t pStart, uint64_t pLen, PlewArray_U8 importer, uint64_t baseLen, PlewArray_U8 srcRoot, uint64_t srcRootLen, PlewArray_U8 stdRoot, uint64_t stdRootLen);
void appendBytes(PlewArray_U8* into, PlewArray_U8 from);
PlewArray_U8 extractSpan(PlewArray_U8 buf, uint64_t start, uint64_t len);
uint64_t dirPrefixLen(PlewArray_U8 path);
PlewArray_U8 computeStdRoot(PlewArray_U8 arg0);
PlewArray_U8 findSrcRoot(PlewArray_U8 entry);
long long pathSeen(PlewArray_U8 buf, PlewArray_Bind loaded, PlewArray_U8 path);
int main(int argc, char** argv) {
    plew_argc = argc; plew_argv = argv;
    PlewArray_U8 combined = PlewArray_U8_new();
    if (plew_arg_count() > 1) {
    PlewString rootPath = plew_arg_at((long long)(1));
    PlewArray_U8 entryBytes = PlewArray_U8_share(({ PlewString __s = rootPath; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    PlewArray_U8 pathBuf = PlewArray_U8_new();
    PlewArray_Bind loaded = PlewArray_Bind_new();
    PlewArray_U8 srcRoot = findSrcRoot(entryBytes);
    PlewArray_U8 stdRoot = computeStdRoot(({ PlewString __s = plew_arg_at((long long)(0)); (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    uint64_t es = (long long)((pathBuf).len);
    appendBytes(&(pathBuf), entryBytes);
    PlewArray_Bind_push(&(loaded), (Bind){.nameStart = es, .nameLen = (long long)((entryBytes).len), .fieldStart = es, .fieldLen = (long long)((entryBytes).len)});
    uint64_t qi = 0;
    while (qi < (long long)((loaded).len)) {
    Bind ent = PlewArray_Bind_get(loaded, (long long)(qi));
    qi = ({ uint64_t __ov; if (__builtin_add_overflow((qi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_U8 path = extractSpan(pathBuf, ent.nameStart, ent.nameLen);
    PlewString src = plew_read_file_bytes(path);
    PlewArray_U8 sb = PlewArray_U8_share(({ PlewString __s = src; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    if ((long long)((combined).len) > 0) {
    PlewArray_U8_push(&(combined), 10);
    }
    appendBytes(&(combined), sb);
    Lexer lxp = (Lexer){.bytes = PlewArray_U8_share(sb), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0};
    lex(&(lxp));
    PlewArray_Bind incs = collectParts(sb, lxp.toks);
    uint64_t baseLen = dirPrefixLen(path);
    uint64_t pj = 0;
    while (pj < (long long)((incs).len)) {
    Bind pb = PlewArray_Bind_get(incs, (long long)(pj));
    PlewArray_U8 childPath = resolveImport(sb, pb.nameStart, pb.nameLen, path, baseLen, srcRoot, (long long)((srcRoot).len), stdRoot, (long long)((stdRoot).len));
    if ((long long)((childPath).len) == 0) {
    }
    else {
    if (pathSeen(pathBuf, loaded, childPath)) {
    }
    else {
    uint64_t cs = (long long)((pathBuf).len);
    appendBytes(&(pathBuf), childPath);
    PlewArray_Bind_push(&(loaded), (Bind){.nameStart = cs, .nameLen = (long long)((childPath).len), .fieldStart = cs, .fieldLen = (long long)((childPath).len)});
    }
    }
    pj = ({ uint64_t __ov; if (__builtin_add_overflow((pj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_U8_release(childPath);
    }
    PlewArray_Bind_release(incs);
    Lexer_release(lxp);
    PlewArray_U8_release(sb);
    PlewArray_U8_release(path);
    }
    PlewArray_U8_release(stdRoot);
    PlewArray_U8_release(srcRoot);
    PlewArray_Bind_release(loaded);
    PlewArray_U8_release(pathBuf);
    PlewArray_U8_release(entryBytes);
    }
    else {
    PlewString s = plew_read_stdin();
    appendBytes(&(combined), ({ PlewString __s = s; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    }
    Lexer lx = (Lexer){.bytes = PlewArray_U8_share(combined), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0};
    lex(&(lx));
    Comp c = (Comp){.bytes = PlewArray_U8_share(combined), .toks = PlewArray_Tok_share(lx.toks), .pos = 0, .exprs = PlewArray_Expr_new(), .stmts = PlewArray_Stmt_new(), .blocks = PlewArray_Block_new(), .funcs = PlewArray_Func_new(), .structs = PlewArray_StructDef_new(), .enums = PlewArray_EnumDef_new(), .types = PlewArray_TypeRef_new(), .genInsts = PlewArray_U64_new(), .fnTypes = PlewArray_U64_new(), .arrayElems = PlewArray_Bind_new(), .locals = PlewArray_Local_new(), .tmp = 0, .curIsMain = 0, .curRetVoid = 0, .curRetStart = 0, .curRetLen = 0, .curRetIsArray = 0, .curRetTy = 0, .curHasRecv = 0, .curRecvStart = 0, .curRecvLen = 0, .curSelfInout = 0, .curTypeParams = PlewArray_Bind_new(), .curTypeArgs = PlewArray_U64_new(), .curRecvInstRef = 0, .curGiveTmp = 0, .impPrint = 0, .impWrite = 0, .impWriteByte = 0, .impReadStdin = 0, .impReadFile = 0, .impArgCount = 0, .impArgAt = 0, .impEprint = 0, .impExit = 0, .impReadFileBytes = 0, .impFileExists = 0};
    PlewArray_TypeRef_push(&(c.types), (TypeRef){.nameStart = 0, .nameLen = 0, .args = PlewArray_U64_new()});
    parseProgram(&(c));
    collectGenInsts(&(c));
    plew_write((PlewString){"#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n#include <string.h>\n", 79});
    plew_write((PlewString){"typedef struct { const char* data; long long len; } PlewString;\n", 64});
    plew_write((PlewString){"__attribute__((unused)) static void* plew_arc_alloc(long long bytes) { long long* p = (long long*)malloc(sizeof(long long) + (size_t)bytes); p[0] = 1; return (void*)(p + 1); }\n", 176});
    plew_write((PlewString){"__attribute__((unused)) static void plew_arc_retain(long long* rc) { if (rc) (*rc) += 1; }\n", 91});
    plew_write((PlewString){"__attribute__((unused)) static void plew_arc_release(long long* rc) { if (rc && (--(*rc)) == 0) free((void*)rc); }\n", 115});
    plew_write((PlewString){"__attribute__((unused)) static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (long long i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }\n", 197});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_read_stdin(void) { size_t cap = 4096, len = 0; char* buf = (char*)malloc(cap); int ch; while ((ch = getchar()) != EOF) { if (len + 1 >= cap) { cap *= 2; buf = (char*)realloc(buf, cap); } buf[len++] = (char)ch; } PlewString s; s.data = buf; s.len = (long long)len; return s; }\n", 323});
    plew_write((PlewString){"__attribute__((unused)) static void plew_write(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stdout); }\n", 107});
    plew_write((PlewString){"__attribute__((unused)) static void plew_eprint(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stderr); }\n", 108});
    plew_write((PlewString){"__attribute__((noreturn)) static void plew_panic(PlewString m) { fputs(\"panic: \", stderr); fwrite(m.data, 1, (size_t)m.len, stderr); fputc('\\n', stderr); exit(1); }\n", 165});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_div(long long a, long long b) { if (b == 0) plew_panic((PlewString){\"division by zero\", 16}); if (b == -1 && a == INT64_MIN) plew_panic((PlewString){\"integer overflow\", 16}); return a / b; }\n", 237});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_mod(long long a, long long b) { if (b == 0) plew_panic((PlewString){\"remainder by zero\", 17}); if (b == -1) return 0; return a % b; }\n", 180});
    plew_write((PlewString){"static int plew_argc = 0;\nstatic char** plew_argv = 0;\n", 55});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_arg_count(void) { return (long long)plew_argc; }\n", 95});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_arg_at(long long i) { PlewString s; if (i < 0 || i >= plew_argc) { s.data = \"\"; s.len = 0; return s; } s.data = plew_argv[i]; s.len = (long long)strlen(plew_argv[i]); return s; }\n", 226});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_read_file(PlewString path) { FILE* f = fopen(path.data, \"rb\"); PlewString s; if (!f) { s.data = \"\"; s.len = 0; return s; } fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET); char* buf = (char*)malloc((size_t)sz + 1); size_t n = fread(buf, 1, (size_t)sz, f); fclose(f); buf[n] = 0; s.data = buf; s.len = (long long)n; return s; }\n", 391});
    uint64_t si = 0;
    while (si < (long long)((c.structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get(c.structs, (long long)(si)));
    if ((long long)((s.typeParams).len) > 0) {
    }
    else {
    plew_write((PlewString){"typedef struct ", 15});
    writeSpan(&(c), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&(c), s.nameStart, s.nameLen);
    plew_write((PlewString){";\n", 2});
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    uint64_t ei = 0;
    while (ei < (long long)((c.enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get(c.enums, (long long)(ei)));
    if ((long long)((e.typeParams).len) > 0) {
    }
    else {
    plew_write((PlewString){"typedef struct ", 15});
    writeSpan(&(c), e.nameStart, e.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&(c), e.nameStart, e.nameLen);
    plew_write((PlewString){";\n", 2});
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    uint64_t mfi = 0;
    while (mfi < (long long)((c.genInsts).len)) {
    emitMonoForward(&(c), PlewArray_U64_get(c.genInsts, (long long)(mfi)));
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genU8ArrayTypedef();
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_read_file_bytes(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; PlewString r = plew_read_file((PlewString){path, p.len}); free(path); return r; }\n", 264});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_file_exists(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; FILE* f = fopen(path, \"rb\"); free(path); if (f) { fclose(f); return 1; } return 0; }\n", 262});
    uint64_t ai = 0;
    while (ai < (long long)((c.arrayElems).len)) {
    Bind ae = PlewArray_Bind_get(c.arrayElems, (long long)(ai));
    if (isU8Elem(&(c), ae.nameStart, ae.nameLen)) {
    }
    else {
    genArrayTypedef(&(c), ae.nameStart, ae.nameLen);
    }
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t ej = 0;
    while (ej < (long long)((c.enums).len)) {
    EnumDef ge = EnumDef_share(PlewArray_EnumDef_get(c.enums, (long long)(ej)));
    if ((long long)((ge.typeParams).len) > 0) {
    }
    else {
    genEnumDef(&(c), ej);
    }
    ej = ({ uint64_t __ov; if (__builtin_add_overflow((ej), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(ge);
    }
    uint64_t sj = 0;
    while (sj < (long long)((c.structs).len)) {
    StructDef gs = StructDef_share(PlewArray_StructDef_get(c.structs, (long long)(sj)));
    if ((long long)((gs.typeParams).len) > 0) {
    }
    else {
    genStructDef(&(c), sj);
    }
    sj = ({ uint64_t __ov; if (__builtin_add_overflow((sj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(gs);
    }
    uint64_t mbi = 0;
    while (mbi < (long long)((c.genInsts).len)) {
    if (isGenericEnumInst(&(c), PlewArray_U64_get(c.genInsts, (long long)(mbi)))) {
    emitMonoEnum(&(c), PlewArray_U64_get(c.genInsts, (long long)(mbi)));
    }
    else {
    emitMonoStruct(&(c), PlewArray_U64_get(c.genInsts, (long long)(mbi)));
    }
    mbi = ({ uint64_t __ov; if (__builtin_add_overflow((mbi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t spp = 0;
    while (spp < (long long)((c.structs).len)) {
    StructDef cps = StructDef_share(PlewArray_StructDef_get(c.structs, (long long)(spp)));
    if ((long long)((cps.typeParams).len) > 0) {
    }
    else {
    if (structNeedsCopy(&(c), cps.nameStart, cps.nameLen)) {
    emitStructCopyProto(&(c), spp);
    emitStructShareProto(&(c), spp);
    emitStructReleaseProto(&(c), spp);
    }
    }
    spp = ({ uint64_t __ov; if (__builtin_add_overflow((spp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(cps);
    }
    genU8ArrayRuntime();
    uint64_t ar = 0;
    while (ar < (long long)((c.arrayElems).len)) {
    Bind ae2 = PlewArray_Bind_get(c.arrayElems, (long long)(ar));
    if (isU8Elem(&(c), ae2.nameStart, ae2.nameLen)) {
    }
    else {
    genArrayRuntimeFns(&(c), ae2.nameStart, ae2.nameLen);
    }
    ar = ({ uint64_t __ov; if (__builtin_add_overflow((ar), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t scd = 0;
    while (scd < (long long)((c.structs).len)) {
    StructDef cs2 = StructDef_share(PlewArray_StructDef_get(c.structs, (long long)(scd)));
    if ((long long)((cs2.typeParams).len) > 0) {
    }
    else {
    if (structNeedsCopy(&(c), cs2.nameStart, cs2.nameLen)) {
    emitStructCopyDef(&(c), scd);
    emitStructShareDef(&(c), scd);
    emitStructReleaseDef(&(c), scd);
    }
    }
    scd = ({ uint64_t __ov; if (__builtin_add_overflow((scd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(cs2);
    }
    uint64_t mcp = 0;
    while (mcp < (long long)((c.genInsts).len)) {
    if (isGenericEnumInst(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)))) {
    if (monoEnumNeedsCopy(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)))) {
    emitMonoEnumCopyProto(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)));
    }
    }
    else {
    if (monoStructNeedsCopy(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)))) {
    emitMonoStructCopyProto(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)));
    }
    }
    mcp = ({ uint64_t __ov; if (__builtin_add_overflow((mcp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t mcd = 0;
    while (mcd < (long long)((c.genInsts).len)) {
    if (isGenericEnumInst(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)))) {
    if (monoEnumNeedsCopy(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)))) {
    emitMonoEnumCopyDef(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)));
    }
    }
    else {
    if (monoStructNeedsCopy(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)))) {
    emitMonoStructCopyDef(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)));
    }
    }
    mcd = ({ uint64_t __ov; if (__builtin_add_overflow((mcd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t fti = 0;
    while (fti < (long long)((c.fnTypes).len)) {
    emitFnTypedef(&(c), PlewArray_U64_get(c.fnTypes, (long long)(fti)));
    fti = ({ uint64_t __ov; if (__builtin_add_overflow((fti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t i = 0;
    while (i < (long long)((c.funcs).len)) {
    Func f = Func_share(PlewArray_Func_get(c.funcs, (long long)(i)));
    if (nameIsMain(&(c), f)) {
    }
    else {
    if ((long long)((f.typeParams).len) > 0) {
    }
    else {
    genSignature(&(c), f);
    plew_write((PlewString){";\n", 2});
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    emitMonoMethods(&(c), 1);
    emitClosures(&(c), 1);
    {
    long long __fe0 = (long long)((c.funcs).len);
    for (long long j = 0; j < __fe0; j++) {
    Func fb = Func_share(PlewArray_Func_get(c.funcs, (long long)(j)));
    if ((long long)((fb.typeParams).len) > 0) {
    }
    else {
    genFunc(&(c), j);
    }
    Func_release(fb);
    }
    }
    emitMonoMethods(&(c), 0);
    emitClosures(&(c), 0);
    Comp_release(c);
    Lexer_release(lx);
    PlewArray_U8_release(combined);
    return 0;
}
unsigned char Lexer_at(Lexer self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow((self.pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)((self.bytes).len)) {
    { unsigned char __ret1 = PlewArray_U8_get(self.bytes, (long long)(i));
    return __ret1; }
    }
    { unsigned char __ret2 = 0;
    return __ret2; }
}
void Lexer_emit(Lexer* self, Kind k, uint64_t start, uint64_t len) {
    PlewArray_Tok_push(&((*self).toks), (Tok){.kind = k, .start = start, .len = len});
    (*self).pos = ({ uint64_t __ov; if (__builtin_add_overflow((start), (len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
}
long long Lexer_lastWasNewline(Lexer self) {
    uint64_t n = (long long)((self.toks).len);
    if (n == 0) {
    { long long __ret3 = 0;
    return __ret3; }
    }
    Tok t = PlewArray_Tok_get(self.toks, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    { long long __ret4 = ({ long long __mr5; Kind __ms5 = t.kind; if (__ms5.tag == 1) { __mr5 = (1); } else { __mr5 = (0); } __mr5; });
    return __ret4; }
}
long long Lexer_lastCanEnd(Lexer self) {
    uint64_t n = (long long)((self.toks).len);
    if (n == 0) {
    { long long __ret6 = 0;
    return __ret6; }
    }
    Tok t = PlewArray_Tok_get(self.toks, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    { long long __ret7 = ({ long long __mr8; Kind __ms8 = t.kind; if (__ms8.tag == 5) { __mr8 = (1); } else if (__ms8.tag == 2) { __mr8 = (1); } else if (__ms8.tag == 3) { __mr8 = (1); } else if (__ms8.tag == 4) { __mr8 = (1); } else if (__ms8.tag == 26) { __mr8 = (1); } else if (__ms8.tag == 28) { __mr8 = (1); } else if (__ms8.tag == 30) { __mr8 = (1); } else if (__ms8.tag == 57) { __mr8 = (1); } else if (__ms8.tag == 23) { __mr8 = (1); } else if (__ms8.tag == 24) { __mr8 = (1); } else if (__ms8.tag == 16) { __mr8 = (1); } else if (__ms8.tag == 14) { __mr8 = (1); } else if (__ms8.tag == 15) { __mr8 = (1); } else { __mr8 = (0); } __mr8; });
    return __ret7; }
}
long long isDigit(unsigned char b) {
    if (b >= 48) {
    if (b <= 57) {
    { long long __ret9 = 1;
    return __ret9; }
    }
    }
    { long long __ret10 = 0;
    return __ret10; }
}
long long isAlpha(unsigned char b) {
    if (b == 95) {
    { long long __ret11 = 1;
    return __ret11; }
    }
    if (b >= 97) {
    if (b <= 122) {
    { long long __ret12 = 1;
    return __ret12; }
    }
    }
    if (b >= 65) {
    if (b <= 90) {
    { long long __ret13 = 1;
    return __ret13; }
    }
    }
    { long long __ret14 = 0;
    return __ret14; }
}
long long isAlnum(unsigned char b) {
    if (isAlpha(b)) {
    { long long __ret15 = 1;
    return __ret15; }
    }
    { long long __ret16 = isDigit(b);
    return __ret16; }
}
long long rangeEquals(PlewArray_U8 bytes, uint64_t start, uint64_t len, PlewString kw) {
    PlewArray_U8 kb = PlewArray_U8_share(({ PlewString __s = kw; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    if (len != (long long)((kb).len)) {
    { long long __ret17 = 0;
    PlewArray_U8_release(kb);
    return __ret17; }
    }
    uint64_t j = 0;
    while (j < len) {
    if (PlewArray_U8_get(bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != PlewArray_U8_get(kb, (long long)(j))) {
    { long long __ret18 = 0;
    PlewArray_U8_release(kb);
    return __ret18; }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret19 = 1;
    PlewArray_U8_release(kb);
    return __ret19; }
    PlewArray_U8_release(kb);
}
Kind identKind(PlewArray_U8 bytes, uint64_t start, uint64_t len) {
    if (rangeEquals(bytes, start, len, (PlewString){"fn", 2})) {
    { Kind __ret20 = (Kind){.tag = 6};
    return __ret20; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"struct", 6})) {
    { Kind __ret21 = (Kind){.tag = 7};
    return __ret21; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"enum", 4})) {
    { Kind __ret22 = (Kind){.tag = 8};
    return __ret22; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"match", 5})) {
    { Kind __ret23 = (Kind){.tag = 9};
    return __ret23; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"if", 2})) {
    { Kind __ret24 = (Kind){.tag = 10};
    return __ret24; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"else", 4})) {
    { Kind __ret25 = (Kind){.tag = 11};
    return __ret25; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"while", 5})) {
    { Kind __ret26 = (Kind){.tag = 12};
    return __ret26; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"for", 3})) {
    { Kind __ret27 = (Kind){.tag = 13};
    return __ret27; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"break", 5})) {
    { Kind __ret28 = (Kind){.tag = 14};
    return __ret28; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"continue", 8})) {
    { Kind __ret29 = (Kind){.tag = 15};
    return __ret29; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"return", 6})) {
    { Kind __ret30 = (Kind){.tag = 16};
    return __ret30; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"give", 4})) {
    { Kind __ret31 = (Kind){.tag = 17};
    return __ret31; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"val", 3})) {
    { Kind __ret32 = (Kind){.tag = 18};
    return __ret32; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"mut", 3})) {
    { Kind __ret33 = (Kind){.tag = 19};
    return __ret33; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"in", 2})) {
    { Kind __ret34 = (Kind){.tag = 20};
    return __ret34; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"as", 2})) {
    { Kind __ret35 = (Kind){.tag = 21};
    return __ret35; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"inout", 5})) {
    { Kind __ret36 = (Kind){.tag = 22};
    return __ret36; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"true", 4})) {
    { Kind __ret37 = (Kind){.tag = 23};
    return __ret37; }
    }
    if (rangeEquals(bytes, start, len, (PlewString){"false", 5})) {
    { Kind __ret38 = (Kind){.tag = 24};
    return __ret38; }
    }
    { Kind __ret39 = (Kind){.tag = 5};
    return __ret39; }
}
void lex(Lexer* lx) {
    while ((*lx).pos < (long long)(((*lx).bytes).len)) {
    unsigned char b = Lexer_at((*lx), 0);
    if (b == 32) {
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 9) {
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 13) {
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 10) {
    if ((*lx).depth > 0) {
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    if (Lexer_lastCanEnd((*lx))) {
    if (Lexer_lastWasNewline((*lx))) {
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    Lexer_emit(&((*lx)), (Kind){.tag = 1}, (*lx).pos, 1);
    }
    }
    else {
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    continue;
    }
    if (b == 47) {
    if (Lexer_at((*lx), 1) == 47) {
    while ((*lx).pos < (long long)(((*lx).bytes).len)) {
    if (Lexer_at((*lx), 0) == 10) {
    break;
    }
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    continue;
    }
    }
    if (isDigit(b)) {
    uint64_t start = (*lx).pos;
    uint64_t j = (*lx).pos;
    while (j < (long long)(((*lx).bytes).len)) {
    if (isDigit(PlewArray_U8_get((*lx).bytes, (long long)(j)))) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    break;
    }
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 2}, start, ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    continue;
    }
    if (isAlpha(b)) {
    uint64_t start = (*lx).pos;
    uint64_t j = (*lx).pos;
    while (j < (long long)(((*lx).bytes).len)) {
    if (isAlnum(PlewArray_U8_get((*lx).bytes, (long long)(j)))) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    break;
    }
    }
    uint64_t len = ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Kind k = identKind((*lx).bytes, start, len);
    Lexer_emit(&((*lx)), k, start, len);
    continue;
    }
    if (b == 34) {
    uint64_t start = (*lx).pos;
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < (long long)(((*lx).bytes).len)) {
    if (PlewArray_U8_get((*lx).bytes, (long long)(j)) == 92) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (PlewArray_U8_get((*lx).bytes, (long long)(j)) == 34) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    break;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 3}, start, ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    continue;
    }
    if (b == 39) {
    uint64_t start = (*lx).pos;
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < (long long)(((*lx).bytes).len)) {
    if (PlewArray_U8_get((*lx).bytes, (long long)(j)) == 92) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (PlewArray_U8_get((*lx).bytes, (long long)(j)) == 39) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    break;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 4}, start, ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    continue;
    }
    unsigned char b2 = Lexer_at((*lx), 1);
    if (b == 46) {
    if (b2 == 46) {
    unsigned char b3 = Lexer_at((*lx), 2);
    if (b3 == 60) {
    Lexer_emit(&((*lx)), (Kind){.tag = 68}, (*lx).pos, 3);
    continue;
    }
    if (b3 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 69}, (*lx).pos, 3);
    continue;
    }
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 33}, (*lx).pos, 1);
    continue;
    }
    if (b == 61) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 35}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit(&((*lx)), (Kind){.tag = 56}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 34}, (*lx).pos, 1);
    continue;
    }
    if (b == 33) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 36}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 48}, (*lx).pos, 1);
    continue;
    }
    if (b == 60) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 38}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 60) {
    unsigned char b3 = Lexer_at((*lx), 2);
    if (b3 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 66}, (*lx).pos, 3);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 52}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 37}, (*lx).pos, 1);
    continue;
    }
    if (b == 62) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 40}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    unsigned char b3 = Lexer_at((*lx), 2);
    if (b3 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 67}, (*lx).pos, 3);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 53}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 39}, (*lx).pos, 1);
    continue;
    }
    if (b == 43) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 58}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 41}, (*lx).pos, 1);
    continue;
    }
    if (b == 45) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 59}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit(&((*lx)), (Kind){.tag = 55}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 42}, (*lx).pos, 1);
    continue;
    }
    if (b == 42) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 60}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 43}, (*lx).pos, 1);
    continue;
    }
    if (b == 47) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 61}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit(&((*lx)), (Kind){.tag = 57}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 44}, (*lx).pos, 1);
    continue;
    }
    if (b == 37) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 62}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 45}, (*lx).pos, 1);
    continue;
    }
    if (b == 38) {
    if (b2 == 38) {
    Lexer_emit(&((*lx)), (Kind){.tag = 46}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 63}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 49}, (*lx).pos, 1);
    continue;
    }
    if (b == 124) {
    if (b2 == 124) {
    Lexer_emit(&((*lx)), (Kind){.tag = 47}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 64}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 50}, (*lx).pos, 1);
    continue;
    }
    if (b == 94) {
    if (b2 == 61) {
    Lexer_emit(&((*lx)), (Kind){.tag = 65}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 51}, (*lx).pos, 1);
    continue;
    }
    if (b == 126) {
    Lexer_emit(&((*lx)), (Kind){.tag = 54}, (*lx).pos, 1);
    continue;
    }
    if (b == 63) {
    if (b2 == 63) {
    Lexer_emit(&((*lx)), (Kind){.tag = 70}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 71}, (*lx).pos, 1);
    continue;
    }
    if (b == 40) {
    Lexer_emit(&((*lx)), (Kind){.tag = 25}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_add_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 41) {
    Lexer_emit(&((*lx)), (Kind){.tag = 26}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_sub_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 91) {
    Lexer_emit(&((*lx)), (Kind){.tag = 27}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_add_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 93) {
    Lexer_emit(&((*lx)), (Kind){.tag = 28}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_sub_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 123) {
    Lexer_emit(&((*lx)), (Kind){.tag = 29}, (*lx).pos, 1);
    continue;
    }
    if (b == 125) {
    Lexer_emit(&((*lx)), (Kind){.tag = 30}, (*lx).pos, 1);
    continue;
    }
    if (b == 44) {
    Lexer_emit(&((*lx)), (Kind){.tag = 31}, (*lx).pos, 1);
    continue;
    }
    if (b == 58) {
    Lexer_emit(&((*lx)), (Kind){.tag = 32}, (*lx).pos, 1);
    continue;
    }
    Lexer_emit(&((*lx)), (Kind){.tag = 71}, (*lx).pos, 1);
    }
    PlewArray_Tok_push(&((*lx).toks), (Tok){.kind = (Kind){.tag = 0}, .start = (*lx).pos, .len = 0});
}
int64_t kindCode(Kind k) {
    { int64_t __ret40 = ({ long long __mr41; Kind __ms41 = k; if (__ms41.tag == 0) { __mr41 = (0); } else if (__ms41.tag == 1) { __mr41 = (1); } else if (__ms41.tag == 2) { __mr41 = (2); } else if (__ms41.tag == 3) { __mr41 = (3); } else if (__ms41.tag == 4) { __mr41 = (5); } else if (__ms41.tag == 5) { __mr41 = (4); } else if (__ms41.tag == 6) { __mr41 = (10); } else if (__ms41.tag == 7) { __mr41 = (11); } else if (__ms41.tag == 8) { __mr41 = (12); } else if (__ms41.tag == 9) { __mr41 = (13); } else if (__ms41.tag == 10) { __mr41 = (14); } else if (__ms41.tag == 11) { __mr41 = (15); } else if (__ms41.tag == 12) { __mr41 = (16); } else if (__ms41.tag == 13) { __mr41 = (17); } else if (__ms41.tag == 14) { __mr41 = (18); } else if (__ms41.tag == 15) { __mr41 = (19); } else if (__ms41.tag == 16) { __mr41 = (20); } else if (__ms41.tag == 17) { __mr41 = (21); } else if (__ms41.tag == 18) { __mr41 = (22); } else if (__ms41.tag == 19) { __mr41 = (23); } else if (__ms41.tag == 20) { __mr41 = (24); } else if (__ms41.tag == 21) { __mr41 = (25); } else if (__ms41.tag == 22) { __mr41 = (26); } else if (__ms41.tag == 23) { __mr41 = (27); } else if (__ms41.tag == 24) { __mr41 = (28); } else if (__ms41.tag == 25) { __mr41 = (40); } else if (__ms41.tag == 26) { __mr41 = (41); } else if (__ms41.tag == 27) { __mr41 = (42); } else if (__ms41.tag == 28) { __mr41 = (43); } else if (__ms41.tag == 29) { __mr41 = (44); } else if (__ms41.tag == 30) { __mr41 = (45); } else if (__ms41.tag == 31) { __mr41 = (46); } else if (__ms41.tag == 32) { __mr41 = (47); } else if (__ms41.tag == 33) { __mr41 = (48); } else if (__ms41.tag == 34) { __mr41 = (49); } else if (__ms41.tag == 35) { __mr41 = (50); } else if (__ms41.tag == 36) { __mr41 = (51); } else if (__ms41.tag == 37) { __mr41 = (52); } else if (__ms41.tag == 38) { __mr41 = (53); } else if (__ms41.tag == 39) { __mr41 = (54); } else if (__ms41.tag == 40) { __mr41 = (55); } else if (__ms41.tag == 41) { __mr41 = (56); } else if (__ms41.tag == 42) { __mr41 = (57); } else if (__ms41.tag == 43) { __mr41 = (58); } else if (__ms41.tag == 44) { __mr41 = (59); } else if (__ms41.tag == 45) { __mr41 = (60); } else if (__ms41.tag == 46) { __mr41 = (61); } else if (__ms41.tag == 47) { __mr41 = (62); } else if (__ms41.tag == 48) { __mr41 = (63); } else if (__ms41.tag == 55) { __mr41 = (64); } else if (__ms41.tag == 56) { __mr41 = (65); } else if (__ms41.tag == 57) { __mr41 = (66); } else if (__ms41.tag == 58) { __mr41 = (67); } else if (__ms41.tag == 59) { __mr41 = (68); } else if (__ms41.tag == 60) { __mr41 = (69); } else if (__ms41.tag == 61) { __mr41 = (70); } else if (__ms41.tag == 62) { __mr41 = (71); } else if (__ms41.tag == 68) { __mr41 = (72); } else if (__ms41.tag == 69) { __mr41 = (73); } else if (__ms41.tag == 49) { __mr41 = (74); } else if (__ms41.tag == 50) { __mr41 = (75); } else if (__ms41.tag == 51) { __mr41 = (76); } else if (__ms41.tag == 52) { __mr41 = (77); } else if (__ms41.tag == 53) { __mr41 = (78); } else if (__ms41.tag == 54) { __mr41 = (79); } else if (__ms41.tag == 63) { __mr41 = (80); } else if (__ms41.tag == 64) { __mr41 = (81); } else if (__ms41.tag == 65) { __mr41 = (82); } else if (__ms41.tag == 66) { __mr41 = (83); } else if (__ms41.tag == 67) { __mr41 = (84); } else if (__ms41.tag == 70) { __mr41 = (85); } else if (__ms41.tag == 71) { __mr41 = (99); } else { __builtin_unreachable(); } __mr41; });
    return __ret40; }
}
Kind Comp_curKind(Comp* self) {
    { Kind __ret42 = PlewArray_Tok_get((*self).toks, (long long)((*self).pos)).kind;
    return __ret42; }
}
Tok Comp_cur(Comp* self) {
    { Tok __ret43 = PlewArray_Tok_get((*self).toks, (long long)((*self).pos));
    return __ret43; }
}
Kind Comp_peekKind(Comp* self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)(((*self).toks).len)) {
    { Kind __ret44 = PlewArray_Tok_get((*self).toks, (long long)(i)).kind;
    return __ret44; }
    }
    { Kind __ret45 = (Kind){.tag = 0};
    return __ret45; }
}
void Comp_advance(Comp* self) {
    (*self).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
}
void Comp_skipNewlines(Comp* self) {
    while (1) {
    {
    Kind _m46 = Comp_curKind(&((*self)));
    if (_m46.tag == 1) {
    Comp_advance(&((*self)));
    }
    else {
    break;
    }
    }
    }
}
long long Comp_identIs(Comp* self, PlewString kw) {
    Tok t = PlewArray_Tok_get((*self).toks, (long long)((*self).pos));
    { long long __ret47 = rangeEquals((*self).bytes, t.start, t.len, kw);
    return __ret47; }
}
uint64_t Comp_pushExpr(Comp* self, Expr e) {
    uint64_t id = (long long)(((*self).exprs).len);
    PlewArray_Expr_push(&((*self).exprs), e);
    { uint64_t __ret48 = id;
    return __ret48; }
}
uint64_t Comp_pushStmt(Comp* self, Stmt s) {
    uint64_t id = (long long)(((*self).stmts).len);
    PlewArray_Stmt_push(&((*self).stmts), s);
    { uint64_t __ret49 = id;
    return __ret49; }
}
uint64_t Comp_pushType(Comp* self, TypeRef t) {
    uint64_t id = (long long)(((*self).types).len);
    PlewArray_TypeRef_push(&((*self).types), t);
    { uint64_t __ret50 = id;
    return __ret50; }
}
int64_t Comp_tokenValue(Comp* self, Tok t) {
    int64_t v = 0;
    uint64_t j = 0;
    while (j < t.len) {
    unsigned char b = PlewArray_U8_get((*self).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((t.start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    v = ({ int64_t __ov; if (__builtin_add_overflow((({ int64_t __ov; if (__builtin_mul_overflow((v), (10), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), (({ int64_t __ov; if (__builtin_sub_overflow((((int64_t)(b))), (48), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { int64_t __ret51 = v;
    return __ret51; }
}
int64_t binPrec(Kind k) {
    { int64_t __ret52 = ({ long long __mr53; Kind __ms53 = k; if (__ms53.tag == 47) { __mr53 = (1); } else if (__ms53.tag == 46) { __mr53 = (2); } else if (__ms53.tag == 35) { __mr53 = (3); } else if (__ms53.tag == 36) { __mr53 = (3); } else if (__ms53.tag == 37) { __mr53 = (3); } else if (__ms53.tag == 38) { __mr53 = (3); } else if (__ms53.tag == 39) { __mr53 = (3); } else if (__ms53.tag == 40) { __mr53 = (3); } else if (__ms53.tag == 70) { __mr53 = (4); } else if (__ms53.tag == 50) { __mr53 = (5); } else if (__ms53.tag == 51) { __mr53 = (6); } else if (__ms53.tag == 49) { __mr53 = (7); } else if (__ms53.tag == 52) { __mr53 = (8); } else if (__ms53.tag == 53) { __mr53 = (8); } else if (__ms53.tag == 41) { __mr53 = (9); } else if (__ms53.tag == 42) { __mr53 = (9); } else if (__ms53.tag == 43) { __mr53 = (10); } else if (__ms53.tag == 44) { __mr53 = (10); } else if (__ms53.tag == 45) { __mr53 = (10); } else { __mr53 = (0); } __mr53; });
    return __ret52; }
}
int64_t charValue(Comp* c, Tok t) {
    uint64_t contentLen = ({ uint64_t __ov; if (__builtin_sub_overflow((t.len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (contentLen == 0) {
    compileErrorAt(lineOf(&((*c)), t.start), (PlewString){"empty character literal", 23});
    }
    uint64_t p = ({ uint64_t __ov; if (__builtin_add_overflow((t.start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    unsigned char b0 = PlewArray_U8_get((*c).bytes, (long long)(p));
    if (b0 == 92) {
    if (contentLen != 2) {
    compileErrorAt(lineOf(&((*c)), t.start), (PlewString){"character literal must be a single scalar", 41});
    }
    unsigned char e = PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    if (e == 110) {
    { int64_t __ret54 = 10;
    return __ret54; }
    }
    if (e == 116) {
    { int64_t __ret55 = 9;
    return __ret55; }
    }
    if (e == 114) {
    { int64_t __ret56 = 13;
    return __ret56; }
    }
    if (e == 48) {
    { int64_t __ret57 = 0;
    return __ret57; }
    }
    { int64_t __ret58 = e;
    return __ret58; }
    }
    uint64_t consumed = 1;
    int64_t value = 0;
    if (b0 < 128) {
    consumed = 1;
    value = b0;
    }
    else {
    if (b0 < 224) {
    consumed = 2;
    value = (((b0 & 31) << 6) | (PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63));
    }
    else {
    if (b0 < 240) {
    consumed = 3;
    value = ((((b0 & 15) << 12) | ((PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63) << 6)) | (PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63));
    }
    else {
    consumed = 4;
    value = (((((b0 & 7) << 18) | ((PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63) << 12)) | ((PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63) << 6)) | (PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (3), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63));
    }
    }
    }
    if (contentLen != consumed) {
    compileErrorAt(lineOf(&((*c)), t.start), (PlewString){"multi-scalar character literal (Grapheme) is not yet supported", 62});
    }
    { int64_t __ret59 = value;
    return __ret59; }
}
uint64_t parsePrimary(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m60 = k;
    if (_m60.tag == 2) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    int64_t v = Comp_tokenValue(&((*c)), t);
    uint64_t sStart = 0;
    uint64_t sLen = 0;
    {
    Kind _m61 = Comp_curKind(&((*c)));
    if (_m61.tag == 5) {
    Tok st = Comp_cur(&((*c)));
    if (st.start == ({ uint64_t __ov; if (__builtin_add_overflow((t.start), (t.len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })) {
    if (isIntType(&((*c)), st.start, st.len)) {
    sStart = st.start;
    sLen = st.len;
    Comp_advance(&((*c)));
    }
    }
    }
    else {
    }
    }
    { uint64_t __ret62 = Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = sStart, .tyLen = sLen}});
    return __ret62; }
    }
    else if (_m60.tag == 4) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    int64_t v = charValue(&((*c)), t);
    { uint64_t __ret63 = Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    return __ret63; }
    }
    else if (_m60.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    {
    Kind _m64 = Comp_peekKind(&((*c)), 1);
    if (_m64.tag == 25) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Arg args = parseCallArgs(&((*c)));
    { uint64_t __ret65 = Comp_pushExpr(&((*c)), (Expr){.tag = 4, .data.Call = {.nameStart = t.start, .nameLen = t.len, .args = PlewArray_Arg_share(args)}});
    PlewArray_Arg_release(args);
    return __ret65; }
    PlewArray_Arg_release(args);
    }
    else {
    Comp_advance(&((*c)));
    { uint64_t __ret66 = Comp_pushExpr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = t.start, .len = t.len}});
    return __ret66; }
    }
    }
    }
    else if (_m60.tag == 23) {
    Tok tt = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret67 = Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 1, .offset = tt.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret67; }
    }
    else if (_m60.tag == 24) {
    Tok tf = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret68 = Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = tf.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret68; }
    }
    else if (_m60.tag == 25) {
    Comp_advance(&((*c)));
    uint64_t inner = parseExpr(&((*c)));
    {
    Kind _m69 = Comp_curKind(&((*c)));
    if (_m69.tag == 26) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    { uint64_t __ret70 = inner;
    return __ret70; }
    }
    else if (_m60.tag == 6) {
    Comp_advance(&((*c)));
    PlewArray_Param params = parseParamList(&((*c)));
    long long hasRet = 0;
    uint64_t retStart = 0;
    uint64_t retLen = 0;
    long long retIsArray = 0;
    uint64_t retRef = 0;
    {
    Kind _m71 = Comp_curKind(&((*c)));
    if (_m71.tag == 55) {
    Comp_advance(&((*c)));
    hasRet = 1;
    PType rty = parseTypeTok(&((*c)));
    retStart = rty.start;
    retLen = rty.len;
    retIsArray = rty.isArray;
    retRef = rty.ref;
    recordArrayElem(&((*c)), rty);
    }
    else {
    }
    }
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock(&((*c)));
    { uint64_t __ret72 = Comp_pushExpr(&((*c)), (Expr){.tag = 17, .data.Closure = {.params = PlewArray_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body}});
    PlewArray_Param_release(params);
    return __ret72; }
    PlewArray_Param_release(params);
    }
    else if (_m60.tag == 37) {
    { uint64_t __ret73 = parseMake(&((*c)));
    return __ret73; }
    }
    else if (_m60.tag == 9) {
    { uint64_t __ret74 = parseMatchExpr(&((*c)));
    return __ret74; }
    }
    else if (_m60.tag == 10) {
    { uint64_t __ret75 = parseIfExpr(&((*c)));
    return __ret75; }
    }
    else if (_m60.tag == 3) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret76 = Comp_pushExpr(&((*c)), (Expr){.tag = 7, .data.Str = {.start = t.start, .len = t.len}});
    return __ret76; }
    }
    else if (_m60.tag == 27) {
    Comp_advance(&((*c)));
    PlewArray_U64 elems = PlewArray_U64_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m77 = Comp_curKind(&((*c)));
    if (_m77.tag == 28) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m77.tag == 0) {
    break;
    }
    else {
    uint64_t e = parseExpr(&((*c)));
    PlewArray_U64_push(&(elems), e);
    {
    Kind _m78 = Comp_curKind(&((*c)));
    if (_m78.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    { uint64_t __ret79 = Comp_pushExpr(&((*c)), (Expr){.tag = 8, .data.Array = {.elems = PlewArray_U64_share(elems)}});
    PlewArray_U64_release(elems);
    return __ret79; }
    PlewArray_U64_release(elems);
    }
    else {
    Tok te = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret80 = Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = te.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    return __ret80; }
    }
    }
}
uint64_t parseUnary(Comp* c) {
    if (Comp_identIs(&((*c)), (PlewString){"try", 3})) {
    Comp_advance(&((*c)));
    uint64_t inner = parsePostfix(&((*c)));
    { uint64_t __ret81 = Comp_pushExpr(&((*c)), (Expr){.tag = 15, .data.Try = {.expr = inner}});
    return __ret81; }
    }
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m82 = k;
    if (_m82.tag == 42) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary(&((*c)));
    { uint64_t __ret83 = Comp_pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 57, .operand = o}});
    return __ret83; }
    }
    else if (_m82.tag == 48) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary(&((*c)));
    { uint64_t __ret84 = Comp_pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 63, .operand = o}});
    return __ret84; }
    }
    else if (_m82.tag == 54) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary(&((*c)));
    { uint64_t __ret85 = Comp_pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 79, .operand = o}});
    return __ret85; }
    }
    else {
    { uint64_t __ret86 = parsePostfix(&((*c)));
    return __ret86; }
    }
    }
}
uint64_t parsePostfix(Comp* c) {
    uint64_t e = parsePrimary(&((*c)));
    while (1) {
    {
    Kind _m87 = Comp_curKind(&((*c)));
    if (_m87.tag == 33) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m88 = Comp_curKind(&((*c)));
    if (_m88.tag == 25) {
    Comp_advance(&((*c)));
    PlewArray_Arg args = parseCallArgs(&((*c)));
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 10, .data.Method = {.recv = e, .nameStart = nameTok.start, .nameLen = nameTok.len, .args = PlewArray_Arg_share(args)}});
    PlewArray_Arg_release(args);
    }
    else {
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    }
    }
    else if (_m87.tag == 27) {
    Comp_advance(&((*c)));
    uint64_t idx = parseExpr(&((*c)));
    {
    Kind _m89 = Comp_curKind(&((*c)));
    if (_m89.tag == 28) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 9, .data.Index = {.base = e, .index = idx}});
    }
    else if (_m87.tag == 55) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 16, .data.Arrow = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    else if (_m87.tag == 21) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 11, .data.Cast = {.operand = e, .tyStart = ty.start, .tyLen = ty.len, .ty = ty.ref}});
    }
    else {
    break;
    }
    }
    }
    { uint64_t __ret90 = e;
    return __ret90; }
}
uint64_t parseMake(Comp* c) {
    Comp_advance(&((*c)));
    Tok typeTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyRef = 0;
    {
    Kind _m91 = Comp_curKind(&((*c)));
    if (_m91.tag == 27) {
    Comp_advance(&((*c)));
    PlewArray_U64 targs = PlewArray_U64_new();
    long long first = 1;
    while (1) {
    {
    Kind _m92 = Comp_curKind(&((*c)));
    if (_m92.tag == 28) {
    break;
    }
    else if (_m92.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m93 = Comp_curKind(&((*c)));
    if (_m93.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    first = 0;
    PType arg = parseTypeTok(&((*c)));
    PlewArray_U64_push(&(targs), arg.ref);
    }
    {
    Kind _m94 = Comp_curKind(&((*c)));
    if (_m94.tag == 28) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    tyRef = Comp_pushType(&((*c)), (TypeRef){.nameStart = typeTok.start, .nameLen = typeTok.len, .args = PlewArray_U64_share(targs)});
    PlewArray_U64_release(targs);
    }
    else {
    }
    }
    uint64_t variantStart = 0;
    uint64_t variantLen = 0;
    long long isEnum = 0;
    {
    Kind _m95 = Comp_curKind(&((*c)));
    if (_m95.tag == 33) {
    Comp_advance(&((*c)));
    Tok vTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    variantStart = vTok.start;
    variantLen = vTok.len;
    isEnum = 1;
    }
    else {
    }
    }
    PlewArray_MakeField fields = PlewArray_MakeField_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m96 = k;
    if (_m96.tag == 57) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m96.tag == 39) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m96.tag == 0) {
    break;
    }
    else if (_m96.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m97 = Comp_curKind(&((*c)));
    if (_m97.tag == 34) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t v = parseExpr(&((*c)));
    PlewArray_MakeField_push(&(fields), (MakeField){.nameStart = fTok.start, .nameLen = fTok.len, .value = v});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    { uint64_t __ret98 = Comp_pushExpr(&((*c)), (Expr){.tag = 6, .data.Make = {.typeStart = typeTok.start, .typeLen = typeTok.len, .variantStart = variantStart, .variantLen = variantLen, .isEnum = isEnum, .ty = tyRef, .fields = PlewArray_MakeField_share(fields)}});
    PlewArray_MakeField_release(fields);
    return __ret98; }
    PlewArray_MakeField_release(fields);
}
uint64_t parseBin(Comp* c, int64_t minPrec) {
    uint64_t left = parseUnary(&((*c)));
    while (1) {
    Kind k = Comp_curKind(&((*c)));
    int64_t prec = binPrec(k);
    if (prec == 0) {
    break;
    }
    if (prec < minPrec) {
    break;
    }
    {
    Kind _m99 = k;
    if (_m99.tag == 70) {
    Comp_advance(&((*c)));
    uint64_t rhs = parseBin(&((*c)), prec);
    left = Comp_pushExpr(&((*c)), (Expr){.tag = 14, .data.Coalesce = {.opt = left, .deflt = rhs}});
    }
    else {
    int64_t op = kindCode(k);
    Comp_advance(&((*c)));
    uint64_t right = parseBin(&((*c)), ({ int64_t __ov; if (__builtin_add_overflow((prec), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    left = Comp_pushExpr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = op, .lhs = left, .rhs = right}});
    }
    }
    }
    { uint64_t __ret100 = left;
    return __ret100; }
}
uint64_t parseExpr(Comp* c) {
    { uint64_t __ret101 = parseBin(&((*c)), 1);
    return __ret101; }
}
PlewArray_Arg parseCallArgs(Comp* c) {
    PlewArray_Arg args = PlewArray_Arg_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m102 = k;
    if (_m102.tag == 26) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m102.tag == 0) {
    break;
    }
    else {
    uint64_t labelStart = 0;
    uint64_t labelLen = 0;
    long long hasLabel = 0;
    {
    Kind _m103 = Comp_curKind(&((*c)));
    if (_m103.tag == 5) {
    {
    Kind _m104 = Comp_peekKind(&((*c)), 1);
    if (_m104.tag == 32) {
    Tok lt = Comp_cur(&((*c)));
    labelStart = lt.start;
    labelLen = lt.len;
    hasLabel = 1;
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    }
    }
    long long isInout = 0;
    {
    Kind _m105 = Comp_curKind(&((*c)));
    if (_m105.tag == 22) {
    Comp_advance(&((*c)));
    isInout = 1;
    }
    else {
    }
    }
    uint64_t e = parseExpr(&((*c)));
    PlewArray_Arg_push(&(args), (Arg){.expr = e, .isInout = isInout, .labelStart = labelStart, .labelLen = labelLen, .hasLabel = hasLabel});
    {
    Kind _m106 = Comp_curKind(&((*c)));
    if (_m106.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    { PlewArray_Arg __ret107 = PlewArray_Arg_share(args);
    PlewArray_Arg_release(args);
    return __ret107; }
    PlewArray_Arg_release(args);
}
long long isAssignOp(Kind k) {
    {
    Kind _m108 = k;
    if (_m108.tag == 34) {
    { long long __ret109 = 1;
    return __ret109; }
    }
    else if (_m108.tag == 58) {
    { long long __ret110 = 1;
    return __ret110; }
    }
    else if (_m108.tag == 59) {
    { long long __ret111 = 1;
    return __ret111; }
    }
    else if (_m108.tag == 60) {
    { long long __ret112 = 1;
    return __ret112; }
    }
    else if (_m108.tag == 61) {
    { long long __ret113 = 1;
    return __ret113; }
    }
    else if (_m108.tag == 62) {
    { long long __ret114 = 1;
    return __ret114; }
    }
    else if (_m108.tag == 63) {
    { long long __ret115 = 1;
    return __ret115; }
    }
    else if (_m108.tag == 64) {
    { long long __ret116 = 1;
    return __ret116; }
    }
    else if (_m108.tag == 65) {
    { long long __ret117 = 1;
    return __ret117; }
    }
    else if (_m108.tag == 66) {
    { long long __ret118 = 1;
    return __ret118; }
    }
    else if (_m108.tag == 67) {
    { long long __ret119 = 1;
    return __ret119; }
    }
    else {
    { long long __ret120 = 0;
    return __ret120; }
    }
    }
}
PType parseTypeTok(Comp* c) {
    Tok head = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m121 = head.kind;
    if (_m121.tag == 6) {
    PlewArray_U64 fargs = PlewArray_U64_new();
    uint64_t retRef = 0;
    {
    Kind _m122 = Comp_curKind(&((*c)));
    if (_m122.tag == 25) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    {
    Kind _m123 = Comp_curKind(&((*c)));
    if (_m123.tag == 26) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m123.tag == 0) {
    break;
    }
    else if (_m123.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    {
    Kind _m124 = Comp_curKind(&((*c)));
    if (_m124.tag == 5) {
    if ((Comp_peekKind(&((*c)), 1)).tag == 32) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    }
    }
    else {
    }
    }
    {
    Kind _m125 = Comp_curKind(&((*c)));
    if (_m125.tag == 22) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PType pty = parseTypeTok(&((*c)));
    PlewArray_U64_push(&(fargs), pty.ref);
    }
    }
    }
    {
    Kind _m126 = Comp_curKind(&((*c)));
    if (_m126.tag == 55) {
    Comp_advance(&((*c)));
    PType rty = parseTypeTok(&((*c)));
    retRef = rty.ref;
    }
    else {
    }
    }
    PlewArray_U64 allArgs = PlewArray_U64_new();
    PlewArray_U64_push(&(allArgs), retRef);
    uint64_t fk = 0;
    while (fk < (long long)((fargs).len)) {
    PlewArray_U64_push(&(allArgs), PlewArray_U64_get(fargs, (long long)(fk)));
    fk = ({ uint64_t __ov; if (__builtin_add_overflow((fk), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t fref = Comp_pushType(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = PlewArray_U64_share(allArgs)});
    { PType __ret127 = (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = fref};
    PlewArray_U64_release(allArgs);
    PlewArray_U64_release(fargs);
    return __ret127; }
    PlewArray_U64_release(allArgs);
    PlewArray_U64_release(fargs);
    }
    else {
    }
    }
    PlewArray_U64 args = PlewArray_U64_new();
    uint64_t elemStart = head.start;
    uint64_t elemLen = head.len;
    long long bracketed = 0;
    {
    Kind _m128 = Comp_curKind(&((*c)));
    if (_m128.tag == 27) {
    bracketed = 1;
    Comp_advance(&((*c)));
    long long first = 1;
    while (1) {
    {
    Kind _m129 = Comp_curKind(&((*c)));
    if (_m129.tag == 28) {
    break;
    }
    else if (_m129.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m130 = Comp_curKind(&((*c)));
    if (_m130.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    first = 0;
    PType arg = parseTypeTok(&((*c)));
    PlewArray_U64_push(&(args), arg.ref);
    if ((long long)((args).len) == 1) {
    elemStart = arg.start;
    elemLen = arg.len;
    }
    }
    {
    Kind _m131 = Comp_curKind(&((*c)));
    if (_m131.tag == 28) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    }
    }
    uint64_t ref = Comp_pushType(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = PlewArray_U64_share(args)});
    if (bracketed) {
    if (rangeEquals((*c).bytes, head.start, head.len, (PlewString){"Array", 5})) {
    { PType __ret132 = (PType){.start = elemStart, .len = elemLen, .isArray = 1, .ref = ref};
    PlewArray_U64_release(args);
    return __ret132; }
    }
    }
    { PType __ret133 = (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = ref};
    PlewArray_U64_release(args);
    return __ret133; }
    PlewArray_U64_release(args);
}
PlewArray_Bind parseTypeParams(Comp* c) {
    PlewArray_Bind ps = PlewArray_Bind_new();
    {
    Kind _m134 = Comp_curKind(&((*c)));
    if (_m134.tag == 27) {
    Comp_advance(&((*c)));
    while (1) {
    {
    Kind _m135 = Comp_curKind(&((*c)));
    if (_m135.tag == 28) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m135.tag == 0) {
    break;
    }
    else if (_m135.tag == 31) {
    Comp_advance(&((*c)));
    }
    else if (_m135.tag == 5) {
    uint64_t nameStart = 0;
    uint64_t nameLen = 0;
    while (1) {
    {
    Kind _m136 = Comp_curKind(&((*c)));
    if (_m136.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    nameStart = t.start;
    nameLen = t.len;
    Comp_advance(&((*c)));
    }
    else {
    break;
    }
    }
    }
    PlewArray_Bind_push(&(ps), (Bind){.nameStart = nameStart, .nameLen = nameLen, .fieldStart = nameStart, .fieldLen = nameLen});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
    else {
    }
    }
    { PlewArray_Bind __ret137 = PlewArray_Bind_share(ps);
    PlewArray_Bind_release(ps);
    return __ret137; }
    PlewArray_Bind_release(ps);
}
void recordArrayElem(Comp* c, PType ty) {
    if (ty.isArray) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind e = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, ty.start, ty.len)) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Bind_push(&((*c).arrayElems), (Bind){.nameStart = ty.start, .nameLen = ty.len, .fieldStart = ty.start, .fieldLen = ty.len});
    }
}
uint64_t parseLet(Comp* c, long long mutable) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyStart = 0;
    uint64_t tyLen = 0;
    long long tyIsArray = 0;
    uint64_t tyRef = 0;
    {
    Kind _m138 = Comp_curKind(&((*c)));
    if (_m138.tag == 32) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    tyRef = ty.ref;
    recordArrayElem(&((*c)), ty);
    }
    else {
    }
    }
    {
    Kind _m139 = Comp_curKind(&((*c)));
    if (_m139.tag == 34) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t init = parseExpr(&((*c)));
    { uint64_t __ret140 = Comp_pushStmt(&((*c)), (Stmt){.tag = 0, .data.Let = {.mutable = mutable, .nameStart = nameTok.start, .nameLen = nameTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .init = init}});
    return __ret140; }
}
uint64_t parsePrint(Comp* c) {
    Tok kw = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    uint64_t e = parseExpr(&((*c)));
    {
    Kind _m141 = Comp_curKind(&((*c)));
    if (_m141.tag == 26) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    { uint64_t __ret142 = Comp_pushStmt(&((*c)), (Stmt){.tag = 2, .data.Print = {.expr = e, .offset = kw.start}});
    return __ret142; }
}
uint64_t parsePanic(Comp* c) {
    Tok kw = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t msg = parseExpr(&((*c)));
    { uint64_t __ret143 = Comp_pushStmt(&((*c)), (Stmt){.tag = 9, .data.Panic = {.msg = msg, .offset = kw.start}});
    return __ret143; }
}
uint64_t parseReturn(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m144 = Comp_curKind(&((*c)));
    if (_m144.tag == 1) {
    { uint64_t __ret145 = Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret145; }
    }
    else if (_m144.tag == 30) {
    { uint64_t __ret146 = Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret146; }
    }
    else if (_m144.tag == 0) {
    { uint64_t __ret147 = Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret147; }
    }
    else {
    uint64_t e = parseExpr(&((*c)));
    { uint64_t __ret148 = Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = e, .hasValue = 1}});
    return __ret148; }
    }
    }
}
uint64_t parseIf(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr(&((*c)));
    uint64_t thenBlk = parseBlock(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m149 = Comp_curKind(&((*c)));
    if (_m149.tag == 11) {
    Comp_advance(&((*c)));
    {
    Kind _m150 = Comp_curKind(&((*c)));
    if (_m150.tag == 10) {
    uint64_t nested = parseIf(&((*c)));
    PlewArray_U64 one = PlewArray_U64_new();
    PlewArray_U64_push(&(one), nested);
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(one)});
    { uint64_t __ret151 = Comp_pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId, .hasElse = 1}});
    PlewArray_U64_release(one);
    return __ret151; }
    PlewArray_U64_release(one);
    }
    else {
    uint64_t elseBlk = parseBlock(&((*c)));
    { uint64_t __ret152 = Comp_pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk, .hasElse = 1}});
    return __ret152; }
    }
    }
    }
    else {
    { uint64_t __ret153 = Comp_pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = 0, .hasElse = 0}});
    return __ret153; }
    }
    }
}
uint64_t parseIfExpr(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr(&((*c)));
    uint64_t thenBlk = parseBlock(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m154 = Comp_curKind(&((*c)));
    if (_m154.tag == 11) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m155 = Comp_curKind(&((*c)));
    if (_m155.tag == 10) {
    uint64_t nested = parseIfExpr(&((*c)));
    PlewArray_U64 one = PlewArray_U64_new();
    PlewArray_U64_push(&(one), Comp_pushStmt(&((*c)), (Stmt){.tag = 10, .data.Give = {.value = nested}}));
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(one)});
    { uint64_t __ret156 = Comp_pushExpr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId}});
    PlewArray_U64_release(one);
    return __ret156; }
    PlewArray_U64_release(one);
    }
    else {
    uint64_t elseBlk = parseBlock(&((*c)));
    { uint64_t __ret157 = Comp_pushExpr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk}});
    return __ret157; }
    }
    }
}
uint64_t parseGive(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t v = parseExpr(&((*c)));
    { uint64_t __ret158 = Comp_pushStmt(&((*c)), (Stmt){.tag = 10, .data.Give = {.value = v}});
    return __ret158; }
}
uint64_t parseWhile(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr(&((*c)));
    uint64_t body = parseBlock(&((*c)));
    { uint64_t __ret159 = Comp_pushStmt(&((*c)), (Stmt){.tag = 6, .data.While = {.cond = cond, .body = body}});
    return __ret159; }
}
uint64_t parseFor(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m160 = Comp_curKind(&((*c)));
    if (_m160.tag == 18) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m161 = Comp_curKind(&((*c)));
    if (_m161.tag == 20) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t lo = parseExpr(&((*c)));
    long long isRange = 0;
    long long inclusive = 0;
    uint64_t hi = 0;
    {
    Kind _m162 = Comp_curKind(&((*c)));
    if (_m162.tag == 68) {
    Comp_advance(&((*c)));
    isRange = 1;
    hi = parseExpr(&((*c)));
    }
    else if (_m162.tag == 69) {
    Comp_advance(&((*c)));
    isRange = 1;
    inclusive = 1;
    hi = parseExpr(&((*c)));
    }
    else {
    }
    }
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock(&((*c)));
    { uint64_t __ret163 = Comp_pushStmt(&((*c)), (Stmt){.tag = 7, .data.For = {.varStart = nameTok.start, .varLen = nameTok.len, .isRange = isRange, .inclusive = inclusive, .iter = lo, .rangeHi = hi, .body = body}});
    return __ret163; }
}
uint64_t parseExprOrAssign(Comp* c) {
    uint64_t lhs = parseExpr(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    if (isAssignOp(k)) {
    int64_t op = kindCode(k);
    Comp_advance(&((*c)));
    uint64_t rhs = parseExpr(&((*c)));
    { uint64_t __ret164 = Comp_pushStmt(&((*c)), (Stmt){.tag = 1, .data.Assign = {.op = op, .target = lhs, .value = rhs}});
    return __ret164; }
    }
    { uint64_t __ret165 = Comp_pushStmt(&((*c)), (Stmt){.tag = 3, .data.ExprStmt = {.expr = lhs}});
    return __ret165; }
}
PatInfo parsePattern(Comp* c) {
    Tok firstTok = Comp_cur(&((*c)));
    long long isWildcard = 0;
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    uint64_t variantStart = 0;
    uint64_t variantLen = 0;
    PlewArray_Bind binds = PlewArray_Bind_new();
    if (rangeEquals((*c).bytes, firstTok.start, firstTok.len, (PlewString){"_", 1})) {
    isWildcard = 1;
    Comp_advance(&((*c)));
    }
    else {
    enumStart = firstTok.start;
    enumLen = firstTok.len;
    Comp_advance(&((*c)));
    {
    Kind _m166 = Comp_curKind(&((*c)));
    if (_m166.tag == 33) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Tok vTok = Comp_cur(&((*c)));
    variantStart = vTok.start;
    variantLen = vTok.len;
    Comp_advance(&((*c)));
    {
    Kind _m167 = Comp_curKind(&((*c)));
    if (_m167.tag == 29) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m168 = Comp_curKind(&((*c)));
    if (_m168.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m168.tag == 0) {
    break;
    }
    else if (_m168.tag == 18) {
    Comp_advance(&((*c)));
    Tok bTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind_push(&(binds), (Bind){.nameStart = bTok.start, .nameLen = bTok.len, .fieldStart = bTok.start, .fieldLen = bTok.len});
    {
    Kind _m169 = Comp_curKind(&((*c)));
    if (_m169.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else if (_m168.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m170 = Comp_curKind(&((*c)));
    if (_m170.tag == 32) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m171 = Comp_curKind(&((*c)));
    if (_m171.tag == 18) {
    Comp_advance(&((*c)));
    Tok bTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind_push(&(binds), (Bind){.nameStart = bTok.start, .nameLen = bTok.len, .fieldStart = fTok.start, .fieldLen = fTok.len});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    {
    Kind _m172 = Comp_curKind(&((*c)));
    if (_m172.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
    else {
    }
    }
    }
    { PatInfo __ret173 = (PatInfo){.isWildcard = isWildcard, .enumStart = enumStart, .enumLen = enumLen, .variantStart = variantStart, .variantLen = variantLen, .binds = PlewArray_Bind_share(binds)};
    PlewArray_Bind_release(binds);
    return __ret173; }
    PlewArray_Bind_release(binds);
}
long long bindNamesMatch(Comp* c, PlewArray_Bind a, PlewArray_Bind b) {
    if ((long long)((a).len) != (long long)((b).len)) {
    { long long __ret174 = 0;
    return __ret174; }
    }
    uint64_t i = 0;
    while (i < (long long)((a).len)) {
    Bind an = PlewArray_Bind_get(a, (long long)(i));
    long long found = 0;
    uint64_t j = 0;
    while (j < (long long)((b).len)) {
    Bind bn = PlewArray_Bind_get(b, (long long)(j));
    if (spansEqual(&((*c)), an.nameStart, an.nameLen, bn.nameStart, bn.nameLen)) {
    found = 1;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (found) {
    }
    else {
    { long long __ret175 = 0;
    return __ret175; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret176 = 1;
    return __ret176; }
}
PlewArray_PatInfo parseArmPatterns(Comp* c) {
    uint64_t startOff = Comp_cur(&((*c))).start;
    PlewArray_PatInfo pats = PlewArray_PatInfo_new();
    PlewArray_PatInfo_push(&(pats), parsePattern(&((*c))));
    while (1) {
    {
    Kind _m177 = Comp_curKind(&((*c)));
    if (_m177.tag == 50) {
    Comp_advance(&((*c)));
    Comp_skipNewlines(&((*c)));
    PlewArray_PatInfo_push(&(pats), parsePattern(&((*c))));
    }
    else {
    break;
    }
    }
    }
    {
    Kind _m178 = Comp_curKind(&((*c)));
    if (_m178.tag == 56) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t pi = 1;
    while (pi < (long long)((pats).len)) {
    PatInfo p0 = PatInfo_share(PlewArray_PatInfo_get(pats, (long long)(0)));
    PatInfo pn = PatInfo_share(PlewArray_PatInfo_get(pats, (long long)(pi)));
    if (bindNamesMatch(&((*c)), p0.binds, pn.binds)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), startOff), (PlewString){"or-pattern alternatives must bind the same names", 48});
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PatInfo_release(pn);
    PatInfo_release(p0);
    }
    { PlewArray_PatInfo __ret179 = PlewArray_PatInfo_share(pats);
    PlewArray_PatInfo_release(pats);
    return __ret179; }
    PlewArray_PatInfo_release(pats);
}
uint64_t parseMatch(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m180 = Comp_curKind(&((*c)));
    if (_m180.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_MatchArm arms = PlewArray_MatchArm_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m181 = k;
    if (_m181.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m181.tag == 0) {
    break;
    }
    else {
    PlewArray_PatInfo pats = parseArmPatterns(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock(&((*c)));
    {
    PlewArray_PatInfo __fa182 = pats;
    for (long long __fi182 = 0; __fi182 < __fa182.len; __fi182++) {
        PatInfo pi = PlewArray_PatInfo_get(__fa182, __fi182);
    PlewArray_MatchArm_push(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = PlewArray_Bind_share(pi.binds), .body = body});
    }
    }
    PlewArray_PatInfo_release(pats);
    }
    }
    }
    { uint64_t __ret183 = Comp_pushStmt(&((*c)), (Stmt){.tag = 8, .data.Match = {.scrut = scrut, .arms = PlewArray_MatchArm_share(arms)}});
    PlewArray_MatchArm_release(arms);
    return __ret183; }
    PlewArray_MatchArm_release(arms);
}
uint64_t parseMatchExpr(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m184 = Comp_curKind(&((*c)));
    if (_m184.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_MatchArm arms = PlewArray_MatchArm_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m185 = k;
    if (_m185.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m185.tag == 0) {
    break;
    }
    else {
    PlewArray_PatInfo pats = parseArmPatterns(&((*c)));
    uint64_t body = parseExpr(&((*c)));
    {
    PlewArray_PatInfo __fa186 = pats;
    for (long long __fi186 = 0; __fi186 < __fa186.len; __fi186++) {
        PatInfo pi = PlewArray_PatInfo_get(__fa186, __fi186);
    PlewArray_MatchArm_push(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = PlewArray_Bind_share(pi.binds), .body = body});
    }
    }
    {
    Kind _m187 = Comp_curKind(&((*c)));
    if (_m187.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_PatInfo_release(pats);
    }
    }
    }
    { uint64_t __ret188 = Comp_pushExpr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = scrut, .arms = PlewArray_MatchArm_share(arms)}});
    PlewArray_MatchArm_release(arms);
    return __ret188; }
    PlewArray_MatchArm_release(arms);
}
uint64_t parseStmt(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m189 = k;
    if (_m189.tag == 18) {
    { uint64_t __ret190 = parseLet(&((*c)), 0);
    return __ret190; }
    }
    else if (_m189.tag == 19) {
    Comp_advance(&((*c)));
    { uint64_t __ret191 = parseLet(&((*c)), 1);
    return __ret191; }
    }
    else if (_m189.tag == 10) {
    { uint64_t __ret192 = parseIf(&((*c)));
    return __ret192; }
    }
    else if (_m189.tag == 12) {
    { uint64_t __ret193 = parseWhile(&((*c)));
    return __ret193; }
    }
    else if (_m189.tag == 13) {
    { uint64_t __ret194 = parseFor(&((*c)));
    return __ret194; }
    }
    else if (_m189.tag == 9) {
    { uint64_t __ret195 = parseMatch(&((*c)));
    return __ret195; }
    }
    else if (_m189.tag == 14) {
    Comp_advance(&((*c)));
    { uint64_t __ret196 = Comp_pushStmt(&((*c)), (Stmt){.tag = 11});
    return __ret196; }
    }
    else if (_m189.tag == 15) {
    Comp_advance(&((*c)));
    { uint64_t __ret197 = Comp_pushStmt(&((*c)), (Stmt){.tag = 12});
    return __ret197; }
    }
    else if (_m189.tag == 16) {
    { uint64_t __ret198 = parseReturn(&((*c)));
    return __ret198; }
    }
    else if (_m189.tag == 5) {
    if (Comp_identIs(&((*c)), (PlewString){"print", 5})) {
    {
    Kind _m199 = Comp_peekKind(&((*c)), 1);
    if (_m199.tag == 25) {
    { uint64_t __ret200 = parsePrint(&((*c)));
    return __ret200; }
    }
    else {
    { uint64_t __ret201 = parseExprOrAssign(&((*c)));
    return __ret201; }
    }
    }
    }
    if (Comp_identIs(&((*c)), (PlewString){"panic", 5})) {
    { uint64_t __ret202 = parsePanic(&((*c)));
    return __ret202; }
    }
    { uint64_t __ret203 = parseExprOrAssign(&((*c)));
    return __ret203; }
    }
    else if (_m189.tag == 17) {
    { uint64_t __ret204 = parseGive(&((*c)));
    return __ret204; }
    }
    else {
    { uint64_t __ret205 = parseExprOrAssign(&((*c)));
    return __ret205; }
    }
    }
}
uint64_t parseBlock(Comp* c) {
    {
    Kind _m206 = Comp_curKind(&((*c)));
    if (_m206.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_U64 stmts = PlewArray_U64_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m207 = k;
    if (_m207.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m207.tag == 0) {
    break;
    }
    else {
    uint64_t s = parseStmt(&((*c)));
    PlewArray_U64_push(&(stmts), s);
    }
    }
    }
    uint64_t id = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(stmts)});
    { uint64_t __ret208 = id;
    PlewArray_U64_release(stmts);
    return __ret208; }
    PlewArray_U64_release(stmts);
}
PlewArray_Param parseParamList(Comp* c) {
    PlewArray_Param params = PlewArray_Param_new();
    {
    Kind _m209 = Comp_curKind(&((*c)));
    if (_m209.tag == 25) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m210 = k;
    if (_m210.tag == 26) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m210.tag == 0) {
    break;
    }
    else {
    Tok pTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t pTyStart = 0;
    uint64_t pTyLen = 0;
    long long pTyIsArray = 0;
    uint64_t pTyRef = 0;
    long long pIsInout = 0;
    long long pNoLabel = 0;
    {
    Kind _m211 = Comp_curKind(&((*c)));
    if (_m211.tag == 54) {
    if ((Comp_peekKind(&((*c)), 1)).tag == 32) {
    Comp_advance(&((*c)));
    pNoLabel = 1;
    }
    }
    else {
    }
    }
    {
    Kind _m212 = Comp_curKind(&((*c)));
    if (_m212.tag == 32) {
    Comp_advance(&((*c)));
    {
    Kind _m213 = Comp_curKind(&((*c)));
    if (_m213.tag == 22) {
    Comp_advance(&((*c)));
    pIsInout = 1;
    }
    else {
    }
    }
    PType pty = parseTypeTok(&((*c)));
    pTyStart = pty.start;
    pTyLen = pty.len;
    pTyIsArray = pty.isArray;
    pTyRef = pty.ref;
    recordArrayElem(&((*c)), pty);
    }
    else {
    }
    }
    long long pHasDefault = 0;
    uint64_t pDefault = 0;
    {
    Kind _m214 = Comp_curKind(&((*c)));
    if (_m214.tag == 34) {
    Comp_advance(&((*c)));
    pHasDefault = 1;
    pDefault = parseExpr(&((*c)));
    }
    else {
    }
    }
    PlewArray_Param_push(&(params), (Param){.nameStart = pTok.start, .nameLen = pTok.len, .tyStart = pTyStart, .tyLen = pTyLen, .tyIsArray = pTyIsArray, .ty = pTyRef, .isInout = pIsInout, .noLabel = pNoLabel, .hasDefault = pHasDefault, .defaultExpr = pDefault});
    {
    Kind _m215 = Comp_curKind(&((*c)));
    if (_m215.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    }
    else {
    }
    }
    { PlewArray_Param __ret216 = PlewArray_Param_share(params);
    PlewArray_Param_release(params);
    return __ret216; }
    PlewArray_Param_release(params);
}
void parseFuncCommon(Comp* c, long long hasRecv, uint64_t recvStart, uint64_t recvLen, long long selfInout, PlewArray_Bind implParams) {
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind ownParams = parseTypeParams(&((*c)));
    PlewArray_Bind typeParams = PlewArray_Bind_new();
    uint64_t ipi = 0;
    while (ipi < (long long)((implParams).len)) {
    PlewArray_Bind_push(&(typeParams), PlewArray_Bind_get(implParams, (long long)(ipi)));
    ipi = ({ uint64_t __ov; if (__builtin_add_overflow((ipi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t opi = 0;
    while (opi < (long long)((ownParams).len)) {
    PlewArray_Bind_push(&(typeParams), PlewArray_Bind_get(ownParams, (long long)(opi)));
    opi = ({ uint64_t __ov; if (__builtin_add_overflow((opi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param params = parseParamList(&((*c)));
    long long hasRet = 0;
    uint64_t retStart = 0;
    uint64_t retLen = 0;
    long long retIsArray = 0;
    uint64_t retRef = 0;
    {
    Kind _m217 = Comp_curKind(&((*c)));
    if (_m217.tag == 55) {
    Comp_advance(&((*c)));
    hasRet = 1;
    PType rty = parseTypeTok(&((*c)));
    retStart = rty.start;
    retLen = rty.len;
    retIsArray = rty.isArray;
    retRef = rty.ref;
    recordArrayElem(&((*c)), rty);
    }
    else {
    }
    }
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock(&((*c)));
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .params = PlewArray_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body, .hasRecv = hasRecv, .recvStart = recvStart, .recvLen = recvLen, .selfInout = selfInout});
    PlewArray_Param_release(params);
    PlewArray_Bind_release(typeParams);
    PlewArray_Bind_release(ownParams);
}
void parseFunc(Comp* c) {
    Comp_advance(&((*c)));
    PlewArray_Bind noParams = PlewArray_Bind_new();
    parseFuncCommon(&((*c)), 0, 0, 0, 0, noParams);
    PlewArray_Bind_release(noParams);
}
void parseImpl(Comp* c) {
    Comp_advance(&((*c)));
    PlewArray_Bind implParams = parseTypeParams(&((*c)));
    PType recvPty = parseTypeTok(&((*c)));
    uint64_t recvStart = recvPty.start;
    uint64_t recvLen = recvPty.len;
    {
    Kind _m218 = Comp_curKind(&((*c)));
    if (_m218.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m219 = k;
    if (_m219.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m219.tag == 0) {
    break;
    }
    else if (_m219.tag == 22) {
    Comp_advance(&((*c)));
    {
    Kind _m220 = Comp_curKind(&((*c)));
    if (_m220.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon(&((*c)), 1, recvStart, recvLen, 1, implParams);
    }
    else if (_m219.tag == 6) {
    Comp_advance(&((*c)));
    parseFuncCommon(&((*c)), 1, recvStart, recvLen, 0, implParams);
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    PlewArray_Bind_release(implParams);
}
void parseStruct(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind typeParams = parseTypeParams(&((*c)));
    {
    Kind _m221 = Comp_curKind(&((*c)));
    if (_m221.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_FieldDef fields = PlewArray_FieldDef_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m222 = k;
    if (_m222.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m222.tag == 0) {
    break;
    }
    else {
    long long isMut = 0;
    {
    Kind _m223 = Comp_curKind(&((*c)));
    if (_m223.tag == 19) {
    Comp_advance(&((*c)));
    isMut = 1;
    }
    else {
    }
    }
    {
    Kind _m224 = Comp_curKind(&((*c)));
    if (_m224.tag == 18) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyStart = 0;
    uint64_t tyLen = 0;
    long long tyIsArray = 0;
    uint64_t tyRef = 0;
    {
    Kind _m225 = Comp_curKind(&((*c)));
    if (_m225.tag == 32) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    tyRef = ty.ref;
    recordArrayElem(&((*c)), ty);
    }
    else {
    }
    }
    PlewArray_FieldDef_push(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .isMut = isMut});
    }
    }
    }
    PlewArray_StructDef_push(&((*c).structs), (StructDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .fields = PlewArray_FieldDef_share(fields)});
    PlewArray_FieldDef_release(fields);
    PlewArray_Bind_release(typeParams);
}
void parseEnum(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind typeParams = parseTypeParams(&((*c)));
    {
    Kind _m226 = Comp_curKind(&((*c)));
    if (_m226.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_Variant variants = PlewArray_Variant_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m227 = k;
    if (_m227.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m227.tag == 0) {
    break;
    }
    else if (_m227.tag == 5) {
    Tok vTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_new();
    {
    Kind _m228 = Comp_curKind(&((*c)));
    if (_m228.tag == 29) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m229 = Comp_curKind(&((*c)));
    if (_m229.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m229.tag == 0) {
    break;
    }
    else if (_m229.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyStart = 0;
    uint64_t tyLen = 0;
    long long tyIsArray = 0;
    uint64_t tyRef = 0;
    {
    Kind _m230 = Comp_curKind(&((*c)));
    if (_m230.tag == 32) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    tyRef = ty.ref;
    recordArrayElem(&((*c)), ty);
    }
    else {
    }
    }
    PlewArray_FieldDef_push(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .isMut = 0});
    {
    Kind _m231 = Comp_curKind(&((*c)));
    if (_m231.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
    else {
    }
    }
    PlewArray_Variant_push(&(variants), (Variant){.nameStart = vTok.start, .nameLen = vTok.len, .fields = PlewArray_FieldDef_share(fields)});
    PlewArray_FieldDef_release(fields);
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    PlewArray_EnumDef_push(&((*c).enums), (EnumDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .variants = PlewArray_Variant_share(variants)});
    PlewArray_Variant_release(variants);
    PlewArray_Bind_release(typeParams);
}
void markImport(Comp* c, uint64_t segStart, uint64_t segLen, uint64_t nameStart, uint64_t nameLen) {
    if (rangeEquals((*c).bytes, segStart, segLen, (PlewString){"Io", 2})) {
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"print", 5})) {
    (*c).impPrint = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"write", 5})) {
    (*c).impWrite = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"writeByte", 9})) {
    (*c).impWriteByte = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readStdin", 9})) {
    (*c).impReadStdin = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFile", 8})) {
    (*c).impReadFile = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFileBytes", 13})) {
    (*c).impReadFileBytes = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"eprint", 6})) {
    (*c).impEprint = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"fileExists", 10})) {
    (*c).impFileExists = 1;
    }
    }
    if (rangeEquals((*c).bytes, segStart, segLen, (PlewString){"Process", 7})) {
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argCount", 8})) {
    (*c).impArgCount = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argAt", 5})) {
    (*c).impArgAt = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"exit", 4})) {
    (*c).impExit = 1;
    }
    }
}
void parseImport(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t segStart = 0;
    uint64_t segLen = 0;
    while (1) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m232 = k;
    if (_m232.tag == 1) {
    break;
    }
    else if (_m232.tag == 0) {
    break;
    }
    else if (_m232.tag == 29) {
    break;
    }
    else if (_m232.tag == 5) {
    if (Comp_identIs(&((*c)), (PlewString){"with", 4})) {
    Comp_advance(&((*c)));
    break;
    }
    Tok t = Comp_cur(&((*c)));
    segStart = t.start;
    segLen = t.len;
    Comp_advance(&((*c)));
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    {
    Kind _m233 = Comp_curKind(&((*c)));
    if (_m233.tag == 29) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m234 = k;
    if (_m234.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m234.tag == 0) {
    break;
    }
    else if (_m234.tag == 31) {
    Comp_advance(&((*c)));
    }
    else if (_m234.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    markImport(&((*c)), segStart, segLen, t.start, t.len);
    Comp_advance(&((*c)));
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
    else {
    }
    }
}
void parseProgram(Comp* c) {
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m235 = k;
    if (_m235.tag == 6) {
    parseFunc(&((*c)));
    }
    else if (_m235.tag == 7) {
    parseStruct(&((*c)));
    }
    else if (_m235.tag == 8) {
    parseEnum(&((*c)));
    }
    else if (_m235.tag == 5) {
    if (Comp_identIs(&((*c)), (PlewString){"import", 6})) {
    parseImport(&((*c)));
    }
    else {
    if (Comp_identIs(&((*c)), (PlewString){"impl", 4})) {
    parseImpl(&((*c)));
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    else if (_m235.tag == 0) {
    break;
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
}
PlewString digitStr(int64_t d) {
    if (d == 0) {
    { PlewString __ret236 = (PlewString){"0", 1};
    return __ret236; }
    }
    if (d == 1) {
    { PlewString __ret237 = (PlewString){"1", 1};
    return __ret237; }
    }
    if (d == 2) {
    { PlewString __ret238 = (PlewString){"2", 1};
    return __ret238; }
    }
    if (d == 3) {
    { PlewString __ret239 = (PlewString){"3", 1};
    return __ret239; }
    }
    if (d == 4) {
    { PlewString __ret240 = (PlewString){"4", 1};
    return __ret240; }
    }
    if (d == 5) {
    { PlewString __ret241 = (PlewString){"5", 1};
    return __ret241; }
    }
    if (d == 6) {
    { PlewString __ret242 = (PlewString){"6", 1};
    return __ret242; }
    }
    if (d == 7) {
    { PlewString __ret243 = (PlewString){"7", 1};
    return __ret243; }
    }
    if (d == 8) {
    { PlewString __ret244 = (PlewString){"8", 1};
    return __ret244; }
    }
    { PlewString __ret245 = (PlewString){"9", 1};
    return __ret245; }
}
void writeInt(int64_t n) {
    if (n < 0) {
    plew_write((PlewString){"-", 1});
    writeInt(({ int64_t __ov; if (__builtin_sub_overflow((0), (n), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    return;
    }
    if (n >= 10) {
    writeInt(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); if (__dr == -1 && __dl == INT64_MIN) plew_panic((PlewString){"integer overflow", 16}); __dl / __dr; }));
    }
    plew_write(digitStr(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); (__dr == -1 ? 0 : __dl % __dr); })));
}
PlewString digitStrU(uint64_t d) {
    if (d == 0) {
    { PlewString __ret246 = (PlewString){"0", 1};
    return __ret246; }
    }
    if (d == 1) {
    { PlewString __ret247 = (PlewString){"1", 1};
    return __ret247; }
    }
    if (d == 2) {
    { PlewString __ret248 = (PlewString){"2", 1};
    return __ret248; }
    }
    if (d == 3) {
    { PlewString __ret249 = (PlewString){"3", 1};
    return __ret249; }
    }
    if (d == 4) {
    { PlewString __ret250 = (PlewString){"4", 1};
    return __ret250; }
    }
    if (d == 5) {
    { PlewString __ret251 = (PlewString){"5", 1};
    return __ret251; }
    }
    if (d == 6) {
    { PlewString __ret252 = (PlewString){"6", 1};
    return __ret252; }
    }
    if (d == 7) {
    { PlewString __ret253 = (PlewString){"7", 1};
    return __ret253; }
    }
    if (d == 8) {
    { PlewString __ret254 = (PlewString){"8", 1};
    return __ret254; }
    }
    { PlewString __ret255 = (PlewString){"9", 1};
    return __ret255; }
}
void writeU64(uint64_t n) {
    if (n >= 10) {
    writeU64(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); __dl / __dr; }));
    }
    plew_write(digitStrU(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); __dl % __dr; })));
}
void writeSpan(Comp* c, uint64_t start, uint64_t len) {
    uint64_t j = 0;
    while (j < len) {
    putchar((int)(PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })))));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void eprintInt(int64_t n) {
    if (n >= 10) {
    eprintInt(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); if (__dr == -1 && __dl == INT64_MIN) plew_panic((PlewString){"integer overflow", 16}); __dl / __dr; }));
    }
    plew_eprint(digitStr(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); (__dr == -1 ? 0 : __dl % __dr); })));
}
void compileError(PlewString msg) {
    plew_eprint((PlewString){"plewc: error: ", 14});
    plew_eprint(msg);
    plew_eprint((PlewString){"\n", 1});
    exit((int)(1));
}
void compileErrorAt(int64_t line, PlewString msg) {
    plew_eprint((PlewString){"plewc: error: line ", 19});
    eprintInt(line);
    plew_eprint((PlewString){": ", 2});
    plew_eprint(msg);
    plew_eprint((PlewString){"\n", 1});
    exit((int)(1));
}
long long isPrimType(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I8", 2})) {
    { long long __ret256 = 1;
    return __ret256; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    { long long __ret257 = 1;
    return __ret257; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    { long long __ret258 = 1;
    return __ret258; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I64", 3})) {
    { long long __ret259 = 1;
    return __ret259; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    { long long __ret260 = 1;
    return __ret260; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U16", 3})) {
    { long long __ret261 = 1;
    return __ret261; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U32", 3})) {
    { long long __ret262 = 1;
    return __ret262; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U64", 3})) {
    { long long __ret263 = 1;
    return __ret263; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"Bool", 4})) {
    { long long __ret264 = 1;
    return __ret264; }
    }
    { long long __ret265 = 0;
    return __ret265; }
}
long long isIntType(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I8", 2})) {
    { long long __ret266 = 1;
    return __ret266; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    { long long __ret267 = 1;
    return __ret267; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    { long long __ret268 = 1;
    return __ret268; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I64", 3})) {
    { long long __ret269 = 1;
    return __ret269; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    { long long __ret270 = 1;
    return __ret270; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U16", 3})) {
    { long long __ret271 = 1;
    return __ret271; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U32", 3})) {
    { long long __ret272 = 1;
    return __ret272; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U64", 3})) {
    { long long __ret273 = 1;
    return __ret273; }
    }
    { long long __ret274 = 0;
    return __ret274; }
}
uint64_t intBits(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I8", 2})) {
    { uint64_t __ret275 = 8;
    return __ret275; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    { uint64_t __ret276 = 8;
    return __ret276; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    { uint64_t __ret277 = 16;
    return __ret277; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U16", 3})) {
    { uint64_t __ret278 = 16;
    return __ret278; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    { uint64_t __ret279 = 32;
    return __ret279; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U32", 3})) {
    { uint64_t __ret280 = 32;
    return __ret280; }
    }
    { uint64_t __ret281 = 64;
    return __ret281; }
}
long long intSigned(Comp* c, uint64_t start, uint64_t len) {
    { long long __ret282 = (PlewArray_U8_get((*c).bytes, (long long)(start)) == 73);
    return __ret282; }
}
long long losslessInt(Comp* c, uint64_t srcStart, uint64_t srcLen, uint64_t dstStart, uint64_t dstLen) {
    uint64_t sBits = intBits(&((*c)), srcStart, srcLen);
    uint64_t dBits = intBits(&((*c)), dstStart, dstLen);
    long long sSigned = intSigned(&((*c)), srcStart, srcLen);
    long long dSigned = intSigned(&((*c)), dstStart, dstLen);
    if (sSigned) {
    if (dSigned) {
    { long long __ret283 = (dBits >= sBits);
    return __ret283; }
    }
    { long long __ret284 = 0;
    return __ret284; }
    }
    if (dSigned) {
    { long long __ret285 = (dBits > sBits);
    return __ret285; }
    }
    { long long __ret286 = (dBits >= sBits);
    return __ret286; }
}
long long litFitsType(Comp* c, int64_t value, uint64_t dstStart, uint64_t dstLen) {
    uint64_t bits = intBits(&((*c)), dstStart, dstLen);
    long long sgn = intSigned(&((*c)), dstStart, dstLen);
    { long long __ret287 = litFitsBits(value, bits, sgn);
    return __ret287; }
}
long long litFitsBits(int64_t value, uint64_t bits, long long sgn) {
    if (sgn) {
    if (bits == 8) {
    if (value < (0 - 128)) {
    { long long __ret288 = 0;
    return __ret288; }
    }
    if (value > 127) {
    { long long __ret289 = 0;
    return __ret289; }
    }
    { long long __ret290 = 1;
    return __ret290; }
    }
    if (bits == 16) {
    if (value < (0 - 32768)) {
    { long long __ret291 = 0;
    return __ret291; }
    }
    if (value > 32767) {
    { long long __ret292 = 0;
    return __ret292; }
    }
    { long long __ret293 = 1;
    return __ret293; }
    }
    if (bits == 32) {
    if (value < (0 - 2147483648)) {
    { long long __ret294 = 0;
    return __ret294; }
    }
    if (value > 2147483647) {
    { long long __ret295 = 0;
    return __ret295; }
    }
    { long long __ret296 = 1;
    return __ret296; }
    }
    { long long __ret297 = 1;
    return __ret297; }
    }
    if (value < 0) {
    { long long __ret298 = 0;
    return __ret298; }
    }
    if (bits == 8) {
    if (value > 255) {
    { long long __ret299 = 0;
    return __ret299; }
    }
    { long long __ret300 = 1;
    return __ret300; }
    }
    if (bits == 16) {
    if (value > 65535) {
    { long long __ret301 = 0;
    return __ret301; }
    }
    { long long __ret302 = 1;
    return __ret302; }
    }
    if (bits == 32) {
    if (value > 4294967295) {
    { long long __ret303 = 0;
    return __ret303; }
    }
    { long long __ret304 = 1;
    return __ret304; }
    }
    { long long __ret305 = 1;
    return __ret305; }
}
void genCElem(Comp* c, uint64_t start, uint64_t len) {
    if (len == 0) {
    plew_write((PlewString){"long long", 9});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    plew_write((PlewString){"unsigned char", 13});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I8", 2})) {
    plew_write((PlewString){"int8_t", 6});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    plew_write((PlewString){"int16_t", 7});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U16", 3})) {
    plew_write((PlewString){"uint16_t", 8});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    plew_write((PlewString){"int32_t", 7});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U32", 3})) {
    plew_write((PlewString){"uint32_t", 8});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I64", 3})) {
    plew_write((PlewString){"int64_t", 7});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U64", 3})) {
    plew_write((PlewString){"uint64_t", 8});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"String", 6})) {
    plew_write((PlewString){"PlewString", 10});
    return;
    }
    if (isPrimType(&((*c)), start, len)) {
    plew_write((PlewString){"long long", 9});
    return;
    }
    writeSpan(&((*c)), start, len);
}
void genCTypeRef(Comp* c, uint64_t start, uint64_t len, long long isArray) {
    if (isArray) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), start, len);
    return;
    }
    genCElem(&((*c)), start, len);
}
void genCType(Comp* c, uint64_t start, uint64_t len) {
    genCElem(&((*c)), start, len);
}
void genTypeInfoCType(Comp* c, TypeInfo ti) {
    if (ti.kind == 1) {
    plew_write((PlewString){"PlewString", 10});
    return;
    }
    if (ti.kind == 2) {
    writeSpan(&((*c)), ti.nameStart, ti.nameLen);
    return;
    }
    if (ti.kind == 3) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), ti.nameStart, ti.nameLen);
    return;
    }
    plew_write((PlewString){"long long", 9});
}
long long spansEqual(Comp* c, uint64_t aStart, uint64_t aLen, uint64_t bStart, uint64_t bLen) {
    if (aLen != bLen) {
    { long long __ret306 = 0;
    return __ret306; }
    }
    uint64_t j = 0;
    while (j < aLen) {
    if (PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((aStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((bStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })))) {
    { long long __ret307 = 0;
    return __ret307; }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret308 = 1;
    return __ret308; }
}
int64_t lineOf(Comp* c, uint64_t offset) {
    int64_t line = 1;
    uint64_t i = 0;
    while (i < offset) {
    if (PlewArray_U8_get((*c).bytes, (long long)(i)) == 10) {
    line = ({ int64_t __ov; if (__builtin_add_overflow((line), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { int64_t __ret309 = line;
    return __ret309; }
}
uint64_t exprOffset(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m310 = e;
    if (_m310.tag == 0) {
        uint64_t offset = _m310.data.Int.offset;
        (void)offset;
    { uint64_t __ret311 = offset;
    return __ret311; }
    }
    else if (_m310.tag == 1) {
        uint64_t start = _m310.data.Ident.start;
        (void)start;
        uint64_t len = _m310.data.Ident.len;
        (void)len;
    { uint64_t __ret312 = start;
    return __ret312; }
    }
    else if (_m310.tag == 7) {
        uint64_t start = _m310.data.Str.start;
        (void)start;
        uint64_t len = _m310.data.Str.len;
        (void)len;
    { uint64_t __ret313 = start;
    return __ret313; }
    }
    else if (_m310.tag == 4) {
        uint64_t nameStart = _m310.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m310.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m310.data.Call.args;
        (void)args;
    { uint64_t __ret314 = nameStart;
    return __ret314; }
    }
    else if (_m310.tag == 10) {
        uint64_t recv = _m310.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m310.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m310.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m310.data.Method.args;
        (void)args;
    { uint64_t __ret315 = nameStart;
    return __ret315; }
    }
    else if (_m310.tag == 5) {
        uint64_t base = _m310.data.Field.base;
        (void)base;
        uint64_t nameStart = _m310.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m310.data.Field.nameLen;
        (void)nameLen;
    { uint64_t __ret316 = exprOffset(&((*c)), base);
    return __ret316; }
    }
    else if (_m310.tag == 9) {
        uint64_t base = _m310.data.Index.base;
        (void)base;
        uint64_t index = _m310.data.Index.index;
        (void)index;
    { uint64_t __ret317 = exprOffset(&((*c)), base);
    return __ret317; }
    }
    else if (_m310.tag == 3) {
        int64_t op = _m310.data.Binary.op;
        (void)op;
        uint64_t lhs = _m310.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m310.data.Binary.rhs;
        (void)rhs;
    { uint64_t __ret318 = exprOffset(&((*c)), lhs);
    return __ret318; }
    }
    else if (_m310.tag == 2) {
        int64_t op = _m310.data.Unary.op;
        (void)op;
        uint64_t operand = _m310.data.Unary.operand;
        (void)operand;
    { uint64_t __ret319 = exprOffset(&((*c)), operand);
    return __ret319; }
    }
    else if (_m310.tag == 11) {
        uint64_t operand = _m310.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m310.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m310.data.Cast.tyLen;
        (void)tyLen;
    { uint64_t __ret320 = exprOffset(&((*c)), operand);
    return __ret320; }
    }
    else if (_m310.tag == 6) {
        uint64_t typeStart = _m310.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m310.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m310.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m310.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m310.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m310.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m310.data.Make.fields;
        (void)fields;
    { uint64_t __ret321 = typeStart;
    return __ret321; }
    }
    else if (_m310.tag == 12) {
        uint64_t scrut = _m310.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m310.data.MatchExpr.arms;
        (void)arms;
    { uint64_t __ret322 = exprOffset(&((*c)), scrut);
    return __ret322; }
    }
    else if (_m310.tag == 13) {
        uint64_t cond = _m310.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m310.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m310.data.IfExpr.elseBlk;
        (void)elseBlk;
    { uint64_t __ret323 = exprOffset(&((*c)), cond);
    return __ret323; }
    }
    else if (_m310.tag == 14) {
        uint64_t opt = _m310.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m310.data.Coalesce.deflt;
        (void)deflt;
    { uint64_t __ret324 = exprOffset(&((*c)), opt);
    return __ret324; }
    }
    else if (_m310.tag == 15) {
        uint64_t expr = _m310.data.Try.expr;
        (void)expr;
    { uint64_t __ret325 = exprOffset(&((*c)), expr);
    return __ret325; }
    }
    else if (_m310.tag == 16) {
        uint64_t base = _m310.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m310.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m310.data.Arrow.nameLen;
        (void)nameLen;
    { uint64_t __ret326 = exprOffset(&((*c)), base);
    return __ret326; }
    }
    else if (_m310.tag == 17) {
        PlewArray_Param params = _m310.data.Closure.params;
        (void)params;
        long long hasRet = _m310.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m310.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m310.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m310.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m310.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m310.data.Closure.body;
        (void)body;
    { uint64_t __ret327 = retStart;
    return __ret327; }
    }
    else {
    { uint64_t __ret328 = 0;
    return __ret328; }
    }
    }
}
uint64_t findFunc(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    }
    else {
    if (spansEqual(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    { uint64_t __ret329 = i;
    Func_release(f);
    return __ret329; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { uint64_t __ret330 = (long long)(((*c).funcs).len);
    return __ret330; }
}
uint64_t findMethod(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (spansEqual(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (spansEqual(&((*c)), recvStart, recvLen, f.recvStart, f.recvLen)) {
    { uint64_t __ret331 = i;
    Func_release(f);
    return __ret331; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { uint64_t __ret332 = (long long)(((*c).funcs).len);
    return __ret332; }
}
long long paramsLabelsOk(Comp* c, PlewArray_Param params, PlewArray_Arg args) {
    if ((long long)((args).len) > (long long)((params).len)) {
    { long long __ret333 = 0;
    return __ret333; }
    }
    uint64_t r = (long long)((args).len);
    while (r < (long long)((params).len)) {
    if (PlewArray_Param_get(params, (long long)(r)).hasDefault) {
    }
    else {
    { long long __ret334 = 0;
    return __ret334; }
    }
    r = ({ uint64_t __ov; if (__builtin_add_overflow((r), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    Arg a = PlewArray_Arg_get(args, (long long)(i));
    Param p = PlewArray_Param_get(params, (long long)(i));
    if (p.noLabel) {
    if (a.hasLabel) {
    { long long __ret335 = 0;
    return __ret335; }
    }
    }
    else {
    if (a.hasLabel) {
    if (spansEqual(&((*c)), a.labelStart, a.labelLen, p.nameStart, p.nameLen)) {
    }
    else {
    { long long __ret336 = 0;
    return __ret336; }
    }
    }
    else {
    { long long __ret337 = 0;
    return __ret337; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret338 = 1;
    return __ret338; }
}
long long callLabelsOk(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t fi = findFunc(&((*c)), nameStart, nameLen);
    if (fi == (long long)(((*c).funcs).len)) {
    { long long __ret339 = 1;
    return __ret339; }
    }
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    { long long __ret340 = paramsLabelsOk(&((*c)), f.params, args);
    Func_release(f);
    return __ret340; }
    Func_release(f);
}
long long armCovers(Comp* c, PlewArray_MatchArm arms, uint64_t variantStart, uint64_t variantLen) {
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    { long long __ret341 = 1;
    MatchArm_release(a);
    return __ret341; }
    }
    if (spansEqual(&((*c)), a.variantStart, a.variantLen, variantStart, variantLen)) {
    { long long __ret342 = 1;
    MatchArm_release(a);
    return __ret342; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    { long long __ret343 = 0;
    return __ret343; }
}
long long matchExhaustive(Comp* c, PlewArray_MatchArm arms) {
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    { long long __ret344 = 1;
    MatchArm_release(a);
    return __ret344; }
    }
    if (enumLen == 0) {
    enumStart = a.enumStart;
    enumLen = a.enumLen;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    if (enumLen == 0) {
    { long long __ret345 = 1;
    return __ret345; }
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (armCovers(&((*c)), arms, v.nameStart, v.nameLen)) {
    }
    else {
    { long long __ret346 = 0;
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret346; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { long long __ret347 = 1;
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret347; }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret348 = 1;
    return __ret348; }
}
uint64_t variantIndex(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    { uint64_t __ret349 = vi;
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret349; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret350 = 0;
    return __ret350; }
}
TypeInfo scalarInfo(void) {
    { TypeInfo __ret351 = (TypeInfo){.kind = 0, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret351; }
}
TypeInfo typeInfoOfName(Comp* c, uint64_t start, uint64_t len, long long isArray) {
    if (isArray) {
    { TypeInfo __ret352 = (TypeInfo){.kind = 3, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret352; }
    }
    if (len == 0) {
    { TypeInfo __ret353 = scalarInfo();
    return __ret353; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"String", 6})) {
    { TypeInfo __ret354 = (TypeInfo){.kind = 1, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret354; }
    }
    if (isPrimType(&((*c)), start, len)) {
    { TypeInfo __ret355 = (TypeInfo){.kind = 0, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret355; }
    }
    { TypeInfo __ret356 = (TypeInfo){.kind = 2, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret356; }
}
void addLocal(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned) {
    PlewArray_Local_push(&((*c).locals), (Local){.nameStart = nameStart, .nameLen = nameLen, .tyStart = tyStart, .tyLen = tyLen, .isArray = isArray, .ty = ty, .isInout = isInout, .isMut = isMut, .owned = owned});
}
uint64_t scopeMark(Comp* c) {
    { uint64_t __ret357 = (long long)(((*c).locals).len);
    return __ret357; }
}
void emitScopeDrops(Comp* c, uint64_t mark) {
    uint64_t i = (long long)(((*c).locals).len);
    while (i > mark) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (lo.owned) {
    if (lo.isArray) {
    plew_write((PlewString){"    ", 4});
    wPA(&((*c)), lo.tyStart, lo.tyLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan(&((*c)), lo.nameStart, lo.nameLen);
    plew_write((PlewString){");\n", 3});
    }
    else {
    if (structLocalReleasable(&((*c)), lo.tyStart, lo.tyLen)) {
    plew_write((PlewString){"    ", 4});
    writeSpan(&((*c)), lo.tyStart, lo.tyLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan(&((*c)), lo.nameStart, lo.nameLen);
    plew_write((PlewString){");\n", 3});
    }
    }
    }
    }
}
long long structLocalReleasable(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret358 = 0;
    return __ret358; }
    }
    if ((long long)((PlewArray_StructDef_get((*c).structs, (long long)(si)).typeParams).len) > 0) {
    { long long __ret359 = 0;
    return __ret359; }
    }
    { long long __ret360 = structNeedsCopy(&((*c)), start, len);
    return __ret360; }
}
void popLocals(Comp* c, uint64_t mark) {
    PlewArray_Local kept = PlewArray_Local_new();
    uint64_t i = 0;
    while (i < mark) {
    PlewArray_Local_push(&(kept), PlewArray_Local_get((*c).locals, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).locals = PlewArray_Local_share(kept);
    PlewArray_Local_release(kept);
}
void scopeExit(Comp* c, uint64_t mark) {
    emitScopeDrops(&((*c)), mark);
    popLocals(&((*c)), mark);
}
long long localIsMutable(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef(&((*c)), start, len)) {
    { long long __ret361 = (*c).curSelfInout;
    return __ret361; }
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (lo.isMut) {
    { long long __ret362 = 1;
    return __ret362; }
    }
    { long long __ret363 = lo.isInout;
    return __ret363; }
    }
    }
    { long long __ret364 = 1;
    return __ret364; }
}
long long isSelfRef(Comp* c, uint64_t start, uint64_t len) {
    if ((*c).curHasRecv) {
    { long long __ret365 = rangeEquals((*c).bytes, start, len, (PlewString){"self", 4});
    return __ret365; }
    }
    { long long __ret366 = 0;
    return __ret366; }
}
long long isInoutLocal(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef(&((*c)), start, len)) {
    { long long __ret367 = (*c).curSelfInout;
    return __ret367; }
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    { long long __ret368 = lo.isInout;
    return __ret368; }
    }
    }
    { long long __ret369 = 0;
    return __ret369; }
}
TypeInfo fieldType(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    { TypeInfo __ret370 = typeInfoOfName(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    PlewArray_FieldDef_release(fs);
    StructDef_release(s);
    return __ret370; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { TypeInfo __ret371 = scalarInfo();
    return __ret371; }
}
long long fieldDeclaredMut(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    { long long __ret372 = f.isMut;
    PlewArray_FieldDef_release(fs);
    StructDef_release(s);
    return __ret372; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { long long __ret373 = 1;
    return __ret373; }
}
long long placeIsMutable(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m374 = e;
    if (_m374.tag == 1) {
        uint64_t start = _m374.data.Ident.start;
        (void)start;
        uint64_t len = _m374.data.Ident.len;
        (void)len;
    { long long __ret375 = localIsMutable(&((*c)), start, len);
    return __ret375; }
    }
    else if (_m374.tag == 5) {
        uint64_t base = _m374.data.Field.base;
        (void)base;
        uint64_t nameStart = _m374.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m374.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 2) {
    if (fieldDeclaredMut(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen)) {
    { long long __ret376 = placeIsMutable(&((*c)), base);
    return __ret376; }
    }
    { long long __ret377 = 0;
    return __ret377; }
    }
    { long long __ret378 = placeIsMutable(&((*c)), base);
    return __ret378; }
    }
    else if (_m374.tag == 9) {
        uint64_t base = _m374.data.Index.base;
        (void)base;
        uint64_t index = _m374.data.Index.index;
        (void)index;
    { long long __ret379 = placeIsMutable(&((*c)), base);
    return __ret379; }
    }
    else if (_m374.tag == 16) {
        uint64_t base = _m374.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m374.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m374.data.Arrow.nameLen;
        (void)nameLen;
    { long long __ret380 = 1;
    return __ret380; }
    }
    else {
    { long long __ret381 = 1;
    return __ret381; }
    }
    }
}
TypeInfo exprType(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m382 = e;
    if (_m382.tag == 0) {
        uint64_t tyStart = _m382.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m382.data.Int.tyLen;
        (void)tyLen;
    if (tyLen != 0) {
    { TypeInfo __ret383 = typeInfoOfName(&((*c)), tyStart, tyLen, 0);
    return __ret383; }
    }
    { TypeInfo __ret384 = scalarInfo();
    return __ret384; }
    }
    else if (_m382.tag == 7) {
        uint64_t start = _m382.data.Str.start;
        (void)start;
        uint64_t len = _m382.data.Str.len;
        (void)len;
    { TypeInfo __ret385 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret385; }
    }
    else if (_m382.tag == 1) {
        uint64_t start = _m382.data.Ident.start;
        (void)start;
        uint64_t len = _m382.data.Ident.len;
        (void)len;
    if (isSelfRef(&((*c)), start, len)) {
    if ((*c).curRecvInstRef != 0) {
    TypeRef rt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)((*c).curRecvInstRef)));
    { TypeInfo __ret386 = (TypeInfo){.kind = 2, .nameStart = rt.nameStart, .nameLen = rt.nameLen, .ref = (*c).curRecvInstRef};
    TypeRef_release(rt);
    return __ret386; }
    TypeRef_release(rt);
    }
    { TypeInfo __ret387 = typeInfoOfName(&((*c)), (*c).curRecvStart, (*c).curRecvLen, 0);
    return __ret387; }
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (isGenericInst(&((*c)), lo.ty)) {
    TypeRef lt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(lo.ty)));
    { TypeInfo __ret388 = (TypeInfo){.kind = 2, .nameStart = lt.nameStart, .nameLen = lt.nameLen, .ref = lo.ty};
    TypeRef_release(lt);
    return __ret388; }
    TypeRef_release(lt);
    }
    if (isRefInst(&((*c)), lo.ty)) {
    TypeRef lt2 = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(lo.ty)));
    { TypeInfo __ret389 = (TypeInfo){.kind = 2, .nameStart = lt2.nameStart, .nameLen = lt2.nameLen, .ref = lo.ty};
    TypeRef_release(lt2);
    return __ret389; }
    TypeRef_release(lt2);
    }
    { TypeInfo __ret390 = typeInfoOfName(&((*c)), lo.tyStart, lo.tyLen, lo.isArray);
    return __ret390; }
    }
    }
    { TypeInfo __ret391 = scalarInfo();
    return __ret391; }
    }
    else if (_m382.tag == 2) {
        int64_t op = _m382.data.Unary.op;
        (void)op;
        uint64_t operand = _m382.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    { TypeInfo __ret392 = exprType(&((*c)), operand);
    return __ret392; }
    }
    if (op == 79) {
    { TypeInfo __ret393 = exprType(&((*c)), operand);
    return __ret393; }
    }
    { TypeInfo __ret394 = scalarInfo();
    return __ret394; }
    }
    else if (_m382.tag == 3) {
        int64_t op = _m382.data.Binary.op;
        (void)op;
        uint64_t lhs = _m382.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m382.data.Binary.rhs;
        (void)rhs;
    if (op >= 56) {
    if (op <= 60) {
    { TypeInfo __ret395 = exprType(&((*c)), lhs);
    return __ret395; }
    }
    }
    if (op >= 74) {
    if (op <= 78) {
    { TypeInfo __ret396 = exprType(&((*c)), lhs);
    return __ret396; }
    }
    }
    { TypeInfo __ret397 = scalarInfo();
    return __ret397; }
    }
    else if (_m382.tag == 4) {
        uint64_t nameStart = _m382.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m382.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m382.data.Call.args;
        (void)args;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readStdin", 9})) {
    { TypeInfo __ret398 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret398; }
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFile", 8})) {
    { TypeInfo __ret399 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret399; }
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFileBytes", 13})) {
    { TypeInfo __ret400 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret400; }
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argAt", 5})) {
    { TypeInfo __ret401 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret401; }
    }
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    if (f.hasRet) {
    if (isGenericInst(&((*c)), f.retTy)) {
    TypeRef rtr = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(f.retTy)));
    { TypeInfo __ret402 = (TypeInfo){.kind = 2, .nameStart = rtr.nameStart, .nameLen = rtr.nameLen, .ref = f.retTy};
    TypeRef_release(rtr);
    Func_release(f);
    return __ret402; }
    TypeRef_release(rtr);
    }
    { TypeInfo __ret403 = typeInfoOfName(&((*c)), f.retStart, f.retLen, f.retIsArray);
    Func_release(f);
    return __ret403; }
    }
    { TypeInfo __ret404 = scalarInfo();
    Func_release(f);
    return __ret404; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { TypeInfo __ret405 = scalarInfo();
    return __ret405; }
    }
    else if (_m382.tag == 5) {
        uint64_t base = _m382.data.Field.base;
        (void)base;
        uint64_t nameStart = _m382.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m382.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (isGenericInst(&((*c)), bt.ref)) {
    { TypeInfo __ret406 = genericFieldTypeInfo(&((*c)), bt.ref, nameStart, nameLen);
    return __ret406; }
    }
    if (bt.kind == 2) {
    { TypeInfo __ret407 = fieldType(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    return __ret407; }
    }
    { TypeInfo __ret408 = scalarInfo();
    return __ret408; }
    }
    else if (_m382.tag == 6) {
        uint64_t typeStart = _m382.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m382.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m382.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m382.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m382.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m382.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m382.data.Make.fields;
        (void)fields;
    if (isGenericInst(&((*c)), ty)) {
    { TypeInfo __ret409 = (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = ty};
    return __ret409; }
    }
    { TypeInfo __ret410 = (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = 0};
    return __ret410; }
    }
    else if (_m382.tag == 8) {
        PlewArray_U64 elems = _m382.data.Array.elems;
        (void)elems;
    { TypeInfo __ret411 = scalarInfo();
    return __ret411; }
    }
    else if (_m382.tag == 9) {
        uint64_t base = _m382.data.Index.base;
        (void)base;
        uint64_t index = _m382.data.Index.index;
        (void)index;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    { TypeInfo __ret412 = typeInfoOfName(&((*c)), bt.nameStart, bt.nameLen, 0);
    return __ret412; }
    }
    { TypeInfo __ret413 = scalarInfo();
    return __ret413; }
    }
    else if (_m382.tag == 10) {
        uint64_t recv = _m382.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m382.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m382.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m382.data.Method.args;
        (void)args;
    TypeInfo rt = exprType(&((*c)), recv);
    if (rt.kind == 2) {
    uint64_t mi = findMethod(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen);
    if (mi == (long long)(((*c).funcs).len)) {
    { TypeInfo __ret414 = scalarInfo();
    return __ret414; }
    }
    Func mf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(mi)));
    if (mf.hasRet) {
    { TypeInfo __ret415 = typeInfoOfName(&((*c)), mf.retStart, mf.retLen, mf.retIsArray);
    Func_release(mf);
    return __ret415; }
    }
    { TypeInfo __ret416 = scalarInfo();
    Func_release(mf);
    return __ret416; }
    Func_release(mf);
    }
    { TypeInfo __ret417 = scalarInfo();
    return __ret417; }
    }
    else if (_m382.tag == 11) {
        uint64_t operand = _m382.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m382.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m382.data.Cast.tyLen;
        (void)tyLen;
    { TypeInfo __ret418 = typeInfoOfName(&((*c)), tyStart, tyLen, 0);
    return __ret418; }
    }
    else if (_m382.tag == 12) {
        uint64_t scrut = _m382.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m382.data.MatchExpr.arms;
        (void)arms;
    if ((long long)((arms).len) > 0) {
    { TypeInfo __ret419 = exprType(&((*c)), PlewArray_MatchArm_get(arms, (long long)(0)).body);
    return __ret419; }
    }
    { TypeInfo __ret420 = scalarInfo();
    return __ret420; }
    }
    else if (_m382.tag == 13) {
        uint64_t cond = _m382.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m382.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m382.data.IfExpr.elseBlk;
        (void)elseBlk;
    uint64_t g = blockGiveExpr(&((*c)), thenBlk);
    if (g < (long long)(((*c).exprs).len)) {
    { TypeInfo __ret421 = exprType(&((*c)), g);
    return __ret421; }
    }
    { TypeInfo __ret422 = scalarInfo();
    return __ret422; }
    }
    else if (_m382.tag == 14) {
        uint64_t opt = _m382.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m382.data.Coalesce.deflt;
        (void)deflt;
    { TypeInfo __ret423 = exprType(&((*c)), deflt);
    return __ret423; }
    }
    else if (_m382.tag == 15) {
        uint64_t expr = _m382.data.Try.expr;
        (void)expr;
    TypeInfo rt = exprType(&((*c)), expr);
    if (isGenericInst(&((*c)), rt.ref)) {
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(rt.ref)));
    if ((long long)((inst.args).len) > 0) {
    { TypeInfo __ret424 = typeInfoOfRef(&((*c)), PlewArray_U64_get(inst.args, (long long)(0)));
    TypeRef_release(inst);
    return __ret424; }
    }
    TypeRef_release(inst);
    }
    { TypeInfo __ret425 = scalarInfo();
    return __ret425; }
    }
    else if (_m382.tag == 16) {
        uint64_t base = _m382.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m382.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m382.data.Arrow.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (isRefInst(&((*c)), bt.ref)) {
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(bt.ref)));
    TypeInfo pt = typeInfoOfRef(&((*c)), PlewArray_U64_get(inst.args, (long long)(0)));
    if (pt.kind == 2) {
    { TypeInfo __ret426 = fieldType(&((*c)), pt.nameStart, pt.nameLen, nameStart, nameLen);
    TypeRef_release(inst);
    return __ret426; }
    }
    TypeRef_release(inst);
    }
    { TypeInfo __ret427 = scalarInfo();
    return __ret427; }
    }
    else if (_m382.tag == 17) {
        PlewArray_Param params = _m382.data.Closure.params;
        (void)params;
        long long hasRet = _m382.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m382.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m382.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m382.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m382.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m382.data.Closure.body;
        (void)body;
    { TypeInfo __ret428 = scalarInfo();
    return __ret428; }
    }
    else { __builtin_unreachable(); }
    }
    { TypeInfo __ret429 = scalarInfo();
    return __ret429; }
}
uint64_t blockGiveExpr(Comp* c, uint64_t blkId) {
    Block blk = Block_share(PlewArray_Block_get((*c).blocks, (long long)(blkId)));
    PlewArray_U64 stmts = PlewArray_U64_share(blk.stmts);
    uint64_t i = 0;
    uint64_t found = (long long)(((*c).exprs).len);
    while (i < (long long)((stmts).len)) {
    Stmt s = PlewArray_Stmt_get((*c).stmts, (long long)(PlewArray_U64_get(stmts, (long long)(i))));
    {
    Stmt _m430 = s;
    if (_m430.tag == 10) {
        uint64_t value = _m430.data.Give.value;
        (void)value;
    found = value;
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret431 = found;
    PlewArray_U64_release(stmts);
    Block_release(blk);
    return __ret431; }
    PlewArray_U64_release(stmts);
    Block_release(blk);
}
void addBindLocal(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    addLocal(&((*c)), bindStart, bindLen, f.tyStart, f.tyLen, f.tyIsArray, f.ty, 0, 0, 0);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
}
void genBindType(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, bindStart, bindLen)) {
    genCTypeRef(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    plew_write((PlewString){"long long", 9});
}
PlewString binOpStr(int64_t op) {
    if (op == 56) {
    { PlewString __ret432 = (PlewString){" + ", 3};
    return __ret432; }
    }
    if (op == 57) {
    { PlewString __ret433 = (PlewString){" - ", 3};
    return __ret433; }
    }
    if (op == 58) {
    { PlewString __ret434 = (PlewString){" * ", 3};
    return __ret434; }
    }
    if (op == 59) {
    { PlewString __ret435 = (PlewString){" / ", 3};
    return __ret435; }
    }
    if (op == 60) {
    { PlewString __ret436 = (PlewString){" % ", 3};
    return __ret436; }
    }
    if (op == 50) {
    { PlewString __ret437 = (PlewString){" == ", 4};
    return __ret437; }
    }
    if (op == 51) {
    { PlewString __ret438 = (PlewString){" != ", 4};
    return __ret438; }
    }
    if (op == 52) {
    { PlewString __ret439 = (PlewString){" < ", 3};
    return __ret439; }
    }
    if (op == 53) {
    { PlewString __ret440 = (PlewString){" <= ", 4};
    return __ret440; }
    }
    if (op == 54) {
    { PlewString __ret441 = (PlewString){" > ", 3};
    return __ret441; }
    }
    if (op == 55) {
    { PlewString __ret442 = (PlewString){" >= ", 4};
    return __ret442; }
    }
    if (op == 61) {
    { PlewString __ret443 = (PlewString){" && ", 4};
    return __ret443; }
    }
    if (op == 62) {
    { PlewString __ret444 = (PlewString){" || ", 4};
    return __ret444; }
    }
    if (op == 74) {
    { PlewString __ret445 = (PlewString){" & ", 3};
    return __ret445; }
    }
    if (op == 75) {
    { PlewString __ret446 = (PlewString){" | ", 3};
    return __ret446; }
    }
    if (op == 76) {
    { PlewString __ret447 = (PlewString){" ^ ", 3};
    return __ret447; }
    }
    if (op == 77) {
    { PlewString __ret448 = (PlewString){" << ", 4};
    return __ret448; }
    }
    if (op == 78) {
    { PlewString __ret449 = (PlewString){" >> ", 4};
    return __ret449; }
    }
    { PlewString __ret450 = (PlewString){" ? ", 3};
    return __ret450; }
}
PlewString unaryOpStr(int64_t op) {
    if (op == 57) {
    { PlewString __ret451 = (PlewString){"-", 1};
    return __ret451; }
    }
    if (op == 79) {
    { PlewString __ret452 = (PlewString){"~", 1};
    return __ret452; }
    }
    { PlewString __ret453 = (PlewString){"!", 1};
    return __ret453; }
}
int64_t strDecodedLen(Comp* c, uint64_t start, uint64_t len) {
    int64_t n = 0;
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow((start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t end = ({ uint64_t __ov; if (__builtin_sub_overflow((({ uint64_t __ov; if (__builtin_add_overflow((start), (len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < end) {
    if (PlewArray_U8_get((*c).bytes, (long long)(j)) == 92) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    n = ({ int64_t __ov; if (__builtin_add_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { int64_t __ret454 = n;
    return __ret454; }
}
long long isCheckedArith(int64_t op) {
    if (op == 56) {
    { long long __ret455 = 1;
    return __ret455; }
    }
    if (op == 57) {
    { long long __ret456 = 1;
    return __ret456; }
    }
    if (op == 58) {
    { long long __ret457 = 1;
    return __ret457; }
    }
    { long long __ret458 = 0;
    return __ret458; }
}
int64_t compoundCheckedBin(int64_t op) {
    if (op == 67) {
    { int64_t __ret459 = 56;
    return __ret459; }
    }
    if (op == 68) {
    { int64_t __ret460 = 57;
    return __ret460; }
    }
    if (op == 69) {
    { int64_t __ret461 = 58;
    return __ret461; }
    }
    { int64_t __ret462 = 0;
    return __ret462; }
}
PlewString overflowBuiltin(int64_t op) {
    if (op == 56) {
    { PlewString __ret463 = (PlewString){"__builtin_add_overflow", 22};
    return __ret463; }
    }
    if (op == 57) {
    { PlewString __ret464 = (PlewString){"__builtin_sub_overflow", 22};
    return __ret464; }
    }
    { PlewString __ret465 = (PlewString){"__builtin_mul_overflow", 22};
    return __ret465; }
}
TypeInfo arithIntType(Comp* c, uint64_t lhs, uint64_t rhs) {
    TypeInfo lt = exprType(&((*c)), lhs);
    if (lt.kind == 0) {
    if (isIntType(&((*c)), lt.nameStart, lt.nameLen)) {
    { TypeInfo __ret466 = lt;
    return __ret466; }
    }
    }
    TypeInfo rt = exprType(&((*c)), rhs);
    if (rt.kind == 0) {
    if (isIntType(&((*c)), rt.nameStart, rt.nameLen)) {
    { TypeInfo __ret467 = rt;
    return __ret467; }
    }
    }
    { TypeInfo __ret468 = scalarInfo();
    return __ret468; }
}
void genCheckedArith(Comp* c, int64_t op, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen) {
    plew_write((PlewString){"({ ", 3});
    genCElem(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __ov; if (", 11});
    plew_write(overflowBuiltin(op));
    plew_write((PlewString){"((", 2});
    genExpr(&((*c)), lhs);
    plew_write((PlewString){"), (", 4});
    genExpr(&((*c)), rhs);
    plew_write((PlewString){"), &__ov)) plew_panic((PlewString){\"integer overflow\", 16}); __ov; })", 69});
}
void genArrayGet(Comp* c, uint64_t base, uint64_t index, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_get(", 5});
    genExpr(&((*c)), base);
    plew_write((PlewString){", (long long)(", 14});
    genExpr(&((*c)), index);
    plew_write((PlewString){"))", 2});
}
PlewString intMinMacro(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I8", 2})) {
    { PlewString __ret469 = (PlewString){"INT8_MIN", 8};
    return __ret469; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    { PlewString __ret470 = (PlewString){"INT16_MIN", 9};
    return __ret470; }
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    { PlewString __ret471 = (PlewString){"INT32_MIN", 9};
    return __ret471; }
    }
    { PlewString __ret472 = (PlewString){"INT64_MIN", 9};
    return __ret472; }
}
void genCheckedNeg(Comp* c, uint64_t operand, uint64_t tyStart, uint64_t tyLen) {
    plew_write((PlewString){"({ ", 3});
    genCElem(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __ov; if (__builtin_sub_overflow((", 35});
    genCElem(&((*c)), tyStart, tyLen);
    plew_write((PlewString){")0, (", 5});
    genExpr(&((*c)), operand);
    plew_write((PlewString){"), &__ov)) plew_panic((PlewString){\"integer overflow\", 16}); __ov; })", 69});
}
void genCheckedDiv(Comp* c, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen, long long isMod) {
    long long signedTy = intSigned(&((*c)), tyStart, tyLen);
    plew_write((PlewString){"({ ", 3});
    genCElem(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __dl = (", 9});
    genExpr(&((*c)), lhs);
    plew_write((PlewString){"); ", 3});
    genCElem(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __dr = (", 9});
    genExpr(&((*c)), rhs);
    plew_write((PlewString){"); if (__dr == 0) plew_panic((PlewString){", 42});
    if (isMod) {
    plew_write((PlewString){"\"remainder by zero\", 17}); ", 27});
    }
    else {
    plew_write((PlewString){"\"division by zero\", 16}); ", 26});
    }
    if (signedTy) {
    if (isMod) {
    plew_write((PlewString){"(__dr == -1 ? 0 : __dl % __dr); })", 34});
    }
    else {
    plew_write((PlewString){"if (__dr == -1 && __dl == ", 26});
    plew_write(intMinMacro(&((*c)), tyStart, tyLen));
    plew_write((PlewString){") plew_panic((PlewString){\"integer overflow\", 16}); __dl / __dr; })", 67});
    }
    }
    else {
    if (isMod) {
    plew_write((PlewString){"__dl % __dr; })", 15});
    }
    else {
    plew_write((PlewString){"__dl / __dr; })", 15});
    }
    }
}
PlewString assignOpStr(int64_t op) {
    if (op == 49) {
    { PlewString __ret473 = (PlewString){" = ", 3};
    return __ret473; }
    }
    if (op == 67) {
    { PlewString __ret474 = (PlewString){" += ", 4};
    return __ret474; }
    }
    if (op == 68) {
    { PlewString __ret475 = (PlewString){" -= ", 4};
    return __ret475; }
    }
    if (op == 69) {
    { PlewString __ret476 = (PlewString){" *= ", 4};
    return __ret476; }
    }
    if (op == 70) {
    { PlewString __ret477 = (PlewString){" /= ", 4};
    return __ret477; }
    }
    if (op == 71) {
    { PlewString __ret478 = (PlewString){" %= ", 4};
    return __ret478; }
    }
    if (op == 80) {
    { PlewString __ret479 = (PlewString){" &= ", 4};
    return __ret479; }
    }
    if (op == 81) {
    { PlewString __ret480 = (PlewString){" |= ", 4};
    return __ret480; }
    }
    if (op == 82) {
    { PlewString __ret481 = (PlewString){" ^= ", 4};
    return __ret481; }
    }
    if (op == 83) {
    { PlewString __ret482 = (PlewString){" <<= ", 5};
    return __ret482; }
    }
    { PlewString __ret483 = (PlewString){" >>= ", 5};
    return __ret483; }
}
long long isCompoundDiv(int64_t op) {
    if (op == 70) {
    { long long __ret484 = 1;
    return __ret484; }
    }
    if (op == 71) {
    { long long __ret485 = 1;
    return __ret485; }
    }
    { long long __ret486 = 0;
    return __ret486; }
}
PlewString compoundDivFn(int64_t op) {
    if (op == 70) {
    { PlewString __ret487 = (PlewString){"plew_div(", 9};
    return __ret487; }
    }
    if (op == 71) {
    { PlewString __ret488 = (PlewString){"plew_mod(", 9};
    return __ret488; }
    }
    { PlewString __ret489 = (PlewString){"", 0};
    return __ret489; }
}
PlewString assignToBinStr(int64_t op) {
    if (op == 67) {
    { PlewString __ret490 = (PlewString){" + ", 3};
    return __ret490; }
    }
    if (op == 68) {
    { PlewString __ret491 = (PlewString){" - ", 3};
    return __ret491; }
    }
    if (op == 69) {
    { PlewString __ret492 = (PlewString){" * ", 3};
    return __ret492; }
    }
    if (op == 70) {
    { PlewString __ret493 = (PlewString){" / ", 3};
    return __ret493; }
    }
    if (op == 71) {
    { PlewString __ret494 = (PlewString){" % ", 3};
    return __ret494; }
    }
    if (op == 80) {
    { PlewString __ret495 = (PlewString){" & ", 3};
    return __ret495; }
    }
    if (op == 81) {
    { PlewString __ret496 = (PlewString){" | ", 3};
    return __ret496; }
    }
    if (op == 82) {
    { PlewString __ret497 = (PlewString){" ^ ", 3};
    return __ret497; }
    }
    if (op == 83) {
    { PlewString __ret498 = (PlewString){" << ", 4};
    return __ret498; }
    }
    { PlewString __ret499 = (PlewString){" >> ", 4};
    return __ret499; }
}
ConstInt notConst(void) {
    { ConstInt __ret500 = (ConstInt){.isConst = 0, .value = 0};
    return __ret500; }
}
ConstInt foldConst(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m501 = e;
    if (_m501.tag == 0) {
        int64_t value = _m501.data.Int.value;
        (void)value;
        long long isBool = _m501.data.Int.isBool;
        (void)isBool;
    if (isBool) {
    { ConstInt __ret502 = notConst();
    return __ret502; }
    }
    { ConstInt __ret503 = (ConstInt){.isConst = 1, .value = value};
    return __ret503; }
    }
    else if (_m501.tag == 2) {
        int64_t op = _m501.data.Unary.op;
        (void)op;
        uint64_t operand = _m501.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    ConstInt o = foldConst(&((*c)), operand);
    if (o.isConst) {
    { ConstInt __ret504 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_sub_overflow((0), (o.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret504; }
    }
    }
    { ConstInt __ret505 = notConst();
    return __ret505; }
    }
    else if (_m501.tag == 3) {
        int64_t op = _m501.data.Binary.op;
        (void)op;
        uint64_t lhs = _m501.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m501.data.Binary.rhs;
        (void)rhs;
    ConstInt a = foldConst(&((*c)), lhs);
    ConstInt b = foldConst(&((*c)), rhs);
    if (a.isConst) {
    if (b.isConst) {
    if (op == 56) {
    { ConstInt __ret506 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_add_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret506; }
    }
    if (op == 57) {
    { ConstInt __ret507 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_sub_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret507; }
    }
    if (op == 58) {
    { ConstInt __ret508 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_mul_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret508; }
    }
    }
    }
    { ConstInt __ret509 = notConst();
    return __ret509; }
    }
    else {
    { ConstInt __ret510 = notConst();
    return __ret510; }
    }
    }
}
long long tiIsInt(Comp* c, TypeInfo ti) {
    if (ti.kind == 0) {
    if (ti.nameLen != 0) {
    { long long __ret511 = isIntType(&((*c)), ti.nameStart, ti.nameLen);
    return __ret511; }
    }
    }
    { long long __ret512 = 0;
    return __ret512; }
}
void checkLitLeaf(Comp* c, int64_t value, uint64_t offset, long long isBool, uint64_t tyStart, uint64_t tyLen, uint64_t eKind, uint64_t eBits, long long eSgn) {
    if (isBool) {
    return;
    }
    if (tyLen != 0) {
    if (litFitsType(&((*c)), value, tyStart, tyLen)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), offset), (PlewString){"integer literal is out of range for its type", 44});
    }
    return;
    }
    if (eKind == 1) {
    if (litFitsBits(value, eBits, eSgn)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), offset), (PlewString){"integer literal is out of range for its type", 44});
    }
    return;
    }
    if (eKind == 0) {
    compileErrorAt(lineOf(&((*c)), offset), (PlewString){"integer literal has no type from context; add a type annotation or a suffix (e.g. `5I32`)", 89});
    }
}
void checkLitCtx(Comp* c, uint64_t id, uint64_t eKind, uint64_t eBits, long long eSgn) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m513 = e;
    if (_m513.tag == 0) {
        int64_t value = _m513.data.Int.value;
        (void)value;
        uint64_t offset = _m513.data.Int.offset;
        (void)offset;
        long long isBool = _m513.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m513.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m513.data.Int.tyLen;
        (void)tyLen;
    checkLitLeaf(&((*c)), value, offset, isBool, tyStart, tyLen, eKind, eBits, eSgn);
    }
    else if (_m513.tag == 2) {
        int64_t op = _m513.data.Unary.op;
        (void)op;
        uint64_t operand = _m513.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    Expr oe = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m514 = oe;
    if (_m514.tag == 0) {
        int64_t value = _m514.data.Int.value;
        (void)value;
        uint64_t offset = _m514.data.Int.offset;
        (void)offset;
        long long isBool = _m514.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m514.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m514.data.Int.tyLen;
        (void)tyLen;
    checkLitLeaf(&((*c)), ({ int64_t __ov; if (__builtin_sub_overflow((0), (value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), offset, isBool, tyStart, tyLen, eKind, eBits, eSgn);
    }
    else {
    checkLitCtx(&((*c)), operand, eKind, eBits, eSgn);
    }
    }
    }
    else {
    if (op == 79) {
    checkLitCtx(&((*c)), operand, eKind, eBits, eSgn);
    }
    }
    }
    else if (_m513.tag == 3) {
        int64_t op = _m513.data.Binary.op;
        (void)op;
        uint64_t lhs = _m513.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m513.data.Binary.rhs;
        (void)rhs;
    long long isArith = 0;
    if (op >= 56) {
    if (op <= 60) {
    isArith = 1;
    }
    }
    if (op >= 74) {
    if (op <= 78) {
    isArith = 1;
    }
    }
    if (isArith) {
    if (eKind == 1) {
    ConstInt cf = foldConst(&((*c)), id);
    if (cf.isConst) {
    if (litFitsBits(cf.value, eBits, eSgn)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), id)), (PlewString){"constant expression is out of range for its type", 48});
    }
    }
    checkLitCtx(&((*c)), lhs, eKind, eBits, eSgn);
    checkLitCtx(&((*c)), rhs, eKind, eBits, eSgn);
    }
    else {
    checkArithNoCtx(&((*c)), lhs, rhs);
    }
    }
    else {
    checkArithNoCtx(&((*c)), lhs, rhs);
    }
    }
    else if (_m513.tag == 4) {
        uint64_t nameStart = _m513.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m513.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m513.data.Call.args;
        (void)args;
    checkCallArgs(&((*c)), nameStart, nameLen, args);
    }
    else if (_m513.tag == 10) {
        uint64_t recv = _m513.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m513.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m513.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m513.data.Method.args;
        (void)args;
    checkMethodArgs(&((*c)), recv, nameStart, nameLen, args);
    }
    else if (_m513.tag == 11) {
        uint64_t operand = _m513.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m513.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m513.data.Cast.tyLen;
        (void)tyLen;
    Expr oe = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m515 = oe;
    if (_m515.tag == 0) {
    }
    else {
    checkLitCtx(&((*c)), operand, 0, 0, 0);
    }
    }
    }
    else if (_m513.tag == 5) {
        uint64_t base = _m513.data.Field.base;
        (void)base;
        uint64_t nameStart = _m513.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m513.data.Field.nameLen;
        (void)nameLen;
    checkLitCtx(&((*c)), base, 0, 0, 0);
    }
    else if (_m513.tag == 9) {
        uint64_t base = _m513.data.Index.base;
        (void)base;
        uint64_t index = _m513.data.Index.index;
        (void)index;
    checkLitCtx(&((*c)), base, 0, 0, 0);
    checkLitCtx(&((*c)), index, 1, 64, 0);
    }
    else if (_m513.tag == 6) {
        uint64_t typeStart = _m513.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m513.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m513.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m513.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m513.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m513.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m513.data.Make.fields;
        (void)fields;
    checkMakeFields(&((*c)), typeStart, typeLen, variantStart, variantLen, isEnum, ty, fields);
    }
    else if (_m513.tag == 8) {
        PlewArray_U64 elems = _m513.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    checkLitCtx(&((*c)), PlewArray_U64_get(elems, (long long)(i)), eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m513.tag == 12) {
        uint64_t scrut = _m513.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m513.data.MatchExpr.arms;
        (void)arms;
    checkLitCtx(&((*c)), scrut, 0, 0, 0);
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    checkLitCtx(&((*c)), PlewArray_MatchArm_get(arms, (long long)(i)).body, eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m513.tag == 14) {
        uint64_t opt = _m513.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m513.data.Coalesce.deflt;
        (void)deflt;
    checkLitCtx(&((*c)), opt, 0, 0, 0);
    checkLitCtx(&((*c)), deflt, eKind, eBits, eSgn);
    }
    else if (_m513.tag == 15) {
        uint64_t expr = _m513.data.Try.expr;
        (void)expr;
    checkLitCtx(&((*c)), expr, 0, 0, 0);
    }
    else {
    }
    }
}
IntTy exprIntTy(Comp* c, uint64_t id) {
    TypeInfo ti = exprType(&((*c)), id);
    if (tiIsInt(&((*c)), ti)) {
    { IntTy __ret516 = (IntTy){.known = 1, .bits = intBits(&((*c)), ti.nameStart, ti.nameLen), .sgn = intSigned(&((*c)), ti.nameStart, ti.nameLen)};
    return __ret516; }
    }
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m517 = e;
    if (_m517.tag == 4) {
        uint64_t nameStart = _m517.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m517.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m517.data.Call.args;
        (void)args;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argCount", 8})) {
    { IntTy __ret518 = (IntTy){.known = 1, .bits = 64, .sgn = 1};
    return __ret518; }
    }
    }
    else if (_m517.tag == 5) {
        uint64_t base = _m517.data.Field.base;
        (void)base;
        uint64_t nameStart = _m517.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m517.data.Field.nameLen;
        (void)nameLen;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"count", 5})) {
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    { IntTy __ret519 = (IntTy){.known = 1, .bits = 64, .sgn = 0};
    return __ret519; }
    }
    }
    }
    else if (_m517.tag == 9) {
        uint64_t base = _m517.data.Index.base;
        (void)base;
        uint64_t index = _m517.data.Index.index;
        (void)index;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    if (isIntType(&((*c)), bt.nameStart, bt.nameLen)) {
    { IntTy __ret520 = (IntTy){.known = 1, .bits = intBits(&((*c)), bt.nameStart, bt.nameLen), .sgn = intSigned(&((*c)), bt.nameStart, bt.nameLen)};
    return __ret520; }
    }
    }
    }
    else {
    }
    }
    { IntTy __ret521 = (IntTy){.known = 0, .bits = 0, .sgn = 0};
    return __ret521; }
}
void checkArithNoCtx(Comp* c, uint64_t lhs, uint64_t rhs) {
    IntTy lt = exprIntTy(&((*c)), lhs);
    if (lt.known) {
    checkLitCtx(&((*c)), lhs, 1, lt.bits, lt.sgn);
    checkLitCtx(&((*c)), rhs, 1, lt.bits, lt.sgn);
    return;
    }
    IntTy rt = exprIntTy(&((*c)), rhs);
    if (rt.known) {
    checkLitCtx(&((*c)), lhs, 1, rt.bits, rt.sgn);
    checkLitCtx(&((*c)), rhs, 1, rt.bits, rt.sgn);
    return;
    }
    checkLitCtx(&((*c)), lhs, 0, 0, 0);
    checkLitCtx(&((*c)), rhs, 0, 0, 0);
}
void checkLitTi(Comp* c, uint64_t id, TypeInfo ti) {
    if (tiIsInt(&((*c)), ti)) {
    checkLitCtx(&((*c)), id, 1, intBits(&((*c)), ti.nameStart, ti.nameLen), intSigned(&((*c)), ti.nameStart, ti.nameLen));
    return;
    }
    checkLitCtx(&((*c)), id, 0, 0, 0);
}
void checkLitSpan(Comp* c, uint64_t id, uint64_t tyStart, uint64_t tyLen, long long isArray) {
    if (isArray) {
    checkLitArray(&((*c)), id, tyStart, tyLen);
    return;
    }
    checkLitTi(&((*c)), id, typeInfoOfName(&((*c)), tyStart, tyLen, 0));
}
void checkLitArray(Comp* c, uint64_t id, uint64_t elemStart, uint64_t elemLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m522 = e;
    if (_m522.tag == 8) {
        PlewArray_U64 elems = _m522.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    checkLitSpan(&((*c)), PlewArray_U64_get(elems, (long long)(i)), elemStart, elemLen, 0);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else {
    checkLitCtx(&((*c)), id, 0, 0, 0);
    }
    }
}
void checkCallArgs(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t fi = findFunc(&((*c)), nameStart, nameLen);
    if (fi == (long long)(((*c).funcs).len)) {
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkLitCtx(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 1, 64, 1);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return;
    }
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    PlewArray_Param ps = PlewArray_Param_share(f.params);
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    if (i < (long long)((ps).len)) {
    Param p = PlewArray_Param_get(ps, (long long)(i));
    checkLitSpan(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, p.tyStart, p.tyLen, p.tyIsArray);
    }
    else {
    checkLitCtx(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 0, 0, 0);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param_release(ps);
    Func_release(f);
}
void checkMethodArgs(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    checkLitCtx(&((*c)), recv, 0, 0, 0);
    TypeInfo rt = exprType(&((*c)), recv);
    if (rt.kind == 2) {
    uint64_t mi = findMethod(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen);
    if (mi != (long long)(((*c).funcs).len)) {
    Func mf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(mi)));
    PlewArray_Param ps = PlewArray_Param_share(mf.params);
    long long genericRecv = isGenericInst(&((*c)), rt.ref);
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    if (i < (long long)((ps).len)) {
    Param p = PlewArray_Param_get(ps, (long long)(i));
    if (genericRecv) {
    TypeInfo pti = substTypeInfo(&((*c)), rt.ref, mf.typeParams, p.ty);
    checkLitTi(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, pti);
    }
    else {
    checkLitSpan(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, p.tyStart, p.tyLen, p.tyIsArray);
    }
    }
    else {
    checkLitCtx(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 0, 0, 0);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param_release(ps);
    Func_release(mf);
    return;
    PlewArray_Param_release(ps);
    Func_release(mf);
    }
    }
    if (rt.kind == 3) {
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"append", 6})) {
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkLitSpan(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, rt.nameStart, rt.nameLen, 0);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return;
    }
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkLitCtx(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 1, 64, 1);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
TypeInfo makeFieldType(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen) {
    if (isEnum) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef en = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual(&((*c)), en.nameStart, en.nameLen, typeStart, typeLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(en.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fj = 0;
    while (fj < (long long)((fs).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fs, (long long)(fj));
    if (spansEqual(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    { TypeInfo __ret523 = typeInfoOfName(&((*c)), fd.tyStart, fd.tyLen, fd.tyIsArray);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(en);
    return __ret523; }
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(en);
    }
    { TypeInfo __ret524 = scalarInfo();
    return __ret524; }
    }
    { TypeInfo __ret525 = fieldType(&((*c)), typeStart, typeLen, fieldStart, fieldLen);
    return __ret525; }
}
void checkMakeFields(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t ty, PlewArray_MakeField fields) {
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    TypeInfo ft = scalarInfo();
    if (isGenericEnumInst(&((*c)), ty)) {
    ft = genericEnumFieldTypeInfo(&((*c)), ty, variantStart, variantLen, mf.nameStart, mf.nameLen);
    }
    else {
    if (isGenericInst(&((*c)), ty)) {
    ft = genericFieldTypeInfo(&((*c)), ty, mf.nameStart, mf.nameLen);
    }
    else {
    ft = makeFieldType(&((*c)), typeStart, typeLen, variantStart, variantLen, isEnum, mf.nameStart, mf.nameLen);
    }
    }
    if (ft.kind == 3) {
    checkLitArray(&((*c)), mf.value, ft.nameStart, ft.nameLen);
    }
    else {
    checkLitTi(&((*c)), mf.value, ft);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void genExpr(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m526 = e;
    if (_m526.tag == 0) {
        int64_t value = _m526.data.Int.value;
        (void)value;
    writeInt(value);
    }
    else if (_m526.tag == 1) {
        uint64_t start = _m526.data.Ident.start;
        (void)start;
        uint64_t len = _m526.data.Ident.len;
        (void)len;
    if (isInoutLocal(&((*c)), start, len)) {
    plew_write((PlewString){"(*", 2});
    writeSpan(&((*c)), start, len);
    plew_write((PlewString){")", 1});
    }
    else {
    writeSpan(&((*c)), start, len);
    }
    }
    else if (_m526.tag == 2) {
        int64_t op = _m526.data.Unary.op;
        (void)op;
        uint64_t operand = _m526.data.Unary.operand;
        (void)operand;
    long long negChecked = 0;
    if (op == 57) {
    TypeInfo ot = exprType(&((*c)), operand);
    if (ot.kind == 0) {
    if (isIntType(&((*c)), ot.nameStart, ot.nameLen)) {
    if (intSigned(&((*c)), ot.nameStart, ot.nameLen)) {
    genCheckedNeg(&((*c)), operand, ot.nameStart, ot.nameLen);
    negChecked = 1;
    }
    }
    }
    }
    if (negChecked) {
    }
    else {
    plew_write(unaryOpStr(op));
    plew_write((PlewString){"(", 1});
    genExpr(&((*c)), operand);
    plew_write((PlewString){")", 1});
    }
    }
    else if (_m526.tag == 3) {
        int64_t op = _m526.data.Binary.op;
        (void)op;
        uint64_t lhs = _m526.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m526.data.Binary.rhs;
        (void)rhs;
    if (isStringEq(&((*c)), op, lhs)) {
    if (op == 51) {
    plew_write((PlewString){"(!PlewString_eq(", 16});
    }
    else {
    plew_write((PlewString){"PlewString_eq(", 14});
    }
    genExpr(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr(&((*c)), rhs);
    if (op == 51) {
    plew_write((PlewString){"))", 2});
    }
    else {
    plew_write((PlewString){")", 1});
    }
    }
    else {
    if (isEnumEq(&((*c)), op, lhs)) {
    emitEnumTagCmp(&((*c)), lhs, rhs, op, 1);
    }
    else {
    if (compareNeedsTrait(&((*c)), op, lhs)) {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), lhs)), (PlewString){"comparison needs Eq/Ord; not available for a struct or array", 60});
    }
    else {
    if (op == 59) {
    TypeInfo dt = arithIntType(&((*c)), lhs, rhs);
    if (dt.nameLen > 0) {
    genCheckedDiv(&((*c)), lhs, rhs, dt.nameStart, dt.nameLen, 0);
    }
    else {
    plew_write((PlewString){"plew_div(", 9});
    genExpr(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    if (op == 60) {
    TypeInfo mt = arithIntType(&((*c)), lhs, rhs);
    if (mt.nameLen > 0) {
    genCheckedDiv(&((*c)), lhs, rhs, mt.nameStart, mt.nameLen, 1);
    }
    else {
    plew_write((PlewString){"plew_mod(", 9});
    genExpr(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    TypeInfo at = arithIntType(&((*c)), lhs, rhs);
    if (isCheckedArith(op)) {
    if (at.nameLen > 0) {
    genCheckedArith(&((*c)), op, lhs, rhs, at.nameStart, at.nameLen);
    }
    else {
    plew_write((PlewString){"(", 1});
    genExpr(&((*c)), lhs);
    plew_write(binOpStr(op));
    genExpr(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    plew_write((PlewString){"(", 1});
    genExpr(&((*c)), lhs);
    plew_write(binOpStr(op));
    genExpr(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    }
    }
    }
    }
    }
    else if (_m526.tag == 4) {
        uint64_t nameStart = _m526.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m526.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m526.data.Call.args;
        (void)args;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"write", 5})) {
    if ((*c).impWrite) {
    plew_write((PlewString){"plew_write(", 11});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"write is not ambient; import it from @Std/Io", 44});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"writeByte", 9})) {
    if ((*c).impWriteByte) {
    plew_write((PlewString){"putchar((int)(", 14});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"writeByte is not ambient; import it from @Std/Io", 48});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"eprint", 6})) {
    if ((*c).impEprint) {
    plew_write((PlewString){"plew_eprint(", 12});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"eprint is not ambient; import it from @Std/Io", 45});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"exit", 4})) {
    if ((*c).impExit) {
    plew_write((PlewString){"exit((int)(", 11});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"exit is not ambient; import it from @Std/Process", 48});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readStdin", 9})) {
    if ((*c).impReadStdin) {
    plew_write((PlewString){"plew_read_stdin()", 17});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"readStdin is not ambient; import it from @Std/Io", 48});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFile", 8})) {
    if ((*c).impReadFile) {
    plew_write((PlewString){"plew_read_file(", 15});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"readFile is not ambient; import it from @Std/Io", 47});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFileBytes", 13})) {
    if ((*c).impReadFile) {
    plew_write((PlewString){"plew_read_file_bytes(", 21});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"readFile is not ambient; import it from @Std/Io", 47});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"fileExists", 10})) {
    if ((*c).impFileExists) {
    plew_write((PlewString){"plew_file_exists(", 17});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"fileExists is not ambient; import it from @Std/Io", 49});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argCount", 8})) {
    if ((*c).impArgCount) {
    plew_write((PlewString){"plew_arg_count()", 16});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"argCount is not ambient; import it from @Std/Process", 52});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argAt", 5})) {
    if ((*c).impArgAt) {
    plew_write((PlewString){"plew_arg_at((long long)(", 24});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"argAt is not ambient; import it from @Std/Process", 49});
    }
    return;
    }
    if (callLabelsOk(&((*c)), nameStart, nameLen, args)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"argument labels do not match the function parameters", 52});
    return;
    }
    writeSpan(&((*c)), nameStart, nameLen);
    plew_write((PlewString){"(", 1});
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    Arg ar = PlewArray_Arg_get(args, (long long)(i));
    if (ar.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr(&((*c)), ar.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr(&((*c)), ar.expr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t cfi = findFunc(&((*c)), nameStart, nameLen);
    if (cfi == (long long)(((*c).funcs).len)) {
    }
    else {
    Func cf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(cfi)));
    PlewArray_Param cps = PlewArray_Param_share(cf.params);
    uint64_t di = (long long)((args).len);
    while (di < (long long)((cps).len)) {
    if (di > 0) {
    plew_write((PlewString){", ", 2});
    }
    genExpr(&((*c)), PlewArray_Param_get(cps, (long long)(di)).defaultExpr);
    di = ({ uint64_t __ov; if (__builtin_add_overflow((di), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param_release(cps);
    Func_release(cf);
    }
    plew_write((PlewString){")", 1});
    }
    else if (_m526.tag == 5) {
        uint64_t base = _m526.data.Field.base;
        (void)base;
        uint64_t nameStart = _m526.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m526.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 1) {
    plew_write((PlewString){"({ PlewString __s = ", 20});
    genExpr(&((*c)), base);
    plew_write((PlewString){"; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; })", 67});
    return;
    }
    if (bt.kind == 3) {
    plew_write((PlewString){"(long long)((", 13});
    genExpr(&((*c)), base);
    plew_write((PlewString){").len)", 6});
    return;
    }
    genExpr(&((*c)), base);
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), nameStart, nameLen);
    }
    else if (_m526.tag == 7) {
        uint64_t start = _m526.data.Str.start;
        (void)start;
        uint64_t len = _m526.data.Str.len;
        (void)len;
    plew_write((PlewString){"(PlewString){\"", 14});
    writeSpan(&((*c)), ({ uint64_t __ov; if (__builtin_add_overflow((start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), ({ uint64_t __ov; if (__builtin_sub_overflow((len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    plew_write((PlewString){"\", ", 3});
    writeInt(strDecodedLen(&((*c)), start, len));
    plew_write((PlewString){"}", 1});
    }
    else if (_m526.tag == 9) {
        uint64_t base = _m526.data.Index.base;
        (void)base;
        uint64_t index = _m526.data.Index.index;
        (void)index;
    TypeInfo bt = exprType(&((*c)), base);
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_get(", 5});
    genExpr(&((*c)), base);
    plew_write((PlewString){", (long long)(", 14});
    genExpr(&((*c)), index);
    plew_write((PlewString){"))", 2});
    }
    else if (_m526.tag == 16) {
        uint64_t base = _m526.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m526.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m526.data.Arrow.nameLen;
        (void)nameLen;
    plew_write((PlewString){"(", 1});
    genExpr(&((*c)), base);
    plew_write((PlewString){")->", 3});
    writeSpan(&((*c)), nameStart, nameLen);
    }
    else if (_m526.tag == 17) {
        PlewArray_Param params = _m526.data.Closure.params;
        (void)params;
        long long hasRet = _m526.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m526.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m526.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m526.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m526.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m526.data.Closure.body;
        (void)body;
    plew_write((PlewString){"__closure", 9});
    writeU64(id);
    }
    else if (_m526.tag == 10) {
        uint64_t recv = _m526.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m526.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m526.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m526.data.Method.args;
        (void)args;
    TypeInfo bt = exprType(&((*c)), recv);
    if (bt.kind == 3) {
    if (placeIsMutable(&((*c)), recv)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), recv)), (PlewString){"cannot mutate an immutable binding; declare it with `mut val`", 61});
    return;
    }
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_push(&(", 8});
    genExpr(&((*c)), recv);
    plew_write((PlewString){"), ", 3});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    uint64_t mi = findMethod(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    if (mi == (long long)(((*c).funcs).len)) {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"no such method on this type", 27});
    return;
    }
    Func mf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(mi)));
    if (paramsLabelsOk(&((*c)), mf.params, args)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"argument labels do not match the method parameters", 50});
    Func_release(mf);
    return;
    }
    if (mf.selfInout) {
    if (placeIsMutable(&((*c)), recv)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), recv)), (PlewString){"cannot call an `inout fn` method on an immutable binding; declare it with `mut val`", 83});
    Func_release(mf);
    return;
    }
    }
    if (isGenericInst(&((*c)), bt.ref)) {
    emitMangle(&((*c)), bt.ref);
    }
    else {
    writeSpan(&((*c)), bt.nameStart, bt.nameLen);
    }
    plew_write((PlewString){"_", 1});
    writeSpan(&((*c)), nameStart, nameLen);
    plew_write((PlewString){"(", 1});
    if (mf.selfInout) {
    plew_write((PlewString){"&(", 2});
    genExpr(&((*c)), recv);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr(&((*c)), recv);
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    plew_write((PlewString){", ", 2});
    Arg ar = PlewArray_Arg_get(args, (long long)(i));
    if (ar.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr(&((*c)), ar.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr(&((*c)), ar.expr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){")", 1});
    Func_release(mf);
    }
    }
    else if (_m526.tag == 8) {
        PlewArray_U64 elems = _m526.data.Array.elems;
        (void)elems;
    plew_write((PlewString){"0", 1});
    }
    else if (_m526.tag == 11) {
        uint64_t operand = _m526.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m526.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m526.data.Cast.tyLen;
        (void)tyLen;
    if (isIntType(&((*c)), tyStart, tyLen)) {
    Expr opE = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m527 = opE;
    if (_m527.tag == 0) {
        int64_t value = _m527.data.Int.value;
        (void)value;
        uint64_t offset = _m527.data.Int.offset;
        (void)offset;
    if (litFitsType(&((*c)), value, tyStart, tyLen)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), offset), (PlewString){"integer literal is out of range for the target type of `as`", 59});
    return;
    }
    }
    else {
    TypeInfo st = exprType(&((*c)), operand);
    if (isIntType(&((*c)), st.nameStart, st.nameLen)) {
    if (losslessInt(&((*c)), st.nameStart, st.nameLen, tyStart, tyLen)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), operand)), (PlewString){"`as` would lose information (narrowing or signedness change); use a fallible TryFrom conversion", 95});
    return;
    }
    }
    }
    }
    }
    plew_write((PlewString){"((", 2});
    genCElem(&((*c)), tyStart, tyLen);
    plew_write((PlewString){")(", 2});
    genExpr(&((*c)), operand);
    plew_write((PlewString){"))", 2});
    }
    else if (_m526.tag == 6) {
        uint64_t typeStart = _m526.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m526.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m526.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m526.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m526.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m526.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m526.data.Make.fields;
        (void)fields;
    if (isRefInst(&((*c)), ty)) {
    TypeRef rt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ty)));
    uint64_t t2 = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    plew_write((PlewString){"({ ", 3});
    emitConcreteCType(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){"* __ref", 7});
    writeU64(t2);
    plew_write((PlewString){" = (", 4});
    emitConcreteCType(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){"*)malloc(sizeof(", 16});
    emitConcreteCType(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){")); *__ref", 10});
    writeU64(t2);
    plew_write((PlewString){" = (", 4});
    if ((long long)((fields).len) > 0) {
    genExpr(&((*c)), PlewArray_MakeField_get(fields, (long long)(0)).value);
    }
    else {
    plew_write((PlewString){"0", 1});
    }
    plew_write((PlewString){"); __ref", 8});
    writeU64(t2);
    plew_write((PlewString){"; })", 4});
    TypeRef_release(rt);
    return;
    TypeRef_release(rt);
    }
    if (isEnum) {
    plew_write((PlewString){"(", 1});
    if (isGenericEnumInst(&((*c)), ty)) {
    emitConcreteCType(&((*c)), ty);
    }
    else {
    writeSpan(&((*c)), typeStart, typeLen);
    }
    plew_write((PlewString){"){.tag = ", 9});
    writeU64(variantIndex(&((*c)), typeStart, typeLen, variantStart, variantLen));
    if ((long long)((fields).len) > 0) {
    plew_write((PlewString){", .data.", 8});
    writeSpan(&((*c)), variantStart, variantLen);
    plew_write((PlewString){" = {", 4});
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), mf.nameStart, mf.nameLen);
    plew_write((PlewString){" = ", 3});
    TypeInfo eft = scalarInfo();
    if (isGenericEnumInst(&((*c)), ty)) {
    eft = genericEnumFieldTypeInfo(&((*c)), ty, variantStart, variantLen, mf.nameStart, mf.nameLen);
    }
    else {
    eft = makeFieldType(&((*c)), typeStart, typeLen, variantStart, variantLen, 1, mf.nameStart, mf.nameLen);
    }
    if (eft.kind == 3) {
    genArrayValue(&((*c)), mf.value, eft.nameStart, eft.nameLen);
    }
    else {
    genExpr(&((*c)), mf.value);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"}", 1});
    }
    plew_write((PlewString){"}", 1});
    }
    else {
    long long generic = isGenericInst(&((*c)), ty);
    plew_write((PlewString){"(", 1});
    if (generic) {
    emitConcreteCType(&((*c)), ty);
    }
    else {
    genCType(&((*c)), typeStart, typeLen);
    }
    plew_write((PlewString){"){", 2});
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), mf.nameStart, mf.nameLen);
    plew_write((PlewString){" = ", 3});
    TypeInfo ft = scalarInfo();
    if (generic) {
    ft = genericFieldTypeInfo(&((*c)), ty, mf.nameStart, mf.nameLen);
    }
    else {
    ft = fieldType(&((*c)), typeStart, typeLen, mf.nameStart, mf.nameLen);
    }
    if (ft.kind == 3) {
    genArrayValue(&((*c)), mf.value, ft.nameStart, ft.nameLen);
    }
    else {
    genExpr(&((*c)), mf.value);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"}", 1});
    }
    }
    else if (_m526.tag == 12) {
        uint64_t scrut = _m526.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m526.data.MatchExpr.arms;
        (void)arms;
    if (matchExhaustive(&((*c)), arms)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), scrut)), (PlewString){"match must be exhaustive: cover all variants or add a wildcard", 62});
    return;
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo rt = exprType(&((*c)), PlewArray_MatchArm_get(arms, (long long)(0)).body);
    uint64_t scrutRef = exprType(&((*c)), scrut).ref;
    long long genericMatch = isGenericEnumInst(&((*c)), scrutRef);
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    long long hasWildcard = 0;
    uint64_t q = 0;
    while (q < (long long)((arms).len)) {
    MatchArm aq = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(q)));
    if (aq.isWildcard) {
    hasWildcard = 1;
    }
    else {
    if (enumLen == 0) {
    enumStart = aq.enumStart;
    enumLen = aq.enumLen;
    }
    }
    q = ({ uint64_t __ov; if (__builtin_add_overflow((q), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(aq);
    }
    plew_write((PlewString){"({ ", 3});
    genTypeInfoCType(&((*c)), rt);
    plew_write((PlewString){" __mr", 5});
    writeU64(t);
    plew_write((PlewString){"; ", 2});
    if (genericMatch) {
    emitMangle(&((*c)), scrutRef);
    }
    else {
    writeSpan(&((*c)), enumStart, enumLen);
    }
    plew_write((PlewString){" __ms", 5});
    writeU64(t);
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), scrut);
    plew_write((PlewString){"; ", 2});
    uint64_t i = 0;
    long long firstCond = 1;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    plew_write((PlewString){"else { __mr", 11});
    writeU64(t);
    plew_write((PlewString){" = (", 4});
    genExpr(&((*c)), a.body);
    plew_write((PlewString){"); } ", 5});
    }
    else {
    if (firstCond) {
    plew_write((PlewString){"if (__ms", 8});
    firstCond = 0;
    }
    else {
    plew_write((PlewString){"else if (__ms", 13});
    }
    writeU64(t);
    plew_write((PlewString){".tag == ", 8});
    writeU64(variantIndex(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen));
    plew_write((PlewString){") { ", 4});
    PlewArray_Bind binds = PlewArray_Bind_share(a.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).len)) {
    Bind bd = PlewArray_Bind_get(binds, (long long)(bi));
    if (genericMatch) {
    genBindTypeInst(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    else {
    genBindType(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = __ms", 7});
    writeU64(t);
    plew_write((PlewString){".data.", 6});
    writeSpan(&((*c)), a.variantStart, a.variantLen);
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), bd.fieldStart, bd.fieldLen);
    plew_write((PlewString){"; (void)", 8});
    writeSpan(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){"; ", 2});
    if (genericMatch) {
    TypeInfo bti = genericEnumFieldTypeInfo(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    addLocal(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0, 0);
    }
    else {
    addBindLocal(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"__mr", 4});
    writeU64(t);
    plew_write((PlewString){" = (", 4});
    genExpr(&((*c)), a.body);
    plew_write((PlewString){"); } ", 5});
    PlewArray_Bind_release(binds);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    if (hasWildcard) {
    }
    else {
    plew_write((PlewString){"else { __builtin_unreachable(); } ", 34});
    }
    plew_write((PlewString){"__mr", 4});
    writeU64(t);
    plew_write((PlewString){"; })", 4});
    }
    else if (_m526.tag == 13) {
        uint64_t cond = _m526.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m526.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m526.data.IfExpr.elseBlk;
        (void)elseBlk;
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t g = blockGiveExpr(&((*c)), thenBlk);
    TypeInfo rt = scalarInfo();
    if (g < (long long)(((*c).exprs).len)) {
    rt = exprType(&((*c)), g);
    }
    plew_write((PlewString){"({ ", 3});
    genTypeInfoCType(&((*c)), rt);
    plew_write((PlewString){" __r", 4});
    writeU64(t);
    plew_write((PlewString){"; if (", 6});
    genCond(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    uint64_t save = (*c).curGiveTmp;
    (*c).curGiveTmp = ({ uint64_t __ov; if (__builtin_add_overflow((t), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    genBlock(&((*c)), thenBlk);
    plew_write((PlewString){"    } else {\n", 13});
    genBlock(&((*c)), elseBlk);
    (*c).curGiveTmp = save;
    plew_write((PlewString){"    } __r", 9});
    writeU64(t);
    plew_write((PlewString){"; })", 4});
    }
    else if (_m526.tag == 14) {
        uint64_t opt = _m526.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m526.data.Coalesce.deflt;
        (void)deflt;
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo ot = exprType(&((*c)), opt);
    plew_write((PlewString){"({ ", 3});
    if (isGenericInst(&((*c)), ot.ref)) {
    emitMangle(&((*c)), ot.ref);
    }
    else {
    genTypeInfoCType(&((*c)), ot);
    }
    plew_write((PlewString){" __c", 4});
    writeU64(t);
    plew_write((PlewString){" = (", 4});
    genExpr(&((*c)), opt);
    plew_write((PlewString){"); __c", 6});
    writeU64(t);
    plew_write((PlewString){".tag == 0 ? __c", 15});
    writeU64(t);
    plew_write((PlewString){".data.Some.v : (", 16});
    genExpr(&((*c)), deflt);
    plew_write((PlewString){"); })", 5});
    }
    else if (_m526.tag == 15) {
        uint64_t expr = _m526.data.Try.expr;
        (void)expr;
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo et = exprType(&((*c)), expr);
    plew_write((PlewString){"({ ", 3});
    if (isGenericInst(&((*c)), et.ref)) {
    emitMangle(&((*c)), et.ref);
    }
    else {
    genTypeInfoCType(&((*c)), et);
    }
    plew_write((PlewString){" __t", 4});
    writeU64(t);
    plew_write((PlewString){" = (", 4});
    genExpr(&((*c)), expr);
    plew_write((PlewString){"); if (__t", 10});
    writeU64(t);
    plew_write((PlewString){".tag == 1) { return (", 21});
    emitMangle(&((*c)), (*c).curRetTy);
    plew_write((PlewString){"){.tag = 1, .data.Err.error = __t", 33});
    writeU64(t);
    plew_write((PlewString){".data.Err.error}; } __t", 23});
    writeU64(t);
    plew_write((PlewString){".data.Ok.value; })", 18});
    }
    else { __builtin_unreachable(); }
    }
}
long long isPlaceExpr(Comp* c, uint64_t id) {
    {
    Expr _m528 = PlewArray_Expr_get((*c).exprs, (long long)(id));
    if (_m528.tag == 1) {
        uint64_t start = _m528.data.Ident.start;
        (void)start;
        uint64_t len = _m528.data.Ident.len;
        (void)len;
    { long long __ret529 = 1;
    return __ret529; }
    }
    else if (_m528.tag == 5) {
        uint64_t base = _m528.data.Field.base;
        (void)base;
        uint64_t nameStart = _m528.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m528.data.Field.nameLen;
        (void)nameLen;
    { long long __ret530 = 1;
    return __ret530; }
    }
    else if (_m528.tag == 9) {
        uint64_t base = _m528.data.Index.base;
        (void)base;
        uint64_t index = _m528.data.Index.index;
        (void)index;
    { long long __ret531 = 1;
    return __ret531; }
    }
    else {
    { long long __ret532 = 0;
    return __ret532; }
    }
    }
}
void genArrayValue(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen) {
    if (isPlaceExpr(&((*c)), exprId)) {
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_share(", 7});
    genExpr(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    genArrayLiteral(&((*c)), exprId, elemStart, elemLen);
}
void genArrayLiteral(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(exprId));
    {
    Expr _m533 = e;
    if (_m533.tag == 8) {
        PlewArray_U64 elems = _m533.data.Array.elems;
        (void)elems;
    if ((long long)((elems).len) == 0) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new()", 6});
    }
    else {
    plew_write((PlewString){"({ PlewArray_", 13});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" __a = PlewArray_", 17});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new(); ", 8});
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(&__a, ", 12});
    genExpr(&((*c)), PlewArray_U64_get(elems, (long long)(i)));
    plew_write((PlewString){"); ", 3});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"__a; })", 7});
    }
    }
    else {
    genExpr(&((*c)), exprId);
    }
    }
}
long long isStringEq(Comp* c, int64_t op, uint64_t lhs) {
    if (op == 50) {
    }
    else {
    if (op == 51) {
    }
    else {
    { long long __ret534 = 0;
    return __ret534; }
    }
    }
    TypeInfo lt = exprType(&((*c)), lhs);
    { long long __ret535 = (lt.kind == 1);
    return __ret535; }
}
long long isEnumName(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, start, len)) {
    { long long __ret536 = 1;
    EnumDef_release(e);
    return __ret536; }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret537 = 0;
    return __ret537; }
}
long long isAllNullary(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, start, len)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if ((long long)((v.fields).len) > 0) {
    { long long __ret538 = 0;
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret538; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { long long __ret539 = 1;
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret539; }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret540 = 0;
    return __ret540; }
}
long long isEnumEq(Comp* c, int64_t op, uint64_t lhs) {
    if (op == 50) {
    }
    else {
    if (op == 51) {
    }
    else {
    { long long __ret541 = 0;
    return __ret541; }
    }
    }
    TypeInfo lt = exprType(&((*c)), lhs);
    if (lt.kind == 2) {
    { long long __ret542 = isEnumName(&((*c)), lt.nameStart, lt.nameLen);
    return __ret542; }
    }
    { long long __ret543 = 0;
    return __ret543; }
}
long long compareNeedsTrait(Comp* c, int64_t op, uint64_t lhs) {
    if (op < 50) {
    { long long __ret544 = 0;
    return __ret544; }
    }
    if (op > 55) {
    { long long __ret545 = 0;
    return __ret545; }
    }
    TypeInfo lt = exprType(&((*c)), lhs);
    if (lt.kind == 3) {
    { long long __ret546 = 1;
    return __ret546; }
    }
    if (lt.kind == 2) {
    if (isEnumName(&((*c)), lt.nameStart, lt.nameLen)) {
    { long long __ret547 = 0;
    return __ret547; }
    }
    { long long __ret548 = 1;
    return __ret548; }
    }
    { long long __ret549 = 0;
    return __ret549; }
}
void emitEnumOperand(Comp* c, uint64_t id, uint64_t enStart, uint64_t enLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m550 = e;
    if (_m550.tag == 6) {
        uint64_t typeStart = _m550.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m550.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m550.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m550.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m550.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m550.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m550.data.Make.fields;
        (void)fields;
    if (isEnum) {
    writeU64(variantIndex(&((*c)), enStart, enLen, variantStart, variantLen));
    return;
    }
    }
    else {
    }
    }
    plew_write((PlewString){"(", 1});
    genExpr(&((*c)), id);
    plew_write((PlewString){").tag", 5});
}
void emitEnumTagCmp(Comp* c, uint64_t lhs, uint64_t rhs, int64_t op, long long outer) {
    TypeInfo lt = exprType(&((*c)), lhs);
    uint64_t enStart = 0;
    uint64_t enLen = 0;
    if (lt.kind == 2) {
    enStart = lt.nameStart;
    enLen = lt.nameLen;
    }
    else {
    TypeInfo rt = exprType(&((*c)), rhs);
    enStart = rt.nameStart;
    enLen = rt.nameLen;
    }
    if (isAllNullary(&((*c)), enStart, enLen)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), lhs)), (PlewString){"enum == needs structural Eq for payload variants (only all-nullary enums compare by tag)", 88});
    return;
    }
    if (outer) {
    plew_write((PlewString){"(", 1});
    }
    emitEnumOperand(&((*c)), lhs, enStart, enLen);
    if (op == 51) {
    plew_write((PlewString){" != ", 4});
    }
    else {
    plew_write((PlewString){" == ", 4});
    }
    emitEnumOperand(&((*c)), rhs, enStart, enLen);
    if (outer) {
    plew_write((PlewString){")", 1});
    }
}
void genCond(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m551 = e;
    if (_m551.tag == 3) {
        int64_t op = _m551.data.Binary.op;
        (void)op;
        uint64_t lhs = _m551.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m551.data.Binary.rhs;
        (void)rhs;
    if (isStringEq(&((*c)), op, lhs)) {
    genExpr(&((*c)), id);
    }
    else {
    if (isEnumEq(&((*c)), op, lhs)) {
    emitEnumTagCmp(&((*c)), lhs, rhs, op, 0);
    }
    else {
    if (compareNeedsTrait(&((*c)), op, lhs)) {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), lhs)), (PlewString){"comparison needs Eq/Ord; not available for a struct or array", 60});
    }
    else {
    genExpr(&((*c)), lhs);
    plew_write(binOpStr(op));
    genExpr(&((*c)), rhs);
    }
    }
    }
    }
    else {
    genExpr(&((*c)), id);
    }
    }
}
void genStmt(Comp* c, uint64_t id) {
    Stmt s = PlewArray_Stmt_get((*c).stmts, (long long)(id));
    {
    Stmt _m552 = s;
    if (_m552.tag == 0) {
        long long mutable = _m552.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m552.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m552.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m552.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m552.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m552.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m552.data.Let.ty;
        (void)ty;
        uint64_t init = _m552.data.Let.init;
        (void)init;
    checkLitSpan(&((*c)), init, tyStart, tyLen, tyIsArray);
    plew_write((PlewString){"    ", 4});
    genCTypeOf(&((*c)), ty, tyStart, tyLen, tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), nameStart, nameLen);
    plew_write((PlewString){" = ", 3});
    if (tyIsArray) {
    genArrayValue(&((*c)), init, tyStart, tyLen);
    }
    else {
    genCopyValue(&((*c)), init, ty, tyStart, tyLen, 0);
    }
    plew_write((PlewString){";\n", 2});
    addLocal(&((*c)), nameStart, nameLen, tyStart, tyLen, tyIsArray, ty, 0, mutable, 1);
    }
    else if (_m552.tag == 1) {
        int64_t op = _m552.data.Assign.op;
        (void)op;
        uint64_t target = _m552.data.Assign.target;
        (void)target;
        uint64_t value = _m552.data.Assign.value;
        (void)value;
    Expr te = PlewArray_Expr_get((*c).exprs, (long long)(target));
    {
    Expr _m553 = te;
    if (_m553.tag == 9) {
        uint64_t base = _m553.data.Index.base;
        (void)base;
        uint64_t index = _m553.data.Index.index;
        (void)index;
    if (placeIsMutable(&((*c)), base)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), base)), (PlewString){"cannot assign to an element of an immutable binding; declare it with `mut val`", 78});
    return;
    }
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    checkLitSpan(&((*c)), value, bt.nameStart, bt.nameLen, 0);
    }
    plew_write((PlewString){"    PlewArray_", 14});
    writeSpan(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_set(&(", 7});
    genExpr(&((*c)), base);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr(&((*c)), index);
    plew_write((PlewString){"), ", 3});
    if (op == 49) {
    genExpr(&((*c)), value);
    }
    else {
    int64_t cbin = compoundCheckedBin(op);
    long long elemInt = isIntType(&((*c)), bt.nameStart, bt.nameLen);
    if (isCompoundDiv(op)) {
    plew_write(compoundDivFn(op));
    genArrayGet(&((*c)), base, index, bt.nameStart, bt.nameLen);
    plew_write((PlewString){", ", 2});
    genExpr(&((*c)), value);
    plew_write((PlewString){")", 1});
    }
    else {
    long long checkedElem = 0;
    if (cbin != 0) {
    if (elemInt) {
    checkedElem = 1;
    }
    }
    if (checkedElem) {
    plew_write((PlewString){"({ ", 3});
    genCElem(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){" __ov; if (", 11});
    plew_write(overflowBuiltin(cbin));
    plew_write((PlewString){"((", 2});
    genArrayGet(&((*c)), base, index, bt.nameStart, bt.nameLen);
    plew_write((PlewString){"), (", 4});
    genExpr(&((*c)), value);
    plew_write((PlewString){"), &__ov)) plew_panic((PlewString){\"integer overflow\", 16}); __ov; })", 69});
    }
    else {
    genArrayGet(&((*c)), base, index, bt.nameStart, bt.nameLen);
    plew_write(assignToBinStr(op));
    genExpr(&((*c)), value);
    }
    }
    }
    plew_write((PlewString){");\n", 3});
    }
    else {
    if (placeIsMutable(&((*c)), target)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), target)), (PlewString){"cannot assign to an immutable place; the binding and field must be declared `mut val`", 85});
    return;
    }
    TypeInfo ctt = exprType(&((*c)), target);
    if (ctt.kind == 3) {
    checkLitArray(&((*c)), value, ctt.nameStart, ctt.nameLen);
    }
    else {
    checkLitTi(&((*c)), value, ctt);
    }
    plew_write((PlewString){"    ", 4});
    genExpr(&((*c)), target);
    if (isCompoundDiv(op)) {
    plew_write((PlewString){" = ", 3});
    TypeInfo dt = exprType(&((*c)), target);
    if (dt.kind == 0) {
    if (isIntType(&((*c)), dt.nameStart, dt.nameLen)) {
    genCheckedDiv(&((*c)), target, value, dt.nameStart, dt.nameLen, (op == 71));
    }
    else {
    plew_write(compoundDivFn(op));
    genExpr(&((*c)), target);
    plew_write((PlewString){", ", 2});
    genExpr(&((*c)), value);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    plew_write(compoundDivFn(op));
    genExpr(&((*c)), target);
    plew_write((PlewString){", ", 2});
    genExpr(&((*c)), value);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    TypeInfo tt = exprType(&((*c)), target);
    int64_t cbin = compoundCheckedBin(op);
    long long checked = 0;
    if (cbin != 0) {
    if (tt.kind == 0) {
    if (isIntType(&((*c)), tt.nameStart, tt.nameLen)) {
    checked = 1;
    }
    }
    }
    if (checked) {
    plew_write((PlewString){" = ", 3});
    genCheckedArith(&((*c)), cbin, target, value, tt.nameStart, tt.nameLen);
    }
    else {
    plew_write(assignOpStr(op));
    if (op == 49) {
    genCopyValue(&((*c)), value, tt.ref, tt.nameStart, tt.nameLen, (tt.kind == 3));
    }
    else {
    genExpr(&((*c)), value);
    }
    }
    }
    plew_write((PlewString){";\n", 2});
    }
    }
    }
    else if (_m552.tag == 2) {
        uint64_t expr = _m552.data.Print.expr;
        (void)expr;
        uint64_t offset = _m552.data.Print.offset;
        (void)offset;
    if ((*c).impPrint) {
    checkLitCtx(&((*c)), expr, 1, 64, 1);
    plew_write((PlewString){"    printf(\"%lld\\n\", (long long)(", 33});
    genExpr(&((*c)), expr);
    plew_write((PlewString){"));\n", 4});
    }
    else {
    compileErrorAt(lineOf(&((*c)), offset), (PlewString){"print is not ambient; import it from @Std/Io", 44});
    }
    }
    else if (_m552.tag == 3) {
        uint64_t expr = _m552.data.ExprStmt.expr;
        (void)expr;
    checkLitCtx(&((*c)), expr, 0, 0, 0);
    plew_write((PlewString){"    ", 4});
    genExpr(&((*c)), expr);
    plew_write((PlewString){";\n", 2});
    }
    else if (_m552.tag == 4) {
        uint64_t value = _m552.data.Return.value;
        (void)value;
        long long hasValue = _m552.data.Return.hasValue;
        (void)hasValue;
    if ((*c).curIsMain) {
    emitScopeDrops(&((*c)), 0);
    plew_write((PlewString){"    return 0;\n", 14});
    }
    else {
    if ((*c).curRetVoid) {
    emitScopeDrops(&((*c)), 0);
    plew_write((PlewString){"    return;\n", 12});
    }
    else {
    if (hasValue) {
    checkLitSpan(&((*c)), value, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    }
    uint64_t rt = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    plew_write((PlewString){"    { ", 6});
    genCTypeOf(&((*c)), (*c).curRetTy, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    plew_write((PlewString){" __ret", 6});
    writeU64(rt);
    plew_write((PlewString){" = ", 3});
    if (hasValue) {
    genCopyValue(&((*c)), value, (*c).curRetTy, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    }
    else {
    plew_write((PlewString){"0", 1});
    }
    plew_write((PlewString){";\n", 2});
    emitScopeDrops(&((*c)), 0);
    plew_write((PlewString){"    return __ret", 16});
    writeU64(rt);
    plew_write((PlewString){"; }\n", 4});
    }
    }
    }
    else if (_m552.tag == 5) {
        uint64_t cond = _m552.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m552.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m552.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m552.data.If.hasElse;
        (void)hasElse;
    checkLitCtx(&((*c)), cond, 0, 0, 0);
    plew_write((PlewString){"    if (", 8});
    genCond(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    genBlock(&((*c)), thenBlk);
    plew_write((PlewString){"    }\n", 6});
    if (hasElse) {
    plew_write((PlewString){"    else {\n", 11});
    genBlock(&((*c)), elseBlk);
    plew_write((PlewString){"    }\n", 6});
    }
    }
    else if (_m552.tag == 6) {
        uint64_t cond = _m552.data.While.cond;
        (void)cond;
        uint64_t body = _m552.data.While.body;
        (void)body;
    checkLitCtx(&((*c)), cond, 0, 0, 0);
    plew_write((PlewString){"    while (", 11});
    genCond(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n", 6});
    }
    else if (_m552.tag == 7) {
        uint64_t varStart = _m552.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m552.data.For.varLen;
        (void)varLen;
        long long isRange = _m552.data.For.isRange;
        (void)isRange;
        long long inclusive = _m552.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m552.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m552.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m552.data.For.body;
        (void)body;
    if (isRange) {
    checkArithNoCtx(&((*c)), iter, rangeHi);
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t forMark = scopeMark(&((*c)));
    if (isRange) {
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    long long __fe", 18});
    writeU64(t);
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), rangeHi);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"    for (long long ", 19});
    writeSpan(&((*c)), varStart, varLen);
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), iter);
    plew_write((PlewString){"; ", 2});
    writeSpan(&((*c)), varStart, varLen);
    if (inclusive) {
    plew_write((PlewString){" <= __fe", 8});
    }
    else {
    plew_write((PlewString){" < __fe", 7});
    }
    writeU64(t);
    plew_write((PlewString){"; ", 2});
    writeSpan(&((*c)), varStart, varLen);
    plew_write((PlewString){"++) {\n", 6});
    addLocal(&((*c)), varStart, varLen, 0, 0, 0, 0, 0, 0, 0);
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    else {
    TypeInfo et = exprType(&((*c)), iter);
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    ", 4});
    wPA(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){" __fa", 5});
    writeU64(t);
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), iter);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"    for (long long __fi", 23});
    writeU64(t);
    plew_write((PlewString){" = 0; __fi", 10});
    writeU64(t);
    plew_write((PlewString){" < __fa", 7});
    writeU64(t);
    plew_write((PlewString){".len; __fi", 10});
    writeU64(t);
    plew_write((PlewString){"++) {\n", 6});
    plew_write((PlewString){"        ", 8});
    genCElem(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), varStart, varLen);
    plew_write((PlewString){" = ", 3});
    wPA(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"_get(__fa", 9});
    writeU64(t);
    plew_write((PlewString){", __fi", 6});
    writeU64(t);
    plew_write((PlewString){");\n", 3});
    addLocal(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0, 0, 0, 0);
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    scopeExit(&((*c)), forMark);
    }
    else if (_m552.tag == 9) {
        uint64_t msg = _m552.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m552.data.Panic.offset;
        (void)offset;
    plew_write((PlewString){"    plew_panic(", 15});
    genExpr(&((*c)), msg);
    plew_write((PlewString){");\n", 3});
    }
    else if (_m552.tag == 10) {
        uint64_t value = _m552.data.Give.value;
        (void)value;
    if ((*c).curGiveTmp != 0) {
    plew_write((PlewString){"    __r", 7});
    writeU64(({ uint64_t __ov; if (__builtin_sub_overflow(((*c).curGiveTmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    plew_write((PlewString){" = (", 4});
    genExpr(&((*c)), value);
    plew_write((PlewString){");\n", 3});
    }
    }
    else if (_m552.tag == 11) {
    plew_write((PlewString){"    break;\n", 11});
    }
    else if (_m552.tag == 12) {
    plew_write((PlewString){"    continue;\n", 14});
    }
    else if (_m552.tag == 8) {
        uint64_t scrut = _m552.data.Match.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m552.data.Match.arms;
        (void)arms;
    if (matchExhaustive(&((*c)), arms)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), scrut)), (PlewString){"match must be exhaustive: cover all variants or add a wildcard", 62});
    return;
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t scrutRef = exprType(&((*c)), scrut).ref;
    long long genericMatch = isGenericEnumInst(&((*c)), scrutRef);
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    long long hasWildcard = 0;
    uint64_t q = 0;
    while (q < (long long)((arms).len)) {
    MatchArm aq = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(q)));
    if (aq.isWildcard) {
    hasWildcard = 1;
    }
    else {
    if (enumLen == 0) {
    enumStart = aq.enumStart;
    enumLen = aq.enumLen;
    }
    }
    q = ({ uint64_t __ov; if (__builtin_add_overflow((q), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(aq);
    }
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    ", 4});
    if (genericMatch) {
    emitMangle(&((*c)), scrutRef);
    }
    else {
    writeSpan(&((*c)), enumStart, enumLen);
    }
    plew_write((PlewString){" _m", 3});
    writeU64(t);
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), scrut);
    plew_write((PlewString){";\n", 2});
    uint64_t i = 0;
    long long firstCond = 1;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    plew_write((PlewString){"    else {\n", 11});
    genBlock(&((*c)), a.body);
    plew_write((PlewString){"    }\n", 6});
    }
    else {
    if (firstCond) {
    plew_write((PlewString){"    if (_m", 10});
    firstCond = 0;
    }
    else {
    plew_write((PlewString){"    else if (_m", 15});
    }
    writeU64(t);
    plew_write((PlewString){".tag == ", 8});
    writeU64(variantIndex(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen));
    plew_write((PlewString){") {\n", 4});
    uint64_t armMark = scopeMark(&((*c)));
    PlewArray_Bind binds = PlewArray_Bind_share(a.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).len)) {
    Bind bd = PlewArray_Bind_get(binds, (long long)(bi));
    plew_write((PlewString){"        ", 8});
    if (genericMatch) {
    genBindTypeInst(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    else {
    genBindType(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = _m", 5});
    writeU64(t);
    plew_write((PlewString){".data.", 6});
    writeSpan(&((*c)), a.variantStart, a.variantLen);
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), bd.fieldStart, bd.fieldLen);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"        (void)", 14});
    writeSpan(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){";\n", 2});
    if (genericMatch) {
    TypeInfo bti = genericEnumFieldTypeInfo(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    addLocal(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0, 0);
    }
    else {
    addBindLocal(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genBlock(&((*c)), a.body);
    scopeExit(&((*c)), armMark);
    plew_write((PlewString){"    }\n", 6});
    PlewArray_Bind_release(binds);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    if (hasWildcard) {
    }
    else {
    plew_write((PlewString){"    else { __builtin_unreachable(); }\n", 38});
    }
    plew_write((PlewString){"    }\n", 6});
    }
    else { __builtin_unreachable(); }
    }
}
void genBlock(Comp* c, uint64_t id) {
    uint64_t mark = scopeMark(&((*c)));
    Block b = Block_share(PlewArray_Block_get((*c).blocks, (long long)(id)));
    PlewArray_U64 stmts = PlewArray_U64_share(b.stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).len)) {
    genStmt(&((*c)), PlewArray_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scopeExit(&((*c)), mark);
    PlewArray_U64_release(stmts);
    Block_release(b);
}
long long nameIsMain(Comp* c, Func f) {
    if (f.hasRecv) {
    { long long __ret554 = 0;
    return __ret554; }
    }
    { long long __ret555 = rangeEquals((*c).bytes, f.nameStart, f.nameLen, (PlewString){"main", 4});
    return __ret555; }
}
uint64_t structIndexByName(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(i)));
    if ((long long)((s.typeParams).len) == 0) {
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, start, len)) {
    { uint64_t __ret556 = i;
    StructDef_release(s);
    return __ret556; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { uint64_t __ret557 = (long long)(((*c).structs).len);
    return __ret557; }
}
long long structNeedsCopy(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret558 = 0;
    return __ret558; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    { long long __ret559 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret559; }
    }
    else {
    if (structNeedsCopy(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret560 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret560; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret561 = 0;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret561; }
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void emitStructCopyProto(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void emitStructCopyDef(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) { ", 6});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    plew_write((PlewString){" r.", 3});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    wPA(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_copy(s.", 8});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    else {
    if (structNeedsCopy(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" r.", 3});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    writeSpan(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_copy(s.", 8});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" return r; }\n", 13});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void emitStructShareProto(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void emitStructShareDef(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) {", 5});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    plew_write((PlewString){" plew_arc_retain(s.", 19});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){".rc);", 5});
    }
    else {
    if (structNeedsCopy(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_share(s.", 9});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" return s; }\n", 13});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void emitStructReleaseProto(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"void ", 5});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void emitStructReleaseDef(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"void ", 5});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) {", 5});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    plew_write((PlewString){" ", 1});
    wPA(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_release(s.", 11});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    else {
    if (structNeedsCopy(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_release(s.", 11});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" }\n", 3});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
long long monoStructNeedsCopy(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret562 = 0;
    TypeRef_release(t);
    return __ret562; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    TypeInfo ti = substTypeInfo(&((*c)), instRef, s.typeParams, PlewArray_FieldDef_get(fields, (long long)(i)).ty);
    if (ti.kind == 3) {
    { long long __ret563 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret563; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret564 = 0;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret564; }
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
void emitMonoStructCopyProto(Comp* c, uint64_t instRef) {
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" s);\n", 5});
}
void emitMonoStructCopyDef(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    TypeRef_release(t);
    return;
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" s) { ", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    TypeInfo ti = substTypeInfo(&((*c)), instRef, s.typeParams, f.ty);
    if (ti.kind == 3) {
    plew_write((PlewString){" r.", 3});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    wPA(&((*c)), ti.nameStart, ti.nameLen);
    plew_write((PlewString){"_copy(s.", 8});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" return r; }\n", 13});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
long long monoEnumNeedsCopy(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    { long long __ret565 = 0;
    TypeRef_release(t);
    return __ret565; }
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(PlewArray_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    TypeInfo ti = substTypeInfo(&((*c)), instRef, e.typeParams, PlewArray_FieldDef_get(fs, (long long)(fi)).ty);
    if (ti.kind == 3) {
    { long long __ret566 = 1;
    PlewArray_FieldDef_release(fs);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret566; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_FieldDef_release(fs);
    }
    { long long __ret567 = 0;
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret567; }
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
void emitMonoEnumCopyProto(Comp* c, uint64_t instRef) {
    emitMonoStructCopyProto(&((*c)), instRef);
}
void emitMonoEnumCopyDef(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    TypeRef_release(t);
    return;
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" s) { ", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    long long anyArray = 0;
    uint64_t ck = 0;
    while (ck < (long long)((fs).len)) {
    TypeInfo cti = substTypeInfo(&((*c)), instRef, e.typeParams, PlewArray_FieldDef_get(fs, (long long)(ck)).ty);
    if (cti.kind == 3) {
    anyArray = 1;
    }
    ck = ({ uint64_t __ov; if (__builtin_add_overflow((ck), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (anyArray) {
    plew_write((PlewString){" if (r.tag == ", 14});
    writeU64(vi);
    plew_write((PlewString){") {", 3});
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    TypeInfo ti = substTypeInfo(&((*c)), instRef, e.typeParams, f.ty);
    if (ti.kind == 3) {
    plew_write((PlewString){" r.data.", 8});
    writeSpan(&((*c)), v.nameStart, v.nameLen);
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    wPA(&((*c)), ti.nameStart, ti.nameLen);
    plew_write((PlewString){"_copy(s.data.", 13});
    writeSpan(&((*c)), v.nameStart, v.nameLen);
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" }", 2});
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    }
    plew_write((PlewString){" return r; }\n", 13});
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
void genStructValue(Comp* c, uint64_t exprId, uint64_t structStart, uint64_t structLen) {
    if (isPlaceExpr(&((*c)), exprId)) {
    if (structNeedsCopy(&((*c)), structStart, structLen)) {
    writeSpan(&((*c)), structStart, structLen);
    plew_write((PlewString){"_share(", 7});
    genExpr(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    }
    genExpr(&((*c)), exprId);
}
void genCopyValue(Comp* c, uint64_t exprId, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray) {
    if (isArray) {
    genArrayValue(&((*c)), exprId, fallStart, fallLen);
    return;
    }
    if (isGenericInst(&((*c)), tyRef)) {
    long long needs = 0;
    if (isGenericEnumInst(&((*c)), tyRef)) {
    needs = monoEnumNeedsCopy(&((*c)), tyRef);
    }
    else {
    needs = monoStructNeedsCopy(&((*c)), tyRef);
    }
    if (needs) {
    if (isPlaceExpr(&((*c)), exprId)) {
    emitMangle(&((*c)), tyRef);
    plew_write((PlewString){"_copy(", 6});
    genExpr(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    }
    genExpr(&((*c)), exprId);
    return;
    }
    genStructValue(&((*c)), exprId, fallStart, fallLen);
}
void genStructDef(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"struct ", 7});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" {\n", 3});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    plew_write((PlewString){"    ", 4});
    genCTypeOf(&((*c)), f.ty, f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";\n", 2});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"};\n", 3});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void genSignature(Comp* c, Func f) {
    if (nameIsMain(&((*c)), f)) {
    plew_write((PlewString){"int main(int argc, char** argv)", 31});
    return;
    }
    if (f.hasRet) {
    genCTypeOf(&((*c)), f.retTy, f.retStart, f.retLen, f.retIsArray);
    plew_write((PlewString){" ", 1});
    }
    else {
    plew_write((PlewString){"void ", 5});
    }
    if (f.hasRecv) {
    if ((*c).curRecvInstRef != 0) {
    emitMangle(&((*c)), (*c).curRecvInstRef);
    }
    else {
    writeSpan(&((*c)), f.recvStart, f.recvLen);
    }
    plew_write((PlewString){"_", 1});
    }
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){"(", 1});
    PlewArray_Param params = PlewArray_Param_share(f.params);
    if (f.hasRecv) {
    if ((*c).curRecvInstRef != 0) {
    emitConcreteCType(&((*c)), (*c).curRecvInstRef);
    }
    else {
    genCTypeRef(&((*c)), f.recvStart, f.recvLen, 0);
    }
    if (f.selfInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" self", 5});
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    plew_write((PlewString){", ", 2});
    Param p = PlewArray_Param_get(params, (long long)(i));
    genCTypeOf(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), p.nameStart, p.nameLen);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else {
    if ((long long)((params).len) == 0) {
    plew_write((PlewString){"void", 4});
    }
    else {
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    Param p = PlewArray_Param_get(params, (long long)(i));
    genCTypeOf(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), p.nameStart, p.nameLen);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    plew_write((PlewString){")", 1});
    PlewArray_Param_release(params);
}
void genFunc(Comp* c, uint64_t fi) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    long long isMain = nameIsMain(&((*c)), f);
    (*c).curIsMain = isMain;
    if (f.hasRet) {
    (*c).curRetVoid = 0;
    (*c).curRetStart = f.retStart;
    (*c).curRetLen = f.retLen;
    (*c).curRetIsArray = f.retIsArray;
    (*c).curRetTy = f.retTy;
    }
    else {
    (*c).curRetVoid = 1;
    (*c).curRetStart = 0;
    (*c).curRetLen = 0;
    (*c).curRetIsArray = 0;
    (*c).curRetTy = 0;
    }
    (*c).curHasRecv = f.hasRecv;
    (*c).curRecvStart = f.recvStart;
    (*c).curRecvLen = f.recvLen;
    (*c).curSelfInout = f.selfInout;
    (*c).locals = PlewArray_Local_new();
    PlewArray_Param params = PlewArray_Param_share(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((params).len)) {
    Param p = PlewArray_Param_get(params, (long long)(pi));
    addLocal(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genSignature(&((*c)), f);
    plew_write((PlewString){" {\n", 3});
    if (isMain) {
    plew_write((PlewString){"    plew_argc = argc; plew_argv = argv;\n", 40});
    }
    genBlock(&((*c)), f.body);
    if (isMain) {
    plew_write((PlewString){"    return 0;\n", 14});
    }
    plew_write((PlewString){"}\n", 2});
    PlewArray_Param_release(params);
    Func_release(f);
}
void genClosure(Comp* c, uint64_t id, long long proto) {
    {
    Expr _m568 = PlewArray_Expr_get((*c).exprs, (long long)(id));
    if (_m568.tag == 17) {
        PlewArray_Param params = _m568.data.Closure.params;
        (void)params;
        long long hasRet = _m568.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m568.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m568.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m568.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m568.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m568.data.Closure.body;
        (void)body;
    if (hasRet) {
    (*c).curRetVoid = 0;
    (*c).curRetStart = retStart;
    (*c).curRetLen = retLen;
    (*c).curRetIsArray = retIsArray;
    (*c).curRetTy = retTy;
    genCTypeOf(&((*c)), retTy, retStart, retLen, retIsArray);
    }
    else {
    (*c).curRetVoid = 1;
    (*c).curRetStart = 0;
    (*c).curRetLen = 0;
    (*c).curRetIsArray = 0;
    (*c).curRetTy = 0;
    plew_write((PlewString){"void", 4});
    }
    plew_write((PlewString){" __closure", 10});
    writeU64(id);
    plew_write((PlewString){"(", 1});
    if ((long long)((params).len) == 0) {
    plew_write((PlewString){"void", 4});
    }
    else {
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    Param p = PlewArray_Param_get(params, (long long)(i));
    genCTypeOf(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), p.nameStart, p.nameLen);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    plew_write((PlewString){")", 1});
    if (proto) {
    plew_write((PlewString){";\n", 2});
    }
    else {
    (*c).curIsMain = 0;
    (*c).curHasRecv = 0;
    (*c).locals = PlewArray_Local_new();
    uint64_t pj = 0;
    while (pj < (long long)((params).len)) {
    Param p2 = PlewArray_Param_get(params, (long long)(pj));
    addLocal(&((*c)), p2.nameStart, p2.nameLen, p2.tyStart, p2.tyLen, p2.tyIsArray, p2.ty, p2.isInout, 0, 0);
    pj = ({ uint64_t __ov; if (__builtin_add_overflow((pj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" {\n", 3});
    genBlock(&((*c)), body);
    plew_write((PlewString){"}\n", 2});
    }
    }
    else {
    }
    }
}
void emitClosures(Comp* c, long long proto) {
    uint64_t i = 0;
    while (i < (long long)(((*c).exprs).len)) {
    {
    Expr _m569 = PlewArray_Expr_get((*c).exprs, (long long)(i));
    if (_m569.tag == 17) {
        PlewArray_Param params = _m569.data.Closure.params;
        (void)params;
        long long hasRet = _m569.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m569.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m569.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m569.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m569.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m569.data.Closure.body;
        (void)body;
    genClosure(&((*c)), i, proto);
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void genEnumDef(Comp* c, uint64_t ei) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    plew_write((PlewString){"struct ", 7});
    writeSpan(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" {\n", 3});
    plew_write((PlewString){"    long long tag;\n", 19});
    plew_write((PlewString){"    union {\n", 12});
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    plew_write((PlewString){"        struct {", 16});
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    if ((long long)((fs).len) == 0) {
    plew_write((PlewString){" char _u; ", 10});
    }
    else {
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    plew_write((PlewString){" ", 1});
    genCTypeOf(&((*c)), f.ty, f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";", 1});
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" ", 1});
    }
    plew_write((PlewString){"} ", 2});
    writeSpan(&((*c)), v.nameStart, v.nameLen);
    plew_write((PlewString){";\n", 2});
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    }
    plew_write((PlewString){"    } data;\n", 12});
    plew_write((PlewString){"};\n", 3});
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
}
uint64_t genericStructIndex(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(i)));
    if ((long long)((s.typeParams).len) > 0) {
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, nameStart, nameLen)) {
    { uint64_t __ret570 = i;
    StructDef_release(s);
    return __ret570; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { uint64_t __ret571 = (long long)(((*c).structs).len);
    return __ret571; }
}
uint64_t genericEnumIndex(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(i)));
    if ((long long)((e.typeParams).len) > 0) {
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, nameStart, nameLen)) {
    { uint64_t __ret572 = i;
    EnumDef_release(e);
    return __ret572; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret573 = (long long)(((*c).enums).len);
    return __ret573; }
}
long long isGenericInst(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret574 = 0;
    return __ret574; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) == 0) {
    { long long __ret575 = 0;
    TypeRef_release(t);
    return __ret575; }
    }
    if (genericStructIndex(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).structs).len)) {
    { long long __ret576 = 1;
    TypeRef_release(t);
    return __ret576; }
    }
    { long long __ret577 = (genericEnumIndex(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).len));
    TypeRef_release(t);
    return __ret577; }
    TypeRef_release(t);
}
long long isFnType(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret578 = 0;
    return __ret578; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    { long long __ret579 = rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"fn", 2});
    TypeRef_release(t);
    return __ret579; }
    TypeRef_release(t);
}
long long isRefInst(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret580 = 0;
    return __ret580; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) != 1) {
    { long long __ret581 = 0;
    TypeRef_release(t);
    return __ret581; }
    }
    { long long __ret582 = rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Ref", 3});
    TypeRef_release(t);
    return __ret582; }
    TypeRef_release(t);
}
long long isGenericEnumInst(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret583 = 0;
    return __ret583; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) == 0) {
    { long long __ret584 = 0;
    TypeRef_release(t);
    return __ret584; }
    }
    { long long __ret585 = (genericEnumIndex(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).len));
    TypeRef_release(t);
    return __ret585; }
    TypeRef_release(t);
}
long long typeRefEq(Comp* c, uint64_t a, uint64_t b) {
    if (a == b) {
    { long long __ret586 = 1;
    return __ret586; }
    }
    TypeRef ta = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(a)));
    TypeRef tb = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(b)));
    if (spansEqual(&((*c)), ta.nameStart, ta.nameLen, tb.nameStart, tb.nameLen)) {
    }
    else {
    { long long __ret587 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret587; }
    }
    if ((long long)((ta.args).len) != (long long)((tb.args).len)) {
    { long long __ret588 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret588; }
    }
    uint64_t i = 0;
    while (i < (long long)((ta.args).len)) {
    if (typeRefEq(&((*c)), PlewArray_U64_get(ta.args, (long long)(i)), PlewArray_U64_get(tb.args, (long long)(i)))) {
    }
    else {
    { long long __ret589 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret589; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret590 = 1;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret590; }
    TypeRef_release(tb);
    TypeRef_release(ta);
}
void emitMangle(Comp* c, uint64_t ref) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(resolveTy(&((*c)), ref))));
    writeSpan(&((*c)), t.nameStart, t.nameLen);
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    plew_write((PlewString){"_", 1});
    emitMangle(&((*c)), PlewArray_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(t);
}
void emitConcreteCType(Comp* c, uint64_t ref) {
    uint64_t r = resolveTy(&((*c)), ref);
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(r)));
    if ((long long)((t.args).len) == 0) {
    genCElem(&((*c)), t.nameStart, t.nameLen);
    TypeRef_release(t);
    return;
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    plew_write((PlewString){"PlewArray_", 10});
    emitMangle(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    TypeRef_release(t);
    return;
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Ref", 3})) {
    emitConcreteCType(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    plew_write((PlewString){"*", 1});
    TypeRef_release(t);
    return;
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"fn", 2})) {
    emitMangle(&((*c)), r);
    TypeRef_release(t);
    return;
    }
    emitMangle(&((*c)), r);
    TypeRef_release(t);
}
void emitFieldCType(Comp* c, uint64_t ref, PlewArray_Bind params, PlewArray_U64 args) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    uint64_t pi = 0;
    while (pi < (long long)((params).len)) {
    Bind p = PlewArray_Bind_get(params, (long long)(pi));
    if (spansEqual(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    emitConcreteCType(&((*c)), PlewArray_U64_get(args, (long long)(pi)));
    TypeRef_release(t);
    return;
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    emitConcreteCType(&((*c)), ref);
    TypeRef_release(t);
}
uint64_t resolveTy(Comp* c, uint64_t tyRef) {
    if (tyRef >= (long long)(((*c).types).len)) {
    { uint64_t __ret591 = tyRef;
    return __ret591; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(tyRef)));
    if ((long long)((t.args).len) == 0) {
    uint64_t i = 0;
    while (i < (long long)(((*c).curTypeParams).len)) {
    Bind p = PlewArray_Bind_get((*c).curTypeParams, (long long)(i));
    if (spansEqual(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    { uint64_t __ret592 = PlewArray_U64_get((*c).curTypeArgs, (long long)(i));
    TypeRef_release(t);
    return __ret592; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    { uint64_t __ret593 = tyRef;
    TypeRef_release(t);
    return __ret593; }
    TypeRef_release(t);
}
void genCTypeOf(Comp* c, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray) {
    if (isArray) {
    genCTypeRef(&((*c)), fallStart, fallLen, 1);
    return;
    }
    uint64_t rt = resolveTy(&((*c)), tyRef);
    if (rt != tyRef) {
    emitConcreteCType(&((*c)), rt);
    return;
    }
    if (isGenericInst(&((*c)), tyRef)) {
    emitConcreteCType(&((*c)), tyRef);
    return;
    }
    if (isRefInst(&((*c)), tyRef)) {
    emitConcreteCType(&((*c)), tyRef);
    return;
    }
    if (isFnType(&((*c)), tyRef)) {
    emitConcreteCType(&((*c)), tyRef);
    return;
    }
    genCTypeRef(&((*c)), fallStart, fallLen, 0);
}
long long isTypeParamName(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    PlewArray_Bind tp = PlewArray_Bind_share(PlewArray_StructDef_get((*c).structs, (long long)(si)).typeParams);
    uint64_t k = 0;
    while (k < (long long)((tp).len)) {
    if (spansEqual(&((*c)), PlewArray_Bind_get(tp, (long long)(k)).nameStart, PlewArray_Bind_get(tp, (long long)(k)).nameLen, start, len)) {
    { long long __ret594 = 1;
    PlewArray_Bind_release(tp);
    return __ret594; }
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_Bind_release(tp);
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    PlewArray_Bind tp2 = PlewArray_Bind_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)).typeParams);
    uint64_t k2 = 0;
    while (k2 < (long long)((tp2).len)) {
    if (spansEqual(&((*c)), PlewArray_Bind_get(tp2, (long long)(k2)).nameStart, PlewArray_Bind_get(tp2, (long long)(k2)).nameLen, start, len)) {
    { long long __ret595 = 1;
    PlewArray_Bind_release(tp2);
    return __ret595; }
    }
    k2 = ({ uint64_t __ov; if (__builtin_add_overflow((k2), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_Bind_release(tp2);
    }
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    PlewArray_Bind tp3 = PlewArray_Bind_share(PlewArray_Func_get((*c).funcs, (long long)(fi)).typeParams);
    uint64_t k3 = 0;
    while (k3 < (long long)((tp3).len)) {
    if (spansEqual(&((*c)), PlewArray_Bind_get(tp3, (long long)(k3)).nameStart, PlewArray_Bind_get(tp3, (long long)(k3)).nameLen, start, len)) {
    { long long __ret596 = 1;
    PlewArray_Bind_release(tp3);
    return __ret596; }
    }
    k3 = ({ uint64_t __ov; if (__builtin_add_overflow((k3), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_Bind_release(tp3);
    }
    { long long __ret597 = 0;
    return __ret597; }
}
long long tyRefIsGround(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret598 = 1;
    return __ret598; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if (isTypeParamName(&((*c)), t.nameStart, t.nameLen)) {
    { long long __ret599 = 0;
    TypeRef_release(t);
    return __ret599; }
    }
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    if (tyRefIsGround(&((*c)), PlewArray_U64_get(t.args, (long long)(i)))) {
    }
    else {
    { long long __ret600 = 0;
    TypeRef_release(t);
    return __ret600; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret601 = 1;
    TypeRef_release(t);
    return __ret601; }
    TypeRef_release(t);
}
void registerArrayElemRef(Comp* c, uint64_t elemRef) {
    if (elemRef >= (long long)(((*c).types).len)) {
    return;
    }
    TypeRef e = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(elemRef)));
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind ae = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual(&((*c)), ae.nameStart, ae.nameLen, e.nameStart, e.nameLen)) {
    TypeRef_release(e);
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Bind_push(&((*c).arrayElems), (Bind){.nameStart = e.nameStart, .nameLen = e.nameLen, .fieldStart = e.nameStart, .fieldLen = e.nameLen});
    TypeRef_release(e);
}
void scanType(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return;
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    scanType(&((*c)), PlewArray_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((t.args).len) == 1) {
    registerArrayElemRef(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    }
    }
    if (isFnType(&((*c)), ref)) {
    uint64_t fj = 0;
    long long seen = 0;
    while (fj < (long long)(((*c).fnTypes).len)) {
    if (typeRefEq(&((*c)), PlewArray_U64_get((*c).fnTypes, (long long)(fj)), ref)) {
    seen = 1;
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (seen) {
    }
    else {
    PlewArray_U64_push(&((*c).fnTypes), ref);
    }
    }
    if (isGenericInst(&((*c)), ref)) {
    if (tyRefIsGround(&((*c)), ref)) {
    uint64_t j = 0;
    while (j < (long long)(((*c).genInsts).len)) {
    if (typeRefEq(&((*c)), PlewArray_U64_get((*c).genInsts, (long long)(j)), ref)) {
    TypeRef_release(t);
    return;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U64_push(&((*c).genInsts), ref);
    }
    }
    TypeRef_release(t);
}
void collectGenInsts(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if ((long long)((f.typeParams).len) > 0) {
    }
    else {
    if (f.hasRet) {
    scanType(&((*c)), f.retTy);
    }
    PlewArray_Param ps = PlewArray_Param_share(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((ps).len)) {
    scanType(&((*c)), PlewArray_Param_get(ps, (long long)(pi)).ty);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param_release(ps);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    if ((long long)((s.typeParams).len) == 0) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(s.fields);
    uint64_t k = 0;
    while (k < (long long)((fs).len)) {
    scanType(&((*c)), PlewArray_FieldDef_get(fs, (long long)(k)).ty);
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if ((long long)((e.typeParams).len) == 0) {
    PlewArray_Variant vs = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vs).len)) {
    PlewArray_FieldDef vfs = PlewArray_FieldDef_share(PlewArray_Variant_get(vs, (long long)(vi)).fields);
    uint64_t k = 0;
    while (k < (long long)((vfs).len)) {
    scanType(&((*c)), PlewArray_FieldDef_get(vfs, (long long)(k)).ty);
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_FieldDef_release(vfs);
    }
    PlewArray_Variant_release(vs);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    uint64_t sti = 0;
    while (sti < (long long)(((*c).stmts).len)) {
    {
    Stmt _m602 = PlewArray_Stmt_get((*c).stmts, (long long)(sti));
    if (_m602.tag == 0) {
        uint64_t ty = _m602.data.Let.ty;
        (void)ty;
    scanType(&((*c)), ty);
    }
    else {
    }
    }
    sti = ({ uint64_t __ov; if (__builtin_add_overflow((sti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t xi = 0;
    while (xi < (long long)(((*c).exprs).len)) {
    {
    Expr _m603 = PlewArray_Expr_get((*c).exprs, (long long)(xi));
    if (_m603.tag == 11) {
        uint64_t operand = _m603.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m603.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m603.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m603.data.Cast.ty;
        (void)ty;
    scanType(&((*c)), ty);
    }
    else if (_m603.tag == 6) {
        uint64_t typeStart = _m603.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m603.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m603.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m603.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m603.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m603.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m603.data.Make.fields;
        (void)fields;
    scanType(&((*c)), ty);
    }
    else {
    }
    }
    xi = ({ uint64_t __ov; if (__builtin_add_overflow((xi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
TypeInfo typeInfoOfRef(Comp* c, uint64_t ref) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) == 0) {
    { TypeInfo __ret604 = typeInfoOfName(&((*c)), t.nameStart, t.nameLen, 0);
    TypeRef_release(t);
    return __ret604; }
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    TypeRef el = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(PlewArray_U64_get(t.args, (long long)(0)))));
    { TypeInfo __ret605 = typeInfoOfName(&((*c)), el.nameStart, el.nameLen, 1);
    TypeRef_release(el);
    TypeRef_release(t);
    return __ret605; }
    TypeRef_release(el);
    }
    { TypeInfo __ret606 = typeInfoOfName(&((*c)), t.nameStart, t.nameLen, 0);
    TypeRef_release(t);
    return __ret606; }
    TypeRef_release(t);
}
TypeInfo substTypeInfo(Comp* c, uint64_t instRef, PlewArray_Bind params, uint64_t tyRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(tyRef)));
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    Bind p = PlewArray_Bind_get(params, (long long)(i));
    if (spansEqual(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    if (i < (long long)((inst.args).len)) {
    { TypeInfo __ret607 = typeInfoOfRef(&((*c)), PlewArray_U64_get(inst.args, (long long)(i)));
    TypeRef_release(inst);
    TypeRef_release(t);
    return __ret607; }
    }
    TypeRef_release(inst);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret608 = typeInfoOfRef(&((*c)), tyRef);
    TypeRef_release(t);
    return __ret608; }
    TypeRef_release(t);
}
TypeInfo genericFieldTypeInfo(Comp* c, uint64_t instRef, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    { TypeInfo __ret609 = scalarInfo();
    TypeRef_release(t);
    return __ret609; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fields, (long long)(i));
    if (spansEqual(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(fd.ty)));
    uint64_t pi = 0;
    while (pi < (long long)((s.typeParams).len)) {
    Bind p = PlewArray_Bind_get(s.typeParams, (long long)(pi));
    if (spansEqual(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    { TypeInfo __ret610 = typeInfoOfRef(&((*c)), PlewArray_U64_get(t.args, (long long)(pi)));
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret610; }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret611 = typeInfoOfRef(&((*c)), fd.ty);
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret611; }
    TypeRef_release(ftr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret612 = scalarInfo();
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret612; }
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
TypeInfo genericEnumFieldTypeInfo(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    { TypeInfo __ret613 = scalarInfo();
    TypeRef_release(t);
    return __ret613; }
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(fd.ty)));
    uint64_t pi = 0;
    while (pi < (long long)((e.typeParams).len)) {
    Bind p = PlewArray_Bind_get(e.typeParams, (long long)(pi));
    if (spansEqual(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    { TypeInfo __ret614 = typeInfoOfRef(&((*c)), PlewArray_U64_get(t.args, (long long)(pi)));
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret614; }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret615 = typeInfoOfRef(&((*c)), fd.ty);
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret615; }
    TypeRef_release(ftr);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { TypeInfo __ret616 = scalarInfo();
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret616; }
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
void genBindTypeInst(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen) {
    TypeInfo ti = genericEnumFieldTypeInfo(&((*c)), instRef, variantStart, variantLen, bindStart, bindLen);
    genTypeInfoCType(&((*c)), ti);
}
void emitFnTypedef(Comp* c, uint64_t fnRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(fnRef)));
    plew_write((PlewString){"typedef ", 8});
    if ((long long)((t.args).len) > 0) {
    emitConcreteCType(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    }
    else {
    plew_write((PlewString){"void", 4});
    }
    plew_write((PlewString){" (*", 3});
    emitMangle(&((*c)), fnRef);
    plew_write((PlewString){")(", 2});
    if ((long long)((t.args).len) <= 1) {
    plew_write((PlewString){"void", 4});
    }
    else {
    uint64_t i = 1;
    while (i < (long long)((t.args).len)) {
    if (i > 1) {
    plew_write((PlewString){", ", 2});
    }
    emitConcreteCType(&((*c)), PlewArray_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    plew_write((PlewString){");\n", 3});
    TypeRef_release(t);
}
void emitMonoForward(Comp* c, uint64_t instRef) {
    plew_write((PlewString){"typedef struct ", 15});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){";\n", 2});
}
void emitMonoStruct(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    TypeRef_release(t);
    return;
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"struct ", 7});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" {\n", 3});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    plew_write((PlewString){"    ", 4});
    emitFieldCType(&((*c)), f.ty, s.typeParams, t.args);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";\n", 2});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"};\n", 3});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
void emitMonoEnum(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    TypeRef_release(t);
    return;
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    plew_write((PlewString){"struct ", 7});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" {\n    long long tag;\n    union {\n", 34});
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    plew_write((PlewString){"        struct {", 16});
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    if ((long long)((fs).len) == 0) {
    plew_write((PlewString){" char _u; ", 10});
    }
    else {
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    plew_write((PlewString){" ", 1});
    emitFieldCType(&((*c)), f.ty, e.typeParams, t.args);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";", 1});
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" ", 1});
    }
    plew_write((PlewString){"} ", 2});
    writeSpan(&((*c)), v.nameStart, v.nameLen);
    plew_write((PlewString){";\n", 2});
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    }
    plew_write((PlewString){"    } data;\n};\n", 15});
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
long long methodMatchesInst(Comp* c, Func f, uint64_t instRef) {
    if (f.hasRecv) {
    }
    else {
    { long long __ret617 = 0;
    return __ret617; }
    }
    if ((long long)((f.typeParams).len) == 0) {
    { long long __ret618 = 0;
    return __ret618; }
    }
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    if (spansEqual(&((*c)), f.recvStart, f.recvLen, inst.nameStart, inst.nameLen)) {
    }
    else {
    { long long __ret619 = 0;
    TypeRef_release(inst);
    return __ret619; }
    }
    { long long __ret620 = ((long long)((f.typeParams).len) == (long long)((inst.args).len));
    TypeRef_release(inst);
    return __ret620; }
    TypeRef_release(inst);
}
void emitMonoMethod(Comp* c, uint64_t fi, uint64_t instRef, long long proto) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    (*c).curRecvInstRef = instRef;
    (*c).curTypeParams = PlewArray_Bind_share(f.typeParams);
    (*c).curTypeArgs = PlewArray_U64_share(inst.args);
    if (proto) {
    genSignature(&((*c)), f);
    plew_write((PlewString){";\n", 2});
    }
    else {
    genFunc(&((*c)), fi);
    }
    PlewArray_Bind noParams = PlewArray_Bind_new();
    PlewArray_U64 noArgs = PlewArray_U64_new();
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = PlewArray_Bind_share(noParams);
    (*c).curTypeArgs = PlewArray_U64_share(noArgs);
    PlewArray_U64_release(noArgs);
    PlewArray_Bind_release(noParams);
    TypeRef_release(inst);
    Func_release(f);
}
void emitMonoMethods(Comp* c, long long proto) {
    uint64_t gi = 0;
    while (gi < (long long)(((*c).genInsts).len)) {
    uint64_t mfi = 0;
    while (mfi < (long long)(((*c).funcs).len)) {
    if (methodMatchesInst(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(mfi)), PlewArray_U64_get((*c).genInsts, (long long)(gi)))) {
    emitMonoMethod(&((*c)), mfi, PlewArray_U64_get((*c).genInsts, (long long)(gi)), proto);
    }
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void wPA(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), elemStart, elemLen);
}
void genArrayTypedef(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"typedef struct { ", 17});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* data; long long len; long long cap; long long* rc; } ", 55});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){";\n", 2});
}
void genArrayRuntimeFns(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new(void) { ", 13});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }\n", 60});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_get(", 5});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } return a.data[i]; }\n", 125});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(", 6});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { ", 6});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (", 61});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){") * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) ", 83});
    if (structNeedsCopy(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"r.data[i] = ", 12});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(a.data[i]);", 17});
    }
    else {
    plew_write((PlewString){"r.data[i] = a.data[i];", 22});
    }
    plew_write((PlewString){" } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }\n", 57});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(", 9});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; ", 55});
    if (structNeedsCopy(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"for (long long i = 0; i < a.len; i++) ", 38});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(a.data[i]); ", 21});
    }
    plew_write((PlewString){"free(a.rc); }\n", 14});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_share(", 7});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { plew_arc_retain(a.rc); return a; }\n", 41});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(", 8});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a) { if (a->rc && (*(a->rc)) > 1) { ", 38});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" nc = ", 6});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(*a); plew_arc_release(a->rc); *a = nc; } }\n", 49});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_set(", 5});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, long long i, ", 18});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { if (i < 0 || i >= a->len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } ", 93});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(a); a->data[i] = v; }\n", 30});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(", 6});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, ", 5});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { ", 6});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; ", 80});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* nd = (", 8});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){") * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }\n", 185});
}
long long isU8Elem(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    { long long __ret621 = rangeEquals((*c).bytes, elemStart, elemLen, (PlewString){"U8", 2});
    return __ret621; }
}
void genU8ArrayTypedef(void) {
    plew_write((PlewString){"typedef struct { unsigned char* data; long long len; long long cap; long long* rc; } PlewArray_U8;\n", 99});
}
void genU8ArrayRuntime(void) {
    plew_write((PlewString){"__attribute__((unused)) static PlewArray_U8 PlewArray_U8_new(void) { PlewArray_U8 a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }\n", 141});
    plew_write((PlewString){"__attribute__((unused)) static unsigned char PlewArray_U8_get(PlewArray_U8 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } return a.data[i]; }\n", 199});
    plew_write((PlewString){"__attribute__((unused)) static PlewArray_U8 PlewArray_U8_copy(PlewArray_U8 a) { PlewArray_U8 r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (unsigned char*)plew_arc_alloc(sizeof(unsigned char) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }\n", 365});
    plew_write((PlewString){"__attribute__((unused)) static void PlewArray_U8_release(PlewArray_U8 a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }\n", 138});
    plew_write((PlewString){"__attribute__((unused)) static PlewArray_U8 PlewArray_U8_share(PlewArray_U8 a) { plew_arc_retain(a.rc); return a; }\n", 116});
    plew_write((PlewString){"__attribute__((unused)) static void PlewArray_U8_unique(PlewArray_U8* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_U8 nc = PlewArray_U8_copy(*a); plew_arc_release(a->rc); *a = nc; } }\n", 185});
    plew_write((PlewString){"__attribute__((unused)) static void PlewArray_U8_set(PlewArray_U8* a, long long i, unsigned char v) { if (i < 0 || i >= a->len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } PlewArray_U8_unique(a); a->data[i] = v; }\n", 231});
    plew_write((PlewString){"__attribute__((unused)) static void PlewArray_U8_push(PlewArray_U8* a, unsigned char v) { PlewArray_U8_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; unsigned char* nd = (unsigned char*)plew_arc_alloc(sizeof(unsigned char) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }\n", 438});
}
long long isPathTokKind(Kind k) {
    {
    Kind _m622 = k;
    if (_m622.tag == 33) {
    { long long __ret623 = 1;
    return __ret623; }
    }
    else if (_m622.tag == 44) {
    { long long __ret624 = 1;
    return __ret624; }
    }
    else if (_m622.tag == 5) {
    { long long __ret625 = 1;
    return __ret625; }
    }
    else {
    { long long __ret626 = 0;
    return __ret626; }
    }
    }
}
PlewArray_Bind collectParts(PlewArray_U8 rootBytes, PlewArray_Tok toks) {
    PlewArray_Bind parts = PlewArray_Bind_new();
    uint64_t i = 0;
    while (i < (long long)((toks).len)) {
    Tok t = PlewArray_Tok_get(toks, (long long)(i));
    long long isKw = 0;
    {
    Kind _m627 = t.kind;
    if (_m627.tag == 5) {
    if (rangeEquals(rootBytes, t.start, t.len, (PlewString){"part", 4})) {
    isKw = 1;
    }
    if (rangeEquals(rootBytes, t.start, t.len, (PlewString){"import", 6})) {
    isKw = 1;
    }
    }
    else {
    }
    }
    if (isKw) {
    if (({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }) < (long long)((toks).len)) {
    Tok first = PlewArray_Tok_get(toks, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    long long starts = 0;
    {
    Kind _m628 = first.kind;
    if (_m628.tag == 33) {
    starts = 1;
    }
    else if (_m628.tag == 44) {
    starts = 1;
    }
    else {
    if (PlewArray_U8_get(rootBytes, (long long)(first.start)) == 64) {
    starts = 1;
    }
    }
    }
    if (starts) {
    uint64_t pathStart = first.start;
    uint64_t pathEnd = ({ uint64_t __ov; if (__builtin_add_overflow((first.start), (first.len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow((i), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    long long go = 1;
    while (go) {
    if (j < (long long)((toks).len)) {
    Tok nt = PlewArray_Tok_get(toks, (long long)(j));
    if (isPathTokKind(nt.kind)) {
    if (nt.start == pathEnd) {
    pathEnd = ({ uint64_t __ov; if (__builtin_add_overflow((nt.start), (nt.len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    go = 0;
    }
    }
    else {
    go = 0;
    }
    }
    else {
    go = 0;
    }
    }
    uint64_t pl = ({ uint64_t __ov; if (__builtin_sub_overflow((pathEnd), (pathStart), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_Bind_push(&(parts), (Bind){.nameStart = pathStart, .nameLen = pl, .fieldStart = pathStart, .fieldLen = pl});
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { PlewArray_Bind __ret629 = PlewArray_Bind_share(parts);
    PlewArray_Bind_release(parts);
    return __ret629; }
    PlewArray_Bind_release(parts);
}
uint64_t stripParents(PlewArray_U8 path, uint64_t baseLen, uint64_t n) {
    uint64_t end = baseLen;
    uint64_t c = 0;
    while (c < n) {
    if (end > 0) {
    end = ({ uint64_t __ov; if (__builtin_sub_overflow((end), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    long long go = 1;
    while (go) {
    if (end > 0) {
    if (PlewArray_U8_get(path, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((end), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
    go = 0;
    }
    else {
    end = ({ uint64_t __ov; if (__builtin_sub_overflow((end), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else {
    go = 0;
    }
    }
    }
    c = ({ uint64_t __ov; if (__builtin_add_overflow((c), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret630 = end;
    return __ret630; }
}
PlewArray_U8 resolveImport(PlewArray_U8 src, uint64_t pStart, uint64_t pLen, PlewArray_U8 importer, uint64_t baseLen, PlewArray_U8 srcRoot, uint64_t srcRootLen, PlewArray_U8 stdRoot, uint64_t stdRootLen) {
    PlewArray_U8 out = PlewArray_U8_new();
    if (pLen == 0) {
    { PlewArray_U8 __ret631 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret631; }
    }
    uint64_t end = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (pLen), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    unsigned char b0 = PlewArray_U8_get(src, (long long)(pStart));
    if (b0 == 64) {
    if (pLen >= 5) {
    if (PlewArray_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 83) {
    if (PlewArray_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 116) {
    if (PlewArray_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (3), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 100) {
    if (PlewArray_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (4), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
    if (stdRootLen == 0) {
    { PlewArray_U8 __ret632 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret632; }
    }
    uint64_t si = 0;
    while (si < stdRootLen) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(stdRoot, (long long)(si)));
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t sj = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (5), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (sj < end) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(src, (long long)(sj)));
    sj = ({ uint64_t __ov; if (__builtin_add_overflow((sj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8_push(&(out), 46);
    PlewArray_U8_push(&(out), 112);
    PlewArray_U8_push(&(out), 119);
    { PlewArray_U8 __ret633 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret633; }
    }
    }
    }
    }
    }
    { PlewArray_U8 __ret634 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret634; }
    }
    if (b0 == 47) {
    if (srcRootLen == 0) {
    { PlewArray_U8 __ret635 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret635; }
    }
    uint64_t i = 0;
    while (i < srcRootLen) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(srcRoot, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < end) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(src, (long long)(j)));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8_push(&(out), 46);
    PlewArray_U8_push(&(out), 112);
    PlewArray_U8_push(&(out), 119);
    { PlewArray_U8 __ret636 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret636; }
    }
    uint64_t rest = pStart;
    uint64_t parents = 0;
    if (({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }) < end) {
    if (PlewArray_U8_get(src, (long long)(pStart)) == 46) {
    if (PlewArray_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
    rest = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    long long go = 1;
    while (go) {
    if (({ uint64_t __ov; if (__builtin_add_overflow((rest), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }) < end) {
    if (PlewArray_U8_get(src, (long long)(rest)) == 46) {
    if (PlewArray_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((rest), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 46) {
    if (PlewArray_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((rest), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
    parents = ({ uint64_t __ov; if (__builtin_add_overflow((parents), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    rest = ({ uint64_t __ov; if (__builtin_add_overflow((rest), (3), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    go = 0;
    }
    }
    else {
    go = 0;
    }
    }
    else {
    go = 0;
    }
    }
    else {
    go = 0;
    }
    }
    }
    }
    }
    uint64_t dirLen = stripParents(importer, baseLen, parents);
    uint64_t k = 0;
    while (k < dirLen) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(importer, (long long)(k)));
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t m = rest;
    while (m < end) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(src, (long long)(m)));
    m = ({ uint64_t __ov; if (__builtin_add_overflow((m), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8_push(&(out), 46);
    PlewArray_U8_push(&(out), 112);
    PlewArray_U8_push(&(out), 119);
    { PlewArray_U8 __ret637 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret637; }
    PlewArray_U8_release(out);
}
void appendBytes(PlewArray_U8* into, PlewArray_U8 from) {
    uint64_t i = 0;
    while (i < (long long)((from).len)) {
    PlewArray_U8_push(&((*into)), PlewArray_U8_get(from, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
PlewArray_U8 extractSpan(PlewArray_U8 buf, uint64_t start, uint64_t len) {
    PlewArray_U8 out = PlewArray_U8_new();
    uint64_t i = 0;
    while (i < len) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(buf, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (i), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { PlewArray_U8 __ret638 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret638; }
    PlewArray_U8_release(out);
}
uint64_t dirPrefixLen(PlewArray_U8 path) {
    uint64_t pre = 0;
    uint64_t k = 0;
    while (k < (long long)((path).len)) {
    if (PlewArray_U8_get(path, (long long)(k)) == 47) {
    pre = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret639 = pre;
    return __ret639; }
}
PlewArray_U8 computeStdRoot(PlewArray_U8 arg0) {
    uint64_t pre = dirPrefixLen(arg0);
    PlewArray_U8 out = PlewArray_U8_new();
    uint64_t i = 0;
    while (i < pre) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(arg0, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8_push(&(out), 115);
    PlewArray_U8_push(&(out), 116);
    PlewArray_U8_push(&(out), 100);
    PlewArray_U8_push(&(out), 47);
    { PlewArray_U8 __ret640 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret640; }
    PlewArray_U8_release(out);
}
PlewArray_U8 findSrcRoot(PlewArray_U8 entry) {
    uint64_t dirLen = dirPrefixLen(entry);
    long long go = 1;
    while (go) {
    PlewArray_U8 mani = PlewArray_U8_new();
    uint64_t i = 0;
    while (i < dirLen) {
    PlewArray_U8_push(&(mani), PlewArray_U8_get(entry, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8 mn = PlewArray_U8_share(({ PlewString __s = (PlewString){"Plew.toml", 9}; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    appendBytes(&(mani), mn);
    if (plew_file_exists(mani)) {
    PlewArray_U8 sr = PlewArray_U8_new();
    uint64_t j = 0;
    while (j < dirLen) {
    PlewArray_U8_push(&(sr), PlewArray_U8_get(entry, (long long)(j)));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8 sx = PlewArray_U8_share(({ PlewString __s = (PlewString){"src/", 4}; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    appendBytes(&(sr), sx);
    { PlewArray_U8 __ret641 = PlewArray_U8_share(sr);
    PlewArray_U8_release(sx);
    PlewArray_U8_release(sr);
    PlewArray_U8_release(mn);
    PlewArray_U8_release(mani);
    return __ret641; }
    PlewArray_U8_release(sx);
    PlewArray_U8_release(sr);
    }
    if (dirLen == 0) {
    go = 0;
    }
    else {
    uint64_t nd = stripParents(entry, dirLen, 1);
    if (nd == dirLen) {
    go = 0;
    }
    else {
    dirLen = nd;
    }
    }
    PlewArray_U8_release(mn);
    PlewArray_U8_release(mani);
    }
    PlewArray_U8 empty = PlewArray_U8_new();
    { PlewArray_U8 __ret642 = PlewArray_U8_share(empty);
    PlewArray_U8_release(empty);
    return __ret642; }
    PlewArray_U8_release(empty);
}
long long pathSeen(PlewArray_U8 buf, PlewArray_Bind loaded, PlewArray_U8 path) {
    uint64_t i = 0;
    while (i < (long long)((loaded).len)) {
    Bind b = PlewArray_Bind_get(loaded, (long long)(i));
    if (b.nameLen == (long long)((path).len)) {
    long long eq = 1;
    uint64_t j = 0;
    while (j < (long long)((path).len)) {
    if (PlewArray_U8_get(buf, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((b.nameStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != PlewArray_U8_get(path, (long long)(j))) {
    eq = 0;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (eq) {
    { long long __ret643 = 1;
    return __ret643; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret644 = 0;
    return __ret644; }
}
