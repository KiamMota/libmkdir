#ifndef _LIBMKDIR_H_
#define _LIBMKDIR_H_

#include <stdio.h>

#ifdef __unix__
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>
#endif

#ifdef _WIN32
#include <direct.h>
#include <windows.h>

#endif

static int makedir(const char *__restrict name) {
  if (!name)
    return -2;
#ifdef __unix__
  return mkdir(name, 0777);
#endif
#ifdef _WIN32
  return _mkdir(name);
#endif
}

static int removedir(const char *__restrict name) {
  if (!name)
    return -2;
#ifdef __unix__
  return rmdir(name);
#endif
#ifdef _WIN32
  return _rmdir(name);
#endif
}

static int havedir(const char *__restrict name) {
#ifdef __unix__
  struct stat st;
  if (stat(name, &st) == 0 && S_ISDIR(st.st_mode)) {
    return 1;
  }
#endif
#ifdef _WIN32

  DWORD attr = GetFileAttributesA(name);
  if (attr != INVALID_FILE_ATTRIBUTES) {
    return 1;
  }
  return 0;
#endif
  return 0;
}

static int renamedir(const char *__restrict old_name,
                     const char *__restrict new_name) {
  if (!old_name || !new_name)
    return -2;
#ifdef __linux__
  return syscall(SYS_rename, old_name, new_name);
#endif
#ifdef __WIN32
  return rename(old_name, new_name);
#endif
#ifdef __unix__
  return rename(old_name, new_name);

#endif
}

#endif
