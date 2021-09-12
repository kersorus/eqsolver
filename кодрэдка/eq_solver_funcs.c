#include "eq_solver.h"

#define BUFSIZE 128

const int infinity = 19;
const double infelicity = 1E-7;

//*************************************************************************************************

int is_zero (double val)
{
    return (fabs (val) <= infelicity) ? 0 : 1;
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
    if (fabs (A - B) <= infelicity)
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
    int check = sscanf (buf, "%lg, %lg, %lg", a, b, c);
    while (check != 3)
    {
        printf ("# Sorry, try to input CORRECT information\n\n"
                "# Enter your a, b, c: ");

		fgets (buf, BUFSIZE, stdin);
        check = sscanf (buf, "%lg, %lg, %lg", a, b, c);
	}
}

//*************************************************************************************************

int square (double a, double b, double c, double *root1, double *root2)
{
    double discr = b * b - 4 * a * c;
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
        *root1 = (-b + sqrt(discr)) / 2 / a;
        *root2 = (-b - sqrt(discr)) / 2 / a;
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
    return (is_zero (c) == 0) ? infinity : -1;

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

int TESTER (int amnt, double root1, double root2, int r_amnt, double r_root1, double r_root2)
{
	if (amnt != r_amnt)
	{
		printf ("#		TEST FAILED: wrong root amount\n"
				"#               expected:    %d\n"
				"#               test result: %d\n", amnt, r_amnt);
		return 1;
	}
	if (root1 != r_root1)
	{
		printf ("#		TEST FAILED: wrong root1\n"
				"#               expected:    %lf\n"
				"#               test result: %lf\n", root1, r_root1);
		return 2;
	}
	if (root2 != r_root2)
	{
		printf ("#		TEST FAILED: wrong root2\n"
				"#               expected:    %lf\n"
				"#               test result: %lf\n", root2, r_root2);
		return 3;
	}

	printf ("#		TEST IS OK\n");
	return 0;
}
