#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef struct { const char* data; long long len; } PlewString;
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
typedef struct { unsigned char* data; long long len; long long cap; } PlewArray_U8;
__attribute__((unused)) static PlewString plew_read_file_bytes(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; PlewString r = plew_read_file((PlewString){path, p.len}); free(path); return r; }
__attribute__((unused)) static long long plew_file_exists(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; FILE* f = fopen(path, "rb"); free(path); if (f) { fclose(f); return 1; } return 0; }
typedef struct { Bind* data; long long len; long long cap; } PlewArray_Bind;
typedef struct { Tok* data; long long len; long long cap; } PlewArray_Tok;
typedef struct { uint64_t* data; long long len; long long cap; } PlewArray_U64;
typedef struct { Arg* data; long long len; long long cap; } PlewArray_Arg;
typedef struct { MakeField* data; long long len; long long cap; } PlewArray_MakeField;
typedef struct { MatchArm* data; long long len; long long cap; } PlewArray_MatchArm;
typedef struct { Param* data; long long len; long long cap; } PlewArray_Param;
typedef struct { FieldDef* data; long long len; long long cap; } PlewArray_FieldDef;
typedef struct { Variant* data; long long len; long long cap; } PlewArray_Variant;
typedef struct { Expr* data; long long len; long long cap; } PlewArray_Expr;
typedef struct { Stmt* data; long long len; long long cap; } PlewArray_Stmt;
typedef struct { Block* data; long long len; long long cap; } PlewArray_Block;
typedef struct { Func* data; long long len; long long cap; } PlewArray_Func;
typedef struct { StructDef* data; long long len; long long cap; } PlewArray_StructDef;
typedef struct { EnumDef* data; long long len; long long cap; } PlewArray_EnumDef;
typedef struct { TypeRef* data; long long len; long long cap; } PlewArray_TypeRef;
typedef struct { Local* data; long long len; long long cap; } PlewArray_Local;
typedef struct { PatInfo* data; long long len; long long cap; } PlewArray_PatInfo;
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
__attribute__((unused)) static PlewArray_U8 PlewArray_U8_new(void) { PlewArray_U8 a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static unsigned char PlewArray_U8_get(PlewArray_U8 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_U8_set(PlewArray_U8* a, long long i, unsigned char v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_U8_push(PlewArray_U8* a, unsigned char v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; unsigned char* nd = (unsigned char*)malloc(sizeof(unsigned char) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_U8 PlewArray_U8_copy(PlewArray_U8 a) { PlewArray_U8 r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (unsigned char*)malloc(sizeof(unsigned char) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Bind PlewArray_Bind_new(void) { PlewArray_Bind a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Bind PlewArray_Bind_get(PlewArray_Bind a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Bind_set(PlewArray_Bind* a, long long i, Bind v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Bind_push(PlewArray_Bind* a, Bind v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Bind* nd = (Bind*)malloc(sizeof(Bind) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Bind PlewArray_Bind_copy(PlewArray_Bind a) { PlewArray_Bind r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Bind*)malloc(sizeof(Bind) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Tok PlewArray_Tok_new(void) { PlewArray_Tok a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Tok PlewArray_Tok_get(PlewArray_Tok a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Tok_set(PlewArray_Tok* a, long long i, Tok v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Tok_push(PlewArray_Tok* a, Tok v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Tok* nd = (Tok*)malloc(sizeof(Tok) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Tok PlewArray_Tok_copy(PlewArray_Tok a) { PlewArray_Tok r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Tok*)malloc(sizeof(Tok) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_U64 PlewArray_U64_new(void) { PlewArray_U64 a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static uint64_t PlewArray_U64_get(PlewArray_U64 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_U64_set(PlewArray_U64* a, long long i, uint64_t v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_U64_push(PlewArray_U64* a, uint64_t v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; uint64_t* nd = (uint64_t*)malloc(sizeof(uint64_t) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_U64 PlewArray_U64_copy(PlewArray_U64 a) { PlewArray_U64 r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (uint64_t*)malloc(sizeof(uint64_t) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Arg PlewArray_Arg_new(void) { PlewArray_Arg a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Arg PlewArray_Arg_get(PlewArray_Arg a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Arg_set(PlewArray_Arg* a, long long i, Arg v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Arg_push(PlewArray_Arg* a, Arg v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Arg* nd = (Arg*)malloc(sizeof(Arg) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Arg PlewArray_Arg_copy(PlewArray_Arg a) { PlewArray_Arg r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Arg*)malloc(sizeof(Arg) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_MakeField PlewArray_MakeField_new(void) { PlewArray_MakeField a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static MakeField PlewArray_MakeField_get(PlewArray_MakeField a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_MakeField_set(PlewArray_MakeField* a, long long i, MakeField v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_MakeField_push(PlewArray_MakeField* a, MakeField v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MakeField* nd = (MakeField*)malloc(sizeof(MakeField) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_MakeField PlewArray_MakeField_copy(PlewArray_MakeField a) { PlewArray_MakeField r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (MakeField*)malloc(sizeof(MakeField) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_MatchArm PlewArray_MatchArm_new(void) { PlewArray_MatchArm a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static MatchArm PlewArray_MatchArm_get(PlewArray_MatchArm a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_MatchArm_set(PlewArray_MatchArm* a, long long i, MatchArm v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_MatchArm_push(PlewArray_MatchArm* a, MatchArm v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MatchArm* nd = (MatchArm*)malloc(sizeof(MatchArm) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_MatchArm PlewArray_MatchArm_copy(PlewArray_MatchArm a) { PlewArray_MatchArm r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (MatchArm*)malloc(sizeof(MatchArm) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Param PlewArray_Param_new(void) { PlewArray_Param a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Param PlewArray_Param_get(PlewArray_Param a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Param_set(PlewArray_Param* a, long long i, Param v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Param_push(PlewArray_Param* a, Param v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Param* nd = (Param*)malloc(sizeof(Param) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Param PlewArray_Param_copy(PlewArray_Param a) { PlewArray_Param r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Param*)malloc(sizeof(Param) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_FieldDef PlewArray_FieldDef_new(void) { PlewArray_FieldDef a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static FieldDef PlewArray_FieldDef_get(PlewArray_FieldDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_FieldDef_set(PlewArray_FieldDef* a, long long i, FieldDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_FieldDef_push(PlewArray_FieldDef* a, FieldDef v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; FieldDef* nd = (FieldDef*)malloc(sizeof(FieldDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_FieldDef PlewArray_FieldDef_copy(PlewArray_FieldDef a) { PlewArray_FieldDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (FieldDef*)malloc(sizeof(FieldDef) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_new(void) { PlewArray_Variant a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Variant PlewArray_Variant_get(PlewArray_Variant a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Variant_set(PlewArray_Variant* a, long long i, Variant v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Variant_push(PlewArray_Variant* a, Variant v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Variant* nd = (Variant*)malloc(sizeof(Variant) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_copy(PlewArray_Variant a) { PlewArray_Variant r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Variant*)malloc(sizeof(Variant) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Expr PlewArray_Expr_new(void) { PlewArray_Expr a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Expr PlewArray_Expr_get(PlewArray_Expr a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Expr_set(PlewArray_Expr* a, long long i, Expr v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Expr_push(PlewArray_Expr* a, Expr v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Expr* nd = (Expr*)malloc(sizeof(Expr) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Expr PlewArray_Expr_copy(PlewArray_Expr a) { PlewArray_Expr r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Expr*)malloc(sizeof(Expr) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Stmt PlewArray_Stmt_new(void) { PlewArray_Stmt a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Stmt PlewArray_Stmt_get(PlewArray_Stmt a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Stmt_set(PlewArray_Stmt* a, long long i, Stmt v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Stmt_push(PlewArray_Stmt* a, Stmt v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Stmt* nd = (Stmt*)malloc(sizeof(Stmt) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Stmt PlewArray_Stmt_copy(PlewArray_Stmt a) { PlewArray_Stmt r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Stmt*)malloc(sizeof(Stmt) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Block PlewArray_Block_new(void) { PlewArray_Block a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Block PlewArray_Block_get(PlewArray_Block a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Block_set(PlewArray_Block* a, long long i, Block v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Block_push(PlewArray_Block* a, Block v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Block* nd = (Block*)malloc(sizeof(Block) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Block PlewArray_Block_copy(PlewArray_Block a) { PlewArray_Block r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Block*)malloc(sizeof(Block) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_new(void) { PlewArray_Func a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Func PlewArray_Func_get(PlewArray_Func a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Func_set(PlewArray_Func* a, long long i, Func v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Func_push(PlewArray_Func* a, Func v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Func* nd = (Func*)malloc(sizeof(Func) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_copy(PlewArray_Func a) { PlewArray_Func r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Func*)malloc(sizeof(Func) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_new(void) { PlewArray_StructDef a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static StructDef PlewArray_StructDef_get(PlewArray_StructDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_StructDef_set(PlewArray_StructDef* a, long long i, StructDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_StructDef_push(PlewArray_StructDef* a, StructDef v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; StructDef* nd = (StructDef*)malloc(sizeof(StructDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_copy(PlewArray_StructDef a) { PlewArray_StructDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (StructDef*)malloc(sizeof(StructDef) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_new(void) { PlewArray_EnumDef a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static EnumDef PlewArray_EnumDef_get(PlewArray_EnumDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_EnumDef_set(PlewArray_EnumDef* a, long long i, EnumDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_EnumDef_push(PlewArray_EnumDef* a, EnumDef v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; EnumDef* nd = (EnumDef*)malloc(sizeof(EnumDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_copy(PlewArray_EnumDef a) { PlewArray_EnumDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (EnumDef*)malloc(sizeof(EnumDef) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_new(void) { PlewArray_TypeRef a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static TypeRef PlewArray_TypeRef_get(PlewArray_TypeRef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_TypeRef_set(PlewArray_TypeRef* a, long long i, TypeRef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_TypeRef_push(PlewArray_TypeRef* a, TypeRef v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; TypeRef* nd = (TypeRef*)malloc(sizeof(TypeRef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_copy(PlewArray_TypeRef a) { PlewArray_TypeRef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (TypeRef*)malloc(sizeof(TypeRef) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_Local PlewArray_Local_new(void) { PlewArray_Local a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Local PlewArray_Local_get(PlewArray_Local a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Local_set(PlewArray_Local* a, long long i, Local v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Local_push(PlewArray_Local* a, Local v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Local* nd = (Local*)malloc(sizeof(Local) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Local PlewArray_Local_copy(PlewArray_Local a) { PlewArray_Local r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Local*)malloc(sizeof(Local) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
__attribute__((unused)) static PlewArray_PatInfo PlewArray_PatInfo_new(void) { PlewArray_PatInfo a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static PatInfo PlewArray_PatInfo_get(PlewArray_PatInfo a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_PatInfo_set(PlewArray_PatInfo* a, long long i, PatInfo v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_PatInfo_push(PlewArray_PatInfo* a, PatInfo v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; PatInfo* nd = (PatInfo*)malloc(sizeof(PatInfo) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_PatInfo PlewArray_PatInfo_copy(PlewArray_PatInfo a) { PlewArray_PatInfo r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (PatInfo*)malloc(sizeof(PatInfo) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }
Lexer Lexer_copy(Lexer s);
TypeRef TypeRef_copy(TypeRef s);
MatchArm MatchArm_copy(MatchArm s);
PatInfo PatInfo_copy(PatInfo s);
Block Block_copy(Block s);
StructDef StructDef_copy(StructDef s);
Variant Variant_copy(Variant s);
EnumDef EnumDef_copy(EnumDef s);
Func Func_copy(Func s);
Comp Comp_copy(Comp s);
Lexer Lexer_copy(Lexer s) { Lexer r = s; r.bytes = PlewArray_U8_copy(s.bytes); r.toks = PlewArray_Tok_copy(s.toks); return r; }
TypeRef TypeRef_copy(TypeRef s) { TypeRef r = s; r.args = PlewArray_U64_copy(s.args); return r; }
MatchArm MatchArm_copy(MatchArm s) { MatchArm r = s; r.binds = PlewArray_Bind_copy(s.binds); return r; }
PatInfo PatInfo_copy(PatInfo s) { PatInfo r = s; r.binds = PlewArray_Bind_copy(s.binds); return r; }
Block Block_copy(Block s) { Block r = s; r.stmts = PlewArray_U64_copy(s.stmts); return r; }
StructDef StructDef_copy(StructDef s) { StructDef r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.fields = PlewArray_FieldDef_copy(s.fields); return r; }
Variant Variant_copy(Variant s) { Variant r = s; r.fields = PlewArray_FieldDef_copy(s.fields); return r; }
EnumDef EnumDef_copy(EnumDef s) { EnumDef r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.variants = PlewArray_Variant_copy(s.variants); return r; }
Func Func_copy(Func s) { Func r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.params = PlewArray_Param_copy(s.params); return r; }
Comp Comp_copy(Comp s) { Comp r = s; r.bytes = PlewArray_U8_copy(s.bytes); r.toks = PlewArray_Tok_copy(s.toks); r.exprs = PlewArray_Expr_copy(s.exprs); r.stmts = PlewArray_Stmt_copy(s.stmts); r.blocks = PlewArray_Block_copy(s.blocks); r.funcs = PlewArray_Func_copy(s.funcs); r.structs = PlewArray_StructDef_copy(s.structs); r.enums = PlewArray_EnumDef_copy(s.enums); r.types = PlewArray_TypeRef_copy(s.types); r.genInsts = PlewArray_U64_copy(s.genInsts); r.fnTypes = PlewArray_U64_copy(s.fnTypes); r.arrayElems = PlewArray_Bind_copy(s.arrayElems); r.locals = PlewArray_Local_copy(s.locals); r.curTypeParams = PlewArray_Bind_copy(s.curTypeParams); r.curTypeArgs = PlewArray_U64_copy(s.curTypeArgs); return r; }
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
void addLocal(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut);
uint64_t scopeMark(Comp* c);
void emitScopeDrops(Comp* c, uint64_t mark);
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
    PlewArray_U8 entryBytes = PlewArray_U8_copy(({ PlewString __s = rootPath; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }));
    PlewArray_U8 pathBuf = PlewArray_U8_new();
    PlewArray_Bind loaded = PlewArray_Bind_new();
    PlewArray_U8 srcRoot = findSrcRoot(entryBytes);
    PlewArray_U8 stdRoot = computeStdRoot(({ PlewString __s = plew_arg_at((long long)(0)); (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }));
    uint64_t es = (long long)((pathBuf).len);
    appendBytes(&(pathBuf), entryBytes);
    PlewArray_Bind_push(&(loaded), (Bind){.nameStart = es, .nameLen = (long long)((entryBytes).len), .fieldStart = es, .fieldLen = (long long)((entryBytes).len)});
    uint64_t qi = 0;
    while (qi < (long long)((loaded).len)) {
    Bind ent = PlewArray_Bind_get(loaded, (long long)(qi));
    qi = ({ uint64_t __ov; if (__builtin_add_overflow((qi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_U8 path = extractSpan(pathBuf, ent.nameStart, ent.nameLen);
    PlewString src = plew_read_file_bytes(path);
    PlewArray_U8 sb = PlewArray_U8_copy(({ PlewString __s = src; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }));
    if ((long long)((combined).len) > 0) {
    PlewArray_U8_push(&(combined), 10);
    }
    appendBytes(&(combined), sb);
    Lexer lxp = (Lexer){.bytes = PlewArray_U8_copy(sb), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0};
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
    }
    }
    }
    else {
    PlewString s = plew_read_stdin();
    appendBytes(&(combined), ({ PlewString __s = s; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }));
    }
    Lexer lx = (Lexer){.bytes = PlewArray_U8_copy(combined), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0};
    lex(&(lx));
    Comp c = (Comp){.bytes = PlewArray_U8_copy(combined), .toks = PlewArray_Tok_copy(lx.toks), .pos = 0, .exprs = PlewArray_Expr_new(), .stmts = PlewArray_Stmt_new(), .blocks = PlewArray_Block_new(), .funcs = PlewArray_Func_new(), .structs = PlewArray_StructDef_new(), .enums = PlewArray_EnumDef_new(), .types = PlewArray_TypeRef_new(), .genInsts = PlewArray_U64_new(), .fnTypes = PlewArray_U64_new(), .arrayElems = PlewArray_Bind_new(), .locals = PlewArray_Local_new(), .tmp = 0, .curIsMain = 0, .curRetVoid = 0, .curRetStart = 0, .curRetLen = 0, .curRetIsArray = 0, .curRetTy = 0, .curHasRecv = 0, .curRecvStart = 0, .curRecvLen = 0, .curSelfInout = 0, .curTypeParams = PlewArray_Bind_new(), .curTypeArgs = PlewArray_U64_new(), .curRecvInstRef = 0, .curGiveTmp = 0, .impPrint = 0, .impWrite = 0, .impWriteByte = 0, .impReadStdin = 0, .impReadFile = 0, .impArgCount = 0, .impArgAt = 0, .impEprint = 0, .impExit = 0, .impReadFileBytes = 0, .impFileExists = 0};
    PlewArray_TypeRef_push(&(c.types), (TypeRef){.nameStart = 0, .nameLen = 0, .args = PlewArray_U64_new()});
    parseProgram(&(c));
    collectGenInsts(&(c));
    plew_write((PlewString){"#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n#include <string.h>\n", 79});
    plew_write((PlewString){"typedef struct { const char* data; long long len; } PlewString;\n", 64});
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
    StructDef s = PlewArray_StructDef_get(c.structs, (long long)(si));
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
    }
    uint64_t ei = 0;
    while (ei < (long long)((c.enums).len)) {
    EnumDef e = PlewArray_EnumDef_get(c.enums, (long long)(ei));
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
    EnumDef ge = PlewArray_EnumDef_get(c.enums, (long long)(ej));
    if ((long long)((ge.typeParams).len) > 0) {
    }
    else {
    genEnumDef(&(c), ej);
    }
    ej = ({ uint64_t __ov; if (__builtin_add_overflow((ej), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t sj = 0;
    while (sj < (long long)((c.structs).len)) {
    StructDef gs = PlewArray_StructDef_get(c.structs, (long long)(sj));
    if ((long long)((gs.typeParams).len) > 0) {
    }
    else {
    genStructDef(&(c), sj);
    }
    sj = ({ uint64_t __ov; if (__builtin_add_overflow((sj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
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
    uint64_t scp = 0;
    while (scp < (long long)((c.structs).len)) {
    StructDef cs = PlewArray_StructDef_get(c.structs, (long long)(scp));
    if ((long long)((cs.typeParams).len) > 0) {
    }
    else {
    if (structNeedsCopy(&(c), cs.nameStart, cs.nameLen)) {
    emitStructCopyProto(&(c), scp);
    }
    }
    scp = ({ uint64_t __ov; if (__builtin_add_overflow((scp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t scd = 0;
    while (scd < (long long)((c.structs).len)) {
    StructDef cs2 = PlewArray_StructDef_get(c.structs, (long long)(scd));
    if ((long long)((cs2.typeParams).len) > 0) {
    }
    else {
    if (structNeedsCopy(&(c), cs2.nameStart, cs2.nameLen)) {
    emitStructCopyDef(&(c), scd);
    }
    }
    scd = ({ uint64_t __ov; if (__builtin_add_overflow((scd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
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
    Func f = PlewArray_Func_get(c.funcs, (long long)(i));
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
    }
    emitMonoMethods(&(c), 1);
    emitClosures(&(c), 1);
    {
    long long __fe0 = (long long)((c.funcs).len);
    for (long long j = 0; j < __fe0; j++) {
    Func fb = PlewArray_Func_get(c.funcs, (long long)(j));
    if ((long long)((fb.typeParams).len) > 0) {
    }
    else {
    genFunc(&(c), j);
    }
    }
    }
    emitMonoMethods(&(c), 0);
    emitClosures(&(c), 0);
    return 0;
}
unsigned char Lexer_at(Lexer self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow((self.pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)((self.bytes).len)) {
    return PlewArray_U8_get(self.bytes, (long long)(i));
    }
    return 0;
}
void Lexer_emit(Lexer* self, Kind k, uint64_t start, uint64_t len) {
    PlewArray_Tok_push(&((*self).toks), (Tok){.kind = k, .start = start, .len = len});
    (*self).pos = ({ uint64_t __ov; if (__builtin_add_overflow((start), (len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
}
long long Lexer_lastWasNewline(Lexer self) {
    uint64_t n = (long long)((self.toks).len);
    if (n == 0) {
    return 0;
    }
    Tok t = PlewArray_Tok_get(self.toks, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    return ({ long long __mr1; Kind __ms1 = t.kind; if (__ms1.tag == 1) { __mr1 = (1); } else { __mr1 = (0); } __mr1; });
}
long long Lexer_lastCanEnd(Lexer self) {
    uint64_t n = (long long)((self.toks).len);
    if (n == 0) {
    return 0;
    }
    Tok t = PlewArray_Tok_get(self.toks, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    return ({ long long __mr2; Kind __ms2 = t.kind; if (__ms2.tag == 5) { __mr2 = (1); } else if (__ms2.tag == 2) { __mr2 = (1); } else if (__ms2.tag == 3) { __mr2 = (1); } else if (__ms2.tag == 4) { __mr2 = (1); } else if (__ms2.tag == 26) { __mr2 = (1); } else if (__ms2.tag == 28) { __mr2 = (1); } else if (__ms2.tag == 30) { __mr2 = (1); } else if (__ms2.tag == 57) { __mr2 = (1); } else if (__ms2.tag == 23) { __mr2 = (1); } else if (__ms2.tag == 24) { __mr2 = (1); } else if (__ms2.tag == 16) { __mr2 = (1); } else if (__ms2.tag == 14) { __mr2 = (1); } else if (__ms2.tag == 15) { __mr2 = (1); } else { __mr2 = (0); } __mr2; });
}
long long isDigit(unsigned char b) {
    if (b >= 48) {
    if (b <= 57) {
    return 1;
    }
    }
    return 0;
}
long long isAlpha(unsigned char b) {
    if (b == 95) {
    return 1;
    }
    if (b >= 97) {
    if (b <= 122) {
    return 1;
    }
    }
    if (b >= 65) {
    if (b <= 90) {
    return 1;
    }
    }
    return 0;
}
long long isAlnum(unsigned char b) {
    if (isAlpha(b)) {
    return 1;
    }
    return isDigit(b);
}
long long rangeEquals(PlewArray_U8 bytes, uint64_t start, uint64_t len, PlewString kw) {
    PlewArray_U8 kb = PlewArray_U8_copy(({ PlewString __s = kw; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }));
    if (len != (long long)((kb).len)) {
    return 0;
    }
    uint64_t j = 0;
    while (j < len) {
    if (PlewArray_U8_get(bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != PlewArray_U8_get(kb, (long long)(j))) {
    return 0;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
}
Kind identKind(PlewArray_U8 bytes, uint64_t start, uint64_t len) {
    if (rangeEquals(bytes, start, len, (PlewString){"fn", 2})) {
    return (Kind){.tag = 6};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"struct", 6})) {
    return (Kind){.tag = 7};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"enum", 4})) {
    return (Kind){.tag = 8};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"match", 5})) {
    return (Kind){.tag = 9};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"if", 2})) {
    return (Kind){.tag = 10};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"else", 4})) {
    return (Kind){.tag = 11};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"while", 5})) {
    return (Kind){.tag = 12};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"for", 3})) {
    return (Kind){.tag = 13};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"break", 5})) {
    return (Kind){.tag = 14};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"continue", 8})) {
    return (Kind){.tag = 15};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"return", 6})) {
    return (Kind){.tag = 16};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"give", 4})) {
    return (Kind){.tag = 17};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"val", 3})) {
    return (Kind){.tag = 18};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"mut", 3})) {
    return (Kind){.tag = 19};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"in", 2})) {
    return (Kind){.tag = 20};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"as", 2})) {
    return (Kind){.tag = 21};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"inout", 5})) {
    return (Kind){.tag = 22};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"true", 4})) {
    return (Kind){.tag = 23};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"false", 5})) {
    return (Kind){.tag = 24};
    }
    return (Kind){.tag = 5};
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
    return ({ long long __mr3; Kind __ms3 = k; if (__ms3.tag == 0) { __mr3 = (0); } else if (__ms3.tag == 1) { __mr3 = (1); } else if (__ms3.tag == 2) { __mr3 = (2); } else if (__ms3.tag == 3) { __mr3 = (3); } else if (__ms3.tag == 4) { __mr3 = (5); } else if (__ms3.tag == 5) { __mr3 = (4); } else if (__ms3.tag == 6) { __mr3 = (10); } else if (__ms3.tag == 7) { __mr3 = (11); } else if (__ms3.tag == 8) { __mr3 = (12); } else if (__ms3.tag == 9) { __mr3 = (13); } else if (__ms3.tag == 10) { __mr3 = (14); } else if (__ms3.tag == 11) { __mr3 = (15); } else if (__ms3.tag == 12) { __mr3 = (16); } else if (__ms3.tag == 13) { __mr3 = (17); } else if (__ms3.tag == 14) { __mr3 = (18); } else if (__ms3.tag == 15) { __mr3 = (19); } else if (__ms3.tag == 16) { __mr3 = (20); } else if (__ms3.tag == 17) { __mr3 = (21); } else if (__ms3.tag == 18) { __mr3 = (22); } else if (__ms3.tag == 19) { __mr3 = (23); } else if (__ms3.tag == 20) { __mr3 = (24); } else if (__ms3.tag == 21) { __mr3 = (25); } else if (__ms3.tag == 22) { __mr3 = (26); } else if (__ms3.tag == 23) { __mr3 = (27); } else if (__ms3.tag == 24) { __mr3 = (28); } else if (__ms3.tag == 25) { __mr3 = (40); } else if (__ms3.tag == 26) { __mr3 = (41); } else if (__ms3.tag == 27) { __mr3 = (42); } else if (__ms3.tag == 28) { __mr3 = (43); } else if (__ms3.tag == 29) { __mr3 = (44); } else if (__ms3.tag == 30) { __mr3 = (45); } else if (__ms3.tag == 31) { __mr3 = (46); } else if (__ms3.tag == 32) { __mr3 = (47); } else if (__ms3.tag == 33) { __mr3 = (48); } else if (__ms3.tag == 34) { __mr3 = (49); } else if (__ms3.tag == 35) { __mr3 = (50); } else if (__ms3.tag == 36) { __mr3 = (51); } else if (__ms3.tag == 37) { __mr3 = (52); } else if (__ms3.tag == 38) { __mr3 = (53); } else if (__ms3.tag == 39) { __mr3 = (54); } else if (__ms3.tag == 40) { __mr3 = (55); } else if (__ms3.tag == 41) { __mr3 = (56); } else if (__ms3.tag == 42) { __mr3 = (57); } else if (__ms3.tag == 43) { __mr3 = (58); } else if (__ms3.tag == 44) { __mr3 = (59); } else if (__ms3.tag == 45) { __mr3 = (60); } else if (__ms3.tag == 46) { __mr3 = (61); } else if (__ms3.tag == 47) { __mr3 = (62); } else if (__ms3.tag == 48) { __mr3 = (63); } else if (__ms3.tag == 55) { __mr3 = (64); } else if (__ms3.tag == 56) { __mr3 = (65); } else if (__ms3.tag == 57) { __mr3 = (66); } else if (__ms3.tag == 58) { __mr3 = (67); } else if (__ms3.tag == 59) { __mr3 = (68); } else if (__ms3.tag == 60) { __mr3 = (69); } else if (__ms3.tag == 61) { __mr3 = (70); } else if (__ms3.tag == 62) { __mr3 = (71); } else if (__ms3.tag == 68) { __mr3 = (72); } else if (__ms3.tag == 69) { __mr3 = (73); } else if (__ms3.tag == 49) { __mr3 = (74); } else if (__ms3.tag == 50) { __mr3 = (75); } else if (__ms3.tag == 51) { __mr3 = (76); } else if (__ms3.tag == 52) { __mr3 = (77); } else if (__ms3.tag == 53) { __mr3 = (78); } else if (__ms3.tag == 54) { __mr3 = (79); } else if (__ms3.tag == 63) { __mr3 = (80); } else if (__ms3.tag == 64) { __mr3 = (81); } else if (__ms3.tag == 65) { __mr3 = (82); } else if (__ms3.tag == 66) { __mr3 = (83); } else if (__ms3.tag == 67) { __mr3 = (84); } else if (__ms3.tag == 70) { __mr3 = (85); } else if (__ms3.tag == 71) { __mr3 = (99); } else { __builtin_unreachable(); } __mr3; });
}
Kind Comp_curKind(Comp* self) {
    return PlewArray_Tok_get((*self).toks, (long long)((*self).pos)).kind;
}
Tok Comp_cur(Comp* self) {
    return PlewArray_Tok_get((*self).toks, (long long)((*self).pos));
}
Kind Comp_peekKind(Comp* self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)(((*self).toks).len)) {
    return PlewArray_Tok_get((*self).toks, (long long)(i)).kind;
    }
    return (Kind){.tag = 0};
}
void Comp_advance(Comp* self) {
    (*self).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
}
void Comp_skipNewlines(Comp* self) {
    while (1) {
    {
    Kind _m4 = Comp_curKind(&((*self)));
    if (_m4.tag == 1) {
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
    return rangeEquals((*self).bytes, t.start, t.len, kw);
}
uint64_t Comp_pushExpr(Comp* self, Expr e) {
    uint64_t id = (long long)(((*self).exprs).len);
    PlewArray_Expr_push(&((*self).exprs), e);
    return id;
}
uint64_t Comp_pushStmt(Comp* self, Stmt s) {
    uint64_t id = (long long)(((*self).stmts).len);
    PlewArray_Stmt_push(&((*self).stmts), s);
    return id;
}
uint64_t Comp_pushType(Comp* self, TypeRef t) {
    uint64_t id = (long long)(((*self).types).len);
    PlewArray_TypeRef_push(&((*self).types), t);
    return id;
}
int64_t Comp_tokenValue(Comp* self, Tok t) {
    int64_t v = 0;
    uint64_t j = 0;
    while (j < t.len) {
    unsigned char b = PlewArray_U8_get((*self).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((t.start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    v = ({ int64_t __ov; if (__builtin_add_overflow((({ int64_t __ov; if (__builtin_mul_overflow((v), (10), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), (({ int64_t __ov; if (__builtin_sub_overflow((((int64_t)(b))), (48), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return v;
}
int64_t binPrec(Kind k) {
    return ({ long long __mr5; Kind __ms5 = k; if (__ms5.tag == 47) { __mr5 = (1); } else if (__ms5.tag == 46) { __mr5 = (2); } else if (__ms5.tag == 35) { __mr5 = (3); } else if (__ms5.tag == 36) { __mr5 = (3); } else if (__ms5.tag == 37) { __mr5 = (3); } else if (__ms5.tag == 38) { __mr5 = (3); } else if (__ms5.tag == 39) { __mr5 = (3); } else if (__ms5.tag == 40) { __mr5 = (3); } else if (__ms5.tag == 70) { __mr5 = (4); } else if (__ms5.tag == 50) { __mr5 = (5); } else if (__ms5.tag == 51) { __mr5 = (6); } else if (__ms5.tag == 49) { __mr5 = (7); } else if (__ms5.tag == 52) { __mr5 = (8); } else if (__ms5.tag == 53) { __mr5 = (8); } else if (__ms5.tag == 41) { __mr5 = (9); } else if (__ms5.tag == 42) { __mr5 = (9); } else if (__ms5.tag == 43) { __mr5 = (10); } else if (__ms5.tag == 44) { __mr5 = (10); } else if (__ms5.tag == 45) { __mr5 = (10); } else { __mr5 = (0); } __mr5; });
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
    return 10;
    }
    if (e == 116) {
    return 9;
    }
    if (e == 114) {
    return 13;
    }
    if (e == 48) {
    return 0;
    }
    return e;
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
    return value;
}
uint64_t parsePrimary(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m6 = k;
    if (_m6.tag == 2) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    int64_t v = Comp_tokenValue(&((*c)), t);
    uint64_t sStart = 0;
    uint64_t sLen = 0;
    {
    Kind _m7 = Comp_curKind(&((*c)));
    if (_m7.tag == 5) {
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
    return Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = sStart, .tyLen = sLen}});
    }
    else if (_m6.tag == 4) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    int64_t v = charValue(&((*c)), t);
    return Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    }
    else if (_m6.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    {
    Kind _m8 = Comp_peekKind(&((*c)), 1);
    if (_m8.tag == 25) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Arg args = parseCallArgs(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 4, .data.Call = {.nameStart = t.start, .nameLen = t.len, .args = PlewArray_Arg_copy(args)}});
    }
    else {
    Comp_advance(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = t.start, .len = t.len}});
    }
    }
    }
    else if (_m6.tag == 23) {
    Tok tt = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 1, .offset = tt.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    }
    else if (_m6.tag == 24) {
    Tok tf = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = tf.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    }
    else if (_m6.tag == 25) {
    Comp_advance(&((*c)));
    uint64_t inner = parseExpr(&((*c)));
    {
    Kind _m9 = Comp_curKind(&((*c)));
    if (_m9.tag == 26) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    return inner;
    }
    else if (_m6.tag == 6) {
    Comp_advance(&((*c)));
    PlewArray_Param params = parseParamList(&((*c)));
    long long hasRet = 0;
    uint64_t retStart = 0;
    uint64_t retLen = 0;
    long long retIsArray = 0;
    uint64_t retRef = 0;
    {
    Kind _m10 = Comp_curKind(&((*c)));
    if (_m10.tag == 55) {
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
    return Comp_pushExpr(&((*c)), (Expr){.tag = 17, .data.Closure = {.params = PlewArray_Param_copy(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body}});
    }
    else if (_m6.tag == 37) {
    return parseMake(&((*c)));
    }
    else if (_m6.tag == 9) {
    return parseMatchExpr(&((*c)));
    }
    else if (_m6.tag == 10) {
    return parseIfExpr(&((*c)));
    }
    else if (_m6.tag == 3) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 7, .data.Str = {.start = t.start, .len = t.len}});
    }
    else if (_m6.tag == 27) {
    Comp_advance(&((*c)));
    PlewArray_U64 elems = PlewArray_U64_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m11 = Comp_curKind(&((*c)));
    if (_m11.tag == 28) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m11.tag == 0) {
    break;
    }
    else {
    uint64_t e = parseExpr(&((*c)));
    PlewArray_U64_push(&(elems), e);
    {
    Kind _m12 = Comp_curKind(&((*c)));
    if (_m12.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    return Comp_pushExpr(&((*c)), (Expr){.tag = 8, .data.Array = {.elems = PlewArray_U64_copy(elems)}});
    }
    else {
    Tok te = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = te.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    }
    }
}
uint64_t parseUnary(Comp* c) {
    if (Comp_identIs(&((*c)), (PlewString){"try", 3})) {
    Comp_advance(&((*c)));
    uint64_t inner = parsePostfix(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 15, .data.Try = {.expr = inner}});
    }
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m13 = k;
    if (_m13.tag == 42) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 57, .operand = o}});
    }
    else if (_m13.tag == 48) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 63, .operand = o}});
    }
    else if (_m13.tag == 54) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 79, .operand = o}});
    }
    else {
    return parsePostfix(&((*c)));
    }
    }
}
uint64_t parsePostfix(Comp* c) {
    uint64_t e = parsePrimary(&((*c)));
    while (1) {
    {
    Kind _m14 = Comp_curKind(&((*c)));
    if (_m14.tag == 33) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m15 = Comp_curKind(&((*c)));
    if (_m15.tag == 25) {
    Comp_advance(&((*c)));
    PlewArray_Arg args = parseCallArgs(&((*c)));
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 10, .data.Method = {.recv = e, .nameStart = nameTok.start, .nameLen = nameTok.len, .args = PlewArray_Arg_copy(args)}});
    }
    else {
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    }
    }
    else if (_m14.tag == 27) {
    Comp_advance(&((*c)));
    uint64_t idx = parseExpr(&((*c)));
    {
    Kind _m16 = Comp_curKind(&((*c)));
    if (_m16.tag == 28) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 9, .data.Index = {.base = e, .index = idx}});
    }
    else if (_m14.tag == 55) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 16, .data.Arrow = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    else if (_m14.tag == 21) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    e = Comp_pushExpr(&((*c)), (Expr){.tag = 11, .data.Cast = {.operand = e, .tyStart = ty.start, .tyLen = ty.len, .ty = ty.ref}});
    }
    else {
    break;
    }
    }
    }
    return e;
}
uint64_t parseMake(Comp* c) {
    Comp_advance(&((*c)));
    Tok typeTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyRef = 0;
    {
    Kind _m17 = Comp_curKind(&((*c)));
    if (_m17.tag == 27) {
    Comp_advance(&((*c)));
    PlewArray_U64 targs = PlewArray_U64_new();
    long long first = 1;
    while (1) {
    {
    Kind _m18 = Comp_curKind(&((*c)));
    if (_m18.tag == 28) {
    break;
    }
    else if (_m18.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m19 = Comp_curKind(&((*c)));
    if (_m19.tag == 31) {
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
    Kind _m20 = Comp_curKind(&((*c)));
    if (_m20.tag == 28) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    tyRef = Comp_pushType(&((*c)), (TypeRef){.nameStart = typeTok.start, .nameLen = typeTok.len, .args = PlewArray_U64_copy(targs)});
    }
    else {
    }
    }
    uint64_t variantStart = 0;
    uint64_t variantLen = 0;
    long long isEnum = 0;
    {
    Kind _m21 = Comp_curKind(&((*c)));
    if (_m21.tag == 33) {
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
    Kind _m22 = k;
    if (_m22.tag == 57) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m22.tag == 39) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m22.tag == 0) {
    break;
    }
    else if (_m22.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m23 = Comp_curKind(&((*c)));
    if (_m23.tag == 34) {
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
    return Comp_pushExpr(&((*c)), (Expr){.tag = 6, .data.Make = {.typeStart = typeTok.start, .typeLen = typeTok.len, .variantStart = variantStart, .variantLen = variantLen, .isEnum = isEnum, .ty = tyRef, .fields = PlewArray_MakeField_copy(fields)}});
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
    Kind _m24 = k;
    if (_m24.tag == 70) {
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
    return left;
}
uint64_t parseExpr(Comp* c) {
    return parseBin(&((*c)), 1);
}
PlewArray_Arg parseCallArgs(Comp* c) {
    PlewArray_Arg args = PlewArray_Arg_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m25 = k;
    if (_m25.tag == 26) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m25.tag == 0) {
    break;
    }
    else {
    uint64_t labelStart = 0;
    uint64_t labelLen = 0;
    long long hasLabel = 0;
    {
    Kind _m26 = Comp_curKind(&((*c)));
    if (_m26.tag == 5) {
    {
    Kind _m27 = Comp_peekKind(&((*c)), 1);
    if (_m27.tag == 32) {
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
    Kind _m28 = Comp_curKind(&((*c)));
    if (_m28.tag == 22) {
    Comp_advance(&((*c)));
    isInout = 1;
    }
    else {
    }
    }
    uint64_t e = parseExpr(&((*c)));
    PlewArray_Arg_push(&(args), (Arg){.expr = e, .isInout = isInout, .labelStart = labelStart, .labelLen = labelLen, .hasLabel = hasLabel});
    {
    Kind _m29 = Comp_curKind(&((*c)));
    if (_m29.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    return PlewArray_Arg_copy(args);
}
long long isAssignOp(Kind k) {
    {
    Kind _m30 = k;
    if (_m30.tag == 34) {
    return 1;
    }
    else if (_m30.tag == 58) {
    return 1;
    }
    else if (_m30.tag == 59) {
    return 1;
    }
    else if (_m30.tag == 60) {
    return 1;
    }
    else if (_m30.tag == 61) {
    return 1;
    }
    else if (_m30.tag == 62) {
    return 1;
    }
    else if (_m30.tag == 63) {
    return 1;
    }
    else if (_m30.tag == 64) {
    return 1;
    }
    else if (_m30.tag == 65) {
    return 1;
    }
    else if (_m30.tag == 66) {
    return 1;
    }
    else if (_m30.tag == 67) {
    return 1;
    }
    else {
    return 0;
    }
    }
}
PType parseTypeTok(Comp* c) {
    Tok head = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m31 = head.kind;
    if (_m31.tag == 6) {
    PlewArray_U64 fargs = PlewArray_U64_new();
    uint64_t retRef = 0;
    {
    Kind _m32 = Comp_curKind(&((*c)));
    if (_m32.tag == 25) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    {
    Kind _m33 = Comp_curKind(&((*c)));
    if (_m33.tag == 26) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m33.tag == 0) {
    break;
    }
    else if (_m33.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    {
    Kind _m34 = Comp_curKind(&((*c)));
    if (_m34.tag == 5) {
    if ((Comp_peekKind(&((*c)), 1)).tag == 32) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    }
    }
    else {
    }
    }
    {
    Kind _m35 = Comp_curKind(&((*c)));
    if (_m35.tag == 22) {
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
    Kind _m36 = Comp_curKind(&((*c)));
    if (_m36.tag == 55) {
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
    uint64_t fref = Comp_pushType(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = PlewArray_U64_copy(allArgs)});
    return (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = fref};
    }
    else {
    }
    }
    PlewArray_U64 args = PlewArray_U64_new();
    uint64_t elemStart = head.start;
    uint64_t elemLen = head.len;
    long long bracketed = 0;
    {
    Kind _m37 = Comp_curKind(&((*c)));
    if (_m37.tag == 27) {
    bracketed = 1;
    Comp_advance(&((*c)));
    long long first = 1;
    while (1) {
    {
    Kind _m38 = Comp_curKind(&((*c)));
    if (_m38.tag == 28) {
    break;
    }
    else if (_m38.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m39 = Comp_curKind(&((*c)));
    if (_m39.tag == 31) {
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
    Kind _m40 = Comp_curKind(&((*c)));
    if (_m40.tag == 28) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    }
    }
    uint64_t ref = Comp_pushType(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = PlewArray_U64_copy(args)});
    if (bracketed) {
    if (rangeEquals((*c).bytes, head.start, head.len, (PlewString){"Array", 5})) {
    return (PType){.start = elemStart, .len = elemLen, .isArray = 1, .ref = ref};
    }
    }
    return (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = ref};
}
PlewArray_Bind parseTypeParams(Comp* c) {
    PlewArray_Bind ps = PlewArray_Bind_new();
    {
    Kind _m41 = Comp_curKind(&((*c)));
    if (_m41.tag == 27) {
    Comp_advance(&((*c)));
    while (1) {
    {
    Kind _m42 = Comp_curKind(&((*c)));
    if (_m42.tag == 28) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m42.tag == 0) {
    break;
    }
    else if (_m42.tag == 31) {
    Comp_advance(&((*c)));
    }
    else if (_m42.tag == 5) {
    uint64_t nameStart = 0;
    uint64_t nameLen = 0;
    while (1) {
    {
    Kind _m43 = Comp_curKind(&((*c)));
    if (_m43.tag == 5) {
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
    return PlewArray_Bind_copy(ps);
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
    Kind _m44 = Comp_curKind(&((*c)));
    if (_m44.tag == 32) {
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
    Kind _m45 = Comp_curKind(&((*c)));
    if (_m45.tag == 34) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t init = parseExpr(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 0, .data.Let = {.mutable = mutable, .nameStart = nameTok.start, .nameLen = nameTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .init = init}});
}
uint64_t parsePrint(Comp* c) {
    Tok kw = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    uint64_t e = parseExpr(&((*c)));
    {
    Kind _m46 = Comp_curKind(&((*c)));
    if (_m46.tag == 26) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 2, .data.Print = {.expr = e, .offset = kw.start}});
}
uint64_t parsePanic(Comp* c) {
    Tok kw = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t msg = parseExpr(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 9, .data.Panic = {.msg = msg, .offset = kw.start}});
}
uint64_t parseReturn(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m47 = Comp_curKind(&((*c)));
    if (_m47.tag == 1) {
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    }
    else if (_m47.tag == 30) {
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    }
    else if (_m47.tag == 0) {
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    }
    else {
    uint64_t e = parseExpr(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = e, .hasValue = 1}});
    }
    }
}
uint64_t parseIf(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr(&((*c)));
    uint64_t thenBlk = parseBlock(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m48 = Comp_curKind(&((*c)));
    if (_m48.tag == 11) {
    Comp_advance(&((*c)));
    {
    Kind _m49 = Comp_curKind(&((*c)));
    if (_m49.tag == 10) {
    uint64_t nested = parseIf(&((*c)));
    PlewArray_U64 one = PlewArray_U64_new();
    PlewArray_U64_push(&(one), nested);
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_copy(one)});
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId, .hasElse = 1}});
    }
    else {
    uint64_t elseBlk = parseBlock(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk, .hasElse = 1}});
    }
    }
    }
    else {
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = 0, .hasElse = 0}});
    }
    }
}
uint64_t parseIfExpr(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr(&((*c)));
    uint64_t thenBlk = parseBlock(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m50 = Comp_curKind(&((*c)));
    if (_m50.tag == 11) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m51 = Comp_curKind(&((*c)));
    if (_m51.tag == 10) {
    uint64_t nested = parseIfExpr(&((*c)));
    PlewArray_U64 one = PlewArray_U64_new();
    PlewArray_U64_push(&(one), Comp_pushStmt(&((*c)), (Stmt){.tag = 10, .data.Give = {.value = nested}}));
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_copy(one)});
    return Comp_pushExpr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId}});
    }
    else {
    uint64_t elseBlk = parseBlock(&((*c)));
    return Comp_pushExpr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk}});
    }
    }
}
uint64_t parseGive(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t v = parseExpr(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 10, .data.Give = {.value = v}});
}
uint64_t parseWhile(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr(&((*c)));
    uint64_t body = parseBlock(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 6, .data.While = {.cond = cond, .body = body}});
}
uint64_t parseFor(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m52 = Comp_curKind(&((*c)));
    if (_m52.tag == 18) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m53 = Comp_curKind(&((*c)));
    if (_m53.tag == 20) {
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
    Kind _m54 = Comp_curKind(&((*c)));
    if (_m54.tag == 68) {
    Comp_advance(&((*c)));
    isRange = 1;
    hi = parseExpr(&((*c)));
    }
    else if (_m54.tag == 69) {
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
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 7, .data.For = {.varStart = nameTok.start, .varLen = nameTok.len, .isRange = isRange, .inclusive = inclusive, .iter = lo, .rangeHi = hi, .body = body}});
}
uint64_t parseExprOrAssign(Comp* c) {
    uint64_t lhs = parseExpr(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    if (isAssignOp(k)) {
    int64_t op = kindCode(k);
    Comp_advance(&((*c)));
    uint64_t rhs = parseExpr(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 1, .data.Assign = {.op = op, .target = lhs, .value = rhs}});
    }
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 3, .data.ExprStmt = {.expr = lhs}});
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
    Kind _m55 = Comp_curKind(&((*c)));
    if (_m55.tag == 33) {
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
    Kind _m56 = Comp_curKind(&((*c)));
    if (_m56.tag == 29) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m57 = Comp_curKind(&((*c)));
    if (_m57.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m57.tag == 0) {
    break;
    }
    else if (_m57.tag == 18) {
    Comp_advance(&((*c)));
    Tok bTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind_push(&(binds), (Bind){.nameStart = bTok.start, .nameLen = bTok.len, .fieldStart = bTok.start, .fieldLen = bTok.len});
    {
    Kind _m58 = Comp_curKind(&((*c)));
    if (_m58.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else if (_m57.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m59 = Comp_curKind(&((*c)));
    if (_m59.tag == 32) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m60 = Comp_curKind(&((*c)));
    if (_m60.tag == 18) {
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
    Kind _m61 = Comp_curKind(&((*c)));
    if (_m61.tag == 31) {
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
    return (PatInfo){.isWildcard = isWildcard, .enumStart = enumStart, .enumLen = enumLen, .variantStart = variantStart, .variantLen = variantLen, .binds = PlewArray_Bind_copy(binds)};
}
long long bindNamesMatch(Comp* c, PlewArray_Bind a, PlewArray_Bind b) {
    if ((long long)((a).len) != (long long)((b).len)) {
    return 0;
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
    return 0;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
}
PlewArray_PatInfo parseArmPatterns(Comp* c) {
    uint64_t startOff = Comp_cur(&((*c))).start;
    PlewArray_PatInfo pats = PlewArray_PatInfo_new();
    PlewArray_PatInfo_push(&(pats), parsePattern(&((*c))));
    while (1) {
    {
    Kind _m62 = Comp_curKind(&((*c)));
    if (_m62.tag == 50) {
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
    Kind _m63 = Comp_curKind(&((*c)));
    if (_m63.tag == 56) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t pi = 1;
    while (pi < (long long)((pats).len)) {
    PatInfo p0 = PlewArray_PatInfo_get(pats, (long long)(0));
    PatInfo pn = PlewArray_PatInfo_get(pats, (long long)(pi));
    if (bindNamesMatch(&((*c)), p0.binds, pn.binds)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), startOff), (PlewString){"or-pattern alternatives must bind the same names", 48});
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return PlewArray_PatInfo_copy(pats);
}
uint64_t parseMatch(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m64 = Comp_curKind(&((*c)));
    if (_m64.tag == 29) {
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
    Kind _m65 = k;
    if (_m65.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m65.tag == 0) {
    break;
    }
    else {
    PlewArray_PatInfo pats = parseArmPatterns(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock(&((*c)));
    {
    PlewArray_PatInfo __fa66 = pats;
    for (long long __fi66 = 0; __fi66 < __fa66.len; __fi66++) {
        PatInfo pi = PlewArray_PatInfo_get(__fa66, __fi66);
    PlewArray_MatchArm_push(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = PlewArray_Bind_copy(pi.binds), .body = body});
    }
    }
    }
    }
    }
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 8, .data.Match = {.scrut = scrut, .arms = PlewArray_MatchArm_copy(arms)}});
}
uint64_t parseMatchExpr(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m67 = Comp_curKind(&((*c)));
    if (_m67.tag == 29) {
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
    Kind _m68 = k;
    if (_m68.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m68.tag == 0) {
    break;
    }
    else {
    PlewArray_PatInfo pats = parseArmPatterns(&((*c)));
    uint64_t body = parseExpr(&((*c)));
    {
    PlewArray_PatInfo __fa69 = pats;
    for (long long __fi69 = 0; __fi69 < __fa69.len; __fi69++) {
        PatInfo pi = PlewArray_PatInfo_get(__fa69, __fi69);
    PlewArray_MatchArm_push(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = PlewArray_Bind_copy(pi.binds), .body = body});
    }
    }
    {
    Kind _m70 = Comp_curKind(&((*c)));
    if (_m70.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    return Comp_pushExpr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = scrut, .arms = PlewArray_MatchArm_copy(arms)}});
}
uint64_t parseStmt(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m71 = k;
    if (_m71.tag == 18) {
    return parseLet(&((*c)), 0);
    }
    else if (_m71.tag == 19) {
    Comp_advance(&((*c)));
    return parseLet(&((*c)), 1);
    }
    else if (_m71.tag == 10) {
    return parseIf(&((*c)));
    }
    else if (_m71.tag == 12) {
    return parseWhile(&((*c)));
    }
    else if (_m71.tag == 13) {
    return parseFor(&((*c)));
    }
    else if (_m71.tag == 9) {
    return parseMatch(&((*c)));
    }
    else if (_m71.tag == 14) {
    Comp_advance(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 11});
    }
    else if (_m71.tag == 15) {
    Comp_advance(&((*c)));
    return Comp_pushStmt(&((*c)), (Stmt){.tag = 12});
    }
    else if (_m71.tag == 16) {
    return parseReturn(&((*c)));
    }
    else if (_m71.tag == 5) {
    if (Comp_identIs(&((*c)), (PlewString){"print", 5})) {
    {
    Kind _m72 = Comp_peekKind(&((*c)), 1);
    if (_m72.tag == 25) {
    return parsePrint(&((*c)));
    }
    else {
    return parseExprOrAssign(&((*c)));
    }
    }
    }
    if (Comp_identIs(&((*c)), (PlewString){"panic", 5})) {
    return parsePanic(&((*c)));
    }
    return parseExprOrAssign(&((*c)));
    }
    else if (_m71.tag == 17) {
    return parseGive(&((*c)));
    }
    else {
    return parseExprOrAssign(&((*c)));
    }
    }
}
uint64_t parseBlock(Comp* c) {
    {
    Kind _m73 = Comp_curKind(&((*c)));
    if (_m73.tag == 29) {
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
    Kind _m74 = k;
    if (_m74.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m74.tag == 0) {
    break;
    }
    else {
    uint64_t s = parseStmt(&((*c)));
    PlewArray_U64_push(&(stmts), s);
    }
    }
    }
    uint64_t id = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_copy(stmts)});
    return id;
}
PlewArray_Param parseParamList(Comp* c) {
    PlewArray_Param params = PlewArray_Param_new();
    {
    Kind _m75 = Comp_curKind(&((*c)));
    if (_m75.tag == 25) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m76 = k;
    if (_m76.tag == 26) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m76.tag == 0) {
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
    Kind _m77 = Comp_curKind(&((*c)));
    if (_m77.tag == 54) {
    if ((Comp_peekKind(&((*c)), 1)).tag == 32) {
    Comp_advance(&((*c)));
    pNoLabel = 1;
    }
    }
    else {
    }
    }
    {
    Kind _m78 = Comp_curKind(&((*c)));
    if (_m78.tag == 32) {
    Comp_advance(&((*c)));
    {
    Kind _m79 = Comp_curKind(&((*c)));
    if (_m79.tag == 22) {
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
    Kind _m80 = Comp_curKind(&((*c)));
    if (_m80.tag == 34) {
    Comp_advance(&((*c)));
    pHasDefault = 1;
    pDefault = parseExpr(&((*c)));
    }
    else {
    }
    }
    PlewArray_Param_push(&(params), (Param){.nameStart = pTok.start, .nameLen = pTok.len, .tyStart = pTyStart, .tyLen = pTyLen, .tyIsArray = pTyIsArray, .ty = pTyRef, .isInout = pIsInout, .noLabel = pNoLabel, .hasDefault = pHasDefault, .defaultExpr = pDefault});
    {
    Kind _m81 = Comp_curKind(&((*c)));
    if (_m81.tag == 31) {
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
    return PlewArray_Param_copy(params);
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
    Kind _m82 = Comp_curKind(&((*c)));
    if (_m82.tag == 55) {
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
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_copy(typeParams), .params = PlewArray_Param_copy(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body, .hasRecv = hasRecv, .recvStart = recvStart, .recvLen = recvLen, .selfInout = selfInout});
}
void parseFunc(Comp* c) {
    Comp_advance(&((*c)));
    PlewArray_Bind noParams = PlewArray_Bind_new();
    parseFuncCommon(&((*c)), 0, 0, 0, 0, noParams);
}
void parseImpl(Comp* c) {
    Comp_advance(&((*c)));
    PlewArray_Bind implParams = parseTypeParams(&((*c)));
    PType recvPty = parseTypeTok(&((*c)));
    uint64_t recvStart = recvPty.start;
    uint64_t recvLen = recvPty.len;
    {
    Kind _m83 = Comp_curKind(&((*c)));
    if (_m83.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m84 = k;
    if (_m84.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m84.tag == 0) {
    break;
    }
    else if (_m84.tag == 22) {
    Comp_advance(&((*c)));
    {
    Kind _m85 = Comp_curKind(&((*c)));
    if (_m85.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon(&((*c)), 1, recvStart, recvLen, 1, implParams);
    }
    else if (_m84.tag == 6) {
    Comp_advance(&((*c)));
    parseFuncCommon(&((*c)), 1, recvStart, recvLen, 0, implParams);
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
}
void parseStruct(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind typeParams = parseTypeParams(&((*c)));
    {
    Kind _m86 = Comp_curKind(&((*c)));
    if (_m86.tag == 29) {
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
    Kind _m87 = k;
    if (_m87.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m87.tag == 0) {
    break;
    }
    else {
    long long isMut = 0;
    {
    Kind _m88 = Comp_curKind(&((*c)));
    if (_m88.tag == 19) {
    Comp_advance(&((*c)));
    isMut = 1;
    }
    else {
    }
    }
    {
    Kind _m89 = Comp_curKind(&((*c)));
    if (_m89.tag == 18) {
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
    Kind _m90 = Comp_curKind(&((*c)));
    if (_m90.tag == 32) {
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
    PlewArray_StructDef_push(&((*c).structs), (StructDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_copy(typeParams), .fields = PlewArray_FieldDef_copy(fields)});
}
void parseEnum(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind typeParams = parseTypeParams(&((*c)));
    {
    Kind _m91 = Comp_curKind(&((*c)));
    if (_m91.tag == 29) {
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
    Kind _m92 = k;
    if (_m92.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m92.tag == 0) {
    break;
    }
    else if (_m92.tag == 5) {
    Tok vTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_new();
    {
    Kind _m93 = Comp_curKind(&((*c)));
    if (_m93.tag == 29) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m94 = Comp_curKind(&((*c)));
    if (_m94.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m94.tag == 0) {
    break;
    }
    else if (_m94.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyStart = 0;
    uint64_t tyLen = 0;
    long long tyIsArray = 0;
    uint64_t tyRef = 0;
    {
    Kind _m95 = Comp_curKind(&((*c)));
    if (_m95.tag == 32) {
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
    Kind _m96 = Comp_curKind(&((*c)));
    if (_m96.tag == 31) {
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
    PlewArray_Variant_push(&(variants), (Variant){.nameStart = vTok.start, .nameLen = vTok.len, .fields = PlewArray_FieldDef_copy(fields)});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    PlewArray_EnumDef_push(&((*c).enums), (EnumDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_copy(typeParams), .variants = PlewArray_Variant_copy(variants)});
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
    Kind _m97 = k;
    if (_m97.tag == 1) {
    break;
    }
    else if (_m97.tag == 0) {
    break;
    }
    else if (_m97.tag == 29) {
    break;
    }
    else if (_m97.tag == 5) {
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
    Kind _m98 = Comp_curKind(&((*c)));
    if (_m98.tag == 29) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m99 = k;
    if (_m99.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m99.tag == 0) {
    break;
    }
    else if (_m99.tag == 31) {
    Comp_advance(&((*c)));
    }
    else if (_m99.tag == 5) {
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
    Kind _m100 = k;
    if (_m100.tag == 6) {
    parseFunc(&((*c)));
    }
    else if (_m100.tag == 7) {
    parseStruct(&((*c)));
    }
    else if (_m100.tag == 8) {
    parseEnum(&((*c)));
    }
    else if (_m100.tag == 5) {
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
    else if (_m100.tag == 0) {
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
    return (PlewString){"0", 1};
    }
    if (d == 1) {
    return (PlewString){"1", 1};
    }
    if (d == 2) {
    return (PlewString){"2", 1};
    }
    if (d == 3) {
    return (PlewString){"3", 1};
    }
    if (d == 4) {
    return (PlewString){"4", 1};
    }
    if (d == 5) {
    return (PlewString){"5", 1};
    }
    if (d == 6) {
    return (PlewString){"6", 1};
    }
    if (d == 7) {
    return (PlewString){"7", 1};
    }
    if (d == 8) {
    return (PlewString){"8", 1};
    }
    return (PlewString){"9", 1};
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
    return (PlewString){"0", 1};
    }
    if (d == 1) {
    return (PlewString){"1", 1};
    }
    if (d == 2) {
    return (PlewString){"2", 1};
    }
    if (d == 3) {
    return (PlewString){"3", 1};
    }
    if (d == 4) {
    return (PlewString){"4", 1};
    }
    if (d == 5) {
    return (PlewString){"5", 1};
    }
    if (d == 6) {
    return (PlewString){"6", 1};
    }
    if (d == 7) {
    return (PlewString){"7", 1};
    }
    if (d == 8) {
    return (PlewString){"8", 1};
    }
    return (PlewString){"9", 1};
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
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I64", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U16", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U32", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U64", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"Bool", 4})) {
    return 1;
    }
    return 0;
}
long long isIntType(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I8", 2})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I64", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U16", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U32", 3})) {
    return 1;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U64", 3})) {
    return 1;
    }
    return 0;
}
uint64_t intBits(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I8", 2})) {
    return 8;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    return 8;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    return 16;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U16", 3})) {
    return 16;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    return 32;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U32", 3})) {
    return 32;
    }
    return 64;
}
long long intSigned(Comp* c, uint64_t start, uint64_t len) {
    return (PlewArray_U8_get((*c).bytes, (long long)(start)) == 73);
}
long long losslessInt(Comp* c, uint64_t srcStart, uint64_t srcLen, uint64_t dstStart, uint64_t dstLen) {
    uint64_t sBits = intBits(&((*c)), srcStart, srcLen);
    uint64_t dBits = intBits(&((*c)), dstStart, dstLen);
    long long sSigned = intSigned(&((*c)), srcStart, srcLen);
    long long dSigned = intSigned(&((*c)), dstStart, dstLen);
    if (sSigned) {
    if (dSigned) {
    return (dBits >= sBits);
    }
    return 0;
    }
    if (dSigned) {
    return (dBits > sBits);
    }
    return (dBits >= sBits);
}
long long litFitsType(Comp* c, int64_t value, uint64_t dstStart, uint64_t dstLen) {
    uint64_t bits = intBits(&((*c)), dstStart, dstLen);
    long long sgn = intSigned(&((*c)), dstStart, dstLen);
    return litFitsBits(value, bits, sgn);
}
long long litFitsBits(int64_t value, uint64_t bits, long long sgn) {
    if (sgn) {
    if (bits == 8) {
    if (value < (0 - 128)) {
    return 0;
    }
    if (value > 127) {
    return 0;
    }
    return 1;
    }
    if (bits == 16) {
    if (value < (0 - 32768)) {
    return 0;
    }
    if (value > 32767) {
    return 0;
    }
    return 1;
    }
    if (bits == 32) {
    if (value < (0 - 2147483648)) {
    return 0;
    }
    if (value > 2147483647) {
    return 0;
    }
    return 1;
    }
    return 1;
    }
    if (value < 0) {
    return 0;
    }
    if (bits == 8) {
    if (value > 255) {
    return 0;
    }
    return 1;
    }
    if (bits == 16) {
    if (value > 65535) {
    return 0;
    }
    return 1;
    }
    if (bits == 32) {
    if (value > 4294967295) {
    return 0;
    }
    return 1;
    }
    return 1;
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
    return 0;
    }
    uint64_t j = 0;
    while (j < aLen) {
    if (PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((aStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((bStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })))) {
    return 0;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
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
    return line;
}
uint64_t exprOffset(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m101 = e;
    if (_m101.tag == 0) {
        uint64_t offset = _m101.data.Int.offset;
        (void)offset;
    return offset;
    }
    else if (_m101.tag == 1) {
        uint64_t start = _m101.data.Ident.start;
        (void)start;
        uint64_t len = _m101.data.Ident.len;
        (void)len;
    return start;
    }
    else if (_m101.tag == 7) {
        uint64_t start = _m101.data.Str.start;
        (void)start;
        uint64_t len = _m101.data.Str.len;
        (void)len;
    return start;
    }
    else if (_m101.tag == 4) {
        uint64_t nameStart = _m101.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m101.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m101.data.Call.args;
        (void)args;
    return nameStart;
    }
    else if (_m101.tag == 10) {
        uint64_t recv = _m101.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m101.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m101.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m101.data.Method.args;
        (void)args;
    return nameStart;
    }
    else if (_m101.tag == 5) {
        uint64_t base = _m101.data.Field.base;
        (void)base;
        uint64_t nameStart = _m101.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m101.data.Field.nameLen;
        (void)nameLen;
    return exprOffset(&((*c)), base);
    }
    else if (_m101.tag == 9) {
        uint64_t base = _m101.data.Index.base;
        (void)base;
        uint64_t index = _m101.data.Index.index;
        (void)index;
    return exprOffset(&((*c)), base);
    }
    else if (_m101.tag == 3) {
        int64_t op = _m101.data.Binary.op;
        (void)op;
        uint64_t lhs = _m101.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m101.data.Binary.rhs;
        (void)rhs;
    return exprOffset(&((*c)), lhs);
    }
    else if (_m101.tag == 2) {
        int64_t op = _m101.data.Unary.op;
        (void)op;
        uint64_t operand = _m101.data.Unary.operand;
        (void)operand;
    return exprOffset(&((*c)), operand);
    }
    else if (_m101.tag == 11) {
        uint64_t operand = _m101.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m101.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m101.data.Cast.tyLen;
        (void)tyLen;
    return exprOffset(&((*c)), operand);
    }
    else if (_m101.tag == 6) {
        uint64_t typeStart = _m101.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m101.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m101.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m101.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m101.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m101.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m101.data.Make.fields;
        (void)fields;
    return typeStart;
    }
    else if (_m101.tag == 12) {
        uint64_t scrut = _m101.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m101.data.MatchExpr.arms;
        (void)arms;
    return exprOffset(&((*c)), scrut);
    }
    else if (_m101.tag == 13) {
        uint64_t cond = _m101.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m101.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m101.data.IfExpr.elseBlk;
        (void)elseBlk;
    return exprOffset(&((*c)), cond);
    }
    else if (_m101.tag == 14) {
        uint64_t opt = _m101.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m101.data.Coalesce.deflt;
        (void)deflt;
    return exprOffset(&((*c)), opt);
    }
    else if (_m101.tag == 15) {
        uint64_t expr = _m101.data.Try.expr;
        (void)expr;
    return exprOffset(&((*c)), expr);
    }
    else if (_m101.tag == 16) {
        uint64_t base = _m101.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m101.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m101.data.Arrow.nameLen;
        (void)nameLen;
    return exprOffset(&((*c)), base);
    }
    else if (_m101.tag == 17) {
        PlewArray_Param params = _m101.data.Closure.params;
        (void)params;
        long long hasRet = _m101.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m101.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m101.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m101.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m101.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m101.data.Closure.body;
        (void)body;
    return retStart;
    }
    else {
    return 0;
    }
    }
}
uint64_t findFunc(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(i));
    if (f.hasRecv) {
    }
    else {
    if (spansEqual(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    return i;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return (long long)(((*c).funcs).len);
}
uint64_t findMethod(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(i));
    if (f.hasRecv) {
    if (spansEqual(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (spansEqual(&((*c)), recvStart, recvLen, f.recvStart, f.recvLen)) {
    return i;
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return (long long)(((*c).funcs).len);
}
long long paramsLabelsOk(Comp* c, PlewArray_Param params, PlewArray_Arg args) {
    if ((long long)((args).len) > (long long)((params).len)) {
    return 0;
    }
    uint64_t r = (long long)((args).len);
    while (r < (long long)((params).len)) {
    if (PlewArray_Param_get(params, (long long)(r)).hasDefault) {
    }
    else {
    return 0;
    }
    r = ({ uint64_t __ov; if (__builtin_add_overflow((r), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    Arg a = PlewArray_Arg_get(args, (long long)(i));
    Param p = PlewArray_Param_get(params, (long long)(i));
    if (p.noLabel) {
    if (a.hasLabel) {
    return 0;
    }
    }
    else {
    if (a.hasLabel) {
    if (spansEqual(&((*c)), a.labelStart, a.labelLen, p.nameStart, p.nameLen)) {
    }
    else {
    return 0;
    }
    }
    else {
    return 0;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
}
long long callLabelsOk(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t fi = findFunc(&((*c)), nameStart, nameLen);
    if (fi == (long long)(((*c).funcs).len)) {
    return 1;
    }
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
    return paramsLabelsOk(&((*c)), f.params, args);
}
long long armCovers(Comp* c, PlewArray_MatchArm arms, uint64_t variantStart, uint64_t variantLen) {
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = PlewArray_MatchArm_get(arms, (long long)(i));
    if (a.isWildcard) {
    return 1;
    }
    if (spansEqual(&((*c)), a.variantStart, a.variantLen, variantStart, variantLen)) {
    return 1;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
long long matchExhaustive(Comp* c, PlewArray_MatchArm arms) {
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = PlewArray_MatchArm_get(arms, (long long)(i));
    if (a.isWildcard) {
    return 1;
    }
    if (enumLen == 0) {
    enumStart = a.enumStart;
    enumLen = a.enumLen;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (enumLen == 0) {
    return 1;
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (armCovers(&((*c)), arms, v.nameStart, v.nameLen)) {
    }
    else {
    return 0;
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
}
uint64_t variantIndex(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    return vi;
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
TypeInfo scalarInfo(void) {
    return (TypeInfo){.kind = 0, .nameStart = 0, .nameLen = 0, .ref = 0};
}
TypeInfo typeInfoOfName(Comp* c, uint64_t start, uint64_t len, long long isArray) {
    if (isArray) {
    return (TypeInfo){.kind = 3, .nameStart = start, .nameLen = len, .ref = 0};
    }
    if (len == 0) {
    return scalarInfo();
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"String", 6})) {
    return (TypeInfo){.kind = 1, .nameStart = start, .nameLen = len, .ref = 0};
    }
    if (isPrimType(&((*c)), start, len)) {
    return (TypeInfo){.kind = 0, .nameStart = start, .nameLen = len, .ref = 0};
    }
    return (TypeInfo){.kind = 2, .nameStart = start, .nameLen = len, .ref = 0};
}
void addLocal(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut) {
    PlewArray_Local_push(&((*c).locals), (Local){.nameStart = nameStart, .nameLen = nameLen, .tyStart = tyStart, .tyLen = tyLen, .isArray = isArray, .ty = ty, .isInout = isInout, .isMut = isMut});
}
uint64_t scopeMark(Comp* c) {
    return (long long)(((*c).locals).len);
}
void emitScopeDrops(Comp* c, uint64_t mark) {
}
void popLocals(Comp* c, uint64_t mark) {
    PlewArray_Local kept = PlewArray_Local_new();
    uint64_t i = 0;
    while (i < mark) {
    PlewArray_Local_push(&(kept), PlewArray_Local_get((*c).locals, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).locals = PlewArray_Local_copy(kept);
}
void scopeExit(Comp* c, uint64_t mark) {
    emitScopeDrops(&((*c)), mark);
    popLocals(&((*c)), mark);
}
long long localIsMutable(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef(&((*c)), start, len)) {
    return (*c).curSelfInout;
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (lo.isMut) {
    return 1;
    }
    return lo.isInout;
    }
    }
    return 1;
}
long long isSelfRef(Comp* c, uint64_t start, uint64_t len) {
    if ((*c).curHasRecv) {
    return rangeEquals((*c).bytes, start, len, (PlewString){"self", 4});
    }
    return 0;
}
long long isInoutLocal(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef(&((*c)), start, len)) {
    return (*c).curSelfInout;
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    return lo.isInout;
    }
    }
    return 0;
}
TypeInfo fieldType(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    return typeInfoOfName(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return scalarInfo();
}
long long fieldDeclaredMut(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    return f.isMut;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
}
long long placeIsMutable(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m102 = e;
    if (_m102.tag == 1) {
        uint64_t start = _m102.data.Ident.start;
        (void)start;
        uint64_t len = _m102.data.Ident.len;
        (void)len;
    return localIsMutable(&((*c)), start, len);
    }
    else if (_m102.tag == 5) {
        uint64_t base = _m102.data.Field.base;
        (void)base;
        uint64_t nameStart = _m102.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m102.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 2) {
    if (fieldDeclaredMut(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen)) {
    return placeIsMutable(&((*c)), base);
    }
    return 0;
    }
    return placeIsMutable(&((*c)), base);
    }
    else if (_m102.tag == 9) {
        uint64_t base = _m102.data.Index.base;
        (void)base;
        uint64_t index = _m102.data.Index.index;
        (void)index;
    return placeIsMutable(&((*c)), base);
    }
    else if (_m102.tag == 16) {
        uint64_t base = _m102.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m102.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m102.data.Arrow.nameLen;
        (void)nameLen;
    return 1;
    }
    else {
    return 1;
    }
    }
}
TypeInfo exprType(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m103 = e;
    if (_m103.tag == 0) {
        uint64_t tyStart = _m103.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m103.data.Int.tyLen;
        (void)tyLen;
    if (tyLen != 0) {
    return typeInfoOfName(&((*c)), tyStart, tyLen, 0);
    }
    return scalarInfo();
    }
    else if (_m103.tag == 7) {
        uint64_t start = _m103.data.Str.start;
        (void)start;
        uint64_t len = _m103.data.Str.len;
        (void)len;
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    }
    else if (_m103.tag == 1) {
        uint64_t start = _m103.data.Ident.start;
        (void)start;
        uint64_t len = _m103.data.Ident.len;
        (void)len;
    if (isSelfRef(&((*c)), start, len)) {
    if ((*c).curRecvInstRef != 0) {
    TypeRef rt = PlewArray_TypeRef_get((*c).types, (long long)((*c).curRecvInstRef));
    return (TypeInfo){.kind = 2, .nameStart = rt.nameStart, .nameLen = rt.nameLen, .ref = (*c).curRecvInstRef};
    }
    return typeInfoOfName(&((*c)), (*c).curRecvStart, (*c).curRecvLen, 0);
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (isGenericInst(&((*c)), lo.ty)) {
    TypeRef lt = PlewArray_TypeRef_get((*c).types, (long long)(lo.ty));
    return (TypeInfo){.kind = 2, .nameStart = lt.nameStart, .nameLen = lt.nameLen, .ref = lo.ty};
    }
    if (isRefInst(&((*c)), lo.ty)) {
    TypeRef lt2 = PlewArray_TypeRef_get((*c).types, (long long)(lo.ty));
    return (TypeInfo){.kind = 2, .nameStart = lt2.nameStart, .nameLen = lt2.nameLen, .ref = lo.ty};
    }
    return typeInfoOfName(&((*c)), lo.tyStart, lo.tyLen, lo.isArray);
    }
    }
    return scalarInfo();
    }
    else if (_m103.tag == 2) {
        int64_t op = _m103.data.Unary.op;
        (void)op;
        uint64_t operand = _m103.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    return exprType(&((*c)), operand);
    }
    if (op == 79) {
    return exprType(&((*c)), operand);
    }
    return scalarInfo();
    }
    else if (_m103.tag == 3) {
        int64_t op = _m103.data.Binary.op;
        (void)op;
        uint64_t lhs = _m103.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m103.data.Binary.rhs;
        (void)rhs;
    if (op >= 56) {
    if (op <= 60) {
    return exprType(&((*c)), lhs);
    }
    }
    if (op >= 74) {
    if (op <= 78) {
    return exprType(&((*c)), lhs);
    }
    }
    return scalarInfo();
    }
    else if (_m103.tag == 4) {
        uint64_t nameStart = _m103.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m103.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m103.data.Call.args;
        (void)args;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readStdin", 9})) {
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFile", 8})) {
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFileBytes", 13})) {
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argAt", 5})) {
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    }
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    if (f.hasRet) {
    if (isGenericInst(&((*c)), f.retTy)) {
    TypeRef rtr = PlewArray_TypeRef_get((*c).types, (long long)(f.retTy));
    return (TypeInfo){.kind = 2, .nameStart = rtr.nameStart, .nameLen = rtr.nameLen, .ref = f.retTy};
    }
    return typeInfoOfName(&((*c)), f.retStart, f.retLen, f.retIsArray);
    }
    return scalarInfo();
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return scalarInfo();
    }
    else if (_m103.tag == 5) {
        uint64_t base = _m103.data.Field.base;
        (void)base;
        uint64_t nameStart = _m103.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m103.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (isGenericInst(&((*c)), bt.ref)) {
    return genericFieldTypeInfo(&((*c)), bt.ref, nameStart, nameLen);
    }
    if (bt.kind == 2) {
    return fieldType(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    }
    return scalarInfo();
    }
    else if (_m103.tag == 6) {
        uint64_t typeStart = _m103.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m103.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m103.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m103.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m103.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m103.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m103.data.Make.fields;
        (void)fields;
    if (isGenericInst(&((*c)), ty)) {
    return (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = ty};
    }
    return (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = 0};
    }
    else if (_m103.tag == 8) {
        PlewArray_U64 elems = _m103.data.Array.elems;
        (void)elems;
    return scalarInfo();
    }
    else if (_m103.tag == 9) {
        uint64_t base = _m103.data.Index.base;
        (void)base;
        uint64_t index = _m103.data.Index.index;
        (void)index;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    return typeInfoOfName(&((*c)), bt.nameStart, bt.nameLen, 0);
    }
    return scalarInfo();
    }
    else if (_m103.tag == 10) {
        uint64_t recv = _m103.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m103.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m103.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m103.data.Method.args;
        (void)args;
    TypeInfo rt = exprType(&((*c)), recv);
    if (rt.kind == 2) {
    uint64_t mi = findMethod(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen);
    if (mi == (long long)(((*c).funcs).len)) {
    return scalarInfo();
    }
    Func mf = PlewArray_Func_get((*c).funcs, (long long)(mi));
    if (mf.hasRet) {
    return typeInfoOfName(&((*c)), mf.retStart, mf.retLen, mf.retIsArray);
    }
    return scalarInfo();
    }
    return scalarInfo();
    }
    else if (_m103.tag == 11) {
        uint64_t operand = _m103.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m103.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m103.data.Cast.tyLen;
        (void)tyLen;
    return typeInfoOfName(&((*c)), tyStart, tyLen, 0);
    }
    else if (_m103.tag == 12) {
        uint64_t scrut = _m103.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m103.data.MatchExpr.arms;
        (void)arms;
    if ((long long)((arms).len) > 0) {
    return exprType(&((*c)), PlewArray_MatchArm_get(arms, (long long)(0)).body);
    }
    return scalarInfo();
    }
    else if (_m103.tag == 13) {
        uint64_t cond = _m103.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m103.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m103.data.IfExpr.elseBlk;
        (void)elseBlk;
    uint64_t g = blockGiveExpr(&((*c)), thenBlk);
    if (g < (long long)(((*c).exprs).len)) {
    return exprType(&((*c)), g);
    }
    return scalarInfo();
    }
    else if (_m103.tag == 14) {
        uint64_t opt = _m103.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m103.data.Coalesce.deflt;
        (void)deflt;
    return exprType(&((*c)), deflt);
    }
    else if (_m103.tag == 15) {
        uint64_t expr = _m103.data.Try.expr;
        (void)expr;
    TypeInfo rt = exprType(&((*c)), expr);
    if (isGenericInst(&((*c)), rt.ref)) {
    TypeRef inst = PlewArray_TypeRef_get((*c).types, (long long)(rt.ref));
    if ((long long)((inst.args).len) > 0) {
    return typeInfoOfRef(&((*c)), PlewArray_U64_get(inst.args, (long long)(0)));
    }
    }
    return scalarInfo();
    }
    else if (_m103.tag == 16) {
        uint64_t base = _m103.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m103.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m103.data.Arrow.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (isRefInst(&((*c)), bt.ref)) {
    TypeRef inst = PlewArray_TypeRef_get((*c).types, (long long)(bt.ref));
    TypeInfo pt = typeInfoOfRef(&((*c)), PlewArray_U64_get(inst.args, (long long)(0)));
    if (pt.kind == 2) {
    return fieldType(&((*c)), pt.nameStart, pt.nameLen, nameStart, nameLen);
    }
    }
    return scalarInfo();
    }
    else if (_m103.tag == 17) {
        PlewArray_Param params = _m103.data.Closure.params;
        (void)params;
        long long hasRet = _m103.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m103.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m103.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m103.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m103.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m103.data.Closure.body;
        (void)body;
    return scalarInfo();
    }
    else { __builtin_unreachable(); }
    }
    return scalarInfo();
}
uint64_t blockGiveExpr(Comp* c, uint64_t blkId) {
    Block blk = PlewArray_Block_get((*c).blocks, (long long)(blkId));
    PlewArray_U64 stmts = PlewArray_U64_copy(blk.stmts);
    uint64_t i = 0;
    uint64_t found = (long long)(((*c).exprs).len);
    while (i < (long long)((stmts).len)) {
    Stmt s = PlewArray_Stmt_get((*c).stmts, (long long)(PlewArray_U64_get(stmts, (long long)(i))));
    {
    Stmt _m104 = s;
    if (_m104.tag == 10) {
        uint64_t value = _m104.data.Give.value;
        (void)value;
    found = value;
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return found;
}
void addBindLocal(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    addLocal(&((*c)), bindStart, bindLen, f.tyStart, f.tyLen, f.tyIsArray, f.ty, 0, 0);
    return;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void genBindType(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, bindStart, bindLen)) {
    genCTypeRef(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    return;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"long long", 9});
}
PlewString binOpStr(int64_t op) {
    if (op == 56) {
    return (PlewString){" + ", 3};
    }
    if (op == 57) {
    return (PlewString){" - ", 3};
    }
    if (op == 58) {
    return (PlewString){" * ", 3};
    }
    if (op == 59) {
    return (PlewString){" / ", 3};
    }
    if (op == 60) {
    return (PlewString){" % ", 3};
    }
    if (op == 50) {
    return (PlewString){" == ", 4};
    }
    if (op == 51) {
    return (PlewString){" != ", 4};
    }
    if (op == 52) {
    return (PlewString){" < ", 3};
    }
    if (op == 53) {
    return (PlewString){" <= ", 4};
    }
    if (op == 54) {
    return (PlewString){" > ", 3};
    }
    if (op == 55) {
    return (PlewString){" >= ", 4};
    }
    if (op == 61) {
    return (PlewString){" && ", 4};
    }
    if (op == 62) {
    return (PlewString){" || ", 4};
    }
    if (op == 74) {
    return (PlewString){" & ", 3};
    }
    if (op == 75) {
    return (PlewString){" | ", 3};
    }
    if (op == 76) {
    return (PlewString){" ^ ", 3};
    }
    if (op == 77) {
    return (PlewString){" << ", 4};
    }
    if (op == 78) {
    return (PlewString){" >> ", 4};
    }
    return (PlewString){" ? ", 3};
}
PlewString unaryOpStr(int64_t op) {
    if (op == 57) {
    return (PlewString){"-", 1};
    }
    if (op == 79) {
    return (PlewString){"~", 1};
    }
    return (PlewString){"!", 1};
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
    return n;
}
long long isCheckedArith(int64_t op) {
    if (op == 56) {
    return 1;
    }
    if (op == 57) {
    return 1;
    }
    if (op == 58) {
    return 1;
    }
    return 0;
}
int64_t compoundCheckedBin(int64_t op) {
    if (op == 67) {
    return 56;
    }
    if (op == 68) {
    return 57;
    }
    if (op == 69) {
    return 58;
    }
    return 0;
}
PlewString overflowBuiltin(int64_t op) {
    if (op == 56) {
    return (PlewString){"__builtin_add_overflow", 22};
    }
    if (op == 57) {
    return (PlewString){"__builtin_sub_overflow", 22};
    }
    return (PlewString){"__builtin_mul_overflow", 22};
}
TypeInfo arithIntType(Comp* c, uint64_t lhs, uint64_t rhs) {
    TypeInfo lt = exprType(&((*c)), lhs);
    if (lt.kind == 0) {
    if (isIntType(&((*c)), lt.nameStart, lt.nameLen)) {
    return lt;
    }
    }
    TypeInfo rt = exprType(&((*c)), rhs);
    if (rt.kind == 0) {
    if (isIntType(&((*c)), rt.nameStart, rt.nameLen)) {
    return rt;
    }
    }
    return scalarInfo();
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
    return (PlewString){"INT8_MIN", 8};
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I16", 3})) {
    return (PlewString){"INT16_MIN", 9};
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"I32", 3})) {
    return (PlewString){"INT32_MIN", 9};
    }
    return (PlewString){"INT64_MIN", 9};
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
    return (PlewString){" = ", 3};
    }
    if (op == 67) {
    return (PlewString){" += ", 4};
    }
    if (op == 68) {
    return (PlewString){" -= ", 4};
    }
    if (op == 69) {
    return (PlewString){" *= ", 4};
    }
    if (op == 70) {
    return (PlewString){" /= ", 4};
    }
    if (op == 71) {
    return (PlewString){" %= ", 4};
    }
    if (op == 80) {
    return (PlewString){" &= ", 4};
    }
    if (op == 81) {
    return (PlewString){" |= ", 4};
    }
    if (op == 82) {
    return (PlewString){" ^= ", 4};
    }
    if (op == 83) {
    return (PlewString){" <<= ", 5};
    }
    return (PlewString){" >>= ", 5};
}
long long isCompoundDiv(int64_t op) {
    if (op == 70) {
    return 1;
    }
    if (op == 71) {
    return 1;
    }
    return 0;
}
PlewString compoundDivFn(int64_t op) {
    if (op == 70) {
    return (PlewString){"plew_div(", 9};
    }
    if (op == 71) {
    return (PlewString){"plew_mod(", 9};
    }
    return (PlewString){"", 0};
}
PlewString assignToBinStr(int64_t op) {
    if (op == 67) {
    return (PlewString){" + ", 3};
    }
    if (op == 68) {
    return (PlewString){" - ", 3};
    }
    if (op == 69) {
    return (PlewString){" * ", 3};
    }
    if (op == 70) {
    return (PlewString){" / ", 3};
    }
    if (op == 71) {
    return (PlewString){" % ", 3};
    }
    if (op == 80) {
    return (PlewString){" & ", 3};
    }
    if (op == 81) {
    return (PlewString){" | ", 3};
    }
    if (op == 82) {
    return (PlewString){" ^ ", 3};
    }
    if (op == 83) {
    return (PlewString){" << ", 4};
    }
    return (PlewString){" >> ", 4};
}
ConstInt notConst(void) {
    return (ConstInt){.isConst = 0, .value = 0};
}
ConstInt foldConst(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m105 = e;
    if (_m105.tag == 0) {
        int64_t value = _m105.data.Int.value;
        (void)value;
        long long isBool = _m105.data.Int.isBool;
        (void)isBool;
    if (isBool) {
    return notConst();
    }
    return (ConstInt){.isConst = 1, .value = value};
    }
    else if (_m105.tag == 2) {
        int64_t op = _m105.data.Unary.op;
        (void)op;
        uint64_t operand = _m105.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    ConstInt o = foldConst(&((*c)), operand);
    if (o.isConst) {
    return (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_sub_overflow((0), (o.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    }
    }
    return notConst();
    }
    else if (_m105.tag == 3) {
        int64_t op = _m105.data.Binary.op;
        (void)op;
        uint64_t lhs = _m105.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m105.data.Binary.rhs;
        (void)rhs;
    ConstInt a = foldConst(&((*c)), lhs);
    ConstInt b = foldConst(&((*c)), rhs);
    if (a.isConst) {
    if (b.isConst) {
    if (op == 56) {
    return (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_add_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    }
    if (op == 57) {
    return (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_sub_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    }
    if (op == 58) {
    return (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_mul_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    }
    }
    }
    return notConst();
    }
    else {
    return notConst();
    }
    }
}
long long tiIsInt(Comp* c, TypeInfo ti) {
    if (ti.kind == 0) {
    if (ti.nameLen != 0) {
    return isIntType(&((*c)), ti.nameStart, ti.nameLen);
    }
    }
    return 0;
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
    Expr _m106 = e;
    if (_m106.tag == 0) {
        int64_t value = _m106.data.Int.value;
        (void)value;
        uint64_t offset = _m106.data.Int.offset;
        (void)offset;
        long long isBool = _m106.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m106.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m106.data.Int.tyLen;
        (void)tyLen;
    checkLitLeaf(&((*c)), value, offset, isBool, tyStart, tyLen, eKind, eBits, eSgn);
    }
    else if (_m106.tag == 2) {
        int64_t op = _m106.data.Unary.op;
        (void)op;
        uint64_t operand = _m106.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    Expr oe = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m107 = oe;
    if (_m107.tag == 0) {
        int64_t value = _m107.data.Int.value;
        (void)value;
        uint64_t offset = _m107.data.Int.offset;
        (void)offset;
        long long isBool = _m107.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m107.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m107.data.Int.tyLen;
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
    else if (_m106.tag == 3) {
        int64_t op = _m106.data.Binary.op;
        (void)op;
        uint64_t lhs = _m106.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m106.data.Binary.rhs;
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
    else if (_m106.tag == 4) {
        uint64_t nameStart = _m106.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m106.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m106.data.Call.args;
        (void)args;
    checkCallArgs(&((*c)), nameStart, nameLen, args);
    }
    else if (_m106.tag == 10) {
        uint64_t recv = _m106.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m106.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m106.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m106.data.Method.args;
        (void)args;
    checkMethodArgs(&((*c)), recv, nameStart, nameLen, args);
    }
    else if (_m106.tag == 11) {
        uint64_t operand = _m106.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m106.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m106.data.Cast.tyLen;
        (void)tyLen;
    Expr oe = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m108 = oe;
    if (_m108.tag == 0) {
    }
    else {
    checkLitCtx(&((*c)), operand, 0, 0, 0);
    }
    }
    }
    else if (_m106.tag == 5) {
        uint64_t base = _m106.data.Field.base;
        (void)base;
        uint64_t nameStart = _m106.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m106.data.Field.nameLen;
        (void)nameLen;
    checkLitCtx(&((*c)), base, 0, 0, 0);
    }
    else if (_m106.tag == 9) {
        uint64_t base = _m106.data.Index.base;
        (void)base;
        uint64_t index = _m106.data.Index.index;
        (void)index;
    checkLitCtx(&((*c)), base, 0, 0, 0);
    checkLitCtx(&((*c)), index, 1, 64, 0);
    }
    else if (_m106.tag == 6) {
        uint64_t typeStart = _m106.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m106.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m106.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m106.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m106.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m106.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m106.data.Make.fields;
        (void)fields;
    checkMakeFields(&((*c)), typeStart, typeLen, variantStart, variantLen, isEnum, ty, fields);
    }
    else if (_m106.tag == 8) {
        PlewArray_U64 elems = _m106.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    checkLitCtx(&((*c)), PlewArray_U64_get(elems, (long long)(i)), eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m106.tag == 12) {
        uint64_t scrut = _m106.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m106.data.MatchExpr.arms;
        (void)arms;
    checkLitCtx(&((*c)), scrut, 0, 0, 0);
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    checkLitCtx(&((*c)), PlewArray_MatchArm_get(arms, (long long)(i)).body, eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m106.tag == 14) {
        uint64_t opt = _m106.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m106.data.Coalesce.deflt;
        (void)deflt;
    checkLitCtx(&((*c)), opt, 0, 0, 0);
    checkLitCtx(&((*c)), deflt, eKind, eBits, eSgn);
    }
    else if (_m106.tag == 15) {
        uint64_t expr = _m106.data.Try.expr;
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
    return (IntTy){.known = 1, .bits = intBits(&((*c)), ti.nameStart, ti.nameLen), .sgn = intSigned(&((*c)), ti.nameStart, ti.nameLen)};
    }
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m109 = e;
    if (_m109.tag == 4) {
        uint64_t nameStart = _m109.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m109.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m109.data.Call.args;
        (void)args;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argCount", 8})) {
    return (IntTy){.known = 1, .bits = 64, .sgn = 1};
    }
    }
    else if (_m109.tag == 5) {
        uint64_t base = _m109.data.Field.base;
        (void)base;
        uint64_t nameStart = _m109.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m109.data.Field.nameLen;
        (void)nameLen;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"count", 5})) {
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    return (IntTy){.known = 1, .bits = 64, .sgn = 0};
    }
    }
    }
    else if (_m109.tag == 9) {
        uint64_t base = _m109.data.Index.base;
        (void)base;
        uint64_t index = _m109.data.Index.index;
        (void)index;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    if (isIntType(&((*c)), bt.nameStart, bt.nameLen)) {
    return (IntTy){.known = 1, .bits = intBits(&((*c)), bt.nameStart, bt.nameLen), .sgn = intSigned(&((*c)), bt.nameStart, bt.nameLen)};
    }
    }
    }
    else {
    }
    }
    return (IntTy){.known = 0, .bits = 0, .sgn = 0};
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
    Expr _m110 = e;
    if (_m110.tag == 8) {
        PlewArray_U64 elems = _m110.data.Array.elems;
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
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
    PlewArray_Param ps = PlewArray_Param_copy(f.params);
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
}
void checkMethodArgs(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    checkLitCtx(&((*c)), recv, 0, 0, 0);
    TypeInfo rt = exprType(&((*c)), recv);
    if (rt.kind == 2) {
    uint64_t mi = findMethod(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen);
    if (mi != (long long)(((*c).funcs).len)) {
    Func mf = PlewArray_Func_get((*c).funcs, (long long)(mi));
    PlewArray_Param ps = PlewArray_Param_copy(mf.params);
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
    return;
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
    EnumDef en = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), en.nameStart, en.nameLen, typeStart, typeLen)) {
    PlewArray_Variant vars = PlewArray_Variant_copy(en.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(v.fields);
    uint64_t fj = 0;
    while (fj < (long long)((fs).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fs, (long long)(fj));
    if (spansEqual(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    return typeInfoOfName(&((*c)), fd.tyStart, fd.tyLen, fd.tyIsArray);
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return scalarInfo();
    }
    return fieldType(&((*c)), typeStart, typeLen, fieldStart, fieldLen);
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
    Expr _m111 = e;
    if (_m111.tag == 0) {
        int64_t value = _m111.data.Int.value;
        (void)value;
    writeInt(value);
    }
    else if (_m111.tag == 1) {
        uint64_t start = _m111.data.Ident.start;
        (void)start;
        uint64_t len = _m111.data.Ident.len;
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
    else if (_m111.tag == 2) {
        int64_t op = _m111.data.Unary.op;
        (void)op;
        uint64_t operand = _m111.data.Unary.operand;
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
    else if (_m111.tag == 3) {
        int64_t op = _m111.data.Binary.op;
        (void)op;
        uint64_t lhs = _m111.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m111.data.Binary.rhs;
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
    else if (_m111.tag == 4) {
        uint64_t nameStart = _m111.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m111.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m111.data.Call.args;
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
    Func cf = PlewArray_Func_get((*c).funcs, (long long)(cfi));
    PlewArray_Param cps = PlewArray_Param_copy(cf.params);
    uint64_t di = (long long)((args).len);
    while (di < (long long)((cps).len)) {
    if (di > 0) {
    plew_write((PlewString){", ", 2});
    }
    genExpr(&((*c)), PlewArray_Param_get(cps, (long long)(di)).defaultExpr);
    di = ({ uint64_t __ov; if (__builtin_add_overflow((di), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    plew_write((PlewString){")", 1});
    }
    else if (_m111.tag == 5) {
        uint64_t base = _m111.data.Field.base;
        (void)base;
        uint64_t nameStart = _m111.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m111.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 1) {
    plew_write((PlewString){"({ PlewString __s = ", 20});
    genExpr(&((*c)), base);
    plew_write((PlewString){"; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; })", 64});
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
    else if (_m111.tag == 7) {
        uint64_t start = _m111.data.Str.start;
        (void)start;
        uint64_t len = _m111.data.Str.len;
        (void)len;
    plew_write((PlewString){"(PlewString){\"", 14});
    writeSpan(&((*c)), ({ uint64_t __ov; if (__builtin_add_overflow((start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), ({ uint64_t __ov; if (__builtin_sub_overflow((len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    plew_write((PlewString){"\", ", 3});
    writeInt(strDecodedLen(&((*c)), start, len));
    plew_write((PlewString){"}", 1});
    }
    else if (_m111.tag == 9) {
        uint64_t base = _m111.data.Index.base;
        (void)base;
        uint64_t index = _m111.data.Index.index;
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
    else if (_m111.tag == 16) {
        uint64_t base = _m111.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m111.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m111.data.Arrow.nameLen;
        (void)nameLen;
    plew_write((PlewString){"(", 1});
    genExpr(&((*c)), base);
    plew_write((PlewString){")->", 3});
    writeSpan(&((*c)), nameStart, nameLen);
    }
    else if (_m111.tag == 17) {
        PlewArray_Param params = _m111.data.Closure.params;
        (void)params;
        long long hasRet = _m111.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m111.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m111.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m111.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m111.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m111.data.Closure.body;
        (void)body;
    plew_write((PlewString){"__closure", 9});
    writeU64(id);
    }
    else if (_m111.tag == 10) {
        uint64_t recv = _m111.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m111.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m111.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m111.data.Method.args;
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
    Func mf = PlewArray_Func_get((*c).funcs, (long long)(mi));
    if (paramsLabelsOk(&((*c)), mf.params, args)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), nameStart), (PlewString){"argument labels do not match the method parameters", 50});
    return;
    }
    if (mf.selfInout) {
    if (placeIsMutable(&((*c)), recv)) {
    }
    else {
    compileErrorAt(lineOf(&((*c)), exprOffset(&((*c)), recv)), (PlewString){"cannot call an `inout fn` method on an immutable binding; declare it with `mut val`", 83});
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
    }
    }
    else if (_m111.tag == 8) {
        PlewArray_U64 elems = _m111.data.Array.elems;
        (void)elems;
    plew_write((PlewString){"0", 1});
    }
    else if (_m111.tag == 11) {
        uint64_t operand = _m111.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m111.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m111.data.Cast.tyLen;
        (void)tyLen;
    if (isIntType(&((*c)), tyStart, tyLen)) {
    Expr opE = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m112 = opE;
    if (_m112.tag == 0) {
        int64_t value = _m112.data.Int.value;
        (void)value;
        uint64_t offset = _m112.data.Int.offset;
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
    else if (_m111.tag == 6) {
        uint64_t typeStart = _m111.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m111.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m111.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m111.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m111.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m111.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m111.data.Make.fields;
        (void)fields;
    if (isRefInst(&((*c)), ty)) {
    TypeRef rt = PlewArray_TypeRef_get((*c).types, (long long)(ty));
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
    return;
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
    else if (_m111.tag == 12) {
        uint64_t scrut = _m111.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m111.data.MatchExpr.arms;
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
    MatchArm aq = PlewArray_MatchArm_get(arms, (long long)(q));
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
    MatchArm a = PlewArray_MatchArm_get(arms, (long long)(i));
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
    PlewArray_Bind binds = PlewArray_Bind_copy(a.binds);
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
    addLocal(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0);
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
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
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
    else if (_m111.tag == 13) {
        uint64_t cond = _m111.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m111.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m111.data.IfExpr.elseBlk;
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
    else if (_m111.tag == 14) {
        uint64_t opt = _m111.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m111.data.Coalesce.deflt;
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
    else if (_m111.tag == 15) {
        uint64_t expr = _m111.data.Try.expr;
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
    Expr _m113 = PlewArray_Expr_get((*c).exprs, (long long)(id));
    if (_m113.tag == 1) {
        uint64_t start = _m113.data.Ident.start;
        (void)start;
        uint64_t len = _m113.data.Ident.len;
        (void)len;
    return 1;
    }
    else if (_m113.tag == 5) {
        uint64_t base = _m113.data.Field.base;
        (void)base;
        uint64_t nameStart = _m113.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m113.data.Field.nameLen;
        (void)nameLen;
    return 1;
    }
    else if (_m113.tag == 9) {
        uint64_t base = _m113.data.Index.base;
        (void)base;
        uint64_t index = _m113.data.Index.index;
        (void)index;
    return 1;
    }
    else {
    return 0;
    }
    }
}
void genArrayValue(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen) {
    if (isPlaceExpr(&((*c)), exprId)) {
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(", 6});
    genExpr(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    genArrayLiteral(&((*c)), exprId, elemStart, elemLen);
}
void genArrayLiteral(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(exprId));
    {
    Expr _m114 = e;
    if (_m114.tag == 8) {
        PlewArray_U64 elems = _m114.data.Array.elems;
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
    return 0;
    }
    }
    TypeInfo lt = exprType(&((*c)), lhs);
    return (lt.kind == 1);
}
long long isEnumName(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, start, len)) {
    return 1;
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
long long isAllNullary(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, start, len)) {
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if ((long long)((v.fields).len) > 0) {
    return 0;
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
long long isEnumEq(Comp* c, int64_t op, uint64_t lhs) {
    if (op == 50) {
    }
    else {
    if (op == 51) {
    }
    else {
    return 0;
    }
    }
    TypeInfo lt = exprType(&((*c)), lhs);
    if (lt.kind == 2) {
    return isEnumName(&((*c)), lt.nameStart, lt.nameLen);
    }
    return 0;
}
long long compareNeedsTrait(Comp* c, int64_t op, uint64_t lhs) {
    if (op < 50) {
    return 0;
    }
    if (op > 55) {
    return 0;
    }
    TypeInfo lt = exprType(&((*c)), lhs);
    if (lt.kind == 3) {
    return 1;
    }
    if (lt.kind == 2) {
    if (isEnumName(&((*c)), lt.nameStart, lt.nameLen)) {
    return 0;
    }
    return 1;
    }
    return 0;
}
void emitEnumOperand(Comp* c, uint64_t id, uint64_t enStart, uint64_t enLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m115 = e;
    if (_m115.tag == 6) {
        uint64_t typeStart = _m115.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m115.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m115.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m115.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m115.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m115.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m115.data.Make.fields;
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
    Expr _m116 = e;
    if (_m116.tag == 3) {
        int64_t op = _m116.data.Binary.op;
        (void)op;
        uint64_t lhs = _m116.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m116.data.Binary.rhs;
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
    Stmt _m117 = s;
    if (_m117.tag == 0) {
        long long mutable = _m117.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m117.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m117.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m117.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m117.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m117.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m117.data.Let.ty;
        (void)ty;
        uint64_t init = _m117.data.Let.init;
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
    if (mutable) {
    genCopyValue(&((*c)), init, ty, tyStart, tyLen, 0);
    }
    else {
    genExpr(&((*c)), init);
    }
    }
    plew_write((PlewString){";\n", 2});
    addLocal(&((*c)), nameStart, nameLen, tyStart, tyLen, tyIsArray, ty, 0, mutable);
    }
    else if (_m117.tag == 1) {
        int64_t op = _m117.data.Assign.op;
        (void)op;
        uint64_t target = _m117.data.Assign.target;
        (void)target;
        uint64_t value = _m117.data.Assign.value;
        (void)value;
    Expr te = PlewArray_Expr_get((*c).exprs, (long long)(target));
    {
    Expr _m118 = te;
    if (_m118.tag == 9) {
        uint64_t base = _m118.data.Index.base;
        (void)base;
        uint64_t index = _m118.data.Index.index;
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
    else if (_m117.tag == 2) {
        uint64_t expr = _m117.data.Print.expr;
        (void)expr;
        uint64_t offset = _m117.data.Print.offset;
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
    else if (_m117.tag == 3) {
        uint64_t expr = _m117.data.ExprStmt.expr;
        (void)expr;
    checkLitCtx(&((*c)), expr, 0, 0, 0);
    plew_write((PlewString){"    ", 4});
    genExpr(&((*c)), expr);
    plew_write((PlewString){";\n", 2});
    }
    else if (_m117.tag == 4) {
        uint64_t value = _m117.data.Return.value;
        (void)value;
        long long hasValue = _m117.data.Return.hasValue;
        (void)hasValue;
    if ((*c).curIsMain) {
    plew_write((PlewString){"    return 0;\n", 14});
    }
    else {
    if ((*c).curRetVoid) {
    plew_write((PlewString){"    return;\n", 12});
    }
    else {
    if (hasValue) {
    checkLitSpan(&((*c)), value, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    }
    plew_write((PlewString){"    return ", 11});
    if (hasValue) {
    genCopyValue(&((*c)), value, (*c).curRetTy, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    }
    else {
    plew_write((PlewString){"0", 1});
    }
    plew_write((PlewString){";\n", 2});
    }
    }
    }
    else if (_m117.tag == 5) {
        uint64_t cond = _m117.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m117.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m117.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m117.data.If.hasElse;
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
    else if (_m117.tag == 6) {
        uint64_t cond = _m117.data.While.cond;
        (void)cond;
        uint64_t body = _m117.data.While.body;
        (void)body;
    checkLitCtx(&((*c)), cond, 0, 0, 0);
    plew_write((PlewString){"    while (", 11});
    genCond(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n", 6});
    }
    else if (_m117.tag == 7) {
        uint64_t varStart = _m117.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m117.data.For.varLen;
        (void)varLen;
        long long isRange = _m117.data.For.isRange;
        (void)isRange;
        long long inclusive = _m117.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m117.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m117.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m117.data.For.body;
        (void)body;
    if (isRange) {
    checkArithNoCtx(&((*c)), iter, rangeHi);
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
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
    addLocal(&((*c)), varStart, varLen, 0, 0, 0, 0, 0, 0);
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
    addLocal(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0, 0, 0);
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    }
    else if (_m117.tag == 9) {
        uint64_t msg = _m117.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m117.data.Panic.offset;
        (void)offset;
    plew_write((PlewString){"    plew_panic(", 15});
    genExpr(&((*c)), msg);
    plew_write((PlewString){");\n", 3});
    }
    else if (_m117.tag == 10) {
        uint64_t value = _m117.data.Give.value;
        (void)value;
    if ((*c).curGiveTmp != 0) {
    plew_write((PlewString){"    __r", 7});
    writeU64(({ uint64_t __ov; if (__builtin_sub_overflow(((*c).curGiveTmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    plew_write((PlewString){" = (", 4});
    genExpr(&((*c)), value);
    plew_write((PlewString){");\n", 3});
    }
    }
    else if (_m117.tag == 11) {
    plew_write((PlewString){"    break;\n", 11});
    }
    else if (_m117.tag == 12) {
    plew_write((PlewString){"    continue;\n", 14});
    }
    else if (_m117.tag == 8) {
        uint64_t scrut = _m117.data.Match.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m117.data.Match.arms;
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
    MatchArm aq = PlewArray_MatchArm_get(arms, (long long)(q));
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
    MatchArm a = PlewArray_MatchArm_get(arms, (long long)(i));
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
    PlewArray_Bind binds = PlewArray_Bind_copy(a.binds);
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
    addLocal(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0);
    }
    else {
    addBindLocal(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genBlock(&((*c)), a.body);
    plew_write((PlewString){"    }\n", 6});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
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
    Block b = PlewArray_Block_get((*c).blocks, (long long)(id));
    PlewArray_U64 stmts = PlewArray_U64_copy(b.stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).len)) {
    genStmt(&((*c)), PlewArray_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scopeExit(&((*c)), mark);
}
long long nameIsMain(Comp* c, Func f) {
    if (f.hasRecv) {
    return 0;
    }
    return rangeEquals((*c).bytes, f.nameStart, f.nameLen, (PlewString){"main", 4});
}
uint64_t structIndexByName(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).len)) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(i));
    if ((long long)((s.typeParams).len) == 0) {
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, start, len)) {
    return i;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return (long long)(((*c).structs).len);
}
long long structNeedsCopy(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    return 0;
    }
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    PlewArray_FieldDef fields = PlewArray_FieldDef_copy(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    return 1;
    }
    else {
    if (structNeedsCopy(&((*c)), f.tyStart, f.tyLen)) {
    return 1;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
void emitStructCopyProto(Comp* c, uint64_t si) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
}
void emitStructCopyDef(Comp* c, uint64_t si) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) { ", 6});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_FieldDef fields = PlewArray_FieldDef_copy(s.fields);
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
}
long long monoStructNeedsCopy(Comp* c, uint64_t instRef) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    return 0;
    }
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    PlewArray_FieldDef fields = PlewArray_FieldDef_copy(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    TypeInfo ti = substTypeInfo(&((*c)), instRef, s.typeParams, PlewArray_FieldDef_get(fields, (long long)(i)).ty);
    if (ti.kind == 3) {
    return 1;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
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
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    return;
    }
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" s) { ", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_FieldDef fields = PlewArray_FieldDef_copy(s.fields);
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
}
long long monoEnumNeedsCopy(Comp* c, uint64_t instRef) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    return 0;
    }
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(PlewArray_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    TypeInfo ti = substTypeInfo(&((*c)), instRef, e.typeParams, PlewArray_FieldDef_get(fs, (long long)(fi)).ty);
    if (ti.kind == 3) {
    return 1;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
void emitMonoEnumCopyProto(Comp* c, uint64_t instRef) {
    emitMonoStructCopyProto(&((*c)), instRef);
}
void emitMonoEnumCopyDef(Comp* c, uint64_t instRef) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    return;
    }
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" s) { ", 6});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(v.fields);
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
    }
    plew_write((PlewString){" return r; }\n", 13});
}
void genStructValue(Comp* c, uint64_t exprId, uint64_t structStart, uint64_t structLen) {
    if (isPlaceExpr(&((*c)), exprId)) {
    if (structNeedsCopy(&((*c)), structStart, structLen)) {
    writeSpan(&((*c)), structStart, structLen);
    plew_write((PlewString){"_copy(", 6});
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
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    plew_write((PlewString){"struct ", 7});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" {\n", 3});
    PlewArray_FieldDef fields = PlewArray_FieldDef_copy(s.fields);
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
    PlewArray_Param params = PlewArray_Param_copy(f.params);
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
}
void genFunc(Comp* c, uint64_t fi) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
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
    PlewArray_Param params = PlewArray_Param_copy(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((params).len)) {
    Param p = PlewArray_Param_get(params, (long long)(pi));
    addLocal(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0);
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
}
void genClosure(Comp* c, uint64_t id, long long proto) {
    {
    Expr _m119 = PlewArray_Expr_get((*c).exprs, (long long)(id));
    if (_m119.tag == 17) {
        PlewArray_Param params = _m119.data.Closure.params;
        (void)params;
        long long hasRet = _m119.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m119.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m119.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m119.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m119.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m119.data.Closure.body;
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
    addLocal(&((*c)), p2.nameStart, p2.nameLen, p2.tyStart, p2.tyLen, p2.tyIsArray, p2.ty, p2.isInout, 0);
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
    Expr _m120 = PlewArray_Expr_get((*c).exprs, (long long)(i));
    if (_m120.tag == 17) {
        PlewArray_Param params = _m120.data.Closure.params;
        (void)params;
        long long hasRet = _m120.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m120.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m120.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m120.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m120.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m120.data.Closure.body;
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
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    plew_write((PlewString){"struct ", 7});
    writeSpan(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" {\n", 3});
    plew_write((PlewString){"    long long tag;\n", 19});
    plew_write((PlewString){"    union {\n", 12});
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    plew_write((PlewString){"        struct {", 16});
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(v.fields);
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
    }
    plew_write((PlewString){"    } data;\n", 12});
    plew_write((PlewString){"};\n", 3});
}
uint64_t genericStructIndex(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).len)) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(i));
    if ((long long)((s.typeParams).len) > 0) {
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, nameStart, nameLen)) {
    return i;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return (long long)(((*c).structs).len);
}
uint64_t genericEnumIndex(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(i));
    if ((long long)((e.typeParams).len) > 0) {
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, nameStart, nameLen)) {
    return i;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return (long long)(((*c).enums).len);
}
long long isGenericInst(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return 0;
    }
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
    if ((long long)((t.args).len) == 0) {
    return 0;
    }
    if (genericStructIndex(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).structs).len)) {
    return 1;
    }
    return (genericEnumIndex(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).len));
}
long long isFnType(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return 0;
    }
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
    return rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"fn", 2});
}
long long isRefInst(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return 0;
    }
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
    if ((long long)((t.args).len) != 1) {
    return 0;
    }
    return rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Ref", 3});
}
long long isGenericEnumInst(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return 0;
    }
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
    if ((long long)((t.args).len) == 0) {
    return 0;
    }
    return (genericEnumIndex(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).len));
}
long long typeRefEq(Comp* c, uint64_t a, uint64_t b) {
    if (a == b) {
    return 1;
    }
    TypeRef ta = PlewArray_TypeRef_get((*c).types, (long long)(a));
    TypeRef tb = PlewArray_TypeRef_get((*c).types, (long long)(b));
    if (spansEqual(&((*c)), ta.nameStart, ta.nameLen, tb.nameStart, tb.nameLen)) {
    }
    else {
    return 0;
    }
    if ((long long)((ta.args).len) != (long long)((tb.args).len)) {
    return 0;
    }
    uint64_t i = 0;
    while (i < (long long)((ta.args).len)) {
    if (typeRefEq(&((*c)), PlewArray_U64_get(ta.args, (long long)(i)), PlewArray_U64_get(tb.args, (long long)(i)))) {
    }
    else {
    return 0;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
}
void emitMangle(Comp* c, uint64_t ref) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(resolveTy(&((*c)), ref)));
    writeSpan(&((*c)), t.nameStart, t.nameLen);
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    plew_write((PlewString){"_", 1});
    emitMangle(&((*c)), PlewArray_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void emitConcreteCType(Comp* c, uint64_t ref) {
    uint64_t r = resolveTy(&((*c)), ref);
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(r));
    if ((long long)((t.args).len) == 0) {
    genCElem(&((*c)), t.nameStart, t.nameLen);
    return;
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    plew_write((PlewString){"PlewArray_", 10});
    emitMangle(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    return;
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Ref", 3})) {
    emitConcreteCType(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    plew_write((PlewString){"*", 1});
    return;
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"fn", 2})) {
    emitMangle(&((*c)), r);
    return;
    }
    emitMangle(&((*c)), r);
}
void emitFieldCType(Comp* c, uint64_t ref, PlewArray_Bind params, PlewArray_U64 args) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
    uint64_t pi = 0;
    while (pi < (long long)((params).len)) {
    Bind p = PlewArray_Bind_get(params, (long long)(pi));
    if (spansEqual(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    emitConcreteCType(&((*c)), PlewArray_U64_get(args, (long long)(pi)));
    return;
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    emitConcreteCType(&((*c)), ref);
}
uint64_t resolveTy(Comp* c, uint64_t tyRef) {
    if (tyRef >= (long long)(((*c).types).len)) {
    return tyRef;
    }
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(tyRef));
    if ((long long)((t.args).len) == 0) {
    uint64_t i = 0;
    while (i < (long long)(((*c).curTypeParams).len)) {
    Bind p = PlewArray_Bind_get((*c).curTypeParams, (long long)(i));
    if (spansEqual(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    return PlewArray_U64_get((*c).curTypeArgs, (long long)(i));
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    return tyRef;
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
    PlewArray_Bind tp = PlewArray_Bind_copy(PlewArray_StructDef_get((*c).structs, (long long)(si)).typeParams);
    uint64_t k = 0;
    while (k < (long long)((tp).len)) {
    if (spansEqual(&((*c)), PlewArray_Bind_get(tp, (long long)(k)).nameStart, PlewArray_Bind_get(tp, (long long)(k)).nameLen, start, len)) {
    return 1;
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    PlewArray_Bind tp2 = PlewArray_Bind_copy(PlewArray_EnumDef_get((*c).enums, (long long)(ei)).typeParams);
    uint64_t k2 = 0;
    while (k2 < (long long)((tp2).len)) {
    if (spansEqual(&((*c)), PlewArray_Bind_get(tp2, (long long)(k2)).nameStart, PlewArray_Bind_get(tp2, (long long)(k2)).nameLen, start, len)) {
    return 1;
    }
    k2 = ({ uint64_t __ov; if (__builtin_add_overflow((k2), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    PlewArray_Bind tp3 = PlewArray_Bind_copy(PlewArray_Func_get((*c).funcs, (long long)(fi)).typeParams);
    uint64_t k3 = 0;
    while (k3 < (long long)((tp3).len)) {
    if (spansEqual(&((*c)), PlewArray_Bind_get(tp3, (long long)(k3)).nameStart, PlewArray_Bind_get(tp3, (long long)(k3)).nameLen, start, len)) {
    return 1;
    }
    k3 = ({ uint64_t __ov; if (__builtin_add_overflow((k3), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
long long tyRefIsGround(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return 1;
    }
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
    if (isTypeParamName(&((*c)), t.nameStart, t.nameLen)) {
    return 0;
    }
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    if (tyRefIsGround(&((*c)), PlewArray_U64_get(t.args, (long long)(i)))) {
    }
    else {
    return 0;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 1;
}
void registerArrayElemRef(Comp* c, uint64_t elemRef) {
    if (elemRef >= (long long)(((*c).types).len)) {
    return;
    }
    TypeRef e = PlewArray_TypeRef_get((*c).types, (long long)(elemRef));
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind ae = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual(&((*c)), ae.nameStart, ae.nameLen, e.nameStart, e.nameLen)) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Bind_push(&((*c).arrayElems), (Bind){.nameStart = e.nameStart, .nameLen = e.nameLen, .fieldStart = e.nameStart, .fieldLen = e.nameLen});
}
void scanType(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return;
    }
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
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
    return;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U64_push(&((*c).genInsts), ref);
    }
    }
}
void collectGenInsts(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
    if ((long long)((f.typeParams).len) > 0) {
    }
    else {
    if (f.hasRet) {
    scanType(&((*c)), f.retTy);
    }
    PlewArray_Param ps = PlewArray_Param_copy(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((ps).len)) {
    scanType(&((*c)), PlewArray_Param_get(ps, (long long)(pi)).ty);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    if ((long long)((s.typeParams).len) == 0) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(s.fields);
    uint64_t k = 0;
    while (k < (long long)((fs).len)) {
    scanType(&((*c)), PlewArray_FieldDef_get(fs, (long long)(k)).ty);
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if ((long long)((e.typeParams).len) == 0) {
    PlewArray_Variant vs = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vs).len)) {
    PlewArray_FieldDef vfs = PlewArray_FieldDef_copy(PlewArray_Variant_get(vs, (long long)(vi)).fields);
    uint64_t k = 0;
    while (k < (long long)((vfs).len)) {
    scanType(&((*c)), PlewArray_FieldDef_get(vfs, (long long)(k)).ty);
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t sti = 0;
    while (sti < (long long)(((*c).stmts).len)) {
    {
    Stmt _m121 = PlewArray_Stmt_get((*c).stmts, (long long)(sti));
    if (_m121.tag == 0) {
        uint64_t ty = _m121.data.Let.ty;
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
    Expr _m122 = PlewArray_Expr_get((*c).exprs, (long long)(xi));
    if (_m122.tag == 11) {
        uint64_t operand = _m122.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m122.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m122.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m122.data.Cast.ty;
        (void)ty;
    scanType(&((*c)), ty);
    }
    else if (_m122.tag == 6) {
        uint64_t typeStart = _m122.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m122.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m122.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m122.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m122.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m122.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m122.data.Make.fields;
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
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(ref));
    if ((long long)((t.args).len) == 0) {
    return typeInfoOfName(&((*c)), t.nameStart, t.nameLen, 0);
    }
    if (rangeEquals((*c).bytes, t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    TypeRef el = PlewArray_TypeRef_get((*c).types, (long long)(PlewArray_U64_get(t.args, (long long)(0))));
    return typeInfoOfName(&((*c)), el.nameStart, el.nameLen, 1);
    }
    return typeInfoOfName(&((*c)), t.nameStart, t.nameLen, 0);
}
TypeInfo substTypeInfo(Comp* c, uint64_t instRef, PlewArray_Bind params, uint64_t tyRef) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(tyRef));
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    Bind p = PlewArray_Bind_get(params, (long long)(i));
    if (spansEqual(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    TypeRef inst = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    if (i < (long long)((inst.args).len)) {
    return typeInfoOfRef(&((*c)), PlewArray_U64_get(inst.args, (long long)(i)));
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return typeInfoOfRef(&((*c)), tyRef);
}
TypeInfo genericFieldTypeInfo(Comp* c, uint64_t instRef, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    return scalarInfo();
    }
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    PlewArray_FieldDef fields = PlewArray_FieldDef_copy(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fields, (long long)(i));
    if (spansEqual(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = PlewArray_TypeRef_get((*c).types, (long long)(fd.ty));
    uint64_t pi = 0;
    while (pi < (long long)((s.typeParams).len)) {
    Bind p = PlewArray_Bind_get(s.typeParams, (long long)(pi));
    if (spansEqual(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    return typeInfoOfRef(&((*c)), PlewArray_U64_get(t.args, (long long)(pi)));
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return typeInfoOfRef(&((*c)), fd.ty);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return scalarInfo();
}
TypeInfo genericEnumFieldTypeInfo(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    return scalarInfo();
    }
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = PlewArray_TypeRef_get((*c).types, (long long)(fd.ty));
    uint64_t pi = 0;
    while (pi < (long long)((e.typeParams).len)) {
    Bind p = PlewArray_Bind_get(e.typeParams, (long long)(pi));
    if (spansEqual(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    return typeInfoOfRef(&((*c)), PlewArray_U64_get(t.args, (long long)(pi)));
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return typeInfoOfRef(&((*c)), fd.ty);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return scalarInfo();
}
void genBindTypeInst(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen) {
    TypeInfo ti = genericEnumFieldTypeInfo(&((*c)), instRef, variantStart, variantLen, bindStart, bindLen);
    genTypeInfoCType(&((*c)), ti);
}
void emitFnTypedef(Comp* c, uint64_t fnRef) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(fnRef));
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
}
void emitMonoForward(Comp* c, uint64_t instRef) {
    plew_write((PlewString){"typedef struct ", 15});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){";\n", 2});
}
void emitMonoStruct(Comp* c, uint64_t instRef) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t si = genericStructIndex(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    return;
    }
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    plew_write((PlewString){"struct ", 7});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" {\n", 3});
    PlewArray_FieldDef fields = PlewArray_FieldDef_copy(s.fields);
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
}
void emitMonoEnum(Comp* c, uint64_t instRef) {
    TypeRef t = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    uint64_t ei = genericEnumIndex(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    return;
    }
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    plew_write((PlewString){"struct ", 7});
    emitMangle(&((*c)), instRef);
    plew_write((PlewString){" {\n    long long tag;\n    union {\n", 34});
    PlewArray_Variant vars = PlewArray_Variant_copy(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    plew_write((PlewString){"        struct {", 16});
    PlewArray_FieldDef fs = PlewArray_FieldDef_copy(v.fields);
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
    }
    plew_write((PlewString){"    } data;\n};\n", 15});
}
long long methodMatchesInst(Comp* c, Func f, uint64_t instRef) {
    if (f.hasRecv) {
    }
    else {
    return 0;
    }
    if ((long long)((f.typeParams).len) == 0) {
    return 0;
    }
    TypeRef inst = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    if (spansEqual(&((*c)), f.recvStart, f.recvLen, inst.nameStart, inst.nameLen)) {
    }
    else {
    return 0;
    }
    return ((long long)((f.typeParams).len) == (long long)((inst.args).len));
}
void emitMonoMethod(Comp* c, uint64_t fi, uint64_t instRef, long long proto) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
    TypeRef inst = PlewArray_TypeRef_get((*c).types, (long long)(instRef));
    (*c).curRecvInstRef = instRef;
    (*c).curTypeParams = PlewArray_Bind_copy(f.typeParams);
    (*c).curTypeArgs = PlewArray_U64_copy(inst.args);
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
    (*c).curTypeParams = PlewArray_Bind_copy(noParams);
    (*c).curTypeArgs = PlewArray_U64_copy(noArgs);
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
    plew_write((PlewString){"* data; long long len; long long cap; } ", 40});
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
    plew_write((PlewString){" a; a.data = 0; a.len = 0; a.cap = 0; return a; }\n", 50});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_get(", 5});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } return a.data[i]; }\n", 125});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_set(", 5});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, long long i, ", 18});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { if (i < 0 || i >= a->len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } a->data[i] = v; }\n", 111});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(", 6});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, ", 5});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; ", 74});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* nd = (", 8});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)malloc(sizeof(", 16});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){") * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }\n", 130});
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
    plew_write((PlewString){"*)malloc(sizeof(", 16});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){") * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }\n", 119});
}
long long isU8Elem(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    return rangeEquals((*c).bytes, elemStart, elemLen, (PlewString){"U8", 2});
}
void genU8ArrayTypedef(void) {
    plew_write((PlewString){"typedef struct { unsigned char* data; long long len; long long cap; } PlewArray_U8;\n", 84});
}
void genU8ArrayRuntime(void) {
    plew_write((PlewString){"__attribute__((unused)) static PlewArray_U8 PlewArray_U8_new(void) { PlewArray_U8 a; a.data = 0; a.len = 0; a.cap = 0; return a; }\n", 131});
    plew_write((PlewString){"__attribute__((unused)) static unsigned char PlewArray_U8_get(PlewArray_U8 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } return a.data[i]; }\n", 199});
    plew_write((PlewString){"__attribute__((unused)) static void PlewArray_U8_set(PlewArray_U8* a, long long i, unsigned char v) { if (i < 0 || i >= a->len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } a->data[i] = v; }\n", 207});
    plew_write((PlewString){"__attribute__((unused)) static void PlewArray_U8_push(PlewArray_U8* a, unsigned char v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; unsigned char* nd = (unsigned char*)malloc(sizeof(unsigned char) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }\n", 351});
    plew_write((PlewString){"__attribute__((unused)) static PlewArray_U8 PlewArray_U8_copy(PlewArray_U8 a) { PlewArray_U8 r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (unsigned char*)malloc(sizeof(unsigned char) * a.len); for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; } return r; }\n", 314});
}
long long isPathTokKind(Kind k) {
    {
    Kind _m123 = k;
    if (_m123.tag == 33) {
    return 1;
    }
    else if (_m123.tag == 44) {
    return 1;
    }
    else if (_m123.tag == 5) {
    return 1;
    }
    else {
    return 0;
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
    Kind _m124 = t.kind;
    if (_m124.tag == 5) {
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
    Kind _m125 = first.kind;
    if (_m125.tag == 33) {
    starts = 1;
    }
    else if (_m125.tag == 44) {
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
    return PlewArray_Bind_copy(parts);
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
    return end;
}
PlewArray_U8 resolveImport(PlewArray_U8 src, uint64_t pStart, uint64_t pLen, PlewArray_U8 importer, uint64_t baseLen, PlewArray_U8 srcRoot, uint64_t srcRootLen, PlewArray_U8 stdRoot, uint64_t stdRootLen) {
    PlewArray_U8 out = PlewArray_U8_new();
    if (pLen == 0) {
    return PlewArray_U8_copy(out);
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
    return PlewArray_U8_copy(out);
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
    return PlewArray_U8_copy(out);
    }
    }
    }
    }
    }
    return PlewArray_U8_copy(out);
    }
    if (b0 == 47) {
    if (srcRootLen == 0) {
    return PlewArray_U8_copy(out);
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
    return PlewArray_U8_copy(out);
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
    return PlewArray_U8_copy(out);
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
    return PlewArray_U8_copy(out);
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
    return pre;
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
    return PlewArray_U8_copy(out);
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
    PlewArray_U8 mn = PlewArray_U8_copy(({ PlewString __s = (PlewString){"Plew.toml", 9}; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }));
    appendBytes(&(mani), mn);
    if (plew_file_exists(mani)) {
    PlewArray_U8 sr = PlewArray_U8_new();
    uint64_t j = 0;
    while (j < dirLen) {
    PlewArray_U8_push(&(sr), PlewArray_U8_get(entry, (long long)(j)));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8 sx = PlewArray_U8_copy(({ PlewString __s = (PlewString){"src/", 4}; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }));
    appendBytes(&(sr), sx);
    return PlewArray_U8_copy(sr);
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
    }
    PlewArray_U8 empty = PlewArray_U8_new();
    return PlewArray_U8_copy(empty);
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
    return 1;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return 0;
}
