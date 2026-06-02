#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct { const char* data; int64_t len; } PlewString;
static int PlewString_eq(PlewString a, PlewString b) { if (a.len != b.len) return 0; for (int64_t i = 0; i < a.len; i++) if (a.data[i] != b.data[i]) return 0; return 1; }
static PlewString plew_read_stdin(void) { size_t cap = 4096, len = 0; char* buf = (char*)malloc(cap); int c; while ((c = getchar()) != EOF) { if (len + 1 >= cap) { cap *= 2; buf = (char*)realloc(buf, cap); } buf[len++] = (char)c; } PlewString s; s.data = buf; s.len = (int64_t)len; return s; }
static void plew_write(PlewString s) { fwrite(s.data, 1, (size_t)s.len, stdout); }

typedef struct Kind Kind;
typedef struct Tok Tok;
typedef struct Lexer Lexer;
typedef struct Expr Expr;
typedef struct Parser Parser;

typedef struct { uint8_t* data; int64_t len; int64_t cap; } PlewArray_U8;
typedef struct { Tok* data; int64_t len; int64_t cap; } PlewArray_Tok;
typedef struct { Expr* data; int64_t len; int64_t cap; } PlewArray_Expr;

struct Kind {
    int tag;
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

struct Expr {
    int tag;
    union {
        struct { int64_t value; } Num;
        struct { uint8_t op; uint64_t lhs; uint64_t rhs; } Bin;
    } data;
};

struct Parser {
    PlewArray_U8 bytes;
    PlewArray_Tok toks;
    uint64_t pos;
    PlewArray_Expr nodes;
};

static PlewArray_U8 PlewArray_U8_new(void) { PlewArray_U8 a; a.data = 0; a.len = 0; a.cap = 0; return a; }
static uint8_t PlewArray_U8_get(PlewArray_U8 a, int64_t i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
static void PlewArray_U8_set(PlewArray_U8* a, int64_t i, uint8_t v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
static void PlewArray_U8_push(PlewArray_U8* a, uint8_t v) { if (a->len >= a->cap) { int64_t nc = a->cap < 4 ? 4 : a->cap * 2; uint8_t* nd = (uint8_t*)malloc(sizeof(uint8_t) * nc); for (int64_t i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }

static PlewArray_Tok PlewArray_Tok_new(void) { PlewArray_Tok a; a.data = 0; a.len = 0; a.cap = 0; return a; }
static Tok PlewArray_Tok_get(PlewArray_Tok a, int64_t i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
static void PlewArray_Tok_set(PlewArray_Tok* a, int64_t i, Tok v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
static void PlewArray_Tok_push(PlewArray_Tok* a, Tok v) { if (a->len >= a->cap) { int64_t nc = a->cap < 4 ? 4 : a->cap * 2; Tok* nd = (Tok*)malloc(sizeof(Tok) * nc); for (int64_t i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }

static PlewArray_Expr PlewArray_Expr_new(void) { PlewArray_Expr a; a.data = 0; a.len = 0; a.cap = 0; return a; }
static Expr PlewArray_Expr_get(PlewArray_Expr a, int64_t i) { if (i < 0 || i >= a.len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } return a.data[i]; }
static void PlewArray_Expr_set(PlewArray_Expr* a, int64_t i, Expr v) { if (i < 0 || i >= a->len) { fprintf(stderr, "panic: index out of range\n"); exit(1); } a->data[i] = v; }
static void PlewArray_Expr_push(PlewArray_Expr* a, Expr v) { if (a->len >= a->cap) { int64_t nc = a->cap < 4 ? 4 : a->cap * 2; Expr* nd = (Expr*)malloc(sizeof(Expr) * nc); for (int64_t i = 0; i < a->len; i++) nd[i] = a->data[i]; a->data = nd; a->cap = nc; } a->data[a->len] = v; a->len++; }

uint8_t at(Lexer *lx, uint64_t off);
int isDigit(uint8_t b);
int isAlpha(uint8_t b);
int isAlnum(uint8_t b);
int rangeEquals(PlewArray_U8 bytes, uint64_t start, uint64_t len, PlewString kw);
Kind identKind(PlewArray_U8 bytes, uint64_t start, uint64_t len);
void emit(Lexer *lx, Kind k, uint64_t start, uint64_t len);
int lastWasNewline(Lexer *lx);
int lastCanEnd(Lexer *lx);
void lex(Lexer *lx);
Kind curKind(Parser *p);
void advance(Parser *p);
uint64_t push(Parser *p, Expr e);
int64_t tokenValue(Parser *p, Tok t);
uint64_t parseAtom(Parser *p);
uint64_t parseTerm(Parser *p);
uint64_t parseExpr(Parser *p);
PlewString digitStr(int64_t d);
void writeInt(int64_t n);
PlewString opStr(uint8_t op);
void genExpr(PlewArray_Expr nodes, uint64_t id);

uint8_t at(Lexer *lx, uint64_t off) {
    uint64_t i = ((*lx).pos + off);
    if ((i < ((*lx).bytes).len)) {
    return PlewArray_U8_get((*lx).bytes, (int64_t)(i));
    }
    return 0;
}

int isDigit(uint8_t b) {
    if ((b >= 48)) {
    if ((b <= 57)) {
    return 1;
    }
    }
    return 0;
}

int isAlpha(uint8_t b) {
    if ((b == 95)) {
    return 1;
    }
    if ((b >= 97)) {
    if ((b <= 122)) {
    return 1;
    }
    }
    if ((b >= 65)) {
    if ((b <= 90)) {
    return 1;
    }
    }
    return 0;
}

int isAlnum(uint8_t b) {
    if (isAlpha(b)) {
    return 1;
    }
    return isDigit(b);
}

int rangeEquals(PlewArray_U8 bytes, uint64_t start, uint64_t len, PlewString kw) {
    PlewArray_U8 kb = ({ PlewString __s = kw; (PlewArray_U8){(uint8_t*)__s.data, __s.len, __s.len}; });
    if ((len != (kb).len)) {
    return 0;
    }
    uint64_t j = 0;
    while ((j < len)) {
    if ((PlewArray_U8_get(bytes, (int64_t)((start + j))) != PlewArray_U8_get(kb, (int64_t)(j)))) {
    return 0;
    }
    j += 1;
    }
    return 1;
}

Kind identKind(PlewArray_U8 bytes, uint64_t start, uint64_t len) {
    if (rangeEquals(bytes, start, len, ((PlewString){"fn", 2}))) {
    return ((Kind){.tag = 5});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"struct", 6}))) {
    return ((Kind){.tag = 6});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"enum", 4}))) {
    return ((Kind){.tag = 7});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"match", 5}))) {
    return ((Kind){.tag = 8});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"if", 2}))) {
    return ((Kind){.tag = 9});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"else", 4}))) {
    return ((Kind){.tag = 10});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"while", 5}))) {
    return ((Kind){.tag = 11});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"for", 3}))) {
    return ((Kind){.tag = 12});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"break", 5}))) {
    return ((Kind){.tag = 13});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"continue", 8}))) {
    return ((Kind){.tag = 14});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"return", 6}))) {
    return ((Kind){.tag = 15});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"give", 4}))) {
    return ((Kind){.tag = 16});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"val", 3}))) {
    return ((Kind){.tag = 17});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"mut", 3}))) {
    return ((Kind){.tag = 18});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"in", 2}))) {
    return ((Kind){.tag = 19});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"as", 2}))) {
    return ((Kind){.tag = 20});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"inout", 5}))) {
    return ((Kind){.tag = 21});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"true", 4}))) {
    return ((Kind){.tag = 22});
    }
    if (rangeEquals(bytes, start, len, ((PlewString){"false", 5}))) {
    return ((Kind){.tag = 23});
    }
    return ((Kind){.tag = 4});
}

