#ifdef __unix__

#ifndef _LINMKDIR_H_
#define _LINMKDIR_H_

#include "base.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int dir_make(const char *restrict name) {
  if (!name)
    return -92;
  return mkdir(name, 0755);
}

int dir_del(const char *restrict name) { return rmdir(name); }

int dir_move(const char *restrict name, const char *restrict path) {
  return rename(name, path);
}

int dir_exists(const char *restrict name) {
  struct stat info;
  return stat(name, &info);
}

#endif

#endif
