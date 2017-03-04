all: disasTest

disasTest: disas.o
	gcc disas.o dtest.c -o dtest
disas.o: disas.c
	gcc disas.c -c

clean:
	rm disas.o disasTest