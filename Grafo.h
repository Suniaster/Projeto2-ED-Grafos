#include "Lista.h"
#ifndef GRAFO
#define GRAFO

typedef struct Vertice{
    int id;                   // Name that represents a Vertice
    Lista* adj;               // List of Adjacency. It contains pointer to Edges that are linking this vertice to others. 
}Vert;

typedef struct Edge{
    int weight;               // Weight of this edge
    Vert path[2];             // Variable to store the vertices that this Edge is linking;
}Edge;


#endif