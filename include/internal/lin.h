#ifdef __linux__

#ifndef _LINMKDIR_H_
#define _LINMKDIR_H_

#include "base.h"
#include <sys/syscall.h>
#include <unistd.h>

int dir_make(const char *restrict name) {
  if (!name)
    return -92;
  return syscall(SYS_mkdir, name, 0755);
}

int dir_del(const char *restrict name) {
  if (!name)
    return -92;
  return syscall(SYS_rmdir, name);
}

int dir_move(const char *restrict name, const char *restrict path) {
  if (!name)
    return -92;
  return syscall(SYS_rename, name, path);
}

#endif

#endif
