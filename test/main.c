#include "internal/base.h"
#include "libmkdir.h"
#include <stdio.h>
#include <time.h>

int main() {
  clock_t start = clock();

  // Imprime diretório atual
  char *current = dir_getcurrent();
  printf("Current directory: %s\n", current);

  // Cria um diretório
  if (dir_make("test_dir") == 0) {
    printf("Directory 'test_dir' created.\n");
  }

  // Verifica se existe
  if (dir_exists("test_dir")) {
    printf("'test_dir' exists.\n");
  }

  // Muda para o diretório criado
  if (dir_setcurrent("test_dir") == 0) {
    printf("Changed to 'test_dir'. Current: %s\n", dir_getcurrent());
  }

  // Volta para o diretório anterior
  dir_setcurrent("..");
  printf("Back to parent directory: %s\n", dir_getcurrent());

  // Renomeia/move o diretório
  if (dir_move("test_dir", "renamed_dir") == 0) {
    printf("'test_dir' renamed to 'renamed_dir'.\n");
  }

  // Remove o diretório
  if (dir_del("renamed_dir") == 0) {
    printf("'renamed_dir' removed.\n");
  }

  // Timestamp final
  clock_t end = clock();
  double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Total elapsed time: %.6f seconds\n", elapsed);

  return 0;
}
