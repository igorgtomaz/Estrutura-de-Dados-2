#include "bst.h"

struct no {
    int key;
    node *left, *right;
};

typedef struct no node;

// Busca
node *search (node *n, int key)
{
    if (!n || n->key == key)
       return n;

    if (key <= n->key)
        return search (n->left, key);
    else
        return search (n->right, key);
}

// Insere
node *insere(node *n, int key)
{
    node *p = (node *)malloc(sizeof(node));

    //Verica se o p foi criado corretamepte
    if (!p)
      return NULL;

    p->left = p->right = NULL;
    p->key = key;

    //Se a arvore está vazia, retorna p
    if (!n)
        return p;

    node *aux = n;

    //Percorre a arvore
    while(1)
    {
        /*
          Se o valor a ser inserido é menor que o valor da esquerda
          insere na esquerda, se maior, insere na direauxa.
        */
        if (key < aux->key)
        {
            if (!aux->left)
            {
                aux->left = p;
                break;
            }
            aux = aux->left;
        } else
        {
            if (!aux->right)
            {
                aux->right = p;
                break;
            }
            aux = aux->right;
        }
    }

    return n;
}

// Printar

// In-order: Começa pelo mais a esquerda volta pra raiz e pega o da direita.
void inorder(node *n)
{
    if(n != NULL)
    {
        inorder(n->left);
        printf("%d\n", n->key);
        inorder(n->right);
    }
}

 /*
  Pre-order: Começa pela raiz e vai pegando os mais a esquerda,
  depois vai retornando a raiz e pegando a direita.
*/
void preorder(node *n)
{
    if(n != NULL)
    {
        printf("%d\n", n->key);
        preorder(n->left);
        preorder(n->right);
    }
}

// Pos-order: Pega primeiro a esquerda, depois a direita e então a raiz.
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
node *deleta(node* n, int valor)
{
  int teste = 0;

    // Procura onde está o valor
    if (!n)
        return NULL;
    else if (n->key < valor)
        n->left = deleta(n->left, valor);
    else if (n->key > valor)
        n->right = deleta(n->right, valor);
    else
    {
      // Encontra o valor a ser excluído
      teste = 1;

        // Raiz sem filhos
        if (n->left == NULL && n->right == NULL)
        {
            free (n);
            n = NULL;
        }
        // Sem filho à esquerda
        else if (n->left == NULL)
        {
            node* t = n;
            n = n->right;
            free (t);
        }
        // Sem filho à direita
        else if (n->right == NULL)
        {
            node* p = n;
            n = n->left;
            free (p);
        }
        // Possuí subárvore na esquerda e na direita
        else
        {
            node* f = n->left;
            /*
              Pega o valor mais a direita da subárvore da esquerda.
            */
            while (f->right != NULL)
            {
                f = f->right;
            }
            n->key = f->key;
            f->key = valor;
            n->left = deleta(n->left,valor);
        }
    }

    if (teste == 1)
      printf("\nValor deletado.\n");
    else
      printf("\nValor não encontrado.\n");

    return n;
}

//Menu exibido na tela
void menu(node *n)
{
  int qtd_num = 0, i, num = 0, menu = 1, menu2 = 0;

  printf("**Bem vindo à Árvore Binária\n");

  while(menu != 0)
  {
    printf("\nO que deseja fazer?\n\n1 - Inserir valores\n2 - Printar a Árvore\n3 - Remover valores\n0 - Sair\n");
    printf("Resposta: ");
    scanf("%i", &menu);

    switch(menu)
    {
      case 1:
        printf("\nDigite quantos números deseja inserir: ");
        scanf("%i", &qtd_num);
        printf("\n");

        for (i = 0; i < qtd_num; i++)
        {
          printf("Digite o valor %i: ", (i+1));
          scanf("%i", &num);
          n = insere(n, num);
        }
        printf("\nNúmeros inseridos.\n");

        break;
      case 2:
        while (1)
        {
          printf("\nQual dos modelos deseja seguir?\n1 - Inorder\n2 - Preorder\n3 - Posorder\nResposta: ");
          scanf("%i", &menu2);
          printf("\n");

          switch(menu2)
          {
            case 1:
              printf("Árvore Binária em Inorder:\n");
              inorder(n);
              printf("\n");
              break;
            case 2:
              printf("Árvore Binária em Preorder:\n");
              preorder(n);
              printf("\n");
              break;
            case 3:
              printf("Árvore Binária em Posorder:\n");
              posorder(n);
              printf("\n");
              break;
            default:
              printf("Opção inválida, favor digitar uma opção de 1 a 3.\n");
              break;
          }

          if (menu2 >= 1 && menu2 <= 3)
          {
            printf("Árvore Binária exibida.\n");
            break;
          }
        }
        break;
      case 3:
        printf("\nDigite o número que deseja remover: ");
        scanf("%i", &num);

        n = deleta(n, num);

        break;
      default:
        printf("Opção inválida, favor digitar uma opção de 1 a 3.\n");
        break;
    }
  }
}
