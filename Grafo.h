#include "Lista.h"
/* Defining Constants */
#define ORIGIN 0
#define DESTINATION 1

/* Defining the Data structure */
#ifndef GRAFO
#define GRAFO

typedef struct Vertice{
    int id;                   // Name that represents a Vertice
    Lista* adj;               // List of Adjacency. It contains pointer to Edges that are linking this vertice to others. 
}Vert;

typedef struct Edge{
    int cost;                 // Weight of this edge
    int path[2];              // Variable to store the vertices that this Edge is linking;
}Edge;

Vert* Read_Input_Graph(char* name, int *VectorLength);

#endif