#include "libmkdir.h"

int main() {
  if (!dirmk("torm/src")) {
    printf("created dir\n");
  } else
    printf("not created dir\n");

  if (!dirrm("torm/src")) {
    printf("DELETED!\n");
    return 0;
  }
  printf("not deleted\n");
  return -1;
}
