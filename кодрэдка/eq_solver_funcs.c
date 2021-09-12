#include "eq_solver.h"

#define BUFSIZE 128

const int    NOROOTS    = -1;
const int    INFINIT    = 19;
const int    EXITCODE   = -2;
const double INFELICITY = 1E-7;

//*************************************************************************************************

int is_zero (double val)
{
    return !(fabs (val) <= INFELICITY);
}

//*************************************************************************************************

void coeff_normalizing (double *a, double *b, double *c)
{
    if (isfinite (*a / *a) == 0) return;
    if (isfinite (*b / *a) && isfinite (*c / *a) == 0) return;

    *b = *b / *a; 
	*c = *c / *a; 
	*a = 1;
}

//*************************************************************************************************

int comparer (double A, double B)
{
    if (fabs (A - B) <= INFELICITY)
    return 0;

    if       (A < B)
    return -1;

    if       (A > B)
    return 1;

    return 2;
}

//*************************************************************************************************

void checker (double *a, double *b, double *c)
{
	char buf[BUFSIZE] = {};
	fgets (buf, BUFSIZE, stdin);
    int check = sscanf (buf, "%lg %lg %lg", a, b, c);
    while (check != 3)
    {
        printf ("# Sorry, try to input CORRECT information\n\n"
                "# Enter your a, b, c: ");

		fgets (buf, BUFSIZE, stdin);
        check = sscanf (buf, "%lg %lg %lg", a, b, c);
	}
}

//*************************************************************************************************

int square (double a, double b, double c, double *root1, double *root2)
{
    double discr = b * b - 4 * a * c;

	double sqrtd = sqrt(discr);
    double  zero = 0;
    int res = comparer (discr, zero);
    switch (res)
        {

        case -1:
        return res;

        case 0:
        *root1 = -b / 2 / a;
        return res;

        case 1:
        *root1 = (-b + sqrtd) / 2 / a;
        *root2 = (-b - sqrtd) / 2 / a;
        return res;

        default:
        printf ("square (): ERROR: discriminant = %lf.\n", discr);
        return res;
    }
}

//*************************************************************************************************

int linear (double b, double c, double* root1)
{

    if     (is_zero (b) == 0)
    return (is_zero (c) == 0) ? INFINIT : -1;

    *root1 = -c / b;

    return 0;
}

//*************************************************************************************************

int solver (double a, double b, double c, double *root1, double *root2)
{
    if (is_zero(a) == 0)
    return linear(b, c, root1);
    return square(a, b, c, root1, root2);
}

//*************************************************************************************************

int TESTER ()
{	
	printf ("#	enter yout coeffs: ");
	double a = 0, b = 0, c = 0;
    checker (&a, &b, &c);
	if (a)
	    coeff_normalizing (&a, &b, &c);

    double x1 = 0, x2 = 0;
    int n_of_roots = solver (a, b, c, &x1, &x2);

	printf ("#	enter your expectations of root amount and roots itself: ");
	int amnt = 0;
	double root1, root2 = 0;
	char buf[BUFSIZE] = {};
	fgets (buf, BUFSIZE, stdin);
    int check = sscanf (buf, "%d %lg %lg", &amnt, &root1, &root2);
    while (check != 3)
    {
        printf ("# Sorry, try to input CORRECT information\n\n");

		fgets (buf, BUFSIZE, stdin);
        check = sscanf (buf, "%d %lg %lg", &amnt, &root1, &root2);
	}

	if (amnt == EXITCODE)
		return 0;
	if (n_of_roots + 1 != amnt)
	{
		printf ("#		TEST FAILED: wrong root amount\n"
				"#               expected:    %d\n"
				"#               test result: %d\n", amnt, n_of_roots);
		return 1;
	}
	if (amnt != NOROOTS)
	{
		if (is_zero (root1 - x2))
		{
			printf ("#		TEST FAILED: wrong root1\n"
					"#               expected:    %lf\n"
					"#               test result: %lf\n", root1, x1);
			return 2;
		}
		if (is_zero (root2 - x1))
		{
			printf ("#		TEST FAILED: wrong root2\n"
					"#               expected:    %lf\n"
					"#               test result: %lf\n", root2, x2);
			return 3;
		}
	}
	printf ("#		TEST IS OK\n");
	TESTER ();

	return 0;
}
