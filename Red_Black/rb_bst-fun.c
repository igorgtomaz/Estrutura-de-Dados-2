#include "rb_bst.h"

struct no
{
    int chave, cor;
    struct no *esq, *dir, *p;
};

node *raiz;

//Cria a sentinela para o qual será apontado
node * inicia_arvore ()
{

    node *sentinela = (node*)malloc(sizeof(node));

    sentinela->p = NULL;
    sentinela->esq = NULL;
    sentinela->dir = NULL;
    sentinela->cor = PRETO;
    sentinela->chave = -99999;

    return sentinela;
}

node *bst_min (node *raiz, node *n)
{
    node *aux = n;

    while (aux->esq != raiz)
        aux = aux->esq;

    return aux;
}

node *busca_nodo(node *raiz, int valor)
{
	node *aux = raiz->dir;

	while (aux != raiz && valor !=  aux->chave)
	{
		if (valor < aux->chave)
			aux = aux->esq;
		else
			aux = aux->dir;
	}

	return aux;
}

int busca_valor(node *raiz, int valor)
{

  if (raiz->dir == NULL)
    return 0;

	node *aux = raiz->dir;

	while (aux != raiz && valor !=  aux->chave)
	{
		if (valor < aux->chave)
			aux = aux->esq;
		else
			aux = aux->dir;
	}

	if (aux != raiz)
    return 1;
  else
    return 0;
}

node *sucessor(node *raiz, node *x)
{
	if (x->dir != raiz)
		return bst_min(raiz, x->dir);

	node *y = x->p;

	while (y != raiz && x == y->dir)
	{
		x = y;
		y = y->p;
	}

	return y;
}

// Rotação à esquerda
void leftRotate (node *n, node *no)
{
    node *y = (node*)malloc(sizeof(node));

    y = no->dir;
    no->dir = y->esq;

    if (y->esq != n)
    {
        y->esq->p = no;
    }

    y->p = no->p;

    if (no->p == n)
    {
        no->p->dir = y;
    }
    else
    {
        if(no == no->p->esq)
        {
            no->p->esq = y;
        }
        else
        {
            no->p->dir = y;
        }
    }
    y->esq = no;
    no->p = y;
}

// Rotação à direita
void rightRotate (node *n, node *no)
{
    node *y = (node*)malloc(sizeof(node));

    y = no->esq;

    no->esq = y->dir;

    if (y->dir != n)
    {
        y->dir->p = no;
    }

    y->p = no->p;

    if (no->p == n)
    {
        no->p->dir=y;
    }
    else
    {
        if (no == no->p->esq)
        {
            no->p->esq = y;
        }
        else
        {
            no->p->dir = y;
        }
    }

    y->dir = no;
    no->p = y;
}

void balancear (node *n, node *no)
{
    node *pai = no->p, *tio, *avo;

    while (pai->cor == VERMELHO)
    {
        avo = pai->p;

        // Esquerda do avô
        if (no->chave < avo->chave)
        {
            tio = avo->dir;

            // Caso PRETO
            if (tio->cor == VERMELHO)
            {
                pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
                pai = no->p;
            }
            else
            {
                // Caso 2
                if (no == pai->dir)
                {
                    leftRotate (n, pai);
                    no = pai;
                    pai = no->p;
                }

                // Caso 3
                pai->cor = PRETO;
                avo->cor = VERMELHO;
                rightRotate (n, avo);
            }
            // Direita do avô
        }
        else
        {
            tio=avo->esq;

            // Caso PRETO
            if (tio->cor == VERMELHO)
            {
                pai->cor = PRETO;
                tio->cor = PRETO;
                avo->cor = VERMELHO;
                no = avo;
                pai = no->p;
            }
            else
            {
                // Caso 2
                if(no == pai->esq)
                {
                    rightRotate(n, pai);
                    no = pai;
                    pai = no->p;
                }

                // Caso 3
                pai->cor = PRETO;
                avo->cor = VERMELHO;
                leftRotate(n,avo);
            }
        }
    }

    // Raiz preta
    n->dir->cor = PRETO;
}

