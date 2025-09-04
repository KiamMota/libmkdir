#include "internal/base.h"
#include "libmkdir.h"

int main() {
  if (!dirmk("projectson")) {
    printf("static dir is created!\n");
  }
}
