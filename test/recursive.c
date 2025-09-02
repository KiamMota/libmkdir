#include "internal/base.h"
#include "libmkdir.h"
#include <stdio.h>

int main() {
  printf("starting test with recursing...\n");
  dir_make("test/src");
  dir_make("test/include");
  if (dir_exists("test/src")) {
    printf("dir created.");
  }
}
