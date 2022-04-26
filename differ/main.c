#include "calc.h"


int main (void)
{
    formula* f = (formula*) calloc (1, sizeof (formula));
    f->lexarr = lexarrCtor (16);
    f->str = Read ("formula.txt", NULL);
    if (f->str == NULL)
    {
        fprintf (stderr, "ERROR: can not open formula.txt file\n");
        return 0;
    }
    if (lexarrFill (f->lexarr, f->str) == 1)
    {
        return 0;
    }
    f->p = 0;
    Node* res = GetG (f);
    TreeDbgDump (res);
    FormulaDump (res);
    /*if (res != NULL)
    {
        printf ("Formula: %s\nValue: %lg\n", f->str, SubstitAndCalc (res, "x = 5, y = 2"));
    }*/
    Node* dtree = Differ (res, "x");
    FormulaDump (dtree);
    TreeDbgDump (dtree);
    Node* stree = Simp (dtree);
    FormulaDump (stree);
    lexarrDtor (f->lexarr);
    free (f->str);
    free (f);
    ChopDown (res);
    ChopDown (dtree);
    return 0;
}