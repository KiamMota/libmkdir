#include "internal/base.h"
#include "libmkdir.h"
#include <stdio.h>

void create() {
  dir_make("myfamily");
  if (!dir_recmake("myfamily/mywife"))
    printf("created sub1\n");
  if (!dir_recmake("myfamily/myson"))
    printf("created sub2\n");
}

void create_files() {
  FILE *f = fopen("myfamily/mywife/marriage.txt", "w");
  if (!f) {
    printf("cannot create file.");
    return;
  }
  printf("created file\n");
  fprintf(f, "%s", "i love you so much!");
  fclose(f);
}

int main() {
  printf("testing with empty directory > rm_rec_empty\n");
  dir_make("rm_rec_empty");
  if (!dir_recdel("rm_rec_empty")) {
    printf("deleted!\n");
  }
  printf("trying with dir with subs\n");
  dir_recmake("rm_rec_oth/other");
  if (!dir_recdel("rm_rec_oth")) {
    printf("deleted!\n");
    return 0;
  }
  printf("not deleted!\n");
}
