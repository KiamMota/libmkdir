#include "libmkdir.h"

int main() {
  if (!dir_recdel("myproject")) {
    printf("deleted myproject");
  }
  if (!dir_recmake("myproject/src")) {
    printf("created!");
  }
}
