#include "Arvore.h"
#include <stdio.h>
#include <stdlib.h>

/*  Rotação Simples Direita:
    Feita quando há um desebalanceamento a esquerda do nó passado como paramêtro
    e também um desbalanceamento a esquerda em seu filho da esquerda.
        X                    Y
       /                    / \
      Y       RSD(X) ->    Z   X
     / 
    Z  
    É passado como parâmetro o nó onde o desbalanceamento é maior que 1.
    O(1)
*/
void RSD(Tnode** N){
    Tnode* aux;
    aux = (*N)->left;
    (*N)->left = aux->right;
    aux->right = (*N);
    (*N) = aux;
}

/*  Rotação Simples Esquerda:
    Feita quando há um desebalanceamento a direita do nó passado como paramêtro
    e também um desbalanceamento a direita em seu filho da direita.
    X                       Y
     \                     / \
      Y       RSE(X)->    X   Z
       \
        Z     
    É passado como parâmetro o nó onde o Fator de Balancealemto é menor que -1.    
    O(1)
*/
void RSE(Tnode** N){
    Tnode* aux;
    aux = (*N)->right;
    (*N)->right = aux->left;
    aux->left = (*N);
    (*N) = aux;
}

/*  Calcula a altura de determinado nó 
    Vê se qual altura das arvores filhas é maior,
    e baseado nisso, sua altura é a decidida + 1;
    O(1);
*/
int Altura(Tnode* N){
    if(N==NULL){
        return 0;
    }
    int left, right;

    if(N->left == NULL)left=-1;
    else left = N->left->height;

    if(N->right == NULL)right=-1;
    else right = N->right->height;

    if(left>right)return left+1;
    else return right+1;
}

/*  Passa em todos os nós abaixo do que foi passado como parametro
    e atualiza a altura dos mesmos.
    O(n), sendo n o tamanho da arvore abaixo do nó que foi passado.
*/
int RecalculaAltura(Tnode **N){
    if((*N)==NULL){
        return 0;
    }
    int leftHeight, rightHeight;
    leftHeight = RecalculaAltura(&(*N)->left);
    rightHeight = RecalculaAltura(&(*N)->right);

    if(leftHeight > rightHeight){
        (*N)->height = leftHeight+1;
        return (*N)->height;
    }
    else{
        (*N)->height = rightHeight+1;
        return (*N)->height;
    }
}

/*  Fator de Balanceamento:
    O FB de um determinado nó é dado pela altura da arvore do seu filho a esquerda menos
    a altura da arvore do seu filho a direita.
    Dessa forma é possível saber se algum dos lados da arvore está maior que o outro.
    O(1)
*/
int FB(Tnode* N){
    if(N==NULL){
        return 0;
    }
    int left, right;

    if(N->left == NULL)left=0;
    else left = N->left->height;

    if(N->right == NULL)right=0;
    else right = N->right->height;

    return left-right;
}

/* Função para concertar o balanceamento de determinado nó:
    Primeiramente é chamada a função do Fator de Balancemento.
    Caso haja algum desbalaceamento, ele é concertado usando
    uma rotação simples, ou uma rotação dupla.
    --Rotação dupla:
      0               0
     /                 \
    0         ou        0
     \                 /
      0               0
    A rotação dupla consiste de duas rotações simples em sequencia, uma
    aplicada no filho que esteja desbalanceado e outra no próprio nó.
    Exemplo:
      X                  X                Z
     /                  /                / \
    Y      RSE(Y)->    Z    RSD(X)->    Y   X
     \                /  
      Z              Y
    Analogamente, para o caso inverso onde há a necessidade de Rotação dupla, é 
    usado o mesmo procedimento, porém é primeiro feito RSD e depois RSE.

    Retorna 1 caso tenha acontecido alguma mudança na árvore.
    Retorna 0 caso contrário.
    O(1)
*/
int Repara(Tnode** N){

    int pivo;
    int pLeft, pRight;
    Tnode* aux;
    pivo = FB((*N));

    if(pivo<-1){
        aux = (*N)->right;
        pRight = FB(aux);

        if(pRight < 0){
            RSE(&(*N));
        }
        if(pRight > 0){
            RSD(&aux);
            RSE(&(*N));
        }
        return 1;
    }
    if(pivo>1){
        aux = (*N)->left;
        pLeft = FB(aux);

        if(pLeft > 0){
            RSD(&(*N));
        }
        if(pLeft < 0){
            RSE(&aux);
            RSD(&(*N));
        }
        return 1;
    }
    return 0;

}

