#ifdef _WIN32

#ifndef _WINMKDIR_H_
#define _WINMKDIR_H_

#include "base.h"
#include <Windows.h>

int dirmk(const char *path) { return CreateDirectoryA(path, NULL) ? 0 : -1; }

static int dir_recmake(const char *__restrict path) {
  char tempPath[MAX_PATH];
  char *p = NULL;
  size_t len;

  snprintf(tempPath, sizeof(tempPath), "%s", path);
  len = strlen(tempPath);
  if (tempPath[len - 1] == '\\' || tempPath[len - 1] == '/') {
    tempPath[len - 1] = '\0';
  }

  for (p = tempPath + 1; *p; p++) {
    if (*p == '\\' || *p == '/') {
      *p = '\0';
      if (!dir_exists(tempPath)) {
        if (dir_make(tempPath) != 0) {
          return -1;
        }
      }
      *p = '\\';
    }
  }
  if (!dir_exists(tempPath)) {
    if (dir_make(tempPath) != 0) {
      return -1;
    }
  }
  return 0;
}

int dir_del(const char *__restrict path) {
  return RemoveDirectoryA(path) ? 0 : -1;
}

int dir_recdel(const char *__restrict path) {
  WIN32_FIND_DATAA ffd;
  HANDLE hFind;
  char searchPath[MAX_PATH];
  char itemPath[MAX_PATH];

  snprintf(searchPath, MAX_PATH, "%s\\*", path);

  hFind = FindFirstFileA(searchPath, &ffd);
  if (hFind == INVALID_HANDLE_VALUE) {
    return -1;
  }

  do {
    if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
      continue;

    snprintf(itemPath, MAX_PATH, "%s\\%s", path, ffd.cFileName);

    if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      if (dir_recdel(itemPath) != 0) {
        FindClose(hFind);
        return -1;
      }
    } else {
      if (!DeleteFileA(itemPath)) {
        FindClose(hFind);
        return -1;
      }
    }
  } while (FindNextFileA(hFind, &ffd));

  FindClose(hFind);

  return dir_del(path);
}

int dir_exists(const char *__restrict path) {
  DWORD dwAttrib = GetFileAttributesA(path);
  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
          (dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
             ? 1
             : 0;
}

int dir_isempty(const char *__restrict path) {
  WIN32_FIND_DATAA ffd;
  HANDLE hFind;
  char searchPath[MAX_PATH];

  snprintf(searchPath, MAX_PATH, "%s\\*", path);

  hFind = FindFirstFileA(searchPath, &ffd);
  if (hFind == INVALID_HANDLE_VALUE) {
    return -1;
  }

  int isEmpty = 1;
  do {
    if (strcmp(ffd.cFileName, ".") != 0 && strcmp(ffd.cFileName, "..") != 0) {
      isEmpty = 0;
      break;
    }
  } while (FindNextFileA(hFind, &ffd));

  FindClose(hFind);

  return isEmpty ? 0 : -1;
}

char *dir_getcurrent() {
  char *buffer = (char *)malloc(MAX_PATH);
  if (GetCurrentDirectoryA(MAX_PATH, buffer)) {
    return buffer;
  }
  free(buffer);
  return NULL;
}

int dir_setcurrent(const char *__restrict path) {
  return SetCurrentDirectoryA(path) ? 0 : -1;
}

int dir_move(const char *__restrict oldpath, const char *__restrict newpath) {
  return MoveFileA(oldpath, newpath) ? 0 : -1;
}

#endif

#endif
