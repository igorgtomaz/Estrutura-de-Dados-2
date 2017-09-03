#include "bst.h"

struct no {
    int key;
    node *left, *right;
};

typedef struct no node;

// Busca
node *search (node *r, int key)
{
    if (!r || r->key == key)
       return r;

    if (key <= r->key)
        return search (r->left, key);
    else
        return search (r->right, key);
}

// Insere
node *insere(node *r, int key)
{
    node *n = (node *)malloc(sizeof(node));

    if (!n)
        return NULL;

    n->left = n->right = NULL;
    n->key = key;

    if (!r)
        return n;

    node *it = r;

    while(1)
    {
        if (key < it->key)
        {
            if (!it->left)
            {
                it->left = n;
                break;
            }
            it = it->left;
        } else
        {
            if (!it->right)
            {
                it->right = n;
                break;
            }
            it = it->right;
        }
    }

    return r;
}

// Printar
void inorder(node *n)
{
    if(n != NULL)
    {
        inorder(n->left);
        printf("%d\n", n->key);
        inorder(n->right);
    }
}

void preorder(node *n)
{
    if(n != NULL)
    {
        printf("%d\n", n->key);
        preorder(n->left);
        preorder(n->right);
    }
}

void posorder(node *n)
{
    if(n != NULL)
    {
        posorder(n->left);
        posorder(n->right);
        printf("%d\n", n->key);
    }
}

// Deleta
int deleta(node *n, int valor)
{
  if (!n)
    return 0;

  node *ant = NULL;
  node *atual = n;

  while(atual)
  {
      if(valor == atual->key)
      {
        if(atual == *n)
          *n = reposiciona(atual);
        else
        {
          if(ant->right = atual)
            ant->right = reposiciona(atual);
          else
            ant->left = reposiciona(atual);
        }
        return 1;
      }
      ant = atual;

      if(valor > atual->key)
        atual = atual->right;
      else
        atual = atual->left;
  }

}

node *reposiciona(node *atual)
{

}
