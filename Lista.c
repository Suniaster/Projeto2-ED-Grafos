#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

Lista* CriaLista(){
    Lista* NovaLista;
    NovaLista = (Lista*)malloc(sizeof(Lista));

    NovaLista->inicio = (cel*)malloc(sizeof(cel));
    NovaLista->fim=NovaLista->inicio;

    NovaLista->tamanho=0;
    return NovaLista;
}

int ListaVazia(Lista* Verificando){
    if(Verificando->inicio==Verificando->fim){
        return 1;
    }
    else{
        return 0;
    }
}

void InsereInicio(Lista* aInserir, void* inf){
    cel* Inserindo = (cel*)malloc(sizeof(cel));
    Inserindo->info = inf;

    Inserindo->prox=aInserir->inicio->prox;
    aInserir->inicio->prox=Inserindo;

    aInserir->tamanho++;
}

void InsereFinal(Lista* aInserir, void* inf){
    cel* Inserindo = (cel*)malloc(sizeof(cel));
    Inserindo->info = inf;

    aInserir->fim->prox = Inserindo;
    aInserir->fim=aInserir->fim->prox;

    aInserir->tamanho++;
}

void* AcessaElemento(Lista* acessando, int indice){
    if(indice+1 > acessando->tamanho ){
        printf("Acessando Local invalido\n");
        return NULL;
    }
    cel* procurando;
    procurando = acessando->inicio->prox;
    for(int i=0; i < indice ;i++){
        procurando = procurando->prox;
    }

    return procurando->info;
}

void* RemoveInicio(Lista* aRemover){
    cel* removida;
    void* infReturn;
    if(ListaVazia(aRemover)){
        printf("Tentando remover de Fila Vazia\n");
        return NULL;
    }
    removida = aRemover->inicio;
    aRemover->inicio=aRemover->inicio->prox;
    infReturn = aRemover->inicio->info;

    free(removida);
    aRemover->tamanho--;
    return infReturn;

}

void* RemoveFinal(Lista* aRemover){
    cel* removida;
    void* infReturn;

    if(ListaVazia(aRemover)){
        printf("Tentando remover de Fila Vazia\n");
        return NULL;
    }
    removida = aRemover->fim;
    aRemover->fim = aRemover->fim->ant;
    infReturn = removida->info;

    free(removida);
    aRemover->tamanho--;
    return infReturn;

}

int ProcuraRef(Lista* aProcurar, void* procurando){
    cel* comparando;
    comparando = aProcurar->inicio->prox;
    while(comparando != aProcurar->fim->prox){
        if(comparando->info == procurando){
            return 1;
        }
        else comparando = comparando->prox;
    }
    return 0;
}

void FreeLista(Lista* aLiberar){
    while(!ListaVazia(aLiberar)){
        free(RemoveInicio(aLiberar));
    }
    free(aLiberar->inicio);
    free(aLiberar);
}

void EmptyList(Lista* toEmpty){
    while(!ListaVazia(toEmpty)){
        RemoveInicio(toEmpty);
    }
    free(toEmpty->inicio);
    free(toEmpty);
}