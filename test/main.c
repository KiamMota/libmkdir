#include "internal/base.h"
#include "libmkdir.h"
#include <stdio.h>

#define _NAME "mydir"

int main() {
  if (!dir_exists(_NAME)) {
    if (!dir_make(_NAME)) {
      printf("folder created.\n");
    }
  }
  if (dir_exists(_NAME)) {
    printf("deleting dir...\n");
    if (!dir_del(_NAME))
      printf("deleted dir.\n");
    else {
      printf("houve algum erro ao deletar.\n");
    }
  }
}
