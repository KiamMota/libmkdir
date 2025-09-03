#include "libmkdir.h"
#include <stdio.h>
#include <time.h>

int main() {
  // Start timestamp
  clock_t start = clock();

  // 1. Get current working directory
  char *current = dir_getcurrent();
  printf("[INFO] Current directory: %s\n", current);

  // 2. Create a new directory
  if (dir_make("test_dir") == 0) {
    printf("[INFO] Directory 'test_dir' created.\n");
  } else {
    printf("[ERROR] Failed to create 'test_dir'.\n");
  }

  // 3. Check if directory exists
  if (dir_exists("test_dir")) {
    printf("[INFO] 'test_dir' exists.\n");
  } else {
    printf("[WARN] 'test_dir' does not exist.\n");
  }

  // 4. Change to the newly created directory
  if (dir_setcurrent("test_dir") == 0) {
    printf("[INFO] Changed to 'test_dir'. Current: %s\n", dir_getcurrent());
  } else {
    printf("[ERROR] Failed to change to 'test_dir'.\n");
  }

  // 5. Create nested directories recursively
  if (dir_recmake("nested/dir/structure") == 0) {
    printf(
        "[INFO] Nested directory structure 'nested/dir/structure' created.\n");
  } else {
    printf("[ERROR] Failed to create nested directories.\n");
  }

  // 6. Go back to parent directory
  if (dir_setcurrent("..") == 0) {
    printf("[INFO] Returned to parent directory: %s\n", dir_getcurrent());
  } else {
    printf("[ERROR] Failed to return to parent directory.\n");
  }

  // 7. Rename or move a directory
  if (dir_move("test_dir", "renamed_dir") == 0) {
    printf("[INFO] 'test_dir' renamed to 'renamed_dir'.\n");
  } else {
    printf("[ERROR] Failed to rename/move 'test_dir'.\n");
  }

  // 8. Remove directories
  if (dir_del("renamed_dir") == 0) {
    printf("[INFO] 'renamed_dir' removed.\n");
  } else {
    printf("[ERROR] Failed to remove 'renamed_dir'.\n");
  }

  if (dir_del("nested") == 0) {
    printf("[INFO] 'nested' directory removed.\n");
  } else {
    printf("[WARN] 'nested' not fully removed (non-empty or missing).\n");
  }

  // End timestamp and calculate elapsed time
  clock_t end = clock();
  double elapsed_seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("[INFO] Total elapsed time: %.6f seconds\n", elapsed_seconds);

  return 0;
}
