#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/*  Depth-Fisrt-Search:
    This function find the first valid path that connect some certain vertice to all others.
    Take as parameter:
        -> A vector of vertices that contains all the graph. "toSearch"
        -> A vector of integers that has the same lenght of the vector of vertices "visited"
            - It is used for store if some vertice was visited or not
        -> An integer that represents what vertice is being searched "searching"
        -> An integer to change between starting paths in search "startingConnection"
    Returns the totalCost of taking this path.
*/
int DFS(Vert* toSearch, int* visited, int searching, int startingConnection){
    /* Mark as Visted when pass through this particular vertice */
    visited[searching] = VISITED;
    printf("%d\n", toSearch[searching].id);

    /* Variable to return the total cost of using the path it will create */
    int totalCost = 0 ;

    /* For each one of the connections this vertice have with other vertices */
    int connection;
    for(int iterator = 0 ;iterator < toSearch[searching].adj->tamanho ; iterator++){
        
        connection = (startingConnection + iterator)%toSearch[searching].adj->tamanho;
        Edge* willSearch;
        willSearch = AcessaElemento(toSearch[searching].adj, connection);

        /* If the path->cost equal to 0, the path actually don't exist */
        /* If the previous statement is true or the vertice was already visited, pass to next vertice */
        if(willSearch->cost == 0 || visited[willSearch->path[DESTINATION]] == VISITED){
            continue;
        }
        totalCost += willSearch->cost;

        /* Search again in the first found valid connection */
        totalCost += DFS(toSearch, visited, willSearch->path[DESTINATION], 0);
    } 
    return totalCost;
}

/*  A function that takes a List of Edges as input and return the sum of the costs */
int Path_Cost(Lista* toCalculate){
    int totalCost = 0;
    for(int index=0; index < toCalculate->tamanho; index++){
        Edge* evaluating;
        evaluating = AcessaElemento(toCalculate, index);
        totalCost += evaluating->cost;
    }
    return totalCost;
}

/* Function to Liberate data allocated on the graph */
void Free_Graph(Vert* toLiberate, int size){
    for(int iterator=0; iterator < size; iterator++){
        FreeLista(toLiberate[iterator].adj);
    }
    free(toLiberate);
}

Lista* MST_Prim(Vert* toSearch, int startPoint ,int size, int* multiplePaths){

    /* If the starting parameter is not valid, stop the function*/ 
    if(startPoint > size-1){
        printf("Problem with parameters in MST_PRIM()\n");
        return NULL;
    }
    /* First is created a vector with the same size of Vertices Vector to store key values and start all of them with infinite*/ 
    int* mstKeys;
    mstKeys = (int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++)mstKeys[i]=INF;
    
    /* Variable to store Edges used in the minimun spanning tree path */
    Lista* pathTaken;
    pathTaken = CriaLista();
    
    /* The key of the first entry is 0 */
    mstKeys[startPoint] = 0;

    /* Auxiliar variables */
    Vert* isFound;                      // Auxliar to check if some vertex is already in the set of vertices explored
    Vert* newInPath;                    // Auxiliar to be inserted in a set 
    Edge* neighbors;                    // Auxiliar to iterate through a list of Edges
    Edge* PATH;                         // Used to find the last Edge that was put in the MST
    Edge* addPATH;                      // Stores a copy of PATH variable
    Lista* toReturn = CriaLista();      // List of Edges to be returned
    int hasAlready;                     // Work as Bollean to check an existence of a element in a set
    int toAdd;                          // Store the index of the next vertice to be explored
    int minKey=INF;                     // Necessary to found minimum values
    *multiplePaths = False;             // Variable to check if exist more then one MST

    /* For every vertex in the vector toSearch */
    for(int iterator=0; iterator < size ; iterator++){
        
        /* Pick a vertex toAdd which is not there in pathTaken and has minimum key value.
           "Choose the best vertex to be explored"
        */
        minKey=INF;
        for(int search=0; search< size; search++){
            hasAlready = False;
            /* Check if this path is already i pathTaken */
            for(int listValues=0;listValues < pathTaken->tamanho;listValues++){
                isFound = AcessaElemento(pathTaken,listValues);
                if(search == isFound->id)hasAlready = True;
            }
            /* Update minimum key */
            if(mstKeys[search] < minKey && hasAlready == False){
                minKey = mstKeys[search];
                toAdd = search;
            }
        }
        
        /*Include toAdd to pathTaken*/
        /* "Explore the vertex" */
        newInPath = (Vert*)malloc(sizeof(Vert));
        memcpy(newInPath, &toSearch[toAdd], sizeof(Vert));
        InsereFinal(pathTaken, newInPath);


        /*  To know what Edge is been used pass through vertices:
            Use the last vertex that was put on the path List
            "newInpPath" to:
            For each adjacent vertex of him, find the one that has minimun value and
            is already on the path list.
            This way, we can know from what vertex the last vertex that was put
            in the path list come from
         */
        /* "Adding the last added edge to the list that will be returned" */
        minKey = INF;
        for(int i=0;i< newInPath->adj->tamanho;i++){
            neighbors = AcessaElemento(newInPath->adj, i);
            hasAlready = False;

            for(int j=0;j<pathTaken->tamanho;j++){
                isFound = AcessaElemento(pathTaken,j);
                if(neighbors->path[DESTINATION] == isFound->id)hasAlready=True;
            }

            if(neighbors->cost<=minKey && hasAlready == True){
                PATH = neighbors;
                minKey = neighbors->cost;
            }
        }
        if(minKey != INF){
            addPATH=(Edge*)malloc(sizeof(Edge));
            memcpy(addPATH, PATH, sizeof(Edge));
            InsereFinal(toReturn, addPATH);
        }

        /*  Update key value of all adjacent vertices of toAdd. To update the key values, 
            iterate through all adjacent vertices. For every adjacent vertex n, if weight of 
            edge of this neighbor is less than the previous key value of neighbor, 
            update the key value as weight of the edge to this neighbor
        */
        for(int n=0; n<toSearch[toAdd].adj->tamanho;n++){
            neighbors = AcessaElemento(toSearch[toAdd].adj,n);

            hasAlready = False;
            /* Check if this path is already i pathTaken */
            /* aka already explored */
            for(int listValues=0;listValues < pathTaken->tamanho;listValues++){
                isFound = AcessaElemento(pathTaken,listValues);
                if(neighbors->path[DESTINATION] == isFound->id)hasAlready = True;
            }

            /*  if this neighbor is not already discovered and has the same cost as the last path put
                it means that exist another MST;
            */
            if(neighbors->cost == mstKeys[neighbors->path[DESTINATION]] && hasAlready == False){
                *multiplePaths = True;
            }

            /* Update the cost of neighbours if it's necessary */
            if(neighbors->cost < mstKeys[neighbors->path[DESTINATION]]){
                mstKeys[neighbors->path[DESTINATION]] = neighbors->cost;
            }
        }

    }
    FreeLista(pathTaken);
    free(mstKeys);
    return toReturn;
}