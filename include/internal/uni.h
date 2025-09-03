#include <string.h>
#ifdef __unix__

#ifndef _LINMKDIR_H_
#define _LINMKDIR_H_

#include "base.h"
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include <errno.h>
int dir_make(const char *restrict name) {

  if (mkdir(name, 0755)) {
    if (errno == EEXIST)
      return 0;
    return -1;
  }
  return 0;
}

char *dir_getcurrent() {
  char *_current_dir = getcwd(NULL, 0);
  if (!_current_dir)
    return "noone";
  return _current_dir;
}

int dir_recmake(const char *name) {
  char path[1024];
  char *p;

  if (!name || !*name)
    return -1;

  strncpy(path, name, sizeof(path) - 1);
  path[sizeof(path) - 1] = '\0';

  for (p = path + 1; *p; p++) {
    if (*p == '/') {
      *p = '\0';
      if (mkdir(path, 0755) != 0 && errno != EEXIST) {
        perror(path);
        return -1;
      }
      *p = '/';
    }
  }

  if (mkdir(path, 0755) != 0 && errno != EEXIST) {
    perror(path);
    return -1;
  }

  return 0;
}

int dir_setcurrent(const char *restrict name) { return chdir(name); }

int dir_del(const char *restrict name) { return rmdir(name); }

int dir_recdel(const char *restrict name) {
  struct dirent *dr;
  DIR *dir = opendir(name);
  while ((dr = readdir(dir)) != NULL) {
    if (strcmp(dr->d_name, ".") != 0 && strcmp(dr->d_name, "..") != 0) {
      if (dr->d_type == DT_DIR) {
      }
    }
  }
}

int dir_move(const char *restrict name, const char *restrict path) {
  return rename(name, path);
}

int dir_exists(const char *restrict name) {
  struct stat info;
  if (stat(name, &info) != 0)
    return 0;
  return 1;
}

int dir_isempty(const char *restrict name) {
  struct dirent *dr;
  DIR *curdir = opendir(name);
  while ((dr = readdir(curdir)) != NULL) {
    if (strcmp(dr->d_name, ".") != 0 && strcmp(dr->d_name, "..") != 0)
      return 0;
  }
  return 1;
}

#endif

#endif
