#include "eq_solver.h"

#define BUFSIZE 128

//*************************************************************************************************

int main()
{
#ifndef TEST
    printf ("# Equation solver ( square (a * x^2 + b * x + c = 0) version )\n"
            "#	(c) kersorus, 2020-21\n\n");
#endif
    printf ("#	Enter your a, b, c: ");

    double a = 0, b = 0, c = 0;
    checker (&a, &b, &c);
    coeff_normalizing (&a, &b, &c);

    double x1 = 0, x2 = 0;
    int n_of_roots = solver (a, b, c, &x1, &x2);

#ifdef TEST
	printf ("#	too stop dat sheet put root amount = -1\n");
	printf ("#	too make infinitii put root amount = 20\n");
	printf ("#	first root is lover then sacond\n");
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
	if (amnt == -1)
		exit (0);
	if (TESTER (amnt, root1, root2, n_of_roots + 1, x2, x1))
		return 667;

	main();
#endif

#ifndef TEST
    printf ("#	Answer: ");
    switch (n_of_roots)
    {
        case -1:
        printf ("no roots.\n");
        break;

        case 0:
        printf ("one root x1 = %lg.\n", x1);
        break;

        case 1:
        printf ("two roots x1 = %lg, x2 = %lg.\n", x1, x2);
        break;

        case 19:
        printf ("any number.\n");
        break;

        default:
        printf ("main(): ERROR: roots = %d.\n", n_of_roots);
        return 1;
    }
#endif
}
