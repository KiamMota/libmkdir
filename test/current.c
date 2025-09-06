#include "libmkdir.h"

int main() {
  char *current = dirgetcur();
  printf("working in %s\n", current);
  dirsetcur("..");
  printf("now working in %s\n", dirgetcur());
}
