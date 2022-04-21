all: compall run


compall:
	gcc Tree/tree.c lexer/lexer.c differ/calc.c differ/main.c -lm -o diff.out

run:
	./diff.out

valrun:
	valgrind -s --leak-check=full ./diff.out