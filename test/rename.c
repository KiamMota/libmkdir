#include "internal/base.h"
#include "libmkdir.h"
#include <stdio.h>

int main() {
  if (!dir_exists("mydir")) {
    printf("dir not found!");
    dir_make("mydir");
  }
  dir_move("mydir", "mydirrenamed");
  printf("renamed!");
}
