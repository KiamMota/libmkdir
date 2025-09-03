#include "libmkdir.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEPTH 1000 // número de diretórios aninhados

int main() {
  clock_t start = clock();

  char path[4096] = {0};
  snprintf(path, sizeof(path), "benchmark_dir");

  // Cria o diretório base
  if (dir_make(path) != 0) {
    printf("[ERROR] Failed to create base directory.\n");
    return 1;
  }

  // Criação de diretórios aninhados
  for (int i = 1; i <= DEPTH; i++) {
    char next[4096];
    snprintf(next, sizeof(next), "%s/dir_%d", path, i);
    if (dir_make(next) != 0) {
      printf("[ERROR] Failed at %s\n", next);
      return 1;
    }
  }

  clock_t mid = clock();
  double creation_time = (double)(mid - start) / CLOCKS_PER_SEC;
  printf("[INFO] Created %d nested directories in %.6f seconds\n", DEPTH,
         creation_time);

  // Verificação de existência
  for (int i = 1; i <= DEPTH; i++) {
    char check[4096];
    snprintf(check, sizeof(check), "%s/dir_%d", path, i);
    if (!dir_exists(check)) {
      printf("[ERROR] Directory missing: %s\n", check);
    }
  }

  clock_t check_time = clock();
  double verification_time = (double)(check_time - mid) / CLOCKS_PER_SEC;
  printf("[INFO] Verification done in %.6f seconds\n", verification_time);

  // Remoção de diretórios de forma inversa (filho -> pai)
  for (int i = DEPTH; i >= 1; i--) {
    char del[4096];
    snprintf(del, sizeof(remove), "%s/dir_%d", path, i);
    if (dir_del(del) != 0) {
      printf("[WARN] Failed to del %s\n", remove);
    }
  }

  if (dir_del(path) != 0) {
    printf("[WARN] Failed to del base directory %s\n", path);
  }

  clock_t end = clock();
  double removal_time = (double)(end - check_time) / CLOCKS_PER_SEC;
  double total_time = (double)(end - start) / CLOCKS_PER_SEC;

  printf("[INFO] Removal done in %.6f seconds\n", removal_time);
  printf("[INFO] Total elapsed time: %.6f seconds\n", total_time);

  return 0;
}