/*  Função de Inserção na Ávore AVL:
    Recebe como parâmetro a raiz da Arvore que está o elemento será inserido.

    Para a inserção de elementos na Árvore AVL, o o filho da esquerda deve ser menor ou 
    igual a seu pai, e o filho da direita deve ser maior ou igual ao mesmo. 

    Função Recursiva.

    Para chegar a uma folha é necessário log(n) chamadas recursivas.

    Caso a função "Recalcula" retorne 1, ou seja, caso haja alguma mudança
    no formato da arvore causado pela inserção, é recalculada a altura de todos
    os nós abaixo desse. 
    
    ** Comentarios:
        O(logn + n') -> ERRADO, mas não sei como faz certo. kkkk :(
        
        Espera-se que a quantidade de chamadas da função RecalculaAltura() seja < log n, porém 
        não sei como conluir algo em relação a complexidade dessa parte da função.
    
*/
int InsereAVL(Tnode** N, void *aInserir, int key){
    if((*N)==NULL){
        (*N) = (Tnode*) malloc(sizeof(Tnode));
        (*N)->inf = aInserir;
        (*N)->left = NULL;
        (*N)->right = NULL;
        (*N)->key = key;
        (*N)->height=0;
        return 1;
    }
    else{
        if(key > (*N)->key ){
            InsereAVL(&(*N)->right, aInserir ,key);
        }
        else{
            InsereAVL(&(*N)->left, aInserir, key);
        }
        if(Repara(&(*N))){
            RecalculaAltura(&(*N));
        }
        (*N)->height=Altura((*N));
        return 0;
    }
}

    /* Funções de Print */
/*  Método Pre-Order:
    -> É feito determinado processo no nó; 
    -> Chama-se recursivamente a função pro seu filho a esquerda;
    -> Chama-se recursivamente a função pro seu filho a direita;
    Usado para conferir formato da árvore,
    elementos são printados mostrando quem são seus filhos.
     Ex:    A
           / \
          B   C
         / \ / \
        D  E F  G
    Ordem: A B D E C F G
*/
void printPreOrder(Tnode *N){

    if(N==NULL){
        return ;
    }
    printf("%d ",N->key);
    if(N->left != NULL){
        printf("Filho da esquerda: %d ||", N->left->key);
    }
    if(N->right != NULL){
        printf("Filho da Direita: %d", N->right->key);
    }

    printf("\n");
    printPreOrder(N->left);
    printPreOrder(N->right);
}

/*  Método In-Order:
    -> Chama-se recursivamente a função pro seu filho a esquerda;
    -> É feito determinado processo no nó; 
    -> Chama-se recursivamente a função pro seu filho a direita;
    Elementos são printados em ordem crescente
*/
void printInOrder(Tnode *N){

    if(N==NULL){
        return ;
    }
    printInOrder(N->left);
    printf("%d\n",N->key);
    printInOrder(N->right);
}

/* Método Pós-Order:
    -> Chama-se recursivamente a função pro seu filho a esquerda;
    -> Chama-se recursivamente a função pro seu filho a direita;    
    -> É feito determinado processo no nó;
    Passa por cada nivel de altura da arvore, começando do mais inferior e indo
    da equerda para a direita.
    Ex:     A
           / \
          B   C
         / \ / \
        D  E F  G
    Ordem: D E F G B C A;     
*/     
void printPosOrder(Tnode *N){

    if(N==NULL){
        return ;
    }
    printPosOrder(N->left);
    printPosOrder(N->right);
    printf("%d\n",N->key);    
}

/*  Procura por determinada "key" na árvore AVL:
    - Verifica se o elemento já foi encontrado;
    - Caso sim: retorna-o;
    - Caso não: Chama recursivamente a função:
        -Para seu filho a esquerda, caso a "key" seja menor do que a informação do nó;
        -Para seu filho a direita, caso a "key" seja maior do que a informação do nó;
    Em caso ne não encontrar a key, ou seja, quando chegar em uma folha inexistente, retorna "NULL"
*/
void* ProcuraAVL(Tnode *N, int aProcurar){
    if(N == NULL){
        return NULL;
    }
    if(aProcurar > N->key){
        return ProcuraAVL(N->right, aProcurar);
    }
    if(aProcurar < N->key){
        return ProcuraAVL(N->left, aProcurar);
    }
    return N->inf;
}
int o =0;
/* Retorna o i-esimo elemento ordenaro na arvore;
*/
void VoltaIAVL(Tnode* N, int *iesimo, void** toReturn){
    o++;
    printf("%d\n", o);
    if(N==NULL || *iesimo <= 0){
        return ;
    }
    VoltaIAVL(N->left, iesimo, toReturn);
    if(*iesimo <= 0)return;
    *iesimo-=1;
    (*toReturn) = N->inf;
    VoltaIAVL(N->right, iesimo, toReturn);
}
/*  Liberação dos dados alocados pela árvore.
    As estruturas que nela estão armazenadas também são
    liberadas.
    Utiliza-se do metodo Pós-Order.
*/
void FreeArvore(Tnode **N){
    if((*N) == NULL){
        return;
    }
    FreeArvore(&(*N)->left);
    FreeArvore(&(*N)->right);
    free((*N)->inf);
    free((*N));
}

void EsvaziaArvore(Tnode **N){
    if((*N) == NULL){
        return;
    }
    FreeArvore(&(*N)->left);
    FreeArvore(&(*N)->right);
    free((*N));
}