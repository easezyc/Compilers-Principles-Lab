make:
	bison -d bison.y
	flex flex.l
	gcc bison.tab.c -lfl -ly -lm -o parser
test:
	./parser test.c
