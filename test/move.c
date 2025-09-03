#include "internal/base.h"
#include "libmkdir.h"

void create_son() {
  if (!dir_recdel("son")) {
    printf("deleted son.\n");
  }
  if (!dir_recmake("son/toys")) {
    printf("recursevly make son/toys.\n");
  }

  FILE *f = fopen("son/text.c", "w");
  fprintf(f, "%s", "hello, dear!");
  if (!f) {
    printf("error while creating file.\n");
    return;
  }
  printf("created file text.c in son/\n.");
}

void create_dad() {
  dir_recdel("dad");
  dir_make("dad");
}

int main() {
  create_dad();
  create_son();
  if (!dir_move("son", "dad")) {
    printf("moved path.\n");
    return 0;
  }
  printf("failed while moving.\n");
}
