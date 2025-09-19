#include "libmkdir.h"
#include <stdio.h>

int main() {
  if(!dirmk("lib////lib"))
  {
      printf("created lib //// lib!");
    return 0;
  }
  if(!dirmk(".."))
  {
    printf("dir maked!");
  }
  printf("not created!");
}
