#include "eq_solver.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

//*************************************************************************************************

int main(int argc, char *argv[])
{
#ifndef TEST
    printf ("# Equation solver ( square (a * x^2 + b * x + c = 0) version )\n"
            "#    (c) kersorus, 2020-21\n\n");
    printf ("#    Enter your a, b, c: ");

    double a = 0, b = 0, c = 0;
    checker (&a, &b, &c);
    if (is_not_zero (a))
        coeff_normalizing (&a, &b, &c);

    double x1 = 0, x2 = 0;
    int n_of_roots = solver (a, b, c, &x1, &x2);

    printf ("#    Answer: ");
    switch (n_of_roots)
    {
        case NOROOTS:
        printf ("no roots.\n");
        break;

        case ONEROOT:
        printf ("one root x1 = %lg.\n", x1);
        break;

        case TWOROOTS:
        printf ("two roots x1 = %lg, x2 = %lg.\n", x1, x2);
        break;

        case INFINIT:
        printf ("any number.\n");
        break;

        default:
        printf ("main(): ERROR: roots = %d.\n", n_of_roots);
        printf ("%d\n", TWOROOTS);
        return 1;
    }
#else
    if (argc == 2)
    {
        if (!freopen (argv[1], "r", stdin))
        {
            perror ("#    first make TESTFILE");
            exit (EXIT_FAILURE);
        }
    }
    else
    {
        perror ("#    give prog name of test file\n");
        exit (EXIT_FAILURE);
    }

    printf ("#    too stop dat sheet put root amount = %d\n", EXITCODE);
    printf ("#    too make infinitii put root amount = %d\n", INFINIT);
    printf ("#    first root is lover then sacond\n");
    printf ("#    no rotts means amnt = %d and any rotts u wan\n\n", NOROOTS);

    int num = 0;
    TESTER (&num);

    fclose (stdin);
#endif

    return 0;
}
