typedef struct no node;
typedef struct tree rb_bst;
#define PRETO 1
#define VERMELHO 0

node *inicia_arvore();
node *bst_min (node *raiz, node *n);
node *busca_nodo(node *raiz, int valor);
int busca_valor(node *raiz, int valor);
node *sucessor(node *raiz, node *x);
void leftRotate (node *n, node *no);
void rightRotate (node *n, node *no);
void balancear (node *n, node *no);
node *new_nodo(node *p, int valor);
void balancear_remocao(node *raiz, node *n);
void inorder(node *p, node *n);
void insere_nodo(node *n, int valor);
node *deleta_nodo(node *raiz, node *z);
int menu(node *p);
