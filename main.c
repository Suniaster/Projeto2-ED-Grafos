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
    List* allEdges;
    int graphSize;
    int multiplePaths;

    /* Read input and store the information in a vector of vertices */
    /* allEdges is a list with all Edges that not repeat in the graph */
    graph = Read_Input_Graph(argv[1], &graphSize, &allEdges);

    /* Using Prim's algorithm to find the first best MST in the graph */
    /* Best path is a array of edges that contain only the necessary edges in the best path */
    Edge* bestPath;
    bestPath = MST_Prim(graph, graphSize, &multiplePaths);

    /* Calculating the path costs */
    int allCost;
    int bestCost;
    allCost = Path_Cost_List(allEdges);
    bestCost = Path_Cost_Array(bestPath, graphSize - 1);

    /* Printing mesages on console */
    Print_Output_Terminal(bestCost, allCost, multiplePaths);

    /* Priting information on output file */
    Print_Output_File("output.txt", bestPath, graphSize - 1);

    /* Freeing memory alocated */
    Free_Graph(graph, graphSize);
    free(bestPath);
    FreeList(allEdges);
    
    return 0;
}