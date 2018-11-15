#include "Lista.h"
#include <string.h>
/* Defining Constants */
#define ORIGIN 0
#define DESTINATION 1
#define VISITED 1
#define NOT_VISITED 0
#define INF 100000
#define True 1
#define False 0

/* Defining the Data structure */
#ifndef GRAFO
#define GRAFO

typedef struct Vertice{
    int id;                   // Name that represents a Vertice
    List* adj;               // List of Adjacency. It contains pointer to Edges that are linking this vertice to others 
}Vert;

typedef struct Edge{
    int cost;                 // Weight of this edge
    int path[2];              // Variable to store the vertices that this Edge is linking;
}Edge;

/* Input and Output Functions*/
Vert* Read_Input_Graph(const char* name, int *VectorLength, List** allEdges);
void Print_Graph(Vert* toPrint,int size);
void Print_Output_File(const char* name, List* toPrint);

/* Graph management Functions */
int DFS(Vert* toSearch, int* visited, int searching, int startingConnection);
List* MST_Prim(Vert* toSearch, int startPoint ,int size, int* multiplePaths);
int Path_Cost(List* toCalculate);

void Free_Graph(Vert* toLiberate, int size);
#endif