void emit(Lexer *lx, Kind k, uint64_t start, uint64_t len) {
    PlewArray_Tok_push(&((*lx).toks), ((Tok){.kind = k, .start = start, .len = len}));
    (*lx).pos = (start + len);
}

int lastWasNewline(Lexer *lx) {
    uint64_t n = ((*lx).toks).len;
    if ((n == 0)) {
    return 0;
    }
    Tok t = PlewArray_Tok_get((*lx).toks, (int64_t)((n - 1)));
    Kind __m0 = t.kind;
    if (__m0.tag == 1) {
    {
    return 1;
    }
    } else {
    {
    return 0;
    }
    }
}

int lastCanEnd(Lexer *lx) {
    uint64_t n = ((*lx).toks).len;
    if ((n == 0)) {
    return 0;
    }
    Tok t = PlewArray_Tok_get((*lx).toks, (int64_t)((n - 1)));
    Kind __m1 = t.kind;
    if (__m1.tag == 4) {
    {
    return 1;
    }
    } else if (__m1.tag == 2) {
    {
    return 1;
    }
    } else if (__m1.tag == 3) {
    {
    return 1;
    }
    } else if (__m1.tag == 25) {
    {
    return 1;
    }
    } else if (__m1.tag == 27) {
    {
    return 1;
    }
    } else if (__m1.tag == 29) {
    {
    return 1;
    }
    } else if (__m1.tag == 50) {
    {
    return 1;
    }
    } else if (__m1.tag == 22) {
    {
    return 1;
    }
    } else if (__m1.tag == 23) {
    {
    return 1;
    }
    } else if (__m1.tag == 15) {
    {
    return 1;
    }
    } else if (__m1.tag == 13) {
    {
    return 1;
    }
    } else if (__m1.tag == 14) {
    {
    return 1;
    }
    } else {
    {
    return 0;
    }
    }
}

