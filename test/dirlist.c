#include "libmkdir.h"
#include <stdio.h>

int main()
{
  signed long it = 0;
  dircnt("/",&it, 1);
  printf("dirlist: %ld", it);
}
