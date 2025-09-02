#include <string.h>
#ifdef __unix__

#ifndef _LINMKDIR_H_
#define _LINMKDIR_H_

#include "base.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int dir_make(const char *restrict name) {
  int len = strlen(name);
  char _path[len + 1];
  strcpy(_path, name);
  if (!strcmp(&_path[len - 1], "/")) {
    memmove(&_path[len - 1], &_path[len + 1], len - 1);
  }

  return mkdir(name, 0755);
}

char *dir_getcurrent() {
  char *_current_dir = getcwd(NULL, 0);
  if (!_current_dir)
    return "noone";
  return _current_dir;
}

int dir_del(const char *restrict name) { return rmdir(name); }

int dir_move(const char *restrict name, const char *restrict path) {
  return rename(name, path);
}

int dir_exists(const char *restrict name) {
  struct stat info;
  if (stat(name, &info) != 0)
    return 0;
  return 1;
}

#endif

#endif
