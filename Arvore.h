#ifndef ARVORE
#define ARVORE

typedef struct TreeNode{
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
    void* inf;
    int key;
}Tnode;


/* Métodos relacionados a árvore AVL */
int InsereAVL(Tnode** N, void *aInserir, int key);
void* ProcuraAVL(Tnode *N, int aProcurar);
void FreeArvore(Tnode **N);
void EsvaziaArvore(Tnode **N);

/* Formas diferentes de Print'ss */
void printInOrder(Tnode *N);
void printPosOrder(Tnode *N);
void printPreOrder(Tnode *N);
#endif