#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

List* CreateList(){
    List* NovaLista;
    NovaLista = (List*)malloc(sizeof(List));

    NovaLista->head = (cel*)malloc(sizeof(cel));
    NovaLista->tail=NovaLista->head;
    NovaLista->head->next=NULL;   
    NovaLista->head->order = NULL;    
    NovaLista->length=0;
    return NovaLista;
}

int ListaVazia(List* Verificando){
    if(Verificando->head==Verificando->tail){
        return 1;
    }
    else{
        return 0;
    }
}

void InsertStart(List* aInserir, void* inf){
    cel* Inserindo = (cel*)malloc(sizeof(cel));
    Inserindo->info = inf;

    Inserindo->next=aInserir->head->next;
    aInserir->head->next=Inserindo;

    aInserir->length++;
}

void InsertEnd(List* aInserir, void* inf){
    cel* Inserindo = (cel*)malloc(sizeof(cel));
    Inserindo->info = inf;

    aInserir->tail->next = Inserindo;
    aInserir->tail=aInserir->tail->next;

    aInserir->length++;
}

void* AccessElement(List* acessando, int indice){
    if(indice+1 > acessando->length ){
        printf("Acessando Local invalido\n");
        return NULL;
    }
    cel* procurando;
    procurando = acessando->head->next;
    for(int i=0; i < indice ;i++){
        procurando = procurando->next;
    }

    return procurando->info;
}

void* RemoveStart(List* aRemover){
    cel* removida;
    void* infReturn;
    if(ListaVazia(aRemover)){
        printf("Tentando remover de Fila Vazia\n");
        return NULL;
    }
    removida = aRemover->head;
    aRemover->head=aRemover->head->next;
    infReturn = aRemover->head->info;

    free(removida);
    aRemover->length--;
    return infReturn;

}

void* RemoveEnd(List* aRemover){
    cel* removida;
    void* infReturn;

    if(ListaVazia(aRemover)){
        printf("Tentando remover de Fila Vazia\n");
        return NULL;
    }
    removida = aRemover->tail;
    aRemover->tail = aRemover->tail->prev;
    infReturn = removida->info;

    free(removida);
    aRemover->length--;
    return infReturn;

}

int ProcuraRef(List* aProcurar, void* procurando){
    cel* comparando;
    comparando = aProcurar->head->next;
    while(comparando != aProcurar->tail->next){
        if(comparando->info == procurando){
            return 1;
        }
        else comparando = comparando->next;
    }
    return 0;
}

void FreeList(List* aLiberar){
    while(!ListaVazia(aLiberar)){
        free(RemoveStart(aLiberar));
    }
    free(aLiberar->head);
    free(aLiberar);
}

void EmptyList(List* toEmpty){
    while(!ListaVazia(toEmpty)){
        RemoveStart(toEmpty);
    }
    free(toEmpty->head);
    free(toEmpty);
}


void* RetiraOrdList(List* aRemover){
    cel* removida;
    void* infReturn;
    if(aRemover->length == 0){
        printf("Tentando remover de Fila Vazia\n");
        return NULL;
    }
    removida = aRemover->head;
    aRemover->head = aRemover->head->next;
    infReturn = aRemover->head->info;

    if(removida->order!=NULL) free(removida->order);
    free(removida);
    aRemover->length--;
    return infReturn;
}

void FreeOrdList(List* aLiberar){
    while(aLiberar->length > 0){
        free(RetiraOrdList(aLiberar));
    }
    if(aLiberar->head->order!=NULL) free(aLiberar->head->order);
    free(aLiberar->head);
    free(aLiberar);
}

void InsereCrescente(List* aInserir, void* inf, int* order, int quantidadeDeChaves){

    cel* Inserindo = (cel*)malloc(sizeof(cel));
    Inserindo->info = inf;
    Inserindo->order = (int*)malloc(quantidadeDeChaves*sizeof(int));
    aInserir->length++;

    /* Coping order to be followed */
    for(int i=0; i < quantidadeDeChaves; i++)Inserindo->order[i] = order[i];

    /* Find the right place to put the new Information */
    cel* confere;
    confere = aInserir->head;
    if(confere->next == NULL){
        Inserindo->next = NULL;
        confere->next = Inserindo;
        return;
    }
    
    for(int keyNumber=0; keyNumber < quantidadeDeChaves ;keyNumber++){
        while(confere->next != NULL && order[keyNumber] > confere->next->order[keyNumber]){
            confere = confere->next;
        }
    }
    
    if(confere->next == NULL){
        Inserindo->next = confere->next;
        confere->next = Inserindo;
        return;
    }

    Inserindo->next = confere->next;
    confere->next = Inserindo;
}
