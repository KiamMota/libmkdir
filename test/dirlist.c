#include "libmkdir.h"
#include <stdio.h>

int main()
{
  signed long it = 0;
  dircnt(dirgetcur(), &it, 0);
  printf("look just path > %ld\n", it);
  it = 0;
  dircntall(dirgetcur(), &it, 0);
  printf("look all > %ld\n", it);
}
