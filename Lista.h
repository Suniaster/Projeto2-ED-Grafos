#ifndef LIST
#define LIST

typedef struct doubleLinkedNode{

    void* info;
    int *order;
    struct doubleLinkedNode* next;
    struct doubleLinkedNode* prev;

}cel;

typedef struct List{
    int length;
    cel* head;
    cel* tail;
}List;

/* Cria List Vazia*/
List* CreateList();

/* Confere Estado da List */
int ListVazia(List* Verificando);

/* Inserção de elemento */
void InsertStart(List* aInserir, void* inf);
void InsertEnd(List* aInserir, void* inf);

/* Acessando Elementos pelo indice */
void* AccessElement(List* acessando, int indice);

/* Remoção de Elementos */
void* RemoveStart(List* aRemover);
void* RemoveEnd(List* aRemover);

/* Outros métodos úteis */
void FreeList(List* aLiberar);

#endif