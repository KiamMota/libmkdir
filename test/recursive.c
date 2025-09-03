#include "internal/base.h"
#include "libmkdir.h"
#include <stdio.h>

int main() {
  if (dir_recmake("recursivee/src") != 0) {
    printf("Failed to create directory.\n");
  } else if (dir_exists("recursivee/src")) {
    printf("dir created.\n");
  }
}
