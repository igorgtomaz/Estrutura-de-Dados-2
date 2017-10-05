#include <time.h>
#include "rb_bst.h"

int menu(node *p)
{
  srand(time(NULL));
  int i, menu, escolha, valor, cor_temp;
  raiz = p;
  node *aux;

  printf("\nO que deseja fazer?\n\n1 - Inserir valores\n2 - Deletar valores\n");
  printf("3 - Printar a Árvore\n4 - Buscar um nodo\n5 - Encerrar programa\nResposta: ");
  scanf("%i", &menu);

  switch (menu) {
    case 1:
      printf("\nQuantos valores deseja adicionar?\nResposta: ");
      scanf("%i", &escolha);

      printf("\nValores inseridos: ");
      for(i = 0; i < escolha;)
      {
        valor = (rand() % 100);

        if (busca_valor(raiz, valor) == 0 && valor > 0)
          {
            printf("%d", valor);
            if (i != (escolha-1))
              printf(" - ");

            insere_nodo(p, valor);
            i++;
          }

      }
      printf("\n");
      return 0;
    break;
    case 2:
      printf("\nDigite o número que deseja excluir: ");
      scanf("%i", &valor);

      aux = busca_nodo(raiz, valor);

      cor_temp = aux->cor;

      deleta_nodo(raiz, aux);

      printf("\nNodo deletado:\nChave = %i\n", valor);
      if (cor_temp == VERMELHO)
        printf("Cor = Vermelho\n");
      else
        printf("Cor = Preto\n");

        return 0;
      break;
      case 3:
          printf("\n------------------");
          printf("\nÁrvore Red Black\n");
          inorder(p, p->dir);
          printf("\n------------------\n");
          return 0;
      break;
      case 4:
        printf("\nDigite o valor que deseja buscar: ");
        scanf("%i", &valor);

        aux = busca_nodo(raiz, valor);

        if (aux != p)
        {
          printf("\nNodo encontrado:\nChave = %i\n", aux->chave);
          if (aux->cor == VERMELHO)
            printf("Cor = Vermelho\n");
          else
            printf("Cor = Preto\n");
        }
        else
        {
            printf("\nNodo não encontrado.\n");
        }

        return 0;
        break;
        case 5:
          printf("\nPrograma encerrado.\n");
            return 1;
        break;
        default:
          printf("Opção inválida, favor digitar uma opção válida.\n");
          return 0;
        break;

        return 0;
  }
}