void lex(Lexer *lx) {
    while (((*lx).pos < ((*lx).bytes).len)) {
    uint8_t b = at(&((*lx)), 0);
    if ((b == 32)) {
    (*lx).pos += 1;
    continue;
    }
    if ((b == 9)) {
    (*lx).pos += 1;
    continue;
    }
    if ((b == 13)) {
    (*lx).pos += 1;
    continue;
    }
    if ((b == 10)) {
    if (((*lx).depth > 0)) {
    (*lx).pos += 1;
    } else {
    if (lastCanEnd(&((*lx)))) {
    if (lastWasNewline(&((*lx)))) {
    (*lx).pos += 1;
    } else {
    emit(&((*lx)), ((Kind){.tag = 1}), (*lx).pos, 1);
    }
    } else {
    (*lx).pos += 1;
    }
    }
    continue;
    }
    if ((b == 47)) {
    if ((at(&((*lx)), 1) == 47)) {
    while (((*lx).pos < ((*lx).bytes).len)) {
    if ((at(&((*lx)), 0) == 10)) {
    break;
    }
    (*lx).pos += 1;
    }
    continue;
    }
    }
    if (isDigit(b)) {
    uint64_t start = (*lx).pos;
    uint64_t j = (*lx).pos;
    while ((j < ((*lx).bytes).len)) {
    if (isDigit(PlewArray_U8_get((*lx).bytes, (int64_t)(j)))) {
    j += 1;
    } else {
    break;
    }
    }
    emit(&((*lx)), ((Kind){.tag = 2}), start, (j - start));
    continue;
    }
    if (isAlpha(b)) {
    uint64_t start = (*lx).pos;
    uint64_t j = (*lx).pos;
    while ((j < ((*lx).bytes).len)) {
    if (isAlnum(PlewArray_U8_get((*lx).bytes, (int64_t)(j)))) {
    j += 1;
    } else {
    break;
    }
    }
    uint64_t len = (j - start);
    Kind k = identKind((*lx).bytes, start, len);
    emit(&((*lx)), k, start, len);
    continue;
    }
    if ((b == 34)) {
    uint64_t start = (*lx).pos;
    uint64_t j = ((*lx).pos + 1);
    while ((j < ((*lx).bytes).len)) {
    if ((PlewArray_U8_get((*lx).bytes, (int64_t)(j)) == 34)) {
    j += 1;
    break;
    }
    j += 1;
    }
    emit(&((*lx)), ((Kind){.tag = 3}), start, (j - start));
    continue;
    }
    uint8_t b2 = at(&((*lx)), 1);
    if ((b == 46)) {
    if ((b2 == 46)) {
    uint8_t b3 = at(&((*lx)), 2);
    if ((b3 == 60)) {
    emit(&((*lx)), ((Kind){.tag = 56}), (*lx).pos, 3);
    continue;
    }
    if ((b3 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 57}), (*lx).pos, 3);
    continue;
    }
    }
    emit(&((*lx)), ((Kind){.tag = 32}), (*lx).pos, 1);
    continue;
    }
    if ((b == 61)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 34}), (*lx).pos, 2);
    continue;
    }
    if ((b2 == 62)) {
    emit(&((*lx)), ((Kind){.tag = 49}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 33}), (*lx).pos, 1);
    continue;
    }
    if ((b == 33)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 35}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 47}), (*lx).pos, 1);
    continue;
    }
    if ((b == 60)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 37}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 36}), (*lx).pos, 1);
    continue;
    }
    if ((b == 62)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 39}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 38}), (*lx).pos, 1);
    continue;
    }
    if ((b == 43)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 51}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 40}), (*lx).pos, 1);
    continue;
    }
    if ((b == 45)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 52}), (*lx).pos, 2);
    continue;
    }
    if ((b2 == 62)) {
    emit(&((*lx)), ((Kind){.tag = 48}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 41}), (*lx).pos, 1);
    continue;
    }
    if ((b == 42)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 53}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 42}), (*lx).pos, 1);
    continue;
    }
    if ((b == 47)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 54}), (*lx).pos, 2);
    continue;
    }
    if ((b2 == 62)) {
    emit(&((*lx)), ((Kind){.tag = 50}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 43}), (*lx).pos, 1);
    continue;
    }
    if ((b == 37)) {
    if ((b2 == 61)) {
    emit(&((*lx)), ((Kind){.tag = 55}), (*lx).pos, 2);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 44}), (*lx).pos, 1);
    continue;
    }
    if ((b == 38)) {
    if ((b2 == 38)) {
    emit(&((*lx)), ((Kind){.tag = 45}), (*lx).pos, 2);
    continue;
    }
    }
    if ((b == 124)) {
    if ((b2 == 124)) {
    emit(&((*lx)), ((Kind){.tag = 46}), (*lx).pos, 2);
    continue;
    }
    }
    if ((b == 40)) {
    emit(&((*lx)), ((Kind){.tag = 24}), (*lx).pos, 1);
    (*lx).depth += 1;
    continue;
    }
    if ((b == 41)) {
    emit(&((*lx)), ((Kind){.tag = 25}), (*lx).pos, 1);
    (*lx).depth -= 1;
    continue;
    }
    if ((b == 91)) {
    emit(&((*lx)), ((Kind){.tag = 26}), (*lx).pos, 1);
    (*lx).depth += 1;
    continue;
    }
    if ((b == 93)) {
    emit(&((*lx)), ((Kind){.tag = 27}), (*lx).pos, 1);
    (*lx).depth -= 1;
    continue;
    }
    if ((b == 123)) {
    emit(&((*lx)), ((Kind){.tag = 28}), (*lx).pos, 1);
    continue;
    }
    if ((b == 125)) {
    emit(&((*lx)), ((Kind){.tag = 29}), (*lx).pos, 1);
    continue;
    }
    if ((b == 44)) {
    emit(&((*lx)), ((Kind){.tag = 30}), (*lx).pos, 1);
    continue;
    }
    if ((b == 58)) {
    emit(&((*lx)), ((Kind){.tag = 31}), (*lx).pos, 1);
    continue;
    }
    emit(&((*lx)), ((Kind){.tag = 58}), (*lx).pos, 1);
    }
    PlewArray_Tok_push(&((*lx).toks), ((Tok){.kind = ((Kind){.tag = 0}), .start = (*lx).pos, .len = 0}));
}

