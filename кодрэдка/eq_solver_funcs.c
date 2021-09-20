#include "eq_solver.h"

#define BUFSIZE 128

/*!
     Global parameter responsible for situations with zero number of roots.
*/
const int    NOROOTS    = -1;
/*!
     Global parameter responsible for situations with infinity number of roots.
*/
const int    INFINIT    = 19;
/*!
     Global parameter that is exitcode for autotests.
*/
const int    EXITCODE   = -2;
/*!
     Global parameter responsible for double's comparison error.
*/
const double INFELICITY = 1E-7;

//*************************************************************************************************

/*!
     \brief Comparing a number with zero.
     \param[in] val - compared number.
     \return 0 - val is zero, 1 - val is not a zero.
     This function allows you to compare a number with zero.
*/

int is_zero (double val)
{
    return !(fabs (val) <= INFELICITY);
}

//*************************************************************************************************

/*!
     \brief Normalizing of odds.
     \param[in] a, b, c - odds of equation.
     This function makes the equation reduced (leads to the form in which a = 1).
*/

void coeff_normalizing (double *a, double *b, double *c)
{
	assert (a);
	assert (b);
	assert (c);

    if (isfinite (*a / *a) == 0) return;
    if (isfinite (*b / *a) && isfinite (*c / *a) == 0) return;

    *b = *b / *a; 
	*c = *c / *a; 
	*a = 1;
}

//*************************************************************************************************

/*!
     \brief Compare a number with number.
     \param[in] A, B - compared numbers.
     \return -1 - A less than B, 0 - A and B are equal, 1 - A more than B.
     This function allows you to compare two numbers.
*/

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

/*!
     \brief Add to scanf().
     \param[in] a, b, c - input parameters (odds in this situation).
     This function prevents user input errors.
*/

void checker (double *a, double *b, double *c)
{
	assert (a);
	assert (b);
	assert (c);

	if (feof (stdin))
	{
		printf ("fuck");
		exit (666);
	}

	char buf[BUFSIZE] = {};
	fgets (buf, BUFSIZE, stdin);
    int check = sscanf (buf, "%lg %lg %lg", a, b, c);
#ifndef TEST
    while (check != 3)
    {
        printf ("# Sorry, try to input CORRECT information\n\n"
                "# Enter your a, b, c: ");

		fgets (buf, BUFSIZE, stdin);
        check = sscanf (buf, "%lg %lg %lg", a, b, c);
	}
#endif
#ifdef TEST
	if (check != 3)
		exit (0);
#endif
}

//*************************************************************************************************

/*!
     \param[in] a, b, c - odds of square equation. root1, root2 - var for result of solving (for roots).
     \return 0 - equation have no roots,
             1 - equation have 1 root,
             2 - equation have 2 roots.
     Function that solves square equation of the form a*x^2 + b*x + c = 0.
*/

int square (double a, double b, double c, double *root1, double *root2)
{
	assert (root1);
	assert (root2);
	assert (root1 != root2);

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

/*!
     \param[in] b, c - odds of linear equation. root1 - var dor res of solving (for root).
     \return -1 - equation have no roots,
             0 - equation have 1 root,
             19 (infinity) - equation have infinity number of roots.
     Function that solves linear equation of the form b*x + c = 0.
*/

int linear (double b, double c, double* root1)
{
	assert (root1);

    if     (is_zero (b) == 0)
    return (is_zero (c) == 0) ? INFINIT : -1;

    *root1 = -c / b;

    return 0;
}

//*************************************************************************************************

/*!
     \brief Function, that solves the equation.
     \param[in] a, b, c - odds of equation. root1, root2 - vars for result of solving (for roots).
     \return The value of the called function is Linear() if equation was linear,
                                                 Square() - if equation was square.
      Calls function Square() or Linear() depending on which equation is given (square or linear).
*/

int solver (double a, double b, double c, double *root1, double *root2)
{
	assert (root1);
	assert (root2);
	assert (root1 != root2);

    if (is_zero(a) == 0)
    return linear(b, c, root1);
    return square(a, b, c, root1, root2);
}

//*************************************************************************************************

/*!
	\brief recursive from-file dev's tester-function.
	\param[in] num - number of test {also is a return value}.
	do tests for proj from file w name that is given as arg for function main().
*/

int TESTER (int *num)
{
	assert (num);

	double a = 0, b = 0, c = 0;
    checker (&a, &b, &c);
	if (a)
	    coeff_normalizing (&a, &b, &c);

    double x1 = 0, x2 = 0;
    int n_of_roots = solver (a, b, c, &x1, &x2);

	int amnt = 0;
	double root1, root2 = 0;
	char buf[BUFSIZE] = {};
	fgets (buf, BUFSIZE, stdin);
    int check = sscanf (buf, "%d %lg %lg", &amnt, &root1, &root2);
	if (feof (stdin))
	{
		printf ("fuck");
		exit (6);
	}
	if (check != 3)
    	return 0;
	if (amnt == EXITCODE)
		return 0;
	if (n_of_roots + 1 != amnt)
	{
		printf ("#		TEST %d FAILED: wrong root amount\n"
				"#               expected:    %d\n"
				"#               test result: %d\n", *num, amnt, n_of_roots);
		return 1;
	}
	if (amnt != NOROOTS)
	{
		if (is_zero (root1 - x2))
		{
			printf ("#		TEST %d FAILED: wrong root1\n"
					"#               expected:    %lf\n"
					"#               test result: %lf\n", *num, root1, x2);
			return 2;
		}
		if (is_zero (root2 - x1))
		{
			printf ("#		TEST %d FAILED: wrong root2\n"
					"#               expected:    %lf\n"
					"#               test result: %lf\n", *num, root2, x1);
			return 3;
		}
	}
	printf ("#		TEST %d IS OK\n", *num);

	(*num)++;
	TESTER (num);

	return 0;
}
