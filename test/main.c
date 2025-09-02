#include "libmkdir.h"
#include <stdio.h>

#define BENCHMARK_NAME "mydir"

int main() {
  if (!havedir(BENCHMARK_NAME)) {
    if (!makedir(BENCHMARK_NAME, 0)) {
      printf("folder created.\n");
    }
  }
  if (havedir(BENCHMARK_NAME)) {
    printf("deleting dir...\n");
    if (!removedir(BENCHMARK_NAME))
      printf("deleted dir.\n");
  }
}
