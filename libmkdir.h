#ifndef _LIBMKDIR_H_
#define _LIBMKDIR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _cplusplus
extern "C" {
#endif

int dirmk(const char *name);
int dirrm(const char *name);
int dirisemp(const char *name);
char *dirgetcur(void);
int dirsetcur(const char *name);
int direxists(const char *name);
int dirmv(const char *name, const char *path);

static int _havebar(const char *path) {
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

/* ------------------------ UNIX --------------------- */

#ifdef __unix__

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#define PERMIS_DEF 0755

static int dir_recdel(const char *name) {

  /* first, check if the name is null or have any string */

  if (strlen(name) <= 0)
    return -4;

  /* first check if the dir is empty before start the recurs */
  if (!direxists(name))
    return -1;
  if (dirisemp(name)) {
    return rmdir(name);
  }

  /* starting the entry */
  struct dirent *entry;
  struct stat st;

  /* starting dir pointer and openning curr dir */
  DIR *dir = opendir(name);

  if (!dir)
    return -7;

  while ((entry = readdir(dir)) != NULL) {
    /* checks if the current entry is not the current dir or other*/
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      /* creates the charbuff fullpath (vla), that will used to all the
       * recursive operations */
      char *fullpath = malloc(strlen(name) + strlen(entry->d_name) + 2);
      if (!fullpath) {
        closedir(dir);
        return -3;
      }
      /* create string in fullpath */
      snprintf(fullpath, (strlen(name) + strlen(entry->d_name) + 2), "%s/%s",
               name, entry->d_name);
      if (stat(fullpath, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
          /* calls itself to change path */
          dir_recdel(fullpath);
          /* delete dir*/
          rmdir(fullpath);
        } else {
          return remove(fullpath);
        }
      }
      free(fullpath);
    }
  }
  closedir(dir);
  return dirrm(name);
}

static int dir_recmake(const char *name) {
  /* default validations */
  if (!name)
    return -1;
  if (strlen(name) <= 0)
    return -1;

  /* creates pointer _name to use buffer*/
  char *_name = strdup(name);

  /* pointer to traverse string */
  char *per = NULL;
  /* assigning the pointer to point to _name */
  per = _name;
  /* if the first index is '/', it increments one per node, otherwise, it just
   * assigns itself. */
  per = (_name[0] == '/') ? per + 1 : per;

  /* until per is not null, increment it. */

  for (; *per; per++) {
    if (*per == '/') {
      /* temporarily stop the route */
      *per = 0;
      if (mkdir(_name, PERMIS_DEF) && errno != EEXIST) {
        free(_name);
        return -1;
      }
      /* continue the route */
      *per = '/';
    }
  }
  if (mkdir(_name, PERMIS_DEF) && errno != EEXIST) {
    free(_name);
    return -1;
  }
  free(_name);
  return 0;
}

int dirmk(const char *name) {
  if (_havebar(name)) {
    return dir_recmake(name);
  }
  return (mkdir(name, PERMIS_DEF));
}

int dirrm(const char *name) {
  if (_havebar(name)) {
    return dir_recdel(name);
  }
  return rmdir(name);
}

char *dirgetcur(void) {
  char *_current_dir = getcwd(NULL, 0);
  if (!_current_dir)
    return "noone";
  return _current_dir;
}

int dirsetcur(const char *name) { return chdir(name); }

int dirmv(const char *name, const char *path) { return rename(name, path); }

int direxists(const char *name) {
  struct stat exists;
  if (stat(name, &exists) != 0)
    return 0;
  return 1;
}

int dirisemp(const char *name) {
  struct dirent *dr;
  DIR *curdir = opendir(name);
  while ((dr = readdir(curdir)) != NULL) {
    if (strcmp(dr->d_name, ".") != 0 && strcmp(dr->d_name, "..") != 0)
      return 0;
  }
  closedir(curdir);
  return 1;
}

#endif // UNIX -----

/* ----------------------- WINDOWS ------------------------------ */

#ifdef _WIN32

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

#ifdef _cplusplus
}
#endif

#endif
