all: main.o Lista.o Grafo.o Inout.o 
	gcc -g main.o Lista.o Grafo.o Inout.o -o mst
main.o: main.c
	gcc -g -c main.c
Lista.o: Lista.c
	gcc -g -c Lista.c
Grafo.o: Grafo.c
	gcc -g -c Grafo.c
Inout.o: Inout.c
	gcc -g -c Inout.c
clean: 
	rm -f main.o Lista.o Grafo.o Inout.o mst