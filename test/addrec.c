#include "libmkdir.h"

int main() {
  if (!dirmk("libmkdir2/src")) {
    printf("created!\n");
    return -1;
  }
  printf("not created.\n");
}
