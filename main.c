#include <stdio.h>
#include "Grafo.h"
#include <stdlib.h>


int main(int argc, char const *argv[]){

    if(argc != 2){
        printf("Quantidade inválida de argumentos...\n");
        printf("Por favor inserir o nome do arquivo de entrada.\n");
        exit(1);
    }

    /* Variables to store the data collected */
    Vert* graph;
    Lista* allEdges;
    int graphSize;

    /* Read input and store the information in a vector of vertices */
    /* allEdges is a list with all Edges that not repeat in the graph */
    graph = Read_Input_Graph(argv[1], &graphSize, &allEdges);

    /* Using Prim's algorithm to find the first best MST in the graph */
    /* Best path is a list of edges that contain only the necessary edges in the best path */
    Lista* bestPath;
    bestPath = MST_Prim(graph, 0, graphSize);

    /* Calculating the path costs */
    int allCost;
    int bestCost;
    allCost = Path_Cost(allEdges);
    bestCost = Path_Cost(bestPath);

    /* Printing mesages on console */
    printf("MST com custo: %d\n", bestCost);
    printf("Economia vs malha totalmente conexa: %d\n", allCost - bestCost);
    printf("Quantidade de MST's diferentes: NULL\n");

    /* Priting information on output file */
    Print_Output_File("output.txt", bestPath);

    /* Freeing memory alocated */
    Free_Graph(graph, graphSize);
    FreeLista(bestPath);
    FreeLista(allEdges);
    
    return 0;
}