node *new_nodo(node *p, int valor)
{
    node *n = (node*) malloc(sizeof(node));

    n->chave = valor;
    n->esq = p;
    n->dir = p;
    n->p = NULL;
    n->cor = VERMELHO;

    return n;
}

void balancear_remocao(node *raiz, node *n)
{
    node *aux;
    while(n != raiz && n->cor == PRETO)
    {
        if(n->chave < n->p->chave)
        {
            aux = n->p->dir;
            if(aux->cor == VERMELHO)
            {
                // Caso PRETO
                aux->cor=PRETO;
                n->p->cor=VERMELHO;
                leftRotate(raiz,n->p);
                aux=n->p->dir;
            }
            if(aux->esq->cor == PRETO && aux->dir->cor == PRETO)
            {
                // Caso 2
                aux->cor=VERMELHO;
                n=n->p;
            }
            else
            {
                if(aux->dir->cor == PRETO)
                {
                    // Caso 3
                    aux->esq->cor=PRETO;
                    aux->cor=VERMELHO;
                    rightRotate(raiz,aux);
                    aux=n->p->dir;
                }
                // Caso 4
                aux->cor=n->p->cor;
                n->p->cor=PRETO;
                aux->dir->cor=PRETO;
                leftRotate(raiz,n->p);
                n=raiz;
            }
        }
        else if (n->chave > n->p->chave)
        {
            aux = n->p->esq;
            if(aux->cor == VERMELHO)
            {
                // Caso PRETO
                aux->cor=PRETO;
                n->p->cor=VERMELHO;
                rightRotate(raiz,n->p);
                aux=n->p->esq;
            }
            if(aux->dir->cor == PRETO && aux->esq->cor == PRETO)
            {
                // Caso 2
                aux->cor=VERMELHO;
                n=n->p;
            }
            else
            {
                if(aux->esq->cor == PRETO)
                {
                    // Caso 3
                    aux->dir->cor=PRETO;
                    aux->cor=VERMELHO;
                    leftRotate(raiz,aux);
                    aux=n->p->esq;
                }
                // Caso 4
                aux->cor=n->p->cor;
                n->p->cor=PRETO;
                aux->esq->cor=PRETO;
                rightRotate(raiz,n->p);
                n=raiz;
            }
        }
    }
    n->cor=PRETO;
}



void inorder(node *p, node *n)
{
    if (n != p)
    {
        inorder(p, n->esq);
        printf("\nChave = %d - ", n->chave);
        if (n->cor == PRETO)
            printf("Cor = PRETO");
        else
            printf("Cor = VERMELHO");
        inorder(p, n->dir);
    }
}

void insere_nodo(node *n, int valor)
{
    node *new, *aux, *aux2;

    //Criando novo nodo
    new = new_nodo(n, valor);

    //Arvore vazia
    if(n->dir == NULL)
    {
        n->dir = new;
        new->p = n;

        //Balanceia com o novo nodo
        balancear(n, new);
        return;
    }

    aux = n->dir;

    //Busca a posição correta para inserir o nodo
    while (aux != n)
    {
        aux2 = aux;

        if (valor < aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }

    /*
       Se for menor, insere a esquerda
       Se for maior, insere a direita
    */
    if (valor < aux2->chave)
        aux2->esq = new;
    else
        aux2->dir = new;

    //Aponta o novo pai
    new->p = aux2;

    //Faz o novo balanceamento
    balancear(n, new);
}

node *deleta_nodo(node *raiz, node *z)
{
	if (!z)
		return NULL;

	node *y, *x;

	if (z->esq == raiz || z->dir == raiz)
		y = z;
	else
		y = sucessor(raiz, z);

	if (y->esq != raiz)
		x = y->esq;
	else
		x = y->dir;

	x->p = y->p;

	if (y->p == raiz)
		raiz = x;
	else if (y == y->p->esq)
		y->p->esq = x;
	else
		y->p->dir = x;

	if (y != z)
		z->chave = y->chave;

	if (y->cor == PRETO)
		balancear_remocao(raiz, x);

	return y;
}
