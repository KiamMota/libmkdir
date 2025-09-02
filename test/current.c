#include "internal/base.h"
#include "libmkdir.h"
#include <stdio.h>
#include <string.h>

int main() {
  char *current = dir_getcurrent();
  printf("working in %s\n", current);
  dir_setcurrent("..");
  printf("now working in %s\n", dir_getcurrent());
}
