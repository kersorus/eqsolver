#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//*************************************************************************************************

int  TESTER            ();
int  is_zero           (double val);
void coeff_normalizing (double *a, double *b, double *c);
int  comparer          (double  A, double  B);
void checker           (double *a, double *b, double *c);
int  square            (double  a, double  b, double  c, double *root1, double *root2);
int  linear            (double  b, double  c, double *root1);
int  solver            (double  a, double  b, double  c, double *root1, double *root2);
