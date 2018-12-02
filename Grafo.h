#include "Lista.h"
#include <string.h>
/* Defining Constants */
#define ORIGIN 0
#define DESTINATION 1
#define VISITED 1
#define NOT_VISITED 0
#define INF 10000
#define True 1
#define False 0

/* Defining the Data structure */
#ifndef GRAFO
#define GRAFO

typedef struct Vertice{
    int id;                   // Name that represents a Vertex
    List* adj;               // List of Adjacency. It contains pointer to Edges that are linking this vertice to others 
}Vert;

typedef struct Edge{
    int cost;                 // Weight of this edge
    int path[2];              // Variable to store the vertices that this Edge is linking;
}Edge;

/* Input and Output Functions*/
Vert* Read_Input_Graph(const char* name, int *VectorLength, List** allEdges);
void Print_Graph(Vert* toPrint,int size);
void Print_Output_File(const char* name, Edge* toPrint, int size);
void Print_Output_Terminal(int bestCost, int totalCost, int multiplePaths);

/* Graph management Functions */
Edge* MST_Prim(Vert* toSearch, int size, int* multiplePaths);
int BestStartPoint(Vert* toSearch, int size);
int Path_Cost_List(List* toCalculate);
int Path_Cost_Array(Edge* toCalculate, int size);
void Order_Edge_Array(Edge* toReturn, int size);

void Free_Graph(Vert* toLiberate, int size);
#endif