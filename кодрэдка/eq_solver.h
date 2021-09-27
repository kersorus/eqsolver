#ifndef _EQSOLVER_H_
#define _EQSOLVER_H_

//*************************************************************************************************

enum amnt_of_roots
{
    EXITCODE = -2,    // parameter responsible that is exitcode for autotests
    NOROOTS = 0,      // parameter responsible for no roots
    ONEROOT,          // parameter responsible for one root
    TWOROOTS,         // parameter responsible for two roots
    INFINIT = 19      // parameter responsible for infinity roots
};

//*************************************************************************************************

enum test_situations
{
    NOPROBLEMS = 0,
    WRRAMNT,
    WRROOTONE,
    WRROOTTWO
};

//*************************************************************************************************

int  TESTER            (int *num);
int  is_not_zero       (double val);
void coeff_normalizing (double *a, double *b, double *c);
int  comparer          (double  A, double  B);
void checker           (double *a, double *b, double *c);
int  square            (double  a, double  b, double  c, double *root1, double *root2);
int  linear            (double  b, double  c, double *root1);
int  solver            (double  a, double  b, double  c, double *root1, double *root2);

#endif
