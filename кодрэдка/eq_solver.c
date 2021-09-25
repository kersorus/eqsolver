#include "eq_solver.h"

#define BUFSIZE 128

const int EXITCODEE = -2;
const int NOROOTSS  = -1;

//*************************************************************************************************

int main(int argc, char *argv[])
{
#ifndef TEST
    printf ("# Equation solver ( square (a * x^2 + b * x + c = 0) version )\n"
            "#    (c) kersorus, 2020-21\n\n");
    printf ("#    Enter your a, b, c: ");

    double a = 0, b = 0, c = 0;
    checker (&a, &b, &c);
    if (a)
        coeff_normalizing (&a, &b, &c);

    double x1 = 0, x2 = 0;
    int n_of_roots = solver (a, b, c, &x1, &x2);

    printf ("#    Answer: ");
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

#ifdef TEST
    if (argc == 2)
    {
        if (!freopen (argv[1], "r", stdin))
        {
            printf ("#    first make TESTFILE");
            exit (5);
        }
    }
    else
    {
        printf ("#    give prog name of test file\n");
        exit (6);
    }

    printf ("#    too stop dat sheet put root amount = %d\n", EXITCODEE);
    printf ("#    too make infinitii put root amount = 20\n");
    printf ("#    first root is lover then sacond\n");
    printf ("#    no rotts means amnt = %d and any rotts u wan\n\n", NOROOTSS);

    int num = 0;
    TESTER (&num);

    fclose (stdin);
#endif

    return 0;
}
