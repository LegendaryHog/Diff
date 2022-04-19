#include "lexer.h"

lex_arr* lexarrCtor (size_t startcap)
{
    lex_arr* lexarr = (lex_arr*) calloc (1, sizeof (lex_arr));
    lexarr->capacity = startcap;
    lexarr->size = 0;
    lexarr->lexs = (lex_t*) calloc (lexarr->capacity, sizeof (lex_t));
    return lexarr;
}

int lexarrDtor (lex_arr* lexarr)
{
    if (!lexarr)
    {
        return 1;
    }
    free (lexarr->lexs);
    free (lexarr);
    return 0;
}

int lexarrPush (lex_arr* lexarr, lex_t push)
{
    if (lexarr->size == lexarr->capacity)
    {
        if (lexarrResize (lexarr) == 1)
        {
            fprintf (stderr, "MEMORY OFF\n");
            return 1;
        }
    }
    lexarr->lexs[lexarr->size++] = push;
    return 0;
}

int lexarrResize (lex_arr* lexarr)
{
    lexarr->capacity *= 2;
    lexarr->lexs = (lex_t*) realloc (lexarr->lexs, lexarr->capacity * sizeof (lex_t));
    if (lexarr->lexs == NULL)
    {
        fprintf (stderr, "MEM OFF\n");
        return 1;
    }
    for (size_t i = lexarr->capacity / 2; i < lexarr->capacity; i++)
    {
        lexarr->lexs[i].type = 0;
    }
    return 0;
}

size_t SkipNumber (const char* str)
{
    size_t i = 0;
    for (i = 0; (str[i] >= '0' && str[i] <= '9') || str[i] == '.'; i++) {;}
    return i;
}