Kind curKind(Parser *p) {
    return PlewArray_Tok_get((*p).toks, (int64_t)((*p).pos)).kind;
}

void advance(Parser *p) {
    (*p).pos = ((*p).pos + 1);
}

uint64_t push(Parser *p, Expr e) {
    uint64_t id = ((*p).nodes).len;
    PlewArray_Expr_push(&((*p).nodes), e);
    return id;
}

int64_t tokenValue(Parser *p, Tok t) {
    int64_t v = 0;
    uint64_t j = 0;
    while ((j < t.len)) {
    uint8_t b = PlewArray_U8_get((*p).bytes, (int64_t)((t.start + j)));
    v = ((v * 10) + (((int64_t)(b)) - 48));
    j += 1;
    }
    return v;
}

uint64_t parseAtom(Parser *p) {
    Kind k = curKind(&((*p)));
    Kind __m2 = k;
    if (__m2.tag == 24) {
    {
    advance(&((*p)));
    uint64_t inner = parseExpr(&((*p)));
    Kind __m3 = curKind(&((*p)));
    if (__m3.tag == 25) {
    {
    advance(&((*p)));
    }
    } else {
    {
    }
    }
    return inner;
    }
    } else if (__m2.tag == 2) {
    {
    Tok t = PlewArray_Tok_get((*p).toks, (int64_t)((*p).pos));
    advance(&((*p)));
    int64_t v = tokenValue(&((*p)), t);
    return push(&((*p)), ((Expr){.tag = 0, .data.Num = {.value = v}}));
    }
    } else {
    {
    return push(&((*p)), ((Expr){.tag = 0, .data.Num = {.value = 0}}));
    }
    }
}

uint64_t parseTerm(Parser *p) {
    uint64_t left = parseAtom(&((*p)));
    while (1) {
    Kind k = curKind(&((*p)));
    Kind __m4 = k;
    if (__m4.tag == 42) {
    {
    advance(&((*p)));
    uint64_t right = parseAtom(&((*p)));
    left = push(&((*p)), ((Expr){.tag = 1, .data.Bin = {.op = 42, .lhs = left, .rhs = right}}));
    }
    } else if (__m4.tag == 43) {
    {
    advance(&((*p)));
    uint64_t right = parseAtom(&((*p)));
    left = push(&((*p)), ((Expr){.tag = 1, .data.Bin = {.op = 47, .lhs = left, .rhs = right}}));
    }
    } else if (__m4.tag == 44) {
    {
    advance(&((*p)));
    uint64_t right = parseAtom(&((*p)));
    left = push(&((*p)), ((Expr){.tag = 1, .data.Bin = {.op = 37, .lhs = left, .rhs = right}}));
    }
    } else {
    {
    break;
    }
    }
    }
    return left;
}

