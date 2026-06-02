#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef struct { const char* data; long long len; } PlewString;
__attribute__((unused)) static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (long long i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }
__attribute__((unused)) static PlewString plew_read_stdin(void) { size_t cap = 4096, len = 0; char* buf = (char*)malloc(cap); int ch; while ((ch = getchar()) != EOF) { if (len + 1 >= cap) { cap *= 2; buf = (char*)realloc(buf, cap); } buf[len++] = (char)ch; } PlewString s; s.data = buf; s.len = (long long)len; return s; }
__attribute__((unused)) static void plew_write(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stdout); }
static int plew_argc = 0;
static char** plew_argv = 0;
__attribute__((unused)) static long long plew_arg_count(void) { return (long long)plew_argc; }
__attribute__((unused)) static PlewString plew_arg_at(long long i) { PlewString s; if (i < 0 || i >= plew_argc) { s.data = ""; s.len = 0; return s; } s.data = plew_argv[i]; s.len = (long long)strlen(plew_argv[i]); return s; }
__attribute__((unused)) static PlewString plew_read_file(PlewString path) { FILE* f = fopen(path.data, "rb"); PlewString s; if (!f) { s.data = ""; s.len = 0; return s; } fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET); char* buf = (char*)malloc((size_t)sz + 1); size_t n = fread(buf, 1, (size_t)sz, f); fclose(f); buf[n] = 0; s.data = buf; s.len = (long long)n; return s; }
typedef struct Tok Tok;
typedef struct Lexer Lexer;
typedef struct PType PType;
typedef struct Local Local;
typedef struct TypeInfo TypeInfo;
typedef struct MakeField MakeField;
typedef struct Bind Bind;
typedef struct Arg Arg;
typedef struct MatchArm MatchArm;
typedef struct Block Block;
typedef struct Param Param;
typedef struct FieldDef FieldDef;
typedef struct StructDef StructDef;
typedef struct Variant Variant;
typedef struct EnumDef EnumDef;
typedef struct Func Func;
typedef struct Comp Comp;
typedef struct Kind Kind;
typedef struct Expr Expr;
typedef struct Stmt Stmt;
typedef struct { unsigned char* data; long long len; long long cap; } PlewArray_U8;
typedef struct { Tok* data; long long len; long long cap; } PlewArray_Tok;
typedef struct { Arg* data; long long len; long long cap; } PlewArray_Arg;
typedef struct { MakeField* data; long long len; long long cap; } PlewArray_MakeField;
typedef struct { long long* data; long long len; long long cap; } PlewArray_U64;
typedef struct { Bind* data; long long len; long long cap; } PlewArray_Bind;
typedef struct { MatchArm* data; long long len; long long cap; } PlewArray_MatchArm;
typedef struct { FieldDef* data; long long len; long long cap; } PlewArray_FieldDef;
typedef struct { Variant* data; long long len; long long cap; } PlewArray_Variant;
typedef struct { Param* data; long long len; long long cap; } PlewArray_Param;
typedef struct { Expr* data; long long len; long long cap; } PlewArray_Expr;
typedef struct { Stmt* data; long long len; long long cap; } PlewArray_Stmt;
typedef struct { Block* data; long long len; long long cap; } PlewArray_Block;
typedef struct { Func* data; long long len; long long cap; } PlewArray_Func;
typedef struct { StructDef* data; long long len; long long cap; } PlewArray_StructDef;
typedef struct { EnumDef* data; long long len; long long cap; } PlewArray_EnumDef;
typedef struct { Local* data; long long len; long long cap; } PlewArray_Local;
struct Kind {
    long long tag;
    union {
        struct { char _u; } Eof;
        struct { char _u; } Newline;
        struct { char _u; } Int;
        struct { char _u; } Str;
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
        struct { char _u; } Arrow;
        struct { char _u; } FatArrow;
        struct { char _u; } SlashGt;
        struct { char _u; } PlusEq;
        struct { char _u; } MinusEq;
        struct { char _u; } StarEq;
        struct { char _u; } SlashEq;
        struct { char _u; } PercentEq;
        struct { char _u; } DotDotLt;
        struct { char _u; } DotDotEq;
        struct { char _u; } Unknown;
    } data;
};
struct Expr {
    long long tag;
    union {
        struct { long long value; } Int;
        struct { long long start; long long len; } Ident;
        struct { long long op; long long operand; } Unary;
        struct { long long op; long long lhs; long long rhs; } Binary;
        struct { long long nameStart; long long nameLen; PlewArray_Arg args; } Call;
        struct { long long base; long long nameStart; long long nameLen; } Field;
        struct { long long typeStart; long long typeLen; long long variantStart; long long variantLen; long long isEnum; PlewArray_MakeField fields; } Make;
        struct { long long start; long long len; } Str;
        struct { PlewArray_U64 elems; } Array;
        struct { long long base; long long index; } Index;
        struct { long long recv; long long nameStart; long long nameLen; PlewArray_Arg args; } Method;
        struct { long long operand; long long tyStart; long long tyLen; } Cast;
    } data;
};
struct Stmt {
    long long tag;
    union {
        struct { long long mutable; long long nameStart; long long nameLen; long long tyStart; long long tyLen; long long tyIsArray; long long init; } Let;
        struct { long long op; long long target; long long value; } Assign;
        struct { long long expr; } Print;
        struct { long long expr; } ExprStmt;
        struct { long long value; long long hasValue; } Return;
        struct { long long cond; long long thenBlk; long long elseBlk; long long hasElse; } If;
        struct { long long cond; long long body; } While;
        struct { long long varStart; long long varLen; long long isRange; long long inclusive; long long iter; long long rangeHi; long long body; } For;
        struct { long long scrut; PlewArray_MatchArm arms; } Match;
        struct { char _u; } Break;
        struct { char _u; } Continue;
    } data;
};
struct Tok {
    Kind kind;
    long long start;
    long long len;
};
struct Lexer {
    PlewArray_U8 bytes;
    long long pos;
    PlewArray_Tok toks;
    long long depth;
};
struct PType {
    long long start;
    long long len;
    long long isArray;
};
struct Local {
    long long nameStart;
    long long nameLen;
    long long tyStart;
    long long tyLen;
    long long isArray;
    long long isInout;
};
struct TypeInfo {
    long long kind;
    long long nameStart;
    long long nameLen;
};
struct MakeField {
    long long nameStart;
    long long nameLen;
    long long value;
};
struct Bind {
    long long nameStart;
    long long nameLen;
};
struct Arg {
    long long expr;
    long long isInout;
    long long labelStart;
    long long labelLen;
    long long hasLabel;
};
struct MatchArm {
    long long isWildcard;
    long long enumStart;
    long long enumLen;
    long long variantStart;
    long long variantLen;
    PlewArray_Bind binds;
    long long body;
};
struct Block {
    PlewArray_U64 stmts;
};
struct Param {
    long long nameStart;
    long long nameLen;
    long long tyStart;
    long long tyLen;
    long long tyIsArray;
    long long isInout;
};
struct FieldDef {
    long long nameStart;
    long long nameLen;
    long long tyStart;
    long long tyLen;
    long long tyIsArray;
};
struct StructDef {
    long long nameStart;
    long long nameLen;
    PlewArray_FieldDef fields;
};
struct Variant {
    long long nameStart;
    long long nameLen;
    PlewArray_FieldDef fields;
};
struct EnumDef {
    long long nameStart;
    long long nameLen;
    PlewArray_Variant variants;
};
struct Func {
    long long nameStart;
    long long nameLen;
    PlewArray_Param params;
    long long hasRet;
    long long retStart;
    long long retLen;
    long long retIsArray;
    long long body;
};
struct Comp {
    PlewArray_U8 bytes;
    PlewArray_Tok toks;
    long long pos;
    PlewArray_Expr exprs;
    PlewArray_Stmt stmts;
    PlewArray_Block blocks;
    PlewArray_Func funcs;
    PlewArray_StructDef structs;
    PlewArray_EnumDef enums;
    PlewArray_Bind arrayElems;
    PlewArray_Local locals;
    long long tmp;
    long long curIsMain;
    long long curRetVoid;
    long long impPrint;
    long long impWrite;
    long long impWriteByte;
    long long impReadStdin;
    long long impReadFile;
    long long impArgCount;
    long long impArgAt;
};
__attribute__((unused)) static PlewArray_U8 PlewArray_U8_new(void) { PlewArray_U8 a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static unsigned char PlewArray_U8_get(PlewArray_U8 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_U8_set(PlewArray_U8* a, long long i, unsigned char v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_U8_push(PlewArray_U8* a, unsigned char v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; unsigned char* nd = (unsigned char*)malloc(sizeof(unsigned char) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Tok PlewArray_Tok_new(void) { PlewArray_Tok a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Tok PlewArray_Tok_get(PlewArray_Tok a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Tok_set(PlewArray_Tok* a, long long i, Tok v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Tok_push(PlewArray_Tok* a, Tok v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Tok* nd = (Tok*)malloc(sizeof(Tok) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Arg PlewArray_Arg_new(void) { PlewArray_Arg a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Arg PlewArray_Arg_get(PlewArray_Arg a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Arg_set(PlewArray_Arg* a, long long i, Arg v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Arg_push(PlewArray_Arg* a, Arg v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Arg* nd = (Arg*)malloc(sizeof(Arg) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_MakeField PlewArray_MakeField_new(void) { PlewArray_MakeField a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static MakeField PlewArray_MakeField_get(PlewArray_MakeField a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_MakeField_set(PlewArray_MakeField* a, long long i, MakeField v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_MakeField_push(PlewArray_MakeField* a, MakeField v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MakeField* nd = (MakeField*)malloc(sizeof(MakeField) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_U64 PlewArray_U64_new(void) { PlewArray_U64 a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static long long PlewArray_U64_get(PlewArray_U64 a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_U64_set(PlewArray_U64* a, long long i, long long v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_U64_push(PlewArray_U64* a, long long v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; long long* nd = (long long*)malloc(sizeof(long long) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Bind PlewArray_Bind_new(void) { PlewArray_Bind a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Bind PlewArray_Bind_get(PlewArray_Bind a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Bind_set(PlewArray_Bind* a, long long i, Bind v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Bind_push(PlewArray_Bind* a, Bind v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Bind* nd = (Bind*)malloc(sizeof(Bind) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_MatchArm PlewArray_MatchArm_new(void) { PlewArray_MatchArm a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static MatchArm PlewArray_MatchArm_get(PlewArray_MatchArm a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_MatchArm_set(PlewArray_MatchArm* a, long long i, MatchArm v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_MatchArm_push(PlewArray_MatchArm* a, MatchArm v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MatchArm* nd = (MatchArm*)malloc(sizeof(MatchArm) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_FieldDef PlewArray_FieldDef_new(void) { PlewArray_FieldDef a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static FieldDef PlewArray_FieldDef_get(PlewArray_FieldDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_FieldDef_set(PlewArray_FieldDef* a, long long i, FieldDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_FieldDef_push(PlewArray_FieldDef* a, FieldDef v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; FieldDef* nd = (FieldDef*)malloc(sizeof(FieldDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_new(void) { PlewArray_Variant a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Variant PlewArray_Variant_get(PlewArray_Variant a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Variant_set(PlewArray_Variant* a, long long i, Variant v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Variant_push(PlewArray_Variant* a, Variant v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Variant* nd = (Variant*)malloc(sizeof(Variant) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Param PlewArray_Param_new(void) { PlewArray_Param a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Param PlewArray_Param_get(PlewArray_Param a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Param_set(PlewArray_Param* a, long long i, Param v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Param_push(PlewArray_Param* a, Param v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Param* nd = (Param*)malloc(sizeof(Param) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Expr PlewArray_Expr_new(void) { PlewArray_Expr a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Expr PlewArray_Expr_get(PlewArray_Expr a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Expr_set(PlewArray_Expr* a, long long i, Expr v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Expr_push(PlewArray_Expr* a, Expr v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Expr* nd = (Expr*)malloc(sizeof(Expr) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Stmt PlewArray_Stmt_new(void) { PlewArray_Stmt a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Stmt PlewArray_Stmt_get(PlewArray_Stmt a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Stmt_set(PlewArray_Stmt* a, long long i, Stmt v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Stmt_push(PlewArray_Stmt* a, Stmt v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Stmt* nd = (Stmt*)malloc(sizeof(Stmt) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Block PlewArray_Block_new(void) { PlewArray_Block a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Block PlewArray_Block_get(PlewArray_Block a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Block_set(PlewArray_Block* a, long long i, Block v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Block_push(PlewArray_Block* a, Block v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Block* nd = (Block*)malloc(sizeof(Block) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_new(void) { PlewArray_Func a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Func PlewArray_Func_get(PlewArray_Func a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Func_set(PlewArray_Func* a, long long i, Func v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Func_push(PlewArray_Func* a, Func v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Func* nd = (Func*)malloc(sizeof(Func) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_new(void) { PlewArray_StructDef a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static StructDef PlewArray_StructDef_get(PlewArray_StructDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_StructDef_set(PlewArray_StructDef* a, long long i, StructDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_StructDef_push(PlewArray_StructDef* a, StructDef v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; StructDef* nd = (StructDef*)malloc(sizeof(StructDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_new(void) { PlewArray_EnumDef a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static EnumDef PlewArray_EnumDef_get(PlewArray_EnumDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_EnumDef_set(PlewArray_EnumDef* a, long long i, EnumDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_EnumDef_push(PlewArray_EnumDef* a, EnumDef v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; EnumDef* nd = (EnumDef*)malloc(sizeof(EnumDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_Local PlewArray_Local_new(void) { PlewArray_Local a; a.data = 0; a.len = 0; a.cap = 0; return a; }
__attribute__((unused)) static Local PlewArray_Local_get(PlewArray_Local a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static void PlewArray_Local_set(PlewArray_Local* a, long long i, Local v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
__attribute__((unused)) static void PlewArray_Local_push(PlewArray_Local* a, Local v) { if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Local* nd = (Local*)malloc(sizeof(Local) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }
unsigned char at(Lexer* lx, long long off);
long long isDigit(unsigned char b);
long long isAlpha(unsigned char b);
long long isAlnum(unsigned char b);
long long rangeEquals(PlewArray_U8 bytes, long long start, long long len, PlewString kw);
Kind identKind(PlewArray_U8 bytes, long long start, long long len);
void emit(Lexer* lx, Kind k, long long start, long long len);
long long lastWasNewline(Lexer* lx);
long long lastCanEnd(Lexer* lx);
void lex(Lexer* lx);
long long kindCode(Kind k);
Kind curKind(Comp* c);
Tok cur(Comp* c);
Kind peekKind(Comp* c, long long off);
void advance(Comp* c);
void skipNewlines(Comp* c);
long long identIs(Comp* c, PlewString kw);
long long pushExpr(Comp* c, Expr e);
long long pushStmt(Comp* c, Stmt s);
long long tokenValue(Comp* c, Tok t);
long long binPrec(Kind k);
long long parsePrimary(Comp* c);
long long parseUnary(Comp* c);
long long parsePostfix(Comp* c);
long long parseMake(Comp* c);
long long parseBin(Comp* c, long long minPrec);
long long parseExpr(Comp* c);
PlewArray_Arg parseCallArgs(Comp* c);
long long isAssignOp(Kind k);
PType parseTypeTok(Comp* c);
void recordArrayElem(Comp* c, PType ty);
long long parseLet(Comp* c, long long mutable);
long long parsePrint(Comp* c);
long long parseReturn(Comp* c);
long long parseIf(Comp* c);
long long parseWhile(Comp* c);
long long parseFor(Comp* c);
long long parseExprOrAssign(Comp* c);
long long parseMatch(Comp* c);
long long parseStmt(Comp* c);
long long parseBlock(Comp* c);
void parseFunc(Comp* c);
void parseStruct(Comp* c);
void parseEnum(Comp* c);
void markImport(Comp* c, long long segStart, long long segLen, long long nameStart, long long nameLen);
void parseImport(Comp* c);
void parseProgram(Comp* c);
PlewString digitStr(long long d);
void writeInt(long long n);
void writeSpan(Comp* c, long long start, long long len);
long long isPrimType(Comp* c, long long start, long long len);
void genCElem(Comp* c, long long start, long long len);
void genCTypeRef(Comp* c, long long start, long long len, long long isArray);
void genCType(Comp* c, long long start, long long len);
long long spansEqual(Comp* c, long long aStart, long long aLen, long long bStart, long long bLen);
long long findFunc(Comp* c, long long nameStart, long long nameLen);
long long callLabelsOk(Comp* c, long long nameStart, long long nameLen, PlewArray_Arg args);
long long armCovers(Comp* c, PlewArray_MatchArm arms, long long variantStart, long long variantLen);
long long matchExhaustive(Comp* c, PlewArray_MatchArm arms);
long long variantIndex(Comp* c, long long enumStart, long long enumLen, long long variantStart, long long variantLen);
TypeInfo scalarInfo(void);
TypeInfo typeInfoOfName(Comp* c, long long start, long long len, long long isArray);
void addLocal(Comp* c, long long nameStart, long long nameLen, long long tyStart, long long tyLen, long long isArray, long long isInout);
long long isInoutLocal(Comp* c, long long start, long long len);
TypeInfo fieldType(Comp* c, long long structStart, long long structLen, long long fieldStart, long long fieldLen);
TypeInfo exprType(Comp* c, long long id);
void addBindLocal(Comp* c, long long enumStart, long long enumLen, long long variantStart, long long variantLen, long long bindStart, long long bindLen);
void genBindType(Comp* c, long long enumStart, long long enumLen, long long variantStart, long long variantLen, long long bindStart, long long bindLen);
PlewString binOpStr(long long op);
PlewString unaryOpStr(long long op);
long long strDecodedLen(Comp* c, long long start, long long len);
PlewString assignOpStr(long long op);
PlewString assignToBinStr(long long op);
void genExpr(Comp* c, long long id);
void genArrayLiteral(Comp* c, long long exprId, long long elemStart, long long elemLen);
long long isStringEq(Comp* c, long long op, long long lhs);
long long isEnumName(Comp* c, long long start, long long len);
long long isAllNullary(Comp* c, long long start, long long len);
long long isEnumEq(Comp* c, long long op, long long lhs);
long long compareNeedsTrait(Comp* c, long long op, long long lhs);
void emitEnumOperand(Comp* c, long long id, long long enStart, long long enLen);
void emitEnumTagCmp(Comp* c, long long lhs, long long rhs, long long op, long long outer);
void genCond(Comp* c, long long id);
void genStmt(Comp* c, long long id);
void genBlock(Comp* c, long long id);
long long nameIsMain(Comp* c, Func f);
void genStructDef(Comp* c, long long si);
void genSignature(Comp* c, Func f);
void genFunc(Comp* c, long long fi);
void genEnumDef(Comp* c, long long ei);
void wPA(Comp* c, long long elemStart, long long elemLen);
void genArrayTypedef(Comp* c, long long elemStart, long long elemLen);
void genArrayRuntimeFns(Comp* c, long long elemStart, long long elemLen);
long long isU8Elem(Comp* c, long long elemStart, long long elemLen);
void genU8ArrayTypedef(void);
void genU8ArrayRuntime(void);
unsigned char at(Lexer* lx, long long off) {
    long long i = ((*lx).pos + off);
    if (i < (long long)(((*lx).bytes).len)) {
    return PlewArray_U8_get((*lx).bytes, (long long)(i));
    }
    return 0;
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
long long rangeEquals(PlewArray_U8 bytes, long long start, long long len, PlewString kw) {
    PlewArray_U8 kb = ({ PlewString __s = kw; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; });
    if (len != (long long)((kb).len)) {
    return 0;
    }
    long long j = 0;
    while (j < len) {
    if (PlewArray_U8_get(bytes, (long long)((start + j))) != PlewArray_U8_get(kb, (long long)(j))) {
    return 0;
    }
    j += 1;
    }
    return 1;
}
Kind identKind(PlewArray_U8 bytes, long long start, long long len) {
    if (rangeEquals(bytes, start, len, (PlewString){"fn", 2})) {
    return (Kind){.tag = 5};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"struct", 6})) {
    return (Kind){.tag = 6};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"enum", 4})) {
    return (Kind){.tag = 7};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"match", 5})) {
    return (Kind){.tag = 8};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"if", 2})) {
    return (Kind){.tag = 9};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"else", 4})) {
    return (Kind){.tag = 10};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"while", 5})) {
    return (Kind){.tag = 11};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"for", 3})) {
    return (Kind){.tag = 12};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"break", 5})) {
    return (Kind){.tag = 13};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"continue", 8})) {
    return (Kind){.tag = 14};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"return", 6})) {
    return (Kind){.tag = 15};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"give", 4})) {
    return (Kind){.tag = 16};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"val", 3})) {
    return (Kind){.tag = 17};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"mut", 3})) {
    return (Kind){.tag = 18};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"in", 2})) {
    return (Kind){.tag = 19};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"as", 2})) {
    return (Kind){.tag = 20};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"inout", 5})) {
    return (Kind){.tag = 21};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"true", 4})) {
    return (Kind){.tag = 22};
    }
    if (rangeEquals(bytes, start, len, (PlewString){"false", 5})) {
    return (Kind){.tag = 23};
    }
    return (Kind){.tag = 4};
}
void emit(Lexer* lx, Kind k, long long start, long long len) {
    PlewArray_Tok_push(&((*lx).toks), (Tok){.kind = k, .start = start, .len = len});
    (*lx).pos = (start + len);
}
long long lastWasNewline(Lexer* lx) {
    long long n = (long long)(((*lx).toks).len);
    if (n == 0) {
    return 0;
    }
    Tok t = PlewArray_Tok_get((*lx).toks, (long long)((n - 1)));
    {
    Kind _m0 = t.kind;
    if (_m0.tag == 1) {
    return 1;
    }
    else {
    return 0;
    }
    }
}
long long lastCanEnd(Lexer* lx) {
    long long n = (long long)(((*lx).toks).len);
    if (n == 0) {
    return 0;
    }
    Tok t = PlewArray_Tok_get((*lx).toks, (long long)((n - 1)));
    {
    Kind _m1 = t.kind;
    if (_m1.tag == 4) {
    return 1;
    }
    else if (_m1.tag == 2) {
    return 1;
    }
    else if (_m1.tag == 3) {
    return 1;
    }
    else if (_m1.tag == 25) {
    return 1;
    }
    else if (_m1.tag == 27) {
    return 1;
    }
    else if (_m1.tag == 29) {
    return 1;
    }
    else if (_m1.tag == 50) {
    return 1;
    }
    else if (_m1.tag == 22) {
    return 1;
    }
    else if (_m1.tag == 23) {
    return 1;
    }
    else if (_m1.tag == 15) {
    return 1;
    }
    else if (_m1.tag == 13) {
    return 1;
    }
    else if (_m1.tag == 14) {
    return 1;
    }
    else {
    return 0;
    }
    }
}
void lex(Lexer* lx) {
    while ((*lx).pos < (long long)(((*lx).bytes).len)) {
    unsigned char b = at(&((*lx)), 0);
    if (b == 32) {
    (*lx).pos += 1;
    continue;
    }
    if (b == 9) {
    (*lx).pos += 1;
    continue;
    }
    if (b == 13) {
    (*lx).pos += 1;
    continue;
    }
    if (b == 10) {
    if ((*lx).depth > 0) {
    (*lx).pos += 1;
    }
    else {
    if (lastCanEnd(&((*lx)))) {
    if (lastWasNewline(&((*lx)))) {
    (*lx).pos += 1;
    }
    else {
    emit(&((*lx)), (Kind){.tag = 1}, (*lx).pos, 1);
    }
    }
    else {
    (*lx).pos += 1;
    }
    }
    continue;
    }
    if (b == 47) {
    if (at(&((*lx)), 1) == 47) {
    while ((*lx).pos < (long long)(((*lx).bytes).len)) {
    if (at(&((*lx)), 0) == 10) {
    break;
    }
    (*lx).pos += 1;
    }
    continue;
    }
    }
    if (isDigit(b)) {
    long long start = (*lx).pos;
    long long j = (*lx).pos;
    while (j < (long long)(((*lx).bytes).len)) {
    if (isDigit(PlewArray_U8_get((*lx).bytes, (long long)(j)))) {
    j += 1;
    }
    else {
    break;
    }
    }
    emit(&((*lx)), (Kind){.tag = 2}, start, (j - start));
    continue;
    }
    if (isAlpha(b)) {
    long long start = (*lx).pos;
    long long j = (*lx).pos;
    while (j < (long long)(((*lx).bytes).len)) {
    if (isAlnum(PlewArray_U8_get((*lx).bytes, (long long)(j)))) {
    j += 1;
    }
    else {
    break;
    }
    }
    long long len = (j - start);
    Kind k = identKind((*lx).bytes, start, len);
    emit(&((*lx)), k, start, len);
    continue;
    }
    if (b == 34) {
    long long start = (*lx).pos;
    long long j = ((*lx).pos + 1);
    while (j < (long long)(((*lx).bytes).len)) {
    if (PlewArray_U8_get((*lx).bytes, (long long)(j)) == 92) {
    j += 2;
    continue;
    }
    if (PlewArray_U8_get((*lx).bytes, (long long)(j)) == 34) {
    j += 1;
    break;
    }
    j += 1;
    }
    emit(&((*lx)), (Kind){.tag = 3}, start, (j - start));
    continue;
    }
    unsigned char b2 = at(&((*lx)), 1);
    if (b == 46) {
    if (b2 == 46) {
    unsigned char b3 = at(&((*lx)), 2);
    if (b3 == 60) {
    emit(&((*lx)), (Kind){.tag = 56}, (*lx).pos, 3);
    continue;
    }
    if (b3 == 61) {
    emit(&((*lx)), (Kind){.tag = 57}, (*lx).pos, 3);
    continue;
    }
    }
    emit(&((*lx)), (Kind){.tag = 32}, (*lx).pos, 1);
    continue;
    }
    if (b == 61) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 34}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    emit(&((*lx)), (Kind){.tag = 49}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 33}, (*lx).pos, 1);
    continue;
    }
    if (b == 33) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 35}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 47}, (*lx).pos, 1);
    continue;
    }
    if (b == 60) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 37}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 36}, (*lx).pos, 1);
    continue;
    }
    if (b == 62) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 39}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 38}, (*lx).pos, 1);
    continue;
    }
    if (b == 43) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 51}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 40}, (*lx).pos, 1);
    continue;
    }
    if (b == 45) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 52}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    emit(&((*lx)), (Kind){.tag = 48}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 41}, (*lx).pos, 1);
    continue;
    }
    if (b == 42) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 53}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 42}, (*lx).pos, 1);
    continue;
    }
    if (b == 47) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 54}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    emit(&((*lx)), (Kind){.tag = 50}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 43}, (*lx).pos, 1);
    continue;
    }
    if (b == 37) {
    if (b2 == 61) {
    emit(&((*lx)), (Kind){.tag = 55}, (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 44}, (*lx).pos, 1);
    continue;
    }
    if (b == 38) {
    if (b2 == 38) {
    emit(&((*lx)), (Kind){.tag = 45}, (*lx).pos, 2);
    continue;
    }
    }
    if (b == 124) {
    if (b2 == 124) {
    emit(&((*lx)), (Kind){.tag = 46}, (*lx).pos, 2);
    continue;
    }
    }
    if (b == 40) {
    emit(&((*lx)), (Kind){.tag = 24}, (*lx).pos, 1);
    (*lx).depth += 1;
    continue;
    }
    if (b == 41) {
    emit(&((*lx)), (Kind){.tag = 25}, (*lx).pos, 1);
    (*lx).depth -= 1;
    continue;
    }
    if (b == 91) {
    emit(&((*lx)), (Kind){.tag = 26}, (*lx).pos, 1);
    (*lx).depth += 1;
    continue;
    }
    if (b == 93) {
    emit(&((*lx)), (Kind){.tag = 27}, (*lx).pos, 1);
    (*lx).depth -= 1;
    continue;
    }
    if (b == 123) {
    emit(&((*lx)), (Kind){.tag = 28}, (*lx).pos, 1);
    continue;
    }
    if (b == 125) {
    emit(&((*lx)), (Kind){.tag = 29}, (*lx).pos, 1);
    continue;
    }
    if (b == 44) {
    emit(&((*lx)), (Kind){.tag = 30}, (*lx).pos, 1);
    continue;
    }
    if (b == 58) {
    emit(&((*lx)), (Kind){.tag = 31}, (*lx).pos, 1);
    continue;
    }
    emit(&((*lx)), (Kind){.tag = 58}, (*lx).pos, 1);
    }
    PlewArray_Tok_push(&((*lx).toks), (Tok){.kind = (Kind){.tag = 0}, .start = (*lx).pos, .len = 0});
}
long long kindCode(Kind k) {
    {
    Kind _m2 = k;
    if (_m2.tag == 0) {
    return 0;
    }
    else if (_m2.tag == 1) {
    return 1;
    }
    else if (_m2.tag == 2) {
    return 2;
    }
    else if (_m2.tag == 3) {
    return 3;
    }
    else if (_m2.tag == 4) {
    return 4;
    }
    else if (_m2.tag == 5) {
    return 10;
    }
    else if (_m2.tag == 6) {
    return 11;
    }
    else if (_m2.tag == 7) {
    return 12;
    }
    else if (_m2.tag == 8) {
    return 13;
    }
    else if (_m2.tag == 9) {
    return 14;
    }
    else if (_m2.tag == 10) {
    return 15;
    }
    else if (_m2.tag == 11) {
    return 16;
    }
    else if (_m2.tag == 12) {
    return 17;
    }
    else if (_m2.tag == 13) {
    return 18;
    }
    else if (_m2.tag == 14) {
    return 19;
    }
    else if (_m2.tag == 15) {
    return 20;
    }
    else if (_m2.tag == 16) {
    return 21;
    }
    else if (_m2.tag == 17) {
    return 22;
    }
    else if (_m2.tag == 18) {
    return 23;
    }
    else if (_m2.tag == 19) {
    return 24;
    }
    else if (_m2.tag == 20) {
    return 25;
    }
    else if (_m2.tag == 21) {
    return 26;
    }
    else if (_m2.tag == 22) {
    return 27;
    }
    else if (_m2.tag == 23) {
    return 28;
    }
    else if (_m2.tag == 24) {
    return 40;
    }
    else if (_m2.tag == 25) {
    return 41;
    }
    else if (_m2.tag == 26) {
    return 42;
    }
    else if (_m2.tag == 27) {
    return 43;
    }
    else if (_m2.tag == 28) {
    return 44;
    }
    else if (_m2.tag == 29) {
    return 45;
    }
    else if (_m2.tag == 30) {
    return 46;
    }
    else if (_m2.tag == 31) {
    return 47;
    }
    else if (_m2.tag == 32) {
    return 48;
    }
    else if (_m2.tag == 33) {
    return 49;
    }
    else if (_m2.tag == 34) {
    return 50;
    }
    else if (_m2.tag == 35) {
    return 51;
    }
    else if (_m2.tag == 36) {
    return 52;
    }
    else if (_m2.tag == 37) {
    return 53;
    }
    else if (_m2.tag == 38) {
    return 54;
    }
    else if (_m2.tag == 39) {
    return 55;
    }
    else if (_m2.tag == 40) {
    return 56;
    }
    else if (_m2.tag == 41) {
    return 57;
    }
    else if (_m2.tag == 42) {
    return 58;
    }
    else if (_m2.tag == 43) {
    return 59;
    }
    else if (_m2.tag == 44) {
    return 60;
    }
    else if (_m2.tag == 45) {
    return 61;
    }
    else if (_m2.tag == 46) {
    return 62;
    }
    else if (_m2.tag == 47) {
    return 63;
    }
    else if (_m2.tag == 48) {
    return 64;
    }
    else if (_m2.tag == 49) {
    return 65;
    }
    else if (_m2.tag == 50) {
    return 66;
    }
    else if (_m2.tag == 51) {
    return 67;
    }
    else if (_m2.tag == 52) {
    return 68;
    }
    else if (_m2.tag == 53) {
    return 69;
    }
    else if (_m2.tag == 54) {
    return 70;
    }
    else if (_m2.tag == 55) {
    return 71;
    }
    else if (_m2.tag == 56) {
    return 72;
    }
    else if (_m2.tag == 57) {
    return 73;
    }
    else if (_m2.tag == 58) {
    return 99;
    }
    else { __builtin_unreachable(); }
    }
}
Kind curKind(Comp* c) {
    return PlewArray_Tok_get((*c).toks, (long long)((*c).pos)).kind;
}
Tok cur(Comp* c) {
    return PlewArray_Tok_get((*c).toks, (long long)((*c).pos));
}
Kind peekKind(Comp* c, long long off) {
    long long i = ((*c).pos + off);
    if (i < (long long)(((*c).toks).len)) {
    return PlewArray_Tok_get((*c).toks, (long long)(i)).kind;
    }
    return (Kind){.tag = 0};
}
void advance(Comp* c) {
    (*c).pos = ((*c).pos + 1);
}
void skipNewlines(Comp* c) {
    while (1) {
    {
    Kind _m3 = curKind(&((*c)));
    if (_m3.tag == 1) {
    advance(&((*c)));
    }
    else {
    break;
    }
    }
    }
}
long long identIs(Comp* c, PlewString kw) {
    Tok t = PlewArray_Tok_get((*c).toks, (long long)((*c).pos));
    return rangeEquals((*c).bytes, t.start, t.len, kw);
}
long long pushExpr(Comp* c, Expr e) {
    long long id = (long long)(((*c).exprs).len);
    PlewArray_Expr_push(&((*c).exprs), e);
    return id;
}
long long pushStmt(Comp* c, Stmt s) {
    long long id = (long long)(((*c).stmts).len);
    PlewArray_Stmt_push(&((*c).stmts), s);
    return id;
}
long long tokenValue(Comp* c, Tok t) {
    long long v = 0;
    long long j = 0;
    while (j < t.len) {
    unsigned char b = PlewArray_U8_get((*c).bytes, (long long)((t.start + j)));
    v = ((v * 10) + (((long long)(b)) - 48));
    j += 1;
    }
    return v;
}
long long binPrec(Kind k) {
    {
    Kind _m4 = k;
    if (_m4.tag == 46) {
    return 1;
    }
    else if (_m4.tag == 45) {
    return 2;
    }
    else if (_m4.tag == 34) {
    return 3;
    }
    else if (_m4.tag == 35) {
    return 3;
    }
    else if (_m4.tag == 36) {
    return 3;
    }
    else if (_m4.tag == 37) {
    return 3;
    }
    else if (_m4.tag == 38) {
    return 3;
    }
    else if (_m4.tag == 39) {
    return 3;
    }
    else if (_m4.tag == 40) {
    return 4;
    }
    else if (_m4.tag == 41) {
    return 4;
    }
    else if (_m4.tag == 42) {
    return 5;
    }
    else if (_m4.tag == 43) {
    return 5;
    }
    else if (_m4.tag == 44) {
    return 5;
    }
    else {
    return 0;
    }
    }
}
long long parsePrimary(Comp* c) {
    Kind k = curKind(&((*c)));
    {
    Kind _m5 = k;
    if (_m5.tag == 2) {
    Tok t = cur(&((*c)));
    advance(&((*c)));
    long long v = tokenValue(&((*c)), t);
    return pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v}});
    }
    else if (_m5.tag == 4) {
    Tok t = cur(&((*c)));
    {
    Kind _m6 = peekKind(&((*c)), 1);
    if (_m6.tag == 24) {
    advance(&((*c)));
    advance(&((*c)));
    PlewArray_Arg args = parseCallArgs(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 4, .data.Call = {.nameStart = t.start, .nameLen = t.len, .args = args}});
    }
    else {
    advance(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = t.start, .len = t.len}});
    }
    }
    }
    else if (_m5.tag == 22) {
    advance(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 1}});
    }
    else if (_m5.tag == 23) {
    advance(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0}});
    }
    else if (_m5.tag == 24) {
    advance(&((*c)));
    long long inner = parseExpr(&((*c)));
    {
    Kind _m7 = curKind(&((*c)));
    if (_m7.tag == 25) {
    advance(&((*c)));
    }
    else {
    }
    }
    return inner;
    }
    else if (_m5.tag == 36) {
    return parseMake(&((*c)));
    }
    else if (_m5.tag == 3) {
    Tok t = cur(&((*c)));
    advance(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 7, .data.Str = {.start = t.start, .len = t.len}});
    }
    else if (_m5.tag == 26) {
    advance(&((*c)));
    PlewArray_U64 elems = PlewArray_U64_new();
    while (1) {
    skipNewlines(&((*c)));
    {
    Kind _m8 = curKind(&((*c)));
    if (_m8.tag == 27) {
    advance(&((*c)));
    break;
    }
    else if (_m8.tag == 0) {
    break;
    }
    else {
    long long e = parseExpr(&((*c)));
    PlewArray_U64_push(&(elems), e);
    {
    Kind _m9 = curKind(&((*c)));
    if (_m9.tag == 30) {
    advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    return pushExpr(&((*c)), (Expr){.tag = 8, .data.Array = {.elems = elems}});
    }
    else {
    advance(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0}});
    }
    }
}
long long parseUnary(Comp* c) {
    Kind k = curKind(&((*c)));
    {
    Kind _m10 = k;
    if (_m10.tag == 41) {
    advance(&((*c)));
    long long o = parseUnary(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 57, .operand = o}});
    }
    else if (_m10.tag == 47) {
    advance(&((*c)));
    long long o = parseUnary(&((*c)));
    return pushExpr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 63, .operand = o}});
    }
    else {
    return parsePostfix(&((*c)));
    }
    }
}
long long parsePostfix(Comp* c) {
    long long e = parsePrimary(&((*c)));
    while (1) {
    {
    Kind _m11 = curKind(&((*c)));
    if (_m11.tag == 32) {
    advance(&((*c)));
    Tok nameTok = cur(&((*c)));
    advance(&((*c)));
    {
    Kind _m12 = curKind(&((*c)));
    if (_m12.tag == 24) {
    advance(&((*c)));
    PlewArray_Arg args = parseCallArgs(&((*c)));
    e = pushExpr(&((*c)), (Expr){.tag = 10, .data.Method = {.recv = e, .nameStart = nameTok.start, .nameLen = nameTok.len, .args = args}});
    }
    else {
    e = pushExpr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    }
    }
    else if (_m11.tag == 26) {
    advance(&((*c)));
    long long idx = parseExpr(&((*c)));
    {
    Kind _m13 = curKind(&((*c)));
    if (_m13.tag == 27) {
    advance(&((*c)));
    }
    else {
    }
    }
    e = pushExpr(&((*c)), (Expr){.tag = 9, .data.Index = {.base = e, .index = idx}});
    }
    else if (_m11.tag == 20) {
    advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    e = pushExpr(&((*c)), (Expr){.tag = 11, .data.Cast = {.operand = e, .tyStart = ty.start, .tyLen = ty.len}});
    }
    else {
    break;
    }
    }
    }
    return e;
}
long long parseMake(Comp* c) {
    advance(&((*c)));
    Tok typeTok = cur(&((*c)));
    advance(&((*c)));
    long long variantStart = 0;
    long long variantLen = 0;
    long long isEnum = 0;
    {
    Kind _m14 = curKind(&((*c)));
    if (_m14.tag == 32) {
    advance(&((*c)));
    Tok vTok = cur(&((*c)));
    advance(&((*c)));
    variantStart = vTok.start;
    variantLen = vTok.len;
    isEnum = 1;
    }
    else {
    }
    }
    PlewArray_MakeField fields = PlewArray_MakeField_new();
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m15 = k;
    if (_m15.tag == 50) {
    advance(&((*c)));
    break;
    }
    else if (_m15.tag == 38) {
    advance(&((*c)));
    break;
    }
    else if (_m15.tag == 0) {
    break;
    }
    else if (_m15.tag == 4) {
    Tok fTok = cur(&((*c)));
    advance(&((*c)));
    {
    Kind _m16 = curKind(&((*c)));
    if (_m16.tag == 33) {
    advance(&((*c)));
    }
    else {
    }
    }
    long long v = parseExpr(&((*c)));
    PlewArray_MakeField_push(&(fields), (MakeField){.nameStart = fTok.start, .nameLen = fTok.len, .value = v});
    }
    else {
    advance(&((*c)));
    }
    }
    }
    return pushExpr(&((*c)), (Expr){.tag = 6, .data.Make = {.typeStart = typeTok.start, .typeLen = typeTok.len, .variantStart = variantStart, .variantLen = variantLen, .isEnum = isEnum, .fields = fields}});
}
long long parseBin(Comp* c, long long minPrec) {
    long long left = parseUnary(&((*c)));
    while (1) {
    Kind k = curKind(&((*c)));
    long long prec = binPrec(k);
    if (prec == 0) {
    break;
    }
    if (prec < minPrec) {
    break;
    }
    long long op = kindCode(k);
    advance(&((*c)));
    long long right = parseBin(&((*c)), (prec + 1));
    left = pushExpr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = op, .lhs = left, .rhs = right}});
    }
    return left;
}
long long parseExpr(Comp* c) {
    return parseBin(&((*c)), 1);
}
PlewArray_Arg parseCallArgs(Comp* c) {
    PlewArray_Arg args = PlewArray_Arg_new();
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m17 = k;
    if (_m17.tag == 25) {
    advance(&((*c)));
    break;
    }
    else if (_m17.tag == 0) {
    break;
    }
    else {
    long long labelStart = 0;
    long long labelLen = 0;
    long long hasLabel = 0;
    {
    Kind _m18 = curKind(&((*c)));
    if (_m18.tag == 4) {
    {
    Kind _m19 = peekKind(&((*c)), 1);
    if (_m19.tag == 31) {
    Tok lt = cur(&((*c)));
    labelStart = lt.start;
    labelLen = lt.len;
    hasLabel = 1;
    advance(&((*c)));
    advance(&((*c)));
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
    Kind _m20 = curKind(&((*c)));
    if (_m20.tag == 21) {
    advance(&((*c)));
    isInout = 1;
    }
    else {
    }
    }
    long long e = parseExpr(&((*c)));
    PlewArray_Arg_push(&(args), (Arg){.expr = e, .isInout = isInout, .labelStart = labelStart, .labelLen = labelLen, .hasLabel = hasLabel});
    {
    Kind _m21 = curKind(&((*c)));
    if (_m21.tag == 30) {
    advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    return args;
}
long long isAssignOp(Kind k) {
    {
    Kind _m22 = k;
    if (_m22.tag == 33) {
    return 1;
    }
    else if (_m22.tag == 51) {
    return 1;
    }
    else if (_m22.tag == 52) {
    return 1;
    }
    else if (_m22.tag == 53) {
    return 1;
    }
    else if (_m22.tag == 54) {
    return 1;
    }
    else if (_m22.tag == 55) {
    return 1;
    }
    else {
    return 0;
    }
    }
}
PType parseTypeTok(Comp* c) {
    Tok head = cur(&((*c)));
    advance(&((*c)));
    {
    Kind _m23 = curKind(&((*c)));
    if (_m23.tag == 26) {
    advance(&((*c)));
    Tok elem = cur(&((*c)));
    advance(&((*c)));
    long long depth = 1;
    while (depth > 0) {
    {
    Kind _m24 = curKind(&((*c)));
    if (_m24.tag == 26) {
    depth += 1;
    }
    else if (_m24.tag == 27) {
    depth -= 1;
    }
    else if (_m24.tag == 0) {
    break;
    }
    else {
    }
    }
    advance(&((*c)));
    }
    return (PType){.start = elem.start, .len = elem.len, .isArray = 1};
    }
    else {
    }
    }
    return (PType){.start = head.start, .len = head.len, .isArray = 0};
}
void recordArrayElem(Comp* c, PType ty) {
    if (ty.isArray) {
    long long i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind e = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, ty.start, ty.len)) {
    return;
    }
    i += 1;
    }
    PlewArray_Bind_push(&((*c).arrayElems), (Bind){.nameStart = ty.start, .nameLen = ty.len});
    }
}
long long parseLet(Comp* c, long long mutable) {
    advance(&((*c)));
    Tok nameTok = cur(&((*c)));
    advance(&((*c)));
    long long tyStart = 0;
    long long tyLen = 0;
    long long tyIsArray = 0;
    {
    Kind _m25 = curKind(&((*c)));
    if (_m25.tag == 31) {
    advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    recordArrayElem(&((*c)), ty);
    }
    else {
    }
    }
    {
    Kind _m26 = curKind(&((*c)));
    if (_m26.tag == 33) {
    advance(&((*c)));
    }
    else {
    }
    }
    long long init = parseExpr(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 0, .data.Let = {.mutable = mutable, .nameStart = nameTok.start, .nameLen = nameTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .init = init}});
}
long long parsePrint(Comp* c) {
    advance(&((*c)));
    advance(&((*c)));
    long long e = parseExpr(&((*c)));
    {
    Kind _m27 = curKind(&((*c)));
    if (_m27.tag == 25) {
    advance(&((*c)));
    }
    else {
    }
    }
    return pushStmt(&((*c)), (Stmt){.tag = 2, .data.Print = {.expr = e}});
}
long long parseReturn(Comp* c) {
    advance(&((*c)));
    {
    Kind _m28 = curKind(&((*c)));
    if (_m28.tag == 1) {
    return pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    }
    else if (_m28.tag == 29) {
    return pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    }
    else if (_m28.tag == 0) {
    return pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    }
    else {
    long long e = parseExpr(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = e, .hasValue = 1}});
    }
    }
}
long long parseIf(Comp* c) {
    advance(&((*c)));
    long long cond = parseExpr(&((*c)));
    long long thenBlk = parseBlock(&((*c)));
    skipNewlines(&((*c)));
    {
    Kind _m29 = curKind(&((*c)));
    if (_m29.tag == 10) {
    advance(&((*c)));
    {
    Kind _m30 = curKind(&((*c)));
    if (_m30.tag == 9) {
    long long nested = parseIf(&((*c)));
    PlewArray_U64 one = PlewArray_U64_new();
    PlewArray_U64_push(&(one), nested);
    long long blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = one});
    return pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId, .hasElse = 1}});
    }
    else {
    long long elseBlk = parseBlock(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk, .hasElse = 1}});
    }
    }
    }
    else {
    return pushStmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = 0, .hasElse = 0}});
    }
    }
}
long long parseWhile(Comp* c) {
    advance(&((*c)));
    long long cond = parseExpr(&((*c)));
    long long body = parseBlock(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 6, .data.While = {.cond = cond, .body = body}});
}
long long parseFor(Comp* c) {
    advance(&((*c)));
    {
    Kind _m31 = curKind(&((*c)));
    if (_m31.tag == 17) {
    advance(&((*c)));
    }
    else {
    }
    }
    Tok nameTok = cur(&((*c)));
    advance(&((*c)));
    {
    Kind _m32 = curKind(&((*c)));
    if (_m32.tag == 19) {
    advance(&((*c)));
    }
    else {
    }
    }
    long long lo = parseExpr(&((*c)));
    long long isRange = 0;
    long long inclusive = 0;
    long long hi = 0;
    {
    Kind _m33 = curKind(&((*c)));
    if (_m33.tag == 56) {
    advance(&((*c)));
    isRange = 1;
    hi = parseExpr(&((*c)));
    }
    else if (_m33.tag == 57) {
    advance(&((*c)));
    isRange = 1;
    inclusive = 1;
    hi = parseExpr(&((*c)));
    }
    else {
    }
    }
    skipNewlines(&((*c)));
    long long body = parseBlock(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 7, .data.For = {.varStart = nameTok.start, .varLen = nameTok.len, .isRange = isRange, .inclusive = inclusive, .iter = lo, .rangeHi = hi, .body = body}});
}
long long parseExprOrAssign(Comp* c) {
    long long lhs = parseExpr(&((*c)));
    Kind k = curKind(&((*c)));
    if (isAssignOp(k)) {
    long long op = kindCode(k);
    advance(&((*c)));
    long long rhs = parseExpr(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 1, .data.Assign = {.op = op, .target = lhs, .value = rhs}});
    }
    return pushStmt(&((*c)), (Stmt){.tag = 3, .data.ExprStmt = {.expr = lhs}});
}
long long parseMatch(Comp* c) {
    advance(&((*c)));
    long long scrut = parseExpr(&((*c)));
    skipNewlines(&((*c)));
    {
    Kind _m34 = curKind(&((*c)));
    if (_m34.tag == 28) {
    advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_MatchArm arms = PlewArray_MatchArm_new();
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m35 = k;
    if (_m35.tag == 29) {
    advance(&((*c)));
    break;
    }
    else if (_m35.tag == 0) {
    break;
    }
    else {
    Tok firstTok = cur(&((*c)));
    long long isWildcard = 0;
    long long enumStart = 0;
    long long enumLen = 0;
    long long variantStart = 0;
    long long variantLen = 0;
    PlewArray_Bind binds = PlewArray_Bind_new();
    if (rangeEquals((*c).bytes, firstTok.start, firstTok.len, (PlewString){"_", 1})) {
    isWildcard = 1;
    advance(&((*c)));
    }
    else {
    enumStart = firstTok.start;
    enumLen = firstTok.len;
    advance(&((*c)));
    {
    Kind _m36 = curKind(&((*c)));
    if (_m36.tag == 32) {
    advance(&((*c)));
    }
    else {
    }
    }
    Tok vTok = cur(&((*c)));
    variantStart = vTok.start;
    variantLen = vTok.len;
    advance(&((*c)));
    {
    Kind _m37 = curKind(&((*c)));
    if (_m37.tag == 28) {
    advance(&((*c)));
    while (1) {
    skipNewlines(&((*c)));
    {
    Kind _m38 = curKind(&((*c)));
    if (_m38.tag == 29) {
    advance(&((*c)));
    break;
    }
    else if (_m38.tag == 0) {
    break;
    }
    else if (_m38.tag == 17) {
    advance(&((*c)));
    Tok bTok = cur(&((*c)));
    advance(&((*c)));
    PlewArray_Bind_push(&(binds), (Bind){.nameStart = bTok.start, .nameLen = bTok.len});
    {
    Kind _m39 = curKind(&((*c)));
    if (_m39.tag == 30) {
    advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    advance(&((*c)));
    }
    }
    }
    }
    else {
    }
    }
    }
    {
    Kind _m40 = curKind(&((*c)));
    if (_m40.tag == 49) {
    advance(&((*c)));
    }
    else {
    }
    }
    skipNewlines(&((*c)));
    long long body = parseBlock(&((*c)));
    PlewArray_MatchArm_push(&(arms), (MatchArm){.isWildcard = isWildcard, .enumStart = enumStart, .enumLen = enumLen, .variantStart = variantStart, .variantLen = variantLen, .binds = binds, .body = body});
    }
    }
    }
    return pushStmt(&((*c)), (Stmt){.tag = 8, .data.Match = {.scrut = scrut, .arms = arms}});
}
long long parseStmt(Comp* c) {
    Kind k = curKind(&((*c)));
    {
    Kind _m41 = k;
    if (_m41.tag == 17) {
    return parseLet(&((*c)), 0);
    }
    else if (_m41.tag == 18) {
    advance(&((*c)));
    return parseLet(&((*c)), 1);
    }
    else if (_m41.tag == 9) {
    return parseIf(&((*c)));
    }
    else if (_m41.tag == 11) {
    return parseWhile(&((*c)));
    }
    else if (_m41.tag == 12) {
    return parseFor(&((*c)));
    }
    else if (_m41.tag == 8) {
    return parseMatch(&((*c)));
    }
    else if (_m41.tag == 13) {
    advance(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 9});
    }
    else if (_m41.tag == 14) {
    advance(&((*c)));
    return pushStmt(&((*c)), (Stmt){.tag = 10});
    }
    else if (_m41.tag == 15) {
    return parseReturn(&((*c)));
    }
    else if (_m41.tag == 4) {
    if (identIs(&((*c)), (PlewString){"print", 5})) {
    {
    Kind _m42 = peekKind(&((*c)), 1);
    if (_m42.tag == 24) {
    return parsePrint(&((*c)));
    }
    else {
    return parseExprOrAssign(&((*c)));
    }
    }
    }
    return parseExprOrAssign(&((*c)));
    }
    else {
    return parseExprOrAssign(&((*c)));
    }
    }
}
long long parseBlock(Comp* c) {
    {
    Kind _m43 = curKind(&((*c)));
    if (_m43.tag == 28) {
    advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_U64 stmts = PlewArray_U64_new();
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m44 = k;
    if (_m44.tag == 29) {
    advance(&((*c)));
    break;
    }
    else if (_m44.tag == 0) {
    break;
    }
    else {
    long long s = parseStmt(&((*c)));
    PlewArray_U64_push(&(stmts), s);
    }
    }
    }
    long long id = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = stmts});
    return id;
}
void parseFunc(Comp* c) {
    advance(&((*c)));
    Tok nameTok = cur(&((*c)));
    advance(&((*c)));
    PlewArray_Param params = PlewArray_Param_new();
    {
    Kind _m45 = curKind(&((*c)));
    if (_m45.tag == 24) {
    advance(&((*c)));
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m46 = k;
    if (_m46.tag == 25) {
    advance(&((*c)));
    break;
    }
    else if (_m46.tag == 0) {
    break;
    }
    else {
    Tok pTok = cur(&((*c)));
    advance(&((*c)));
    long long pTyStart = 0;
    long long pTyLen = 0;
    long long pTyIsArray = 0;
    long long pIsInout = 0;
    {
    Kind _m47 = curKind(&((*c)));
    if (_m47.tag == 31) {
    advance(&((*c)));
    {
    Kind _m48 = curKind(&((*c)));
    if (_m48.tag == 21) {
    advance(&((*c)));
    pIsInout = 1;
    }
    else {
    }
    }
    PType pty = parseTypeTok(&((*c)));
    pTyStart = pty.start;
    pTyLen = pty.len;
    pTyIsArray = pty.isArray;
    recordArrayElem(&((*c)), pty);
    }
    else {
    }
    }
    PlewArray_Param_push(&(params), (Param){.nameStart = pTok.start, .nameLen = pTok.len, .tyStart = pTyStart, .tyLen = pTyLen, .tyIsArray = pTyIsArray, .isInout = pIsInout});
    {
    Kind _m49 = curKind(&((*c)));
    if (_m49.tag == 30) {
    advance(&((*c)));
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
    long long hasRet = 0;
    long long retStart = 0;
    long long retLen = 0;
    long long retIsArray = 0;
    {
    Kind _m50 = curKind(&((*c)));
    if (_m50.tag == 48) {
    advance(&((*c)));
    hasRet = 1;
    PType rty = parseTypeTok(&((*c)));
    retStart = rty.start;
    retLen = rty.len;
    retIsArray = rty.isArray;
    recordArrayElem(&((*c)), rty);
    }
    else {
    }
    }
    skipNewlines(&((*c)));
    long long body = parseBlock(&((*c)));
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .params = params, .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .body = body});
}
void parseStruct(Comp* c) {
    advance(&((*c)));
    Tok nameTok = cur(&((*c)));
    advance(&((*c)));
    {
    Kind _m51 = curKind(&((*c)));
    if (_m51.tag == 28) {
    advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_FieldDef fields = PlewArray_FieldDef_new();
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m52 = k;
    if (_m52.tag == 29) {
    advance(&((*c)));
    break;
    }
    else if (_m52.tag == 0) {
    break;
    }
    else if (_m52.tag == 17) {
    advance(&((*c)));
    }
    else if (_m52.tag == 18) {
    advance(&((*c)));
    }
    else if (_m52.tag == 4) {
    Tok fTok = cur(&((*c)));
    advance(&((*c)));
    long long tyStart = 0;
    long long tyLen = 0;
    long long tyIsArray = 0;
    {
    Kind _m53 = curKind(&((*c)));
    if (_m53.tag == 31) {
    advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    recordArrayElem(&((*c)), ty);
    }
    else {
    }
    }
    PlewArray_FieldDef_push(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray});
    }
    else {
    advance(&((*c)));
    }
    }
    }
    PlewArray_StructDef_push(&((*c).structs), (StructDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .fields = fields});
}
void parseEnum(Comp* c) {
    advance(&((*c)));
    Tok nameTok = cur(&((*c)));
    advance(&((*c)));
    {
    Kind _m54 = curKind(&((*c)));
    if (_m54.tag == 28) {
    advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_Variant variants = PlewArray_Variant_new();
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m55 = k;
    if (_m55.tag == 29) {
    advance(&((*c)));
    break;
    }
    else if (_m55.tag == 0) {
    break;
    }
    else if (_m55.tag == 4) {
    Tok vTok = cur(&((*c)));
    advance(&((*c)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_new();
    {
    Kind _m56 = curKind(&((*c)));
    if (_m56.tag == 28) {
    advance(&((*c)));
    while (1) {
    skipNewlines(&((*c)));
    {
    Kind _m57 = curKind(&((*c)));
    if (_m57.tag == 29) {
    advance(&((*c)));
    break;
    }
    else if (_m57.tag == 0) {
    break;
    }
    else if (_m57.tag == 4) {
    Tok fTok = cur(&((*c)));
    advance(&((*c)));
    long long tyStart = 0;
    long long tyLen = 0;
    long long tyIsArray = 0;
    {
    Kind _m58 = curKind(&((*c)));
    if (_m58.tag == 31) {
    advance(&((*c)));
    PType ty = parseTypeTok(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    recordArrayElem(&((*c)), ty);
    }
    else {
    }
    }
    PlewArray_FieldDef_push(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray});
    {
    Kind _m59 = curKind(&((*c)));
    if (_m59.tag == 30) {
    advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    advance(&((*c)));
    }
    }
    }
    }
    else {
    }
    }
    PlewArray_Variant_push(&(variants), (Variant){.nameStart = vTok.start, .nameLen = vTok.len, .fields = fields});
    }
    else {
    advance(&((*c)));
    }
    }
    }
    PlewArray_EnumDef_push(&((*c).enums), (EnumDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .variants = variants});
}
void markImport(Comp* c, long long segStart, long long segLen, long long nameStart, long long nameLen) {
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
    }
    if (rangeEquals((*c).bytes, segStart, segLen, (PlewString){"Process", 7})) {
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argCount", 8})) {
    (*c).impArgCount = 1;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argAt", 5})) {
    (*c).impArgAt = 1;
    }
    }
}
void parseImport(Comp* c) {
    advance(&((*c)));
    long long segStart = 0;
    long long segLen = 0;
    while (1) {
    Kind k = curKind(&((*c)));
    {
    Kind _m60 = k;
    if (_m60.tag == 1) {
    break;
    }
    else if (_m60.tag == 0) {
    break;
    }
    else if (_m60.tag == 28) {
    break;
    }
    else if (_m60.tag == 4) {
    if (identIs(&((*c)), (PlewString){"with", 4})) {
    advance(&((*c)));
    break;
    }
    Tok t = cur(&((*c)));
    segStart = t.start;
    segLen = t.len;
    advance(&((*c)));
    }
    else {
    advance(&((*c)));
    }
    }
    }
    {
    Kind _m61 = curKind(&((*c)));
    if (_m61.tag == 28) {
    advance(&((*c)));
    while (1) {
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m62 = k;
    if (_m62.tag == 29) {
    advance(&((*c)));
    break;
    }
    else if (_m62.tag == 0) {
    break;
    }
    else if (_m62.tag == 30) {
    advance(&((*c)));
    }
    else if (_m62.tag == 4) {
    Tok t = cur(&((*c)));
    markImport(&((*c)), segStart, segLen, t.start, t.len);
    advance(&((*c)));
    }
    else {
    advance(&((*c)));
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
    skipNewlines(&((*c)));
    Kind k = curKind(&((*c)));
    {
    Kind _m63 = k;
    if (_m63.tag == 5) {
    parseFunc(&((*c)));
    }
    else if (_m63.tag == 6) {
    parseStruct(&((*c)));
    }
    else if (_m63.tag == 7) {
    parseEnum(&((*c)));
    }
    else if (_m63.tag == 4) {
    if (identIs(&((*c)), (PlewString){"import", 6})) {
    parseImport(&((*c)));
    }
    else {
    advance(&((*c)));
    }
    }
    else if (_m63.tag == 0) {
    break;
    }
    else {
    advance(&((*c)));
    }
    }
    }
}
PlewString digitStr(long long d) {
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
void writeInt(long long n) {
    if (n < 0) {
    plew_write((PlewString){"-", 1});
    writeInt((0 - n));
    return;
    }
    if (n >= 10) {
    writeInt((n / 10));
    }
    plew_write(digitStr((n % 10)));
}
void writeSpan(Comp* c, long long start, long long len) {
    long long j = 0;
    while (j < len) {
    putchar((int)(PlewArray_U8_get((*c).bytes, (long long)((start + j)))));
    j += 1;
    }
}
long long isPrimType(Comp* c, long long start, long long len) {
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
void genCElem(Comp* c, long long start, long long len) {
    if (len == 0) {
    plew_write((PlewString){"long long", 9});
    return;
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"U8", 2})) {
    plew_write((PlewString){"unsigned char", 13});
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
void genCTypeRef(Comp* c, long long start, long long len, long long isArray) {
    if (isArray) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), start, len);
    return;
    }
    genCElem(&((*c)), start, len);
}
void genCType(Comp* c, long long start, long long len) {
    genCElem(&((*c)), start, len);
}
long long spansEqual(Comp* c, long long aStart, long long aLen, long long bStart, long long bLen) {
    if (aLen != bLen) {
    return 0;
    }
    long long j = 0;
    while (j < aLen) {
    if (PlewArray_U8_get((*c).bytes, (long long)((aStart + j))) != PlewArray_U8_get((*c).bytes, (long long)((bStart + j)))) {
    return 0;
    }
    j += 1;
    }
    return 1;
}
long long findFunc(Comp* c, long long nameStart, long long nameLen) {
    long long i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(i));
    if (spansEqual(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    return ((long long)(i));
    }
    i += 1;
    }
    return (0 - 1);
}
long long callLabelsOk(Comp* c, long long nameStart, long long nameLen, PlewArray_Arg args) {
    long long fi = findFunc(&((*c)), nameStart, nameLen);
    if (fi < 0) {
    return 1;
    }
    Func f = PlewArray_Func_get((*c).funcs, (long long)(((long long)(fi))));
    if ((long long)((f.params).len) != (long long)((args).len)) {
    return 0;
    }
    long long i = 0;
    while (i < (long long)((args).len)) {
    Arg a = PlewArray_Arg_get(args, (long long)(i));
    if (a.hasLabel) {
    Param p = PlewArray_Param_get(f.params, (long long)(i));
    if (spansEqual(&((*c)), a.labelStart, a.labelLen, p.nameStart, p.nameLen)) {
    }
    else {
    return 0;
    }
    }
    else {
    return 0;
    }
    i += 1;
    }
    return 1;
}
long long armCovers(Comp* c, PlewArray_MatchArm arms, long long variantStart, long long variantLen) {
    long long i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = PlewArray_MatchArm_get(arms, (long long)(i));
    if (a.isWildcard) {
    return 1;
    }
    if (spansEqual(&((*c)), a.variantStart, a.variantLen, variantStart, variantLen)) {
    return 1;
    }
    i += 1;
    }
    return 0;
}
long long matchExhaustive(Comp* c, PlewArray_MatchArm arms) {
    long long enumStart = 0;
    long long enumLen = 0;
    long long i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = PlewArray_MatchArm_get(arms, (long long)(i));
    if (a.isWildcard) {
    return 1;
    }
    if (enumLen == 0) {
    enumStart = a.enumStart;
    enumLen = a.enumLen;
    }
    i += 1;
    }
    if (enumLen == 0) {
    return 1;
    }
    long long ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = e.variants;
    long long vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (armCovers(&((*c)), arms, v.nameStart, v.nameLen)) {
    }
    else {
    return 0;
    }
    vi += 1;
    }
    return 1;
    }
    ei += 1;
    }
    return 1;
}
long long variantIndex(Comp* c, long long enumStart, long long enumLen, long long variantStart, long long variantLen) {
    long long ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = e.variants;
    long long vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    return ((long long)(vi));
    }
    vi += 1;
    }
    }
    ei += 1;
    }
    return 0;
}
TypeInfo scalarInfo(void) {
    return (TypeInfo){.kind = 0, .nameStart = 0, .nameLen = 0};
}
TypeInfo typeInfoOfName(Comp* c, long long start, long long len, long long isArray) {
    if (isArray) {
    return (TypeInfo){.kind = 3, .nameStart = start, .nameLen = len};
    }
    if (len == 0) {
    return scalarInfo();
    }
    if (rangeEquals((*c).bytes, start, len, (PlewString){"String", 6})) {
    return (TypeInfo){.kind = 1, .nameStart = start, .nameLen = len};
    }
    if (isPrimType(&((*c)), start, len)) {
    return scalarInfo();
    }
    return (TypeInfo){.kind = 2, .nameStart = start, .nameLen = len};
}
void addLocal(Comp* c, long long nameStart, long long nameLen, long long tyStart, long long tyLen, long long isArray, long long isInout) {
    PlewArray_Local_push(&((*c).locals), (Local){.nameStart = nameStart, .nameLen = nameLen, .tyStart = tyStart, .tyLen = tyLen, .isArray = isArray, .isInout = isInout});
}
long long isInoutLocal(Comp* c, long long start, long long len) {
    long long i = (long long)(((*c).locals).len);
    while (i > 0) {
    i -= 1;
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    return lo.isInout;
    }
    }
    return 0;
}
TypeInfo fieldType(Comp* c, long long structStart, long long structLen, long long fieldStart, long long fieldLen) {
    long long si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    if (spansEqual(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    PlewArray_FieldDef fs = s.fields;
    long long fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    return typeInfoOfName(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    }
    fi += 1;
    }
    }
    si += 1;
    }
    return scalarInfo();
}
TypeInfo exprType(Comp* c, long long id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m64 = e;
    if (_m64.tag == 0) {
        long long value = _m64.data.Int.value;
        (void)value;
    return scalarInfo();
    }
    else if (_m64.tag == 7) {
        long long start = _m64.data.Str.start;
        (void)start;
        long long len = _m64.data.Str.len;
        (void)len;
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0};
    }
    else if (_m64.tag == 1) {
        long long start = _m64.data.Ident.start;
        (void)start;
        long long len = _m64.data.Ident.len;
        (void)len;
    long long i = (long long)(((*c).locals).len);
    while (i > 0) {
    i -= 1;
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    return typeInfoOfName(&((*c)), lo.tyStart, lo.tyLen, lo.isArray);
    }
    }
    return scalarInfo();
    }
    else if (_m64.tag == 2) {
        long long op = _m64.data.Unary.op;
        (void)op;
        long long operand = _m64.data.Unary.operand;
        (void)operand;
    return scalarInfo();
    }
    else if (_m64.tag == 3) {
        long long op = _m64.data.Binary.op;
        (void)op;
        long long lhs = _m64.data.Binary.lhs;
        (void)lhs;
        long long rhs = _m64.data.Binary.rhs;
        (void)rhs;
    return scalarInfo();
    }
    else if (_m64.tag == 4) {
        long long nameStart = _m64.data.Call.nameStart;
        (void)nameStart;
        long long nameLen = _m64.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m64.data.Call.args;
        (void)args;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readStdin", 9})) {
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0};
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readFile", 8})) {
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0};
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argAt", 5})) {
    return (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0};
    }
    long long fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    if (f.hasRet) {
    return typeInfoOfName(&((*c)), f.retStart, f.retLen, f.retIsArray);
    }
    return scalarInfo();
    }
    fi += 1;
    }
    return scalarInfo();
    }
    else if (_m64.tag == 5) {
        long long base = _m64.data.Field.base;
        (void)base;
        long long nameStart = _m64.data.Field.nameStart;
        (void)nameStart;
        long long nameLen = _m64.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 2) {
    return fieldType(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    }
    return scalarInfo();
    }
    else if (_m64.tag == 6) {
        long long typeStart = _m64.data.Make.typeStart;
        (void)typeStart;
        long long typeLen = _m64.data.Make.typeLen;
        (void)typeLen;
        long long variantStart = _m64.data.Make.variantStart;
        (void)variantStart;
        long long variantLen = _m64.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m64.data.Make.isEnum;
        (void)isEnum;
        PlewArray_MakeField fields = _m64.data.Make.fields;
        (void)fields;
    return (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen};
    }
    else if (_m64.tag == 8) {
        PlewArray_U64 elems = _m64.data.Array.elems;
        (void)elems;
    return scalarInfo();
    }
    else if (_m64.tag == 9) {
        long long base = _m64.data.Index.base;
        (void)base;
        long long index = _m64.data.Index.index;
        (void)index;
    TypeInfo bt = exprType(&((*c)), base);
    if (bt.kind == 3) {
    return typeInfoOfName(&((*c)), bt.nameStart, bt.nameLen, 0);
    }
    return scalarInfo();
    }
    else if (_m64.tag == 10) {
        long long recv = _m64.data.Method.recv;
        (void)recv;
        long long nameStart = _m64.data.Method.nameStart;
        (void)nameStart;
        long long nameLen = _m64.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m64.data.Method.args;
        (void)args;
    return scalarInfo();
    }
    else if (_m64.tag == 11) {
        long long operand = _m64.data.Cast.operand;
        (void)operand;
        long long tyStart = _m64.data.Cast.tyStart;
        (void)tyStart;
        long long tyLen = _m64.data.Cast.tyLen;
        (void)tyLen;
    return typeInfoOfName(&((*c)), tyStart, tyLen, 0);
    }
    else { __builtin_unreachable(); }
    }
    return scalarInfo();
}
void addBindLocal(Comp* c, long long enumStart, long long enumLen, long long variantStart, long long variantLen, long long bindStart, long long bindLen) {
    long long ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = e.variants;
    long long vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = v.fields;
    long long fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, bindStart, bindLen)) {
    addLocal(&((*c)), bindStart, bindLen, f.tyStart, f.tyLen, f.tyIsArray, 0);
    return;
    }
    fi += 1;
    }
    }
    vi += 1;
    }
    }
    ei += 1;
    }
}
void genBindType(Comp* c, long long enumStart, long long enumLen, long long variantStart, long long variantLen, long long bindStart, long long bindLen) {
    long long ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = e.variants;
    long long vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if (spansEqual(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = v.fields;
    long long fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual(&((*c)), f.nameStart, f.nameLen, bindStart, bindLen)) {
    genCTypeRef(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    return;
    }
    fi += 1;
    }
    }
    vi += 1;
    }
    }
    ei += 1;
    }
    plew_write((PlewString){"long long", 9});
}
PlewString binOpStr(long long op) {
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
    return (PlewString){" ? ", 3};
}
PlewString unaryOpStr(long long op) {
    if (op == 57) {
    return (PlewString){"-", 1};
    }
    return (PlewString){"!", 1};
}
long long strDecodedLen(Comp* c, long long start, long long len) {
    long long n = 0;
    long long j = (start + 1);
    long long end = ((start + len) - 1);
    while (j < end) {
    if (PlewArray_U8_get((*c).bytes, (long long)(j)) == 92) {
    j += 2;
    }
    else {
    j += 1;
    }
    n += 1;
    }
    return n;
}
PlewString assignOpStr(long long op) {
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
    return (PlewString){" %= ", 4};
}
PlewString assignToBinStr(long long op) {
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
    return (PlewString){" % ", 3};
}
void genExpr(Comp* c, long long id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m65 = e;
    if (_m65.tag == 0) {
        long long value = _m65.data.Int.value;
        (void)value;
    writeInt(value);
    }
    else if (_m65.tag == 1) {
        long long start = _m65.data.Ident.start;
        (void)start;
        long long len = _m65.data.Ident.len;
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
    else if (_m65.tag == 2) {
        long long op = _m65.data.Unary.op;
        (void)op;
        long long operand = _m65.data.Unary.operand;
        (void)operand;
    plew_write(unaryOpStr(op));
    plew_write((PlewString){"(", 1});
    genExpr(&((*c)), operand);
    plew_write((PlewString){")", 1});
    }
    else if (_m65.tag == 3) {
        long long op = _m65.data.Binary.op;
        (void)op;
        long long lhs = _m65.data.Binary.lhs;
        (void)lhs;
        long long rhs = _m65.data.Binary.rhs;
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
    plew_write((PlewString){"__plew_compare_requires_Eq_or_Ord", 33});
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
    else if (_m65.tag == 4) {
        long long nameStart = _m65.data.Call.nameStart;
        (void)nameStart;
        long long nameLen = _m65.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m65.data.Call.args;
        (void)args;
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"write", 5})) {
    if ((*c).impWrite) {
    plew_write((PlewString){"plew_write(", 11});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    plew_write((PlewString){"__plew_write_requires_import_Std_Io", 35});
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
    plew_write((PlewString){"__plew_writeByte_requires_import_Std_Io", 39});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"readStdin", 9})) {
    if ((*c).impReadStdin) {
    plew_write((PlewString){"plew_read_stdin()", 17});
    }
    else {
    plew_write((PlewString){"__plew_readStdin_requires_import_Std_Io", 39});
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
    plew_write((PlewString){"__plew_readFile_requires_import_Std_Io", 38});
    }
    return;
    }
    if (rangeEquals((*c).bytes, nameStart, nameLen, (PlewString){"argCount", 8})) {
    if ((*c).impArgCount) {
    plew_write((PlewString){"plew_arg_count()", 16});
    }
    else {
    plew_write((PlewString){"__plew_argCount_requires_import_Std_Process", 43});
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
    plew_write((PlewString){"__plew_argAt_requires_import_Std_Process", 40});
    }
    return;
    }
    if (callLabelsOk(&((*c)), nameStart, nameLen, args)) {
    }
    else {
    plew_write((PlewString){"__plew_call_label_mismatch", 26});
    return;
    }
    writeSpan(&((*c)), nameStart, nameLen);
    plew_write((PlewString){"(", 1});
    long long i = 0;
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
    i += 1;
    }
    plew_write((PlewString){")", 1});
    }
    else if (_m65.tag == 5) {
        long long base = _m65.data.Field.base;
        (void)base;
        long long nameStart = _m65.data.Field.nameStart;
        (void)nameStart;
        long long nameLen = _m65.data.Field.nameLen;
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
    else if (_m65.tag == 7) {
        long long start = _m65.data.Str.start;
        (void)start;
        long long len = _m65.data.Str.len;
        (void)len;
    plew_write((PlewString){"(PlewString){\"", 14});
    writeSpan(&((*c)), (start + 1), (len - 2));
    plew_write((PlewString){"\", ", 3});
    writeInt(strDecodedLen(&((*c)), start, len));
    plew_write((PlewString){"}", 1});
    }
    else if (_m65.tag == 9) {
        long long base = _m65.data.Index.base;
        (void)base;
        long long index = _m65.data.Index.index;
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
    else if (_m65.tag == 10) {
        long long recv = _m65.data.Method.recv;
        (void)recv;
        long long nameStart = _m65.data.Method.nameStart;
        (void)nameStart;
        long long nameLen = _m65.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m65.data.Method.args;
        (void)args;
    TypeInfo bt = exprType(&((*c)), recv);
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_push(&(", 8});
    genExpr(&((*c)), recv);
    plew_write((PlewString){"), ", 3});
    genExpr(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else if (_m65.tag == 8) {
        PlewArray_U64 elems = _m65.data.Array.elems;
        (void)elems;
    plew_write((PlewString){"0", 1});
    }
    else if (_m65.tag == 11) {
        long long operand = _m65.data.Cast.operand;
        (void)operand;
        long long tyStart = _m65.data.Cast.tyStart;
        (void)tyStart;
        long long tyLen = _m65.data.Cast.tyLen;
        (void)tyLen;
    plew_write((PlewString){"((", 2});
    genCElem(&((*c)), tyStart, tyLen);
    plew_write((PlewString){")(", 2});
    genExpr(&((*c)), operand);
    plew_write((PlewString){"))", 2});
    }
    else if (_m65.tag == 6) {
        long long typeStart = _m65.data.Make.typeStart;
        (void)typeStart;
        long long typeLen = _m65.data.Make.typeLen;
        (void)typeLen;
        long long variantStart = _m65.data.Make.variantStart;
        (void)variantStart;
        long long variantLen = _m65.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m65.data.Make.isEnum;
        (void)isEnum;
        PlewArray_MakeField fields = _m65.data.Make.fields;
        (void)fields;
    if (isEnum) {
    plew_write((PlewString){"(", 1});
    writeSpan(&((*c)), typeStart, typeLen);
    plew_write((PlewString){"){.tag = ", 9});
    writeInt(variantIndex(&((*c)), typeStart, typeLen, variantStart, variantLen));
    if ((long long)((fields).len) > 0) {
    plew_write((PlewString){", .data.", 8});
    writeSpan(&((*c)), variantStart, variantLen);
    plew_write((PlewString){" = {", 4});
    long long i = 0;
    while (i < (long long)((fields).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), mf.nameStart, mf.nameLen);
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), mf.value);
    i += 1;
    }
    plew_write((PlewString){"}", 1});
    }
    plew_write((PlewString){"}", 1});
    }
    else {
    plew_write((PlewString){"(", 1});
    genCType(&((*c)), typeStart, typeLen);
    plew_write((PlewString){"){", 2});
    long long i = 0;
    while (i < (long long)((fields).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), mf.nameStart, mf.nameLen);
    plew_write((PlewString){" = ", 3});
    TypeInfo ft = fieldType(&((*c)), typeStart, typeLen, mf.nameStart, mf.nameLen);
    if (ft.kind == 3) {
    genArrayLiteral(&((*c)), mf.value, ft.nameStart, ft.nameLen);
    }
    else {
    genExpr(&((*c)), mf.value);
    }
    i += 1;
    }
    plew_write((PlewString){"}", 1});
    }
    }
    else { __builtin_unreachable(); }
    }
}
void genArrayLiteral(Comp* c, long long exprId, long long elemStart, long long elemLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(exprId));
    {
    Expr _m66 = e;
    if (_m66.tag == 8) {
        PlewArray_U64 elems = _m66.data.Array.elems;
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
    long long i = 0;
    while (i < (long long)((elems).len)) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(&__a, ", 12});
    genExpr(&((*c)), PlewArray_U64_get(elems, (long long)(i)));
    plew_write((PlewString){"); ", 3});
    i += 1;
    }
    plew_write((PlewString){"__a; })", 7});
    }
    }
    else {
    genExpr(&((*c)), exprId);
    }
    }
}
long long isStringEq(Comp* c, long long op, long long lhs) {
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
long long isEnumName(Comp* c, long long start, long long len) {
    long long ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, start, len)) {
    return 1;
    }
    ei += 1;
    }
    return 0;
}
long long isAllNullary(Comp* c, long long start, long long len) {
    long long ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    if (spansEqual(&((*c)), e.nameStart, e.nameLen, start, len)) {
    PlewArray_Variant vars = e.variants;
    long long vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    if ((long long)((v.fields).len) > 0) {
    return 0;
    }
    vi += 1;
    }
    return 1;
    }
    ei += 1;
    }
    return 0;
}
long long isEnumEq(Comp* c, long long op, long long lhs) {
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
long long compareNeedsTrait(Comp* c, long long op, long long lhs) {
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
void emitEnumOperand(Comp* c, long long id, long long enStart, long long enLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m67 = e;
    if (_m67.tag == 6) {
        long long typeStart = _m67.data.Make.typeStart;
        (void)typeStart;
        long long typeLen = _m67.data.Make.typeLen;
        (void)typeLen;
        long long variantStart = _m67.data.Make.variantStart;
        (void)variantStart;
        long long variantLen = _m67.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m67.data.Make.isEnum;
        (void)isEnum;
        PlewArray_MakeField fields = _m67.data.Make.fields;
        (void)fields;
    if (isEnum) {
    writeInt(variantIndex(&((*c)), enStart, enLen, variantStart, variantLen));
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
void emitEnumTagCmp(Comp* c, long long lhs, long long rhs, long long op, long long outer) {
    TypeInfo lt = exprType(&((*c)), lhs);
    long long enStart = 0;
    long long enLen = 0;
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
    plew_write((PlewString){"__plew_enum_eq_requires_Eq_derive", 33});
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
void genCond(Comp* c, long long id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m68 = e;
    if (_m68.tag == 3) {
        long long op = _m68.data.Binary.op;
        (void)op;
        long long lhs = _m68.data.Binary.lhs;
        (void)lhs;
        long long rhs = _m68.data.Binary.rhs;
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
    plew_write((PlewString){"__plew_compare_requires_Eq_or_Ord", 33});
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
void genStmt(Comp* c, long long id) {
    Stmt s = PlewArray_Stmt_get((*c).stmts, (long long)(id));
    {
    Stmt _m69 = s;
    if (_m69.tag == 0) {
        long long mutable = _m69.data.Let.mutable;
        (void)mutable;
        long long nameStart = _m69.data.Let.nameStart;
        (void)nameStart;
        long long nameLen = _m69.data.Let.nameLen;
        (void)nameLen;
        long long tyStart = _m69.data.Let.tyStart;
        (void)tyStart;
        long long tyLen = _m69.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m69.data.Let.tyIsArray;
        (void)tyIsArray;
        long long init = _m69.data.Let.init;
        (void)init;
    plew_write((PlewString){"    ", 4});
    genCTypeRef(&((*c)), tyStart, tyLen, tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), nameStart, nameLen);
    plew_write((PlewString){" = ", 3});
    if (tyIsArray) {
    genArrayLiteral(&((*c)), init, tyStart, tyLen);
    }
    else {
    genExpr(&((*c)), init);
    }
    plew_write((PlewString){";\n", 2});
    addLocal(&((*c)), nameStart, nameLen, tyStart, tyLen, tyIsArray, 0);
    }
    else if (_m69.tag == 1) {
        long long op = _m69.data.Assign.op;
        (void)op;
        long long target = _m69.data.Assign.target;
        (void)target;
        long long value = _m69.data.Assign.value;
        (void)value;
    Expr te = PlewArray_Expr_get((*c).exprs, (long long)(target));
    {
    Expr _m70 = te;
    if (_m70.tag == 9) {
        long long base = _m70.data.Index.base;
        (void)base;
        long long index = _m70.data.Index.index;
        (void)index;
    TypeInfo bt = exprType(&((*c)), base);
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
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_get(", 5});
    genExpr(&((*c)), base);
    plew_write((PlewString){", (long long)(", 14});
    genExpr(&((*c)), index);
    plew_write((PlewString){"))", 2});
    plew_write(assignToBinStr(op));
    genExpr(&((*c)), value);
    }
    plew_write((PlewString){");\n", 3});
    }
    else {
    plew_write((PlewString){"    ", 4});
    genExpr(&((*c)), target);
    plew_write(assignOpStr(op));
    TypeInfo tt = exprType(&((*c)), target);
    if (tt.kind == 3) {
    genArrayLiteral(&((*c)), value, tt.nameStart, tt.nameLen);
    }
    else {
    genExpr(&((*c)), value);
    }
    plew_write((PlewString){";\n", 2});
    }
    }
    }
    else if (_m69.tag == 2) {
        long long expr = _m69.data.Print.expr;
        (void)expr;
    if ((*c).impPrint) {
    plew_write((PlewString){"    printf(\"%lld\\n\", (long long)(", 33});
    genExpr(&((*c)), expr);
    plew_write((PlewString){"));\n", 4});
    }
    else {
    plew_write((PlewString){"    __plew_print_requires_import_Std_Io;\n", 41});
    }
    }
    else if (_m69.tag == 3) {
        long long expr = _m69.data.ExprStmt.expr;
        (void)expr;
    plew_write((PlewString){"    ", 4});
    genExpr(&((*c)), expr);
    plew_write((PlewString){";\n", 2});
    }
    else if (_m69.tag == 4) {
        long long value = _m69.data.Return.value;
        (void)value;
        long long hasValue = _m69.data.Return.hasValue;
        (void)hasValue;
    if ((*c).curIsMain) {
    plew_write((PlewString){"    return 0;\n", 14});
    }
    else {
    if ((*c).curRetVoid) {
    plew_write((PlewString){"    return;\n", 12});
    }
    else {
    plew_write((PlewString){"    return ", 11});
    if (hasValue) {
    genExpr(&((*c)), value);
    }
    else {
    plew_write((PlewString){"0", 1});
    }
    plew_write((PlewString){";\n", 2});
    }
    }
    }
    else if (_m69.tag == 5) {
        long long cond = _m69.data.If.cond;
        (void)cond;
        long long thenBlk = _m69.data.If.thenBlk;
        (void)thenBlk;
        long long elseBlk = _m69.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m69.data.If.hasElse;
        (void)hasElse;
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
    else if (_m69.tag == 6) {
        long long cond = _m69.data.While.cond;
        (void)cond;
        long long body = _m69.data.While.body;
        (void)body;
    plew_write((PlewString){"    while (", 11});
    genCond(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n", 6});
    }
    else if (_m69.tag == 7) {
        long long varStart = _m69.data.For.varStart;
        (void)varStart;
        long long varLen = _m69.data.For.varLen;
        (void)varLen;
        long long isRange = _m69.data.For.isRange;
        (void)isRange;
        long long inclusive = _m69.data.For.inclusive;
        (void)inclusive;
        long long iter = _m69.data.For.iter;
        (void)iter;
        long long rangeHi = _m69.data.For.rangeHi;
        (void)rangeHi;
        long long body = _m69.data.For.body;
        (void)body;
    long long t = (*c).tmp;
    (*c).tmp = ((*c).tmp + 1);
    if (isRange) {
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    long long __fe", 18});
    writeInt(((long long)(t)));
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
    writeInt(((long long)(t)));
    plew_write((PlewString){"; ", 2});
    writeSpan(&((*c)), varStart, varLen);
    plew_write((PlewString){"++) {\n", 6});
    addLocal(&((*c)), varStart, varLen, 0, 0, 0, 0);
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    else {
    TypeInfo et = exprType(&((*c)), iter);
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    ", 4});
    wPA(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){" __fa", 5});
    writeInt(((long long)(t)));
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), iter);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"    for (long long __fi", 23});
    writeInt(((long long)(t)));
    plew_write((PlewString){" = 0; __fi", 10});
    writeInt(((long long)(t)));
    plew_write((PlewString){" < __fa", 7});
    writeInt(((long long)(t)));
    plew_write((PlewString){".len; __fi", 10});
    writeInt(((long long)(t)));
    plew_write((PlewString){"++) {\n", 6});
    plew_write((PlewString){"        ", 8});
    genCElem(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), varStart, varLen);
    plew_write((PlewString){" = ", 3});
    wPA(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"_get(__fa", 9});
    writeInt(((long long)(t)));
    plew_write((PlewString){", __fi", 6});
    writeInt(((long long)(t)));
    plew_write((PlewString){");\n", 3});
    addLocal(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0);
    genBlock(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    }
    else if (_m69.tag == 9) {
    plew_write((PlewString){"    break;\n", 11});
    }
    else if (_m69.tag == 10) {
    plew_write((PlewString){"    continue;\n", 14});
    }
    else if (_m69.tag == 8) {
        long long scrut = _m69.data.Match.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m69.data.Match.arms;
        (void)arms;
    if (matchExhaustive(&((*c)), arms)) {
    }
    else {
    plew_write((PlewString){"    __plew_match_not_exhaustive;\n", 33});
    return;
    }
    long long t = (*c).tmp;
    (*c).tmp = ((*c).tmp + 1);
    long long enumStart = 0;
    long long enumLen = 0;
    long long hasWildcard = 0;
    long long q = 0;
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
    q += 1;
    }
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    ", 4});
    writeSpan(&((*c)), enumStart, enumLen);
    plew_write((PlewString){" _m", 3});
    writeInt(((long long)(t)));
    plew_write((PlewString){" = ", 3});
    genExpr(&((*c)), scrut);
    plew_write((PlewString){";\n", 2});
    long long i = 0;
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
    writeInt(((long long)(t)));
    plew_write((PlewString){".tag == ", 8});
    writeInt(variantIndex(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen));
    plew_write((PlewString){") {\n", 4});
    PlewArray_Bind binds = a.binds;
    long long bi = 0;
    while (bi < (long long)((binds).len)) {
    Bind bd = PlewArray_Bind_get(binds, (long long)(bi));
    plew_write((PlewString){"        ", 8});
    genBindType(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.nameStart, bd.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = _m", 5});
    writeInt(((long long)(t)));
    plew_write((PlewString){".data.", 6});
    writeSpan(&((*c)), a.variantStart, a.variantLen);
    plew_write((PlewString){".", 1});
    writeSpan(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"        (void)", 14});
    writeSpan(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){";\n", 2});
    addBindLocal(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.nameStart, bd.nameLen);
    bi += 1;
    }
    genBlock(&((*c)), a.body);
    plew_write((PlewString){"    }\n", 6});
    }
    i += 1;
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
void genBlock(Comp* c, long long id) {
    Block b = PlewArray_Block_get((*c).blocks, (long long)(id));
    PlewArray_U64 stmts = b.stmts;
    long long i = 0;
    while (i < (long long)((stmts).len)) {
    genStmt(&((*c)), PlewArray_U64_get(stmts, (long long)(i)));
    i += 1;
    }
}
long long nameIsMain(Comp* c, Func f) {
    return rangeEquals((*c).bytes, f.nameStart, f.nameLen, (PlewString){"main", 4});
}
void genStructDef(Comp* c, long long si) {
    StructDef s = PlewArray_StructDef_get((*c).structs, (long long)(si));
    plew_write((PlewString){"struct ", 7});
    writeSpan(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" {\n", 3});
    PlewArray_FieldDef fields = s.fields;
    long long i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    plew_write((PlewString){"    ", 4});
    genCTypeRef(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";\n", 2});
    i += 1;
    }
    plew_write((PlewString){"};\n", 3});
}
void genSignature(Comp* c, Func f) {
    if (nameIsMain(&((*c)), f)) {
    plew_write((PlewString){"int main(int argc, char** argv)", 31});
    return;
    }
    if (f.hasRet) {
    genCTypeRef(&((*c)), f.retStart, f.retLen, f.retIsArray);
    plew_write((PlewString){" ", 1});
    }
    else {
    plew_write((PlewString){"void ", 5});
    }
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){"(", 1});
    PlewArray_Param params = f.params;
    if ((long long)((params).len) == 0) {
    plew_write((PlewString){"void", 4});
    }
    else {
    long long i = 0;
    while (i < (long long)((params).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    Param p = PlewArray_Param_get(params, (long long)(i));
    genCTypeRef(&((*c)), p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), p.nameStart, p.nameLen);
    i += 1;
    }
    }
    plew_write((PlewString){")", 1});
}
void genFunc(Comp* c, long long fi) {
    Func f = PlewArray_Func_get((*c).funcs, (long long)(fi));
    long long isMain = nameIsMain(&((*c)), f);
    (*c).curIsMain = isMain;
    if (f.hasRet) {
    (*c).curRetVoid = 0;
    }
    else {
    (*c).curRetVoid = 1;
    }
    (*c).locals = PlewArray_Local_new();
    PlewArray_Param params = f.params;
    long long pi = 0;
    while (pi < (long long)((params).len)) {
    Param p = PlewArray_Param_get(params, (long long)(pi));
    addLocal(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.isInout);
    pi += 1;
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
void genEnumDef(Comp* c, long long ei) {
    EnumDef e = PlewArray_EnumDef_get((*c).enums, (long long)(ei));
    plew_write((PlewString){"struct ", 7});
    writeSpan(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" {\n", 3});
    plew_write((PlewString){"    long long tag;\n", 19});
    plew_write((PlewString){"    union {\n", 12});
    PlewArray_Variant vars = e.variants;
    long long vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = PlewArray_Variant_get(vars, (long long)(vi));
    plew_write((PlewString){"        struct {", 16});
    PlewArray_FieldDef fs = v.fields;
    if ((long long)((fs).len) == 0) {
    plew_write((PlewString){" char _u; ", 10});
    }
    else {
    long long fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    plew_write((PlewString){" ", 1});
    genCTypeRef(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";", 1});
    fi += 1;
    }
    plew_write((PlewString){" ", 1});
    }
    plew_write((PlewString){"} ", 2});
    writeSpan(&((*c)), v.nameStart, v.nameLen);
    plew_write((PlewString){";\n", 2});
    vi += 1;
    }
    plew_write((PlewString){"    } data;\n", 12});
    plew_write((PlewString){"};\n", 3});
}
void wPA(Comp* c, long long elemStart, long long elemLen) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan(&((*c)), elemStart, elemLen);
}
void genArrayTypedef(Comp* c, long long elemStart, long long elemLen) {
    plew_write((PlewString){"typedef struct { ", 17});
    genCElem(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* data; long long len; long long cap; } ", 40});
    wPA(&((*c)), elemStart, elemLen);
    plew_write((PlewString){";\n", 2});
}
void genArrayRuntimeFns(Comp* c, long long elemStart, long long elemLen) {
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
}
long long isU8Elem(Comp* c, long long elemStart, long long elemLen) {
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
}
int main(int argc, char** argv) {
    plew_argc = argc; plew_argv = argv;
    PlewString src = (PlewString){"", 0};
    if (plew_arg_count() > 1) {
    src = plew_read_file(plew_arg_at((long long)(1)));
    }
    else {
    src = plew_read_stdin();
    }
    Lexer lx = (Lexer){.bytes = ({ PlewString __s = src; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0};
    lex(&(lx));
    Comp c = (Comp){.bytes = ({ PlewString __s = src; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len}; }), .toks = lx.toks, .pos = 0, .exprs = PlewArray_Expr_new(), .stmts = PlewArray_Stmt_new(), .blocks = PlewArray_Block_new(), .funcs = PlewArray_Func_new(), .structs = PlewArray_StructDef_new(), .enums = PlewArray_EnumDef_new(), .arrayElems = PlewArray_Bind_new(), .locals = PlewArray_Local_new(), .tmp = 0, .curIsMain = 0, .curRetVoid = 0, .impPrint = 0, .impWrite = 0, .impWriteByte = 0, .impReadStdin = 0, .impReadFile = 0, .impArgCount = 0, .impArgAt = 0};
    parseProgram(&(c));
    plew_write((PlewString){"#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n#include <string.h>\n", 79});
    plew_write((PlewString){"typedef struct { const char* data; long long len; } PlewString;\n", 64});
    plew_write((PlewString){"__attribute__((unused)) static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (long long i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }\n", 197});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_read_stdin(void) { size_t cap = 4096, len = 0; char* buf = (char*)malloc(cap); int ch; while ((ch = getchar()) != EOF) { if (len + 1 >= cap) { cap *= 2; buf = (char*)realloc(buf, cap); } buf[len++] = (char)ch; } PlewString s; s.data = buf; s.len = (long long)len; return s; }\n", 323});
    plew_write((PlewString){"__attribute__((unused)) static void plew_write(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stdout); }\n", 107});
    plew_write((PlewString){"static int plew_argc = 0;\nstatic char** plew_argv = 0;\n", 55});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_arg_count(void) { return (long long)plew_argc; }\n", 95});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_arg_at(long long i) { PlewString s; if (i < 0 || i >= plew_argc) { s.data = \"\"; s.len = 0; return s; } s.data = plew_argv[i]; s.len = (long long)strlen(plew_argv[i]); return s; }\n", 226});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_read_file(PlewString path) { FILE* f = fopen(path.data, \"rb\"); PlewString s; if (!f) { s.data = \"\"; s.len = 0; return s; } fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET); char* buf = (char*)malloc((size_t)sz + 1); size_t n = fread(buf, 1, (size_t)sz, f); fclose(f); buf[n] = 0; s.data = buf; s.len = (long long)n; return s; }\n", 391});
    long long si = 0;
    while (si < (long long)((c.structs).len)) {
    StructDef s = PlewArray_StructDef_get(c.structs, (long long)(si));
    plew_write((PlewString){"typedef struct ", 15});
    writeSpan(&(c), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&(c), s.nameStart, s.nameLen);
    plew_write((PlewString){";\n", 2});
    si += 1;
    }
    long long ei = 0;
    while (ei < (long long)((c.enums).len)) {
    EnumDef e = PlewArray_EnumDef_get(c.enums, (long long)(ei));
    plew_write((PlewString){"typedef struct ", 15});
    writeSpan(&(c), e.nameStart, e.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan(&(c), e.nameStart, e.nameLen);
    plew_write((PlewString){";\n", 2});
    ei += 1;
    }
    genU8ArrayTypedef();
    long long ai = 0;
    while (ai < (long long)((c.arrayElems).len)) {
    Bind ae = PlewArray_Bind_get(c.arrayElems, (long long)(ai));
    if (isU8Elem(&(c), ae.nameStart, ae.nameLen)) {
    }
    else {
    genArrayTypedef(&(c), ae.nameStart, ae.nameLen);
    }
    ai += 1;
    }
    long long ej = 0;
    while (ej < (long long)((c.enums).len)) {
    genEnumDef(&(c), ej);
    ej += 1;
    }
    long long sj = 0;
    while (sj < (long long)((c.structs).len)) {
    genStructDef(&(c), sj);
    sj += 1;
    }
    genU8ArrayRuntime();
    long long ar = 0;
    while (ar < (long long)((c.arrayElems).len)) {
    Bind ae2 = PlewArray_Bind_get(c.arrayElems, (long long)(ar));
    if (isU8Elem(&(c), ae2.nameStart, ae2.nameLen)) {
    }
    else {
    genArrayRuntimeFns(&(c), ae2.nameStart, ae2.nameLen);
    }
    ar += 1;
    }
    long long i = 0;
    while (i < (long long)((c.funcs).len)) {
    Func f = PlewArray_Func_get(c.funcs, (long long)(i));
    if (nameIsMain(&(c), f)) {
    }
    else {
    genSignature(&(c), f);
    plew_write((PlewString){";\n", 2});
    }
    i += 1;
    }
    {
    long long __fe71 = (long long)((c.funcs).len);
    for (long long j = 0; j < __fe71; j++) {
    genFunc(&(c), j);
    }
    }
    return 0;
}