size_t SkipSpaces (const char* str)
{
    size_t i = 0;
    for (i = 0; str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'; i++) {;}
    return i;
}

int lexarrFill (lex_arr* lexarr, const char* str)
{
    size_t p = 0;
    for (;;)
    {
        p += SkipSpaces (str + p);
        if (str[p] == '+')
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = ADD;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] == '-')
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = SUB;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] == '*')
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = MUL;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] == '/')
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = DIV;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] == '^')
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = DEG;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] == '(')
        {
            lex_t lex = {};
            lex.type = BRAC;
            lex.val.brac = LBRAC;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] == ')')
        {
            lex_t lex = {};
            lex.type = BRAC;
            lex.val.brac = RBRAC;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] >= '0' && str[p] <= '9')
        {
            lex_t lex = {};
            lex.type = NUM;
            sscanf (str + p, "%lf", &lex.val.num);
            p += SkipNumber (str + p);
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (str[p] == '\0' || str[p] == '$')
        {
            lex_t lex = {};
            lex.type = END;
            p++;
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
            break;
        }
        else if (lexsin (str + p))
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = SIN;
            p += strlen ("sin");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (lexcos (str + p))
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = COS;
            p += strlen ("cos");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (lexsqrt (str + p))
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = SQRT;
            p += strlen ("sqrt");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (lexcbrt (str + p))
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = CBRT;
            p += strlen ("cbrt");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (lexln (str + p))
        {
            lex_t lex = {};
            lex.type = OPER;
            lex.val.op = LN;
            p += strlen ("ln");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (lexpi (str + p))
        {
            lex_t lex = {};
            lex.type = CONST;
            lex.val.con = PI;
            p += strlen ("pi");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (lexphi (str + p))
        {
            lex_t lex = {};
            lex.type = CONST;
            lex.val.con = PHI;
            p += strlen ("phi");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else if (lexnum_e (str + p))
        {
            lex_t lex = {};
            lex.type = CONST;
            lex.val.con = NUM_E;
            p += strlen ("e");
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        else
        {
            lex_t lex = {};
            lex.type = VAR;
            sscanf (str + p, "%8[^ /*+-^)$]", lex.val.var.name);
            p += SkipVar (str + p);
            if (lexarrPush (lexarr, lex) == 1)
                return 1;
        }
        p += SkipSpaces (str + p);
    }
    return 0;
}

int lexarrDump (lex_arr* lexarr)
{
    FILE* file = stdout;
    if (lexarr == NULL)
    {
        fprintf (stderr, "lexarr NULL pointer\n");
        return 1;
    }

    fprintf (file, "lexarr: %p\n\tcapacity: %zd\n\tsize: %zd\n\tlexs: %p\n\n", lexarr, lexarr->capacity, lexarr->size, lexarr->lexs);

    if (lexarr->lexs == NULL)
    {
        fprintf (stderr, "lexs array NULL pointer\n");
        return 1;
    }

    for (size_t i = 0; i < lexarr->size; i++)
    {
        fprintf (file, "pos: %zd\n", i);
        switch (lexarr->lexs[i].type) {
            case OPER:
                fprintf (file, "\ttype: operand\n");
                fprintf (file, "\toperand: %c\n", (char)lexarr->lexs[i].val.op);
                break;
            case BRAC:
                fprintf (file, "\ttype: brace\n");
                fprintf (file, "\tbrace: %c\n", (char)lexarr->lexs[i].val.brac);
                break;
            case NUM:
                fprintf (file, "\ttype: num\n");
                fprintf (file, "\tconst: %lf\n", lexarr->lexs[i].val.num);
                break;
            case CONST:
                fprintf (file, "\ttype: const\n");
                fprintf (file, "\tconst: %d\n", lexarr->lexs[i].val.con);
                break;
        }
    }
    return 0;
}

int fprintelem (FILE* file, lex_t lexem)
{
    switch (lexem.type) {
            case OPER:
                switch (lexem.val.op) {
                    case ADD: case SUB: case MUL: case DIV: case DEG:
                        return fprintf (file, "%c ", lexem.val.op);
                    case SIN:
                        return fprintf (file, "sin ");
                    case COS:
                        return fprintf (file, "cos ");
                    case SQRT:
                        return fprintf (file, "sqrt ");
                    case CBRT:
                        return fprintf (file, "cbrt ");
                    case LN:
                        return fprintf (file, "ln ");
                }
                break;
            case BRAC:
                if (lexem.type == BRAC && lexem.val.brac == LBRAC)
                    return fprintf (file, "( ");
                else
                    return fprintf (file, ") ");
            case CONST:
                switch (lexem.val.con) {
                    case PI:
                        return fprintf (file, "pi ");
                    case PHI:
                        return fprintf (file, "phi ");
                    case NUM_E:
                        return fprintf (file, "e ");
                }
            case NUM:
                return fprintf (file, "%lg ", lexem.val.num);
            case END:
                return 0;
            case VAR:
                return fprintf (file, "%s ", lexem.val.var.name);
            default:
                fprintf (file, "ERROR\n");
                return 0;
    }
}

int lexsin (const char* str)
{
    char lexstr[4] = {};
    sscanf (str, "%3s", lexstr);
    if (strcmp (lexstr, "sin") == 0)
        return 1;
    else
        return 0;
}

int lexcos (const char* str)
{
    char lexstr[4] = {};
    sscanf (str, "%3s", lexstr);
    if (strcmp (lexstr, "cos") == 0)
        return 1;
    else
        return 0;
}

int lexsqrt (const char* str)
{
    char lexstr[5] = {};
    sscanf (str, "%4s", lexstr);
    if (strcmp (lexstr, "sqrt") == 0)
        return 1;
    else
        return 0;
}

int lexcbrt (const char* str)
{
    char lexstr[5] = {};
    sscanf (str, "%4s", lexstr);
    if (strcmp (lexstr, "cbrt") == 0)
        return 1;
    else
        return 0;
}

int lexln (const char* str)
{
    char lexstr[3] = {};
    sscanf (str, "%2s", lexstr);
    if (strcmp (lexstr, "ln") == 0)
        return 1;
    else
        return 0;
}

int lexpi (const char* str)
{
    char lexstr[3] = {};
    sscanf (str, "%[^ )^$+-*/]", lexstr);
    if (strcmp (lexstr, "pi") == 0)
        return 1;
    else
        return 0;
}

int lexphi (const char* str)
{
    char lexstr[4] = {};
    sscanf (str, "%[^ )^$+-*/]", lexstr);
    if (strcmp (lexstr, "phi") == 0)
        return 1;
    else
        return 0;
}

int lexnum_e (const char* str)
{
    char lexstr[2] = {};
    sscanf (str, "%[^ )^$+-*/]", lexstr);
    if (strcmp (lexstr, "e") == 0)
        return 1;
    else
        return 0;
}

size_t SkipVar (const char* str)
{
    size_t i = 0;
    for (i = 0; str[i] != ' ' && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '^' && str[i] != '$' && str[i] != ')' && str[i] != '\0' && str[i] != '='; i++) {;}
    return 1;
}







