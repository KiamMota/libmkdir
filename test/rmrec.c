#include "internal/base.h"
#include "libmkdir.h"

int main() {
  dir_make("mydir");
  dir_recmake("mydir/other");
  dir_recmake("mydir/other2");
  if (dir_isempty("mydir")) {
    printf("dir is not empty!");
  }

  dir_recdel("mydir");
}
