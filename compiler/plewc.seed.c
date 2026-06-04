#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef struct { const char* data; long long len; } PlewString;
__attribute__((unused)) static void* plew_arc_alloc(long long bytes) { long long* p = (long long*)malloc(sizeof(long long) + (size_t)bytes); p[0] = 1; return (void*)(p + 1); }
__attribute__((unused)) static void plew_arc_retain(long long* rc) { if (rc) (*rc) += 1; }
__attribute__((unused)) static void plew_arc_release(long long* rc) { if (rc && (--(*rc)) == 0) free((void*)rc); }
__attribute__((unused)) static void* plew_ref_share(void* p) { if (p) ((long long*)p)[-1] += 1; return p; }
typedef struct { void* fn; void* env; long long* rc; void (*drop)(void*); } PlewClosure;
__attribute__((unused)) static PlewClosure plew_closure_share(PlewClosure cl) { plew_arc_retain(cl.rc); return cl; }
__attribute__((unused)) static void plew_closure_release(PlewClosure cl) { if (cl.rc && (--(*cl.rc)) == 0) { if (cl.drop) cl.drop(cl.env); free((void*)cl.rc); } }
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
typedef struct CaptureEntry CaptureEntry;
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
typedef struct TraitDef TraitDef;
typedef struct DeriveReq DeriveReq;
typedef struct Conform Conform;
typedef struct MethodAlias MethodAlias;
typedef struct FuncBound FuncBound;
typedef struct FnInst FnInst;
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
typedef struct { Func* data; long long len; long long cap; long long* rc; } PlewArray_Func;
typedef struct { Variant* data; long long len; long long cap; long long* rc; } PlewArray_Variant;
typedef struct { Expr* data; long long len; long long cap; long long* rc; } PlewArray_Expr;
typedef struct { Stmt* data; long long len; long long cap; long long* rc; } PlewArray_Stmt;
typedef struct { Block* data; long long len; long long cap; long long* rc; } PlewArray_Block;
typedef struct { StructDef* data; long long len; long long cap; long long* rc; } PlewArray_StructDef;
typedef struct { EnumDef* data; long long len; long long cap; long long* rc; } PlewArray_EnumDef;
typedef struct { TraitDef* data; long long len; long long cap; long long* rc; } PlewArray_TraitDef;
typedef struct { Conform* data; long long len; long long cap; long long* rc; } PlewArray_Conform;
typedef struct { MethodAlias* data; long long len; long long cap; long long* rc; } PlewArray_MethodAlias;
typedef struct { DeriveReq* data; long long len; long long cap; long long* rc; } PlewArray_DeriveReq;
typedef struct { FuncBound* data; long long len; long long cap; long long* rc; } PlewArray_FuncBound;
typedef struct { TypeRef* data; long long len; long long cap; long long* rc; } PlewArray_TypeRef;
typedef struct { FnInst* data; long long len; long long cap; long long* rc; } PlewArray_FnInst;
typedef struct { CaptureEntry* data; long long len; long long cap; long long* rc; } PlewArray_CaptureEntry;
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
        struct { char _u; } KwUnique;
        struct { char _u; } KwDeinit;
        struct { char _u; } KwMove;
        struct { char _u; } KwBorrow;
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
        struct { uint64_t operand; long long isBorrow; } Move;
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
struct CaptureEntry {
    uint64_t closureId;
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t tyStart;
    uint64_t tyLen;
    long long isArray;
    uint64_t ty;
    long long boxed;
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
    long long moved;
    uint64_t cnum;
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
    long long isStruct;
};
struct PatInfo {
    long long isWildcard;
    uint64_t enumStart;
    uint64_t enumLen;
    uint64_t variantStart;
    uint64_t variantLen;
    PlewArray_Bind binds;
    long long isStruct;
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
    long long isMove;
    long long isBorrow;
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
    long long hasDefault;
    uint64_t defaultVal;
};
struct StructDef {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_Bind typeParams;
    PlewArray_FieldDef fields;
    long long isUnique;
};
struct Variant {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_FieldDef fields;
};
struct TraitDef {
    uint64_t nameStart;
    uint64_t nameLen;
    PlewArray_Bind supertraits;
    PlewArray_Func reqs;
};
struct DeriveReq {
    uint64_t typeStart;
    uint64_t typeLen;
    long long isEnum;
    uint64_t nameStart;
    uint64_t nameLen;
};
struct Conform {
    uint64_t typeStart;
    uint64_t typeLen;
    uint64_t traitStart;
    uint64_t traitLen;
    long long derived;
    PlewArray_Func witnessed;
};
struct MethodAlias {
    uint64_t recvStart;
    uint64_t recvLen;
    uint64_t aliasStart;
    uint64_t aliasLen;
    uint64_t realStart;
    uint64_t realLen;
};
struct FuncBound {
    uint64_t fnIdx;
    uint64_t paramStart;
    uint64_t paramLen;
    uint64_t traitStart;
    uint64_t traitLen;
};
struct FnInst {
    uint64_t fnIdx;
    PlewArray_U64 args;
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
    long long selfMove;
    long long isAssoc;
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
    PlewArray_TraitDef traits;
    PlewArray_Conform conforms;
    PlewArray_MethodAlias methodAliases;
    PlewArray_DeriveReq derives;
    PlewArray_Bind pendingDerives;
    PlewArray_FuncBound funcBounds;
    uint64_t curCheckFn;
    PlewArray_Func curWitnessed;
    PlewArray_Bind curWhereTraits;
    PlewArray_TypeRef types;
    PlewArray_U64 genInsts;
    PlewArray_FnInst fnInsts;
    PlewArray_U64 fnTypes;
    PlewArray_U64 fnThunks;
    PlewArray_CaptureEntry captures;
    uint64_t curClosureId;
    long long curInClosure;
    uint64_t curCaptureMark;
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
    long long curSelfMove;
    PlewArray_Bind curTypeParams;
    PlewArray_U64 curTypeArgs;
    uint64_t curRecvInstRef;
    uint64_t curGiveTmp;
    uint64_t curLoopMark;
    uint64_t curBranchBase;
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
    PlewArray_Bind deinits;
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
TraitDef TraitDef_copy(TraitDef s);
TraitDef TraitDef_share(TraitDef s);
void TraitDef_release(TraitDef s);
Conform Conform_copy(Conform s);
Conform Conform_share(Conform s);
void Conform_release(Conform s);
FnInst FnInst_copy(FnInst s);
FnInst FnInst_share(FnInst s);
void FnInst_release(FnInst s);
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
__attribute__((unused)) static void PlewArray_MatchArm_set(PlewArray_MatchArm* a, long long i, MatchArm v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_MatchArm_unique(a); MatchArm_release(a->data[i]); a->data[i] = MatchArm_copy(v); }
__attribute__((unused)) static void PlewArray_MatchArm_push(PlewArray_MatchArm* a, MatchArm v) { PlewArray_MatchArm_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MatchArm* nd = (MatchArm*)plew_arc_alloc(sizeof(MatchArm) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = MatchArm_copy(v); a->len++; }
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
__attribute__((unused)) static PlewArray_Func PlewArray_Func_new(void) { PlewArray_Func a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Func PlewArray_Func_get(PlewArray_Func a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_copy(PlewArray_Func a) { PlewArray_Func r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Func*)plew_arc_alloc(sizeof(Func) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = Func_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Func_release(PlewArray_Func a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) Func_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_Func PlewArray_Func_share(PlewArray_Func a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Func_unique(PlewArray_Func* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Func nc = PlewArray_Func_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Func_set(PlewArray_Func* a, long long i, Func v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Func_unique(a); Func_release(a->data[i]); a->data[i] = Func_copy(v); }
__attribute__((unused)) static void PlewArray_Func_push(PlewArray_Func* a, Func v) { PlewArray_Func_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Func* nd = (Func*)plew_arc_alloc(sizeof(Func) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = Func_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_new(void) { PlewArray_Variant a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Variant PlewArray_Variant_get(PlewArray_Variant a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_copy(PlewArray_Variant a) { PlewArray_Variant r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Variant*)plew_arc_alloc(sizeof(Variant) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = Variant_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Variant_release(PlewArray_Variant a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) Variant_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_Variant PlewArray_Variant_share(PlewArray_Variant a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Variant_unique(PlewArray_Variant* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Variant nc = PlewArray_Variant_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Variant_set(PlewArray_Variant* a, long long i, Variant v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Variant_unique(a); Variant_release(a->data[i]); a->data[i] = Variant_copy(v); }
__attribute__((unused)) static void PlewArray_Variant_push(PlewArray_Variant* a, Variant v) { PlewArray_Variant_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Variant* nd = (Variant*)plew_arc_alloc(sizeof(Variant) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = Variant_copy(v); a->len++; }
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
__attribute__((unused)) static void PlewArray_Block_set(PlewArray_Block* a, long long i, Block v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Block_unique(a); Block_release(a->data[i]); a->data[i] = Block_copy(v); }
__attribute__((unused)) static void PlewArray_Block_push(PlewArray_Block* a, Block v) { PlewArray_Block_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Block* nd = (Block*)plew_arc_alloc(sizeof(Block) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = Block_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_new(void) { PlewArray_StructDef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static StructDef PlewArray_StructDef_get(PlewArray_StructDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_copy(PlewArray_StructDef a) { PlewArray_StructDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (StructDef*)plew_arc_alloc(sizeof(StructDef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = StructDef_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_StructDef_release(PlewArray_StructDef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) StructDef_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_StructDef PlewArray_StructDef_share(PlewArray_StructDef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_StructDef_unique(PlewArray_StructDef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_StructDef nc = PlewArray_StructDef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_StructDef_set(PlewArray_StructDef* a, long long i, StructDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_StructDef_unique(a); StructDef_release(a->data[i]); a->data[i] = StructDef_copy(v); }
__attribute__((unused)) static void PlewArray_StructDef_push(PlewArray_StructDef* a, StructDef v) { PlewArray_StructDef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; StructDef* nd = (StructDef*)plew_arc_alloc(sizeof(StructDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = StructDef_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_new(void) { PlewArray_EnumDef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static EnumDef PlewArray_EnumDef_get(PlewArray_EnumDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_copy(PlewArray_EnumDef a) { PlewArray_EnumDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (EnumDef*)plew_arc_alloc(sizeof(EnumDef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = EnumDef_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_EnumDef_release(PlewArray_EnumDef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) EnumDef_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_EnumDef PlewArray_EnumDef_share(PlewArray_EnumDef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_EnumDef_unique(PlewArray_EnumDef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_EnumDef nc = PlewArray_EnumDef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_EnumDef_set(PlewArray_EnumDef* a, long long i, EnumDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_EnumDef_unique(a); EnumDef_release(a->data[i]); a->data[i] = EnumDef_copy(v); }
__attribute__((unused)) static void PlewArray_EnumDef_push(PlewArray_EnumDef* a, EnumDef v) { PlewArray_EnumDef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; EnumDef* nd = (EnumDef*)plew_arc_alloc(sizeof(EnumDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = EnumDef_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_TraitDef PlewArray_TraitDef_new(void) { PlewArray_TraitDef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static TraitDef PlewArray_TraitDef_get(PlewArray_TraitDef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_TraitDef PlewArray_TraitDef_copy(PlewArray_TraitDef a) { PlewArray_TraitDef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (TraitDef*)plew_arc_alloc(sizeof(TraitDef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = TraitDef_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_TraitDef_release(PlewArray_TraitDef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) TraitDef_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_TraitDef PlewArray_TraitDef_share(PlewArray_TraitDef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_TraitDef_unique(PlewArray_TraitDef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_TraitDef nc = PlewArray_TraitDef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_TraitDef_set(PlewArray_TraitDef* a, long long i, TraitDef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_TraitDef_unique(a); TraitDef_release(a->data[i]); a->data[i] = TraitDef_copy(v); }
__attribute__((unused)) static void PlewArray_TraitDef_push(PlewArray_TraitDef* a, TraitDef v) { PlewArray_TraitDef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; TraitDef* nd = (TraitDef*)plew_arc_alloc(sizeof(TraitDef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = TraitDef_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_Conform PlewArray_Conform_new(void) { PlewArray_Conform a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static Conform PlewArray_Conform_get(PlewArray_Conform a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_Conform PlewArray_Conform_copy(PlewArray_Conform a) { PlewArray_Conform r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (Conform*)plew_arc_alloc(sizeof(Conform) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = Conform_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_Conform_release(PlewArray_Conform a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) Conform_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_Conform PlewArray_Conform_share(PlewArray_Conform a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_Conform_unique(PlewArray_Conform* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_Conform nc = PlewArray_Conform_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_Conform_set(PlewArray_Conform* a, long long i, Conform v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_Conform_unique(a); Conform_release(a->data[i]); a->data[i] = Conform_copy(v); }
__attribute__((unused)) static void PlewArray_Conform_push(PlewArray_Conform* a, Conform v) { PlewArray_Conform_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; Conform* nd = (Conform*)plew_arc_alloc(sizeof(Conform) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = Conform_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_MethodAlias PlewArray_MethodAlias_new(void) { PlewArray_MethodAlias a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static MethodAlias PlewArray_MethodAlias_get(PlewArray_MethodAlias a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_MethodAlias PlewArray_MethodAlias_copy(PlewArray_MethodAlias a) { PlewArray_MethodAlias r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (MethodAlias*)plew_arc_alloc(sizeof(MethodAlias) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_MethodAlias_release(PlewArray_MethodAlias a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_MethodAlias PlewArray_MethodAlias_share(PlewArray_MethodAlias a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_MethodAlias_unique(PlewArray_MethodAlias* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_MethodAlias nc = PlewArray_MethodAlias_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_MethodAlias_set(PlewArray_MethodAlias* a, long long i, MethodAlias v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_MethodAlias_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_MethodAlias_push(PlewArray_MethodAlias* a, MethodAlias v) { PlewArray_MethodAlias_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; MethodAlias* nd = (MethodAlias*)plew_arc_alloc(sizeof(MethodAlias) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_DeriveReq PlewArray_DeriveReq_new(void) { PlewArray_DeriveReq a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static DeriveReq PlewArray_DeriveReq_get(PlewArray_DeriveReq a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_DeriveReq PlewArray_DeriveReq_copy(PlewArray_DeriveReq a) { PlewArray_DeriveReq r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (DeriveReq*)plew_arc_alloc(sizeof(DeriveReq) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_DeriveReq_release(PlewArray_DeriveReq a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_DeriveReq PlewArray_DeriveReq_share(PlewArray_DeriveReq a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_DeriveReq_unique(PlewArray_DeriveReq* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_DeriveReq nc = PlewArray_DeriveReq_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_DeriveReq_set(PlewArray_DeriveReq* a, long long i, DeriveReq v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_DeriveReq_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_DeriveReq_push(PlewArray_DeriveReq* a, DeriveReq v) { PlewArray_DeriveReq_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; DeriveReq* nd = (DeriveReq*)plew_arc_alloc(sizeof(DeriveReq) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_FuncBound PlewArray_FuncBound_new(void) { PlewArray_FuncBound a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static FuncBound PlewArray_FuncBound_get(PlewArray_FuncBound a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_FuncBound PlewArray_FuncBound_copy(PlewArray_FuncBound a) { PlewArray_FuncBound r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (FuncBound*)plew_arc_alloc(sizeof(FuncBound) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_FuncBound_release(PlewArray_FuncBound a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_FuncBound PlewArray_FuncBound_share(PlewArray_FuncBound a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_FuncBound_unique(PlewArray_FuncBound* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_FuncBound nc = PlewArray_FuncBound_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_FuncBound_set(PlewArray_FuncBound* a, long long i, FuncBound v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_FuncBound_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_FuncBound_push(PlewArray_FuncBound* a, FuncBound v) { PlewArray_FuncBound_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; FuncBound* nd = (FuncBound*)plew_arc_alloc(sizeof(FuncBound) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_new(void) { PlewArray_TypeRef a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static TypeRef PlewArray_TypeRef_get(PlewArray_TypeRef a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_copy(PlewArray_TypeRef a) { PlewArray_TypeRef r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (TypeRef*)plew_arc_alloc(sizeof(TypeRef) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = TypeRef_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_TypeRef_release(PlewArray_TypeRef a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) TypeRef_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_TypeRef PlewArray_TypeRef_share(PlewArray_TypeRef a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_TypeRef_unique(PlewArray_TypeRef* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_TypeRef nc = PlewArray_TypeRef_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_TypeRef_set(PlewArray_TypeRef* a, long long i, TypeRef v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_TypeRef_unique(a); TypeRef_release(a->data[i]); a->data[i] = TypeRef_copy(v); }
__attribute__((unused)) static void PlewArray_TypeRef_push(PlewArray_TypeRef* a, TypeRef v) { PlewArray_TypeRef_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; TypeRef* nd = (TypeRef*)plew_arc_alloc(sizeof(TypeRef) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = TypeRef_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_FnInst PlewArray_FnInst_new(void) { PlewArray_FnInst a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static FnInst PlewArray_FnInst_get(PlewArray_FnInst a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_FnInst PlewArray_FnInst_copy(PlewArray_FnInst a) { PlewArray_FnInst r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (FnInst*)plew_arc_alloc(sizeof(FnInst) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = FnInst_copy(a.data[i]); } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_FnInst_release(PlewArray_FnInst a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; for (long long i = 0; i < a.len; i++) FnInst_release(a.data[i]); free(a.rc); }
__attribute__((unused)) static PlewArray_FnInst PlewArray_FnInst_share(PlewArray_FnInst a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_FnInst_unique(PlewArray_FnInst* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_FnInst nc = PlewArray_FnInst_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_FnInst_set(PlewArray_FnInst* a, long long i, FnInst v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_FnInst_unique(a); FnInst_release(a->data[i]); a->data[i] = FnInst_copy(v); }
__attribute__((unused)) static void PlewArray_FnInst_push(PlewArray_FnInst* a, FnInst v) { PlewArray_FnInst_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; FnInst* nd = (FnInst*)plew_arc_alloc(sizeof(FnInst) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = FnInst_copy(v); a->len++; }
__attribute__((unused)) static PlewArray_CaptureEntry PlewArray_CaptureEntry_new(void) { PlewArray_CaptureEntry a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }
__attribute__((unused)) static CaptureEntry PlewArray_CaptureEntry_get(PlewArray_CaptureEntry a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static PlewArray_CaptureEntry PlewArray_CaptureEntry_copy(PlewArray_CaptureEntry a) { PlewArray_CaptureEntry r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (CaptureEntry*)plew_arc_alloc(sizeof(CaptureEntry) * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) r.data[i] = a.data[i]; } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }
__attribute__((unused)) static void PlewArray_CaptureEntry_release(PlewArray_CaptureEntry a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; free(a.rc); }
__attribute__((unused)) static PlewArray_CaptureEntry PlewArray_CaptureEntry_share(PlewArray_CaptureEntry a) { plew_arc_retain(a.rc); return a; }
__attribute__((unused)) static void PlewArray_CaptureEntry_unique(PlewArray_CaptureEntry* a) { if (a->rc && (*(a->rc)) > 1) { PlewArray_CaptureEntry nc = PlewArray_CaptureEntry_copy(*a); plew_arc_release(a->rc); *a = nc; } }
__attribute__((unused)) static void PlewArray_CaptureEntry_set(PlewArray_CaptureEntry* a, long long i, CaptureEntry v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_CaptureEntry_unique(a); a->data[i] = v; }
__attribute__((unused)) static void PlewArray_CaptureEntry_push(PlewArray_CaptureEntry* a, CaptureEntry v) { PlewArray_CaptureEntry_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; CaptureEntry* nd = (CaptureEntry*)plew_arc_alloc(sizeof(CaptureEntry) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = v; a->len++; }
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
__attribute__((unused)) static void PlewArray_PatInfo_set(PlewArray_PatInfo* a, long long i, PatInfo v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } PlewArray_PatInfo_unique(a); PatInfo_release(a->data[i]); a->data[i] = PatInfo_copy(v); }
__attribute__((unused)) static void PlewArray_PatInfo_push(PlewArray_PatInfo* a, PatInfo v) { PlewArray_PatInfo_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; PatInfo* nd = (PatInfo*)plew_arc_alloc(sizeof(PatInfo) * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = PatInfo_copy(v); a->len++; }
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
TraitDef TraitDef_copy(TraitDef s) { TraitDef r = s; r.supertraits = PlewArray_Bind_copy(s.supertraits); r.reqs = PlewArray_Func_copy(s.reqs); return r; }
TraitDef TraitDef_share(TraitDef s) { plew_arc_retain(s.supertraits.rc); plew_arc_retain(s.reqs.rc); return s; }
void TraitDef_release(TraitDef s) { PlewArray_Bind_release(s.supertraits); PlewArray_Func_release(s.reqs); }
Conform Conform_copy(Conform s) { Conform r = s; r.witnessed = PlewArray_Func_copy(s.witnessed); return r; }
Conform Conform_share(Conform s) { plew_arc_retain(s.witnessed.rc); return s; }
void Conform_release(Conform s) { PlewArray_Func_release(s.witnessed); }
FnInst FnInst_copy(FnInst s) { FnInst r = s; r.args = PlewArray_U64_copy(s.args); return r; }
FnInst FnInst_share(FnInst s) { plew_arc_retain(s.args.rc); return s; }
void FnInst_release(FnInst s) { PlewArray_U64_release(s.args); }
EnumDef EnumDef_copy(EnumDef s) { EnumDef r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.variants = PlewArray_Variant_copy(s.variants); return r; }
EnumDef EnumDef_share(EnumDef s) { plew_arc_retain(s.typeParams.rc); plew_arc_retain(s.variants.rc); return s; }
void EnumDef_release(EnumDef s) { PlewArray_Bind_release(s.typeParams); PlewArray_Variant_release(s.variants); }
Func Func_copy(Func s) { Func r = s; r.typeParams = PlewArray_Bind_copy(s.typeParams); r.params = PlewArray_Param_copy(s.params); return r; }
Func Func_share(Func s) { plew_arc_retain(s.typeParams.rc); plew_arc_retain(s.params.rc); return s; }
void Func_release(Func s) { PlewArray_Bind_release(s.typeParams); PlewArray_Param_release(s.params); }
Comp Comp_copy(Comp s) { Comp r = s; r.bytes = PlewArray_U8_copy(s.bytes); r.toks = PlewArray_Tok_copy(s.toks); r.exprs = PlewArray_Expr_copy(s.exprs); r.stmts = PlewArray_Stmt_copy(s.stmts); r.blocks = PlewArray_Block_copy(s.blocks); r.funcs = PlewArray_Func_copy(s.funcs); r.structs = PlewArray_StructDef_copy(s.structs); r.enums = PlewArray_EnumDef_copy(s.enums); r.traits = PlewArray_TraitDef_copy(s.traits); r.conforms = PlewArray_Conform_copy(s.conforms); r.methodAliases = PlewArray_MethodAlias_copy(s.methodAliases); r.derives = PlewArray_DeriveReq_copy(s.derives); r.pendingDerives = PlewArray_Bind_copy(s.pendingDerives); r.funcBounds = PlewArray_FuncBound_copy(s.funcBounds); r.curWitnessed = PlewArray_Func_copy(s.curWitnessed); r.curWhereTraits = PlewArray_Bind_copy(s.curWhereTraits); r.types = PlewArray_TypeRef_copy(s.types); r.genInsts = PlewArray_U64_copy(s.genInsts); r.fnInsts = PlewArray_FnInst_copy(s.fnInsts); r.fnTypes = PlewArray_U64_copy(s.fnTypes); r.fnThunks = PlewArray_U64_copy(s.fnThunks); r.captures = PlewArray_CaptureEntry_copy(s.captures); r.arrayElems = PlewArray_Bind_copy(s.arrayElems); r.locals = PlewArray_Local_copy(s.locals); r.curTypeParams = PlewArray_Bind_copy(s.curTypeParams); r.curTypeArgs = PlewArray_U64_copy(s.curTypeArgs); r.deinits = PlewArray_Bind_copy(s.deinits); return r; }
Comp Comp_share(Comp s) { plew_arc_retain(s.bytes.rc); plew_arc_retain(s.toks.rc); plew_arc_retain(s.exprs.rc); plew_arc_retain(s.stmts.rc); plew_arc_retain(s.blocks.rc); plew_arc_retain(s.funcs.rc); plew_arc_retain(s.structs.rc); plew_arc_retain(s.enums.rc); plew_arc_retain(s.traits.rc); plew_arc_retain(s.conforms.rc); plew_arc_retain(s.methodAliases.rc); plew_arc_retain(s.derives.rc); plew_arc_retain(s.pendingDerives.rc); plew_arc_retain(s.funcBounds.rc); plew_arc_retain(s.curWitnessed.rc); plew_arc_retain(s.curWhereTraits.rc); plew_arc_retain(s.types.rc); plew_arc_retain(s.genInsts.rc); plew_arc_retain(s.fnInsts.rc); plew_arc_retain(s.fnTypes.rc); plew_arc_retain(s.fnThunks.rc); plew_arc_retain(s.captures.rc); plew_arc_retain(s.arrayElems.rc); plew_arc_retain(s.locals.rc); plew_arc_retain(s.curTypeParams.rc); plew_arc_retain(s.curTypeArgs.rc); plew_arc_retain(s.deinits.rc); return s; }
void Comp_release(Comp s) { PlewArray_U8_release(s.bytes); PlewArray_Tok_release(s.toks); PlewArray_Expr_release(s.exprs); PlewArray_Stmt_release(s.stmts); PlewArray_Block_release(s.blocks); PlewArray_Func_release(s.funcs); PlewArray_StructDef_release(s.structs); PlewArray_EnumDef_release(s.enums); PlewArray_TraitDef_release(s.traits); PlewArray_Conform_release(s.conforms); PlewArray_MethodAlias_release(s.methodAliases); PlewArray_DeriveReq_release(s.derives); PlewArray_Bind_release(s.pendingDerives); PlewArray_FuncBound_release(s.funcBounds); PlewArray_Func_release(s.curWitnessed); PlewArray_Bind_release(s.curWhereTraits); PlewArray_TypeRef_release(s.types); PlewArray_U64_release(s.genInsts); PlewArray_FnInst_release(s.fnInsts); PlewArray_U64_release(s.fnTypes); PlewArray_U64_release(s.fnThunks); PlewArray_CaptureEntry_release(s.captures); PlewArray_Bind_release(s.arrayElems); PlewArray_Local_release(s.locals); PlewArray_Bind_release(s.curTypeParams); PlewArray_U64_release(s.curTypeArgs); PlewArray_Bind_release(s.deinits); }
unsigned char Lexer_at_off_U64(Lexer self, uint64_t off);
void Lexer_emit_k_Kind_start_U64_len_U64(Lexer* self, Kind k, uint64_t start, uint64_t len);
long long Lexer_lastWasNewline(Lexer self);
long long Lexer_lastCanEnd(Lexer self);
long long isDigit_b_U8(unsigned char b);
long long isAlpha_b_U8(unsigned char b);
long long isAlnum_b_U8(unsigned char b);
long long rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8 bytes, uint64_t start, uint64_t len, PlewString kw);
Kind identKind_bytes_AU8_start_U64_len_U64(PlewArray_U8 bytes, uint64_t start, uint64_t len);
void lex_lx_Lexer(Lexer* lx);
int64_t kindCode_k_Kind(Kind k);
Kind Comp_curKind(Comp* self);
Tok Comp_cur(Comp* self);
Kind Comp_peekKind_off_U64(Comp* self, uint64_t off);
void Comp_advance(Comp* self);
void Comp_skipNewlines(Comp* self);
long long Comp_identIs_kw_String(Comp* self, PlewString kw);
uint64_t Comp_pushExpr_e_Expr(Comp* self, Expr e);
uint64_t Comp_pushStmt_s_Stmt(Comp* self, Stmt s);
uint64_t Comp_pushType_t_TypeRef(Comp* self, TypeRef t);
int64_t Comp_tokenValue_t_Tok(Comp* self, Tok t);
int64_t binPrec_k_Kind(Kind k);
int64_t charValue_c_Comp_t_Tok(Comp* c, Tok t);
uint64_t parsePrimary_c_Comp(Comp* c);
uint64_t parseUnary_c_Comp(Comp* c);
uint64_t parsePostfix_c_Comp(Comp* c);
uint64_t parseMake_c_Comp(Comp* c);
uint64_t parseBin_c_Comp_minPrec_I64(Comp* c, int64_t minPrec);
uint64_t parseExpr_c_Comp(Comp* c);
PlewArray_Arg parseCallArgs_c_Comp(Comp* c);
long long isAssignOp_k_Kind(Kind k);
PType parseTypeTok_c_Comp(Comp* c);
PlewArray_Bind parseTypeParams_c_Comp(Comp* c);
void recordArrayElem_c_Comp_ty_PType(Comp* c, PType ty);
uint64_t parseLet_c_Comp_mutable_Bool(Comp* c, long long mutable);
uint64_t parsePrint_c_Comp(Comp* c);
uint64_t parsePanic_c_Comp(Comp* c);
uint64_t parseReturn_c_Comp(Comp* c);
uint64_t parseIf_c_Comp(Comp* c);
uint64_t parseIfExpr_c_Comp(Comp* c);
uint64_t parseGive_c_Comp(Comp* c);
uint64_t parseWhile_c_Comp(Comp* c);
uint64_t parseFor_c_Comp(Comp* c);
uint64_t parseExprOrAssign_c_Comp(Comp* c);
PatInfo parsePattern_c_Comp(Comp* c);
long long bindNamesMatch_c_Comp_a_ABind_b_ABind(Comp* c, PlewArray_Bind a, PlewArray_Bind b);
PlewArray_PatInfo parseArmPatterns_c_Comp(Comp* c);
uint64_t parseArmBody_c_Comp(Comp* c);
uint64_t parseMatch_c_Comp(Comp* c);
uint64_t parseMatchExpr_c_Comp(Comp* c);
uint64_t parseStmt_c_Comp(Comp* c);
uint64_t parseBlock_c_Comp(Comp* c);
PlewArray_Param parseParamList_c_Comp(Comp* c);
void parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(Comp* c, long long hasRecv, uint64_t recvStart, uint64_t recvLen, long long selfInout, long long selfMove, PlewArray_Bind implParams, long long traitImpl, long long isAssoc);
PlewArray_Bind parseWhereClause_c_Comp(Comp* c);
void parseFunc_c_Comp(Comp* c);
void parseImpl_c_Comp(Comp* c);
void parseTrait_c_Comp(Comp* c);
Func parseReqSig_c_Comp_isAssoc_Bool(Comp* c, long long isAssoc);
void parseStruct_c_Comp_isUnique_Bool(Comp* c, long long isUnique);
void parseEnum_c_Comp(Comp* c);
void parseDirective_c_Comp(Comp* c);
void drainDerives_c_Comp_typeStart_U64_typeLen_U64_isEnum_Bool(Comp* c, uint64_t typeStart, uint64_t typeLen, long long isEnum);
Bind internBytes_c_Comp_s_String(Comp* c, PlewString s);
Param synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(Bind nameSpan, uint64_t tyStart, uint64_t tyLen);
void synthStructEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(Comp* c, DeriveReq d, Bind eqN, Bind lhsN, Bind rhsN, Bind boolN, Bind eqTrait);
unsigned char digitByte_d_U64(uint64_t d);
void appendU64Digits_c_Comp_n_U64(Comp* c, uint64_t n);
Bind internName_c_Comp_prefix_U8_n_U64(Comp* c, unsigned char prefix, uint64_t n);
uint64_t enumIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
uint64_t synthBool_c_Comp_v_I64(Comp* c, int64_t v);
void synthEnumEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(Comp* c, DeriveReq d, Bind eqN, Bind lhsN, Bind rhsN, Bind boolN, Bind eqTrait);
uint64_t synthOrdering_c_Comp_ordN_Bind_variantN_Bind(Comp* c, Bind ordN, Bind variantN);
uint64_t synthReturnBlock_c_Comp_value_U64(Comp* c, uint64_t value);
void synthStructOrd_c_Comp_d_DeriveReq_cmpN_Bind_lhsN_Bind_rhsN_Bind_ordN_Bind_lessN_Bind_greaterN_Bind_equalN_Bind_ordTrait_Bind(Comp* c, DeriveReq d, Bind cmpN, Bind lhsN, Bind rhsN, Bind ordN, Bind lessN, Bind greaterN, Bind equalN, Bind ordTrait);
void synthesizeDerives_c_Comp(Comp* c);
void markImport_c_Comp_segStart_U64_segLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t segStart, uint64_t segLen, uint64_t nameStart, uint64_t nameLen);
void parseImport_c_Comp(Comp* c);
void parseProgram_c_Comp(Comp* c);
PlewString digitStr_d_I64(int64_t d);
void writeInt_n_I64(int64_t n);
PlewString digitStrU_d_U64(uint64_t d);
void writeU64_n_U64(uint64_t n);
void writeSpan_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void eprintInt_n_I64(int64_t n);
void compileError_msg_String(PlewString msg);
void compileErrorAt_line_I64_msg_String(int64_t line, PlewString msg);
long long isPrimType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long isIntType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
uint64_t intBits_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long intSigned_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long losslessInt_c_Comp_srcStart_U64_srcLen_U64_dstStart_U64_dstLen_U64(Comp* c, uint64_t srcStart, uint64_t srcLen, uint64_t dstStart, uint64_t dstLen);
long long litFitsType_c_Comp_value_I64_dstStart_U64_dstLen_U64(Comp* c, int64_t value, uint64_t dstStart, uint64_t dstLen);
long long litFitsBits_value_I64_bits_U64_sgn_Bool(int64_t value, uint64_t bits, long long sgn);
uint64_t arrayElemRef_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
Bind arrayElemNameForRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef);
void genCElem_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(Comp* c, uint64_t start, uint64_t len, long long isArray);
void genCType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void genTypeInfoCType_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
long long spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(Comp* c, uint64_t aStart, uint64_t aLen, uint64_t bStart, uint64_t bLen);
int64_t lineOf_c_Comp_offset_U64(Comp* c, uint64_t offset);
uint64_t exprOffset_c_Comp_id_U64(Comp* c, uint64_t id);
uint64_t findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
uint64_t firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
long long funcNameExists_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
uint64_t findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
long long isTypeName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
Bind assocRecvName_c_Comp_recv_U64(Comp* c, uint64_t recv);
long long paramsLabelsOk_c_Comp_params_AParam_args_AArg(Comp* c, PlewArray_Param params, PlewArray_Arg args);
long long argMatchesParam_c_Comp_argExpr_U64_p_Param(Comp* c, uint64_t argExpr, Param p);
long long paramsTypesMatch_c_Comp_params_AParam_args_AArg(Comp* c, PlewArray_Param params, PlewArray_Arg args);
long long callLabelsOk_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
long long armCovers_c_Comp_arms_AMatchArm_variantStart_U64_variantLen_U64(Comp* c, PlewArray_MatchArm arms, uint64_t variantStart, uint64_t variantLen);
long long matchExhaustive_c_Comp_arms_AMatchArm(Comp* c, PlewArray_MatchArm arms);
uint64_t variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen);
TypeInfo scalarInfo(void);
Bind kwSpan_c_Comp_kw_String_kwLen_U64(Comp* c, PlewString kw, uint64_t kwLen);
Bind stringTypeSpan_c_Comp(Comp* c);
TypeInfo typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(Comp* c, uint64_t start, uint64_t len, long long isArray);
void addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned);
void addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned, uint64_t cnum);
uint64_t shadowCount_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
void writeLocalCName_c_Comp_lo_Local(Comp* c, Local lo);
void writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(Comp* c, uint64_t start, uint64_t len, uint64_t cnum);
uint64_t scopeMark_c_Comp(Comp* c);
void emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(Comp* c, uint64_t mark, uint64_t exclIdx);
void emitRefRelease_c_Comp_nameStart_U64_nameLen_U64_refTy_U64_cnum_U64(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t refTy, uint64_t cnum);
long long structHasDeinit_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long structLocalReleasable_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void popLocals_c_Comp_mark_U64(Comp* c, uint64_t mark);
void scopeExit_c_Comp_mark_U64(Comp* c, uint64_t mark);
long long localIsMutable_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long isSelfRef_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long isInoutLocal_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long typeIsUnique_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
uint64_t localIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long localMoved_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void markMovedLocal_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void markMovedExpr_c_Comp_exprId_U64(Comp* c, uint64_t exprId);
TypeInfo fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen);
long long fieldDeclaredMut_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen);
long long placeIsMutable_c_Comp_id_U64(Comp* c, uint64_t id);
TypeInfo exprType_c_Comp_id_U64(Comp* c, uint64_t id);
uint64_t blockGiveExpr_c_Comp_blkId_U64(Comp* c, uint64_t blkId);
void addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen);
void genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen);
PlewString binOpStr_op_I64(int64_t op);
PlewString unaryOpStr_op_I64(int64_t op);
int64_t strDecodedLen_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long isCheckedArith_op_I64(int64_t op);
int64_t compoundCheckedBin_op_I64(int64_t op);
PlewString overflowBuiltin_op_I64(int64_t op);
TypeInfo arithIntType_c_Comp_lhs_U64_rhs_U64(Comp* c, uint64_t lhs, uint64_t rhs);
void genCheckedArith_c_Comp_op_I64_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64(Comp* c, int64_t op, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen);
void genArrayGet_c_Comp_base_U64_index_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t base, uint64_t index, uint64_t elemStart, uint64_t elemLen);
PlewString intMinMacro_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void genCheckedNeg_c_Comp_operand_U64_tyStart_U64_tyLen_U64(Comp* c, uint64_t operand, uint64_t tyStart, uint64_t tyLen);
void genCheckedDiv_c_Comp_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64_isMod_Bool(Comp* c, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen, long long isMod);
PlewString assignOpStr_op_I64(int64_t op);
long long isCompoundDiv_op_I64(int64_t op);
PlewString compoundDivFn_op_I64(int64_t op);
PlewString assignToBinStr_op_I64(int64_t op);
ConstInt notConst(void);
ConstInt foldConst_c_Comp_id_U64(Comp* c, uint64_t id);
long long tiIsInt_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
void checkLitLeaf_c_Comp_value_I64_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(Comp* c, int64_t value, uint64_t offset, long long isBool, uint64_t tyStart, uint64_t tyLen, uint64_t eKind, uint64_t eBits, long long eSgn);
void checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(Comp* c, uint64_t id, uint64_t eKind, uint64_t eBits, long long eSgn);
IntTy exprIntTy_c_Comp_id_U64(Comp* c, uint64_t id);
void checkArithNoCtx_c_Comp_lhs_U64_rhs_U64(Comp* c, uint64_t lhs, uint64_t rhs);
void checkLitTi_c_Comp_id_U64_ti_TypeInfo(Comp* c, uint64_t id, TypeInfo ti);
void checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(Comp* c, uint64_t id, uint64_t tyStart, uint64_t tyLen, long long isArray);
void checkLitArray_c_Comp_id_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t id, uint64_t elemStart, uint64_t elemLen);
long long typeIsTransitivelyUnique_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void checkFieldContagion_c_Comp(Comp* c);
void checkParamModes_c_Comp_params_AParam(Comp* c, PlewArray_Param params);
void checkArrayElemsNotUnique_c_Comp(Comp* c);
void checkGenericUniqueArgs_c_Comp(Comp* c);
void checkAllParamModes_c_Comp(Comp* c);
void checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(Comp* c, uint64_t exprId, long long inoutOk);
void checkUniqueArgModes_c_Comp_args_AArg(Comp* c, PlewArray_Arg args);
void checkCallArgs_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
void checkMethodArgs_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
TypeInfo makeFieldType_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen);
void checkMakeFields_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_ty_U64_fields_AMakeField(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t ty, PlewArray_MakeField fields);
long long paramSelectorEq_c_Comp_a_AParam_b_AParam(Comp* c, PlewArray_Param a, PlewArray_Param b);
long long witnessedHas_c_Comp_witnessed_AFunc_r_Func(Comp* c, PlewArray_Func witnessed, Func r);
void checkConformances_c_Comp(Comp* c);
long long typeHasMember_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen);
void checkViaTargets_c_Comp(Comp* c);
long long builtinEqOrd_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen);
long long typeConformsTo_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen);
long long typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(Comp* c, uint64_t typeStart, uint64_t typeLen, PlewString traitName);
void checkFnBounds_c_Comp(Comp* c);
void checkMethodBounds_c_Comp(Comp* c);
long long isTypeParamOf_c_Comp_fnIdx_U64_start_U64_len_U64(Comp* c, uint64_t fnIdx, uint64_t start, uint64_t len);
long long boundProvidesMethod_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
long long boundHasTraitNamed_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_traitName_String(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, PlewString traitName);
void checkBoundsExpr_c_Comp_exprId_U64(Comp* c, uint64_t exprId);
void checkBoundsStmt_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId);
void checkBoundsBlock_c_Comp_blkId_U64(Comp* c, uint64_t blkId);
void checkGenericBodies_c_Comp(Comp* c);
long long sameLabels_c_Comp_a_AParam_b_AParam(Comp* c, PlewArray_Param a, PlewArray_Param b);
void checkOverloadCollisions_c_Comp(Comp* c);
void checkImplOnBuiltin_c_Comp(Comp* c);
void checkMoveFnReceivers_c_Comp(Comp* c);
void emitClosureCall_c_Comp_tyRef_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t tyRef, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
void emitCaptureInit_c_Comp_e_CaptureEntry(Comp* c, CaptureEntry e);
long long makeProvides_c_Comp_fields_AMakeField_nameStart_U64_nameLen_U64(Comp* c, PlewArray_MakeField fields, uint64_t nameStart, uint64_t nameLen);
void emitStructMatchExpr_c_Comp_scrut_U64_arm_MatchArm(Comp* c, uint64_t scrut, MatchArm arm);
void genExpr_c_Comp_id_U64(Comp* c, uint64_t id);
long long isPlaceExpr_c_Comp_id_U64(Comp* c, uint64_t id);
void genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen);
void genArrayLiteral_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen);
long long isStringEq_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs);
long long isEnumName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long isAllNullary_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long isEnumEq_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs);
long long compareNeedsTrait_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs);
void emitEnumOperand_c_Comp_id_U64_enStart_U64_enLen_U64(Comp* c, uint64_t id, uint64_t enStart, uint64_t enLen);
void emitEnumTagCmp_c_Comp_lhs_U64_rhs_U64_op_I64_outer_Bool(Comp* c, uint64_t lhs, uint64_t rhs, int64_t op, long long outer);
uint64_t findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(Comp* c, uint64_t typeStart, uint64_t typeLen, PlewString name);
uint64_t orderingVariantIndex_c_Comp_name_String(Comp* c, PlewString name);
long long hasCompareWitness_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs);
long long eqWitnessReady_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
void emitEqCall_c_Comp_typeStart_U64_typeLen_U64_lhs_U64_rhs_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t lhs, uint64_t rhs);
void emitTraitCompare_c_Comp_op_I64_lhs_U64_rhs_U64(Comp* c, int64_t op, uint64_t lhs, uint64_t rhs);
void genCond_c_Comp_id_U64(Comp* c, uint64_t id);
long long tryArrayElemFieldAssign_c_Comp_op_I64_target_U64_value_U64(Comp* c, int64_t op, uint64_t target, uint64_t value);
void emitStructMatch_c_Comp_scrut_U64_arm_MatchArm(Comp* c, uint64_t scrut, MatchArm arm);
void genStmt_c_Comp_id_U64(Comp* c, uint64_t id);
void genBlock_c_Comp_id_U64(Comp* c, uint64_t id);
long long nameIsMain_c_Comp_f_Func(Comp* c, Func f);
long long isTraitName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long methodRecvIsTrait_c_Comp_f_Func(Comp* c, Func f);
long long methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t lo, uint64_t hi, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen);
void instantiateProvidedMethods_c_Comp(Comp* c);
uint64_t structIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long structNeedsCopy_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long structNeedsRelease_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void emitDeinitProtos_c_Comp(Comp* c);
void emitStructCopyProto_c_Comp_si_U64(Comp* c, uint64_t si);
void emitStructCopyDef_c_Comp_si_U64(Comp* c, uint64_t si);
void emitStructShareProto_c_Comp_si_U64(Comp* c, uint64_t si);
void emitStructShareDef_c_Comp_si_U64(Comp* c, uint64_t si);
void emitStructReleaseProto_c_Comp_si_U64(Comp* c, uint64_t si);
void emitStructReleaseDef_c_Comp_si_U64(Comp* c, uint64_t si);
long long monoStructNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoStructCopyProto_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoStructCopyDef_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
long long monoEnumNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoEnumCopyProto_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoEnumCopyDef_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void genStructValue_c_Comp_exprId_U64_structStart_U64_structLen_U64(Comp* c, uint64_t exprId, uint64_t structStart, uint64_t structLen);
void genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(Comp* c, uint64_t exprId, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray);
void genStructDef_c_Comp_si_U64(Comp* c, uint64_t si);
void writeFnSelector_c_Comp_f_Func(Comp* c, Func f);
void genSignature_c_Comp_f_Func(Comp* c, Func f);
void emitSelfDeinit_c_Comp(Comp* c);
void genFunc_c_Comp_fi_U64(Comp* c, uint64_t fi);
void genClosure_c_Comp_id_U64_proto_Bool(Comp* c, uint64_t id, long long proto);
void addFnThunk_c_Comp_fi_U64(Comp* c, uint64_t fi);
void collectFnThunks_c_Comp(Comp* c);
void genThunk_c_Comp_fi_U64_proto_Bool(Comp* c, uint64_t fi, long long proto);
void emitThunks_c_Comp_proto_Bool(Comp* c, long long proto);
long long closureHasCaptures_c_Comp_id_U64(Comp* c, uint64_t id);
long long isBoxedLocalAt_c_Comp_nameStart_U64(Comp* c, uint64_t nameStart);
long long isBoxedCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(Comp* c, uint64_t closureId, uint64_t start, uint64_t len);
long long isCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(Comp* c, uint64_t closureId, uint64_t start, uint64_t len);
void emitClosureEnvStruct_c_Comp_id_U64(Comp* c, uint64_t id);
void emitClosureEnvDrop_c_Comp_id_U64(Comp* c, uint64_t id);
void emitClosureEnvs_c_Comp(Comp* c);
void emitClosures_c_Comp_proto_Bool(Comp* c, long long proto);
void genEnumDef_c_Comp_ei_U64(Comp* c, uint64_t ei);
uint64_t genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
long long isGenericInst_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long isFnType_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long isRefInst_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long isGenericEnumInst_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long typeRefEq_c_Comp_a_U64_b_U64(Comp* c, uint64_t a, uint64_t b);
void emitMangle_c_Comp_ref_U64(Comp* c, uint64_t ref);
void appendMangle_c_Comp_ref_U64(Comp* c, uint64_t ref);
Bind appendMangleSpan_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long isCompoundType_c_Comp_ref_U64(Comp* c, uint64_t ref);
void emitConcreteCType_c_Comp_ref_U64(Comp* c, uint64_t ref);
void emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(Comp* c, uint64_t ref, PlewArray_Bind params, PlewArray_U64 args);
uint64_t resolveTy_c_Comp_tyRef_U64(Comp* c, uint64_t tyRef);
void genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(Comp* c, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray);
long long isTypeParamName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long tyRefIsGround_c_Comp_ref_U64(Comp* c, uint64_t ref);
void ensureArrayElemDeps_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef);
void registerArrayElemRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef);
void scanType_c_Comp_ref_U64(Comp* c, uint64_t ref);
void collectGenInsts_c_Comp(Comp* c);
TypeInfo typeInfoOfRef_c_Comp_ref_U64(Comp* c, uint64_t ref);
TypeInfo substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(Comp* c, uint64_t instRef, PlewArray_Bind params, uint64_t tyRef);
TypeInfo genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t fieldStart, uint64_t fieldLen);
TypeInfo genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen);
void genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen);
void emitMonoForward_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoStruct_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoEnum_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
long long methodMatchesInst_c_Comp_f_Func_instRef_U64(Comp* c, Func f, uint64_t instRef);
void emitMonoMethod_c_Comp_fi_U64_instRef_U64_proto_Bool(Comp* c, uint64_t fi, uint64_t instRef, long long proto);
void emitMonoMethods_c_Comp_proto_Bool(Comp* c, long long proto);
long long isGenericFreeFn_c_Comp_fi_U64(Comp* c, uint64_t fi);
uint64_t findOrAddTypeRef_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t tyRefOfInfo_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
PlewArray_U64 inferFnArgs_c_Comp_f_Func_args_AArg(Comp* c, Func f, PlewArray_Arg args);
long long fnArgsAllGround_c_Comp_args_AU64(Comp* c, PlewArray_U64 args);
long long fnInstExists_c_Comp_fnIdx_U64_args_AU64(Comp* c, uint64_t fnIdx, PlewArray_U64 args);
void registerCallInst_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args);
long long captureSupported_c_Comp_lo_Local(Comp* c, Local lo);
void recordCapture_c_Comp_closureId_U64_localIdx_U64(Comp* c, uint64_t closureId, uint64_t localIdx);
void scanExprInsts_c_Comp_exprId_U64(Comp* c, uint64_t exprId);
void scanAddArmBinds_c_Comp_a_MatchArm(Comp* c, MatchArm a);
void scanStmtInsts_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId);
void scanBlockInsts_c_Comp_blkId_U64(Comp* c, uint64_t blkId);
void collectFnInsts_c_Comp(Comp* c);
void emitMonoFn_c_Comp_instIdx_U64_proto_Bool(Comp* c, uint64_t instIdx, long long proto);
void emitMonoFns_c_Comp_proto_Bool(Comp* c, long long proto);
void wPA_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
void genArrayTypedef_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
void genArrayRuntimeFns_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
long long isU8Elem_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
void genU8ArrayTypedef(void);
void genU8ArrayRuntime(void);
long long isPathTokKind_k_Kind(Kind k);
PlewArray_Bind collectParts_rootBytes_AU8_toks_ATok(PlewArray_U8 rootBytes, PlewArray_Tok toks);
uint64_t stripParents_path_AU8_baseLen_U64_n_U64(PlewArray_U8 path, uint64_t baseLen, uint64_t n);
PlewArray_U8 resolveImport_src_AU8_pStart_U64_pLen_U64_importer_AU8_baseLen_U64_srcRoot_AU8_srcRootLen_U64_stdRoot_AU8_stdRootLen_U64(PlewArray_U8 src, uint64_t pStart, uint64_t pLen, PlewArray_U8 importer, uint64_t baseLen, PlewArray_U8 srcRoot, uint64_t srcRootLen, PlewArray_U8 stdRoot, uint64_t stdRootLen);
void appendBytes_into_AU8_from_AU8(PlewArray_U8* into, PlewArray_U8 from);
PlewArray_U8 extractSpan_buf_AU8_start_U64_len_U64(PlewArray_U8 buf, uint64_t start, uint64_t len);
uint64_t dirPrefixLen_path_AU8(PlewArray_U8 path);
PlewArray_U8 computeStdRoot_arg0_AU8(PlewArray_U8 arg0);
PlewArray_U8 findSrcRoot_entry_AU8(PlewArray_U8 entry);
long long pathSeen_buf_AU8_loaded_ABind_path_AU8(PlewArray_U8 buf, PlewArray_Bind loaded, PlewArray_U8 path);
int main(int argc, char** argv) {
    plew_argc = argc; plew_argv = argv;
    PlewArray_U8 combined = PlewArray_U8_new();
    if (plew_arg_count() > 1) {
    PlewString rootPath = plew_arg_at((long long)(1));
    PlewArray_U8 entryBytes = PlewArray_U8_share(({ PlewString __s = rootPath; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    if (plew_file_exists(entryBytes)) {
    }
    else {
    plew_eprint((PlewString){"plewc: error: cannot open source file: ", 39});
    plew_eprint(rootPath);
    plew_eprint((PlewString){"\n", 1});
    exit((int)(1));
    }
    PlewArray_U8 pathBuf = PlewArray_U8_new();
    PlewArray_Bind loaded = PlewArray_Bind_new();
    PlewArray_U8 srcRoot = findSrcRoot_entry_AU8(PlewArray_U8_share(entryBytes));
    PlewArray_U8 stdRoot = computeStdRoot_arg0_AU8(PlewArray_U8_share(({ PlewString __s = plew_arg_at((long long)(0)); (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; })));
    uint64_t es = (long long)((pathBuf).len);
    appendBytes_into_AU8_from_AU8(&(pathBuf), PlewArray_U8_share(entryBytes));
    PlewArray_Bind_push(&(loaded), (Bind){.nameStart = es, .nameLen = (long long)((entryBytes).len), .fieldStart = es, .fieldLen = (long long)((entryBytes).len)});
    uint64_t qi = 0;
    while (qi < (long long)((loaded).len)) {
    Bind ent = PlewArray_Bind_get(loaded, (long long)(qi));
    qi = ({ uint64_t __ov; if (__builtin_add_overflow((qi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_U8 path = extractSpan_buf_AU8_start_U64_len_U64(PlewArray_U8_share(pathBuf), ent.nameStart, ent.nameLen);
    PlewString src = plew_read_file_bytes(path);
    PlewArray_U8 sb = PlewArray_U8_share(({ PlewString __s = src; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    if ((long long)((combined).len) > 0) {
    PlewArray_U8_push(&(combined), 10);
    }
    appendBytes_into_AU8_from_AU8(&(combined), PlewArray_U8_share(sb));
    Lexer lxp = (Lexer){.bytes = PlewArray_U8_share(sb), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0};
    lex_lx_Lexer(&(lxp));
    PlewArray_Bind incs = collectParts_rootBytes_AU8_toks_ATok(PlewArray_U8_share(sb), PlewArray_Tok_share(lxp.toks));
    uint64_t baseLen = dirPrefixLen_path_AU8(PlewArray_U8_share(path));
    uint64_t pj = 0;
    while (pj < (long long)((incs).len)) {
    Bind pb = PlewArray_Bind_get(incs, (long long)(pj));
    PlewArray_U8 childPath = resolveImport_src_AU8_pStart_U64_pLen_U64_importer_AU8_baseLen_U64_srcRoot_AU8_srcRootLen_U64_stdRoot_AU8_stdRootLen_U64(PlewArray_U8_share(sb), pb.nameStart, pb.nameLen, PlewArray_U8_share(path), baseLen, PlewArray_U8_share(srcRoot), (long long)((srcRoot).len), PlewArray_U8_share(stdRoot), (long long)((stdRoot).len));
    if ((long long)((childPath).len) == 0) {
    }
    else {
    if (pathSeen_buf_AU8_loaded_ABind_path_AU8(PlewArray_U8_share(pathBuf), PlewArray_Bind_share(loaded), PlewArray_U8_share(childPath))) {
    }
    else {
    uint64_t cs = (long long)((pathBuf).len);
    appendBytes_into_AU8_from_AU8(&(pathBuf), PlewArray_U8_share(childPath));
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
    appendBytes_into_AU8_from_AU8(&(combined), PlewArray_U8_share(({ PlewString __s = s; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; })));
    }
    appendBytes_into_AU8_from_AU8(&(combined), PlewArray_U8_share(({ PlewString __s = (PlewString){"\n// kwSpan builtins: String U8 Array\n", 37}; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; })));
    Lexer lx = (Lexer){.bytes = PlewArray_U8_share(combined), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0};
    lex_lx_Lexer(&(lx));
    Comp c = (Comp){.bytes = PlewArray_U8_share(combined), .toks = PlewArray_Tok_share(lx.toks), .pos = 0, .exprs = PlewArray_Expr_new(), .stmts = PlewArray_Stmt_new(), .blocks = PlewArray_Block_new(), .funcs = PlewArray_Func_new(), .structs = PlewArray_StructDef_new(), .enums = PlewArray_EnumDef_new(), .traits = PlewArray_TraitDef_new(), .conforms = PlewArray_Conform_new(), .methodAliases = PlewArray_MethodAlias_new(), .derives = PlewArray_DeriveReq_new(), .pendingDerives = PlewArray_Bind_new(), .funcBounds = PlewArray_FuncBound_new(), .curCheckFn = 0, .curWitnessed = PlewArray_Func_new(), .curWhereTraits = PlewArray_Bind_new(), .types = PlewArray_TypeRef_new(), .genInsts = PlewArray_U64_new(), .fnInsts = PlewArray_FnInst_new(), .fnTypes = PlewArray_U64_new(), .fnThunks = PlewArray_U64_new(), .captures = PlewArray_CaptureEntry_new(), .curClosureId = 0, .curInClosure = 0, .curCaptureMark = 0, .arrayElems = PlewArray_Bind_new(), .locals = PlewArray_Local_new(), .tmp = 0, .curIsMain = 0, .curRetVoid = 0, .curRetStart = 0, .curRetLen = 0, .curRetIsArray = 0, .curRetTy = 0, .curHasRecv = 0, .curRecvStart = 0, .curRecvLen = 0, .curSelfInout = 0, .curSelfMove = 0, .curTypeParams = PlewArray_Bind_new(), .curTypeArgs = PlewArray_U64_new(), .curRecvInstRef = 0, .curGiveTmp = 0, .curLoopMark = 0, .curBranchBase = 0, .impPrint = 0, .impWrite = 0, .impWriteByte = 0, .impReadStdin = 0, .impReadFile = 0, .impArgCount = 0, .impArgAt = 0, .impEprint = 0, .impExit = 0, .impReadFileBytes = 0, .impFileExists = 0, .deinits = PlewArray_Bind_new()};
    PlewArray_TypeRef_push(&(c.types), (TypeRef){.nameStart = 0, .nameLen = 0, .args = PlewArray_U64_new()});
    parseProgram_c_Comp(&(c));
    synthesizeDerives_c_Comp(&(c));
    instantiateProvidedMethods_c_Comp(&(c));
    checkFieldContagion_c_Comp(&(c));
    checkAllParamModes_c_Comp(&(c));
    checkArrayElemsNotUnique_c_Comp(&(c));
    checkConformances_c_Comp(&(c));
    checkOverloadCollisions_c_Comp(&(c));
    checkImplOnBuiltin_c_Comp(&(c));
    checkMoveFnReceivers_c_Comp(&(c));
    collectGenInsts_c_Comp(&(c));
    collectFnInsts_c_Comp(&(c));
    collectFnThunks_c_Comp(&(c));
    checkFnBounds_c_Comp(&(c));
    checkGenericBodies_c_Comp(&(c));
    checkGenericUniqueArgs_c_Comp(&(c));
    plew_write((PlewString){"#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n#include <string.h>\n", 79});
    plew_write((PlewString){"typedef struct { const char* data; long long len; } PlewString;\n", 64});
    plew_write((PlewString){"__attribute__((unused)) static void* plew_arc_alloc(long long bytes) { long long* p = (long long*)malloc(sizeof(long long) + (size_t)bytes); p[0] = 1; return (void*)(p + 1); }\n", 176});
    plew_write((PlewString){"__attribute__((unused)) static void plew_arc_retain(long long* rc) { if (rc) (*rc) += 1; }\n", 91});
    plew_write((PlewString){"__attribute__((unused)) static void plew_arc_release(long long* rc) { if (rc && (--(*rc)) == 0) free((void*)rc); }\n", 115});
    plew_write((PlewString){"__attribute__((unused)) static void* plew_ref_share(void* p) { if (p) ((long long*)p)[-1] += 1; return p; }\n", 108});
    plew_write((PlewString){"typedef struct { void* fn; void* env; long long* rc; void (*drop)(void*); } PlewClosure;\n", 89});
    plew_write((PlewString){"__attribute__((unused)) static PlewClosure plew_closure_share(PlewClosure cl) { plew_arc_retain(cl.rc); return cl; }\n", 117});
    plew_write((PlewString){"__attribute__((unused)) static void plew_closure_release(PlewClosure cl) { if (cl.rc && (--(*cl.rc)) == 0) { if (cl.drop) cl.drop(cl.env); free((void*)cl.rc); } }\n", 163});
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
    writeSpan_c_Comp_start_U64_len_U64(&(c), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&(c), s.nameStart, s.nameLen);
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
    writeSpan_c_Comp_start_U64_len_U64(&(c), e.nameStart, e.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&(c), e.nameStart, e.nameLen);
    plew_write((PlewString){";\n", 2});
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    uint64_t mfi = 0;
    while (mfi < (long long)((c.genInsts).len)) {
    emitMonoForward_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mfi)));
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genU8ArrayTypedef();
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_read_file_bytes(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; PlewString r = plew_read_file((PlewString){path, p.len}); free(path); return r; }\n", 264});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_file_exists(PlewArray_U8 p) { char* path = (char*)malloc((size_t)p.len + 1); memcpy(path, p.data, (size_t)p.len); path[p.len] = 0; FILE* f = fopen(path, \"rb\"); free(path); if (f) { fclose(f); return 1; } return 0; }\n", 262});
    uint64_t ai = 0;
    while (ai < (long long)((c.arrayElems).len)) {
    Bind ae = PlewArray_Bind_get(c.arrayElems, (long long)(ai));
    if (isU8Elem_c_Comp_elemStart_U64_elemLen_U64(&(c), ae.nameStart, ae.nameLen)) {
    }
    else {
    genArrayTypedef_c_Comp_elemStart_U64_elemLen_U64(&(c), ae.nameStart, ae.nameLen);
    }
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t ej = 0;
    while (ej < (long long)((c.enums).len)) {
    EnumDef ge = EnumDef_share(PlewArray_EnumDef_get(c.enums, (long long)(ej)));
    if ((long long)((ge.typeParams).len) > 0) {
    }
    else {
    genEnumDef_c_Comp_ei_U64(&(c), ej);
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
    genStructDef_c_Comp_si_U64(&(c), sj);
    }
    sj = ({ uint64_t __ov; if (__builtin_add_overflow((sj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(gs);
    }
    uint64_t mbi = 0;
    while (mbi < (long long)((c.genInsts).len)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mbi)))) {
    emitMonoEnum_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mbi)));
    }
    else {
    emitMonoStruct_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mbi)));
    }
    mbi = ({ uint64_t __ov; if (__builtin_add_overflow((mbi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    emitDeinitProtos_c_Comp(&(c));
    uint64_t spp = 0;
    while (spp < (long long)((c.structs).len)) {
    StructDef cps = StructDef_share(PlewArray_StructDef_get(c.structs, (long long)(spp)));
    if ((long long)((cps.typeParams).len) > 0) {
    }
    else {
    if (cps.isUnique) {
    }
    else {
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&(c), cps.nameStart, cps.nameLen)) {
    emitStructCopyProto_c_Comp_si_U64(&(c), spp);
    emitStructShareProto_c_Comp_si_U64(&(c), spp);
    }
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&(c), cps.nameStart, cps.nameLen)) {
    emitStructReleaseProto_c_Comp_si_U64(&(c), spp);
    }
    }
    spp = ({ uint64_t __ov; if (__builtin_add_overflow((spp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(cps);
    }
    genU8ArrayRuntime();
    uint64_t ar = 0;
    while (ar < (long long)((c.arrayElems).len)) {
    Bind ae2 = PlewArray_Bind_get(c.arrayElems, (long long)(ar));
    if (isU8Elem_c_Comp_elemStart_U64_elemLen_U64(&(c), ae2.nameStart, ae2.nameLen)) {
    }
    else {
    genArrayRuntimeFns_c_Comp_elemStart_U64_elemLen_U64(&(c), ae2.nameStart, ae2.nameLen);
    }
    ar = ({ uint64_t __ov; if (__builtin_add_overflow((ar), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t scd = 0;
    while (scd < (long long)((c.structs).len)) {
    StructDef cs2 = StructDef_share(PlewArray_StructDef_get(c.structs, (long long)(scd)));
    if ((long long)((cs2.typeParams).len) > 0) {
    }
    else {
    if (cs2.isUnique) {
    }
    else {
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&(c), cs2.nameStart, cs2.nameLen)) {
    emitStructCopyDef_c_Comp_si_U64(&(c), scd);
    emitStructShareDef_c_Comp_si_U64(&(c), scd);
    }
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&(c), cs2.nameStart, cs2.nameLen)) {
    emitStructReleaseDef_c_Comp_si_U64(&(c), scd);
    }
    }
    scd = ({ uint64_t __ov; if (__builtin_add_overflow((scd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(cs2);
    }
    uint64_t mcp = 0;
    while (mcp < (long long)((c.genInsts).len)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)))) {
    if (monoEnumNeedsCopy_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)))) {
    emitMonoEnumCopyProto_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)));
    }
    }
    else {
    if (monoStructNeedsCopy_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)))) {
    emitMonoStructCopyProto_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcp)));
    }
    }
    mcp = ({ uint64_t __ov; if (__builtin_add_overflow((mcp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t mcd = 0;
    while (mcd < (long long)((c.genInsts).len)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)))) {
    if (monoEnumNeedsCopy_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)))) {
    emitMonoEnumCopyDef_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)));
    }
    }
    else {
    if (monoStructNeedsCopy_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)))) {
    emitMonoStructCopyDef_c_Comp_instRef_U64(&(c), PlewArray_U64_get(c.genInsts, (long long)(mcd)));
    }
    }
    mcd = ({ uint64_t __ov; if (__builtin_add_overflow((mcd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    emitClosureEnvs_c_Comp(&(c));
    uint64_t i = 0;
    while (i < (long long)((c.funcs).len)) {
    Func f = Func_share(PlewArray_Func_get(c.funcs, (long long)(i)));
    if (nameIsMain_c_Comp_f_Func(&(c), f)) {
    }
    else {
    if ((long long)((f.typeParams).len) > 0) {
    }
    else {
    if (methodRecvIsTrait_c_Comp_f_Func(&(c), f)) {
    }
    else {
    genSignature_c_Comp_f_Func(&(c), f);
    plew_write((PlewString){";\n", 2});
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    emitMonoMethods_c_Comp_proto_Bool(&(c), 1);
    emitMonoFns_c_Comp_proto_Bool(&(c), 1);
    emitThunks_c_Comp_proto_Bool(&(c), 1);
    emitClosures_c_Comp_proto_Bool(&(c), 1);
    {
    long long __fe0 = (long long)((c.funcs).len);
    for (long long j = 0; j < __fe0; j++) {
    Func fb = Func_share(PlewArray_Func_get(c.funcs, (long long)(j)));
    if ((long long)((fb.typeParams).len) > 0) {
    }
    else {
    if (methodRecvIsTrait_c_Comp_f_Func(&(c), fb)) {
    }
    else {
    genFunc_c_Comp_fi_U64(&(c), j);
    }
    }
    Func_release(fb);
    }
    }
    emitMonoMethods_c_Comp_proto_Bool(&(c), 0);
    emitMonoFns_c_Comp_proto_Bool(&(c), 0);
    emitThunks_c_Comp_proto_Bool(&(c), 0);
    emitClosures_c_Comp_proto_Bool(&(c), 0);
    Comp_release(c);
    Lexer_release(lx);
    PlewArray_U8_release(combined);
    return 0;
}
unsigned char Lexer_at_off_U64(Lexer self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow((self.pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)((self.bytes).len)) {
    { unsigned char __ret1 = PlewArray_U8_get(self.bytes, (long long)(i));
    return __ret1; }
    }
    { unsigned char __ret2 = 0;
    return __ret2; }
}
void Lexer_emit_k_Kind_start_U64_len_U64(Lexer* self, Kind k, uint64_t start, uint64_t len) {
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
    { long long __ret7 = ({ long long __mr8; Kind __ms8 = t.kind; if (__ms8.tag == 5) { __mr8 = (1); } else if (__ms8.tag == 2) { __mr8 = (1); } else if (__ms8.tag == 3) { __mr8 = (1); } else if (__ms8.tag == 4) { __mr8 = (1); } else if (__ms8.tag == 30) { __mr8 = (1); } else if (__ms8.tag == 32) { __mr8 = (1); } else if (__ms8.tag == 34) { __mr8 = (1); } else if (__ms8.tag == 61) { __mr8 = (1); } else if (__ms8.tag == 27) { __mr8 = (1); } else if (__ms8.tag == 28) { __mr8 = (1); } else if (__ms8.tag == 16) { __mr8 = (1); } else if (__ms8.tag == 14) { __mr8 = (1); } else if (__ms8.tag == 15) { __mr8 = (1); } else { __mr8 = (0); } __mr8; });
    return __ret7; }
}
long long isDigit_b_U8(unsigned char b) {
    if (b >= 48) {
    if (b <= 57) {
    { long long __ret9 = 1;
    return __ret9; }
    }
    }
    { long long __ret10 = 0;
    return __ret10; }
}
long long isAlpha_b_U8(unsigned char b) {
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
long long isAlnum_b_U8(unsigned char b) {
    if (isAlpha_b_U8(b)) {
    { long long __ret15 = 1;
    return __ret15; }
    }
    { long long __ret16 = isDigit_b_U8(b);
    return __ret16; }
}
long long rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8 bytes, uint64_t start, uint64_t len, PlewString kw) {
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
Kind identKind_bytes_AU8_start_U64_len_U64(PlewArray_U8 bytes, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"fn", 2})) {
    { Kind __ret20 = (Kind){.tag = 6};
    return __ret20; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"struct", 6})) {
    { Kind __ret21 = (Kind){.tag = 7};
    return __ret21; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"enum", 4})) {
    { Kind __ret22 = (Kind){.tag = 8};
    return __ret22; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"match", 5})) {
    { Kind __ret23 = (Kind){.tag = 9};
    return __ret23; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"if", 2})) {
    { Kind __ret24 = (Kind){.tag = 10};
    return __ret24; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"else", 4})) {
    { Kind __ret25 = (Kind){.tag = 11};
    return __ret25; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"while", 5})) {
    { Kind __ret26 = (Kind){.tag = 12};
    return __ret26; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"for", 3})) {
    { Kind __ret27 = (Kind){.tag = 13};
    return __ret27; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"break", 5})) {
    { Kind __ret28 = (Kind){.tag = 14};
    return __ret28; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"continue", 8})) {
    { Kind __ret29 = (Kind){.tag = 15};
    return __ret29; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"return", 6})) {
    { Kind __ret30 = (Kind){.tag = 16};
    return __ret30; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"give", 4})) {
    { Kind __ret31 = (Kind){.tag = 17};
    return __ret31; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"val", 3})) {
    { Kind __ret32 = (Kind){.tag = 18};
    return __ret32; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"mut", 3})) {
    { Kind __ret33 = (Kind){.tag = 19};
    return __ret33; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"in", 2})) {
    { Kind __ret34 = (Kind){.tag = 20};
    return __ret34; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"as", 2})) {
    { Kind __ret35 = (Kind){.tag = 21};
    return __ret35; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"inout", 5})) {
    { Kind __ret36 = (Kind){.tag = 22};
    return __ret36; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"unique", 6})) {
    { Kind __ret37 = (Kind){.tag = 23};
    return __ret37; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"deinit", 6})) {
    { Kind __ret38 = (Kind){.tag = 24};
    return __ret38; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"move", 4})) {
    { Kind __ret39 = (Kind){.tag = 25};
    return __ret39; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"borrow", 6})) {
    { Kind __ret40 = (Kind){.tag = 26};
    return __ret40; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"true", 4})) {
    { Kind __ret41 = (Kind){.tag = 27};
    return __ret41; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(bytes), start, len, (PlewString){"false", 5})) {
    { Kind __ret42 = (Kind){.tag = 28};
    return __ret42; }
    }
    { Kind __ret43 = (Kind){.tag = 5};
    return __ret43; }
}
void lex_lx_Lexer(Lexer* lx) {
    while ((*lx).pos < (long long)(((*lx).bytes).len)) {
    unsigned char b = Lexer_at_off_U64((*lx), 0);
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
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 1}, (*lx).pos, 1);
    }
    }
    else {
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    continue;
    }
    if (b == 47) {
    if (Lexer_at_off_U64((*lx), 1) == 47) {
    while ((*lx).pos < (long long)(((*lx).bytes).len)) {
    if (Lexer_at_off_U64((*lx), 0) == 10) {
    break;
    }
    (*lx).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    continue;
    }
    }
    if (isDigit_b_U8(b)) {
    uint64_t start = (*lx).pos;
    uint64_t j = (*lx).pos;
    while (j < (long long)(((*lx).bytes).len)) {
    if (isDigit_b_U8(PlewArray_U8_get((*lx).bytes, (long long)(j)))) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    break;
    }
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 2}, start, ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    continue;
    }
    if (isAlpha_b_U8(b)) {
    uint64_t start = (*lx).pos;
    uint64_t j = (*lx).pos;
    while (j < (long long)(((*lx).bytes).len)) {
    if (isAlnum_b_U8(PlewArray_U8_get((*lx).bytes, (long long)(j)))) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    break;
    }
    }
    uint64_t len = ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Kind k = identKind_bytes_AU8_start_U64_len_U64(PlewArray_U8_share((*lx).bytes), start, len);
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), k, start, len);
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
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 3}, start, ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
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
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 4}, start, ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    continue;
    }
    unsigned char b2 = Lexer_at_off_U64((*lx), 1);
    if (b == 46) {
    if (b2 == 46) {
    unsigned char b3 = Lexer_at_off_U64((*lx), 2);
    if (b3 == 60) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 72}, (*lx).pos, 3);
    continue;
    }
    if (b3 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 73}, (*lx).pos, 3);
    continue;
    }
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 37}, (*lx).pos, 1);
    continue;
    }
    if (b == 61) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 39}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 60}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 38}, (*lx).pos, 1);
    continue;
    }
    if (b == 33) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 40}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 52}, (*lx).pos, 1);
    continue;
    }
    if (b == 60) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 42}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 60) {
    unsigned char b3 = Lexer_at_off_U64((*lx), 2);
    if (b3 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 70}, (*lx).pos, 3);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 56}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 41}, (*lx).pos, 1);
    continue;
    }
    if (b == 62) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 44}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    unsigned char b3 = Lexer_at_off_U64((*lx), 2);
    if (b3 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 71}, (*lx).pos, 3);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 57}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 43}, (*lx).pos, 1);
    continue;
    }
    if (b == 43) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 62}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 45}, (*lx).pos, 1);
    continue;
    }
    if (b == 45) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 63}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 59}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 46}, (*lx).pos, 1);
    continue;
    }
    if (b == 42) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 64}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 47}, (*lx).pos, 1);
    continue;
    }
    if (b == 47) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 65}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 61}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 48}, (*lx).pos, 1);
    continue;
    }
    if (b == 37) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 66}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 49}, (*lx).pos, 1);
    continue;
    }
    if (b == 38) {
    if (b2 == 38) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 50}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 67}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 53}, (*lx).pos, 1);
    continue;
    }
    if (b == 124) {
    if (b2 == 124) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 51}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 68}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 54}, (*lx).pos, 1);
    continue;
    }
    if (b == 94) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 69}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 55}, (*lx).pos, 1);
    continue;
    }
    if (b == 126) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 58}, (*lx).pos, 1);
    continue;
    }
    if (b == 63) {
    if (b2 == 63) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 74}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 75}, (*lx).pos, 1);
    continue;
    }
    if (b == 40) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 29}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_add_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 41) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 30}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_sub_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 91) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 31}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_add_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 93) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 32}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_sub_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 123) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 33}, (*lx).pos, 1);
    continue;
    }
    if (b == 125) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 34}, (*lx).pos, 1);
    continue;
    }
    if (b == 44) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 35}, (*lx).pos, 1);
    continue;
    }
    if (b == 58) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 36}, (*lx).pos, 1);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 75}, (*lx).pos, 1);
    }
    PlewArray_Tok_push(&((*lx).toks), (Tok){.kind = (Kind){.tag = 0}, .start = (*lx).pos, .len = 0});
}
int64_t kindCode_k_Kind(Kind k) {
    { int64_t __ret44 = ({ long long __mr45; Kind __ms45 = k; if (__ms45.tag == 0) { __mr45 = (0); } else if (__ms45.tag == 1) { __mr45 = (1); } else if (__ms45.tag == 2) { __mr45 = (2); } else if (__ms45.tag == 3) { __mr45 = (3); } else if (__ms45.tag == 4) { __mr45 = (5); } else if (__ms45.tag == 5) { __mr45 = (4); } else if (__ms45.tag == 6) { __mr45 = (10); } else if (__ms45.tag == 7) { __mr45 = (11); } else if (__ms45.tag == 8) { __mr45 = (12); } else if (__ms45.tag == 9) { __mr45 = (13); } else if (__ms45.tag == 10) { __mr45 = (14); } else if (__ms45.tag == 11) { __mr45 = (15); } else if (__ms45.tag == 12) { __mr45 = (16); } else if (__ms45.tag == 13) { __mr45 = (17); } else if (__ms45.tag == 14) { __mr45 = (18); } else if (__ms45.tag == 15) { __mr45 = (19); } else if (__ms45.tag == 16) { __mr45 = (20); } else if (__ms45.tag == 17) { __mr45 = (21); } else if (__ms45.tag == 18) { __mr45 = (22); } else if (__ms45.tag == 19) { __mr45 = (23); } else if (__ms45.tag == 20) { __mr45 = (24); } else if (__ms45.tag == 21) { __mr45 = (25); } else if (__ms45.tag == 22) { __mr45 = (26); } else if (__ms45.tag == 23) { __mr45 = (29); } else if (__ms45.tag == 24) { __mr45 = (30); } else if (__ms45.tag == 25) { __mr45 = (31); } else if (__ms45.tag == 26) { __mr45 = (32); } else if (__ms45.tag == 27) { __mr45 = (27); } else if (__ms45.tag == 28) { __mr45 = (28); } else if (__ms45.tag == 29) { __mr45 = (40); } else if (__ms45.tag == 30) { __mr45 = (41); } else if (__ms45.tag == 31) { __mr45 = (42); } else if (__ms45.tag == 32) { __mr45 = (43); } else if (__ms45.tag == 33) { __mr45 = (44); } else if (__ms45.tag == 34) { __mr45 = (45); } else if (__ms45.tag == 35) { __mr45 = (46); } else if (__ms45.tag == 36) { __mr45 = (47); } else if (__ms45.tag == 37) { __mr45 = (48); } else if (__ms45.tag == 38) { __mr45 = (49); } else if (__ms45.tag == 39) { __mr45 = (50); } else if (__ms45.tag == 40) { __mr45 = (51); } else if (__ms45.tag == 41) { __mr45 = (52); } else if (__ms45.tag == 42) { __mr45 = (53); } else if (__ms45.tag == 43) { __mr45 = (54); } else if (__ms45.tag == 44) { __mr45 = (55); } else if (__ms45.tag == 45) { __mr45 = (56); } else if (__ms45.tag == 46) { __mr45 = (57); } else if (__ms45.tag == 47) { __mr45 = (58); } else if (__ms45.tag == 48) { __mr45 = (59); } else if (__ms45.tag == 49) { __mr45 = (60); } else if (__ms45.tag == 50) { __mr45 = (61); } else if (__ms45.tag == 51) { __mr45 = (62); } else if (__ms45.tag == 52) { __mr45 = (63); } else if (__ms45.tag == 59) { __mr45 = (64); } else if (__ms45.tag == 60) { __mr45 = (65); } else if (__ms45.tag == 61) { __mr45 = (66); } else if (__ms45.tag == 62) { __mr45 = (67); } else if (__ms45.tag == 63) { __mr45 = (68); } else if (__ms45.tag == 64) { __mr45 = (69); } else if (__ms45.tag == 65) { __mr45 = (70); } else if (__ms45.tag == 66) { __mr45 = (71); } else if (__ms45.tag == 72) { __mr45 = (72); } else if (__ms45.tag == 73) { __mr45 = (73); } else if (__ms45.tag == 53) { __mr45 = (74); } else if (__ms45.tag == 54) { __mr45 = (75); } else if (__ms45.tag == 55) { __mr45 = (76); } else if (__ms45.tag == 56) { __mr45 = (77); } else if (__ms45.tag == 57) { __mr45 = (78); } else if (__ms45.tag == 58) { __mr45 = (79); } else if (__ms45.tag == 67) { __mr45 = (80); } else if (__ms45.tag == 68) { __mr45 = (81); } else if (__ms45.tag == 69) { __mr45 = (82); } else if (__ms45.tag == 70) { __mr45 = (83); } else if (__ms45.tag == 71) { __mr45 = (84); } else if (__ms45.tag == 74) { __mr45 = (85); } else if (__ms45.tag == 75) { __mr45 = (99); } else { __builtin_unreachable(); } __mr45; });
    return __ret44; }
}
Kind Comp_curKind(Comp* self) {
    { Kind __ret46 = PlewArray_Tok_get((*self).toks, (long long)((*self).pos)).kind;
    return __ret46; }
}
Tok Comp_cur(Comp* self) {
    { Tok __ret47 = PlewArray_Tok_get((*self).toks, (long long)((*self).pos));
    return __ret47; }
}
Kind Comp_peekKind_off_U64(Comp* self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)(((*self).toks).len)) {
    { Kind __ret48 = PlewArray_Tok_get((*self).toks, (long long)(i)).kind;
    return __ret48; }
    }
    { Kind __ret49 = (Kind){.tag = 0};
    return __ret49; }
}
void Comp_advance(Comp* self) {
    (*self).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
}
void Comp_skipNewlines(Comp* self) {
    while (1) {
    {
    Kind _m50 = Comp_curKind(&((*self)));
    if (_m50.tag == 1) {
    Comp_advance(&((*self)));
    }
    else {
    break;
    }
    }
    }
}
long long Comp_identIs_kw_String(Comp* self, PlewString kw) {
    Tok t = PlewArray_Tok_get((*self).toks, (long long)((*self).pos));
    { long long __ret51 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*self).bytes), t.start, t.len, kw);
    return __ret51; }
}
uint64_t Comp_pushExpr_e_Expr(Comp* self, Expr e) {
    uint64_t id = (long long)(((*self).exprs).len);
    PlewArray_Expr_push(&((*self).exprs), e);
    { uint64_t __ret52 = id;
    return __ret52; }
}
uint64_t Comp_pushStmt_s_Stmt(Comp* self, Stmt s) {
    uint64_t id = (long long)(((*self).stmts).len);
    PlewArray_Stmt_push(&((*self).stmts), s);
    { uint64_t __ret53 = id;
    return __ret53; }
}
uint64_t Comp_pushType_t_TypeRef(Comp* self, TypeRef t) {
    uint64_t id = (long long)(((*self).types).len);
    PlewArray_TypeRef_push(&((*self).types), t);
    { uint64_t __ret54 = id;
    return __ret54; }
}
int64_t Comp_tokenValue_t_Tok(Comp* self, Tok t) {
    int64_t v = 0;
    uint64_t j = 0;
    while (j < t.len) {
    unsigned char b = PlewArray_U8_get((*self).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((t.start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    v = ({ int64_t __ov; if (__builtin_add_overflow((({ int64_t __ov; if (__builtin_mul_overflow((v), (10), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), (({ int64_t __ov; if (__builtin_sub_overflow((((int64_t)(b))), (48), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { int64_t __ret55 = v;
    return __ret55; }
}
int64_t binPrec_k_Kind(Kind k) {
    { int64_t __ret56 = ({ long long __mr57; Kind __ms57 = k; if (__ms57.tag == 51) { __mr57 = (1); } else if (__ms57.tag == 50) { __mr57 = (2); } else if (__ms57.tag == 39) { __mr57 = (3); } else if (__ms57.tag == 40) { __mr57 = (3); } else if (__ms57.tag == 41) { __mr57 = (3); } else if (__ms57.tag == 42) { __mr57 = (3); } else if (__ms57.tag == 43) { __mr57 = (3); } else if (__ms57.tag == 44) { __mr57 = (3); } else if (__ms57.tag == 74) { __mr57 = (4); } else if (__ms57.tag == 54) { __mr57 = (5); } else if (__ms57.tag == 55) { __mr57 = (6); } else if (__ms57.tag == 53) { __mr57 = (7); } else if (__ms57.tag == 56) { __mr57 = (8); } else if (__ms57.tag == 57) { __mr57 = (8); } else if (__ms57.tag == 45) { __mr57 = (9); } else if (__ms57.tag == 46) { __mr57 = (9); } else if (__ms57.tag == 47) { __mr57 = (10); } else if (__ms57.tag == 48) { __mr57 = (10); } else if (__ms57.tag == 49) { __mr57 = (10); } else { __mr57 = (0); } __mr57; });
    return __ret56; }
}
int64_t charValue_c_Comp_t_Tok(Comp* c, Tok t) {
    uint64_t contentLen = ({ uint64_t __ov; if (__builtin_sub_overflow((t.len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (contentLen == 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"empty character literal", 23});
    }
    uint64_t p = ({ uint64_t __ov; if (__builtin_add_overflow((t.start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    unsigned char b0 = PlewArray_U8_get((*c).bytes, (long long)(p));
    if (b0 == 92) {
    if (contentLen != 2) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"character literal must be a single scalar", 41});
    }
    unsigned char e = PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    if (e == 110) {
    { int64_t __ret58 = 10;
    return __ret58; }
    }
    if (e == 116) {
    { int64_t __ret59 = 9;
    return __ret59; }
    }
    if (e == 114) {
    { int64_t __ret60 = 13;
    return __ret60; }
    }
    if (e == 48) {
    { int64_t __ret61 = 0;
    return __ret61; }
    }
    { int64_t __ret62 = e;
    return __ret62; }
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
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"multi-scalar character literal (Grapheme) is not yet supported", 62});
    }
    { int64_t __ret63 = value;
    return __ret63; }
}
uint64_t parsePrimary_c_Comp(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m64 = k;
    if (_m64.tag == 2) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    int64_t v = Comp_tokenValue_t_Tok(&((*c)), t);
    uint64_t sStart = 0;
    uint64_t sLen = 0;
    {
    Kind _m65 = Comp_curKind(&((*c)));
    if (_m65.tag == 5) {
    Tok st = Comp_cur(&((*c)));
    if (st.start == ({ uint64_t __ov; if (__builtin_add_overflow((t.start), (t.len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), st.start, st.len)) {
    sStart = st.start;
    sLen = st.len;
    Comp_advance(&((*c)));
    }
    }
    }
    else {
    }
    }
    { uint64_t __ret66 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = sStart, .tyLen = sLen}});
    return __ret66; }
    }
    else if (_m64.tag == 4) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    int64_t v = charValue_c_Comp_t_Tok(&((*c)), t);
    { uint64_t __ret67 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    return __ret67; }
    }
    else if (_m64.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    {
    Kind _m68 = Comp_peekKind_off_U64(&((*c)), 1);
    if (_m68.tag == 29) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Arg args = parseCallArgs_c_Comp(&((*c)));
    { uint64_t __ret69 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 4, .data.Call = {.nameStart = t.start, .nameLen = t.len, .args = PlewArray_Arg_share(args)}});
    PlewArray_Arg_release(args);
    return __ret69; }
    PlewArray_Arg_release(args);
    }
    else {
    Comp_advance(&((*c)));
    { uint64_t __ret70 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = t.start, .len = t.len}});
    return __ret70; }
    }
    }
    }
    else if (_m64.tag == 27) {
    Tok tt = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret71 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 1, .offset = tt.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret71; }
    }
    else if (_m64.tag == 28) {
    Tok tf = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret72 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = tf.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret72; }
    }
    else if (_m64.tag == 29) {
    Comp_advance(&((*c)));
    uint64_t inner = parseExpr_c_Comp(&((*c)));
    {
    Kind _m73 = Comp_curKind(&((*c)));
    if (_m73.tag == 30) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    { uint64_t __ret74 = inner;
    return __ret74; }
    }
    else if (_m64.tag == 6) {
    Comp_advance(&((*c)));
    PlewArray_Param params = parseParamList_c_Comp(&((*c)));
    long long hasRet = 0;
    uint64_t retStart = 0;
    uint64_t retLen = 0;
    long long retIsArray = 0;
    uint64_t retRef = 0;
    {
    Kind _m75 = Comp_curKind(&((*c)));
    if (_m75.tag == 59) {
    Comp_advance(&((*c)));
    hasRet = 1;
    PType rty = parseTypeTok_c_Comp(&((*c)));
    retStart = rty.start;
    retLen = rty.len;
    retIsArray = rty.isArray;
    retRef = rty.ref;
    recordArrayElem_c_Comp_ty_PType(&((*c)), rty);
    }
    else {
    }
    }
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret76 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 17, .data.Closure = {.params = PlewArray_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body}});
    PlewArray_Param_release(params);
    return __ret76; }
    PlewArray_Param_release(params);
    }
    else if (_m64.tag == 41) {
    { uint64_t __ret77 = parseMake_c_Comp(&((*c)));
    return __ret77; }
    }
    else if (_m64.tag == 9) {
    { uint64_t __ret78 = parseMatchExpr_c_Comp(&((*c)));
    return __ret78; }
    }
    else if (_m64.tag == 10) {
    { uint64_t __ret79 = parseIfExpr_c_Comp(&((*c)));
    return __ret79; }
    }
    else if (_m64.tag == 3) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret80 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 7, .data.Str = {.start = t.start, .len = t.len}});
    return __ret80; }
    }
    else if (_m64.tag == 31) {
    Comp_advance(&((*c)));
    PlewArray_U64 elems = PlewArray_U64_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m81 = Comp_curKind(&((*c)));
    if (_m81.tag == 32) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m81.tag == 0) {
    break;
    }
    else {
    uint64_t e = parseExpr_c_Comp(&((*c)));
    PlewArray_U64_push(&(elems), e);
    {
    Kind _m82 = Comp_curKind(&((*c)));
    if (_m82.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    { uint64_t __ret83 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 8, .data.Array = {.elems = PlewArray_U64_share(elems)}});
    PlewArray_U64_release(elems);
    return __ret83; }
    PlewArray_U64_release(elems);
    }
    else {
    Tok te = Comp_cur(&((*c)));
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), te.start), (PlewString){"expected an expression", 22});
    Comp_advance(&((*c)));
    { uint64_t __ret84 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = te.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    return __ret84; }
    }
    }
}
uint64_t parseUnary_c_Comp(Comp* c) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"try", 3})) {
    Comp_advance(&((*c)));
    uint64_t inner = parsePostfix_c_Comp(&((*c)));
    { uint64_t __ret85 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 15, .data.Try = {.expr = inner}});
    return __ret85; }
    }
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m86 = k;
    if (_m86.tag == 25) {
    Comp_advance(&((*c)));
    uint64_t o = parsePostfix_c_Comp(&((*c)));
    { uint64_t __ret87 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 18, .data.Move = {.operand = o, .isBorrow = 0}});
    return __ret87; }
    }
    else if (_m86.tag == 26) {
    Comp_advance(&((*c)));
    uint64_t o = parsePostfix_c_Comp(&((*c)));
    { uint64_t __ret88 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 18, .data.Move = {.operand = o, .isBorrow = 1}});
    return __ret88; }
    }
    else if (_m86.tag == 46) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary_c_Comp(&((*c)));
    { uint64_t __ret89 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 57, .operand = o}});
    return __ret89; }
    }
    else if (_m86.tag == 52) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary_c_Comp(&((*c)));
    { uint64_t __ret90 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 63, .operand = o}});
    return __ret90; }
    }
    else if (_m86.tag == 58) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary_c_Comp(&((*c)));
    { uint64_t __ret91 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 79, .operand = o}});
    return __ret91; }
    }
    else {
    { uint64_t __ret92 = parsePostfix_c_Comp(&((*c)));
    return __ret92; }
    }
    }
}
uint64_t parsePostfix_c_Comp(Comp* c) {
    uint64_t e = parsePrimary_c_Comp(&((*c)));
    while (1) {
    {
    Kind _m93 = Comp_curKind(&((*c)));
    if (_m93.tag == 37) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m94 = Comp_curKind(&((*c)));
    if (_m94.tag == 29) {
    Comp_advance(&((*c)));
    PlewArray_Arg args = parseCallArgs_c_Comp(&((*c)));
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 10, .data.Method = {.recv = e, .nameStart = nameTok.start, .nameLen = nameTok.len, .args = PlewArray_Arg_share(args)}});
    PlewArray_Arg_release(args);
    }
    else {
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    }
    }
    else if (_m93.tag == 31) {
    Comp_advance(&((*c)));
    uint64_t idx = parseExpr_c_Comp(&((*c)));
    {
    Kind _m95 = Comp_curKind(&((*c)));
    if (_m95.tag == 32) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 9, .data.Index = {.base = e, .index = idx}});
    }
    else if (_m93.tag == 59) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 16, .data.Arrow = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    else if (_m93.tag == 21) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok_c_Comp(&((*c)));
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 11, .data.Cast = {.operand = e, .tyStart = ty.start, .tyLen = ty.len, .ty = ty.ref}});
    }
    else {
    break;
    }
    }
    }
    { uint64_t __ret96 = e;
    return __ret96; }
}
uint64_t parseMake_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    Tok typeTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyRef = 0;
    {
    Kind _m97 = Comp_curKind(&((*c)));
    if (_m97.tag == 31) {
    Comp_advance(&((*c)));
    PlewArray_U64 targs = PlewArray_U64_new();
    long long first = 1;
    while (1) {
    {
    Kind _m98 = Comp_curKind(&((*c)));
    if (_m98.tag == 32) {
    break;
    }
    else if (_m98.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m99 = Comp_curKind(&((*c)));
    if (_m99.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    first = 0;
    PType arg = parseTypeTok_c_Comp(&((*c)));
    PlewArray_U64_push(&(targs), arg.ref);
    }
    {
    Kind _m100 = Comp_curKind(&((*c)));
    if (_m100.tag == 32) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    tyRef = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = typeTok.start, .nameLen = typeTok.len, .args = PlewArray_U64_share(targs)});
    PlewArray_U64_release(targs);
    }
    else {
    }
    }
    uint64_t variantStart = 0;
    uint64_t variantLen = 0;
    long long isEnum = 0;
    {
    Kind _m101 = Comp_curKind(&((*c)));
    if (_m101.tag == 37) {
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
    Kind _m102 = k;
    if (_m102.tag == 61) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m102.tag == 43) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m102.tag == 0) {
    break;
    }
    else if (_m102.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m103 = Comp_curKind(&((*c)));
    if (_m103.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t v = parseExpr_c_Comp(&((*c)));
    PlewArray_MakeField_push(&(fields), (MakeField){.nameStart = fTok.start, .nameLen = fTok.len, .value = v});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    { uint64_t __ret104 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 6, .data.Make = {.typeStart = typeTok.start, .typeLen = typeTok.len, .variantStart = variantStart, .variantLen = variantLen, .isEnum = isEnum, .ty = tyRef, .fields = PlewArray_MakeField_share(fields)}});
    PlewArray_MakeField_release(fields);
    return __ret104; }
    PlewArray_MakeField_release(fields);
}
uint64_t parseBin_c_Comp_minPrec_I64(Comp* c, int64_t minPrec) {
    uint64_t left = parseUnary_c_Comp(&((*c)));
    while (1) {
    Kind k = Comp_curKind(&((*c)));
    int64_t prec = binPrec_k_Kind(k);
    if (prec == 0) {
    break;
    }
    if (prec < minPrec) {
    break;
    }
    {
    Kind _m105 = k;
    if (_m105.tag == 74) {
    Comp_advance(&((*c)));
    uint64_t rhs = parseBin_c_Comp_minPrec_I64(&((*c)), prec);
    left = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 14, .data.Coalesce = {.opt = left, .deflt = rhs}});
    }
    else {
    int64_t op = kindCode_k_Kind(k);
    Comp_advance(&((*c)));
    uint64_t right = parseBin_c_Comp_minPrec_I64(&((*c)), ({ int64_t __ov; if (__builtin_add_overflow((prec), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    left = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = op, .lhs = left, .rhs = right}});
    if (prec == 3) {
    if (binPrec_k_Kind(Comp_curKind(&((*c)))) == 3) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"comparison operators are non-associative; add parentheses (e.g. `(a < b) && (b < c)`)", 85});
    }
    }
    }
    }
    }
    { uint64_t __ret106 = left;
    return __ret106; }
}
uint64_t parseExpr_c_Comp(Comp* c) {
    { uint64_t __ret107 = parseBin_c_Comp_minPrec_I64(&((*c)), 1);
    return __ret107; }
}
PlewArray_Arg parseCallArgs_c_Comp(Comp* c) {
    PlewArray_Arg args = PlewArray_Arg_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m108 = k;
    if (_m108.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m108.tag == 0) {
    break;
    }
    else {
    uint64_t labelStart = 0;
    uint64_t labelLen = 0;
    long long hasLabel = 0;
    {
    Kind _m109 = Comp_curKind(&((*c)));
    if (_m109.tag == 5) {
    {
    Kind _m110 = Comp_peekKind_off_U64(&((*c)), 1);
    if (_m110.tag == 36) {
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
    Kind _m111 = Comp_curKind(&((*c)));
    if (_m111.tag == 22) {
    Comp_advance(&((*c)));
    isInout = 1;
    }
    else {
    }
    }
    uint64_t e = parseExpr_c_Comp(&((*c)));
    PlewArray_Arg_push(&(args), (Arg){.expr = e, .isInout = isInout, .labelStart = labelStart, .labelLen = labelLen, .hasLabel = hasLabel});
    {
    Kind _m112 = Comp_curKind(&((*c)));
    if (_m112.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    { PlewArray_Arg __ret113 = PlewArray_Arg_share(args);
    PlewArray_Arg_release(args);
    return __ret113; }
    PlewArray_Arg_release(args);
}
long long isAssignOp_k_Kind(Kind k) {
    {
    Kind _m114 = k;
    if (_m114.tag == 38) {
    { long long __ret115 = 1;
    return __ret115; }
    }
    else if (_m114.tag == 62) {
    { long long __ret116 = 1;
    return __ret116; }
    }
    else if (_m114.tag == 63) {
    { long long __ret117 = 1;
    return __ret117; }
    }
    else if (_m114.tag == 64) {
    { long long __ret118 = 1;
    return __ret118; }
    }
    else if (_m114.tag == 65) {
    { long long __ret119 = 1;
    return __ret119; }
    }
    else if (_m114.tag == 66) {
    { long long __ret120 = 1;
    return __ret120; }
    }
    else if (_m114.tag == 67) {
    { long long __ret121 = 1;
    return __ret121; }
    }
    else if (_m114.tag == 68) {
    { long long __ret122 = 1;
    return __ret122; }
    }
    else if (_m114.tag == 69) {
    { long long __ret123 = 1;
    return __ret123; }
    }
    else if (_m114.tag == 70) {
    { long long __ret124 = 1;
    return __ret124; }
    }
    else if (_m114.tag == 71) {
    { long long __ret125 = 1;
    return __ret125; }
    }
    else {
    { long long __ret126 = 0;
    return __ret126; }
    }
    }
}
PType parseTypeTok_c_Comp(Comp* c) {
    Tok head = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m127 = head.kind;
    if (_m127.tag == 6) {
    PlewArray_U64 fargs = PlewArray_U64_new();
    uint64_t retRef = 0;
    {
    Kind _m128 = Comp_curKind(&((*c)));
    if (_m128.tag == 29) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    {
    Kind _m129 = Comp_curKind(&((*c)));
    if (_m129.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m129.tag == 0) {
    break;
    }
    else if (_m129.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    {
    Kind _m130 = Comp_curKind(&((*c)));
    if (_m130.tag == 5) {
    if ((Comp_peekKind_off_U64(&((*c)), 1)).tag == 36) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    }
    }
    else {
    }
    }
    {
    Kind _m131 = Comp_curKind(&((*c)));
    if (_m131.tag == 22) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PType pty = parseTypeTok_c_Comp(&((*c)));
    PlewArray_U64_push(&(fargs), pty.ref);
    }
    }
    }
    {
    Kind _m132 = Comp_curKind(&((*c)));
    if (_m132.tag == 59) {
    Comp_advance(&((*c)));
    PType rty = parseTypeTok_c_Comp(&((*c)));
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
    uint64_t fref = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = PlewArray_U64_share(allArgs)});
    { PType __ret133 = (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = fref};
    PlewArray_U64_release(allArgs);
    PlewArray_U64_release(fargs);
    return __ret133; }
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
    Kind _m134 = Comp_curKind(&((*c)));
    if (_m134.tag == 31) {
    bracketed = 1;
    Comp_advance(&((*c)));
    long long first = 1;
    while (1) {
    {
    Kind _m135 = Comp_curKind(&((*c)));
    if (_m135.tag == 32) {
    break;
    }
    else if (_m135.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m136 = Comp_curKind(&((*c)));
    if (_m136.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    first = 0;
    PType arg = parseTypeTok_c_Comp(&((*c)));
    PlewArray_U64_push(&(args), arg.ref);
    if ((long long)((args).len) == 1) {
    elemStart = arg.start;
    elemLen = arg.len;
    }
    }
    {
    Kind _m137 = Comp_curKind(&((*c)));
    if (_m137.tag == 32) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    }
    }
    uint64_t ref = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = PlewArray_U64_share(args)});
    if (bracketed) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), head.start, head.len, (PlewString){"Array", 5})) {
    if ((long long)((args).len) > 0) {
    if (isCompoundType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(args, (long long)(0)))) {
    Bind mn = appendMangleSpan_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(args, (long long)(0)));
    { PType __ret138 = (PType){.start = mn.nameStart, .len = mn.nameLen, .isArray = 1, .ref = ref};
    PlewArray_U64_release(args);
    return __ret138; }
    }
    }
    { PType __ret139 = (PType){.start = elemStart, .len = elemLen, .isArray = 1, .ref = ref};
    PlewArray_U64_release(args);
    return __ret139; }
    }
    }
    { PType __ret140 = (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = ref};
    PlewArray_U64_release(args);
    return __ret140; }
    PlewArray_U64_release(args);
}
PlewArray_Bind parseTypeParams_c_Comp(Comp* c) {
    PlewArray_Bind ps = PlewArray_Bind_new();
    {
    Kind _m141 = Comp_curKind(&((*c)));
    if (_m141.tag == 31) {
    Comp_advance(&((*c)));
    while (1) {
    {
    Kind _m142 = Comp_curKind(&((*c)));
    if (_m142.tag == 32) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m142.tag == 0) {
    break;
    }
    else if (_m142.tag == 35) {
    Comp_advance(&((*c)));
    }
    else if (_m142.tag == 36) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"inline trait constraint is not allowed in `[...]`; use a `where` clause", 71});
    Comp_advance(&((*c)));
    }
    else if (_m142.tag == 5) {
    uint64_t nameStart = 0;
    uint64_t nameLen = 0;
    while (1) {
    {
    Kind _m143 = Comp_curKind(&((*c)));
    if (_m143.tag == 5) {
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
    { PlewArray_Bind __ret144 = PlewArray_Bind_share(ps);
    PlewArray_Bind_release(ps);
    return __ret144; }
    PlewArray_Bind_release(ps);
}
void recordArrayElem_c_Comp_ty_PType(Comp* c, PType ty) {
    if (ty.isArray) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind e = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, ty.start, ty.len)) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t elemRef = 0;
    if (ty.ref < (long long)(((*c).types).len)) {
    TypeRef at = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ty.ref)));
    if ((long long)((at.args).len) > 0) {
    elemRef = PlewArray_U64_get(at.args, (long long)(0));
    }
    TypeRef_release(at);
    }
    ensureArrayElemDeps_c_Comp_elemRef_U64(&((*c)), elemRef);
    PlewArray_Bind_push(&((*c).arrayElems), (Bind){.nameStart = ty.start, .nameLen = ty.len, .fieldStart = elemRef, .fieldLen = 0});
    }
}
uint64_t parseLet_c_Comp_mutable_Bool(Comp* c, long long mutable) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyStart = 0;
    uint64_t tyLen = 0;
    long long tyIsArray = 0;
    uint64_t tyRef = 0;
    {
    Kind _m145 = Comp_curKind(&((*c)));
    if (_m145.tag == 36) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok_c_Comp(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    tyRef = ty.ref;
    recordArrayElem_c_Comp_ty_PType(&((*c)), ty);
    }
    else {
    }
    }
    {
    Kind _m146 = Comp_curKind(&((*c)));
    if (_m146.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t init = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret147 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 0, .data.Let = {.mutable = mutable, .nameStart = nameTok.start, .nameLen = nameTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .init = init}});
    return __ret147; }
}
uint64_t parsePrint_c_Comp(Comp* c) {
    Tok kw = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    uint64_t e = parseExpr_c_Comp(&((*c)));
    {
    Kind _m148 = Comp_curKind(&((*c)));
    if (_m148.tag == 30) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    { uint64_t __ret149 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 2, .data.Print = {.expr = e, .offset = kw.start}});
    return __ret149; }
}
uint64_t parsePanic_c_Comp(Comp* c) {
    Tok kw = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t msg = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret150 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 9, .data.Panic = {.msg = msg, .offset = kw.start}});
    return __ret150; }
}
uint64_t parseReturn_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m151 = Comp_curKind(&((*c)));
    if (_m151.tag == 1) {
    { uint64_t __ret152 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret152; }
    }
    else if (_m151.tag == 34) {
    { uint64_t __ret153 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret153; }
    }
    else if (_m151.tag == 0) {
    { uint64_t __ret154 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret154; }
    }
    else {
    uint64_t e = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret155 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = e, .hasValue = 1}});
    return __ret155; }
    }
    }
}
uint64_t parseIf_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr_c_Comp(&((*c)));
    uint64_t thenBlk = parseBlock_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m156 = Comp_curKind(&((*c)));
    if (_m156.tag == 11) {
    Comp_advance(&((*c)));
    {
    Kind _m157 = Comp_curKind(&((*c)));
    if (_m157.tag == 10) {
    uint64_t nested = parseIf_c_Comp(&((*c)));
    PlewArray_U64 one = PlewArray_U64_new();
    PlewArray_U64_push(&(one), nested);
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(one)});
    { uint64_t __ret158 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId, .hasElse = 1}});
    PlewArray_U64_release(one);
    return __ret158; }
    PlewArray_U64_release(one);
    }
    else {
    uint64_t elseBlk = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret159 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk, .hasElse = 1}});
    return __ret159; }
    }
    }
    }
    else {
    { uint64_t __ret160 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = 0, .hasElse = 0}});
    return __ret160; }
    }
    }
}
uint64_t parseIfExpr_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr_c_Comp(&((*c)));
    uint64_t thenBlk = parseBlock_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m161 = Comp_curKind(&((*c)));
    if (_m161.tag == 11) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m162 = Comp_curKind(&((*c)));
    if (_m162.tag == 10) {
    uint64_t nested = parseIfExpr_c_Comp(&((*c)));
    PlewArray_U64 one = PlewArray_U64_new();
    PlewArray_U64_push(&(one), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 10, .data.Give = {.value = nested}}));
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(one)});
    { uint64_t __ret163 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId}});
    PlewArray_U64_release(one);
    return __ret163; }
    PlewArray_U64_release(one);
    }
    else {
    uint64_t elseBlk = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret164 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk}});
    return __ret164; }
    }
    }
}
uint64_t parseGive_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t v = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret165 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 10, .data.Give = {.value = v}});
    return __ret165; }
}
uint64_t parseWhile_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr_c_Comp(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret166 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 6, .data.While = {.cond = cond, .body = body}});
    return __ret166; }
}
uint64_t parseFor_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m167 = Comp_curKind(&((*c)));
    if (_m167.tag == 18) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m168 = Comp_curKind(&((*c)));
    if (_m168.tag == 20) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t lo = parseExpr_c_Comp(&((*c)));
    long long isRange = 0;
    long long inclusive = 0;
    uint64_t hi = 0;
    {
    Kind _m169 = Comp_curKind(&((*c)));
    if (_m169.tag == 72) {
    Comp_advance(&((*c)));
    isRange = 1;
    hi = parseExpr_c_Comp(&((*c)));
    }
    else if (_m169.tag == 73) {
    Comp_advance(&((*c)));
    isRange = 1;
    inclusive = 1;
    hi = parseExpr_c_Comp(&((*c)));
    }
    else {
    }
    }
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret170 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 7, .data.For = {.varStart = nameTok.start, .varLen = nameTok.len, .isRange = isRange, .inclusive = inclusive, .iter = lo, .rangeHi = hi, .body = body}});
    return __ret170; }
}
uint64_t parseExprOrAssign_c_Comp(Comp* c) {
    uint64_t lhs = parseExpr_c_Comp(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    if (isAssignOp_k_Kind(k)) {
    int64_t op = kindCode_k_Kind(k);
    Comp_advance(&((*c)));
    uint64_t rhs = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret171 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 1, .data.Assign = {.op = op, .target = lhs, .value = rhs}});
    return __ret171; }
    }
    { uint64_t __ret172 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.ExprStmt = {.expr = lhs}});
    return __ret172; }
}
PatInfo parsePattern_c_Comp(Comp* c) {
    Tok firstTok = Comp_cur(&((*c)));
    long long isWildcard = 0;
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    uint64_t variantStart = 0;
    uint64_t variantLen = 0;
    PlewArray_Bind binds = PlewArray_Bind_new();
    long long isStruct = 0;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), firstTok.start, firstTok.len, (PlewString){"_", 1})) {
    isWildcard = 1;
    Comp_advance(&((*c)));
    }
    else {
    enumStart = firstTok.start;
    enumLen = firstTok.len;
    Comp_advance(&((*c)));
    long long popen = 0;
    {
    Kind _m173 = Comp_curKind(&((*c)));
    if (_m173.tag == 37) {
    Comp_advance(&((*c)));
    Tok vTok = Comp_cur(&((*c)));
    variantStart = vTok.start;
    variantLen = vTok.len;
    Comp_advance(&((*c)));
    {
    Kind _m174 = Comp_curKind(&((*c)));
    if (_m174.tag == 33) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"destructure an enum variant with parentheses, e.g. `Optional.Some(val v)`", 73});
    }
    else if (_m174.tag == 29) {
    Comp_advance(&((*c)));
    popen = 1;
    }
    else {
    }
    }
    }
    else if (_m173.tag == 33) {
    isStruct = 1;
    Comp_advance(&((*c)));
    popen = 1;
    }
    else {
    }
    }
    if (popen) {
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m175 = Comp_curKind(&((*c)));
    if (_m175.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m175.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m175.tag == 0) {
    break;
    }
    else if (_m175.tag == 18) {
    Comp_advance(&((*c)));
    Tok bTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind_push(&(binds), (Bind){.nameStart = bTok.start, .nameLen = bTok.len, .fieldStart = bTok.start, .fieldLen = bTok.len});
    {
    Kind _m176 = Comp_curKind(&((*c)));
    if (_m176.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else if (_m175.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m177 = Comp_curKind(&((*c)));
    if (_m177.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m178 = Comp_curKind(&((*c)));
    if (_m178.tag == 18) {
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
    Kind _m179 = Comp_curKind(&((*c)));
    if (_m179.tag == 35) {
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
    }
    { PatInfo __ret180 = (PatInfo){.isWildcard = isWildcard, .enumStart = enumStart, .enumLen = enumLen, .variantStart = variantStart, .variantLen = variantLen, .binds = PlewArray_Bind_share(binds), .isStruct = isStruct};
    PlewArray_Bind_release(binds);
    return __ret180; }
    PlewArray_Bind_release(binds);
}
long long bindNamesMatch_c_Comp_a_ABind_b_ABind(Comp* c, PlewArray_Bind a, PlewArray_Bind b) {
    if ((long long)((a).len) != (long long)((b).len)) {
    { long long __ret181 = 0;
    return __ret181; }
    }
    uint64_t i = 0;
    while (i < (long long)((a).len)) {
    Bind an = PlewArray_Bind_get(a, (long long)(i));
    long long found = 0;
    uint64_t j = 0;
    while (j < (long long)((b).len)) {
    Bind bn = PlewArray_Bind_get(b, (long long)(j));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), an.nameStart, an.nameLen, bn.nameStart, bn.nameLen)) {
    found = 1;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (found) {
    }
    else {
    { long long __ret182 = 0;
    return __ret182; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret183 = 1;
    return __ret183; }
}
PlewArray_PatInfo parseArmPatterns_c_Comp(Comp* c) {
    uint64_t startOff = Comp_cur(&((*c))).start;
    PlewArray_PatInfo pats = PlewArray_PatInfo_new();
    PlewArray_PatInfo_push(&(pats), parsePattern_c_Comp(&((*c))));
    while (1) {
    {
    Kind _m184 = Comp_curKind(&((*c)));
    if (_m184.tag == 54) {
    Comp_advance(&((*c)));
    Comp_skipNewlines(&((*c)));
    PlewArray_PatInfo_push(&(pats), parsePattern_c_Comp(&((*c))));
    }
    else {
    break;
    }
    }
    }
    {
    Kind _m185 = Comp_curKind(&((*c)));
    if (_m185.tag == 60) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t pi = 1;
    while (pi < (long long)((pats).len)) {
    PatInfo p0 = PatInfo_share(PlewArray_PatInfo_get(pats, (long long)(0)));
    PatInfo pn = PatInfo_share(PlewArray_PatInfo_get(pats, (long long)(pi)));
    if (bindNamesMatch_c_Comp_a_ABind_b_ABind(&((*c)), PlewArray_Bind_share(p0.binds), PlewArray_Bind_share(pn.binds))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), startOff), (PlewString){"or-pattern alternatives must bind the same names", 48});
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PatInfo_release(pn);
    PatInfo_release(p0);
    }
    { PlewArray_PatInfo __ret186 = PlewArray_PatInfo_share(pats);
    PlewArray_PatInfo_release(pats);
    return __ret186; }
    PlewArray_PatInfo_release(pats);
}
uint64_t parseArmBody_c_Comp(Comp* c) {
    {
    Kind _m187 = Comp_curKind(&((*c)));
    if (_m187.tag == 33) {
    { uint64_t __ret188 = parseBlock_c_Comp(&((*c)));
    return __ret188; }
    }
    else {
    uint64_t s = parseStmt_c_Comp(&((*c)));
    PlewArray_U64 stmts = PlewArray_U64_new();
    PlewArray_U64_push(&(stmts), s);
    uint64_t id = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(stmts)});
    { uint64_t __ret189 = id;
    PlewArray_U64_release(stmts);
    return __ret189; }
    PlewArray_U64_release(stmts);
    }
    }
}
uint64_t parseMatch_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m190 = Comp_curKind(&((*c)));
    if (_m190.tag == 33) {
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
    Kind _m191 = k;
    if (_m191.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m191.tag == 0) {
    break;
    }
    else {
    PlewArray_PatInfo pats = parseArmPatterns_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseArmBody_c_Comp(&((*c)));
    {
    PlewArray_PatInfo __fa192 = pats;
    for (long long __fi192 = 0; __fi192 < __fa192.len; __fi192++) {
        PatInfo pi = PlewArray_PatInfo_get(__fa192, __fi192);
    PlewArray_MatchArm_push(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = PlewArray_Bind_share(pi.binds), .body = body, .isStruct = pi.isStruct});
    }
    }
    PlewArray_PatInfo_release(pats);
    }
    }
    }
    { uint64_t __ret193 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 8, .data.Match = {.scrut = scrut, .arms = PlewArray_MatchArm_share(arms)}});
    PlewArray_MatchArm_release(arms);
    return __ret193; }
    PlewArray_MatchArm_release(arms);
}
uint64_t parseMatchExpr_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m194 = Comp_curKind(&((*c)));
    if (_m194.tag == 33) {
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
    Kind _m195 = k;
    if (_m195.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m195.tag == 0) {
    break;
    }
    else {
    PlewArray_PatInfo pats = parseArmPatterns_c_Comp(&((*c)));
    uint64_t body = parseExpr_c_Comp(&((*c)));
    {
    PlewArray_PatInfo __fa196 = pats;
    for (long long __fi196 = 0; __fi196 < __fa196.len; __fi196++) {
        PatInfo pi = PlewArray_PatInfo_get(__fa196, __fi196);
    PlewArray_MatchArm_push(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = PlewArray_Bind_share(pi.binds), .body = body, .isStruct = pi.isStruct});
    }
    }
    {
    Kind _m197 = Comp_curKind(&((*c)));
    if (_m197.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_PatInfo_release(pats);
    }
    }
    }
    { uint64_t __ret198 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = scrut, .arms = PlewArray_MatchArm_share(arms)}});
    PlewArray_MatchArm_release(arms);
    return __ret198; }
    PlewArray_MatchArm_release(arms);
}
uint64_t parseStmt_c_Comp(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m199 = k;
    if (_m199.tag == 18) {
    { uint64_t __ret200 = parseLet_c_Comp_mutable_Bool(&((*c)), 0);
    return __ret200; }
    }
    else if (_m199.tag == 19) {
    Comp_advance(&((*c)));
    { uint64_t __ret201 = parseLet_c_Comp_mutable_Bool(&((*c)), 1);
    return __ret201; }
    }
    else if (_m199.tag == 10) {
    { uint64_t __ret202 = parseIf_c_Comp(&((*c)));
    return __ret202; }
    }
    else if (_m199.tag == 12) {
    { uint64_t __ret203 = parseWhile_c_Comp(&((*c)));
    return __ret203; }
    }
    else if (_m199.tag == 13) {
    { uint64_t __ret204 = parseFor_c_Comp(&((*c)));
    return __ret204; }
    }
    else if (_m199.tag == 9) {
    { uint64_t __ret205 = parseMatch_c_Comp(&((*c)));
    return __ret205; }
    }
    else if (_m199.tag == 14) {
    Comp_advance(&((*c)));
    { uint64_t __ret206 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 11});
    return __ret206; }
    }
    else if (_m199.tag == 15) {
    Comp_advance(&((*c)));
    { uint64_t __ret207 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 12});
    return __ret207; }
    }
    else if (_m199.tag == 16) {
    { uint64_t __ret208 = parseReturn_c_Comp(&((*c)));
    return __ret208; }
    }
    else if (_m199.tag == 5) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"print", 5})) {
    {
    Kind _m209 = Comp_peekKind_off_U64(&((*c)), 1);
    if (_m209.tag == 29) {
    { uint64_t __ret210 = parsePrint_c_Comp(&((*c)));
    return __ret210; }
    }
    else {
    { uint64_t __ret211 = parseExprOrAssign_c_Comp(&((*c)));
    return __ret211; }
    }
    }
    }
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"panic", 5})) {
    { uint64_t __ret212 = parsePanic_c_Comp(&((*c)));
    return __ret212; }
    }
    { uint64_t __ret213 = parseExprOrAssign_c_Comp(&((*c)));
    return __ret213; }
    }
    else if (_m199.tag == 17) {
    { uint64_t __ret214 = parseGive_c_Comp(&((*c)));
    return __ret214; }
    }
    else {
    { uint64_t __ret215 = parseExprOrAssign_c_Comp(&((*c)));
    return __ret215; }
    }
    }
}
uint64_t parseBlock_c_Comp(Comp* c) {
    {
    Kind _m216 = Comp_curKind(&((*c)));
    if (_m216.tag == 33) {
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
    Kind _m217 = k;
    if (_m217.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m217.tag == 0) {
    break;
    }
    else {
    uint64_t s = parseStmt_c_Comp(&((*c)));
    PlewArray_U64_push(&(stmts), s);
    }
    }
    }
    uint64_t id = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(stmts)});
    { uint64_t __ret218 = id;
    PlewArray_U64_release(stmts);
    return __ret218; }
    PlewArray_U64_release(stmts);
}
PlewArray_Param parseParamList_c_Comp(Comp* c) {
    PlewArray_Param params = PlewArray_Param_new();
    {
    Kind _m219 = Comp_curKind(&((*c)));
    if (_m219.tag == 29) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m220 = k;
    if (_m220.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m220.tag == 0) {
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
    long long pIsMove = 0;
    long long pIsBorrow = 0;
    long long pNoLabel = 0;
    {
    Kind _m221 = Comp_curKind(&((*c)));
    if (_m221.tag == 58) {
    if ((Comp_peekKind_off_U64(&((*c)), 1)).tag == 36) {
    Comp_advance(&((*c)));
    pNoLabel = 1;
    }
    }
    else {
    }
    }
    {
    Kind _m222 = Comp_curKind(&((*c)));
    if (_m222.tag == 36) {
    Comp_advance(&((*c)));
    {
    Kind _m223 = Comp_curKind(&((*c)));
    if (_m223.tag == 22) {
    Comp_advance(&((*c)));
    pIsInout = 1;
    }
    else if (_m223.tag == 25) {
    Comp_advance(&((*c)));
    pIsMove = 1;
    }
    else if (_m223.tag == 26) {
    Comp_advance(&((*c)));
    pIsBorrow = 1;
    }
    else {
    }
    }
    PType pty = parseTypeTok_c_Comp(&((*c)));
    pTyStart = pty.start;
    pTyLen = pty.len;
    pTyIsArray = pty.isArray;
    pTyRef = pty.ref;
    recordArrayElem_c_Comp_ty_PType(&((*c)), pty);
    }
    else {
    }
    }
    long long pHasDefault = 0;
    uint64_t pDefault = 0;
    {
    Kind _m224 = Comp_curKind(&((*c)));
    if (_m224.tag == 38) {
    Comp_advance(&((*c)));
    pHasDefault = 1;
    pDefault = parseExpr_c_Comp(&((*c)));
    }
    else {
    }
    }
    PlewArray_Param_push(&(params), (Param){.nameStart = pTok.start, .nameLen = pTok.len, .tyStart = pTyStart, .tyLen = pTyLen, .tyIsArray = pTyIsArray, .ty = pTyRef, .isInout = pIsInout, .isMove = pIsMove, .isBorrow = pIsBorrow, .noLabel = pNoLabel, .hasDefault = pHasDefault, .defaultExpr = pDefault});
    {
    Kind _m225 = Comp_curKind(&((*c)));
    if (_m225.tag == 35) {
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
    { PlewArray_Param __ret226 = PlewArray_Param_share(params);
    PlewArray_Param_release(params);
    return __ret226; }
    PlewArray_Param_release(params);
}
void parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(Comp* c, long long hasRecv, uint64_t recvStart, uint64_t recvLen, long long selfInout, long long selfMove, PlewArray_Bind implParams, long long traitImpl, long long isAssoc) {
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind ownParams = parseTypeParams_c_Comp(&((*c)));
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
    PlewArray_Param params = parseParamList_c_Comp(&((*c)));
    long long hasRet = 0;
    uint64_t retStart = 0;
    uint64_t retLen = 0;
    long long retIsArray = 0;
    uint64_t retRef = 0;
    {
    Kind _m227 = Comp_curKind(&((*c)));
    if (_m227.tag == 59) {
    Comp_advance(&((*c)));
    hasRet = 1;
    PType rty = parseTypeTok_c_Comp(&((*c)));
    retStart = rty.start;
    retLen = rty.len;
    retIsArray = rty.isArray;
    retRef = rty.ref;
    recordArrayElem_c_Comp_ty_PType(&((*c)), rty);
    }
    else {
    }
    }
    PlewArray_Bind boundParams = parseWhereClause_c_Comp(&((*c)));
    PlewArray_Bind boundTraits = PlewArray_Bind_share((*c).curWhereTraits);
    if (traitImpl) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"via", 3})) {
    Comp_advance(&((*c)));
    Tok realTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_MethodAlias_push(&((*c).methodAliases), (MethodAlias){.recvStart = recvStart, .recvLen = recvLen, .aliasStart = nameTok.start, .aliasLen = nameTok.len, .realStart = realTok.start, .realLen = realTok.len});
    PlewArray_Func_push(&((*c).curWitnessed), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .params = PlewArray_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = 0, .hasRecv = 0, .recvStart = 0, .recvLen = 0, .selfInout = 0, .selfMove = 0, .isAssoc = 0});
    PlewArray_Bind_release(boundTraits);
    PlewArray_Bind_release(boundParams);
    PlewArray_Param_release(params);
    PlewArray_Bind_release(typeParams);
    PlewArray_Bind_release(ownParams);
    return;
    }
    PlewArray_Func_push(&((*c).curWitnessed), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .params = PlewArray_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = 0, .hasRecv = 0, .recvStart = 0, .recvLen = 0, .selfInout = 0, .selfMove = 0, .isAssoc = 0});
    }
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    uint64_t fnIdx = (long long)(((*c).funcs).len);
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .params = PlewArray_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body, .hasRecv = hasRecv, .recvStart = recvStart, .recvLen = recvLen, .selfInout = selfInout, .selfMove = selfMove, .isAssoc = isAssoc});
    uint64_t wbi = 0;
    while (wbi < (long long)((boundParams).len)) {
    Bind bp = PlewArray_Bind_get(boundParams, (long long)(wbi));
    Bind bt = PlewArray_Bind_get(boundTraits, (long long)(wbi));
    PlewArray_FuncBound_push(&((*c).funcBounds), (FuncBound){.fnIdx = fnIdx, .paramStart = bp.nameStart, .paramLen = bp.nameLen, .traitStart = bt.nameStart, .traitLen = bt.nameLen});
    wbi = ({ uint64_t __ov; if (__builtin_add_overflow((wbi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Bind_release(boundTraits);
    PlewArray_Bind_release(boundParams);
    PlewArray_Param_release(params);
    PlewArray_Bind_release(typeParams);
    PlewArray_Bind_release(ownParams);
}
PlewArray_Bind parseWhereClause_c_Comp(Comp* c) {
    PlewArray_Bind boundParams = PlewArray_Bind_new();
    PlewArray_Bind boundTraits = PlewArray_Bind_new();
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"where", 5})) {
    Comp_advance(&((*c)));
    long long cont = 1;
    while (cont) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m228 = Comp_curKind(&((*c)));
    if (_m228.tag == 5) {
    Tok pTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m229 = Comp_curKind(&((*c)));
    if (_m229.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    long long moreTraits = 1;
    while (moreTraits) {
    {
    Kind _m230 = Comp_curKind(&((*c)));
    if (_m230.tag == 5) {
    Tok tTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind_push(&(boundParams), (Bind){.nameStart = pTok.start, .nameLen = pTok.len, .fieldStart = pTok.start, .fieldLen = pTok.len});
    PlewArray_Bind_push(&(boundTraits), (Bind){.nameStart = tTok.start, .nameLen = tTok.len, .fieldStart = tTok.start, .fieldLen = tTok.len});
    }
    else {
    }
    }
    {
    Kind _m231 = Comp_curKind(&((*c)));
    if (_m231.tag == 45) {
    Comp_advance(&((*c)));
    }
    else {
    moreTraits = 0;
    }
    }
    }
    {
    Kind _m232 = Comp_curKind(&((*c)));
    if (_m232.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    cont = 0;
    }
    }
    }
    else {
    cont = 0;
    }
    }
    }
    }
    (*c).curWhereTraits = PlewArray_Bind_share(boundTraits);
    { PlewArray_Bind __ret233 = PlewArray_Bind_share(boundParams);
    PlewArray_Bind_release(boundTraits);
    PlewArray_Bind_release(boundParams);
    return __ret233; }
    PlewArray_Bind_release(boundTraits);
    PlewArray_Bind_release(boundParams);
}
void parseFunc_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    PlewArray_Bind noParams = PlewArray_Bind_new();
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(&((*c)), 0, 0, 0, 0, 0, PlewArray_Bind_share(noParams), 0, 0);
    PlewArray_Bind_release(noParams);
}
void parseImpl_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    PlewArray_Bind implParams = parseTypeParams_c_Comp(&((*c)));
    PType recvPty = parseTypeTok_c_Comp(&((*c)));
    uint64_t recvStart = recvPty.start;
    uint64_t recvLen = recvPty.len;
    long long isTraitImpl = 0;
    uint64_t traitStart = 0;
    uint64_t traitLen = 0;
    {
    Kind _m234 = Comp_curKind(&((*c)));
    if (_m234.tag == 21) {
    Comp_advance(&((*c)));
    Tok traitTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    isTraitImpl = 1;
    traitStart = traitTok.start;
    traitLen = traitTok.len;
    (*c).curWitnessed = PlewArray_Func_new();
    }
    else {
    }
    }
    {
    Kind _m235 = Comp_curKind(&((*c)));
    if (_m235.tag == 33) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m236 = k;
    if (_m236.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m236.tag == 0) {
    break;
    }
    else if (_m236.tag == 22) {
    Comp_advance(&((*c)));
    {
    Kind _m237 = Comp_curKind(&((*c)));
    if (_m237.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(&((*c)), 1, recvStart, recvLen, 1, 0, PlewArray_Bind_share(implParams), isTraitImpl, 0);
    }
    else if (_m236.tag == 6) {
    Comp_advance(&((*c)));
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(&((*c)), 1, recvStart, recvLen, 0, 0, PlewArray_Bind_share(implParams), isTraitImpl, 0);
    }
    else if (_m236.tag == 25) {
    Comp_advance(&((*c)));
    {
    Kind _m238 = Comp_curKind(&((*c)));
    if (_m238.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(&((*c)), 1, recvStart, recvLen, 0, 1, PlewArray_Bind_share(implParams), isTraitImpl, 0);
    }
    else if (_m236.tag == 26) {
    Comp_advance(&((*c)));
    {
    Kind _m239 = Comp_curKind(&((*c)));
    if (_m239.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(&((*c)), 1, recvStart, recvLen, 0, 0, PlewArray_Bind_share(implParams), isTraitImpl, 0);
    }
    else if (_m236.tag == 24) {
    Tok deinitTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    PlewArray_Param noParams = PlewArray_Param_new();
    PlewArray_Bind noTypeParams = PlewArray_Bind_new();
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = deinitTok.start, .nameLen = deinitTok.len, .typeParams = PlewArray_Bind_share(noTypeParams), .params = PlewArray_Param_share(noParams), .hasRet = 0, .retStart = 0, .retLen = 0, .retIsArray = 0, .retTy = 0, .body = body, .hasRecv = 1, .recvStart = recvStart, .recvLen = recvLen, .selfInout = 0, .selfMove = 0, .isAssoc = 0});
    PlewArray_Bind_push(&((*c).deinits), (Bind){.nameStart = recvStart, .nameLen = recvLen, .fieldStart = recvStart, .fieldLen = recvLen});
    PlewArray_Bind_release(noTypeParams);
    PlewArray_Param_release(noParams);
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"assoc", 5})) {
    Comp_advance(&((*c)));
    {
    Kind _m240 = Comp_curKind(&((*c)));
    if (_m240.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool(&((*c)), 0, recvStart, recvLen, 0, 0, PlewArray_Bind_share(implParams), isTraitImpl, 1);
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
    if (isTraitImpl) {
    PlewArray_Conform_push(&((*c).conforms), (Conform){.typeStart = recvStart, .typeLen = recvLen, .traitStart = traitStart, .traitLen = traitLen, .derived = 0, .witnessed = PlewArray_Func_share((*c).curWitnessed)});
    }
    PlewArray_Bind_release(implParams);
}
void parseTrait_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind supertraits = PlewArray_Bind_new();
    {
    Kind _m241 = Comp_curKind(&((*c)));
    if (_m241.tag == 36) {
    Comp_advance(&((*c)));
    long long more = 1;
    while (more) {
    {
    Kind _m242 = Comp_curKind(&((*c)));
    if (_m242.tag == 5) {
    Tok st = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind_push(&(supertraits), (Bind){.nameStart = st.start, .nameLen = st.len, .fieldStart = st.start, .fieldLen = st.len});
    }
    else {
    }
    }
    {
    Kind _m243 = Comp_curKind(&((*c)));
    if (_m243.tag == 45) {
    Comp_advance(&((*c)));
    }
    else {
    more = 0;
    }
    }
    }
    }
    else {
    }
    }
    {
    Kind _m244 = Comp_curKind(&((*c)));
    if (_m244.tag == 33) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_Func reqs = PlewArray_Func_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m245 = k;
    if (_m245.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m245.tag == 0) {
    break;
    }
    else if (_m245.tag == 6) {
    Comp_advance(&((*c)));
    PlewArray_Func_push(&(reqs), parseReqSig_c_Comp_isAssoc_Bool(&((*c)), 0));
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"assoc", 5})) {
    Comp_advance(&((*c)));
    {
    Kind _m246 = Comp_curKind(&((*c)));
    if (_m246.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PlewArray_Func_push(&(reqs), parseReqSig_c_Comp_isAssoc_Bool(&((*c)), 1));
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
    PlewArray_TraitDef_push(&((*c).traits), (TraitDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .supertraits = PlewArray_Bind_share(supertraits), .reqs = PlewArray_Func_share(reqs)});
    PlewArray_Func_release(reqs);
    PlewArray_Bind_release(supertraits);
}
Func parseReqSig_c_Comp_isAssoc_Bool(Comp* c, long long isAssoc) {
    Tok reqTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind tps = parseTypeParams_c_Comp(&((*c)));
    PlewArray_Param ps = parseParamList_c_Comp(&((*c)));
    long long hasRet = 0;
    uint64_t rs = 0;
    uint64_t rl = 0;
    long long ria = 0;
    uint64_t rr = 0;
    {
    Kind _m247 = Comp_curKind(&((*c)));
    if (_m247.tag == 59) {
    Comp_advance(&((*c)));
    PType rty = parseTypeTok_c_Comp(&((*c)));
    hasRet = 1;
    rs = rty.start;
    rl = rty.len;
    ria = rty.isArray;
    rr = rty.ref;
    recordArrayElem_c_Comp_ty_PType(&((*c)), rty);
    }
    else {
    }
    }
    Func sig = (Func){.nameStart = reqTok.start, .nameLen = reqTok.len, .typeParams = PlewArray_Bind_share(tps), .params = PlewArray_Param_share(ps), .hasRet = hasRet, .retStart = rs, .retLen = rl, .retIsArray = ria, .retTy = rr, .body = 0, .hasRecv = 0, .recvStart = 0, .recvLen = 0, .selfInout = 0, .selfMove = 0, .isAssoc = isAssoc};
    { Func __ret248 = Func_share(sig);
    Func_release(sig);
    PlewArray_Param_release(ps);
    PlewArray_Bind_release(tps);
    return __ret248; }
    Func_release(sig);
    PlewArray_Param_release(ps);
    PlewArray_Bind_release(tps);
}
void parseStruct_c_Comp_isUnique_Bool(Comp* c, long long isUnique) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind typeParams = parseTypeParams_c_Comp(&((*c)));
    {
    Kind _m249 = Comp_curKind(&((*c)));
    if (_m249.tag == 33) {
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
    Kind _m250 = k;
    if (_m250.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m250.tag == 0) {
    break;
    }
    else if (_m250.tag == 35) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"struct fields are separated by newlines, not commas", 51});
    }
    else if (_m250.tag == 24) {
    Tok deinitTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    PlewArray_Param noParams = PlewArray_Param_new();
    PlewArray_Bind noTypeParams = PlewArray_Bind_new();
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = deinitTok.start, .nameLen = deinitTok.len, .typeParams = PlewArray_Bind_share(noTypeParams), .params = PlewArray_Param_share(noParams), .hasRet = 0, .retStart = 0, .retLen = 0, .retIsArray = 0, .retTy = 0, .body = body, .hasRecv = 1, .recvStart = nameTok.start, .recvLen = nameTok.len, .selfInout = 0, .selfMove = 0, .isAssoc = 0});
    PlewArray_Bind_push(&((*c).deinits), (Bind){.nameStart = nameTok.start, .nameLen = nameTok.len, .fieldStart = nameTok.start, .fieldLen = nameTok.len});
    PlewArray_Bind_release(noTypeParams);
    PlewArray_Param_release(noParams);
    }
    else {
    long long isMut = 0;
    {
    Kind _m251 = Comp_curKind(&((*c)));
    if (_m251.tag == 19) {
    Comp_advance(&((*c)));
    isMut = 1;
    }
    else {
    }
    }
    {
    Kind _m252 = Comp_curKind(&((*c)));
    if (_m252.tag == 18) {
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
    Kind _m253 = Comp_curKind(&((*c)));
    if (_m253.tag == 36) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok_c_Comp(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    tyRef = ty.ref;
    recordArrayElem_c_Comp_ty_PType(&((*c)), ty);
    }
    else {
    }
    }
    long long hasDefault = 0;
    uint64_t defaultVal = 0;
    {
    Kind _m254 = Comp_curKind(&((*c)));
    if (_m254.tag == 38) {
    Comp_advance(&((*c)));
    defaultVal = parseExpr_c_Comp(&((*c)));
    hasDefault = 1;
    }
    else {
    }
    }
    PlewArray_FieldDef_push(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .isMut = isMut, .hasDefault = hasDefault, .defaultVal = defaultVal});
    }
    }
    }
    PlewArray_StructDef_push(&((*c).structs), (StructDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .fields = PlewArray_FieldDef_share(fields), .isUnique = isUnique});
    drainDerives_c_Comp_typeStart_U64_typeLen_U64_isEnum_Bool(&((*c)), nameTok.start, nameTok.len, 0);
    PlewArray_FieldDef_release(fields);
    PlewArray_Bind_release(typeParams);
}
void parseEnum_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind typeParams = parseTypeParams_c_Comp(&((*c)));
    {
    Kind _m255 = Comp_curKind(&((*c)));
    if (_m255.tag == 33) {
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
    Kind _m256 = k;
    if (_m256.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m256.tag == 0) {
    break;
    }
    else if (_m256.tag == 5) {
    Tok vTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_new();
    long long vopen = 0;
    {
    Kind _m257 = Comp_curKind(&((*c)));
    if (_m257.tag == 33) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"enum variant payloads use parentheses, e.g. `Foo(x: I32, y: I32)`", 65});
    }
    else if (_m257.tag == 29) {
    Comp_advance(&((*c)));
    vopen = 1;
    }
    else {
    }
    }
    if (vopen) {
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m258 = Comp_curKind(&((*c)));
    if (_m258.tag == 30) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m258.tag == 0) {
    break;
    }
    else if (_m258.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyStart = 0;
    uint64_t tyLen = 0;
    long long tyIsArray = 0;
    uint64_t tyRef = 0;
    {
    Kind _m259 = Comp_curKind(&((*c)));
    if (_m259.tag == 36) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok_c_Comp(&((*c)));
    tyStart = ty.start;
    tyLen = ty.len;
    tyIsArray = ty.isArray;
    tyRef = ty.ref;
    recordArrayElem_c_Comp_ty_PType(&((*c)), ty);
    }
    else {
    }
    }
    PlewArray_FieldDef_push(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .isMut = 0, .hasDefault = 0, .defaultVal = 0});
    {
    Kind _m260 = Comp_curKind(&((*c)));
    if (_m260.tag == 35) {
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
    PlewArray_Variant_push(&(variants), (Variant){.nameStart = vTok.start, .nameLen = vTok.len, .fields = PlewArray_FieldDef_share(fields)});
    PlewArray_FieldDef_release(fields);
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    PlewArray_EnumDef_push(&((*c).enums), (EnumDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = PlewArray_Bind_share(typeParams), .variants = PlewArray_Variant_share(variants)});
    drainDerives_c_Comp_typeStart_U64_typeLen_U64_isEnum_Bool(&((*c)), nameTok.start, nameTok.len, 1);
    PlewArray_Variant_release(variants);
    PlewArray_Bind_release(typeParams);
}
void parseDirective_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m261 = Comp_curKind(&((*c)));
    if (_m261.tag == 31) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    {
    Kind _m262 = Comp_curKind(&((*c)));
    if (_m262.tag == 32) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m262.tag == 0) {
    break;
    }
    else if (_m262.tag == 35) {
    Comp_advance(&((*c)));
    }
    else if (_m262.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    PlewArray_Bind_push(&((*c).pendingDerives), (Bind){.nameStart = t.start, .nameLen = t.len, .fieldStart = t.start, .fieldLen = t.len});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
}
void drainDerives_c_Comp_typeStart_U64_typeLen_U64_isEnum_Bool(Comp* c, uint64_t typeStart, uint64_t typeLen, long long isEnum) {
    uint64_t i = 0;
    while (i < (long long)(((*c).pendingDerives).len)) {
    Bind d = PlewArray_Bind_get((*c).pendingDerives, (long long)(i));
    PlewArray_DeriveReq_push(&((*c).derives), (DeriveReq){.typeStart = typeStart, .typeLen = typeLen, .isEnum = isEnum, .nameStart = d.nameStart, .nameLen = d.nameLen});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).pendingDerives = PlewArray_Bind_new();
}
Bind internBytes_c_Comp_s_String(Comp* c, PlewString s) {
    uint64_t start = (long long)(((*c).bytes).len);
    PlewArray_U8 sb = PlewArray_U8_share(({ PlewString __s = s; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    uint64_t i = 0;
    while (i < (long long)((sb).len)) {
    PlewArray_U8_push(&((*c).bytes), PlewArray_U8_get(sb, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Bind __ret263 = (Bind){.nameStart = start, .nameLen = (long long)((sb).len), .fieldStart = start, .fieldLen = (long long)((sb).len)};
    PlewArray_U8_release(sb);
    return __ret263; }
    PlewArray_U8_release(sb);
}
Param synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(Bind nameSpan, uint64_t tyStart, uint64_t tyLen) {
    Param p = (Param){.nameStart = nameSpan.nameStart, .nameLen = nameSpan.nameLen, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = 0, .ty = 0, .isInout = 0, .isMove = 0, .isBorrow = 0, .noLabel = 0, .hasDefault = 0, .defaultExpr = 0};
    { Param __ret264 = p;
    return __ret264; }
}
void synthStructEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(Comp* c, DeriveReq d, Bind eqN, Bind lhsN, Bind rhsN, Bind boolN, Bind eqTrait) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), d.typeStart, d.typeLen);
    if (si >= (long long)(((*c).structs).len)) {
    return;
    }
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)).fields);
    PlewArray_Param params = PlewArray_Param_new();
    PlewArray_Param_push(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(lhsN, d.typeStart, d.typeLen));
    PlewArray_Param_push(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(rhsN, d.typeStart, d.typeLen));
    uint64_t lhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = lhsN.nameStart, .len = lhsN.nameLen}});
    uint64_t rhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = rhsN.nameStart, .len = rhsN.nameLen}});
    uint64_t acc = 0;
    long long first = 1;
    uint64_t fi = 0;
    while (fi < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(fi));
    uint64_t lf = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = lhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t rf = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = rhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t eqi = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 50, .lhs = lf, .rhs = rf}});
    if (first) {
    acc = eqi;
    first = 0;
    }
    else {
    acc = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 61, .lhs = acc, .rhs = eqi}});
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (first) {
    acc = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 1, .offset = 0, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    }
    uint64_t ret = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = acc, .hasValue = 1}});
    PlewArray_U64 stmts = PlewArray_U64_new();
    PlewArray_U64_push(&(stmts), ret);
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(stmts)});
    PlewArray_Bind noTP = PlewArray_Bind_new();
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = eqN.nameStart, .nameLen = eqN.nameLen, .typeParams = PlewArray_Bind_share(noTP), .params = PlewArray_Param_share(params), .hasRet = 1, .retStart = boolN.nameStart, .retLen = boolN.nameLen, .retIsArray = 0, .retTy = 0, .body = blkId, .hasRecv = 0, .recvStart = d.typeStart, .recvLen = d.typeLen, .selfInout = 0, .selfMove = 0, .isAssoc = 1});
    PlewArray_Func wit = PlewArray_Func_new();
    PlewArray_Conform_push(&((*c).conforms), (Conform){.typeStart = d.typeStart, .typeLen = d.typeLen, .traitStart = eqTrait.nameStart, .traitLen = eqTrait.nameLen, .derived = 1, .witnessed = PlewArray_Func_share(wit)});
    PlewArray_Func_release(wit);
    PlewArray_Bind_release(noTP);
    PlewArray_U64_release(stmts);
    PlewArray_Param_release(params);
    PlewArray_FieldDef_release(fields);
}
unsigned char digitByte_d_U64(uint64_t d) {
    if (d == 0) {
    { unsigned char __ret265 = 48;
    return __ret265; }
    }
    if (d == 1) {
    { unsigned char __ret266 = 49;
    return __ret266; }
    }
    if (d == 2) {
    { unsigned char __ret267 = 50;
    return __ret267; }
    }
    if (d == 3) {
    { unsigned char __ret268 = 51;
    return __ret268; }
    }
    if (d == 4) {
    { unsigned char __ret269 = 52;
    return __ret269; }
    }
    if (d == 5) {
    { unsigned char __ret270 = 53;
    return __ret270; }
    }
    if (d == 6) {
    { unsigned char __ret271 = 54;
    return __ret271; }
    }
    if (d == 7) {
    { unsigned char __ret272 = 55;
    return __ret272; }
    }
    if (d == 8) {
    { unsigned char __ret273 = 56;
    return __ret273; }
    }
    { unsigned char __ret274 = 57;
    return __ret274; }
}
void appendU64Digits_c_Comp_n_U64(Comp* c, uint64_t n) {
    if (n >= 10) {
    appendU64Digits_c_Comp_n_U64(&((*c)), ({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); __dl / __dr; }));
    }
    PlewArray_U8_push(&((*c).bytes), digitByte_d_U64(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); __dl % __dr; })));
}
Bind internName_c_Comp_prefix_U8_n_U64(Comp* c, unsigned char prefix, uint64_t n) {
    uint64_t start = (long long)(((*c).bytes).len);
    PlewArray_U8_push(&((*c).bytes), prefix);
    appendU64Digits_c_Comp_n_U64(&((*c)), n);
    uint64_t len = ({ uint64_t __ov; if (__builtin_sub_overflow(((long long)(((*c).bytes).len)), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    { Bind __ret275 = (Bind){.nameStart = start, .nameLen = len, .fieldStart = start, .fieldLen = len};
    return __ret275; }
}
uint64_t enumIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).enums).len)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), PlewArray_EnumDef_get((*c).enums, (long long)(i)).nameStart, PlewArray_EnumDef_get((*c).enums, (long long)(i)).nameLen, start, len)) {
    { uint64_t __ret276 = i;
    return __ret276; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret277 = (long long)(((*c).enums).len);
    return __ret277; }
}
uint64_t synthBool_c_Comp_v_I64(Comp* c, int64_t v) {
    { uint64_t __ret278 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = 0, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret278; }
}
void synthEnumEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(Comp* c, DeriveReq d, Bind eqN, Bind lhsN, Bind rhsN, Bind boolN, Bind eqTrait) {
    uint64_t ei = enumIndexByName_c_Comp_start_U64_len_U64(&((*c)), d.typeStart, d.typeLen);
    if (ei >= (long long)(((*c).enums).len)) {
    return;
    }
    PlewArray_Variant variants = PlewArray_Variant_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)).variants);
    PlewArray_Param params = PlewArray_Param_new();
    PlewArray_Param_push(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(lhsN, d.typeStart, d.typeLen));
    PlewArray_Param_push(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(rhsN, d.typeStart, d.typeLen));
    uint64_t lhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = lhsN.nameStart, .len = lhsN.nameLen}});
    uint64_t rhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = rhsN.nameStart, .len = rhsN.nameLen}});
    uint64_t counter = 0;
    PlewArray_MatchArm outerArms = PlewArray_MatchArm_new();
    uint64_t vi = 0;
    while (vi < (long long)((variants).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(variants, (long long)(vi)));
    PlewArray_FieldDef flds = PlewArray_FieldDef_share(v.fields);
    PlewArray_Bind lhsBinds = PlewArray_Bind_new();
    PlewArray_Bind rhsBinds = PlewArray_Bind_new();
    uint64_t payload = 0;
    long long firstp = 1;
    uint64_t fj = 0;
    while (fj < (long long)((flds).len)) {
    FieldDef f = PlewArray_FieldDef_get(flds, (long long)(fj));
    Bind ln = internName_c_Comp_prefix_U8_n_U64(&((*c)), 76, counter);
    counter = ({ uint64_t __ov; if (__builtin_add_overflow((counter), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Bind rn = internName_c_Comp_prefix_U8_n_U64(&((*c)), 82, counter);
    counter = ({ uint64_t __ov; if (__builtin_add_overflow((counter), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_Bind_push(&(lhsBinds), (Bind){.nameStart = ln.nameStart, .nameLen = ln.nameLen, .fieldStart = f.nameStart, .fieldLen = f.nameLen});
    PlewArray_Bind_push(&(rhsBinds), (Bind){.nameStart = rn.nameStart, .nameLen = rn.nameLen, .fieldStart = f.nameStart, .fieldLen = f.nameLen});
    uint64_t li = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = ln.nameStart, .len = ln.nameLen}});
    uint64_t ri = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = rn.nameStart, .len = rn.nameLen}});
    uint64_t eqj = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 50, .lhs = li, .rhs = ri}});
    if (firstp) {
    payload = eqj;
    firstp = 0;
    }
    else {
    payload = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 61, .lhs = payload, .rhs = eqj}});
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (firstp) {
    payload = synthBool_c_Comp_v_I64(&((*c)), 1);
    }
    PlewArray_MatchArm innerArms = PlewArray_MatchArm_new();
    PlewArray_MatchArm_push(&(innerArms), (MatchArm){.isWildcard = 0, .enumStart = d.typeStart, .enumLen = d.typeLen, .variantStart = v.nameStart, .variantLen = v.nameLen, .binds = PlewArray_Bind_share(rhsBinds), .body = payload, .isStruct = 0});
    PlewArray_Bind noBinds = PlewArray_Bind_new();
    PlewArray_MatchArm_push(&(innerArms), (MatchArm){.isWildcard = 1, .enumStart = 0, .enumLen = 0, .variantStart = 0, .variantLen = 0, .binds = PlewArray_Bind_share(noBinds), .body = synthBool_c_Comp_v_I64(&((*c)), 0), .isStruct = 0});
    uint64_t innerMatch = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = rhsId, .arms = PlewArray_MatchArm_share(innerArms)}});
    PlewArray_MatchArm_push(&(outerArms), (MatchArm){.isWildcard = 0, .enumStart = d.typeStart, .enumLen = d.typeLen, .variantStart = v.nameStart, .variantLen = v.nameLen, .binds = PlewArray_Bind_share(lhsBinds), .body = innerMatch, .isStruct = 0});
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_Bind_release(noBinds);
    PlewArray_MatchArm_release(innerArms);
    PlewArray_Bind_release(rhsBinds);
    PlewArray_Bind_release(lhsBinds);
    PlewArray_FieldDef_release(flds);
    Variant_release(v);
    }
    uint64_t outerMatch = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = lhsId, .arms = PlewArray_MatchArm_share(outerArms)}});
    uint64_t ret = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = outerMatch, .hasValue = 1}});
    PlewArray_U64 stmts = PlewArray_U64_new();
    PlewArray_U64_push(&(stmts), ret);
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(stmts)});
    PlewArray_Bind noTP = PlewArray_Bind_new();
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = eqN.nameStart, .nameLen = eqN.nameLen, .typeParams = PlewArray_Bind_share(noTP), .params = PlewArray_Param_share(params), .hasRet = 1, .retStart = boolN.nameStart, .retLen = boolN.nameLen, .retIsArray = 0, .retTy = 0, .body = blkId, .hasRecv = 0, .recvStart = d.typeStart, .recvLen = d.typeLen, .selfInout = 0, .selfMove = 0, .isAssoc = 1});
    PlewArray_Func wit = PlewArray_Func_new();
    PlewArray_Conform_push(&((*c).conforms), (Conform){.typeStart = d.typeStart, .typeLen = d.typeLen, .traitStart = eqTrait.nameStart, .traitLen = eqTrait.nameLen, .derived = 1, .witnessed = PlewArray_Func_share(wit)});
    PlewArray_Func_release(wit);
    PlewArray_Bind_release(noTP);
    PlewArray_U64_release(stmts);
    PlewArray_MatchArm_release(outerArms);
    PlewArray_Param_release(params);
    PlewArray_Variant_release(variants);
}
uint64_t synthOrdering_c_Comp_ordN_Bind_variantN_Bind(Comp* c, Bind ordN, Bind variantN) {
    PlewArray_MakeField noFields = PlewArray_MakeField_new();
    { uint64_t __ret279 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 6, .data.Make = {.typeStart = ordN.nameStart, .typeLen = ordN.nameLen, .variantStart = variantN.nameStart, .variantLen = variantN.nameLen, .isEnum = 1, .ty = 0, .fields = PlewArray_MakeField_share(noFields)}});
    PlewArray_MakeField_release(noFields);
    return __ret279; }
    PlewArray_MakeField_release(noFields);
}
uint64_t synthReturnBlock_c_Comp_value_U64(Comp* c, uint64_t value) {
    uint64_t ret = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = value, .hasValue = 1}});
    PlewArray_U64 stmts = PlewArray_U64_new();
    PlewArray_U64_push(&(stmts), ret);
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(stmts)});
    { uint64_t __ret280 = blkId;
    PlewArray_U64_release(stmts);
    return __ret280; }
    PlewArray_U64_release(stmts);
}
void synthStructOrd_c_Comp_d_DeriveReq_cmpN_Bind_lhsN_Bind_rhsN_Bind_ordN_Bind_lessN_Bind_greaterN_Bind_equalN_Bind_ordTrait_Bind(Comp* c, DeriveReq d, Bind cmpN, Bind lhsN, Bind rhsN, Bind ordN, Bind lessN, Bind greaterN, Bind equalN, Bind ordTrait) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), d.typeStart, d.typeLen);
    if (si >= (long long)(((*c).structs).len)) {
    return;
    }
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)).fields);
    PlewArray_Param params = PlewArray_Param_new();
    PlewArray_Param_push(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(lhsN, d.typeStart, d.typeLen));
    PlewArray_Param_push(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(rhsN, d.typeStart, d.typeLen));
    uint64_t lhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = lhsN.nameStart, .len = lhsN.nameLen}});
    uint64_t rhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = rhsN.nameStart, .len = rhsN.nameLen}});
    PlewArray_U64 stmts = PlewArray_U64_new();
    uint64_t fi = 0;
    while (fi < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(fi));
    uint64_t lf1 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = lhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t rf1 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = rhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t lt = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 52, .lhs = lf1, .rhs = rf1}});
    uint64_t lessBlk = synthReturnBlock_c_Comp_value_U64(&((*c)), synthOrdering_c_Comp_ordN_Bind_variantN_Bind(&((*c)), ordN, lessN));
    PlewArray_U64_push(&(stmts), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = lt, .thenBlk = lessBlk, .elseBlk = 0, .hasElse = 0}}));
    uint64_t lf2 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = lhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t rf2 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = rhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t gt = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 54, .lhs = lf2, .rhs = rf2}});
    uint64_t grBlk = synthReturnBlock_c_Comp_value_U64(&((*c)), synthOrdering_c_Comp_ordN_Bind_variantN_Bind(&((*c)), ordN, greaterN));
    PlewArray_U64_push(&(stmts), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 5, .data.If = {.cond = gt, .thenBlk = grBlk, .elseBlk = 0, .hasElse = 0}}));
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U64_push(&(stmts), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.Return = {.value = synthOrdering_c_Comp_ordN_Bind_variantN_Bind(&((*c)), ordN, equalN), .hasValue = 1}}));
    uint64_t blkId = (long long)(((*c).blocks).len);
    PlewArray_Block_push(&((*c).blocks), (Block){.stmts = PlewArray_U64_share(stmts)});
    PlewArray_Bind noTP = PlewArray_Bind_new();
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = cmpN.nameStart, .nameLen = cmpN.nameLen, .typeParams = PlewArray_Bind_share(noTP), .params = PlewArray_Param_share(params), .hasRet = 1, .retStart = ordN.nameStart, .retLen = ordN.nameLen, .retIsArray = 0, .retTy = 0, .body = blkId, .hasRecv = 0, .recvStart = d.typeStart, .recvLen = d.typeLen, .selfInout = 0, .selfMove = 0, .isAssoc = 1});
    PlewArray_Func wit = PlewArray_Func_new();
    PlewArray_Conform_push(&((*c).conforms), (Conform){.typeStart = d.typeStart, .typeLen = d.typeLen, .traitStart = ordTrait.nameStart, .traitLen = ordTrait.nameLen, .derived = 1, .witnessed = PlewArray_Func_share(wit)});
    PlewArray_Func_release(wit);
    PlewArray_Bind_release(noTP);
    PlewArray_U64_release(stmts);
    PlewArray_Param_release(params);
    PlewArray_FieldDef_release(fields);
}
void synthesizeDerives_c_Comp(Comp* c) {
    if ((long long)(((*c).derives).len) == 0) {
    return;
    }
    Bind eqN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"eq", 2});
    Bind lhsN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"lhs", 3});
    Bind rhsN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"rhs", 3});
    Bind boolN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"Bool", 4});
    Bind eqTrait = internBytes_c_Comp_s_String(&((*c)), (PlewString){"Eq", 2});
    Bind cmpN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"compare", 7});
    Bind ordN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"Ordering", 8});
    Bind lessN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"Less", 4});
    Bind greaterN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"Greater", 7});
    Bind equalN = internBytes_c_Comp_s_String(&((*c)), (PlewString){"Equal", 5});
    Bind ordTrait = internBytes_c_Comp_s_String(&((*c)), (PlewString){"Ord", 3});
    uint64_t i = 0;
    while (i < (long long)(((*c).derives).len)) {
    DeriveReq d = PlewArray_DeriveReq_get((*c).derives, (long long)(i));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), d.nameStart, d.nameLen, (PlewString){"Eq", 2})) {
    if (d.isEnum) {
    synthEnumEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(&((*c)), d, eqN, lhsN, rhsN, boolN, eqTrait);
    }
    else {
    synthStructEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(&((*c)), d, eqN, lhsN, rhsN, boolN, eqTrait);
    }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), d.nameStart, d.nameLen, (PlewString){"Ord", 3})) {
    if (enumIndexByName_c_Comp_start_U64_len_U64(&((*c)), ordN.nameStart, ordN.nameLen) >= (long long)(((*c).enums).len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), d.nameStart), (PlewString){"deriving `Ord` requires `enum Ordering` to be in scope", 54});
    }
    else {
    if (d.isEnum) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), d.nameStart), (PlewString){"`@[Ord]` on an enum is not yet supported (derive it on structs; enums: manual impl for now)", 91});
    }
    else {
    synthStructOrd_c_Comp_d_DeriveReq_cmpN_Bind_lhsN_Bind_rhsN_Bind_ordN_Bind_lessN_Bind_greaterN_Bind_equalN_Bind_ordTrait_Bind(&((*c)), d, cmpN, lhsN, rhsN, ordN, lessN, greaterN, equalN, ordTrait);
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void markImport_c_Comp_segStart_U64_segLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t segStart, uint64_t segLen, uint64_t nameStart, uint64_t nameLen) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), segStart, segLen, (PlewString){"Io", 2})) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"print", 5})) {
    (*c).impPrint = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"write", 5})) {
    (*c).impWrite = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"writeByte", 9})) {
    (*c).impWriteByte = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readStdin", 9})) {
    (*c).impReadStdin = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readFile", 8})) {
    (*c).impReadFile = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readFileBytes", 13})) {
    (*c).impReadFileBytes = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"eprint", 6})) {
    (*c).impEprint = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"fileExists", 10})) {
    (*c).impFileExists = 1;
    }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), segStart, segLen, (PlewString){"Process", 7})) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"argCount", 8})) {
    (*c).impArgCount = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"argAt", 5})) {
    (*c).impArgAt = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"exit", 4})) {
    (*c).impExit = 1;
    }
    }
}
void parseImport_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t segStart = 0;
    uint64_t segLen = 0;
    while (1) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m281 = k;
    if (_m281.tag == 1) {
    break;
    }
    else if (_m281.tag == 0) {
    break;
    }
    else if (_m281.tag == 33) {
    break;
    }
    else if (_m281.tag == 5) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"with", 4})) {
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
    Kind _m282 = Comp_curKind(&((*c)));
    if (_m282.tag == 33) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m283 = k;
    if (_m283.tag == 34) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m283.tag == 0) {
    break;
    }
    else if (_m283.tag == 35) {
    Comp_advance(&((*c)));
    }
    else if (_m283.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    markImport_c_Comp_segStart_U64_segLen_U64_nameStart_U64_nameLen_U64(&((*c)), segStart, segLen, t.start, t.len);
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
void parseProgram_c_Comp(Comp* c) {
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m284 = k;
    if (_m284.tag == 6) {
    parseFunc_c_Comp(&((*c)));
    }
    else if (_m284.tag == 7) {
    parseStruct_c_Comp_isUnique_Bool(&((*c)), 0);
    }
    else if (_m284.tag == 23) {
    Comp_advance(&((*c)));
    {
    Kind _m285 = Comp_curKind(&((*c)));
    if (_m285.tag == 7) {
    parseStruct_c_Comp_isUnique_Bool(&((*c)), 1);
    }
    else {
    }
    }
    }
    else if (_m284.tag == 8) {
    parseEnum_c_Comp(&((*c)));
    }
    else if (_m284.tag == 5) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"import", 6})) {
    parseImport_c_Comp(&((*c)));
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"impl", 4})) {
    parseImpl_c_Comp(&((*c)));
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"trait", 5})) {
    parseTrait_c_Comp(&((*c)));
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
    else if (_m284.tag == 0) {
    break;
    }
    else {
    if ((Comp_peekKind_off_U64(&((*c)), 1)).tag == 31) {
    parseDirective_c_Comp(&((*c)));
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    }
}
PlewString digitStr_d_I64(int64_t d) {
    if (d == 0) {
    { PlewString __ret286 = (PlewString){"0", 1};
    return __ret286; }
    }
    if (d == 1) {
    { PlewString __ret287 = (PlewString){"1", 1};
    return __ret287; }
    }
    if (d == 2) {
    { PlewString __ret288 = (PlewString){"2", 1};
    return __ret288; }
    }
    if (d == 3) {
    { PlewString __ret289 = (PlewString){"3", 1};
    return __ret289; }
    }
    if (d == 4) {
    { PlewString __ret290 = (PlewString){"4", 1};
    return __ret290; }
    }
    if (d == 5) {
    { PlewString __ret291 = (PlewString){"5", 1};
    return __ret291; }
    }
    if (d == 6) {
    { PlewString __ret292 = (PlewString){"6", 1};
    return __ret292; }
    }
    if (d == 7) {
    { PlewString __ret293 = (PlewString){"7", 1};
    return __ret293; }
    }
    if (d == 8) {
    { PlewString __ret294 = (PlewString){"8", 1};
    return __ret294; }
    }
    { PlewString __ret295 = (PlewString){"9", 1};
    return __ret295; }
}
void writeInt_n_I64(int64_t n) {
    if (n < 0) {
    plew_write((PlewString){"-", 1});
    writeInt_n_I64(({ int64_t __ov; if (__builtin_sub_overflow((0), (n), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    return;
    }
    if (n >= 10) {
    writeInt_n_I64(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); if (__dr == -1 && __dl == INT64_MIN) plew_panic((PlewString){"integer overflow", 16}); __dl / __dr; }));
    }
    plew_write(digitStr_d_I64(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); (__dr == -1 ? 0 : __dl % __dr); })));
}
PlewString digitStrU_d_U64(uint64_t d) {
    if (d == 0) {
    { PlewString __ret296 = (PlewString){"0", 1};
    return __ret296; }
    }
    if (d == 1) {
    { PlewString __ret297 = (PlewString){"1", 1};
    return __ret297; }
    }
    if (d == 2) {
    { PlewString __ret298 = (PlewString){"2", 1};
    return __ret298; }
    }
    if (d == 3) {
    { PlewString __ret299 = (PlewString){"3", 1};
    return __ret299; }
    }
    if (d == 4) {
    { PlewString __ret300 = (PlewString){"4", 1};
    return __ret300; }
    }
    if (d == 5) {
    { PlewString __ret301 = (PlewString){"5", 1};
    return __ret301; }
    }
    if (d == 6) {
    { PlewString __ret302 = (PlewString){"6", 1};
    return __ret302; }
    }
    if (d == 7) {
    { PlewString __ret303 = (PlewString){"7", 1};
    return __ret303; }
    }
    if (d == 8) {
    { PlewString __ret304 = (PlewString){"8", 1};
    return __ret304; }
    }
    { PlewString __ret305 = (PlewString){"9", 1};
    return __ret305; }
}
void writeU64_n_U64(uint64_t n) {
    if (n >= 10) {
    writeU64_n_U64(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); __dl / __dr; }));
    }
    plew_write(digitStrU_d_U64(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); __dl % __dr; })));
}
void writeSpan_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t j = 0;
    while (j < len) {
    putchar((int)(PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })))));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void eprintInt_n_I64(int64_t n) {
    if (n >= 10) {
    eprintInt_n_I64(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); if (__dr == -1 && __dl == INT64_MIN) plew_panic((PlewString){"integer overflow", 16}); __dl / __dr; }));
    }
    plew_eprint(digitStr_d_I64(({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); (__dr == -1 ? 0 : __dl % __dr); })));
}
void compileError_msg_String(PlewString msg) {
    plew_eprint((PlewString){"plewc: error: ", 14});
    plew_eprint(msg);
    plew_eprint((PlewString){"\n", 1});
    exit((int)(1));
}
void compileErrorAt_line_I64_msg_String(int64_t line, PlewString msg) {
    plew_eprint((PlewString){"plewc: error: line ", 19});
    eprintInt_n_I64(line);
    plew_eprint((PlewString){": ", 2});
    plew_eprint(msg);
    plew_eprint((PlewString){"\n", 1});
    exit((int)(1));
}
long long isPrimType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { long long __ret306 = 1;
    return __ret306; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { long long __ret307 = 1;
    return __ret307; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { long long __ret308 = 1;
    return __ret308; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I64", 3})) {
    { long long __ret309 = 1;
    return __ret309; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    { long long __ret310 = 1;
    return __ret310; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    { long long __ret311 = 1;
    return __ret311; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    { long long __ret312 = 1;
    return __ret312; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U64", 3})) {
    { long long __ret313 = 1;
    return __ret313; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"Bool", 4})) {
    { long long __ret314 = 1;
    return __ret314; }
    }
    { long long __ret315 = 0;
    return __ret315; }
}
long long isIntType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { long long __ret316 = 1;
    return __ret316; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { long long __ret317 = 1;
    return __ret317; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { long long __ret318 = 1;
    return __ret318; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I64", 3})) {
    { long long __ret319 = 1;
    return __ret319; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    { long long __ret320 = 1;
    return __ret320; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    { long long __ret321 = 1;
    return __ret321; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    { long long __ret322 = 1;
    return __ret322; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U64", 3})) {
    { long long __ret323 = 1;
    return __ret323; }
    }
    { long long __ret324 = 0;
    return __ret324; }
}
uint64_t intBits_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { uint64_t __ret325 = 8;
    return __ret325; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    { uint64_t __ret326 = 8;
    return __ret326; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { uint64_t __ret327 = 16;
    return __ret327; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    { uint64_t __ret328 = 16;
    return __ret328; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { uint64_t __ret329 = 32;
    return __ret329; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    { uint64_t __ret330 = 32;
    return __ret330; }
    }
    { uint64_t __ret331 = 64;
    return __ret331; }
}
long long intSigned_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    { long long __ret332 = (PlewArray_U8_get((*c).bytes, (long long)(start)) == 73);
    return __ret332; }
}
long long losslessInt_c_Comp_srcStart_U64_srcLen_U64_dstStart_U64_dstLen_U64(Comp* c, uint64_t srcStart, uint64_t srcLen, uint64_t dstStart, uint64_t dstLen) {
    uint64_t sBits = intBits_c_Comp_start_U64_len_U64(&((*c)), srcStart, srcLen);
    uint64_t dBits = intBits_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    long long sSigned = intSigned_c_Comp_start_U64_len_U64(&((*c)), srcStart, srcLen);
    long long dSigned = intSigned_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    if (sSigned) {
    if (dSigned) {
    { long long __ret333 = (dBits >= sBits);
    return __ret333; }
    }
    { long long __ret334 = 0;
    return __ret334; }
    }
    if (dSigned) {
    { long long __ret335 = (dBits > sBits);
    return __ret335; }
    }
    { long long __ret336 = (dBits >= sBits);
    return __ret336; }
}
long long litFitsType_c_Comp_value_I64_dstStart_U64_dstLen_U64(Comp* c, int64_t value, uint64_t dstStart, uint64_t dstLen) {
    uint64_t bits = intBits_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    long long sgn = intSigned_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    { long long __ret337 = litFitsBits_value_I64_bits_U64_sgn_Bool(value, bits, sgn);
    return __ret337; }
}
long long litFitsBits_value_I64_bits_U64_sgn_Bool(int64_t value, uint64_t bits, long long sgn) {
    if (sgn) {
    if (bits == 8) {
    if (value < (0 - 128)) {
    { long long __ret338 = 0;
    return __ret338; }
    }
    if (value > 127) {
    { long long __ret339 = 0;
    return __ret339; }
    }
    { long long __ret340 = 1;
    return __ret340; }
    }
    if (bits == 16) {
    if (value < (0 - 32768)) {
    { long long __ret341 = 0;
    return __ret341; }
    }
    if (value > 32767) {
    { long long __ret342 = 0;
    return __ret342; }
    }
    { long long __ret343 = 1;
    return __ret343; }
    }
    if (bits == 32) {
    if (value < (0 - 2147483648)) {
    { long long __ret344 = 0;
    return __ret344; }
    }
    if (value > 2147483647) {
    { long long __ret345 = 0;
    return __ret345; }
    }
    { long long __ret346 = 1;
    return __ret346; }
    }
    { long long __ret347 = 1;
    return __ret347; }
    }
    if (value < 0) {
    { long long __ret348 = 0;
    return __ret348; }
    }
    if (bits == 8) {
    if (value > 255) {
    { long long __ret349 = 0;
    return __ret349; }
    }
    { long long __ret350 = 1;
    return __ret350; }
    }
    if (bits == 16) {
    if (value > 65535) {
    { long long __ret351 = 0;
    return __ret351; }
    }
    { long long __ret352 = 1;
    return __ret352; }
    }
    if (bits == 32) {
    if (value > 4294967295) {
    { long long __ret353 = 0;
    return __ret353; }
    }
    { long long __ret354 = 1;
    return __ret354; }
    }
    { long long __ret355 = 1;
    return __ret355; }
}
uint64_t arrayElemRef_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind ae = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ae.nameStart, ae.nameLen, start, len)) {
    { uint64_t __ret356 = ae.fieldStart;
    return __ret356; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret357 = 0;
    return __ret357; }
}
Bind arrayElemNameForRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind ae = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (ae.fieldStart == elemRef) {
    { Bind __ret358 = (Bind){.nameStart = ae.nameStart, .nameLen = ae.nameLen, .fieldStart = elemRef, .fieldLen = 0};
    return __ret358; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (elemRef < (long long)(((*c).types).len)) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(elemRef)));
    { Bind __ret359 = (Bind){.nameStart = t.nameStart, .nameLen = t.nameLen, .fieldStart = elemRef, .fieldLen = 0};
    TypeRef_release(t);
    return __ret359; }
    TypeRef_release(t);
    }
    { Bind __ret360 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret360; }
}
void genCElem_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (len == 0) {
    plew_write((PlewString){"long long", 9});
    return;
    }
    uint64_t er = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (er != 0) {
    if (isCompoundType_c_Comp_ref_U64(&((*c)), er)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), er);
    return;
    }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    plew_write((PlewString){"unsigned char", 13});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    plew_write((PlewString){"int8_t", 6});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    plew_write((PlewString){"int16_t", 7});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    plew_write((PlewString){"uint16_t", 8});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    plew_write((PlewString){"int32_t", 7});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    plew_write((PlewString){"uint32_t", 8});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I64", 3})) {
    plew_write((PlewString){"int64_t", 7});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"U64", 3})) {
    plew_write((PlewString){"uint64_t", 8});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"String", 6})) {
    plew_write((PlewString){"PlewString", 10});
    return;
    }
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    plew_write((PlewString){"long long", 9});
    return;
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), start, len);
}
void genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(Comp* c, uint64_t start, uint64_t len, long long isArray) {
    if (isArray) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), start, len);
    return;
    }
    genCElem_c_Comp_start_U64_len_U64(&((*c)), start, len);
}
void genCType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    genCElem_c_Comp_start_U64_len_U64(&((*c)), start, len);
}
void genTypeInfoCType_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.kind == 1) {
    plew_write((PlewString){"PlewString", 10});
    return;
    }
    if (ti.kind == 2) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen);
    return;
    }
    if (ti.kind == 3) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen);
    return;
    }
    plew_write((PlewString){"long long", 9});
}
long long spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(Comp* c, uint64_t aStart, uint64_t aLen, uint64_t bStart, uint64_t bLen) {
    if (aLen != bLen) {
    { long long __ret361 = 0;
    return __ret361; }
    }
    uint64_t j = 0;
    while (j < aLen) {
    if (PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((aStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((bStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })))) {
    { long long __ret362 = 0;
    return __ret362; }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret363 = 1;
    return __ret363; }
}
int64_t lineOf_c_Comp_offset_U64(Comp* c, uint64_t offset) {
    int64_t line = 1;
    uint64_t i = 0;
    while (i < offset) {
    if (PlewArray_U8_get((*c).bytes, (long long)(i)) == 10) {
    line = ({ int64_t __ov; if (__builtin_add_overflow((line), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { int64_t __ret364 = line;
    return __ret364; }
}
uint64_t exprOffset_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m365 = e;
    if (_m365.tag == 0) {
        uint64_t offset = _m365.data.Int.offset;
        (void)offset;
    { uint64_t __ret366 = offset;
    return __ret366; }
    }
    else if (_m365.tag == 1) {
        uint64_t start = _m365.data.Ident.start;
        (void)start;
        uint64_t len = _m365.data.Ident.len;
        (void)len;
    { uint64_t __ret367 = start;
    return __ret367; }
    }
    else if (_m365.tag == 7) {
        uint64_t start = _m365.data.Str.start;
        (void)start;
        uint64_t len = _m365.data.Str.len;
        (void)len;
    { uint64_t __ret368 = start;
    return __ret368; }
    }
    else if (_m365.tag == 4) {
        uint64_t nameStart = _m365.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m365.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m365.data.Call.args;
        (void)args;
    { uint64_t __ret369 = nameStart;
    return __ret369; }
    }
    else if (_m365.tag == 10) {
        uint64_t recv = _m365.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m365.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m365.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m365.data.Method.args;
        (void)args;
    { uint64_t __ret370 = nameStart;
    return __ret370; }
    }
    else if (_m365.tag == 5) {
        uint64_t base = _m365.data.Field.base;
        (void)base;
        uint64_t nameStart = _m365.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m365.data.Field.nameLen;
        (void)nameLen;
    { uint64_t __ret371 = exprOffset_c_Comp_id_U64(&((*c)), base);
    return __ret371; }
    }
    else if (_m365.tag == 9) {
        uint64_t base = _m365.data.Index.base;
        (void)base;
        uint64_t index = _m365.data.Index.index;
        (void)index;
    { uint64_t __ret372 = exprOffset_c_Comp_id_U64(&((*c)), base);
    return __ret372; }
    }
    else if (_m365.tag == 3) {
        int64_t op = _m365.data.Binary.op;
        (void)op;
        uint64_t lhs = _m365.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m365.data.Binary.rhs;
        (void)rhs;
    { uint64_t __ret373 = exprOffset_c_Comp_id_U64(&((*c)), lhs);
    return __ret373; }
    }
    else if (_m365.tag == 2) {
        int64_t op = _m365.data.Unary.op;
        (void)op;
        uint64_t operand = _m365.data.Unary.operand;
        (void)operand;
    { uint64_t __ret374 = exprOffset_c_Comp_id_U64(&((*c)), operand);
    return __ret374; }
    }
    else if (_m365.tag == 11) {
        uint64_t operand = _m365.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m365.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m365.data.Cast.tyLen;
        (void)tyLen;
    { uint64_t __ret375 = exprOffset_c_Comp_id_U64(&((*c)), operand);
    return __ret375; }
    }
    else if (_m365.tag == 6) {
        uint64_t typeStart = _m365.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m365.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m365.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m365.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m365.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m365.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m365.data.Make.fields;
        (void)fields;
    { uint64_t __ret376 = typeStart;
    return __ret376; }
    }
    else if (_m365.tag == 12) {
        uint64_t scrut = _m365.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m365.data.MatchExpr.arms;
        (void)arms;
    { uint64_t __ret377 = exprOffset_c_Comp_id_U64(&((*c)), scrut);
    return __ret377; }
    }
    else if (_m365.tag == 13) {
        uint64_t cond = _m365.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m365.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m365.data.IfExpr.elseBlk;
        (void)elseBlk;
    { uint64_t __ret378 = exprOffset_c_Comp_id_U64(&((*c)), cond);
    return __ret378; }
    }
    else if (_m365.tag == 14) {
        uint64_t opt = _m365.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m365.data.Coalesce.deflt;
        (void)deflt;
    { uint64_t __ret379 = exprOffset_c_Comp_id_U64(&((*c)), opt);
    return __ret379; }
    }
    else if (_m365.tag == 15) {
        uint64_t expr = _m365.data.Try.expr;
        (void)expr;
    { uint64_t __ret380 = exprOffset_c_Comp_id_U64(&((*c)), expr);
    return __ret380; }
    }
    else if (_m365.tag == 16) {
        uint64_t base = _m365.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m365.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m365.data.Arrow.nameLen;
        (void)nameLen;
    { uint64_t __ret381 = exprOffset_c_Comp_id_U64(&((*c)), base);
    return __ret381; }
    }
    else if (_m365.tag == 17) {
        PlewArray_Param params = _m365.data.Closure.params;
        (void)params;
        long long hasRet = _m365.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m365.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m365.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m365.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m365.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m365.data.Closure.body;
        (void)body;
    { uint64_t __ret382 = retStart;
    return __ret382; }
    }
    else {
    { uint64_t __ret383 = 0;
    return __ret383; }
    }
    }
}
uint64_t findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t firstLabel = (long long)(((*c).funcs).len);
    uint64_t typeMatch = (long long)(((*c).funcs).len);
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(f.params), PlewArray_Arg_share(args))) {
    if (firstLabel == (long long)(((*c).funcs).len)) {
    firstLabel = i;
    }
    if (typeMatch == (long long)(((*c).funcs).len)) {
    if (paramsTypesMatch_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(f.params), PlewArray_Arg_share(args))) {
    typeMatch = i;
    }
    }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    if (typeMatch != (long long)(((*c).funcs).len)) {
    { uint64_t __ret384 = typeMatch;
    return __ret384; }
    }
    { uint64_t __ret385 = firstLabel;
    return __ret385; }
}
uint64_t firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    { uint64_t __ret386 = i;
    Func_release(f);
    return __ret386; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { uint64_t __ret387 = (long long)(((*c).funcs).len);
    return __ret387; }
}
long long funcNameExists_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    { long long __ret388 = (firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen) != (long long)(((*c).funcs).len));
    return __ret388; }
}
uint64_t findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t firstLabel = (long long)(((*c).funcs).len);
    uint64_t typeMatch = (long long)(((*c).funcs).len);
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), recvStart, recvLen, f.recvStart, f.recvLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(f.params), PlewArray_Arg_share(args))) {
    if (firstLabel == (long long)(((*c).funcs).len)) {
    firstLabel = i;
    }
    if (typeMatch == (long long)(((*c).funcs).len)) {
    if (paramsTypesMatch_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(f.params), PlewArray_Arg_share(args))) {
    typeMatch = i;
    }
    }
    }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    if (typeMatch != (long long)(((*c).funcs).len)) {
    { uint64_t __ret389 = typeMatch;
    return __ret389; }
    }
    if (firstLabel != (long long)(((*c).funcs).len)) {
    { uint64_t __ret390 = firstLabel;
    return __ret390; }
    }
    uint64_t ai = 0;
    while (ai < (long long)(((*c).methodAliases).len)) {
    MethodAlias al = PlewArray_MethodAlias_get((*c).methodAliases, (long long)(ai));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), recvStart, recvLen, al.recvStart, al.recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, al.aliasStart, al.aliasLen)) {
    { uint64_t __ret391 = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), recvStart, recvLen, al.realStart, al.realLen, PlewArray_Arg_share(args));
    return __ret391; }
    }
    }
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret392 = (long long)(((*c).funcs).len);
    return __ret392; }
}
uint64_t findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t firstLabel = (long long)(((*c).funcs).len);
    uint64_t typeMatch = (long long)(((*c).funcs).len);
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.isAssoc) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), recvStart, recvLen, f.recvStart, f.recvLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(f.params), PlewArray_Arg_share(args))) {
    if (firstLabel == (long long)(((*c).funcs).len)) {
    firstLabel = i;
    }
    if (typeMatch == (long long)(((*c).funcs).len)) {
    if (paramsTypesMatch_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(f.params), PlewArray_Arg_share(args))) {
    typeMatch = i;
    }
    }
    }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    if (typeMatch != (long long)(((*c).funcs).len)) {
    { uint64_t __ret393 = typeMatch;
    return __ret393; }
    }
    { uint64_t __ret394 = firstLabel;
    return __ret394; }
}
long long isTypeName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len) < (long long)(((*c).structs).len)) {
    { long long __ret395 = 1;
    return __ret395; }
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), PlewArray_EnumDef_get((*c).enums, (long long)(ei)).nameStart, PlewArray_EnumDef_get((*c).enums, (long long)(ei)).nameLen, start, len)) {
    { long long __ret396 = 1;
    return __ret396; }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret397 = (genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), start, len) < (long long)(((*c).structs).len));
    return __ret397; }
}
Bind assocRecvName_c_Comp_recv_U64(Comp* c, uint64_t recv) {
    {
    Expr _m398 = PlewArray_Expr_get((*c).exprs, (long long)(recv));
    if (_m398.tag == 1) {
        uint64_t start = _m398.data.Ident.start;
        (void)start;
        uint64_t len = _m398.data.Ident.len;
        (void)len;
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { Bind __ret399 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret399; }
    }
    if (localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len) < (long long)(((*c).locals).len)) {
    { Bind __ret400 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret400; }
    }
    if (isTypeName_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { Bind __ret401 = (Bind){.nameStart = start, .nameLen = len, .fieldStart = start, .fieldLen = len};
    return __ret401; }
    }
    { Bind __ret402 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret402; }
    }
    else {
    { Bind __ret403 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret403; }
    }
    }
}
long long paramsLabelsOk_c_Comp_params_AParam_args_AArg(Comp* c, PlewArray_Param params, PlewArray_Arg args) {
    if ((long long)((args).len) > (long long)((params).len)) {
    { long long __ret404 = 0;
    return __ret404; }
    }
    uint64_t r = (long long)((args).len);
    while (r < (long long)((params).len)) {
    if (PlewArray_Param_get(params, (long long)(r)).hasDefault) {
    }
    else {
    { long long __ret405 = 0;
    return __ret405; }
    }
    r = ({ uint64_t __ov; if (__builtin_add_overflow((r), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    Arg a = PlewArray_Arg_get(args, (long long)(i));
    Param p = PlewArray_Param_get(params, (long long)(i));
    if (p.noLabel) {
    if (a.hasLabel) {
    { long long __ret406 = 0;
    return __ret406; }
    }
    }
    else {
    if (a.hasLabel) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), a.labelStart, a.labelLen, p.nameStart, p.nameLen)) {
    }
    else {
    { long long __ret407 = 0;
    return __ret407; }
    }
    }
    else {
    { long long __ret408 = 0;
    return __ret408; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret409 = 1;
    return __ret409; }
}
long long argMatchesParam_c_Comp_argExpr_U64_p_Param(Comp* c, uint64_t argExpr, Param p) {
    TypeInfo ti = exprType_c_Comp_id_U64(&((*c)), argExpr);
    if (p.tyIsArray) {
    if (ti.kind == 3) {
    { long long __ret410 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ti.nameStart, ti.nameLen, p.tyStart, p.tyLen);
    return __ret410; }
    }
    { long long __ret411 = 0;
    return __ret411; }
    }
    if (ti.kind == 1) {
    { long long __ret412 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), p.tyStart, p.tyLen, (PlewString){"String", 6});
    return __ret412; }
    }
    if (ti.kind == 2) {
    { long long __ret413 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ti.nameStart, ti.nameLen, p.tyStart, p.tyLen);
    return __ret413; }
    }
    if (ti.nameLen != 0) {
    { long long __ret414 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ti.nameStart, ti.nameLen, p.tyStart, p.tyLen);
    return __ret414; }
    }
    { long long __ret415 = isIntType_c_Comp_start_U64_len_U64(&((*c)), p.tyStart, p.tyLen);
    return __ret415; }
}
long long paramsTypesMatch_c_Comp_params_AParam_args_AArg(Comp* c, PlewArray_Param params, PlewArray_Arg args) {
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    if (i < (long long)((params).len)) {
    if (argMatchesParam_c_Comp_argExpr_U64_p_Param(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, PlewArray_Param_get(params, (long long)(i)))) {
    }
    else {
    { long long __ret416 = 0;
    return __ret416; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret417 = 1;
    return __ret417; }
}
long long callLabelsOk_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    if (funcNameExists_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen)) {
    { long long __ret418 = (findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args)) != (long long)(((*c).funcs).len));
    return __ret418; }
    }
    { long long __ret419 = 1;
    return __ret419; }
}
long long armCovers_c_Comp_arms_AMatchArm_variantStart_U64_variantLen_U64(Comp* c, PlewArray_MatchArm arms, uint64_t variantStart, uint64_t variantLen) {
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    { long long __ret420 = 1;
    MatchArm_release(a);
    return __ret420; }
    }
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), a.variantStart, a.variantLen, variantStart, variantLen)) {
    { long long __ret421 = 1;
    MatchArm_release(a);
    return __ret421; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    { long long __ret422 = 0;
    return __ret422; }
}
long long matchExhaustive_c_Comp_arms_AMatchArm(Comp* c, PlewArray_MatchArm arms) {
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    { long long __ret423 = 1;
    MatchArm_release(a);
    return __ret423; }
    }
    if (enumLen == 0) {
    enumStart = a.enumStart;
    enumLen = a.enumLen;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    if (enumLen == 0) {
    { long long __ret424 = 1;
    return __ret424; }
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (armCovers_c_Comp_arms_AMatchArm_variantStart_U64_variantLen_U64(&((*c)), PlewArray_MatchArm_share(arms), v.nameStart, v.nameLen)) {
    }
    else {
    { long long __ret425 = 0;
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret425; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { long long __ret426 = 1;
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret426; }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret427 = 1;
    return __ret427; }
}
uint64_t variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    { uint64_t __ret428 = vi;
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret428; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret429 = 0;
    return __ret429; }
}
TypeInfo scalarInfo(void) {
    { TypeInfo __ret430 = (TypeInfo){.kind = 0, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret430; }
}
Bind kwSpan_c_Comp_kw_String_kwLen_U64(Comp* c, PlewString kw, uint64_t kwLen) {
    uint64_t n = (long long)(((*c).bytes).len);
    if (n < kwLen) {
    { Bind __ret431 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret431; }
    }
    uint64_t i = 0;
    uint64_t last = ({ uint64_t __ov; if (__builtin_sub_overflow((n), (kwLen), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (i <= last) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), i, kwLen, kw)) {
    { Bind __ret432 = (Bind){.nameStart = i, .nameLen = kwLen, .fieldStart = i, .fieldLen = kwLen};
    return __ret432; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Bind __ret433 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret433; }
}
Bind stringTypeSpan_c_Comp(Comp* c) {
    { Bind __ret434 = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"String", 6}, 6);
    return __ret434; }
}
TypeInfo typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(Comp* c, uint64_t start, uint64_t len, long long isArray) {
    if (isArray) {
    { TypeInfo __ret435 = (TypeInfo){.kind = 3, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret435; }
    }
    if (len == 0) {
    { TypeInfo __ret436 = scalarInfo();
    return __ret436; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"String", 6})) {
    { TypeInfo __ret437 = (TypeInfo){.kind = 1, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret437; }
    }
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { TypeInfo __ret438 = (TypeInfo){.kind = 0, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret438; }
    }
    { TypeInfo __ret439 = (TypeInfo){.kind = 2, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret439; }
}
void addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned) {
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), nameStart, nameLen, tyStart, tyLen, isArray, ty, isInout, isMut, owned, 0);
}
void addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned, uint64_t cnum) {
    PlewArray_Local_push(&((*c).locals), (Local){.nameStart = nameStart, .nameLen = nameLen, .tyStart = tyStart, .tyLen = tyLen, .isArray = isArray, .ty = ty, .isInout = isInout, .isMut = isMut, .owned = owned, .moved = 0, .cnum = cnum});
}
uint64_t shadowCount_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t n = 0;
    uint64_t i = 0;
    while (i < (long long)(((*c).locals).len)) {
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, nameStart, nameLen)) {
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret440 = n;
    return __ret440; }
}
void writeLocalCName_c_Comp_lo_Local(Comp* c, Local lo) {
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), lo.nameStart, lo.nameLen, lo.cnum);
}
void writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(Comp* c, uint64_t start, uint64_t len, uint64_t cnum) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (cnum > 0) {
    plew_write((PlewString){"_s", 2});
    writeU64_n_U64(cnum);
    }
}
uint64_t scopeMark_c_Comp(Comp* c) {
    { uint64_t __ret441 = (long long)(((*c).locals).len);
    return __ret441; }
}
void emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(Comp* c, uint64_t mark, uint64_t exclIdx) {
    uint64_t i = (long long)(((*c).locals).len);
    while (i > mark) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i == exclIdx) {
    }
    else {
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (lo.moved) {
    }
    else {
    if (lo.owned) {
    if (lo.isArray) {
    plew_write((PlewString){"    ", 4});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), lo.tyStart, lo.tyLen);
    plew_write((PlewString){"_release(", 9});
    writeLocalCName_c_Comp_lo_Local(&((*c)), lo);
    plew_write((PlewString){");\n", 3});
    }
    else {
    if (isBoxedLocalAt_c_Comp_nameStart_U64(&((*c)), lo.nameStart)) {
    plew_write((PlewString){"    plew_arc_release(((long long*)", 34});
    writeLocalCName_c_Comp_lo_Local(&((*c)), lo);
    plew_write((PlewString){") - 1);\n", 8});
    }
    else {
    if (isFnType_c_Comp_ref_U64(&((*c)), lo.ty)) {
    plew_write((PlewString){"    plew_closure_release(", 25});
    writeLocalCName_c_Comp_lo_Local(&((*c)), lo);
    plew_write((PlewString){");\n", 3});
    }
    else {
    if (isRefInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    emitRefRelease_c_Comp_nameStart_U64_nameLen_U64_refTy_U64_cnum_U64(&((*c)), lo.nameStart, lo.nameLen, lo.ty, lo.cnum);
    }
    else {
    if (structHasDeinit_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen)) {
    plew_write((PlewString){"    ", 4});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen);
    plew_write((PlewString){"_deinit(", 8});
    writeLocalCName_c_Comp_lo_Local(&((*c)), lo);
    plew_write((PlewString){");\n", 3});
    }
    if (structLocalReleasable_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen)) {
    plew_write((PlewString){"    ", 4});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen);
    plew_write((PlewString){"_release(", 9});
    writeLocalCName_c_Comp_lo_Local(&((*c)), lo);
    plew_write((PlewString){");\n", 3});
    }
    }
    }
    }
    }
    }
    }
    }
    }
}
void emitRefRelease_c_Comp_nameStart_U64_nameLen_U64_refTy_U64_cnum_U64(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t refTy, uint64_t cnum) {
    TypeRef rt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(refTy)));
    TypeInfo bti = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){"    if (", 8});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){") { long long* __rrc = ((long long*)", 36});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){") - 1; if ((--(*__rrc)) == 0) {", 31});
    if (bti.kind == 3) {
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), bti.nameStart, bti.nameLen);
    plew_write((PlewString){"_release(*", 10});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){");", 2});
    }
    else {
    if (bti.kind == 2) {
    if (structHasDeinit_c_Comp_start_U64_len_U64(&((*c)), bti.nameStart, bti.nameLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bti.nameStart, bti.nameLen);
    plew_write((PlewString){"_deinit(*", 9});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){");", 2});
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), bti.nameStart, bti.nameLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bti.nameStart, bti.nameLen);
    plew_write((PlewString){"_release(*", 10});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){");", 2});
    }
    }
    }
    plew_write((PlewString){" free(__rrc); } }\n", 18});
    TypeRef_release(rt);
}
long long structHasDeinit_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).deinits).len)) {
    Bind d = PlewArray_Bind_get((*c).deinits, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), d.nameStart, d.nameLen, start, len)) {
    { long long __ret442 = 1;
    return __ret442; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret443 = 0;
    return __ret443; }
}
long long structLocalReleasable_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret444 = 0;
    return __ret444; }
    }
    if ((long long)((PlewArray_StructDef_get((*c).structs, (long long)(si)).typeParams).len) > 0) {
    { long long __ret445 = 0;
    return __ret445; }
    }
    { long long __ret446 = structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), start, len);
    return __ret446; }
}
void popLocals_c_Comp_mark_U64(Comp* c, uint64_t mark) {
    PlewArray_Local kept = PlewArray_Local_new();
    uint64_t i = 0;
    while (i < mark) {
    PlewArray_Local_push(&(kept), PlewArray_Local_get((*c).locals, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).locals = PlewArray_Local_share(kept);
    PlewArray_Local_release(kept);
}
void scopeExit_c_Comp_mark_U64(Comp* c, uint64_t mark) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), mark, (long long)(((*c).locals).len));
    popLocals_c_Comp_mark_U64(&((*c)), mark);
}
long long localIsMutable_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { long long __ret447 = (*c).curSelfInout;
    return __ret447; }
    }
    if ((*c).curInClosure) {
    if (isCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(&((*c)), (*c).curClosureId, start, len)) {
    { long long __ret448 = isBoxedCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(&((*c)), (*c).curClosureId, start, len);
    return __ret448; }
    }
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (lo.isMut) {
    { long long __ret449 = 1;
    return __ret449; }
    }
    { long long __ret450 = lo.isInout;
    return __ret450; }
    }
    }
    { long long __ret451 = 1;
    return __ret451; }
}
long long isSelfRef_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if ((*c).curHasRecv) {
    { long long __ret452 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"self", 4});
    return __ret452; }
    }
    { long long __ret453 = 0;
    return __ret453; }
}
long long isInoutLocal_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { long long __ret454 = (*c).curSelfInout;
    return __ret454; }
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    { long long __ret455 = lo.isInout;
    return __ret455; }
    }
    }
    { long long __ret456 = 0;
    return __ret456; }
}
long long typeIsUnique_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret457 = 0;
    return __ret457; }
    }
    { long long __ret458 = PlewArray_StructDef_get((*c).structs, (long long)(si)).isUnique;
    return __ret458; }
}
uint64_t localIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    { uint64_t __ret459 = i;
    return __ret459; }
    }
    }
    { uint64_t __ret460 = (long long)(((*c).locals).len);
    return __ret460; }
}
long long localMoved_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    { long long __ret461 = lo.moved;
    return __ret461; }
    }
    }
    { long long __ret462 = 0;
    return __ret462; }
}
void markMovedLocal_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t target = (long long)(((*c).locals).len);
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    target = i;
    i = 0;
    }
    }
    if (target >= (long long)(((*c).locals).len)) {
    return;
    }
    PlewArray_Local rebuilt = PlewArray_Local_new();
    uint64_t j = 0;
    while (j < (long long)(((*c).locals).len)) {
    Local lo = PlewArray_Local_get((*c).locals, (long long)(j));
    if (j == target) {
    PlewArray_Local_push(&(rebuilt), (Local){.nameStart = lo.nameStart, .nameLen = lo.nameLen, .tyStart = lo.tyStart, .tyLen = lo.tyLen, .isArray = lo.isArray, .ty = lo.ty, .isInout = lo.isInout, .isMut = lo.isMut, .owned = lo.owned, .moved = 1, .cnum = lo.cnum});
    }
    else {
    PlewArray_Local_push(&(rebuilt), lo);
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).locals = PlewArray_Local_share(rebuilt);
    PlewArray_Local_release(rebuilt);
}
void markMovedExpr_c_Comp_exprId_U64(Comp* c, uint64_t exprId) {
    {
    Expr _m463 = PlewArray_Expr_get((*c).exprs, (long long)(exprId));
    if (_m463.tag == 1) {
        uint64_t start = _m463.data.Ident.start;
        (void)start;
        uint64_t len = _m463.data.Ident.len;
        (void)len;
    markMovedLocal_c_Comp_start_U64_len_U64(&((*c)), start, len);
    }
    else {
    }
    }
}
TypeInfo fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    { TypeInfo __ret464 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    PlewArray_FieldDef_release(fs);
    StructDef_release(s);
    return __ret464; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { TypeInfo __ret465 = scalarInfo();
    return __ret465; }
}
long long fieldDeclaredMut_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    { long long __ret466 = f.isMut;
    PlewArray_FieldDef_release(fs);
    StructDef_release(s);
    return __ret466; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { long long __ret467 = 1;
    return __ret467; }
}
long long placeIsMutable_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m468 = e;
    if (_m468.tag == 1) {
        uint64_t start = _m468.data.Ident.start;
        (void)start;
        uint64_t len = _m468.data.Ident.len;
        (void)len;
    { long long __ret469 = localIsMutable_c_Comp_start_U64_len_U64(&((*c)), start, len);
    return __ret469; }
    }
    else if (_m468.tag == 5) {
        uint64_t base = _m468.data.Field.base;
        (void)base;
        uint64_t nameStart = _m468.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m468.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 2) {
    if (fieldDeclaredMut_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen)) {
    { long long __ret470 = placeIsMutable_c_Comp_id_U64(&((*c)), base);
    return __ret470; }
    }
    { long long __ret471 = 0;
    return __ret471; }
    }
    { long long __ret472 = placeIsMutable_c_Comp_id_U64(&((*c)), base);
    return __ret472; }
    }
    else if (_m468.tag == 9) {
        uint64_t base = _m468.data.Index.base;
        (void)base;
        uint64_t index = _m468.data.Index.index;
        (void)index;
    { long long __ret473 = placeIsMutable_c_Comp_id_U64(&((*c)), base);
    return __ret473; }
    }
    else if (_m468.tag == 16) {
        uint64_t base = _m468.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m468.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m468.data.Arrow.nameLen;
        (void)nameLen;
    { long long __ret474 = 1;
    return __ret474; }
    }
    else {
    { long long __ret475 = 1;
    return __ret475; }
    }
    }
}
TypeInfo exprType_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m476 = e;
    if (_m476.tag == 0) {
        uint64_t tyStart = _m476.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m476.data.Int.tyLen;
        (void)tyLen;
    if (tyLen != 0) {
    { TypeInfo __ret477 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), tyStart, tyLen, 0);
    return __ret477; }
    }
    { TypeInfo __ret478 = scalarInfo();
    return __ret478; }
    }
    else if (_m476.tag == 7) {
        uint64_t start = _m476.data.Str.start;
        (void)start;
        uint64_t len = _m476.data.Str.len;
        (void)len;
    { TypeInfo __ret479 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret479; }
    }
    else if (_m476.tag == 1) {
        uint64_t start = _m476.data.Ident.start;
        (void)start;
        uint64_t len = _m476.data.Ident.len;
        (void)len;
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    if ((*c).curRecvInstRef != 0) {
    TypeRef rt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)((*c).curRecvInstRef)));
    { TypeInfo __ret480 = (TypeInfo){.kind = 2, .nameStart = rt.nameStart, .nameLen = rt.nameLen, .ref = (*c).curRecvInstRef};
    TypeRef_release(rt);
    return __ret480; }
    TypeRef_release(rt);
    }
    { TypeInfo __ret481 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), (*c).curRecvStart, (*c).curRecvLen, 0);
    return __ret481; }
    }
    if ((*c).curInClosure) {
    uint64_t ci = 0;
    while (ci < (long long)(((*c).captures).len)) {
    CaptureEntry ce = PlewArray_CaptureEntry_get((*c).captures, (long long)(ci));
    if (ce.closureId == (*c).curClosureId) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ce.nameStart, ce.nameLen, start, len)) {
    if (isRefInst_c_Comp_ref_U64(&((*c)), ce.ty)) {
    TypeRef rt2 = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ce.ty)));
    { TypeInfo __ret482 = (TypeInfo){.kind = 2, .nameStart = rt2.nameStart, .nameLen = rt2.nameLen, .ref = ce.ty};
    TypeRef_release(rt2);
    return __ret482; }
    TypeRef_release(rt2);
    }
    { TypeInfo __ret483 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), ce.tyStart, ce.tyLen, ce.isArray);
    return __ret483; }
    }
    }
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    uint64_t i = (long long)(((*c).locals).len);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = PlewArray_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    TypeRef lt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(lo.ty)));
    { TypeInfo __ret484 = (TypeInfo){.kind = 2, .nameStart = lt.nameStart, .nameLen = lt.nameLen, .ref = lo.ty};
    TypeRef_release(lt);
    return __ret484; }
    TypeRef_release(lt);
    }
    if (isRefInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    TypeRef lt2 = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(lo.ty)));
    { TypeInfo __ret485 = (TypeInfo){.kind = 2, .nameStart = lt2.nameStart, .nameLen = lt2.nameLen, .ref = lo.ty};
    TypeRef_release(lt2);
    return __ret485; }
    TypeRef_release(lt2);
    }
    if (lo.isArray) {
    }
    else {
    uint64_t k = 0;
    while (k < (long long)(((*c).curTypeParams).len)) {
    Bind tp = PlewArray_Bind_get((*c).curTypeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.tyStart, lo.tyLen, tp.nameStart, tp.nameLen)) {
    { TypeInfo __ret486 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get((*c).curTypeArgs, (long long)(k)));
    return __ret486; }
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    { TypeInfo __ret487 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), lo.tyStart, lo.tyLen, lo.isArray);
    return __ret487; }
    }
    }
    { TypeInfo __ret488 = scalarInfo();
    return __ret488; }
    }
    else if (_m476.tag == 2) {
        int64_t op = _m476.data.Unary.op;
        (void)op;
        uint64_t operand = _m476.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    { TypeInfo __ret489 = exprType_c_Comp_id_U64(&((*c)), operand);
    return __ret489; }
    }
    if (op == 79) {
    { TypeInfo __ret490 = exprType_c_Comp_id_U64(&((*c)), operand);
    return __ret490; }
    }
    { TypeInfo __ret491 = scalarInfo();
    return __ret491; }
    }
    else if (_m476.tag == 3) {
        int64_t op = _m476.data.Binary.op;
        (void)op;
        uint64_t lhs = _m476.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m476.data.Binary.rhs;
        (void)rhs;
    if (op >= 56) {
    if (op <= 60) {
    { TypeInfo __ret492 = exprType_c_Comp_id_U64(&((*c)), lhs);
    return __ret492; }
    }
    }
    if (op >= 74) {
    if (op <= 78) {
    { TypeInfo __ret493 = exprType_c_Comp_id_U64(&((*c)), lhs);
    return __ret493; }
    }
    }
    { TypeInfo __ret494 = scalarInfo();
    return __ret494; }
    }
    else if (_m476.tag == 4) {
        uint64_t nameStart = _m476.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m476.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m476.data.Call.args;
        (void)args;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readStdin", 9})) {
    { TypeInfo __ret495 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret495; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readFile", 8})) {
    { TypeInfo __ret496 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret496; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readFileBytes", 13})) {
    { TypeInfo __ret497 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret497; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"argAt", 5})) {
    { TypeInfo __ret498 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret498; }
    }
    uint64_t fi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args));
    if (fi < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRet) {
    if (isGenericFreeFn_c_Comp_fi_U64(&((*c)), fi)) {
    if (f.retIsArray) {
    }
    else {
    PlewArray_U64 inferred = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), f, PlewArray_Arg_share(args));
    uint64_t k = 0;
    while (k < (long long)((f.typeParams).len)) {
    Bind tp = PlewArray_Bind_get(f.typeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.retStart, f.retLen, tp.nameStart, tp.nameLen)) {
    if (k < (long long)((inferred).len)) {
    if (PlewArray_U64_get(inferred, (long long)(k)) != 0) {
    { TypeInfo __ret499 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(inferred, (long long)(k)));
    PlewArray_U64_release(inferred);
    Func_release(f);
    return __ret499; }
    }
    }
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U64_release(inferred);
    }
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), f.retTy)) {
    TypeRef rtr = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(f.retTy)));
    { TypeInfo __ret500 = (TypeInfo){.kind = 2, .nameStart = rtr.nameStart, .nameLen = rtr.nameLen, .ref = f.retTy};
    TypeRef_release(rtr);
    Func_release(f);
    return __ret500; }
    TypeRef_release(rtr);
    }
    { TypeInfo __ret501 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), f.retStart, f.retLen, f.retIsArray);
    Func_release(f);
    return __ret501; }
    }
    { TypeInfo __ret502 = scalarInfo();
    Func_release(f);
    return __ret502; }
    Func_release(f);
    }
    { TypeInfo __ret503 = scalarInfo();
    return __ret503; }
    }
    else if (_m476.tag == 5) {
        uint64_t base = _m476.data.Field.base;
        (void)base;
        uint64_t nameStart = _m476.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m476.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 1) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"bytes", 5})) {
    Bind u8 = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"U8", 2}, 2);
    if (u8.nameLen != 0) {
    { TypeInfo __ret504 = (TypeInfo){.kind = 3, .nameStart = u8.nameStart, .nameLen = u8.nameLen, .ref = 0};
    return __ret504; }
    }
    }
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    { TypeInfo __ret505 = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.ref, nameStart, nameLen);
    return __ret505; }
    }
    if (bt.kind == 2) {
    { TypeInfo __ret506 = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    return __ret506; }
    }
    { TypeInfo __ret507 = scalarInfo();
    return __ret507; }
    }
    else if (_m476.tag == 6) {
        uint64_t typeStart = _m476.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m476.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m476.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m476.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m476.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m476.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m476.data.Make.fields;
        (void)fields;
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ty)) {
    { TypeInfo __ret508 = (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = ty};
    return __ret508; }
    }
    { TypeInfo __ret509 = (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = 0};
    return __ret509; }
    }
    else if (_m476.tag == 8) {
        PlewArray_U64 elems = _m476.data.Array.elems;
        (void)elems;
    { TypeInfo __ret510 = scalarInfo();
    return __ret510; }
    }
    else if (_m476.tag == 9) {
        uint64_t base = _m476.data.Index.base;
        (void)base;
        uint64_t index = _m476.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    uint64_t er = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    if (er != 0) {
    uint64_t rr = resolveTy_c_Comp_tyRef_U64(&((*c)), er);
    if (rr < (long long)(((*c).types).len)) {
    TypeRef rt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(rr)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), rt.nameStart, rt.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((rt.args).len) > 0) {
    Bind xn = arrayElemNameForRef_c_Comp_elemRef_U64(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    { TypeInfo __ret511 = (TypeInfo){.kind = 3, .nameStart = xn.nameStart, .nameLen = xn.nameLen, .ref = 0};
    TypeRef_release(rt);
    return __ret511; }
    }
    }
    TypeRef_release(rt);
    }
    }
    { TypeInfo __ret512 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), bt.nameStart, bt.nameLen, 0);
    return __ret512; }
    }
    { TypeInfo __ret513 = scalarInfo();
    return __ret513; }
    }
    else if (_m476.tag == 10) {
        uint64_t recv = _m476.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m476.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m476.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m476.data.Method.args;
        (void)args;
    Bind arn = assocRecvName_c_Comp_recv_U64(&((*c)), recv);
    if (arn.nameLen != 0) {
    uint64_t afi = findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), arn.nameStart, arn.nameLen, nameStart, nameLen, PlewArray_Arg_share(args));
    if (afi == (long long)(((*c).funcs).len)) {
    { TypeInfo __ret514 = scalarInfo();
    return __ret514; }
    }
    Func af = Func_share(PlewArray_Func_get((*c).funcs, (long long)(afi)));
    if (af.hasRet) {
    { TypeInfo __ret515 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), af.retStart, af.retLen, af.retIsArray);
    Func_release(af);
    return __ret515; }
    }
    { TypeInfo __ret516 = scalarInfo();
    Func_release(af);
    return __ret516; }
    Func_release(af);
    }
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (rt.kind == 2) {
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen, PlewArray_Arg_share(args));
    if (mi == (long long)(((*c).funcs).len)) {
    { TypeInfo __ret517 = scalarInfo();
    return __ret517; }
    }
    Func mf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(mi)));
    if (mf.hasRet) {
    { TypeInfo __ret518 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), mf.retStart, mf.retLen, mf.retIsArray);
    Func_release(mf);
    return __ret518; }
    }
    { TypeInfo __ret519 = scalarInfo();
    Func_release(mf);
    return __ret519; }
    Func_release(mf);
    }
    { TypeInfo __ret520 = scalarInfo();
    return __ret520; }
    }
    else if (_m476.tag == 11) {
        uint64_t operand = _m476.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m476.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m476.data.Cast.tyLen;
        (void)tyLen;
    { TypeInfo __ret521 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), tyStart, tyLen, 0);
    return __ret521; }
    }
    else if (_m476.tag == 12) {
        uint64_t scrut = _m476.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m476.data.MatchExpr.arms;
        (void)arms;
    if ((long long)((arms).len) > 0) {
    { TypeInfo __ret522 = exprType_c_Comp_id_U64(&((*c)), PlewArray_MatchArm_get(arms, (long long)(0)).body);
    return __ret522; }
    }
    { TypeInfo __ret523 = scalarInfo();
    return __ret523; }
    }
    else if (_m476.tag == 13) {
        uint64_t cond = _m476.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m476.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m476.data.IfExpr.elseBlk;
        (void)elseBlk;
    uint64_t g = blockGiveExpr_c_Comp_blkId_U64(&((*c)), thenBlk);
    if (g < (long long)(((*c).exprs).len)) {
    { TypeInfo __ret524 = exprType_c_Comp_id_U64(&((*c)), g);
    return __ret524; }
    }
    { TypeInfo __ret525 = scalarInfo();
    return __ret525; }
    }
    else if (_m476.tag == 14) {
        uint64_t opt = _m476.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m476.data.Coalesce.deflt;
        (void)deflt;
    { TypeInfo __ret526 = exprType_c_Comp_id_U64(&((*c)), deflt);
    return __ret526; }
    }
    else if (_m476.tag == 15) {
        uint64_t expr = _m476.data.Try.expr;
        (void)expr;
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), expr);
    if (isGenericInst_c_Comp_ref_U64(&((*c)), rt.ref)) {
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(rt.ref)));
    if ((long long)((inst.args).len) > 0) {
    { TypeInfo __ret527 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(inst.args, (long long)(0)));
    TypeRef_release(inst);
    return __ret527; }
    }
    TypeRef_release(inst);
    }
    { TypeInfo __ret528 = scalarInfo();
    return __ret528; }
    }
    else if (_m476.tag == 16) {
        uint64_t base = _m476.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m476.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m476.data.Arrow.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (isRefInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(bt.ref)));
    TypeInfo pt = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(inst.args, (long long)(0)));
    if (pt.kind == 2) {
    { TypeInfo __ret529 = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), pt.nameStart, pt.nameLen, nameStart, nameLen);
    TypeRef_release(inst);
    return __ret529; }
    }
    TypeRef_release(inst);
    }
    { TypeInfo __ret530 = scalarInfo();
    return __ret530; }
    }
    else if (_m476.tag == 17) {
        PlewArray_Param params = _m476.data.Closure.params;
        (void)params;
        long long hasRet = _m476.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m476.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m476.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m476.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m476.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m476.data.Closure.body;
        (void)body;
    { TypeInfo __ret531 = scalarInfo();
    return __ret531; }
    }
    else if (_m476.tag == 18) {
        uint64_t operand = _m476.data.Move.operand;
        (void)operand;
        long long isBorrow = _m476.data.Move.isBorrow;
        (void)isBorrow;
    { TypeInfo __ret532 = exprType_c_Comp_id_U64(&((*c)), operand);
    return __ret532; }
    }
    else { __builtin_unreachable(); }
    }
    { TypeInfo __ret533 = scalarInfo();
    return __ret533; }
}
uint64_t blockGiveExpr_c_Comp_blkId_U64(Comp* c, uint64_t blkId) {
    Block blk = Block_share(PlewArray_Block_get((*c).blocks, (long long)(blkId)));
    PlewArray_U64 stmts = PlewArray_U64_share(blk.stmts);
    uint64_t i = 0;
    uint64_t found = (long long)(((*c).exprs).len);
    while (i < (long long)((stmts).len)) {
    Stmt s = PlewArray_Stmt_get((*c).stmts, (long long)(PlewArray_U64_get(stmts, (long long)(i))));
    {
    Stmt _m534 = s;
    if (_m534.tag == 10) {
        uint64_t value = _m534.data.Give.value;
        (void)value;
    found = value;
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret535 = found;
    PlewArray_U64_release(stmts);
    Block_release(blk);
    return __ret535; }
    PlewArray_U64_release(stmts);
    Block_release(blk);
}
void addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), bindStart, bindLen, f.tyStart, f.tyLen, f.tyIsArray, f.ty, 0, 0, 0);
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
void genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, bindStart, bindLen)) {
    genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
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
PlewString binOpStr_op_I64(int64_t op) {
    if (op == 56) {
    { PlewString __ret536 = (PlewString){" + ", 3};
    return __ret536; }
    }
    if (op == 57) {
    { PlewString __ret537 = (PlewString){" - ", 3};
    return __ret537; }
    }
    if (op == 58) {
    { PlewString __ret538 = (PlewString){" * ", 3};
    return __ret538; }
    }
    if (op == 59) {
    { PlewString __ret539 = (PlewString){" / ", 3};
    return __ret539; }
    }
    if (op == 60) {
    { PlewString __ret540 = (PlewString){" % ", 3};
    return __ret540; }
    }
    if (op == 50) {
    { PlewString __ret541 = (PlewString){" == ", 4};
    return __ret541; }
    }
    if (op == 51) {
    { PlewString __ret542 = (PlewString){" != ", 4};
    return __ret542; }
    }
    if (op == 52) {
    { PlewString __ret543 = (PlewString){" < ", 3};
    return __ret543; }
    }
    if (op == 53) {
    { PlewString __ret544 = (PlewString){" <= ", 4};
    return __ret544; }
    }
    if (op == 54) {
    { PlewString __ret545 = (PlewString){" > ", 3};
    return __ret545; }
    }
    if (op == 55) {
    { PlewString __ret546 = (PlewString){" >= ", 4};
    return __ret546; }
    }
    if (op == 61) {
    { PlewString __ret547 = (PlewString){" && ", 4};
    return __ret547; }
    }
    if (op == 62) {
    { PlewString __ret548 = (PlewString){" || ", 4};
    return __ret548; }
    }
    if (op == 74) {
    { PlewString __ret549 = (PlewString){" & ", 3};
    return __ret549; }
    }
    if (op == 75) {
    { PlewString __ret550 = (PlewString){" | ", 3};
    return __ret550; }
    }
    if (op == 76) {
    { PlewString __ret551 = (PlewString){" ^ ", 3};
    return __ret551; }
    }
    if (op == 77) {
    { PlewString __ret552 = (PlewString){" << ", 4};
    return __ret552; }
    }
    if (op == 78) {
    { PlewString __ret553 = (PlewString){" >> ", 4};
    return __ret553; }
    }
    { PlewString __ret554 = (PlewString){" ? ", 3};
    return __ret554; }
}
PlewString unaryOpStr_op_I64(int64_t op) {
    if (op == 57) {
    { PlewString __ret555 = (PlewString){"-", 1};
    return __ret555; }
    }
    if (op == 79) {
    { PlewString __ret556 = (PlewString){"~", 1};
    return __ret556; }
    }
    { PlewString __ret557 = (PlewString){"!", 1};
    return __ret557; }
}
int64_t strDecodedLen_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
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
    { int64_t __ret558 = n;
    return __ret558; }
}
long long isCheckedArith_op_I64(int64_t op) {
    if (op == 56) {
    { long long __ret559 = 1;
    return __ret559; }
    }
    if (op == 57) {
    { long long __ret560 = 1;
    return __ret560; }
    }
    if (op == 58) {
    { long long __ret561 = 1;
    return __ret561; }
    }
    { long long __ret562 = 0;
    return __ret562; }
}
int64_t compoundCheckedBin_op_I64(int64_t op) {
    if (op == 67) {
    { int64_t __ret563 = 56;
    return __ret563; }
    }
    if (op == 68) {
    { int64_t __ret564 = 57;
    return __ret564; }
    }
    if (op == 69) {
    { int64_t __ret565 = 58;
    return __ret565; }
    }
    { int64_t __ret566 = 0;
    return __ret566; }
}
PlewString overflowBuiltin_op_I64(int64_t op) {
    if (op == 56) {
    { PlewString __ret567 = (PlewString){"__builtin_add_overflow", 22};
    return __ret567; }
    }
    if (op == 57) {
    { PlewString __ret568 = (PlewString){"__builtin_sub_overflow", 22};
    return __ret568; }
    }
    { PlewString __ret569 = (PlewString){"__builtin_mul_overflow", 22};
    return __ret569; }
}
TypeInfo arithIntType_c_Comp_lhs_U64_rhs_U64(Comp* c, uint64_t lhs, uint64_t rhs) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 0) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), lt.nameStart, lt.nameLen)) {
    { TypeInfo __ret570 = lt;
    return __ret570; }
    }
    }
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), rhs);
    if (rt.kind == 0) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), rt.nameStart, rt.nameLen)) {
    { TypeInfo __ret571 = rt;
    return __ret571; }
    }
    }
    { TypeInfo __ret572 = scalarInfo();
    return __ret572; }
}
void genCheckedArith_c_Comp_op_I64_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64(Comp* c, int64_t op, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen) {
    plew_write((PlewString){"({ ", 3});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __ov; if (", 11});
    plew_write(overflowBuiltin_op_I64(op));
    plew_write((PlewString){"((", 2});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){"), (", 4});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){"), &__ov)) plew_panic((PlewString){\"integer overflow\", 16}); __ov; })", 69});
}
void genArrayGet_c_Comp_base_U64_index_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t base, uint64_t index, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_get(", 5});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){", (long long)(", 14});
    genExpr_c_Comp_id_U64(&((*c)), index);
    plew_write((PlewString){"))", 2});
}
PlewString intMinMacro_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { PlewString __ret573 = (PlewString){"INT8_MIN", 8};
    return __ret573; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { PlewString __ret574 = (PlewString){"INT16_MIN", 9};
    return __ret574; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { PlewString __ret575 = (PlewString){"INT32_MIN", 9};
    return __ret575; }
    }
    { PlewString __ret576 = (PlewString){"INT64_MIN", 9};
    return __ret576; }
}
void genCheckedNeg_c_Comp_operand_U64_tyStart_U64_tyLen_U64(Comp* c, uint64_t operand, uint64_t tyStart, uint64_t tyLen) {
    plew_write((PlewString){"({ ", 3});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __ov; if (__builtin_sub_overflow((", 35});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){")0, (", 5});
    genExpr_c_Comp_id_U64(&((*c)), operand);
    plew_write((PlewString){"), &__ov)) plew_panic((PlewString){\"integer overflow\", 16}); __ov; })", 69});
}
void genCheckedDiv_c_Comp_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64_isMod_Bool(Comp* c, uint64_t lhs, uint64_t rhs, uint64_t tyStart, uint64_t tyLen, long long isMod) {
    long long signedTy = intSigned_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){"({ ", 3});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __dl = (", 9});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){"); ", 3});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){" __dr = (", 9});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
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
    plew_write(intMinMacro_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen));
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
PlewString assignOpStr_op_I64(int64_t op) {
    if (op == 49) {
    { PlewString __ret577 = (PlewString){" = ", 3};
    return __ret577; }
    }
    if (op == 67) {
    { PlewString __ret578 = (PlewString){" += ", 4};
    return __ret578; }
    }
    if (op == 68) {
    { PlewString __ret579 = (PlewString){" -= ", 4};
    return __ret579; }
    }
    if (op == 69) {
    { PlewString __ret580 = (PlewString){" *= ", 4};
    return __ret580; }
    }
    if (op == 70) {
    { PlewString __ret581 = (PlewString){" /= ", 4};
    return __ret581; }
    }
    if (op == 71) {
    { PlewString __ret582 = (PlewString){" %= ", 4};
    return __ret582; }
    }
    if (op == 80) {
    { PlewString __ret583 = (PlewString){" &= ", 4};
    return __ret583; }
    }
    if (op == 81) {
    { PlewString __ret584 = (PlewString){" |= ", 4};
    return __ret584; }
    }
    if (op == 82) {
    { PlewString __ret585 = (PlewString){" ^= ", 4};
    return __ret585; }
    }
    if (op == 83) {
    { PlewString __ret586 = (PlewString){" <<= ", 5};
    return __ret586; }
    }
    { PlewString __ret587 = (PlewString){" >>= ", 5};
    return __ret587; }
}
long long isCompoundDiv_op_I64(int64_t op) {
    if (op == 70) {
    { long long __ret588 = 1;
    return __ret588; }
    }
    if (op == 71) {
    { long long __ret589 = 1;
    return __ret589; }
    }
    { long long __ret590 = 0;
    return __ret590; }
}
PlewString compoundDivFn_op_I64(int64_t op) {
    if (op == 70) {
    { PlewString __ret591 = (PlewString){"plew_div(", 9};
    return __ret591; }
    }
    if (op == 71) {
    { PlewString __ret592 = (PlewString){"plew_mod(", 9};
    return __ret592; }
    }
    { PlewString __ret593 = (PlewString){"", 0};
    return __ret593; }
}
PlewString assignToBinStr_op_I64(int64_t op) {
    if (op == 67) {
    { PlewString __ret594 = (PlewString){" + ", 3};
    return __ret594; }
    }
    if (op == 68) {
    { PlewString __ret595 = (PlewString){" - ", 3};
    return __ret595; }
    }
    if (op == 69) {
    { PlewString __ret596 = (PlewString){" * ", 3};
    return __ret596; }
    }
    if (op == 70) {
    { PlewString __ret597 = (PlewString){" / ", 3};
    return __ret597; }
    }
    if (op == 71) {
    { PlewString __ret598 = (PlewString){" % ", 3};
    return __ret598; }
    }
    if (op == 80) {
    { PlewString __ret599 = (PlewString){" & ", 3};
    return __ret599; }
    }
    if (op == 81) {
    { PlewString __ret600 = (PlewString){" | ", 3};
    return __ret600; }
    }
    if (op == 82) {
    { PlewString __ret601 = (PlewString){" ^ ", 3};
    return __ret601; }
    }
    if (op == 83) {
    { PlewString __ret602 = (PlewString){" << ", 4};
    return __ret602; }
    }
    { PlewString __ret603 = (PlewString){" >> ", 4};
    return __ret603; }
}
ConstInt notConst(void) {
    { ConstInt __ret604 = (ConstInt){.isConst = 0, .value = 0};
    return __ret604; }
}
ConstInt foldConst_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m605 = e;
    if (_m605.tag == 0) {
        int64_t value = _m605.data.Int.value;
        (void)value;
        long long isBool = _m605.data.Int.isBool;
        (void)isBool;
    if (isBool) {
    { ConstInt __ret606 = notConst();
    return __ret606; }
    }
    { ConstInt __ret607 = (ConstInt){.isConst = 1, .value = value};
    return __ret607; }
    }
    else if (_m605.tag == 2) {
        int64_t op = _m605.data.Unary.op;
        (void)op;
        uint64_t operand = _m605.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    ConstInt o = foldConst_c_Comp_id_U64(&((*c)), operand);
    if (o.isConst) {
    { ConstInt __ret608 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_sub_overflow((0), (o.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret608; }
    }
    }
    { ConstInt __ret609 = notConst();
    return __ret609; }
    }
    else if (_m605.tag == 3) {
        int64_t op = _m605.data.Binary.op;
        (void)op;
        uint64_t lhs = _m605.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m605.data.Binary.rhs;
        (void)rhs;
    ConstInt a = foldConst_c_Comp_id_U64(&((*c)), lhs);
    ConstInt b = foldConst_c_Comp_id_U64(&((*c)), rhs);
    if (a.isConst) {
    if (b.isConst) {
    if (op == 56) {
    { ConstInt __ret610 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_add_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret610; }
    }
    if (op == 57) {
    { ConstInt __ret611 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_sub_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret611; }
    }
    if (op == 58) {
    { ConstInt __ret612 = (ConstInt){.isConst = 1, .value = ({ int64_t __ov; if (__builtin_mul_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })};
    return __ret612; }
    }
    }
    }
    { ConstInt __ret613 = notConst();
    return __ret613; }
    }
    else {
    { ConstInt __ret614 = notConst();
    return __ret614; }
    }
    }
}
long long tiIsInt_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.kind == 0) {
    if (ti.nameLen != 0) {
    { long long __ret615 = isIntType_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen);
    return __ret615; }
    }
    }
    { long long __ret616 = 0;
    return __ret616; }
}
void checkLitLeaf_c_Comp_value_I64_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(Comp* c, int64_t value, uint64_t offset, long long isBool, uint64_t tyStart, uint64_t tyLen, uint64_t eKind, uint64_t eBits, long long eSgn) {
    if (isBool) {
    return;
    }
    if (tyLen != 0) {
    if (litFitsType_c_Comp_value_I64_dstStart_U64_dstLen_U64(&((*c)), value, tyStart, tyLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"integer literal is out of range for its type", 44});
    }
    return;
    }
    if (eKind == 1) {
    if (litFitsBits_value_I64_bits_U64_sgn_Bool(value, eBits, eSgn)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"integer literal is out of range for its type", 44});
    }
    return;
    }
    if (eKind == 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"integer literal has no type from context; add a type annotation or a suffix (e.g. `5I32`)", 89});
    }
}
void checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(Comp* c, uint64_t id, uint64_t eKind, uint64_t eBits, long long eSgn) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m617 = e;
    if (_m617.tag == 0) {
        int64_t value = _m617.data.Int.value;
        (void)value;
        uint64_t offset = _m617.data.Int.offset;
        (void)offset;
        long long isBool = _m617.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m617.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m617.data.Int.tyLen;
        (void)tyLen;
    checkLitLeaf_c_Comp_value_I64_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), value, offset, isBool, tyStart, tyLen, eKind, eBits, eSgn);
    }
    else if (_m617.tag == 2) {
        int64_t op = _m617.data.Unary.op;
        (void)op;
        uint64_t operand = _m617.data.Unary.operand;
        (void)operand;
    if (op == 57) {
    Expr oe = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m618 = oe;
    if (_m618.tag == 0) {
        int64_t value = _m618.data.Int.value;
        (void)value;
        uint64_t offset = _m618.data.Int.offset;
        (void)offset;
        long long isBool = _m618.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m618.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m618.data.Int.tyLen;
        (void)tyLen;
    checkLitLeaf_c_Comp_value_I64_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), ({ int64_t __ov; if (__builtin_sub_overflow((0), (value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), offset, isBool, tyStart, tyLen, eKind, eBits, eSgn);
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), operand, eKind, eBits, eSgn);
    }
    }
    }
    else {
    if (op == 79) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), operand, eKind, eBits, eSgn);
    }
    }
    }
    else if (_m617.tag == 3) {
        int64_t op = _m617.data.Binary.op;
        (void)op;
        uint64_t lhs = _m617.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m617.data.Binary.rhs;
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
    ConstInt cf = foldConst_c_Comp_id_U64(&((*c)), id);
    if (cf.isConst) {
    if (litFitsBits_value_I64_bits_U64_sgn_Bool(cf.value, eBits, eSgn)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), id)), (PlewString){"constant expression is out of range for its type", 48});
    }
    }
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), lhs, eKind, eBits, eSgn);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), rhs, eKind, eBits, eSgn);
    }
    else {
    checkArithNoCtx_c_Comp_lhs_U64_rhs_U64(&((*c)), lhs, rhs);
    }
    }
    else {
    checkArithNoCtx_c_Comp_lhs_U64_rhs_U64(&((*c)), lhs, rhs);
    }
    }
    else if (_m617.tag == 4) {
        uint64_t nameStart = _m617.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m617.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m617.data.Call.args;
        (void)args;
    checkCallArgs_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args));
    }
    else if (_m617.tag == 10) {
        uint64_t recv = _m617.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m617.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m617.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m617.data.Method.args;
        (void)args;
    checkMethodArgs_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), recv, nameStart, nameLen, PlewArray_Arg_share(args));
    }
    else if (_m617.tag == 11) {
        uint64_t operand = _m617.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m617.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m617.data.Cast.tyLen;
        (void)tyLen;
    Expr oe = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m619 = oe;
    if (_m619.tag == 0) {
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), operand, 0, 0, 0);
    }
    }
    }
    else if (_m617.tag == 5) {
        uint64_t base = _m617.data.Field.base;
        (void)base;
        uint64_t nameStart = _m617.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m617.data.Field.nameLen;
        (void)nameLen;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), base, 0, 0, 0);
    }
    else if (_m617.tag == 9) {
        uint64_t base = _m617.data.Index.base;
        (void)base;
        uint64_t index = _m617.data.Index.index;
        (void)index;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), base, 0, 0, 0);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), index, 1, 64, 0);
    }
    else if (_m617.tag == 6) {
        uint64_t typeStart = _m617.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m617.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m617.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m617.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m617.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m617.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m617.data.Make.fields;
        (void)fields;
    checkMakeFields_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_ty_U64_fields_AMakeField(&((*c)), typeStart, typeLen, variantStart, variantLen, isEnum, ty, PlewArray_MakeField_share(fields));
    }
    else if (_m617.tag == 8) {
        PlewArray_U64 elems = _m617.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), PlewArray_U64_get(elems, (long long)(i)), eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m617.tag == 12) {
        uint64_t scrut = _m617.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m617.data.MatchExpr.arms;
        (void)arms;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), scrut, 0, 0, 0);
    uint64_t i = 0;
    while (i < (long long)((arms).len)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), PlewArray_MatchArm_get(arms, (long long)(i)).body, eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m617.tag == 14) {
        uint64_t opt = _m617.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m617.data.Coalesce.deflt;
        (void)deflt;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), opt, 0, 0, 0);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), deflt, eKind, eBits, eSgn);
    }
    else if (_m617.tag == 15) {
        uint64_t expr = _m617.data.Try.expr;
        (void)expr;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), expr, 0, 0, 0);
    }
    else {
    }
    }
}
IntTy exprIntTy_c_Comp_id_U64(Comp* c, uint64_t id) {
    TypeInfo ti = exprType_c_Comp_id_U64(&((*c)), id);
    if (tiIsInt_c_Comp_ti_TypeInfo(&((*c)), ti)) {
    { IntTy __ret620 = (IntTy){.known = 1, .bits = intBits_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen), .sgn = intSigned_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen)};
    return __ret620; }
    }
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m621 = e;
    if (_m621.tag == 4) {
        uint64_t nameStart = _m621.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m621.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m621.data.Call.args;
        (void)args;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"argCount", 8})) {
    { IntTy __ret622 = (IntTy){.known = 1, .bits = 64, .sgn = 1};
    return __ret622; }
    }
    }
    else if (_m621.tag == 5) {
        uint64_t base = _m621.data.Field.base;
        (void)base;
        uint64_t nameStart = _m621.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m621.data.Field.nameLen;
        (void)nameLen;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"count", 5})) {
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    { IntTy __ret623 = (IntTy){.known = 1, .bits = 64, .sgn = 0};
    return __ret623; }
    }
    }
    }
    else if (_m621.tag == 9) {
        uint64_t base = _m621.data.Index.base;
        (void)base;
        uint64_t index = _m621.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen)) {
    { IntTy __ret624 = (IntTy){.known = 1, .bits = intBits_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen), .sgn = intSigned_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen)};
    return __ret624; }
    }
    }
    }
    else {
    }
    }
    { IntTy __ret625 = (IntTy){.known = 0, .bits = 0, .sgn = 0};
    return __ret625; }
}
void checkArithNoCtx_c_Comp_lhs_U64_rhs_U64(Comp* c, uint64_t lhs, uint64_t rhs) {
    IntTy lt = exprIntTy_c_Comp_id_U64(&((*c)), lhs);
    if (lt.known) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), lhs, 1, lt.bits, lt.sgn);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), rhs, 1, lt.bits, lt.sgn);
    return;
    }
    IntTy rt = exprIntTy_c_Comp_id_U64(&((*c)), rhs);
    if (rt.known) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), lhs, 1, rt.bits, rt.sgn);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), rhs, 1, rt.bits, rt.sgn);
    return;
    }
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), lhs, 0, 0, 0);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), rhs, 0, 0, 0);
}
void checkLitTi_c_Comp_id_U64_ti_TypeInfo(Comp* c, uint64_t id, TypeInfo ti) {
    if (tiIsInt_c_Comp_ti_TypeInfo(&((*c)), ti)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), id, 1, intBits_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen), intSigned_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen));
    return;
    }
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), id, 0, 0, 0);
}
void checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(Comp* c, uint64_t id, uint64_t tyStart, uint64_t tyLen, long long isArray) {
    if (isArray) {
    checkLitArray_c_Comp_id_U64_elemStart_U64_elemLen_U64(&((*c)), id, tyStart, tyLen);
    return;
    }
    checkLitTi_c_Comp_id_U64_ti_TypeInfo(&((*c)), id, typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), tyStart, tyLen, 0));
}
void checkLitArray_c_Comp_id_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t id, uint64_t elemStart, uint64_t elemLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m626 = e;
    if (_m626.tag == 8) {
        PlewArray_U64 elems = _m626.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), PlewArray_U64_get(elems, (long long)(i)), elemStart, elemLen, 0);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), id, 0, 0, 0);
    }
    }
}
long long typeIsTransitivelyUnique_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { long long __ret627 = 1;
    return __ret627; }
    }
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret628 = 0;
    return __ret628; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    uint64_t i = 0;
    while (i < (long long)((s.fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(s.fields, (long long)(i));
    if (f.tyIsArray) {
    }
    else {
    if (typeIsTransitivelyUnique_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret629 = 1;
    StructDef_release(s);
    return __ret629; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret630 = 0;
    StructDef_release(s);
    return __ret630; }
    StructDef_release(s);
}
void checkFieldContagion_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(i)));
    if (s.isUnique) {
    }
    else {
    uint64_t j = 0;
    while (j < (long long)((s.fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(s.fields, (long long)(j));
    if (f.tyIsArray) {
    }
    else {
    if (typeIsTransitivelyUnique_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), f.nameStart), (PlewString){"a struct with a unique field must be declared `unique`", 54});
    }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
}
void checkParamModes_c_Comp_params_AParam(Comp* c, PlewArray_Param params) {
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    Param p = PlewArray_Param_get(params, (long long)(i));
    if (p.tyIsArray) {
    }
    else {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), p.tyStart, p.tyLen)) {
    long long hasMode = ((p.isMove || p.isBorrow) || p.isInout);
    if (hasMode) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), p.nameStart), (PlewString){"a unique-type parameter requires a mode (`move`, `borrow`, or `inout`)", 70});
    }
    }
    else {
    if (p.isMove) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), p.nameStart), (PlewString){"`move` is not allowed on a copyable type; pass by value or use `inout`", 70});
    }
    if (p.isBorrow) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), p.nameStart), (PlewString){"`borrow` is redundant on a copyable type; pass by value", 55});
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void checkArrayElemsNotUnique_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind ae = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), ae.nameStart, ae.nameLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), ae.nameStart), (PlewString){"a unique type cannot be stored in an Array; wrap it in Ref[T]", 61});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void checkGenericUniqueArgs_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).types).len)) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(i)));
    if ((long long)((t.args).len) == 0) {
    }
    else {
    if (isRefInst_c_Comp_ref_U64(&((*c)), i)) {
    }
    else {
    uint64_t j = 0;
    while (j < (long long)((t.args).len)) {
    TypeInfo ai = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(j)));
    if (ai.kind == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), ai.nameStart, ai.nameLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), ai.nameStart), (PlewString){"a unique type cannot be a generic type argument; wrap it in Ref[T]", 66});
    }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeRef_release(t);
    }
}
void checkAllParamModes_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    checkParamModes_c_Comp_params_AParam(&((*c)), PlewArray_Param_share(PlewArray_Func_get((*c).funcs, (long long)(i)).params));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(Comp* c, uint64_t exprId, long long inoutOk) {
    if (inoutOk) {
    return;
    }
    if (isPlaceExpr_c_Comp_id_U64(&((*c)), exprId)) {
    TypeInfo ti = exprType_c_Comp_id_U64(&((*c)), exprId);
    if (ti.kind == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), exprId)), (PlewString){"a unique value cannot be copied; use `move`, `borrow`, or `inout`", 65});
    }
    }
    }
}
void checkUniqueArgModes_c_Comp_args_AArg(Comp* c, PlewArray_Arg args) {
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, PlewArray_Arg_get(args, (long long)(i)).isInout);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void checkCallArgs_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    checkUniqueArgModes_c_Comp_args_AArg(&((*c)), PlewArray_Arg_share(args));
    uint64_t fi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args));
    if (fi == (long long)(((*c).funcs).len)) {
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 1, 64, 1);
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
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, p.tyStart, p.tyLen, p.tyIsArray);
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 0, 0, 0);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param_release(ps);
    Func_release(f);
}
void checkMethodArgs_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    checkUniqueArgModes_c_Comp_args_AArg(&((*c)), PlewArray_Arg_share(args));
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), recv, 0, 0, 0);
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (rt.kind == 2) {
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen, PlewArray_Arg_share(args));
    if (mi != (long long)(((*c).funcs).len)) {
    Func mf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(mi)));
    PlewArray_Param ps = PlewArray_Param_share(mf.params);
    long long genericRecv = isGenericInst_c_Comp_ref_U64(&((*c)), rt.ref);
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    if (i < (long long)((ps).len)) {
    Param p = PlewArray_Param_get(ps, (long long)(i));
    if (genericRecv) {
    TypeInfo pti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), rt.ref, PlewArray_Bind_share(mf.typeParams), p.ty);
    checkLitTi_c_Comp_id_U64_ti_TypeInfo(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, pti);
    }
    else {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, p.tyStart, p.tyLen, p.tyIsArray);
    }
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 0, 0, 0);
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
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"append", 6})) {
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, rt.nameStart, rt.nameLen, 0);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return;
    }
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr, 1, 64, 1);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
TypeInfo makeFieldType_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen) {
    if (isEnum) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef en = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), en.nameStart, en.nameLen, typeStart, typeLen)) {
    PlewArray_Variant vars = PlewArray_Variant_share(en.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fj = 0;
    while (fj < (long long)((fs).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fs, (long long)(fj));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    { TypeInfo __ret631 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), fd.tyStart, fd.tyLen, fd.tyIsArray);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(en);
    return __ret631; }
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
    { TypeInfo __ret632 = scalarInfo();
    return __ret632; }
    }
    { TypeInfo __ret633 = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, fieldStart, fieldLen);
    return __ret633; }
}
void checkMakeFields_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_ty_U64_fields_AMakeField(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t ty, PlewArray_MakeField fields) {
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(&((*c)), mf.value, 0);
    TypeInfo ft = scalarInfo();
    if (isRefInst_c_Comp_ref_U64(&((*c)), ty)) {
    TypeRef rt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ty)));
    ft = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    TypeRef_release(rt);
    }
    else {
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ty)) {
    ft = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), ty, variantStart, variantLen, mf.nameStart, mf.nameLen);
    }
    else {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ty)) {
    ft = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), ty, mf.nameStart, mf.nameLen);
    }
    else {
    ft = makeFieldType_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, variantStart, variantLen, isEnum, mf.nameStart, mf.nameLen);
    }
    }
    }
    if (ft.kind == 3) {
    checkLitArray_c_Comp_id_U64_elemStart_U64_elemLen_U64(&((*c)), mf.value, ft.nameStart, ft.nameLen);
    }
    else {
    checkLitTi_c_Comp_id_U64_ti_TypeInfo(&((*c)), mf.value, ft);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long paramSelectorEq_c_Comp_a_AParam_b_AParam(Comp* c, PlewArray_Param a, PlewArray_Param b) {
    if ((long long)((a).len) != (long long)((b).len)) {
    { long long __ret634 = 0;
    return __ret634; }
    }
    uint64_t i = 0;
    while (i < (long long)((a).len)) {
    Param pa = PlewArray_Param_get(a, (long long)(i));
    Param pb = PlewArray_Param_get(b, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), pa.nameStart, pa.nameLen, pb.nameStart, pb.nameLen)) {
    }
    else {
    { long long __ret635 = 0;
    return __ret635; }
    }
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), pa.tyStart, pa.tyLen, pb.tyStart, pb.tyLen)) {
    }
    else {
    { long long __ret636 = 0;
    return __ret636; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret637 = 1;
    return __ret637; }
}
long long witnessedHas_c_Comp_witnessed_AFunc_r_Func(Comp* c, PlewArray_Func witnessed, Func r) {
    uint64_t i = 0;
    while (i < (long long)((witnessed).len)) {
    Func w = Func_share(PlewArray_Func_get(witnessed, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), w.nameStart, w.nameLen, r.nameStart, r.nameLen)) {
    if (paramSelectorEq_c_Comp_a_AParam_b_AParam(&((*c)), PlewArray_Param_share(w.params), PlewArray_Param_share(r.params))) {
    { long long __ret638 = 1;
    Func_release(w);
    return __ret638; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(w);
    }
    { long long __ret639 = 0;
    return __ret639; }
}
void checkConformances_c_Comp(Comp* c) {
    uint64_t ci = 0;
    while (ci < (long long)(((*c).conforms).len)) {
    Conform cf = Conform_share(PlewArray_Conform_get((*c).conforms, (long long)(ci)));
    if (cf.derived) {
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    long long found = 0;
    uint64_t ti = 0;
    while (ti < (long long)(((*c).traits).len)) {
    TraitDef t = TraitDef_share(PlewArray_TraitDef_get((*c).traits, (long long)(ti)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, cf.traitStart, cf.traitLen)) {
    found = 1;
    uint64_t ri = 0;
    while (ri < (long long)((t.reqs).len)) {
    Func r = Func_share(PlewArray_Func_get(t.reqs, (long long)(ri)));
    if (witnessedHas_c_Comp_witnessed_AFunc_r_Func(&((*c)), PlewArray_Func_share(cf.witnessed), r)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), cf.typeStart), (PlewString){"incomplete trait conformance: a requirement is not witnessed (define its body or bind it with `via`)", 100});
    }
    ri = ({ uint64_t __ov; if (__builtin_add_overflow((ri), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(r);
    }
    uint64_t sti = 0;
    while (sti < (long long)((t.supertraits).len)) {
    Bind sup = PlewArray_Bind_get(t.supertraits, (long long)(sti));
    if (typeConformsTo_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(&((*c)), cf.typeStart, cf.typeLen, sup.nameStart, sup.nameLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), cf.typeStart), (PlewString){"supertrait not satisfied: this type must also conform to the trait's supertrait", 79});
    }
    sti = ({ uint64_t __ov; if (__builtin_add_overflow((sti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ti = ({ uint64_t __ov; if (__builtin_add_overflow((ti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TraitDef_release(t);
    }
    if (found) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), cf.traitStart), (PlewString){"conformance to an unknown trait (is it declared / imported?)", 60});
    }
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Conform_release(cf);
    }
    checkViaTargets_c_Comp(&((*c)));
}
long long typeHasMember_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, recvStart, recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    { long long __ret640 = 1;
    Func_release(f);
    return __ret640; }
    }
    }
    }
    else {
    if (f.isAssoc) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, recvStart, recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    { long long __ret641 = 1;
    Func_release(f);
    return __ret641; }
    }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { long long __ret642 = 0;
    return __ret642; }
}
void checkViaTargets_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).methodAliases).len)) {
    MethodAlias al = PlewArray_MethodAlias_get((*c).methodAliases, (long long)(i));
    if (typeHasMember_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(&((*c)), al.recvStart, al.recvLen, al.realStart, al.realLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), al.aliasStart), (PlewString){"`via` target is not a member of this type", 41});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long builtinEqOrd_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen) {
    long long isEqOrd = (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), traitStart, traitLen, (PlewString){"Eq", 2}) || rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), traitStart, traitLen, (PlewString){"Ord", 3}));
    if (isEqOrd) {
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen)) {
    { long long __ret643 = 1;
    return __ret643; }
    }
    { long long __ret644 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), typeStart, typeLen, (PlewString){"String", 6});
    return __ret644; }
    }
    { long long __ret645 = 0;
    return __ret645; }
}
long long typeConformsTo_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen) {
    if (builtinEqOrd_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(&((*c)), typeStart, typeLen, traitStart, traitLen)) {
    { long long __ret646 = 1;
    return __ret646; }
    }
    uint64_t i = 0;
    while (i < (long long)(((*c).conforms).len)) {
    Conform cf = Conform_share(PlewArray_Conform_get((*c).conforms, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), cf.typeStart, cf.typeLen, typeStart, typeLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), cf.traitStart, cf.traitLen, traitStart, traitLen)) {
    { long long __ret647 = 1;
    Conform_release(cf);
    return __ret647; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Conform_release(cf);
    }
    { long long __ret648 = 0;
    return __ret648; }
}
long long typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(Comp* c, uint64_t typeStart, uint64_t typeLen, PlewString traitName) {
    uint64_t i = 0;
    while (i < (long long)(((*c).conforms).len)) {
    Conform cf = Conform_share(PlewArray_Conform_get((*c).conforms, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), cf.typeStart, cf.typeLen, typeStart, typeLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), cf.traitStart, cf.traitLen, traitName)) {
    { long long __ret649 = 1;
    Conform_release(cf);
    return __ret649; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Conform_release(cf);
    }
    { long long __ret650 = 0;
    return __ret650; }
}
void checkFnBounds_c_Comp(Comp* c) {
    uint64_t ii = 0;
    while (ii < (long long)(((*c).fnInsts).len)) {
    FnInst fin = FnInst_share(PlewArray_FnInst_get((*c).fnInsts, (long long)(ii)));
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fin.fnIdx)));
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).len)) {
    FuncBound fb = PlewArray_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == fin.fnIdx) {
    uint64_t pi = 0;
    while (pi < (long long)((f.typeParams).len)) {
    Bind tp = PlewArray_Bind_get(f.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), tp.nameStart, tp.nameLen, fb.paramStart, fb.paramLen)) {
    if (pi < (long long)((fin.args).len)) {
    TypeRef at = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(PlewArray_U64_get(fin.args, (long long)(pi)))));
    if (typeConformsTo_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(&((*c)), at.nameStart, at.nameLen, fb.traitStart, fb.traitLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), fb.paramStart), (PlewString){"type argument does not conform to the trait required by `where`", 63});
    }
    TypeRef_release(at);
    }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    ii = ({ uint64_t __ov; if (__builtin_add_overflow((ii), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    FnInst_release(fin);
    }
    checkMethodBounds_c_Comp(&((*c)));
}
void checkMethodBounds_c_Comp(Comp* c) {
    uint64_t gi = 0;
    while (gi < (long long)(((*c).genInsts).len)) {
    uint64_t instRef = PlewArray_U64_get((*c).genInsts, (long long)(gi));
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t mfi = 0;
    while (mfi < (long long)(((*c).funcs).len)) {
    if (methodMatchesInst_c_Comp_f_Func_instRef_U64(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(mfi)), instRef)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(mfi)));
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).len)) {
    FuncBound fb = PlewArray_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == mfi) {
    uint64_t pi = 0;
    while (pi < (long long)((f.typeParams).len)) {
    Bind tp = PlewArray_Bind_get(f.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), tp.nameStart, tp.nameLen, fb.paramStart, fb.paramLen)) {
    if (pi < (long long)((inst.args).len)) {
    TypeRef at = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(PlewArray_U64_get(inst.args, (long long)(pi)))));
    if (typeConformsTo_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(&((*c)), at.nameStart, at.nameLen, fb.traitStart, fb.traitLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), fb.paramStart), (PlewString){"receiver type argument does not conform to the trait required by the method's `where`", 85});
    }
    TypeRef_release(at);
    }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Func_release(f);
    }
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeRef_release(inst);
    }
}
long long isTypeParamOf_c_Comp_fnIdx_U64_start_U64_len_U64(Comp* c, uint64_t fnIdx, uint64_t start, uint64_t len) {
    if (fnIdx >= (long long)(((*c).funcs).len)) {
    { long long __ret651 = 0;
    return __ret651; }
    }
    PlewArray_Bind tps = PlewArray_Bind_share(PlewArray_Func_get((*c).funcs, (long long)(fnIdx)).typeParams);
    uint64_t i = 0;
    while (i < (long long)((tps).len)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), PlewArray_Bind_get(tps, (long long)(i)).nameStart, PlewArray_Bind_get(tps, (long long)(i)).nameLen, start, len)) {
    { long long __ret652 = 1;
    PlewArray_Bind_release(tps);
    return __ret652; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret653 = 0;
    PlewArray_Bind_release(tps);
    return __ret653; }
    PlewArray_Bind_release(tps);
}
long long boundProvidesMethod_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).len)) {
    FuncBound fb = PlewArray_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == fnIdx) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fb.paramStart, fb.paramLen, tpStart, tpLen)) {
    uint64_t ti = 0;
    while (ti < (long long)(((*c).traits).len)) {
    TraitDef t = TraitDef_share(PlewArray_TraitDef_get((*c).traits, (long long)(ti)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, fb.traitStart, fb.traitLen)) {
    uint64_t ri = 0;
    while (ri < (long long)((t.reqs).len)) {
    Func r = Func_share(PlewArray_Func_get(t.reqs, (long long)(ri)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), r.nameStart, r.nameLen, nameStart, nameLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(r.params), PlewArray_Arg_share(args))) {
    { long long __ret654 = 1;
    Func_release(r);
    TraitDef_release(t);
    return __ret654; }
    }
    }
    ri = ({ uint64_t __ov; if (__builtin_add_overflow((ri), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(r);
    }
    }
    ti = ({ uint64_t __ov; if (__builtin_add_overflow((ti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TraitDef_release(t);
    }
    uint64_t gi = 0;
    while (gi < (long long)(((*c).funcs).len)) {
    Func g = Func_share(PlewArray_Func_get((*c).funcs, (long long)(gi)));
    if (g.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), g.recvStart, g.recvLen, fb.traitStart, fb.traitLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), g.nameStart, g.nameLen, nameStart, nameLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(g.params), PlewArray_Arg_share(args))) {
    { long long __ret655 = 1;
    Func_release(g);
    return __ret655; }
    }
    }
    }
    }
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(g);
    }
    }
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret656 = 0;
    return __ret656; }
}
long long boundHasTraitNamed_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_traitName_String(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, PlewString traitName) {
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).len)) {
    FuncBound fb = PlewArray_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == fnIdx) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fb.paramStart, fb.paramLen, tpStart, tpLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), fb.traitStart, fb.traitLen, traitName)) {
    { long long __ret657 = 1;
    return __ret657; }
    }
    }
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret658 = 0;
    return __ret658; }
}
void checkBoundsExpr_c_Comp_exprId_U64(Comp* c, uint64_t exprId) {
    {
    Expr _m659 = PlewArray_Expr_get((*c).exprs, (long long)(exprId));
    if (_m659.tag == 2) {
        int64_t op = _m659.data.Unary.op;
        (void)op;
        uint64_t operand = _m659.data.Unary.operand;
        (void)operand;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m659.tag == 3) {
        int64_t op = _m659.data.Binary.op;
        (void)op;
        uint64_t lhs = _m659.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m659.data.Binary.rhs;
        (void)rhs;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), lhs);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), rhs);
    if (op >= 50) {
    if (op <= 55) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 2) {
    if (isTypeParamOf_c_Comp_fnIdx_U64_start_U64_len_U64(&((*c)), (*c).curCheckFn, lt.nameStart, lt.nameLen)) {
    PlewString need = (PlewString){"Ord", 3};
    if (op == 50) {
    need = (PlewString){"Eq", 2};
    }
    if (op == 51) {
    need = (PlewString){"Eq", 2};
    }
    if (boundHasTraitNamed_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_traitName_String(&((*c)), (*c).curCheckFn, lt.nameStart, lt.nameLen, need)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), lhs)), (PlewString){"comparison on a type parameter needs an Eq/Ord bound (add `where T: Eq` / `: Ord`)", 82});
    }
    }
    }
    }
    }
    }
    else if (_m659.tag == 4) {
        uint64_t nameStart = _m659.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m659.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m659.data.Call.args;
        (void)args;
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m659.tag == 10) {
        uint64_t recv = _m659.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m659.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m659.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m659.data.Method.args;
        (void)args;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), recv);
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (rt.kind == 2) {
    if (isTypeParamOf_c_Comp_fnIdx_U64_start_U64_len_U64(&((*c)), (*c).curCheckFn, rt.nameStart, rt.nameLen)) {
    if (boundProvidesMethod_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), (*c).curCheckFn, rt.nameStart, rt.nameLen, nameStart, nameLen, PlewArray_Arg_share(args))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"method not provided by the bounds of this type parameter (add a `where T: Trait` that declares it)", 98});
    }
    }
    }
    }
    else if (_m659.tag == 5) {
        uint64_t base = _m659.data.Field.base;
        (void)base;
        uint64_t nameStart = _m659.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m659.data.Field.nameLen;
        (void)nameLen;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m659.tag == 9) {
        uint64_t base = _m659.data.Index.base;
        (void)base;
        uint64_t index = _m659.data.Index.index;
        (void)index;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), base);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), index);
    }
    else if (_m659.tag == 6) {
        uint64_t typeStart = _m659.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m659.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m659.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m659.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m659.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m659.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m659.data.Make.fields;
        (void)fields;
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), PlewArray_MakeField_get(fields, (long long)(i)).value);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m659.tag == 8) {
        PlewArray_U64 elems = _m659.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), PlewArray_U64_get(elems, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m659.tag == 11) {
        uint64_t operand = _m659.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m659.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m659.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m659.data.Cast.ty;
        (void)ty;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m659.tag == 14) {
        uint64_t opt = _m659.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m659.data.Coalesce.deflt;
        (void)deflt;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), opt);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), deflt);
    }
    else if (_m659.tag == 15) {
        uint64_t expr = _m659.data.Try.expr;
        (void)expr;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m659.tag == 16) {
        uint64_t base = _m659.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m659.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m659.data.Arrow.nameLen;
        (void)nameLen;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m659.tag == 13) {
        uint64_t cond = _m659.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m659.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m659.data.IfExpr.elseBlk;
        (void)elseBlk;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), cond);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), thenBlk);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    else if (_m659.tag == 12) {
        uint64_t scrut = _m659.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m659.data.MatchExpr.arms;
        (void)arms;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm(&((*c)), a);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m659.tag == 18) {
        uint64_t operand = _m659.data.Move.operand;
        (void)operand;
        long long isBorrow = _m659.data.Move.isBorrow;
        (void)isBorrow;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), operand);
    }
    else {
    }
    }
}
void checkBoundsStmt_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId) {
    {
    Stmt _m660 = PlewArray_Stmt_get((*c).stmts, (long long)(stmtId));
    if (_m660.tag == 0) {
        long long mutable = _m660.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m660.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m660.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m660.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m660.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m660.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m660.data.Let.ty;
        (void)ty;
        uint64_t init = _m660.data.Let.init;
        (void)init;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), init);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), nameStart, nameLen, tyStart, tyLen, tyIsArray, ty, 0, mutable, 1);
    }
    else if (_m660.tag == 1) {
        int64_t op = _m660.data.Assign.op;
        (void)op;
        uint64_t target = _m660.data.Assign.target;
        (void)target;
        uint64_t value = _m660.data.Assign.value;
        (void)value;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), target);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m660.tag == 2) {
        uint64_t expr = _m660.data.Print.expr;
        (void)expr;
        uint64_t offset = _m660.data.Print.offset;
        (void)offset;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m660.tag == 3) {
        uint64_t expr = _m660.data.ExprStmt.expr;
        (void)expr;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m660.tag == 4) {
        uint64_t value = _m660.data.Return.value;
        (void)value;
        long long hasValue = _m660.data.Return.hasValue;
        (void)hasValue;
    if (hasValue) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), value);
    }
    }
    else if (_m660.tag == 5) {
        uint64_t cond = _m660.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m660.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m660.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m660.data.If.hasElse;
        (void)hasElse;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), cond);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), thenBlk);
    if (hasElse) {
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    }
    else if (_m660.tag == 6) {
        uint64_t cond = _m660.data.While.cond;
        (void)cond;
        uint64_t body = _m660.data.While.body;
        (void)body;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), cond);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), body);
    }
    else if (_m660.tag == 7) {
        uint64_t varStart = _m660.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m660.data.For.varLen;
        (void)varLen;
        long long isRange = _m660.data.For.isRange;
        (void)isRange;
        long long inclusive = _m660.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m660.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m660.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m660.data.For.body;
        (void)body;
    uint64_t forMark = scopeMark_c_Comp(&((*c)));
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), iter);
    if (isRange) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), rangeHi);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, 0, 0, 0, 0, 0, 0, 0);
    }
    else {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), iter);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0, 0, 0, 0);
    }
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), body);
    popLocals_c_Comp_mark_U64(&((*c)), forMark);
    }
    else if (_m660.tag == 8) {
        uint64_t scrut = _m660.data.Match.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m660.data.Match.arms;
        (void)arms;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm(&((*c)), a);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m660.tag == 9) {
        uint64_t msg = _m660.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m660.data.Panic.offset;
        (void)offset;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), msg);
    }
    else if (_m660.tag == 10) {
        uint64_t value = _m660.data.Give.value;
        (void)value;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m660.tag == 11) {
    }
    else if (_m660.tag == 12) {
    }
    else { __builtin_unreachable(); }
    }
}
void checkBoundsBlock_c_Comp_blkId_U64(Comp* c, uint64_t blkId) {
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    PlewArray_U64 stmts = PlewArray_U64_share(PlewArray_Block_get((*c).blocks, (long long)(blkId)).stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).len)) {
    checkBoundsStmt_c_Comp_stmtId_U64(&((*c)), PlewArray_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    PlewArray_U64_release(stmts);
}
void checkGenericBodies_c_Comp(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if ((long long)((f.typeParams).len) > 0) {
    PlewArray_Bind noParams = PlewArray_Bind_new();
    PlewArray_U64 noArgs = PlewArray_U64_new();
    (*c).locals = PlewArray_Local_new();
    (*c).curHasRecv = f.hasRecv;
    (*c).curRecvStart = f.recvStart;
    (*c).curRecvLen = f.recvLen;
    (*c).curSelfInout = f.selfInout;
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = PlewArray_Bind_share(noParams);
    (*c).curTypeArgs = PlewArray_U64_share(noArgs);
    (*c).curCheckFn = fi;
    uint64_t pi = 0;
    while (pi < (long long)((f.params).len)) {
    Param p = PlewArray_Param_get(f.params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), f.body);
    PlewArray_U64_release(noArgs);
    PlewArray_Bind_release(noParams);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    (*c).locals = PlewArray_Local_new();
    (*c).curHasRecv = 0;
    (*c).curCheckFn = (long long)(((*c).funcs).len);
}
long long sameLabels_c_Comp_a_AParam_b_AParam(Comp* c, PlewArray_Param a, PlewArray_Param b) {
    if ((long long)((a).len) != (long long)((b).len)) {
    { long long __ret661 = 0;
    return __ret661; }
    }
    uint64_t i = 0;
    while (i < (long long)((a).len)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), PlewArray_Param_get(a, (long long)(i)).nameStart, PlewArray_Param_get(a, (long long)(i)).nameLen, PlewArray_Param_get(b, (long long)(i)).nameStart, PlewArray_Param_get(b, (long long)(i)).nameLen)) {
    }
    else {
    { long long __ret662 = 0;
    return __ret662; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret663 = 1;
    return __ret663; }
}
void checkOverloadCollisions_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func fi = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (fi.hasRecv) {
    }
    else {
    if (fi.isAssoc) {
    }
    else {
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < (long long)(((*c).funcs).len)) {
    Func fj = Func_share(PlewArray_Func_get((*c).funcs, (long long)(j)));
    if (fj.hasRecv) {
    }
    else {
    if (fj.isAssoc) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fi.nameStart, fi.nameLen, fj.nameStart, fj.nameLen)) {
    if (sameLabels_c_Comp_a_AParam_b_AParam(&((*c)), PlewArray_Param_share(fi.params), PlewArray_Param_share(fj.params))) {
    if ((long long)((fi.typeParams).len) > 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), fj.nameStart), (PlewString){"a generic function shares its selector (name + labels) with another overload; spec forbids generic/concrete overload on the same selector", 137});
    }
    else {
    if ((long long)((fj.typeParams).len) > 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), fj.nameStart), (PlewString){"a generic function shares its selector (name + labels) with another overload; spec forbids generic/concrete overload on the same selector", 137});
    }
    }
    }
    }
    }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(fj);
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(fi);
    }
}
void checkImplOnBuiltin_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    long long onBuiltin = 0;
    if (f.hasRecv) {
    onBuiltin = (isPrimType_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen) || rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), f.recvStart, f.recvLen, (PlewString){"String", 6}));
    }
    else {
    if (f.isAssoc) {
    onBuiltin = (isPrimType_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen) || rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), f.recvStart, f.recvLen, (PlewString){"String", 6}));
    }
    }
    if (onBuiltin) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), f.nameStart), (PlewString){"cannot define methods on a built-in type", 40});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
}
void checkMoveFnReceivers_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (f.selfMove) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), f.nameStart), (PlewString){"`move fn` (consuming self) is only allowed on a unique type", 59});
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
}
void emitClosureCall_c_Comp_tyRef_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t tyRef, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(tyRef)));
    plew_write((PlewString){"((", 2});
    if ((long long)((t.args).len) > 0) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    }
    else {
    plew_write((PlewString){"void", 4});
    }
    plew_write((PlewString){" (*)(void*", 10});
    uint64_t pi = 1;
    while (pi < (long long)((t.args).len)) {
    plew_write((PlewString){", ", 2});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(pi)));
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"))(", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){").fn)((", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){").env", 5});
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    plew_write((PlewString){", ", 2});
    Arg ar = PlewArray_Arg_get(args, (long long)(i));
    if (ar.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){")", 1});
    TypeRef_release(t);
}
void emitCaptureInit_c_Comp_e_CaptureEntry(Comp* c, CaptureEntry e) {
    if (e.boxed) {
    plew_write((PlewString){"plew_ref_share(", 15});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){")", 1});
    return;
    }
    if (e.isArray) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){")", 1});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), e.tyStart, e.tyLen, (PlewString){"Ref", 3})) {
    plew_write((PlewString){"plew_ref_share(", 15});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){")", 1});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), e.tyStart, e.tyLen, (PlewString){"String", 6})) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    return;
    }
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    return;
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){")", 1});
    return;
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
}
long long makeProvides_c_Comp_fields_AMakeField_nameStart_U64_nameLen_U64(Comp* c, PlewArray_MakeField fields, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), mf.nameStart, mf.nameLen, nameStart, nameLen)) {
    { long long __ret664 = 1;
    return __ret664; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret665 = 0;
    return __ret665; }
}
void emitStructMatchExpr_c_Comp_scrut_U64_arm_MatchArm(Comp* c, uint64_t scrut, MatchArm arm) {
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo st = exprType_c_Comp_id_U64(&((*c)), scrut);
    long long generic = isGenericInst_c_Comp_ref_U64(&((*c)), st.ref);
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    plew_write((PlewString){"({ ", 3});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), st.ref, st.nameStart, st.nameLen, 0);
    plew_write((PlewString){" _m", 3});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), scrut);
    plew_write((PlewString){"; ", 2});
    PlewArray_Bind binds = PlewArray_Bind_share(arm.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).len)) {
    Bind bd = PlewArray_Bind_get(binds, (long long)(bi));
    TypeInfo ft = scalarInfo();
    if (generic) {
    ft = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), st.ref, bd.fieldStart, bd.fieldLen);
    }
    else {
    ft = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), st.nameStart, st.nameLen, bd.fieldStart, bd.fieldLen);
    }
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), ft.ref, ft.nameStart, ft.nameLen, (ft.kind == 3));
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = _m", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.fieldStart, bd.fieldLen);
    plew_write((PlewString){"; ", 2});
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), bd.nameStart, bd.nameLen, ft.nameStart, ft.nameLen, (ft.kind == 3), ft.ref, 0, 0, 0);
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genExpr_c_Comp_id_U64(&((*c)), arm.body);
    plew_write((PlewString){"; })", 4});
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    PlewArray_Bind_release(binds);
}
void genExpr_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m666 = e;
    if (_m666.tag == 0) {
        int64_t value = _m666.data.Int.value;
        (void)value;
    writeInt_n_I64(value);
    }
    else if (_m666.tag == 1) {
        uint64_t start = _m666.data.Ident.start;
        (void)start;
        uint64_t len = _m666.data.Ident.len;
        (void)len;
    if ((*c).curInClosure) {
    if (isCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(&((*c)), (*c).curClosureId, start, len)) {
    long long boxedCap = isBoxedCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(&((*c)), (*c).curClosureId, start, len);
    if (boxedCap) {
    plew_write((PlewString){"(*((__closure_env", 17});
    }
    else {
    plew_write((PlewString){"((__closure_env", 15});
    }
    writeU64_n_U64((*c).curClosureId);
    plew_write((PlewString){"*)__env)->", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (boxedCap) {
    plew_write((PlewString){")", 1});
    }
    return;
    }
    }
    if (localMoved_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), start), (PlewString){"use of moved value (it was consumed by an earlier `move`)", 57});
    }
    if (isInoutLocal_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    plew_write((PlewString){"(*", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), start, len);
    plew_write((PlewString){")", 1});
    }
    else {
    uint64_t lvi = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (lvi < (long long)(((*c).locals).len)) {
    if (isBoxedLocalAt_c_Comp_nameStart_U64(&((*c)), PlewArray_Local_get((*c).locals, (long long)(lvi)).nameStart)) {
    plew_write((PlewString){"(*", 2});
    writeLocalCName_c_Comp_lo_Local(&((*c)), PlewArray_Local_get((*c).locals, (long long)(lvi)));
    plew_write((PlewString){")", 1});
    }
    else {
    writeLocalCName_c_Comp_lo_Local(&((*c)), PlewArray_Local_get((*c).locals, (long long)(lvi)));
    }
    }
    else {
    uint64_t fvi = firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), start, len);
    if (fvi < (long long)(((*c).funcs).len)) {
    plew_write((PlewString){"(PlewClosure){(void*)&", 22});
    writeFnSelector_c_Comp_f_Func(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(fvi)));
    plew_write((PlewString){"__thunk, 0, 0, 0}", 17});
    }
    else {
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), start, len);
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), start), (PlewString){"unknown identifier", 18});
    }
    }
    }
    }
    }
    else if (_m666.tag == 18) {
        uint64_t operand = _m666.data.Move.operand;
        (void)operand;
        long long isBorrow = _m666.data.Move.isBorrow;
        (void)isBorrow;
    if (isBorrow) {
    genExpr_c_Comp_id_U64(&((*c)), operand);
    }
    else {
    {
    Expr _m667 = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    if (_m667.tag == 1) {
        uint64_t start = _m667.data.Ident.start;
        (void)start;
        uint64_t len = _m667.data.Ident.len;
        (void)len;
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), operand)), (PlewString){"moving `self` is not yet supported", 34});
    }
    if (localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len) < (*c).curBranchBase) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), operand)), (PlewString){"cannot `move` a variable declared outside the enclosing conditional/loop (the move would be conditional); move it unconditionally", 129});
    }
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), operand)), (PlewString){"`move` is only supported from a local variable (field/element moves are not yet supported)", 90});
    }
    }
    genExpr_c_Comp_id_U64(&((*c)), operand);
    markMovedExpr_c_Comp_exprId_U64(&((*c)), operand);
    }
    }
    else if (_m666.tag == 2) {
        int64_t op = _m666.data.Unary.op;
        (void)op;
        uint64_t operand = _m666.data.Unary.operand;
        (void)operand;
    long long negChecked = 0;
    if (op == 57) {
    TypeInfo ot = exprType_c_Comp_id_U64(&((*c)), operand);
    if (ot.kind == 0) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), ot.nameStart, ot.nameLen)) {
    if (intSigned_c_Comp_start_U64_len_U64(&((*c)), ot.nameStart, ot.nameLen)) {
    genCheckedNeg_c_Comp_operand_U64_tyStart_U64_tyLen_U64(&((*c)), operand, ot.nameStart, ot.nameLen);
    negChecked = 1;
    }
    }
    }
    }
    if (negChecked) {
    }
    else {
    plew_write(unaryOpStr_op_I64(op));
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), operand);
    plew_write((PlewString){")", 1});
    }
    }
    else if (_m666.tag == 3) {
        int64_t op = _m666.data.Binary.op;
        (void)op;
        uint64_t lhs = _m666.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m666.data.Binary.rhs;
        (void)rhs;
    if (isStringEq_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    if (op == 51) {
    plew_write((PlewString){"(!PlewString_eq(", 16});
    }
    else {
    plew_write((PlewString){"PlewString_eq(", 14});
    }
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    if (op == 51) {
    plew_write((PlewString){"))", 2});
    }
    else {
    plew_write((PlewString){")", 1});
    }
    }
    else {
    if (hasCompareWitness_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    emitTraitCompare_c_Comp_op_I64_lhs_U64_rhs_U64(&((*c)), op, lhs, rhs);
    }
    else {
    if (isEnumEq_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    emitEnumTagCmp_c_Comp_lhs_U64_rhs_U64_op_I64_outer_Bool(&((*c)), lhs, rhs, op, 1);
    }
    else {
    if (compareNeedsTrait_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), lhs)), (PlewString){"comparison needs Eq/Ord; not available for a struct or array", 60});
    }
    else {
    if (op == 59) {
    TypeInfo dt = arithIntType_c_Comp_lhs_U64_rhs_U64(&((*c)), lhs, rhs);
    if (dt.nameLen > 0) {
    genCheckedDiv_c_Comp_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64_isMod_Bool(&((*c)), lhs, rhs, dt.nameStart, dt.nameLen, 0);
    }
    else {
    plew_write((PlewString){"plew_div(", 9});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    if (op == 60) {
    TypeInfo mt = arithIntType_c_Comp_lhs_U64_rhs_U64(&((*c)), lhs, rhs);
    if (mt.nameLen > 0) {
    genCheckedDiv_c_Comp_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64_isMod_Bool(&((*c)), lhs, rhs, mt.nameStart, mt.nameLen, 1);
    }
    else {
    plew_write((PlewString){"plew_mod(", 9});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    TypeInfo at = arithIntType_c_Comp_lhs_U64_rhs_U64(&((*c)), lhs, rhs);
    if (isCheckedArith_op_I64(op)) {
    if (at.nameLen > 0) {
    genCheckedArith_c_Comp_op_I64_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64(&((*c)), op, lhs, rhs, at.nameStart, at.nameLen);
    }
    else {
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write(binOpStr_op_I64(op));
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write(binOpStr_op_I64(op));
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){")", 1});
    }
    }
    }
    }
    }
    }
    }
    }
    else if (_m666.tag == 4) {
        uint64_t nameStart = _m666.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m666.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m666.data.Call.args;
        (void)args;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"write", 5})) {
    if ((*c).impWrite) {
    plew_write((PlewString){"plew_write(", 11});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"write is not ambient; import it from @Std/Io", 44});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"writeByte", 9})) {
    if ((*c).impWriteByte) {
    plew_write((PlewString){"putchar((int)(", 14});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"writeByte is not ambient; import it from @Std/Io", 48});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"eprint", 6})) {
    if ((*c).impEprint) {
    plew_write((PlewString){"plew_eprint(", 12});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"eprint is not ambient; import it from @Std/Io", 45});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"exit", 4})) {
    if ((*c).impExit) {
    plew_write((PlewString){"exit((int)(", 11});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"exit is not ambient; import it from @Std/Process", 48});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readStdin", 9})) {
    if ((*c).impReadStdin) {
    plew_write((PlewString){"plew_read_stdin()", 17});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"readStdin is not ambient; import it from @Std/Io", 48});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readFile", 8})) {
    if ((*c).impReadFile) {
    plew_write((PlewString){"plew_read_file(", 15});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"readFile is not ambient; import it from @Std/Io", 47});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"readFileBytes", 13})) {
    if ((*c).impReadFile) {
    plew_write((PlewString){"plew_read_file_bytes(", 21});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"readFile is not ambient; import it from @Std/Io", 47});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"fileExists", 10})) {
    if ((*c).impFileExists) {
    plew_write((PlewString){"plew_file_exists(", 17});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"fileExists is not ambient; import it from @Std/Io", 49});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"argCount", 8})) {
    if ((*c).impArgCount) {
    plew_write((PlewString){"plew_arg_count()", 16});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"argCount is not ambient; import it from @Std/Process", 52});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"argAt", 5})) {
    if ((*c).impArgAt) {
    plew_write((PlewString){"plew_arg_at((long long)(", 24});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"argAt is not ambient; import it from @Std/Process", 49});
    }
    return;
    }
    if (callLabelsOk_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"argument labels do not match the function parameters", 52});
    return;
    }
    uint64_t lvi = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    if (lvi < (long long)(((*c).locals).len)) {
    if (isFnType_c_Comp_ref_U64(&((*c)), PlewArray_Local_get((*c).locals, (long long)(lvi)).ty)) {
    emitClosureCall_c_Comp_tyRef_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), PlewArray_Local_get((*c).locals, (long long)(lvi)).ty, nameStart, nameLen, PlewArray_Arg_share(args));
    return;
    }
    }
    uint64_t cfi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args));
    if (cfi == (long long)(((*c).funcs).len)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    }
    else {
    if (isGenericFreeFn_c_Comp_fi_U64(&((*c)), cfi)) {
    PlewArray_U64 inferred = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(cfi)), PlewArray_Arg_share(args));
    if (fnInstExists_c_Comp_fnIdx_U64_args_AU64(&((*c)), cfi, PlewArray_U64_share(inferred))) {
    PlewArray_Bind savedP = PlewArray_Bind_share((*c).curTypeParams);
    PlewArray_U64 savedA = PlewArray_U64_share((*c).curTypeArgs);
    (*c).curTypeParams = PlewArray_Bind_share(PlewArray_Func_get((*c).funcs, (long long)(cfi)).typeParams);
    (*c).curTypeArgs = PlewArray_U64_share(inferred);
    writeFnSelector_c_Comp_f_Func(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(cfi)));
    (*c).curTypeParams = PlewArray_Bind_share(savedP);
    (*c).curTypeArgs = PlewArray_U64_share(savedA);
    PlewArray_U64_release(savedA);
    PlewArray_Bind_release(savedP);
    }
    else {
    writeFnSelector_c_Comp_f_Func(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(cfi)));
    }
    PlewArray_U64_release(inferred);
    }
    else {
    writeFnSelector_c_Comp_f_Func(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(cfi)));
    }
    }
    plew_write((PlewString){"(", 1});
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    Arg ar = PlewArray_Arg_get(args, (long long)(i));
    if (ar.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    long long argIsArr = 0;
    if (cfi < (long long)(((*c).funcs).len)) {
    Func cf0 = Func_share(PlewArray_Func_get((*c).funcs, (long long)(cfi)));
    if (i < (long long)((cf0.params).len)) {
    if (PlewArray_Param_get(cf0.params, (long long)(i)).tyIsArray) {
    argIsArr = 1;
    }
    }
    Func_release(cf0);
    }
    if (argIsArr) {
    Func cf1 = Func_share(PlewArray_Func_get((*c).funcs, (long long)(cfi)));
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), ar.expr, PlewArray_Param_get(cf1.params, (long long)(i)).tyStart, PlewArray_Param_get(cf1.params, (long long)(i)).tyLen);
    Func_release(cf1);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
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
    if (PlewArray_Param_get(cps, (long long)(di)).tyIsArray) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), PlewArray_Param_get(cps, (long long)(di)).defaultExpr, PlewArray_Param_get(cps, (long long)(di)).tyStart, PlewArray_Param_get(cps, (long long)(di)).tyLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Param_get(cps, (long long)(di)).defaultExpr);
    }
    di = ({ uint64_t __ov; if (__builtin_add_overflow((di), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param_release(cps);
    Func_release(cf);
    }
    plew_write((PlewString){")", 1});
    }
    else if (_m666.tag == 5) {
        uint64_t base = _m666.data.Field.base;
        (void)base;
        uint64_t nameStart = _m666.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m666.data.Field.nameLen;
        (void)nameLen;
    {
    Expr _m668 = PlewArray_Expr_get((*c).exprs, (long long)(base));
    if (_m668.tag == 1) {
        uint64_t bs = _m668.data.Ident.start;
        (void)bs;
        uint64_t bl = _m668.data.Ident.len;
        (void)bl;
    if (localIndexByName_c_Comp_start_U64_len_U64(&((*c)), bs, bl) < (long long)(((*c).locals).len)) {
    }
    else {
    if (isEnumName_c_Comp_start_U64_len_U64(&((*c)), bs, bl)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), bs), (PlewString){"an enum variant is not a value; construct it with JSX, e.g. `<Color.Green />`", 77});
    }
    }
    }
    else {
    }
    }
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 1) {
    plew_write((PlewString){"({ PlewString __s = ", 20});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){"; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; })", 67});
    return;
    }
    if (bt.kind == 3) {
    plew_write((PlewString){"(long long)((", 13});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){").len)", 6});
    return;
    }
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    }
    else if (_m666.tag == 7) {
        uint64_t start = _m666.data.Str.start;
        (void)start;
        uint64_t len = _m666.data.Str.len;
        (void)len;
    plew_write((PlewString){"(PlewString){\"", 14});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), ({ uint64_t __ov; if (__builtin_add_overflow((start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), ({ uint64_t __ov; if (__builtin_sub_overflow((len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    plew_write((PlewString){"\", ", 3});
    writeInt_n_I64(strDecodedLen_c_Comp_start_U64_len_U64(&((*c)), start, len));
    plew_write((PlewString){"}", 1});
    }
    else if (_m666.tag == 9) {
        uint64_t base = _m666.data.Index.base;
        (void)base;
        uint64_t index = _m666.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_get(", 5});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){", (long long)(", 14});
    genExpr_c_Comp_id_U64(&((*c)), index);
    plew_write((PlewString){"))", 2});
    }
    else if (_m666.tag == 16) {
        uint64_t base = _m666.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m666.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m666.data.Arrow.nameLen;
        (void)nameLen;
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){")->", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    }
    else if (_m666.tag == 17) {
        PlewArray_Param params = _m666.data.Closure.params;
        (void)params;
        long long hasRet = _m666.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m666.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m666.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m666.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m666.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m666.data.Closure.body;
        (void)body;
    if (closureHasCaptures_c_Comp_id_U64(&((*c)), id)) {
    plew_write((PlewString){"({ __closure_env", 16});
    writeU64_n_U64(id);
    plew_write((PlewString){"* __e = (__closure_env", 22});
    writeU64_n_U64(id);
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(__closure_env", 37});
    writeU64_n_U64(id);
    plew_write((PlewString){")); ", 4});
    uint64_t ci = 0;
    while (ci < (long long)(((*c).captures).len)) {
    CaptureEntry e_s1 = PlewArray_CaptureEntry_get((*c).captures, (long long)(ci));
    if (e_s1.closureId == id) {
    plew_write((PlewString){"__e->", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e_s1.nameStart, e_s1.nameLen);
    plew_write((PlewString){" = ", 3});
    emitCaptureInit_c_Comp_e_CaptureEntry(&((*c)), e_s1);
    plew_write((PlewString){"; ", 2});
    }
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"(PlewClosure){(void*)&__closure", 31});
    writeU64_n_U64(id);
    plew_write((PlewString){", (void*)__e, ((long long*)__e) - 1, &__closure_env", 51});
    writeU64_n_U64(id);
    plew_write((PlewString){"_release}; })", 13});
    }
    else {
    plew_write((PlewString){"(PlewClosure){(void*)&__closure", 31});
    writeU64_n_U64(id);
    plew_write((PlewString){", 0, 0, 0}", 10});
    }
    }
    else if (_m666.tag == 10) {
        uint64_t recv = _m666.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m666.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m666.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m666.data.Method.args;
        (void)args;
    Bind arn = assocRecvName_c_Comp_recv_U64(&((*c)), recv);
    if (arn.nameLen != 0) {
    uint64_t afi = findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), arn.nameStart, arn.nameLen, nameStart, nameLen, PlewArray_Arg_share(args));
    if (afi == (long long)(((*c).funcs).len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"no such associated function on this type", 40});
    return;
    }
    Func af = Func_share(PlewArray_Func_get((*c).funcs, (long long)(afi)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), arn.nameStart, arn.nameLen);
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), af);
    plew_write((PlewString){"(", 1});
    uint64_t ai = 0;
    while (ai < (long long)((args).len)) {
    if (ai > 0) {
    plew_write((PlewString){", ", 2});
    }
    Arg aa = PlewArray_Arg_get(args, (long long)(ai));
    if (aa.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr_c_Comp_id_U64(&((*c)), aa.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), aa.expr);
    }
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t adi = (long long)((args).len);
    while (adi < (long long)((af.params).len)) {
    if (adi > 0) {
    plew_write((PlewString){", ", 2});
    }
    if (PlewArray_Param_get(af.params, (long long)(adi)).tyIsArray) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), PlewArray_Param_get(af.params, (long long)(adi)).defaultExpr, PlewArray_Param_get(af.params, (long long)(adi)).tyStart, PlewArray_Param_get(af.params, (long long)(adi)).tyLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Param_get(af.params, (long long)(adi)).defaultExpr);
    }
    adi = ({ uint64_t __ov; if (__builtin_add_overflow((adi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){")", 1});
    Func_release(af);
    return;
    Func_release(af);
    }
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (bt.kind == 3) {
    if (placeIsMutable_c_Comp_id_U64(&((*c)), recv)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot mutate an immutable binding; declare it with `mut val`", 61});
    return;
    }
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_push(&(", 8});
    genExpr_c_Comp_id_U64(&((*c)), recv);
    plew_write((PlewString){"), ", 3});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")", 1});
    }
    else {
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen, PlewArray_Arg_share(args));
    if (mi == (long long)(((*c).funcs).len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"no such method on this type", 27});
    return;
    }
    Func mf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(mi)));
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), PlewArray_Param_share(mf.params), PlewArray_Arg_share(args))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"argument labels do not match the method parameters", 50});
    Func_release(mf);
    return;
    }
    if (mf.selfInout) {
    if (placeIsMutable_c_Comp_id_U64(&((*c)), recv)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call an `inout fn` method on an immutable binding; declare it with `mut val`", 83});
    Func_release(mf);
    return;
    }
    {
    Expr _m669 = PlewArray_Expr_get((*c).exprs, (long long)(recv));
    if (_m669.tag == 9) {
        uint64_t abase = _m669.data.Index.base;
        (void)abase;
        uint64_t aidx = _m669.data.Index.index;
        (void)aidx;
    if (exprType_c_Comp_id_U64(&((*c)), abase).kind == 3) {
    plew_write((PlewString){"({ ", 3});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){" __ge = ", 8});
    genArrayGet_c_Comp_base_U64_index_U64_elemStart_U64_elemLen_U64(&((*c)), abase, aidx, bt.nameStart, bt.nameLen);
    plew_write((PlewString){"; ", 2});
    if (mf.hasRet) {
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), mf.retTy, mf.retStart, mf.retLen, mf.retIsArray);
    plew_write((PlewString){" __mr = ", 8});
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    emitMangle_c_Comp_ref_U64(&((*c)), bt.ref);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    }
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), mf);
    plew_write((PlewString){"(&__ge", 6});
    uint64_t gi = 0;
    while (gi < (long long)((args).len)) {
    plew_write((PlewString){", ", 2});
    Arg ga = PlewArray_Arg_get(args, (long long)(gi));
    if (ga.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr_c_Comp_id_U64(&((*c)), ga.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), ga.expr);
    }
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"); PlewArray_", 13});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_set(&(", 7});
    genExpr_c_Comp_id_U64(&((*c)), abase);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr_c_Comp_id_U64(&((*c)), aidx);
    plew_write((PlewString){"), __ge); ", 10});
    if (mf.hasRet) {
    plew_write((PlewString){"__mr; ", 6});
    }
    plew_write((PlewString){"})", 2});
    Func_release(mf);
    return;
    }
    }
    else {
    }
    }
    }
    if (mf.selfMove) {
    {
    Expr _m670 = PlewArray_Expr_get((*c).exprs, (long long)(recv));
    if (_m670.tag == 1) {
        uint64_t start = _m670.data.Ident.start;
        (void)start;
        uint64_t len = _m670.data.Ident.len;
        (void)len;
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"calling a `move fn` on `self` is not yet supported", 50});
    }
    uint64_t li = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (li < (long long)(((*c).locals).len)) {
    if (PlewArray_Local_get((*c).locals, (long long)(li)).owned) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call a `move fn` on a borrowed value (it consumes the receiver)", 70});
    }
    }
    if (li < (*c).curBranchBase) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call a `move fn` on a variable declared outside the enclosing conditional/loop (the consume would be conditional)", 120});
    }
    }
    else if (_m670.tag == 5) {
        uint64_t base = _m670.data.Field.base;
        (void)base;
        uint64_t nameStart = _m670.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m670.data.Field.nameLen;
        (void)nameLen;
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call a `move fn` on a field (partial move, not yet supported)", 68});
    }
    else if (_m670.tag == 9) {
        uint64_t base = _m670.data.Index.base;
        (void)base;
        uint64_t index = _m670.data.Index.index;
        (void)index;
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call a `move fn` on an element (partial move, not yet supported)", 71});
    }
    else {
    }
    }
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    emitMangle_c_Comp_ref_U64(&((*c)), bt.ref);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    }
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), mf);
    plew_write((PlewString){"(", 1});
    if (mf.selfInout) {
    plew_write((PlewString){"&(", 2});
    genExpr_c_Comp_id_U64(&((*c)), recv);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), recv);
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    plew_write((PlewString){", ", 2});
    Arg ar = PlewArray_Arg_get(args, (long long)(i));
    if (ar.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){")", 1});
    if (mf.selfMove) {
    markMovedExpr_c_Comp_exprId_U64(&((*c)), recv);
    }
    Func_release(mf);
    }
    }
    else if (_m666.tag == 8) {
        PlewArray_U64 elems = _m666.data.Array.elems;
        (void)elems;
    plew_write((PlewString){"0", 1});
    }
    else if (_m666.tag == 11) {
        uint64_t operand = _m666.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m666.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m666.data.Cast.tyLen;
        (void)tyLen;
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen)) {
    Expr opE = PlewArray_Expr_get((*c).exprs, (long long)(operand));
    {
    Expr _m671 = opE;
    if (_m671.tag == 0) {
        int64_t value = _m671.data.Int.value;
        (void)value;
        uint64_t offset = _m671.data.Int.offset;
        (void)offset;
    if (litFitsType_c_Comp_value_I64_dstStart_U64_dstLen_U64(&((*c)), value, tyStart, tyLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"integer literal is out of range for the target type of `as`", 59});
    return;
    }
    }
    else {
    TypeInfo st = exprType_c_Comp_id_U64(&((*c)), operand);
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), st.nameStart, st.nameLen)) {
    if (losslessInt_c_Comp_srcStart_U64_srcLen_U64_dstStart_U64_dstLen_U64(&((*c)), st.nameStart, st.nameLen, tyStart, tyLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), operand)), (PlewString){"`as` would lose information (narrowing or signedness change); use a fallible TryFrom conversion", 95});
    return;
    }
    }
    }
    }
    }
    plew_write((PlewString){"((", 2});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){")(", 2});
    genExpr_c_Comp_id_U64(&((*c)), operand);
    plew_write((PlewString){"))", 2});
    }
    else if (_m666.tag == 6) {
        uint64_t typeStart = _m666.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m666.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m666.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m666.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m666.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m666.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m666.data.Make.fields;
        (void)fields;
    if (isRefInst_c_Comp_ref_U64(&((*c)), ty)) {
    TypeRef rt = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ty)));
    uint64_t t2 = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    plew_write((PlewString){"({ ", 3});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){"* __ref", 7});
    writeU64_n_U64(t2);
    plew_write((PlewString){" = (", 4});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){")); *__ref", 10});
    writeU64_n_U64(t2);
    plew_write((PlewString){" = (", 4});
    if ((long long)((fields).len) > 0) {
    TypeInfo bti = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(rt.args, (long long)(0)));
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), PlewArray_MakeField_get(fields, (long long)(0)).value, PlewArray_U64_get(rt.args, (long long)(0)), bti.nameStart, bti.nameLen, (bti.kind == 3));
    }
    else {
    plew_write((PlewString){"0", 1});
    }
    plew_write((PlewString){"); __ref", 8});
    writeU64_n_U64(t2);
    plew_write((PlewString){"; })", 4});
    TypeRef_release(rt);
    return;
    TypeRef_release(rt);
    }
    if (isEnum) {
    plew_write((PlewString){"(", 1});
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ty)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), ty);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen);
    }
    plew_write((PlewString){"){.tag = ", 9});
    writeU64_n_U64(variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(&((*c)), typeStart, typeLen, variantStart, variantLen));
    if ((long long)((fields).len) > 0) {
    plew_write((PlewString){", .data.", 8});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), variantStart, variantLen);
    plew_write((PlewString){" = {", 4});
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), mf.nameStart, mf.nameLen);
    plew_write((PlewString){" = ", 3});
    TypeInfo eft = scalarInfo();
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ty)) {
    eft = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), ty, variantStart, variantLen, mf.nameStart, mf.nameLen);
    }
    else {
    eft = makeFieldType_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, variantStart, variantLen, 1, mf.nameStart, mf.nameLen);
    }
    if (eft.kind == 3) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), mf.value, eft.nameStart, eft.nameLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), mf.value);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"}", 1});
    }
    plew_write((PlewString){"}", 1});
    }
    else {
    long long generic = isGenericInst_c_Comp_ref_U64(&((*c)), ty);
    plew_write((PlewString){"(", 1});
    if (generic) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), ty);
    }
    else {
    genCType_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen);
    }
    plew_write((PlewString){"){", 2});
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = PlewArray_MakeField_get(fields, (long long)(i));
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), mf.nameStart, mf.nameLen);
    plew_write((PlewString){" = ", 3});
    TypeInfo ft = scalarInfo();
    if (generic) {
    ft = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), ty, mf.nameStart, mf.nameLen);
    }
    else {
    ft = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, mf.nameStart, mf.nameLen);
    }
    if (ft.kind == 3) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), mf.value, ft.nameStart, ft.nameLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), mf.value);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t dEmitted = (long long)((fields).len);
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    StructDef sd = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), sd.nameStart, sd.nameLen, typeStart, typeLen)) {
    PlewArray_FieldDef flds = PlewArray_FieldDef_share(sd.fields);
    uint64_t fi = 0;
    while (fi < (long long)((flds).len)) {
    FieldDef fd = PlewArray_FieldDef_get(flds, (long long)(fi));
    if (fd.hasDefault) {
    if (makeProvides_c_Comp_fields_AMakeField_nameStart_U64_nameLen_U64(&((*c)), PlewArray_MakeField_share(fields), fd.nameStart, fd.nameLen)) {
    }
    else {
    if (dEmitted > 0) {
    plew_write((PlewString){", ", 2});
    }
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), fd.nameStart, fd.nameLen);
    plew_write((PlewString){" = ", 3});
    if (fd.tyIsArray) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), fd.defaultVal, fd.tyStart, fd.tyLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), fd.defaultVal);
    }
    dEmitted = ({ uint64_t __ov; if (__builtin_add_overflow((dEmitted), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(flds);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(sd);
    }
    plew_write((PlewString){"}", 1});
    }
    }
    else if (_m666.tag == 12) {
        uint64_t scrut = _m666.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m666.data.MatchExpr.arms;
        (void)arms;
    if ((long long)((arms).len) > 0) {
    if (PlewArray_MatchArm_get(arms, (long long)(0)).isStruct) {
    emitStructMatchExpr_c_Comp_scrut_U64_arm_MatchArm(&((*c)), scrut, PlewArray_MatchArm_get(arms, (long long)(0)));
    return;
    }
    }
    if (matchExhaustive_c_Comp_arms_AMatchArm(&((*c)), PlewArray_MatchArm_share(arms))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), scrut)), (PlewString){"match must be exhaustive: cover all variants or add a wildcard", 62});
    return;
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), PlewArray_MatchArm_get(arms, (long long)(0)).body);
    uint64_t scrutRef = exprType_c_Comp_id_U64(&((*c)), scrut).ref;
    long long genericMatch = isGenericEnumInst_c_Comp_ref_U64(&((*c)), scrutRef);
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
    genTypeInfoCType_c_Comp_ti_TypeInfo(&((*c)), rt);
    plew_write((PlewString){" __mr", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){"; ", 2});
    if (genericMatch) {
    emitMangle_c_Comp_ref_U64(&((*c)), scrutRef);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), enumStart, enumLen);
    }
    plew_write((PlewString){" __ms", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), scrut);
    plew_write((PlewString){"; ", 2});
    uint64_t i = 0;
    long long firstCond = 1;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    plew_write((PlewString){"else { __mr", 11});
    writeU64_n_U64(t);
    plew_write((PlewString){" = (", 4});
    genExpr_c_Comp_id_U64(&((*c)), a.body);
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
    writeU64_n_U64(t);
    plew_write((PlewString){".tag == ", 8});
    writeU64_n_U64(variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen));
    plew_write((PlewString){") { ", 4});
    PlewArray_Bind binds = PlewArray_Bind_share(a.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).len)) {
    Bind bd = PlewArray_Bind_get(binds, (long long)(bi));
    if (genericMatch) {
    genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    else {
    genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = __ms", 7});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), a.variantStart, a.variantLen);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.fieldStart, bd.fieldLen);
    plew_write((PlewString){"; (void)", 8});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){"; ", 2});
    if (genericMatch) {
    TypeInfo bti = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0, 0);
    }
    else {
    addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"__mr", 4});
    writeU64_n_U64(t);
    plew_write((PlewString){" = (", 4});
    genExpr_c_Comp_id_U64(&((*c)), a.body);
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
    writeU64_n_U64(t);
    plew_write((PlewString){"; })", 4});
    }
    else if (_m666.tag == 13) {
        uint64_t cond = _m666.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m666.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m666.data.IfExpr.elseBlk;
        (void)elseBlk;
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t g = blockGiveExpr_c_Comp_blkId_U64(&((*c)), thenBlk);
    TypeInfo rt = scalarInfo();
    if (g < (long long)(((*c).exprs).len)) {
    rt = exprType_c_Comp_id_U64(&((*c)), g);
    }
    plew_write((PlewString){"({ ", 3});
    genTypeInfoCType_c_Comp_ti_TypeInfo(&((*c)), rt);
    plew_write((PlewString){" __r", 4});
    writeU64_n_U64(t);
    plew_write((PlewString){"; if (", 6});
    genCond_c_Comp_id_U64(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    uint64_t save = (*c).curGiveTmp;
    (*c).curGiveTmp = ({ uint64_t __ov; if (__builtin_add_overflow((t), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    genBlock_c_Comp_id_U64(&((*c)), thenBlk);
    plew_write((PlewString){"    } else {\n", 13});
    genBlock_c_Comp_id_U64(&((*c)), elseBlk);
    (*c).curGiveTmp = save;
    plew_write((PlewString){"    } __r", 9});
    writeU64_n_U64(t);
    plew_write((PlewString){"; })", 4});
    }
    else if (_m666.tag == 14) {
        uint64_t opt = _m666.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m666.data.Coalesce.deflt;
        (void)deflt;
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo ot = exprType_c_Comp_id_U64(&((*c)), opt);
    plew_write((PlewString){"({ ", 3});
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ot.ref)) {
    emitMangle_c_Comp_ref_U64(&((*c)), ot.ref);
    }
    else {
    genTypeInfoCType_c_Comp_ti_TypeInfo(&((*c)), ot);
    }
    plew_write((PlewString){" __c", 4});
    writeU64_n_U64(t);
    plew_write((PlewString){" = (", 4});
    genExpr_c_Comp_id_U64(&((*c)), opt);
    plew_write((PlewString){"); __c", 6});
    writeU64_n_U64(t);
    plew_write((PlewString){".tag == 0 ? __c", 15});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.Some.v : (", 16});
    genExpr_c_Comp_id_U64(&((*c)), deflt);
    plew_write((PlewString){"); })", 5});
    }
    else if (_m666.tag == 15) {
        uint64_t expr = _m666.data.Try.expr;
        (void)expr;
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), expr);
    plew_write((PlewString){"({ ", 3});
    if (isGenericInst_c_Comp_ref_U64(&((*c)), et.ref)) {
    emitMangle_c_Comp_ref_U64(&((*c)), et.ref);
    }
    else {
    genTypeInfoCType_c_Comp_ti_TypeInfo(&((*c)), et);
    }
    plew_write((PlewString){" __t", 4});
    writeU64_n_U64(t);
    plew_write((PlewString){" = (", 4});
    genExpr_c_Comp_id_U64(&((*c)), expr);
    plew_write((PlewString){"); if (__t", 10});
    writeU64_n_U64(t);
    plew_write((PlewString){".tag == 1) { return (", 21});
    emitMangle_c_Comp_ref_U64(&((*c)), (*c).curRetTy);
    plew_write((PlewString){"){.tag = 1, .data.Err.error = __t", 33});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.Err.error}; } __t", 23});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.Ok.value; })", 18});
    }
    else { __builtin_unreachable(); }
    }
}
long long isPlaceExpr_c_Comp_id_U64(Comp* c, uint64_t id) {
    {
    Expr _m672 = PlewArray_Expr_get((*c).exprs, (long long)(id));
    if (_m672.tag == 1) {
        uint64_t start = _m672.data.Ident.start;
        (void)start;
        uint64_t len = _m672.data.Ident.len;
        (void)len;
    { long long __ret673 = 1;
    return __ret673; }
    }
    else if (_m672.tag == 5) {
        uint64_t base = _m672.data.Field.base;
        (void)base;
        uint64_t nameStart = _m672.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m672.data.Field.nameLen;
        (void)nameLen;
    { long long __ret674 = 1;
    return __ret674; }
    }
    else if (_m672.tag == 9) {
        uint64_t base = _m672.data.Index.base;
        (void)base;
        uint64_t index = _m672.data.Index.index;
        (void)index;
    { long long __ret675 = 1;
    return __ret675; }
    }
    else {
    { long long __ret676 = 0;
    return __ret676; }
    }
    }
}
void genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen) {
    if (isPlaceExpr_c_Comp_id_U64(&((*c)), exprId)) {
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_share(", 7});
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    genArrayLiteral_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), exprId, elemStart, elemLen);
}
void genArrayLiteral_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t exprId, uint64_t elemStart, uint64_t elemLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(exprId));
    {
    Expr _m677 = e;
    if (_m677.tag == 8) {
        PlewArray_U64 elems = _m677.data.Array.elems;
        (void)elems;
    if ((long long)((elems).len) == 0) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new()", 6});
    }
    else {
    plew_write((PlewString){"({ PlewArray_", 13});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" __a = PlewArray_", 17});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new(); ", 8});
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(&__a, ", 12});
    genExpr_c_Comp_id_U64(&((*c)), PlewArray_U64_get(elems, (long long)(i)));
    plew_write((PlewString){"); ", 3});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"__a; })", 7});
    }
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    }
    }
}
long long isStringEq_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    if (op == 50) {
    }
    else {
    if (op == 51) {
    }
    else {
    { long long __ret678 = 0;
    return __ret678; }
    }
    }
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    { long long __ret679 = (lt.kind == 1);
    return __ret679; }
}
long long isEnumName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    { long long __ret680 = 1;
    EnumDef_release(e);
    return __ret680; }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret681 = 0;
    return __ret681; }
}
long long isAllNullary_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if ((long long)((v.fields).len) > 0) {
    { long long __ret682 = 0;
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret682; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { long long __ret683 = 1;
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret683; }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret684 = 0;
    return __ret684; }
}
long long isEnumEq_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    if (op == 50) {
    }
    else {
    if (op == 51) {
    }
    else {
    { long long __ret685 = 0;
    return __ret685; }
    }
    }
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 2) {
    { long long __ret686 = isEnumName_c_Comp_start_U64_len_U64(&((*c)), lt.nameStart, lt.nameLen);
    return __ret686; }
    }
    { long long __ret687 = 0;
    return __ret687; }
}
long long compareNeedsTrait_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    if (op < 50) {
    { long long __ret688 = 0;
    return __ret688; }
    }
    if (op > 55) {
    { long long __ret689 = 0;
    return __ret689; }
    }
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 3) {
    { long long __ret690 = 1;
    return __ret690; }
    }
    if (lt.kind == 2) {
    if (isEnumName_c_Comp_start_U64_len_U64(&((*c)), lt.nameStart, lt.nameLen)) {
    { long long __ret691 = 0;
    return __ret691; }
    }
    { long long __ret692 = 1;
    return __ret692; }
    }
    { long long __ret693 = 0;
    return __ret693; }
}
void emitEnumOperand_c_Comp_id_U64_enStart_U64_enLen_U64(Comp* c, uint64_t id, uint64_t enStart, uint64_t enLen) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m694 = e;
    if (_m694.tag == 6) {
        uint64_t typeStart = _m694.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m694.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m694.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m694.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m694.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m694.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m694.data.Make.fields;
        (void)fields;
    if (isEnum) {
    writeU64_n_U64(variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(&((*c)), enStart, enLen, variantStart, variantLen));
    return;
    }
    }
    else {
    }
    }
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), id);
    plew_write((PlewString){").tag", 5});
}
void emitEnumTagCmp_c_Comp_lhs_U64_rhs_U64_op_I64_outer_Bool(Comp* c, uint64_t lhs, uint64_t rhs, int64_t op, long long outer) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    uint64_t enStart = 0;
    uint64_t enLen = 0;
    if (lt.kind == 2) {
    enStart = lt.nameStart;
    enLen = lt.nameLen;
    }
    else {
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), rhs);
    enStart = rt.nameStart;
    enLen = rt.nameLen;
    }
    if (isAllNullary_c_Comp_start_U64_len_U64(&((*c)), enStart, enLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), lhs)), (PlewString){"enum == needs structural Eq for payload variants (only all-nullary enums compare by tag)", 88});
    return;
    }
    if (outer) {
    plew_write((PlewString){"(", 1});
    }
    emitEnumOperand_c_Comp_id_U64_enStart_U64_enLen_U64(&((*c)), lhs, enStart, enLen);
    if (op == 51) {
    plew_write((PlewString){" != ", 4});
    }
    else {
    plew_write((PlewString){" == ", 4});
    }
    emitEnumOperand_c_Comp_id_U64_enStart_U64_enLen_U64(&((*c)), rhs, enStart, enLen);
    if (outer) {
    plew_write((PlewString){")", 1});
    }
}
uint64_t findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(Comp* c, uint64_t typeStart, uint64_t typeLen, PlewString name) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.isAssoc) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, typeStart, typeLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), f.nameStart, f.nameLen, name)) {
    { uint64_t __ret695 = i;
    Func_release(f);
    return __ret695; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { uint64_t __ret696 = (long long)(((*c).funcs).len);
    return __ret696; }
}
uint64_t orderingVariantIndex_c_Comp_name_String(Comp* c, PlewString name) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), e.nameStart, e.nameLen, (PlewString){"Ordering", 8})) {
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), PlewArray_Variant_get(vars, (long long)(vi)).nameStart, PlewArray_Variant_get(vars, (long long)(vi)).nameLen, name)) {
    { uint64_t __ret697 = vi;
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    return __ret697; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret698 = 0;
    return __ret698; }
}
long long hasCompareWitness_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 2) {
    if (op == 50) {
    { long long __ret699 = eqWitnessReady_c_Comp_ti_TypeInfo(&((*c)), lt);
    return __ret699; }
    }
    if (op == 51) {
    { long long __ret700 = eqWitnessReady_c_Comp_ti_TypeInfo(&((*c)), lt);
    return __ret700; }
    }
    if (op >= 52) {
    if (op <= 55) {
    if (typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(&((*c)), lt.nameStart, lt.nameLen, (PlewString){"Ord", 3})) {
    { long long __ret701 = (findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(&((*c)), lt.nameStart, lt.nameLen, (PlewString){"compare", 7}) < (long long)(((*c).funcs).len));
    return __ret701; }
    }
    }
    }
    }
    { long long __ret702 = 0;
    return __ret702; }
}
long long eqWitnessReady_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(&((*c)), ti.nameStart, ti.nameLen, (PlewString){"Eq", 2})) {
    { long long __ret703 = (findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(&((*c)), ti.nameStart, ti.nameLen, (PlewString){"eq", 2}) < (long long)(((*c).funcs).len));
    return __ret703; }
    }
    { long long __ret704 = 0;
    return __ret704; }
}
void emitEqCall_c_Comp_typeStart_U64_typeLen_U64_lhs_U64_rhs_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t lhs, uint64_t rhs) {
    uint64_t fi = findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(&((*c)), typeStart, typeLen, (PlewString){"eq", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen);
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(fi)));
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){")", 1});
}
void emitTraitCompare_c_Comp_op_I64_lhs_U64_rhs_U64(Comp* c, int64_t op, uint64_t lhs, uint64_t rhs) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (op == 50) {
    emitEqCall_c_Comp_typeStart_U64_typeLen_U64_lhs_U64_rhs_U64(&((*c)), lt.nameStart, lt.nameLen, lhs, rhs);
    return;
    }
    if (op == 51) {
    plew_write((PlewString){"(!", 2});
    emitEqCall_c_Comp_typeStart_U64_typeLen_U64_lhs_U64_rhs_U64(&((*c)), lt.nameStart, lt.nameLen, lhs, rhs);
    plew_write((PlewString){")", 1});
    return;
    }
    uint64_t ci = findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(&((*c)), lt.nameStart, lt.nameLen, (PlewString){"compare", 7});
    uint64_t lessIdx = orderingVariantIndex_c_Comp_name_String(&((*c)), (PlewString){"Less", 4});
    uint64_t greaterIdx = orderingVariantIndex_c_Comp_name_String(&((*c)), (PlewString){"Greater", 7});
    plew_write((PlewString){"(", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), lt.nameStart, lt.nameLen);
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(ci)));
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){").tag ", 6});
    if (op == 52) {
    plew_write((PlewString){"== ", 3});
    writeU64_n_U64(lessIdx);
    }
    if (op == 53) {
    plew_write((PlewString){"!= ", 3});
    writeU64_n_U64(greaterIdx);
    }
    if (op == 54) {
    plew_write((PlewString){"== ", 3});
    writeU64_n_U64(greaterIdx);
    }
    if (op == 55) {
    plew_write((PlewString){"!= ", 3});
    writeU64_n_U64(lessIdx);
    }
    plew_write((PlewString){")", 1});
}
void genCond_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = PlewArray_Expr_get((*c).exprs, (long long)(id));
    {
    Expr _m705 = e;
    if (_m705.tag == 3) {
        int64_t op = _m705.data.Binary.op;
        (void)op;
        uint64_t lhs = _m705.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m705.data.Binary.rhs;
        (void)rhs;
    if (isStringEq_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    genExpr_c_Comp_id_U64(&((*c)), id);
    }
    else {
    if (hasCompareWitness_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    emitTraitCompare_c_Comp_op_I64_lhs_U64_rhs_U64(&((*c)), op, lhs, rhs);
    }
    else {
    if (isEnumEq_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    emitEnumTagCmp_c_Comp_lhs_U64_rhs_U64_op_I64_outer_Bool(&((*c)), lhs, rhs, op, 0);
    }
    else {
    if (compareNeedsTrait_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), lhs)), (PlewString){"comparison needs Eq/Ord; not available for a struct or array", 60});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write(binOpStr_op_I64(op));
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    }
    }
    }
    }
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), id);
    }
    }
}
long long tryArrayElemFieldAssign_c_Comp_op_I64_target_U64_value_U64(Comp* c, int64_t op, uint64_t target, uint64_t value) {
    Expr te = PlewArray_Expr_get((*c).exprs, (long long)(target));
    {
    Expr _m706 = te;
    if (_m706.tag == 5) {
        uint64_t base = _m706.data.Field.base;
        (void)base;
        uint64_t nameStart = _m706.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m706.data.Field.nameLen;
        (void)nameLen;
    Expr be = PlewArray_Expr_get((*c).exprs, (long long)(base));
    {
    Expr _m707 = be;
    if (_m707.tag == 9) {
        uint64_t abase = _m707.data.Index.base;
        (void)abase;
        uint64_t index = _m707.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), abase);
    if (bt.kind == 3) {
    }
    else {
    { long long __ret708 = 0;
    return __ret708; }
    }
    if (placeIsMutable_c_Comp_id_U64(&((*c)), target)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), target)), (PlewString){"cannot assign through this place; the binding and field must be declared `mut val`", 82});
    { long long __ret709 = 1;
    return __ret709; }
    }
    TypeInfo ft = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    if (op == 49) {
    checkLitTi_c_Comp_id_U64_ti_TypeInfo(&((*c)), value, ft);
    }
    plew_write((PlewString){"    PlewArray_", 14});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_set(&(", 7});
    genExpr_c_Comp_id_U64(&((*c)), abase);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr_c_Comp_id_U64(&((*c)), index);
    plew_write((PlewString){"), ({ ", 6});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){" __ge = ", 8});
    genArrayGet_c_Comp_base_U64_index_U64_elemStart_U64_elemLen_U64(&((*c)), abase, index, bt.nameStart, bt.nameLen);
    plew_write((PlewString){"; __ge.", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){" = ", 3});
    if (op == 49) {
    genExpr_c_Comp_id_U64(&((*c)), value);
    }
    else {
    int64_t cbin = compoundCheckedBin_op_I64(op);
    long long fieldInt = isIntType_c_Comp_start_U64_len_U64(&((*c)), ft.nameStart, ft.nameLen);
    if (isCompoundDiv_op_I64(op)) {
    plew_write(compoundDivFn_op_I64(op));
    plew_write((PlewString){"__ge.", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), value);
    plew_write((PlewString){")", 1});
    }
    else {
    long long checkedF = 0;
    if (cbin != 0) {
    if (fieldInt) {
    checkedF = 1;
    }
    }
    if (checkedF) {
    plew_write((PlewString){"({ ", 3});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), ft.nameStart, ft.nameLen);
    plew_write((PlewString){" __ov; if (", 11});
    plew_write(overflowBuiltin_op_I64(cbin));
    plew_write((PlewString){"((__ge.", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){"), (", 4});
    genExpr_c_Comp_id_U64(&((*c)), value);
    plew_write((PlewString){"), &__ov)) plew_panic((PlewString){\"integer overflow\", 16}); __ov; })", 69});
    }
    else {
    plew_write((PlewString){"__ge.", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write(assignToBinStr_op_I64(op));
    genExpr_c_Comp_id_U64(&((*c)), value);
    }
    }
    }
    plew_write((PlewString){"; __ge; }));\n", 13});
    { long long __ret710 = 1;
    return __ret710; }
    }
    else {
    { long long __ret711 = 0;
    return __ret711; }
    }
    }
    }
    else {
    { long long __ret712 = 0;
    return __ret712; }
    }
    }
}
void emitStructMatch_c_Comp_scrut_U64_arm_MatchArm(Comp* c, uint64_t scrut, MatchArm arm) {
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo st = exprType_c_Comp_id_U64(&((*c)), scrut);
    long long generic = isGenericInst_c_Comp_ref_U64(&((*c)), st.ref);
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    plew_write((PlewString){"    {\n    ", 10});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), st.ref, st.nameStart, st.nameLen, 0);
    plew_write((PlewString){" _m", 3});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), scrut);
    plew_write((PlewString){";\n", 2});
    PlewArray_Bind binds = PlewArray_Bind_share(arm.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).len)) {
    Bind bd = PlewArray_Bind_get(binds, (long long)(bi));
    TypeInfo ft = scalarInfo();
    if (generic) {
    ft = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), st.ref, bd.fieldStart, bd.fieldLen);
    }
    else {
    ft = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), st.nameStart, st.nameLen, bd.fieldStart, bd.fieldLen);
    }
    plew_write((PlewString){"        ", 8});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), ft.ref, ft.nameStart, ft.nameLen, (ft.kind == 3));
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = _m", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.fieldStart, bd.fieldLen);
    plew_write((PlewString){";\n        (void)", 16});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){";\n", 2});
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), bd.nameStart, bd.nameLen, ft.nameStart, ft.nameLen, (ft.kind == 3), ft.ref, 0, 0, 0);
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t savedBB = (*c).curBranchBase;
    (*c).curBranchBase = mark;
    genBlock_c_Comp_id_U64(&((*c)), arm.body);
    (*c).curBranchBase = savedBB;
    scopeExit_c_Comp_mark_U64(&((*c)), mark);
    plew_write((PlewString){"    }\n", 6});
    PlewArray_Bind_release(binds);
}
void genStmt_c_Comp_id_U64(Comp* c, uint64_t id) {
    Stmt s = PlewArray_Stmt_get((*c).stmts, (long long)(id));
    {
    Stmt _m713 = s;
    if (_m713.tag == 0) {
        long long mutable = _m713.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m713.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m713.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m713.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m713.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m713.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m713.data.Let.ty;
        (void)ty;
        uint64_t init = _m713.data.Let.init;
        (void)init;
    uint64_t effStart = tyStart;
    uint64_t effLen = tyLen;
    long long effArr = tyIsArray;
    uint64_t effTy = ty;
    if (tyLen == 0) {
    if (tyIsArray) {
    }
    else {
    TypeInfo ti = exprType_c_Comp_id_U64(&((*c)), init);
    effStart = ti.nameStart;
    effLen = ti.nameLen;
    effTy = ti.ref;
    if (ti.kind == 3) {
    effArr = 1;
    }
    if (ti.kind == 1) {
    if (effLen == 0) {
    Bind ss = stringTypeSpan_c_Comp(&((*c)));
    if (ss.nameLen == 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), init)), (PlewString){"cannot infer the type of this binding; add a type annotation (e.g. `: String`)", 78});
    return;
    }
    effStart = ss.nameStart;
    effLen = ss.nameLen;
    }
    }
    }
    }
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), init, effStart, effLen, effArr);
    checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(&((*c)), init, 0);
    uint64_t cnum = shadowCount_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen);
    if (isBoxedLocalAt_c_Comp_nameStart_U64(&((*c)), nameStart)) {
    plew_write((PlewString){"    ", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), effTy, effStart, effLen, effArr);
    plew_write((PlewString){"* ", 2});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){" = (", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), effTy, effStart, effLen, effArr);
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), effTy, effStart, effLen, effArr);
    plew_write((PlewString){")); *", 5});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), init);
    plew_write((PlewString){";\n", 2});
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), nameStart, nameLen, effStart, effLen, effArr, effTy, 0, mutable, 1, cnum);
    return;
    }
    plew_write((PlewString){"    ", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), effTy, effStart, effLen, effArr);
    plew_write((PlewString){" ", 1});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){" = ", 3});
    if (effArr) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), init, effStart, effLen);
    }
    else {
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), init, effTy, effStart, effLen, 0);
    }
    plew_write((PlewString){";\n", 2});
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), nameStart, nameLen, effStart, effLen, effArr, effTy, 0, mutable, 1, cnum);
    }
    else if (_m713.tag == 1) {
        int64_t op = _m713.data.Assign.op;
        (void)op;
        uint64_t target = _m713.data.Assign.target;
        (void)target;
        uint64_t value = _m713.data.Assign.value;
        (void)value;
    if (tryArrayElemFieldAssign_c_Comp_op_I64_target_U64_value_U64(&((*c)), op, target, value)) {
    return;
    }
    Expr te = PlewArray_Expr_get((*c).exprs, (long long)(target));
    {
    Expr _m714 = te;
    if (_m714.tag == 9) {
        uint64_t base = _m714.data.Index.base;
        (void)base;
        uint64_t index = _m714.data.Index.index;
        (void)index;
    if (placeIsMutable_c_Comp_id_U64(&((*c)), base)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), base)), (PlewString){"cannot assign to an element of an immutable binding; declare it with `mut val`", 78});
    return;
    }
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), value, bt.nameStart, bt.nameLen, 0);
    }
    plew_write((PlewString){"    PlewArray_", 14});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_set(&(", 7});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr_c_Comp_id_U64(&((*c)), index);
    plew_write((PlewString){"), ", 3});
    if (op == 49) {
    genExpr_c_Comp_id_U64(&((*c)), value);
    }
    else {
    int64_t cbin = compoundCheckedBin_op_I64(op);
    long long elemInt = isIntType_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    if (isCompoundDiv_op_I64(op)) {
    plew_write(compoundDivFn_op_I64(op));
    genArrayGet_c_Comp_base_U64_index_U64_elemStart_U64_elemLen_U64(&((*c)), base, index, bt.nameStart, bt.nameLen);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), value);
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
    genCElem_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){" __ov; if (", 11});
    plew_write(overflowBuiltin_op_I64(cbin));
    plew_write((PlewString){"((", 2});
    genArrayGet_c_Comp_base_U64_index_U64_elemStart_U64_elemLen_U64(&((*c)), base, index, bt.nameStart, bt.nameLen);
    plew_write((PlewString){"), (", 4});
    genExpr_c_Comp_id_U64(&((*c)), value);
    plew_write((PlewString){"), &__ov)) plew_panic((PlewString){\"integer overflow\", 16}); __ov; })", 69});
    }
    else {
    genArrayGet_c_Comp_base_U64_index_U64_elemStart_U64_elemLen_U64(&((*c)), base, index, bt.nameStart, bt.nameLen);
    plew_write(assignToBinStr_op_I64(op));
    genExpr_c_Comp_id_U64(&((*c)), value);
    }
    }
    }
    plew_write((PlewString){");\n", 3});
    }
    else {
    if (placeIsMutable_c_Comp_id_U64(&((*c)), target)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), target)), (PlewString){"cannot assign to an immutable place; the binding and field must be declared `mut val`", 85});
    return;
    }
    TypeInfo ctt = exprType_c_Comp_id_U64(&((*c)), target);
    if (ctt.kind == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), ctt.nameStart, ctt.nameLen)) {
    if (op == 49) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), target)), (PlewString){"compound assignment is not valid for a unique value", 51});
    return;
    }
    checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(&((*c)), value, 0);
    plew_write((PlewString){"    ", 4});
    if (structHasDeinit_c_Comp_start_U64_len_U64(&((*c)), ctt.nameStart, ctt.nameLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), ctt.nameStart, ctt.nameLen);
    plew_write((PlewString){"_deinit(", 8});
    genExpr_c_Comp_id_U64(&((*c)), target);
    plew_write((PlewString){"); ", 3});
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), ctt.nameStart, ctt.nameLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), ctt.nameStart, ctt.nameLen);
    plew_write((PlewString){"_release(", 9});
    genExpr_c_Comp_id_U64(&((*c)), target);
    plew_write((PlewString){"); ", 3});
    }
    genExpr_c_Comp_id_U64(&((*c)), target);
    plew_write((PlewString){" = ", 3});
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), value, ctt.ref, ctt.nameStart, ctt.nameLen, 0);
    plew_write((PlewString){";\n", 2});
    return;
    }
    }
    if (ctt.kind == 3) {
    checkLitArray_c_Comp_id_U64_elemStart_U64_elemLen_U64(&((*c)), value, ctt.nameStart, ctt.nameLen);
    }
    else {
    checkLitTi_c_Comp_id_U64_ti_TypeInfo(&((*c)), value, ctt);
    }
    plew_write((PlewString){"    ", 4});
    genExpr_c_Comp_id_U64(&((*c)), target);
    if (isCompoundDiv_op_I64(op)) {
    plew_write((PlewString){" = ", 3});
    TypeInfo dt = exprType_c_Comp_id_U64(&((*c)), target);
    if (dt.kind == 0) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), dt.nameStart, dt.nameLen)) {
    genCheckedDiv_c_Comp_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64_isMod_Bool(&((*c)), target, value, dt.nameStart, dt.nameLen, (op == 71));
    }
    else {
    plew_write(compoundDivFn_op_I64(op));
    genExpr_c_Comp_id_U64(&((*c)), target);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), value);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    plew_write(compoundDivFn_op_I64(op));
    genExpr_c_Comp_id_U64(&((*c)), target);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), value);
    plew_write((PlewString){")", 1});
    }
    }
    else {
    TypeInfo tt = exprType_c_Comp_id_U64(&((*c)), target);
    int64_t cbin = compoundCheckedBin_op_I64(op);
    long long checked = 0;
    if (cbin != 0) {
    if (tt.kind == 0) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), tt.nameStart, tt.nameLen)) {
    checked = 1;
    }
    }
    }
    if (checked) {
    plew_write((PlewString){" = ", 3});
    genCheckedArith_c_Comp_op_I64_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64(&((*c)), cbin, target, value, tt.nameStart, tt.nameLen);
    }
    else {
    plew_write(assignOpStr_op_I64(op));
    if (op == 49) {
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), value, tt.ref, tt.nameStart, tt.nameLen, (tt.kind == 3));
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), value);
    }
    }
    }
    plew_write((PlewString){";\n", 2});
    }
    }
    }
    else if (_m713.tag == 2) {
        uint64_t expr = _m713.data.Print.expr;
        (void)expr;
        uint64_t offset = _m713.data.Print.offset;
        (void)offset;
    if ((*c).impPrint) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), expr, 1, 64, 1);
    plew_write((PlewString){"    printf(\"%lld\\n\", (long long)(", 33});
    genExpr_c_Comp_id_U64(&((*c)), expr);
    plew_write((PlewString){"));\n", 4});
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"print is not ambient; import it from @Std/Io", 44});
    }
    }
    else if (_m713.tag == 3) {
        uint64_t expr = _m713.data.ExprStmt.expr;
        (void)expr;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), expr, 0, 0, 0);
    plew_write((PlewString){"    ", 4});
    genExpr_c_Comp_id_U64(&((*c)), expr);
    plew_write((PlewString){";\n", 2});
    }
    else if (_m713.tag == 4) {
        uint64_t value = _m713.data.Return.value;
        (void)value;
        long long hasValue = _m713.data.Return.hasValue;
        (void)hasValue;
    if ((*c).curIsMain) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), 0, (long long)(((*c).locals).len));
    plew_write((PlewString){"    return 0;\n", 14});
    }
    else {
    if ((*c).curRetVoid) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), 0, (long long)(((*c).locals).len));
    emitSelfDeinit_c_Comp(&((*c)));
    plew_write((PlewString){"    return;\n", 12});
    }
    else {
    if (hasValue) {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), value, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    }
    uint64_t rt = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    plew_write((PlewString){"    { ", 6});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), (*c).curRetTy, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    plew_write((PlewString){" __ret", 6});
    writeU64_n_U64(rt);
    plew_write((PlewString){" = ", 3});
    if (hasValue) {
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), value, (*c).curRetTy, (*c).curRetStart, (*c).curRetLen, (*c).curRetIsArray);
    }
    else {
    plew_write((PlewString){"0", 1});
    }
    plew_write((PlewString){";\n", 2});
    uint64_t retExcl = (long long)(((*c).locals).len);
    if (hasValue) {
    TypeInfo vt = exprType_c_Comp_id_U64(&((*c)), value);
    if (vt.kind == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), vt.nameStart, vt.nameLen)) {
    {
    Expr _m715 = PlewArray_Expr_get((*c).exprs, (long long)(value));
    if (_m715.tag == 1) {
        uint64_t start = _m715.data.Ident.start;
        (void)start;
        uint64_t len = _m715.data.Ident.len;
        (void)len;
    if ((*c).curSelfMove) {
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), value)), (PlewString){"returning `self` from a `move fn` is not yet supported", 54});
    }
    }
    retExcl = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    }
    else if (_m715.tag == 5) {
        uint64_t base = _m715.data.Field.base;
        (void)base;
        uint64_t nameStart = _m715.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m715.data.Field.nameLen;
        (void)nameLen;
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), value)), (PlewString){"returning a field of a unique value is a partial move (not yet supported)", 73});
    }
    else if (_m715.tag == 9) {
        uint64_t base = _m715.data.Index.base;
        (void)base;
        uint64_t index = _m715.data.Index.index;
        (void)index;
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), value)), (PlewString){"returning an element of a unique value is a partial move (not yet supported)", 76});
    }
    else {
    }
    }
    }
    }
    }
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), 0, retExcl);
    emitSelfDeinit_c_Comp(&((*c)));
    plew_write((PlewString){"    return __ret", 16});
    writeU64_n_U64(rt);
    plew_write((PlewString){"; }\n", 4});
    }
    }
    }
    else if (_m713.tag == 5) {
        uint64_t cond = _m713.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m713.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m713.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m713.data.If.hasElse;
        (void)hasElse;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), cond, 0, 0, 0);
    plew_write((PlewString){"    if (", 8});
    genCond_c_Comp_id_U64(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    uint64_t savedBB = (*c).curBranchBase;
    (*c).curBranchBase = scopeMark_c_Comp(&((*c)));
    genBlock_c_Comp_id_U64(&((*c)), thenBlk);
    plew_write((PlewString){"    }\n", 6});
    if (hasElse) {
    plew_write((PlewString){"    else {\n", 11});
    (*c).curBranchBase = scopeMark_c_Comp(&((*c)));
    genBlock_c_Comp_id_U64(&((*c)), elseBlk);
    plew_write((PlewString){"    }\n", 6});
    }
    (*c).curBranchBase = savedBB;
    }
    else if (_m713.tag == 6) {
        uint64_t cond = _m713.data.While.cond;
        (void)cond;
        uint64_t body = _m713.data.While.body;
        (void)body;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), cond, 0, 0, 0);
    plew_write((PlewString){"    while (", 11});
    genCond_c_Comp_id_U64(&((*c)), cond);
    plew_write((PlewString){") {\n", 4});
    uint64_t savedLoopMark = (*c).curLoopMark;
    (*c).curLoopMark = scopeMark_c_Comp(&((*c)));
    uint64_t savedBB = (*c).curBranchBase;
    (*c).curBranchBase = scopeMark_c_Comp(&((*c)));
    genBlock_c_Comp_id_U64(&((*c)), body);
    (*c).curBranchBase = savedBB;
    (*c).curLoopMark = savedLoopMark;
    plew_write((PlewString){"    }\n", 6});
    }
    else if (_m713.tag == 7) {
        uint64_t varStart = _m713.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m713.data.For.varLen;
        (void)varLen;
        long long isRange = _m713.data.For.isRange;
        (void)isRange;
        long long inclusive = _m713.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m713.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m713.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m713.data.For.body;
        (void)body;
    if (isRange) {
    checkArithNoCtx_c_Comp_lhs_U64_rhs_U64(&((*c)), iter, rangeHi);
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t forMark = scopeMark_c_Comp(&((*c)));
    uint64_t savedLoopMark = (*c).curLoopMark;
    (*c).curLoopMark = forMark;
    uint64_t savedBB = (*c).curBranchBase;
    (*c).curBranchBase = forMark;
    if (isRange) {
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    long long __fe", 18});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), rangeHi);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"    for (long long ", 19});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), varStart, varLen);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), iter);
    plew_write((PlewString){"; ", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), varStart, varLen);
    if (inclusive) {
    plew_write((PlewString){" <= __fe", 8});
    }
    else {
    plew_write((PlewString){" < __fe", 7});
    }
    writeU64_n_U64(t);
    plew_write((PlewString){"; ", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), varStart, varLen);
    plew_write((PlewString){"++) {\n", 6});
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, 0, 0, 0, 0, 0, 0, 0);
    genBlock_c_Comp_id_U64(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    else {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), iter);
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    ", 4});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){" __fa", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), iter);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"    for (long long __fi", 23});
    writeU64_n_U64(t);
    plew_write((PlewString){" = 0; __fi", 10});
    writeU64_n_U64(t);
    plew_write((PlewString){" < __fa", 7});
    writeU64_n_U64(t);
    plew_write((PlewString){".len; __fi", 10});
    writeU64_n_U64(t);
    plew_write((PlewString){"++) {\n", 6});
    plew_write((PlewString){"        ", 8});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), varStart, varLen);
    plew_write((PlewString){" = ", 3});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"_get(__fa", 9});
    writeU64_n_U64(t);
    plew_write((PlewString){", __fi", 6});
    writeU64_n_U64(t);
    plew_write((PlewString){");\n", 3});
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0, 0, 0, 0);
    genBlock_c_Comp_id_U64(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    (*c).curBranchBase = savedBB;
    (*c).curLoopMark = savedLoopMark;
    scopeExit_c_Comp_mark_U64(&((*c)), forMark);
    }
    else if (_m713.tag == 9) {
        uint64_t msg = _m713.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m713.data.Panic.offset;
        (void)offset;
    plew_write((PlewString){"    plew_panic(", 15});
    genExpr_c_Comp_id_U64(&((*c)), msg);
    plew_write((PlewString){");\n", 3});
    }
    else if (_m713.tag == 10) {
        uint64_t value = _m713.data.Give.value;
        (void)value;
    TypeInfo gvt = exprType_c_Comp_id_U64(&((*c)), value);
    if (gvt.kind == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), gvt.nameStart, gvt.nameLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), value)), (PlewString){"a value-position if/match cannot yield a unique value yet; use a statement form", 79});
    }
    }
    if ((*c).curGiveTmp != 0) {
    plew_write((PlewString){"    __r", 7});
    writeU64_n_U64(({ uint64_t __ov; if (__builtin_sub_overflow(((*c).curGiveTmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    plew_write((PlewString){" = (", 4});
    genExpr_c_Comp_id_U64(&((*c)), value);
    plew_write((PlewString){");\n", 3});
    }
    }
    else if (_m713.tag == 11) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), (*c).curLoopMark, (long long)(((*c).locals).len));
    plew_write((PlewString){"    break;\n", 11});
    }
    else if (_m713.tag == 12) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), (*c).curLoopMark, (long long)(((*c).locals).len));
    plew_write((PlewString){"    continue;\n", 14});
    }
    else if (_m713.tag == 8) {
        uint64_t scrut = _m713.data.Match.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m713.data.Match.arms;
        (void)arms;
    if ((long long)((arms).len) > 0) {
    if (PlewArray_MatchArm_get(arms, (long long)(0)).isStruct) {
    emitStructMatch_c_Comp_scrut_U64_arm_MatchArm(&((*c)), scrut, PlewArray_MatchArm_get(arms, (long long)(0)));
    return;
    }
    }
    if (matchExhaustive_c_Comp_arms_AMatchArm(&((*c)), PlewArray_MatchArm_share(arms))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), scrut)), (PlewString){"match must be exhaustive: cover all variants or add a wildcard", 62});
    return;
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t scrutRef = exprType_c_Comp_id_U64(&((*c)), scrut).ref;
    long long genericMatch = isGenericEnumInst_c_Comp_ref_U64(&((*c)), scrutRef);
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
    emitMangle_c_Comp_ref_U64(&((*c)), scrutRef);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), enumStart, enumLen);
    }
    plew_write((PlewString){" _m", 3});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    genExpr_c_Comp_id_U64(&((*c)), scrut);
    plew_write((PlewString){";\n", 2});
    uint64_t i = 0;
    long long firstCond = 1;
    uint64_t savedBB = (*c).curBranchBase;
    while (i < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    plew_write((PlewString){"    else {\n", 11});
    (*c).curBranchBase = scopeMark_c_Comp(&((*c)));
    genBlock_c_Comp_id_U64(&((*c)), a.body);
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
    writeU64_n_U64(t);
    plew_write((PlewString){".tag == ", 8});
    writeU64_n_U64(variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen));
    plew_write((PlewString){") {\n", 4});
    uint64_t armMark = scopeMark_c_Comp(&((*c)));
    PlewArray_Bind binds = PlewArray_Bind_share(a.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).len)) {
    Bind bd = PlewArray_Bind_get(binds, (long long)(bi));
    plew_write((PlewString){"        ", 8});
    if (genericMatch) {
    genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    else {
    genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = _m", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), a.variantStart, a.variantLen);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.fieldStart, bd.fieldLen);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"        (void)", 14});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){";\n", 2});
    if (genericMatch) {
    TypeInfo bti = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0, 0);
    }
    else {
    addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).curBranchBase = armMark;
    genBlock_c_Comp_id_U64(&((*c)), a.body);
    scopeExit_c_Comp_mark_U64(&((*c)), armMark);
    plew_write((PlewString){"    }\n", 6});
    PlewArray_Bind_release(binds);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    (*c).curBranchBase = savedBB;
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
void genBlock_c_Comp_id_U64(Comp* c, uint64_t id) {
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    Block b = Block_share(PlewArray_Block_get((*c).blocks, (long long)(id)));
    PlewArray_U64 stmts = PlewArray_U64_share(b.stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).len)) {
    genStmt_c_Comp_id_U64(&((*c)), PlewArray_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scopeExit_c_Comp_mark_U64(&((*c)), mark);
    PlewArray_U64_release(stmts);
    Block_release(b);
}
long long nameIsMain_c_Comp_f_Func(Comp* c, Func f) {
    if (f.hasRecv) {
    { long long __ret716 = 0;
    return __ret716; }
    }
    { long long __ret717 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), f.nameStart, f.nameLen, (PlewString){"main", 4});
    return __ret717; }
}
long long isTraitName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).traits).len)) {
    TraitDef t = TraitDef_share(PlewArray_TraitDef_get((*c).traits, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, start, len)) {
    { long long __ret718 = 1;
    TraitDef_release(t);
    return __ret718; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TraitDef_release(t);
    }
    { long long __ret719 = 0;
    return __ret719; }
}
long long methodRecvIsTrait_c_Comp_f_Func(Comp* c, Func f) {
    if (f.hasRecv) {
    { long long __ret720 = isTraitName_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen);
    return __ret720; }
    }
    { long long __ret721 = 0;
    return __ret721; }
}
long long methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t lo, uint64_t hi, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = lo;
    while (i < hi) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, recvStart, recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    { long long __ret722 = 1;
    Func_release(f);
    return __ret722; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { long long __ret723 = 0;
    return __ret723; }
}
void instantiateProvidedMethods_c_Comp(Comp* c) {
    uint64_t nFuncs = (long long)(((*c).funcs).len);
    uint64_t ci = 0;
    while (ci < (long long)(((*c).conforms).len)) {
    Conform cf = Conform_share(PlewArray_Conform_get((*c).conforms, (long long)(ci)));
    uint64_t fi = 0;
    while (fi < nFuncs) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, cf.traitStart, cf.traitLen)) {
    if (methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(&((*c)), 0, nFuncs, cf.typeStart, cf.typeLen, f.nameStart, f.nameLen)) {
    }
    else {
    if (methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(&((*c)), nFuncs, (long long)(((*c).funcs).len), cf.typeStart, cf.typeLen, f.nameStart, f.nameLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), cf.typeStart), (PlewString){"two conformed traits provide a method of the same name; the bare call is ambiguous (`#`-disambiguation not yet supported)", 121});
    }
    else {
    PlewArray_Func_push(&((*c).funcs), (Func){.nameStart = f.nameStart, .nameLen = f.nameLen, .typeParams = PlewArray_Bind_share(f.typeParams), .params = PlewArray_Param_share(f.params), .hasRet = f.hasRet, .retStart = f.retStart, .retLen = f.retLen, .retIsArray = f.retIsArray, .retTy = f.retTy, .body = f.body, .hasRecv = 1, .recvStart = cf.typeStart, .recvLen = cf.typeLen, .selfInout = f.selfInout, .selfMove = f.selfMove, .isAssoc = f.isAssoc});
    }
    }
    }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Conform_release(cf);
    }
}
uint64_t structIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(i)));
    if ((long long)((s.typeParams).len) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, start, len)) {
    { uint64_t __ret724 = i;
    StructDef_release(s);
    return __ret724; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { uint64_t __ret725 = (long long)(((*c).structs).len);
    return __ret725; }
}
long long structNeedsCopy_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret726 = 0;
    return __ret726; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    { long long __ret727 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret727; }
    }
    else {
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret728 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret728; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret729 = 0;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret729; }
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
long long structNeedsRelease_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret730 = 0;
    return __ret730; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    { long long __ret731 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret731; }
    }
    else {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret732 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret732; }
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret733 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret733; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret734 = 0;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    return __ret734; }
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void emitDeinitProtos_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).deinits).len)) {
    Bind d = PlewArray_Bind_get((*c).deinits, (long long)(i));
    plew_write((PlewString){"void ", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), d.nameStart, d.nameLen);
    plew_write((PlewString){"_deinit(", 8});
    genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), d.nameStart, d.nameLen, 0);
    plew_write((PlewString){" self);\n", 8});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void emitStructCopyProto_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void emitStructCopyDef_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) { ", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    plew_write((PlewString){" r.", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_copy(s.", 8});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    else {
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" r.", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_copy(s.", 8});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" return r; }\n", 13});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void emitStructShareProto_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void emitStructShareDef_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) {", 5});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    plew_write((PlewString){" plew_arc_retain(s.", 19});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){".rc);", 5});
    }
    else {
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_share(s.", 9});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" return s; }\n", 13});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void emitStructReleaseProto_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"void ", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void emitStructReleaseDef_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"void ", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) {", 5});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    if (f.tyIsArray) {
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_release(s.", 11});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    else {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    if (structHasDeinit_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_deinit(s.", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_release(s.", 11});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    }
    else {
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_release(s.", 11});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" }\n", 3});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
long long monoStructNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    { long long __ret735 = 0;
    TypeRef_release(t);
    return __ret735; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, PlewArray_Bind_share(s.typeParams), PlewArray_FieldDef_get(fields, (long long)(i)).ty);
    if (ti.kind == 3) {
    { long long __ret736 = 1;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret736; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret737 = 0;
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret737; }
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
void emitMonoStructCopyProto_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" s);\n", 5});
}
void emitMonoStructCopyDef_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    TypeRef_release(t);
    return;
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" s) { ", 6});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, PlewArray_Bind_share(s.typeParams), f.ty);
    if (ti.kind == 3) {
    plew_write((PlewString){" r.", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), ti.nameStart, ti.nameLen);
    plew_write((PlewString){"_copy(s.", 8});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" return r; }\n", 13});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
long long monoEnumNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    { long long __ret738 = 0;
    TypeRef_release(t);
    return __ret738; }
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(PlewArray_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, PlewArray_Bind_share(e.typeParams), PlewArray_FieldDef_get(fs, (long long)(fi)).ty);
    if (ti.kind == 3) {
    { long long __ret739 = 1;
    PlewArray_FieldDef_release(fs);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret739; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_FieldDef_release(fs);
    }
    { long long __ret740 = 0;
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret740; }
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
void emitMonoEnumCopyProto_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    emitMonoStructCopyProto_c_Comp_instRef_U64(&((*c)), instRef);
}
void emitMonoEnumCopyDef_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    TypeRef_release(t);
    return;
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){"_copy(", 6});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" s) { ", 6});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" r = s;", 7});
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    long long anyArray = 0;
    uint64_t ck = 0;
    while (ck < (long long)((fs).len)) {
    TypeInfo cti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, PlewArray_Bind_share(e.typeParams), PlewArray_FieldDef_get(fs, (long long)(ck)).ty);
    if (cti.kind == 3) {
    anyArray = 1;
    }
    ck = ({ uint64_t __ov; if (__builtin_add_overflow((ck), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (anyArray) {
    plew_write((PlewString){" if (r.tag == ", 14});
    writeU64_n_U64(vi);
    plew_write((PlewString){") {", 3});
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef f = PlewArray_FieldDef_get(fs, (long long)(fi));
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, PlewArray_Bind_share(e.typeParams), f.ty);
    if (ti.kind == 3) {
    plew_write((PlewString){" r.data.", 8});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), v.nameStart, v.nameLen);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){" = ", 3});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), ti.nameStart, ti.nameLen);
    plew_write((PlewString){"_copy(s.data.", 13});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), v.nameStart, v.nameLen);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
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
void genStructValue_c_Comp_exprId_U64_structStart_U64_structLen_U64(Comp* c, uint64_t exprId, uint64_t structStart, uint64_t structLen) {
    if (isPlaceExpr_c_Comp_id_U64(&((*c)), exprId)) {
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), structStart, structLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), structStart, structLen);
    plew_write((PlewString){"_share(", 7});
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    }
    genExpr_c_Comp_id_U64(&((*c)), exprId);
}
void genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(Comp* c, uint64_t exprId, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray) {
    if (isArray) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), exprId, fallStart, fallLen);
    return;
    }
    if (isRefInst_c_Comp_ref_U64(&((*c)), tyRef)) {
    if (isPlaceExpr_c_Comp_id_U64(&((*c)), exprId)) {
    plew_write((PlewString){"plew_ref_share((void*)(", 23});
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    plew_write((PlewString){"))", 2});
    return;
    }
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    return;
    }
    if (isFnType_c_Comp_ref_U64(&((*c)), tyRef)) {
    if (isPlaceExpr_c_Comp_id_U64(&((*c)), exprId)) {
    plew_write((PlewString){"plew_closure_share(", 19});
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    return;
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), tyRef)) {
    long long needs = 0;
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), tyRef)) {
    needs = monoEnumNeedsCopy_c_Comp_instRef_U64(&((*c)), tyRef);
    }
    else {
    needs = monoStructNeedsCopy_c_Comp_instRef_U64(&((*c)), tyRef);
    }
    if (needs) {
    if (isPlaceExpr_c_Comp_id_U64(&((*c)), exprId)) {
    emitMangle_c_Comp_ref_U64(&((*c)), tyRef);
    plew_write((PlewString){"_copy(", 6});
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    }
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    return;
    }
    genStructValue_c_Comp_exprId_U64_structStart_U64_structLen_U64(&((*c)), exprId, fallStart, fallLen);
}
void genStructDef_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"struct ", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" {\n", 3});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    plew_write((PlewString){"    ", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.ty, f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";\n", 2});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"};\n", 3});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
}
void writeFnSelector_c_Comp_f_Func(Comp* c, Func f) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    PlewArray_Param params = PlewArray_Param_share(f.params);
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    Param p = PlewArray_Param_get(params, (long long)(i));
    plew_write((PlewString){"_", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
    plew_write((PlewString){"_", 1});
    long long resolved = 0;
    if (f.hasRecv) {
    }
    else {
    if (p.tyIsArray) {
    }
    else {
    uint64_t k = 0;
    while (k < (long long)(((*c).curTypeParams).len)) {
    Bind tp = PlewArray_Bind_get((*c).curTypeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.tyStart, p.tyLen, tp.nameStart, tp.nameLen)) {
    emitMangle_c_Comp_ref_U64(&((*c)), PlewArray_U64_get((*c).curTypeArgs, (long long)(k)));
    resolved = 1;
    k = (long long)(((*c).curTypeParams).len);
    }
    else {
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    }
    if (resolved) {
    }
    else {
    if (p.tyIsArray) {
    plew_write((PlewString){"A", 1});
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.tyStart, p.tyLen);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Param_release(params);
}
void genSignature_c_Comp_f_Func(Comp* c, Func f) {
    if (nameIsMain_c_Comp_f_Func(&((*c)), f)) {
    plew_write((PlewString){"int main(int argc, char** argv)", 31});
    return;
    }
    if (f.hasRet) {
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.retTy, f.retStart, f.retLen, f.retIsArray);
    plew_write((PlewString){" ", 1});
    }
    else {
    plew_write((PlewString){"void ", 5});
    }
    if (f.hasRecv) {
    if ((*c).curRecvInstRef != 0) {
    emitMangle_c_Comp_ref_U64(&((*c)), (*c).curRecvInstRef);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen);
    }
    plew_write((PlewString){"_", 1});
    }
    else {
    if (f.isAssoc) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen);
    plew_write((PlewString){"_", 1});
    }
    }
    writeFnSelector_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"(", 1});
    PlewArray_Param params = PlewArray_Param_share(f.params);
    if (f.hasRecv) {
    if ((*c).curRecvInstRef != 0) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), (*c).curRecvInstRef);
    }
    else {
    genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), f.recvStart, f.recvLen, 0);
    }
    if (f.selfInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" self", 5});
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    plew_write((PlewString){", ", 2});
    Param p = PlewArray_Param_get(params, (long long)(i));
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
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
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    plew_write((PlewString){")", 1});
    PlewArray_Param_release(params);
}
void emitSelfDeinit_c_Comp(Comp* c) {
    if ((*c).curSelfMove) {
    if (structHasDeinit_c_Comp_start_U64_len_U64(&((*c)), (*c).curRecvStart, (*c).curRecvLen)) {
    plew_write((PlewString){"    ", 4});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), (*c).curRecvStart, (*c).curRecvLen);
    plew_write((PlewString){"_deinit(self);\n", 15});
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), (*c).curRecvStart, (*c).curRecvLen)) {
    plew_write((PlewString){"    ", 4});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), (*c).curRecvStart, (*c).curRecvLen);
    plew_write((PlewString){"_release(self);\n", 16});
    }
    }
}
void genFunc_c_Comp_fi_U64(Comp* c, uint64_t fi) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    long long isMain = nameIsMain_c_Comp_f_Func(&((*c)), f);
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
    (*c).curSelfMove = f.selfMove;
    (*c).curBranchBase = 0;
    (*c).locals = PlewArray_Local_new();
    PlewArray_Param params = PlewArray_Param_share(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((params).len)) {
    Param p = PlewArray_Param_get(params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, p.isMove);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genSignature_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){" {\n", 3});
    if (isMain) {
    plew_write((PlewString){"    plew_argc = argc; plew_argv = argv;\n", 40});
    }
    genBlock_c_Comp_id_U64(&((*c)), f.body);
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), 0, (long long)(((*c).locals).len));
    emitSelfDeinit_c_Comp(&((*c)));
    if (isMain) {
    plew_write((PlewString){"    return 0;\n", 14});
    }
    plew_write((PlewString){"}\n", 2});
    PlewArray_Param_release(params);
    Func_release(f);
}
void genClosure_c_Comp_id_U64_proto_Bool(Comp* c, uint64_t id, long long proto) {
    {
    Expr _m741 = PlewArray_Expr_get((*c).exprs, (long long)(id));
    if (_m741.tag == 17) {
        PlewArray_Param params = _m741.data.Closure.params;
        (void)params;
        long long hasRet = _m741.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m741.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m741.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m741.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m741.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m741.data.Closure.body;
        (void)body;
    if (hasRet) {
    (*c).curRetVoid = 0;
    (*c).curRetStart = retStart;
    (*c).curRetLen = retLen;
    (*c).curRetIsArray = retIsArray;
    (*c).curRetTy = retTy;
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), retTy, retStart, retLen, retIsArray);
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
    writeU64_n_U64(id);
    plew_write((PlewString){"(void* __env", 12});
    if ((long long)((params).len) == 0) {
    }
    else {
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    plew_write((PlewString){", ", 2});
    Param p = PlewArray_Param_get(params, (long long)(i));
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
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
    (*c).curBranchBase = 0;
    (*c).locals = PlewArray_Local_new();
    uint64_t pj = 0;
    while (pj < (long long)((params).len)) {
    Param p2 = PlewArray_Param_get(params, (long long)(pj));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p2.nameStart, p2.nameLen, p2.tyStart, p2.tyLen, p2.tyIsArray, p2.ty, p2.isInout, 0, p2.isMove);
    pj = ({ uint64_t __ov; if (__builtin_add_overflow((pj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t savedId = (*c).curClosureId;
    long long savedIn = (*c).curInClosure;
    (*c).curClosureId = id;
    (*c).curInClosure = 1;
    plew_write((PlewString){" {\n", 3});
    genBlock_c_Comp_id_U64(&((*c)), body);
    plew_write((PlewString){"}\n", 2});
    (*c).curClosureId = savedId;
    (*c).curInClosure = savedIn;
    }
    }
    else {
    }
    }
}
void addFnThunk_c_Comp_fi_U64(Comp* c, uint64_t fi) {
    uint64_t i = 0;
    while (i < (long long)(((*c).fnThunks).len)) {
    if (PlewArray_U64_get((*c).fnThunks, (long long)(i)) == fi) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U64_push(&((*c).fnThunks), fi);
}
void collectFnThunks_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).exprs).len)) {
    {
    Expr _m742 = PlewArray_Expr_get((*c).exprs, (long long)(i));
    if (_m742.tag == 1) {
        uint64_t start = _m742.data.Ident.start;
        (void)start;
        uint64_t len = _m742.data.Ident.len;
        (void)len;
    uint64_t fvi = firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), start, len);
    if (fvi < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fvi)));
    if (f.hasRecv) {
    }
    else {
    if (f.isAssoc) {
    }
    else {
    if ((long long)((f.typeParams).len) > 0) {
    }
    else {
    addFnThunk_c_Comp_fi_U64(&((*c)), fvi);
    }
    }
    }
    Func_release(f);
    }
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void genThunk_c_Comp_fi_U64_proto_Bool(Comp* c, uint64_t fi, long long proto) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRet) {
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.retTy, f.retStart, f.retLen, f.retIsArray);
    plew_write((PlewString){" ", 1});
    }
    else {
    plew_write((PlewString){"void ", 5});
    }
    writeFnSelector_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"__thunk(void* __env", 19});
    PlewArray_Param params = PlewArray_Param_share(f.params);
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    plew_write((PlewString){", ", 2});
    Param p = PlewArray_Param_get(params, (long long)(i));
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    if (p.isInout) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){")", 1});
    if (proto) {
    plew_write((PlewString){";\n", 2});
    PlewArray_Param_release(params);
    Func_release(f);
    return;
    }
    plew_write((PlewString){" { (void)__env; ", 16});
    if (f.hasRet) {
    plew_write((PlewString){"return ", 7});
    }
    writeFnSelector_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"(", 1});
    uint64_t j = 0;
    while (j < (long long)((params).len)) {
    if (j > 0) {
    plew_write((PlewString){", ", 2});
    }
    Param p2 = PlewArray_Param_get(params, (long long)(j));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p2.nameStart, p2.nameLen);
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"); }\n", 5});
    PlewArray_Param_release(params);
    Func_release(f);
}
void emitThunks_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t i = 0;
    while (i < (long long)(((*c).fnThunks).len)) {
    genThunk_c_Comp_fi_U64_proto_Bool(&((*c)), PlewArray_U64_get((*c).fnThunks, (long long)(i)), proto);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long closureHasCaptures_c_Comp_id_U64(Comp* c, uint64_t id) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).len)) {
    if (PlewArray_CaptureEntry_get((*c).captures, (long long)(i)).closureId == id) {
    { long long __ret743 = 1;
    return __ret743; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret744 = 0;
    return __ret744; }
}
long long isBoxedLocalAt_c_Comp_nameStart_U64(Comp* c, uint64_t nameStart) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).len)) {
    CaptureEntry e = PlewArray_CaptureEntry_get((*c).captures, (long long)(i));
    if (e.boxed) {
    if (e.nameStart == nameStart) {
    { long long __ret745 = 1;
    return __ret745; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret746 = 0;
    return __ret746; }
}
long long isBoxedCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(Comp* c, uint64_t closureId, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).len)) {
    CaptureEntry e = PlewArray_CaptureEntry_get((*c).captures, (long long)(i));
    if (e.closureId == closureId) {
    if (e.boxed) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    { long long __ret747 = 1;
    return __ret747; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret748 = 0;
    return __ret748; }
}
long long isCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(Comp* c, uint64_t closureId, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).len)) {
    CaptureEntry e = PlewArray_CaptureEntry_get((*c).captures, (long long)(i));
    if (e.closureId == closureId) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    { long long __ret749 = 1;
    return __ret749; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret750 = 0;
    return __ret750; }
}
void emitClosureEnvStruct_c_Comp_id_U64(Comp* c, uint64_t id) {
    plew_write((PlewString){"typedef struct { ", 17});
    uint64_t j = 0;
    while (j < (long long)(((*c).captures).len)) {
    CaptureEntry e = PlewArray_CaptureEntry_get((*c).captures, (long long)(j));
    if (e.closureId == id) {
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), e.ty, e.tyStart, e.tyLen, e.isArray);
    if (e.boxed) {
    plew_write((PlewString){"*", 1});
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){"; ", 2});
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"} __closure_env", 15});
    writeU64_n_U64(id);
    plew_write((PlewString){";\n", 2});
}
void emitClosureEnvDrop_c_Comp_id_U64(Comp* c, uint64_t id) {
    plew_write((PlewString){"__attribute__((unused)) static void __closure_env", 49});
    writeU64_n_U64(id);
    plew_write((PlewString){"_release(void* __p) {\n    __closure_env", 39});
    writeU64_n_U64(id);
    plew_write((PlewString){"* e = (__closure_env", 20});
    writeU64_n_U64(id);
    plew_write((PlewString){"*)__p; (void)e;\n", 16});
    uint64_t j = 0;
    while (j < (long long)(((*c).captures).len)) {
    CaptureEntry e = PlewArray_CaptureEntry_get((*c).captures, (long long)(j));
    if (e.closureId == id) {
    if (e.boxed) {
    plew_write((PlewString){"    plew_arc_release(((long long*)e->", 37});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){") - 1);\n", 8});
    }
    else {
    if (e.isArray) {
    plew_write((PlewString){"    PlewArray_", 14});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen);
    plew_write((PlewString){"_release(e->", 12});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){");\n", 3});
    }
    else {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), e.tyStart, e.tyLen, (PlewString){"Ref", 3})) {
    plew_write((PlewString){"    plew_arc_release(((long long*)e->", 37});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){") - 1);\n", 8});
    }
    else {
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen)) {
    plew_write((PlewString){"    ", 4});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen);
    plew_write((PlewString){"_release(e->", 12});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){");\n", 3});
    }
    }
    }
    }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"}\n", 2});
}
void emitClosureEnvs_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).exprs).len)) {
    {
    Expr _m751 = PlewArray_Expr_get((*c).exprs, (long long)(i));
    if (_m751.tag == 17) {
        PlewArray_Param params = _m751.data.Closure.params;
        (void)params;
        long long hasRet = _m751.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m751.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m751.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m751.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m751.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m751.data.Closure.body;
        (void)body;
    if (closureHasCaptures_c_Comp_id_U64(&((*c)), i)) {
    emitClosureEnvStruct_c_Comp_id_U64(&((*c)), i);
    emitClosureEnvDrop_c_Comp_id_U64(&((*c)), i);
    }
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void emitClosures_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t i = 0;
    while (i < (long long)(((*c).exprs).len)) {
    {
    Expr _m752 = PlewArray_Expr_get((*c).exprs, (long long)(i));
    if (_m752.tag == 17) {
        PlewArray_Param params = _m752.data.Closure.params;
        (void)params;
        long long hasRet = _m752.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m752.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m752.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m752.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m752.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m752.data.Closure.body;
        (void)body;
    genClosure_c_Comp_id_U64_proto_Bool(&((*c)), i, proto);
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void genEnumDef_c_Comp_ei_U64(Comp* c, uint64_t ei) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    plew_write((PlewString){"struct ", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
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
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.ty, f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";", 1});
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" ", 1});
    }
    plew_write((PlewString){"} ", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), v.nameStart, v.nameLen);
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
uint64_t genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).len)) {
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(i)));
    if ((long long)((s.typeParams).len) > 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, nameStart, nameLen)) {
    { uint64_t __ret753 = i;
    StructDef_release(s);
    return __ret753; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { uint64_t __ret754 = (long long)(((*c).structs).len);
    return __ret754; }
}
uint64_t genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).enums).len)) {
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(i)));
    if ((long long)((e.typeParams).len) > 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, nameStart, nameLen)) {
    { uint64_t __ret755 = i;
    EnumDef_release(e);
    return __ret755; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret756 = (long long)(((*c).enums).len);
    return __ret756; }
}
long long isGenericInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret757 = 0;
    return __ret757; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) == 0) {
    { long long __ret758 = 0;
    TypeRef_release(t);
    return __ret758; }
    }
    if (genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).structs).len)) {
    { long long __ret759 = 1;
    TypeRef_release(t);
    return __ret759; }
    }
    { long long __ret760 = (genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).len));
    TypeRef_release(t);
    return __ret760; }
    TypeRef_release(t);
}
long long isFnType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret761 = 0;
    return __ret761; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    { long long __ret762 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"fn", 2});
    TypeRef_release(t);
    return __ret762; }
    TypeRef_release(t);
}
long long isRefInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret763 = 0;
    return __ret763; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) != 1) {
    { long long __ret764 = 0;
    TypeRef_release(t);
    return __ret764; }
    }
    { long long __ret765 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Ref", 3});
    TypeRef_release(t);
    return __ret765; }
    TypeRef_release(t);
}
long long isGenericEnumInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret766 = 0;
    return __ret766; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) == 0) {
    { long long __ret767 = 0;
    TypeRef_release(t);
    return __ret767; }
    }
    { long long __ret768 = (genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).len));
    TypeRef_release(t);
    return __ret768; }
    TypeRef_release(t);
}
long long typeRefEq_c_Comp_a_U64_b_U64(Comp* c, uint64_t a, uint64_t b) {
    if (a == b) {
    { long long __ret769 = 1;
    return __ret769; }
    }
    TypeRef ta = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(a)));
    TypeRef tb = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(b)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ta.nameStart, ta.nameLen, tb.nameStart, tb.nameLen)) {
    }
    else {
    { long long __ret770 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret770; }
    }
    if ((long long)((ta.args).len) != (long long)((tb.args).len)) {
    { long long __ret771 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret771; }
    }
    uint64_t i = 0;
    while (i < (long long)((ta.args).len)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), PlewArray_U64_get(ta.args, (long long)(i)), PlewArray_U64_get(tb.args, (long long)(i)))) {
    }
    else {
    { long long __ret772 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret772; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret773 = 1;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret773; }
    TypeRef_release(tb);
    TypeRef_release(ta);
}
void emitMangle_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(resolveTy_c_Comp_tyRef_U64(&((*c)), ref))));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), t.nameStart, t.nameLen);
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    plew_write((PlewString){"_", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(t);
}
void appendMangle_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(resolveTy_c_Comp_tyRef_U64(&((*c)), ref))));
    uint64_t j = 0;
    while (j < t.nameLen) {
    PlewArray_U8_push(&((*c).bytes), PlewArray_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((t.nameStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    PlewArray_U8_push(&((*c).bytes), 95);
    appendMangle_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(t);
}
Bind appendMangleSpan_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    uint64_t start = (long long)(((*c).bytes).len);
    appendMangle_c_Comp_ref_U64(&((*c)), ref);
    uint64_t n = (long long)(((*c).bytes).len);
    { Bind __ret774 = (Bind){.nameStart = start, .nameLen = ({ uint64_t __ov; if (__builtin_sub_overflow((n), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), .fieldStart = ref, .fieldLen = 0};
    return __ret774; }
}
long long isCompoundType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    uint64_t r = resolveTy_c_Comp_tyRef_U64(&((*c)), ref);
    if (r >= (long long)(((*c).types).len)) {
    { long long __ret775 = 0;
    return __ret775; }
    }
    { long long __ret776 = ((long long)((PlewArray_TypeRef_get((*c).types, (long long)(r)).args).len) > 0);
    return __ret776; }
}
void emitConcreteCType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    uint64_t r = resolveTy_c_Comp_tyRef_U64(&((*c)), ref);
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(r)));
    if ((long long)((t.args).len) == 0) {
    genCElem_c_Comp_start_U64_len_U64(&((*c)), t.nameStart, t.nameLen);
    TypeRef_release(t);
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    plew_write((PlewString){"PlewArray_", 10});
    emitMangle_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    TypeRef_release(t);
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Ref", 3})) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    plew_write((PlewString){"*", 1});
    TypeRef_release(t);
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"fn", 2})) {
    plew_write((PlewString){"PlewClosure", 11});
    TypeRef_release(t);
    return;
    }
    emitMangle_c_Comp_ref_U64(&((*c)), r);
    TypeRef_release(t);
}
void emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(Comp* c, uint64_t ref, PlewArray_Bind params, PlewArray_U64 args) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    uint64_t pi = 0;
    while (pi < (long long)((params).len)) {
    Bind p = PlewArray_Bind_get(params, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(args, (long long)(pi)));
    TypeRef_release(t);
    return;
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    emitConcreteCType_c_Comp_ref_U64(&((*c)), ref);
    TypeRef_release(t);
}
uint64_t resolveTy_c_Comp_tyRef_U64(Comp* c, uint64_t tyRef) {
    if (tyRef >= (long long)(((*c).types).len)) {
    { uint64_t __ret777 = tyRef;
    return __ret777; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(tyRef)));
    if ((long long)((t.args).len) == 0) {
    uint64_t i = 0;
    while (i < (long long)(((*c).curTypeParams).len)) {
    Bind p = PlewArray_Bind_get((*c).curTypeParams, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    { uint64_t __ret778 = PlewArray_U64_get((*c).curTypeArgs, (long long)(i));
    TypeRef_release(t);
    return __ret778; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    { uint64_t __ret779 = tyRef;
    TypeRef_release(t);
    return __ret779; }
    TypeRef_release(t);
}
void genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(Comp* c, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray) {
    if (isArray) {
    genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), fallStart, fallLen, 1);
    return;
    }
    uint64_t rt = resolveTy_c_Comp_tyRef_U64(&((*c)), tyRef);
    if (rt != tyRef) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), rt);
    return;
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), tyRef)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), tyRef);
    return;
    }
    if (isRefInst_c_Comp_ref_U64(&((*c)), tyRef)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), tyRef);
    return;
    }
    if (isFnType_c_Comp_ref_U64(&((*c)), tyRef)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), tyRef);
    return;
    }
    genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), fallStart, fallLen, 0);
}
long long isTypeParamName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).len)) {
    PlewArray_Bind tp = PlewArray_Bind_share(PlewArray_StructDef_get((*c).structs, (long long)(si)).typeParams);
    uint64_t k = 0;
    while (k < (long long)((tp).len)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), PlewArray_Bind_get(tp, (long long)(k)).nameStart, PlewArray_Bind_get(tp, (long long)(k)).nameLen, start, len)) {
    { long long __ret780 = 1;
    PlewArray_Bind_release(tp);
    return __ret780; }
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
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), PlewArray_Bind_get(tp2, (long long)(k2)).nameStart, PlewArray_Bind_get(tp2, (long long)(k2)).nameLen, start, len)) {
    { long long __ret781 = 1;
    PlewArray_Bind_release(tp2);
    return __ret781; }
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
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), PlewArray_Bind_get(tp3, (long long)(k3)).nameStart, PlewArray_Bind_get(tp3, (long long)(k3)).nameLen, start, len)) {
    { long long __ret782 = 1;
    PlewArray_Bind_release(tp3);
    return __ret782; }
    }
    k3 = ({ uint64_t __ov; if (__builtin_add_overflow((k3), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PlewArray_Bind_release(tp3);
    }
    { long long __ret783 = 0;
    return __ret783; }
}
long long tyRefIsGround_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    { long long __ret784 = 1;
    return __ret784; }
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if (isTypeParamName_c_Comp_start_U64_len_U64(&((*c)), t.nameStart, t.nameLen)) {
    { long long __ret785 = 0;
    TypeRef_release(t);
    return __ret785; }
    }
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    if (tyRefIsGround_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(i)))) {
    }
    else {
    { long long __ret786 = 0;
    TypeRef_release(t);
    return __ret786; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret787 = 1;
    TypeRef_release(t);
    return __ret787; }
    TypeRef_release(t);
}
void ensureArrayElemDeps_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef) {
    if (elemRef == 0) {
    return;
    }
    uint64_t r = resolveTy_c_Comp_tyRef_U64(&((*c)), elemRef);
    if (r >= (long long)(((*c).types).len)) {
    return;
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(r)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((t.args).len) > 0) {
    registerArrayElemRef_c_Comp_elemRef_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    }
    }
    TypeRef_release(t);
}
void registerArrayElemRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef) {
    if (elemRef >= (long long)(((*c).types).len)) {
    return;
    }
    ensureArrayElemDeps_c_Comp_elemRef_U64(&((*c)), elemRef);
    uint64_t nStart = PlewArray_TypeRef_get((*c).types, (long long)(elemRef)).nameStart;
    uint64_t nLen = PlewArray_TypeRef_get((*c).types, (long long)(elemRef)).nameLen;
    uint64_t fRef = 0;
    if (isCompoundType_c_Comp_ref_U64(&((*c)), elemRef)) {
    Bind mn = appendMangleSpan_c_Comp_ref_U64(&((*c)), elemRef);
    nStart = mn.nameStart;
    nLen = mn.nameLen;
    fRef = elemRef;
    }
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).len)) {
    Bind ae = PlewArray_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ae.nameStart, ae.nameLen, nStart, nLen)) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_Bind_push(&((*c).arrayElems), (Bind){.nameStart = nStart, .nameLen = nLen, .fieldStart = fRef, .fieldLen = 0});
}
void scanType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).len)) {
    return;
    }
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    uint64_t i = 0;
    while (i < (long long)((t.args).len)) {
    scanType_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((t.args).len) == 1) {
    registerArrayElemRef_c_Comp_elemRef_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(0)));
    }
    }
    if (isFnType_c_Comp_ref_U64(&((*c)), ref)) {
    uint64_t fj = 0;
    long long seen = 0;
    while (fj < (long long)(((*c).fnTypes).len)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), PlewArray_U64_get((*c).fnTypes, (long long)(fj)), ref)) {
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
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ref)) {
    if (tyRefIsGround_c_Comp_ref_U64(&((*c)), ref)) {
    uint64_t j = 0;
    while (j < (long long)(((*c).genInsts).len)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), PlewArray_U64_get((*c).genInsts, (long long)(j)), ref)) {
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
void collectGenInsts_c_Comp(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if ((long long)((f.typeParams).len) > 0) {
    }
    else {
    if (f.hasRet) {
    scanType_c_Comp_ref_U64(&((*c)), f.retTy);
    }
    PlewArray_Param ps = PlewArray_Param_share(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((ps).len)) {
    scanType_c_Comp_ref_U64(&((*c)), PlewArray_Param_get(ps, (long long)(pi)).ty);
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
    scanType_c_Comp_ref_U64(&((*c)), PlewArray_FieldDef_get(fs, (long long)(k)).ty);
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
    scanType_c_Comp_ref_U64(&((*c)), PlewArray_FieldDef_get(vfs, (long long)(k)).ty);
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
    Stmt _m788 = PlewArray_Stmt_get((*c).stmts, (long long)(sti));
    if (_m788.tag == 0) {
        uint64_t ty = _m788.data.Let.ty;
        (void)ty;
    scanType_c_Comp_ref_U64(&((*c)), ty);
    }
    else {
    }
    }
    sti = ({ uint64_t __ov; if (__builtin_add_overflow((sti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t xi = 0;
    while (xi < (long long)(((*c).exprs).len)) {
    {
    Expr _m789 = PlewArray_Expr_get((*c).exprs, (long long)(xi));
    if (_m789.tag == 11) {
        uint64_t operand = _m789.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m789.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m789.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m789.data.Cast.ty;
        (void)ty;
    scanType_c_Comp_ref_U64(&((*c)), ty);
    }
    else if (_m789.tag == 6) {
        uint64_t typeStart = _m789.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m789.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m789.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m789.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m789.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m789.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m789.data.Make.fields;
        (void)fields;
    scanType_c_Comp_ref_U64(&((*c)), ty);
    }
    else {
    }
    }
    xi = ({ uint64_t __ov; if (__builtin_add_overflow((xi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
TypeInfo typeInfoOfRef_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).len) == 0) {
    { TypeInfo __ret790 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), t.nameStart, t.nameLen, 0);
    TypeRef_release(t);
    return __ret790; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    TypeRef el = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(PlewArray_U64_get(t.args, (long long)(0)))));
    { TypeInfo __ret791 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), el.nameStart, el.nameLen, 1);
    TypeRef_release(el);
    TypeRef_release(t);
    return __ret791; }
    TypeRef_release(el);
    }
    { TypeInfo __ret792 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), t.nameStart, t.nameLen, 0);
    TypeRef_release(t);
    return __ret792; }
    TypeRef_release(t);
}
TypeInfo substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(Comp* c, uint64_t instRef, PlewArray_Bind params, uint64_t tyRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(tyRef)));
    uint64_t i = 0;
    while (i < (long long)((params).len)) {
    Bind p = PlewArray_Bind_get(params, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    if (i < (long long)((inst.args).len)) {
    { TypeInfo __ret793 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(inst.args, (long long)(i)));
    TypeRef_release(inst);
    TypeRef_release(t);
    return __ret793; }
    }
    TypeRef_release(inst);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret794 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), tyRef);
    TypeRef_release(t);
    return __ret794; }
    TypeRef_release(t);
}
TypeInfo genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    { TypeInfo __ret795 = scalarInfo();
    TypeRef_release(t);
    return __ret795; }
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fields, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(fd.ty)));
    uint64_t pi = 0;
    while (pi < (long long)((s.typeParams).len)) {
    Bind p = PlewArray_Bind_get(s.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    { TypeInfo __ret796 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(pi)));
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret796; }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret797 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), fd.ty);
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret797; }
    TypeRef_release(ftr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret798 = scalarInfo();
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret798; }
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
TypeInfo genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    { TypeInfo __ret799 = scalarInfo();
    TypeRef_release(t);
    return __ret799; }
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    PlewArray_Variant vars = PlewArray_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).len)) {
    Variant v = Variant_share(PlewArray_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    PlewArray_FieldDef fs = PlewArray_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).len)) {
    FieldDef fd = PlewArray_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(fd.ty)));
    uint64_t pi = 0;
    while (pi < (long long)((e.typeParams).len)) {
    Bind p = PlewArray_Bind_get(e.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    { TypeInfo __ret800 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(t.args, (long long)(pi)));
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret800; }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret801 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), fd.ty);
    TypeRef_release(ftr);
    PlewArray_FieldDef_release(fs);
    Variant_release(v);
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret801; }
    TypeRef_release(ftr);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { TypeInfo __ret802 = scalarInfo();
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret802; }
    PlewArray_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
void genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen) {
    TypeInfo ti = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), instRef, variantStart, variantLen, bindStart, bindLen);
    genTypeInfoCType_c_Comp_ti_TypeInfo(&((*c)), ti);
}
void emitMonoForward_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    plew_write((PlewString){"typedef struct ", 15});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){";\n", 2});
}
void emitMonoStruct_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).len)) {
    TypeRef_release(t);
    return;
    }
    StructDef s = StructDef_share(PlewArray_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"struct ", 7});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" {\n", 3});
    PlewArray_FieldDef fields = PlewArray_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    FieldDef f = PlewArray_FieldDef_get(fields, (long long)(i));
    plew_write((PlewString){"    ", 4});
    emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(&((*c)), f.ty, PlewArray_Bind_share(s.typeParams), PlewArray_U64_share(t.args));
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";\n", 2});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"};\n", 3});
    PlewArray_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
void emitMonoEnum_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).len)) {
    TypeRef_release(t);
    return;
    }
    EnumDef e = EnumDef_share(PlewArray_EnumDef_get((*c).enums, (long long)(ei)));
    plew_write((PlewString){"struct ", 7});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
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
    emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(&((*c)), f.ty, PlewArray_Bind_share(e.typeParams), PlewArray_U64_share(t.args));
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";", 1});
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" ", 1});
    }
    plew_write((PlewString){"} ", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), v.nameStart, v.nameLen);
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
long long methodMatchesInst_c_Comp_f_Func_instRef_U64(Comp* c, Func f, uint64_t instRef) {
    if (f.hasRecv) {
    }
    else {
    { long long __ret803 = 0;
    return __ret803; }
    }
    if ((long long)((f.typeParams).len) == 0) {
    { long long __ret804 = 0;
    return __ret804; }
    }
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, inst.nameStart, inst.nameLen)) {
    }
    else {
    { long long __ret805 = 0;
    TypeRef_release(inst);
    return __ret805; }
    }
    { long long __ret806 = ((long long)((f.typeParams).len) == (long long)((inst.args).len));
    TypeRef_release(inst);
    return __ret806; }
    TypeRef_release(inst);
}
void emitMonoMethod_c_Comp_fi_U64_instRef_U64_proto_Bool(Comp* c, uint64_t fi, uint64_t instRef, long long proto) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    TypeRef inst = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(instRef)));
    (*c).curRecvInstRef = instRef;
    (*c).curTypeParams = PlewArray_Bind_share(f.typeParams);
    (*c).curTypeArgs = PlewArray_U64_share(inst.args);
    if (proto) {
    genSignature_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){";\n", 2});
    }
    else {
    genFunc_c_Comp_fi_U64(&((*c)), fi);
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
void emitMonoMethods_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t gi = 0;
    while (gi < (long long)(((*c).genInsts).len)) {
    uint64_t mfi = 0;
    while (mfi < (long long)(((*c).funcs).len)) {
    if (methodMatchesInst_c_Comp_f_Func_instRef_U64(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(mfi)), PlewArray_U64_get((*c).genInsts, (long long)(gi)))) {
    emitMonoMethod_c_Comp_fi_U64_instRef_U64_proto_Bool(&((*c)), mfi, PlewArray_U64_get((*c).genInsts, (long long)(gi)), proto);
    }
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long isGenericFreeFn_c_Comp_fi_U64(Comp* c, uint64_t fi) {
    if (fi >= (long long)(((*c).funcs).len)) {
    { long long __ret807 = 0;
    return __ret807; }
    }
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRecv) {
    { long long __ret808 = 0;
    Func_release(f);
    return __ret808; }
    }
    { long long __ret809 = ((long long)((f.typeParams).len) > 0);
    Func_release(f);
    return __ret809; }
    Func_release(f);
}
uint64_t findOrAddTypeRef_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).types).len)) {
    TypeRef t = TypeRef_share(PlewArray_TypeRef_get((*c).types, (long long)(i)));
    if ((long long)((t.args).len) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, nameStart, nameLen)) {
    { uint64_t __ret810 = i;
    TypeRef_release(t);
    return __ret810; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeRef_release(t);
    }
    PlewArray_U64 noArgs = PlewArray_U64_new();
    { uint64_t __ret811 = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = nameStart, .nameLen = nameLen, .args = PlewArray_U64_share(noArgs)});
    PlewArray_U64_release(noArgs);
    return __ret811; }
    PlewArray_U64_release(noArgs);
}
uint64_t tyRefOfInfo_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.ref != 0) {
    { uint64_t __ret812 = ti.ref;
    return __ret812; }
    }
    if (ti.nameLen == 0) {
    { uint64_t __ret813 = 0;
    return __ret813; }
    }
    if (ti.kind == 3) {
    { uint64_t __ret814 = 0;
    return __ret814; }
    }
    { uint64_t __ret815 = findOrAddTypeRef_c_Comp_nameStart_U64_nameLen_U64(&((*c)), ti.nameStart, ti.nameLen);
    return __ret815; }
}
PlewArray_U64 inferFnArgs_c_Comp_f_Func_args_AArg(Comp* c, Func f, PlewArray_Arg args) {
    PlewArray_U64 out = PlewArray_U64_new();
    uint64_t ti = 0;
    while (ti < (long long)((f.typeParams).len)) {
    Bind tp = PlewArray_Bind_get(f.typeParams, (long long)(ti));
    uint64_t found = 0;
    uint64_t pi = 0;
    while (pi < (long long)((f.params).len)) {
    Param p = PlewArray_Param_get(f.params, (long long)(pi));
    if (p.tyIsArray) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.tyStart, p.tyLen, tp.nameStart, tp.nameLen)) {
    if (pi < (long long)((args).len)) {
    TypeInfo at = exprType_c_Comp_id_U64(&((*c)), PlewArray_Arg_get(args, (long long)(pi)).expr);
    found = tyRefOfInfo_c_Comp_ti_TypeInfo(&((*c)), at);
    }
    }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U64_push(&(out), found);
    ti = ({ uint64_t __ov; if (__builtin_add_overflow((ti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { PlewArray_U64 __ret816 = PlewArray_U64_share(out);
    PlewArray_U64_release(out);
    return __ret816; }
    PlewArray_U64_release(out);
}
long long fnArgsAllGround_c_Comp_args_AU64(Comp* c, PlewArray_U64 args) {
    if ((long long)((args).len) == 0) {
    { long long __ret817 = 0;
    return __ret817; }
    }
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    if (PlewArray_U64_get(args, (long long)(i)) == 0) {
    { long long __ret818 = 0;
    return __ret818; }
    }
    if (tyRefIsGround_c_Comp_ref_U64(&((*c)), PlewArray_U64_get(args, (long long)(i)))) {
    }
    else {
    { long long __ret819 = 0;
    return __ret819; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret820 = 1;
    return __ret820; }
}
long long fnInstExists_c_Comp_fnIdx_U64_args_AU64(Comp* c, uint64_t fnIdx, PlewArray_U64 args) {
    uint64_t i = 0;
    while (i < (long long)(((*c).fnInsts).len)) {
    FnInst fin = FnInst_share(PlewArray_FnInst_get((*c).fnInsts, (long long)(i)));
    if (fin.fnIdx == fnIdx) {
    if ((long long)((fin.args).len) == (long long)((args).len)) {
    long long same = 1;
    uint64_t j = 0;
    while (j < (long long)((args).len)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), PlewArray_U64_get(fin.args, (long long)(j)), PlewArray_U64_get(args, (long long)(j)))) {
    }
    else {
    same = 0;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (same) {
    { long long __ret821 = 1;
    FnInst_release(fin);
    return __ret821; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    FnInst_release(fin);
    }
    { long long __ret822 = 0;
    return __ret822; }
}
void registerCallInst_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, PlewArray_Arg args) {
    uint64_t fi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args));
    if (fi < (long long)(((*c).funcs).len)) {
    if (isGenericFreeFn_c_Comp_fi_U64(&((*c)), fi)) {
    PlewArray_U64 inferred = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), PlewArray_Func_get((*c).funcs, (long long)(fi)), PlewArray_Arg_share(args));
    if (fnArgsAllGround_c_Comp_args_AU64(&((*c)), PlewArray_U64_share(inferred))) {
    if (fnInstExists_c_Comp_fnIdx_U64_args_AU64(&((*c)), fi, PlewArray_U64_share(inferred))) {
    }
    else {
    PlewArray_FnInst_push(&((*c).fnInsts), (FnInst){.fnIdx = fi, .args = PlewArray_U64_share(inferred)});
    }
    }
    PlewArray_U64_release(inferred);
    }
    }
}
long long captureSupported_c_Comp_lo_Local(Comp* c, Local lo) {
    if (lo.isArray) {
    { long long __ret823 = 1;
    return __ret823; }
    }
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen)) {
    { long long __ret824 = 1;
    return __ret824; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), lo.tyStart, lo.tyLen, (PlewString){"String", 6})) {
    { long long __ret825 = 1;
    return __ret825; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), lo.tyStart, lo.tyLen, (PlewString){"Ref", 3})) {
    { long long __ret826 = 1;
    return __ret826; }
    }
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen);
    if (si < (long long)(((*c).structs).len)) {
    if (PlewArray_StructDef_get((*c).structs, (long long)(si)).isUnique) {
    { long long __ret827 = 0;
    return __ret827; }
    }
    if ((long long)((PlewArray_StructDef_get((*c).structs, (long long)(si)).typeParams).len) > 0) {
    { long long __ret828 = 0;
    return __ret828; }
    }
    { long long __ret829 = 1;
    return __ret829; }
    }
    { long long __ret830 = 0;
    return __ret830; }
}
void recordCapture_c_Comp_closureId_U64_localIdx_U64(Comp* c, uint64_t closureId, uint64_t localIdx) {
    Local lo = PlewArray_Local_get((*c).locals, (long long)(localIdx));
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).len)) {
    CaptureEntry e = PlewArray_CaptureEntry_get((*c).captures, (long long)(i));
    if (e.closureId == closureId) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, lo.nameStart, lo.nameLen)) {
    return;
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    long long boxed = 0;
    if (lo.isMut) {
    if (lo.isArray) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), lo.nameStart), (PlewString){"capturing a mutable non-scalar value (`mut val` array/struct/string) in a closure is not yet supported", 102});
    }
    else {
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen)) {
    boxed = 1;
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), lo.nameStart), (PlewString){"capturing a mutable non-scalar value (`mut val` array/struct/string) in a closure is not yet supported", 102});
    }
    }
    }
    else {
    if (captureSupported_c_Comp_lo_Local(&((*c)), lo)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), lo.nameStart), (PlewString){"capturing this value (unique / generic / enum / function) in a closure is not yet supported", 91});
    }
    }
    PlewArray_CaptureEntry_push(&((*c).captures), (CaptureEntry){.closureId = closureId, .nameStart = lo.nameStart, .nameLen = lo.nameLen, .tyStart = lo.tyStart, .tyLen = lo.tyLen, .isArray = lo.isArray, .ty = lo.ty, .boxed = boxed});
}
void scanExprInsts_c_Comp_exprId_U64(Comp* c, uint64_t exprId) {
    {
    Expr _m831 = PlewArray_Expr_get((*c).exprs, (long long)(exprId));
    if (_m831.tag == 1) {
        uint64_t start = _m831.data.Ident.start;
        (void)start;
        uint64_t len = _m831.data.Ident.len;
        (void)len;
    if ((*c).curInClosure) {
    uint64_t li = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (li < (*c).curCaptureMark) {
    recordCapture_c_Comp_closureId_U64_localIdx_U64(&((*c)), (*c).curClosureId, li);
    }
    }
    }
    else if (_m831.tag == 17) {
        PlewArray_Param params = _m831.data.Closure.params;
        (void)params;
        long long hasRet = _m831.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m831.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m831.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m831.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m831.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m831.data.Closure.body;
        (void)body;
    if ((*c).curInClosure) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), exprId)), (PlewString){"nested closures are not yet supported", 37});
    }
    uint64_t savedId = (*c).curClosureId;
    long long savedIn = (*c).curInClosure;
    uint64_t savedMark = (*c).curCaptureMark;
    uint64_t enclMark = scopeMark_c_Comp(&((*c)));
    (*c).curClosureId = exprId;
    (*c).curInClosure = 1;
    (*c).curCaptureMark = enclMark;
    uint64_t pi = 0;
    while (pi < (long long)((params).len)) {
    Param p = PlewArray_Param_get(params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), body);
    popLocals_c_Comp_mark_U64(&((*c)), enclMark);
    (*c).curClosureId = savedId;
    (*c).curInClosure = savedIn;
    (*c).curCaptureMark = savedMark;
    }
    else if (_m831.tag == 2) {
        int64_t op = _m831.data.Unary.op;
        (void)op;
        uint64_t operand = _m831.data.Unary.operand;
        (void)operand;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m831.tag == 3) {
        int64_t op = _m831.data.Binary.op;
        (void)op;
        uint64_t lhs = _m831.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m831.data.Binary.rhs;
        (void)rhs;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), lhs);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), rhs);
    }
    else if (_m831.tag == 4) {
        uint64_t nameStart = _m831.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m831.data.Call.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m831.data.Call.args;
        (void)args;
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    registerCallInst_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, PlewArray_Arg_share(args));
    }
    else if (_m831.tag == 10) {
        uint64_t recv = _m831.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m831.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m831.data.Method.nameLen;
        (void)nameLen;
        PlewArray_Arg args = _m831.data.Method.args;
        (void)args;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), recv);
    uint64_t i = 0;
    while (i < (long long)((args).len)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), PlewArray_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m831.tag == 5) {
        uint64_t base = _m831.data.Field.base;
        (void)base;
        uint64_t nameStart = _m831.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m831.data.Field.nameLen;
        (void)nameLen;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m831.tag == 9) {
        uint64_t base = _m831.data.Index.base;
        (void)base;
        uint64_t index = _m831.data.Index.index;
        (void)index;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), base);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), index);
    }
    else if (_m831.tag == 6) {
        uint64_t typeStart = _m831.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m831.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m831.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m831.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m831.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m831.data.Make.ty;
        (void)ty;
        PlewArray_MakeField fields = _m831.data.Make.fields;
        (void)fields;
    uint64_t i = 0;
    while (i < (long long)((fields).len)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), PlewArray_MakeField_get(fields, (long long)(i)).value);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m831.tag == 8) {
        PlewArray_U64 elems = _m831.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).len)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), PlewArray_U64_get(elems, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m831.tag == 11) {
        uint64_t operand = _m831.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m831.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m831.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m831.data.Cast.ty;
        (void)ty;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m831.tag == 14) {
        uint64_t opt = _m831.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m831.data.Coalesce.deflt;
        (void)deflt;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), opt);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), deflt);
    }
    else if (_m831.tag == 15) {
        uint64_t expr = _m831.data.Try.expr;
        (void)expr;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m831.tag == 16) {
        uint64_t base = _m831.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m831.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m831.data.Arrow.nameLen;
        (void)nameLen;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m831.tag == 13) {
        uint64_t cond = _m831.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m831.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m831.data.IfExpr.elseBlk;
        (void)elseBlk;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), cond);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), thenBlk);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    else if (_m831.tag == 12) {
        uint64_t scrut = _m831.data.MatchExpr.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m831.data.MatchExpr.arms;
        (void)arms;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm(&((*c)), a);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m831.tag == 18) {
        uint64_t operand = _m831.data.Move.operand;
        (void)operand;
        long long isBorrow = _m831.data.Move.isBorrow;
        (void)isBorrow;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), operand);
    }
    else {
    }
    }
}
void scanAddArmBinds_c_Comp_a_MatchArm(Comp* c, MatchArm a) {
    uint64_t bi = 0;
    while (bi < (long long)((a.binds).len)) {
    Bind bd = PlewArray_Bind_get(a.binds, (long long)(bi));
    addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen);
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void scanStmtInsts_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId) {
    {
    Stmt _m832 = PlewArray_Stmt_get((*c).stmts, (long long)(stmtId));
    if (_m832.tag == 0) {
        long long mutable = _m832.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m832.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m832.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m832.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m832.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m832.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m832.data.Let.ty;
        (void)ty;
        uint64_t init = _m832.data.Let.init;
        (void)init;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), init);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), nameStart, nameLen, tyStart, tyLen, tyIsArray, ty, 0, mutable, 1);
    }
    else if (_m832.tag == 1) {
        int64_t op = _m832.data.Assign.op;
        (void)op;
        uint64_t target = _m832.data.Assign.target;
        (void)target;
        uint64_t value = _m832.data.Assign.value;
        (void)value;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), target);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m832.tag == 2) {
        uint64_t expr = _m832.data.Print.expr;
        (void)expr;
        uint64_t offset = _m832.data.Print.offset;
        (void)offset;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m832.tag == 3) {
        uint64_t expr = _m832.data.ExprStmt.expr;
        (void)expr;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m832.tag == 4) {
        uint64_t value = _m832.data.Return.value;
        (void)value;
        long long hasValue = _m832.data.Return.hasValue;
        (void)hasValue;
    if (hasValue) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), value);
    }
    }
    else if (_m832.tag == 5) {
        uint64_t cond = _m832.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m832.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m832.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m832.data.If.hasElse;
        (void)hasElse;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), cond);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), thenBlk);
    if (hasElse) {
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    }
    else if (_m832.tag == 6) {
        uint64_t cond = _m832.data.While.cond;
        (void)cond;
        uint64_t body = _m832.data.While.body;
        (void)body;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), cond);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), body);
    }
    else if (_m832.tag == 7) {
        uint64_t varStart = _m832.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m832.data.For.varLen;
        (void)varLen;
        long long isRange = _m832.data.For.isRange;
        (void)isRange;
        long long inclusive = _m832.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m832.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m832.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m832.data.For.body;
        (void)body;
    uint64_t forMark = scopeMark_c_Comp(&((*c)));
    scanExprInsts_c_Comp_exprId_U64(&((*c)), iter);
    if (isRange) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), rangeHi);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, 0, 0, 0, 0, 0, 0, 0);
    }
    else {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), iter);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0, 0, 0, 0);
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), body);
    popLocals_c_Comp_mark_U64(&((*c)), forMark);
    }
    else if (_m832.tag == 8) {
        uint64_t scrut = _m832.data.Match.scrut;
        (void)scrut;
        PlewArray_MatchArm arms = _m832.data.Match.arms;
        (void)arms;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).len)) {
    MatchArm a = MatchArm_share(PlewArray_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm(&((*c)), a);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m832.tag == 9) {
        uint64_t msg = _m832.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m832.data.Panic.offset;
        (void)offset;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), msg);
    }
    else if (_m832.tag == 10) {
        uint64_t value = _m832.data.Give.value;
        (void)value;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m832.tag == 11) {
    }
    else if (_m832.tag == 12) {
    }
    else { __builtin_unreachable(); }
    }
}
void scanBlockInsts_c_Comp_blkId_U64(Comp* c, uint64_t blkId) {
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    PlewArray_U64 stmts = PlewArray_U64_share(PlewArray_Block_get((*c).blocks, (long long)(blkId)).stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).len)) {
    scanStmtInsts_c_Comp_stmtId_U64(&((*c)), PlewArray_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    PlewArray_U64_release(stmts);
}
void collectFnInsts_c_Comp(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).len)) {
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fi)));
    if ((long long)((f.typeParams).len) > 0) {
    }
    else {
    PlewArray_Bind noParams = PlewArray_Bind_new();
    PlewArray_U64 noArgs = PlewArray_U64_new();
    (*c).locals = PlewArray_Local_new();
    (*c).curHasRecv = f.hasRecv;
    (*c).curRecvStart = f.recvStart;
    (*c).curRecvLen = f.recvLen;
    (*c).curSelfInout = f.selfInout;
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = PlewArray_Bind_share(noParams);
    (*c).curTypeArgs = PlewArray_U64_share(noArgs);
    uint64_t pi = 0;
    while (pi < (long long)((f.params).len)) {
    Param p = PlewArray_Param_get(f.params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), f.body);
    PlewArray_U64_release(noArgs);
    PlewArray_Bind_release(noParams);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    uint64_t si = 0;
    while (si < (long long)(((*c).fnInsts).len)) {
    FnInst fin = FnInst_share(PlewArray_FnInst_get((*c).fnInsts, (long long)(si)));
    Func gf = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fin.fnIdx)));
    (*c).locals = PlewArray_Local_new();
    (*c).curHasRecv = 0;
    (*c).curRecvStart = 0;
    (*c).curRecvLen = 0;
    (*c).curSelfInout = 0;
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = PlewArray_Bind_share(gf.typeParams);
    (*c).curTypeArgs = PlewArray_U64_share(fin.args);
    uint64_t gpi = 0;
    while (gpi < (long long)((gf.params).len)) {
    Param gp = PlewArray_Param_get(gf.params, (long long)(gpi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), gp.nameStart, gp.nameLen, gp.tyStart, gp.tyLen, gp.tyIsArray, gp.ty, gp.isInout, 0, 0);
    gpi = ({ uint64_t __ov; if (__builtin_add_overflow((gpi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), gf.body);
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(gf);
    FnInst_release(fin);
    }
    PlewArray_Bind noP = PlewArray_Bind_new();
    PlewArray_U64 noA = PlewArray_U64_new();
    (*c).locals = PlewArray_Local_new();
    (*c).curHasRecv = 0;
    (*c).curTypeParams = PlewArray_Bind_share(noP);
    (*c).curTypeArgs = PlewArray_U64_share(noA);
    (*c).curInClosure = 0;
    (*c).curClosureId = 0;
    (*c).curCaptureMark = 0;
    PlewArray_U64_release(noA);
    PlewArray_Bind_release(noP);
}
void emitMonoFn_c_Comp_instIdx_U64_proto_Bool(Comp* c, uint64_t instIdx, long long proto) {
    FnInst fin = FnInst_share(PlewArray_FnInst_get((*c).fnInsts, (long long)(instIdx)));
    Func f = Func_share(PlewArray_Func_get((*c).funcs, (long long)(fin.fnIdx)));
    (*c).curTypeParams = PlewArray_Bind_share(f.typeParams);
    (*c).curTypeArgs = PlewArray_U64_share(fin.args);
    if (proto) {
    genSignature_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){";\n", 2});
    }
    else {
    genFunc_c_Comp_fi_U64(&((*c)), fin.fnIdx);
    }
    PlewArray_Bind noParams = PlewArray_Bind_new();
    PlewArray_U64 noArgs = PlewArray_U64_new();
    (*c).curTypeParams = PlewArray_Bind_share(noParams);
    (*c).curTypeArgs = PlewArray_U64_share(noArgs);
    PlewArray_U64_release(noArgs);
    PlewArray_Bind_release(noParams);
    Func_release(f);
    FnInst_release(fin);
}
void emitMonoFns_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t i = 0;
    while (i < (long long)(((*c).fnInsts).len)) {
    emitMonoFn_c_Comp_instIdx_U64_proto_Bool(&((*c)), i, proto);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void wPA_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"PlewArray_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
}
void genArrayTypedef_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"typedef struct { ", 17});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* data; long long len; long long cap; long long* rc; } ", 55});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){";\n", 2});
}
void genArrayRuntimeFns_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new(void) { ", 13});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a; a.data = 0; a.len = 0; a.cap = 0; a.rc = 0; return a; }\n", 60});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_get(", 5});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a, long long i) { if (i < 0 || i >= a.len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } return a.data[i]; }\n", 125});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { ", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" r; r.len = a.len; r.cap = a.len; if (a.len > 0) { r.data = (", 61});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){") * a.len); r.rc = ((long long*)r.data) - 1; for (long long i = 0; i < a.len; i++) ", 83});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"r.data[i] = ", 12});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(a.data[i]);", 17});
    }
    else {
    plew_write((PlewString){"r.data[i] = a.data[i];", 22});
    }
    plew_write((PlewString){" } else { r.data = 0; r.cap = 0; r.rc = 0; } return r; }\n", 57});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(", 9});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { if (!a.rc) return; if ((--(*a.rc)) != 0) return; ", 55});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"for (long long i = 0; i < a.len; i++) ", 38});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(a.data[i]); ", 21});
    }
    plew_write((PlewString){"free(a.rc); }\n", 14});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_share(", 7});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { plew_arc_retain(a.rc); return a; }\n", 41});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(", 8});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a) { if (a->rc && (*(a->rc)) > 1) { ", 38});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" nc = ", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(*a); plew_arc_release(a->rc); *a = nc; } }\n", 49});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_set(", 5});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, long long i, ", 18});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { if (i < 0 || i >= a->len) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } ", 93});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(a); ", 12});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(a->data[i]); a->data[i] = ", 35});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(v); }\n", 12});
    }
    else {
    plew_write((PlewString){"a->data[i] = v; }\n", 18});
    }
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, ", 5});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { ", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(a); if (a->len >= a->cap) { long long nc = a->cap < 4 ? 4 : a->cap * 2; ", 80});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* nd = (", 8});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){") * nc); for (long long i = 0; i < a->len; i++) nd[i] = a->data[i]; plew_arc_release(a->rc); a->data = nd; a->rc = ((long long*)nd) - 1; a->cap = nc; } a->data[a->len] = ", 170});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(v)", 8});
    }
    else {
    plew_write((PlewString){"v", 1});
    }
    plew_write((PlewString){"; a->len++; }\n", 14});
}
long long isU8Elem_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    { long long __ret833 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share((*c).bytes), elemStart, elemLen, (PlewString){"U8", 2});
    return __ret833; }
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
long long isPathTokKind_k_Kind(Kind k) {
    {
    Kind _m834 = k;
    if (_m834.tag == 37) {
    { long long __ret835 = 1;
    return __ret835; }
    }
    else if (_m834.tag == 48) {
    { long long __ret836 = 1;
    return __ret836; }
    }
    else if (_m834.tag == 5) {
    { long long __ret837 = 1;
    return __ret837; }
    }
    else {
    { long long __ret838 = 0;
    return __ret838; }
    }
    }
}
PlewArray_Bind collectParts_rootBytes_AU8_toks_ATok(PlewArray_U8 rootBytes, PlewArray_Tok toks) {
    PlewArray_Bind parts = PlewArray_Bind_new();
    uint64_t i = 0;
    while (i < (long long)((toks).len)) {
    Tok t = PlewArray_Tok_get(toks, (long long)(i));
    long long isKw = 0;
    {
    Kind _m839 = t.kind;
    if (_m839.tag == 5) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(rootBytes), t.start, t.len, (PlewString){"part", 4})) {
    isKw = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(PlewArray_U8_share(rootBytes), t.start, t.len, (PlewString){"import", 6})) {
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
    Kind _m840 = first.kind;
    if (_m840.tag == 37) {
    starts = 1;
    }
    else if (_m840.tag == 48) {
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
    if (isPathTokKind_k_Kind(nt.kind)) {
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
    { PlewArray_Bind __ret841 = PlewArray_Bind_share(parts);
    PlewArray_Bind_release(parts);
    return __ret841; }
    PlewArray_Bind_release(parts);
}
uint64_t stripParents_path_AU8_baseLen_U64_n_U64(PlewArray_U8 path, uint64_t baseLen, uint64_t n) {
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
    { uint64_t __ret842 = end;
    return __ret842; }
}
PlewArray_U8 resolveImport_src_AU8_pStart_U64_pLen_U64_importer_AU8_baseLen_U64_srcRoot_AU8_srcRootLen_U64_stdRoot_AU8_stdRootLen_U64(PlewArray_U8 src, uint64_t pStart, uint64_t pLen, PlewArray_U8 importer, uint64_t baseLen, PlewArray_U8 srcRoot, uint64_t srcRootLen, PlewArray_U8 stdRoot, uint64_t stdRootLen) {
    PlewArray_U8 out = PlewArray_U8_new();
    if (pLen == 0) {
    { PlewArray_U8 __ret843 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret843; }
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
    { PlewArray_U8 __ret844 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret844; }
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
    { PlewArray_U8 __ret845 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret845; }
    }
    }
    }
    }
    }
    { PlewArray_U8 __ret846 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret846; }
    }
    if (b0 == 47) {
    if (srcRootLen == 0) {
    { PlewArray_U8 __ret847 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret847; }
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
    { PlewArray_U8 __ret848 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret848; }
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
    uint64_t dirLen = stripParents_path_AU8_baseLen_U64_n_U64(PlewArray_U8_share(importer), baseLen, parents);
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
    { PlewArray_U8 __ret849 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret849; }
    PlewArray_U8_release(out);
}
void appendBytes_into_AU8_from_AU8(PlewArray_U8* into, PlewArray_U8 from) {
    uint64_t i = 0;
    while (i < (long long)((from).len)) {
    PlewArray_U8_push(&((*into)), PlewArray_U8_get(from, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
PlewArray_U8 extractSpan_buf_AU8_start_U64_len_U64(PlewArray_U8 buf, uint64_t start, uint64_t len) {
    PlewArray_U8 out = PlewArray_U8_new();
    uint64_t i = 0;
    while (i < len) {
    PlewArray_U8_push(&(out), PlewArray_U8_get(buf, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (i), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { PlewArray_U8 __ret850 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret850; }
    PlewArray_U8_release(out);
}
uint64_t dirPrefixLen_path_AU8(PlewArray_U8 path) {
    uint64_t pre = 0;
    uint64_t k = 0;
    while (k < (long long)((path).len)) {
    if (PlewArray_U8_get(path, (long long)(k)) == 47) {
    pre = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret851 = pre;
    return __ret851; }
}
PlewArray_U8 computeStdRoot_arg0_AU8(PlewArray_U8 arg0) {
    uint64_t pre = dirPrefixLen_path_AU8(PlewArray_U8_share(arg0));
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
    { PlewArray_U8 __ret852 = PlewArray_U8_share(out);
    PlewArray_U8_release(out);
    return __ret852; }
    PlewArray_U8_release(out);
}
PlewArray_U8 findSrcRoot_entry_AU8(PlewArray_U8 entry) {
    uint64_t dirLen = dirPrefixLen_path_AU8(PlewArray_U8_share(entry));
    long long go = 1;
    while (go) {
    PlewArray_U8 mani = PlewArray_U8_new();
    uint64_t i = 0;
    while (i < dirLen) {
    PlewArray_U8_push(&(mani), PlewArray_U8_get(entry, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8 mn = PlewArray_U8_share(({ PlewString __s = (PlewString){"Plew.toml", 9}; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    appendBytes_into_AU8_from_AU8(&(mani), PlewArray_U8_share(mn));
    if (plew_file_exists(mani)) {
    PlewArray_U8 sr = PlewArray_U8_new();
    uint64_t j = 0;
    while (j < dirLen) {
    PlewArray_U8_push(&(sr), PlewArray_U8_get(entry, (long long)(j)));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    PlewArray_U8 sx = PlewArray_U8_share(({ PlewString __s = (PlewString){"src/", 4}; (PlewArray_U8){(unsigned char*)__s.data, __s.len, __s.len, 0}; }));
    appendBytes_into_AU8_from_AU8(&(sr), PlewArray_U8_share(sx));
    { PlewArray_U8 __ret853 = PlewArray_U8_share(sr);
    PlewArray_U8_release(sx);
    PlewArray_U8_release(sr);
    PlewArray_U8_release(mn);
    PlewArray_U8_release(mani);
    return __ret853; }
    PlewArray_U8_release(sx);
    PlewArray_U8_release(sr);
    }
    if (dirLen == 0) {
    go = 0;
    }
    else {
    uint64_t nd = stripParents_path_AU8_baseLen_U64_n_U64(PlewArray_U8_share(entry), dirLen, 1);
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
    { PlewArray_U8 __ret854 = PlewArray_U8_share(empty);
    PlewArray_U8_release(empty);
    return __ret854; }
    PlewArray_U8_release(empty);
}
long long pathSeen_buf_AU8_loaded_ABind_path_AU8(PlewArray_U8 buf, PlewArray_Bind loaded, PlewArray_U8 path) {
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
    { long long __ret855 = 1;
    return __ret855; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret856 = 0;
    return __ret856; }
}
