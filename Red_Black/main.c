#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rb_bst.h"
#include "rb_bst-fun.c"
#include "menu.c"

int main()
{
  int teste = 0;
  node *p = inicia_arvore();

  printf("Bem vindos a Red-Black-Tree!\n");

  while(teste == 0)
  {
    teste = menu(p);
  }

  return 0;
}
