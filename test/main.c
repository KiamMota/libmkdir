#include "libmkdir.h"
#include <stdio.h>

#define _NAME "mydir"

int main() {
  if (!havedir(_NAME)) {
    if (!makedir(_NAME)) {
      printf("folder created.\n");
    }
  }
  if (havedir(_NAME)) {
    printf("deleting dir...\n");
    if (!removedir(_NAME))
      printf("deleted dir.\n");
  }
}
