#include "Grafo.h"
#include <stdio.h>
#include <stdlib.h>
/*  Function to read input file.
    It receives a string with the name of the file in it.
    The function alocate space the necessary to store all the data that the input file is passing.
    It returns a vector of vertices which every index of it has:
        - An 'id': to identify the origin vertice;
        - An Adjacency List: which contain a list of arrests that indicate the path and the cost of a certain movimentaion in the graph.  
    The parameter "VectorLength" returns by reference the lentgh of the array read in the function.
    The parameter allEdges return by reference a list with all edges without repetitions, A-B = B-A.
*/
Vert* Read_Input_Graph(const char* name, int *VectorLength, Lista** allEdges){

    FILE* toRead;               // Variable to read input file

    toRead = fopen(name, "r");  // Opening only for reading
    if(toRead == NULL){         // Checking if it has openned correctly 
        printf("Failed to open File for reading, stoping the program...\n");
        exit(1);
    }
    
    int numberOfVertices;
    fscanf(toRead, "%d", &numberOfVertices);
    *VectorLength = numberOfVertices;

    /* Vector of Vertices to be returned */
    Vert* toReturn;
    toReturn = (Vert*)malloc(numberOfVertices * sizeof(Vert));

    /* Creating a list that will contain all vertices and be returned bu reference */
    Edge* toInsert;
    (*allEdges) = CriaLista();

    /* For every line in input file:
        -> Save the "id", which works as a identifier, of the vertice;
        -> Initializate a new Adjecency List for this vertice;
        -> Read and save the necessary information about the connections of this vertice;
    */
    for(int origin=0; origin < numberOfVertices; origin++){
        toReturn[origin].id = origin;
        toReturn[origin].adj = CriaLista();
        
        /* Iterate for every possible destination */
        for(int destination = 0; destination < numberOfVertices; destination++){
            int pathCost;
            fscanf(toRead, "%d", &pathCost);
            /*  If a path cost is 0 or less, this path actually doesn't exist.
                So it it will be not put on Adjancecy list of this Vertice
            */
            if(pathCost <= 0)continue;      
            
            /* Setting read values */
            Edge* newEdge;
            newEdge = (Edge*)malloc(sizeof(Edge));
            newEdge->cost = pathCost;
            newEdge->path[ORIGIN] = origin;
            newEdge->path[DESTINATION] = destination;

            /* Inserting into the Adjency list*/
            InsereFinal(toReturn[origin].adj, newEdge);

            /* Conditional to remove the repetitions */
            if(origin > destination){
                toInsert = (Edge*)malloc(sizeof(Edge));
                toInsert->cost = pathCost;
                toInsert->path[ORIGIN] = origin;
                toInsert->path[DESTINATION] = destination;
                InsereFinal((*allEdges), toInsert);
            }  
        }
    }
    fclose(toRead);
    return toReturn;
}

/* This function receives an array of Vertices and print them in the terminal */
void Print_Graph(Vert* toPrint,int size){
    /* Iterates on every vertice of the argument array */
    for(int i=0 ; i < size;i++){
        /* Print it's "id" */
        printf("%d  ->",toPrint[i].id);

        /* Print the vertices that are conecting to this vertice */
        for(int j=0 ;j<toPrint[i].adj->tamanho;j++){
            Edge* reading;
            reading = AcessaElemento(toPrint[i].adj,j);
            printf("\t|%d: %d\n", reading->path[1], reading->cost);
        }
        printf("\n");
    }
}

/*  Function to print the file with edges information 
    Takes as input:
        -> Name of the file ("name");
        -> A list of edges to be printed ("toPrint");
*/
void Print_Output_File(const char* name, Lista* toPrint){

    /* Opening file to write */
    FILE* printing;
    printing = fopen(name, "w");

    /* Ordering elements to print information in order */
    int swap;
    Edge* willChange;
    for(int i=0; i < toPrint->tamanho; i++){
        willChange = AcessaElemento(toPrint, i);
        if(willChange->path[ORIGIN] > willChange->path[DESTINATION]){
            swap = willChange->path[ORIGIN];
            willChange->path[ORIGIN] =  willChange->path[DESTINATION];
            willChange->path[DESTINATION] = swap;
        }
    }

    /* Priting the information of the edges */
    Edge* willPrint;
    for(int i=0; i < toPrint->tamanho; i++){
        willPrint = AcessaElemento(toPrint, i);
        fprintf(printing, "%d,%d\n", willPrint->path[ORIGIN], willPrint->path[DESTINATION]);
    }
    /* Liberating allocated data */

    /* Closing File */
    fclose(printing);
}