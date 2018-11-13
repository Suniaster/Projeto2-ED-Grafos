#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/*  Function to read input file.
    It receives a string with the name of the file in it.
    The function alocate space the necessary to store all the data that the input file is passing.
    It returns a vector of vertices which every index of it has:
        - An 'id': to identify the origin vertice;
        - An Adjacency List: which contain a list of arrests that indicate the path and the cost of a certain movimentaion in the graph.  
    The last parameter "VectorLength" returns by reference the lentgh of the array read in the function. 
*/
Vert* Read_Input_Graph(char* name, int *VectorLength){

    FILE* toRead;               // Variable to read input file

    toRead = fopen(name, "r");  // Opening only for reading
    if(toRead == NULL){         // Checking if it has openned correctly 
        printf("Failed to open File for reading, stoping the program...\n");
        exit(1);
    }
    
    int numberOfVertices;
    fscanf(toRead, "%d", &numberOfVertices);
    *VectorLength = numberOfVertices;

    Vert* toReturn;
    toReturn = (Vert*)malloc(numberOfVertices * sizeof(Vert));

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
        }
    }
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

/*  Depth-Fisrt-Search:
    This function find the first valid path that connect some certain vertice to all others.
    Take as parameter:
        -> A vector of vertices that contains all the graph. "toSearch"
        -> a vector of integers that has the same lenght of the vector of vertices "visited"
            - It is used for store if some vertice was visited or not
        -> A integer that represents what vertice is being searched "searching"
        -> ????
*/
void DFS(Vert* toSearch, int* visited, int searching, const int numberOfVertices){
    /* Mark as Visted when pass through this particular vertice */
    visited[searching] = VISITED;
    printf("%d\n", toSearch[searching].id);

    /* For each one of the connections this vertice have with other vertices */
    for(int connection = 0 ;connection < toSearch[searching].adj->tamanho ; connection++){
        Edge* willSearch;
        willSearch = AcessaElemento(toSearch[searching].adj, connection);
        /* If the path->cost equal to 0, the path actually don't exist */
        /* If the previous statement is true or the vertice was already visited, pass to next vertice */
        if(willSearch->cost == 0 || visited[willSearch->path[DESTINATION]] == VISITED){
            continue;
        }

        /* Search again in the first found valid connection */
        DFS(toSearch, visited, willSearch->path[DESTINATION], numberOfVertices);
    }
}