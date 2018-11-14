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

Lista* MST_Prim(Vert* toSearch, int startPoint ,int size){

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
    Vert* isFound;
    Vert* newInPath;
    Edge* neighbors;
    Edge* PATH;
    Edge* addPATH;
    Lista* toReturn = CriaLista();
    int hasAlready;
    int toAdd;
    int minKey=INF; 

    /* For every vertex in the vector toSearch */
    for(int iterator=0; iterator < size ; iterator++){
        
        /* Pick a vertex toAdd which is not there in pathTaken and has minimum key value.
        */
        minKey=INF;
        for(int search=0; search< size; search++){
           hasAlready = False;
           for(int listValues=0;listValues < pathTaken->tamanho;listValues++){
                isFound = AcessaElemento(pathTaken,listValues);
                if(search == isFound->id)hasAlready = True;
           }
           if(mstKeys[search] < minKey && hasAlready == False){
               minKey = mstKeys[search];
               toAdd = search;
           }
        }

        /*Include toAdd to pathTaken*/
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
        minKey = INF;
        for(int i=0;i< newInPath->adj->tamanho;i++){
            neighbors = AcessaElemento(newInPath->adj, i);
            hasAlready = False;

            for(int j=0;j<pathTaken->tamanho;j++){
                isFound = AcessaElemento(pathTaken,j);
                if(neighbors->path[DESTINATION] == isFound->id)hasAlready=True;
            }

            if(neighbors->cost<minKey && hasAlready == True){
                PATH = neighbors;
                minKey = neighbors->cost;
            }
        }
        // If the last block of code has find what it was suposed to, insert that Edge in a list to return
        if(minKey != INF){
            addPATH=(Edge*)malloc(sizeof(Edge));
            memcpy(addPATH, PATH, sizeof(Edge));
            InsereFinal(toReturn, addPATH);
        }

        /* Update key value of all adjacent vertices of toAdd. To update the key values, 
        iterate through all adjacent vertices. For every adjacent vertex n, if weight of 
        edge of this neighbor is less than the previous key value of neighbor, update the key value as weight of the edge to this neighbor
        */
        for(int n=0; n<toSearch[toAdd].adj->tamanho;n++){
            neighbors = AcessaElemento(toSearch[toAdd].adj,n);

            if(neighbors->cost < mstKeys[neighbors->path[DESTINATION]]){
                mstKeys[neighbors->path[DESTINATION]] = neighbors->cost;
            }
        }

    }
    FreeLista(pathTaken);
    free(mstKeys);
    return toReturn;
}