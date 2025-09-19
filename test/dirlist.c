#include "libmkdir.h"
#include <stdio.h>

int main()
{
  printf("diretorios em / : %d\n", dirlistcount("/"));
  printf("dir in ~: %d \n", dirlistcount("~"));
}
