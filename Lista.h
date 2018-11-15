#ifndef LISTA
#define LISTA

typedef struct doubleLinkedNode{

    void* info;
    int *ordem;
    struct doubleLinkedNode* prox;
    struct doubleLinkedNode* ant;

}cel;

typedef struct Lista{
    int tamanho;
    cel* inicio;
    cel* fim;
}Lista;

/* Cria Lista Vazia*/
Lista* CriaLista();

/* Confere Estado da Lista */
int ListaVazia(Lista* Verificando);

/* Inserção de elemento */
void InsereInicio(Lista* aInserir, void* inf);
void InsereFinal(Lista* aInserir, void* inf);

/* Acessando Elementos pelo indice */
void* AcessaElemento(Lista* acessando, int indice);

/* Remoção de Elementos */
void* RemoveInicio(Lista* aRemover);
void* RemoveFinal(Lista* aRemover);

/* Lista ordenada */
void InsereCrescente(Lista* aInserir, void* inf, int* Ordem, int quantidadeDeChaves);
void* RetiraOrdList(Lista* aRemover);
void FreeOrdLista(Lista* aLiberar);

/* Outros métodos úteis */
int ProcuraRef(Lista* aProcurar, void* procurando);
void FreeLista(Lista* aLiberar);
void EmptyList(Lista* toEmpty);

#endif