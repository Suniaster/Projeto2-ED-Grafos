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

void FreeList(List* aLiberar){
    while(!ListaVazia(aLiberar)){
        free(RemoveStart(aLiberar));
    }
    free(aLiberar->head);
    free(aLiberar);
}