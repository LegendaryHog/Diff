all: compall run


compall:
	gcc Tree/tree.c lexer/lexer.c Calcul/calc.c Calcul/main.c -lm -o calc.out

run:
	./calc.out

valrun:
	valgrind -s ./calc.out