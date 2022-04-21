#ifndef CALCH
#define CALCH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "../lexer/lexer.h"
#include "../Tree/tree.h"

#define CL CpyTree (ftree->left)
#define CR CpyTree (ftree->right)
#define DL RecDif (ftree->left, varname)
#define DR RecDif (ftree->right, varname)
#define _ADD_(x, y) BranchOper (ftree, x, y, ADD)
#define _SUB_(x, y) BranchOper (ftree, x, y, SUB)
#define _MUL_(x, y) BranchOper (ftree, x, y, MUL)
#define _DIV_(x, y) BranchOper (ftree, x, y, DIV)
#define _DEG_(x, y) BranchOper (ftree, x, y, DEG)
#define _SIN_(x)    BranchFunc (ftree, x, SIN)
#define _COS_(x)    BranchFunc (ftree, x, COS)
#define _SQRT_(x)   BranchFunc (ftree, x, SQRT)
#define _CBRT_(x)   BranchFunc (ftree, x, CBRT)
#define _LN_(x)     BranchFunc (ftree, x, LN)


#define SKIPSPACES f->p += SkipSpaces (f->str + f->p);
#define ACTLEX f->lexarr->lexs[f->p]
#define CALC_L CalcTree (tree->left) 
#define CALC_R CalcTree (tree->right)

typedef struct formula {
    lex_arr* lexarr;
    char* str;
    size_t p;
} formula;

typedef struct VARARR {
    struct VARIABLE* arr;
    size_t size;
    size_t capacity;
} vararr;

double SubstitAndCalc (Node* tree, const char* substit);

Node* Differ (Node* ftree, const char* varname);

Node* RecDif (Node* ftree, const char* varname);

Node* BranchFunc (Node* node, Node* val, enum OPERAND oper);

Node* BranchOper (Node* node, Node* val1, Node* val2, enum OPERAND oper);

Node* MakeNum (Node* node, double val);

int    Subtit (Node* tree, const char* subtit);

int    RecSubtit (Node* node, vararr* varr);

vararr* vararrCtor (size_t startcap);

int     vararrDtor (vararr* varr);

int     vararrResize (vararr* varr);

int     vararrPush (vararr* varr, struct VARIABLE push);

double CalcTree (Node* tree);

Node* GetG (formula* f);

Node* GetN (formula* f);

Node* GetT (formula* f);

Node* GetE (formula* f);

Node* GetP (formula* f);

Node* GetP0 (formula* f);

Node* SyntaxError (formula* f);

int powint (int base, int deg);

char* Read (const char* filename, long* ptrbufsz);

int   FormulaDump (Node* tree);

size_t SkipSpaces (const char* str);

size_t SkipNumber (const char* str);
// is lex funcs
//------------------------------------------
int isadd (lex_t lexem);

int issub (lex_t lexem);

int ismul (lex_t lexem);

int isdiv (lex_t lexem);

int isdeg (lex_t lexem);

int issin (lex_t lexem);

int iscos (lex_t lexem);

int issqrt (lex_t lexem);

int iscbrt (lex_t lexem);

int isln (lex_t lexem);

int islbr (lex_t lexem);

int isrbr (lex_t lexem);

int isnum (lex_t lexem);

int ispi (lex_t lexem);

int isphi (lex_t lexem);

int isnum_e (lex_t lexem);

int isconst (lex_t lexem);

int isend (lex_t lexem);

int isvar (lex_t lexem);

//------------------------------------------


#endif