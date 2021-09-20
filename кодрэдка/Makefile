clean:
	rm ./a.out
	clear

eqsol:
	gcc eq_solver.c eq_solver_funcs.c -lm -D NDEBUG

debug:
	gcc -Wall eq_solver.c eq_solver_funcs.c -lm -g

eqtest:
	gcc -Wall eq_solver.c eq_solver_funcs.c -lm -D TEST
