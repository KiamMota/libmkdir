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
    if (!dir_remove(_NAME))
      printf("deleted dir.\n");
  }
}
