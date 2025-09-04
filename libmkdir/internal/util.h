#ifndef _LIBMKDIR_UTIL_H_
#define _LIBMKDIR_UTIL_H_

#include "base.h"

static int havebar(const char *path) {
  const char *p = path;
  if (path[0] == '/' || path[0] == '\\')
    p++;
  for (; *p; p++) {
    if (*p == '/' || *p == '\\') {
      return 1;
    }
  }
  return 0;
}

#endif
