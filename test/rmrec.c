#include "libmkdir.h"
#include <stdio.h>

void create() {
  dir_make("myfamily");
  if (!dir_recmake("myfamily/mywife"))
    printf("created sub1\n");
  if (!dir_recmake("mydear/myson"))
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
  create();
  create_files();
  printf("----- REMOVE RECURS --- \n");
  dir_recdel("mydear");
}
