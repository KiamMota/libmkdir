#include "libmkdir.h"
#include <stdio.h>

int main()
{
  signed long it = 0;
  dirlistcnt("/",&it, 0);
  printf("dirlist: %ld", it);
}
