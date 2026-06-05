#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
typedef struct { const char* data; long long len; } PlewString;
__attribute__((unused)) static void* plew_arc_alloc(long long bytes) { long long* p = (long long*)malloc(sizeof(long long) + (size_t)bytes); p[0] = 1; return (void*)(p + 1); }
__attribute__((unused)) static void plew_arc_retain(long long* rc) { if (rc) (*rc) += 1; }
__attribute__((unused)) static void plew_arc_release(long long* rc) { if (rc && (--(*rc)) == 0) free((void*)rc); }
__attribute__((unused)) static void* plew_ref_share(void* p) { if (p) ((long long*)p)[-1] += 1; return p; }
__attribute__((unused)) static void* plew_rawbuf_alloc(long long elemSize, long long cap) { long long* h = (long long*)malloc(2 * sizeof(long long) + (size_t)(elemSize * cap)); h[0] = cap; h[1] = 1; return (void*)(h + 2); }
__attribute__((unused)) static long long plew_rawbuf_cap(void* p) { return p ? ((long long*)p)[-2] : 0; }
__attribute__((unused)) static int plew_rawbuf_is_unique(void* p) { return p ? (((long long*)p)[-1] == 1) : 1; }
__attribute__((unused)) static void* plew_rawbuf_share(void* p) { if (p) ((long long*)p)[-1] += 1; return p; }
__attribute__((unused)) static void plew_rawbuf_release(void* p) { if (p && (--(((long long*)p)[-1])) == 0) free(((long long*)p) - 2); }
typedef struct { void* fn; void* env; long long* rc; void (*drop)(void*); } PlewClosure;
__attribute__((unused)) static PlewClosure plew_closure_share(PlewClosure cl) { plew_arc_retain(cl.rc); return cl; }
__attribute__((unused)) static void plew_closure_release(PlewClosure cl) { if (cl.rc && (--(*cl.rc)) == 0) { if (cl.drop) cl.drop(cl.env); free((void*)cl.rc); } }
__attribute__((unused)) static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (long long i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }
__attribute__((unused)) static PlewString plew_readStdin(void) { size_t cap = 4096, len = 0; char* buf = (char*)malloc(cap); int ch; while ((ch = getchar()) != EOF) { if (len + 1 >= cap) { cap *= 2; buf = (char*)realloc(buf, cap); } buf[len++] = (char)ch; } PlewString s; s.data = buf; s.len = (long long)len; return s; }
__attribute__((unused)) static void plew_write(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stdout); }
__attribute__((unused)) static void plew_writeByte(unsigned char b) { putchar((int)b); }
__attribute__((noreturn)) static void plew_exit(long long code) { exit((int)code); }
__attribute__((unused)) static void plew_eprint(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stderr); }
__attribute__((noreturn)) static void plew_panic(PlewString m) { fputs("panic: ", stderr); fwrite(m.data, 1, (size_t)m.len, stderr); fputc('\n', stderr); exit(1); }
__attribute__((unused)) static long long plew_div(long long a, long long b) { if (b == 0) plew_panic((PlewString){"division by zero", 16}); if (b == -1 && a == INT64_MIN) plew_panic((PlewString){"integer overflow", 16}); return a / b; }
__attribute__((unused)) static long long plew_mod(long long a, long long b) { if (b == 0) plew_panic((PlewString){"remainder by zero", 17}); if (b == -1) return 0; return a % b; }
static int plew_argc = 0;
static char** plew_argv = 0;
__attribute__((unused)) static long long plew_argCount(void) { return (long long)plew_argc; }
__attribute__((unused)) static PlewString plew_argAt(long long i) { PlewString s; if (i < 0 || i >= plew_argc) { s.data = ""; s.len = 0; return s; } s.data = plew_argv[i]; s.len = (long long)strlen(plew_argv[i]); return s; }
__attribute__((unused)) static PlewString plew_readFile(PlewString path) { FILE* f = fopen(path.data, "rb"); PlewString s; if (!f) { s.data = ""; s.len = 0; return s; } fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET); char* buf = (char*)malloc((size_t)sz + 1); size_t n = fread(buf, 1, (size_t)sz, f); fclose(f); buf[n] = 0; s.data = buf; s.len = (long long)n; return s; }
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
typedef struct AssocBinding AssocBinding;
typedef struct Conform Conform;
typedef struct MethodAlias MethodAlias;
typedef struct FuncBound FuncBound;
typedef struct FnInst FnInst;
typedef struct EnumDef EnumDef;
typedef struct Func Func;
typedef struct Comp Comp;
typedef struct LetEff LetEff;
typedef struct ConstInt ConstInt;
typedef struct IntTy IntTy;
typedef struct Kind Kind;
typedef struct Expr Expr;
typedef struct Stmt Stmt;
typedef struct Array_Arg Array_Arg;
typedef struct Array_Bind Array_Bind;
typedef struct Array_PatInfo Array_PatInfo;
typedef struct Array_Param Array_Param;
typedef struct Array_MatchArm Array_MatchArm;
typedef struct Array_MakeField Array_MakeField;
typedef struct Array_Func Array_Func;
typedef struct Array_U64 Array_U64;
typedef struct Array_Tok Array_Tok;
typedef struct Array_FieldDef Array_FieldDef;
typedef struct Array_Variant Array_Variant;
typedef struct Array_Expr Array_Expr;
typedef struct Array_Stmt Array_Stmt;
typedef struct Array_Block Array_Block;
typedef struct Array_StructDef Array_StructDef;
typedef struct Array_EnumDef Array_EnumDef;
typedef struct Array_TraitDef Array_TraitDef;
typedef struct Array_Conform Array_Conform;
typedef struct Array_MethodAlias Array_MethodAlias;
typedef struct Array_DeriveReq Array_DeriveReq;
typedef struct Array_FuncBound Array_FuncBound;
typedef struct Array_TypeRef Array_TypeRef;
typedef struct Array_FnInst Array_FnInst;
typedef struct Array_CaptureEntry Array_CaptureEntry;
typedef struct Array_Local Array_Local;
typedef struct Array_AssocBinding Array_AssocBinding;
struct Array_Arg {
    Arg* data;
    uint64_t count;
};
struct Array_Bind {
    Bind* data;
    uint64_t count;
};
struct Array_PatInfo {
    PatInfo* data;
    uint64_t count;
};
struct Array_Param {
    Param* data;
    uint64_t count;
};
struct Array_MatchArm {
    MatchArm* data;
    uint64_t count;
};
struct Array_MakeField {
    MakeField* data;
    uint64_t count;
};
struct Array_Func {
    Func* data;
    uint64_t count;
};
struct Array_U64 {
    uint64_t* data;
    uint64_t count;
};
struct Array_Tok {
    Tok* data;
    uint64_t count;
};
struct Array_FieldDef {
    FieldDef* data;
    uint64_t count;
};
struct Array_Variant {
    Variant* data;
    uint64_t count;
};
struct Array_Expr {
    Expr* data;
    uint64_t count;
};
struct Array_Stmt {
    Stmt* data;
    uint64_t count;
};
struct Array_Block {
    Block* data;
    uint64_t count;
};
struct Array_StructDef {
    StructDef* data;
    uint64_t count;
};
struct Array_EnumDef {
    EnumDef* data;
    uint64_t count;
};
struct Array_TraitDef {
    TraitDef* data;
    uint64_t count;
};
struct Array_Conform {
    Conform* data;
    uint64_t count;
};
struct Array_MethodAlias {
    MethodAlias* data;
    uint64_t count;
};
struct Array_DeriveReq {
    DeriveReq* data;
    uint64_t count;
};
struct Array_FuncBound {
    FuncBound* data;
    uint64_t count;
};
struct Array_TypeRef {
    TypeRef* data;
    uint64_t count;
};
struct Array_FnInst {
    FnInst* data;
    uint64_t count;
};
struct Array_CaptureEntry {
    CaptureEntry* data;
    uint64_t count;
};
struct Array_Local {
    Local* data;
    uint64_t count;
};
struct Array_AssocBinding {
    AssocBinding* data;
    uint64_t count;
};
typedef struct { unsigned char* data; long long count; } Array_U8;
__attribute__((unused)) static PlewString plew_readFileBytes(Array_U8 p) { char* path = (char*)malloc((size_t)p.count + 1); memcpy(path, p.data, (size_t)p.count); path[p.count] = 0; PlewString r = plew_readFile((PlewString){path, p.count}); free(path); return r; }
__attribute__((unused)) static long long plew_fileExists(Array_U8 p) { char* path = (char*)malloc((size_t)p.count + 1); memcpy(path, p.data, (size_t)p.count); path[p.count] = 0; FILE* f = fopen(path, "rb"); free(path); if (f) { fclose(f); return 1; } return 0; }
__attribute__((unused)) static PlewString plew_stringFromBytes(Array_U8 p) { char* buf = (char*)malloc((size_t)p.count + 1); memcpy(buf, p.data, (size_t)p.count); buf[p.count] = 0; PlewString s; s.data = buf; s.len = p.count; return s; }
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
        struct { char _u; } KwAsync;
        struct { char _u; } KwAwait;
        struct { char _u; } KwExtern;
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
        struct { uint64_t value; uint64_t offset; long long isBool; uint64_t tyStart; uint64_t tyLen; } Int;
        struct { uint64_t start; uint64_t len; } Ident;
        struct { int64_t op; uint64_t operand; } Unary;
        struct { int64_t op; uint64_t lhs; uint64_t rhs; } Binary;
        struct { uint64_t nameStart; uint64_t nameLen; Array_Arg args; } Call;
        struct { uint64_t base; uint64_t nameStart; uint64_t nameLen; } Field;
        struct { uint64_t typeStart; uint64_t typeLen; uint64_t variantStart; uint64_t variantLen; long long isEnum; uint64_t ty; Array_MakeField fields; } Make;
        struct { uint64_t start; uint64_t len; } Str;
        struct { Array_U64 elems; } Array;
        struct { uint64_t base; uint64_t index; } Index;
        struct { uint64_t recv; uint64_t nameStart; uint64_t nameLen; Array_Arg args; } Method;
        struct { uint64_t operand; uint64_t tyStart; uint64_t tyLen; uint64_t ty; } Cast;
        struct { uint64_t scrut; Array_MatchArm arms; } MatchExpr;
        struct { uint64_t cond; uint64_t thenBlk; uint64_t elseBlk; } IfExpr;
        struct { uint64_t opt; uint64_t deflt; } Coalesce;
        struct { uint64_t expr; } Try;
        struct { uint64_t base; uint64_t nameStart; uint64_t nameLen; } Arrow;
        struct { Array_Param params; long long hasRet; uint64_t retStart; uint64_t retLen; long long retIsArray; uint64_t retTy; uint64_t body; } Closure;
        struct { uint64_t operand; long long isBorrow; } Move;
        struct { uint64_t operand; } Await;
    } data;
};
struct Stmt {
    long long tag;
    union {
        struct { long long mutable; uint64_t nameStart; uint64_t nameLen; uint64_t tyStart; uint64_t tyLen; long long tyIsArray; uint64_t ty; uint64_t init; } Let;
        struct { int64_t op; uint64_t target; uint64_t value; } Assign;
        struct { uint64_t expr; } ExprStmt;
        struct { uint64_t value; long long hasValue; } Return;
        struct { uint64_t cond; uint64_t thenBlk; uint64_t elseBlk; long long hasElse; } If;
        struct { uint64_t cond; uint64_t body; } While;
        struct { uint64_t varStart; uint64_t varLen; long long isRange; long long inclusive; uint64_t iter; uint64_t rangeHi; uint64_t body; long long isStruct; uint64_t patStart; uint64_t patLen; Array_Bind binds; } For;
        struct { uint64_t scrut; Array_MatchArm arms; } Match;
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
    Array_U8 bytes;
    uint64_t pos;
    Array_Tok toks;
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
    Array_U64 args;
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
    Array_Bind binds;
    uint64_t body;
    long long isStruct;
};
struct PatInfo {
    long long isWildcard;
    uint64_t enumStart;
    uint64_t enumLen;
    uint64_t variantStart;
    uint64_t variantLen;
    Array_Bind binds;
    long long isStruct;
};
struct Block {
    Array_U64 stmts;
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
    uint64_t vis;
};
struct StructDef {
    uint64_t nameStart;
    uint64_t nameLen;
    Array_Bind typeParams;
    Array_FieldDef fields;
    long long isUnique;
    long long isExtern;
};
struct Variant {
    uint64_t nameStart;
    uint64_t nameLen;
    Array_FieldDef fields;
};
struct TraitDef {
    uint64_t nameStart;
    uint64_t nameLen;
    Array_Bind supertraits;
    Array_Func reqs;
    Array_Bind assocTypes;
};
struct DeriveReq {
    uint64_t typeStart;
    uint64_t typeLen;
    long long isEnum;
    uint64_t nameStart;
    uint64_t nameLen;
};
struct AssocBinding {
    uint64_t recvStart;
    uint64_t recvLen;
    uint64_t nameStart;
    uint64_t nameLen;
    uint64_t tyStart;
    uint64_t tyLen;
    long long tyIsArray;
    uint64_t ty;
};
struct Conform {
    uint64_t typeStart;
    uint64_t typeLen;
    uint64_t traitStart;
    uint64_t traitLen;
    long long derived;
    Array_Func witnessed;
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
    Array_U64 args;
    uint64_t recvInstRef;
};
struct EnumDef {
    uint64_t nameStart;
    uint64_t nameLen;
    Array_Bind typeParams;
    Array_Variant variants;
};
struct Func {
    uint64_t nameStart;
    uint64_t nameLen;
    Array_Bind typeParams;
    Array_Param params;
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
    long long isAsync;
    long long isExtern;
    long long isPub;
    long long isProvided;
};
struct Comp {
    Array_U8 bytes;
    Array_Tok toks;
    uint64_t pos;
    Array_Expr exprs;
    Array_Stmt stmts;
    Array_Block blocks;
    Array_Func funcs;
    Array_StructDef structs;
    Array_EnumDef enums;
    Array_TraitDef traits;
    Array_Conform conforms;
    Array_MethodAlias methodAliases;
    Array_DeriveReq derives;
    Array_Bind pendingDerives;
    Array_FuncBound funcBounds;
    uint64_t curCheckFn;
    Array_Func curWitnessed;
    Array_Bind curWhereTraits;
    Array_Bind curImplBoundParams;
    Array_Bind curImplBoundTraits;
    Array_U64 boxedFields;
    Array_TypeRef types;
    Array_U64 genInsts;
    Array_FnInst fnInsts;
    Array_U64 fnTypes;
    Array_U64 fnThunks;
    Array_CaptureEntry captures;
    uint64_t curClosureId;
    long long curInClosure;
    uint64_t curCaptureMark;
    Array_Bind arrayElems;
    Array_Local locals;
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
    Array_Bind curTypeParams;
    Array_U64 curTypeArgs;
    uint64_t curRecvInstRef;
    uint64_t curSelfRef;
    uint64_t curItemRef;
    uint64_t curGiveTmp;
    uint64_t curLoopMark;
    uint64_t curBranchBase;
    Array_Bind deinits;
    long long curAsync;
    uint64_t asyncState;
    uint64_t curAsyncFn;
    uint64_t asyncVarSeq;
    Array_Bind moduleRanges;
    Array_Bind exports;
    Array_Bind imports;
    Array_AssocBinding assocBindings;
};
struct LetEff {
    uint64_t start;
    uint64_t len;
    long long arr;
    uint64_t ty;
};
struct ConstInt {
    long long isConst;
    long long neg;
    uint64_t value;
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
Expr Expr_copy(Expr s);
Expr Expr_share(Expr s);
void Expr_release(Expr s);
Stmt Stmt_copy(Stmt s);
Stmt Stmt_share(Stmt s);
void Stmt_release(Stmt s);
__attribute__((unused)) static Array_U8 Array_U8_new(void) { Array_U8 a; a.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), 0); a.count = 0; return a; }
__attribute__((unused)) static unsigned char Array_U8_get(Array_U8 a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_U8 Array_U8_copy(Array_U8 a) { Array_U8 r; r.count = a.count; r.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_U8_release(Array_U8 a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_U8 Array_U8_share(Array_U8 a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_U8_unique(Array_U8* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_U8 nc = Array_U8_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_U8_set(Array_U8* a, long long i, unsigned char v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_U8_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_U8_push(Array_U8* a, unsigned char v) { Array_U8_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; unsigned char* nd = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_Bind Array_Bind_new(void) { Array_Bind a; a.data = (Bind*)plew_rawbuf_alloc(sizeof(Bind), 0); a.count = 0; return a; }
__attribute__((unused)) static Bind Array_Bind_get(Array_Bind a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Bind Array_Bind_copy(Array_Bind a) { Array_Bind r; r.count = a.count; r.data = (Bind*)plew_rawbuf_alloc(sizeof(Bind), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_Bind_release(Array_Bind a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Bind Array_Bind_share(Array_Bind a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Bind_unique(Array_Bind* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Bind nc = Array_Bind_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Bind_set(Array_Bind* a, long long i, Bind v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Bind_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_Bind_push(Array_Bind* a, Bind v) { Array_Bind_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Bind* nd = (Bind*)plew_rawbuf_alloc(sizeof(Bind), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_Tok Array_Tok_new(void) { Array_Tok a; a.data = (Tok*)plew_rawbuf_alloc(sizeof(Tok), 0); a.count = 0; return a; }
__attribute__((unused)) static Tok Array_Tok_get(Array_Tok a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Tok Array_Tok_copy(Array_Tok a) { Array_Tok r; r.count = a.count; r.data = (Tok*)plew_rawbuf_alloc(sizeof(Tok), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_Tok_release(Array_Tok a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Tok Array_Tok_share(Array_Tok a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Tok_unique(Array_Tok* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Tok nc = Array_Tok_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Tok_set(Array_Tok* a, long long i, Tok v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Tok_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_Tok_push(Array_Tok* a, Tok v) { Array_Tok_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Tok* nd = (Tok*)plew_rawbuf_alloc(sizeof(Tok), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_U64 Array_U64_new(void) { Array_U64 a; a.data = (uint64_t*)plew_rawbuf_alloc(sizeof(uint64_t), 0); a.count = 0; return a; }
__attribute__((unused)) static uint64_t Array_U64_get(Array_U64 a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_U64 Array_U64_copy(Array_U64 a) { Array_U64 r; r.count = a.count; r.data = (uint64_t*)plew_rawbuf_alloc(sizeof(uint64_t), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_U64_release(Array_U64 a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_U64 Array_U64_share(Array_U64 a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_U64_unique(Array_U64* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_U64 nc = Array_U64_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_U64_set(Array_U64* a, long long i, uint64_t v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_U64_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_U64_push(Array_U64* a, uint64_t v) { Array_U64_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; uint64_t* nd = (uint64_t*)plew_rawbuf_alloc(sizeof(uint64_t), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_Arg Array_Arg_new(void) { Array_Arg a; a.data = (Arg*)plew_rawbuf_alloc(sizeof(Arg), 0); a.count = 0; return a; }
__attribute__((unused)) static Arg Array_Arg_get(Array_Arg a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Arg Array_Arg_copy(Array_Arg a) { Array_Arg r; r.count = a.count; r.data = (Arg*)plew_rawbuf_alloc(sizeof(Arg), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_Arg_release(Array_Arg a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Arg Array_Arg_share(Array_Arg a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Arg_unique(Array_Arg* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Arg nc = Array_Arg_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Arg_set(Array_Arg* a, long long i, Arg v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Arg_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_Arg_push(Array_Arg* a, Arg v) { Array_Arg_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Arg* nd = (Arg*)plew_rawbuf_alloc(sizeof(Arg), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_MakeField Array_MakeField_new(void) { Array_MakeField a; a.data = (MakeField*)plew_rawbuf_alloc(sizeof(MakeField), 0); a.count = 0; return a; }
__attribute__((unused)) static MakeField Array_MakeField_get(Array_MakeField a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_MakeField Array_MakeField_copy(Array_MakeField a) { Array_MakeField r; r.count = a.count; r.data = (MakeField*)plew_rawbuf_alloc(sizeof(MakeField), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_MakeField_release(Array_MakeField a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_MakeField Array_MakeField_share(Array_MakeField a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_MakeField_unique(Array_MakeField* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_MakeField nc = Array_MakeField_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_MakeField_set(Array_MakeField* a, long long i, MakeField v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_MakeField_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_MakeField_push(Array_MakeField* a, MakeField v) { Array_MakeField_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; MakeField* nd = (MakeField*)plew_rawbuf_alloc(sizeof(MakeField), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_MatchArm Array_MatchArm_new(void) { Array_MatchArm a; a.data = (MatchArm*)plew_rawbuf_alloc(sizeof(MatchArm), 0); a.count = 0; return a; }
__attribute__((unused)) static MatchArm Array_MatchArm_get(Array_MatchArm a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_MatchArm Array_MatchArm_copy(Array_MatchArm a) { Array_MatchArm r; r.count = a.count; r.data = (MatchArm*)plew_rawbuf_alloc(sizeof(MatchArm), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = MatchArm_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_MatchArm_release(Array_MatchArm a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) MatchArm_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_MatchArm Array_MatchArm_share(Array_MatchArm a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_MatchArm_unique(Array_MatchArm* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_MatchArm nc = Array_MatchArm_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_MatchArm_set(Array_MatchArm* a, long long i, MatchArm v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_MatchArm_unique(a); MatchArm_release(a->data[i]); a->data[i] = MatchArm_copy(v); }
__attribute__((unused)) static void Array_MatchArm_push(Array_MatchArm* a, MatchArm v) { Array_MatchArm_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; MatchArm* nd = (MatchArm*)plew_rawbuf_alloc(sizeof(MatchArm), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = MatchArm_copy(v); a->count++; }
__attribute__((unused)) static Array_Param Array_Param_new(void) { Array_Param a; a.data = (Param*)plew_rawbuf_alloc(sizeof(Param), 0); a.count = 0; return a; }
__attribute__((unused)) static Param Array_Param_get(Array_Param a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Param Array_Param_copy(Array_Param a) { Array_Param r; r.count = a.count; r.data = (Param*)plew_rawbuf_alloc(sizeof(Param), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_Param_release(Array_Param a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Param Array_Param_share(Array_Param a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Param_unique(Array_Param* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Param nc = Array_Param_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Param_set(Array_Param* a, long long i, Param v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Param_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_Param_push(Array_Param* a, Param v) { Array_Param_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Param* nd = (Param*)plew_rawbuf_alloc(sizeof(Param), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_FieldDef Array_FieldDef_new(void) { Array_FieldDef a; a.data = (FieldDef*)plew_rawbuf_alloc(sizeof(FieldDef), 0); a.count = 0; return a; }
__attribute__((unused)) static FieldDef Array_FieldDef_get(Array_FieldDef a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_FieldDef Array_FieldDef_copy(Array_FieldDef a) { Array_FieldDef r; r.count = a.count; r.data = (FieldDef*)plew_rawbuf_alloc(sizeof(FieldDef), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_FieldDef_release(Array_FieldDef a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_FieldDef Array_FieldDef_share(Array_FieldDef a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_FieldDef_unique(Array_FieldDef* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_FieldDef nc = Array_FieldDef_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_FieldDef_set(Array_FieldDef* a, long long i, FieldDef v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_FieldDef_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_FieldDef_push(Array_FieldDef* a, FieldDef v) { Array_FieldDef_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; FieldDef* nd = (FieldDef*)plew_rawbuf_alloc(sizeof(FieldDef), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_Func Array_Func_new(void) { Array_Func a; a.data = (Func*)plew_rawbuf_alloc(sizeof(Func), 0); a.count = 0; return a; }
__attribute__((unused)) static Func Array_Func_get(Array_Func a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Func Array_Func_copy(Array_Func a) { Array_Func r; r.count = a.count; r.data = (Func*)plew_rawbuf_alloc(sizeof(Func), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = Func_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_Func_release(Array_Func a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) Func_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Func Array_Func_share(Array_Func a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Func_unique(Array_Func* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Func nc = Array_Func_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Func_set(Array_Func* a, long long i, Func v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Func_unique(a); Func_release(a->data[i]); a->data[i] = Func_copy(v); }
__attribute__((unused)) static void Array_Func_push(Array_Func* a, Func v) { Array_Func_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Func* nd = (Func*)plew_rawbuf_alloc(sizeof(Func), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = Func_copy(v); a->count++; }
__attribute__((unused)) static Array_Variant Array_Variant_new(void) { Array_Variant a; a.data = (Variant*)plew_rawbuf_alloc(sizeof(Variant), 0); a.count = 0; return a; }
__attribute__((unused)) static Variant Array_Variant_get(Array_Variant a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Variant Array_Variant_copy(Array_Variant a) { Array_Variant r; r.count = a.count; r.data = (Variant*)plew_rawbuf_alloc(sizeof(Variant), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = Variant_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_Variant_release(Array_Variant a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) Variant_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Variant Array_Variant_share(Array_Variant a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Variant_unique(Array_Variant* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Variant nc = Array_Variant_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Variant_set(Array_Variant* a, long long i, Variant v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Variant_unique(a); Variant_release(a->data[i]); a->data[i] = Variant_copy(v); }
__attribute__((unused)) static void Array_Variant_push(Array_Variant* a, Variant v) { Array_Variant_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Variant* nd = (Variant*)plew_rawbuf_alloc(sizeof(Variant), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = Variant_copy(v); a->count++; }
__attribute__((unused)) static Array_Expr Array_Expr_new(void) { Array_Expr a; a.data = (Expr*)plew_rawbuf_alloc(sizeof(Expr), 0); a.count = 0; return a; }
__attribute__((unused)) static Expr Array_Expr_get(Array_Expr a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Expr Array_Expr_copy(Array_Expr a) { Array_Expr r; r.count = a.count; r.data = (Expr*)plew_rawbuf_alloc(sizeof(Expr), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_Expr_release(Array_Expr a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Expr Array_Expr_share(Array_Expr a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Expr_unique(Array_Expr* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Expr nc = Array_Expr_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Expr_set(Array_Expr* a, long long i, Expr v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Expr_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_Expr_push(Array_Expr* a, Expr v) { Array_Expr_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Expr* nd = (Expr*)plew_rawbuf_alloc(sizeof(Expr), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_Stmt Array_Stmt_new(void) { Array_Stmt a; a.data = (Stmt*)plew_rawbuf_alloc(sizeof(Stmt), 0); a.count = 0; return a; }
__attribute__((unused)) static Stmt Array_Stmt_get(Array_Stmt a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Stmt Array_Stmt_copy(Array_Stmt a) { Array_Stmt r; r.count = a.count; r.data = (Stmt*)plew_rawbuf_alloc(sizeof(Stmt), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_Stmt_release(Array_Stmt a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Stmt Array_Stmt_share(Array_Stmt a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Stmt_unique(Array_Stmt* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Stmt nc = Array_Stmt_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Stmt_set(Array_Stmt* a, long long i, Stmt v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Stmt_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_Stmt_push(Array_Stmt* a, Stmt v) { Array_Stmt_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Stmt* nd = (Stmt*)plew_rawbuf_alloc(sizeof(Stmt), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_Block Array_Block_new(void) { Array_Block a; a.data = (Block*)plew_rawbuf_alloc(sizeof(Block), 0); a.count = 0; return a; }
__attribute__((unused)) static Block Array_Block_get(Array_Block a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Block Array_Block_copy(Array_Block a) { Array_Block r; r.count = a.count; r.data = (Block*)plew_rawbuf_alloc(sizeof(Block), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = Block_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_Block_release(Array_Block a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) Block_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Block Array_Block_share(Array_Block a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Block_unique(Array_Block* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Block nc = Array_Block_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Block_set(Array_Block* a, long long i, Block v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Block_unique(a); Block_release(a->data[i]); a->data[i] = Block_copy(v); }
__attribute__((unused)) static void Array_Block_push(Array_Block* a, Block v) { Array_Block_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Block* nd = (Block*)plew_rawbuf_alloc(sizeof(Block), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = Block_copy(v); a->count++; }
__attribute__((unused)) static Array_StructDef Array_StructDef_new(void) { Array_StructDef a; a.data = (StructDef*)plew_rawbuf_alloc(sizeof(StructDef), 0); a.count = 0; return a; }
__attribute__((unused)) static StructDef Array_StructDef_get(Array_StructDef a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_StructDef Array_StructDef_copy(Array_StructDef a) { Array_StructDef r; r.count = a.count; r.data = (StructDef*)plew_rawbuf_alloc(sizeof(StructDef), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = StructDef_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_StructDef_release(Array_StructDef a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) StructDef_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_StructDef Array_StructDef_share(Array_StructDef a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_StructDef_unique(Array_StructDef* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_StructDef nc = Array_StructDef_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_StructDef_set(Array_StructDef* a, long long i, StructDef v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_StructDef_unique(a); StructDef_release(a->data[i]); a->data[i] = StructDef_copy(v); }
__attribute__((unused)) static void Array_StructDef_push(Array_StructDef* a, StructDef v) { Array_StructDef_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; StructDef* nd = (StructDef*)plew_rawbuf_alloc(sizeof(StructDef), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = StructDef_copy(v); a->count++; }
__attribute__((unused)) static Array_EnumDef Array_EnumDef_new(void) { Array_EnumDef a; a.data = (EnumDef*)plew_rawbuf_alloc(sizeof(EnumDef), 0); a.count = 0; return a; }
__attribute__((unused)) static EnumDef Array_EnumDef_get(Array_EnumDef a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_EnumDef Array_EnumDef_copy(Array_EnumDef a) { Array_EnumDef r; r.count = a.count; r.data = (EnumDef*)plew_rawbuf_alloc(sizeof(EnumDef), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = EnumDef_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_EnumDef_release(Array_EnumDef a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) EnumDef_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_EnumDef Array_EnumDef_share(Array_EnumDef a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_EnumDef_unique(Array_EnumDef* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_EnumDef nc = Array_EnumDef_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_EnumDef_set(Array_EnumDef* a, long long i, EnumDef v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_EnumDef_unique(a); EnumDef_release(a->data[i]); a->data[i] = EnumDef_copy(v); }
__attribute__((unused)) static void Array_EnumDef_push(Array_EnumDef* a, EnumDef v) { Array_EnumDef_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; EnumDef* nd = (EnumDef*)plew_rawbuf_alloc(sizeof(EnumDef), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = EnumDef_copy(v); a->count++; }
__attribute__((unused)) static Array_TraitDef Array_TraitDef_new(void) { Array_TraitDef a; a.data = (TraitDef*)plew_rawbuf_alloc(sizeof(TraitDef), 0); a.count = 0; return a; }
__attribute__((unused)) static TraitDef Array_TraitDef_get(Array_TraitDef a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_TraitDef Array_TraitDef_copy(Array_TraitDef a) { Array_TraitDef r; r.count = a.count; r.data = (TraitDef*)plew_rawbuf_alloc(sizeof(TraitDef), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = TraitDef_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_TraitDef_release(Array_TraitDef a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) TraitDef_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_TraitDef Array_TraitDef_share(Array_TraitDef a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_TraitDef_unique(Array_TraitDef* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_TraitDef nc = Array_TraitDef_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_TraitDef_set(Array_TraitDef* a, long long i, TraitDef v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_TraitDef_unique(a); TraitDef_release(a->data[i]); a->data[i] = TraitDef_copy(v); }
__attribute__((unused)) static void Array_TraitDef_push(Array_TraitDef* a, TraitDef v) { Array_TraitDef_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; TraitDef* nd = (TraitDef*)plew_rawbuf_alloc(sizeof(TraitDef), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = TraitDef_copy(v); a->count++; }
__attribute__((unused)) static Array_Conform Array_Conform_new(void) { Array_Conform a; a.data = (Conform*)plew_rawbuf_alloc(sizeof(Conform), 0); a.count = 0; return a; }
__attribute__((unused)) static Conform Array_Conform_get(Array_Conform a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Conform Array_Conform_copy(Array_Conform a) { Array_Conform r; r.count = a.count; r.data = (Conform*)plew_rawbuf_alloc(sizeof(Conform), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = Conform_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_Conform_release(Array_Conform a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) Conform_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Conform Array_Conform_share(Array_Conform a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Conform_unique(Array_Conform* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Conform nc = Array_Conform_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Conform_set(Array_Conform* a, long long i, Conform v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Conform_unique(a); Conform_release(a->data[i]); a->data[i] = Conform_copy(v); }
__attribute__((unused)) static void Array_Conform_push(Array_Conform* a, Conform v) { Array_Conform_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Conform* nd = (Conform*)plew_rawbuf_alloc(sizeof(Conform), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = Conform_copy(v); a->count++; }
__attribute__((unused)) static Array_MethodAlias Array_MethodAlias_new(void) { Array_MethodAlias a; a.data = (MethodAlias*)plew_rawbuf_alloc(sizeof(MethodAlias), 0); a.count = 0; return a; }
__attribute__((unused)) static MethodAlias Array_MethodAlias_get(Array_MethodAlias a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_MethodAlias Array_MethodAlias_copy(Array_MethodAlias a) { Array_MethodAlias r; r.count = a.count; r.data = (MethodAlias*)plew_rawbuf_alloc(sizeof(MethodAlias), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_MethodAlias_release(Array_MethodAlias a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_MethodAlias Array_MethodAlias_share(Array_MethodAlias a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_MethodAlias_unique(Array_MethodAlias* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_MethodAlias nc = Array_MethodAlias_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_MethodAlias_set(Array_MethodAlias* a, long long i, MethodAlias v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_MethodAlias_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_MethodAlias_push(Array_MethodAlias* a, MethodAlias v) { Array_MethodAlias_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; MethodAlias* nd = (MethodAlias*)plew_rawbuf_alloc(sizeof(MethodAlias), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_DeriveReq Array_DeriveReq_new(void) { Array_DeriveReq a; a.data = (DeriveReq*)plew_rawbuf_alloc(sizeof(DeriveReq), 0); a.count = 0; return a; }
__attribute__((unused)) static DeriveReq Array_DeriveReq_get(Array_DeriveReq a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_DeriveReq Array_DeriveReq_copy(Array_DeriveReq a) { Array_DeriveReq r; r.count = a.count; r.data = (DeriveReq*)plew_rawbuf_alloc(sizeof(DeriveReq), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_DeriveReq_release(Array_DeriveReq a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_DeriveReq Array_DeriveReq_share(Array_DeriveReq a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_DeriveReq_unique(Array_DeriveReq* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_DeriveReq nc = Array_DeriveReq_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_DeriveReq_set(Array_DeriveReq* a, long long i, DeriveReq v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_DeriveReq_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_DeriveReq_push(Array_DeriveReq* a, DeriveReq v) { Array_DeriveReq_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; DeriveReq* nd = (DeriveReq*)plew_rawbuf_alloc(sizeof(DeriveReq), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_FuncBound Array_FuncBound_new(void) { Array_FuncBound a; a.data = (FuncBound*)plew_rawbuf_alloc(sizeof(FuncBound), 0); a.count = 0; return a; }
__attribute__((unused)) static FuncBound Array_FuncBound_get(Array_FuncBound a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_FuncBound Array_FuncBound_copy(Array_FuncBound a) { Array_FuncBound r; r.count = a.count; r.data = (FuncBound*)plew_rawbuf_alloc(sizeof(FuncBound), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_FuncBound_release(Array_FuncBound a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_FuncBound Array_FuncBound_share(Array_FuncBound a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_FuncBound_unique(Array_FuncBound* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_FuncBound nc = Array_FuncBound_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_FuncBound_set(Array_FuncBound* a, long long i, FuncBound v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_FuncBound_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_FuncBound_push(Array_FuncBound* a, FuncBound v) { Array_FuncBound_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; FuncBound* nd = (FuncBound*)plew_rawbuf_alloc(sizeof(FuncBound), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_TypeRef Array_TypeRef_new(void) { Array_TypeRef a; a.data = (TypeRef*)plew_rawbuf_alloc(sizeof(TypeRef), 0); a.count = 0; return a; }
__attribute__((unused)) static TypeRef Array_TypeRef_get(Array_TypeRef a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_TypeRef Array_TypeRef_copy(Array_TypeRef a) { Array_TypeRef r; r.count = a.count; r.data = (TypeRef*)plew_rawbuf_alloc(sizeof(TypeRef), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = TypeRef_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_TypeRef_release(Array_TypeRef a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) TypeRef_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_TypeRef Array_TypeRef_share(Array_TypeRef a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_TypeRef_unique(Array_TypeRef* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_TypeRef nc = Array_TypeRef_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_TypeRef_set(Array_TypeRef* a, long long i, TypeRef v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_TypeRef_unique(a); TypeRef_release(a->data[i]); a->data[i] = TypeRef_copy(v); }
__attribute__((unused)) static void Array_TypeRef_push(Array_TypeRef* a, TypeRef v) { Array_TypeRef_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; TypeRef* nd = (TypeRef*)plew_rawbuf_alloc(sizeof(TypeRef), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = TypeRef_copy(v); a->count++; }
__attribute__((unused)) static Array_FnInst Array_FnInst_new(void) { Array_FnInst a; a.data = (FnInst*)plew_rawbuf_alloc(sizeof(FnInst), 0); a.count = 0; return a; }
__attribute__((unused)) static FnInst Array_FnInst_get(Array_FnInst a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_FnInst Array_FnInst_copy(Array_FnInst a) { Array_FnInst r; r.count = a.count; r.data = (FnInst*)plew_rawbuf_alloc(sizeof(FnInst), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = FnInst_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_FnInst_release(Array_FnInst a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) FnInst_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_FnInst Array_FnInst_share(Array_FnInst a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_FnInst_unique(Array_FnInst* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_FnInst nc = Array_FnInst_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_FnInst_set(Array_FnInst* a, long long i, FnInst v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_FnInst_unique(a); FnInst_release(a->data[i]); a->data[i] = FnInst_copy(v); }
__attribute__((unused)) static void Array_FnInst_push(Array_FnInst* a, FnInst v) { Array_FnInst_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; FnInst* nd = (FnInst*)plew_rawbuf_alloc(sizeof(FnInst), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = FnInst_copy(v); a->count++; }
__attribute__((unused)) static Array_CaptureEntry Array_CaptureEntry_new(void) { Array_CaptureEntry a; a.data = (CaptureEntry*)plew_rawbuf_alloc(sizeof(CaptureEntry), 0); a.count = 0; return a; }
__attribute__((unused)) static CaptureEntry Array_CaptureEntry_get(Array_CaptureEntry a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_CaptureEntry Array_CaptureEntry_copy(Array_CaptureEntry a) { Array_CaptureEntry r; r.count = a.count; r.data = (CaptureEntry*)plew_rawbuf_alloc(sizeof(CaptureEntry), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_CaptureEntry_release(Array_CaptureEntry a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_CaptureEntry Array_CaptureEntry_share(Array_CaptureEntry a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_CaptureEntry_unique(Array_CaptureEntry* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_CaptureEntry nc = Array_CaptureEntry_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_CaptureEntry_set(Array_CaptureEntry* a, long long i, CaptureEntry v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_CaptureEntry_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_CaptureEntry_push(Array_CaptureEntry* a, CaptureEntry v) { Array_CaptureEntry_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; CaptureEntry* nd = (CaptureEntry*)plew_rawbuf_alloc(sizeof(CaptureEntry), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_Local Array_Local_new(void) { Array_Local a; a.data = (Local*)plew_rawbuf_alloc(sizeof(Local), 0); a.count = 0; return a; }
__attribute__((unused)) static Local Array_Local_get(Array_Local a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_Local Array_Local_copy(Array_Local a) { Array_Local r; r.count = a.count; r.data = (Local*)plew_rawbuf_alloc(sizeof(Local), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_Local_release(Array_Local a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_Local Array_Local_share(Array_Local a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_Local_unique(Array_Local* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_Local nc = Array_Local_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_Local_set(Array_Local* a, long long i, Local v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_Local_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_Local_push(Array_Local* a, Local v) { Array_Local_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; Local* nd = (Local*)plew_rawbuf_alloc(sizeof(Local), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_AssocBinding Array_AssocBinding_new(void) { Array_AssocBinding a; a.data = (AssocBinding*)plew_rawbuf_alloc(sizeof(AssocBinding), 0); a.count = 0; return a; }
__attribute__((unused)) static AssocBinding Array_AssocBinding_get(Array_AssocBinding a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_AssocBinding Array_AssocBinding_copy(Array_AssocBinding a) { Array_AssocBinding r; r.count = a.count; r.data = (AssocBinding*)plew_rawbuf_alloc(sizeof(AssocBinding), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }
__attribute__((unused)) static void Array_AssocBinding_release(Array_AssocBinding a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_AssocBinding Array_AssocBinding_share(Array_AssocBinding a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_AssocBinding_unique(Array_AssocBinding* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_AssocBinding nc = Array_AssocBinding_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_AssocBinding_set(Array_AssocBinding* a, long long i, AssocBinding v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_AssocBinding_unique(a); a->data[i] = v; }
__attribute__((unused)) static void Array_AssocBinding_push(Array_AssocBinding* a, AssocBinding v) { Array_AssocBinding_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; AssocBinding* nd = (AssocBinding*)plew_rawbuf_alloc(sizeof(AssocBinding), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }
__attribute__((unused)) static Array_PatInfo Array_PatInfo_new(void) { Array_PatInfo a; a.data = (PatInfo*)plew_rawbuf_alloc(sizeof(PatInfo), 0); a.count = 0; return a; }
__attribute__((unused)) static PatInfo Array_PatInfo_get(Array_PatInfo a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
__attribute__((unused)) static Array_PatInfo Array_PatInfo_copy(Array_PatInfo a) { Array_PatInfo r; r.count = a.count; r.data = (PatInfo*)plew_rawbuf_alloc(sizeof(PatInfo), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = PatInfo_copy(a.data[i]); return r; }
__attribute__((unused)) static void Array_PatInfo_release(Array_PatInfo a) { if (!a.data) return; if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) PatInfo_release(a.data[i]); } plew_rawbuf_release((void*)a.data); }
__attribute__((unused)) static Array_PatInfo Array_PatInfo_share(Array_PatInfo a) { plew_rawbuf_share((void*)a.data); return a; }
__attribute__((unused)) static void Array_PatInfo_unique(Array_PatInfo* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_PatInfo nc = Array_PatInfo_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }
__attribute__((unused)) static void Array_PatInfo_set(Array_PatInfo* a, long long i, PatInfo v) { if (i < 0 || i >= a->count) { fprintf(stderr, "panic: index out of range\n"); exit(1); } Array_PatInfo_unique(a); PatInfo_release(a->data[i]); a->data[i] = PatInfo_copy(v); }
__attribute__((unused)) static void Array_PatInfo_push(Array_PatInfo* a, PatInfo v) { Array_PatInfo_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; PatInfo* nd = (PatInfo*)plew_rawbuf_alloc(sizeof(PatInfo), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = PatInfo_copy(v); a->count++; }
Lexer Lexer_copy(Lexer s) { Lexer r = s; r.bytes = Array_U8_copy(s.bytes); r.toks = Array_Tok_copy(s.toks); return r; }
Lexer Lexer_share(Lexer s) { Array_U8_share(s.bytes); Array_Tok_share(s.toks); return s; }
void Lexer_release(Lexer s) { Array_U8_release(s.bytes); Array_Tok_release(s.toks); }
TypeRef TypeRef_copy(TypeRef s) { TypeRef r = s; r.args = Array_U64_copy(s.args); return r; }
TypeRef TypeRef_share(TypeRef s) { Array_U64_share(s.args); return s; }
void TypeRef_release(TypeRef s) { Array_U64_release(s.args); }
MatchArm MatchArm_copy(MatchArm s) { MatchArm r = s; r.binds = Array_Bind_copy(s.binds); return r; }
MatchArm MatchArm_share(MatchArm s) { Array_Bind_share(s.binds); return s; }
void MatchArm_release(MatchArm s) { Array_Bind_release(s.binds); }
PatInfo PatInfo_copy(PatInfo s) { PatInfo r = s; r.binds = Array_Bind_copy(s.binds); return r; }
PatInfo PatInfo_share(PatInfo s) { Array_Bind_share(s.binds); return s; }
void PatInfo_release(PatInfo s) { Array_Bind_release(s.binds); }
Block Block_copy(Block s) { Block r = s; r.stmts = Array_U64_copy(s.stmts); return r; }
Block Block_share(Block s) { Array_U64_share(s.stmts); return s; }
void Block_release(Block s) { Array_U64_release(s.stmts); }
StructDef StructDef_copy(StructDef s) { StructDef r = s; r.typeParams = Array_Bind_copy(s.typeParams); r.fields = Array_FieldDef_copy(s.fields); return r; }
StructDef StructDef_share(StructDef s) { Array_Bind_share(s.typeParams); Array_FieldDef_share(s.fields); return s; }
void StructDef_release(StructDef s) { Array_Bind_release(s.typeParams); Array_FieldDef_release(s.fields); }
Variant Variant_copy(Variant s) { Variant r = s; r.fields = Array_FieldDef_copy(s.fields); return r; }
Variant Variant_share(Variant s) { Array_FieldDef_share(s.fields); return s; }
void Variant_release(Variant s) { Array_FieldDef_release(s.fields); }
TraitDef TraitDef_copy(TraitDef s) { TraitDef r = s; r.supertraits = Array_Bind_copy(s.supertraits); r.reqs = Array_Func_copy(s.reqs); r.assocTypes = Array_Bind_copy(s.assocTypes); return r; }
TraitDef TraitDef_share(TraitDef s) { Array_Bind_share(s.supertraits); Array_Func_share(s.reqs); Array_Bind_share(s.assocTypes); return s; }
void TraitDef_release(TraitDef s) { Array_Bind_release(s.supertraits); Array_Func_release(s.reqs); Array_Bind_release(s.assocTypes); }
Conform Conform_copy(Conform s) { Conform r = s; r.witnessed = Array_Func_copy(s.witnessed); return r; }
Conform Conform_share(Conform s) { Array_Func_share(s.witnessed); return s; }
void Conform_release(Conform s) { Array_Func_release(s.witnessed); }
FnInst FnInst_copy(FnInst s) { FnInst r = s; r.args = Array_U64_copy(s.args); return r; }
FnInst FnInst_share(FnInst s) { Array_U64_share(s.args); return s; }
void FnInst_release(FnInst s) { Array_U64_release(s.args); }
EnumDef EnumDef_copy(EnumDef s) { EnumDef r = s; r.typeParams = Array_Bind_copy(s.typeParams); r.variants = Array_Variant_copy(s.variants); return r; }
EnumDef EnumDef_share(EnumDef s) { Array_Bind_share(s.typeParams); Array_Variant_share(s.variants); return s; }
void EnumDef_release(EnumDef s) { Array_Bind_release(s.typeParams); Array_Variant_release(s.variants); }
Func Func_copy(Func s) { Func r = s; r.typeParams = Array_Bind_copy(s.typeParams); r.params = Array_Param_copy(s.params); return r; }
Func Func_share(Func s) { Array_Bind_share(s.typeParams); Array_Param_share(s.params); return s; }
void Func_release(Func s) { Array_Bind_release(s.typeParams); Array_Param_release(s.params); }
Comp Comp_copy(Comp s) { Comp r = s; r.bytes = Array_U8_copy(s.bytes); r.toks = Array_Tok_copy(s.toks); r.exprs = Array_Expr_copy(s.exprs); r.stmts = Array_Stmt_copy(s.stmts); r.blocks = Array_Block_copy(s.blocks); r.funcs = Array_Func_copy(s.funcs); r.structs = Array_StructDef_copy(s.structs); r.enums = Array_EnumDef_copy(s.enums); r.traits = Array_TraitDef_copy(s.traits); r.conforms = Array_Conform_copy(s.conforms); r.methodAliases = Array_MethodAlias_copy(s.methodAliases); r.derives = Array_DeriveReq_copy(s.derives); r.pendingDerives = Array_Bind_copy(s.pendingDerives); r.funcBounds = Array_FuncBound_copy(s.funcBounds); r.curWitnessed = Array_Func_copy(s.curWitnessed); r.curWhereTraits = Array_Bind_copy(s.curWhereTraits); r.curImplBoundParams = Array_Bind_copy(s.curImplBoundParams); r.curImplBoundTraits = Array_Bind_copy(s.curImplBoundTraits); r.boxedFields = Array_U64_copy(s.boxedFields); r.types = Array_TypeRef_copy(s.types); r.genInsts = Array_U64_copy(s.genInsts); r.fnInsts = Array_FnInst_copy(s.fnInsts); r.fnTypes = Array_U64_copy(s.fnTypes); r.fnThunks = Array_U64_copy(s.fnThunks); r.captures = Array_CaptureEntry_copy(s.captures); r.arrayElems = Array_Bind_copy(s.arrayElems); r.locals = Array_Local_copy(s.locals); r.curTypeParams = Array_Bind_copy(s.curTypeParams); r.curTypeArgs = Array_U64_copy(s.curTypeArgs); r.deinits = Array_Bind_copy(s.deinits); r.moduleRanges = Array_Bind_copy(s.moduleRanges); r.exports = Array_Bind_copy(s.exports); r.imports = Array_Bind_copy(s.imports); r.assocBindings = Array_AssocBinding_copy(s.assocBindings); return r; }
Comp Comp_share(Comp s) { Array_U8_share(s.bytes); Array_Tok_share(s.toks); Array_Expr_share(s.exprs); Array_Stmt_share(s.stmts); Array_Block_share(s.blocks); Array_Func_share(s.funcs); Array_StructDef_share(s.structs); Array_EnumDef_share(s.enums); Array_TraitDef_share(s.traits); Array_Conform_share(s.conforms); Array_MethodAlias_share(s.methodAliases); Array_DeriveReq_share(s.derives); Array_Bind_share(s.pendingDerives); Array_FuncBound_share(s.funcBounds); Array_Func_share(s.curWitnessed); Array_Bind_share(s.curWhereTraits); Array_Bind_share(s.curImplBoundParams); Array_Bind_share(s.curImplBoundTraits); Array_U64_share(s.boxedFields); Array_TypeRef_share(s.types); Array_U64_share(s.genInsts); Array_FnInst_share(s.fnInsts); Array_U64_share(s.fnTypes); Array_U64_share(s.fnThunks); Array_CaptureEntry_share(s.captures); Array_Bind_share(s.arrayElems); Array_Local_share(s.locals); Array_Bind_share(s.curTypeParams); Array_U64_share(s.curTypeArgs); Array_Bind_share(s.deinits); Array_Bind_share(s.moduleRanges); Array_Bind_share(s.exports); Array_Bind_share(s.imports); Array_AssocBinding_share(s.assocBindings); return s; }
void Comp_release(Comp s) { Array_U8_release(s.bytes); Array_Tok_release(s.toks); Array_Expr_release(s.exprs); Array_Stmt_release(s.stmts); Array_Block_release(s.blocks); Array_Func_release(s.funcs); Array_StructDef_release(s.structs); Array_EnumDef_release(s.enums); Array_TraitDef_release(s.traits); Array_Conform_release(s.conforms); Array_MethodAlias_release(s.methodAliases); Array_DeriveReq_release(s.derives); Array_Bind_release(s.pendingDerives); Array_FuncBound_release(s.funcBounds); Array_Func_release(s.curWitnessed); Array_Bind_release(s.curWhereTraits); Array_Bind_release(s.curImplBoundParams); Array_Bind_release(s.curImplBoundTraits); Array_U64_release(s.boxedFields); Array_TypeRef_release(s.types); Array_U64_release(s.genInsts); Array_FnInst_release(s.fnInsts); Array_U64_release(s.fnTypes); Array_U64_release(s.fnThunks); Array_CaptureEntry_release(s.captures); Array_Bind_release(s.arrayElems); Array_Local_release(s.locals); Array_Bind_release(s.curTypeParams); Array_U64_release(s.curTypeArgs); Array_Bind_release(s.deinits); Array_Bind_release(s.moduleRanges); Array_Bind_release(s.exports); Array_Bind_release(s.imports); Array_AssocBinding_release(s.assocBindings); }
Expr Expr_copy(Expr s) { Expr r = s; if (s.tag == 4) { r.data.Call.args = Array_Arg_copy(s.data.Call.args); } if (s.tag == 6) { r.data.Make.fields = Array_MakeField_copy(s.data.Make.fields); } if (s.tag == 8) { r.data.Array.elems = Array_U64_copy(s.data.Array.elems); } if (s.tag == 10) { r.data.Method.args = Array_Arg_copy(s.data.Method.args); } if (s.tag == 12) { r.data.MatchExpr.arms = Array_MatchArm_copy(s.data.MatchExpr.arms); } if (s.tag == 17) { r.data.Closure.params = Array_Param_copy(s.data.Closure.params); } return r; }
Expr Expr_share(Expr s) { if (s.tag == 4) { Array_Arg_share(s.data.Call.args); } if (s.tag == 6) { Array_MakeField_share(s.data.Make.fields); } if (s.tag == 8) { Array_U64_share(s.data.Array.elems); } if (s.tag == 10) { Array_Arg_share(s.data.Method.args); } if (s.tag == 12) { Array_MatchArm_share(s.data.MatchExpr.arms); } if (s.tag == 17) { Array_Param_share(s.data.Closure.params); } return s; }
void Expr_release(Expr s) { if (s.tag == 4) { Array_Arg_release(s.data.Call.args); } if (s.tag == 6) { Array_MakeField_release(s.data.Make.fields); } if (s.tag == 8) { Array_U64_release(s.data.Array.elems); } if (s.tag == 10) { Array_Arg_release(s.data.Method.args); } if (s.tag == 12) { Array_MatchArm_release(s.data.MatchExpr.arms); } if (s.tag == 17) { Array_Param_release(s.data.Closure.params); } }
Stmt Stmt_copy(Stmt s) { Stmt r = s; if (s.tag == 6) { r.data.For.binds = Array_Bind_copy(s.data.For.binds); } if (s.tag == 7) { r.data.Match.arms = Array_MatchArm_copy(s.data.Match.arms); } return r; }
Stmt Stmt_share(Stmt s) { if (s.tag == 6) { Array_Bind_share(s.data.For.binds); } if (s.tag == 7) { Array_MatchArm_share(s.data.Match.arms); } return s; }
void Stmt_release(Stmt s) { if (s.tag == 6) { Array_Bind_release(s.data.For.binds); } if (s.tag == 7) { Array_MatchArm_release(s.data.Match.arms); } }
unsigned char Lexer_at_off_U64(Lexer self, uint64_t off);
void Lexer_emit_k_Kind_start_U64_len_U64(Lexer* self, Kind k, uint64_t start, uint64_t len);
long long Lexer_lastWasNewline(Lexer self);
long long Lexer_lastCanEnd(Lexer self);
long long isDigit_b_U8(unsigned char b);
long long isAlpha_b_U8(unsigned char b);
long long isAlnum_b_U8(unsigned char b);
long long rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8 bytes, uint64_t start, uint64_t len, PlewString kw);
Kind identKind_bytes_AU8_start_U64_len_U64(Array_U8 bytes, uint64_t start, uint64_t len);
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
void expect_c_Comp_k_Kind_msg_String(Comp* c, Kind k, PlewString msg);
uint64_t tokenValue_c_Comp_t_Tok(Comp* c, Tok t);
int64_t binPrec_k_Kind(Kind k);
uint64_t charValue_c_Comp_t_Tok(Comp* c, Tok t);
uint64_t parsePrimary_c_Comp(Comp* c);
uint64_t parseUnary_c_Comp(Comp* c);
uint64_t parsePostfix_c_Comp(Comp* c);
uint64_t parseMake_c_Comp(Comp* c);
uint64_t parseBin_c_Comp_minPrec_I64(Comp* c, int64_t minPrec);
uint64_t parseExpr_c_Comp(Comp* c);
Array_Arg parseCallArgs_c_Comp(Comp* c);
long long isAssignOp_k_Kind(Kind k);
PType parseTypeTok_c_Comp(Comp* c);
Array_Bind parseTypeParams_c_Comp(Comp* c);
void recordArrayElem_c_Comp_ty_PType(Comp* c, PType ty);
uint64_t parseLet_c_Comp_mutable_Bool(Comp* c, long long mutable);
uint64_t parsePanic_c_Comp(Comp* c);
uint64_t parseReturn_c_Comp(Comp* c);
uint64_t parseIf_c_Comp(Comp* c);
uint64_t parseIfExpr_c_Comp(Comp* c);
uint64_t parseGive_c_Comp(Comp* c);
uint64_t parseWhile_c_Comp(Comp* c);
uint64_t parseFor_c_Comp(Comp* c);
uint64_t parseExprOrAssign_c_Comp(Comp* c);
PatInfo parsePattern_c_Comp(Comp* c);
long long bindNamesMatch_c_Comp_a_ABind_b_ABind(Comp* c, Array_Bind a, Array_Bind b);
Array_PatInfo parseArmPatterns_c_Comp(Comp* c);
uint64_t parseArmBody_c_Comp(Comp* c);
uint64_t parseMatch_c_Comp(Comp* c);
uint64_t parseMatchExpr_c_Comp(Comp* c);
uint64_t parseStmt_c_Comp(Comp* c);
uint64_t parseBlock_c_Comp(Comp* c);
Array_Param parseParamList_c_Comp(Comp* c);
void parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(Comp* c, long long hasRecv, uint64_t recvStart, uint64_t recvLen, long long selfInout, long long selfMove, Array_Bind implParams, long long traitImpl, long long isAssoc, long long isAsync, long long isPub);
Array_Bind parseWhereClause_c_Comp(Comp* c);
void parseFunc_c_Comp_isAsync_Bool(Comp* c, long long isAsync);
void parseImpl_c_Comp_isPub_Bool(Comp* c, long long isPub);
void parseTrait_c_Comp(Comp* c);
Func parseReqSig_c_Comp_isAssoc_Bool_isExtern_Bool(Comp* c, long long isAssoc, long long isExtern);
void parseExtern_c_Comp(Comp* c);
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
void parseExport_c_Comp(Comp* c);
void recordExport_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
void parseImport_c_Comp(Comp* c);
void parseProgram_c_Comp(Comp* c);
PlewString digitStr_d_I64(int64_t d);
void writeInt_n_I64(int64_t n);
PlewString digitStrU_d_U64(uint64_t d);
void writeU64_n_U64(uint64_t n);
void writeIntLit_n_U64(uint64_t n);
void writeSpan_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void eprintInt_n_I64(int64_t n);
void compileError_msg_String(PlewString msg);
void compileErrorAt_line_I64_msg_String(int64_t line, PlewString msg);
long long isPrimType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long isIntType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
uint64_t intBits_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long intSigned_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long losslessInt_c_Comp_srcStart_U64_srcLen_U64_dstStart_U64_dstLen_U64(Comp* c, uint64_t srcStart, uint64_t srcLen, uint64_t dstStart, uint64_t dstLen);
long long litFitsType_c_Comp_value_U64_neg_Bool_dstStart_U64_dstLen_U64(Comp* c, uint64_t value, long long neg, uint64_t dstStart, uint64_t dstLen);
long long litFitsBits_value_U64_neg_Bool_bits_U64_sgn_Bool(uint64_t value, long long neg, uint64_t bits, long long sgn);
uint64_t arrayElemRef_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
Bind arrayElemNameForRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef);
void genCElem_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(Comp* c, uint64_t start, uint64_t len, long long isArray);
void genCType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void genTypeInfoCType_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
long long spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(Comp* c, uint64_t aStart, uint64_t aLen, uint64_t bStart, uint64_t bLen);
int64_t lineOf_c_Comp_offset_U64(Comp* c, uint64_t offset);
uint64_t exprOffset_c_Comp_id_U64(Comp* c, uint64_t id);
uint64_t moduleOf_c_Comp_offset_U64(Comp* c, uint64_t offset);
LetEff inferLetType_c_Comp_tyStart_U64_tyLen_U64_tyIsArray_Bool_ty_U64_init_U64(Comp* c, uint64_t tyStart, uint64_t tyLen, long long tyIsArray, uint64_t ty, uint64_t init);
uint64_t findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
uint64_t firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
long long funcNameExists_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
uint64_t findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
long long isTypeName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
Bind assocRecvName_c_Comp_recv_U64(Comp* c, uint64_t recv);
long long paramsLabelsOk_c_Comp_params_AParam_args_AArg(Comp* c, Array_Param params, Array_Arg args);
long long argMatchesParam_c_Comp_argExpr_U64_p_Param(Comp* c, uint64_t argExpr, Param p);
long long paramsTypesMatch_c_Comp_params_AParam_args_AArg(Comp* c, Array_Param params, Array_Arg args);
long long callLabelsOk_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
long long armCovers_c_Comp_arms_AMatchArm_variantStart_U64_variantLen_U64(Comp* c, Array_MatchArm arms, uint64_t variantStart, uint64_t variantLen);
long long matchExhaustive_c_Comp_arms_AMatchArm(Comp* c, Array_MatchArm arms);
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
uint64_t fieldVis_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen);
long long inAnonImplOf_c_Comp_ownerStart_U64_ownerLen_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen);
void checkFieldReadVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t offset);
void checkFieldWriteVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t offset);
void checkMethodVis_c_Comp_ownerStart_U64_ownerLen_U64_mf_Func_offset_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen, Func mf, uint64_t offset);
long long placeIsMutable_c_Comp_id_U64(Comp* c, uint64_t id);
TypeInfo exprType_c_Comp_id_U64(Comp* c, uint64_t id);
uint64_t blockGiveExpr_c_Comp_blkId_U64(Comp* c, uint64_t blkId);
void addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen);
void addBindLocalCn_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64_cnum_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen, uint64_t cnum);
void genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen);
int64_t opEq(void);
int64_t opNe(void);
int64_t opLt(void);
int64_t opLe(void);
int64_t opGt(void);
int64_t opGe(void);
int64_t opAdd(void);
int64_t opSub(void);
int64_t opMul(void);
int64_t opDiv(void);
int64_t opRem(void);
int64_t opAnd(void);
int64_t opOr(void);
int64_t opNot(void);
int64_t opBitAnd(void);
int64_t opBitOr(void);
int64_t opBitXor(void);
int64_t opShl(void);
int64_t opShr(void);
int64_t opBitNot(void);
int64_t opAssign(void);
int64_t opAddAssign(void);
int64_t opSubAssign(void);
int64_t opMulAssign(void);
int64_t opDivAssign(void);
int64_t opRemAssign(void);
int64_t opBitAndAssign(void);
int64_t opBitOrAssign(void);
int64_t opBitXorAssign(void);
int64_t opShlAssign(void);
int64_t opShrAssign(void);
int64_t opCoalesce(void);
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
ConstInt mkConst_neg_Bool_mag_U64(long long neg, uint64_t mag);
ConstInt addConst_na_Bool_a_U64_nb_Bool_b_U64(long long na, uint64_t a, long long nb, uint64_t b);
ConstInt foldConst_c_Comp_id_U64(Comp* c, uint64_t id);
long long tiIsInt_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
void checkLitLeaf_c_Comp_value_U64_neg_Bool_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(Comp* c, uint64_t value, long long neg, uint64_t offset, long long isBool, uint64_t tyStart, uint64_t tyLen, uint64_t eKind, uint64_t eBits, long long eSgn);
void checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(Comp* c, uint64_t id, uint64_t eKind, uint64_t eBits, long long eSgn);
IntTy exprIntTy_c_Comp_id_U64(Comp* c, uint64_t id);
void checkArithNoCtx_c_Comp_lhs_U64_rhs_U64(Comp* c, uint64_t lhs, uint64_t rhs);
void checkLitTi_c_Comp_id_U64_ti_TypeInfo(Comp* c, uint64_t id, TypeInfo ti);
void checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(Comp* c, uint64_t id, uint64_t tyStart, uint64_t tyLen, long long isArray);
void checkLitArray_c_Comp_id_U64_elemStart_U64_elemLen_U64(Comp* c, uint64_t id, uint64_t elemStart, uint64_t elemLen);
long long typeIsTransitivelyUnique_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void checkFieldContagion_c_Comp(Comp* c);
void checkFieldDefaults_c_Comp(Comp* c);
void checkParamModes_c_Comp_params_AParam(Comp* c, Array_Param params);
void checkArrayElemsNotUnique_c_Comp(Comp* c);
void checkGenericUniqueArgs_c_Comp(Comp* c);
void checkAllParamModes_c_Comp(Comp* c);
void checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(Comp* c, uint64_t exprId, long long inoutOk);
void checkUniqueArgModes_c_Comp_args_AArg(Comp* c, Array_Arg args);
void checkCallArgs_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
void checkMethodArgs_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
TypeInfo makeFieldType_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen);
void checkMakeFields_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_ty_U64_fields_AMakeField(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t ty, Array_MakeField fields);
long long paramSelectorEq_c_Comp_a_AParam_b_AParam(Comp* c, Array_Param a, Array_Param b);
Bind assocBindingSpan_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen);
long long paramSelectorEqSubst_c_Comp_w_AParam_r_AParam_recvStart_U64_recvLen_U64(Comp* c, Array_Param w, Array_Param r, uint64_t recvStart, uint64_t recvLen);
long long witnessedHas_c_Comp_witnessed_AFunc_r_Func_recvStart_U64_recvLen_U64(Comp* c, Array_Func witnessed, Func r, uint64_t recvStart, uint64_t recvLen);
void checkConformances_c_Comp(Comp* c);
long long typeHasMember_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen);
void checkViaTargets_c_Comp(Comp* c);
long long builtinEqOrd_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen);
long long typeConformsTo_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen);
long long typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(Comp* c, uint64_t typeStart, uint64_t typeLen, PlewString traitName);
void checkFnBounds_c_Comp(Comp* c);
void checkMethodBounds_c_Comp(Comp* c);
long long isTypeParamOf_c_Comp_fnIdx_U64_start_U64_len_U64(Comp* c, uint64_t fnIdx, uint64_t start, uint64_t len);
long long boundProvidesMethod_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
long long boundHasTraitNamed_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_traitName_String(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, PlewString traitName);
void checkBoundsExpr_c_Comp_exprId_U64(Comp* c, uint64_t exprId);
void checkBoundsStmt_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId);
void checkBoundsBlock_c_Comp_blkId_U64(Comp* c, uint64_t blkId);
void checkGenericBodies_c_Comp(Comp* c);
long long sameLabels_c_Comp_a_AParam_b_AParam(Comp* c, Array_Param a, Array_Param b);
void checkOverloadCollisions_c_Comp(Comp* c);
long long methodWitnessesAConformance_c_Comp_recvStart_U64_recvLen_U64_mStart_U64_mLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t mStart, uint64_t mLen);
void checkImplOnBuiltin_c_Comp(Comp* c);
void checkMoveFnReceivers_c_Comp(Comp* c);
long long isExportedName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
void checkImports_c_Comp(Comp* c);
long long isImportedInto_c_Comp_mod_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t mod, uint64_t nameStart, uint64_t nameLen);
void checkUseVisibility_c_Comp(Comp* c);
void emitClosureCall_c_Comp_tyRef_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t tyRef, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
void emitClosureFieldCall_c_Comp_tyRef_U64_recv_U64_fieldStart_U64_fieldLen_U64_args_AArg(Comp* c, uint64_t tyRef, uint64_t recv, uint64_t fieldStart, uint64_t fieldLen, Array_Arg args);
void emitCaptureInit_c_Comp_e_CaptureEntry(Comp* c, CaptureEntry e);
void genArrayUserMethod_c_Comp_recv_U64_elemStart_U64_elemLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t elemStart, uint64_t elemLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
long long argIsElementTyped_c_Comp_mf_Func_i_U64(Comp* c, Func mf, uint64_t i);
long long makeProvides_c_Comp_fields_AMakeField_nameStart_U64_nameLen_U64(Comp* c, Array_MakeField fields, uint64_t nameStart, uint64_t nameLen);
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
TypeInfo forBindFieldType_c_Comp_et_TypeInfo_bd_Bind(Comp* c, TypeInfo et, Bind bd);
void addForStructBinds_c_Comp_et_TypeInfo_binds_ABind(Comp* c, TypeInfo et, Array_Bind binds);
void compileIterableFor_c_Comp_t_U64_varStart_U64_varLen_U64_iter_U64_body_U64_et_TypeInfo(Comp* c, uint64_t t, uint64_t varStart, uint64_t varLen, uint64_t iter, uint64_t body, TypeInfo et);
void genStmt_c_Comp_id_U64(Comp* c, uint64_t id);
void genBlock_c_Comp_id_U64(Comp* c, uint64_t id);
long long nameIsMain_c_Comp_f_Func(Comp* c, Func f);
long long isTraitName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long methodRecvIsTrait_c_Comp_f_Func(Comp* c, Func f);
long long methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t lo, uint64_t hi, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen);
Array_Bind providedCopyTypeParams_c_Comp_recvStart_U64_recvLen_U64_ownParams_ABind(Comp* c, uint64_t recvStart, uint64_t recvLen, Array_Bind ownParams);
void instantiateProvidedMethods_c_Comp(Comp* c);
uint64_t structIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long structNeedsCopy_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long structNeedsRelease_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
void emitDeinitProtos_c_Comp(Comp* c);
void emitStructCopyProto_c_Comp_si_U64(Comp* c, uint64_t si);
void emitStructShareProto_c_Comp_si_U64(Comp* c, uint64_t si);
long long typeInfoNeedsCopy_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
long long typeInfoNeedsRelease_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
long long fieldNeedsCopy_c_Comp_f_FieldDef(Comp* c, FieldDef f);
long long fieldNeedsRelease_c_Comp_f_FieldDef(Comp* c, FieldDef f);
long long enumNeedsCopy_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long enumNeedsRelease_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long monoEnumNeedsRelease_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
long long pointeeNeedsRelease_c_Comp_f_FieldDef(Comp* c, FieldDef f);
void emitBoxedFieldRetain_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64(Comp* c, FieldDef f, long long isEnum, uint64_t vStart, uint64_t vLen);
void emitBoxedFieldRelease_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64(Comp* c, FieldDef f, long long isEnum, uint64_t vStart, uint64_t vLen);
void emitStructReleaseProto_c_Comp_si_U64(Comp* c, uint64_t si);
void weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(Comp* c, PlewString obj, long long isEnum, uint64_t vStart, uint64_t vLen, FieldDef f);
void emitFieldAction_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64_mode_U64(Comp* c, FieldDef f, long long isEnum, uint64_t vStart, uint64_t vLen, uint64_t mode);
long long variantHasAction_c_Comp_v_Variant_mode_U64(Comp* c, Variant v, uint64_t mode);
void emitEnumCopyProto_c_Comp_ei_U64(Comp* c, uint64_t ei);
void emitEnumShareProto_c_Comp_ei_U64(Comp* c, uint64_t ei);
void emitEnumReleaseProto_c_Comp_ei_U64(Comp* c, uint64_t ei);
void emitEnumModeDef_c_Comp_ei_U64_mode_U64(Comp* c, uint64_t ei, uint64_t mode);
void emitStructModeDef_c_Comp_si_U64_mode_U64(Comp* c, uint64_t si, uint64_t mode);
void emitMonoModeProto_c_Comp_instRef_U64_mode_U64(Comp* c, uint64_t instRef, uint64_t mode);
void emitMonoModeDef_c_Comp_instRef_U64_isEnum_Bool_mode_U64(Comp* c, uint64_t instRef, long long isEnum, uint64_t mode);
long long monoStructNeedsRelease_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoFieldAction_c_Comp_ti_TypeInfo_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef_mode_U64(Comp* c, TypeInfo ti, long long isEnum, uint64_t vStart, uint64_t vLen, FieldDef f, uint64_t mode);
void emitTypeInfoCName_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
long long monoStructNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
long long monoEnumNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
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
long long isRawBufInst_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long isPromiseInst_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long isIndirectContainer_c_Comp_nStart_U64_nLen_U64(Comp* c, uint64_t nStart, uint64_t nLen);
long long isTransparentContainer_c_Comp_nStart_U64_nLen_U64(Comp* c, uint64_t nStart, uint64_t nLen);
uint64_t concreteEnumIndex_c_Comp_nStart_U64_nLen_U64(Comp* c, uint64_t nStart, uint64_t nLen);
long long containsU64_xs_AU64_v_U64(Array_U64 xs, uint64_t v);
long long nameReachesOwner_c_Comp_nStart_U64_nLen_U64_args_AU64_tStart_U64_tLen_U64_visited_AU64(Comp* c, uint64_t nStart, uint64_t nLen, Array_U64 args, uint64_t tStart, uint64_t tLen, Array_U64* visited);
long long typeRefReachesOwner_c_Comp_ref_U64_tStart_U64_tLen_U64_visited_AU64(Comp* c, uint64_t ref, uint64_t tStart, uint64_t tLen, Array_U64* visited);
long long fieldReachesOwner_c_Comp_f_FieldDef_tStart_U64_tLen_U64_visited_AU64(Comp* c, FieldDef f, uint64_t tStart, uint64_t tLen, Array_U64* visited);
long long fieldIsBoxed_c_Comp_f_FieldDef(Comp* c, FieldDef f);
FieldDef noField(void);
FieldDef findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen);
void genBoxCell_c_Comp_fd_FieldDef_valueId_U64(Comp* c, FieldDef fd, uint64_t valueId);
void markBoxedFields_c_Comp(Comp* c);
long long isGenericEnumInst_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long typeRefEq_c_Comp_a_U64_b_U64(Comp* c, uint64_t a, uint64_t b);
void emitMangle_c_Comp_ref_U64(Comp* c, uint64_t ref);
void appendMangle_c_Comp_ref_U64(Comp* c, uint64_t ref);
Bind appendMangleSpan_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long sameMangle_c_Comp_refA_U64_refB_U64(Comp* c, uint64_t refA, uint64_t refB);
long long isCompoundType_c_Comp_ref_U64(Comp* c, uint64_t ref);
void emitConcreteCType_c_Comp_ref_U64(Comp* c, uint64_t ref);
void emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(Comp* c, uint64_t ref, Array_Bind params, Array_U64 args);
uint64_t resolveTy_c_Comp_tyRef_U64(Comp* c, uint64_t tyRef);
void genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(Comp* c, uint64_t tyRef, uint64_t fallStart, uint64_t fallLen, long long isArray);
long long isTypeParamName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len);
long long tyRefIsGround_c_Comp_ref_U64(Comp* c, uint64_t ref);
void ensureArrayElemDeps_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef);
void registerArrayElemRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef);
uint64_t groundTypeRef_c_Comp_ref_U64(Comp* c, uint64_t ref);
uint64_t groundUnderInst_c_Comp_instRef_U64_tyRef_U64(Comp* c, uint64_t instRef, uint64_t tyRef);
uint64_t simpleTypeRef_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t assocItemRef_c_Comp_recvStart_U64_recvLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen);
void setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t recvInstRef);
void clearSelfItemEnv_c_Comp(Comp* c);
void scanType_c_Comp_ref_U64(Comp* c, uint64_t ref);
void scanGenInstFields_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void collectGenInsts_c_Comp(Comp* c);
TypeInfo typeInfoOfRef_c_Comp_ref_U64(Comp* c, uint64_t ref);
TypeInfo iterableItemInfo_c_Comp_et_TypeInfo(Comp* c, TypeInfo et);
TypeInfo substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(Comp* c, uint64_t instRef, Array_Bind params, uint64_t tyRef);
TypeInfo genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t fieldStart, uint64_t fieldLen);
TypeInfo genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen);
void genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen);
void emitMonoForward_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoStruct_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
void emitMonoEnum_c_Comp_instRef_U64(Comp* c, uint64_t instRef);
long long methodMatchesInst_c_Comp_f_Func_instRef_U64(Comp* c, Func f, uint64_t instRef);
void emitMonoMethod_c_Comp_fi_U64_instRef_U64_proto_Bool(Comp* c, uint64_t fi, uint64_t instRef, long long proto);
uint64_t arrayInstRef_c_Comp_ae_Bind(Comp* c, Bind ae);
long long isRegisteredGenInst_c_Comp_ref_U64(Comp* c, uint64_t ref);
long long providedRetReachable_c_Comp_mf_Func_recvInstRef_U64(Comp* c, Func mf, uint64_t recvInstRef);
void emitArrayMethods_c_Comp_proto_Bool(Comp* c, long long proto);
void emitMonoMethods_c_Comp_proto_Bool(Comp* c, long long proto);
long long isGenericFreeFn_c_Comp_fi_U64(Comp* c, uint64_t fi);
uint64_t findOrAddTypeRef_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
uint64_t closureFnTypeRef_c_Comp_params_AParam_retTy_U64(Comp* c, Array_Param params, uint64_t retTy);
uint64_t unifyTypeParam_c_Comp_paramRef_U64_argRef_U64_tpStart_U64_tpLen_U64(Comp* c, uint64_t paramRef, uint64_t argRef, uint64_t tpStart, uint64_t tpLen);
uint64_t tyRefOfInfo_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti);
uint64_t argArrayElemRef_c_Comp_argExpr_U64(Comp* c, uint64_t argExpr);
Array_U64 inferFnArgs_c_Comp_f_Func_args_AArg(Comp* c, Func f, Array_Arg args);
long long fnArgsAllGround_c_Comp_args_AU64(Comp* c, Array_U64 args);
long long fnInstExists_c_Comp_fnIdx_U64_args_AU64(Comp* c, uint64_t fnIdx, Array_U64 args);
void registerCallInst_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
void registerMethodInst_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
uint64_t recvParamCount_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
void writeMethodInstSuffixFrom_c_Comp_typeArgs_AU64_startIdx_U64(Comp* c, Array_U64 typeArgs, uint64_t startIdx);
long long captureSupported_c_Comp_lo_Local(Comp* c, Local lo);
void recordCapture_c_Comp_closureId_U64_localIdx_U64(Comp* c, uint64_t closureId, uint64_t localIdx);
void scanExprInsts_c_Comp_exprId_U64(Comp* c, uint64_t exprId);
void scanAddArmBinds_c_Comp_a_MatchArm_scrutTi_TypeInfo(Comp* c, MatchArm a, TypeInfo scrutTi);
void scanStmtInsts_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId);
void scanBlockInsts_c_Comp_blkId_U64(Comp* c, uint64_t blkId);
void collectFnInsts_c_Comp(Comp* c);
void emitMonoFn_c_Comp_instIdx_U64_proto_Bool(Comp* c, uint64_t instIdx, long long proto);
void emitMonoFns_c_Comp_proto_Bool(Comp* c, long long proto);
long long emitArrayIntrinsic_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
void emitArrayElemValue_c_Comp_argExpr_U64_arrStart_U64_arrLen_U64(Comp* c, uint64_t argExpr, uint64_t arrStart, uint64_t arrLen);
long long emitRawIntrinsic_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args);
void emitElemCType_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
long long isRawIntrinsicName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
long long isArrayIntrinsicName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen);
void wPA_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
void genArrayRuntimeFns_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
long long isU8Elem_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
long long elemIsRef_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen);
long long skipArrayElem_c_Comp_ae_Bind(Comp* c, Bind ae);
void genU8ArrayTypedef(void);
void genU8ArrayRuntime(void);
long long hasAnyAsync_c_Comp(Comp* c);
void emitAsyncRuntime_c_Comp(Comp* c);
void writeAsyncFrameName_c_Comp_f_Func(Comp* c, Func f);
void rejectAsyncUnsupported_c_Comp_blockId_U64(Comp* c, uint64_t blockId);
void collectAsyncFields_c_Comp_blockId_U64(Comp* c, uint64_t blockId);
void collectAsyncMatchBinds_c_Comp_scrutRef_U64_genericMatch_Bool_arm_MatchArm(Comp* c, uint64_t scrutRef, long long genericMatch, MatchArm arm);
void emitAsyncSuspend_c_Comp_operandId_U64(Comp* c, uint64_t operandId);
uint64_t nextAsyncVar_c_Comp(Comp* c);
void genAsyncLet_c_Comp_nameStart_U64_nameLen_U64_effStart_U64_effLen_U64_effArr_Bool_effTy_U64_init_U64_mutable_Bool(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t effStart, uint64_t effLen, long long effArr, uint64_t effTy, uint64_t init, long long mutable);
void genAsyncReturn_c_Comp_value_U64_hasValue_Bool(Comp* c, uint64_t value, long long hasValue);
void emitAsyncFrameStruct_c_Comp_fi_U64(Comp* c, uint64_t fi);
void emitAsyncDecls_c_Comp(Comp* c);
void genAsyncFunc_c_Comp_fi_U64(Comp* c, uint64_t fi);
uint64_t countAsyncAwaits_c_Comp_blockId_U64(Comp* c, uint64_t blockId);
long long exprIsAwait_c_Comp_id_U64(Comp* c, uint64_t id);
long long isPathTokKind_k_Kind(Kind k);
Array_Bind collectParts_rootBytes_AU8_toks_ATok(Array_U8 rootBytes, Array_Tok toks);
uint64_t stripParents_path_AU8_baseLen_U64_n_U64(Array_U8 path, uint64_t baseLen, uint64_t n);
Array_U8 resolveImport_src_AU8_pStart_U64_pLen_U64_importer_AU8_baseLen_U64_srcRoot_AU8_srcRootLen_U64_stdRoot_AU8_stdRootLen_U64(Array_U8 src, uint64_t pStart, uint64_t pLen, Array_U8 importer, uint64_t baseLen, Array_U8 srcRoot, uint64_t srcRootLen, Array_U8 stdRoot, uint64_t stdRootLen);
void appendBytes_into_AU8_from_AU8(Array_U8* into, Array_U8 from);
Array_U8 extractSpan_buf_AU8_start_U64_len_U64(Array_U8 buf, uint64_t start, uint64_t len);
uint64_t dirPrefixLen_path_AU8(Array_U8 path);
Array_U8 computeStdRoot_arg0_AU8(Array_U8 arg0);
Array_U8 findSrcRoot_entry_AU8(Array_U8 entry);
long long pathSeen_buf_AU8_loaded_ABind_path_AU8(Array_U8 buf, Array_Bind loaded, Array_U8 path);
void assert_cond_Bool_message_String(long long cond, PlewString message);
long long String_isEmpty(PlewString self);
unsigned char digitByteI_d_I64(int64_t d);
unsigned char digitByteU_d_U64(uint64_t d);
PlewString I64_format_format_String(int64_t self, PlewString format);
PlewString U64_format_format_String(uint64_t self, PlewString format);
PlewString I8_format_format_String(int8_t self, PlewString format);
PlewString I16_format_format_String(int16_t self, PlewString format);
PlewString I32_format_format_String(int32_t self, PlewString format);
PlewString U8_format_format_String(unsigned char self, PlewString format);
PlewString U16_format_format_String(uint16_t self, PlewString format);
PlewString U32_format_format_String(uint32_t self, PlewString format);
PlewString Bool_format_format_String(long long self, PlewString format);
void Array_U8_append_value_T(Array_U8* self, unsigned char value);
unsigned char Array_U8_get_i_U64(Array_U8 self, uint64_t i);
void Array_U8_set_i_U64_value_T(Array_U8* self, uint64_t i, unsigned char value);
void Array_Bind_append_value_T(Array_Bind* self, Bind value);
Bind Array_Bind_get_i_U64(Array_Bind self, uint64_t i);
void Array_Bind_set_i_U64_value_T(Array_Bind* self, uint64_t i, Bind value);
void Array_Tok_append_value_T(Array_Tok* self, Tok value);
Tok Array_Tok_get_i_U64(Array_Tok self, uint64_t i);
void Array_Tok_set_i_U64_value_T(Array_Tok* self, uint64_t i, Tok value);
void Array_U64_append_value_T(Array_U64* self, uint64_t value);
uint64_t Array_U64_get_i_U64(Array_U64 self, uint64_t i);
void Array_U64_set_i_U64_value_T(Array_U64* self, uint64_t i, uint64_t value);
void Array_Arg_append_value_T(Array_Arg* self, Arg value);
Arg Array_Arg_get_i_U64(Array_Arg self, uint64_t i);
void Array_Arg_set_i_U64_value_T(Array_Arg* self, uint64_t i, Arg value);
void Array_MakeField_append_value_T(Array_MakeField* self, MakeField value);
MakeField Array_MakeField_get_i_U64(Array_MakeField self, uint64_t i);
void Array_MakeField_set_i_U64_value_T(Array_MakeField* self, uint64_t i, MakeField value);
void Array_MatchArm_append_value_T(Array_MatchArm* self, MatchArm value);
MatchArm Array_MatchArm_get_i_U64(Array_MatchArm self, uint64_t i);
void Array_MatchArm_set_i_U64_value_T(Array_MatchArm* self, uint64_t i, MatchArm value);
void Array_Param_append_value_T(Array_Param* self, Param value);
Param Array_Param_get_i_U64(Array_Param self, uint64_t i);
void Array_Param_set_i_U64_value_T(Array_Param* self, uint64_t i, Param value);
void Array_FieldDef_append_value_T(Array_FieldDef* self, FieldDef value);
FieldDef Array_FieldDef_get_i_U64(Array_FieldDef self, uint64_t i);
void Array_FieldDef_set_i_U64_value_T(Array_FieldDef* self, uint64_t i, FieldDef value);
void Array_Func_append_value_T(Array_Func* self, Func value);
Func Array_Func_get_i_U64(Array_Func self, uint64_t i);
void Array_Func_set_i_U64_value_T(Array_Func* self, uint64_t i, Func value);
void Array_Variant_append_value_T(Array_Variant* self, Variant value);
Variant Array_Variant_get_i_U64(Array_Variant self, uint64_t i);
void Array_Variant_set_i_U64_value_T(Array_Variant* self, uint64_t i, Variant value);
void Array_Expr_append_value_T(Array_Expr* self, Expr value);
Expr Array_Expr_get_i_U64(Array_Expr self, uint64_t i);
void Array_Expr_set_i_U64_value_T(Array_Expr* self, uint64_t i, Expr value);
void Array_Stmt_append_value_T(Array_Stmt* self, Stmt value);
Stmt Array_Stmt_get_i_U64(Array_Stmt self, uint64_t i);
void Array_Stmt_set_i_U64_value_T(Array_Stmt* self, uint64_t i, Stmt value);
void Array_Block_append_value_T(Array_Block* self, Block value);
Block Array_Block_get_i_U64(Array_Block self, uint64_t i);
void Array_Block_set_i_U64_value_T(Array_Block* self, uint64_t i, Block value);
void Array_StructDef_append_value_T(Array_StructDef* self, StructDef value);
StructDef Array_StructDef_get_i_U64(Array_StructDef self, uint64_t i);
void Array_StructDef_set_i_U64_value_T(Array_StructDef* self, uint64_t i, StructDef value);
void Array_EnumDef_append_value_T(Array_EnumDef* self, EnumDef value);
EnumDef Array_EnumDef_get_i_U64(Array_EnumDef self, uint64_t i);
void Array_EnumDef_set_i_U64_value_T(Array_EnumDef* self, uint64_t i, EnumDef value);
void Array_TraitDef_append_value_T(Array_TraitDef* self, TraitDef value);
TraitDef Array_TraitDef_get_i_U64(Array_TraitDef self, uint64_t i);
void Array_TraitDef_set_i_U64_value_T(Array_TraitDef* self, uint64_t i, TraitDef value);
void Array_Conform_append_value_T(Array_Conform* self, Conform value);
Conform Array_Conform_get_i_U64(Array_Conform self, uint64_t i);
void Array_Conform_set_i_U64_value_T(Array_Conform* self, uint64_t i, Conform value);
void Array_MethodAlias_append_value_T(Array_MethodAlias* self, MethodAlias value);
MethodAlias Array_MethodAlias_get_i_U64(Array_MethodAlias self, uint64_t i);
void Array_MethodAlias_set_i_U64_value_T(Array_MethodAlias* self, uint64_t i, MethodAlias value);
void Array_DeriveReq_append_value_T(Array_DeriveReq* self, DeriveReq value);
DeriveReq Array_DeriveReq_get_i_U64(Array_DeriveReq self, uint64_t i);
void Array_DeriveReq_set_i_U64_value_T(Array_DeriveReq* self, uint64_t i, DeriveReq value);
void Array_FuncBound_append_value_T(Array_FuncBound* self, FuncBound value);
FuncBound Array_FuncBound_get_i_U64(Array_FuncBound self, uint64_t i);
void Array_FuncBound_set_i_U64_value_T(Array_FuncBound* self, uint64_t i, FuncBound value);
void Array_TypeRef_append_value_T(Array_TypeRef* self, TypeRef value);
TypeRef Array_TypeRef_get_i_U64(Array_TypeRef self, uint64_t i);
void Array_TypeRef_set_i_U64_value_T(Array_TypeRef* self, uint64_t i, TypeRef value);
void Array_FnInst_append_value_T(Array_FnInst* self, FnInst value);
FnInst Array_FnInst_get_i_U64(Array_FnInst self, uint64_t i);
void Array_FnInst_set_i_U64_value_T(Array_FnInst* self, uint64_t i, FnInst value);
void Array_CaptureEntry_append_value_T(Array_CaptureEntry* self, CaptureEntry value);
CaptureEntry Array_CaptureEntry_get_i_U64(Array_CaptureEntry self, uint64_t i);
void Array_CaptureEntry_set_i_U64_value_T(Array_CaptureEntry* self, uint64_t i, CaptureEntry value);
void Array_Local_append_value_T(Array_Local* self, Local value);
Local Array_Local_get_i_U64(Array_Local self, uint64_t i);
void Array_Local_set_i_U64_value_T(Array_Local* self, uint64_t i, Local value);
void Array_AssocBinding_append_value_T(Array_AssocBinding* self, AssocBinding value);
AssocBinding Array_AssocBinding_get_i_U64(Array_AssocBinding self, uint64_t i);
void Array_AssocBinding_set_i_U64_value_T(Array_AssocBinding* self, uint64_t i, AssocBinding value);
void Array_PatInfo_append_value_T(Array_PatInfo* self, PatInfo value);
PatInfo Array_PatInfo_get_i_U64(Array_PatInfo self, uint64_t i);
void Array_PatInfo_set_i_U64_value_T(Array_PatInfo* self, uint64_t i, PatInfo value);
int main(int argc, char** argv) {
    plew_argc = argc; plew_argv = argv;
    Array_U8 combined = Array_U8_new();
    Array_Bind moduleRanges = Array_Bind_new();
    uint64_t nextModuleId = 1;
    if (plew_argCount() > 1) {
    PlewString rootPath = plew_argAt(1);
    Array_U8 entryBytes = Array_U8_share(({ PlewString __s = rootPath; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; }));
    if (plew_fileExists(Array_U8_share(entryBytes))) {
    }
    else {
    plew_eprint((PlewString){"plewc: error: cannot open source file: ", 39});
    plew_eprint(rootPath);
    plew_eprint((PlewString){"\n", 1});
    plew_exit(1);
    }
    Array_U8 pathBuf = Array_U8_new();
    Array_Bind loaded = Array_Bind_new();
    Array_U8 srcRoot = findSrcRoot_entry_AU8(Array_U8_share(entryBytes));
    Array_U8 stdRoot = computeStdRoot_arg0_AU8(Array_U8_share(({ PlewString __s = plew_argAt(0); Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; })));
    uint64_t es = (long long)((pathBuf).count);
    appendBytes_into_AU8_from_AU8(&(pathBuf), Array_U8_share(entryBytes));
    Array_Bind_append_value_T(&(loaded), (Bind){.nameStart = es, .nameLen = (long long)((entryBytes).count), .fieldStart = 0, .fieldLen = (long long)((entryBytes).count)});
    uint64_t qi = 0;
    while (qi < (long long)((loaded).count)) {
    Bind ent = Array_Bind_get(loaded, (long long)(qi));
    qi = ({ uint64_t __ov; if (__builtin_add_overflow((qi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t moduleId = ent.fieldStart;
    Array_U8 path = extractSpan_buf_AU8_start_U64_len_U64(Array_U8_share(pathBuf), ent.nameStart, ent.nameLen);
    PlewString src = plew_readFileBytes(Array_U8_share(path));
    Array_U8 sb = Array_U8_share(({ PlewString __s = src; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; }));
    if ((long long)((combined).count) > 0) {
    Array_U8_append_value_T(&(combined), 10);
    }
    uint64_t rangeStart = (long long)((combined).count);
    appendBytes_into_AU8_from_AU8(&(combined), Array_U8_share(sb));
    Array_Bind_append_value_T(&(moduleRanges), (Bind){.nameStart = rangeStart, .nameLen = ({ uint64_t __ov; if (__builtin_sub_overflow(((long long)((combined).count)), (rangeStart), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), .fieldStart = moduleId, .fieldLen = 0});
    Lexer lxp = (Lexer){.bytes = Array_U8_share(sb), .pos = 0, .toks = Array_Tok_new(), .depth = 0};
    lex_lx_Lexer(&(lxp));
    Array_Bind incs = collectParts_rootBytes_AU8_toks_ATok(Array_U8_share(sb), Array_Tok_share(lxp.toks));
    uint64_t baseLen = dirPrefixLen_path_AU8(Array_U8_share(path));
    uint64_t pj = 0;
    while (pj < (long long)((incs).count)) {
    Bind pb = Array_Bind_get(incs, (long long)(pj));
    Array_U8 childPath = resolveImport_src_AU8_pStart_U64_pLen_U64_importer_AU8_baseLen_U64_srcRoot_AU8_srcRootLen_U64_stdRoot_AU8_stdRootLen_U64(Array_U8_share(sb), pb.nameStart, pb.nameLen, Array_U8_share(path), baseLen, Array_U8_share(srcRoot), (long long)((srcRoot).count), Array_U8_share(stdRoot), (long long)((stdRoot).count));
    if ((long long)((childPath).count) == 0) {
    }
    else {
    if (pathSeen_buf_AU8_loaded_ABind_path_AU8(Array_U8_share(pathBuf), Array_Bind_share(loaded), Array_U8_share(childPath))) {
    }
    else {
    uint64_t childModule = moduleId;
    if (pb.fieldStart == 1) {
    childModule = nextModuleId;
    nextModuleId = ({ uint64_t __ov; if (__builtin_add_overflow((nextModuleId), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t cs = (long long)((pathBuf).count);
    appendBytes_into_AU8_from_AU8(&(pathBuf), Array_U8_share(childPath));
    Array_Bind_append_value_T(&(loaded), (Bind){.nameStart = cs, .nameLen = (long long)((childPath).count), .fieldStart = childModule, .fieldLen = (long long)((childPath).count)});
    }
    }
    pj = ({ uint64_t __ov; if (__builtin_add_overflow((pj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_U8_release(childPath);
    }
    Array_Bind_release(incs);
    Lexer_release(lxp);
    Array_U8_release(sb);
    Array_U8_release(path);
    }
    Array_U8_release(stdRoot);
    Array_U8_release(srcRoot);
    Array_Bind_release(loaded);
    Array_U8_release(pathBuf);
    Array_U8_release(entryBytes);
    }
    else {
    PlewString s = plew_readStdin();
    uint64_t rangeStart = (long long)((combined).count);
    appendBytes_into_AU8_from_AU8(&(combined), Array_U8_share(({ PlewString __s = s; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; })));
    Array_Bind_append_value_T(&(moduleRanges), (Bind){.nameStart = rangeStart, .nameLen = ({ uint64_t __ov; if (__builtin_sub_overflow(((long long)((combined).count)), (rangeStart), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), .fieldStart = 0, .fieldLen = 0});
    }
    Array_U8 prelPath = Array_U8_new();
    appendBytes_into_AU8_from_AU8(&(prelPath), computeStdRoot_arg0_AU8(Array_U8_share(({ PlewString __s = plew_argAt(0); Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; }))));
    appendBytes_into_AU8_from_AU8(&(prelPath), Array_U8_share(({ PlewString __s = (PlewString){"Prelude.pw", 10}; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; })));
    if (plew_fileExists(Array_U8_share(prelPath))) {
    PlewString prelSrc = plew_readFileBytes(Array_U8_share(prelPath));
    if ((long long)((combined).count) > 0) {
    Array_U8_append_value_T(&(combined), 10);
    }
    uint64_t prelStart = (long long)((combined).count);
    appendBytes_into_AU8_from_AU8(&(combined), Array_U8_share(({ PlewString __s = prelSrc; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; })));
    Array_Bind_append_value_T(&(moduleRanges), (Bind){.nameStart = prelStart, .nameLen = ({ uint64_t __ov; if (__builtin_sub_overflow(((long long)((combined).count)), (prelStart), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), .fieldStart = nextModuleId, .fieldLen = 0});
    nextModuleId = ({ uint64_t __ov; if (__builtin_add_overflow((nextModuleId), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    appendBytes_into_AU8_from_AU8(&(combined), Array_U8_share(({ PlewString __s = (PlewString){"\n// kwSpan builtins: String U8 U64 Bool Array\n", 46}; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; })));
    Lexer lx = (Lexer){.bytes = Array_U8_share(combined), .pos = 0, .toks = Array_Tok_new(), .depth = 0};
    lex_lx_Lexer(&(lx));
    Comp c = (Comp){.bytes = Array_U8_share(combined), .toks = Array_Tok_share(lx.toks), .pos = 0, .exprs = Array_Expr_new(), .stmts = Array_Stmt_new(), .blocks = Array_Block_new(), .funcs = Array_Func_new(), .structs = Array_StructDef_new(), .enums = Array_EnumDef_new(), .traits = Array_TraitDef_new(), .conforms = Array_Conform_new(), .methodAliases = Array_MethodAlias_new(), .derives = Array_DeriveReq_new(), .pendingDerives = Array_Bind_new(), .funcBounds = Array_FuncBound_new(), .curCheckFn = 0, .curWitnessed = Array_Func_new(), .curWhereTraits = Array_Bind_new(), .types = Array_TypeRef_new(), .genInsts = Array_U64_new(), .fnInsts = Array_FnInst_new(), .fnTypes = Array_U64_new(), .fnThunks = Array_U64_new(), .captures = Array_CaptureEntry_new(), .curClosureId = 0, .curInClosure = 0, .curCaptureMark = 0, .arrayElems = Array_Bind_new(), .locals = Array_Local_new(), .tmp = 0, .curIsMain = 0, .curRetVoid = 0, .curRetStart = 0, .curRetLen = 0, .curRetIsArray = 0, .curRetTy = 0, .curHasRecv = 0, .curRecvStart = 0, .curRecvLen = 0, .curSelfInout = 0, .curSelfMove = 0, .curTypeParams = Array_Bind_new(), .curTypeArgs = Array_U64_new(), .curRecvInstRef = 0, .curGiveTmp = 0, .curLoopMark = 0, .curBranchBase = 0, .deinits = Array_Bind_new(), .curAsync = 0, .asyncState = 0, .curAsyncFn = 0, .asyncVarSeq = 0, .moduleRanges = Array_Bind_share(moduleRanges), .exports = Array_Bind_new(), .imports = Array_Bind_new(), .curImplBoundParams = Array_Bind_new(), .curImplBoundTraits = Array_Bind_new(), .boxedFields = Array_U64_new(), .curSelfRef = 0, .curItemRef = 0, .assocBindings = Array_AssocBinding_new()};
    Array_TypeRef_append_value_T(&(c.types), (TypeRef){.nameStart = 0, .nameLen = 0, .args = Array_U64_new()});
    parseProgram_c_Comp(&(c));
    synthesizeDerives_c_Comp(&(c));
    instantiateProvidedMethods_c_Comp(&(c));
    markBoxedFields_c_Comp(&(c));
    checkFieldContagion_c_Comp(&(c));
    checkFieldDefaults_c_Comp(&(c));
    checkAllParamModes_c_Comp(&(c));
    checkArrayElemsNotUnique_c_Comp(&(c));
    checkConformances_c_Comp(&(c));
    checkOverloadCollisions_c_Comp(&(c));
    checkImplOnBuiltin_c_Comp(&(c));
    checkMoveFnReceivers_c_Comp(&(c));
    checkImports_c_Comp(&(c));
    checkUseVisibility_c_Comp(&(c));
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
    plew_write((PlewString){"__attribute__((unused)) static void* plew_rawbuf_alloc(long long elemSize, long long cap) { long long* h = (long long*)malloc(2 * sizeof(long long) + (size_t)(elemSize * cap)); h[0] = cap; h[1] = 1; return (void*)(h + 2); }\n", 224});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_rawbuf_cap(void* p) { return p ? ((long long*)p)[-2] : 0; }\n", 106});
    plew_write((PlewString){"__attribute__((unused)) static int plew_rawbuf_is_unique(void* p) { return p ? (((long long*)p)[-1] == 1) : 1; }\n", 113});
    plew_write((PlewString){"__attribute__((unused)) static void* plew_rawbuf_share(void* p) { if (p) ((long long*)p)[-1] += 1; return p; }\n", 111});
    plew_write((PlewString){"__attribute__((unused)) static void plew_rawbuf_release(void* p) { if (p && (--(((long long*)p)[-1])) == 0) free(((long long*)p) - 2); }\n", 137});
    plew_write((PlewString){"typedef struct { void* fn; void* env; long long* rc; void (*drop)(void*); } PlewClosure;\n", 89});
    plew_write((PlewString){"__attribute__((unused)) static PlewClosure plew_closure_share(PlewClosure cl) { plew_arc_retain(cl.rc); return cl; }\n", 117});
    plew_write((PlewString){"__attribute__((unused)) static void plew_closure_release(PlewClosure cl) { if (cl.rc && (--(*cl.rc)) == 0) { if (cl.drop) cl.drop(cl.env); free((void*)cl.rc); } }\n", 163});
    plew_write((PlewString){"__attribute__((unused)) static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (long long i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }\n", 197});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_readStdin(void) { size_t cap = 4096, len = 0; char* buf = (char*)malloc(cap); int ch; while ((ch = getchar()) != EOF) { if (len + 1 >= cap) { cap *= 2; buf = (char*)realloc(buf, cap); } buf[len++] = (char)ch; } PlewString s; s.data = buf; s.len = (long long)len; return s; }\n", 322});
    plew_write((PlewString){"__attribute__((unused)) static void plew_write(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stdout); }\n", 107});
    plew_write((PlewString){"__attribute__((unused)) static void plew_writeByte(unsigned char b) { putchar((int)b); }\n", 89});
    plew_write((PlewString){"__attribute__((noreturn)) static void plew_exit(long long code) { exit((int)code); }\n", 85});
    plew_write((PlewString){"__attribute__((unused)) static void plew_eprint(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stderr); }\n", 108});
    plew_write((PlewString){"__attribute__((noreturn)) static void plew_panic(PlewString m) { fputs(\"panic: \", stderr); fwrite(m.data, 1, (size_t)m.len, stderr); fputc('\\n', stderr); exit(1); }\n", 165});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_div(long long a, long long b) { if (b == 0) plew_panic((PlewString){\"division by zero\", 16}); if (b == -1 && a == INT64_MIN) plew_panic((PlewString){\"integer overflow\", 16}); return a / b; }\n", 237});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_mod(long long a, long long b) { if (b == 0) plew_panic((PlewString){\"remainder by zero\", 17}); if (b == -1) return 0; return a % b; }\n", 180});
    plew_write((PlewString){"static int plew_argc = 0;\nstatic char** plew_argv = 0;\n", 55});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_argCount(void) { return (long long)plew_argc; }\n", 94});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_argAt(long long i) { PlewString s; if (i < 0 || i >= plew_argc) { s.data = \"\"; s.len = 0; return s; } s.data = plew_argv[i]; s.len = (long long)strlen(plew_argv[i]); return s; }\n", 225});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_readFile(PlewString path) { FILE* f = fopen(path.data, \"rb\"); PlewString s; if (!f) { s.data = \"\"; s.len = 0; return s; } fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET); char* buf = (char*)malloc((size_t)sz + 1); size_t n = fread(buf, 1, (size_t)sz, f); fclose(f); buf[n] = 0; s.data = buf; s.len = (long long)n; return s; }\n", 390});
    emitAsyncRuntime_c_Comp(&(c));
    uint64_t si = 0;
    while (si < (long long)((c.structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get(c.structs, (long long)(si)));
    if (((long long)((s.typeParams).count) > 0) || s.isExtern) {
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
    while (ei < (long long)((c.enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get(c.enums, (long long)(ei)));
    if ((long long)((e.typeParams).count) > 0) {
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
    while (mfi < (long long)((c.genInsts).count)) {
    emitMonoForward_c_Comp_instRef_U64(&(c), Array_U64_get(c.genInsts, (long long)(mfi)));
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t afi = 0;
    while (afi < (long long)((c.genInsts).count)) {
    TypeRef aft = TypeRef_share(Array_TypeRef_get(c.types, (long long)(Array_U64_get(c.genInsts, (long long)(afi)))));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(c.bytes), aft.nameStart, aft.nameLen, (PlewString){"Array", 5})) {
    emitMonoStruct_c_Comp_instRef_U64(&(c), Array_U64_get(c.genInsts, (long long)(afi)));
    }
    afi = ({ uint64_t __ov; if (__builtin_add_overflow((afi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeRef_release(aft);
    }
    genU8ArrayTypedef();
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_readFileBytes(Array_U8 p) { char* path = (char*)malloc((size_t)p.count + 1); memcpy(path, p.data, (size_t)p.count); path[p.count] = 0; PlewString r = plew_readFile((PlewString){path, p.count}); free(path); return r; }\n", 265});
    plew_write((PlewString){"__attribute__((unused)) static long long plew_fileExists(Array_U8 p) { char* path = (char*)malloc((size_t)p.count + 1); memcpy(path, p.data, (size_t)p.count); path[p.count] = 0; FILE* f = fopen(path, \"rb\"); free(path); if (f) { fclose(f); return 1; } return 0; }\n", 263});
    plew_write((PlewString){"__attribute__((unused)) static PlewString plew_stringFromBytes(Array_U8 p) { char* buf = (char*)malloc((size_t)p.count + 1); memcpy(buf, p.data, (size_t)p.count); buf[p.count] = 0; PlewString s; s.data = buf; s.len = p.count; return s; }\n", 238});
    uint64_t ej = 0;
    while (ej < (long long)((c.enums).count)) {
    EnumDef ge = EnumDef_share(Array_EnumDef_get(c.enums, (long long)(ej)));
    if ((long long)((ge.typeParams).count) > 0) {
    }
    else {
    genEnumDef_c_Comp_ei_U64(&(c), ej);
    }
    ej = ({ uint64_t __ov; if (__builtin_add_overflow((ej), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(ge);
    }
    uint64_t sj = 0;
    while (sj < (long long)((c.structs).count)) {
    StructDef gs = StructDef_share(Array_StructDef_get(c.structs, (long long)(sj)));
    if (((long long)((gs.typeParams).count) > 0) || gs.isExtern) {
    }
    else {
    genStructDef_c_Comp_si_U64(&(c), sj);
    }
    sj = ({ uint64_t __ov; if (__builtin_add_overflow((sj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(gs);
    }
    uint64_t mbi = 0;
    while (mbi < (long long)((c.genInsts).count)) {
    TypeRef mbt = TypeRef_share(Array_TypeRef_get(c.types, (long long)(Array_U64_get(c.genInsts, (long long)(mbi)))));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(c.bytes), mbt.nameStart, mbt.nameLen, (PlewString){"Array", 5})) {
    }
    else {
    if (isGenericEnumInst_c_Comp_ref_U64(&(c), Array_U64_get(c.genInsts, (long long)(mbi)))) {
    emitMonoEnum_c_Comp_instRef_U64(&(c), Array_U64_get(c.genInsts, (long long)(mbi)));
    }
    else {
    emitMonoStruct_c_Comp_instRef_U64(&(c), Array_U64_get(c.genInsts, (long long)(mbi)));
    }
    }
    mbi = ({ uint64_t __ov; if (__builtin_add_overflow((mbi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeRef_release(mbt);
    }
    emitDeinitProtos_c_Comp(&(c));
    uint64_t spp = 0;
    while (spp < (long long)((c.structs).count)) {
    StructDef cps = StructDef_share(Array_StructDef_get(c.structs, (long long)(spp)));
    if (((long long)((cps.typeParams).count) > 0) || cps.isExtern) {
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
    uint64_t epp = 0;
    while (epp < (long long)((c.enums).count)) {
    EnumDef cpe = EnumDef_share(Array_EnumDef_get(c.enums, (long long)(epp)));
    if ((long long)((cpe.typeParams).count) > 0) {
    }
    else {
    if (enumNeedsCopy_c_Comp_start_U64_len_U64(&(c), cpe.nameStart, cpe.nameLen)) {
    emitEnumCopyProto_c_Comp_ei_U64(&(c), epp);
    emitEnumShareProto_c_Comp_ei_U64(&(c), epp);
    }
    if (enumNeedsRelease_c_Comp_start_U64_len_U64(&(c), cpe.nameStart, cpe.nameLen)) {
    emitEnumReleaseProto_c_Comp_ei_U64(&(c), epp);
    }
    }
    epp = ({ uint64_t __ov; if (__builtin_add_overflow((epp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(cpe);
    }
    uint64_t mep = 0;
    while (mep < (long long)((c.genInsts).count)) {
    uint64_t mei = Array_U64_get(c.genInsts, (long long)(mep));
    long long meEnum = isGenericEnumInst_c_Comp_ref_U64(&(c), mei);
    long long meCopy = 0;
    long long meRel = 0;
    if (meEnum) {
    meCopy = monoEnumNeedsCopy_c_Comp_instRef_U64(&(c), mei);
    meRel = monoEnumNeedsRelease_c_Comp_instRef_U64(&(c), mei);
    }
    else {
    if (isGenericInst_c_Comp_ref_U64(&(c), mei)) {
    meCopy = monoStructNeedsCopy_c_Comp_instRef_U64(&(c), mei);
    meRel = monoStructNeedsRelease_c_Comp_instRef_U64(&(c), mei);
    }
    }
    if (meCopy) {
    emitMonoModeProto_c_Comp_instRef_U64_mode_U64(&(c), mei, 0);
    emitMonoModeProto_c_Comp_instRef_U64_mode_U64(&(c), mei, 1);
    }
    if (meRel) {
    emitMonoModeProto_c_Comp_instRef_U64_mode_U64(&(c), mei, 2);
    }
    mep = ({ uint64_t __ov; if (__builtin_add_overflow((mep), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genU8ArrayRuntime();
    uint64_t ar = 0;
    while (ar < (long long)((c.arrayElems).count)) {
    Bind ae2 = Array_Bind_get(c.arrayElems, (long long)(ar));
    if (skipArrayElem_c_Comp_ae_Bind(&(c), ae2)) {
    }
    else {
    genArrayRuntimeFns_c_Comp_elemStart_U64_elemLen_U64(&(c), ae2.nameStart, ae2.nameLen);
    }
    ar = ({ uint64_t __ov; if (__builtin_add_overflow((ar), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t scd = 0;
    while (scd < (long long)((c.structs).count)) {
    StructDef cs2 = StructDef_share(Array_StructDef_get(c.structs, (long long)(scd)));
    if (((long long)((cs2.typeParams).count) > 0) || cs2.isExtern) {
    }
    else {
    if (cs2.isUnique) {
    }
    else {
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&(c), cs2.nameStart, cs2.nameLen)) {
    emitStructModeDef_c_Comp_si_U64_mode_U64(&(c), scd, 0);
    emitStructModeDef_c_Comp_si_U64_mode_U64(&(c), scd, 1);
    }
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&(c), cs2.nameStart, cs2.nameLen)) {
    emitStructModeDef_c_Comp_si_U64_mode_U64(&(c), scd, 2);
    }
    }
    scd = ({ uint64_t __ov; if (__builtin_add_overflow((scd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(cs2);
    }
    uint64_t ecd = 0;
    while (ecd < (long long)((c.enums).count)) {
    EnumDef ce2 = EnumDef_share(Array_EnumDef_get(c.enums, (long long)(ecd)));
    if ((long long)((ce2.typeParams).count) > 0) {
    }
    else {
    if (enumNeedsCopy_c_Comp_start_U64_len_U64(&(c), ce2.nameStart, ce2.nameLen)) {
    emitEnumModeDef_c_Comp_ei_U64_mode_U64(&(c), ecd, 0);
    emitEnumModeDef_c_Comp_ei_U64_mode_U64(&(c), ecd, 1);
    }
    if (enumNeedsRelease_c_Comp_start_U64_len_U64(&(c), ce2.nameStart, ce2.nameLen)) {
    emitEnumModeDef_c_Comp_ei_U64_mode_U64(&(c), ecd, 2);
    }
    }
    ecd = ({ uint64_t __ov; if (__builtin_add_overflow((ecd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(ce2);
    }
    uint64_t mcd = 0;
    while (mcd < (long long)((c.genInsts).count)) {
    uint64_t mdi = Array_U64_get(c.genInsts, (long long)(mcd));
    long long mdEnum = isGenericEnumInst_c_Comp_ref_U64(&(c), mdi);
    long long mdCopy = 0;
    long long mdRel = 0;
    if (mdEnum) {
    mdCopy = monoEnumNeedsCopy_c_Comp_instRef_U64(&(c), mdi);
    mdRel = monoEnumNeedsRelease_c_Comp_instRef_U64(&(c), mdi);
    }
    else {
    if (isGenericInst_c_Comp_ref_U64(&(c), mdi)) {
    mdCopy = monoStructNeedsCopy_c_Comp_instRef_U64(&(c), mdi);
    mdRel = monoStructNeedsRelease_c_Comp_instRef_U64(&(c), mdi);
    }
    }
    if (mdCopy) {
    emitMonoModeDef_c_Comp_instRef_U64_isEnum_Bool_mode_U64(&(c), mdi, mdEnum, 0);
    emitMonoModeDef_c_Comp_instRef_U64_isEnum_Bool_mode_U64(&(c), mdi, mdEnum, 1);
    }
    if (mdRel) {
    emitMonoModeDef_c_Comp_instRef_U64_isEnum_Bool_mode_U64(&(c), mdi, mdEnum, 2);
    }
    mcd = ({ uint64_t __ov; if (__builtin_add_overflow((mcd), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    emitClosureEnvs_c_Comp(&(c));
    emitAsyncDecls_c_Comp(&(c));
    uint64_t i = 0;
    while (i < (long long)((c.funcs).count)) {
    Func f = Func_share(Array_Func_get(c.funcs, (long long)(i)));
    if (nameIsMain_c_Comp_f_Func(&(c), f)) {
    }
    else {
    if (f.isExtern) {
    }
    else {
    if ((long long)((f.typeParams).count) > 0) {
    }
    else {
    if (methodRecvIsTrait_c_Comp_f_Func(&(c), f)) {
    }
    else {
    if (f.isProvided && !(providedRetReachable_c_Comp_mf_Func_recvInstRef_U64(&(c), f, 0))) {
    }
    else {
    if (f.hasRecv) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&(c), f.recvStart, f.recvLen, 0);
    }
    else {
    clearSelfItemEnv_c_Comp(&(c));
    }
    genSignature_c_Comp_f_Func(&(c), f);
    plew_write((PlewString){";\n", 2});
    clearSelfItemEnv_c_Comp(&(c));
    }
    }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    emitMonoMethods_c_Comp_proto_Bool(&(c), 1);
    emitArrayMethods_c_Comp_proto_Bool(&(c), 1);
    emitMonoFns_c_Comp_proto_Bool(&(c), 1);
    emitThunks_c_Comp_proto_Bool(&(c), 1);
    emitClosures_c_Comp_proto_Bool(&(c), 1);
    {
    long long __fe0 = (long long)((c.funcs).count);
    for (long long j = 0; j < __fe0; j++) {
    Func fb = Func_share(Array_Func_get(c.funcs, (long long)(j)));
    if ((long long)((fb.typeParams).count) > 0) {
    }
    else {
    if (fb.isExtern) {
    }
    else {
    if (methodRecvIsTrait_c_Comp_f_Func(&(c), fb)) {
    }
    else {
    if (fb.isProvided && !(providedRetReachable_c_Comp_mf_Func_recvInstRef_U64(&(c), fb, 0))) {
    }
    else {
    if (fb.isAsync) {
    genAsyncFunc_c_Comp_fi_U64(&(c), j);
    }
    else {
    genFunc_c_Comp_fi_U64(&(c), j);
    }
    }
    }
    }
    }
    Func_release(fb);
    }
    }
    emitMonoMethods_c_Comp_proto_Bool(&(c), 0);
    emitArrayMethods_c_Comp_proto_Bool(&(c), 0);
    emitMonoFns_c_Comp_proto_Bool(&(c), 0);
    emitThunks_c_Comp_proto_Bool(&(c), 0);
    emitClosures_c_Comp_proto_Bool(&(c), 0);
    Comp_release(c);
    Lexer_release(lx);
    Array_U8_release(prelPath);
    Array_Bind_release(moduleRanges);
    Array_U8_release(combined);
    return 0;
}
unsigned char Lexer_at_off_U64(Lexer self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow((self.pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)((self.bytes).count)) {
    { unsigned char __ret1 = Array_U8_get(self.bytes, (long long)(i));
    return __ret1; }
    }
    { unsigned char __ret2 = 0;
    return __ret2; }
}
void Lexer_emit_k_Kind_start_U64_len_U64(Lexer* self, Kind k, uint64_t start, uint64_t len) {
    Array_Tok_append_value_T(&((*self).toks), (Tok){.kind = k, .start = start, .len = len});
    (*self).pos = ({ uint64_t __ov; if (__builtin_add_overflow((start), (len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
}
long long Lexer_lastWasNewline(Lexer self) {
    uint64_t n = (long long)((self.toks).count);
    if (n == 0) {
    { long long __ret3 = 0;
    return __ret3; }
    }
    Tok t = Array_Tok_get(self.toks, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    { long long __ret4 = ({ long long __mr5; Kind __ms5 = t.kind; if (__ms5.tag == 1) { __mr5 = (1); } else { __mr5 = (0); } __mr5; });
    return __ret4; }
}
long long Lexer_lastCanEnd(Lexer self) {
    uint64_t n = (long long)((self.toks).count);
    if (n == 0) {
    { long long __ret6 = 0;
    return __ret6; }
    }
    Tok t = Array_Tok_get(self.toks, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    { long long __ret7 = ({ long long __mr8; Kind __ms8 = t.kind; if (__ms8.tag == 5) { __mr8 = (1); } else if (__ms8.tag == 2) { __mr8 = (1); } else if (__ms8.tag == 3) { __mr8 = (1); } else if (__ms8.tag == 4) { __mr8 = (1); } else if (__ms8.tag == 33) { __mr8 = (1); } else if (__ms8.tag == 35) { __mr8 = (1); } else if (__ms8.tag == 37) { __mr8 = (1); } else if (__ms8.tag == 64) { __mr8 = (1); } else if (__ms8.tag == 30) { __mr8 = (1); } else if (__ms8.tag == 31) { __mr8 = (1); } else if (__ms8.tag == 16) { __mr8 = (1); } else if (__ms8.tag == 14) { __mr8 = (1); } else if (__ms8.tag == 15) { __mr8 = (1); } else { __mr8 = (0); } __mr8; });
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
long long rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8 bytes, uint64_t start, uint64_t len, PlewString kw) {
    Array_U8 kb = Array_U8_share(({ PlewString __s = kw; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; }));
    if (len != (long long)((kb).count)) {
    { long long __ret17 = 0;
    Array_U8_release(kb);
    return __ret17; }
    }
    uint64_t j = 0;
    while (j < len) {
    if (Array_U8_get(bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != Array_U8_get(kb, (long long)(j))) {
    { long long __ret18 = 0;
    Array_U8_release(kb);
    return __ret18; }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret19 = 1;
    Array_U8_release(kb);
    return __ret19; }
    Array_U8_release(kb);
}
Kind identKind_bytes_AU8_start_U64_len_U64(Array_U8 bytes, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"fn", 2})) {
    { Kind __ret20 = (Kind){.tag = 6};
    return __ret20; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"struct", 6})) {
    { Kind __ret21 = (Kind){.tag = 7};
    return __ret21; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"enum", 4})) {
    { Kind __ret22 = (Kind){.tag = 8};
    return __ret22; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"match", 5})) {
    { Kind __ret23 = (Kind){.tag = 9};
    return __ret23; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"if", 2})) {
    { Kind __ret24 = (Kind){.tag = 10};
    return __ret24; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"else", 4})) {
    { Kind __ret25 = (Kind){.tag = 11};
    return __ret25; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"while", 5})) {
    { Kind __ret26 = (Kind){.tag = 12};
    return __ret26; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"for", 3})) {
    { Kind __ret27 = (Kind){.tag = 13};
    return __ret27; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"break", 5})) {
    { Kind __ret28 = (Kind){.tag = 14};
    return __ret28; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"continue", 8})) {
    { Kind __ret29 = (Kind){.tag = 15};
    return __ret29; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"return", 6})) {
    { Kind __ret30 = (Kind){.tag = 16};
    return __ret30; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"give", 4})) {
    { Kind __ret31 = (Kind){.tag = 17};
    return __ret31; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"val", 3})) {
    { Kind __ret32 = (Kind){.tag = 18};
    return __ret32; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"mut", 3})) {
    { Kind __ret33 = (Kind){.tag = 19};
    return __ret33; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"in", 2})) {
    { Kind __ret34 = (Kind){.tag = 20};
    return __ret34; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"as", 2})) {
    { Kind __ret35 = (Kind){.tag = 21};
    return __ret35; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"inout", 5})) {
    { Kind __ret36 = (Kind){.tag = 22};
    return __ret36; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"unique", 6})) {
    { Kind __ret37 = (Kind){.tag = 23};
    return __ret37; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"deinit", 6})) {
    { Kind __ret38 = (Kind){.tag = 24};
    return __ret38; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"move", 4})) {
    { Kind __ret39 = (Kind){.tag = 25};
    return __ret39; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"borrow", 6})) {
    { Kind __ret40 = (Kind){.tag = 26};
    return __ret40; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"async", 5})) {
    { Kind __ret41 = (Kind){.tag = 27};
    return __ret41; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"await", 5})) {
    { Kind __ret42 = (Kind){.tag = 28};
    return __ret42; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"extern", 6})) {
    { Kind __ret43 = (Kind){.tag = 29};
    return __ret43; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"true", 4})) {
    { Kind __ret44 = (Kind){.tag = 30};
    return __ret44; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(bytes), start, len, (PlewString){"false", 5})) {
    { Kind __ret45 = (Kind){.tag = 31};
    return __ret45; }
    }
    { Kind __ret46 = (Kind){.tag = 5};
    return __ret46; }
}
void lex_lx_Lexer(Lexer* lx) {
    while ((*lx).pos < (long long)(((*lx).bytes).count)) {
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
    while ((*lx).pos < (long long)(((*lx).bytes).count)) {
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
    while (j < (long long)(((*lx).bytes).count)) {
    if (isDigit_b_U8(Array_U8_get((*lx).bytes, (long long)(j)))) {
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
    while (j < (long long)(((*lx).bytes).count)) {
    if (isAlnum_b_U8(Array_U8_get((*lx).bytes, (long long)(j)))) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    break;
    }
    }
    uint64_t len = ({ uint64_t __ov; if (__builtin_sub_overflow((j), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Kind k = identKind_bytes_AU8_start_U64_len_U64(Array_U8_share((*lx).bytes), start, len);
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), k, start, len);
    continue;
    }
    if (b == 34) {
    uint64_t start = (*lx).pos;
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow(((*lx).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < (long long)(((*lx).bytes).count)) {
    if (Array_U8_get((*lx).bytes, (long long)(j)) == 92) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (Array_U8_get((*lx).bytes, (long long)(j)) == 34) {
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
    while (j < (long long)(((*lx).bytes).count)) {
    if (Array_U8_get((*lx).bytes, (long long)(j)) == 92) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (Array_U8_get((*lx).bytes, (long long)(j)) == 39) {
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
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 75}, (*lx).pos, 3);
    continue;
    }
    if (b3 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 76}, (*lx).pos, 3);
    continue;
    }
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 40}, (*lx).pos, 1);
    continue;
    }
    if (b == 61) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 42}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 63}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 41}, (*lx).pos, 1);
    continue;
    }
    if (b == 33) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 43}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 55}, (*lx).pos, 1);
    continue;
    }
    if (b == 60) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 45}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 60) {
    unsigned char b3 = Lexer_at_off_U64((*lx), 2);
    if (b3 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 73}, (*lx).pos, 3);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 59}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 44}, (*lx).pos, 1);
    continue;
    }
    if (b == 62) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 47}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    unsigned char b3 = Lexer_at_off_U64((*lx), 2);
    if (b3 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 74}, (*lx).pos, 3);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 60}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 46}, (*lx).pos, 1);
    continue;
    }
    if (b == 43) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 65}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 48}, (*lx).pos, 1);
    continue;
    }
    if (b == 45) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 66}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 62}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 49}, (*lx).pos, 1);
    continue;
    }
    if (b == 42) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 67}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 50}, (*lx).pos, 1);
    continue;
    }
    if (b == 47) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 68}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 62) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 64}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 51}, (*lx).pos, 1);
    continue;
    }
    if (b == 37) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 69}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 52}, (*lx).pos, 1);
    continue;
    }
    if (b == 38) {
    if (b2 == 38) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 53}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 70}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 56}, (*lx).pos, 1);
    continue;
    }
    if (b == 124) {
    if (b2 == 124) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 54}, (*lx).pos, 2);
    continue;
    }
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 71}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 57}, (*lx).pos, 1);
    continue;
    }
    if (b == 94) {
    if (b2 == 61) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 72}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 58}, (*lx).pos, 1);
    continue;
    }
    if (b == 126) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 61}, (*lx).pos, 1);
    continue;
    }
    if (b == 63) {
    if (b2 == 63) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 77}, (*lx).pos, 2);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 78}, (*lx).pos, 1);
    continue;
    }
    if (b == 40) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 32}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_add_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 41) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 33}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_sub_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 91) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 34}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_add_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 93) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 35}, (*lx).pos, 1);
    (*lx).depth = ({ int64_t __ov; if (__builtin_sub_overflow(((*lx).depth), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    if (b == 123) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 36}, (*lx).pos, 1);
    continue;
    }
    if (b == 125) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 37}, (*lx).pos, 1);
    continue;
    }
    if (b == 44) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 38}, (*lx).pos, 1);
    continue;
    }
    if (b == 58) {
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 39}, (*lx).pos, 1);
    continue;
    }
    Lexer_emit_k_Kind_start_U64_len_U64(&((*lx)), (Kind){.tag = 78}, (*lx).pos, 1);
    }
    Array_Tok_append_value_T(&((*lx).toks), (Tok){.kind = (Kind){.tag = 0}, .start = (*lx).pos, .len = 0});
}
int64_t kindCode_k_Kind(Kind k) {
    { int64_t __ret47 = ({ long long __mr48; Kind __ms48 = k; if (__ms48.tag == 0) { __mr48 = (0); } else if (__ms48.tag == 1) { __mr48 = (1); } else if (__ms48.tag == 2) { __mr48 = (2); } else if (__ms48.tag == 3) { __mr48 = (3); } else if (__ms48.tag == 4) { __mr48 = (5); } else if (__ms48.tag == 5) { __mr48 = (4); } else if (__ms48.tag == 6) { __mr48 = (10); } else if (__ms48.tag == 7) { __mr48 = (11); } else if (__ms48.tag == 8) { __mr48 = (12); } else if (__ms48.tag == 9) { __mr48 = (13); } else if (__ms48.tag == 10) { __mr48 = (14); } else if (__ms48.tag == 11) { __mr48 = (15); } else if (__ms48.tag == 12) { __mr48 = (16); } else if (__ms48.tag == 13) { __mr48 = (17); } else if (__ms48.tag == 14) { __mr48 = (18); } else if (__ms48.tag == 15) { __mr48 = (19); } else if (__ms48.tag == 16) { __mr48 = (20); } else if (__ms48.tag == 17) { __mr48 = (21); } else if (__ms48.tag == 18) { __mr48 = (22); } else if (__ms48.tag == 19) { __mr48 = (23); } else if (__ms48.tag == 20) { __mr48 = (24); } else if (__ms48.tag == 21) { __mr48 = (25); } else if (__ms48.tag == 22) { __mr48 = (26); } else if (__ms48.tag == 23) { __mr48 = (29); } else if (__ms48.tag == 24) { __mr48 = (30); } else if (__ms48.tag == 25) { __mr48 = (31); } else if (__ms48.tag == 26) { __mr48 = (32); } else if (__ms48.tag == 27) { __mr48 = (33); } else if (__ms48.tag == 28) { __mr48 = (34); } else if (__ms48.tag == 29) { __mr48 = (35); } else if (__ms48.tag == 30) { __mr48 = (27); } else if (__ms48.tag == 31) { __mr48 = (28); } else if (__ms48.tag == 32) { __mr48 = (40); } else if (__ms48.tag == 33) { __mr48 = (41); } else if (__ms48.tag == 34) { __mr48 = (42); } else if (__ms48.tag == 35) { __mr48 = (43); } else if (__ms48.tag == 36) { __mr48 = (44); } else if (__ms48.tag == 37) { __mr48 = (45); } else if (__ms48.tag == 38) { __mr48 = (46); } else if (__ms48.tag == 39) { __mr48 = (47); } else if (__ms48.tag == 40) { __mr48 = (48); } else if (__ms48.tag == 41) { __mr48 = (49); } else if (__ms48.tag == 42) { __mr48 = (50); } else if (__ms48.tag == 43) { __mr48 = (51); } else if (__ms48.tag == 44) { __mr48 = (52); } else if (__ms48.tag == 45) { __mr48 = (53); } else if (__ms48.tag == 46) { __mr48 = (54); } else if (__ms48.tag == 47) { __mr48 = (55); } else if (__ms48.tag == 48) { __mr48 = (56); } else if (__ms48.tag == 49) { __mr48 = (57); } else if (__ms48.tag == 50) { __mr48 = (58); } else if (__ms48.tag == 51) { __mr48 = (59); } else if (__ms48.tag == 52) { __mr48 = (60); } else if (__ms48.tag == 53) { __mr48 = (61); } else if (__ms48.tag == 54) { __mr48 = (62); } else if (__ms48.tag == 55) { __mr48 = (63); } else if (__ms48.tag == 62) { __mr48 = (64); } else if (__ms48.tag == 63) { __mr48 = (65); } else if (__ms48.tag == 64) { __mr48 = (66); } else if (__ms48.tag == 65) { __mr48 = (67); } else if (__ms48.tag == 66) { __mr48 = (68); } else if (__ms48.tag == 67) { __mr48 = (69); } else if (__ms48.tag == 68) { __mr48 = (70); } else if (__ms48.tag == 69) { __mr48 = (71); } else if (__ms48.tag == 75) { __mr48 = (72); } else if (__ms48.tag == 76) { __mr48 = (73); } else if (__ms48.tag == 56) { __mr48 = (74); } else if (__ms48.tag == 57) { __mr48 = (75); } else if (__ms48.tag == 58) { __mr48 = (76); } else if (__ms48.tag == 59) { __mr48 = (77); } else if (__ms48.tag == 60) { __mr48 = (78); } else if (__ms48.tag == 61) { __mr48 = (79); } else if (__ms48.tag == 70) { __mr48 = (80); } else if (__ms48.tag == 71) { __mr48 = (81); } else if (__ms48.tag == 72) { __mr48 = (82); } else if (__ms48.tag == 73) { __mr48 = (83); } else if (__ms48.tag == 74) { __mr48 = (84); } else if (__ms48.tag == 77) { __mr48 = (85); } else if (__ms48.tag == 78) { __mr48 = (99); } else { __builtin_unreachable(); } __mr48; });
    return __ret47; }
}
Kind Comp_curKind(Comp* self) {
    { Kind __ret49 = Array_Tok_get((*self).toks, (long long)((*self).pos)).kind;
    return __ret49; }
}
Tok Comp_cur(Comp* self) {
    { Tok __ret50 = Array_Tok_get((*self).toks, (long long)((*self).pos));
    return __ret50; }
}
Kind Comp_peekKind_off_U64(Comp* self, uint64_t off) {
    uint64_t i = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (off), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i < (long long)(((*self).toks).count)) {
    { Kind __ret51 = Array_Tok_get((*self).toks, (long long)(i)).kind;
    return __ret51; }
    }
    { Kind __ret52 = (Kind){.tag = 0};
    return __ret52; }
}
void Comp_advance(Comp* self) {
    (*self).pos = ({ uint64_t __ov; if (__builtin_add_overflow(((*self).pos), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
}
void Comp_skipNewlines(Comp* self) {
    while (1) {
    {
    Kind _m53 = Comp_curKind(&((*self)));
    if (_m53.tag == 1) {
    Comp_advance(&((*self)));
    }
    else {
    break;
    }
    }
    }
}
long long Comp_identIs_kw_String(Comp* self, PlewString kw) {
    Tok t = Array_Tok_get((*self).toks, (long long)((*self).pos));
    { long long __ret54 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*self).bytes), t.start, t.len, kw);
    return __ret54; }
}
uint64_t Comp_pushExpr_e_Expr(Comp* self, Expr e) {
    uint64_t id = (long long)(((*self).exprs).count);
    Array_Expr_append_value_T(&((*self).exprs), e);
    { uint64_t __ret55 = id;
    return __ret55; }
}
uint64_t Comp_pushStmt_s_Stmt(Comp* self, Stmt s) {
    uint64_t id = (long long)(((*self).stmts).count);
    Array_Stmt_append_value_T(&((*self).stmts), s);
    { uint64_t __ret56 = id;
    return __ret56; }
}
uint64_t Comp_pushType_t_TypeRef(Comp* self, TypeRef t) {
    uint64_t id = (long long)(((*self).types).count);
    Array_TypeRef_append_value_T(&((*self).types), t);
    { uint64_t __ret57 = id;
    return __ret57; }
}
void expect_c_Comp_k_Kind_msg_String(Comp* c, Kind k, PlewString msg) {
    if (kindCode_k_Kind(Comp_curKind(&((*c)))) == kindCode_k_Kind(k)) {
    Comp_advance(&((*c)));
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), msg);
    }
}
uint64_t tokenValue_c_Comp_t_Tok(Comp* c, Tok t) {
    uint64_t v = 0;
    uint64_t j = 0;
    while (j < t.len) {
    uint64_t d = ({ uint64_t __ov; if (__builtin_sub_overflow((((uint64_t)(Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((t.start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })))))), (48), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (v > 1844674407370955161) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"integer literal exceeds the maximum value (18446744073709551615 = U64 max)", 74});
    }
    if (v == 1844674407370955161) {
    if (d > 5) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"integer literal exceeds the maximum value (18446744073709551615 = U64 max)", 74});
    }
    }
    v = ({ uint64_t __ov; if (__builtin_add_overflow((({ uint64_t __ov; if (__builtin_mul_overflow((v), (10), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), (d), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret58 = v;
    return __ret58; }
}
int64_t binPrec_k_Kind(Kind k) {
    { int64_t __ret59 = ({ long long __mr60; Kind __ms60 = k; if (__ms60.tag == 54) { __mr60 = (1); } else if (__ms60.tag == 53) { __mr60 = (2); } else if (__ms60.tag == 42) { __mr60 = (3); } else if (__ms60.tag == 43) { __mr60 = (3); } else if (__ms60.tag == 44) { __mr60 = (3); } else if (__ms60.tag == 45) { __mr60 = (3); } else if (__ms60.tag == 46) { __mr60 = (3); } else if (__ms60.tag == 47) { __mr60 = (3); } else if (__ms60.tag == 77) { __mr60 = (4); } else if (__ms60.tag == 57) { __mr60 = (5); } else if (__ms60.tag == 58) { __mr60 = (6); } else if (__ms60.tag == 56) { __mr60 = (7); } else if (__ms60.tag == 59) { __mr60 = (8); } else if (__ms60.tag == 60) { __mr60 = (8); } else if (__ms60.tag == 48) { __mr60 = (9); } else if (__ms60.tag == 49) { __mr60 = (9); } else if (__ms60.tag == 50) { __mr60 = (10); } else if (__ms60.tag == 51) { __mr60 = (10); } else if (__ms60.tag == 52) { __mr60 = (10); } else { __mr60 = (0); } __mr60; });
    return __ret59; }
}
uint64_t charValue_c_Comp_t_Tok(Comp* c, Tok t) {
    uint64_t contentLen = ({ uint64_t __ov; if (__builtin_sub_overflow((t.len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (contentLen == 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"empty character literal", 23});
    }
    uint64_t p = ({ uint64_t __ov; if (__builtin_add_overflow((t.start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    unsigned char b0 = Array_U8_get((*c).bytes, (long long)(p));
    if (b0 == 92) {
    if (contentLen != 2) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"character literal must be a single scalar", 41});
    }
    unsigned char e = Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    if (e == 110) {
    { uint64_t __ret61 = 10;
    return __ret61; }
    }
    if (e == 116) {
    { uint64_t __ret62 = 9;
    return __ret62; }
    }
    if (e == 114) {
    { uint64_t __ret63 = 13;
    return __ret63; }
    }
    if (e == 48) {
    { uint64_t __ret64 = 0;
    return __ret64; }
    }
    { uint64_t __ret65 = e;
    return __ret65; }
    }
    uint64_t consumed = 1;
    uint64_t value = 0;
    if (b0 < 128) {
    consumed = 1;
    value = b0;
    }
    else {
    if (b0 < 224) {
    consumed = 2;
    value = (((b0 & 31) << 6) | (Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63));
    }
    else {
    if (b0 < 240) {
    consumed = 3;
    value = ((((b0 & 15) << 12) | ((Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63) << 6)) | (Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63));
    }
    else {
    consumed = 4;
    value = (((((b0 & 7) << 18) | ((Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63) << 12)) | ((Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63) << 6)) | (Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((p), (3), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) & 63));
    }
    }
    }
    if (contentLen != consumed) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), t.start), (PlewString){"multi-scalar character literal (Grapheme) is not yet supported", 62});
    }
    { uint64_t __ret66 = value;
    return __ret66; }
}
uint64_t parsePrimary_c_Comp(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m67 = k;
    if (_m67.tag == 2) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t v = tokenValue_c_Comp_t_Tok(&((*c)), t);
    uint64_t sStart = 0;
    uint64_t sLen = 0;
    {
    Kind _m68 = Comp_curKind(&((*c)));
    if (_m68.tag == 5) {
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
    { uint64_t __ret69 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = sStart, .tyLen = sLen}});
    return __ret69; }
    }
    else if (_m67.tag == 4) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t v = charValue_c_Comp_t_Tok(&((*c)), t);
    { uint64_t __ret70 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = t.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    return __ret70; }
    }
    else if (_m67.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    {
    Kind _m71 = Comp_peekKind_off_U64(&((*c)), 1);
    if (_m71.tag == 32) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    Array_Arg args = parseCallArgs_c_Comp(&((*c)));
    { uint64_t __ret72 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 4, .data.Call = {.nameStart = t.start, .nameLen = t.len, .args = Array_Arg_share(args)}});
    Array_Arg_release(args);
    return __ret72; }
    Array_Arg_release(args);
    }
    else {
    Comp_advance(&((*c)));
    { uint64_t __ret73 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = t.start, .len = t.len}});
    return __ret73; }
    }
    }
    }
    else if (_m67.tag == 30) {
    Tok tt = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret74 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 1, .offset = tt.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret74; }
    }
    else if (_m67.tag == 31) {
    Tok tf = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret75 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = tf.start, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret75; }
    }
    else if (_m67.tag == 32) {
    Comp_advance(&((*c)));
    uint64_t inner = parseExpr_c_Comp(&((*c)));
    expect_c_Comp_k_Kind_msg_String(&((*c)), (Kind){.tag = 33}, (PlewString){"expected ')' to close a parenthesized expression", 48});
    { uint64_t __ret76 = inner;
    return __ret76; }
    }
    else if (_m67.tag == 6) {
    Comp_advance(&((*c)));
    Array_Param params = parseParamList_c_Comp(&((*c)));
    long long hasRet = 0;
    uint64_t retStart = 0;
    uint64_t retLen = 0;
    long long retIsArray = 0;
    uint64_t retRef = 0;
    {
    Kind _m77 = Comp_curKind(&((*c)));
    if (_m77.tag == 62) {
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
    { uint64_t __ret78 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 17, .data.Closure = {.params = Array_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body}});
    Array_Param_release(params);
    return __ret78; }
    Array_Param_release(params);
    }
    else if (_m67.tag == 44) {
    { uint64_t __ret79 = parseMake_c_Comp(&((*c)));
    return __ret79; }
    }
    else if (_m67.tag == 9) {
    { uint64_t __ret80 = parseMatchExpr_c_Comp(&((*c)));
    return __ret80; }
    }
    else if (_m67.tag == 10) {
    { uint64_t __ret81 = parseIfExpr_c_Comp(&((*c)));
    return __ret81; }
    }
    else if (_m67.tag == 3) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    { uint64_t __ret82 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 7, .data.Str = {.start = t.start, .len = t.len}});
    return __ret82; }
    }
    else if (_m67.tag == 34) {
    Comp_advance(&((*c)));
    Array_U64 elems = Array_U64_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m83 = Comp_curKind(&((*c)));
    if (_m83.tag == 35) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m83.tag == 0) {
    break;
    }
    else {
    uint64_t e = parseExpr_c_Comp(&((*c)));
    Array_U64_append_value_T(&(elems), e);
    {
    Kind _m84 = Comp_curKind(&((*c)));
    if (_m84.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    { uint64_t __ret85 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 8, .data.Array = {.elems = Array_U64_share(elems)}});
    Array_U64_release(elems);
    return __ret85; }
    Array_U64_release(elems);
    }
    else {
    Tok te = Comp_cur(&((*c)));
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), te.start), (PlewString){"expected an expression", 22});
    Comp_advance(&((*c)));
    { uint64_t __ret86 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = 0, .offset = te.start, .isBool = 0, .tyStart = 0, .tyLen = 0}});
    return __ret86; }
    }
    }
}
uint64_t parseUnary_c_Comp(Comp* c) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"try", 3})) {
    Comp_advance(&((*c)));
    uint64_t inner = parsePostfix_c_Comp(&((*c)));
    { uint64_t __ret87 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 15, .data.Try = {.expr = inner}});
    return __ret87; }
    }
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m88 = k;
    if (_m88.tag == 28) {
    Comp_advance(&((*c)));
    uint64_t o = parsePostfix_c_Comp(&((*c)));
    { uint64_t __ret89 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 19, .data.Await = {.operand = o}});
    return __ret89; }
    }
    else if (_m88.tag == 25) {
    Comp_advance(&((*c)));
    uint64_t o = parsePostfix_c_Comp(&((*c)));
    { uint64_t __ret90 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 18, .data.Move = {.operand = o, .isBorrow = 0}});
    return __ret90; }
    }
    else if (_m88.tag == 26) {
    Comp_advance(&((*c)));
    uint64_t o = parsePostfix_c_Comp(&((*c)));
    { uint64_t __ret91 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 18, .data.Move = {.operand = o, .isBorrow = 1}});
    return __ret91; }
    }
    else if (_m88.tag == 49) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary_c_Comp(&((*c)));
    { uint64_t __ret92 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 57, .operand = o}});
    return __ret92; }
    }
    else if (_m88.tag == 55) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary_c_Comp(&((*c)));
    { uint64_t __ret93 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 63, .operand = o}});
    return __ret93; }
    }
    else if (_m88.tag == 61) {
    Comp_advance(&((*c)));
    uint64_t o = parseUnary_c_Comp(&((*c)));
    { uint64_t __ret94 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 2, .data.Unary = {.op = 79, .operand = o}});
    return __ret94; }
    }
    else {
    { uint64_t __ret95 = parsePostfix_c_Comp(&((*c)));
    return __ret95; }
    }
    }
}
uint64_t parsePostfix_c_Comp(Comp* c) {
    uint64_t e = parsePrimary_c_Comp(&((*c)));
    while (1) {
    {
    Kind _m96 = Comp_curKind(&((*c)));
    if (_m96.tag == 40) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m97 = Comp_curKind(&((*c)));
    if (_m97.tag == 32) {
    Comp_advance(&((*c)));
    Array_Arg args = parseCallArgs_c_Comp(&((*c)));
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 10, .data.Method = {.recv = e, .nameStart = nameTok.start, .nameLen = nameTok.len, .args = Array_Arg_share(args)}});
    Array_Arg_release(args);
    }
    else {
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    }
    }
    else if (_m96.tag == 34) {
    Comp_advance(&((*c)));
    uint64_t idx = parseExpr_c_Comp(&((*c)));
    expect_c_Comp_k_Kind_msg_String(&((*c)), (Kind){.tag = 35}, (PlewString){"expected ']' to close an index", 30});
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 9, .data.Index = {.base = e, .index = idx}});
    }
    else if (_m96.tag == 62) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 16, .data.Arrow = {.base = e, .nameStart = nameTok.start, .nameLen = nameTok.len}});
    }
    else if (_m96.tag == 21) {
    Comp_advance(&((*c)));
    PType ty = parseTypeTok_c_Comp(&((*c)));
    e = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 11, .data.Cast = {.operand = e, .tyStart = ty.start, .tyLen = ty.len, .ty = ty.ref}});
    }
    else if (_m96.tag == 1) {
    uint64_t off = 1;
    while ((Comp_peekKind_off_U64(&((*c)), off)).tag == 1) {
    off = ({ uint64_t __ov; if (__builtin_add_overflow((off), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if ((Comp_peekKind_off_U64(&((*c)), off)).tag == 40) {
    Comp_skipNewlines(&((*c)));
    }
    else {
    break;
    }
    }
    else {
    break;
    }
    }
    }
    { uint64_t __ret98 = e;
    return __ret98; }
}
uint64_t parseMake_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    Tok typeTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyRef = 0;
    {
    Kind _m99 = Comp_curKind(&((*c)));
    if (_m99.tag == 34) {
    Comp_advance(&((*c)));
    Array_U64 targs = Array_U64_new();
    long long first = 1;
    while (1) {
    {
    Kind _m100 = Comp_curKind(&((*c)));
    if (_m100.tag == 35) {
    break;
    }
    else if (_m100.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m101 = Comp_curKind(&((*c)));
    if (_m101.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    first = 0;
    PType arg = parseTypeTok_c_Comp(&((*c)));
    Array_U64_append_value_T(&(targs), arg.ref);
    }
    {
    Kind _m102 = Comp_curKind(&((*c)));
    if (_m102.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    tyRef = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = typeTok.start, .nameLen = typeTok.len, .args = Array_U64_share(targs)});
    Array_U64_release(targs);
    }
    else {
    }
    }
    uint64_t variantStart = 0;
    uint64_t variantLen = 0;
    long long isEnum = 0;
    {
    Kind _m103 = Comp_curKind(&((*c)));
    if (_m103.tag == 40) {
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
    Array_MakeField fields = Array_MakeField_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m104 = k;
    if (_m104.tag == 64) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m104.tag == 46) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m104.tag == 0) {
    break;
    }
    else if (_m104.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m105 = Comp_curKind(&((*c)));
    if (_m105.tag == 41) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t v = parseExpr_c_Comp(&((*c)));
    Array_MakeField_append_value_T(&(fields), (MakeField){.nameStart = fTok.start, .nameLen = fTok.len, .value = v});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    { uint64_t __ret106 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 6, .data.Make = {.typeStart = typeTok.start, .typeLen = typeTok.len, .variantStart = variantStart, .variantLen = variantLen, .isEnum = isEnum, .ty = tyRef, .fields = Array_MakeField_share(fields)}});
    Array_MakeField_release(fields);
    return __ret106; }
    Array_MakeField_release(fields);
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
    Kind _m107 = k;
    if (_m107.tag == 77) {
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
    { uint64_t __ret108 = left;
    return __ret108; }
}
uint64_t parseExpr_c_Comp(Comp* c) {
    { uint64_t __ret109 = parseBin_c_Comp_minPrec_I64(&((*c)), 1);
    return __ret109; }
}
Array_Arg parseCallArgs_c_Comp(Comp* c) {
    Array_Arg args = Array_Arg_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m110 = k;
    if (_m110.tag == 33) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m110.tag == 0) {
    break;
    }
    else {
    uint64_t labelStart = 0;
    uint64_t labelLen = 0;
    long long hasLabel = 0;
    {
    Kind _m111 = Comp_curKind(&((*c)));
    if (_m111.tag == 5) {
    {
    Kind _m112 = Comp_peekKind_off_U64(&((*c)), 1);
    if (_m112.tag == 39) {
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
    Kind _m113 = Comp_curKind(&((*c)));
    if (_m113.tag == 22) {
    Comp_advance(&((*c)));
    isInout = 1;
    }
    else {
    }
    }
    uint64_t e = parseExpr_c_Comp(&((*c)));
    Array_Arg_append_value_T(&(args), (Arg){.expr = e, .isInout = isInout, .labelStart = labelStart, .labelLen = labelLen, .hasLabel = hasLabel});
    {
    Kind _m114 = Comp_curKind(&((*c)));
    if (_m114.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    }
    }
    { Array_Arg __ret115 = Array_Arg_share(args);
    Array_Arg_release(args);
    return __ret115; }
    Array_Arg_release(args);
}
long long isAssignOp_k_Kind(Kind k) {
    {
    Kind _m116 = k;
    if (_m116.tag == 41) {
    { long long __ret117 = 1;
    return __ret117; }
    }
    else if (_m116.tag == 65) {
    { long long __ret118 = 1;
    return __ret118; }
    }
    else if (_m116.tag == 66) {
    { long long __ret119 = 1;
    return __ret119; }
    }
    else if (_m116.tag == 67) {
    { long long __ret120 = 1;
    return __ret120; }
    }
    else if (_m116.tag == 68) {
    { long long __ret121 = 1;
    return __ret121; }
    }
    else if (_m116.tag == 69) {
    { long long __ret122 = 1;
    return __ret122; }
    }
    else if (_m116.tag == 70) {
    { long long __ret123 = 1;
    return __ret123; }
    }
    else if (_m116.tag == 71) {
    { long long __ret124 = 1;
    return __ret124; }
    }
    else if (_m116.tag == 72) {
    { long long __ret125 = 1;
    return __ret125; }
    }
    else if (_m116.tag == 73) {
    { long long __ret126 = 1;
    return __ret126; }
    }
    else if (_m116.tag == 74) {
    { long long __ret127 = 1;
    return __ret127; }
    }
    else {
    { long long __ret128 = 0;
    return __ret128; }
    }
    }
}
PType parseTypeTok_c_Comp(Comp* c) {
    Tok head = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m129 = head.kind;
    if (_m129.tag == 6) {
    Array_U64 fargs = Array_U64_new();
    uint64_t retRef = 0;
    {
    Kind _m130 = Comp_curKind(&((*c)));
    if (_m130.tag == 32) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    {
    Kind _m131 = Comp_curKind(&((*c)));
    if (_m131.tag == 33) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m131.tag == 0) {
    break;
    }
    else if (_m131.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    {
    Kind _m132 = Comp_curKind(&((*c)));
    if (_m132.tag == 5) {
    if ((Comp_peekKind_off_U64(&((*c)), 1)).tag == 39) {
    Comp_advance(&((*c)));
    Comp_advance(&((*c)));
    }
    }
    else {
    }
    }
    {
    Kind _m133 = Comp_curKind(&((*c)));
    if (_m133.tag == 22) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PType pty = parseTypeTok_c_Comp(&((*c)));
    Array_U64_append_value_T(&(fargs), pty.ref);
    }
    }
    }
    {
    Kind _m134 = Comp_curKind(&((*c)));
    if (_m134.tag == 62) {
    Comp_advance(&((*c)));
    PType rty = parseTypeTok_c_Comp(&((*c)));
    retRef = rty.ref;
    }
    else {
    }
    }
    Array_U64 allArgs = Array_U64_new();
    Array_U64_append_value_T(&(allArgs), retRef);
    uint64_t fk = 0;
    while (fk < (long long)((fargs).count)) {
    Array_U64_append_value_T(&(allArgs), Array_U64_get(fargs, (long long)(fk)));
    fk = ({ uint64_t __ov; if (__builtin_add_overflow((fk), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t fref = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = Array_U64_share(allArgs)});
    { PType __ret135 = (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = fref};
    Array_U64_release(allArgs);
    Array_U64_release(fargs);
    return __ret135; }
    Array_U64_release(allArgs);
    Array_U64_release(fargs);
    }
    else {
    }
    }
    Array_U64 args = Array_U64_new();
    uint64_t elemStart = head.start;
    uint64_t elemLen = head.len;
    long long bracketed = 0;
    {
    Kind _m136 = Comp_curKind(&((*c)));
    if (_m136.tag == 34) {
    bracketed = 1;
    Comp_advance(&((*c)));
    long long first = 1;
    while (1) {
    {
    Kind _m137 = Comp_curKind(&((*c)));
    if (_m137.tag == 35) {
    break;
    }
    else if (_m137.tag == 0) {
    break;
    }
    else {
    }
    }
    if (first) {
    }
    else {
    {
    Kind _m138 = Comp_curKind(&((*c)));
    if (_m138.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    first = 0;
    PType arg = parseTypeTok_c_Comp(&((*c)));
    Array_U64_append_value_T(&(args), arg.ref);
    if ((long long)((args).count) == 1) {
    elemStart = arg.start;
    elemLen = arg.len;
    }
    }
    {
    Kind _m139 = Comp_curKind(&((*c)));
    if (_m139.tag == 35) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    }
    }
    uint64_t ref = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = head.start, .nameLen = head.len, .args = Array_U64_share(args)});
    if (bracketed) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), head.start, head.len, (PlewString){"Array", 5})) {
    if ((long long)((args).count) > 0) {
    if (isCompoundType_c_Comp_ref_U64(&((*c)), Array_U64_get(args, (long long)(0)))) {
    Bind mn = appendMangleSpan_c_Comp_ref_U64(&((*c)), Array_U64_get(args, (long long)(0)));
    { PType __ret140 = (PType){.start = mn.nameStart, .len = mn.nameLen, .isArray = 1, .ref = ref};
    Array_U64_release(args);
    return __ret140; }
    }
    }
    { PType __ret141 = (PType){.start = elemStart, .len = elemLen, .isArray = 1, .ref = ref};
    Array_U64_release(args);
    return __ret141; }
    }
    }
    { PType __ret142 = (PType){.start = head.start, .len = head.len, .isArray = 0, .ref = ref};
    Array_U64_release(args);
    return __ret142; }
    Array_U64_release(args);
}
Array_Bind parseTypeParams_c_Comp(Comp* c) {
    Array_Bind ps = Array_Bind_new();
    {
    Kind _m143 = Comp_curKind(&((*c)));
    if (_m143.tag == 34) {
    Comp_advance(&((*c)));
    while (1) {
    {
    Kind _m144 = Comp_curKind(&((*c)));
    if (_m144.tag == 35) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m144.tag == 0) {
    break;
    }
    else if (_m144.tag == 38) {
    Comp_advance(&((*c)));
    }
    else if (_m144.tag == 39) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"inline trait constraint is not allowed in `[...]`; use a `where` clause", 71});
    Comp_advance(&((*c)));
    }
    else if (_m144.tag == 5) {
    uint64_t nameStart = 0;
    uint64_t nameLen = 0;
    while (1) {
    {
    Kind _m145 = Comp_curKind(&((*c)));
    if (_m145.tag == 5) {
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
    Array_Bind_append_value_T(&(ps), (Bind){.nameStart = nameStart, .nameLen = nameLen, .fieldStart = nameStart, .fieldLen = nameLen});
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
    { Array_Bind __ret146 = Array_Bind_share(ps);
    Array_Bind_release(ps);
    return __ret146; }
    Array_Bind_release(ps);
}
void recordArrayElem_c_Comp_ty_PType(Comp* c, PType ty) {
    if (ty.isArray) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).count)) {
    Bind e = Array_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, ty.start, ty.len)) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t elemRef = 0;
    if (ty.ref < (long long)(((*c).types).count)) {
    TypeRef at = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ty.ref)));
    if ((long long)((at.args).count) > 0) {
    elemRef = Array_U64_get(at.args, (long long)(0));
    }
    TypeRef_release(at);
    }
    ensureArrayElemDeps_c_Comp_elemRef_U64(&((*c)), elemRef);
    Array_Bind_append_value_T(&((*c).arrayElems), (Bind){.nameStart = ty.start, .nameLen = ty.len, .fieldStart = elemRef, .fieldLen = 0});
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
    Kind _m147 = Comp_curKind(&((*c)));
    if (_m147.tag == 39) {
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
    expect_c_Comp_k_Kind_msg_String(&((*c)), (Kind){.tag = 41}, (PlewString){"expected '=' — a variable declaration must be initialized", 59});
    uint64_t init = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret148 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 0, .data.Let = {.mutable = mutable, .nameStart = nameTok.start, .nameLen = nameTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .init = init}});
    return __ret148; }
}
uint64_t parsePanic_c_Comp(Comp* c) {
    Tok kw = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t msg = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret149 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 8, .data.Panic = {.msg = msg, .offset = kw.start}});
    return __ret149; }
}
uint64_t parseReturn_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m150 = Comp_curKind(&((*c)));
    if (_m150.tag == 1) {
    { uint64_t __ret151 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret151; }
    }
    else if (_m150.tag == 37) {
    { uint64_t __ret152 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret152; }
    }
    else if (_m150.tag == 0) {
    { uint64_t __ret153 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = 0, .hasValue = 0}});
    return __ret153; }
    }
    else {
    uint64_t e = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret154 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = e, .hasValue = 1}});
    return __ret154; }
    }
    }
}
uint64_t parseIf_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr_c_Comp(&((*c)));
    uint64_t thenBlk = parseBlock_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m155 = Comp_curKind(&((*c)));
    if (_m155.tag == 11) {
    Comp_advance(&((*c)));
    {
    Kind _m156 = Comp_curKind(&((*c)));
    if (_m156.tag == 10) {
    uint64_t nested = parseIf_c_Comp(&((*c)));
    Array_U64 one = Array_U64_new();
    Array_U64_append_value_T(&(one), nested);
    uint64_t blkId = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(one)});
    { uint64_t __ret157 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId, .hasElse = 1}});
    Array_U64_release(one);
    return __ret157; }
    Array_U64_release(one);
    }
    else {
    uint64_t elseBlk = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret158 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk, .hasElse = 1}});
    return __ret158; }
    }
    }
    }
    else {
    { uint64_t __ret159 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.If = {.cond = cond, .thenBlk = thenBlk, .elseBlk = 0, .hasElse = 0}});
    return __ret159; }
    }
    }
}
uint64_t parseIfExpr_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr_c_Comp(&((*c)));
    uint64_t thenBlk = parseBlock_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m160 = Comp_curKind(&((*c)));
    if (_m160.tag == 11) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m161 = Comp_curKind(&((*c)));
    if (_m161.tag == 10) {
    uint64_t nested = parseIfExpr_c_Comp(&((*c)));
    Array_U64 one = Array_U64_new();
    Array_U64_append_value_T(&(one), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 9, .data.Give = {.value = nested}}));
    uint64_t blkId = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(one)});
    { uint64_t __ret162 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = blkId}});
    Array_U64_release(one);
    return __ret162; }
    Array_U64_release(one);
    }
    else {
    uint64_t elseBlk = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret163 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 13, .data.IfExpr = {.cond = cond, .thenBlk = thenBlk, .elseBlk = elseBlk}});
    return __ret163; }
    }
    }
}
uint64_t parseGive_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t v = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret164 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 9, .data.Give = {.value = v}});
    return __ret164; }
}
uint64_t parseWhile_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t cond = parseExpr_c_Comp(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    { uint64_t __ret165 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 5, .data.While = {.cond = cond, .body = body}});
    return __ret165; }
}
uint64_t parseFor_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    long long isStruct = 0;
    uint64_t patStart = 0;
    uint64_t patLen = 0;
    Array_Bind binds = Array_Bind_new();
    uint64_t nameStart = 0;
    uint64_t nameLen = 0;
    long long isPattern = 0;
    {
    Kind _m166 = Comp_curKind(&((*c)));
    if (_m166.tag == 5) {
    {
    Kind _m167 = Comp_peekKind_off_U64(&((*c)), 1);
    if (_m167.tag == 36) {
    isPattern = 1;
    }
    else {
    }
    }
    }
    else {
    }
    }
    if (isPattern) {
    PatInfo pi = parsePattern_c_Comp(&((*c)));
    isStruct = pi.isStruct;
    patStart = pi.enumStart;
    patLen = pi.enumLen;
    binds = Array_Bind_share(pi.binds);
    PatInfo_release(pi);
    }
    else {
    {
    Kind _m168 = Comp_curKind(&((*c)));
    if (_m168.tag == 18) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Tok nameTok = Comp_cur(&((*c)));
    nameStart = nameTok.start;
    nameLen = nameTok.len;
    Comp_advance(&((*c)));
    }
    {
    Kind _m169 = Comp_curKind(&((*c)));
    if (_m169.tag == 20) {
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
    Kind _m170 = Comp_curKind(&((*c)));
    if (_m170.tag == 75) {
    Comp_advance(&((*c)));
    isRange = 1;
    hi = parseExpr_c_Comp(&((*c)));
    }
    else if (_m170.tag == 76) {
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
    { uint64_t __ret171 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 6, .data.For = {.varStart = nameStart, .varLen = nameLen, .isRange = isRange, .inclusive = inclusive, .iter = lo, .rangeHi = hi, .body = body, .isStruct = isStruct, .patStart = patStart, .patLen = patLen, .binds = Array_Bind_share(binds)}});
    Array_Bind_release(binds);
    return __ret171; }
    Array_Bind_release(binds);
}
uint64_t parseExprOrAssign_c_Comp(Comp* c) {
    uint64_t lhs = parseExpr_c_Comp(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    if (isAssignOp_k_Kind(k)) {
    int64_t op = kindCode_k_Kind(k);
    Comp_advance(&((*c)));
    uint64_t rhs = parseExpr_c_Comp(&((*c)));
    { uint64_t __ret172 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 1, .data.Assign = {.op = op, .target = lhs, .value = rhs}});
    return __ret172; }
    }
    { uint64_t __ret173 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 2, .data.ExprStmt = {.expr = lhs}});
    return __ret173; }
}
PatInfo parsePattern_c_Comp(Comp* c) {
    Tok firstTok = Comp_cur(&((*c)));
    long long isWildcard = 0;
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    uint64_t variantStart = 0;
    uint64_t variantLen = 0;
    Array_Bind binds = Array_Bind_new();
    long long isStruct = 0;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), firstTok.start, firstTok.len, (PlewString){"_", 1})) {
    isWildcard = 1;
    Comp_advance(&((*c)));
    }
    else {
    enumStart = firstTok.start;
    enumLen = firstTok.len;
    Comp_advance(&((*c)));
    long long popen = 0;
    {
    Kind _m174 = Comp_curKind(&((*c)));
    if (_m174.tag == 40) {
    Comp_advance(&((*c)));
    Tok vTok = Comp_cur(&((*c)));
    variantStart = vTok.start;
    variantLen = vTok.len;
    Comp_advance(&((*c)));
    {
    Kind _m175 = Comp_curKind(&((*c)));
    if (_m175.tag == 36) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"destructure an enum variant with parentheses, e.g. `Optional.Some(val v)`", 73});
    }
    else if (_m175.tag == 32) {
    Comp_advance(&((*c)));
    popen = 1;
    }
    else {
    }
    }
    }
    else if (_m174.tag == 36) {
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
    Kind _m176 = Comp_curKind(&((*c)));
    if (_m176.tag == 33) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m176.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m176.tag == 0) {
    break;
    }
    else if (_m176.tag == 18) {
    Comp_advance(&((*c)));
    Tok bTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind_append_value_T(&(binds), (Bind){.nameStart = bTok.start, .nameLen = bTok.len, .fieldStart = bTok.start, .fieldLen = bTok.len});
    {
    Kind _m177 = Comp_curKind(&((*c)));
    if (_m177.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else if (_m176.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m178 = Comp_curKind(&((*c)));
    if (_m178.tag == 39) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m179 = Comp_curKind(&((*c)));
    if (_m179.tag == 18) {
    Comp_advance(&((*c)));
    Tok bTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind_append_value_T(&(binds), (Bind){.nameStart = bTok.start, .nameLen = bTok.len, .fieldStart = fTok.start, .fieldLen = fTok.len});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    {
    Kind _m180 = Comp_curKind(&((*c)));
    if (_m180.tag == 38) {
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
    { PatInfo __ret181 = (PatInfo){.isWildcard = isWildcard, .enumStart = enumStart, .enumLen = enumLen, .variantStart = variantStart, .variantLen = variantLen, .binds = Array_Bind_share(binds), .isStruct = isStruct};
    Array_Bind_release(binds);
    return __ret181; }
    Array_Bind_release(binds);
}
long long bindNamesMatch_c_Comp_a_ABind_b_ABind(Comp* c, Array_Bind a, Array_Bind b) {
    if ((long long)((a).count) != (long long)((b).count)) {
    { long long __ret182 = 0;
    return __ret182; }
    }
    uint64_t i = 0;
    while (i < (long long)((a).count)) {
    Bind an = Array_Bind_get(a, (long long)(i));
    long long found = 0;
    uint64_t j = 0;
    while (j < (long long)((b).count)) {
    Bind bn = Array_Bind_get(b, (long long)(j));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), an.nameStart, an.nameLen, bn.nameStart, bn.nameLen)) {
    found = 1;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (found) {
    }
    else {
    { long long __ret183 = 0;
    return __ret183; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret184 = 1;
    return __ret184; }
}
Array_PatInfo parseArmPatterns_c_Comp(Comp* c) {
    uint64_t startOff = Comp_cur(&((*c))).start;
    Array_PatInfo pats = Array_PatInfo_new();
    Array_PatInfo_append_value_T(&(pats), parsePattern_c_Comp(&((*c))));
    while (1) {
    {
    Kind _m185 = Comp_curKind(&((*c)));
    if (_m185.tag == 57) {
    Comp_advance(&((*c)));
    Comp_skipNewlines(&((*c)));
    Array_PatInfo_append_value_T(&(pats), parsePattern_c_Comp(&((*c))));
    }
    else {
    break;
    }
    }
    }
    {
    Kind _m186 = Comp_curKind(&((*c)));
    if (_m186.tag == 63) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    uint64_t pi = 1;
    while (pi < (long long)((pats).count)) {
    PatInfo p0 = PatInfo_share(Array_PatInfo_get(pats, (long long)(0)));
    PatInfo pn = PatInfo_share(Array_PatInfo_get(pats, (long long)(pi)));
    if (bindNamesMatch_c_Comp_a_ABind_b_ABind(&((*c)), Array_Bind_share(p0.binds), Array_Bind_share(pn.binds))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), startOff), (PlewString){"or-pattern alternatives must bind the same names", 48});
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    PatInfo_release(pn);
    PatInfo_release(p0);
    }
    { Array_PatInfo __ret187 = Array_PatInfo_share(pats);
    Array_PatInfo_release(pats);
    return __ret187; }
    Array_PatInfo_release(pats);
}
uint64_t parseArmBody_c_Comp(Comp* c) {
    {
    Kind _m188 = Comp_curKind(&((*c)));
    if (_m188.tag == 36) {
    { uint64_t __ret189 = parseBlock_c_Comp(&((*c)));
    return __ret189; }
    }
    else {
    uint64_t s = parseStmt_c_Comp(&((*c)));
    Array_U64 stmts = Array_U64_new();
    Array_U64_append_value_T(&(stmts), s);
    uint64_t id = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(stmts)});
    { uint64_t __ret190 = id;
    Array_U64_release(stmts);
    return __ret190; }
    Array_U64_release(stmts);
    }
    }
}
uint64_t parseMatch_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m191 = Comp_curKind(&((*c)));
    if (_m191.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_MatchArm arms = Array_MatchArm_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m192 = k;
    if (_m192.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m192.tag == 0) {
    break;
    }
    else {
    Array_PatInfo pats = parseArmPatterns_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseArmBody_c_Comp(&((*c)));
    {
    Array_PatInfo __fa193 = pats;
    for (long long __fi193 = 0; __fi193 < (long long)__fa193.count; __fi193++) {
        PatInfo pi = Array_PatInfo_get(__fa193, __fi193);
    Array_MatchArm_append_value_T(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = Array_Bind_share(pi.binds), .body = body, .isStruct = pi.isStruct});
    }
    }
    Array_PatInfo_release(pats);
    }
    }
    }
    { uint64_t __ret194 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 7, .data.Match = {.scrut = scrut, .arms = Array_MatchArm_share(arms)}});
    Array_MatchArm_release(arms);
    return __ret194; }
    Array_MatchArm_release(arms);
}
uint64_t parseMatchExpr_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t scrut = parseExpr_c_Comp(&((*c)));
    Comp_skipNewlines(&((*c)));
    {
    Kind _m195 = Comp_curKind(&((*c)));
    if (_m195.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_MatchArm arms = Array_MatchArm_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m196 = k;
    if (_m196.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m196.tag == 0) {
    break;
    }
    else {
    Array_PatInfo pats = parseArmPatterns_c_Comp(&((*c)));
    uint64_t body = parseExpr_c_Comp(&((*c)));
    {
    Array_PatInfo __fa197 = pats;
    for (long long __fi197 = 0; __fi197 < (long long)__fa197.count; __fi197++) {
        PatInfo pi = Array_PatInfo_get(__fa197, __fi197);
    Array_MatchArm_append_value_T(&(arms), (MatchArm){.isWildcard = pi.isWildcard, .enumStart = pi.enumStart, .enumLen = pi.enumLen, .variantStart = pi.variantStart, .variantLen = pi.variantLen, .binds = Array_Bind_share(pi.binds), .body = body, .isStruct = pi.isStruct});
    }
    }
    {
    Kind _m198 = Comp_curKind(&((*c)));
    if (_m198.tag == 38) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_PatInfo_release(pats);
    }
    }
    }
    { uint64_t __ret199 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = scrut, .arms = Array_MatchArm_share(arms)}});
    Array_MatchArm_release(arms);
    return __ret199; }
    Array_MatchArm_release(arms);
}
uint64_t parseStmt_c_Comp(Comp* c) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m200 = k;
    if (_m200.tag == 18) {
    { uint64_t __ret201 = parseLet_c_Comp_mutable_Bool(&((*c)), 0);
    return __ret201; }
    }
    else if (_m200.tag == 19) {
    Comp_advance(&((*c)));
    { uint64_t __ret202 = parseLet_c_Comp_mutable_Bool(&((*c)), 1);
    return __ret202; }
    }
    else if (_m200.tag == 10) {
    { uint64_t __ret203 = parseIf_c_Comp(&((*c)));
    return __ret203; }
    }
    else if (_m200.tag == 12) {
    { uint64_t __ret204 = parseWhile_c_Comp(&((*c)));
    return __ret204; }
    }
    else if (_m200.tag == 13) {
    { uint64_t __ret205 = parseFor_c_Comp(&((*c)));
    return __ret205; }
    }
    else if (_m200.tag == 9) {
    { uint64_t __ret206 = parseMatch_c_Comp(&((*c)));
    return __ret206; }
    }
    else if (_m200.tag == 14) {
    Comp_advance(&((*c)));
    { uint64_t __ret207 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 10});
    return __ret207; }
    }
    else if (_m200.tag == 15) {
    Comp_advance(&((*c)));
    { uint64_t __ret208 = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 11});
    return __ret208; }
    }
    else if (_m200.tag == 16) {
    { uint64_t __ret209 = parseReturn_c_Comp(&((*c)));
    return __ret209; }
    }
    else if (_m200.tag == 5) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"panic", 5})) {
    { uint64_t __ret210 = parsePanic_c_Comp(&((*c)));
    return __ret210; }
    }
    { uint64_t __ret211 = parseExprOrAssign_c_Comp(&((*c)));
    return __ret211; }
    }
    else if (_m200.tag == 17) {
    { uint64_t __ret212 = parseGive_c_Comp(&((*c)));
    return __ret212; }
    }
    else {
    { uint64_t __ret213 = parseExprOrAssign_c_Comp(&((*c)));
    return __ret213; }
    }
    }
}
uint64_t parseBlock_c_Comp(Comp* c) {
    {
    Kind _m214 = Comp_curKind(&((*c)));
    if (_m214.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_U64 stmts = Array_U64_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m215 = k;
    if (_m215.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m215.tag == 0) {
    break;
    }
    else {
    uint64_t s = parseStmt_c_Comp(&((*c)));
    Array_U64_append_value_T(&(stmts), s);
    }
    }
    }
    uint64_t id = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(stmts)});
    { uint64_t __ret216 = id;
    Array_U64_release(stmts);
    return __ret216; }
    Array_U64_release(stmts);
}
Array_Param parseParamList_c_Comp(Comp* c) {
    Array_Param params = Array_Param_new();
    {
    Kind _m217 = Comp_curKind(&((*c)));
    if (_m217.tag == 32) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m218 = k;
    if (_m218.tag == 33) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m218.tag == 0) {
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
    Kind _m219 = Comp_curKind(&((*c)));
    if (_m219.tag == 61) {
    if ((Comp_peekKind_off_U64(&((*c)), 1)).tag == 39) {
    Comp_advance(&((*c)));
    pNoLabel = 1;
    }
    }
    else {
    }
    }
    {
    Kind _m220 = Comp_curKind(&((*c)));
    if (_m220.tag == 39) {
    Comp_advance(&((*c)));
    {
    Kind _m221 = Comp_curKind(&((*c)));
    if (_m221.tag == 22) {
    Comp_advance(&((*c)));
    pIsInout = 1;
    }
    else if (_m221.tag == 25) {
    Comp_advance(&((*c)));
    pIsMove = 1;
    }
    else if (_m221.tag == 26) {
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
    Kind _m222 = Comp_curKind(&((*c)));
    if (_m222.tag == 41) {
    Comp_advance(&((*c)));
    pHasDefault = 1;
    pDefault = parseExpr_c_Comp(&((*c)));
    }
    else {
    }
    }
    Array_Param_append_value_T(&(params), (Param){.nameStart = pTok.start, .nameLen = pTok.len, .tyStart = pTyStart, .tyLen = pTyLen, .tyIsArray = pTyIsArray, .ty = pTyRef, .isInout = pIsInout, .isMove = pIsMove, .isBorrow = pIsBorrow, .noLabel = pNoLabel, .hasDefault = pHasDefault, .defaultExpr = pDefault});
    {
    Kind _m223 = Comp_curKind(&((*c)));
    if (_m223.tag == 38) {
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
    { Array_Param __ret224 = Array_Param_share(params);
    Array_Param_release(params);
    return __ret224; }
    Array_Param_release(params);
}
void parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(Comp* c, long long hasRecv, uint64_t recvStart, uint64_t recvLen, long long selfInout, long long selfMove, Array_Bind implParams, long long traitImpl, long long isAssoc, long long isAsync, long long isPub) {
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind ownParams = parseTypeParams_c_Comp(&((*c)));
    Array_Bind typeParams = Array_Bind_new();
    uint64_t ipi = 0;
    while (ipi < (long long)((implParams).count)) {
    Array_Bind_append_value_T(&(typeParams), Array_Bind_get(implParams, (long long)(ipi)));
    ipi = ({ uint64_t __ov; if (__builtin_add_overflow((ipi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t opi = 0;
    while (opi < (long long)((ownParams).count)) {
    Array_Bind_append_value_T(&(typeParams), Array_Bind_get(ownParams, (long long)(opi)));
    opi = ({ uint64_t __ov; if (__builtin_add_overflow((opi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Param params = parseParamList_c_Comp(&((*c)));
    long long hasRet = 0;
    uint64_t retStart = 0;
    uint64_t retLen = 0;
    long long retIsArray = 0;
    uint64_t retRef = 0;
    {
    Kind _m225 = Comp_curKind(&((*c)));
    if (_m225.tag == 62) {
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
    Array_Bind boundParams = parseWhereClause_c_Comp(&((*c)));
    Array_Bind boundTraits = Array_Bind_share((*c).curWhereTraits);
    if (traitImpl) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"via", 3})) {
    Comp_advance(&((*c)));
    Tok realTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_MethodAlias_append_value_T(&((*c).methodAliases), (MethodAlias){.recvStart = recvStart, .recvLen = recvLen, .aliasStart = nameTok.start, .aliasLen = nameTok.len, .realStart = realTok.start, .realLen = realTok.len});
    Array_Func_append_value_T(&((*c).curWitnessed), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = Array_Bind_share(typeParams), .params = Array_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = 0, .hasRecv = 0, .recvStart = 0, .recvLen = 0, .selfInout = 0, .selfMove = 0, .isAssoc = 0, .isAsync = 0, .isExtern = 0, .isPub = 0, .isProvided = 0});
    Array_Bind_release(boundTraits);
    Array_Bind_release(boundParams);
    Array_Param_release(params);
    Array_Bind_release(typeParams);
    Array_Bind_release(ownParams);
    return;
    }
    Array_Func_append_value_T(&((*c).curWitnessed), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = Array_Bind_share(typeParams), .params = Array_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = 0, .hasRecv = 0, .recvStart = 0, .recvLen = 0, .selfInout = 0, .selfMove = 0, .isAssoc = 0, .isAsync = 0, .isExtern = 0, .isPub = 0, .isProvided = 0});
    }
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    uint64_t fnIdx = (long long)(((*c).funcs).count);
    Array_Func_append_value_T(&((*c).funcs), (Func){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = Array_Bind_share(typeParams), .params = Array_Param_share(params), .hasRet = hasRet, .retStart = retStart, .retLen = retLen, .retIsArray = retIsArray, .retTy = retRef, .body = body, .hasRecv = hasRecv, .recvStart = recvStart, .recvLen = recvLen, .selfInout = selfInout, .selfMove = selfMove, .isAssoc = isAssoc, .isAsync = isAsync, .isExtern = 0, .isPub = isPub, .isProvided = 0});
    uint64_t wbi = 0;
    while (wbi < (long long)((boundParams).count)) {
    Bind bp = Array_Bind_get(boundParams, (long long)(wbi));
    Bind bt = Array_Bind_get(boundTraits, (long long)(wbi));
    Array_FuncBound_append_value_T(&((*c).funcBounds), (FuncBound){.fnIdx = fnIdx, .paramStart = bp.nameStart, .paramLen = bp.nameLen, .traitStart = bt.nameStart, .traitLen = bt.nameLen});
    wbi = ({ uint64_t __ov; if (__builtin_add_overflow((wbi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t ibi = 0;
    while (ibi < (long long)(((*c).curImplBoundParams).count)) {
    Bind ibp = Array_Bind_get((*c).curImplBoundParams, (long long)(ibi));
    Bind ibt = Array_Bind_get((*c).curImplBoundTraits, (long long)(ibi));
    Array_FuncBound_append_value_T(&((*c).funcBounds), (FuncBound){.fnIdx = fnIdx, .paramStart = ibp.nameStart, .paramLen = ibp.nameLen, .traitStart = ibt.nameStart, .traitLen = ibt.nameLen});
    ibi = ({ uint64_t __ov; if (__builtin_add_overflow((ibi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Bind_release(boundTraits);
    Array_Bind_release(boundParams);
    Array_Param_release(params);
    Array_Bind_release(typeParams);
    Array_Bind_release(ownParams);
}
Array_Bind parseWhereClause_c_Comp(Comp* c) {
    Array_Bind boundParams = Array_Bind_new();
    Array_Bind boundTraits = Array_Bind_new();
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"where", 5})) {
    Comp_advance(&((*c)));
    long long cont = 1;
    while (cont) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m226 = Comp_curKind(&((*c)));
    if (_m226.tag == 5) {
    Tok pTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m227 = Comp_curKind(&((*c)));
    if (_m227.tag == 39) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    long long moreTraits = 1;
    while (moreTraits) {
    {
    Kind _m228 = Comp_curKind(&((*c)));
    if (_m228.tag == 5) {
    Tok tTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind_append_value_T(&(boundParams), (Bind){.nameStart = pTok.start, .nameLen = pTok.len, .fieldStart = pTok.start, .fieldLen = pTok.len});
    Array_Bind_append_value_T(&(boundTraits), (Bind){.nameStart = tTok.start, .nameLen = tTok.len, .fieldStart = tTok.start, .fieldLen = tTok.len});
    }
    else {
    }
    }
    {
    Kind _m229 = Comp_curKind(&((*c)));
    if (_m229.tag == 48) {
    Comp_advance(&((*c)));
    }
    else {
    moreTraits = 0;
    }
    }
    }
    {
    Kind _m230 = Comp_curKind(&((*c)));
    if (_m230.tag == 38) {
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
    (*c).curWhereTraits = Array_Bind_share(boundTraits);
    { Array_Bind __ret231 = Array_Bind_share(boundParams);
    Array_Bind_release(boundTraits);
    Array_Bind_release(boundParams);
    return __ret231; }
    Array_Bind_release(boundTraits);
    Array_Bind_release(boundParams);
}
void parseFunc_c_Comp_isAsync_Bool(Comp* c, long long isAsync) {
    Comp_advance(&((*c)));
    Array_Bind noParams = Array_Bind_new();
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(&((*c)), 0, 0, 0, 0, 0, Array_Bind_share(noParams), 0, 0, isAsync, 0);
    Array_Bind_release(noParams);
}
void parseImpl_c_Comp_isPub_Bool(Comp* c, long long isPub) {
    Comp_advance(&((*c)));
    Array_Bind implParams = parseTypeParams_c_Comp(&((*c)));
    Tok headTok = Comp_cur(&((*c)));
    PType recvPty = parseTypeTok_c_Comp(&((*c)));
    uint64_t recvStart = recvPty.start;
    uint64_t recvLen = recvPty.len;
    if (recvPty.isArray) {
    recvStart = headTok.start;
    recvLen = headTok.len;
    }
    long long isTraitImpl = 0;
    uint64_t traitStart = 0;
    uint64_t traitLen = 0;
    {
    Kind _m232 = Comp_curKind(&((*c)));
    if (_m232.tag == 21) {
    Comp_advance(&((*c)));
    Tok traitTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    isTraitImpl = 1;
    traitStart = traitTok.start;
    traitLen = traitTok.len;
    (*c).curWitnessed = Array_Func_new();
    }
    else {
    }
    }
    Array_Bind implBoundParams = parseWhereClause_c_Comp(&((*c)));
    (*c).curImplBoundParams = Array_Bind_share(implBoundParams);
    (*c).curImplBoundTraits = Array_Bind_share((*c).curWhereTraits);
    {
    Kind _m233 = Comp_curKind(&((*c)));
    if (_m233.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m234 = k;
    if (_m234.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m234.tag == 0) {
    break;
    }
    else if (_m234.tag == 22) {
    Comp_advance(&((*c)));
    {
    Kind _m235 = Comp_curKind(&((*c)));
    if (_m235.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(&((*c)), 1, recvStart, recvLen, 1, 0, Array_Bind_share(implParams), isTraitImpl, 0, 0, isPub);
    }
    else if (_m234.tag == 6) {
    Comp_advance(&((*c)));
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(&((*c)), 1, recvStart, recvLen, 0, 0, Array_Bind_share(implParams), isTraitImpl, 0, 0, isPub);
    }
    else if (_m234.tag == 27) {
    Comp_advance(&((*c)));
    long long asyncMove = 0;
    {
    Kind _m236 = Comp_curKind(&((*c)));
    if (_m236.tag == 25) {
    Comp_advance(&((*c)));
    asyncMove = 1;
    }
    else {
    }
    }
    {
    Kind _m237 = Comp_curKind(&((*c)));
    if (_m237.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(&((*c)), 1, recvStart, recvLen, 0, asyncMove, Array_Bind_share(implParams), isTraitImpl, 0, 1, isPub);
    }
    else if (_m234.tag == 25) {
    Comp_advance(&((*c)));
    {
    Kind _m238 = Comp_curKind(&((*c)));
    if (_m238.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(&((*c)), 1, recvStart, recvLen, 0, 1, Array_Bind_share(implParams), isTraitImpl, 0, 0, isPub);
    }
    else if (_m234.tag == 26) {
    Comp_advance(&((*c)));
    {
    Kind _m239 = Comp_curKind(&((*c)));
    if (_m239.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(&((*c)), 1, recvStart, recvLen, 0, 0, Array_Bind_share(implParams), isTraitImpl, 0, 0, isPub);
    }
    else if (_m234.tag == 24) {
    Tok deinitTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    Array_Param noParams = Array_Param_new();
    Array_Bind noTypeParams = Array_Bind_new();
    Array_Func_append_value_T(&((*c).funcs), (Func){.nameStart = deinitTok.start, .nameLen = deinitTok.len, .typeParams = Array_Bind_share(noTypeParams), .params = Array_Param_share(noParams), .hasRet = 0, .retStart = 0, .retLen = 0, .retIsArray = 0, .retTy = 0, .body = body, .hasRecv = 1, .recvStart = recvStart, .recvLen = recvLen, .selfInout = 0, .selfMove = 0, .isAssoc = 0, .isAsync = 0, .isExtern = 0, .isPub = 0, .isProvided = 0});
    Array_Bind_append_value_T(&((*c).deinits), (Bind){.nameStart = recvStart, .nameLen = recvLen, .fieldStart = recvStart, .fieldLen = recvLen});
    Array_Bind_release(noTypeParams);
    Array_Param_release(noParams);
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
    parseFuncCommon_c_Comp_hasRecv_Bool_recvStart_U64_recvLen_U64_selfInout_Bool_selfMove_Bool_implParams_ABind_traitImpl_Bool_isAssoc_Bool_isAsync_Bool_isPub_Bool(&((*c)), 0, recvStart, recvLen, 0, 0, Array_Bind_share(implParams), isTraitImpl, 1, 0, isPub);
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"type", 4})) {
    Comp_advance(&((*c)));
    {
    Kind _m241 = Comp_curKind(&((*c)));
    if (_m241.tag == 5) {
    Tok atName = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    {
    Kind _m242 = Comp_curKind(&((*c)));
    if (_m242.tag == 41) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    PType cty = parseTypeTok_c_Comp(&((*c)));
    recordArrayElem_c_Comp_ty_PType(&((*c)), cty);
    Array_AssocBinding_append_value_T(&((*c).assocBindings), (AssocBinding){.recvStart = recvStart, .recvLen = recvLen, .nameStart = atName.start, .nameLen = atName.len, .tyStart = cty.start, .tyLen = cty.len, .tyIsArray = cty.isArray, .ty = cty.ref});
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
    if (isTraitImpl) {
    Array_Conform_append_value_T(&((*c).conforms), (Conform){.typeStart = recvStart, .typeLen = recvLen, .traitStart = traitStart, .traitLen = traitLen, .derived = 0, .witnessed = Array_Func_share((*c).curWitnessed)});
    }
    Array_Bind noBounds = Array_Bind_new();
    (*c).curImplBoundParams = Array_Bind_share(noBounds);
    (*c).curImplBoundTraits = Array_Bind_share(noBounds);
    Array_Bind_release(noBounds);
    Array_Bind_release(implBoundParams);
    Array_Bind_release(implParams);
}
void parseTrait_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind supertraits = Array_Bind_new();
    {
    Kind _m243 = Comp_curKind(&((*c)));
    if (_m243.tag == 39) {
    Comp_advance(&((*c)));
    long long more = 1;
    while (more) {
    {
    Kind _m244 = Comp_curKind(&((*c)));
    if (_m244.tag == 5) {
    Tok st = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind_append_value_T(&(supertraits), (Bind){.nameStart = st.start, .nameLen = st.len, .fieldStart = st.start, .fieldLen = st.len});
    }
    else {
    }
    }
    {
    Kind _m245 = Comp_curKind(&((*c)));
    if (_m245.tag == 48) {
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
    Kind _m246 = Comp_curKind(&((*c)));
    if (_m246.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_Func reqs = Array_Func_new();
    Array_Bind assocTypes = Array_Bind_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m247 = k;
    if (_m247.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m247.tag == 0) {
    break;
    }
    else if (_m247.tag == 6) {
    Comp_advance(&((*c)));
    Array_Func_append_value_T(&(reqs), parseReqSig_c_Comp_isAssoc_Bool_isExtern_Bool(&((*c)), 0, 0));
    }
    else if (_m247.tag == 22) {
    Comp_advance(&((*c)));
    {
    Kind _m248 = Comp_curKind(&((*c)));
    if (_m248.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_Func_append_value_T(&(reqs), parseReqSig_c_Comp_isAssoc_Bool_isExtern_Bool(&((*c)), 0, 0));
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"assoc", 5})) {
    Comp_advance(&((*c)));
    {
    Kind _m249 = Comp_curKind(&((*c)));
    if (_m249.tag == 6) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_Func_append_value_T(&(reqs), parseReqSig_c_Comp_isAssoc_Bool_isExtern_Bool(&((*c)), 1, 0));
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"type", 4})) {
    Comp_advance(&((*c)));
    {
    Kind _m250 = Comp_curKind(&((*c)));
    if (_m250.tag == 5) {
    Tok at = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind_append_value_T(&(assocTypes), (Bind){.nameStart = at.start, .nameLen = at.len, .fieldStart = at.start, .fieldLen = at.len});
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
    Array_TraitDef_append_value_T(&((*c).traits), (TraitDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .supertraits = Array_Bind_share(supertraits), .reqs = Array_Func_share(reqs), .assocTypes = Array_Bind_share(assocTypes)});
    Array_Bind_release(assocTypes);
    Array_Func_release(reqs);
    Array_Bind_release(supertraits);
}
Func parseReqSig_c_Comp_isAssoc_Bool_isExtern_Bool(Comp* c, long long isAssoc, long long isExtern) {
    Tok reqTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind tps = parseTypeParams_c_Comp(&((*c)));
    Array_Param ps = parseParamList_c_Comp(&((*c)));
    long long hasRet = 0;
    uint64_t rs = 0;
    uint64_t rl = 0;
    long long ria = 0;
    uint64_t rr = 0;
    {
    Kind _m251 = Comp_curKind(&((*c)));
    if (_m251.tag == 62) {
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
    Func sig = (Func){.nameStart = reqTok.start, .nameLen = reqTok.len, .typeParams = Array_Bind_share(tps), .params = Array_Param_share(ps), .hasRet = hasRet, .retStart = rs, .retLen = rl, .retIsArray = ria, .retTy = rr, .body = 0, .hasRecv = 0, .recvStart = 0, .recvLen = 0, .selfInout = 0, .selfMove = 0, .isAssoc = isAssoc, .isAsync = 0, .isExtern = isExtern, .isPub = 0, .isProvided = 0};
    { Func __ret252 = Func_share(sig);
    Func_release(sig);
    Array_Param_release(ps);
    Array_Bind_release(tps);
    return __ret252; }
    Func_release(sig);
    Array_Param_release(ps);
    Array_Bind_release(tps);
}
void parseExtern_c_Comp(Comp* c) {
    Tok externTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    long long abiOk = 0;
    {
    Kind _m253 = Comp_curKind(&((*c)));
    if (_m253.tag == 3) {
    Tok t = Comp_cur(&((*c)));
    if (t.len >= 2) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), ({ uint64_t __ov; if (__builtin_add_overflow((t.start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), ({ uint64_t __ov; if (__builtin_sub_overflow((t.len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), (PlewString){"plew-intrinsic", 14})) {
    abiOk = 1;
    }
    }
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    if (abiOk) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), externTok.start), (PlewString){"only `extern \"plew-intrinsic\"` blocks are supported for now", 59});
    }
    {
    Kind _m254 = Comp_curKind(&((*c)));
    if (_m254.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    Comp_skipNewlines(&((*c)));
    {
    Kind _m255 = Comp_curKind(&((*c)));
    if (_m255.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m255.tag == 0) {
    break;
    }
    else if (_m255.tag == 6) {
    Comp_advance(&((*c)));
    Array_Func_append_value_T(&((*c).funcs), parseReqSig_c_Comp_isAssoc_Bool_isExtern_Bool(&((*c)), 0, 1));
    }
    else if (_m255.tag == 7) {
    Comp_advance(&((*c)));
    Tok sTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind noTP = Array_Bind_new();
    Array_FieldDef noFields = Array_FieldDef_new();
    Array_StructDef_append_value_T(&((*c).structs), (StructDef){.nameStart = sTok.start, .nameLen = sTok.len, .typeParams = Array_Bind_share(noTP), .fields = Array_FieldDef_share(noFields), .isUnique = 0, .isExtern = 1});
    Array_FieldDef_release(noFields);
    Array_Bind_release(noTP);
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
}
void parseStruct_c_Comp_isUnique_Bool(Comp* c, long long isUnique) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind typeParams = parseTypeParams_c_Comp(&((*c)));
    {
    Kind _m256 = Comp_curKind(&((*c)));
    if (_m256.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_FieldDef fields = Array_FieldDef_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m257 = k;
    if (_m257.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m257.tag == 0) {
    break;
    }
    else if (_m257.tag == 38) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"struct fields are separated by newlines, not commas", 51});
    }
    else if (_m257.tag == 24) {
    Tok deinitTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Comp_skipNewlines(&((*c)));
    uint64_t body = parseBlock_c_Comp(&((*c)));
    Array_Param noParams = Array_Param_new();
    Array_Bind noTypeParams = Array_Bind_new();
    Array_Func_append_value_T(&((*c).funcs), (Func){.nameStart = deinitTok.start, .nameLen = deinitTok.len, .typeParams = Array_Bind_share(noTypeParams), .params = Array_Param_share(noParams), .hasRet = 0, .retStart = 0, .retLen = 0, .retIsArray = 0, .retTy = 0, .body = body, .hasRecv = 1, .recvStart = nameTok.start, .recvLen = nameTok.len, .selfInout = 0, .selfMove = 0, .isAssoc = 0, .isAsync = 0, .isExtern = 0, .isPub = 0, .isProvided = 0});
    Array_Bind_append_value_T(&((*c).deinits), (Bind){.nameStart = nameTok.start, .nameLen = nameTok.len, .fieldStart = nameTok.start, .fieldLen = nameTok.len});
    Array_Bind_release(noTypeParams);
    Array_Param_release(noParams);
    }
    else {
    uint64_t vis = 0;
    {
    Kind _m258 = Comp_curKind(&((*c)));
    if (_m258.tag == 5) {
    Tok pubTok = Comp_cur(&((*c)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), pubTok.start, pubTok.len, (PlewString){"pub", 3})) {
    Comp_advance(&((*c)));
    vis = 2;
    {
    Kind _m259 = Comp_curKind(&((*c)));
    if (_m259.tag == 32) {
    Comp_advance(&((*c)));
    {
    Kind _m260 = Comp_curKind(&((*c)));
    if (_m260.tag == 5) {
    Tok qt = Comp_cur(&((*c)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), qt.start, qt.len, (PlewString){"get", 3})) {
    vis = 1;
    }
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    {
    Kind _m261 = Comp_curKind(&((*c)));
    if (_m261.tag == 33) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    }
    else {
    }
    }
    }
    }
    else {
    }
    }
    long long isMut = 0;
    {
    Kind _m262 = Comp_curKind(&((*c)));
    if (_m262.tag == 19) {
    Comp_advance(&((*c)));
    isMut = 1;
    }
    else {
    }
    }
    {
    Kind _m263 = Comp_curKind(&((*c)));
    if (_m263.tag == 18) {
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
    Kind _m264 = Comp_curKind(&((*c)));
    if (_m264.tag == 39) {
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
    Kind _m265 = Comp_curKind(&((*c)));
    if (_m265.tag == 41) {
    Comp_advance(&((*c)));
    defaultVal = parseExpr_c_Comp(&((*c)));
    hasDefault = 1;
    }
    else {
    }
    }
    Array_FieldDef_append_value_T(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .isMut = isMut, .hasDefault = hasDefault, .defaultVal = defaultVal, .vis = vis});
    }
    }
    }
    Array_StructDef_append_value_T(&((*c).structs), (StructDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = Array_Bind_share(typeParams), .fields = Array_FieldDef_share(fields), .isUnique = isUnique, .isExtern = 0});
    drainDerives_c_Comp_typeStart_U64_typeLen_U64_isEnum_Bool(&((*c)), nameTok.start, nameTok.len, 0);
    Array_FieldDef_release(fields);
    Array_Bind_release(typeParams);
}
void parseEnum_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    Tok nameTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind typeParams = parseTypeParams_c_Comp(&((*c)));
    {
    Kind _m266 = Comp_curKind(&((*c)));
    if (_m266.tag == 36) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    Array_Variant variants = Array_Variant_new();
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m267 = k;
    if (_m267.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m267.tag == 0) {
    break;
    }
    else if (_m267.tag == 5) {
    Tok vTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_FieldDef fields = Array_FieldDef_new();
    long long vopen = 0;
    {
    Kind _m268 = Comp_curKind(&((*c)));
    if (_m268.tag == 36) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), Comp_cur(&((*c))).start), (PlewString){"enum variant payloads use parentheses, e.g. `Foo(x: I32, y: I32)`", 65});
    }
    else if (_m268.tag == 32) {
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
    Kind _m269 = Comp_curKind(&((*c)));
    if (_m269.tag == 33) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m269.tag == 0) {
    break;
    }
    else if (_m269.tag == 5) {
    Tok fTok = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    uint64_t tyStart = 0;
    uint64_t tyLen = 0;
    long long tyIsArray = 0;
    uint64_t tyRef = 0;
    {
    Kind _m270 = Comp_curKind(&((*c)));
    if (_m270.tag == 39) {
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
    Array_FieldDef_append_value_T(&(fields), (FieldDef){.nameStart = fTok.start, .nameLen = fTok.len, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = tyIsArray, .ty = tyRef, .isMut = 0, .hasDefault = 0, .defaultVal = 0, .vis = 0});
    {
    Kind _m271 = Comp_curKind(&((*c)));
    if (_m271.tag == 38) {
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
    Array_Variant_append_value_T(&(variants), (Variant){.nameStart = vTok.start, .nameLen = vTok.len, .fields = Array_FieldDef_share(fields)});
    Array_FieldDef_release(fields);
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    Array_EnumDef_append_value_T(&((*c).enums), (EnumDef){.nameStart = nameTok.start, .nameLen = nameTok.len, .typeParams = Array_Bind_share(typeParams), .variants = Array_Variant_share(variants)});
    drainDerives_c_Comp_typeStart_U64_typeLen_U64_isEnum_Bool(&((*c)), nameTok.start, nameTok.len, 1);
    Array_Variant_release(variants);
    Array_Bind_release(typeParams);
}
void parseDirective_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    {
    Kind _m272 = Comp_curKind(&((*c)));
    if (_m272.tag == 34) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
    while (1) {
    {
    Kind _m273 = Comp_curKind(&((*c)));
    if (_m273.tag == 35) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m273.tag == 0) {
    break;
    }
    else if (_m273.tag == 38) {
    Comp_advance(&((*c)));
    }
    else if (_m273.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    Comp_advance(&((*c)));
    Array_Bind_append_value_T(&((*c).pendingDerives), (Bind){.nameStart = t.start, .nameLen = t.len, .fieldStart = t.start, .fieldLen = t.len});
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
}
void drainDerives_c_Comp_typeStart_U64_typeLen_U64_isEnum_Bool(Comp* c, uint64_t typeStart, uint64_t typeLen, long long isEnum) {
    uint64_t i = 0;
    while (i < (long long)(((*c).pendingDerives).count)) {
    Bind d = Array_Bind_get((*c).pendingDerives, (long long)(i));
    Array_DeriveReq_append_value_T(&((*c).derives), (DeriveReq){.typeStart = typeStart, .typeLen = typeLen, .isEnum = isEnum, .nameStart = d.nameStart, .nameLen = d.nameLen});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).pendingDerives = Array_Bind_new();
}
Bind internBytes_c_Comp_s_String(Comp* c, PlewString s) {
    uint64_t start = (long long)(((*c).bytes).count);
    Array_U8 sb = Array_U8_share(({ PlewString __s = s; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; }));
    uint64_t i = 0;
    while (i < (long long)((sb).count)) {
    Array_U8_append_value_T(&((*c).bytes), Array_U8_get(sb, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Bind __ret274 = (Bind){.nameStart = start, .nameLen = (long long)((sb).count), .fieldStart = start, .fieldLen = (long long)((sb).count)};
    Array_U8_release(sb);
    return __ret274; }
    Array_U8_release(sb);
}
Param synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(Bind nameSpan, uint64_t tyStart, uint64_t tyLen) {
    Param p = (Param){.nameStart = nameSpan.nameStart, .nameLen = nameSpan.nameLen, .tyStart = tyStart, .tyLen = tyLen, .tyIsArray = 0, .ty = 0, .isInout = 0, .isMove = 0, .isBorrow = 0, .noLabel = 0, .hasDefault = 0, .defaultExpr = 0};
    { Param __ret275 = p;
    return __ret275; }
}
void synthStructEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(Comp* c, DeriveReq d, Bind eqN, Bind lhsN, Bind rhsN, Bind boolN, Bind eqTrait) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), d.typeStart, d.typeLen);
    if (si >= (long long)(((*c).structs).count)) {
    return;
    }
    Array_FieldDef fields = Array_FieldDef_share(Array_StructDef_get((*c).structs, (long long)(si)).fields);
    Array_Param params = Array_Param_new();
    Array_Param_append_value_T(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(lhsN, d.typeStart, d.typeLen));
    Array_Param_append_value_T(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(rhsN, d.typeStart, d.typeLen));
    uint64_t lhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = lhsN.nameStart, .len = lhsN.nameLen}});
    uint64_t rhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = rhsN.nameStart, .len = rhsN.nameLen}});
    uint64_t acc = 0;
    long long first = 1;
    uint64_t fi = 0;
    while (fi < (long long)((fields).count)) {
    FieldDef f = Array_FieldDef_get(fields, (long long)(fi));
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
    uint64_t ret = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = acc, .hasValue = 1}});
    Array_U64 stmts = Array_U64_new();
    Array_U64_append_value_T(&(stmts), ret);
    uint64_t blkId = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(stmts)});
    Array_Bind noTP = Array_Bind_new();
    Array_Func_append_value_T(&((*c).funcs), (Func){.nameStart = eqN.nameStart, .nameLen = eqN.nameLen, .typeParams = Array_Bind_share(noTP), .params = Array_Param_share(params), .hasRet = 1, .retStart = boolN.nameStart, .retLen = boolN.nameLen, .retIsArray = 0, .retTy = 0, .body = blkId, .hasRecv = 0, .recvStart = d.typeStart, .recvLen = d.typeLen, .selfInout = 0, .selfMove = 0, .isAssoc = 1, .isAsync = 0, .isExtern = 0, .isPub = 0, .isProvided = 0});
    Array_Func wit = Array_Func_new();
    Array_Conform_append_value_T(&((*c).conforms), (Conform){.typeStart = d.typeStart, .typeLen = d.typeLen, .traitStart = eqTrait.nameStart, .traitLen = eqTrait.nameLen, .derived = 1, .witnessed = Array_Func_share(wit)});
    Array_Func_release(wit);
    Array_Bind_release(noTP);
    Array_U64_release(stmts);
    Array_Param_release(params);
    Array_FieldDef_release(fields);
}
unsigned char digitByte_d_U64(uint64_t d) {
    if (d == 0) {
    { unsigned char __ret276 = 48;
    return __ret276; }
    }
    if (d == 1) {
    { unsigned char __ret277 = 49;
    return __ret277; }
    }
    if (d == 2) {
    { unsigned char __ret278 = 50;
    return __ret278; }
    }
    if (d == 3) {
    { unsigned char __ret279 = 51;
    return __ret279; }
    }
    if (d == 4) {
    { unsigned char __ret280 = 52;
    return __ret280; }
    }
    if (d == 5) {
    { unsigned char __ret281 = 53;
    return __ret281; }
    }
    if (d == 6) {
    { unsigned char __ret282 = 54;
    return __ret282; }
    }
    if (d == 7) {
    { unsigned char __ret283 = 55;
    return __ret283; }
    }
    if (d == 8) {
    { unsigned char __ret284 = 56;
    return __ret284; }
    }
    { unsigned char __ret285 = 57;
    return __ret285; }
}
void appendU64Digits_c_Comp_n_U64(Comp* c, uint64_t n) {
    if (n >= 10) {
    appendU64Digits_c_Comp_n_U64(&((*c)), ({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); __dl / __dr; }));
    }
    Array_U8_append_value_T(&((*c).bytes), digitByte_d_U64(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); __dl % __dr; })));
}
Bind internName_c_Comp_prefix_U8_n_U64(Comp* c, unsigned char prefix, uint64_t n) {
    uint64_t start = (long long)(((*c).bytes).count);
    Array_U8_append_value_T(&((*c).bytes), prefix);
    appendU64Digits_c_Comp_n_U64(&((*c)), n);
    uint64_t len = ({ uint64_t __ov; if (__builtin_sub_overflow(((long long)(((*c).bytes).count)), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    { Bind __ret286 = (Bind){.nameStart = start, .nameLen = len, .fieldStart = start, .fieldLen = len};
    return __ret286; }
}
uint64_t enumIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).enums).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_EnumDef_get((*c).enums, (long long)(i)).nameStart, Array_EnumDef_get((*c).enums, (long long)(i)).nameLen, start, len)) {
    { uint64_t __ret287 = i;
    return __ret287; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret288 = (long long)(((*c).enums).count);
    return __ret288; }
}
uint64_t synthBool_c_Comp_v_I64(Comp* c, int64_t v) {
    { uint64_t __ret289 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 0, .data.Int = {.value = v, .offset = 0, .isBool = 1, .tyStart = 0, .tyLen = 0}});
    return __ret289; }
}
void synthEnumEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(Comp* c, DeriveReq d, Bind eqN, Bind lhsN, Bind rhsN, Bind boolN, Bind eqTrait) {
    uint64_t ei = enumIndexByName_c_Comp_start_U64_len_U64(&((*c)), d.typeStart, d.typeLen);
    if (ei >= (long long)(((*c).enums).count)) {
    return;
    }
    Array_Variant variants = Array_Variant_share(Array_EnumDef_get((*c).enums, (long long)(ei)).variants);
    Array_Param params = Array_Param_new();
    Array_Param_append_value_T(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(lhsN, d.typeStart, d.typeLen));
    Array_Param_append_value_T(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(rhsN, d.typeStart, d.typeLen));
    uint64_t lhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = lhsN.nameStart, .len = lhsN.nameLen}});
    uint64_t rhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = rhsN.nameStart, .len = rhsN.nameLen}});
    uint64_t counter = 0;
    Array_MatchArm outerArms = Array_MatchArm_new();
    uint64_t vi = 0;
    while (vi < (long long)((variants).count)) {
    Variant v = Variant_share(Array_Variant_get(variants, (long long)(vi)));
    Array_FieldDef flds = Array_FieldDef_share(v.fields);
    Array_Bind lhsBinds = Array_Bind_new();
    Array_Bind rhsBinds = Array_Bind_new();
    uint64_t payload = 0;
    long long firstp = 1;
    uint64_t fj = 0;
    while (fj < (long long)((flds).count)) {
    FieldDef f = Array_FieldDef_get(flds, (long long)(fj));
    Bind ln = internName_c_Comp_prefix_U8_n_U64(&((*c)), 76, counter);
    counter = ({ uint64_t __ov; if (__builtin_add_overflow((counter), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Bind rn = internName_c_Comp_prefix_U8_n_U64(&((*c)), 82, counter);
    counter = ({ uint64_t __ov; if (__builtin_add_overflow((counter), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_Bind_append_value_T(&(lhsBinds), (Bind){.nameStart = ln.nameStart, .nameLen = ln.nameLen, .fieldStart = f.nameStart, .fieldLen = f.nameLen});
    Array_Bind_append_value_T(&(rhsBinds), (Bind){.nameStart = rn.nameStart, .nameLen = rn.nameLen, .fieldStart = f.nameStart, .fieldLen = f.nameLen});
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
    Array_MatchArm innerArms = Array_MatchArm_new();
    Array_MatchArm_append_value_T(&(innerArms), (MatchArm){.isWildcard = 0, .enumStart = d.typeStart, .enumLen = d.typeLen, .variantStart = v.nameStart, .variantLen = v.nameLen, .binds = Array_Bind_share(rhsBinds), .body = payload, .isStruct = 0});
    Array_Bind noBinds = Array_Bind_new();
    Array_MatchArm_append_value_T(&(innerArms), (MatchArm){.isWildcard = 1, .enumStart = 0, .enumLen = 0, .variantStart = 0, .variantLen = 0, .binds = Array_Bind_share(noBinds), .body = synthBool_c_Comp_v_I64(&((*c)), 0), .isStruct = 0});
    uint64_t innerMatch = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = rhsId, .arms = Array_MatchArm_share(innerArms)}});
    Array_MatchArm_append_value_T(&(outerArms), (MatchArm){.isWildcard = 0, .enumStart = d.typeStart, .enumLen = d.typeLen, .variantStart = v.nameStart, .variantLen = v.nameLen, .binds = Array_Bind_share(lhsBinds), .body = innerMatch, .isStruct = 0});
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_Bind_release(noBinds);
    Array_MatchArm_release(innerArms);
    Array_Bind_release(rhsBinds);
    Array_Bind_release(lhsBinds);
    Array_FieldDef_release(flds);
    Variant_release(v);
    }
    uint64_t outerMatch = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 12, .data.MatchExpr = {.scrut = lhsId, .arms = Array_MatchArm_share(outerArms)}});
    uint64_t ret = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = outerMatch, .hasValue = 1}});
    Array_U64 stmts = Array_U64_new();
    Array_U64_append_value_T(&(stmts), ret);
    uint64_t blkId = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(stmts)});
    Array_Bind noTP = Array_Bind_new();
    Array_Func_append_value_T(&((*c).funcs), (Func){.nameStart = eqN.nameStart, .nameLen = eqN.nameLen, .typeParams = Array_Bind_share(noTP), .params = Array_Param_share(params), .hasRet = 1, .retStart = boolN.nameStart, .retLen = boolN.nameLen, .retIsArray = 0, .retTy = 0, .body = blkId, .hasRecv = 0, .recvStart = d.typeStart, .recvLen = d.typeLen, .selfInout = 0, .selfMove = 0, .isAssoc = 1, .isAsync = 0, .isExtern = 0, .isPub = 0, .isProvided = 0});
    Array_Func wit = Array_Func_new();
    Array_Conform_append_value_T(&((*c).conforms), (Conform){.typeStart = d.typeStart, .typeLen = d.typeLen, .traitStart = eqTrait.nameStart, .traitLen = eqTrait.nameLen, .derived = 1, .witnessed = Array_Func_share(wit)});
    Array_Func_release(wit);
    Array_Bind_release(noTP);
    Array_U64_release(stmts);
    Array_MatchArm_release(outerArms);
    Array_Param_release(params);
    Array_Variant_release(variants);
}
uint64_t synthOrdering_c_Comp_ordN_Bind_variantN_Bind(Comp* c, Bind ordN, Bind variantN) {
    Array_MakeField noFields = Array_MakeField_new();
    { uint64_t __ret290 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 6, .data.Make = {.typeStart = ordN.nameStart, .typeLen = ordN.nameLen, .variantStart = variantN.nameStart, .variantLen = variantN.nameLen, .isEnum = 1, .ty = 0, .fields = Array_MakeField_share(noFields)}});
    Array_MakeField_release(noFields);
    return __ret290; }
    Array_MakeField_release(noFields);
}
uint64_t synthReturnBlock_c_Comp_value_U64(Comp* c, uint64_t value) {
    uint64_t ret = Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = value, .hasValue = 1}});
    Array_U64 stmts = Array_U64_new();
    Array_U64_append_value_T(&(stmts), ret);
    uint64_t blkId = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(stmts)});
    { uint64_t __ret291 = blkId;
    Array_U64_release(stmts);
    return __ret291; }
    Array_U64_release(stmts);
}
void synthStructOrd_c_Comp_d_DeriveReq_cmpN_Bind_lhsN_Bind_rhsN_Bind_ordN_Bind_lessN_Bind_greaterN_Bind_equalN_Bind_ordTrait_Bind(Comp* c, DeriveReq d, Bind cmpN, Bind lhsN, Bind rhsN, Bind ordN, Bind lessN, Bind greaterN, Bind equalN, Bind ordTrait) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), d.typeStart, d.typeLen);
    if (si >= (long long)(((*c).structs).count)) {
    return;
    }
    Array_FieldDef fields = Array_FieldDef_share(Array_StructDef_get((*c).structs, (long long)(si)).fields);
    Array_Param params = Array_Param_new();
    Array_Param_append_value_T(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(lhsN, d.typeStart, d.typeLen));
    Array_Param_append_value_T(&(params), synthParam_nameSpan_Bind_tyStart_U64_tyLen_U64(rhsN, d.typeStart, d.typeLen));
    uint64_t lhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = lhsN.nameStart, .len = lhsN.nameLen}});
    uint64_t rhsId = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 1, .data.Ident = {.start = rhsN.nameStart, .len = rhsN.nameLen}});
    Array_U64 stmts = Array_U64_new();
    uint64_t fi = 0;
    while (fi < (long long)((fields).count)) {
    FieldDef f = Array_FieldDef_get(fields, (long long)(fi));
    uint64_t lf1 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = lhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t rf1 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = rhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t lt = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 52, .lhs = lf1, .rhs = rf1}});
    uint64_t lessBlk = synthReturnBlock_c_Comp_value_U64(&((*c)), synthOrdering_c_Comp_ordN_Bind_variantN_Bind(&((*c)), ordN, lessN));
    Array_U64_append_value_T(&(stmts), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.If = {.cond = lt, .thenBlk = lessBlk, .elseBlk = 0, .hasElse = 0}}));
    uint64_t lf2 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = lhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t rf2 = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 5, .data.Field = {.base = rhsId, .nameStart = f.nameStart, .nameLen = f.nameLen}});
    uint64_t gt = Comp_pushExpr_e_Expr(&((*c)), (Expr){.tag = 3, .data.Binary = {.op = 54, .lhs = lf2, .rhs = rf2}});
    uint64_t grBlk = synthReturnBlock_c_Comp_value_U64(&((*c)), synthOrdering_c_Comp_ordN_Bind_variantN_Bind(&((*c)), ordN, greaterN));
    Array_U64_append_value_T(&(stmts), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 4, .data.If = {.cond = gt, .thenBlk = grBlk, .elseBlk = 0, .hasElse = 0}}));
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_append_value_T(&(stmts), Comp_pushStmt_s_Stmt(&((*c)), (Stmt){.tag = 3, .data.Return = {.value = synthOrdering_c_Comp_ordN_Bind_variantN_Bind(&((*c)), ordN, equalN), .hasValue = 1}}));
    uint64_t blkId = (long long)(((*c).blocks).count);
    Array_Block_append_value_T(&((*c).blocks), (Block){.stmts = Array_U64_share(stmts)});
    Array_Bind noTP = Array_Bind_new();
    Array_Func_append_value_T(&((*c).funcs), (Func){.nameStart = cmpN.nameStart, .nameLen = cmpN.nameLen, .typeParams = Array_Bind_share(noTP), .params = Array_Param_share(params), .hasRet = 1, .retStart = ordN.nameStart, .retLen = ordN.nameLen, .retIsArray = 0, .retTy = 0, .body = blkId, .hasRecv = 0, .recvStart = d.typeStart, .recvLen = d.typeLen, .selfInout = 0, .selfMove = 0, .isAssoc = 1, .isAsync = 0, .isExtern = 0, .isPub = 0, .isProvided = 0});
    Array_Func wit = Array_Func_new();
    Array_Conform_append_value_T(&((*c).conforms), (Conform){.typeStart = d.typeStart, .typeLen = d.typeLen, .traitStart = ordTrait.nameStart, .traitLen = ordTrait.nameLen, .derived = 1, .witnessed = Array_Func_share(wit)});
    Array_Func_release(wit);
    Array_Bind_release(noTP);
    Array_U64_release(stmts);
    Array_Param_release(params);
    Array_FieldDef_release(fields);
}
void synthesizeDerives_c_Comp(Comp* c) {
    if ((long long)(((*c).derives).count) == 0) {
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
    while (i < (long long)(((*c).derives).count)) {
    DeriveReq d = Array_DeriveReq_get((*c).derives, (long long)(i));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), d.nameStart, d.nameLen, (PlewString){"Eq", 2})) {
    if (d.isEnum) {
    synthEnumEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(&((*c)), d, eqN, lhsN, rhsN, boolN, eqTrait);
    }
    else {
    synthStructEq_c_Comp_d_DeriveReq_eqN_Bind_lhsN_Bind_rhsN_Bind_boolN_Bind_eqTrait_Bind(&((*c)), d, eqN, lhsN, rhsN, boolN, eqTrait);
    }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), d.nameStart, d.nameLen, (PlewString){"Ord", 3})) {
    if (enumIndexByName_c_Comp_start_U64_len_U64(&((*c)), ordN.nameStart, ordN.nameLen) >= (long long)(((*c).enums).count)) {
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
    Array_Bind_append_value_T(&((*c).imports), (Bind){.nameStart = nameStart, .nameLen = nameLen, .fieldStart = moduleOf_c_Comp_offset_U64(&((*c)), nameStart), .fieldLen = 0});
}
void parseExport_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    long long isPath = 0;
    {
    Kind _m292 = Comp_curKind(&((*c)));
    if (_m292.tag == 40) {
    isPath = 1;
    }
    else if (_m292.tag == 51) {
    isPath = 1;
    }
    else if (_m292.tag == 5) {
    Tok ft = Comp_cur(&((*c)));
    if (Array_U8_get((*c).bytes, (long long)(ft.start)) == 64) {
    isPath = 1;
    }
    }
    else {
    }
    }
    if (isPath) {
    long long go = 1;
    while (go) {
    {
    Kind _m293 = Comp_curKind(&((*c)));
    if (_m293.tag == 0) {
    go = 0;
    }
    else if (_m293.tag == 36) {
    go = 0;
    }
    else if (_m293.tag == 5) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"with", 4})) {
    Comp_advance(&((*c)));
    go = 0;
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    else {
    Comp_advance(&((*c)));
    }
    }
    }
    {
    Kind _m294 = Comp_curKind(&((*c)));
    if (_m294.tag == 36) {
    Comp_advance(&((*c)));
    long long g2 = 1;
    while (g2) {
    {
    Kind _m295 = Comp_curKind(&((*c)));
    if (_m295.tag == 37) {
    Comp_advance(&((*c)));
    g2 = 0;
    }
    else if (_m295.tag == 0) {
    g2 = 0;
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
    return;
    }
    {
    Kind _m296 = Comp_curKind(&((*c)));
    if (_m296.tag == 29) {
    uint64_t xfB = (long long)(((*c).funcs).count);
    uint64_t xsB = (long long)(((*c).structs).count);
    parseExtern_c_Comp(&((*c)));
    uint64_t xi = xfB;
    while (xi < (long long)(((*c).funcs).count)) {
    recordExport_c_Comp_nameStart_U64_nameLen_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(xi)).nameStart, Array_Func_get((*c).funcs, (long long)(xi)).nameLen);
    xi = ({ uint64_t __ov; if (__builtin_add_overflow((xi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t xj = xsB;
    while (xj < (long long)(((*c).structs).count)) {
    recordExport_c_Comp_nameStart_U64_nameLen_U64(&((*c)), Array_StructDef_get((*c).structs, (long long)(xj)).nameStart, Array_StructDef_get((*c).structs, (long long)(xj)).nameLen);
    xj = ({ uint64_t __ov; if (__builtin_add_overflow((xj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return;
    }
    else {
    }
    }
    uint64_t sB = (long long)(((*c).structs).count);
    uint64_t eB = (long long)(((*c).enums).count);
    uint64_t fB = (long long)(((*c).funcs).count);
    uint64_t tB = (long long)(((*c).traits).count);
    {
    Kind _m297 = Comp_curKind(&((*c)));
    if (_m297.tag == 6) {
    parseFunc_c_Comp_isAsync_Bool(&((*c)), 0);
    }
    else if (_m297.tag == 27) {
    Comp_advance(&((*c)));
    {
    Kind _m298 = Comp_curKind(&((*c)));
    if (_m298.tag == 6) {
    parseFunc_c_Comp_isAsync_Bool(&((*c)), 1);
    }
    else {
    }
    }
    }
    else if (_m297.tag == 7) {
    parseStruct_c_Comp_isUnique_Bool(&((*c)), 0);
    }
    else if (_m297.tag == 23) {
    Comp_advance(&((*c)));
    {
    Kind _m299 = Comp_curKind(&((*c)));
    if (_m299.tag == 7) {
    parseStruct_c_Comp_isUnique_Bool(&((*c)), 1);
    }
    else {
    }
    }
    }
    else if (_m297.tag == 8) {
    parseEnum_c_Comp(&((*c)));
    }
    else if (_m297.tag == 5) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"trait", 5})) {
    parseTrait_c_Comp(&((*c)));
    }
    }
    else {
    }
    }
    if ((long long)(((*c).structs).count) > sB) {
    recordExport_c_Comp_nameStart_U64_nameLen_U64(&((*c)), Array_StructDef_get((*c).structs, (long long)(sB)).nameStart, Array_StructDef_get((*c).structs, (long long)(sB)).nameLen);
    }
    else {
    if ((long long)(((*c).enums).count) > eB) {
    recordExport_c_Comp_nameStart_U64_nameLen_U64(&((*c)), Array_EnumDef_get((*c).enums, (long long)(eB)).nameStart, Array_EnumDef_get((*c).enums, (long long)(eB)).nameLen);
    }
    else {
    if ((long long)(((*c).funcs).count) > fB) {
    recordExport_c_Comp_nameStart_U64_nameLen_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(fB)).nameStart, Array_Func_get((*c).funcs, (long long)(fB)).nameLen);
    }
    else {
    if ((long long)(((*c).traits).count) > tB) {
    recordExport_c_Comp_nameStart_U64_nameLen_U64(&((*c)), Array_TraitDef_get((*c).traits, (long long)(tB)).nameStart, Array_TraitDef_get((*c).traits, (long long)(tB)).nameLen);
    }
    }
    }
    }
}
void recordExport_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    Array_Bind_append_value_T(&((*c).exports), (Bind){.nameStart = nameStart, .nameLen = nameLen, .fieldStart = moduleOf_c_Comp_offset_U64(&((*c)), nameStart), .fieldLen = 0});
}
void parseImport_c_Comp(Comp* c) {
    Comp_advance(&((*c)));
    uint64_t segStart = 0;
    uint64_t segLen = 0;
    while (1) {
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m300 = k;
    if (_m300.tag == 1) {
    break;
    }
    else if (_m300.tag == 0) {
    break;
    }
    else if (_m300.tag == 36) {
    break;
    }
    else if (_m300.tag == 5) {
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
    Kind _m301 = Comp_curKind(&((*c)));
    if (_m301.tag == 36) {
    Comp_advance(&((*c)));
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m302 = k;
    if (_m302.tag == 37) {
    Comp_advance(&((*c)));
    break;
    }
    else if (_m302.tag == 0) {
    break;
    }
    else if (_m302.tag == 38) {
    Comp_advance(&((*c)));
    }
    else if (_m302.tag == 5) {
    Tok t = Comp_cur(&((*c)));
    markImport_c_Comp_segStart_U64_segLen_U64_nameStart_U64_nameLen_U64(&((*c)), segStart, segLen, t.start, t.len);
    Comp_advance(&((*c)));
    {
    Kind _m303 = Comp_curKind(&((*c)));
    if (_m303.tag == 21) {
    Comp_advance(&((*c)));
    {
    Kind _m304 = Comp_curKind(&((*c)));
    if (_m304.tag == 5) {
    Comp_advance(&((*c)));
    }
    else {
    }
    }
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
void parseProgram_c_Comp(Comp* c) {
    while (1) {
    Comp_skipNewlines(&((*c)));
    Kind k = Comp_curKind(&((*c)));
    {
    Kind _m305 = k;
    if (_m305.tag == 6) {
    parseFunc_c_Comp_isAsync_Bool(&((*c)), 0);
    }
    else if (_m305.tag == 27) {
    Comp_advance(&((*c)));
    {
    Kind _m306 = Comp_curKind(&((*c)));
    if (_m306.tag == 6) {
    parseFunc_c_Comp_isAsync_Bool(&((*c)), 1);
    }
    else {
    }
    }
    }
    else if (_m305.tag == 7) {
    parseStruct_c_Comp_isUnique_Bool(&((*c)), 0);
    }
    else if (_m305.tag == 23) {
    Comp_advance(&((*c)));
    {
    Kind _m307 = Comp_curKind(&((*c)));
    if (_m307.tag == 7) {
    parseStruct_c_Comp_isUnique_Bool(&((*c)), 1);
    }
    else {
    }
    }
    }
    else if (_m305.tag == 8) {
    parseEnum_c_Comp(&((*c)));
    }
    else if (_m305.tag == 29) {
    parseExtern_c_Comp(&((*c)));
    }
    else if (_m305.tag == 5) {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"import", 6})) {
    parseImport_c_Comp(&((*c)));
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"export", 6})) {
    parseExport_c_Comp(&((*c)));
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"impl", 4})) {
    parseImpl_c_Comp_isPub_Bool(&((*c)), 0);
    }
    else {
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"pub", 3})) {
    Comp_advance(&((*c)));
    if (Comp_identIs_kw_String(&((*c)), (PlewString){"impl", 4})) {
    parseImpl_c_Comp_isPub_Bool(&((*c)), 1);
    }
    else {
    Comp_advance(&((*c)));
    }
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
    }
    }
    else if (_m305.tag == 0) {
    break;
    }
    else {
    if ((Comp_peekKind_off_U64(&((*c)), 1)).tag == 34) {
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
    { PlewString __ret308 = (PlewString){"0", 1};
    return __ret308; }
    }
    if (d == 1) {
    { PlewString __ret309 = (PlewString){"1", 1};
    return __ret309; }
    }
    if (d == 2) {
    { PlewString __ret310 = (PlewString){"2", 1};
    return __ret310; }
    }
    if (d == 3) {
    { PlewString __ret311 = (PlewString){"3", 1};
    return __ret311; }
    }
    if (d == 4) {
    { PlewString __ret312 = (PlewString){"4", 1};
    return __ret312; }
    }
    if (d == 5) {
    { PlewString __ret313 = (PlewString){"5", 1};
    return __ret313; }
    }
    if (d == 6) {
    { PlewString __ret314 = (PlewString){"6", 1};
    return __ret314; }
    }
    if (d == 7) {
    { PlewString __ret315 = (PlewString){"7", 1};
    return __ret315; }
    }
    if (d == 8) {
    { PlewString __ret316 = (PlewString){"8", 1};
    return __ret316; }
    }
    { PlewString __ret317 = (PlewString){"9", 1};
    return __ret317; }
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
    { PlewString __ret318 = (PlewString){"0", 1};
    return __ret318; }
    }
    if (d == 1) {
    { PlewString __ret319 = (PlewString){"1", 1};
    return __ret319; }
    }
    if (d == 2) {
    { PlewString __ret320 = (PlewString){"2", 1};
    return __ret320; }
    }
    if (d == 3) {
    { PlewString __ret321 = (PlewString){"3", 1};
    return __ret321; }
    }
    if (d == 4) {
    { PlewString __ret322 = (PlewString){"4", 1};
    return __ret322; }
    }
    if (d == 5) {
    { PlewString __ret323 = (PlewString){"5", 1};
    return __ret323; }
    }
    if (d == 6) {
    { PlewString __ret324 = (PlewString){"6", 1};
    return __ret324; }
    }
    if (d == 7) {
    { PlewString __ret325 = (PlewString){"7", 1};
    return __ret325; }
    }
    if (d == 8) {
    { PlewString __ret326 = (PlewString){"8", 1};
    return __ret326; }
    }
    { PlewString __ret327 = (PlewString){"9", 1};
    return __ret327; }
}
void writeU64_n_U64(uint64_t n) {
    if (n >= 10) {
    writeU64_n_U64(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); __dl / __dr; }));
    }
    plew_write(digitStrU_d_U64(({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); __dl % __dr; })));
}
void writeIntLit_n_U64(uint64_t n) {
    writeU64_n_U64(n);
    if (n > 9223372036854775807) {
    plew_write((PlewString){"ULL", 3});
    }
}
void writeSpan_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t j = 0;
    while (j < len) {
    plew_writeByte(Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))));
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
    plew_exit(1);
}
void compileErrorAt_line_I64_msg_String(int64_t line, PlewString msg) {
    plew_eprint((PlewString){"plewc: error: line ", 19});
    eprintInt_n_I64(line);
    plew_eprint((PlewString){": ", 2});
    plew_eprint(msg);
    plew_eprint((PlewString){"\n", 1});
    plew_exit(1);
}
long long isPrimType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { long long __ret328 = 1;
    return __ret328; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { long long __ret329 = 1;
    return __ret329; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { long long __ret330 = 1;
    return __ret330; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I64", 3})) {
    { long long __ret331 = 1;
    return __ret331; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    { long long __ret332 = 1;
    return __ret332; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    { long long __ret333 = 1;
    return __ret333; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    { long long __ret334 = 1;
    return __ret334; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U64", 3})) {
    { long long __ret335 = 1;
    return __ret335; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"Bool", 4})) {
    { long long __ret336 = 1;
    return __ret336; }
    }
    { long long __ret337 = 0;
    return __ret337; }
}
long long isIntType_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { long long __ret338 = 1;
    return __ret338; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { long long __ret339 = 1;
    return __ret339; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { long long __ret340 = 1;
    return __ret340; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I64", 3})) {
    { long long __ret341 = 1;
    return __ret341; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    { long long __ret342 = 1;
    return __ret342; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    { long long __ret343 = 1;
    return __ret343; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    { long long __ret344 = 1;
    return __ret344; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U64", 3})) {
    { long long __ret345 = 1;
    return __ret345; }
    }
    { long long __ret346 = 0;
    return __ret346; }
}
uint64_t intBits_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { uint64_t __ret347 = 8;
    return __ret347; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    { uint64_t __ret348 = 8;
    return __ret348; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { uint64_t __ret349 = 16;
    return __ret349; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    { uint64_t __ret350 = 16;
    return __ret350; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { uint64_t __ret351 = 32;
    return __ret351; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    { uint64_t __ret352 = 32;
    return __ret352; }
    }
    { uint64_t __ret353 = 64;
    return __ret353; }
}
long long intSigned_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    { long long __ret354 = (Array_U8_get((*c).bytes, (long long)(start)) == 73);
    return __ret354; }
}
long long losslessInt_c_Comp_srcStart_U64_srcLen_U64_dstStart_U64_dstLen_U64(Comp* c, uint64_t srcStart, uint64_t srcLen, uint64_t dstStart, uint64_t dstLen) {
    uint64_t sBits = intBits_c_Comp_start_U64_len_U64(&((*c)), srcStart, srcLen);
    uint64_t dBits = intBits_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    long long sSigned = intSigned_c_Comp_start_U64_len_U64(&((*c)), srcStart, srcLen);
    long long dSigned = intSigned_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    if (sSigned) {
    if (dSigned) {
    { long long __ret355 = (dBits >= sBits);
    return __ret355; }
    }
    { long long __ret356 = 0;
    return __ret356; }
    }
    if (dSigned) {
    { long long __ret357 = (dBits > sBits);
    return __ret357; }
    }
    { long long __ret358 = (dBits >= sBits);
    return __ret358; }
}
long long litFitsType_c_Comp_value_U64_neg_Bool_dstStart_U64_dstLen_U64(Comp* c, uint64_t value, long long neg, uint64_t dstStart, uint64_t dstLen) {
    uint64_t bits = intBits_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    long long sgn = intSigned_c_Comp_start_U64_len_U64(&((*c)), dstStart, dstLen);
    { long long __ret359 = litFitsBits_value_U64_neg_Bool_bits_U64_sgn_Bool(value, neg, bits, sgn);
    return __ret359; }
}
long long litFitsBits_value_U64_neg_Bool_bits_U64_sgn_Bool(uint64_t value, long long neg, uint64_t bits, long long sgn) {
    if (neg) {
    if (sgn) {
    }
    else {
    { long long __ret360 = 0;
    return __ret360; }
    }
    if (bits == 8) {
    { long long __ret361 = (value <= 128);
    return __ret361; }
    }
    if (bits == 16) {
    { long long __ret362 = (value <= 32768);
    return __ret362; }
    }
    if (bits == 32) {
    { long long __ret363 = (value <= 2147483648);
    return __ret363; }
    }
    if (value == 0) {
    { long long __ret364 = 1;
    return __ret364; }
    }
    { long long __ret365 = (({ uint64_t __ov; if (__builtin_sub_overflow((value), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }) <= 9223372036854775807);
    return __ret365; }
    }
    if (sgn) {
    if (bits == 8) {
    { long long __ret366 = (value <= 127);
    return __ret366; }
    }
    if (bits == 16) {
    { long long __ret367 = (value <= 32767);
    return __ret367; }
    }
    if (bits == 32) {
    { long long __ret368 = (value <= 2147483647);
    return __ret368; }
    }
    { long long __ret369 = (value <= 9223372036854775807);
    return __ret369; }
    }
    if (bits == 8) {
    { long long __ret370 = (value <= 255);
    return __ret370; }
    }
    if (bits == 16) {
    { long long __ret371 = (value <= 65535);
    return __ret371; }
    }
    if (bits == 32) {
    { long long __ret372 = (value <= 4294967295);
    return __ret372; }
    }
    { long long __ret373 = 1;
    return __ret373; }
}
uint64_t arrayElemRef_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).count)) {
    Bind ae = Array_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ae.nameStart, ae.nameLen, start, len)) {
    { uint64_t __ret374 = ae.fieldStart;
    return __ret374; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret375 = 0;
    return __ret375; }
}
Bind arrayElemNameForRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef) {
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).count)) {
    Bind ae = Array_Bind_get((*c).arrayElems, (long long)(i));
    if (ae.fieldStart != 0) {
    if (sameMangle_c_Comp_refA_U64_refB_U64(&((*c)), ae.fieldStart, elemRef)) {
    { Bind __ret376 = (Bind){.nameStart = ae.nameStart, .nameLen = ae.nameLen, .fieldStart = elemRef, .fieldLen = 0};
    return __ret376; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (elemRef < (long long)(((*c).types).count)) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(elemRef)));
    { Bind __ret377 = (Bind){.nameStart = t.nameStart, .nameLen = t.nameLen, .fieldStart = elemRef, .fieldLen = 0};
    TypeRef_release(t);
    return __ret377; }
    TypeRef_release(t);
    }
    { Bind __ret378 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret378; }
}
void genCElem_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (len == 0) {
    plew_write((PlewString){"long long", 9});
    return;
    }
    uint64_t k = 0;
    while (k < (long long)(((*c).curTypeParams).count)) {
    Bind p = Array_Bind_get((*c).curTypeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.nameStart, p.nameLen, start, len)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get((*c).curTypeArgs, (long long)(k)));
    return;
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t er = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (er != 0) {
    if (isCompoundType_c_Comp_ref_U64(&((*c)), er)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), er);
    return;
    }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U8", 2})) {
    plew_write((PlewString){"unsigned char", 13});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    plew_write((PlewString){"int8_t", 6});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    plew_write((PlewString){"int16_t", 7});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U16", 3})) {
    plew_write((PlewString){"uint16_t", 8});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    plew_write((PlewString){"int32_t", 7});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U32", 3})) {
    plew_write((PlewString){"uint32_t", 8});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I64", 3})) {
    plew_write((PlewString){"int64_t", 7});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"U64", 3})) {
    plew_write((PlewString){"uint64_t", 8});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"String", 6})) {
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
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), start, len);
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
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), ti.nameStart, ti.nameLen);
    return;
    }
    plew_write((PlewString){"long long", 9});
}
long long spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(Comp* c, uint64_t aStart, uint64_t aLen, uint64_t bStart, uint64_t bLen) {
    if (aLen != bLen) {
    { long long __ret379 = 0;
    return __ret379; }
    }
    uint64_t j = 0;
    while (j < aLen) {
    if (Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((aStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((bStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })))) {
    { long long __ret380 = 0;
    return __ret380; }
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret381 = 1;
    return __ret381; }
}
int64_t lineOf_c_Comp_offset_U64(Comp* c, uint64_t offset) {
    int64_t line = 1;
    uint64_t i = 0;
    while (i < offset) {
    if (Array_U8_get((*c).bytes, (long long)(i)) == 10) {
    line = ({ int64_t __ov; if (__builtin_add_overflow((line), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { int64_t __ret382 = line;
    return __ret382; }
}
uint64_t exprOffset_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m383 = e;
    if (_m383.tag == 0) {
        uint64_t offset = _m383.data.Int.offset;
        (void)offset;
    { uint64_t __ret384 = offset;
    Expr_release(e);
    return __ret384; }
    }
    else if (_m383.tag == 1) {
        uint64_t start = _m383.data.Ident.start;
        (void)start;
        uint64_t len = _m383.data.Ident.len;
        (void)len;
    { uint64_t __ret385 = start;
    Expr_release(e);
    return __ret385; }
    }
    else if (_m383.tag == 7) {
        uint64_t start = _m383.data.Str.start;
        (void)start;
        uint64_t len = _m383.data.Str.len;
        (void)len;
    { uint64_t __ret386 = start;
    Expr_release(e);
    return __ret386; }
    }
    else if (_m383.tag == 4) {
        uint64_t nameStart = _m383.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m383.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m383.data.Call.args;
        (void)args;
    { uint64_t __ret387 = nameStart;
    Expr_release(e);
    return __ret387; }
    }
    else if (_m383.tag == 10) {
        uint64_t recv = _m383.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m383.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m383.data.Method.nameLen;
        (void)nameLen;
        Array_Arg args = _m383.data.Method.args;
        (void)args;
    { uint64_t __ret388 = nameStart;
    Expr_release(e);
    return __ret388; }
    }
    else if (_m383.tag == 5) {
        uint64_t base = _m383.data.Field.base;
        (void)base;
        uint64_t nameStart = _m383.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m383.data.Field.nameLen;
        (void)nameLen;
    { uint64_t __ret389 = exprOffset_c_Comp_id_U64(&((*c)), base);
    Expr_release(e);
    return __ret389; }
    }
    else if (_m383.tag == 9) {
        uint64_t base = _m383.data.Index.base;
        (void)base;
        uint64_t index = _m383.data.Index.index;
        (void)index;
    { uint64_t __ret390 = exprOffset_c_Comp_id_U64(&((*c)), base);
    Expr_release(e);
    return __ret390; }
    }
    else if (_m383.tag == 3) {
        int64_t op = _m383.data.Binary.op;
        (void)op;
        uint64_t lhs = _m383.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m383.data.Binary.rhs;
        (void)rhs;
    { uint64_t __ret391 = exprOffset_c_Comp_id_U64(&((*c)), lhs);
    Expr_release(e);
    return __ret391; }
    }
    else if (_m383.tag == 2) {
        int64_t op = _m383.data.Unary.op;
        (void)op;
        uint64_t operand = _m383.data.Unary.operand;
        (void)operand;
    { uint64_t __ret392 = exprOffset_c_Comp_id_U64(&((*c)), operand);
    Expr_release(e);
    return __ret392; }
    }
    else if (_m383.tag == 11) {
        uint64_t operand = _m383.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m383.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m383.data.Cast.tyLen;
        (void)tyLen;
    { uint64_t __ret393 = exprOffset_c_Comp_id_U64(&((*c)), operand);
    Expr_release(e);
    return __ret393; }
    }
    else if (_m383.tag == 6) {
        uint64_t typeStart = _m383.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m383.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m383.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m383.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m383.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m383.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m383.data.Make.fields;
        (void)fields;
    { uint64_t __ret394 = typeStart;
    Expr_release(e);
    return __ret394; }
    }
    else if (_m383.tag == 12) {
        uint64_t scrut = _m383.data.MatchExpr.scrut;
        (void)scrut;
        Array_MatchArm arms = _m383.data.MatchExpr.arms;
        (void)arms;
    { uint64_t __ret395 = exprOffset_c_Comp_id_U64(&((*c)), scrut);
    Expr_release(e);
    return __ret395; }
    }
    else if (_m383.tag == 13) {
        uint64_t cond = _m383.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m383.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m383.data.IfExpr.elseBlk;
        (void)elseBlk;
    { uint64_t __ret396 = exprOffset_c_Comp_id_U64(&((*c)), cond);
    Expr_release(e);
    return __ret396; }
    }
    else if (_m383.tag == 14) {
        uint64_t opt = _m383.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m383.data.Coalesce.deflt;
        (void)deflt;
    { uint64_t __ret397 = exprOffset_c_Comp_id_U64(&((*c)), opt);
    Expr_release(e);
    return __ret397; }
    }
    else if (_m383.tag == 15) {
        uint64_t expr = _m383.data.Try.expr;
        (void)expr;
    { uint64_t __ret398 = exprOffset_c_Comp_id_U64(&((*c)), expr);
    Expr_release(e);
    return __ret398; }
    }
    else if (_m383.tag == 16) {
        uint64_t base = _m383.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m383.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m383.data.Arrow.nameLen;
        (void)nameLen;
    { uint64_t __ret399 = exprOffset_c_Comp_id_U64(&((*c)), base);
    Expr_release(e);
    return __ret399; }
    }
    else if (_m383.tag == 17) {
        Array_Param params = _m383.data.Closure.params;
        (void)params;
        long long hasRet = _m383.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m383.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m383.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m383.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m383.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m383.data.Closure.body;
        (void)body;
    { uint64_t __ret400 = retStart;
    Expr_release(e);
    return __ret400; }
    }
    else {
    { uint64_t __ret401 = 0;
    Expr_release(e);
    return __ret401; }
    }
    }
    Expr_release(e);
}
uint64_t moduleOf_c_Comp_offset_U64(Comp* c, uint64_t offset) {
    uint64_t i = 0;
    while (i < (long long)(((*c).moduleRanges).count)) {
    Bind r = Array_Bind_get((*c).moduleRanges, (long long)(i));
    if (offset >= r.nameStart) {
    if (offset < ({ uint64_t __ov; if (__builtin_add_overflow((r.nameStart), (r.nameLen), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })) {
    { uint64_t __ret402 = r.fieldStart;
    return __ret402; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret403 = 0;
    return __ret403; }
}
LetEff inferLetType_c_Comp_tyStart_U64_tyLen_U64_tyIsArray_Bool_ty_U64_init_U64(Comp* c, uint64_t tyStart, uint64_t tyLen, long long tyIsArray, uint64_t ty, uint64_t init) {
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
    }
    else {
    effStart = ss.nameStart;
    effLen = ss.nameLen;
    }
    }
    }
    }
    }
    { LetEff __ret404 = (LetEff){.start = effStart, .len = effLen, .arr = effArr, .ty = effTy};
    return __ret404; }
}
uint64_t findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    uint64_t firstLabel = (long long)(((*c).funcs).count);
    uint64_t typeMatch = (long long)(((*c).funcs).count);
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(f.params), Array_Arg_share(args))) {
    if (firstLabel == (long long)(((*c).funcs).count)) {
    firstLabel = i;
    }
    if (typeMatch == (long long)(((*c).funcs).count)) {
    if (paramsTypesMatch_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(f.params), Array_Arg_share(args))) {
    typeMatch = i;
    }
    }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    if (typeMatch != (long long)(((*c).funcs).count)) {
    { uint64_t __ret405 = typeMatch;
    return __ret405; }
    }
    { uint64_t __ret406 = firstLabel;
    return __ret406; }
}
uint64_t firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    { uint64_t __ret407 = i;
    Func_release(f);
    return __ret407; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { uint64_t __ret408 = (long long)(((*c).funcs).count);
    return __ret408; }
}
long long funcNameExists_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    { long long __ret409 = (firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen) != (long long)(((*c).funcs).count));
    return __ret409; }
}
uint64_t findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    uint64_t firstLabel = (long long)(((*c).funcs).count);
    uint64_t typeMatch = (long long)(((*c).funcs).count);
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), recvStart, recvLen, f.recvStart, f.recvLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(f.params), Array_Arg_share(args))) {
    if (firstLabel == (long long)(((*c).funcs).count)) {
    firstLabel = i;
    }
    if (typeMatch == (long long)(((*c).funcs).count)) {
    if (paramsTypesMatch_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(f.params), Array_Arg_share(args))) {
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
    if (typeMatch != (long long)(((*c).funcs).count)) {
    { uint64_t __ret410 = typeMatch;
    return __ret410; }
    }
    if (firstLabel != (long long)(((*c).funcs).count)) {
    { uint64_t __ret411 = firstLabel;
    return __ret411; }
    }
    uint64_t ai = 0;
    while (ai < (long long)(((*c).methodAliases).count)) {
    MethodAlias al = Array_MethodAlias_get((*c).methodAliases, (long long)(ai));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), recvStart, recvLen, al.recvStart, al.recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, al.aliasStart, al.aliasLen)) {
    { uint64_t __ret412 = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), recvStart, recvLen, al.realStart, al.realLen, Array_Arg_share(args));
    return __ret412; }
    }
    }
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret413 = (long long)(((*c).funcs).count);
    return __ret413; }
}
uint64_t findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    uint64_t firstLabel = (long long)(((*c).funcs).count);
    uint64_t typeMatch = (long long)(((*c).funcs).count);
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.isAssoc) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nameStart, nameLen, f.nameStart, f.nameLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), recvStart, recvLen, f.recvStart, f.recvLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(f.params), Array_Arg_share(args))) {
    if (firstLabel == (long long)(((*c).funcs).count)) {
    firstLabel = i;
    }
    if (typeMatch == (long long)(((*c).funcs).count)) {
    if (paramsTypesMatch_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(f.params), Array_Arg_share(args))) {
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
    if (typeMatch != (long long)(((*c).funcs).count)) {
    { uint64_t __ret414 = typeMatch;
    return __ret414; }
    }
    { uint64_t __ret415 = firstLabel;
    return __ret415; }
}
long long isTypeName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len) < (long long)(((*c).structs).count)) {
    { long long __ret416 = 1;
    return __ret416; }
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_EnumDef_get((*c).enums, (long long)(ei)).nameStart, Array_EnumDef_get((*c).enums, (long long)(ei)).nameLen, start, len)) {
    { long long __ret417 = 1;
    return __ret417; }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret418 = (genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), start, len) < (long long)(((*c).structs).count));
    return __ret418; }
}
Bind assocRecvName_c_Comp_recv_U64(Comp* c, uint64_t recv) {
    {
    Expr _m419 = Array_Expr_get((*c).exprs, (long long)(recv));
    if (_m419.tag == 1) {
        uint64_t start = _m419.data.Ident.start;
        (void)start;
        uint64_t len = _m419.data.Ident.len;
        (void)len;
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { Bind __ret420 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret420; }
    }
    if (localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len) < (long long)(((*c).locals).count)) {
    { Bind __ret421 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret421; }
    }
    if (isTypeName_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { Bind __ret422 = (Bind){.nameStart = start, .nameLen = len, .fieldStart = start, .fieldLen = len};
    return __ret422; }
    }
    { Bind __ret423 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret423; }
    }
    else {
    { Bind __ret424 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret424; }
    }
    }
}
long long paramsLabelsOk_c_Comp_params_AParam_args_AArg(Comp* c, Array_Param params, Array_Arg args) {
    if ((long long)((args).count) > (long long)((params).count)) {
    { long long __ret425 = 0;
    return __ret425; }
    }
    uint64_t r = (long long)((args).count);
    while (r < (long long)((params).count)) {
    if (Array_Param_get(params, (long long)(r)).hasDefault) {
    }
    else {
    { long long __ret426 = 0;
    return __ret426; }
    }
    r = ({ uint64_t __ov; if (__builtin_add_overflow((r), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    Arg a = Array_Arg_get(args, (long long)(i));
    Param p = Array_Param_get(params, (long long)(i));
    if (p.noLabel) {
    if (a.hasLabel) {
    { long long __ret427 = 0;
    return __ret427; }
    }
    }
    else {
    if (a.hasLabel) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), a.labelStart, a.labelLen, p.nameStart, p.nameLen)) {
    }
    else {
    { long long __ret428 = 0;
    return __ret428; }
    }
    }
    else {
    { long long __ret429 = 0;
    return __ret429; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret430 = 1;
    return __ret430; }
}
long long argMatchesParam_c_Comp_argExpr_U64_p_Param(Comp* c, uint64_t argExpr, Param p) {
    TypeInfo ti = exprType_c_Comp_id_U64(&((*c)), argExpr);
    if (p.tyIsArray) {
    if (ti.kind == 3) {
    { long long __ret431 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ti.nameStart, ti.nameLen, p.tyStart, p.tyLen);
    return __ret431; }
    }
    { long long __ret432 = 0;
    return __ret432; }
    }
    if (ti.kind == 1) {
    { long long __ret433 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), p.tyStart, p.tyLen, (PlewString){"String", 6});
    return __ret433; }
    }
    if (ti.kind == 2) {
    { long long __ret434 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ti.nameStart, ti.nameLen, p.tyStart, p.tyLen);
    return __ret434; }
    }
    if (ti.nameLen != 0) {
    { long long __ret435 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ti.nameStart, ti.nameLen, p.tyStart, p.tyLen);
    return __ret435; }
    }
    { long long __ret436 = isIntType_c_Comp_start_U64_len_U64(&((*c)), p.tyStart, p.tyLen);
    return __ret436; }
}
long long paramsTypesMatch_c_Comp_params_AParam_args_AArg(Comp* c, Array_Param params, Array_Arg args) {
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    if (i < (long long)((params).count)) {
    if (argMatchesParam_c_Comp_argExpr_U64_p_Param(&((*c)), Array_Arg_get(args, (long long)(i)).expr, Array_Param_get(params, (long long)(i)))) {
    }
    else {
    { long long __ret437 = 0;
    return __ret437; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret438 = 1;
    return __ret438; }
}
long long callLabelsOk_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    if (funcNameExists_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen)) {
    { long long __ret439 = (findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args)) != (long long)(((*c).funcs).count));
    return __ret439; }
    }
    { long long __ret440 = 1;
    return __ret440; }
}
long long armCovers_c_Comp_arms_AMatchArm_variantStart_U64_variantLen_U64(Comp* c, Array_MatchArm arms, uint64_t variantStart, uint64_t variantLen) {
    uint64_t i = 0;
    while (i < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    { long long __ret441 = 1;
    MatchArm_release(a);
    return __ret441; }
    }
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), a.variantStart, a.variantLen, variantStart, variantLen)) {
    { long long __ret442 = 1;
    MatchArm_release(a);
    return __ret442; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    { long long __ret443 = 0;
    return __ret443; }
}
long long matchExhaustive_c_Comp_arms_AMatchArm(Comp* c, Array_MatchArm arms) {
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    uint64_t i = 0;
    while (i < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(i)));
    if (a.isWildcard) {
    { long long __ret444 = 1;
    MatchArm_release(a);
    return __ret444; }
    }
    if (enumLen == 0) {
    enumStart = a.enumStart;
    enumLen = a.enumLen;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    if (enumLen == 0) {
    { long long __ret445 = 1;
    return __ret445; }
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (armCovers_c_Comp_arms_AMatchArm_variantStart_U64_variantLen_U64(&((*c)), Array_MatchArm_share(arms), v.nameStart, v.nameLen)) {
    }
    else {
    { long long __ret446 = 0;
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(e);
    return __ret446; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { long long __ret447 = 1;
    Array_Variant_release(vars);
    EnumDef_release(e);
    return __ret447; }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret448 = 1;
    return __ret448; }
}
uint64_t variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    { uint64_t __ret449 = vi;
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(e);
    return __ret449; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret450 = 0;
    return __ret450; }
}
TypeInfo scalarInfo(void) {
    { TypeInfo __ret451 = (TypeInfo){.kind = 0, .nameStart = 0, .nameLen = 0, .ref = 0};
    return __ret451; }
}
Bind kwSpan_c_Comp_kw_String_kwLen_U64(Comp* c, PlewString kw, uint64_t kwLen) {
    uint64_t n = (long long)(((*c).bytes).count);
    if (n < kwLen) {
    { Bind __ret452 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret452; }
    }
    uint64_t i = 0;
    uint64_t last = ({ uint64_t __ov; if (__builtin_sub_overflow((n), (kwLen), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (i <= last) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), i, kwLen, kw)) {
    { Bind __ret453 = (Bind){.nameStart = i, .nameLen = kwLen, .fieldStart = i, .fieldLen = kwLen};
    return __ret453; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Bind __ret454 = (Bind){.nameStart = 0, .nameLen = 0, .fieldStart = 0, .fieldLen = 0};
    return __ret454; }
}
Bind stringTypeSpan_c_Comp(Comp* c) {
    { Bind __ret455 = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"String", 6}, 6);
    return __ret455; }
}
TypeInfo typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(Comp* c, uint64_t start, uint64_t len, long long isArray) {
    if (isArray) {
    { TypeInfo __ret456 = (TypeInfo){.kind = 3, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret456; }
    }
    if (len == 0) {
    { TypeInfo __ret457 = scalarInfo();
    return __ret457; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"String", 6})) {
    { TypeInfo __ret458 = (TypeInfo){.kind = 1, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret458; }
    }
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { TypeInfo __ret459 = (TypeInfo){.kind = 0, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret459; }
    }
    { TypeInfo __ret460 = (TypeInfo){.kind = 2, .nameStart = start, .nameLen = len, .ref = 0};
    return __ret460; }
}
void addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned) {
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), nameStart, nameLen, tyStart, tyLen, isArray, ty, isInout, isMut, owned, 0);
}
void addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t tyStart, uint64_t tyLen, long long isArray, uint64_t ty, long long isInout, long long isMut, long long owned, uint64_t cnum) {
    Array_Local_append_value_T(&((*c).locals), (Local){.nameStart = nameStart, .nameLen = nameLen, .tyStart = tyStart, .tyLen = tyLen, .isArray = isArray, .ty = ty, .isInout = isInout, .isMut = isMut, .owned = owned, .moved = 0, .cnum = cnum});
}
uint64_t shadowCount_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t n = 0;
    uint64_t i = 0;
    while (i < (long long)(((*c).locals).count)) {
    Local lo = Array_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, nameStart, nameLen)) {
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret461 = n;
    return __ret461; }
}
void writeLocalCName_c_Comp_lo_Local(Comp* c, Local lo) {
    if ((*c).curAsync) {
    plew_write((PlewString){"__f->", 5});
    }
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
    { uint64_t __ret462 = (long long)(((*c).locals).count);
    return __ret462; }
}
void emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(Comp* c, uint64_t mark, uint64_t exclIdx) {
    uint64_t i = (long long)(((*c).locals).count);
    while (i > mark) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (i == exclIdx) {
    }
    else {
    Local lo = Array_Local_get((*c).locals, (long long)(i));
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
    if (isGenericInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    long long miNeeds = 0;
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    miNeeds = monoEnumNeedsRelease_c_Comp_instRef_U64(&((*c)), lo.ty);
    }
    else {
    miNeeds = monoStructNeedsRelease_c_Comp_instRef_U64(&((*c)), lo.ty);
    }
    if (miNeeds) {
    plew_write((PlewString){"    ", 4});
    emitMangle_c_Comp_ref_U64(&((*c)), lo.ty);
    plew_write((PlewString){"_release(", 9});
    writeLocalCName_c_Comp_lo_Local(&((*c)), lo);
    plew_write((PlewString){");\n", 3});
    }
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
    else {
    if (enumNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen)) {
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
    }
}
void emitRefRelease_c_Comp_nameStart_U64_nameLen_U64_refTy_U64_cnum_U64(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t refTy, uint64_t cnum) {
    TypeRef rt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(refTy)));
    TypeInfo bti = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
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
    while (i < (long long)(((*c).deinits).count)) {
    Bind d = Array_Bind_get((*c).deinits, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), d.nameStart, d.nameLen, start, len)) {
    { long long __ret463 = 1;
    return __ret463; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret464 = 0;
    return __ret464; }
}
long long structLocalReleasable_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).count)) {
    { long long __ret465 = 0;
    return __ret465; }
    }
    if ((long long)((Array_StructDef_get((*c).structs, (long long)(si)).typeParams).count) > 0) {
    { long long __ret466 = 0;
    return __ret466; }
    }
    { long long __ret467 = structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), start, len);
    return __ret467; }
}
void popLocals_c_Comp_mark_U64(Comp* c, uint64_t mark) {
    Array_Local kept = Array_Local_new();
    uint64_t i = 0;
    while (i < mark) {
    Array_Local_append_value_T(&(kept), Array_Local_get((*c).locals, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).locals = Array_Local_share(kept);
    Array_Local_release(kept);
}
void scopeExit_c_Comp_mark_U64(Comp* c, uint64_t mark) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), mark, (long long)(((*c).locals).count));
    popLocals_c_Comp_mark_U64(&((*c)), mark);
}
long long localIsMutable_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { long long __ret468 = (*c).curSelfInout;
    return __ret468; }
    }
    if ((*c).curInClosure) {
    if (isCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(&((*c)), (*c).curClosureId, start, len)) {
    { long long __ret469 = isBoxedCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(&((*c)), (*c).curClosureId, start, len);
    return __ret469; }
    }
    }
    uint64_t i = (long long)(((*c).locals).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = Array_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (lo.isMut) {
    { long long __ret470 = 1;
    return __ret470; }
    }
    { long long __ret471 = lo.isInout;
    return __ret471; }
    }
    }
    { long long __ret472 = 1;
    return __ret472; }
}
long long isSelfRef_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if ((*c).curHasRecv) {
    { long long __ret473 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"self", 4});
    return __ret473; }
    }
    { long long __ret474 = 0;
    return __ret474; }
}
long long isInoutLocal_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { long long __ret475 = (*c).curSelfInout;
    return __ret475; }
    }
    uint64_t i = (long long)(((*c).locals).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = Array_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    { long long __ret476 = lo.isInout;
    return __ret476; }
    }
    }
    { long long __ret477 = 0;
    return __ret477; }
}
long long typeIsUnique_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).count)) {
    { long long __ret478 = 0;
    return __ret478; }
    }
    { long long __ret479 = Array_StructDef_get((*c).structs, (long long)(si)).isUnique;
    return __ret479; }
}
uint64_t localIndexByName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = (long long)(((*c).locals).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = Array_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    { uint64_t __ret480 = i;
    return __ret480; }
    }
    }
    { uint64_t __ret481 = (long long)(((*c).locals).count);
    return __ret481; }
}
long long localMoved_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = (long long)(((*c).locals).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = Array_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    { long long __ret482 = lo.moved;
    return __ret482; }
    }
    }
    { long long __ret483 = 0;
    return __ret483; }
}
void markMovedLocal_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t target = (long long)(((*c).locals).count);
    uint64_t i = (long long)(((*c).locals).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = Array_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    target = i;
    i = 0;
    }
    }
    if (target >= (long long)(((*c).locals).count)) {
    return;
    }
    Array_Local rebuilt = Array_Local_new();
    uint64_t j = 0;
    while (j < (long long)(((*c).locals).count)) {
    Local lo = Array_Local_get((*c).locals, (long long)(j));
    if (j == target) {
    Array_Local_append_value_T(&(rebuilt), (Local){.nameStart = lo.nameStart, .nameLen = lo.nameLen, .tyStart = lo.tyStart, .tyLen = lo.tyLen, .isArray = lo.isArray, .ty = lo.ty, .isInout = lo.isInout, .isMut = lo.isMut, .owned = lo.owned, .moved = 1, .cnum = lo.cnum});
    }
    else {
    Array_Local_append_value_T(&(rebuilt), lo);
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).locals = Array_Local_share(rebuilt);
    Array_Local_release(rebuilt);
}
void markMovedExpr_c_Comp_exprId_U64(Comp* c, uint64_t exprId) {
    {
    Expr _m484 = Array_Expr_get((*c).exprs, (long long)(exprId));
    if (_m484.tag == 1) {
        uint64_t start = _m484.data.Ident.start;
        (void)start;
        uint64_t len = _m484.data.Ident.len;
        (void)len;
    markMovedLocal_c_Comp_start_U64_len_U64(&((*c)), start, len);
    }
    else {
    }
    }
}
TypeInfo fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    Array_FieldDef fs = Array_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef f = Array_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    if (f.tyIsArray) {
    }
    else {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    { TypeInfo __ret485 = (TypeInfo){.kind = 2, .nameStart = f.tyStart, .nameLen = f.tyLen, .ref = f.ty};
    Array_FieldDef_release(fs);
    StructDef_release(s);
    return __ret485; }
    }
    }
    { TypeInfo __ret486 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    Array_FieldDef_release(fs);
    StructDef_release(s);
    return __ret486; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { TypeInfo __ret487 = scalarInfo();
    return __ret487; }
}
long long fieldDeclaredMut_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    Array_FieldDef fs = Array_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef f = Array_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    { long long __ret488 = f.isMut;
    Array_FieldDef_release(fs);
    StructDef_release(s);
    return __ret488; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { long long __ret489 = 1;
    return __ret489; }
}
uint64_t fieldVis_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t structStart, uint64_t structLen, uint64_t fieldStart, uint64_t fieldLen) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, structStart, structLen)) {
    Array_FieldDef fs = Array_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef f = Array_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    { uint64_t __ret490 = f.vis;
    Array_FieldDef_release(fs);
    StructDef_release(s);
    return __ret490; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { uint64_t __ret491 = 3;
    return __ret491; }
}
long long inAnonImplOf_c_Comp_ownerStart_U64_ownerLen_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen) {
    if ((*c).curHasRecv) {
    { long long __ret492 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), (*c).curRecvStart, (*c).curRecvLen, ownerStart, ownerLen);
    return __ret492; }
    }
    { long long __ret493 = 0;
    return __ret493; }
}
void checkFieldReadVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t offset) {
    uint64_t v = fieldVis_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), ownerStart, ownerLen, fieldStart, fieldLen);
    if (v == 0) {
    if (inAnonImplOf_c_Comp_ownerStart_U64_ownerLen_U64(&((*c)), ownerStart, ownerLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"field is private (visible only in its type's anonymous impl)", 60});
    }
    }
}
void checkFieldWriteVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t offset) {
    uint64_t v = fieldVis_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), ownerStart, ownerLen, fieldStart, fieldLen);
    if (v == 0) {
    if (inAnonImplOf_c_Comp_ownerStart_U64_ownerLen_U64(&((*c)), ownerStart, ownerLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"field is private (writable only in its type's anonymous impl)", 61});
    }
    }
    else {
    if (v == 1) {
    if (inAnonImplOf_c_Comp_ownerStart_U64_ownerLen_U64(&((*c)), ownerStart, ownerLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"field is `pub(get)` — readable but writable only in its type's anonymous impl", 79});
    }
    }
    }
}
void checkMethodVis_c_Comp_ownerStart_U64_ownerLen_U64_mf_Func_offset_U64(Comp* c, uint64_t ownerStart, uint64_t ownerLen, Func mf, uint64_t offset) {
    if (mf.isPub) {
    }
    else {
    if (inAnonImplOf_c_Comp_ownerStart_U64_ownerLen_U64(&((*c)), ownerStart, ownerLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"method is private (callable only in its type's anonymous impl; put it in a `pub impl`)", 86});
    }
    }
}
long long placeIsMutable_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m494 = e;
    if (_m494.tag == 1) {
        uint64_t start = _m494.data.Ident.start;
        (void)start;
        uint64_t len = _m494.data.Ident.len;
        (void)len;
    { long long __ret495 = localIsMutable_c_Comp_start_U64_len_U64(&((*c)), start, len);
    Expr_release(e);
    return __ret495; }
    }
    else if (_m494.tag == 5) {
        uint64_t base = _m494.data.Field.base;
        (void)base;
        uint64_t nameStart = _m494.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m494.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 2) {
    if (fieldDeclaredMut_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen)) {
    { long long __ret496 = placeIsMutable_c_Comp_id_U64(&((*c)), base);
    Expr_release(e);
    return __ret496; }
    }
    { long long __ret497 = 0;
    Expr_release(e);
    return __ret497; }
    }
    { long long __ret498 = placeIsMutable_c_Comp_id_U64(&((*c)), base);
    Expr_release(e);
    return __ret498; }
    }
    else if (_m494.tag == 9) {
        uint64_t base = _m494.data.Index.base;
        (void)base;
        uint64_t index = _m494.data.Index.index;
        (void)index;
    { long long __ret499 = placeIsMutable_c_Comp_id_U64(&((*c)), base);
    Expr_release(e);
    return __ret499; }
    }
    else if (_m494.tag == 16) {
        uint64_t base = _m494.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m494.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m494.data.Arrow.nameLen;
        (void)nameLen;
    { long long __ret500 = 1;
    Expr_release(e);
    return __ret500; }
    }
    else {
    { long long __ret501 = 1;
    Expr_release(e);
    return __ret501; }
    }
    }
    Expr_release(e);
}
TypeInfo exprType_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m502 = e;
    if (_m502.tag == 0) {
        long long isBool = _m502.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m502.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m502.data.Int.tyLen;
        (void)tyLen;
    if (isBool) {
    Bind b = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Bool", 4}, 4);
    if (b.nameLen != 0) {
    { TypeInfo __ret503 = (TypeInfo){.kind = 0, .nameStart = b.nameStart, .nameLen = b.nameLen, .ref = 0};
    Expr_release(e);
    return __ret503; }
    }
    }
    if (tyLen != 0) {
    { TypeInfo __ret504 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), tyStart, tyLen, 0);
    Expr_release(e);
    return __ret504; }
    }
    { TypeInfo __ret505 = scalarInfo();
    Expr_release(e);
    return __ret505; }
    }
    else if (_m502.tag == 7) {
        uint64_t start = _m502.data.Str.start;
        (void)start;
        uint64_t len = _m502.data.Str.len;
        (void)len;
    { TypeInfo __ret506 = (TypeInfo){.kind = 1, .nameStart = 0, .nameLen = 0, .ref = 0};
    Expr_release(e);
    return __ret506; }
    }
    else if (_m502.tag == 1) {
        uint64_t start = _m502.data.Ident.start;
        (void)start;
        uint64_t len = _m502.data.Ident.len;
        (void)len;
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    if ((*c).curRecvInstRef != 0) {
    TypeRef rt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)((*c).curRecvInstRef)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), rt.nameStart, rt.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((rt.args).count) == 1) {
    Bind en = arrayElemNameForRef_c_Comp_elemRef_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
    { TypeInfo __ret507 = (TypeInfo){.kind = 3, .nameStart = en.nameStart, .nameLen = en.nameLen, .ref = (*c).curRecvInstRef};
    TypeRef_release(rt);
    Expr_release(e);
    return __ret507; }
    }
    }
    { TypeInfo __ret508 = (TypeInfo){.kind = 2, .nameStart = rt.nameStart, .nameLen = rt.nameLen, .ref = (*c).curRecvInstRef};
    TypeRef_release(rt);
    Expr_release(e);
    return __ret508; }
    TypeRef_release(rt);
    }
    { TypeInfo __ret509 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), (*c).curRecvStart, (*c).curRecvLen, 0);
    Expr_release(e);
    return __ret509; }
    }
    if ((*c).curInClosure) {
    uint64_t ci = 0;
    while (ci < (long long)(((*c).captures).count)) {
    CaptureEntry ce = Array_CaptureEntry_get((*c).captures, (long long)(ci));
    if (ce.closureId == (*c).curClosureId) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ce.nameStart, ce.nameLen, start, len)) {
    if (isRefInst_c_Comp_ref_U64(&((*c)), ce.ty)) {
    TypeRef rt2 = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ce.ty)));
    { TypeInfo __ret510 = (TypeInfo){.kind = 2, .nameStart = rt2.nameStart, .nameLen = rt2.nameLen, .ref = ce.ty};
    TypeRef_release(rt2);
    Expr_release(e);
    return __ret510; }
    TypeRef_release(rt2);
    }
    { TypeInfo __ret511 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), ce.tyStart, ce.tyLen, ce.isArray);
    Expr_release(e);
    return __ret511; }
    }
    }
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    uint64_t i = (long long)(((*c).locals).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Local lo = Array_Local_get((*c).locals, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.nameStart, lo.nameLen, start, len)) {
    if (lo.isArray) {
    { TypeInfo __ret512 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), lo.tyStart, lo.tyLen, 1);
    Expr_release(e);
    return __ret512; }
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    TypeRef lt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(lo.ty)));
    { TypeInfo __ret513 = (TypeInfo){.kind = 2, .nameStart = lt.nameStart, .nameLen = lt.nameLen, .ref = lo.ty};
    TypeRef_release(lt);
    Expr_release(e);
    return __ret513; }
    TypeRef_release(lt);
    }
    if (isRefInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    TypeRef lt2 = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(lo.ty)));
    { TypeInfo __ret514 = (TypeInfo){.kind = 2, .nameStart = lt2.nameStart, .nameLen = lt2.nameLen, .ref = lo.ty};
    TypeRef_release(lt2);
    Expr_release(e);
    return __ret514; }
    TypeRef_release(lt2);
    }
    if (isRawBufInst_c_Comp_ref_U64(&((*c)), lo.ty)) {
    TypeRef lt3 = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(lo.ty)));
    { TypeInfo __ret515 = (TypeInfo){.kind = 2, .nameStart = lt3.nameStart, .nameLen = lt3.nameLen, .ref = lo.ty};
    TypeRef_release(lt3);
    Expr_release(e);
    return __ret515; }
    TypeRef_release(lt3);
    }
    if (lo.isArray) {
    }
    else {
    uint64_t k = 0;
    while (k < (long long)(((*c).curTypeParams).count)) {
    Bind tp = Array_Bind_get((*c).curTypeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), lo.tyStart, lo.tyLen, tp.nameStart, tp.nameLen)) {
    { TypeInfo __ret516 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get((*c).curTypeArgs, (long long)(k)));
    Expr_release(e);
    return __ret516; }
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    { TypeInfo __ret517 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), lo.tyStart, lo.tyLen, lo.isArray);
    Expr_release(e);
    return __ret517; }
    }
    }
    { TypeInfo __ret518 = scalarInfo();
    Expr_release(e);
    return __ret518; }
    }
    else if (_m502.tag == 2) {
        int64_t op = _m502.data.Unary.op;
        (void)op;
        uint64_t operand = _m502.data.Unary.operand;
        (void)operand;
    if (op == opSub()) {
    { TypeInfo __ret519 = exprType_c_Comp_id_U64(&((*c)), operand);
    Expr_release(e);
    return __ret519; }
    }
    if (op == opBitNot()) {
    { TypeInfo __ret520 = exprType_c_Comp_id_U64(&((*c)), operand);
    Expr_release(e);
    return __ret520; }
    }
    { TypeInfo __ret521 = scalarInfo();
    Expr_release(e);
    return __ret521; }
    }
    else if (_m502.tag == 3) {
        int64_t op = _m502.data.Binary.op;
        (void)op;
        uint64_t lhs = _m502.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m502.data.Binary.rhs;
        (void)rhs;
    if (op >= 56) {
    if (op <= 60) {
    { TypeInfo __ret522 = exprType_c_Comp_id_U64(&((*c)), lhs);
    Expr_release(e);
    return __ret522; }
    }
    }
    if (op >= 74) {
    if (op <= 78) {
    { TypeInfo __ret523 = exprType_c_Comp_id_U64(&((*c)), lhs);
    Expr_release(e);
    return __ret523; }
    }
    }
    { TypeInfo __ret524 = scalarInfo();
    Expr_release(e);
    return __ret524; }
    }
    else if (_m502.tag == 4) {
        uint64_t nameStart = _m502.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m502.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m502.data.Call.args;
        (void)args;
    if (isRawIntrinsicName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawLoad", 7})) {
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    if (bt.ref < (long long)(((*c).types).count)) {
    TypeRef rb = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(bt.ref)));
    if ((long long)((rb.args).count) == 1) {
    { TypeInfo __ret525 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(rb.args, (long long)(0)));
    TypeRef_release(rb);
    Expr_release(e);
    return __ret525; }
    }
    TypeRef_release(rb);
    }
    { TypeInfo __ret526 = scalarInfo();
    Expr_release(e);
    return __ret526; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawCap", 6})) {
    Bind u64 = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"U64", 3}, 3);
    if (u64.nameLen != 0) {
    { TypeInfo __ret527 = (TypeInfo){.kind = 0, .nameStart = u64.nameStart, .nameLen = u64.nameLen, .ref = 0};
    Expr_release(e);
    return __ret527; }
    }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawIsUnique", 11})) {
    Bind bl = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Bool", 4}, 4);
    if (bl.nameLen != 0) {
    { TypeInfo __ret528 = (TypeInfo){.kind = 0, .nameStart = bl.nameStart, .nameLen = bl.nameLen, .ref = 0};
    Expr_release(e);
    return __ret528; }
    }
    }
    { TypeInfo __ret529 = scalarInfo();
    Expr_release(e);
    return __ret529; }
    }
    if (isArrayIntrinsicName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayGet", 8})) {
    TypeInfo at = exprType_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    { TypeInfo __ret530 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), at.nameStart, at.nameLen, 0);
    Expr_release(e);
    return __ret530; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayLen", 8})) {
    Bind u64 = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"U64", 3}, 3);
    if (u64.nameLen != 0) {
    { TypeInfo __ret531 = (TypeInfo){.kind = 0, .nameStart = u64.nameStart, .nameLen = u64.nameLen, .ref = 0};
    Expr_release(e);
    return __ret531; }
    }
    }
    { TypeInfo __ret532 = scalarInfo();
    Expr_release(e);
    return __ret532; }
    }
    uint64_t fi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args));
    if (fi < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRet) {
    if (isGenericFreeFn_c_Comp_fi_U64(&((*c)), fi)) {
    if (f.retIsArray) {
    }
    else {
    Array_U64 inferred = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), f, Array_Arg_share(args));
    uint64_t k = 0;
    while (k < (long long)((f.typeParams).count)) {
    Bind tp = Array_Bind_get(f.typeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.retStart, f.retLen, tp.nameStart, tp.nameLen)) {
    if (k < (long long)((inferred).count)) {
    if (Array_U64_get(inferred, (long long)(k)) != 0) {
    { TypeInfo __ret533 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(inferred, (long long)(k)));
    Array_U64_release(inferred);
    Func_release(f);
    Expr_release(e);
    return __ret533; }
    }
    }
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_release(inferred);
    }
    }
    if (f.retIsArray) {
    }
    else {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), f.retTy)) {
    TypeRef rtr = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(f.retTy)));
    { TypeInfo __ret534 = (TypeInfo){.kind = 2, .nameStart = rtr.nameStart, .nameLen = rtr.nameLen, .ref = f.retTy};
    TypeRef_release(rtr);
    Func_release(f);
    Expr_release(e);
    return __ret534; }
    TypeRef_release(rtr);
    }
    }
    { TypeInfo __ret535 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), f.retStart, f.retLen, f.retIsArray);
    Func_release(f);
    Expr_release(e);
    return __ret535; }
    }
    { TypeInfo __ret536 = scalarInfo();
    Func_release(f);
    Expr_release(e);
    return __ret536; }
    Func_release(f);
    }
    uint64_t lvi = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    if (lvi < (long long)(((*c).locals).count)) {
    uint64_t lty = Array_Local_get((*c).locals, (long long)(lvi)).ty;
    if (isFnType_c_Comp_ref_U64(&((*c)), lty)) {
    TypeRef ftr = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(lty)));
    if ((long long)((ftr.args).count) > 0) {
    { TypeInfo __ret537 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(ftr.args, (long long)(0)));
    TypeRef_release(ftr);
    Expr_release(e);
    return __ret537; }
    }
    TypeRef_release(ftr);
    }
    }
    { TypeInfo __ret538 = scalarInfo();
    Expr_release(e);
    return __ret538; }
    }
    else if (_m502.tag == 5) {
        uint64_t base = _m502.data.Field.base;
        (void)base;
        uint64_t nameStart = _m502.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m502.data.Field.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 1) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"bytes", 5})) {
    Bind u8 = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"U8", 2}, 2);
    if (u8.nameLen != 0) {
    { TypeInfo __ret539 = (TypeInfo){.kind = 3, .nameStart = u8.nameStart, .nameLen = u8.nameLen, .ref = 0};
    Expr_release(e);
    return __ret539; }
    }
    }
    }
    if (bt.kind == 3) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"count", 5})) {
    Bind u64 = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"U64", 3}, 3);
    if (u64.nameLen != 0) {
    { TypeInfo __ret540 = (TypeInfo){.kind = 0, .nameStart = u64.nameStart, .nameLen = u64.nameLen, .ref = 0};
    Expr_release(e);
    return __ret540; }
    }
    }
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    { TypeInfo __ret541 = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.ref, nameStart, nameLen);
    Expr_release(e);
    return __ret541; }
    }
    if (bt.kind == 2) {
    { TypeInfo __ret542 = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    Expr_release(e);
    return __ret542; }
    }
    { TypeInfo __ret543 = scalarInfo();
    Expr_release(e);
    return __ret543; }
    }
    else if (_m502.tag == 6) {
        uint64_t typeStart = _m502.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m502.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m502.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m502.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m502.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m502.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m502.data.Make.fields;
        (void)fields;
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ty)) {
    { TypeInfo __ret544 = (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = ty};
    Expr_release(e);
    return __ret544; }
    }
    { TypeInfo __ret545 = (TypeInfo){.kind = 2, .nameStart = typeStart, .nameLen = typeLen, .ref = 0};
    Expr_release(e);
    return __ret545; }
    }
    else if (_m502.tag == 8) {
        Array_U64 elems = _m502.data.Array.elems;
        (void)elems;
    { TypeInfo __ret546 = scalarInfo();
    Expr_release(e);
    return __ret546; }
    }
    else if (_m502.tag == 9) {
        uint64_t base = _m502.data.Index.base;
        (void)base;
        uint64_t index = _m502.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    uint64_t er = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    if (er != 0) {
    uint64_t rr = resolveTy_c_Comp_tyRef_U64(&((*c)), er);
    if (rr < (long long)(((*c).types).count)) {
    TypeRef rt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(rr)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), rt.nameStart, rt.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((rt.args).count) > 0) {
    Bind xn = arrayElemNameForRef_c_Comp_elemRef_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
    { TypeInfo __ret547 = (TypeInfo){.kind = 3, .nameStart = xn.nameStart, .nameLen = xn.nameLen, .ref = 0};
    TypeRef_release(rt);
    Expr_release(e);
    return __ret547; }
    }
    }
    if (isCompoundType_c_Comp_ref_U64(&((*c)), rr)) {
    { TypeInfo __ret548 = (TypeInfo){.kind = 2, .nameStart = rt.nameStart, .nameLen = rt.nameLen, .ref = rr};
    TypeRef_release(rt);
    Expr_release(e);
    return __ret548; }
    }
    TypeRef_release(rt);
    }
    }
    { TypeInfo __ret549 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), bt.nameStart, bt.nameLen, 0);
    Expr_release(e);
    return __ret549; }
    }
    { TypeInfo __ret550 = scalarInfo();
    Expr_release(e);
    return __ret550; }
    }
    else if (_m502.tag == 10) {
        uint64_t recv = _m502.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m502.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m502.data.Method.nameLen;
        (void)nameLen;
        Array_Arg args = _m502.data.Method.args;
        (void)args;
    Bind arn = assocRecvName_c_Comp_recv_U64(&((*c)), recv);
    if (arn.nameLen != 0) {
    uint64_t afi = findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), arn.nameStart, arn.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (afi == (long long)(((*c).funcs).count)) {
    { TypeInfo __ret551 = scalarInfo();
    Expr_release(e);
    return __ret551; }
    }
    Func af = Func_share(Array_Func_get((*c).funcs, (long long)(afi)));
    if (af.hasRet) {
    { TypeInfo __ret552 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), af.retStart, af.retLen, af.retIsArray);
    Func_release(af);
    Expr_release(e);
    return __ret552; }
    }
    { TypeInfo __ret553 = scalarInfo();
    Func_release(af);
    Expr_release(e);
    return __ret553; }
    Func_release(af);
    }
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (rt.kind == 1) {
    Bind ss = stringTypeSpan_c_Comp(&((*c)));
    if (ss.nameLen != 0) {
    rt = (TypeInfo){.kind = 2, .nameStart = ss.nameStart, .nameLen = ss.nameLen, .ref = 0};
    }
    }
    if (rt.kind == 2) {
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (mi == (long long)(((*c).funcs).count)) {
    { TypeInfo __ret554 = scalarInfo();
    Expr_release(e);
    return __ret554; }
    }
    Func mf = Func_share(Array_Func_get((*c).funcs, (long long)(mi)));
    if (mf.hasRet) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), rt.ref)) {
    TypeRef gt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(rt.ref)));
    uint64_t gsi = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), gt.nameStart, gt.nameLen);
    if (gsi < (long long)(((*c).structs).count)) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), gt.nameStart, gt.nameLen, rt.ref);
    Array_Bind gSavedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 gSavedA = Array_U64_share((*c).curTypeArgs);
    uint64_t rcount = (long long)((Array_StructDef_get((*c).structs, (long long)(gsi)).typeParams).count);
    Array_U64 gfa = Array_U64_new();
    uint64_t gri = 0;
    while (gri < rcount) {
    if (gri < (long long)((gt.args).count)) {
    Array_U64_append_value_T(&(gfa), Array_U64_get(gt.args, (long long)(gri)));
    }
    gri = ({ uint64_t __ov; if (__builtin_add_overflow((gri), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if ((long long)((mf.typeParams).count) > rcount) {
    Array_U64 ginf = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), mf, Array_Arg_share(args));
    uint64_t goi = rcount;
    while (goi < (long long)((ginf).count)) {
    Array_U64_append_value_T(&(gfa), Array_U64_get(ginf, (long long)(goi)));
    goi = ({ uint64_t __ov; if (__builtin_add_overflow((goi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_release(ginf);
    }
    (*c).curTypeParams = Array_Bind_share(mf.typeParams);
    (*c).curTypeArgs = Array_U64_share(gfa);
    uint64_t gr = groundTypeRef_c_Comp_ref_U64(&((*c)), mf.retTy);
    (*c).curTypeParams = Array_Bind_share(gSavedP);
    (*c).curTypeArgs = Array_U64_share(gSavedA);
    clearSelfItemEnv_c_Comp(&((*c)));
    { TypeInfo __ret555 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), gr);
    Array_U64_release(gfa);
    Array_U64_release(gSavedA);
    Array_Bind_release(gSavedP);
    TypeRef_release(gt);
    Func_release(mf);
    Expr_release(e);
    return __ret555; }
    Array_U64_release(gfa);
    Array_U64_release(gSavedA);
    Array_Bind_release(gSavedP);
    }
    uint64_t gei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), gt.nameStart, gt.nameLen);
    if (gei < (long long)(((*c).enums).count)) {
    { TypeInfo __ret556 = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), rt.ref, Array_Bind_share(Array_EnumDef_get((*c).enums, (long long)(gei)).typeParams), mf.retTy);
    TypeRef_release(gt);
    Func_release(mf);
    Expr_release(e);
    return __ret556; }
    }
    TypeRef_release(gt);
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), mf.retTy)) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), rt.nameStart, rt.nameLen, 0);
    Array_Bind savedTP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedTA = Array_U64_share((*c).curTypeArgs);
    if ((long long)((mf.typeParams).count) > 0) {
    (*c).curTypeParams = Array_Bind_share(mf.typeParams);
    (*c).curTypeArgs = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), mf, Array_Arg_share(args));
    }
    uint64_t gr2 = groundTypeRef_c_Comp_ref_U64(&((*c)), mf.retTy);
    (*c).curTypeParams = Array_Bind_share(savedTP);
    (*c).curTypeArgs = Array_U64_share(savedTA);
    clearSelfItemEnv_c_Comp(&((*c)));
    { TypeInfo __ret557 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), gr2);
    Array_U64_release(savedTA);
    Array_Bind_release(savedTP);
    Func_release(mf);
    Expr_release(e);
    return __ret557; }
    Array_U64_release(savedTA);
    Array_Bind_release(savedTP);
    }
    { TypeInfo __ret558 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), mf.retStart, mf.retLen, mf.retIsArray);
    Func_release(mf);
    Expr_release(e);
    return __ret558; }
    }
    { TypeInfo __ret559 = scalarInfo();
    Func_release(mf);
    Expr_release(e);
    return __ret559; }
    Func_release(mf);
    }
    if (rt.kind == 3) {
    Bind arrName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Array", 5}, 5);
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), arrName.nameStart, arrName.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (mi == (long long)(((*c).funcs).count)) {
    { TypeInfo __ret560 = scalarInfo();
    Expr_release(e);
    return __ret560; }
    }
    Func mf = Func_share(Array_Func_get((*c).funcs, (long long)(mi)));
    if (mf.hasRet) {
    if ((long long)((mf.typeParams).count) >= 1) {
    if (mf.retTy < (long long)(((*c).types).count)) {
    TypeRef rtt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(mf.retTy)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), rtt.nameStart, rtt.nameLen, Array_Bind_get(mf.typeParams, (long long)(0)).nameStart, Array_Bind_get(mf.typeParams, (long long)(0)).nameLen)) {
    { TypeInfo __ret561 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), rt.nameStart, rt.nameLen, 0);
    TypeRef_release(rtt);
    Func_release(mf);
    Expr_release(e);
    return __ret561; }
    }
    TypeRef_release(rtt);
    }
    }
    { TypeInfo __ret562 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), mf.retStart, mf.retLen, mf.retIsArray);
    Func_release(mf);
    Expr_release(e);
    return __ret562; }
    }
    { TypeInfo __ret563 = scalarInfo();
    Func_release(mf);
    Expr_release(e);
    return __ret563; }
    Func_release(mf);
    }
    { TypeInfo __ret564 = scalarInfo();
    Expr_release(e);
    return __ret564; }
    }
    else if (_m502.tag == 11) {
        uint64_t operand = _m502.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m502.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m502.data.Cast.tyLen;
        (void)tyLen;
    { TypeInfo __ret565 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), tyStart, tyLen, 0);
    Expr_release(e);
    return __ret565; }
    }
    else if (_m502.tag == 12) {
        uint64_t scrut = _m502.data.MatchExpr.scrut;
        (void)scrut;
        Array_MatchArm arms = _m502.data.MatchExpr.arms;
        (void)arms;
    if ((long long)((arms).count) > 0) {
    { TypeInfo __ret566 = exprType_c_Comp_id_U64(&((*c)), Array_MatchArm_get(arms, (long long)(0)).body);
    Expr_release(e);
    return __ret566; }
    }
    { TypeInfo __ret567 = scalarInfo();
    Expr_release(e);
    return __ret567; }
    }
    else if (_m502.tag == 13) {
        uint64_t cond = _m502.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m502.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m502.data.IfExpr.elseBlk;
        (void)elseBlk;
    uint64_t g = blockGiveExpr_c_Comp_blkId_U64(&((*c)), thenBlk);
    if (g < (long long)(((*c).exprs).count)) {
    { TypeInfo __ret568 = exprType_c_Comp_id_U64(&((*c)), g);
    Expr_release(e);
    return __ret568; }
    }
    { TypeInfo __ret569 = scalarInfo();
    Expr_release(e);
    return __ret569; }
    }
    else if (_m502.tag == 14) {
        uint64_t opt = _m502.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m502.data.Coalesce.deflt;
        (void)deflt;
    { TypeInfo __ret570 = exprType_c_Comp_id_U64(&((*c)), deflt);
    Expr_release(e);
    return __ret570; }
    }
    else if (_m502.tag == 15) {
        uint64_t expr = _m502.data.Try.expr;
        (void)expr;
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), expr);
    if (isGenericInst_c_Comp_ref_U64(&((*c)), rt.ref)) {
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(rt.ref)));
    if ((long long)((inst.args).count) > 0) {
    { TypeInfo __ret571 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(inst.args, (long long)(0)));
    TypeRef_release(inst);
    Expr_release(e);
    return __ret571; }
    }
    TypeRef_release(inst);
    }
    { TypeInfo __ret572 = scalarInfo();
    Expr_release(e);
    return __ret572; }
    }
    else if (_m502.tag == 16) {
        uint64_t base = _m502.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m502.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m502.data.Arrow.nameLen;
        (void)nameLen;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (isRefInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(bt.ref)));
    TypeInfo pt = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(inst.args, (long long)(0)));
    if (pt.kind == 2) {
    { TypeInfo __ret573 = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), pt.nameStart, pt.nameLen, nameStart, nameLen);
    TypeRef_release(inst);
    Expr_release(e);
    return __ret573; }
    }
    TypeRef_release(inst);
    }
    { TypeInfo __ret574 = scalarInfo();
    Expr_release(e);
    return __ret574; }
    }
    else if (_m502.tag == 17) {
        Array_Param params = _m502.data.Closure.params;
        (void)params;
        long long hasRet = _m502.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m502.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m502.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m502.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m502.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m502.data.Closure.body;
        (void)body;
    { TypeInfo __ret575 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), closureFnTypeRef_c_Comp_params_AParam_retTy_U64(&((*c)), Array_Param_share(params), retTy));
    Expr_release(e);
    return __ret575; }
    }
    else if (_m502.tag == 18) {
        uint64_t operand = _m502.data.Move.operand;
        (void)operand;
        long long isBorrow = _m502.data.Move.isBorrow;
        (void)isBorrow;
    { TypeInfo __ret576 = exprType_c_Comp_id_U64(&((*c)), operand);
    Expr_release(e);
    return __ret576; }
    }
    else if (_m502.tag == 19) {
        uint64_t operand = _m502.data.Await.operand;
        (void)operand;
    TypeInfo ot = exprType_c_Comp_id_U64(&((*c)), operand);
    if (ot.ref != 0) {
    TypeRef tr = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ot.ref)));
    if ((long long)((tr.args).count) > 0) {
    { TypeInfo __ret577 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(tr.args, (long long)(0)));
    TypeRef_release(tr);
    Expr_release(e);
    return __ret577; }
    }
    TypeRef_release(tr);
    }
    { TypeInfo __ret578 = scalarInfo();
    Expr_release(e);
    return __ret578; }
    }
    else { __builtin_unreachable(); }
    }
    { TypeInfo __ret579 = scalarInfo();
    Expr_release(e);
    return __ret579; }
    Expr_release(e);
}
uint64_t blockGiveExpr_c_Comp_blkId_U64(Comp* c, uint64_t blkId) {
    Block blk = Block_share(Array_Block_get((*c).blocks, (long long)(blkId)));
    Array_U64 stmts = Array_U64_share(blk.stmts);
    uint64_t i = 0;
    uint64_t found = (long long)(((*c).exprs).count);
    while (i < (long long)((stmts).count)) {
    Stmt s = Stmt_share(Array_Stmt_get((*c).stmts, (long long)(Array_U64_get(stmts, (long long)(i)))));
    {
    Stmt _m580 = s;
    if (_m580.tag == 9) {
        uint64_t value = _m580.data.Give.value;
        (void)value;
    found = value;
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Stmt_release(s);
    }
    { uint64_t __ret581 = found;
    Array_U64_release(stmts);
    Block_release(blk);
    return __ret581; }
    Array_U64_release(stmts);
    Block_release(blk);
}
void addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen) {
    addBindLocalCn_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64_cnum_U64(&((*c)), enumStart, enumLen, variantStart, variantLen, fieldStart, fieldLen, bindStart, bindLen, 0);
}
void addBindLocalCn_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64_cnum_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen, uint64_t bindStart, uint64_t bindLen, uint64_t cnum) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef f = Array_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, fieldStart, fieldLen)) {
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), bindStart, bindLen, f.tyStart, f.tyLen, f.tyIsArray, f.ty, 0, 0, 0, cnum);
    Array_FieldDef_release(fs);
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(e);
    return;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
}
void genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(Comp* c, uint64_t enumStart, uint64_t enumLen, uint64_t variantStart, uint64_t variantLen, uint64_t bindStart, uint64_t bindLen) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, enumStart, enumLen)) {
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef f = Array_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, bindStart, bindLen)) {
    genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), f.tyStart, f.tyLen, f.tyIsArray);
    Array_FieldDef_release(fs);
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(e);
    return;
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    plew_write((PlewString){"long long", 9});
}
int64_t opEq(void) {
    { int64_t __ret582 = kindCode_k_Kind((Kind){.tag = 42});
    return __ret582; }
}
int64_t opNe(void) {
    { int64_t __ret583 = kindCode_k_Kind((Kind){.tag = 43});
    return __ret583; }
}
int64_t opLt(void) {
    { int64_t __ret584 = kindCode_k_Kind((Kind){.tag = 44});
    return __ret584; }
}
int64_t opLe(void) {
    { int64_t __ret585 = kindCode_k_Kind((Kind){.tag = 45});
    return __ret585; }
}
int64_t opGt(void) {
    { int64_t __ret586 = kindCode_k_Kind((Kind){.tag = 46});
    return __ret586; }
}
int64_t opGe(void) {
    { int64_t __ret587 = kindCode_k_Kind((Kind){.tag = 47});
    return __ret587; }
}
int64_t opAdd(void) {
    { int64_t __ret588 = kindCode_k_Kind((Kind){.tag = 48});
    return __ret588; }
}
int64_t opSub(void) {
    { int64_t __ret589 = kindCode_k_Kind((Kind){.tag = 49});
    return __ret589; }
}
int64_t opMul(void) {
    { int64_t __ret590 = kindCode_k_Kind((Kind){.tag = 50});
    return __ret590; }
}
int64_t opDiv(void) {
    { int64_t __ret591 = kindCode_k_Kind((Kind){.tag = 51});
    return __ret591; }
}
int64_t opRem(void) {
    { int64_t __ret592 = kindCode_k_Kind((Kind){.tag = 52});
    return __ret592; }
}
int64_t opAnd(void) {
    { int64_t __ret593 = kindCode_k_Kind((Kind){.tag = 53});
    return __ret593; }
}
int64_t opOr(void) {
    { int64_t __ret594 = kindCode_k_Kind((Kind){.tag = 54});
    return __ret594; }
}
int64_t opNot(void) {
    { int64_t __ret595 = kindCode_k_Kind((Kind){.tag = 55});
    return __ret595; }
}
int64_t opBitAnd(void) {
    { int64_t __ret596 = kindCode_k_Kind((Kind){.tag = 56});
    return __ret596; }
}
int64_t opBitOr(void) {
    { int64_t __ret597 = kindCode_k_Kind((Kind){.tag = 57});
    return __ret597; }
}
int64_t opBitXor(void) {
    { int64_t __ret598 = kindCode_k_Kind((Kind){.tag = 58});
    return __ret598; }
}
int64_t opShl(void) {
    { int64_t __ret599 = kindCode_k_Kind((Kind){.tag = 59});
    return __ret599; }
}
int64_t opShr(void) {
    { int64_t __ret600 = kindCode_k_Kind((Kind){.tag = 60});
    return __ret600; }
}
int64_t opBitNot(void) {
    { int64_t __ret601 = kindCode_k_Kind((Kind){.tag = 61});
    return __ret601; }
}
int64_t opAssign(void) {
    { int64_t __ret602 = kindCode_k_Kind((Kind){.tag = 41});
    return __ret602; }
}
int64_t opAddAssign(void) {
    { int64_t __ret603 = kindCode_k_Kind((Kind){.tag = 65});
    return __ret603; }
}
int64_t opSubAssign(void) {
    { int64_t __ret604 = kindCode_k_Kind((Kind){.tag = 66});
    return __ret604; }
}
int64_t opMulAssign(void) {
    { int64_t __ret605 = kindCode_k_Kind((Kind){.tag = 67});
    return __ret605; }
}
int64_t opDivAssign(void) {
    { int64_t __ret606 = kindCode_k_Kind((Kind){.tag = 68});
    return __ret606; }
}
int64_t opRemAssign(void) {
    { int64_t __ret607 = kindCode_k_Kind((Kind){.tag = 69});
    return __ret607; }
}
int64_t opBitAndAssign(void) {
    { int64_t __ret608 = kindCode_k_Kind((Kind){.tag = 70});
    return __ret608; }
}
int64_t opBitOrAssign(void) {
    { int64_t __ret609 = kindCode_k_Kind((Kind){.tag = 71});
    return __ret609; }
}
int64_t opBitXorAssign(void) {
    { int64_t __ret610 = kindCode_k_Kind((Kind){.tag = 72});
    return __ret610; }
}
int64_t opShlAssign(void) {
    { int64_t __ret611 = kindCode_k_Kind((Kind){.tag = 73});
    return __ret611; }
}
int64_t opShrAssign(void) {
    { int64_t __ret612 = kindCode_k_Kind((Kind){.tag = 74});
    return __ret612; }
}
int64_t opCoalesce(void) {
    { int64_t __ret613 = kindCode_k_Kind((Kind){.tag = 77});
    return __ret613; }
}
PlewString binOpStr_op_I64(int64_t op) {
    if (op == opAdd()) {
    { PlewString __ret614 = (PlewString){" + ", 3};
    return __ret614; }
    }
    if (op == opSub()) {
    { PlewString __ret615 = (PlewString){" - ", 3};
    return __ret615; }
    }
    if (op == opMul()) {
    { PlewString __ret616 = (PlewString){" * ", 3};
    return __ret616; }
    }
    if (op == opDiv()) {
    { PlewString __ret617 = (PlewString){" / ", 3};
    return __ret617; }
    }
    if (op == opRem()) {
    { PlewString __ret618 = (PlewString){" % ", 3};
    return __ret618; }
    }
    if (op == opEq()) {
    { PlewString __ret619 = (PlewString){" == ", 4};
    return __ret619; }
    }
    if (op == opNe()) {
    { PlewString __ret620 = (PlewString){" != ", 4};
    return __ret620; }
    }
    if (op == opLt()) {
    { PlewString __ret621 = (PlewString){" < ", 3};
    return __ret621; }
    }
    if (op == opLe()) {
    { PlewString __ret622 = (PlewString){" <= ", 4};
    return __ret622; }
    }
    if (op == opGt()) {
    { PlewString __ret623 = (PlewString){" > ", 3};
    return __ret623; }
    }
    if (op == opGe()) {
    { PlewString __ret624 = (PlewString){" >= ", 4};
    return __ret624; }
    }
    if (op == opAnd()) {
    { PlewString __ret625 = (PlewString){" && ", 4};
    return __ret625; }
    }
    if (op == opOr()) {
    { PlewString __ret626 = (PlewString){" || ", 4};
    return __ret626; }
    }
    if (op == opBitAnd()) {
    { PlewString __ret627 = (PlewString){" & ", 3};
    return __ret627; }
    }
    if (op == opBitOr()) {
    { PlewString __ret628 = (PlewString){" | ", 3};
    return __ret628; }
    }
    if (op == opBitXor()) {
    { PlewString __ret629 = (PlewString){" ^ ", 3};
    return __ret629; }
    }
    if (op == opShl()) {
    { PlewString __ret630 = (PlewString){" << ", 4};
    return __ret630; }
    }
    if (op == opShr()) {
    { PlewString __ret631 = (PlewString){" >> ", 4};
    return __ret631; }
    }
    { PlewString __ret632 = (PlewString){" ? ", 3};
    return __ret632; }
}
PlewString unaryOpStr_op_I64(int64_t op) {
    if (op == opSub()) {
    { PlewString __ret633 = (PlewString){"-", 1};
    return __ret633; }
    }
    if (op == opBitNot()) {
    { PlewString __ret634 = (PlewString){"~", 1};
    return __ret634; }
    }
    { PlewString __ret635 = (PlewString){"!", 1};
    return __ret635; }
}
int64_t strDecodedLen_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    int64_t n = 0;
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow((start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t end = ({ uint64_t __ov; if (__builtin_sub_overflow((({ uint64_t __ov; if (__builtin_add_overflow((start), (len), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < end) {
    if (Array_U8_get((*c).bytes, (long long)(j)) == 92) {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    n = ({ int64_t __ov; if (__builtin_add_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { int64_t __ret636 = n;
    return __ret636; }
}
long long isCheckedArith_op_I64(int64_t op) {
    if (op == opAdd()) {
    { long long __ret637 = 1;
    return __ret637; }
    }
    if (op == opSub()) {
    { long long __ret638 = 1;
    return __ret638; }
    }
    if (op == opMul()) {
    { long long __ret639 = 1;
    return __ret639; }
    }
    { long long __ret640 = 0;
    return __ret640; }
}
int64_t compoundCheckedBin_op_I64(int64_t op) {
    if (op == opAddAssign()) {
    { int64_t __ret641 = opAdd();
    return __ret641; }
    }
    if (op == opSubAssign()) {
    { int64_t __ret642 = opSub();
    return __ret642; }
    }
    if (op == opMulAssign()) {
    { int64_t __ret643 = opMul();
    return __ret643; }
    }
    { int64_t __ret644 = 0;
    return __ret644; }
}
PlewString overflowBuiltin_op_I64(int64_t op) {
    if (op == opAdd()) {
    { PlewString __ret645 = (PlewString){"__builtin_add_overflow", 22};
    return __ret645; }
    }
    if (op == opSub()) {
    { PlewString __ret646 = (PlewString){"__builtin_sub_overflow", 22};
    return __ret646; }
    }
    { PlewString __ret647 = (PlewString){"__builtin_mul_overflow", 22};
    return __ret647; }
}
TypeInfo arithIntType_c_Comp_lhs_U64_rhs_U64(Comp* c, uint64_t lhs, uint64_t rhs) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 0) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), lt.nameStart, lt.nameLen)) {
    { TypeInfo __ret648 = lt;
    return __ret648; }
    }
    }
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), rhs);
    if (rt.kind == 0) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), rt.nameStart, rt.nameLen)) {
    { TypeInfo __ret649 = rt;
    return __ret649; }
    }
    }
    { TypeInfo __ret650 = scalarInfo();
    return __ret650; }
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
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_get(", 5});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){", (long long)(", 14});
    genExpr_c_Comp_id_U64(&((*c)), index);
    plew_write((PlewString){"))", 2});
}
PlewString intMinMacro_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I8", 2})) {
    { PlewString __ret651 = (PlewString){"INT8_MIN", 8};
    return __ret651; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I16", 3})) {
    { PlewString __ret652 = (PlewString){"INT16_MIN", 9};
    return __ret652; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), start, len, (PlewString){"I32", 3})) {
    { PlewString __ret653 = (PlewString){"INT32_MIN", 9};
    return __ret653; }
    }
    { PlewString __ret654 = (PlewString){"INT64_MIN", 9};
    return __ret654; }
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
    if (op == opAssign()) {
    { PlewString __ret655 = (PlewString){" = ", 3};
    return __ret655; }
    }
    if (op == opAddAssign()) {
    { PlewString __ret656 = (PlewString){" += ", 4};
    return __ret656; }
    }
    if (op == opSubAssign()) {
    { PlewString __ret657 = (PlewString){" -= ", 4};
    return __ret657; }
    }
    if (op == opMulAssign()) {
    { PlewString __ret658 = (PlewString){" *= ", 4};
    return __ret658; }
    }
    if (op == opDivAssign()) {
    { PlewString __ret659 = (PlewString){" /= ", 4};
    return __ret659; }
    }
    if (op == opRemAssign()) {
    { PlewString __ret660 = (PlewString){" %= ", 4};
    return __ret660; }
    }
    if (op == opBitAndAssign()) {
    { PlewString __ret661 = (PlewString){" &= ", 4};
    return __ret661; }
    }
    if (op == opBitOrAssign()) {
    { PlewString __ret662 = (PlewString){" |= ", 4};
    return __ret662; }
    }
    if (op == opBitXorAssign()) {
    { PlewString __ret663 = (PlewString){" ^= ", 4};
    return __ret663; }
    }
    if (op == opShlAssign()) {
    { PlewString __ret664 = (PlewString){" <<= ", 5};
    return __ret664; }
    }
    { PlewString __ret665 = (PlewString){" >>= ", 5};
    return __ret665; }
}
long long isCompoundDiv_op_I64(int64_t op) {
    if (op == opDivAssign()) {
    { long long __ret666 = 1;
    return __ret666; }
    }
    if (op == opRemAssign()) {
    { long long __ret667 = 1;
    return __ret667; }
    }
    { long long __ret668 = 0;
    return __ret668; }
}
PlewString compoundDivFn_op_I64(int64_t op) {
    if (op == opDivAssign()) {
    { PlewString __ret669 = (PlewString){"plew_div(", 9};
    return __ret669; }
    }
    if (op == opRemAssign()) {
    { PlewString __ret670 = (PlewString){"plew_mod(", 9};
    return __ret670; }
    }
    { PlewString __ret671 = (PlewString){"", 0};
    return __ret671; }
}
PlewString assignToBinStr_op_I64(int64_t op) {
    if (op == opAddAssign()) {
    { PlewString __ret672 = (PlewString){" + ", 3};
    return __ret672; }
    }
    if (op == opSubAssign()) {
    { PlewString __ret673 = (PlewString){" - ", 3};
    return __ret673; }
    }
    if (op == opMulAssign()) {
    { PlewString __ret674 = (PlewString){" * ", 3};
    return __ret674; }
    }
    if (op == opDivAssign()) {
    { PlewString __ret675 = (PlewString){" / ", 3};
    return __ret675; }
    }
    if (op == opRemAssign()) {
    { PlewString __ret676 = (PlewString){" % ", 3};
    return __ret676; }
    }
    if (op == opBitAndAssign()) {
    { PlewString __ret677 = (PlewString){" & ", 3};
    return __ret677; }
    }
    if (op == opBitOrAssign()) {
    { PlewString __ret678 = (PlewString){" | ", 3};
    return __ret678; }
    }
    if (op == opBitXorAssign()) {
    { PlewString __ret679 = (PlewString){" ^ ", 3};
    return __ret679; }
    }
    if (op == opShlAssign()) {
    { PlewString __ret680 = (PlewString){" << ", 4};
    return __ret680; }
    }
    { PlewString __ret681 = (PlewString){" >> ", 4};
    return __ret681; }
}
ConstInt notConst(void) {
    { ConstInt __ret682 = (ConstInt){.isConst = 0, .neg = 0, .value = 0};
    return __ret682; }
}
ConstInt mkConst_neg_Bool_mag_U64(long long neg, uint64_t mag) {
    if (mag == 0) {
    { ConstInt __ret683 = (ConstInt){.isConst = 1, .neg = 0, .value = 0};
    return __ret683; }
    }
    { ConstInt __ret684 = (ConstInt){.isConst = 1, .neg = neg, .value = mag};
    return __ret684; }
}
ConstInt addConst_na_Bool_a_U64_nb_Bool_b_U64(long long na, uint64_t a, long long nb, uint64_t b) {
    if (na == nb) {
    if (a > ({ uint64_t __ov; if (__builtin_sub_overflow((9223372036854775807), (b), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })) {
    { ConstInt __ret685 = notConst();
    return __ret685; }
    }
    { ConstInt __ret686 = mkConst_neg_Bool_mag_U64(na, ({ uint64_t __ov; if (__builtin_add_overflow((a), (b), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    return __ret686; }
    }
    if (a >= b) {
    { ConstInt __ret687 = mkConst_neg_Bool_mag_U64(na, ({ uint64_t __ov; if (__builtin_sub_overflow((a), (b), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    return __ret687; }
    }
    { ConstInt __ret688 = mkConst_neg_Bool_mag_U64(nb, ({ uint64_t __ov; if (__builtin_sub_overflow((b), (a), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    return __ret688; }
}
ConstInt foldConst_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m689 = e;
    if (_m689.tag == 0) {
        uint64_t value = _m689.data.Int.value;
        (void)value;
        long long isBool = _m689.data.Int.isBool;
        (void)isBool;
    if (isBool) {
    { ConstInt __ret690 = notConst();
    Expr_release(e);
    return __ret690; }
    }
    if (value > 9223372036854775807) {
    { ConstInt __ret691 = notConst();
    Expr_release(e);
    return __ret691; }
    }
    { ConstInt __ret692 = (ConstInt){.isConst = 1, .neg = 0, .value = value};
    Expr_release(e);
    return __ret692; }
    }
    else if (_m689.tag == 2) {
        int64_t op = _m689.data.Unary.op;
        (void)op;
        uint64_t operand = _m689.data.Unary.operand;
        (void)operand;
    if (op == opSub()) {
    ConstInt o = foldConst_c_Comp_id_U64(&((*c)), operand);
    if (o.isConst) {
    { ConstInt __ret693 = mkConst_neg_Bool_mag_U64(!(o.neg), o.value);
    Expr_release(e);
    return __ret693; }
    }
    }
    { ConstInt __ret694 = notConst();
    Expr_release(e);
    return __ret694; }
    }
    else if (_m689.tag == 3) {
        int64_t op = _m689.data.Binary.op;
        (void)op;
        uint64_t lhs = _m689.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m689.data.Binary.rhs;
        (void)rhs;
    ConstInt a = foldConst_c_Comp_id_U64(&((*c)), lhs);
    ConstInt b = foldConst_c_Comp_id_U64(&((*c)), rhs);
    if (a.isConst) {
    if (b.isConst) {
    if (op == opAdd()) {
    { ConstInt __ret695 = addConst_na_Bool_a_U64_nb_Bool_b_U64(a.neg, a.value, b.neg, b.value);
    Expr_release(e);
    return __ret695; }
    }
    if (op == opSub()) {
    { ConstInt __ret696 = addConst_na_Bool_a_U64_nb_Bool_b_U64(a.neg, a.value, !(b.neg), b.value);
    Expr_release(e);
    return __ret696; }
    }
    if (op == opMul()) {
    if (a.value == 0) {
    { ConstInt __ret697 = mkConst_neg_Bool_mag_U64(0, 0);
    Expr_release(e);
    return __ret697; }
    }
    if (b.value > ({ uint64_t __dl = (9223372036854775807); uint64_t __dr = (a.value); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); __dl / __dr; })) {
    { ConstInt __ret698 = notConst();
    Expr_release(e);
    return __ret698; }
    }
    { ConstInt __ret699 = mkConst_neg_Bool_mag_U64((a.neg != b.neg), ({ uint64_t __ov; if (__builtin_mul_overflow((a.value), (b.value), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    Expr_release(e);
    return __ret699; }
    }
    }
    }
    { ConstInt __ret700 = notConst();
    Expr_release(e);
    return __ret700; }
    }
    else {
    { ConstInt __ret701 = notConst();
    Expr_release(e);
    return __ret701; }
    }
    }
    Expr_release(e);
}
long long tiIsInt_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.kind == 0) {
    if (ti.nameLen != 0) {
    { long long __ret702 = isIntType_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen);
    return __ret702; }
    }
    }
    { long long __ret703 = 0;
    return __ret703; }
}
void checkLitLeaf_c_Comp_value_U64_neg_Bool_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(Comp* c, uint64_t value, long long neg, uint64_t offset, long long isBool, uint64_t tyStart, uint64_t tyLen, uint64_t eKind, uint64_t eBits, long long eSgn) {
    if (isBool) {
    return;
    }
    if (tyLen != 0) {
    if (litFitsType_c_Comp_value_U64_neg_Bool_dstStart_U64_dstLen_U64(&((*c)), value, neg, tyStart, tyLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"integer literal is out of range for its type", 44});
    }
    return;
    }
    if (eKind == 1) {
    if (litFitsBits_value_U64_neg_Bool_bits_U64_sgn_Bool(value, neg, eBits, eSgn)) {
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
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m704 = e;
    if (_m704.tag == 0) {
        uint64_t value = _m704.data.Int.value;
        (void)value;
        uint64_t offset = _m704.data.Int.offset;
        (void)offset;
        long long isBool = _m704.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m704.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m704.data.Int.tyLen;
        (void)tyLen;
    checkLitLeaf_c_Comp_value_U64_neg_Bool_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), value, 0, offset, isBool, tyStart, tyLen, eKind, eBits, eSgn);
    }
    else if (_m704.tag == 2) {
        int64_t op = _m704.data.Unary.op;
        (void)op;
        uint64_t operand = _m704.data.Unary.operand;
        (void)operand;
    if (op == opSub()) {
    Expr oe = Expr_share(Array_Expr_get((*c).exprs, (long long)(operand)));
    {
    Expr _m705 = oe;
    if (_m705.tag == 0) {
        uint64_t value = _m705.data.Int.value;
        (void)value;
        uint64_t offset = _m705.data.Int.offset;
        (void)offset;
        long long isBool = _m705.data.Int.isBool;
        (void)isBool;
        uint64_t tyStart = _m705.data.Int.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m705.data.Int.tyLen;
        (void)tyLen;
    checkLitLeaf_c_Comp_value_U64_neg_Bool_offset_U64_isBool_Bool_tyStart_U64_tyLen_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), value, 1, offset, isBool, tyStart, tyLen, eKind, eBits, eSgn);
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), operand, eKind, eBits, eSgn);
    }
    }
    Expr_release(oe);
    }
    else {
    if (op == opBitNot()) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), operand, eKind, eBits, eSgn);
    }
    }
    }
    else if (_m704.tag == 3) {
        int64_t op = _m704.data.Binary.op;
        (void)op;
        uint64_t lhs = _m704.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m704.data.Binary.rhs;
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
    if (litFitsBits_value_U64_neg_Bool_bits_U64_sgn_Bool(cf.value, cf.neg, eBits, eSgn)) {
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
    else if (_m704.tag == 4) {
        uint64_t nameStart = _m704.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m704.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m704.data.Call.args;
        (void)args;
    checkCallArgs_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args));
    }
    else if (_m704.tag == 10) {
        uint64_t recv = _m704.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m704.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m704.data.Method.nameLen;
        (void)nameLen;
        Array_Arg args = _m704.data.Method.args;
        (void)args;
    checkMethodArgs_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), recv, nameStart, nameLen, Array_Arg_share(args));
    }
    else if (_m704.tag == 11) {
        uint64_t operand = _m704.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m704.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m704.data.Cast.tyLen;
        (void)tyLen;
    Expr oe = Expr_share(Array_Expr_get((*c).exprs, (long long)(operand)));
    {
    Expr _m706 = oe;
    if (_m706.tag == 0) {
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), operand, 0, 0, 0);
    }
    }
    Expr_release(oe);
    }
    else if (_m704.tag == 5) {
        uint64_t base = _m704.data.Field.base;
        (void)base;
        uint64_t nameStart = _m704.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m704.data.Field.nameLen;
        (void)nameLen;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), base, 0, 0, 0);
    }
    else if (_m704.tag == 9) {
        uint64_t base = _m704.data.Index.base;
        (void)base;
        uint64_t index = _m704.data.Index.index;
        (void)index;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), base, 0, 0, 0);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), index, 1, 64, 0);
    }
    else if (_m704.tag == 6) {
        uint64_t typeStart = _m704.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m704.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m704.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m704.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m704.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m704.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m704.data.Make.fields;
        (void)fields;
    checkMakeFields_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_ty_U64_fields_AMakeField(&((*c)), typeStart, typeLen, variantStart, variantLen, isEnum, ty, Array_MakeField_share(fields));
    }
    else if (_m704.tag == 8) {
        Array_U64 elems = _m704.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).count)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), Array_U64_get(elems, (long long)(i)), eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m704.tag == 12) {
        uint64_t scrut = _m704.data.MatchExpr.scrut;
        (void)scrut;
        Array_MatchArm arms = _m704.data.MatchExpr.arms;
        (void)arms;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), scrut, 0, 0, 0);
    uint64_t i = 0;
    while (i < (long long)((arms).count)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), Array_MatchArm_get(arms, (long long)(i)).body, eKind, eBits, eSgn);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m704.tag == 14) {
        uint64_t opt = _m704.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m704.data.Coalesce.deflt;
        (void)deflt;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), opt, 0, 0, 0);
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), deflt, eKind, eBits, eSgn);
    }
    else if (_m704.tag == 15) {
        uint64_t expr = _m704.data.Try.expr;
        (void)expr;
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), expr, 0, 0, 0);
    }
    else {
    }
    }
    Expr_release(e);
}
IntTy exprIntTy_c_Comp_id_U64(Comp* c, uint64_t id) {
    TypeInfo ti = exprType_c_Comp_id_U64(&((*c)), id);
    if (tiIsInt_c_Comp_ti_TypeInfo(&((*c)), ti)) {
    { IntTy __ret707 = (IntTy){.known = 1, .bits = intBits_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen), .sgn = intSigned_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen)};
    return __ret707; }
    }
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m708 = e;
    if (_m708.tag == 4) {
        uint64_t nameStart = _m708.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m708.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m708.data.Call.args;
        (void)args;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"argCount", 8})) {
    { IntTy __ret709 = (IntTy){.known = 1, .bits = 64, .sgn = 1};
    Expr_release(e);
    return __ret709; }
    }
    }
    else if (_m708.tag == 5) {
        uint64_t base = _m708.data.Field.base;
        (void)base;
        uint64_t nameStart = _m708.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m708.data.Field.nameLen;
        (void)nameLen;
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"count", 5})) {
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    { IntTy __ret710 = (IntTy){.known = 1, .bits = 64, .sgn = 0};
    Expr_release(e);
    return __ret710; }
    }
    }
    }
    else if (_m708.tag == 9) {
        uint64_t base = _m708.data.Index.base;
        (void)base;
        uint64_t index = _m708.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen)) {
    { IntTy __ret711 = (IntTy){.known = 1, .bits = intBits_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen), .sgn = intSigned_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen)};
    Expr_release(e);
    return __ret711; }
    }
    }
    }
    else {
    }
    }
    { IntTy __ret712 = (IntTy){.known = 0, .bits = 0, .sgn = 0};
    Expr_release(e);
    return __ret712; }
    Expr_release(e);
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
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m713 = e;
    if (_m713.tag == 8) {
        Array_U64 elems = _m713.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).count)) {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), Array_U64_get(elems, (long long)(i)), elemStart, elemLen, 0);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), id, 0, 0, 0);
    }
    }
    Expr_release(e);
}
long long typeIsTransitivelyUnique_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    { long long __ret714 = 1;
    return __ret714; }
    }
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).count)) {
    { long long __ret715 = 0;
    return __ret715; }
    }
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    uint64_t i = 0;
    while (i < (long long)((s.fields).count)) {
    FieldDef f = Array_FieldDef_get(s.fields, (long long)(i));
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), f)) {
    }
    else {
    if (f.tyIsArray) {
    }
    else {
    if (typeIsTransitivelyUnique_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret716 = 1;
    StructDef_release(s);
    return __ret716; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret717 = 0;
    StructDef_release(s);
    return __ret717; }
    StructDef_release(s);
}
void checkFieldContagion_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(i)));
    if (s.isUnique) {
    }
    else {
    uint64_t j = 0;
    while (j < (long long)((s.fields).count)) {
    FieldDef f = Array_FieldDef_get(s.fields, (long long)(j));
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
void checkFieldDefaults_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(i)));
    uint64_t j = 0;
    while (j < (long long)((s.fields).count)) {
    FieldDef f = Array_FieldDef_get(s.fields, (long long)(j));
    if (f.hasDefault) {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), f.defaultVal, f.tyStart, f.tyLen, f.tyIsArray);
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
}
void checkParamModes_c_Comp_params_AParam(Comp* c, Array_Param params) {
    uint64_t i = 0;
    while (i < (long long)((params).count)) {
    Param p = Array_Param_get(params, (long long)(i));
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
    while (i < (long long)(((*c).arrayElems).count)) {
    Bind ae = Array_Bind_get((*c).arrayElems, (long long)(i));
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), ae.nameStart, ae.nameLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), ae.nameStart), (PlewString){"a unique type cannot be stored in an Array; wrap it in Ref[T]", 61});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void checkGenericUniqueArgs_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).types).count)) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(i)));
    if ((long long)((t.args).count) == 0) {
    }
    else {
    if (isRefInst_c_Comp_ref_U64(&((*c)), i)) {
    }
    else {
    uint64_t j = 0;
    while (j < (long long)((t.args).count)) {
    TypeInfo ai = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(j)));
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
    while (i < (long long)(((*c).funcs).count)) {
    checkParamModes_c_Comp_params_AParam(&((*c)), Array_Param_share(Array_Func_get((*c).funcs, (long long)(i)).params));
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
void checkUniqueArgModes_c_Comp_args_AArg(Comp* c, Array_Arg args) {
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, Array_Arg_get(args, (long long)(i)).isInout);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void checkCallArgs_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    checkUniqueArgModes_c_Comp_args_AArg(&((*c)), Array_Arg_share(args));
    uint64_t fi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args));
    if (fi == (long long)(((*c).funcs).count)) {
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, 1, 64, 1);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return;
    }
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    Array_Param ps = Array_Param_share(f.params);
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    if (i < (long long)((ps).count)) {
    Param p = Array_Param_get(ps, (long long)(i));
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, p.tyStart, p.tyLen, p.tyIsArray);
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, 0, 0, 0);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Param_release(ps);
    Func_release(f);
}
void checkMethodArgs_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    checkUniqueArgModes_c_Comp_args_AArg(&((*c)), Array_Arg_share(args));
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), recv, 0, 0, 0);
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (rt.kind == 2) {
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (mi != (long long)(((*c).funcs).count)) {
    Func mf = Func_share(Array_Func_get((*c).funcs, (long long)(mi)));
    Array_Param ps = Array_Param_share(mf.params);
    long long genericRecv = isGenericInst_c_Comp_ref_U64(&((*c)), rt.ref);
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    if (i < (long long)((ps).count)) {
    Param p = Array_Param_get(ps, (long long)(i));
    if (genericRecv) {
    TypeInfo pti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), rt.ref, Array_Bind_share(mf.typeParams), p.ty);
    checkLitTi_c_Comp_id_U64_ti_TypeInfo(&((*c)), Array_Arg_get(args, (long long)(i)).expr, pti);
    }
    else {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, p.tyStart, p.tyLen, p.tyIsArray);
    }
    }
    else {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, 0, 0, 0);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Param_release(ps);
    Func_release(mf);
    return;
    Array_Param_release(ps);
    Func_release(mf);
    }
    }
    if (rt.kind == 3) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"append", 6})) {
    long long innerArr = 0;
    uint64_t innerStart = 0;
    uint64_t innerLen = 0;
    uint64_t er = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), rt.nameStart, rt.nameLen);
    if (er != 0) {
    uint64_t rr = resolveTy_c_Comp_tyRef_U64(&((*c)), er);
    if (rr < (long long)(((*c).types).count)) {
    TypeRef rtp = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(rr)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), rtp.nameStart, rtp.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((rtp.args).count) > 0) {
    Bind xn = arrayElemNameForRef_c_Comp_elemRef_U64(&((*c)), Array_U64_get(rtp.args, (long long)(0)));
    innerArr = 1;
    innerStart = xn.nameStart;
    innerLen = xn.nameLen;
    }
    }
    TypeRef_release(rtp);
    }
    }
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    if (innerArr) {
    checkLitArray_c_Comp_id_U64_elemStart_U64_elemLen_U64(&((*c)), Array_Arg_get(args, (long long)(i)).expr, innerStart, innerLen);
    }
    else {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, rt.nameStart, rt.nameLen, 0);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    return;
    }
    }
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), Array_Arg_get(args, (long long)(i)).expr, 1, 64, 1);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
TypeInfo makeFieldType_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen) {
    if (isEnum) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef en = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), en.nameStart, en.nameLen, typeStart, typeLen)) {
    Array_Variant vars = Array_Variant_share(en.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    uint64_t fj = 0;
    while (fj < (long long)((fs).count)) {
    FieldDef fd = Array_FieldDef_get(fs, (long long)(fj));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    { TypeInfo __ret718 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), fd.tyStart, fd.tyLen, fd.tyIsArray);
    Array_FieldDef_release(fs);
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(en);
    return __ret718; }
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(en);
    }
    { TypeInfo __ret719 = scalarInfo();
    return __ret719; }
    }
    { TypeInfo __ret720 = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, fieldStart, fieldLen);
    return __ret720; }
}
void checkMakeFields_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_ty_U64_fields_AMakeField(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t ty, Array_MakeField fields) {
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    MakeField mf = Array_MakeField_get(fields, (long long)(i));
    checkUniquePlaceCopy_c_Comp_exprId_U64_inoutOk_Bool(&((*c)), mf.value, 0);
    TypeInfo ft = scalarInfo();
    if (isRefInst_c_Comp_ref_U64(&((*c)), ty)) {
    TypeRef rt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ty)));
    ft = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
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
long long paramSelectorEq_c_Comp_a_AParam_b_AParam(Comp* c, Array_Param a, Array_Param b) {
    if ((long long)((a).count) != (long long)((b).count)) {
    { long long __ret721 = 0;
    return __ret721; }
    }
    uint64_t i = 0;
    while (i < (long long)((a).count)) {
    Param pa = Array_Param_get(a, (long long)(i));
    Param pb = Array_Param_get(b, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), pa.nameStart, pa.nameLen, pb.nameStart, pb.nameLen)) {
    }
    else {
    { long long __ret722 = 0;
    return __ret722; }
    }
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), pa.tyStart, pa.tyLen, pb.tyStart, pb.tyLen)) {
    }
    else {
    { long long __ret723 = 0;
    return __ret723; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret724 = 1;
    return __ret724; }
}
Bind assocBindingSpan_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).assocBindings).count)) {
    AssocBinding ab = Array_AssocBinding_get((*c).assocBindings, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ab.recvStart, ab.recvLen, recvStart, recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ab.nameStart, ab.nameLen, nameStart, nameLen)) {
    { Bind __ret725 = (Bind){.nameStart = ab.tyStart, .nameLen = ab.tyLen, .fieldStart = ab.tyStart, .fieldLen = ab.tyLen};
    return __ret725; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Bind __ret726 = (Bind){.nameStart = nameStart, .nameLen = nameLen, .fieldStart = nameStart, .fieldLen = nameLen};
    return __ret726; }
}
long long paramSelectorEqSubst_c_Comp_w_AParam_r_AParam_recvStart_U64_recvLen_U64(Comp* c, Array_Param w, Array_Param r, uint64_t recvStart, uint64_t recvLen) {
    if ((long long)((w).count) != (long long)((r).count)) {
    { long long __ret727 = 0;
    return __ret727; }
    }
    uint64_t i = 0;
    while (i < (long long)((w).count)) {
    Param pw = Array_Param_get(w, (long long)(i));
    Param pr = Array_Param_get(r, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), pw.nameStart, pw.nameLen, pr.nameStart, pr.nameLen)) {
    }
    else {
    { long long __ret728 = 0;
    return __ret728; }
    }
    Bind sub = assocBindingSpan_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(&((*c)), recvStart, recvLen, pr.tyStart, pr.tyLen);
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), pw.tyStart, pw.tyLen, sub.nameStart, sub.nameLen)) {
    }
    else {
    { long long __ret729 = 0;
    return __ret729; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret730 = 1;
    return __ret730; }
}
long long witnessedHas_c_Comp_witnessed_AFunc_r_Func_recvStart_U64_recvLen_U64(Comp* c, Array_Func witnessed, Func r, uint64_t recvStart, uint64_t recvLen) {
    uint64_t i = 0;
    while (i < (long long)((witnessed).count)) {
    Func w = Func_share(Array_Func_get(witnessed, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), w.nameStart, w.nameLen, r.nameStart, r.nameLen)) {
    if (paramSelectorEqSubst_c_Comp_w_AParam_r_AParam_recvStart_U64_recvLen_U64(&((*c)), Array_Param_share(w.params), Array_Param_share(r.params), recvStart, recvLen)) {
    { long long __ret731 = 1;
    Func_release(w);
    return __ret731; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(w);
    }
    { long long __ret732 = 0;
    return __ret732; }
}
void checkConformances_c_Comp(Comp* c) {
    uint64_t ci = 0;
    while (ci < (long long)(((*c).conforms).count)) {
    Conform cf = Conform_share(Array_Conform_get((*c).conforms, (long long)(ci)));
    if (cf.derived) {
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    long long found = 0;
    uint64_t ti = 0;
    while (ti < (long long)(((*c).traits).count)) {
    TraitDef t = TraitDef_share(Array_TraitDef_get((*c).traits, (long long)(ti)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, cf.traitStart, cf.traitLen)) {
    found = 1;
    uint64_t ri = 0;
    while (ri < (long long)((t.reqs).count)) {
    Func r = Func_share(Array_Func_get(t.reqs, (long long)(ri)));
    if (witnessedHas_c_Comp_witnessed_AFunc_r_Func_recvStart_U64_recvLen_U64(&((*c)), Array_Func_share(cf.witnessed), r, cf.typeStart, cf.typeLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), cf.typeStart), (PlewString){"incomplete trait conformance: a requirement is not witnessed (define its body or bind it with `via`)", 100});
    }
    ri = ({ uint64_t __ov; if (__builtin_add_overflow((ri), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(r);
    }
    uint64_t sti = 0;
    while (sti < (long long)((t.supertraits).count)) {
    Bind sup = Array_Bind_get(t.supertraits, (long long)(sti));
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
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, recvStart, recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    { long long __ret733 = 1;
    Func_release(f);
    return __ret733; }
    }
    }
    }
    else {
    if (f.isAssoc) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, recvStart, recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    { long long __ret734 = 1;
    Func_release(f);
    return __ret734; }
    }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { long long __ret735 = 0;
    return __ret735; }
}
void checkViaTargets_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).methodAliases).count)) {
    MethodAlias al = Array_MethodAlias_get((*c).methodAliases, (long long)(i));
    if (typeHasMember_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(&((*c)), al.recvStart, al.recvLen, al.realStart, al.realLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), al.aliasStart), (PlewString){"`via` target is not a member of this type", 41});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long builtinEqOrd_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen) {
    long long isEqOrd = (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), traitStart, traitLen, (PlewString){"Eq", 2}) || rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), traitStart, traitLen, (PlewString){"Ord", 3}));
    if (isEqOrd) {
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen)) {
    { long long __ret736 = 1;
    return __ret736; }
    }
    { long long __ret737 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), typeStart, typeLen, (PlewString){"String", 6});
    return __ret737; }
    }
    { long long __ret738 = 0;
    return __ret738; }
}
long long typeConformsTo_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t traitStart, uint64_t traitLen) {
    if (builtinEqOrd_c_Comp_typeStart_U64_typeLen_U64_traitStart_U64_traitLen_U64(&((*c)), typeStart, typeLen, traitStart, traitLen)) {
    { long long __ret739 = 1;
    return __ret739; }
    }
    uint64_t i = 0;
    while (i < (long long)(((*c).conforms).count)) {
    Conform cf = Conform_share(Array_Conform_get((*c).conforms, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), cf.typeStart, cf.typeLen, typeStart, typeLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), cf.traitStart, cf.traitLen, traitStart, traitLen)) {
    { long long __ret740 = 1;
    Conform_release(cf);
    return __ret740; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Conform_release(cf);
    }
    { long long __ret741 = 0;
    return __ret741; }
}
long long typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(Comp* c, uint64_t typeStart, uint64_t typeLen, PlewString traitName) {
    uint64_t i = 0;
    while (i < (long long)(((*c).conforms).count)) {
    Conform cf = Conform_share(Array_Conform_get((*c).conforms, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), cf.typeStart, cf.typeLen, typeStart, typeLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), cf.traitStart, cf.traitLen, traitName)) {
    { long long __ret742 = 1;
    Conform_release(cf);
    return __ret742; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Conform_release(cf);
    }
    { long long __ret743 = 0;
    return __ret743; }
}
void checkFnBounds_c_Comp(Comp* c) {
    uint64_t ii = 0;
    while (ii < (long long)(((*c).fnInsts).count)) {
    FnInst fin = FnInst_share(Array_FnInst_get((*c).fnInsts, (long long)(ii)));
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fin.fnIdx)));
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).count)) {
    FuncBound fb = Array_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == fin.fnIdx) {
    uint64_t pi = 0;
    while (pi < (long long)((f.typeParams).count)) {
    Bind tp = Array_Bind_get(f.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), tp.nameStart, tp.nameLen, fb.paramStart, fb.paramLen)) {
    if (pi < (long long)((fin.args).count)) {
    TypeRef at = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(Array_U64_get(fin.args, (long long)(pi)))));
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
    while (gi < (long long)(((*c).genInsts).count)) {
    uint64_t instRef = Array_U64_get((*c).genInsts, (long long)(gi));
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t mfi = 0;
    while (mfi < (long long)(((*c).funcs).count)) {
    if (methodMatchesInst_c_Comp_f_Func_instRef_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(mfi)), instRef)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(mfi)));
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).count)) {
    FuncBound fb = Array_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == mfi) {
    uint64_t pi = 0;
    while (pi < (long long)((f.typeParams).count)) {
    Bind tp = Array_Bind_get(f.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), tp.nameStart, tp.nameLen, fb.paramStart, fb.paramLen)) {
    if (pi < (long long)((inst.args).count)) {
    TypeRef at = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(Array_U64_get(inst.args, (long long)(pi)))));
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
    if (fnIdx >= (long long)(((*c).funcs).count)) {
    { long long __ret744 = 0;
    return __ret744; }
    }
    Array_Bind tps = Array_Bind_share(Array_Func_get((*c).funcs, (long long)(fnIdx)).typeParams);
    uint64_t i = 0;
    while (i < (long long)((tps).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_Bind_get(tps, (long long)(i)).nameStart, Array_Bind_get(tps, (long long)(i)).nameLen, start, len)) {
    { long long __ret745 = 1;
    Array_Bind_release(tps);
    return __ret745; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret746 = 0;
    Array_Bind_release(tps);
    return __ret746; }
    Array_Bind_release(tps);
}
long long boundProvidesMethod_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).count)) {
    FuncBound fb = Array_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == fnIdx) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fb.paramStart, fb.paramLen, tpStart, tpLen)) {
    uint64_t ti = 0;
    while (ti < (long long)(((*c).traits).count)) {
    TraitDef t = TraitDef_share(Array_TraitDef_get((*c).traits, (long long)(ti)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, fb.traitStart, fb.traitLen)) {
    uint64_t ri = 0;
    while (ri < (long long)((t.reqs).count)) {
    Func r = Func_share(Array_Func_get(t.reqs, (long long)(ri)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), r.nameStart, r.nameLen, nameStart, nameLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(r.params), Array_Arg_share(args))) {
    { long long __ret747 = 1;
    Func_release(r);
    TraitDef_release(t);
    return __ret747; }
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
    while (gi < (long long)(((*c).funcs).count)) {
    Func g = Func_share(Array_Func_get((*c).funcs, (long long)(gi)));
    if (g.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), g.recvStart, g.recvLen, fb.traitStart, fb.traitLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), g.nameStart, g.nameLen, nameStart, nameLen)) {
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(g.params), Array_Arg_share(args))) {
    { long long __ret748 = 1;
    Func_release(g);
    return __ret748; }
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
    { long long __ret749 = 0;
    return __ret749; }
}
long long boundHasTraitNamed_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_traitName_String(Comp* c, uint64_t fnIdx, uint64_t tpStart, uint64_t tpLen, PlewString traitName) {
    uint64_t bi = 0;
    while (bi < (long long)(((*c).funcBounds).count)) {
    FuncBound fb = Array_FuncBound_get((*c).funcBounds, (long long)(bi));
    if (fb.fnIdx == fnIdx) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fb.paramStart, fb.paramLen, tpStart, tpLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), fb.traitStart, fb.traitLen, traitName)) {
    { long long __ret750 = 1;
    return __ret750; }
    }
    }
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret751 = 0;
    return __ret751; }
}
void checkBoundsExpr_c_Comp_exprId_U64(Comp* c, uint64_t exprId) {
    {
    Expr _m752 = Array_Expr_get((*c).exprs, (long long)(exprId));
    if (_m752.tag == 2) {
        int64_t op = _m752.data.Unary.op;
        (void)op;
        uint64_t operand = _m752.data.Unary.operand;
        (void)operand;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m752.tag == 3) {
        int64_t op = _m752.data.Binary.op;
        (void)op;
        uint64_t lhs = _m752.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m752.data.Binary.rhs;
        (void)rhs;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), lhs);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), rhs);
    if (op >= 50) {
    if (op <= 55) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 2) {
    if (isTypeParamOf_c_Comp_fnIdx_U64_start_U64_len_U64(&((*c)), (*c).curCheckFn, lt.nameStart, lt.nameLen)) {
    PlewString need = (PlewString){"Ord", 3};
    if (op == opEq()) {
    need = (PlewString){"Eq", 2};
    }
    if (op == opNe()) {
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
    else if (_m752.tag == 4) {
        uint64_t nameStart = _m752.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m752.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m752.data.Call.args;
        (void)args;
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), Array_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m752.tag == 10) {
        uint64_t recv = _m752.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m752.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m752.data.Method.nameLen;
        (void)nameLen;
        Array_Arg args = _m752.data.Method.args;
        (void)args;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), recv);
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), Array_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (rt.kind == 2) {
    if (isTypeParamOf_c_Comp_fnIdx_U64_start_U64_len_U64(&((*c)), (*c).curCheckFn, rt.nameStart, rt.nameLen)) {
    if (boundProvidesMethod_c_Comp_fnIdx_U64_tpStart_U64_tpLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), (*c).curCheckFn, rt.nameStart, rt.nameLen, nameStart, nameLen, Array_Arg_share(args))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"method not provided by the bounds of this type parameter (add a `where T: Trait` that declares it)", 98});
    }
    }
    }
    }
    else if (_m752.tag == 5) {
        uint64_t base = _m752.data.Field.base;
        (void)base;
        uint64_t nameStart = _m752.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m752.data.Field.nameLen;
        (void)nameLen;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m752.tag == 9) {
        uint64_t base = _m752.data.Index.base;
        (void)base;
        uint64_t index = _m752.data.Index.index;
        (void)index;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), base);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), index);
    }
    else if (_m752.tag == 6) {
        uint64_t typeStart = _m752.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m752.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m752.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m752.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m752.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m752.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m752.data.Make.fields;
        (void)fields;
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), Array_MakeField_get(fields, (long long)(i)).value);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m752.tag == 8) {
        Array_U64 elems = _m752.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).count)) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), Array_U64_get(elems, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m752.tag == 11) {
        uint64_t operand = _m752.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m752.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m752.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m752.data.Cast.ty;
        (void)ty;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m752.tag == 14) {
        uint64_t opt = _m752.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m752.data.Coalesce.deflt;
        (void)deflt;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), opt);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), deflt);
    }
    else if (_m752.tag == 15) {
        uint64_t expr = _m752.data.Try.expr;
        (void)expr;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m752.tag == 16) {
        uint64_t base = _m752.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m752.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m752.data.Arrow.nameLen;
        (void)nameLen;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m752.tag == 13) {
        uint64_t cond = _m752.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m752.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m752.data.IfExpr.elseBlk;
        (void)elseBlk;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), cond);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), thenBlk);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    else if (_m752.tag == 12) {
        uint64_t scrut = _m752.data.MatchExpr.scrut;
        (void)scrut;
        Array_MatchArm arms = _m752.data.MatchExpr.arms;
        (void)arms;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm_scrutTi_TypeInfo(&((*c)), a, exprType_c_Comp_id_U64(&((*c)), scrut));
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m752.tag == 18) {
        uint64_t operand = _m752.data.Move.operand;
        (void)operand;
        long long isBorrow = _m752.data.Move.isBorrow;
        (void)isBorrow;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), operand);
    }
    else {
    }
    }
}
void checkBoundsStmt_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId) {
    {
    Stmt _m753 = Array_Stmt_get((*c).stmts, (long long)(stmtId));
    if (_m753.tag == 0) {
        long long mutable = _m753.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m753.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m753.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m753.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m753.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m753.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m753.data.Let.ty;
        (void)ty;
        uint64_t init = _m753.data.Let.init;
        (void)init;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), init);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), nameStart, nameLen, tyStart, tyLen, tyIsArray, ty, 0, mutable, 1);
    }
    else if (_m753.tag == 1) {
        int64_t op = _m753.data.Assign.op;
        (void)op;
        uint64_t target = _m753.data.Assign.target;
        (void)target;
        uint64_t value = _m753.data.Assign.value;
        (void)value;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), target);
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m753.tag == 2) {
        uint64_t expr = _m753.data.ExprStmt.expr;
        (void)expr;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m753.tag == 3) {
        uint64_t value = _m753.data.Return.value;
        (void)value;
        long long hasValue = _m753.data.Return.hasValue;
        (void)hasValue;
    if (hasValue) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), value);
    }
    }
    else if (_m753.tag == 4) {
        uint64_t cond = _m753.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m753.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m753.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m753.data.If.hasElse;
        (void)hasElse;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), cond);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), thenBlk);
    if (hasElse) {
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    }
    else if (_m753.tag == 5) {
        uint64_t cond = _m753.data.While.cond;
        (void)cond;
        uint64_t body = _m753.data.While.body;
        (void)body;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), cond);
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), body);
    }
    else if (_m753.tag == 6) {
        uint64_t varStart = _m753.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m753.data.For.varLen;
        (void)varLen;
        long long isRange = _m753.data.For.isRange;
        (void)isRange;
        long long inclusive = _m753.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m753.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m753.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m753.data.For.body;
        (void)body;
        long long isStruct = _m753.data.For.isStruct;
        (void)isStruct;
        uint64_t patStart = _m753.data.For.patStart;
        (void)patStart;
        uint64_t patLen = _m753.data.For.patLen;
        (void)patLen;
        Array_Bind binds = _m753.data.For.binds;
        (void)binds;
    uint64_t forMark = scopeMark_c_Comp(&((*c)));
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), iter);
    if (isRange) {
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), rangeHi);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, 0, 0, 0, 0, 0, 0, 0);
    }
    else {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), iter);
    if (isStruct) {
    addForStructBinds_c_Comp_et_TypeInfo_binds_ABind(&((*c)), et, Array_Bind_share(binds));
    }
    else {
    if (et.kind == 3) {
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0, 0, 0, 0);
    }
    else {
    TypeInfo elemTi = iterableItemInfo_c_Comp_et_TypeInfo(&((*c)), et);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, elemTi.nameStart, elemTi.nameLen, (elemTi.kind == 3), elemTi.ref, 0, 0, 0);
    }
    }
    }
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), body);
    popLocals_c_Comp_mark_U64(&((*c)), forMark);
    }
    else if (_m753.tag == 7) {
        uint64_t scrut = _m753.data.Match.scrut;
        (void)scrut;
        Array_MatchArm arms = _m753.data.Match.arms;
        (void)arms;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm_scrutTi_TypeInfo(&((*c)), a, exprType_c_Comp_id_U64(&((*c)), scrut));
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m753.tag == 8) {
        uint64_t msg = _m753.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m753.data.Panic.offset;
        (void)offset;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), msg);
    }
    else if (_m753.tag == 9) {
        uint64_t value = _m753.data.Give.value;
        (void)value;
    checkBoundsExpr_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m753.tag == 10) {
    }
    else if (_m753.tag == 11) {
    }
    else { __builtin_unreachable(); }
    }
}
void checkBoundsBlock_c_Comp_blkId_U64(Comp* c, uint64_t blkId) {
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    Array_U64 stmts = Array_U64_share(Array_Block_get((*c).blocks, (long long)(blkId)).stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).count)) {
    checkBoundsStmt_c_Comp_stmtId_U64(&((*c)), Array_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    Array_U64_release(stmts);
}
void checkGenericBodies_c_Comp(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    if ((long long)((f.typeParams).count) > 0) {
    Array_Bind noParams = Array_Bind_new();
    Array_U64 noArgs = Array_U64_new();
    (*c).locals = Array_Local_new();
    (*c).curHasRecv = f.hasRecv;
    (*c).curRecvStart = f.recvStart;
    (*c).curRecvLen = f.recvLen;
    (*c).curSelfInout = f.selfInout;
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = Array_Bind_share(noParams);
    (*c).curTypeArgs = Array_U64_share(noArgs);
    (*c).curCheckFn = fi;
    uint64_t pi = 0;
    while (pi < (long long)((f.params).count)) {
    Param p = Array_Param_get(f.params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    checkBoundsBlock_c_Comp_blkId_U64(&((*c)), f.body);
    Array_U64_release(noArgs);
    Array_Bind_release(noParams);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    (*c).locals = Array_Local_new();
    (*c).curHasRecv = 0;
    (*c).curCheckFn = (long long)(((*c).funcs).count);
}
long long sameLabels_c_Comp_a_AParam_b_AParam(Comp* c, Array_Param a, Array_Param b) {
    if ((long long)((a).count) != (long long)((b).count)) {
    { long long __ret754 = 0;
    return __ret754; }
    }
    uint64_t i = 0;
    while (i < (long long)((a).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_Param_get(a, (long long)(i)).nameStart, Array_Param_get(a, (long long)(i)).nameLen, Array_Param_get(b, (long long)(i)).nameStart, Array_Param_get(b, (long long)(i)).nameLen)) {
    }
    else {
    { long long __ret755 = 0;
    return __ret755; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret756 = 1;
    return __ret756; }
}
void checkOverloadCollisions_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func fi = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (fi.hasRecv) {
    }
    else {
    if (fi.isAssoc) {
    }
    else {
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < (long long)(((*c).funcs).count)) {
    Func fj = Func_share(Array_Func_get((*c).funcs, (long long)(j)));
    if (fj.hasRecv) {
    }
    else {
    if (fj.isAssoc) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fi.nameStart, fi.nameLen, fj.nameStart, fj.nameLen)) {
    if (sameLabels_c_Comp_a_AParam_b_AParam(&((*c)), Array_Param_share(fi.params), Array_Param_share(fj.params))) {
    if ((long long)((fi.typeParams).count) > 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), fj.nameStart), (PlewString){"a generic function shares its selector (name + labels) with another overload; spec forbids generic/concrete overload on the same selector", 137});
    }
    else {
    if ((long long)((fj.typeParams).count) > 0) {
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
long long methodWitnessesAConformance_c_Comp_recvStart_U64_recvLen_U64_mStart_U64_mLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t mStart, uint64_t mLen) {
    uint64_t ci = 0;
    while (ci < (long long)(((*c).conforms).count)) {
    Conform cf = Conform_share(Array_Conform_get((*c).conforms, (long long)(ci)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), cf.typeStart, cf.typeLen, recvStart, recvLen)) {
    uint64_t ti = 0;
    while (ti < (long long)(((*c).traits).count)) {
    TraitDef tr = TraitDef_share(Array_TraitDef_get((*c).traits, (long long)(ti)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), tr.nameStart, tr.nameLen, cf.traitStart, cf.traitLen)) {
    uint64_t ri = 0;
    while (ri < (long long)((tr.reqs).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_Func_get(tr.reqs, (long long)(ri)).nameStart, Array_Func_get(tr.reqs, (long long)(ri)).nameLen, mStart, mLen)) {
    { long long __ret757 = 1;
    TraitDef_release(tr);
    Conform_release(cf);
    return __ret757; }
    }
    ri = ({ uint64_t __ov; if (__builtin_add_overflow((ri), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ti = ({ uint64_t __ov; if (__builtin_add_overflow((ti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TraitDef_release(tr);
    }
    }
    ci = ({ uint64_t __ov; if (__builtin_add_overflow((ci), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Conform_release(cf);
    }
    { long long __ret758 = 0;
    return __ret758; }
}
void checkImplOnBuiltin_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    long long onBuiltin = 0;
    if (f.hasRecv) {
    onBuiltin = isPrimType_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen);
    }
    else {
    if (f.isAssoc) {
    onBuiltin = isPrimType_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen);
    }
    }
    if (onBuiltin) {
    if (methodWitnessesAConformance_c_Comp_recvStart_U64_recvLen_U64_mStart_U64_mLen_U64(&((*c)), f.recvStart, f.recvLen, f.nameStart, f.nameLen)) {
    onBuiltin = 0;
    }
    }
    if (onBuiltin) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), f.nameStart), (PlewString){"cannot define methods on a built-in type you do not own (use a trait conformance via core, or an extension `#Ext`)", 114});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
}
void checkMoveFnReceivers_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
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
long long isExportedName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).exports).count)) {
    Bind e = Array_Bind_get((*c).exports, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, nameStart, nameLen)) {
    { long long __ret759 = 1;
    return __ret759; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret760 = 0;
    return __ret760; }
}
void checkImports_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).imports).count)) {
    Bind im = Array_Bind_get((*c).imports, (long long)(i));
    if (isExportedName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), im.nameStart, im.nameLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), im.nameStart), (PlewString){"imported name is not exported (mark it `export` in its module, or import it from the right module)", 98});
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long isImportedInto_c_Comp_mod_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t mod, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).imports).count)) {
    Bind im = Array_Bind_get((*c).imports, (long long)(i));
    if (im.fieldStart == mod) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), im.nameStart, im.nameLen, nameStart, nameLen)) {
    { long long __ret761 = 1;
    return __ret761; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret762 = 0;
    return __ret762; }
}
void checkUseVisibility_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).exprs).count)) {
    {
    Expr _m763 = Array_Expr_get((*c).exprs, (long long)(i));
    if (_m763.tag == 4) {
        uint64_t nameStart = _m763.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m763.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m763.data.Call.args;
        (void)args;
    uint64_t fi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args));
    if (fi < (long long)(((*c).funcs).count)) {
    uint64_t useMod = moduleOf_c_Comp_offset_U64(&((*c)), nameStart);
    uint64_t defMod = moduleOf_c_Comp_offset_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(fi)).nameStart);
    if (useMod == defMod) {
    }
    else {
    if (isImportedInto_c_Comp_mod_U64_nameStart_U64_nameLen_U64(&((*c)), useMod, nameStart, nameLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"use of a function from another module without importing it (add `import … with { … }`)", 90});
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
}
void emitClosureCall_c_Comp_tyRef_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t tyRef, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(tyRef)));
    plew_write((PlewString){"((", 2});
    if ((long long)((t.args).count) > 0) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(0)));
    }
    else {
    plew_write((PlewString){"void", 4});
    }
    plew_write((PlewString){" (*)(void*", 10});
    uint64_t pi = 1;
    while (pi < (long long)((t.args).count)) {
    plew_write((PlewString){", ", 2});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(pi)));
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"))(", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){").fn)((", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){").env", 5});
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    plew_write((PlewString){", ", 2});
    Arg ar = Array_Arg_get(args, (long long)(i));
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
void emitClosureFieldCall_c_Comp_tyRef_U64_recv_U64_fieldStart_U64_fieldLen_U64_args_AArg(Comp* c, uint64_t tyRef, uint64_t recv, uint64_t fieldStart, uint64_t fieldLen, Array_Arg args) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(tyRef)));
    uint64_t tmp = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    plew_write((PlewString){"({ PlewClosure __cl", 19});
    writeU64_n_U64(tmp);
    plew_write((PlewString){" = (", 4});
    genExpr_c_Comp_id_U64(&((*c)), recv);
    plew_write((PlewString){").", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), fieldStart, fieldLen);
    plew_write((PlewString){"; ((", 4});
    if ((long long)((t.args).count) > 0) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(0)));
    }
    else {
    plew_write((PlewString){"void", 4});
    }
    plew_write((PlewString){" (*)(void*", 10});
    uint64_t pi = 1;
    while (pi < (long long)((t.args).count)) {
    plew_write((PlewString){", ", 2});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(pi)));
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"))(__cl", 7});
    writeU64_n_U64(tmp);
    plew_write((PlewString){".fn))(__cl", 10});
    writeU64_n_U64(tmp);
    plew_write((PlewString){".env", 4});
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    plew_write((PlewString){", ", 2});
    Arg ar = Array_Arg_get(args, (long long)(i));
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
    plew_write((PlewString){"); })", 5});
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
    plew_write((PlewString){"Array_", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){")", 1});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), e.tyStart, e.tyLen, (PlewString){"Ref", 3})) {
    plew_write((PlewString){"plew_ref_share(", 15});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){")", 1});
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), e.tyStart, e.tyLen, (PlewString){"String", 6})) {
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
void genArrayUserMethod_c_Comp_recv_U64_elemStart_U64_elemLen_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t elemStart, uint64_t elemLen, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    Bind arrName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Array", 5}, 5);
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), arrName.nameStart, arrName.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (mi == (long long)(((*c).funcs).count)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"no such method on this array type", 33});
    return;
    }
    Func mf = Func_share(Array_Func_get((*c).funcs, (long long)(mi)));
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(mf.params), Array_Arg_share(args))) {
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
    }
    plew_write((PlewString){"Array_", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), mf);
    if (mf.selfInout) {
    plew_write((PlewString){"(&(", 3});
    }
    else {
    plew_write((PlewString){"((", 2});
    }
    genExpr_c_Comp_id_U64(&((*c)), recv);
    plew_write((PlewString){")", 1});
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    plew_write((PlewString){", ", 2});
    if (argIsElementTyped_c_Comp_mf_Func_i_U64(&((*c)), mf, i)) {
    emitArrayElemValue_c_Comp_argExpr_U64_arrStart_U64_arrLen_U64(&((*c)), Array_Arg_get(args, (long long)(i)).expr, elemStart, elemLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(i)).expr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){")", 1});
    Func_release(mf);
}
long long argIsElementTyped_c_Comp_mf_Func_i_U64(Comp* c, Func mf, uint64_t i) {
    if (i >= (long long)((mf.params).count)) {
    { long long __ret764 = 0;
    return __ret764; }
    }
    if ((long long)((mf.typeParams).count) == 0) {
    { long long __ret765 = 0;
    return __ret765; }
    }
    Param p = Array_Param_get(mf.params, (long long)(i));
    if (p.tyIsArray) {
    { long long __ret766 = 0;
    return __ret766; }
    }
    { long long __ret767 = spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.tyStart, p.tyLen, Array_Bind_get(mf.typeParams, (long long)(0)).nameStart, Array_Bind_get(mf.typeParams, (long long)(0)).nameLen);
    return __ret767; }
}
long long makeProvides_c_Comp_fields_AMakeField_nameStart_U64_nameLen_U64(Comp* c, Array_MakeField fields, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    MakeField mf = Array_MakeField_get(fields, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), mf.nameStart, mf.nameLen, nameStart, nameLen)) {
    { long long __ret768 = 1;
    return __ret768; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret769 = 0;
    return __ret769; }
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
    Array_Bind binds = Array_Bind_share(arm.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).count)) {
    Bind bd = Array_Bind_get(binds, (long long)(bi));
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
    Array_Bind_release(binds);
}
void genExpr_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m770 = e;
    if (_m770.tag == 0) {
        uint64_t value = _m770.data.Int.value;
        (void)value;
    writeIntLit_n_U64(value);
    }
    else if (_m770.tag == 1) {
        uint64_t start = _m770.data.Ident.start;
        (void)start;
        uint64_t len = _m770.data.Ident.len;
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
    Expr_release(e);
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
    if (lvi < (long long)(((*c).locals).count)) {
    if (isBoxedLocalAt_c_Comp_nameStart_U64(&((*c)), Array_Local_get((*c).locals, (long long)(lvi)).nameStart)) {
    plew_write((PlewString){"(*", 2});
    writeLocalCName_c_Comp_lo_Local(&((*c)), Array_Local_get((*c).locals, (long long)(lvi)));
    plew_write((PlewString){")", 1});
    }
    else {
    writeLocalCName_c_Comp_lo_Local(&((*c)), Array_Local_get((*c).locals, (long long)(lvi)));
    }
    }
    else {
    uint64_t fvi = firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), start, len);
    if (fvi < (long long)(((*c).funcs).count)) {
    plew_write((PlewString){"(PlewClosure){(void*)&", 22});
    writeFnSelector_c_Comp_f_Func(&((*c)), Array_Func_get((*c).funcs, (long long)(fvi)));
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
    else if (_m770.tag == 18) {
        uint64_t operand = _m770.data.Move.operand;
        (void)operand;
        long long isBorrow = _m770.data.Move.isBorrow;
        (void)isBorrow;
    if (isBorrow) {
    genExpr_c_Comp_id_U64(&((*c)), operand);
    }
    else {
    {
    Expr _m771 = Array_Expr_get((*c).exprs, (long long)(operand));
    if (_m771.tag == 1) {
        uint64_t start = _m771.data.Ident.start;
        (void)start;
        uint64_t len = _m771.data.Ident.len;
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
    else if (_m770.tag == 2) {
        int64_t op = _m770.data.Unary.op;
        (void)op;
        uint64_t operand = _m770.data.Unary.operand;
        (void)operand;
    long long negChecked = 0;
    if (op == opSub()) {
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
    else if (_m770.tag == 3) {
        int64_t op = _m770.data.Binary.op;
        (void)op;
        uint64_t lhs = _m770.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m770.data.Binary.rhs;
        (void)rhs;
    if (isStringEq_c_Comp_op_I64_lhs_U64(&((*c)), op, lhs)) {
    if (op == opNe()) {
    plew_write((PlewString){"(!PlewString_eq(", 16});
    }
    else {
    plew_write((PlewString){"PlewString_eq(", 14});
    }
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    if (op == opNe()) {
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
    if (op == opDiv()) {
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
    if (op == opRem()) {
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
    else if (_m770.tag == 4) {
        uint64_t nameStart = _m770.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m770.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m770.data.Call.args;
        (void)args;
    if (callLabelsOk_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"argument labels do not match the function parameters", 52});
    Expr_release(e);
    return;
    }
    uint64_t lvi = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    if (lvi < (long long)(((*c).locals).count)) {
    if (isFnType_c_Comp_ref_U64(&((*c)), Array_Local_get((*c).locals, (long long)(lvi)).ty)) {
    emitClosureCall_c_Comp_tyRef_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), Array_Local_get((*c).locals, (long long)(lvi)).ty, nameStart, nameLen, Array_Arg_share(args));
    Expr_release(e);
    return;
    }
    }
    uint64_t cfi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args));
    if (cfi == (long long)(((*c).funcs).count)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"unknown function (a typo, or a builtin used without its `import @Std/…`)", 74});
    }
    else {
    if (Array_Func_get((*c).funcs, (long long)(cfi)).isExtern) {
    if (emitArrayIntrinsic_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args))) {
    Expr_release(e);
    return;
    }
    if (emitRawIntrinsic_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args))) {
    Expr_release(e);
    return;
    }
    plew_write((PlewString){"plew_", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(cfi)).nameStart, Array_Func_get((*c).funcs, (long long)(cfi)).nameLen);
    }
    else {
    if (isGenericFreeFn_c_Comp_fi_U64(&((*c)), cfi)) {
    Array_U64 inferred = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), Array_Func_get((*c).funcs, (long long)(cfi)), Array_Arg_share(args));
    if (fnInstExists_c_Comp_fnIdx_U64_args_AU64(&((*c)), cfi, Array_U64_share(inferred))) {
    Array_Bind savedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedA = Array_U64_share((*c).curTypeArgs);
    (*c).curTypeParams = Array_Bind_share(Array_Func_get((*c).funcs, (long long)(cfi)).typeParams);
    (*c).curTypeArgs = Array_U64_share(inferred);
    writeFnSelector_c_Comp_f_Func(&((*c)), Array_Func_get((*c).funcs, (long long)(cfi)));
    (*c).curTypeParams = Array_Bind_share(savedP);
    (*c).curTypeArgs = Array_U64_share(savedA);
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    }
    else {
    writeFnSelector_c_Comp_f_Func(&((*c)), Array_Func_get((*c).funcs, (long long)(cfi)));
    }
    Array_U64_release(inferred);
    }
    else {
    writeFnSelector_c_Comp_f_Func(&((*c)), Array_Func_get((*c).funcs, (long long)(cfi)));
    }
    }
    }
    plew_write((PlewString){"(", 1});
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    Arg ar = Array_Arg_get(args, (long long)(i));
    if (ar.isInout) {
    plew_write((PlewString){"&(", 2});
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    plew_write((PlewString){")", 1});
    }
    else {
    long long argIsArr = 0;
    if (cfi < (long long)(((*c).funcs).count)) {
    Func cf0 = Func_share(Array_Func_get((*c).funcs, (long long)(cfi)));
    if (i < (long long)((cf0.params).count)) {
    if (Array_Param_get(cf0.params, (long long)(i)).tyIsArray) {
    argIsArr = 1;
    }
    }
    Func_release(cf0);
    }
    if (argIsArr) {
    Func cf1 = Func_share(Array_Func_get((*c).funcs, (long long)(cfi)));
    uint64_t es = Array_Param_get(cf1.params, (long long)(i)).tyStart;
    uint64_t el = Array_Param_get(cf1.params, (long long)(i)).tyLen;
    uint64_t aref = argArrayElemRef_c_Comp_argExpr_U64(&((*c)), ar.expr);
    if (aref != 0) {
    if (isCompoundType_c_Comp_ref_U64(&((*c)), aref)) {
    Bind mn = appendMangleSpan_c_Comp_ref_U64(&((*c)), aref);
    es = mn.nameStart;
    el = mn.nameLen;
    }
    else {
    TypeRef at3 = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(aref)));
    es = at3.nameStart;
    el = at3.nameLen;
    TypeRef_release(at3);
    }
    }
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), ar.expr, es, el);
    Func_release(cf1);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), ar.expr);
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (cfi == (long long)(((*c).funcs).count)) {
    }
    else {
    Func cf = Func_share(Array_Func_get((*c).funcs, (long long)(cfi)));
    Array_Param cps = Array_Param_share(cf.params);
    uint64_t di = (long long)((args).count);
    while (di < (long long)((cps).count)) {
    if (di > 0) {
    plew_write((PlewString){", ", 2});
    }
    if (Array_Param_get(cps, (long long)(di)).tyIsArray) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), Array_Param_get(cps, (long long)(di)).defaultExpr, Array_Param_get(cps, (long long)(di)).tyStart, Array_Param_get(cps, (long long)(di)).tyLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), Array_Param_get(cps, (long long)(di)).defaultExpr);
    }
    di = ({ uint64_t __ov; if (__builtin_add_overflow((di), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Param_release(cps);
    Func_release(cf);
    }
    plew_write((PlewString){")", 1});
    }
    else if (_m770.tag == 5) {
        uint64_t base = _m770.data.Field.base;
        (void)base;
        uint64_t nameStart = _m770.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m770.data.Field.nameLen;
        (void)nameLen;
    {
    Expr _m772 = Array_Expr_get((*c).exprs, (long long)(base));
    if (_m772.tag == 1) {
        uint64_t bs = _m772.data.Ident.start;
        (void)bs;
        uint64_t bl = _m772.data.Ident.len;
        (void)bl;
    if (localIndexByName_c_Comp_start_U64_len_U64(&((*c)), bs, bl) < (long long)(((*c).locals).count)) {
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
    if (bt.kind == 2) {
    checkFieldReadVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen, nameStart);
    }
    else {
    if (bt.kind == 3) {
    Bind arrName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Array", 5}, 5);
    checkFieldReadVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(&((*c)), arrName.nameStart, arrName.nameLen, nameStart, nameLen, nameStart);
    }
    }
    if (bt.kind == 1) {
    plew_write((PlewString){"({ PlewString __s = ", 20});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){"; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; })", 214});
    Expr_release(e);
    return;
    }
    if (bt.kind == 3) {
    plew_write((PlewString){"(long long)((", 13});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){").count)", 8});
    Expr_release(e);
    return;
    }
    long long rdBoxed = 0;
    if (bt.kind == 2) {
    FieldDef rfd = findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, 0, 0, 0, nameStart, nameLen);
    if (rfd.nameLen > 0) {
    rdBoxed = fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), rfd);
    }
    }
    if (rdBoxed) {
    plew_write((PlewString){"(*(", 3});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){"))", 2});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    }
    }
    else if (_m770.tag == 7) {
        uint64_t start = _m770.data.Str.start;
        (void)start;
        uint64_t len = _m770.data.Str.len;
        (void)len;
    plew_write((PlewString){"(PlewString){\"", 14});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), ({ uint64_t __ov; if (__builtin_add_overflow((start), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), ({ uint64_t __ov; if (__builtin_sub_overflow((len), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }));
    plew_write((PlewString){"\", ", 3});
    writeInt_n_I64(strDecodedLen_c_Comp_start_U64_len_U64(&((*c)), start, len));
    plew_write((PlewString){"}", 1});
    }
    else if (_m770.tag == 9) {
        uint64_t base = _m770.data.Index.base;
        (void)base;
        uint64_t index = _m770.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_get(", 5});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){", (long long)(", 14});
    genExpr_c_Comp_id_U64(&((*c)), index);
    plew_write((PlewString){"))", 2});
    }
    else if (_m770.tag == 16) {
        uint64_t base = _m770.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m770.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m770.data.Arrow.nameLen;
        (void)nameLen;
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){")->", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    }
    else if (_m770.tag == 17) {
        Array_Param params = _m770.data.Closure.params;
        (void)params;
        long long hasRet = _m770.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m770.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m770.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m770.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m770.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m770.data.Closure.body;
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
    while (ci < (long long)(((*c).captures).count)) {
    CaptureEntry e_s1 = Array_CaptureEntry_get((*c).captures, (long long)(ci));
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
    else if (_m770.tag == 10) {
        uint64_t recv = _m770.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m770.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m770.data.Method.nameLen;
        (void)nameLen;
        Array_Arg args = _m770.data.Method.args;
        (void)args;
    Bind arn = assocRecvName_c_Comp_recv_U64(&((*c)), recv);
    if (arn.nameLen != 0) {
    uint64_t afi = findAssoc_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), arn.nameStart, arn.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (afi == (long long)(((*c).funcs).count)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"no such associated function on this type", 40});
    Expr_release(e);
    return;
    }
    Func af = Func_share(Array_Func_get((*c).funcs, (long long)(afi)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), arn.nameStart, arn.nameLen);
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), af);
    plew_write((PlewString){"(", 1});
    uint64_t ai = 0;
    while (ai < (long long)((args).count)) {
    if (ai > 0) {
    plew_write((PlewString){", ", 2});
    }
    Arg aa = Array_Arg_get(args, (long long)(ai));
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
    uint64_t adi = (long long)((args).count);
    while (adi < (long long)((af.params).count)) {
    if (adi > 0) {
    plew_write((PlewString){", ", 2});
    }
    if (Array_Param_get(af.params, (long long)(adi)).tyIsArray) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), Array_Param_get(af.params, (long long)(adi)).defaultExpr, Array_Param_get(af.params, (long long)(adi)).tyStart, Array_Param_get(af.params, (long long)(adi)).tyLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), Array_Param_get(af.params, (long long)(adi)).defaultExpr);
    }
    adi = ({ uint64_t __ov; if (__builtin_add_overflow((adi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){")", 1});
    Func_release(af);
    Expr_release(e);
    return;
    Func_release(af);
    }
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (bt.kind == 1) {
    Bind ss = stringTypeSpan_c_Comp(&((*c)));
    if (ss.nameLen != 0) {
    bt = (TypeInfo){.kind = 2, .nameStart = ss.nameStart, .nameLen = ss.nameLen, .ref = 0};
    }
    }
    if (bt.kind == 3) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"append", 6})) {
    Bind arrName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Array", 5}, 5);
    uint64_t ami = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), arrName.nameStart, arrName.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (ami != (long long)(((*c).funcs).count)) {
    genArrayUserMethod_c_Comp_recv_U64_elemStart_U64_elemLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), recv, bt.nameStart, bt.nameLen, nameStart, nameLen, Array_Arg_share(args));
    Expr_release(e);
    return;
    }
    }
    else {
    genArrayUserMethod_c_Comp_recv_U64_elemStart_U64_elemLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), recv, bt.nameStart, bt.nameLen, nameStart, nameLen, Array_Arg_share(args));
    Expr_release(e);
    return;
    }
    if (placeIsMutable_c_Comp_id_U64(&((*c)), recv)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot mutate an immutable binding; declare it with `mut val`", 61});
    Expr_release(e);
    return;
    }
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_push(&(", 8});
    genExpr_c_Comp_id_U64(&((*c)), recv);
    plew_write((PlewString){"), ", 3});
    long long elemIsArr = 0;
    uint64_t ixStart = 0;
    uint64_t ixLen = 0;
    uint64_t aer = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    if (aer != 0) {
    uint64_t arr2 = resolveTy_c_Comp_tyRef_U64(&((*c)), aer);
    if (arr2 < (long long)(((*c).types).count)) {
    TypeRef atp = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(arr2)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), atp.nameStart, atp.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((atp.args).count) > 0) {
    Bind xn2 = arrayElemNameForRef_c_Comp_elemRef_U64(&((*c)), Array_U64_get(atp.args, (long long)(0)));
    elemIsArr = 1;
    ixStart = xn2.nameStart;
    ixLen = xn2.nameLen;
    }
    }
    TypeRef_release(atp);
    }
    }
    if (elemIsArr) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr, ixStart, ixLen);
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    }
    plew_write((PlewString){")", 1});
    }
    else {
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (mi == (long long)(((*c).funcs).count)) {
    TypeInfo fti = scalarInfo();
    if (isGenericInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    fti = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.ref, nameStart, nameLen);
    }
    else {
    fti = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    }
    if (isFnType_c_Comp_ref_U64(&((*c)), fti.ref)) {
    emitClosureFieldCall_c_Comp_tyRef_U64_recv_U64_fieldStart_U64_fieldLen_U64_args_AArg(&((*c)), fti.ref, recv, nameStart, nameLen, Array_Arg_share(args));
    Expr_release(e);
    return;
    }
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"no such method on this type", 27});
    Expr_release(e);
    return;
    }
    Func mf = Func_share(Array_Func_get((*c).funcs, (long long)(mi)));
    checkMethodVis_c_Comp_ownerStart_U64_ownerLen_U64_mf_Func_offset_U64(&((*c)), bt.nameStart, bt.nameLen, mf, nameStart);
    if (paramsLabelsOk_c_Comp_params_AParam_args_AArg(&((*c)), Array_Param_share(mf.params), Array_Arg_share(args))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), nameStart), (PlewString){"argument labels do not match the method parameters", 50});
    Func_release(mf);
    Expr_release(e);
    return;
    }
    if (mf.selfInout) {
    if (placeIsMutable_c_Comp_id_U64(&((*c)), recv)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call an `inout fn` method on an immutable binding; declare it with `mut val`", 83});
    Func_release(mf);
    Expr_release(e);
    return;
    }
    {
    Expr _m773 = Array_Expr_get((*c).exprs, (long long)(recv));
    if (_m773.tag == 9) {
        uint64_t abase = _m773.data.Index.base;
        (void)abase;
        uint64_t aidx = _m773.data.Index.index;
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
    while (gi < (long long)((args).count)) {
    plew_write((PlewString){", ", 2});
    Arg ga = Array_Arg_get(args, (long long)(gi));
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
    plew_write((PlewString){"); Array_", 9});
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
    Expr_release(e);
    return;
    }
    }
    else {
    }
    }
    }
    if (mf.selfMove) {
    {
    Expr _m774 = Array_Expr_get((*c).exprs, (long long)(recv));
    if (_m774.tag == 1) {
        uint64_t start = _m774.data.Ident.start;
        (void)start;
        uint64_t len = _m774.data.Ident.len;
        (void)len;
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"calling a `move fn` on `self` is not yet supported", 50});
    }
    uint64_t li = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (li < (long long)(((*c).locals).count)) {
    if (Array_Local_get((*c).locals, (long long)(li)).owned) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call a `move fn` on a borrowed value (it consumes the receiver)", 70});
    }
    }
    if (li < (*c).curBranchBase) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call a `move fn` on a variable declared outside the enclosing conditional/loop (the consume would be conditional)", 120});
    }
    }
    else if (_m774.tag == 5) {
        uint64_t base = _m774.data.Field.base;
        (void)base;
        uint64_t nameStart = _m774.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m774.data.Field.nameLen;
        (void)nameLen;
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), recv)), (PlewString){"cannot call a `move fn` on a field (partial move, not yet supported)", 68});
    }
    else if (_m774.tag == 9) {
        uint64_t base = _m774.data.Index.base;
        (void)base;
        uint64_t index = _m774.data.Index.index;
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
    if ((long long)((mf.typeParams).count) > 0) {
    uint64_t rcount = 0;
    uint64_t recvInst = 0;
    if (isGenericInst_c_Comp_ref_U64(&((*c)), bt.ref)) {
    rcount = recvParamCount_c_Comp_nameStart_U64_nameLen_U64(&((*c)), bt.nameStart, bt.nameLen);
    recvInst = bt.ref;
    }
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), bt.nameStart, bt.nameLen, recvInst);
    Array_U64 mArgs = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), mf, Array_Arg_share(args));
    clearSelfItemEnv_c_Comp(&((*c)));
    writeMethodInstSuffixFrom_c_Comp_typeArgs_AU64_startIdx_U64(&((*c)), Array_U64_share(mArgs), rcount);
    Array_U64_release(mArgs);
    }
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
    while (i < (long long)((args).count)) {
    plew_write((PlewString){", ", 2});
    Arg ar = Array_Arg_get(args, (long long)(i));
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
    else if (_m770.tag == 8) {
        Array_U64 elems = _m770.data.Array.elems;
        (void)elems;
    plew_write((PlewString){"0", 1});
    }
    else if (_m770.tag == 11) {
        uint64_t operand = _m770.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m770.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m770.data.Cast.tyLen;
        (void)tyLen;
    if (isIntType_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen)) {
    Expr opE = Expr_share(Array_Expr_get((*c).exprs, (long long)(operand)));
    {
    Expr _m775 = opE;
    if (_m775.tag == 0) {
        uint64_t value = _m775.data.Int.value;
        (void)value;
        uint64_t offset = _m775.data.Int.offset;
        (void)offset;
    if (litFitsType_c_Comp_value_U64_neg_Bool_dstStart_U64_dstLen_U64(&((*c)), value, 0, tyStart, tyLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), offset), (PlewString){"integer literal is out of range for the target type of `as`", 59});
    Expr_release(opE);
    Expr_release(e);
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
    Expr_release(opE);
    Expr_release(e);
    return;
    }
    }
    }
    }
    Expr_release(opE);
    }
    plew_write((PlewString){"((", 2});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), tyStart, tyLen);
    plew_write((PlewString){")(", 2});
    genExpr_c_Comp_id_U64(&((*c)), operand);
    plew_write((PlewString){"))", 2});
    }
    else if (_m770.tag == 6) {
        uint64_t typeStart = _m770.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m770.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m770.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m770.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m770.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m770.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m770.data.Make.fields;
        (void)fields;
    if (isRefInst_c_Comp_ref_U64(&((*c)), ty)) {
    TypeRef rt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ty)));
    uint64_t t2 = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    plew_write((PlewString){"({ ", 3});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){"* __ref", 7});
    writeU64_n_U64(t2);
    plew_write((PlewString){" = (", 4});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
    plew_write((PlewString){")); *__ref", 10});
    writeU64_n_U64(t2);
    plew_write((PlewString){" = (", 4});
    if ((long long)((fields).count) > 0) {
    TypeInfo bti = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(rt.args, (long long)(0)));
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), Array_MakeField_get(fields, (long long)(0)).value, Array_U64_get(rt.args, (long long)(0)), bti.nameStart, bti.nameLen, (bti.kind == 3));
    }
    else {
    plew_write((PlewString){"0", 1});
    }
    plew_write((PlewString){"); __ref", 8});
    writeU64_n_U64(t2);
    plew_write((PlewString){"; })", 4});
    TypeRef_release(rt);
    Expr_release(e);
    return;
    TypeRef_release(rt);
    }
    if (isEnum) {
    uint64_t ety = ty;
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ety)) {
    }
    else {
    uint64_t gei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), typeStart, typeLen);
    if (gei < (long long)(((*c).enums).count)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), (*c).curRetTy)) {
    TypeRef rt2 = TypeRef_share(Array_TypeRef_get((*c).types, (long long)((*c).curRetTy)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), rt2.nameStart, rt2.nameLen, typeStart, typeLen)) {
    ety = (*c).curRetTy;
    }
    TypeRef_release(rt2);
    }
    }
    }
    plew_write((PlewString){"(", 1});
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ety)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), ety);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen);
    }
    plew_write((PlewString){"){.tag = ", 9});
    writeU64_n_U64(variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(&((*c)), typeStart, typeLen, variantStart, variantLen));
    if ((long long)((fields).count) > 0) {
    plew_write((PlewString){", .data.", 8});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), variantStart, variantLen);
    plew_write((PlewString){" = {", 4});
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = Array_MakeField_get(fields, (long long)(i));
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), mf.nameStart, mf.nameLen);
    plew_write((PlewString){" = ", 3});
    TypeInfo eft = scalarInfo();
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ety)) {
    eft = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), ety, variantStart, variantLen, mf.nameStart, mf.nameLen);
    }
    else {
    eft = makeFieldType_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, variantStart, variantLen, 1, mf.nameStart, mf.nameLen);
    }
    FieldDef efd = findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, variantStart, variantLen, 1, mf.nameStart, mf.nameLen);
    if (efd.nameLen > 0) {
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), efd)) {
    genBoxCell_c_Comp_fd_FieldDef_valueId_U64(&((*c)), efd, mf.value);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    continue;
    }
    }
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), mf.value, eft.ref, eft.nameStart, eft.nameLen, (eft.kind == 3));
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
    while (i < (long long)((fields).count)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    MakeField mf = Array_MakeField_get(fields, (long long)(i));
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
    FieldDef sfd = findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), typeStart, typeLen, 0, 0, 0, mf.nameStart, mf.nameLen);
    long long sBoxed = 0;
    if (sfd.nameLen > 0) {
    sBoxed = fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), sfd);
    }
    if (sBoxed) {
    genBoxCell_c_Comp_fd_FieldDef_valueId_U64(&((*c)), sfd, mf.value);
    }
    else {
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), mf.value, ft.ref, ft.nameStart, ft.nameLen, (ft.kind == 3));
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t dEmitted = (long long)((fields).count);
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    StructDef sd = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), sd.nameStart, sd.nameLen, typeStart, typeLen)) {
    Array_FieldDef flds = Array_FieldDef_share(sd.fields);
    uint64_t fi = 0;
    while (fi < (long long)((flds).count)) {
    FieldDef fd = Array_FieldDef_get(flds, (long long)(fi));
    if (fd.hasDefault) {
    if (makeProvides_c_Comp_fields_AMakeField_nameStart_U64_nameLen_U64(&((*c)), Array_MakeField_share(fields), fd.nameStart, fd.nameLen)) {
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
    Array_FieldDef_release(flds);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(sd);
    }
    plew_write((PlewString){"}", 1});
    }
    }
    else if (_m770.tag == 12) {
        uint64_t scrut = _m770.data.MatchExpr.scrut;
        (void)scrut;
        Array_MatchArm arms = _m770.data.MatchExpr.arms;
        (void)arms;
    if ((long long)((arms).count) > 0) {
    if (Array_MatchArm_get(arms, (long long)(0)).isStruct) {
    emitStructMatchExpr_c_Comp_scrut_U64_arm_MatchArm(&((*c)), scrut, Array_MatchArm_get(arms, (long long)(0)));
    Expr_release(e);
    return;
    }
    }
    if (matchExhaustive_c_Comp_arms_AMatchArm(&((*c)), Array_MatchArm_share(arms))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), scrut)), (PlewString){"match must be exhaustive: cover all variants or add a wildcard", 62});
    Expr_release(e);
    return;
    }
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), Array_MatchArm_get(arms, (long long)(0)).body);
    uint64_t scrutRef = exprType_c_Comp_id_U64(&((*c)), scrut).ref;
    long long genericMatch = isGenericEnumInst_c_Comp_ref_U64(&((*c)), scrutRef);
    uint64_t enumStart = 0;
    uint64_t enumLen = 0;
    long long hasWildcard = 0;
    uint64_t q = 0;
    while (q < (long long)((arms).count)) {
    MatchArm aq = MatchArm_share(Array_MatchArm_get(arms, (long long)(q)));
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
    while (i < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(i)));
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
    Array_Bind binds = Array_Bind_share(a.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).count)) {
    Bind bd = Array_Bind_get(binds, (long long)(bi));
    if (genericMatch) {
    genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    else {
    genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    long long mBoxed = 0;
    if (genericMatch) {
    }
    else {
    FieldDef mfd = findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, 1, bd.fieldStart, bd.fieldLen);
    if (mfd.nameLen > 0) {
    mBoxed = fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), mfd);
    }
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = ", 3});
    if (mBoxed) {
    plew_write((PlewString){"*(", 2});
    }
    plew_write((PlewString){"__ms", 4});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), a.variantStart, a.variantLen);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.fieldStart, bd.fieldLen);
    if (mBoxed) {
    plew_write((PlewString){")", 1});
    }
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
    Array_Bind_release(binds);
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
    else if (_m770.tag == 13) {
        uint64_t cond = _m770.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m770.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m770.data.IfExpr.elseBlk;
        (void)elseBlk;
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    uint64_t g = blockGiveExpr_c_Comp_blkId_U64(&((*c)), thenBlk);
    TypeInfo rt = scalarInfo();
    if (g < (long long)(((*c).exprs).count)) {
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
    else if (_m770.tag == 14) {
        uint64_t opt = _m770.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m770.data.Coalesce.deflt;
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
    else if (_m770.tag == 15) {
        uint64_t expr = _m770.data.Try.expr;
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
    else if (_m770.tag == 19) {
        uint64_t operand = _m770.data.Await.operand;
        (void)operand;
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), operand)), (PlewString){"`await` is only allowed at statement head in an `async fn` (`val x = await e` / `await e` / `return await e`) for now", 117});
    }
    else { __builtin_unreachable(); }
    }
    Expr_release(e);
}
long long isPlaceExpr_c_Comp_id_U64(Comp* c, uint64_t id) {
    {
    Expr _m776 = Array_Expr_get((*c).exprs, (long long)(id));
    if (_m776.tag == 1) {
        uint64_t start = _m776.data.Ident.start;
        (void)start;
        uint64_t len = _m776.data.Ident.len;
        (void)len;
    { long long __ret777 = 1;
    return __ret777; }
    }
    else if (_m776.tag == 5) {
        uint64_t base = _m776.data.Field.base;
        (void)base;
        uint64_t nameStart = _m776.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m776.data.Field.nameLen;
        (void)nameLen;
    { long long __ret778 = 1;
    return __ret778; }
    }
    else if (_m776.tag == 9) {
        uint64_t base = _m776.data.Index.base;
        (void)base;
        uint64_t index = _m776.data.Index.index;
        (void)index;
    { long long __ret779 = 1;
    return __ret779; }
    }
    else {
    { long long __ret780 = 0;
    return __ret780; }
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
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(exprId)));
    {
    Expr _m781 = e;
    if (_m781.tag == 8) {
        Array_U64 elems = _m781.data.Array.elems;
        (void)elems;
    if ((long long)((elems).count) == 0) {
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new()", 6});
    }
    else {
    plew_write((PlewString){"({ ", 3});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" __a = ", 7});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new(); ", 8});
    uint64_t i = 0;
    while (i < (long long)((elems).count)) {
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(&__a, ", 12});
    genExpr_c_Comp_id_U64(&((*c)), Array_U64_get(elems, (long long)(i)));
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
    Expr_release(e);
}
long long isStringEq_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    if (op == opEq()) {
    }
    else {
    if (op == opNe()) {
    }
    else {
    { long long __ret782 = 0;
    return __ret782; }
    }
    }
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    { long long __ret783 = (lt.kind == 1);
    return __ret783; }
}
long long isEnumName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    { long long __ret784 = 1;
    EnumDef_release(e);
    return __ret784; }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret785 = 0;
    return __ret785; }
}
long long isAllNullary_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if ((long long)((v.fields).count) > 0) {
    { long long __ret786 = 0;
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(e);
    return __ret786; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { long long __ret787 = 1;
    Array_Variant_release(vars);
    EnumDef_release(e);
    return __ret787; }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { long long __ret788 = 0;
    return __ret788; }
}
long long isEnumEq_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    if (op == opEq()) {
    }
    else {
    if (op == opNe()) {
    }
    else {
    { long long __ret789 = 0;
    return __ret789; }
    }
    }
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 2) {
    { long long __ret790 = isEnumName_c_Comp_start_U64_len_U64(&((*c)), lt.nameStart, lt.nameLen);
    return __ret790; }
    }
    { long long __ret791 = 0;
    return __ret791; }
}
long long compareNeedsTrait_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    if (op < 50) {
    { long long __ret792 = 0;
    return __ret792; }
    }
    if (op > 55) {
    { long long __ret793 = 0;
    return __ret793; }
    }
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 3) {
    { long long __ret794 = 1;
    return __ret794; }
    }
    if (lt.kind == 2) {
    if (isEnumName_c_Comp_start_U64_len_U64(&((*c)), lt.nameStart, lt.nameLen)) {
    { long long __ret795 = 0;
    return __ret795; }
    }
    { long long __ret796 = 1;
    return __ret796; }
    }
    { long long __ret797 = 0;
    return __ret797; }
}
void emitEnumOperand_c_Comp_id_U64_enStart_U64_enLen_U64(Comp* c, uint64_t id, uint64_t enStart, uint64_t enLen) {
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m798 = e;
    if (_m798.tag == 6) {
        uint64_t typeStart = _m798.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m798.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m798.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m798.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m798.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m798.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m798.data.Make.fields;
        (void)fields;
    if (isEnum) {
    writeU64_n_U64(variantIndex_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64(&((*c)), enStart, enLen, variantStart, variantLen));
    Expr_release(e);
    return;
    }
    }
    else {
    }
    }
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), id);
    plew_write((PlewString){").tag", 5});
    Expr_release(e);
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
    if (op == opNe()) {
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
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.isAssoc) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, typeStart, typeLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), f.nameStart, f.nameLen, name)) {
    { uint64_t __ret799 = i;
    Func_release(f);
    return __ret799; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { uint64_t __ret800 = (long long)(((*c).funcs).count);
    return __ret800; }
}
uint64_t orderingVariantIndex_c_Comp_name_String(Comp* c, PlewString name) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), e.nameStart, e.nameLen, (PlewString){"Ordering", 8})) {
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), Array_Variant_get(vars, (long long)(vi)).nameStart, Array_Variant_get(vars, (long long)(vi)).nameLen, name)) {
    { uint64_t __ret801 = vi;
    Array_Variant_release(vars);
    EnumDef_release(e);
    return __ret801; }
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret802 = 0;
    return __ret802; }
}
long long hasCompareWitness_c_Comp_op_I64_lhs_U64(Comp* c, int64_t op, uint64_t lhs) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (lt.kind == 2) {
    if (op == opEq()) {
    { long long __ret803 = eqWitnessReady_c_Comp_ti_TypeInfo(&((*c)), lt);
    return __ret803; }
    }
    if (op == opNe()) {
    { long long __ret804 = eqWitnessReady_c_Comp_ti_TypeInfo(&((*c)), lt);
    return __ret804; }
    }
    if (op >= 52) {
    if (op <= 55) {
    if (typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(&((*c)), lt.nameStart, lt.nameLen, (PlewString){"Ord", 3})) {
    { long long __ret805 = (findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(&((*c)), lt.nameStart, lt.nameLen, (PlewString){"compare", 7}) < (long long)(((*c).funcs).count));
    return __ret805; }
    }
    }
    }
    }
    { long long __ret806 = 0;
    return __ret806; }
}
long long eqWitnessReady_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (typeConformsToName_c_Comp_typeStart_U64_typeLen_U64_traitName_String(&((*c)), ti.nameStart, ti.nameLen, (PlewString){"Eq", 2})) {
    { long long __ret807 = (findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(&((*c)), ti.nameStart, ti.nameLen, (PlewString){"eq", 2}) < (long long)(((*c).funcs).count));
    return __ret807; }
    }
    { long long __ret808 = 0;
    return __ret808; }
}
void emitEqCall_c_Comp_typeStart_U64_typeLen_U64_lhs_U64_rhs_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t lhs, uint64_t rhs) {
    uint64_t fi = findAssocByName_c_Comp_typeStart_U64_typeLen_U64_name_String(&((*c)), typeStart, typeLen, (PlewString){"eq", 2});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen);
    plew_write((PlewString){"_", 1});
    writeFnSelector_c_Comp_f_Func(&((*c)), Array_Func_get((*c).funcs, (long long)(fi)));
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){")", 1});
}
void emitTraitCompare_c_Comp_op_I64_lhs_U64_rhs_U64(Comp* c, int64_t op, uint64_t lhs, uint64_t rhs) {
    TypeInfo lt = exprType_c_Comp_id_U64(&((*c)), lhs);
    if (op == opEq()) {
    emitEqCall_c_Comp_typeStart_U64_typeLen_U64_lhs_U64_rhs_U64(&((*c)), lt.nameStart, lt.nameLen, lhs, rhs);
    return;
    }
    if (op == opNe()) {
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
    writeFnSelector_c_Comp_f_Func(&((*c)), Array_Func_get((*c).funcs, (long long)(ci)));
    plew_write((PlewString){"(", 1});
    genExpr_c_Comp_id_U64(&((*c)), lhs);
    plew_write((PlewString){", ", 2});
    genExpr_c_Comp_id_U64(&((*c)), rhs);
    plew_write((PlewString){").tag ", 6});
    if (op == opLt()) {
    plew_write((PlewString){"== ", 3});
    writeU64_n_U64(lessIdx);
    }
    if (op == opLe()) {
    plew_write((PlewString){"!= ", 3});
    writeU64_n_U64(greaterIdx);
    }
    if (op == opGt()) {
    plew_write((PlewString){"== ", 3});
    writeU64_n_U64(greaterIdx);
    }
    if (op == opGe()) {
    plew_write((PlewString){"!= ", 3});
    writeU64_n_U64(lessIdx);
    }
    plew_write((PlewString){")", 1});
}
void genCond_c_Comp_id_U64(Comp* c, uint64_t id) {
    Expr e = Expr_share(Array_Expr_get((*c).exprs, (long long)(id)));
    {
    Expr _m809 = e;
    if (_m809.tag == 3) {
        int64_t op = _m809.data.Binary.op;
        (void)op;
        uint64_t lhs = _m809.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m809.data.Binary.rhs;
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
    Expr_release(e);
}
long long tryArrayElemFieldAssign_c_Comp_op_I64_target_U64_value_U64(Comp* c, int64_t op, uint64_t target, uint64_t value) {
    Expr te = Expr_share(Array_Expr_get((*c).exprs, (long long)(target)));
    {
    Expr _m810 = te;
    if (_m810.tag == 5) {
        uint64_t base = _m810.data.Field.base;
        (void)base;
        uint64_t nameStart = _m810.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m810.data.Field.nameLen;
        (void)nameLen;
    Expr be = Expr_share(Array_Expr_get((*c).exprs, (long long)(base)));
    {
    Expr _m811 = be;
    if (_m811.tag == 9) {
        uint64_t abase = _m811.data.Index.base;
        (void)abase;
        uint64_t index = _m811.data.Index.index;
        (void)index;
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), abase);
    if (bt.kind == 3) {
    }
    else {
    { long long __ret812 = 0;
    Expr_release(be);
    Expr_release(te);
    return __ret812; }
    }
    if (placeIsMutable_c_Comp_id_U64(&((*c)), target)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), target)), (PlewString){"cannot assign through this place; the binding and field must be declared `mut val`", 82});
    { long long __ret813 = 1;
    Expr_release(be);
    Expr_release(te);
    return __ret813; }
    }
    TypeInfo ft = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), bt.nameStart, bt.nameLen, nameStart, nameLen);
    if (op == opAssign()) {
    checkLitTi_c_Comp_id_U64_ti_TypeInfo(&((*c)), value, ft);
    }
    plew_write((PlewString){"    Array_", 10});
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
    if (op == opAssign()) {
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
    { long long __ret814 = 1;
    Expr_release(be);
    Expr_release(te);
    return __ret814; }
    }
    else {
    { long long __ret815 = 0;
    Expr_release(be);
    Expr_release(te);
    return __ret815; }
    }
    }
    Expr_release(be);
    }
    else {
    { long long __ret816 = 0;
    Expr_release(te);
    return __ret816; }
    }
    }
    Expr_release(te);
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
    Array_Bind binds = Array_Bind_share(arm.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).count)) {
    Bind bd = Array_Bind_get(binds, (long long)(bi));
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
    Array_Bind_release(binds);
}
TypeInfo forBindFieldType_c_Comp_et_TypeInfo_bd_Bind(Comp* c, TypeInfo et, Bind bd) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), et.ref)) {
    { TypeInfo __ret817 = genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(&((*c)), et.ref, bd.fieldStart, bd.fieldLen);
    return __ret817; }
    }
    { TypeInfo __ret818 = fieldType_c_Comp_structStart_U64_structLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), et.nameStart, et.nameLen, bd.fieldStart, bd.fieldLen);
    return __ret818; }
}
void addForStructBinds_c_Comp_et_TypeInfo_binds_ABind(Comp* c, TypeInfo et, Array_Bind binds) {
    uint64_t bi = 0;
    while (bi < (long long)((binds).count)) {
    Bind bd = Array_Bind_get(binds, (long long)(bi));
    TypeInfo ft = forBindFieldType_c_Comp_et_TypeInfo_bd_Bind(&((*c)), et, bd);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), bd.nameStart, bd.nameLen, ft.nameStart, ft.nameLen, (ft.kind == 3), ft.ref, 0, 0, 0);
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void compileIterableFor_c_Comp_t_U64_varStart_U64_varLen_U64_iter_U64_body_U64_et_TypeInfo(Comp* c, uint64_t t, uint64_t varStart, uint64_t varLen, uint64_t iter, uint64_t body, TypeInfo et) {
    Array_Arg noArgs = Array_Arg_new();
    Bind itName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"iterator", 8}, 8);
    uint64_t imi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), et.nameStart, et.nameLen, itName.nameStart, itName.nameLen, Array_Arg_share(noArgs));
    uint64_t itRef = 0;
    uint64_t itFallStart = 0;
    uint64_t itFallLen = 0;
    long long itFallArr = 0;
    long long isIterable = 0;
    if (imi == (long long)(((*c).funcs).count)) {
    itRef = et.ref;
    itFallStart = et.nameStart;
    itFallLen = et.nameLen;
    }
    else {
    isIterable = 1;
    Func imf = Func_share(Array_Func_get((*c).funcs, (long long)(imi)));
    itRef = groundUnderInst_c_Comp_instRef_U64_tyRef_U64(&((*c)), et.ref, imf.retTy);
    itFallStart = imf.retStart;
    itFallLen = imf.retLen;
    itFallArr = imf.retIsArray;
    Func_release(imf);
    }
    long long itGeneric = isGenericInst_c_Comp_ref_U64(&((*c)), itRef);
    Bind nxName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"next", 4}, 4);
    uint64_t nmi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), itFallStart, itFallLen, nxName.nameStart, nxName.nameLen, Array_Arg_share(noArgs));
    if (nmi == (long long)(((*c).funcs).count)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), iter)), (PlewString){"type is not iterable: no `iterator()` or `next()` method (conform to Iterable or Iterator)", 90});
    Array_Arg_release(noArgs);
    return;
    }
    Func nmf = Func_share(Array_Func_get((*c).funcs, (long long)(nmi)));
    uint64_t optRef = groundUnderInst_c_Comp_instRef_U64_tyRef_U64(&((*c)), itRef, nmf.retTy);
    uint64_t itemRef = 0;
    if (optRef < (long long)(((*c).types).count)) {
    TypeRef ot = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(optRef)));
    if ((long long)((ot.args).count) > 0) {
    itemRef = Array_U64_get(ot.args, (long long)(0));
    }
    TypeRef_release(ot);
    }
    TypeInfo itemInfo = typeInfoOfRef_c_Comp_ref_U64(&((*c)), itemRef);
    long long itemIsArr = (itemInfo.kind == 3);
    plew_write((PlewString){"    {\n", 6});
    plew_write((PlewString){"    ", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), itRef, itFallStart, itFallLen, itFallArr);
    plew_write((PlewString){" __it", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    if (isIterable) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), et.ref)) {
    emitMangle_c_Comp_ref_U64(&((*c)), et.ref);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), et.nameStart, et.nameLen);
    }
    plew_write((PlewString){"_iterator(", 10});
    genExpr_c_Comp_id_U64(&((*c)), iter);
    plew_write((PlewString){")", 1});
    }
    else {
    genExpr_c_Comp_id_U64(&((*c)), iter);
    }
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"    while (1) {\n", 16});
    plew_write((PlewString){"        ", 8});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), optRef, nmf.retStart, nmf.retLen, nmf.retIsArray);
    plew_write((PlewString){" __o", 4});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    if (itGeneric) {
    emitMangle_c_Comp_ref_U64(&((*c)), itRef);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), itFallStart, itFallLen);
    }
    plew_write((PlewString){"_next(&__it", 11});
    writeU64_n_U64(t);
    plew_write((PlewString){");\n", 3});
    plew_write((PlewString){"        if (__o", 15});
    writeU64_n_U64(t);
    plew_write((PlewString){".tag != 0) { break; }\n", 22});
    plew_write((PlewString){"        ", 8});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), itemRef, itemInfo.nameStart, itemInfo.nameLen, itemIsArr);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), varStart, varLen);
    plew_write((PlewString){" = __o", 6});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.Some.v;\n", 14});
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, itemInfo.nameStart, itemInfo.nameLen, itemIsArr, itemRef, 0, 0, 0);
    genBlock_c_Comp_id_U64(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    Func_release(nmf);
    Array_Arg_release(noArgs);
}
void genStmt_c_Comp_id_U64(Comp* c, uint64_t id) {
    Stmt s = Stmt_share(Array_Stmt_get((*c).stmts, (long long)(id)));
    {
    Stmt _m819 = s;
    if (_m819.tag == 0) {
        long long mutable = _m819.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m819.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m819.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m819.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m819.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m819.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m819.data.Let.ty;
        (void)ty;
        uint64_t init = _m819.data.Let.init;
        (void)init;
    LetEff le = inferLetType_c_Comp_tyStart_U64_tyLen_U64_tyIsArray_Bool_ty_U64_init_U64(&((*c)), tyStart, tyLen, tyIsArray, ty, init);
    uint64_t effStart = le.start;
    uint64_t effLen = le.len;
    long long effArr = le.arr;
    uint64_t effTy = le.ty;
    if ((*c).curAsync) {
    genAsyncLet_c_Comp_nameStart_U64_nameLen_U64_effStart_U64_effLen_U64_effArr_Bool_effTy_U64_init_U64_mutable_Bool(&((*c)), nameStart, nameLen, effStart, effLen, effArr, effTy, init, mutable);
    Stmt_release(s);
    return;
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
    Stmt_release(s);
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
    else if (_m819.tag == 1) {
        int64_t op = _m819.data.Assign.op;
        (void)op;
        uint64_t target = _m819.data.Assign.target;
        (void)target;
        uint64_t value = _m819.data.Assign.value;
        (void)value;
    if (tryArrayElemFieldAssign_c_Comp_op_I64_target_U64_value_U64(&((*c)), op, target, value)) {
    Stmt_release(s);
    return;
    }
    Expr te = Expr_share(Array_Expr_get((*c).exprs, (long long)(target)));
    {
    Expr _m820 = te;
    if (_m820.tag == 9) {
        uint64_t base = _m820.data.Index.base;
        (void)base;
        uint64_t index = _m820.data.Index.index;
        (void)index;
    if (placeIsMutable_c_Comp_id_U64(&((*c)), base)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), base)), (PlewString){"cannot assign to an element of an immutable binding; declare it with `mut val`", 78});
    Expr_release(te);
    Stmt_release(s);
    return;
    }
    TypeInfo bt = exprType_c_Comp_id_U64(&((*c)), base);
    if (bt.kind == 3) {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), value, bt.nameStart, bt.nameLen, 0);
    }
    plew_write((PlewString){"    Array_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bt.nameStart, bt.nameLen);
    plew_write((PlewString){"_set(&(", 7});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr_c_Comp_id_U64(&((*c)), index);
    plew_write((PlewString){"), ", 3});
    if (op == opAssign()) {
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
    Expr_release(te);
    Stmt_release(s);
    return;
    }
    {
    Expr _m821 = Array_Expr_get((*c).exprs, (long long)(target));
    if (_m821.tag == 5) {
        uint64_t base = _m821.data.Field.base;
        (void)base;
        uint64_t nameStart = _m821.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m821.data.Field.nameLen;
        (void)nameLen;
    TypeInfo fbt = exprType_c_Comp_id_U64(&((*c)), base);
    if (fbt.kind == 2) {
    checkFieldWriteVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(&((*c)), fbt.nameStart, fbt.nameLen, nameStart, nameLen, nameStart);
    FieldDef afd = findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), fbt.nameStart, fbt.nameLen, 0, 0, 0, nameStart, nameLen);
    if (afd.nameLen > 0) {
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), afd)) {
    if (op == opAssign()) {
    plew_write((PlewString){"    ", 4});
    genExpr_c_Comp_id_U64(&((*c)), base);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), nameStart, nameLen);
    plew_write((PlewString){" = ", 3});
    genBoxCell_c_Comp_fd_FieldDef_valueId_U64(&((*c)), afd, value);
    plew_write((PlewString){";\n", 2});
    Expr_release(te);
    Stmt_release(s);
    return;
    }
    }
    }
    }
    else {
    if (fbt.kind == 3) {
    Bind arrW = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Array", 5}, 5);
    checkFieldWriteVis_c_Comp_ownerStart_U64_ownerLen_U64_fieldStart_U64_fieldLen_U64_offset_U64(&((*c)), arrW.nameStart, arrW.nameLen, nameStart, nameLen, nameStart);
    }
    }
    }
    else {
    }
    }
    TypeInfo ctt = exprType_c_Comp_id_U64(&((*c)), target);
    if (ctt.kind == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), ctt.nameStart, ctt.nameLen)) {
    if (op == opAssign()) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), target)), (PlewString){"compound assignment is not valid for a unique value", 51});
    Expr_release(te);
    Stmt_release(s);
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
    Expr_release(te);
    Stmt_release(s);
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
    genCheckedDiv_c_Comp_lhs_U64_rhs_U64_tyStart_U64_tyLen_U64_isMod_Bool(&((*c)), target, value, dt.nameStart, dt.nameLen, (op == opRemAssign()));
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
    if (op == opAssign()) {
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
    Expr_release(te);
    }
    else if (_m819.tag == 2) {
        uint64_t expr = _m819.data.ExprStmt.expr;
        (void)expr;
    if ((*c).curAsync) {
    {
    Expr _m822 = Array_Expr_get((*c).exprs, (long long)(expr));
    if (_m822.tag == 19) {
        uint64_t operand = _m822.data.Await.operand;
        (void)operand;
    emitAsyncSuspend_c_Comp_operandId_U64(&((*c)), operand);
    Stmt_release(s);
    return;
    }
    else {
    }
    }
    }
    checkLitCtx_c_Comp_id_U64_eKind_U64_eBits_U64_eSgn_Bool(&((*c)), expr, 0, 0, 0);
    plew_write((PlewString){"    ", 4});
    genExpr_c_Comp_id_U64(&((*c)), expr);
    plew_write((PlewString){";\n", 2});
    }
    else if (_m819.tag == 3) {
        uint64_t value = _m819.data.Return.value;
        (void)value;
        long long hasValue = _m819.data.Return.hasValue;
        (void)hasValue;
    if ((*c).curAsync) {
    genAsyncReturn_c_Comp_value_U64_hasValue_Bool(&((*c)), value, hasValue);
    Stmt_release(s);
    return;
    }
    if ((*c).curIsMain) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), 0, (long long)(((*c).locals).count));
    plew_write((PlewString){"    return 0;\n", 14});
    }
    else {
    if ((*c).curRetVoid) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), 0, (long long)(((*c).locals).count));
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
    uint64_t retExcl = (long long)(((*c).locals).count);
    if (hasValue) {
    TypeInfo vt = exprType_c_Comp_id_U64(&((*c)), value);
    if (vt.kind == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), vt.nameStart, vt.nameLen)) {
    {
    Expr _m823 = Array_Expr_get((*c).exprs, (long long)(value));
    if (_m823.tag == 1) {
        uint64_t start = _m823.data.Ident.start;
        (void)start;
        uint64_t len = _m823.data.Ident.len;
        (void)len;
    if ((*c).curSelfMove) {
    if (isSelfRef_c_Comp_start_U64_len_U64(&((*c)), start, len)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), value)), (PlewString){"returning `self` from a `move fn` is not yet supported", 54});
    }
    }
    retExcl = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    }
    else if (_m823.tag == 5) {
        uint64_t base = _m823.data.Field.base;
        (void)base;
        uint64_t nameStart = _m823.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m823.data.Field.nameLen;
        (void)nameLen;
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), value)), (PlewString){"returning a field of a unique value is a partial move (not yet supported)", 73});
    }
    else if (_m823.tag == 9) {
        uint64_t base = _m823.data.Index.base;
        (void)base;
        uint64_t index = _m823.data.Index.index;
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
    else if (_m819.tag == 4) {
        uint64_t cond = _m819.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m819.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m819.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m819.data.If.hasElse;
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
    else if (_m819.tag == 5) {
        uint64_t cond = _m819.data.While.cond;
        (void)cond;
        uint64_t body = _m819.data.While.body;
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
    else if (_m819.tag == 6) {
        uint64_t varStart = _m819.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m819.data.For.varLen;
        (void)varLen;
        long long isRange = _m819.data.For.isRange;
        (void)isRange;
        long long inclusive = _m819.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m819.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m819.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m819.data.For.body;
        (void)body;
        long long isStruct = _m819.data.For.isStruct;
        (void)isStruct;
        uint64_t patStart = _m819.data.For.patStart;
        (void)patStart;
        uint64_t patLen = _m819.data.For.patLen;
        (void)patLen;
        Array_Bind binds = _m819.data.For.binds;
        (void)binds;
    if (isRange) {
    checkArithNoCtx_c_Comp_lhs_U64_rhs_U64(&((*c)), iter, rangeHi);
    if (isStruct) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), patStart), (PlewString){"a struct-destructure for-loop iterates an array, not a range", 60});
    }
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
    if (et.kind == 3) {
    }
    else {
    if (isStruct) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), patStart), (PlewString){"a struct-destructure for-loop iterates an array, not an iterable", 64});
    }
    compileIterableFor_c_Comp_t_U64_varStart_U64_varLen_U64_iter_U64_body_U64_et_TypeInfo(&((*c)), t, varStart, varLen, iter, body, et);
    (*c).curBranchBase = savedBB;
    (*c).curLoopMark = savedLoopMark;
    scopeExit_c_Comp_mark_U64(&((*c)), forMark);
    Stmt_release(s);
    return;
    }
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
    plew_write((PlewString){" < (long long)__fa", 18});
    writeU64_n_U64(t);
    plew_write((PlewString){".count; __fi", 12});
    writeU64_n_U64(t);
    plew_write((PlewString){"++) {\n", 6});
    if (isStruct) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), patStart, patLen, et.nameStart, et.nameLen)) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), patStart), (PlewString){"for-loop destructure pattern type does not match the element type", 65});
    }
    plew_write((PlewString){"        ", 8});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){" __fe", 5});
    writeU64_n_U64(t);
    plew_write((PlewString){" = ", 3});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"_get(__fa", 9});
    writeU64_n_U64(t);
    plew_write((PlewString){", __fi", 6});
    writeU64_n_U64(t);
    plew_write((PlewString){");\n", 3});
    uint64_t bi = 0;
    while (bi < (long long)((binds).count)) {
    Bind bd = Array_Bind_get(binds, (long long)(bi));
    TypeInfo ft = forBindFieldType_c_Comp_et_TypeInfo_bd_Bind(&((*c)), et, bd);
    plew_write((PlewString){"        ", 8});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), ft.ref, ft.nameStart, ft.nameLen, (ft.kind == 3));
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){" = __fe", 7});
    writeU64_n_U64(t);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.fieldStart, bd.fieldLen);
    plew_write((PlewString){";\n        (void)", 16});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){";\n", 2});
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    addForStructBinds_c_Comp_et_TypeInfo_binds_ABind(&((*c)), et, Array_Bind_share(binds));
    }
    else {
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
    }
    genBlock_c_Comp_id_U64(&((*c)), body);
    plew_write((PlewString){"    }\n    }\n", 12});
    }
    (*c).curBranchBase = savedBB;
    (*c).curLoopMark = savedLoopMark;
    scopeExit_c_Comp_mark_U64(&((*c)), forMark);
    }
    else if (_m819.tag == 8) {
        uint64_t msg = _m819.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m819.data.Panic.offset;
        (void)offset;
    plew_write((PlewString){"    plew_panic(", 15});
    genExpr_c_Comp_id_U64(&((*c)), msg);
    plew_write((PlewString){");\n", 3});
    }
    else if (_m819.tag == 9) {
        uint64_t value = _m819.data.Give.value;
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
    else if (_m819.tag == 10) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), (*c).curLoopMark, (long long)(((*c).locals).count));
    plew_write((PlewString){"    break;\n", 11});
    }
    else if (_m819.tag == 11) {
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), (*c).curLoopMark, (long long)(((*c).locals).count));
    plew_write((PlewString){"    continue;\n", 14});
    }
    else if (_m819.tag == 7) {
        uint64_t scrut = _m819.data.Match.scrut;
        (void)scrut;
        Array_MatchArm arms = _m819.data.Match.arms;
        (void)arms;
    if ((long long)((arms).count) > 0) {
    if (Array_MatchArm_get(arms, (long long)(0)).isStruct) {
    emitStructMatch_c_Comp_scrut_U64_arm_MatchArm(&((*c)), scrut, Array_MatchArm_get(arms, (long long)(0)));
    Stmt_release(s);
    return;
    }
    }
    if (matchExhaustive_c_Comp_arms_AMatchArm(&((*c)), Array_MatchArm_share(arms))) {
    }
    else {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), exprOffset_c_Comp_id_U64(&((*c)), scrut)), (PlewString){"match must be exhaustive: cover all variants or add a wildcard", 62});
    Stmt_release(s);
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
    while (q < (long long)((arms).count)) {
    MatchArm aq = MatchArm_share(Array_MatchArm_get(arms, (long long)(q)));
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
    while (i < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(i)));
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
    Array_Bind binds = Array_Bind_share(a.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).count)) {
    Bind bd = Array_Bind_get(binds, (long long)(bi));
    uint64_t bcn = 0;
    if ((*c).curAsync) {
    bcn = nextAsyncVar_c_Comp(&((*c)));
    plew_write((PlewString){"        __f->", 13});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), bd.nameStart, bd.nameLen, bcn);
    }
    else {
    plew_write((PlewString){"        ", 8});
    if (genericMatch) {
    genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    else {
    genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    }
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    }
    long long smBoxed = 0;
    if (genericMatch) {
    }
    else {
    FieldDef smfd = findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, 1, bd.fieldStart, bd.fieldLen);
    if (smfd.nameLen > 0) {
    smBoxed = fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), smfd);
    }
    }
    plew_write((PlewString){" = ", 3});
    if (smBoxed) {
    plew_write((PlewString){"*(", 2});
    }
    plew_write((PlewString){"_m", 2});
    writeU64_n_U64(t);
    plew_write((PlewString){".data.", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), a.variantStart, a.variantLen);
    plew_write((PlewString){".", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.fieldStart, bd.fieldLen);
    if (smBoxed) {
    plew_write((PlewString){")", 1});
    }
    plew_write((PlewString){";\n", 2});
    if ((*c).curAsync) {
    }
    else {
    plew_write((PlewString){"        (void)", 14});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), bd.nameStart, bd.nameLen);
    plew_write((PlewString){";\n", 2});
    }
    if (genericMatch) {
    TypeInfo bti = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), scrutRef, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0, 0, bcn);
    }
    else {
    addBindLocalCn_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64_cnum_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen, bcn);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).curBranchBase = armMark;
    genBlock_c_Comp_id_U64(&((*c)), a.body);
    scopeExit_c_Comp_mark_U64(&((*c)), armMark);
    plew_write((PlewString){"    }\n", 6});
    Array_Bind_release(binds);
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
    Stmt_release(s);
}
void genBlock_c_Comp_id_U64(Comp* c, uint64_t id) {
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    Block b = Block_share(Array_Block_get((*c).blocks, (long long)(id)));
    Array_U64 stmts = Array_U64_share(b.stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).count)) {
    genStmt_c_Comp_id_U64(&((*c)), Array_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scopeExit_c_Comp_mark_U64(&((*c)), mark);
    Array_U64_release(stmts);
    Block_release(b);
}
long long nameIsMain_c_Comp_f_Func(Comp* c, Func f) {
    if (f.hasRecv) {
    { long long __ret824 = 0;
    return __ret824; }
    }
    { long long __ret825 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), f.nameStart, f.nameLen, (PlewString){"main", 4});
    return __ret825; }
}
long long isTraitName_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).traits).count)) {
    TraitDef t = TraitDef_share(Array_TraitDef_get((*c).traits, (long long)(i)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, start, len)) {
    { long long __ret826 = 1;
    TraitDef_release(t);
    return __ret826; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TraitDef_release(t);
    }
    { long long __ret827 = 0;
    return __ret827; }
}
long long methodRecvIsTrait_c_Comp_f_Func(Comp* c, Func f) {
    if (f.hasRecv) {
    { long long __ret828 = isTraitName_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen);
    return __ret828; }
    }
    { long long __ret829 = 0;
    return __ret829; }
}
long long methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(Comp* c, uint64_t lo, uint64_t hi, uint64_t recvStart, uint64_t recvLen, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = lo;
    while (i < hi) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, recvStart, recvLen)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.nameStart, f.nameLen, nameStart, nameLen)) {
    { long long __ret830 = 1;
    Func_release(f);
    return __ret830; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    { long long __ret831 = 0;
    return __ret831; }
}
Array_Bind providedCopyTypeParams_c_Comp_recvStart_U64_recvLen_U64_ownParams_ABind(Comp* c, uint64_t recvStart, uint64_t recvLen, Array_Bind ownParams) {
    Array_Bind out = Array_Bind_new();
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    if ((long long)((Array_StructDef_get((*c).structs, (long long)(si)).typeParams).count) > 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_StructDef_get((*c).structs, (long long)(si)).nameStart, Array_StructDef_get((*c).structs, (long long)(si)).nameLen, recvStart, recvLen)) {
    uint64_t k = 0;
    while (k < (long long)((Array_StructDef_get((*c).structs, (long long)(si)).typeParams).count)) {
    Array_Bind_append_value_T(&(out), Array_Bind_get(Array_StructDef_get((*c).structs, (long long)(si)).typeParams, (long long)(k)));
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t oi = 0;
    while (oi < (long long)((ownParams).count)) {
    Array_Bind_append_value_T(&(out), Array_Bind_get(ownParams, (long long)(oi)));
    oi = ({ uint64_t __ov; if (__builtin_add_overflow((oi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Array_Bind __ret832 = Array_Bind_share(out);
    Array_Bind_release(out);
    return __ret832; }
    Array_Bind_release(out);
}
void instantiateProvidedMethods_c_Comp(Comp* c) {
    uint64_t nFuncs = (long long)(((*c).funcs).count);
    uint64_t ci = 0;
    while (ci < (long long)(((*c).conforms).count)) {
    Conform cf = Conform_share(Array_Conform_get((*c).conforms, (long long)(ci)));
    uint64_t fi = 0;
    while (fi < nFuncs) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRecv) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, cf.traitStart, cf.traitLen)) {
    if (methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(&((*c)), 0, nFuncs, cf.typeStart, cf.typeLen, f.nameStart, f.nameLen)) {
    }
    else {
    if (methodInRange_c_Comp_lo_U64_hi_U64_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64(&((*c)), nFuncs, (long long)(((*c).funcs).count), cf.typeStart, cf.typeLen, f.nameStart, f.nameLen)) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), cf.typeStart), (PlewString){"two conformed traits provide a method of the same name; the bare call is ambiguous (`#`-disambiguation not yet supported)", 121});
    }
    else {
    Array_Bind copiedTP = providedCopyTypeParams_c_Comp_recvStart_U64_recvLen_U64_ownParams_ABind(&((*c)), cf.typeStart, cf.typeLen, Array_Bind_share(f.typeParams));
    Array_Func_append_value_T(&((*c).funcs), (Func){.nameStart = f.nameStart, .nameLen = f.nameLen, .typeParams = Array_Bind_share(copiedTP), .params = Array_Param_share(f.params), .hasRet = f.hasRet, .retStart = f.retStart, .retLen = f.retLen, .retIsArray = f.retIsArray, .retTy = f.retTy, .body = f.body, .hasRecv = 1, .recvStart = cf.typeStart, .recvLen = cf.typeLen, .selfInout = f.selfInout, .selfMove = f.selfMove, .isAssoc = f.isAssoc, .isAsync = f.isAsync, .isExtern = f.isExtern, .isPub = f.isPub, .isProvided = 1});
    Array_Bind_release(copiedTP);
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
    while (i < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(i)));
    if ((long long)((s.typeParams).count) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, start, len)) {
    { uint64_t __ret833 = i;
    StructDef_release(s);
    return __ret833; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { uint64_t __ret834 = (long long)(((*c).structs).count);
    return __ret834; }
}
long long structNeedsCopy_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).count)) {
    { long long __ret835 = 0;
    return __ret835; }
    }
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    if (fieldNeedsCopy_c_Comp_f_FieldDef(&((*c)), Array_FieldDef_get(fields, (long long)(i)))) {
    { long long __ret836 = 1;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    return __ret836; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret837 = 0;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    return __ret837; }
    Array_FieldDef_release(fields);
    StructDef_release(s);
}
long long structNeedsRelease_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (si >= (long long)(((*c).structs).count)) {
    { long long __ret838 = 0;
    return __ret838; }
    }
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    if (fieldNeedsRelease_c_Comp_f_FieldDef(&((*c)), Array_FieldDef_get(fields, (long long)(i)))) {
    { long long __ret839 = 1;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    return __ret839; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret840 = 0;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    return __ret840; }
    Array_FieldDef_release(fields);
    StructDef_release(s);
}
void emitDeinitProtos_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).deinits).count)) {
    Bind d = Array_Bind_get((*c).deinits, (long long)(i));
    plew_write((PlewString){"void ", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), d.nameStart, d.nameLen);
    plew_write((PlewString){"_deinit(", 8});
    genCTypeRef_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), d.nameStart, d.nameLen, 0);
    plew_write((PlewString){" self);\n", 8});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void emitStructCopyProto_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void emitStructShareProto_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
long long typeInfoNeedsCopy_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.kind == 3) {
    { long long __ret841 = 1;
    return __ret841; }
    }
    if (ti.kind == 2) {
    if (ti.ref != 0) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ti.ref)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ti.ref)) {
    { long long __ret842 = monoEnumNeedsCopy_c_Comp_instRef_U64(&((*c)), ti.ref);
    return __ret842; }
    }
    { long long __ret843 = monoStructNeedsCopy_c_Comp_instRef_U64(&((*c)), ti.ref);
    return __ret843; }
    }
    }
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen)) {
    { long long __ret844 = 1;
    return __ret844; }
    }
    { long long __ret845 = enumNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen);
    return __ret845; }
    }
    { long long __ret846 = 0;
    return __ret846; }
}
long long typeInfoNeedsRelease_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.kind == 3) {
    { long long __ret847 = 1;
    return __ret847; }
    }
    if (ti.kind == 2) {
    if (ti.ref != 0) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ti.ref)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), ti.ref)) {
    { long long __ret848 = monoEnumNeedsRelease_c_Comp_instRef_U64(&((*c)), ti.ref);
    return __ret848; }
    }
    { long long __ret849 = 0;
    return __ret849; }
    }
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen)) {
    { long long __ret850 = 1;
    return __ret850; }
    }
    { long long __ret851 = enumNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen);
    return __ret851; }
    }
    { long long __ret852 = 0;
    return __ret852; }
}
long long fieldNeedsCopy_c_Comp_f_FieldDef(Comp* c, FieldDef f) {
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), f)) {
    { long long __ret853 = 1;
    return __ret853; }
    }
    if (f.tyIsArray) {
    { long long __ret854 = 1;
    return __ret854; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), f.tyStart, f.tyLen, (PlewString){"RawBuffer", 9})) {
    { long long __ret855 = 1;
    return __ret855; }
    }
    if (f.ty != 0) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    { long long __ret856 = monoEnumNeedsCopy_c_Comp_instRef_U64(&((*c)), f.ty);
    return __ret856; }
    }
    { long long __ret857 = monoStructNeedsCopy_c_Comp_instRef_U64(&((*c)), f.ty);
    return __ret857; }
    }
    }
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret858 = 1;
    return __ret858; }
    }
    { long long __ret859 = enumNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    return __ret859; }
}
long long fieldNeedsRelease_c_Comp_f_FieldDef(Comp* c, FieldDef f) {
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), f)) {
    { long long __ret860 = 1;
    return __ret860; }
    }
    if (f.tyIsArray) {
    { long long __ret861 = 1;
    return __ret861; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), f.tyStart, f.tyLen, (PlewString){"RawBuffer", 9})) {
    { long long __ret862 = 1;
    return __ret862; }
    }
    if (f.ty != 0) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    { long long __ret863 = monoEnumNeedsRelease_c_Comp_instRef_U64(&((*c)), f.ty);
    return __ret863; }
    }
    { long long __ret864 = 0;
    return __ret864; }
    }
    }
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret865 = 1;
    return __ret865; }
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret866 = 1;
    return __ret866; }
    }
    { long long __ret867 = enumNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    return __ret867; }
}
long long enumNeedsCopy_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = concreteEnumIndex_c_Comp_nStart_U64_nLen_U64(&((*c)), start, len);
    if (ei >= (long long)(((*c).enums).count)) {
    { long long __ret868 = 0;
    return __ret868; }
    }
    Array_Variant vars = Array_Variant_share(Array_EnumDef_get((*c).enums, (long long)(ei)).variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Array_FieldDef fs = Array_FieldDef_share(Array_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    if (fieldNeedsCopy_c_Comp_f_FieldDef(&((*c)), Array_FieldDef_get(fs, (long long)(fi)))) {
    { long long __ret869 = 1;
    Array_FieldDef_release(fs);
    Array_Variant_release(vars);
    return __ret869; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(fs);
    }
    { long long __ret870 = 0;
    Array_Variant_release(vars);
    return __ret870; }
    Array_Variant_release(vars);
}
long long enumNeedsRelease_c_Comp_start_U64_len_U64(Comp* c, uint64_t start, uint64_t len) {
    uint64_t ei = concreteEnumIndex_c_Comp_nStart_U64_nLen_U64(&((*c)), start, len);
    if (ei >= (long long)(((*c).enums).count)) {
    { long long __ret871 = 0;
    return __ret871; }
    }
    Array_Variant vars = Array_Variant_share(Array_EnumDef_get((*c).enums, (long long)(ei)).variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Array_FieldDef fs = Array_FieldDef_share(Array_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    if (fieldNeedsRelease_c_Comp_f_FieldDef(&((*c)), Array_FieldDef_get(fs, (long long)(fi)))) {
    { long long __ret872 = 1;
    Array_FieldDef_release(fs);
    Array_Variant_release(vars);
    return __ret872; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(fs);
    }
    { long long __ret873 = 0;
    Array_Variant_release(vars);
    return __ret873; }
    Array_Variant_release(vars);
}
long long monoEnumNeedsRelease_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).count)) {
    { long long __ret874 = 0;
    TypeRef_release(t);
    return __ret874; }
    }
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Array_FieldDef fs = Array_FieldDef_share(Array_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, Array_Bind_share(e.typeParams), Array_FieldDef_get(fs, (long long)(fi)).ty);
    if (typeInfoNeedsRelease_c_Comp_ti_TypeInfo(&((*c)), ti)) {
    { long long __ret875 = 1;
    Array_FieldDef_release(fs);
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret875; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(fs);
    }
    { long long __ret876 = 0;
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret876; }
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
long long pointeeNeedsRelease_c_Comp_f_FieldDef(Comp* c, FieldDef f) {
    if (f.ty != 0) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    if (isGenericEnumInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    { long long __ret877 = monoEnumNeedsRelease_c_Comp_instRef_U64(&((*c)), f.ty);
    return __ret877; }
    }
    { long long __ret878 = 0;
    return __ret878; }
    }
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    { long long __ret879 = 1;
    return __ret879; }
    }
    { long long __ret880 = enumNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    return __ret880; }
}
void emitBoxedFieldRetain_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64(Comp* c, FieldDef f, long long isEnum, uint64_t vStart, uint64_t vLen) {
    plew_write((PlewString){" plew_ref_share((void*)s.", 25});
    if (isEnum) {
    plew_write((PlewString){"data.", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), vStart, vLen);
    plew_write((PlewString){".", 1});
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){");", 2});
}
void emitBoxedFieldRelease_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64(Comp* c, FieldDef f, long long isEnum, uint64_t vStart, uint64_t vLen) {
    plew_write((PlewString){" { ", 3});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.ty, f.tyStart, f.tyLen, 0);
    plew_write((PlewString){"* __bp = s.", 11});
    if (isEnum) {
    plew_write((PlewString){"data.", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), vStart, vLen);
    plew_write((PlewString){".", 1});
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){"; if (__bp) { long long* __brc = ((long long*)__bp) - 1; if ((--(*__brc)) == 0) {", 81});
    if (pointeeNeedsRelease_c_Comp_f_FieldDef(&((*c)), f)) {
    plew_write((PlewString){" ", 1});
    if (isGenericInst_c_Comp_ref_U64(&((*c)), f.ty)) {
    emitMangle_c_Comp_ref_U64(&((*c)), f.ty);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    }
    plew_write((PlewString){"_release(*__bp);", 16});
    }
    plew_write((PlewString){" free(__brc); } } }", 19});
}
void emitStructReleaseProto_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"void ", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s);\n", 5});
    StructDef_release(s);
}
void weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(Comp* c, PlewString obj, long long isEnum, uint64_t vStart, uint64_t vLen, FieldDef f) {
    plew_write(obj);
    if (isEnum) {
    plew_write((PlewString){".data.", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), vStart, vLen);
    plew_write((PlewString){".", 1});
    }
    else {
    plew_write((PlewString){".", 1});
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
}
void emitFieldAction_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64_mode_U64(Comp* c, FieldDef f, long long isEnum, uint64_t vStart, uint64_t vLen, uint64_t mode) {
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), f)) {
    if (mode == 2) {
    emitBoxedFieldRelease_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64(&((*c)), f, isEnum, vStart, vLen);
    }
    else {
    emitBoxedFieldRetain_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64(&((*c)), f, isEnum, vStart, vLen);
    }
    return;
    }
    if (f.tyIsArray) {
    if (mode == 0) {
    plew_write((PlewString){" ", 1});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"r", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){" = ", 3});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_copy(", 6});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    }
    else {
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), f.tyStart, f.tyLen);
    if (mode == 1) {
    plew_write((PlewString){"_share(", 7});
    }
    else {
    plew_write((PlewString){"_release(", 9});
    }
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    }
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), f.tyStart, f.tyLen, (PlewString){"RawBuffer", 9})) {
    if (mode == 2) {
    plew_write((PlewString){" plew_rawbuf_release((void*)", 28});
    }
    else {
    plew_write((PlewString){" plew_rawbuf_share((void*)", 26});
    }
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    return;
    }
    if (mode == 2) {
    if (typeIsUnique_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    if (structHasDeinit_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_deinit(", 8});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    }
    if (structNeedsRelease_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen)) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    plew_write((PlewString){"_release(", 9});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    }
    return;
    }
    }
    long long gen = 0;
    if (f.ty != 0) {
    gen = isGenericInst_c_Comp_ref_U64(&((*c)), f.ty);
    }
    long long needs = 0;
    if (mode == 2) {
    needs = fieldNeedsRelease_c_Comp_f_FieldDef(&((*c)), f);
    }
    else {
    needs = fieldNeedsCopy_c_Comp_f_FieldDef(&((*c)), f);
    }
    if (needs) {
    }
    else {
    return;
    }
    if (mode == 0) {
    plew_write((PlewString){" ", 1});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"r", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){" = ", 3});
    if (gen) {
    emitMangle_c_Comp_ref_U64(&((*c)), f.ty);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    }
    plew_write((PlewString){"_copy(", 6});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    }
    else {
    plew_write((PlewString){" ", 1});
    if (gen) {
    emitMangle_c_Comp_ref_U64(&((*c)), f.ty);
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.tyStart, f.tyLen);
    }
    if (mode == 1) {
    plew_write((PlewString){"_share(", 7});
    }
    else {
    plew_write((PlewString){"_release(", 9});
    }
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    }
}
long long variantHasAction_c_Comp_v_Variant_mode_U64(Comp* c, Variant v, uint64_t mode) {
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    uint64_t i = 0;
    while (i < (long long)((fs).count)) {
    if (mode == 2) {
    if (fieldNeedsRelease_c_Comp_f_FieldDef(&((*c)), Array_FieldDef_get(fs, (long long)(i)))) {
    { long long __ret881 = 1;
    Array_FieldDef_release(fs);
    return __ret881; }
    }
    }
    else {
    if (fieldNeedsCopy_c_Comp_f_FieldDef(&((*c)), Array_FieldDef_get(fs, (long long)(i)))) {
    { long long __ret882 = 1;
    Array_FieldDef_release(fs);
    return __ret882; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret883 = 0;
    Array_FieldDef_release(fs);
    return __ret883; }
    Array_FieldDef_release(fs);
}
void emitEnumCopyProto_c_Comp_ei_U64(Comp* c, uint64_t ei) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){"_copy(", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" s);\n", 5});
    EnumDef_release(e);
}
void emitEnumShareProto_c_Comp_ei_U64(Comp* c, uint64_t ei) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){"_share(", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" s);\n", 5});
    EnumDef_release(e);
}
void emitEnumReleaseProto_c_Comp_ei_U64(Comp* c, uint64_t ei) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    plew_write((PlewString){"void ", 5});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){"_release(", 9});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" s);\n", 5});
    EnumDef_release(e);
}
void emitEnumModeDef_c_Comp_ei_U64_mode_U64(Comp* c, uint64_t ei, uint64_t mode) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if (mode == 2) {
    plew_write((PlewString){"void ", 5});
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" ", 1});
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    if (mode == 0) {
    plew_write((PlewString){"_copy(", 6});
    }
    else {
    if (mode == 1) {
    plew_write((PlewString){"_share(", 7});
    }
    else {
    plew_write((PlewString){"_release(", 9});
    }
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" s) {", 5});
    if (mode == 0) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" r = s;", 7});
    }
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (variantHasAction_c_Comp_v_Variant_mode_U64(&((*c)), v, mode)) {
    plew_write((PlewString){" if (s.tag == ", 14});
    writeU64_n_U64(vi);
    plew_write((PlewString){") {", 3});
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    emitFieldAction_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64_mode_U64(&((*c)), Array_FieldDef_get(fs, (long long)(fi)), 1, v.nameStart, v.nameLen, mode);
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" }", 2});
    Array_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    if (mode == 2) {
    plew_write((PlewString){" }\n", 3});
    }
    else {
    plew_write((PlewString){" return ", 8});
    if (mode == 0) {
    plew_write((PlewString){"r", 1});
    }
    else {
    plew_write((PlewString){"s", 1});
    }
    plew_write((PlewString){"; }\n", 4});
    }
    Array_Variant_release(vars);
    EnumDef_release(e);
}
void emitStructModeDef_c_Comp_si_U64_mode_U64(Comp* c, uint64_t si, uint64_t mode) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if (mode == 2) {
    plew_write((PlewString){"void ", 5});
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" ", 1});
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    if (mode == 0) {
    plew_write((PlewString){"_copy(", 6});
    }
    else {
    if (mode == 1) {
    plew_write((PlewString){"_share(", 7});
    }
    else {
    plew_write((PlewString){"_release(", 9});
    }
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" s) {", 5});
    if (mode == 0) {
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" r = s;", 7});
    }
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    emitFieldAction_c_Comp_f_FieldDef_isEnum_Bool_vStart_U64_vLen_U64_mode_U64(&((*c)), Array_FieldDef_get(fields, (long long)(i)), 0, 0, 0, mode);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (mode == 2) {
    plew_write((PlewString){" }\n", 3});
    }
    else {
    plew_write((PlewString){" return ", 8});
    if (mode == 0) {
    plew_write((PlewString){"r", 1});
    }
    else {
    plew_write((PlewString){"s", 1});
    }
    plew_write((PlewString){"; }\n", 4});
    }
    Array_FieldDef_release(fields);
    StructDef_release(s);
}
void emitMonoModeProto_c_Comp_instRef_U64_mode_U64(Comp* c, uint64_t instRef, uint64_t mode) {
    if (mode == 2) {
    plew_write((PlewString){"void ", 5});
    }
    else {
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    }
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    if (mode == 0) {
    plew_write((PlewString){"_copy(", 6});
    }
    else {
    if (mode == 1) {
    plew_write((PlewString){"_share(", 7});
    }
    else {
    plew_write((PlewString){"_release(", 9});
    }
    }
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" s);\n", 5});
}
void emitMonoModeDef_c_Comp_instRef_U64_isEnum_Bool_mode_U64(Comp* c, uint64_t instRef, long long isEnum, uint64_t mode) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    Array_Bind params = Array_Bind_new();
    Array_Variant vars = Array_Variant_new();
    Array_FieldDef fields = Array_FieldDef_new();
    if (isEnum) {
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).count)) {
    Array_FieldDef_release(fields);
    Array_Variant_release(vars);
    Array_Bind_release(params);
    TypeRef_release(t);
    return;
    }
    params = Array_Bind_share(Array_EnumDef_get((*c).enums, (long long)(ei)).typeParams);
    vars = Array_Variant_share(Array_EnumDef_get((*c).enums, (long long)(ei)).variants);
    }
    else {
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).count)) {
    Array_FieldDef_release(fields);
    Array_Variant_release(vars);
    Array_Bind_release(params);
    TypeRef_release(t);
    return;
    }
    params = Array_Bind_share(Array_StructDef_get((*c).structs, (long long)(si)).typeParams);
    fields = Array_FieldDef_share(Array_StructDef_get((*c).structs, (long long)(si)).fields);
    }
    Array_Bind savedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedA = Array_U64_share((*c).curTypeArgs);
    (*c).curTypeParams = Array_Bind_share(params);
    (*c).curTypeArgs = Array_U64_share(t.args);
    if (mode == 2) {
    plew_write((PlewString){"void ", 5});
    }
    else {
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" ", 1});
    }
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    if (mode == 0) {
    plew_write((PlewString){"_copy(", 6});
    }
    else {
    if (mode == 1) {
    plew_write((PlewString){"_share(", 7});
    }
    else {
    plew_write((PlewString){"_release(", 9});
    }
    }
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" s) {", 5});
    if (mode == 0) {
    plew_write((PlewString){" ", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" r = s;", 7});
    }
    if (isEnum) {
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    long long any = 0;
    uint64_t ck = 0;
    while (ck < (long long)((fs).count)) {
    TypeInfo cti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, Array_Bind_share(params), Array_FieldDef_get(fs, (long long)(ck)).ty);
    if (mode == 2) {
    if (typeInfoNeedsRelease_c_Comp_ti_TypeInfo(&((*c)), cti)) {
    any = 1;
    }
    }
    else {
    if (typeInfoNeedsCopy_c_Comp_ti_TypeInfo(&((*c)), cti)) {
    any = 1;
    }
    }
    ck = ({ uint64_t __ov; if (__builtin_add_overflow((ck), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (any) {
    plew_write((PlewString){" if (s.tag == ", 14});
    writeU64_n_U64(vi);
    plew_write((PlewString){") {", 3});
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, Array_Bind_share(params), Array_FieldDef_get(fs, (long long)(fi)).ty);
    emitMonoFieldAction_c_Comp_ti_TypeInfo_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef_mode_U64(&((*c)), ti, 1, v.nameStart, v.nameLen, Array_FieldDef_get(fs, (long long)(fi)), mode);
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){" }", 2});
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(fs);
    Variant_release(v);
    }
    }
    else {
    uint64_t fi = 0;
    while (fi < (long long)((fields).count)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, Array_Bind_share(params), Array_FieldDef_get(fields, (long long)(fi)).ty);
    emitMonoFieldAction_c_Comp_ti_TypeInfo_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef_mode_U64(&((*c)), ti, 0, 0, 0, Array_FieldDef_get(fields, (long long)(fi)), mode);
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    if (mode == 2) {
    plew_write((PlewString){" }\n", 3});
    }
    else {
    plew_write((PlewString){" return ", 8});
    if (mode == 0) {
    plew_write((PlewString){"r", 1});
    }
    else {
    plew_write((PlewString){"s", 1});
    }
    plew_write((PlewString){"; }\n", 4});
    }
    (*c).curTypeParams = Array_Bind_share(savedP);
    (*c).curTypeArgs = Array_U64_share(savedA);
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    Array_FieldDef_release(fields);
    Array_Variant_release(vars);
    Array_Bind_release(params);
    TypeRef_release(t);
}
long long monoStructNeedsRelease_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).count)) {
    { long long __ret884 = 0;
    TypeRef_release(t);
    return __ret884; }
    }
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, Array_Bind_share(s.typeParams), Array_FieldDef_get(fields, (long long)(i)).ty);
    if (typeInfoNeedsRelease_c_Comp_ti_TypeInfo(&((*c)), ti)) {
    { long long __ret885 = 1;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret885; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret886 = 0;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret886; }
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
void emitMonoFieldAction_c_Comp_ti_TypeInfo_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef_mode_U64(Comp* c, TypeInfo ti, long long isEnum, uint64_t vStart, uint64_t vLen, FieldDef f, uint64_t mode) {
    long long needs = 0;
    if (mode == 2) {
    needs = typeInfoNeedsRelease_c_Comp_ti_TypeInfo(&((*c)), ti);
    }
    else {
    needs = typeInfoNeedsCopy_c_Comp_ti_TypeInfo(&((*c)), ti);
    }
    if (needs) {
    }
    else {
    return;
    }
    if (mode == 0) {
    plew_write((PlewString){" ", 1});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"r", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){" = ", 3});
    if (ti.kind == 3) {
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), ti.nameStart, ti.nameLen);
    }
    else {
    emitTypeInfoCName_c_Comp_ti_TypeInfo(&((*c)), ti);
    }
    plew_write((PlewString){"_copy(", 6});
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
    return;
    }
    plew_write((PlewString){" ", 1});
    if (ti.kind == 3) {
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), ti.nameStart, ti.nameLen);
    }
    else {
    emitTypeInfoCName_c_Comp_ti_TypeInfo(&((*c)), ti);
    }
    if (mode == 1) {
    plew_write((PlewString){"_share(", 7});
    }
    else {
    plew_write((PlewString){"_release(", 9});
    }
    weAccF_c_Comp_obj_String_isEnum_Bool_vStart_U64_vLen_U64_f_FieldDef(&((*c)), (PlewString){"s", 1}, isEnum, vStart, vLen, f);
    plew_write((PlewString){");", 2});
}
void emitTypeInfoCName_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.ref != 0) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ti.ref)) {
    emitMangle_c_Comp_ref_U64(&((*c)), ti.ref);
    return;
    }
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), ti.nameStart, ti.nameLen);
}
long long monoStructNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).count)) {
    { long long __ret887 = 0;
    TypeRef_release(t);
    return __ret887; }
    }
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, Array_Bind_share(s.typeParams), Array_FieldDef_get(fields, (long long)(i)).ty);
    if (typeInfoNeedsCopy_c_Comp_ti_TypeInfo(&((*c)), ti)) {
    { long long __ret888 = 1;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret888; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret889 = 0;
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret889; }
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
long long monoEnumNeedsCopy_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).count)) {
    { long long __ret890 = 0;
    TypeRef_release(t);
    return __ret890; }
    }
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Array_FieldDef fs = Array_FieldDef_share(Array_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    TypeInfo ti = substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(&((*c)), instRef, Array_Bind_share(e.typeParams), Array_FieldDef_get(fs, (long long)(fi)).ty);
    if (typeInfoNeedsCopy_c_Comp_ti_TypeInfo(&((*c)), ti)) {
    { long long __ret891 = 1;
    Array_FieldDef_release(fs);
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret891; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(fs);
    }
    { long long __ret892 = 0;
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret892; }
    Array_Variant_release(vars);
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
    if (isPlaceExpr_c_Comp_id_U64(&((*c)), exprId)) {
    if (enumNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), fallStart, fallLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), fallStart, fallLen);
    plew_write((PlewString){"_share(", 7});
    genExpr_c_Comp_id_U64(&((*c)), exprId);
    plew_write((PlewString){")", 1});
    return;
    }
    }
    genStructValue_c_Comp_exprId_U64_structStart_U64_structLen_U64(&((*c)), exprId, fallStart, fallLen);
}
void genStructDef_c_Comp_si_U64(Comp* c, uint64_t si) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    plew_write((PlewString){"struct ", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), s.nameStart, s.nameLen);
    plew_write((PlewString){" {\n", 3});
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    FieldDef f = Array_FieldDef_get(fields, (long long)(i));
    plew_write((PlewString){"    ", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.ty, f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), f)) {
    plew_write((PlewString){"*", 1});
    }
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";\n", 2});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"};\n", 3});
    Array_FieldDef_release(fields);
    StructDef_release(s);
}
void writeFnSelector_c_Comp_f_Func(Comp* c, Func f) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    Array_Param params = Array_Param_share(f.params);
    uint64_t i = 0;
    while (i < (long long)((params).count)) {
    Param p = Array_Param_get(params, (long long)(i));
    plew_write((PlewString){"_", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
    plew_write((PlewString){"_", 1});
    if (p.tyIsArray) {
    plew_write((PlewString){"A", 1});
    }
    long long resolved = 0;
    if (f.hasRecv) {
    }
    else {
    uint64_t k = 0;
    while (k < (long long)(((*c).curTypeParams).count)) {
    Bind tp = Array_Bind_get((*c).curTypeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.tyStart, p.tyLen, tp.nameStart, tp.nameLen)) {
    emitMangle_c_Comp_ref_U64(&((*c)), Array_U64_get((*c).curTypeArgs, (long long)(k)));
    resolved = 1;
    k = (long long)(((*c).curTypeParams).count);
    }
    else {
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    if (resolved) {
    }
    else {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.tyStart, p.tyLen);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Param_release(params);
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
    if (f.hasRecv) {
    if ((long long)((f.typeParams).count) > 0) {
    if ((long long)(((*c).curTypeArgs).count) > 0) {
    uint64_t rcount = 0;
    if ((*c).curRecvInstRef != 0) {
    rcount = recvParamCount_c_Comp_nameStart_U64_nameLen_U64(&((*c)), f.recvStart, f.recvLen);
    }
    writeMethodInstSuffixFrom_c_Comp_typeArgs_AU64_startIdx_U64(&((*c)), Array_U64_share((*c).curTypeArgs), rcount);
    }
    }
    }
    plew_write((PlewString){"(", 1});
    Array_Param params = Array_Param_share(f.params);
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
    while (i < (long long)((params).count)) {
    plew_write((PlewString){", ", 2});
    Param p = Array_Param_get(params, (long long)(i));
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
    if ((long long)((params).count) == 0) {
    plew_write((PlewString){"void", 4});
    }
    else {
    uint64_t i = 0;
    while (i < (long long)((params).count)) {
    if (i > 0) {
    plew_write((PlewString){", ", 2});
    }
    Param p = Array_Param_get(params, (long long)(i));
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
    Array_Param_release(params);
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
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
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
    if (f.hasRecv) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), f.recvStart, f.recvLen, (*c).curRecvInstRef);
    }
    else {
    clearSelfItemEnv_c_Comp(&((*c)));
    }
    (*c).curBranchBase = 0;
    (*c).locals = Array_Local_new();
    Array_Param params = Array_Param_share(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((params).count)) {
    Param p = Array_Param_get(params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, p.isMove);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genSignature_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){" {\n", 3});
    if (isMain) {
    plew_write((PlewString){"    plew_argc = argc; plew_argv = argv;\n", 40});
    }
    genBlock_c_Comp_id_U64(&((*c)), f.body);
    emitScopeDrops_c_Comp_mark_U64_exclIdx_U64(&((*c)), 0, (long long)(((*c).locals).count));
    emitSelfDeinit_c_Comp(&((*c)));
    if (isMain) {
    plew_write((PlewString){"    return 0;\n", 14});
    }
    plew_write((PlewString){"}\n", 2});
    clearSelfItemEnv_c_Comp(&((*c)));
    Array_Param_release(params);
    Func_release(f);
}
void genClosure_c_Comp_id_U64_proto_Bool(Comp* c, uint64_t id, long long proto) {
    {
    Expr _m893 = Array_Expr_get((*c).exprs, (long long)(id));
    if (_m893.tag == 17) {
        Array_Param params = _m893.data.Closure.params;
        (void)params;
        long long hasRet = _m893.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m893.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m893.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m893.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m893.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m893.data.Closure.body;
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
    if ((long long)((params).count) == 0) {
    }
    else {
    uint64_t i = 0;
    while (i < (long long)((params).count)) {
    plew_write((PlewString){", ", 2});
    Param p = Array_Param_get(params, (long long)(i));
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
    (*c).locals = Array_Local_new();
    uint64_t pj = 0;
    while (pj < (long long)((params).count)) {
    Param p2 = Array_Param_get(params, (long long)(pj));
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
    while (i < (long long)(((*c).fnThunks).count)) {
    if (Array_U64_get((*c).fnThunks, (long long)(i)) == fi) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_append_value_T(&((*c).fnThunks), fi);
}
void collectFnThunks_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).exprs).count)) {
    {
    Expr _m894 = Array_Expr_get((*c).exprs, (long long)(i));
    if (_m894.tag == 1) {
        uint64_t start = _m894.data.Ident.start;
        (void)start;
        uint64_t len = _m894.data.Ident.len;
        (void)len;
    uint64_t fvi = firstFuncByName_c_Comp_nameStart_U64_nameLen_U64(&((*c)), start, len);
    if (fvi < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fvi)));
    if (f.hasRecv) {
    }
    else {
    if (f.isAssoc) {
    }
    else {
    if ((long long)((f.typeParams).count) > 0) {
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
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRet) {
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.retTy, f.retStart, f.retLen, f.retIsArray);
    plew_write((PlewString){" ", 1});
    }
    else {
    plew_write((PlewString){"void ", 5});
    }
    writeFnSelector_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"__thunk(void* __env", 19});
    Array_Param params = Array_Param_share(f.params);
    uint64_t i = 0;
    while (i < (long long)((params).count)) {
    plew_write((PlewString){", ", 2});
    Param p = Array_Param_get(params, (long long)(i));
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
    Array_Param_release(params);
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
    while (j < (long long)((params).count)) {
    if (j > 0) {
    plew_write((PlewString){", ", 2});
    }
    Param p2 = Array_Param_get(params, (long long)(j));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p2.nameStart, p2.nameLen);
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"); }\n", 5});
    Array_Param_release(params);
    Func_release(f);
}
void emitThunks_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t i = 0;
    while (i < (long long)(((*c).fnThunks).count)) {
    genThunk_c_Comp_fi_U64_proto_Bool(&((*c)), Array_U64_get((*c).fnThunks, (long long)(i)), proto);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long closureHasCaptures_c_Comp_id_U64(Comp* c, uint64_t id) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).count)) {
    if (Array_CaptureEntry_get((*c).captures, (long long)(i)).closureId == id) {
    { long long __ret895 = 1;
    return __ret895; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret896 = 0;
    return __ret896; }
}
long long isBoxedLocalAt_c_Comp_nameStart_U64(Comp* c, uint64_t nameStart) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).count)) {
    CaptureEntry e = Array_CaptureEntry_get((*c).captures, (long long)(i));
    if (e.boxed) {
    if (e.nameStart == nameStart) {
    { long long __ret897 = 1;
    return __ret897; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret898 = 0;
    return __ret898; }
}
long long isBoxedCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(Comp* c, uint64_t closureId, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).count)) {
    CaptureEntry e = Array_CaptureEntry_get((*c).captures, (long long)(i));
    if (e.closureId == closureId) {
    if (e.boxed) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    { long long __ret899 = 1;
    return __ret899; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret900 = 0;
    return __ret900; }
}
long long isCaptureOf_c_Comp_closureId_U64_start_U64_len_U64(Comp* c, uint64_t closureId, uint64_t start, uint64_t len) {
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).count)) {
    CaptureEntry e = Array_CaptureEntry_get((*c).captures, (long long)(i));
    if (e.closureId == closureId) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, start, len)) {
    { long long __ret901 = 1;
    return __ret901; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret902 = 0;
    return __ret902; }
}
void emitClosureEnvStruct_c_Comp_id_U64(Comp* c, uint64_t id) {
    plew_write((PlewString){"typedef struct { ", 17});
    uint64_t j = 0;
    while (j < (long long)(((*c).captures).count)) {
    CaptureEntry e = Array_CaptureEntry_get((*c).captures, (long long)(j));
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
    while (j < (long long)(((*c).captures).count)) {
    CaptureEntry e = Array_CaptureEntry_get((*c).captures, (long long)(j));
    if (e.closureId == id) {
    if (e.boxed) {
    plew_write((PlewString){"    plew_arc_release(((long long*)e->", 37});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){") - 1);\n", 8});
    }
    else {
    if (e.isArray) {
    plew_write((PlewString){"    Array_", 10});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.tyStart, e.tyLen);
    plew_write((PlewString){"_release(e->", 12});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){");\n", 3});
    }
    else {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), e.tyStart, e.tyLen, (PlewString){"Ref", 3})) {
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
    while (i < (long long)(((*c).exprs).count)) {
    {
    Expr _m903 = Array_Expr_get((*c).exprs, (long long)(i));
    if (_m903.tag == 17) {
        Array_Param params = _m903.data.Closure.params;
        (void)params;
        long long hasRet = _m903.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m903.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m903.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m903.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m903.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m903.data.Closure.body;
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
    while (i < (long long)(((*c).exprs).count)) {
    {
    Expr _m904 = Array_Expr_get((*c).exprs, (long long)(i));
    if (_m904.tag == 17) {
        Array_Param params = _m904.data.Closure.params;
        (void)params;
        long long hasRet = _m904.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m904.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m904.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m904.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m904.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m904.data.Closure.body;
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
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    plew_write((PlewString){"struct ", 7});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), e.nameStart, e.nameLen);
    plew_write((PlewString){" {\n", 3});
    plew_write((PlewString){"    long long tag;\n", 19});
    plew_write((PlewString){"    union {\n", 12});
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    plew_write((PlewString){"        struct {", 16});
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    if ((long long)((fs).count) == 0) {
    plew_write((PlewString){" char _u; ", 10});
    }
    else {
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef f = Array_FieldDef_get(fs, (long long)(fi));
    plew_write((PlewString){" ", 1});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), f.ty, f.tyStart, f.tyLen, f.tyIsArray);
    plew_write((PlewString){" ", 1});
    if (fieldIsBoxed_c_Comp_f_FieldDef(&((*c)), f)) {
    plew_write((PlewString){"*", 1});
    }
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
    Array_FieldDef_release(fs);
    Variant_release(v);
    }
    plew_write((PlewString){"    } data;\n", 12});
    plew_write((PlewString){"};\n", 3});
    Array_Variant_release(vars);
    EnumDef_release(e);
}
uint64_t genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(i)));
    if ((long long)((s.typeParams).count) > 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), s.nameStart, s.nameLen, nameStart, nameLen)) {
    { uint64_t __ret905 = i;
    StructDef_release(s);
    return __ret905; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    { uint64_t __ret906 = (long long)(((*c).structs).count);
    return __ret906; }
}
uint64_t genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(i)));
    if ((long long)((e.typeParams).count) > 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, nameStart, nameLen)) {
    { uint64_t __ret907 = i;
    EnumDef_release(e);
    return __ret907; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret908 = (long long)(((*c).enums).count);
    return __ret908; }
}
long long isGenericInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret909 = 0;
    return __ret909; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).count) == 0) {
    { long long __ret910 = 0;
    TypeRef_release(t);
    return __ret910; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    TypeRef a0 = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(Array_U64_get(t.args, (long long)(0)))));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), a0.nameStart, a0.nameLen, (PlewString){"U8", 2})) {
    { long long __ret911 = 0;
    TypeRef_release(a0);
    TypeRef_release(t);
    return __ret911; }
    }
    TypeRef_release(a0);
    }
    if (genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).structs).count)) {
    { long long __ret912 = 1;
    TypeRef_release(t);
    return __ret912; }
    }
    { long long __ret913 = (genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).count));
    TypeRef_release(t);
    return __ret913; }
    TypeRef_release(t);
}
long long isFnType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret914 = 0;
    return __ret914; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    { long long __ret915 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"fn", 2});
    TypeRef_release(t);
    return __ret915; }
    TypeRef_release(t);
}
long long isRefInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret916 = 0;
    return __ret916; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).count) != 1) {
    { long long __ret917 = 0;
    TypeRef_release(t);
    return __ret917; }
    }
    { long long __ret918 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Ref", 3});
    TypeRef_release(t);
    return __ret918; }
    TypeRef_release(t);
}
long long isRawBufInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret919 = 0;
    return __ret919; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).count) != 1) {
    { long long __ret920 = 0;
    TypeRef_release(t);
    return __ret920; }
    }
    { long long __ret921 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"RawBuffer", 9});
    TypeRef_release(t);
    return __ret921; }
    TypeRef_release(t);
}
long long isPromiseInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret922 = 0;
    return __ret922; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    { long long __ret923 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Promise", 7});
    TypeRef_release(t);
    return __ret923; }
    TypeRef_release(t);
}
long long isIndirectContainer_c_Comp_nStart_U64_nLen_U64(Comp* c, uint64_t nStart, uint64_t nLen) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nStart, nLen, (PlewString){"Array", 5})) {
    { long long __ret924 = 1;
    return __ret924; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nStart, nLen, (PlewString){"RawBuffer", 9})) {
    { long long __ret925 = 1;
    return __ret925; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nStart, nLen, (PlewString){"Ref", 3})) {
    { long long __ret926 = 1;
    return __ret926; }
    }
    { long long __ret927 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nStart, nLen, (PlewString){"WeakRef", 7});
    return __ret927; }
}
long long isTransparentContainer_c_Comp_nStart_U64_nLen_U64(Comp* c, uint64_t nStart, uint64_t nLen) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nStart, nLen, (PlewString){"Optional", 8})) {
    { long long __ret928 = 1;
    return __ret928; }
    }
    { long long __ret929 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nStart, nLen, (PlewString){"Result", 6});
    return __ret929; }
}
uint64_t concreteEnumIndex_c_Comp_nStart_U64_nLen_U64(Comp* c, uint64_t nStart, uint64_t nLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(i)));
    if ((long long)((e.typeParams).count) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), e.nameStart, e.nameLen, nStart, nLen)) {
    { uint64_t __ret930 = i;
    EnumDef_release(e);
    return __ret930; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    { uint64_t __ret931 = (long long)(((*c).enums).count);
    return __ret931; }
}
long long containsU64_xs_AU64_v_U64(Array_U64 xs, uint64_t v) {
    uint64_t i = 0;
    while (i < (long long)((xs).count)) {
    if (Array_U64_get(xs, (long long)(i)) == v) {
    { long long __ret932 = 1;
    return __ret932; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret933 = 0;
    return __ret933; }
}
long long nameReachesOwner_c_Comp_nStart_U64_nLen_U64_args_AU64_tStart_U64_tLen_U64_visited_AU64(Comp* c, uint64_t nStart, uint64_t nLen, Array_U64 args, uint64_t tStart, uint64_t tLen, Array_U64* visited) {
    if (isIndirectContainer_c_Comp_nStart_U64_nLen_U64(&((*c)), nStart, nLen)) {
    { long long __ret934 = 0;
    return __ret934; }
    }
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), nStart, nLen, tStart, tLen)) {
    { long long __ret935 = 1;
    return __ret935; }
    }
    if (isTransparentContainer_c_Comp_nStart_U64_nLen_U64(&((*c)), nStart, nLen)) {
    uint64_t ai = 0;
    while (ai < (long long)((args).count)) {
    if (typeRefReachesOwner_c_Comp_ref_U64_tStart_U64_tLen_U64_visited_AU64(&((*c)), Array_U64_get(args, (long long)(ai)), tStart, tLen, &((*visited)))) {
    { long long __ret936 = 1;
    return __ret936; }
    }
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret937 = 0;
    return __ret937; }
    }
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), nStart, nLen);
    if (si < (long long)(((*c).structs).count)) {
    uint64_t key = Array_StructDef_get((*c).structs, (long long)(si)).nameStart;
    if (containsU64_xs_AU64_v_U64(Array_U64_share((*visited)), key)) {
    { long long __ret938 = 0;
    return __ret938; }
    }
    Array_U64_append_value_T(&((*visited)), key);
    Array_FieldDef fields = Array_FieldDef_share(Array_StructDef_get((*c).structs, (long long)(si)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fields).count)) {
    if (fieldReachesOwner_c_Comp_f_FieldDef_tStart_U64_tLen_U64_visited_AU64(&((*c)), Array_FieldDef_get(fields, (long long)(fi)), tStart, tLen, &((*visited)))) {
    { long long __ret939 = 1;
    Array_FieldDef_release(fields);
    return __ret939; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret940 = 0;
    Array_FieldDef_release(fields);
    return __ret940; }
    Array_FieldDef_release(fields);
    }
    uint64_t ei = concreteEnumIndex_c_Comp_nStart_U64_nLen_U64(&((*c)), nStart, nLen);
    if (ei < (long long)(((*c).enums).count)) {
    uint64_t key = Array_EnumDef_get((*c).enums, (long long)(ei)).nameStart;
    if (containsU64_xs_AU64_v_U64(Array_U64_share((*visited)), key)) {
    { long long __ret941 = 0;
    return __ret941; }
    }
    Array_U64_append_value_T(&((*visited)), key);
    Array_Variant vars = Array_Variant_share(Array_EnumDef_get((*c).enums, (long long)(ei)).variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Array_FieldDef vf = Array_FieldDef_share(Array_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fj = 0;
    while (fj < (long long)((vf).count)) {
    if (fieldReachesOwner_c_Comp_f_FieldDef_tStart_U64_tLen_U64_visited_AU64(&((*c)), Array_FieldDef_get(vf, (long long)(fj)), tStart, tLen, &((*visited)))) {
    { long long __ret942 = 1;
    Array_FieldDef_release(vf);
    Array_Variant_release(vars);
    return __ret942; }
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(vf);
    }
    { long long __ret943 = 0;
    Array_Variant_release(vars);
    return __ret943; }
    Array_Variant_release(vars);
    }
    uint64_t gi = 0;
    while (gi < (long long)((args).count)) {
    if (typeRefReachesOwner_c_Comp_ref_U64_tStart_U64_tLen_U64_visited_AU64(&((*c)), Array_U64_get(args, (long long)(gi)), tStart, tLen, &((*visited)))) {
    { long long __ret944 = 1;
    return __ret944; }
    }
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret945 = 0;
    return __ret945; }
}
long long typeRefReachesOwner_c_Comp_ref_U64_tStart_U64_tLen_U64_visited_AU64(Comp* c, uint64_t ref, uint64_t tStart, uint64_t tLen, Array_U64* visited) {
    if (ref == 0) {
    { long long __ret946 = 0;
    return __ret946; }
    }
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret947 = 0;
    return __ret947; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    { long long __ret948 = nameReachesOwner_c_Comp_nStart_U64_nLen_U64_args_AU64_tStart_U64_tLen_U64_visited_AU64(&((*c)), t.nameStart, t.nameLen, Array_U64_share(t.args), tStart, tLen, &((*visited)));
    TypeRef_release(t);
    return __ret948; }
    TypeRef_release(t);
}
long long fieldReachesOwner_c_Comp_f_FieldDef_tStart_U64_tLen_U64_visited_AU64(Comp* c, FieldDef f, uint64_t tStart, uint64_t tLen, Array_U64* visited) {
    if (f.tyIsArray) {
    { long long __ret949 = 0;
    return __ret949; }
    }
    if (f.ty != 0) {
    { long long __ret950 = typeRefReachesOwner_c_Comp_ref_U64_tStart_U64_tLen_U64_visited_AU64(&((*c)), f.ty, tStart, tLen, &((*visited)));
    return __ret950; }
    }
    Array_U64 noArgs = Array_U64_new();
    { long long __ret951 = nameReachesOwner_c_Comp_nStart_U64_nLen_U64_args_AU64_tStart_U64_tLen_U64_visited_AU64(&((*c)), f.tyStart, f.tyLen, Array_U64_share(noArgs), tStart, tLen, &((*visited)));
    Array_U64_release(noArgs);
    return __ret951; }
    Array_U64_release(noArgs);
}
long long fieldIsBoxed_c_Comp_f_FieldDef(Comp* c, FieldDef f) {
    { long long __ret952 = containsU64_xs_AU64_v_U64(Array_U64_share((*c).boxedFields), f.nameStart);
    return __ret952; }
}
FieldDef noField(void) {
    { FieldDef __ret953 = (FieldDef){.nameStart = 0, .nameLen = 0, .tyStart = 0, .tyLen = 0, .tyIsArray = 0, .ty = 0, .isMut = 0, .hasDefault = 0, .defaultVal = 0, .vis = 0};
    return __ret953; }
}
FieldDef findFieldDef_c_Comp_typeStart_U64_typeLen_U64_variantStart_U64_variantLen_U64_isEnum_Bool_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t typeStart, uint64_t typeLen, uint64_t variantStart, uint64_t variantLen, long long isEnum, uint64_t fieldStart, uint64_t fieldLen) {
    if (isEnum) {
    uint64_t ei = concreteEnumIndex_c_Comp_nStart_U64_nLen_U64(&((*c)), typeStart, typeLen);
    if (ei >= (long long)(((*c).enums).count)) {
    { FieldDef __ret954 = noField();
    return __ret954; }
    }
    Array_Variant vars = Array_Variant_share(Array_EnumDef_get((*c).enums, (long long)(ei)).variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    uint64_t fj = 0;
    while (fj < (long long)((fs).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_FieldDef_get(fs, (long long)(fj)).nameStart, Array_FieldDef_get(fs, (long long)(fj)).nameLen, fieldStart, fieldLen)) {
    { FieldDef __ret955 = Array_FieldDef_get(fs, (long long)(fj));
    Array_FieldDef_release(fs);
    Variant_release(v);
    Array_Variant_release(vars);
    return __ret955; }
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { FieldDef __ret956 = noField();
    Array_Variant_release(vars);
    return __ret956; }
    Array_Variant_release(vars);
    }
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), typeStart, typeLen);
    if (si >= (long long)(((*c).structs).count)) {
    { FieldDef __ret957 = noField();
    return __ret957; }
    }
    Array_FieldDef fs = Array_FieldDef_share(Array_StructDef_get((*c).structs, (long long)(si)).fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_FieldDef_get(fs, (long long)(fi)).nameStart, Array_FieldDef_get(fs, (long long)(fi)).nameLen, fieldStart, fieldLen)) {
    { FieldDef __ret958 = Array_FieldDef_get(fs, (long long)(fi));
    Array_FieldDef_release(fs);
    return __ret958; }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { FieldDef __ret959 = noField();
    Array_FieldDef_release(fs);
    return __ret959; }
    Array_FieldDef_release(fs);
}
void genBoxCell_c_Comp_fd_FieldDef_valueId_U64(Comp* c, FieldDef fd, uint64_t valueId) {
    uint64_t t = (*c).tmp;
    (*c).tmp = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).tmp), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    plew_write((PlewString){"({ ", 3});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), fd.ty, fd.tyStart, fd.tyLen, 0);
    plew_write((PlewString){"* __box", 7});
    writeU64_n_U64(t);
    plew_write((PlewString){" = (", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), fd.ty, fd.tyStart, fd.tyLen, 0);
    plew_write((PlewString){"*)plew_arc_alloc(sizeof(", 24});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), fd.ty, fd.tyStart, fd.tyLen, 0);
    plew_write((PlewString){")); *__box", 10});
    writeU64_n_U64(t);
    plew_write((PlewString){" = (", 4});
    uint64_t savedRet = (*c).curRetTy;
    (*c).curRetTy = fd.ty;
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), valueId, fd.ty, fd.tyStart, fd.tyLen, 0);
    (*c).curRetTy = savedRet;
    plew_write((PlewString){"); __box", 8});
    writeU64_n_U64(t);
    plew_write((PlewString){"; })", 4});
}
void markBoxedFields_c_Comp(Comp* c) {
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if ((long long)((s.typeParams).count) == 0) {
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fields).count)) {
    FieldDef f = Array_FieldDef_get(fields, (long long)(fi));
    Array_U64 visited = Array_U64_new();
    if (fieldReachesOwner_c_Comp_f_FieldDef_tStart_U64_tLen_U64_visited_AU64(&((*c)), f, s.nameStart, s.nameLen, &(visited))) {
    Array_U64_append_value_T(&((*c).boxedFields), f.nameStart);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_U64_release(visited);
    }
    Array_FieldDef_release(fields);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if ((long long)((e.typeParams).count) == 0) {
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Array_FieldDef vf = Array_FieldDef_share(Array_Variant_get(vars, (long long)(vi)).fields);
    uint64_t fj = 0;
    while (fj < (long long)((vf).count)) {
    FieldDef f = Array_FieldDef_get(vf, (long long)(fj));
    Array_U64 visited = Array_U64_new();
    if (fieldReachesOwner_c_Comp_f_FieldDef_tStart_U64_tLen_U64_visited_AU64(&((*c)), f, e.nameStart, e.nameLen, &(visited))) {
    Array_U64_append_value_T(&((*c).boxedFields), f.nameStart);
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_U64_release(visited);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(vf);
    }
    Array_Variant_release(vars);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
}
long long isGenericEnumInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret960 = 0;
    return __ret960; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).count) == 0) {
    { long long __ret961 = 0;
    TypeRef_release(t);
    return __ret961; }
    }
    { long long __ret962 = (genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen) < (long long)(((*c).enums).count));
    TypeRef_release(t);
    return __ret962; }
    TypeRef_release(t);
}
long long typeRefEq_c_Comp_a_U64_b_U64(Comp* c, uint64_t a, uint64_t b) {
    if (a == b) {
    { long long __ret963 = 1;
    return __ret963; }
    }
    TypeRef ta = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(a)));
    TypeRef tb = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(b)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ta.nameStart, ta.nameLen, tb.nameStart, tb.nameLen)) {
    }
    else {
    { long long __ret964 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret964; }
    }
    if ((long long)((ta.args).count) != (long long)((tb.args).count)) {
    { long long __ret965 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret965; }
    }
    uint64_t i = 0;
    while (i < (long long)((ta.args).count)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), Array_U64_get(ta.args, (long long)(i)), Array_U64_get(tb.args, (long long)(i)))) {
    }
    else {
    { long long __ret966 = 0;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret966; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret967 = 1;
    TypeRef_release(tb);
    TypeRef_release(ta);
    return __ret967; }
    TypeRef_release(tb);
    TypeRef_release(ta);
}
void emitMangle_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(resolveTy_c_Comp_tyRef_U64(&((*c)), ref))));
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), t.nameStart, t.nameLen);
    uint64_t i = 0;
    while (i < (long long)((t.args).count)) {
    plew_write((PlewString){"_", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(t);
}
void appendMangle_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(resolveTy_c_Comp_tyRef_U64(&((*c)), ref))));
    uint64_t j = 0;
    while (j < t.nameLen) {
    Array_U8_append_value_T(&((*c).bytes), Array_U8_get((*c).bytes, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((t.nameStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t i = 0;
    while (i < (long long)((t.args).count)) {
    Array_U8_append_value_T(&((*c).bytes), 95);
    appendMangle_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(t);
}
Bind appendMangleSpan_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    uint64_t start = (long long)(((*c).bytes).count);
    appendMangle_c_Comp_ref_U64(&((*c)), ref);
    uint64_t n = (long long)(((*c).bytes).count);
    { Bind __ret968 = (Bind){.nameStart = start, .nameLen = ({ uint64_t __ov; if (__builtin_sub_overflow((n), (start), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }), .fieldStart = ref, .fieldLen = 0};
    return __ret968; }
}
long long sameMangle_c_Comp_refA_U64_refB_U64(Comp* c, uint64_t refA, uint64_t refB) {
    uint64_t ra = resolveTy_c_Comp_tyRef_U64(&((*c)), refA);
    uint64_t rb = resolveTy_c_Comp_tyRef_U64(&((*c)), refB);
    if (ra >= (long long)(((*c).types).count)) {
    { long long __ret969 = 0;
    return __ret969; }
    }
    if (rb >= (long long)(((*c).types).count)) {
    { long long __ret970 = 0;
    return __ret970; }
    }
    TypeRef a = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ra)));
    TypeRef b = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(rb)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), a.nameStart, a.nameLen, b.nameStart, b.nameLen)) {
    }
    else {
    { long long __ret971 = 0;
    TypeRef_release(b);
    TypeRef_release(a);
    return __ret971; }
    }
    if ((long long)((a.args).count) != (long long)((b.args).count)) {
    { long long __ret972 = 0;
    TypeRef_release(b);
    TypeRef_release(a);
    return __ret972; }
    }
    uint64_t i = 0;
    while (i < (long long)((a.args).count)) {
    if (sameMangle_c_Comp_refA_U64_refB_U64(&((*c)), Array_U64_get(a.args, (long long)(i)), Array_U64_get(b.args, (long long)(i)))) {
    }
    else {
    { long long __ret973 = 0;
    TypeRef_release(b);
    TypeRef_release(a);
    return __ret973; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret974 = 1;
    TypeRef_release(b);
    TypeRef_release(a);
    return __ret974; }
    TypeRef_release(b);
    TypeRef_release(a);
}
long long isCompoundType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    uint64_t r = resolveTy_c_Comp_tyRef_U64(&((*c)), ref);
    if (r >= (long long)(((*c).types).count)) {
    { long long __ret975 = 0;
    return __ret975; }
    }
    { long long __ret976 = ((long long)((Array_TypeRef_get((*c).types, (long long)(r)).args).count) > 0);
    return __ret976; }
}
void emitConcreteCType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    uint64_t r = resolveTy_c_Comp_tyRef_U64(&((*c)), ref);
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(r)));
    if ((long long)((t.args).count) == 0) {
    genCElem_c_Comp_start_U64_len_U64(&((*c)), t.nameStart, t.nameLen);
    TypeRef_release(t);
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Ref", 3})) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(0)));
    plew_write((PlewString){"*", 1});
    TypeRef_release(t);
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"RawBuffer", 9})) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(0)));
    plew_write((PlewString){"*", 1});
    TypeRef_release(t);
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Promise", 7})) {
    plew_write((PlewString){"PlewPromise*", 12});
    TypeRef_release(t);
    return;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"fn", 2})) {
    plew_write((PlewString){"PlewClosure", 11});
    TypeRef_release(t);
    return;
    }
    emitMangle_c_Comp_ref_U64(&((*c)), r);
    TypeRef_release(t);
}
void emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(Comp* c, uint64_t ref, Array_Bind params, Array_U64 args) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    uint64_t pi = 0;
    while (pi < (long long)((params).count)) {
    Bind p = Array_Bind_get(params, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get(args, (long long)(pi)));
    TypeRef_release(t);
    return;
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    emitConcreteCType_c_Comp_ref_U64(&((*c)), ref);
    TypeRef_release(t);
}
uint64_t resolveTy_c_Comp_tyRef_U64(Comp* c, uint64_t tyRef) {
    if (tyRef >= (long long)(((*c).types).count)) {
    { uint64_t __ret977 = tyRef;
    return __ret977; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(tyRef)));
    if ((long long)((t.args).count) == 0) {
    if ((*c).curSelfRef != 0) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Self", 4})) {
    { uint64_t __ret978 = (*c).curSelfRef;
    TypeRef_release(t);
    return __ret978; }
    }
    }
    if ((*c).curItemRef != 0) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Item", 4})) {
    { uint64_t __ret979 = (*c).curItemRef;
    TypeRef_release(t);
    return __ret979; }
    }
    }
    uint64_t i = 0;
    while (i < (long long)(((*c).curTypeParams).count)) {
    Bind p = Array_Bind_get((*c).curTypeParams, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    { uint64_t __ret980 = Array_U64_get((*c).curTypeArgs, (long long)(i));
    TypeRef_release(t);
    return __ret980; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    { uint64_t __ret981 = tyRef;
    TypeRef_release(t);
    return __ret981; }
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
    if (isRawBufInst_c_Comp_ref_U64(&((*c)), tyRef)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), tyRef);
    return;
    }
    if (isPromiseInst_c_Comp_ref_U64(&((*c)), tyRef)) {
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
    uint64_t ni = 0;
    while (ni < (long long)(((*c).structs).count)) {
    if ((long long)((Array_StructDef_get((*c).structs, (long long)(ni)).typeParams).count) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_StructDef_get((*c).structs, (long long)(ni)).nameStart, Array_StructDef_get((*c).structs, (long long)(ni)).nameLen, start, len)) {
    { long long __ret982 = 0;
    return __ret982; }
    }
    }
    ni = ({ uint64_t __ov; if (__builtin_add_overflow((ni), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t nj = 0;
    while (nj < (long long)(((*c).enums).count)) {
    if ((long long)((Array_EnumDef_get((*c).enums, (long long)(nj)).typeParams).count) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_EnumDef_get((*c).enums, (long long)(nj)).nameStart, Array_EnumDef_get((*c).enums, (long long)(nj)).nameLen, start, len)) {
    { long long __ret983 = 0;
    return __ret983; }
    }
    }
    nj = ({ uint64_t __ov; if (__builtin_add_overflow((nj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    Array_Bind tp = Array_Bind_share(Array_StructDef_get((*c).structs, (long long)(si)).typeParams);
    uint64_t k = 0;
    while (k < (long long)((tp).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_Bind_get(tp, (long long)(k)).nameStart, Array_Bind_get(tp, (long long)(k)).nameLen, start, len)) {
    { long long __ret984 = 1;
    Array_Bind_release(tp);
    return __ret984; }
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_Bind_release(tp);
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    Array_Bind tp2 = Array_Bind_share(Array_EnumDef_get((*c).enums, (long long)(ei)).typeParams);
    uint64_t k2 = 0;
    while (k2 < (long long)((tp2).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_Bind_get(tp2, (long long)(k2)).nameStart, Array_Bind_get(tp2, (long long)(k2)).nameLen, start, len)) {
    { long long __ret985 = 1;
    Array_Bind_release(tp2);
    return __ret985; }
    }
    k2 = ({ uint64_t __ov; if (__builtin_add_overflow((k2), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_Bind_release(tp2);
    }
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).count)) {
    Array_Bind tp3 = Array_Bind_share(Array_Func_get((*c).funcs, (long long)(fi)).typeParams);
    uint64_t k3 = 0;
    while (k3 < (long long)((tp3).count)) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), Array_Bind_get(tp3, (long long)(k3)).nameStart, Array_Bind_get(tp3, (long long)(k3)).nameLen, start, len)) {
    { long long __ret986 = 1;
    Array_Bind_release(tp3);
    return __ret986; }
    }
    k3 = ({ uint64_t __ov; if (__builtin_add_overflow((k3), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_Bind_release(tp3);
    }
    { long long __ret987 = 0;
    return __ret987; }
}
long long tyRefIsGround_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { long long __ret988 = 1;
    return __ret988; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    if (isTypeParamName_c_Comp_start_U64_len_U64(&((*c)), t.nameStart, t.nameLen)) {
    { long long __ret989 = 0;
    TypeRef_release(t);
    return __ret989; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Self", 4})) {
    { long long __ret990 = 0;
    TypeRef_release(t);
    return __ret990; }
    }
    uint64_t i = 0;
    while (i < (long long)((t.args).count)) {
    if (tyRefIsGround_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(i)))) {
    }
    else {
    { long long __ret991 = 0;
    TypeRef_release(t);
    return __ret991; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret992 = 1;
    TypeRef_release(t);
    return __ret992; }
    TypeRef_release(t);
}
void ensureArrayElemDeps_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef) {
    if (elemRef == 0) {
    return;
    }
    uint64_t r = resolveTy_c_Comp_tyRef_U64(&((*c)), elemRef);
    if (r >= (long long)(((*c).types).count)) {
    return;
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(r)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((t.args).count) > 0) {
    registerArrayElemRef_c_Comp_elemRef_U64(&((*c)), Array_U64_get(t.args, (long long)(0)));
    }
    }
    TypeRef_release(t);
}
void registerArrayElemRef_c_Comp_elemRef_U64(Comp* c, uint64_t elemRef) {
    uint64_t re = resolveTy_c_Comp_tyRef_U64(&((*c)), elemRef);
    if (re >= (long long)(((*c).types).count)) {
    return;
    }
    ensureArrayElemDeps_c_Comp_elemRef_U64(&((*c)), re);
    uint64_t nStart = Array_TypeRef_get((*c).types, (long long)(re)).nameStart;
    uint64_t nLen = Array_TypeRef_get((*c).types, (long long)(re)).nameLen;
    uint64_t fRef = 0;
    if (isCompoundType_c_Comp_ref_U64(&((*c)), re)) {
    Bind mn = appendMangleSpan_c_Comp_ref_U64(&((*c)), re);
    nStart = mn.nameStart;
    nLen = mn.nameLen;
    fRef = re;
    }
    uint64_t i = 0;
    while (i < (long long)(((*c).arrayElems).count)) {
    Bind ae = Array_Bind_get((*c).arrayElems, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ae.nameStart, ae.nameLen, nStart, nLen)) {
    return;
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Bind_append_value_T(&((*c).arrayElems), (Bind){.nameStart = nStart, .nameLen = nLen, .fieldStart = fRef, .fieldLen = 0});
}
uint64_t groundTypeRef_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    { uint64_t __ret993 = ref;
    return __ret993; }
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).count) == 0) {
    { uint64_t __ret994 = resolveTy_c_Comp_tyRef_U64(&((*c)), ref);
    TypeRef_release(t);
    return __ret994; }
    }
    Array_U64 newArgs = Array_U64_new();
    long long changed = 0;
    uint64_t i = 0;
    while (i < (long long)((t.args).count)) {
    uint64_t g = groundTypeRef_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(i)));
    if (g == Array_U64_get(t.args, (long long)(i))) {
    }
    else {
    changed = 1;
    }
    Array_U64_append_value_T(&(newArgs), g);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (changed) {
    uint64_t idx = (long long)(((*c).types).count);
    Array_TypeRef_append_value_T(&((*c).types), (TypeRef){.nameStart = t.nameStart, .nameLen = t.nameLen, .args = Array_U64_share(newArgs)});
    { uint64_t __ret995 = idx;
    Array_U64_release(newArgs);
    TypeRef_release(t);
    return __ret995; }
    }
    { uint64_t __ret996 = ref;
    Array_U64_release(newArgs);
    TypeRef_release(t);
    return __ret996; }
    Array_U64_release(newArgs);
    TypeRef_release(t);
}
uint64_t groundUnderInst_c_Comp_instRef_U64_tyRef_U64(Comp* c, uint64_t instRef, uint64_t tyRef) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), instRef)) {
    }
    else {
    { uint64_t __ret997 = tyRef;
    return __ret997; }
    }
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), inst.nameStart, inst.nameLen);
    if (si >= (long long)(((*c).structs).count)) {
    { uint64_t __ret998 = tyRef;
    TypeRef_release(inst);
    return __ret998; }
    }
    StructDef sd = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if ((long long)((sd.typeParams).count) == (long long)((inst.args).count)) {
    }
    else {
    { uint64_t __ret999 = tyRef;
    StructDef_release(sd);
    TypeRef_release(inst);
    return __ret999; }
    }
    Array_Bind savedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedA = Array_U64_share((*c).curTypeArgs);
    (*c).curTypeParams = Array_Bind_share(sd.typeParams);
    (*c).curTypeArgs = Array_U64_share(inst.args);
    uint64_t g = groundTypeRef_c_Comp_ref_U64(&((*c)), tyRef);
    (*c).curTypeParams = Array_Bind_share(savedP);
    (*c).curTypeArgs = Array_U64_share(savedA);
    { uint64_t __ret1000 = g;
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    StructDef_release(sd);
    TypeRef_release(inst);
    return __ret1000; }
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    StructDef_release(sd);
    TypeRef_release(inst);
}
uint64_t simpleTypeRef_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    Array_U64 noArgs = Array_U64_new();
    uint64_t idx = (long long)(((*c).types).count);
    Array_TypeRef_append_value_T(&((*c).types), (TypeRef){.nameStart = nameStart, .nameLen = nameLen, .args = Array_U64_share(noArgs)});
    { uint64_t __ret1001 = idx;
    Array_U64_release(noArgs);
    return __ret1001; }
    Array_U64_release(noArgs);
}
uint64_t assocItemRef_c_Comp_recvStart_U64_recvLen_U64(Comp* c, uint64_t recvStart, uint64_t recvLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).assocBindings).count)) {
    AssocBinding ab = Array_AssocBinding_get((*c).assocBindings, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ab.recvStart, ab.recvLen, recvStart, recvLen)) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), ab.nameStart, ab.nameLen, (PlewString){"Item", 4})) {
    { uint64_t __ret1002 = ab.ty;
    return __ret1002; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret1003 = 0;
    return __ret1003; }
}
void setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(Comp* c, uint64_t recvStart, uint64_t recvLen, uint64_t recvInstRef) {
    if (recvInstRef != 0) {
    (*c).curSelfRef = recvInstRef;
    }
    else {
    (*c).curSelfRef = simpleTypeRef_c_Comp_nameStart_U64_nameLen_U64(&((*c)), recvStart, recvLen);
    }
    uint64_t itemR0 = assocItemRef_c_Comp_recvStart_U64_recvLen_U64(&((*c)), recvStart, recvLen);
    if (itemR0 == 0) {
    (*c).curItemRef = 0;
    }
    else {
    if (recvInstRef != 0) {
    (*c).curItemRef = groundUnderInst_c_Comp_instRef_U64_tyRef_U64(&((*c)), recvInstRef, itemR0);
    }
    else {
    (*c).curItemRef = itemR0;
    }
    }
}
void clearSelfItemEnv_c_Comp(Comp* c) {
    (*c).curSelfRef = 0;
    (*c).curItemRef = 0;
}
void scanType_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (ref >= (long long)(((*c).types).count)) {
    return;
    }
    uint64_t ref_s1 = groundTypeRef_c_Comp_ref_U64(&((*c)), ref);
    if (ref_s1 >= (long long)(((*c).types).count)) {
    return;
    }
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref_s1)));
    uint64_t i = 0;
    while (i < (long long)((t.args).count)) {
    scanType_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((t.args).count) == 1) {
    registerArrayElemRef_c_Comp_elemRef_U64(&((*c)), Array_U64_get(t.args, (long long)(0)));
    }
    }
    if (isFnType_c_Comp_ref_U64(&((*c)), ref_s1)) {
    uint64_t fj = 0;
    long long seen = 0;
    while (fj < (long long)(((*c).fnTypes).count)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), Array_U64_get((*c).fnTypes, (long long)(fj)), ref_s1)) {
    seen = 1;
    }
    fj = ({ uint64_t __ov; if (__builtin_add_overflow((fj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (seen) {
    }
    else {
    Array_U64_append_value_T(&((*c).fnTypes), ref_s1);
    }
    }
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ref_s1)) {
    if (tyRefIsGround_c_Comp_ref_U64(&((*c)), ref_s1)) {
    uint64_t j = 0;
    while (j < (long long)(((*c).genInsts).count)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), Array_U64_get((*c).genInsts, (long long)(j)), ref_s1)) {
    TypeRef_release(t);
    return;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_append_value_T(&((*c).genInsts), ref_s1);
    scanGenInstFields_c_Comp_instRef_U64(&((*c)), ref_s1);
    }
    }
    TypeRef_release(t);
}
void scanGenInstFields_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    StructDef sd = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), sd.nameStart, sd.nameLen, inst.nameStart, inst.nameLen)) {
    if ((long long)((sd.typeParams).count) == (long long)((inst.args).count)) {
    if ((long long)((sd.typeParams).count) > 0) {
    Array_Bind savedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedA = Array_U64_share((*c).curTypeArgs);
    (*c).curTypeParams = Array_Bind_share(sd.typeParams);
    (*c).curTypeArgs = Array_U64_share(inst.args);
    Array_FieldDef fs = Array_FieldDef_share(sd.fields);
    uint64_t k = 0;
    while (k < (long long)((fs).count)) {
    scanType_c_Comp_ref_U64(&((*c)), Array_FieldDef_get(fs, (long long)(k)).ty);
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t mfi = 0;
    while (mfi < (long long)(((*c).funcs).count)) {
    Func mf = Func_share(Array_Func_get((*c).funcs, (long long)(mfi)));
    if (mf.hasRecv) {
    if (mf.isProvided) {
    }
    else {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), mf.recvStart, mf.recvLen, inst.nameStart, inst.nameLen)) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), inst.nameStart, inst.nameLen, instRef);
    if (mf.hasRet) {
    scanType_c_Comp_ref_U64(&((*c)), mf.retTy);
    }
    Array_Param mps = Array_Param_share(mf.params);
    uint64_t mpi = 0;
    while (mpi < (long long)((mps).count)) {
    scanType_c_Comp_ref_U64(&((*c)), Array_Param_get(mps, (long long)(mpi)).ty);
    mpi = ({ uint64_t __ov; if (__builtin_add_overflow((mpi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    clearSelfItemEnv_c_Comp(&((*c)));
    Array_Param_release(mps);
    }
    }
    }
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(mf);
    }
    (*c).curTypeParams = Array_Bind_share(savedP);
    (*c).curTypeArgs = Array_U64_share(savedA);
    Array_FieldDef_release(fs);
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    }
    }
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(sd);
    }
    TypeRef_release(inst);
}
void collectGenInsts_c_Comp(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    if ((long long)((f.typeParams).count) > 0) {
    }
    else {
    long long skipProvidedTemplate = 0;
    if (methodRecvIsTrait_c_Comp_f_Func(&((*c)), f)) {
    skipProvidedTemplate = 1;
    }
    if (f.isProvided) {
    if (genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), f.recvStart, f.recvLen) < (long long)(((*c).structs).count)) {
    skipProvidedTemplate = 1;
    }
    }
    if (skipProvidedTemplate) {
    }
    else {
    if (f.hasRecv) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), f.recvStart, f.recvLen, 0);
    }
    else {
    clearSelfItemEnv_c_Comp(&((*c)));
    }
    if (f.hasRet) {
    scanType_c_Comp_ref_U64(&((*c)), f.retTy);
    }
    Array_Param ps = Array_Param_share(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((ps).count)) {
    scanType_c_Comp_ref_U64(&((*c)), Array_Param_get(ps, (long long)(pi)).ty);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    clearSelfItemEnv_c_Comp(&((*c)));
    Array_Param_release(ps);
    }
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    uint64_t si = 0;
    while (si < (long long)(((*c).structs).count)) {
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    if ((long long)((s.typeParams).count) == 0) {
    Array_FieldDef fs = Array_FieldDef_share(s.fields);
    uint64_t k = 0;
    while (k < (long long)((fs).count)) {
    scanType_c_Comp_ref_U64(&((*c)), Array_FieldDef_get(fs, (long long)(k)).ty);
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    StructDef_release(s);
    }
    uint64_t ei = 0;
    while (ei < (long long)(((*c).enums).count)) {
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    if ((long long)((e.typeParams).count) == 0) {
    Array_Variant vs = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vs).count)) {
    Array_FieldDef vfs = Array_FieldDef_share(Array_Variant_get(vs, (long long)(vi)).fields);
    uint64_t k = 0;
    while (k < (long long)((vfs).count)) {
    scanType_c_Comp_ref_U64(&((*c)), Array_FieldDef_get(vfs, (long long)(k)).ty);
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_FieldDef_release(vfs);
    }
    Array_Variant_release(vs);
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    EnumDef_release(e);
    }
    uint64_t sti = 0;
    while (sti < (long long)(((*c).stmts).count)) {
    {
    Stmt _m1004 = Array_Stmt_get((*c).stmts, (long long)(sti));
    if (_m1004.tag == 0) {
        uint64_t ty = _m1004.data.Let.ty;
        (void)ty;
    scanType_c_Comp_ref_U64(&((*c)), ty);
    }
    else {
    }
    }
    sti = ({ uint64_t __ov; if (__builtin_add_overflow((sti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t xi = 0;
    while (xi < (long long)(((*c).exprs).count)) {
    {
    Expr _m1005 = Array_Expr_get((*c).exprs, (long long)(xi));
    if (_m1005.tag == 11) {
        uint64_t operand = _m1005.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m1005.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m1005.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m1005.data.Cast.ty;
        (void)ty;
    scanType_c_Comp_ref_U64(&((*c)), ty);
    }
    else if (_m1005.tag == 6) {
        uint64_t typeStart = _m1005.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m1005.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m1005.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m1005.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m1005.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m1005.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m1005.data.Make.fields;
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
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(ref)));
    if ((long long)((t.args).count) == 0) {
    { TypeInfo __ret1006 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), t.nameStart, t.nameLen, 0);
    TypeRef_release(t);
    return __ret1006; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), t.nameStart, t.nameLen, (PlewString){"Array", 5})) {
    TypeRef el = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(Array_U64_get(t.args, (long long)(0)))));
    { TypeInfo __ret1007 = typeInfoOfName_c_Comp_start_U64_len_U64_isArray_Bool(&((*c)), el.nameStart, el.nameLen, 1);
    TypeRef_release(el);
    TypeRef_release(t);
    return __ret1007; }
    TypeRef_release(el);
    }
    { TypeInfo __ret1008 = (TypeInfo){.kind = 2, .nameStart = t.nameStart, .nameLen = t.nameLen, .ref = ref};
    TypeRef_release(t);
    return __ret1008; }
    TypeRef_release(t);
}
TypeInfo iterableItemInfo_c_Comp_et_TypeInfo(Comp* c, TypeInfo et) {
    Array_Arg noArgs = Array_Arg_new();
    Bind itName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"iterator", 8}, 8);
    uint64_t imi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), et.nameStart, et.nameLen, itName.nameStart, itName.nameLen, Array_Arg_share(noArgs));
    uint64_t itRef = et.ref;
    uint64_t nrStart = et.nameStart;
    uint64_t nrLen = et.nameLen;
    if (imi == (long long)(((*c).funcs).count)) {
    }
    else {
    Func imf = Func_share(Array_Func_get((*c).funcs, (long long)(imi)));
    itRef = groundUnderInst_c_Comp_instRef_U64_tyRef_U64(&((*c)), et.ref, imf.retTy);
    nrStart = imf.retStart;
    nrLen = imf.retLen;
    Func_release(imf);
    }
    Bind nxName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"next", 4}, 4);
    uint64_t nmi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nrStart, nrLen, nxName.nameStart, nxName.nameLen, Array_Arg_share(noArgs));
    if (nmi == (long long)(((*c).funcs).count)) {
    { TypeInfo __ret1009 = scalarInfo();
    Array_Arg_release(noArgs);
    return __ret1009; }
    }
    Func nmf = Func_share(Array_Func_get((*c).funcs, (long long)(nmi)));
    uint64_t optRef = groundUnderInst_c_Comp_instRef_U64_tyRef_U64(&((*c)), itRef, nmf.retTy);
    if (optRef < (long long)(((*c).types).count)) {
    TypeRef ot = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(optRef)));
    if ((long long)((ot.args).count) > 0) {
    { TypeInfo __ret1010 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(ot.args, (long long)(0)));
    TypeRef_release(ot);
    Func_release(nmf);
    Array_Arg_release(noArgs);
    return __ret1010; }
    }
    TypeRef_release(ot);
    }
    { TypeInfo __ret1011 = scalarInfo();
    Func_release(nmf);
    Array_Arg_release(noArgs);
    return __ret1011; }
    Func_release(nmf);
    Array_Arg_release(noArgs);
}
TypeInfo substTypeInfo_c_Comp_instRef_U64_params_ABind_tyRef_U64(Comp* c, uint64_t instRef, Array_Bind params, uint64_t tyRef) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(tyRef)));
    uint64_t i = 0;
    while (i < (long long)((params).count)) {
    Bind p = Array_Bind_get(params, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, p.nameStart, p.nameLen)) {
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    if (i < (long long)((inst.args).count)) {
    { TypeInfo __ret1012 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(inst.args, (long long)(i)));
    TypeRef_release(inst);
    TypeRef_release(t);
    return __ret1012; }
    }
    TypeRef_release(inst);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret1013 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), tyRef);
    TypeRef_release(t);
    return __ret1013; }
    TypeRef_release(t);
}
TypeInfo genericFieldTypeInfo_c_Comp_instRef_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).count)) {
    { TypeInfo __ret1014 = scalarInfo();
    TypeRef_release(t);
    return __ret1014; }
    }
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    FieldDef fd = Array_FieldDef_get(fields, (long long)(i));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(fd.ty)));
    uint64_t pi = 0;
    while (pi < (long long)((s.typeParams).count)) {
    Bind p = Array_Bind_get(s.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    { TypeInfo __ret1015 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(pi)));
    TypeRef_release(ftr);
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret1015; }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), ftr.nameStart, ftr.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((ftr.args).count) > 0) {
    TypeRef elr = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(Array_U64_get(ftr.args, (long long)(0)))));
    uint64_t ej = 0;
    while (ej < (long long)((s.typeParams).count)) {
    Bind ep = Array_Bind_get(s.typeParams, (long long)(ej));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), elr.nameStart, elr.nameLen, ep.nameStart, ep.nameLen)) {
    uint64_t argRef = Array_U64_get(t.args, (long long)(ej));
    if (isCompoundType_c_Comp_ref_U64(&((*c)), argRef)) {
    Bind mn = appendMangleSpan_c_Comp_ref_U64(&((*c)), argRef);
    { TypeInfo __ret1016 = (TypeInfo){.kind = 3, .nameStart = mn.nameStart, .nameLen = mn.nameLen, .ref = 0};
    TypeRef_release(elr);
    TypeRef_release(ftr);
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret1016; }
    }
    TypeRef at = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(argRef)));
    { TypeInfo __ret1017 = (TypeInfo){.kind = 3, .nameStart = at.nameStart, .nameLen = at.nameLen, .ref = 0};
    TypeRef_release(at);
    TypeRef_release(elr);
    TypeRef_release(ftr);
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret1017; }
    TypeRef_release(at);
    }
    ej = ({ uint64_t __ov; if (__builtin_add_overflow((ej), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(elr);
    }
    }
    { TypeInfo __ret1018 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), fd.ty);
    TypeRef_release(ftr);
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret1018; }
    TypeRef_release(ftr);
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret1019 = scalarInfo();
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
    return __ret1019; }
    Array_FieldDef_release(fields);
    StructDef_release(s);
    TypeRef_release(t);
}
TypeInfo genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(Comp* c, uint64_t instRef, uint64_t variantStart, uint64_t variantLen, uint64_t fieldStart, uint64_t fieldLen) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).count)) {
    { TypeInfo __ret1020 = scalarInfo();
    TypeRef_release(t);
    return __ret1020; }
    }
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), v.nameStart, v.nameLen, variantStart, variantLen)) {
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef fd = Array_FieldDef_get(fs, (long long)(fi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), fd.nameStart, fd.nameLen, fieldStart, fieldLen)) {
    TypeRef ftr = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(fd.ty)));
    uint64_t pi = 0;
    while (pi < (long long)((e.typeParams).count)) {
    Bind p = Array_Bind_get(e.typeParams, (long long)(pi));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), ftr.nameStart, ftr.nameLen, p.nameStart, p.nameLen)) {
    { TypeInfo __ret1021 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), Array_U64_get(t.args, (long long)(pi)));
    TypeRef_release(ftr);
    Array_FieldDef_release(fs);
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret1021; }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { TypeInfo __ret1022 = typeInfoOfRef_c_Comp_ref_U64(&((*c)), fd.ty);
    TypeRef_release(ftr);
    Array_FieldDef_release(fs);
    Variant_release(v);
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret1022; }
    TypeRef_release(ftr);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_FieldDef_release(fs);
    }
    vi = ({ uint64_t __ov; if (__builtin_add_overflow((vi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Variant_release(v);
    }
    { TypeInfo __ret1023 = scalarInfo();
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
    return __ret1023; }
    Array_Variant_release(vars);
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
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t si = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (si >= (long long)(((*c).structs).count)) {
    TypeRef_release(t);
    return;
    }
    StructDef s = StructDef_share(Array_StructDef_get((*c).structs, (long long)(si)));
    Array_Bind savedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedA = Array_U64_share((*c).curTypeArgs);
    (*c).curTypeParams = Array_Bind_share(s.typeParams);
    (*c).curTypeArgs = Array_U64_share(t.args);
    plew_write((PlewString){"struct ", 7});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" {\n", 3});
    Array_FieldDef fields = Array_FieldDef_share(s.fields);
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    FieldDef f = Array_FieldDef_get(fields, (long long)(i));
    plew_write((PlewString){"    ", 4});
    emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(&((*c)), f.ty, Array_Bind_share(s.typeParams), Array_U64_share(t.args));
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.nameStart, f.nameLen);
    plew_write((PlewString){";\n", 2});
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"};\n", 3});
    (*c).curTypeParams = Array_Bind_share(savedP);
    (*c).curTypeArgs = Array_U64_share(savedA);
    Array_FieldDef_release(fields);
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    StructDef_release(s);
    TypeRef_release(t);
}
void emitMonoEnum_c_Comp_instRef_U64(Comp* c, uint64_t instRef) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    uint64_t ei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), t.nameStart, t.nameLen);
    if (ei >= (long long)(((*c).enums).count)) {
    TypeRef_release(t);
    return;
    }
    EnumDef e = EnumDef_share(Array_EnumDef_get((*c).enums, (long long)(ei)));
    plew_write((PlewString){"struct ", 7});
    emitMangle_c_Comp_ref_U64(&((*c)), instRef);
    plew_write((PlewString){" {\n    long long tag;\n    union {\n", 34});
    Array_Variant vars = Array_Variant_share(e.variants);
    uint64_t vi = 0;
    while (vi < (long long)((vars).count)) {
    Variant v = Variant_share(Array_Variant_get(vars, (long long)(vi)));
    plew_write((PlewString){"        struct {", 16});
    Array_FieldDef fs = Array_FieldDef_share(v.fields);
    if ((long long)((fs).count) == 0) {
    plew_write((PlewString){" char _u; ", 10});
    }
    else {
    uint64_t fi = 0;
    while (fi < (long long)((fs).count)) {
    FieldDef f = Array_FieldDef_get(fs, (long long)(fi));
    plew_write((PlewString){" ", 1});
    emitFieldCType_c_Comp_ref_U64_params_ABind_args_AU64(&((*c)), f.ty, Array_Bind_share(e.typeParams), Array_U64_share(t.args));
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
    Array_FieldDef_release(fs);
    Variant_release(v);
    }
    plew_write((PlewString){"    } data;\n};\n", 15});
    Array_Variant_release(vars);
    EnumDef_release(e);
    TypeRef_release(t);
}
long long methodMatchesInst_c_Comp_f_Func_instRef_U64(Comp* c, Func f, uint64_t instRef) {
    if (f.hasRecv) {
    }
    else {
    { long long __ret1024 = 0;
    return __ret1024; }
    }
    if ((long long)((f.typeParams).count) == 0) {
    { long long __ret1025 = 0;
    return __ret1025; }
    }
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), f.recvStart, f.recvLen, inst.nameStart, inst.nameLen)) {
    }
    else {
    { long long __ret1026 = 0;
    TypeRef_release(inst);
    return __ret1026; }
    }
    { long long __ret1027 = ((long long)((f.typeParams).count) == (long long)((inst.args).count));
    TypeRef_release(inst);
    return __ret1027; }
    TypeRef_release(inst);
}
void emitMonoMethod_c_Comp_fi_U64_instRef_U64_proto_Bool(Comp* c, uint64_t fi, uint64_t instRef, long long proto) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(instRef)));
    (*c).curRecvInstRef = instRef;
    (*c).curTypeParams = Array_Bind_share(f.typeParams);
    (*c).curTypeArgs = Array_U64_share(inst.args);
    if (proto) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), f.recvStart, f.recvLen, instRef);
    genSignature_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){";\n", 2});
    clearSelfItemEnv_c_Comp(&((*c)));
    }
    else {
    genFunc_c_Comp_fi_U64(&((*c)), fi);
    }
    Array_Bind noParams = Array_Bind_new();
    Array_U64 noArgs = Array_U64_new();
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = Array_Bind_share(noParams);
    (*c).curTypeArgs = Array_U64_share(noArgs);
    Array_U64_release(noArgs);
    Array_Bind_release(noParams);
    TypeRef_release(inst);
    Func_release(f);
}
uint64_t arrayInstRef_c_Comp_ae_Bind(Comp* c, Bind ae) {
    Bind arrName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"Array", 5}, 5);
    if (arrName.nameLen == 0) {
    { uint64_t __ret1028 = (long long)(((*c).types).count);
    return __ret1028; }
    }
    uint64_t elemRef = ae.fieldStart;
    if (elemRef == 0) {
    Array_U64 noArgs = Array_U64_new();
    elemRef = (long long)(((*c).types).count);
    Array_TypeRef_append_value_T(&((*c).types), (TypeRef){.nameStart = ae.nameStart, .nameLen = ae.nameLen, .args = Array_U64_share(noArgs)});
    Array_U64_release(noArgs);
    }
    Array_U64 args = ({ Array_U64 __a = Array_U64_new(); Array_U64_push(&__a, elemRef); __a; });
    uint64_t idx = (long long)(((*c).types).count);
    Array_TypeRef_append_value_T(&((*c).types), (TypeRef){.nameStart = arrName.nameStart, .nameLen = arrName.nameLen, .args = Array_U64_share(args)});
    { uint64_t __ret1029 = idx;
    Array_U64_release(args);
    return __ret1029; }
    Array_U64_release(args);
}
long long isRegisteredGenInst_c_Comp_ref_U64(Comp* c, uint64_t ref) {
    if (isGenericInst_c_Comp_ref_U64(&((*c)), ref)) {
    }
    else {
    { long long __ret1030 = 1;
    return __ret1030; }
    }
    uint64_t i = 0;
    while (i < (long long)(((*c).genInsts).count)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), Array_U64_get((*c).genInsts, (long long)(i)), ref)) {
    { long long __ret1031 = 1;
    return __ret1031; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret1032 = 0;
    return __ret1032; }
}
long long providedRetReachable_c_Comp_mf_Func_recvInstRef_U64(Comp* c, Func mf, uint64_t recvInstRef) {
    if (mf.hasRet) {
    }
    else {
    { long long __ret1033 = 1;
    return __ret1033; }
    }
    Array_Bind savedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedA = Array_U64_share((*c).curTypeArgs);
    if (recvInstRef != 0) {
    (*c).curTypeParams = Array_Bind_share(mf.typeParams);
    (*c).curTypeArgs = Array_U64_share(Array_TypeRef_get((*c).types, (long long)(recvInstRef)).args);
    }
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), mf.recvStart, mf.recvLen, recvInstRef);
    uint64_t gret = groundTypeRef_c_Comp_ref_U64(&((*c)), mf.retTy);
    clearSelfItemEnv_c_Comp(&((*c)));
    (*c).curTypeParams = Array_Bind_share(savedP);
    (*c).curTypeArgs = Array_U64_share(savedA);
    { long long __ret1034 = isRegisteredGenInst_c_Comp_ref_U64(&((*c)), gret);
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    return __ret1034; }
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
}
void emitArrayMethods_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t ei = 0;
    while (ei < (long long)(((*c).arrayElems).count)) {
    if (isTypeParamName_c_Comp_start_U64_len_U64(&((*c)), Array_Bind_get((*c).arrayElems, (long long)(ei)).nameStart, Array_Bind_get((*c).arrayElems, (long long)(ei)).nameLen)) {
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    uint64_t inst = arrayInstRef_c_Comp_ae_Bind(&((*c)), Array_Bind_get((*c).arrayElems, (long long)(ei)));
    if (inst < (long long)(((*c).types).count)) {
    uint64_t mfi = 0;
    while (mfi < (long long)(((*c).funcs).count)) {
    if (methodMatchesInst_c_Comp_f_Func_instRef_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(mfi)), inst)) {
    emitMonoMethod_c_Comp_fi_U64_instRef_U64_proto_Bool(&((*c)), mfi, inst, proto);
    }
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    ei = ({ uint64_t __ov; if (__builtin_add_overflow((ei), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
}
void emitMonoMethods_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t gi = 0;
    while (gi < (long long)(((*c).genInsts).count)) {
    TypeRef gt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(Array_U64_get((*c).genInsts, (long long)(gi)))));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), gt.nameStart, gt.nameLen, (PlewString){"Array", 5})) {
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    uint64_t mfi = 0;
    while (mfi < (long long)(((*c).funcs).count)) {
    if (methodMatchesInst_c_Comp_f_Func_instRef_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(mfi)), Array_U64_get((*c).genInsts, (long long)(gi)))) {
    long long emit = 1;
    if (Array_Func_get((*c).funcs, (long long)(mfi)).isProvided) {
    if (providedRetReachable_c_Comp_mf_Func_recvInstRef_U64(&((*c)), Array_Func_get((*c).funcs, (long long)(mfi)), Array_U64_get((*c).genInsts, (long long)(gi)))) {
    }
    else {
    emit = 0;
    }
    }
    if (emit) {
    emitMonoMethod_c_Comp_fi_U64_instRef_U64_proto_Bool(&((*c)), mfi, Array_U64_get((*c).genInsts, (long long)(gi)), proto);
    }
    }
    mfi = ({ uint64_t __ov; if (__builtin_add_overflow((mfi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    gi = ({ uint64_t __ov; if (__builtin_add_overflow((gi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(gt);
    }
}
long long isGenericFreeFn_c_Comp_fi_U64(Comp* c, uint64_t fi) {
    if (fi >= (long long)(((*c).funcs).count)) {
    { long long __ret1035 = 0;
    return __ret1035; }
    }
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    if (f.hasRecv) {
    { long long __ret1036 = 0;
    Func_release(f);
    return __ret1036; }
    }
    { long long __ret1037 = ((long long)((f.typeParams).count) > 0);
    Func_release(f);
    return __ret1037; }
    Func_release(f);
}
uint64_t findOrAddTypeRef_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t i = 0;
    while (i < (long long)(((*c).types).count)) {
    TypeRef t = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(i)));
    if ((long long)((t.args).count) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), t.nameStart, t.nameLen, nameStart, nameLen)) {
    { uint64_t __ret1038 = i;
    TypeRef_release(t);
    return __ret1038; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    TypeRef_release(t);
    }
    Array_U64 noArgs = Array_U64_new();
    { uint64_t __ret1039 = Comp_pushType_t_TypeRef(&((*c)), (TypeRef){.nameStart = nameStart, .nameLen = nameLen, .args = Array_U64_share(noArgs)});
    Array_U64_release(noArgs);
    return __ret1039; }
    Array_U64_release(noArgs);
}
uint64_t closureFnTypeRef_c_Comp_params_AParam_retTy_U64(Comp* c, Array_Param params, uint64_t retTy) {
    Bind fnName = kwSpan_c_Comp_kw_String_kwLen_U64(&((*c)), (PlewString){"fn", 2}, 2);
    Array_U64 args = Array_U64_new();
    Array_U64_append_value_T(&(args), retTy);
    uint64_t i = 0;
    while (i < (long long)((params).count)) {
    Array_U64_append_value_T(&(args), Array_Param_get(params, (long long)(i)).ty);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t idx = (long long)(((*c).types).count);
    Array_TypeRef_append_value_T(&((*c).types), (TypeRef){.nameStart = fnName.nameStart, .nameLen = fnName.nameLen, .args = Array_U64_share(args)});
    { uint64_t __ret1040 = idx;
    Array_U64_release(args);
    return __ret1040; }
    Array_U64_release(args);
}
uint64_t unifyTypeParam_c_Comp_paramRef_U64_argRef_U64_tpStart_U64_tpLen_U64(Comp* c, uint64_t paramRef, uint64_t argRef, uint64_t tpStart, uint64_t tpLen) {
    if (paramRef >= (long long)(((*c).types).count)) {
    { uint64_t __ret1041 = 0;
    return __ret1041; }
    }
    TypeRef pt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(paramRef)));
    if ((long long)((pt.args).count) == 0) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), pt.nameStart, pt.nameLen, tpStart, tpLen)) {
    { uint64_t __ret1042 = argRef;
    TypeRef_release(pt);
    return __ret1042; }
    }
    { uint64_t __ret1043 = 0;
    TypeRef_release(pt);
    return __ret1043; }
    }
    if (argRef >= (long long)(((*c).types).count)) {
    { uint64_t __ret1044 = 0;
    TypeRef_release(pt);
    return __ret1044; }
    }
    TypeRef at = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(argRef)));
    uint64_t i = 0;
    while (i < (long long)((pt.args).count)) {
    if (i < (long long)((at.args).count)) {
    uint64_t r = unifyTypeParam_c_Comp_paramRef_U64_argRef_U64_tpStart_U64_tpLen_U64(&((*c)), Array_U64_get(pt.args, (long long)(i)), Array_U64_get(at.args, (long long)(i)), tpStart, tpLen);
    if (r != 0) {
    { uint64_t __ret1045 = r;
    TypeRef_release(at);
    TypeRef_release(pt);
    return __ret1045; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret1046 = 0;
    TypeRef_release(at);
    TypeRef_release(pt);
    return __ret1046; }
    TypeRef_release(at);
    TypeRef_release(pt);
}
uint64_t tyRefOfInfo_c_Comp_ti_TypeInfo(Comp* c, TypeInfo ti) {
    if (ti.ref != 0) {
    { uint64_t __ret1047 = ti.ref;
    return __ret1047; }
    }
    if (ti.nameLen == 0) {
    { uint64_t __ret1048 = 0;
    return __ret1048; }
    }
    if (ti.kind == 3) {
    { uint64_t __ret1049 = 0;
    return __ret1049; }
    }
    { uint64_t __ret1050 = findOrAddTypeRef_c_Comp_nameStart_U64_nameLen_U64(&((*c)), ti.nameStart, ti.nameLen);
    return __ret1050; }
}
uint64_t argArrayElemRef_c_Comp_argExpr_U64(Comp* c, uint64_t argExpr) {
    {
    Expr _m1051 = Array_Expr_get((*c).exprs, (long long)(argExpr));
    if (_m1051.tag == 1) {
        uint64_t start = _m1051.data.Ident.start;
        (void)start;
        uint64_t len = _m1051.data.Ident.len;
        (void)len;
    uint64_t li = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (li < (long long)(((*c).locals).count)) {
    Local lo = Array_Local_get((*c).locals, (long long)(li));
    if (lo.ty < (long long)(((*c).types).count)) {
    TypeRef lt = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(lo.ty)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), lt.nameStart, lt.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((lt.args).count) > 0) {
    { uint64_t __ret1052 = Array_U64_get(lt.args, (long long)(0));
    TypeRef_release(lt);
    return __ret1052; }
    }
    }
    TypeRef_release(lt);
    }
    }
    }
    else {
    }
    }
    { uint64_t __ret1053 = 0;
    return __ret1053; }
}
Array_U64 inferFnArgs_c_Comp_f_Func_args_AArg(Comp* c, Func f, Array_Arg args) {
    Array_U64 out = Array_U64_new();
    uint64_t ti = 0;
    while (ti < (long long)((f.typeParams).count)) {
    Bind tp = Array_Bind_get(f.typeParams, (long long)(ti));
    uint64_t found = 0;
    uint64_t pi = 0;
    while (pi < (long long)((f.params).count)) {
    Param p = Array_Param_get(f.params, (long long)(pi));
    if (p.tyIsArray) {
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.tyStart, p.tyLen, tp.nameStart, tp.nameLen)) {
    if (pi < (long long)((args).count)) {
    if (found == 0) {
    found = argArrayElemRef_c_Comp_argExpr_U64(&((*c)), Array_Arg_get(args, (long long)(pi)).expr);
    }
    }
    }
    }
    else {
    if (pi < (long long)((args).count)) {
    if (found == 0) {
    TypeInfo at = exprType_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(pi)).expr);
    uint64_t argRef = tyRefOfInfo_c_Comp_ti_TypeInfo(&((*c)), at);
    found = unifyTypeParam_c_Comp_paramRef_U64_argRef_U64_tpStart_U64_tpLen_U64(&((*c)), p.ty, argRef, tp.nameStart, tp.nameLen);
    }
    }
    }
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_append_value_T(&(out), found);
    ti = ({ uint64_t __ov; if (__builtin_add_overflow((ti), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Array_U64 __ret1054 = Array_U64_share(out);
    Array_U64_release(out);
    return __ret1054; }
    Array_U64_release(out);
}
long long fnArgsAllGround_c_Comp_args_AU64(Comp* c, Array_U64 args) {
    if ((long long)((args).count) == 0) {
    { long long __ret1055 = 0;
    return __ret1055; }
    }
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    if (Array_U64_get(args, (long long)(i)) == 0) {
    { long long __ret1056 = 0;
    return __ret1056; }
    }
    if (tyRefIsGround_c_Comp_ref_U64(&((*c)), Array_U64_get(args, (long long)(i)))) {
    }
    else {
    { long long __ret1057 = 0;
    return __ret1057; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret1058 = 1;
    return __ret1058; }
}
long long fnInstExists_c_Comp_fnIdx_U64_args_AU64(Comp* c, uint64_t fnIdx, Array_U64 args) {
    uint64_t i = 0;
    while (i < (long long)(((*c).fnInsts).count)) {
    FnInst fin = FnInst_share(Array_FnInst_get((*c).fnInsts, (long long)(i)));
    if (fin.fnIdx == fnIdx) {
    if ((long long)((fin.args).count) == (long long)((args).count)) {
    long long same = 1;
    uint64_t j = 0;
    while (j < (long long)((args).count)) {
    if (typeRefEq_c_Comp_a_U64_b_U64(&((*c)), Array_U64_get(fin.args, (long long)(j)), Array_U64_get(args, (long long)(j)))) {
    }
    else {
    same = 0;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (same) {
    { long long __ret1059 = 1;
    FnInst_release(fin);
    return __ret1059; }
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    FnInst_release(fin);
    }
    { long long __ret1060 = 0;
    return __ret1060; }
}
void registerCallInst_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    uint64_t fi = findFunc_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args));
    if (fi < (long long)(((*c).funcs).count)) {
    if (Array_Func_get((*c).funcs, (long long)(fi)).isExtern) {
    }
    else {
    if (isGenericFreeFn_c_Comp_fi_U64(&((*c)), fi)) {
    Array_U64 inferred = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), Array_Func_get((*c).funcs, (long long)(fi)), Array_Arg_share(args));
    if (fnArgsAllGround_c_Comp_args_AU64(&((*c)), Array_U64_share(inferred))) {
    if (fnInstExists_c_Comp_fnIdx_U64_args_AU64(&((*c)), fi, Array_U64_share(inferred))) {
    }
    else {
    Array_FnInst_append_value_T(&((*c).fnInsts), (FnInst){.fnIdx = fi, .args = Array_U64_share(inferred), .recvInstRef = 0});
    }
    }
    Array_U64_release(inferred);
    }
    }
    }
}
void registerMethodInst_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t recv, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    TypeInfo rt = exprType_c_Comp_id_U64(&((*c)), recv);
    if (rt.kind == 2) {
    }
    else {
    return;
    }
    long long genericRecv = isGenericInst_c_Comp_ref_U64(&((*c)), rt.ref);
    uint64_t mi = findMethod_c_Comp_recvStart_U64_recvLen_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), rt.nameStart, rt.nameLen, nameStart, nameLen, Array_Arg_share(args));
    if (mi == (long long)(((*c).funcs).count)) {
    return;
    }
    Func mf = Func_share(Array_Func_get((*c).funcs, (long long)(mi)));
    if ((long long)((mf.typeParams).count) == 0) {
    Func_release(mf);
    return;
    }
    uint64_t rcount = 0;
    uint64_t recvInst = 0;
    if (genericRecv) {
    rcount = recvParamCount_c_Comp_nameStart_U64_nameLen_U64(&((*c)), rt.nameStart, rt.nameLen);
    recvInst = rt.ref;
    if ((long long)((mf.typeParams).count) > rcount) {
    }
    else {
    Func_release(mf);
    return;
    }
    }
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), rt.nameStart, rt.nameLen, recvInst);
    Array_U64 inferred = inferFnArgs_c_Comp_f_Func_args_AArg(&((*c)), mf, Array_Arg_share(args));
    Array_U64 fullArgs = Array_U64_new();
    if (genericRecv) {
    TypeRef inst = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(recvInst)));
    uint64_t ri = 0;
    while (ri < rcount) {
    if (ri < (long long)((inst.args).count)) {
    Array_U64_append_value_T(&(fullArgs), Array_U64_get(inst.args, (long long)(ri)));
    }
    ri = ({ uint64_t __ov; if (__builtin_add_overflow((ri), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t oi = rcount;
    while (oi < (long long)((inferred).count)) {
    Array_U64_append_value_T(&(fullArgs), Array_U64_get(inferred, (long long)(oi)));
    oi = ({ uint64_t __ov; if (__builtin_add_overflow((oi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    TypeRef_release(inst);
    }
    else {
    uint64_t ai = 0;
    while (ai < (long long)((inferred).count)) {
    Array_U64_append_value_T(&(fullArgs), Array_U64_get(inferred, (long long)(ai)));
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    if (fnArgsAllGround_c_Comp_args_AU64(&((*c)), Array_U64_share(fullArgs))) {
    if (fnInstExists_c_Comp_fnIdx_U64_args_AU64(&((*c)), mi, Array_U64_share(fullArgs))) {
    }
    else {
    Array_FnInst_append_value_T(&((*c).fnInsts), (FnInst){.fnIdx = mi, .args = Array_U64_share(fullArgs), .recvInstRef = recvInst});
    }
    Array_Bind savedP = Array_Bind_share((*c).curTypeParams);
    Array_U64 savedA = Array_U64_share((*c).curTypeArgs);
    (*c).curTypeParams = Array_Bind_share(mf.typeParams);
    (*c).curTypeArgs = Array_U64_share(fullArgs);
    if (mf.hasRet) {
    scanType_c_Comp_ref_U64(&((*c)), mf.retTy);
    }
    (*c).curTypeParams = Array_Bind_share(savedP);
    (*c).curTypeArgs = Array_U64_share(savedA);
    Array_U64_release(savedA);
    Array_Bind_release(savedP);
    }
    clearSelfItemEnv_c_Comp(&((*c)));
    Array_U64_release(fullArgs);
    Array_U64_release(inferred);
    Func_release(mf);
}
uint64_t recvParamCount_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    uint64_t gsi = genericStructIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen);
    if (gsi < (long long)(((*c).structs).count)) {
    { uint64_t __ret1061 = (long long)((Array_StructDef_get((*c).structs, (long long)(gsi)).typeParams).count);
    return __ret1061; }
    }
    uint64_t gei = genericEnumIndex_c_Comp_nameStart_U64_nameLen_U64(&((*c)), nameStart, nameLen);
    if (gei < (long long)(((*c).enums).count)) {
    { uint64_t __ret1062 = (long long)((Array_EnumDef_get((*c).enums, (long long)(gei)).typeParams).count);
    return __ret1062; }
    }
    { uint64_t __ret1063 = 0;
    return __ret1063; }
}
void writeMethodInstSuffixFrom_c_Comp_typeArgs_AU64_startIdx_U64(Comp* c, Array_U64 typeArgs, uint64_t startIdx) {
    uint64_t i = startIdx;
    while (i < (long long)((typeArgs).count)) {
    plew_write((PlewString){"_", 1});
    emitMangle_c_Comp_ref_U64(&((*c)), Array_U64_get(typeArgs, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long captureSupported_c_Comp_lo_Local(Comp* c, Local lo) {
    if (lo.isArray) {
    { long long __ret1064 = 1;
    return __ret1064; }
    }
    if (isPrimType_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen)) {
    { long long __ret1065 = 1;
    return __ret1065; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), lo.tyStart, lo.tyLen, (PlewString){"String", 6})) {
    { long long __ret1066 = 1;
    return __ret1066; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), lo.tyStart, lo.tyLen, (PlewString){"Ref", 3})) {
    { long long __ret1067 = 1;
    return __ret1067; }
    }
    uint64_t si = structIndexByName_c_Comp_start_U64_len_U64(&((*c)), lo.tyStart, lo.tyLen);
    if (si < (long long)(((*c).structs).count)) {
    if (Array_StructDef_get((*c).structs, (long long)(si)).isUnique) {
    { long long __ret1068 = 0;
    return __ret1068; }
    }
    if ((long long)((Array_StructDef_get((*c).structs, (long long)(si)).typeParams).count) > 0) {
    { long long __ret1069 = 0;
    return __ret1069; }
    }
    { long long __ret1070 = 1;
    return __ret1070; }
    }
    { long long __ret1071 = 0;
    return __ret1071; }
}
void recordCapture_c_Comp_closureId_U64_localIdx_U64(Comp* c, uint64_t closureId, uint64_t localIdx) {
    Local lo = Array_Local_get((*c).locals, (long long)(localIdx));
    uint64_t i = 0;
    while (i < (long long)(((*c).captures).count)) {
    CaptureEntry e = Array_CaptureEntry_get((*c).captures, (long long)(i));
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
    Array_CaptureEntry_append_value_T(&((*c).captures), (CaptureEntry){.closureId = closureId, .nameStart = lo.nameStart, .nameLen = lo.nameLen, .tyStart = lo.tyStart, .tyLen = lo.tyLen, .isArray = lo.isArray, .ty = lo.ty, .boxed = boxed});
}
void scanExprInsts_c_Comp_exprId_U64(Comp* c, uint64_t exprId) {
    {
    Expr _m1072 = Array_Expr_get((*c).exprs, (long long)(exprId));
    if (_m1072.tag == 1) {
        uint64_t start = _m1072.data.Ident.start;
        (void)start;
        uint64_t len = _m1072.data.Ident.len;
        (void)len;
    if ((*c).curInClosure) {
    uint64_t li = localIndexByName_c_Comp_start_U64_len_U64(&((*c)), start, len);
    if (li < (*c).curCaptureMark) {
    recordCapture_c_Comp_closureId_U64_localIdx_U64(&((*c)), (*c).curClosureId, li);
    }
    }
    }
    else if (_m1072.tag == 17) {
        Array_Param params = _m1072.data.Closure.params;
        (void)params;
        long long hasRet = _m1072.data.Closure.hasRet;
        (void)hasRet;
        uint64_t retStart = _m1072.data.Closure.retStart;
        (void)retStart;
        uint64_t retLen = _m1072.data.Closure.retLen;
        (void)retLen;
        long long retIsArray = _m1072.data.Closure.retIsArray;
        (void)retIsArray;
        uint64_t retTy = _m1072.data.Closure.retTy;
        (void)retTy;
        uint64_t body = _m1072.data.Closure.body;
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
    while (pi < (long long)((params).count)) {
    Param p = Array_Param_get(params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), body);
    popLocals_c_Comp_mark_U64(&((*c)), enclMark);
    (*c).curClosureId = savedId;
    (*c).curInClosure = savedIn;
    (*c).curCaptureMark = savedMark;
    }
    else if (_m1072.tag == 2) {
        int64_t op = _m1072.data.Unary.op;
        (void)op;
        uint64_t operand = _m1072.data.Unary.operand;
        (void)operand;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m1072.tag == 3) {
        int64_t op = _m1072.data.Binary.op;
        (void)op;
        uint64_t lhs = _m1072.data.Binary.lhs;
        (void)lhs;
        uint64_t rhs = _m1072.data.Binary.rhs;
        (void)rhs;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), lhs);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), rhs);
    }
    else if (_m1072.tag == 4) {
        uint64_t nameStart = _m1072.data.Call.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m1072.data.Call.nameLen;
        (void)nameLen;
        Array_Arg args = _m1072.data.Call.args;
        (void)args;
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), Array_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    registerCallInst_c_Comp_nameStart_U64_nameLen_U64_args_AArg(&((*c)), nameStart, nameLen, Array_Arg_share(args));
    }
    else if (_m1072.tag == 10) {
        uint64_t recv = _m1072.data.Method.recv;
        (void)recv;
        uint64_t nameStart = _m1072.data.Method.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m1072.data.Method.nameLen;
        (void)nameLen;
        Array_Arg args = _m1072.data.Method.args;
        (void)args;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), recv);
    uint64_t i = 0;
    while (i < (long long)((args).count)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), Array_Arg_get(args, (long long)(i)).expr);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    registerMethodInst_c_Comp_recv_U64_nameStart_U64_nameLen_U64_args_AArg(&((*c)), recv, nameStart, nameLen, Array_Arg_share(args));
    TypeInfo mrt = exprType_c_Comp_id_U64(&((*c)), exprId);
    if (mrt.ref != 0) {
    scanType_c_Comp_ref_U64(&((*c)), mrt.ref);
    }
    }
    else if (_m1072.tag == 5) {
        uint64_t base = _m1072.data.Field.base;
        (void)base;
        uint64_t nameStart = _m1072.data.Field.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m1072.data.Field.nameLen;
        (void)nameLen;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m1072.tag == 9) {
        uint64_t base = _m1072.data.Index.base;
        (void)base;
        uint64_t index = _m1072.data.Index.index;
        (void)index;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), base);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), index);
    }
    else if (_m1072.tag == 6) {
        uint64_t typeStart = _m1072.data.Make.typeStart;
        (void)typeStart;
        uint64_t typeLen = _m1072.data.Make.typeLen;
        (void)typeLen;
        uint64_t variantStart = _m1072.data.Make.variantStart;
        (void)variantStart;
        uint64_t variantLen = _m1072.data.Make.variantLen;
        (void)variantLen;
        long long isEnum = _m1072.data.Make.isEnum;
        (void)isEnum;
        uint64_t ty = _m1072.data.Make.ty;
        (void)ty;
        Array_MakeField fields = _m1072.data.Make.fields;
        (void)fields;
    uint64_t i = 0;
    while (i < (long long)((fields).count)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), Array_MakeField_get(fields, (long long)(i)).value);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m1072.tag == 8) {
        Array_U64 elems = _m1072.data.Array.elems;
        (void)elems;
    uint64_t i = 0;
    while (i < (long long)((elems).count)) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), Array_U64_get(elems, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m1072.tag == 11) {
        uint64_t operand = _m1072.data.Cast.operand;
        (void)operand;
        uint64_t tyStart = _m1072.data.Cast.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m1072.data.Cast.tyLen;
        (void)tyLen;
        uint64_t ty = _m1072.data.Cast.ty;
        (void)ty;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), operand);
    }
    else if (_m1072.tag == 14) {
        uint64_t opt = _m1072.data.Coalesce.opt;
        (void)opt;
        uint64_t deflt = _m1072.data.Coalesce.deflt;
        (void)deflt;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), opt);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), deflt);
    }
    else if (_m1072.tag == 15) {
        uint64_t expr = _m1072.data.Try.expr;
        (void)expr;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m1072.tag == 16) {
        uint64_t base = _m1072.data.Arrow.base;
        (void)base;
        uint64_t nameStart = _m1072.data.Arrow.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m1072.data.Arrow.nameLen;
        (void)nameLen;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), base);
    }
    else if (_m1072.tag == 13) {
        uint64_t cond = _m1072.data.IfExpr.cond;
        (void)cond;
        uint64_t thenBlk = _m1072.data.IfExpr.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m1072.data.IfExpr.elseBlk;
        (void)elseBlk;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), cond);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), thenBlk);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    else if (_m1072.tag == 12) {
        uint64_t scrut = _m1072.data.MatchExpr.scrut;
        (void)scrut;
        Array_MatchArm arms = _m1072.data.MatchExpr.arms;
        (void)arms;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm_scrutTi_TypeInfo(&((*c)), a, exprType_c_Comp_id_U64(&((*c)), scrut));
    scanExprInsts_c_Comp_exprId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m1072.tag == 18) {
        uint64_t operand = _m1072.data.Move.operand;
        (void)operand;
        long long isBorrow = _m1072.data.Move.isBorrow;
        (void)isBorrow;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), operand);
    }
    else {
    }
    }
}
void scanAddArmBinds_c_Comp_a_MatchArm_scrutTi_TypeInfo(Comp* c, MatchArm a, TypeInfo scrutTi) {
    if (a.isStruct) {
    addForStructBinds_c_Comp_et_TypeInfo_binds_ABind(&((*c)), scrutTi, Array_Bind_share(a.binds));
    return;
    }
    long long genericMatch = isGenericEnumInst_c_Comp_ref_U64(&((*c)), scrutTi.ref);
    uint64_t bi = 0;
    while (bi < (long long)((a.binds).count)) {
    Bind bd = Array_Bind_get(a.binds, (long long)(bi));
    if (genericMatch) {
    TypeInfo bti = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), scrutTi.ref, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0, 0);
    }
    else {
    addBindLocal_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64(&((*c)), a.enumStart, a.enumLen, a.variantStart, a.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
void scanStmtInsts_c_Comp_stmtId_U64(Comp* c, uint64_t stmtId) {
    {
    Stmt _m1073 = Array_Stmt_get((*c).stmts, (long long)(stmtId));
    if (_m1073.tag == 0) {
        long long mutable = _m1073.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m1073.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m1073.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m1073.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m1073.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m1073.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m1073.data.Let.ty;
        (void)ty;
        uint64_t init = _m1073.data.Let.init;
        (void)init;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), init);
    LetEff le = inferLetType_c_Comp_tyStart_U64_tyLen_U64_tyIsArray_Bool_ty_U64_init_U64(&((*c)), tyStart, tyLen, tyIsArray, ty, init);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), nameStart, nameLen, le.start, le.len, le.arr, le.ty, 0, mutable, 1);
    }
    else if (_m1073.tag == 1) {
        int64_t op = _m1073.data.Assign.op;
        (void)op;
        uint64_t target = _m1073.data.Assign.target;
        (void)target;
        uint64_t value = _m1073.data.Assign.value;
        (void)value;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), target);
    scanExprInsts_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m1073.tag == 2) {
        uint64_t expr = _m1073.data.ExprStmt.expr;
        (void)expr;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), expr);
    }
    else if (_m1073.tag == 3) {
        uint64_t value = _m1073.data.Return.value;
        (void)value;
        long long hasValue = _m1073.data.Return.hasValue;
        (void)hasValue;
    if (hasValue) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), value);
    }
    }
    else if (_m1073.tag == 4) {
        uint64_t cond = _m1073.data.If.cond;
        (void)cond;
        uint64_t thenBlk = _m1073.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m1073.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m1073.data.If.hasElse;
        (void)hasElse;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), cond);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), thenBlk);
    if (hasElse) {
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), elseBlk);
    }
    }
    else if (_m1073.tag == 5) {
        uint64_t cond = _m1073.data.While.cond;
        (void)cond;
        uint64_t body = _m1073.data.While.body;
        (void)body;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), cond);
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), body);
    }
    else if (_m1073.tag == 6) {
        uint64_t varStart = _m1073.data.For.varStart;
        (void)varStart;
        uint64_t varLen = _m1073.data.For.varLen;
        (void)varLen;
        long long isRange = _m1073.data.For.isRange;
        (void)isRange;
        long long inclusive = _m1073.data.For.inclusive;
        (void)inclusive;
        uint64_t iter = _m1073.data.For.iter;
        (void)iter;
        uint64_t rangeHi = _m1073.data.For.rangeHi;
        (void)rangeHi;
        uint64_t body = _m1073.data.For.body;
        (void)body;
        long long isStruct = _m1073.data.For.isStruct;
        (void)isStruct;
        uint64_t patStart = _m1073.data.For.patStart;
        (void)patStart;
        uint64_t patLen = _m1073.data.For.patLen;
        (void)patLen;
        Array_Bind binds = _m1073.data.For.binds;
        (void)binds;
    uint64_t forMark = scopeMark_c_Comp(&((*c)));
    scanExprInsts_c_Comp_exprId_U64(&((*c)), iter);
    if (isRange) {
    scanExprInsts_c_Comp_exprId_U64(&((*c)), rangeHi);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, 0, 0, 0, 0, 0, 0, 0);
    }
    else {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), iter);
    if (isStruct) {
    addForStructBinds_c_Comp_et_TypeInfo_binds_ABind(&((*c)), et, Array_Bind_share(binds));
    }
    else {
    if (et.kind == 3) {
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, et.nameStart, et.nameLen, 0, 0, 0, 0, 0);
    }
    else {
    TypeInfo elemTi = iterableItemInfo_c_Comp_et_TypeInfo(&((*c)), et);
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), varStart, varLen, elemTi.nameStart, elemTi.nameLen, (elemTi.kind == 3), elemTi.ref, 0, 0, 0);
    }
    }
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), body);
    popLocals_c_Comp_mark_U64(&((*c)), forMark);
    }
    else if (_m1073.tag == 7) {
        uint64_t scrut = _m1073.data.Match.scrut;
        (void)scrut;
        Array_MatchArm arms = _m1073.data.Match.arms;
        (void)arms;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), scrut);
    uint64_t ai = 0;
    while (ai < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(ai)));
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    scanAddArmBinds_c_Comp_a_MatchArm_scrutTi_TypeInfo(&((*c)), a, exprType_c_Comp_id_U64(&((*c)), scrut));
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), a.body);
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else if (_m1073.tag == 8) {
        uint64_t msg = _m1073.data.Panic.msg;
        (void)msg;
        uint64_t offset = _m1073.data.Panic.offset;
        (void)offset;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), msg);
    }
    else if (_m1073.tag == 9) {
        uint64_t value = _m1073.data.Give.value;
        (void)value;
    scanExprInsts_c_Comp_exprId_U64(&((*c)), value);
    }
    else if (_m1073.tag == 10) {
    }
    else if (_m1073.tag == 11) {
    }
    else { __builtin_unreachable(); }
    }
}
void scanBlockInsts_c_Comp_blkId_U64(Comp* c, uint64_t blkId) {
    uint64_t mark = scopeMark_c_Comp(&((*c)));
    Array_U64 stmts = Array_U64_share(Array_Block_get((*c).blocks, (long long)(blkId)).stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).count)) {
    scanStmtInsts_c_Comp_stmtId_U64(&((*c)), Array_U64_get(stmts, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    popLocals_c_Comp_mark_U64(&((*c)), mark);
    Array_U64_release(stmts);
}
void collectFnInsts_c_Comp(Comp* c) {
    uint64_t fi = 0;
    while (fi < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    if ((long long)((f.typeParams).count) > 0) {
    }
    else {
    Array_Bind noParams = Array_Bind_new();
    Array_U64 noArgs = Array_U64_new();
    (*c).locals = Array_Local_new();
    (*c).curHasRecv = f.hasRecv;
    (*c).curRecvStart = f.recvStart;
    (*c).curRecvLen = f.recvLen;
    (*c).curSelfInout = f.selfInout;
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = Array_Bind_share(noParams);
    (*c).curTypeArgs = Array_U64_share(noArgs);
    uint64_t pi = 0;
    while (pi < (long long)((f.params).count)) {
    Param p = Array_Param_get(f.params, (long long)(pi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, p.isInout, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), f.body);
    Array_U64_release(noArgs);
    Array_Bind_release(noParams);
    }
    fi = ({ uint64_t __ov; if (__builtin_add_overflow((fi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
    uint64_t si = 0;
    while (si < (long long)(((*c).fnInsts).count)) {
    FnInst fin = FnInst_share(Array_FnInst_get((*c).fnInsts, (long long)(si)));
    Func gf = Func_share(Array_Func_get((*c).funcs, (long long)(fin.fnIdx)));
    (*c).locals = Array_Local_new();
    (*c).curHasRecv = 0;
    (*c).curRecvStart = 0;
    (*c).curRecvLen = 0;
    (*c).curSelfInout = 0;
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = Array_Bind_share(gf.typeParams);
    (*c).curTypeArgs = Array_U64_share(fin.args);
    uint64_t gpi = 0;
    while (gpi < (long long)((gf.params).count)) {
    Param gp = Array_Param_get(gf.params, (long long)(gpi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), gp.nameStart, gp.nameLen, gp.tyStart, gp.tyLen, gp.tyIsArray, gp.ty, gp.isInout, 0, 0);
    gpi = ({ uint64_t __ov; if (__builtin_add_overflow((gpi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    scanBlockInsts_c_Comp_blkId_U64(&((*c)), gf.body);
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(gf);
    FnInst_release(fin);
    }
    Array_Bind noP = Array_Bind_new();
    Array_U64 noA = Array_U64_new();
    (*c).locals = Array_Local_new();
    (*c).curHasRecv = 0;
    (*c).curTypeParams = Array_Bind_share(noP);
    (*c).curTypeArgs = Array_U64_share(noA);
    (*c).curInClosure = 0;
    (*c).curClosureId = 0;
    (*c).curCaptureMark = 0;
    Array_U64_release(noA);
    Array_Bind_release(noP);
}
void emitMonoFn_c_Comp_instIdx_U64_proto_Bool(Comp* c, uint64_t instIdx, long long proto) {
    FnInst fin = FnInst_share(Array_FnInst_get((*c).fnInsts, (long long)(instIdx)));
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fin.fnIdx)));
    (*c).curTypeParams = Array_Bind_share(f.typeParams);
    (*c).curTypeArgs = Array_U64_share(fin.args);
    (*c).curRecvInstRef = fin.recvInstRef;
    if (proto) {
    if (f.hasRecv) {
    setSelfItemEnv_c_Comp_recvStart_U64_recvLen_U64_recvInstRef_U64(&((*c)), f.recvStart, f.recvLen, fin.recvInstRef);
    }
    genSignature_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){";\n", 2});
    clearSelfItemEnv_c_Comp(&((*c)));
    }
    else {
    genFunc_c_Comp_fi_U64(&((*c)), fin.fnIdx);
    }
    Array_Bind noParams = Array_Bind_new();
    Array_U64 noArgs = Array_U64_new();
    (*c).curRecvInstRef = 0;
    (*c).curTypeParams = Array_Bind_share(noParams);
    (*c).curTypeArgs = Array_U64_share(noArgs);
    Array_U64_release(noArgs);
    Array_Bind_release(noParams);
    Func_release(f);
    FnInst_release(fin);
}
void emitMonoFns_c_Comp_proto_Bool(Comp* c, long long proto) {
    uint64_t i = 0;
    while (i < (long long)(((*c).fnInsts).count)) {
    emitMonoFn_c_Comp_instIdx_U64_proto_Bool(&((*c)), i, proto);
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
long long emitArrayIntrinsic_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayPush", 9})) {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"_push(&(", 8});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"), ", 3});
    emitArrayElemValue_c_Comp_argExpr_U64_arrStart_U64_arrLen_U64(&((*c)), Array_Arg_get(args, (long long)(1)).expr, et.nameStart, et.nameLen);
    plew_write((PlewString){")", 1});
    { long long __ret1074 = 1;
    return __ret1074; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayGet", 8})) {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"_get((", 6});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(1)).expr);
    plew_write((PlewString){"))", 2});
    { long long __ret1075 = 1;
    return __ret1075; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arraySet", 8})) {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"_set(&(", 7});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(1)).expr);
    plew_write((PlewString){"), ", 3});
    emitArrayElemValue_c_Comp_argExpr_U64_arrStart_U64_arrLen_U64(&((*c)), Array_Arg_get(args, (long long)(2)).expr, et.nameStart, et.nameLen);
    plew_write((PlewString){")", 1});
    { long long __ret1076 = 1;
    return __ret1076; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayLen", 8})) {
    plew_write((PlewString){"((", 2});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){").count)", 8});
    { long long __ret1077 = 1;
    return __ret1077; }
    }
    { long long __ret1078 = 0;
    return __ret1078; }
}
void emitArrayElemValue_c_Comp_argExpr_U64_arrStart_U64_arrLen_U64(Comp* c, uint64_t argExpr, uint64_t arrStart, uint64_t arrLen) {
    uint64_t aer = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), arrStart, arrLen);
    if (aer != 0) {
    uint64_t arr2 = resolveTy_c_Comp_tyRef_U64(&((*c)), aer);
    if (arr2 < (long long)(((*c).types).count)) {
    TypeRef atp = TypeRef_share(Array_TypeRef_get((*c).types, (long long)(arr2)));
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), atp.nameStart, atp.nameLen, (PlewString){"Array", 5})) {
    if ((long long)((atp.args).count) > 0) {
    Bind xn = arrayElemNameForRef_c_Comp_elemRef_U64(&((*c)), Array_U64_get(atp.args, (long long)(0)));
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), argExpr, xn.nameStart, xn.nameLen);
    TypeRef_release(atp);
    return;
    }
    }
    TypeRef_release(atp);
    }
    }
    genExpr_c_Comp_id_U64(&((*c)), argExpr);
}
long long emitRawIntrinsic_c_Comp_nameStart_U64_nameLen_U64_args_AArg(Comp* c, uint64_t nameStart, uint64_t nameLen, Array_Arg args) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawAlloc", 8})) {
    TypeInfo et = exprType_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(1)).expr);
    plew_write((PlewString){"(", 1});
    emitElemCType_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"*)plew_rawbuf_alloc(sizeof(", 27});
    emitElemCType_c_Comp_elemStart_U64_elemLen_U64(&((*c)), et.nameStart, et.nameLen);
    plew_write((PlewString){"), (long long)(", 15});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    { long long __ret1079 = 1;
    return __ret1079; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawLoad", 7})) {
    plew_write((PlewString){"((", 2});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")[(", 3});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(1)).expr);
    plew_write((PlewString){")])", 3});
    { long long __ret1080 = 1;
    return __ret1080; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawStore", 8})) {
    plew_write((PlewString){"((", 2});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){")[(", 3});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(1)).expr);
    plew_write((PlewString){")] = (", 6});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(2)).expr);
    plew_write((PlewString){"))", 2});
    { long long __ret1081 = 1;
    return __ret1081; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawCap", 6})) {
    plew_write((PlewString){"plew_rawbuf_cap((void*)(", 24});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    { long long __ret1082 = 1;
    return __ret1082; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawIsUnique", 11})) {
    plew_write((PlewString){"plew_rawbuf_is_unique((void*)(", 30});
    genExpr_c_Comp_id_U64(&((*c)), Array_Arg_get(args, (long long)(0)).expr);
    plew_write((PlewString){"))", 2});
    { long long __ret1083 = 1;
    return __ret1083; }
    }
    { long long __ret1084 = 0;
    return __ret1084; }
}
void emitElemCType_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    uint64_t k = 0;
    while (k < (long long)(((*c).curTypeParams).count)) {
    Bind p = Array_Bind_get((*c).curTypeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.nameStart, p.nameLen, elemStart, elemLen)) {
    emitConcreteCType_c_Comp_ref_U64(&((*c)), Array_U64_get((*c).curTypeArgs, (long long)(k)));
    return;
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
}
long long isRawIntrinsicName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawAlloc", 8})) {
    { long long __ret1085 = 1;
    return __ret1085; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawLoad", 7})) {
    { long long __ret1086 = 1;
    return __ret1086; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawStore", 8})) {
    { long long __ret1087 = 1;
    return __ret1087; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawCap", 6})) {
    { long long __ret1088 = 1;
    return __ret1088; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"rawIsUnique", 11})) {
    { long long __ret1089 = 1;
    return __ret1089; }
    }
    { long long __ret1090 = 0;
    return __ret1090; }
}
long long isArrayIntrinsicName_c_Comp_nameStart_U64_nameLen_U64(Comp* c, uint64_t nameStart, uint64_t nameLen) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayPush", 9})) {
    { long long __ret1091 = 1;
    return __ret1091; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayGet", 8})) {
    { long long __ret1092 = 1;
    return __ret1092; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arraySet", 8})) {
    { long long __ret1093 = 1;
    return __ret1093; }
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), nameStart, nameLen, (PlewString){"arrayLen", 8})) {
    { long long __ret1094 = 1;
    return __ret1094; }
    }
    { long long __ret1095 = 0;
    return __ret1095; }
}
void wPA_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    uint64_t k = 0;
    while (k < (long long)(((*c).curTypeParams).count)) {
    Bind p = Array_Bind_get((*c).curTypeParams, (long long)(k));
    if (spansEqual_c_Comp_aStart_U64_aLen_U64_bStart_U64_bLen_U64(&((*c)), p.nameStart, p.nameLen, elemStart, elemLen)) {
    plew_write((PlewString){"Array_", 6});
    emitMangle_c_Comp_ref_U64(&((*c)), Array_U64_get((*c).curTypeArgs, (long long)(k)));
    return;
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"Array_", 6});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
}
void genArrayRuntimeFns_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_new(void) { ", 13});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a; a.data = (", 14});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)plew_rawbuf_alloc(sizeof(", 27});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"), 0); a.count = 0; return a; }\n", 32});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_get(", 5});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } return a.data[i]; }\n", 127});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { ", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" r; r.count = a.count; r.data = (", 33});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)plew_rawbuf_alloc(sizeof(", 27});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"), a.count); for (long long i = 0; i < a.count; i++) ", 53});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"r.data[i] = ", 12});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(a.data[i]);", 17});
    }
    else {
    if (elemIsRef_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"r.data[i] = plew_ref_share(a.data[i]);", 38});
    }
    else {
    plew_write((PlewString){"r.data[i] = a.data[i];", 22});
    }
    }
    plew_write((PlewString){" return r; }\n", 13});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(", 9});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { if (!a.data) return; ", 27});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) ", 84});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(a.data[i]); } ", 23});
    }
    else {
    if (elemIsRef_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"if (plew_rawbuf_is_unique((void*)a.data)) { for (long long i = 0; i < a.count; i++) if (a.data[i]) { long long* __erc = ((long long*)a.data[i]) - 1; if ((--(*__erc)) == 0) free(__erc); } } ", 189});
    }
    }
    plew_write((PlewString){"plew_rawbuf_release((void*)a.data); }\n", 38});
    plew_write((PlewString){"__attribute__((unused)) static ", 31});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" ", 1});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_share(", 7});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" a) { plew_rawbuf_share((void*)a.data); return a; }\n", 52});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(", 8});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { ", 53});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" nc = ", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }\n", 61});
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_set(", 5});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, long long i, ", 18});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { if (i < 0 || i >= a->count) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } ", 95});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(a); ", 12});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_release(a->data[i]); a->data[i] = ", 35});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(v); }\n", 12});
    }
    else {
    if (elemIsRef_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"if (a->data[i]) { long long* __erc = ((long long*)a->data[i]) - 1; if ((--(*__erc)) == 0) free(__erc); } a->data[i] = plew_ref_share(v); }\n", 139});
    }
    else {
    plew_write((PlewString){"a->data[i] = v; }\n", 18});
    }
    }
    plew_write((PlewString){"__attribute__((unused)) static void ", 36});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_push(", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* a, ", 5});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){" v) { ", 6});
    wPA_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; ", 178});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"* nd = (", 8});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"*)plew_rawbuf_alloc(sizeof(", 27});
    genCElem_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = ", 142});
    if (structNeedsCopy_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen)) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    plew_write((PlewString){"_copy(v)", 8});
    }
    else {
    if (elemIsRef_c_Comp_elemStart_U64_elemLen_U64(&((*c)), elemStart, elemLen)) {
    plew_write((PlewString){"plew_ref_share(v)", 17});
    }
    else {
    plew_write((PlewString){"v", 1});
    }
    }
    plew_write((PlewString){"; a->count++; }\n", 16});
}
long long isU8Elem_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    { long long __ret1096 = rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share((*c).bytes), elemStart, elemLen, (PlewString){"U8", 2});
    return __ret1096; }
}
long long elemIsRef_c_Comp_elemStart_U64_elemLen_U64(Comp* c, uint64_t elemStart, uint64_t elemLen) {
    uint64_t er = arrayElemRef_c_Comp_start_U64_len_U64(&((*c)), elemStart, elemLen);
    if (er == 0) {
    { long long __ret1097 = 0;
    return __ret1097; }
    }
    { long long __ret1098 = isRefInst_c_Comp_ref_U64(&((*c)), er);
    return __ret1098; }
}
long long skipArrayElem_c_Comp_ae_Bind(Comp* c, Bind ae) {
    if (isU8Elem_c_Comp_elemStart_U64_elemLen_U64(&((*c)), ae.nameStart, ae.nameLen)) {
    { long long __ret1099 = 1;
    return __ret1099; }
    }
    if (isTypeParamName_c_Comp_start_U64_len_U64(&((*c)), ae.nameStart, ae.nameLen)) {
    { long long __ret1100 = 1;
    return __ret1100; }
    }
    { long long __ret1101 = 0;
    return __ret1101; }
}
void genU8ArrayTypedef(void) {
    plew_write((PlewString){"typedef struct { unsigned char* data; long long count; } Array_U8;\n", 67});
}
void genU8ArrayRuntime(void) {
    plew_write((PlewString){"__attribute__((unused)) static Array_U8 Array_U8_new(void) { Array_U8 a; a.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), 0); a.count = 0; return a; }\n", 168});
    plew_write((PlewString){"__attribute__((unused)) static unsigned char Array_U8_get(Array_U8 a, long long i) { if (i < 0 || i >= a.count) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } return a.data[i]; }\n", 193});
    plew_write((PlewString){"__attribute__((unused)) static Array_U8 Array_U8_copy(Array_U8 a) { Array_U8 r; r.count = a.count; r.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), a.count); for (long long i = 0; i < a.count; i++) r.data[i] = a.data[i]; return r; }\n", 250});
    plew_write((PlewString){"__attribute__((unused)) static void Array_U8_release(Array_U8 a) { if (!a.data) return; plew_rawbuf_release((void*)a.data); }\n", 126});
    plew_write((PlewString){"__attribute__((unused)) static Array_U8 Array_U8_share(Array_U8 a) { plew_rawbuf_share((void*)a.data); return a; }\n", 115});
    plew_write((PlewString){"__attribute__((unused)) static void Array_U8_unique(Array_U8* a) { if (!plew_rawbuf_is_unique((void*)a->data)) { Array_U8 nc = Array_U8_copy(*a); plew_rawbuf_release((void*)a->data); *a = nc; } }\n", 196});
    plew_write((PlewString){"__attribute__((unused)) static void Array_U8_set(Array_U8* a, long long i, unsigned char v) { if (i < 0 || i >= a->count) { fprintf(stderr, \"panic: index out of range\\n\"); exit(1); } Array_U8_unique(a); a->data[i] = v; }\n", 221});
    plew_write((PlewString){"__attribute__((unused)) static void Array_U8_push(Array_U8* a, unsigned char v) { Array_U8_unique(a); if (a->count >= (long long)plew_rawbuf_cap((void*)a->data)) { long long __cap = (long long)plew_rawbuf_cap((void*)a->data); long long nc = __cap < 4 ? 4 : __cap * 2; unsigned char* nd = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), nc); for (long long i = 0; i < a->count; i++) nd[i] = a->data[i]; plew_rawbuf_release((void*)a->data); a->data = nd; } a->data[a->count] = v; a->count++; }\n", 501});
}
long long hasAnyAsync_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    if (Array_Func_get((*c).funcs, (long long)(i)).isAsync) {
    { long long __ret1102 = 1;
    return __ret1102; }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret1103 = 0;
    return __ret1103; }
}
void emitAsyncRuntime_c_Comp(Comp* c) {
    if (hasAnyAsync_c_Comp(&((*c)))) {
    }
    else {
    return;
    }
    plew_write((PlewString){"// ---- async runtime (event loop / promises / timers) ----\n", 60});
    plew_write((PlewString){"typedef struct PlewPromise PlewPromise;\n", 40});
    plew_write((PlewString){"typedef void (*PlewResumeFn)(void*);\n", 37});
    plew_write((PlewString){"struct PlewPromise { int done; long long value; PlewResumeFn k; void* kframe; };\n", 81});
    plew_write((PlewString){"typedef struct { PlewResumeFn fn; void* arg; } PlewTask;\n", 57});
    plew_write((PlewString){"static PlewTask* plew_ready = 0; static long long plew_ready_len = 0, plew_ready_cap = 0, plew_ready_head = 0;\n", 111});
    plew_write((PlewString){"static void plew_enqueue(PlewResumeFn fn, void* arg) { if (plew_ready_len == plew_ready_cap) { plew_ready_cap = plew_ready_cap ? plew_ready_cap * 2 : 16; plew_ready = (PlewTask*)realloc(plew_ready, (size_t)plew_ready_cap * sizeof(PlewTask)); } plew_ready[plew_ready_len++] = (PlewTask){fn, arg}; }\n", 298});
    plew_write((PlewString){"static int plew_dequeue(PlewTask* out) { if (plew_ready_head >= plew_ready_len) { plew_ready_head = 0; plew_ready_len = 0; return 0; } *out = plew_ready[plew_ready_head++]; return 1; }\n", 185});
    plew_write((PlewString){"typedef struct { long long deadline; PlewPromise* p; } PlewTimer;\n", 66});
    plew_write((PlewString){"static PlewTimer* plew_timers = 0; static long long plew_timers_len = 0, plew_timers_cap = 0; static long long plew_vnow = 0;\n", 126});
    plew_write((PlewString){"static PlewPromise* plew_promise_new(void) { PlewPromise* p = (PlewPromise*)malloc(sizeof(PlewPromise)); p->done = 0; p->value = 0; p->k = 0; p->kframe = 0; return p; }\n", 169});
    plew_write((PlewString){"static void plew_promise_resolve(PlewPromise* p, long long v) { p->done = 1; p->value = v; if (p->k) { PlewResumeFn k = p->k; void* f = p->kframe; p->k = 0; plew_enqueue(k, f); } }\n", 181});
    plew_write((PlewString){"static void plew_timer_add(long long delay, PlewPromise* p) { if (plew_timers_len == plew_timers_cap) { plew_timers_cap = plew_timers_cap ? plew_timers_cap * 2 : 8; plew_timers = (PlewTimer*)realloc(plew_timers, (size_t)plew_timers_cap * sizeof(PlewTimer)); } plew_timers[plew_timers_len].deadline = plew_vnow + delay; plew_timers[plew_timers_len].p = p; plew_timers_len++; }\n", 376});
    plew_write((PlewString){"__attribute__((unused)) static PlewPromise* plew_sleep(long long ms) { PlewPromise* p = plew_promise_new(); plew_timer_add(ms, p); return p; }\n", 143});
    plew_write((PlewString){"static void plew_loop_run(void) { PlewTask t; while (1) { while (plew_dequeue(&t)) { t.fn(t.arg); } if (plew_timers_len == 0) break; long long bi = -1, bd = 0; for (long long i = 0; i < plew_timers_len; i++) { if (bi < 0 || plew_timers[i].deadline < bd) { bi = i; bd = plew_timers[i].deadline; } } PlewPromise* p = plew_timers[bi].p; plew_vnow = plew_timers[bi].deadline; plew_timers[bi] = plew_timers[--plew_timers_len]; plew_promise_resolve(p, 0); } }\n", 454});
}
void writeAsyncFrameName_c_Comp_f_Func(Comp* c, Func f) {
    plew_write((PlewString){"__af_", 5});
    if (f.hasRecv) {
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), f.recvStart, f.recvLen);
    plew_write((PlewString){"_", 1});
    }
    writeFnSelector_c_Comp_f_Func(&((*c)), f);
}
void rejectAsyncUnsupported_c_Comp_blockId_U64(Comp* c, uint64_t blockId) {
    Block b = Block_share(Array_Block_get((*c).blocks, (long long)(blockId)));
    Array_U64 stmts = Array_U64_share(b.stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).count)) {
    {
    Stmt _m1104 = Array_Stmt_get((*c).stmts, (long long)(Array_U64_get(stmts, (long long)(i))));
    if (_m1104.tag == 0) {
    }
    else if (_m1104.tag == 1) {
    }
    else if (_m1104.tag == 2) {
    }
    else if (_m1104.tag == 3) {
    }
    else if (_m1104.tag == 10) {
    }
    else if (_m1104.tag == 11) {
    }
    else if (_m1104.tag == 8) {
    }
    else if (_m1104.tag == 4) {
        uint64_t thenBlk = _m1104.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m1104.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m1104.data.If.hasElse;
        (void)hasElse;
    rejectAsyncUnsupported_c_Comp_blockId_U64(&((*c)), thenBlk);
    if (hasElse) {
    rejectAsyncUnsupported_c_Comp_blockId_U64(&((*c)), elseBlk);
    }
    }
    else if (_m1104.tag == 5) {
        uint64_t body = _m1104.data.While.body;
        (void)body;
    rejectAsyncUnsupported_c_Comp_blockId_U64(&((*c)), body);
    }
    else if (_m1104.tag == 7) {
        Array_MatchArm arms = _m1104.data.Match.arms;
        (void)arms;
    if ((long long)((arms).count) > 0) {
    if (Array_MatchArm_get(arms, (long long)(0)).isStruct) {
    compileError_msg_String((PlewString){"struct-destructure `match` is not yet supported inside an `async fn` (enum match is; this is additive)", 102});
    }
    }
    uint64_t ai = 0;
    while (ai < (long long)((arms).count)) {
    rejectAsyncUnsupported_c_Comp_blockId_U64(&((*c)), Array_MatchArm_get(arms, (long long)(ai)).body);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else {
    compileError_msg_String((PlewString){"this statement is not yet supported inside an `async fn` (for / give and mid-expression await are additive; if / while / match / bindings / calls / returns are supported)", 170});
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_release(stmts);
    Block_release(b);
}
void collectAsyncFields_c_Comp_blockId_U64(Comp* c, uint64_t blockId) {
    Block b = Block_share(Array_Block_get((*c).blocks, (long long)(blockId)));
    Array_U64 stmts = Array_U64_share(b.stmts);
    uint64_t i = 0;
    while (i < (long long)((stmts).count)) {
    {
    Stmt _m1105 = Array_Stmt_get((*c).stmts, (long long)(Array_U64_get(stmts, (long long)(i))));
    if (_m1105.tag == 0) {
        long long mutable = _m1105.data.Let.mutable;
        (void)mutable;
        uint64_t nameStart = _m1105.data.Let.nameStart;
        (void)nameStart;
        uint64_t nameLen = _m1105.data.Let.nameLen;
        (void)nameLen;
        uint64_t tyStart = _m1105.data.Let.tyStart;
        (void)tyStart;
        uint64_t tyLen = _m1105.data.Let.tyLen;
        (void)tyLen;
        long long tyIsArray = _m1105.data.Let.tyIsArray;
        (void)tyIsArray;
        uint64_t ty = _m1105.data.Let.ty;
        (void)ty;
        uint64_t init = _m1105.data.Let.init;
        (void)init;
    uint64_t cnum = nextAsyncVar_c_Comp(&((*c)));
    LetEff le = inferLetType_c_Comp_tyStart_U64_tyLen_U64_tyIsArray_Bool_ty_U64_init_U64(&((*c)), tyStart, tyLen, tyIsArray, ty, init);
    plew_write((PlewString){"    ", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), le.ty, le.start, le.len, le.arr);
    plew_write((PlewString){" ", 1});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){";\n", 2});
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), nameStart, nameLen, le.start, le.len, le.arr, le.ty, 0, mutable, 0, cnum);
    }
    else if (_m1105.tag == 4) {
        uint64_t thenBlk = _m1105.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m1105.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m1105.data.If.hasElse;
        (void)hasElse;
    collectAsyncFields_c_Comp_blockId_U64(&((*c)), thenBlk);
    if (hasElse) {
    collectAsyncFields_c_Comp_blockId_U64(&((*c)), elseBlk);
    }
    }
    else if (_m1105.tag == 5) {
        uint64_t body = _m1105.data.While.body;
        (void)body;
    collectAsyncFields_c_Comp_blockId_U64(&((*c)), body);
    }
    else if (_m1105.tag == 7) {
        uint64_t scrut = _m1105.data.Match.scrut;
        (void)scrut;
        Array_MatchArm arms = _m1105.data.Match.arms;
        (void)arms;
    uint64_t scrutRef = exprType_c_Comp_id_U64(&((*c)), scrut).ref;
    long long genericMatch = isGenericEnumInst_c_Comp_ref_U64(&((*c)), scrutRef);
    uint64_t ai = 0;
    while (ai < (long long)((arms).count)) {
    MatchArm a = MatchArm_share(Array_MatchArm_get(arms, (long long)(ai)));
    if (a.isWildcard) {
    }
    else {
    if (a.isStruct) {
    }
    else {
    collectAsyncMatchBinds_c_Comp_scrutRef_U64_genericMatch_Bool_arm_MatchArm(&((*c)), scrutRef, genericMatch, a);
    }
    }
    collectAsyncFields_c_Comp_blockId_U64(&((*c)), a.body);
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    MatchArm_release(a);
    }
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U64_release(stmts);
    Block_release(b);
}
void collectAsyncMatchBinds_c_Comp_scrutRef_U64_genericMatch_Bool_arm_MatchArm(Comp* c, uint64_t scrutRef, long long genericMatch, MatchArm arm) {
    Array_Bind binds = Array_Bind_share(arm.binds);
    uint64_t bi = 0;
    while (bi < (long long)((binds).count)) {
    Bind bd = Array_Bind_get(binds, (long long)(bi));
    uint64_t cnum = nextAsyncVar_c_Comp(&((*c)));
    plew_write((PlewString){"    ", 4});
    if (genericMatch) {
    genBindTypeInst_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), scrutRef, arm.variantStart, arm.variantLen, bd.fieldStart, bd.fieldLen);
    }
    else {
    genBindType_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_bindStart_U64_bindLen_U64(&((*c)), arm.enumStart, arm.enumLen, arm.variantStart, arm.variantLen, bd.fieldStart, bd.fieldLen);
    }
    plew_write((PlewString){" ", 1});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), bd.nameStart, bd.nameLen, cnum);
    plew_write((PlewString){";\n", 2});
    if (genericMatch) {
    TypeInfo bti = genericEnumFieldTypeInfo_c_Comp_instRef_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64(&((*c)), scrutRef, arm.variantStart, arm.variantLen, bd.fieldStart, bd.fieldLen);
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), bd.nameStart, bd.nameLen, bti.nameStart, bti.nameLen, (bti.kind == 3), 0, 0, 0, 0, cnum);
    }
    else {
    addBindLocalCn_c_Comp_enumStart_U64_enumLen_U64_variantStart_U64_variantLen_U64_fieldStart_U64_fieldLen_U64_bindStart_U64_bindLen_U64_cnum_U64(&((*c)), arm.enumStart, arm.enumLen, arm.variantStart, arm.variantLen, bd.fieldStart, bd.fieldLen, bd.nameStart, bd.nameLen, cnum);
    }
    bi = ({ uint64_t __ov; if (__builtin_add_overflow((bi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_Bind_release(binds);
}
void emitAsyncSuspend_c_Comp_operandId_U64(Comp* c, uint64_t operandId) {
    uint64_t st = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).asyncState), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    (*c).asyncState = st;
    plew_write((PlewString){"    __f->__sub = (", 18});
    genExpr_c_Comp_id_U64(&((*c)), operandId);
    plew_write((PlewString){");\n    __f->__state = ", 22});
    writeU64_n_U64(st);
    plew_write((PlewString){";\n    if (!__f->__sub->done) { __f->__sub->k = ", 47});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), Array_Func_get((*c).funcs, (long long)((*c).curAsyncFn)));
    plew_write((PlewString){"_resume; __f->__sub->kframe = (void*)__f; return; }\n    __L", 59});
    writeU64_n_U64(st);
    plew_write((PlewString){": ;\n", 4});
}
uint64_t nextAsyncVar_c_Comp(Comp* c) {
    (*c).asyncVarSeq = ({ uint64_t __ov; if (__builtin_add_overflow(((*c).asyncVarSeq), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    { uint64_t __ret1106 = (*c).asyncVarSeq;
    return __ret1106; }
}
void genAsyncLet_c_Comp_nameStart_U64_nameLen_U64_effStart_U64_effLen_U64_effArr_Bool_effTy_U64_init_U64_mutable_Bool(Comp* c, uint64_t nameStart, uint64_t nameLen, uint64_t effStart, uint64_t effLen, long long effArr, uint64_t effTy, uint64_t init, long long mutable) {
    uint64_t cnum = nextAsyncVar_c_Comp(&((*c)));
    {
    Expr _m1107 = Array_Expr_get((*c).exprs, (long long)(init));
    if (_m1107.tag == 19) {
        uint64_t operand = _m1107.data.Await.operand;
        (void)operand;
    emitAsyncSuspend_c_Comp_operandId_U64(&((*c)), operand);
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), nameStart, nameLen, effStart, effLen, effArr, effTy, 0, mutable, 0, cnum);
    plew_write((PlewString){"    __f->", 9});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){" = (", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), effTy, effStart, effLen, effArr);
    plew_write((PlewString){")(__f->__sub->value);\n", 22});
    }
    else {
    checkLitSpan_c_Comp_id_U64_tyStart_U64_tyLen_U64_isArray_Bool(&((*c)), init, effStart, effLen, effArr);
    addLocalCn_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool_cnum_U64(&((*c)), nameStart, nameLen, effStart, effLen, effArr, effTy, 0, mutable, 0, cnum);
    plew_write((PlewString){"    __f->", 9});
    writeNameCn_c_Comp_start_U64_len_U64_cnum_U64(&((*c)), nameStart, nameLen, cnum);
    plew_write((PlewString){" = ", 3});
    if (effArr) {
    genArrayValue_c_Comp_exprId_U64_elemStart_U64_elemLen_U64(&((*c)), init, effStart, effLen);
    }
    else {
    genCopyValue_c_Comp_exprId_U64_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), init, effTy, effStart, effLen, 0);
    }
    plew_write((PlewString){";\n", 2});
    }
    }
}
void genAsyncReturn_c_Comp_value_U64_hasValue_Bool(Comp* c, uint64_t value, long long hasValue) {
    if (hasValue) {
    {
    Expr _m1108 = Array_Expr_get((*c).exprs, (long long)(value));
    if (_m1108.tag == 19) {
        uint64_t operand = _m1108.data.Await.operand;
        (void)operand;
    emitAsyncSuspend_c_Comp_operandId_U64(&((*c)), operand);
    plew_write((PlewString){"    plew_promise_resolve(__f->__self, (long long)(__f->__sub->value));\n", 71});
    }
    else {
    plew_write((PlewString){"    plew_promise_resolve(__f->__self, (long long)(", 50});
    genExpr_c_Comp_id_U64(&((*c)), value);
    plew_write((PlewString){"));\n", 4});
    }
    }
    }
    else {
    plew_write((PlewString){"    plew_promise_resolve(__f->__self, 0);\n", 42});
    }
    plew_write((PlewString){"    free(__f);\n    return;\n", 27});
}
void emitAsyncFrameStruct_c_Comp_fi_U64(Comp* c, uint64_t fi) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    Array_Local savedLocals = Array_Local_share((*c).locals);
    (*c).locals = Array_Local_new();
    plew_write((PlewString){"typedef struct {\n", 17});
    plew_write((PlewString){"    int __state; PlewPromise* __self; PlewPromise* __sub;\n", 58});
    Array_Param params = Array_Param_share(f.params);
    uint64_t pi = 0;
    while (pi < (long long)((params).count)) {
    Param p = Array_Param_get(params, (long long)(pi));
    plew_write((PlewString){"    ", 4});
    genCTypeOf_c_Comp_tyRef_U64_fallStart_U64_fallLen_U64_isArray_Bool(&((*c)), p.ty, p.tyStart, p.tyLen, p.tyIsArray);
    plew_write((PlewString){" ", 1});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
    plew_write((PlewString){";\n", 2});
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p.nameStart, p.nameLen, p.tyStart, p.tyLen, p.tyIsArray, p.ty, 0, 0, 0);
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    (*c).asyncVarSeq = 0;
    collectAsyncFields_c_Comp_blockId_U64(&((*c)), f.body);
    plew_write((PlewString){"} ", 2});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){";\n", 2});
    plew_write((PlewString){"static void ", 12});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"_resume(void*);\n", 16});
    (*c).locals = Array_Local_share(savedLocals);
    Array_Param_release(params);
    Array_Local_release(savedLocals);
    Func_release(f);
}
void emitAsyncDecls_c_Comp(Comp* c) {
    uint64_t i = 0;
    while (i < (long long)(((*c).funcs).count)) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(i)));
    if (f.isAsync) {
    if ((long long)((f.typeParams).count) > 0) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), f.nameStart), (PlewString){"generic `async fn` is not yet supported", 39});
    }
    else {
    if (f.hasRecv) {
    compileErrorAt_line_I64_msg_String(lineOf_c_Comp_offset_U64(&((*c)), f.nameStart), (PlewString){"`async fn` methods are not yet supported (only free `async fn` for now)", 71});
    }
    else {
    emitAsyncFrameStruct_c_Comp_fi_U64(&((*c)), i);
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Func_release(f);
    }
}
void genAsyncFunc_c_Comp_fi_U64(Comp* c, uint64_t fi) {
    Func f = Func_share(Array_Func_get((*c).funcs, (long long)(fi)));
    long long isMain = nameIsMain_c_Comp_f_Func(&((*c)), f);
    Array_Param params = Array_Param_share(f.params);
    if (isMain) {
    plew_write((PlewString){"int main(int argc, char** argv) {\n", 34});
    plew_write((PlewString){"    plew_argc = argc; plew_argv = argv;\n", 40});
    }
    else {
    genSignature_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){" {\n", 3});
    }
    plew_write((PlewString){"    ", 4});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"* __f = (", 9});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"*)malloc(sizeof(", 16});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"));\n    __f->__state = 0;\n", 26});
    uint64_t pi = 0;
    while (pi < (long long)((params).count)) {
    Param p = Array_Param_get(params, (long long)(pi));
    plew_write((PlewString){"    __f->", 9});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
    plew_write((PlewString){" = ", 3});
    writeSpan_c_Comp_start_U64_len_U64(&((*c)), p.nameStart, p.nameLen);
    plew_write((PlewString){";\n", 2});
    pi = ({ uint64_t __ov; if (__builtin_add_overflow((pi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"    PlewPromise* __self = plew_promise_new();\n    __f->__self = __self;\n    ", 76});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"_resume((void*)__f);\n", 21});
    if (isMain) {
    plew_write((PlewString){"    plew_loop_run();\n    return 0;\n}\n", 37});
    }
    else {
    plew_write((PlewString){"    return __self;\n}\n", 21});
    }
    rejectAsyncUnsupported_c_Comp_blockId_U64(&((*c)), f.body);
    plew_write((PlewString){"static void ", 12});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"_resume(void* __fp) {\n    ", 26});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"* __f = (", 9});
    writeAsyncFrameName_c_Comp_f_Func(&((*c)), f);
    plew_write((PlewString){"*)__fp;\n", 8});
    uint64_t nstates = countAsyncAwaits_c_Comp_blockId_U64(&((*c)), f.body);
    if (nstates > 0) {
    plew_write((PlewString){"    switch (__f->__state) {\n", 28});
    uint64_t s = 1;
    while (s <= nstates) {
    plew_write((PlewString){"        case ", 13});
    writeU64_n_U64(s);
    plew_write((PlewString){": goto __L", 10});
    writeU64_n_U64(s);
    plew_write((PlewString){";\n", 2});
    s = ({ uint64_t __ov; if (__builtin_add_overflow((s), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    plew_write((PlewString){"        default: break;\n    }\n", 30});
    }
    Array_Local savedLocals = Array_Local_share((*c).locals);
    (*c).locals = Array_Local_new();
    (*c).curAsync = 1;
    (*c).asyncState = 0;
    (*c).asyncVarSeq = 0;
    (*c).curAsyncFn = fi;
    (*c).curIsMain = 0;
    (*c).curHasRecv = 0;
    (*c).curBranchBase = 0;
    (*c).curRetVoid = 1;
    uint64_t qi = 0;
    while (qi < (long long)((params).count)) {
    Param p2 = Array_Param_get(params, (long long)(qi));
    addLocal_c_Comp_nameStart_U64_nameLen_U64_tyStart_U64_tyLen_U64_isArray_Bool_ty_U64_isInout_Bool_isMut_Bool_owned_Bool(&((*c)), p2.nameStart, p2.nameLen, p2.tyStart, p2.tyLen, p2.tyIsArray, p2.ty, 0, 0, 0);
    qi = ({ uint64_t __ov; if (__builtin_add_overflow((qi), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    genBlock_c_Comp_id_U64(&((*c)), f.body);
    plew_write((PlewString){"    plew_promise_resolve(__f->__self, 0);\n    free(__f);\n}\n", 59});
    (*c).curAsync = 0;
    (*c).locals = Array_Local_share(savedLocals);
    Array_Local_release(savedLocals);
    Array_Param_release(params);
    Func_release(f);
}
uint64_t countAsyncAwaits_c_Comp_blockId_U64(Comp* c, uint64_t blockId) {
    Block b = Block_share(Array_Block_get((*c).blocks, (long long)(blockId)));
    Array_U64 stmts = Array_U64_share(b.stmts);
    uint64_t n = 0;
    uint64_t i = 0;
    while (i < (long long)((stmts).count)) {
    {
    Stmt _m1109 = Array_Stmt_get((*c).stmts, (long long)(Array_U64_get(stmts, (long long)(i))));
    if (_m1109.tag == 0) {
        uint64_t init = _m1109.data.Let.init;
        (void)init;
    if (exprIsAwait_c_Comp_id_U64(&((*c)), init)) {
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m1109.tag == 3) {
        uint64_t value = _m1109.data.Return.value;
        (void)value;
        long long hasValue = _m1109.data.Return.hasValue;
        (void)hasValue;
    if (hasValue) {
    if (exprIsAwait_c_Comp_id_U64(&((*c)), value)) {
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    else if (_m1109.tag == 2) {
        uint64_t expr = _m1109.data.ExprStmt.expr;
        (void)expr;
    if (exprIsAwait_c_Comp_id_U64(&((*c)), expr)) {
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m1109.tag == 4) {
        uint64_t thenBlk = _m1109.data.If.thenBlk;
        (void)thenBlk;
        uint64_t elseBlk = _m1109.data.If.elseBlk;
        (void)elseBlk;
        long long hasElse = _m1109.data.If.hasElse;
        (void)hasElse;
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (countAsyncAwaits_c_Comp_blockId_U64(&((*c)), thenBlk)), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    if (hasElse) {
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (countAsyncAwaits_c_Comp_blockId_U64(&((*c)), elseBlk)), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else if (_m1109.tag == 5) {
        uint64_t body = _m1109.data.While.body;
        (void)body;
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (countAsyncAwaits_c_Comp_blockId_U64(&((*c)), body)), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else if (_m1109.tag == 7) {
        Array_MatchArm arms = _m1109.data.Match.arms;
        (void)arms;
    uint64_t ai = 0;
    while (ai < (long long)((arms).count)) {
    n = ({ uint64_t __ov; if (__builtin_add_overflow((n), (countAsyncAwaits_c_Comp_blockId_U64(&((*c)), Array_MatchArm_get(arms, (long long)(ai)).body)), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    ai = ({ uint64_t __ov; if (__builtin_add_overflow((ai), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    else {
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret1110 = n;
    Array_U64_release(stmts);
    Block_release(b);
    return __ret1110; }
    Array_U64_release(stmts);
    Block_release(b);
}
long long exprIsAwait_c_Comp_id_U64(Comp* c, uint64_t id) {
    {
    Expr _m1111 = Array_Expr_get((*c).exprs, (long long)(id));
    if (_m1111.tag == 19) {
    { long long __ret1112 = 1;
    return __ret1112; }
    }
    else {
    { long long __ret1113 = 0;
    return __ret1113; }
    }
    }
}
long long isPathTokKind_k_Kind(Kind k) {
    {
    Kind _m1114 = k;
    if (_m1114.tag == 40) {
    { long long __ret1115 = 1;
    return __ret1115; }
    }
    else if (_m1114.tag == 51) {
    { long long __ret1116 = 1;
    return __ret1116; }
    }
    else if (_m1114.tag == 5) {
    { long long __ret1117 = 1;
    return __ret1117; }
    }
    else {
    { long long __ret1118 = 0;
    return __ret1118; }
    }
    }
}
Array_Bind collectParts_rootBytes_AU8_toks_ATok(Array_U8 rootBytes, Array_Tok toks) {
    Array_Bind parts = Array_Bind_new();
    uint64_t i = 0;
    while (i < (long long)((toks).count)) {
    Tok t = Array_Tok_get(toks, (long long)(i));
    long long isKw = 0;
    long long isImport = 0;
    {
    Kind _m1119 = t.kind;
    if (_m1119.tag == 5) {
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(rootBytes), t.start, t.len, (PlewString){"part", 4})) {
    isKw = 1;
    }
    if (rangeEquals_bytes_AU8_start_U64_len_U64_kw_String(Array_U8_share(rootBytes), t.start, t.len, (PlewString){"import", 6})) {
    isKw = 1;
    isImport = 1;
    }
    }
    else {
    }
    }
    if (isKw) {
    if (({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }) < (long long)((toks).count)) {
    Tok first = Array_Tok_get(toks, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; })));
    long long starts = 0;
    {
    Kind _m1120 = first.kind;
    if (_m1120.tag == 40) {
    starts = 1;
    }
    else if (_m1120.tag == 51) {
    starts = 1;
    }
    else {
    if (Array_U8_get(rootBytes, (long long)(first.start)) == 64) {
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
    if (j < (long long)((toks).count)) {
    Tok nt = Array_Tok_get(toks, (long long)(j));
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
    uint64_t kind = 0;
    if (isImport) {
    kind = 1;
    }
    Array_Bind_append_value_T(&(parts), (Bind){.nameStart = pathStart, .nameLen = pl, .fieldStart = kind, .fieldLen = pl});
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Array_Bind __ret1121 = Array_Bind_share(parts);
    Array_Bind_release(parts);
    return __ret1121; }
    Array_Bind_release(parts);
}
uint64_t stripParents_path_AU8_baseLen_U64_n_U64(Array_U8 path, uint64_t baseLen, uint64_t n) {
    uint64_t end = baseLen;
    uint64_t c = 0;
    while (c < n) {
    if (end > 0) {
    end = ({ uint64_t __ov; if (__builtin_sub_overflow((end), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    long long go = 1;
    while (go) {
    if (end > 0) {
    if (Array_U8_get(path, (long long)(({ uint64_t __ov; if (__builtin_sub_overflow((end), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
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
    { uint64_t __ret1122 = end;
    return __ret1122; }
}
Array_U8 resolveImport_src_AU8_pStart_U64_pLen_U64_importer_AU8_baseLen_U64_srcRoot_AU8_srcRootLen_U64_stdRoot_AU8_stdRootLen_U64(Array_U8 src, uint64_t pStart, uint64_t pLen, Array_U8 importer, uint64_t baseLen, Array_U8 srcRoot, uint64_t srcRootLen, Array_U8 stdRoot, uint64_t stdRootLen) {
    Array_U8 out = Array_U8_new();
    if (pLen == 0) {
    { Array_U8 __ret1123 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1123; }
    }
    uint64_t end = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (pLen), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    unsigned char b0 = Array_U8_get(src, (long long)(pStart));
    if (b0 == 64) {
    if (pLen >= 5) {
    if (Array_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 83) {
    if (Array_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 116) {
    if (Array_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (3), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 100) {
    if (Array_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (4), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
    if (stdRootLen == 0) {
    { Array_U8 __ret1124 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1124; }
    }
    uint64_t si = 0;
    while (si < stdRootLen) {
    Array_U8_append_value_T(&(out), Array_U8_get(stdRoot, (long long)(si)));
    si = ({ uint64_t __ov; if (__builtin_add_overflow((si), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t sj = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (5), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (sj < end) {
    Array_U8_append_value_T(&(out), Array_U8_get(src, (long long)(sj)));
    sj = ({ uint64_t __ov; if (__builtin_add_overflow((sj), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U8_append_value_T(&(out), 46);
    Array_U8_append_value_T(&(out), 112);
    Array_U8_append_value_T(&(out), 119);
    { Array_U8 __ret1125 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1125; }
    }
    }
    }
    }
    }
    { Array_U8 __ret1126 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1126; }
    }
    if (b0 == 47) {
    if (srcRootLen == 0) {
    { Array_U8 __ret1127 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1127; }
    }
    uint64_t i = 0;
    while (i < srcRootLen) {
    Array_U8_append_value_T(&(out), Array_U8_get(srcRoot, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t j = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    while (j < end) {
    Array_U8_append_value_T(&(out), Array_U8_get(src, (long long)(j)));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U8_append_value_T(&(out), 46);
    Array_U8_append_value_T(&(out), 112);
    Array_U8_append_value_T(&(out), 119);
    { Array_U8 __ret1128 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1128; }
    }
    uint64_t rest = pStart;
    uint64_t parents = 0;
    if (({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }) < end) {
    if (Array_U8_get(src, (long long)(pStart)) == 46) {
    if (Array_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((pStart), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
    rest = ({ uint64_t __ov; if (__builtin_add_overflow((pStart), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    else {
    long long go = 1;
    while (go) {
    if (({ uint64_t __ov; if (__builtin_add_overflow((rest), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }) < end) {
    if (Array_U8_get(src, (long long)(rest)) == 46) {
    if (Array_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((rest), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 46) {
    if (Array_U8_get(src, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((rest), (2), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) == 47) {
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
    uint64_t dirLen = stripParents_path_AU8_baseLen_U64_n_U64(Array_U8_share(importer), baseLen, parents);
    uint64_t k = 0;
    while (k < dirLen) {
    Array_U8_append_value_T(&(out), Array_U8_get(importer, (long long)(k)));
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    uint64_t m = rest;
    while (m < end) {
    Array_U8_append_value_T(&(out), Array_U8_get(src, (long long)(m)));
    m = ({ uint64_t __ov; if (__builtin_add_overflow((m), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U8_append_value_T(&(out), 46);
    Array_U8_append_value_T(&(out), 112);
    Array_U8_append_value_T(&(out), 119);
    { Array_U8 __ret1129 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1129; }
    Array_U8_release(out);
}
void appendBytes_into_AU8_from_AU8(Array_U8* into, Array_U8 from) {
    uint64_t i = 0;
    while (i < (long long)((from).count)) {
    Array_U8_append_value_T(&((*into)), Array_U8_get(from, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
}
Array_U8 extractSpan_buf_AU8_start_U64_len_U64(Array_U8 buf, uint64_t start, uint64_t len) {
    Array_U8 out = Array_U8_new();
    uint64_t i = 0;
    while (i < len) {
    Array_U8_append_value_T(&(out), Array_U8_get(buf, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((start), (i), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { Array_U8 __ret1130 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1130; }
    Array_U8_release(out);
}
uint64_t dirPrefixLen_path_AU8(Array_U8 path) {
    uint64_t pre = 0;
    uint64_t k = 0;
    while (k < (long long)((path).count)) {
    if (Array_U8_get(path, (long long)(k)) == 47) {
    pre = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    k = ({ uint64_t __ov; if (__builtin_add_overflow((k), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { uint64_t __ret1131 = pre;
    return __ret1131; }
}
Array_U8 computeStdRoot_arg0_AU8(Array_U8 arg0) {
    uint64_t pre = dirPrefixLen_path_AU8(Array_U8_share(arg0));
    Array_U8 out = Array_U8_new();
    uint64_t i = 0;
    while (i < pre) {
    Array_U8_append_value_T(&(out), Array_U8_get(arg0, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U8_append_value_T(&(out), 115);
    Array_U8_append_value_T(&(out), 116);
    Array_U8_append_value_T(&(out), 100);
    Array_U8_append_value_T(&(out), 47);
    { Array_U8 __ret1132 = Array_U8_share(out);
    Array_U8_release(out);
    return __ret1132; }
    Array_U8_release(out);
}
Array_U8 findSrcRoot_entry_AU8(Array_U8 entry) {
    uint64_t dirLen = dirPrefixLen_path_AU8(Array_U8_share(entry));
    long long go = 1;
    while (go) {
    Array_U8 mani = Array_U8_new();
    uint64_t i = 0;
    while (i < dirLen) {
    Array_U8_append_value_T(&(mani), Array_U8_get(entry, (long long)(i)));
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U8 mn = Array_U8_share(({ PlewString __s = (PlewString){"Plew.toml", 9}; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; }));
    appendBytes_into_AU8_from_AU8(&(mani), Array_U8_share(mn));
    if (plew_fileExists(Array_U8_share(mani))) {
    Array_U8 sr = Array_U8_new();
    uint64_t j = 0;
    while (j < dirLen) {
    Array_U8_append_value_T(&(sr), Array_U8_get(entry, (long long)(j)));
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U8 sx = Array_U8_share(({ PlewString __s = (PlewString){"src/", 4}; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; }));
    appendBytes_into_AU8_from_AU8(&(sr), Array_U8_share(sx));
    { Array_U8 __ret1133 = Array_U8_share(sr);
    Array_U8_release(sx);
    Array_U8_release(sr);
    Array_U8_release(mn);
    Array_U8_release(mani);
    return __ret1133; }
    Array_U8_release(sx);
    Array_U8_release(sr);
    }
    if (dirLen == 0) {
    go = 0;
    }
    else {
    uint64_t nd = stripParents_path_AU8_baseLen_U64_n_U64(Array_U8_share(entry), dirLen, 1);
    if (nd == dirLen) {
    go = 0;
    }
    else {
    dirLen = nd;
    }
    }
    Array_U8_release(mn);
    Array_U8_release(mani);
    }
    Array_U8 empty = Array_U8_new();
    { Array_U8 __ret1134 = Array_U8_share(empty);
    Array_U8_release(empty);
    return __ret1134; }
    Array_U8_release(empty);
}
long long pathSeen_buf_AU8_loaded_ABind_path_AU8(Array_U8 buf, Array_Bind loaded, Array_U8 path) {
    uint64_t i = 0;
    while (i < (long long)((loaded).count)) {
    Bind b = Array_Bind_get(loaded, (long long)(i));
    if (b.nameLen == (long long)((path).count)) {
    long long eq = 1;
    uint64_t j = 0;
    while (j < (long long)((path).count)) {
    if (Array_U8_get(buf, (long long)(({ uint64_t __ov; if (__builtin_add_overflow((b.nameStart), (j), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; }))) != Array_U8_get(path, (long long)(j))) {
    eq = 0;
    }
    j = ({ uint64_t __ov; if (__builtin_add_overflow((j), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    if (eq) {
    { long long __ret1135 = 1;
    return __ret1135; }
    }
    }
    i = ({ uint64_t __ov; if (__builtin_add_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    { long long __ret1136 = 0;
    return __ret1136; }
}
void assert_cond_Bool_message_String(long long cond, PlewString message) {
    if (cond) {
    }
    else {
    plew_panic(message);
    }
}
long long String_isEmpty(PlewString self) {
    { long long __ret1137 = ((long long)((({ PlewString __s = self; Array_U8 __b; __b.data = (unsigned char*)plew_rawbuf_alloc(sizeof(unsigned char), __s.len); for (long long __i = 0; __i < __s.len; __i++) __b.data[__i] = (unsigned char)__s.data[__i]; __b.count = __s.len; __b; })).count) == 0);
    return __ret1137; }
}
unsigned char digitByteI_d_I64(int64_t d) {
    if (d == 0) {
    { unsigned char __ret1138 = 48;
    return __ret1138; }
    }
    if (d == 1) {
    { unsigned char __ret1139 = 49;
    return __ret1139; }
    }
    if (d == 2) {
    { unsigned char __ret1140 = 50;
    return __ret1140; }
    }
    if (d == 3) {
    { unsigned char __ret1141 = 51;
    return __ret1141; }
    }
    if (d == 4) {
    { unsigned char __ret1142 = 52;
    return __ret1142; }
    }
    if (d == 5) {
    { unsigned char __ret1143 = 53;
    return __ret1143; }
    }
    if (d == 6) {
    { unsigned char __ret1144 = 54;
    return __ret1144; }
    }
    if (d == 7) {
    { unsigned char __ret1145 = 55;
    return __ret1145; }
    }
    if (d == 8) {
    { unsigned char __ret1146 = 56;
    return __ret1146; }
    }
    { unsigned char __ret1147 = 57;
    return __ret1147; }
}
unsigned char digitByteU_d_U64(uint64_t d) {
    if (d == 0) {
    { unsigned char __ret1148 = 48;
    return __ret1148; }
    }
    if (d == 1) {
    { unsigned char __ret1149 = 49;
    return __ret1149; }
    }
    if (d == 2) {
    { unsigned char __ret1150 = 50;
    return __ret1150; }
    }
    if (d == 3) {
    { unsigned char __ret1151 = 51;
    return __ret1151; }
    }
    if (d == 4) {
    { unsigned char __ret1152 = 52;
    return __ret1152; }
    }
    if (d == 5) {
    { unsigned char __ret1153 = 53;
    return __ret1153; }
    }
    if (d == 6) {
    { unsigned char __ret1154 = 54;
    return __ret1154; }
    }
    if (d == 7) {
    { unsigned char __ret1155 = 55;
    return __ret1155; }
    }
    if (d == 8) {
    { unsigned char __ret1156 = 56;
    return __ret1156; }
    }
    { unsigned char __ret1157 = 57;
    return __ret1157; }
}
PlewString I64_format_format_String(int64_t self, PlewString format) {
    int64_t n = self;
    long long neg = 0;
    if (n < 0) {
    neg = 1;
    }
    Array_U8 digits = Array_U8_new();
    if (n == 0) {
    Array_U8_append_value_T(&(digits), 48);
    }
    while (n != 0) {
    int64_t d = ({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); (__dr == -1 ? 0 : __dl % __dr); });
    if (d < 0) {
    d = ({ int64_t __ov; if (__builtin_sub_overflow((0), (d), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    }
    Array_U8_append_value_T(&(digits), digitByteI_d_I64(d));
    n = ({ int64_t __dl = (n); int64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); if (__dr == -1 && __dl == INT64_MIN) plew_panic((PlewString){"integer overflow", 16}); __dl / __dr; });
    }
    Array_U8 out = Array_U8_new();
    if (neg) {
    Array_U8_append_value_T(&(out), 45);
    }
    uint64_t i = (long long)((digits).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_U8_append_value_T(&(out), Array_U8_get(digits, (long long)(i)));
    }
    { PlewString __ret1158 = plew_stringFromBytes(Array_U8_share(out));
    Array_U8_release(out);
    Array_U8_release(digits);
    return __ret1158; }
    Array_U8_release(out);
    Array_U8_release(digits);
}
PlewString U64_format_format_String(uint64_t self, PlewString format) {
    uint64_t n = self;
    Array_U8 digits = Array_U8_new();
    if (n == 0) {
    Array_U8_append_value_T(&(digits), 48);
    }
    while (n != 0) {
    uint64_t d = ({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"remainder by zero", 17}); __dl % __dr; });
    Array_U8_append_value_T(&(digits), digitByteU_d_U64(d));
    n = ({ uint64_t __dl = (n); uint64_t __dr = (10); if (__dr == 0) plew_panic((PlewString){"division by zero", 16}); __dl / __dr; });
    }
    Array_U8 out = Array_U8_new();
    uint64_t i = (long long)((digits).count);
    while (i > 0) {
    i = ({ uint64_t __ov; if (__builtin_sub_overflow((i), (1), &__ov)) plew_panic((PlewString){"integer overflow", 16}); __ov; });
    Array_U8_append_value_T(&(out), Array_U8_get(digits, (long long)(i)));
    }
    { PlewString __ret1159 = plew_stringFromBytes(Array_U8_share(out));
    Array_U8_release(out);
    Array_U8_release(digits);
    return __ret1159; }
    Array_U8_release(out);
    Array_U8_release(digits);
}
PlewString I8_format_format_String(int8_t self, PlewString format) {
    { PlewString __ret1160 = I64_format_format_String(((int64_t)(self)), format);
    return __ret1160; }
}
PlewString I16_format_format_String(int16_t self, PlewString format) {
    { PlewString __ret1161 = I64_format_format_String(((int64_t)(self)), format);
    return __ret1161; }
}
PlewString I32_format_format_String(int32_t self, PlewString format) {
    { PlewString __ret1162 = I64_format_format_String(((int64_t)(self)), format);
    return __ret1162; }
}
PlewString U8_format_format_String(unsigned char self, PlewString format) {
    { PlewString __ret1163 = U64_format_format_String(((uint64_t)(self)), format);
    return __ret1163; }
}
PlewString U16_format_format_String(uint16_t self, PlewString format) {
    { PlewString __ret1164 = U64_format_format_String(((uint64_t)(self)), format);
    return __ret1164; }
}
PlewString U32_format_format_String(uint32_t self, PlewString format) {
    { PlewString __ret1165 = U64_format_format_String(((uint64_t)(self)), format);
    return __ret1165; }
}
PlewString Bool_format_format_String(long long self, PlewString format) {
    if (self) {
    { PlewString __ret1166 = (PlewString){"1", 1};
    return __ret1166; }
    }
    else {
    { PlewString __ret1167 = (PlewString){"0", 1};
    return __ret1167; }
    }
}
void Array_U8_append_value_T(Array_U8* self, unsigned char value) {
    Array_U8_push(&((*self)), value);
}
unsigned char Array_U8_get_i_U64(Array_U8 self, uint64_t i) {
    { unsigned char __ret1168 = Array_U8_get((self), (long long)(i));
    return __ret1168; }
}
void Array_U8_set_i_U64_value_T(Array_U8* self, uint64_t i, unsigned char value) {
    Array_U8_set(&((*self)), (long long)(i), value);
}
void Array_Bind_append_value_T(Array_Bind* self, Bind value) {
    Array_Bind_push(&((*self)), value);
}
Bind Array_Bind_get_i_U64(Array_Bind self, uint64_t i) {
    { Bind __ret1169 = Array_Bind_get((self), (long long)(i));
    return __ret1169; }
}
void Array_Bind_set_i_U64_value_T(Array_Bind* self, uint64_t i, Bind value) {
    Array_Bind_set(&((*self)), (long long)(i), value);
}
void Array_Tok_append_value_T(Array_Tok* self, Tok value) {
    Array_Tok_push(&((*self)), value);
}
Tok Array_Tok_get_i_U64(Array_Tok self, uint64_t i) {
    { Tok __ret1170 = Array_Tok_get((self), (long long)(i));
    return __ret1170; }
}
void Array_Tok_set_i_U64_value_T(Array_Tok* self, uint64_t i, Tok value) {
    Array_Tok_set(&((*self)), (long long)(i), value);
}
void Array_U64_append_value_T(Array_U64* self, uint64_t value) {
    Array_U64_push(&((*self)), value);
}
uint64_t Array_U64_get_i_U64(Array_U64 self, uint64_t i) {
    { uint64_t __ret1171 = Array_U64_get((self), (long long)(i));
    return __ret1171; }
}
void Array_U64_set_i_U64_value_T(Array_U64* self, uint64_t i, uint64_t value) {
    Array_U64_set(&((*self)), (long long)(i), value);
}
void Array_Arg_append_value_T(Array_Arg* self, Arg value) {
    Array_Arg_push(&((*self)), value);
}
Arg Array_Arg_get_i_U64(Array_Arg self, uint64_t i) {
    { Arg __ret1172 = Array_Arg_get((self), (long long)(i));
    return __ret1172; }
}
void Array_Arg_set_i_U64_value_T(Array_Arg* self, uint64_t i, Arg value) {
    Array_Arg_set(&((*self)), (long long)(i), value);
}
void Array_MakeField_append_value_T(Array_MakeField* self, MakeField value) {
    Array_MakeField_push(&((*self)), value);
}
MakeField Array_MakeField_get_i_U64(Array_MakeField self, uint64_t i) {
    { MakeField __ret1173 = Array_MakeField_get((self), (long long)(i));
    return __ret1173; }
}
void Array_MakeField_set_i_U64_value_T(Array_MakeField* self, uint64_t i, MakeField value) {
    Array_MakeField_set(&((*self)), (long long)(i), value);
}
void Array_MatchArm_append_value_T(Array_MatchArm* self, MatchArm value) {
    Array_MatchArm_push(&((*self)), value);
}
MatchArm Array_MatchArm_get_i_U64(Array_MatchArm self, uint64_t i) {
    { MatchArm __ret1174 = Array_MatchArm_get((self), (long long)(i));
    return __ret1174; }
}
void Array_MatchArm_set_i_U64_value_T(Array_MatchArm* self, uint64_t i, MatchArm value) {
    Array_MatchArm_set(&((*self)), (long long)(i), value);
}
void Array_Param_append_value_T(Array_Param* self, Param value) {
    Array_Param_push(&((*self)), value);
}
Param Array_Param_get_i_U64(Array_Param self, uint64_t i) {
    { Param __ret1175 = Array_Param_get((self), (long long)(i));
    return __ret1175; }
}
void Array_Param_set_i_U64_value_T(Array_Param* self, uint64_t i, Param value) {
    Array_Param_set(&((*self)), (long long)(i), value);
}
void Array_FieldDef_append_value_T(Array_FieldDef* self, FieldDef value) {
    Array_FieldDef_push(&((*self)), value);
}
FieldDef Array_FieldDef_get_i_U64(Array_FieldDef self, uint64_t i) {
    { FieldDef __ret1176 = Array_FieldDef_get((self), (long long)(i));
    return __ret1176; }
}
void Array_FieldDef_set_i_U64_value_T(Array_FieldDef* self, uint64_t i, FieldDef value) {
    Array_FieldDef_set(&((*self)), (long long)(i), value);
}
void Array_Func_append_value_T(Array_Func* self, Func value) {
    Array_Func_push(&((*self)), value);
}
Func Array_Func_get_i_U64(Array_Func self, uint64_t i) {
    { Func __ret1177 = Array_Func_get((self), (long long)(i));
    return __ret1177; }
}
void Array_Func_set_i_U64_value_T(Array_Func* self, uint64_t i, Func value) {
    Array_Func_set(&((*self)), (long long)(i), value);
}
void Array_Variant_append_value_T(Array_Variant* self, Variant value) {
    Array_Variant_push(&((*self)), value);
}
Variant Array_Variant_get_i_U64(Array_Variant self, uint64_t i) {
    { Variant __ret1178 = Array_Variant_get((self), (long long)(i));
    return __ret1178; }
}
void Array_Variant_set_i_U64_value_T(Array_Variant* self, uint64_t i, Variant value) {
    Array_Variant_set(&((*self)), (long long)(i), value);
}
void Array_Expr_append_value_T(Array_Expr* self, Expr value) {
    Array_Expr_push(&((*self)), value);
}
Expr Array_Expr_get_i_U64(Array_Expr self, uint64_t i) {
    { Expr __ret1179 = Array_Expr_get((self), (long long)(i));
    return __ret1179; }
}
void Array_Expr_set_i_U64_value_T(Array_Expr* self, uint64_t i, Expr value) {
    Array_Expr_set(&((*self)), (long long)(i), value);
}
void Array_Stmt_append_value_T(Array_Stmt* self, Stmt value) {
    Array_Stmt_push(&((*self)), value);
}
Stmt Array_Stmt_get_i_U64(Array_Stmt self, uint64_t i) {
    { Stmt __ret1180 = Array_Stmt_get((self), (long long)(i));
    return __ret1180; }
}
void Array_Stmt_set_i_U64_value_T(Array_Stmt* self, uint64_t i, Stmt value) {
    Array_Stmt_set(&((*self)), (long long)(i), value);
}
void Array_Block_append_value_T(Array_Block* self, Block value) {
    Array_Block_push(&((*self)), value);
}
Block Array_Block_get_i_U64(Array_Block self, uint64_t i) {
    { Block __ret1181 = Array_Block_get((self), (long long)(i));
    return __ret1181; }
}
void Array_Block_set_i_U64_value_T(Array_Block* self, uint64_t i, Block value) {
    Array_Block_set(&((*self)), (long long)(i), value);
}
void Array_StructDef_append_value_T(Array_StructDef* self, StructDef value) {
    Array_StructDef_push(&((*self)), value);
}
StructDef Array_StructDef_get_i_U64(Array_StructDef self, uint64_t i) {
    { StructDef __ret1182 = Array_StructDef_get((self), (long long)(i));
    return __ret1182; }
}
void Array_StructDef_set_i_U64_value_T(Array_StructDef* self, uint64_t i, StructDef value) {
    Array_StructDef_set(&((*self)), (long long)(i), value);
}
void Array_EnumDef_append_value_T(Array_EnumDef* self, EnumDef value) {
    Array_EnumDef_push(&((*self)), value);
}
EnumDef Array_EnumDef_get_i_U64(Array_EnumDef self, uint64_t i) {
    { EnumDef __ret1183 = Array_EnumDef_get((self), (long long)(i));
    return __ret1183; }
}
void Array_EnumDef_set_i_U64_value_T(Array_EnumDef* self, uint64_t i, EnumDef value) {
    Array_EnumDef_set(&((*self)), (long long)(i), value);
}
void Array_TraitDef_append_value_T(Array_TraitDef* self, TraitDef value) {
    Array_TraitDef_push(&((*self)), value);
}
TraitDef Array_TraitDef_get_i_U64(Array_TraitDef self, uint64_t i) {
    { TraitDef __ret1184 = Array_TraitDef_get((self), (long long)(i));
    return __ret1184; }
}
void Array_TraitDef_set_i_U64_value_T(Array_TraitDef* self, uint64_t i, TraitDef value) {
    Array_TraitDef_set(&((*self)), (long long)(i), value);
}
void Array_Conform_append_value_T(Array_Conform* self, Conform value) {
    Array_Conform_push(&((*self)), value);
}
Conform Array_Conform_get_i_U64(Array_Conform self, uint64_t i) {
    { Conform __ret1185 = Array_Conform_get((self), (long long)(i));
    return __ret1185; }
}
void Array_Conform_set_i_U64_value_T(Array_Conform* self, uint64_t i, Conform value) {
    Array_Conform_set(&((*self)), (long long)(i), value);
}
void Array_MethodAlias_append_value_T(Array_MethodAlias* self, MethodAlias value) {
    Array_MethodAlias_push(&((*self)), value);
}
MethodAlias Array_MethodAlias_get_i_U64(Array_MethodAlias self, uint64_t i) {
    { MethodAlias __ret1186 = Array_MethodAlias_get((self), (long long)(i));
    return __ret1186; }
}
void Array_MethodAlias_set_i_U64_value_T(Array_MethodAlias* self, uint64_t i, MethodAlias value) {
    Array_MethodAlias_set(&((*self)), (long long)(i), value);
}
void Array_DeriveReq_append_value_T(Array_DeriveReq* self, DeriveReq value) {
    Array_DeriveReq_push(&((*self)), value);
}
DeriveReq Array_DeriveReq_get_i_U64(Array_DeriveReq self, uint64_t i) {
    { DeriveReq __ret1187 = Array_DeriveReq_get((self), (long long)(i));
    return __ret1187; }
}
void Array_DeriveReq_set_i_U64_value_T(Array_DeriveReq* self, uint64_t i, DeriveReq value) {
    Array_DeriveReq_set(&((*self)), (long long)(i), value);
}
void Array_FuncBound_append_value_T(Array_FuncBound* self, FuncBound value) {
    Array_FuncBound_push(&((*self)), value);
}
FuncBound Array_FuncBound_get_i_U64(Array_FuncBound self, uint64_t i) {
    { FuncBound __ret1188 = Array_FuncBound_get((self), (long long)(i));
    return __ret1188; }
}
void Array_FuncBound_set_i_U64_value_T(Array_FuncBound* self, uint64_t i, FuncBound value) {
    Array_FuncBound_set(&((*self)), (long long)(i), value);
}
void Array_TypeRef_append_value_T(Array_TypeRef* self, TypeRef value) {
    Array_TypeRef_push(&((*self)), value);
}
TypeRef Array_TypeRef_get_i_U64(Array_TypeRef self, uint64_t i) {
    { TypeRef __ret1189 = Array_TypeRef_get((self), (long long)(i));
    return __ret1189; }
}
void Array_TypeRef_set_i_U64_value_T(Array_TypeRef* self, uint64_t i, TypeRef value) {
    Array_TypeRef_set(&((*self)), (long long)(i), value);
}
void Array_FnInst_append_value_T(Array_FnInst* self, FnInst value) {
    Array_FnInst_push(&((*self)), value);
}
FnInst Array_FnInst_get_i_U64(Array_FnInst self, uint64_t i) {
    { FnInst __ret1190 = Array_FnInst_get((self), (long long)(i));
    return __ret1190; }
}
void Array_FnInst_set_i_U64_value_T(Array_FnInst* self, uint64_t i, FnInst value) {
    Array_FnInst_set(&((*self)), (long long)(i), value);
}
void Array_CaptureEntry_append_value_T(Array_CaptureEntry* self, CaptureEntry value) {
    Array_CaptureEntry_push(&((*self)), value);
}
CaptureEntry Array_CaptureEntry_get_i_U64(Array_CaptureEntry self, uint64_t i) {
    { CaptureEntry __ret1191 = Array_CaptureEntry_get((self), (long long)(i));
    return __ret1191; }
}
void Array_CaptureEntry_set_i_U64_value_T(Array_CaptureEntry* self, uint64_t i, CaptureEntry value) {
    Array_CaptureEntry_set(&((*self)), (long long)(i), value);
}
void Array_Local_append_value_T(Array_Local* self, Local value) {
    Array_Local_push(&((*self)), value);
}
Local Array_Local_get_i_U64(Array_Local self, uint64_t i) {
    { Local __ret1192 = Array_Local_get((self), (long long)(i));
    return __ret1192; }
}
void Array_Local_set_i_U64_value_T(Array_Local* self, uint64_t i, Local value) {
    Array_Local_set(&((*self)), (long long)(i), value);
}
void Array_AssocBinding_append_value_T(Array_AssocBinding* self, AssocBinding value) {
    Array_AssocBinding_push(&((*self)), value);
}
AssocBinding Array_AssocBinding_get_i_U64(Array_AssocBinding self, uint64_t i) {
    { AssocBinding __ret1193 = Array_AssocBinding_get((self), (long long)(i));
    return __ret1193; }
}
void Array_AssocBinding_set_i_U64_value_T(Array_AssocBinding* self, uint64_t i, AssocBinding value) {
    Array_AssocBinding_set(&((*self)), (long long)(i), value);
}
void Array_PatInfo_append_value_T(Array_PatInfo* self, PatInfo value) {
    Array_PatInfo_push(&((*self)), value);
}
PatInfo Array_PatInfo_get_i_U64(Array_PatInfo self, uint64_t i) {
    { PatInfo __ret1194 = Array_PatInfo_get((self), (long long)(i));
    return __ret1194; }
}
void Array_PatInfo_set_i_U64_value_T(Array_PatInfo* self, uint64_t i, PatInfo value) {
    Array_PatInfo_set(&((*self)), (long long)(i), value);
}
