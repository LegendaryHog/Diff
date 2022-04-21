#ifndef LEXERH
#define LEXERH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VARSNUM 16
#define VARLEN 8
#define SIN_LEN 3
#define COS_LEN 3
#define SQRT_LEN 4
#define CBRT_LEN 4
#define LN_LEN 2
#define PI_LEN 2
#define PHI_LEN 3
#define NUM_E_LEN 1



enum OPERAND {
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    DEG = '^',
    SIN = 's',
    COS = 'c',
    SQRT = 'S',
    CBRT = 'C',
    LN = 'l',
};

enum BRACE {
    LBRAC = '(',
    RBRAC = ')',
};

enum TYPE {
    OPER = 1,
    NUM,
    BRAC,
    CONST,
    END,
    VAR,
};

enum CONSTANT {
    PI,
    PHI,
    NUM_E,
};

struct VARIABLE {
    char name[VARLEN];
    double value;
};
typedef struct lexem {
    enum TYPE type;
    union VALUE {
        enum OPERAND op;
        enum BRACE brac;
        enum CONSTANT con;
        struct VARIABLE var;
        double num;
    } val;
} lex_t;

typedef struct lex_arr {
    lex_t* lexs;
    size_t size;
    size_t capacity;
} lex_arr;

lex_arr* lexarrCtor (size_t startcap);

int      lexarrFill (lex_arr* lexarr, const char* str);

int      lexarrResize (lex_arr* lexarr);

int      lexarrPush (lex_arr* lexarr, lex_t push);

int      lexarrDtor (lex_arr* lexarr);

size_t   SkipSpaces (const char* str);

size_t   SkipNumber (const char* str);

size_t   SkipVar    (const char* str);

int      lexarrDump (lex_arr* lexarr);

int      fprintelem (FILE* file, lex_t lexem);

int lexsin (const char* str);

int lexcos (const char* str);

int lexsqrt (const char* str);

int lexcbrt (const char* str);

int lexln (const char* str);

int lexpi (const char* str);

int lexphi (const char* str);

int lexnum_e (const char* str);


#endif