uint64_t parseExpr(Parser *p) {
    uint64_t left = parseTerm(&((*p)));
    while (1) {
    Kind k = curKind(&((*p)));
    Kind __m5 = k;
    if (__m5.tag == 40) {
    {
    advance(&((*p)));
    uint64_t right = parseTerm(&((*p)));
    left = push(&((*p)), ((Expr){.tag = 1, .data.Bin = {.op = 43, .lhs = left, .rhs = right}}));
    }
    } else if (__m5.tag == 41) {
    {
    advance(&((*p)));
    uint64_t right = parseTerm(&((*p)));
    left = push(&((*p)), ((Expr){.tag = 1, .data.Bin = {.op = 45, .lhs = left, .rhs = right}}));
    }
    } else {
    {
    break;
    }
    }
    }
    return left;
}

PlewString digitStr(int64_t d) {
    if ((d == 0)) {
    return ((PlewString){"0", 1});
    }
    if ((d == 1)) {
    return ((PlewString){"1", 1});
    }
    if ((d == 2)) {
    return ((PlewString){"2", 1});
    }
    if ((d == 3)) {
    return ((PlewString){"3", 1});
    }
    if ((d == 4)) {
    return ((PlewString){"4", 1});
    }
    if ((d == 5)) {
    return ((PlewString){"5", 1});
    }
    if ((d == 6)) {
    return ((PlewString){"6", 1});
    }
    if ((d == 7)) {
    return ((PlewString){"7", 1});
    }
    if ((d == 8)) {
    return ((PlewString){"8", 1});
    }
    return ((PlewString){"9", 1});
}

void writeInt(int64_t n) {
    if ((n < 0)) {
    plew_write(((PlewString){"-", 1}));
    writeInt((0 - n));
    return;
    }
    if ((n >= 10)) {
    writeInt((n / 10));
    }
    plew_write(digitStr((n % 10)));
}

PlewString opStr(uint8_t op) {
    if ((op == 43)) {
    return ((PlewString){" + ", 3});
    }
    if ((op == 45)) {
    return ((PlewString){" - ", 3});
    }
    if ((op == 42)) {
    return ((PlewString){" * ", 3});
    }
    if ((op == 37)) {
    return ((PlewString){" % ", 3});
    }
    return ((PlewString){" / ", 3});
}

void genExpr(PlewArray_Expr nodes, uint64_t id) {
    Expr node = PlewArray_Expr_get(nodes, (int64_t)(id));
    Expr __m6 = node;
    if (__m6.tag == 0) {
        int64_t value = __m6.data.Num.value;
    {
    writeInt(value);
    }
    } else if (__m6.tag == 1) {
        uint8_t op = __m6.data.Bin.op;
        uint64_t lhs = __m6.data.Bin.lhs;
        uint64_t rhs = __m6.data.Bin.rhs;
    {
    plew_write(((PlewString){"(", 1}));
    genExpr(nodes, lhs);
    plew_write(opStr(op));
    genExpr(nodes, rhs);
    plew_write(((PlewString){")", 1}));
    }
    }
}

int main(void) {
    PlewString src = plew_read_stdin();
    Lexer lx = ((Lexer){.bytes = ({ PlewString __s = src; (PlewArray_U8){(uint8_t*)__s.data, __s.len, __s.len}; }), .pos = 0, .toks = PlewArray_Tok_new(), .depth = 0});
    lex(&(lx));
    Parser p = ((Parser){.bytes = ({ PlewString __s = src; (PlewArray_U8){(uint8_t*)__s.data, __s.len, __s.len}; }), .toks = lx.toks, .pos = 0, .nodes = PlewArray_Expr_new()});
    uint64_t root = parseExpr(&(p));
    plew_write(((PlewString){"#include <stdio.h>\n", 19}));
    plew_write(((PlewString){"int main(void) {\n", 17}));
    plew_write(((PlewString){"    printf(\"%lld\\n\", (long long)(", 33}));
    genExpr(p.nodes, root);
    plew_write(((PlewString){"));\n", 4}));
    plew_write(((PlewString){"    return 0;\n", 14}));
    plew_write(((PlewString){"}\n", 2}));
    return 0;
}

