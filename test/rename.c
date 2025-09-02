#include "libmkdir.h"
#include <stdio.h>

int main() {
  if (havedir("mydir")) {
    if (!rename("mydir", "mydir2")) {
      printf("renamed!\n");
    }
    return 0;
  }
  if (!havedir("mydir")) {
    if (!makedir("mydir")) {
      printf("dir created");
    }
    if (!rename("mydir", "mydir2"))
      ;
    printf("renamed!\n");
  }
}
