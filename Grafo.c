#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/*  A function that takes a List of Edges as input and return the sum of the costs */
int Path_Cost_List(List* toCalculate){
    int totalCost = 0;
    for(int index=0; index < toCalculate->length; index++){
        Edge* evaluating;
        evaluating = AccessElement(toCalculate, index);
        totalCost += evaluating->cost;
    }
    return totalCost;
}

/*  A function that takes a List of Edges as input and return the sum of the costs */
int Path_Cost_Array(Edge* toCalculate, int size){
    int totalCost = 0;
    for(int index=0; index < size; index++){
        totalCost += toCalculate[index].cost;
    }
    return totalCost;
}

/* Function to Liberate data allocated on the graph */
void Free_Graph(Vert* toLiberate, int size){
    for(int iterator=0; iterator < size; iterator++){
        FreeList(toLiberate[iterator].adj);
    }
    free(toLiberate);
}

void Order_Edge_Array(Edge* toReturn, int size){
    int swap;
    int now, prev;
    Edge swapEdge;
    for(int iterator = 0; iterator < size; iterator++){
        /* Ordering elements in toReturn array */
        /* If Origin is less than the Destinantion, swap it's values */
        if(toReturn[iterator].path[ORIGIN] > toReturn[iterator].path[DESTINATION]){
            swap = toReturn[iterator].path[ORIGIN];
            toReturn[iterator].path[ORIGIN] =  toReturn[iterator].path[DESTINATION];
            toReturn[iterator].path[DESTINATION] = swap;
        }

        /* InsertionSort to be certain that the element is in the correct place */
        /* The edges have to be in order, with the first edge having more */
        for(int i=iterator; i>0 ;i--){
            now = toReturn[i].path[ORIGIN]*INF + toReturn[i].path[DESTINATION];
            prev = toReturn[i-1].path[ORIGIN]*INF + toReturn[i-1].path[DESTINATION];
            while(now < prev){
                swapEdge = toReturn[i];
                toReturn[i] =  toReturn[i-1];
                toReturn[i-1] = swapEdge;
                /* Recalculating values */ 
                now = toReturn[i].path[ORIGIN]*INF + toReturn[i].path[DESTINATION];
                prev = toReturn[i-1].path[ORIGIN]*INF + toReturn[i-1].path[DESTINATION];
            }
        }
    }
}

/* Algorithm of Prim's to find a Minimum Sppaning Tree:
    It take as parameter:
    -> A vector of vertices that are representing the graph
    -> One starting point (it's to really necessary, but inside the function it's explained)
    -> The amount of vertices in the graph
    -> An variable to return by reference if exist more than one Mst

    Knowing that a MST of a connected graph with N vertices have always N-1 egdes,
    the function will return a array ,with length size-1, of edges that are used in to make 
    the mst. 
 */
Edge* MST_Prim(Vert* toSearch, int startPoint ,int size, int* multiplePaths){

    /* If the starting parameter is not valid, stop the function*/ 
    if(startPoint > size-1){
        printf("Problem with parameters in MST_PRIM()\n");
        return NULL;
    }
    /* First is created a vector with the same size of Vertices Vector to store key values 
        and start all of them with infinite*/ 
    int* mstKeys;
    mstKeys = (int*)malloc(size*sizeof(int));
    
    /* Variable to store vertices that were already explored */
    int* exploredVertices = malloc(size*sizeof(int));

    /* Initialization variables */
    for(int i=0;i<size;i++){
        exploredVertices[i]=NOT_VISITED;
        mstKeys[i]=INF;
    }
    
    /* The key of the parameter entry is 0 */
    /* ~This isn't actually necessary, but with it is possible for 
    the function to return diferents MST's*/
    mstKeys[startPoint] = 0;

    /* Auxiliar variables */
    Vert* isFound;      // Auxliar to check if some vertex is already in the set of vertices explored               
    Edge* neighbors;                    // Auxiliar to iterate through a list of Edges
    Edge* PATH;                         // Used to find the last Edge that was put in the MST
    Edge* addPATH;                      // Stores a copy of PATH variable
    Edge* toReturn=calloc((size-1),sizeof(Edge));// Array of Edges to be returned
    int hasAlreadyVisited;                     // Work as Bollean to check an existence of a element in a set
    int toAdd;                          // Store the index of the next vertice to be explored
    int minKey=INF;                     // Necessary to found minimum values
    *multiplePaths = False;             // Variable to check if exist more then one MST
    /* Auxiliar Variables to Order the return vector */
    int swap;
    Edge swapEdge;
    int now, prev; 

    /* For every vertex in the vector toSearch */
    for(int iterator=0; iterator < size ; iterator++){
        
        /* Pick a vertex toAdd which is not there in exploredVertices and has minimum 
            key value. "Choose the best vertex to be explored"
        */
        minKey=INF;
        for(int search=0; search< size; search++){
            hasAlreadyVisited = False;

            /* Check if this path is already i pathTaken */
            /* ~aka "check if the vertex is already explored" */
            if(exploredVertices[search] == VISITED) hasAlreadyVisited = True;

            /*  If it's key is minimum and it was not already explored
                Update the minimum key */
            if(mstKeys[search] < minKey && hasAlreadyVisited == False){
                minKey = mstKeys[search];
                toAdd = search;
            }
        }
        
        /* Include toAdd to exploredVertices */
        /* ~aka "Explore the vertex with minimum key value that was not 
            alredy explored" 
        */
        exploredVertices[toAdd] = VISITED;

        /*  Update key value of all adjacent vertices of toAdd. To update the key values, 
            iterate through all adjacent vertices. For every adjacent vertex n, if weight of 
            edge of this neighbor is less than the previous key value of neighbor, 
            update the key value as weight of the edge to this neighbor
        */
        minKey = INF;
        for(int n=0; n<toSearch[toAdd].adj->length;n++){
            neighbors = AccessElement(toSearch[toAdd].adj,n);

            hasAlreadyVisited = False;
            /* Check if this path is already i pathTaken */
            /* aka already explored */
            if(exploredVertices[neighbors->path[DESTINATION]] == VISITED) 
                hasAlreadyVisited = True;

            /*  if this neighbor is not already discovered and has the same cost as the last path put
                it means that exist another MST;
            */
            if(neighbors->cost == mstKeys[neighbors->path[DESTINATION]] && hasAlreadyVisited == False){
                *multiplePaths = True;
            }

            /* Update the cost of neighbours if it's necessary */
            if(neighbors->cost < mstKeys[neighbors->path[DESTINATION]] && hasAlreadyVisited == False){
                mstKeys[neighbors->path[DESTINATION]] = neighbors->cost;
            }
            
            /* "Adding the last added edge to the list that will be returned" */
            /*  To know what Edge is been used pass through vertices:
                Use the last vertex that was put on the path List
                "newInpPath" to:
                For each adjacent vertex of him, find the one that has minimun value and
                is already on the path list.
                This way, we can know from what vertex the last vertex that was put
                in the path list come from
            */
            if(neighbors->cost<minKey && hasAlreadyVisited == True){
                PATH = neighbors;
                minKey = neighbors->cost;
            }
        }
        if(minKey != INF){
            /* Inserting element into returning array */
            toReturn[iterator-1] = *PATH;

        }

    }
    free(exploredVertices);
    free(mstKeys);
    return toReturn;
}