all: teste.o Lista.o Grafo.o Inout.o 
	gcc -g teste.o Lista.o Grafo.o Inout.o
teste.o: teste.c
	gcc -g -c teste.c
Lista.o: Lista.c
	gcc -g -c Lista.c
Grafo.o: Grafo.c
	gcc -g -c Grafo.c
Inout.o: Inout.c
	gcc -g -c Inout.c
clean: 
	rm teste.o Lista.o Grafo.o Inout.o a.out