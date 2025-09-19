#ifndef _LIBMKDIR_H_
#define _LIBMKDIR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _cplusplus
extern "C" {
#endif

typedef enum {
  DIR_OK,
  DIR_ERR_UNKNOWN = -7,
  DIR_ERR_NOCLASS,
  DIR_ERR_MEM,
  DIR_ERR_SYSMEM,
  DIR_ERR_INVAPARAM,
  DIR_ERR_PERM = -9,
  DIR_ERR_EXISTS,
  DIR_ERR_NOEXISTS,
  DIR_ERR_NOT_EXISTS,
  DIR_ERR_PATH,
  DIR_ERR_IO,
} LDIR;

/* creates directory recursive or not */
static int dirmk(const char *name);
/* removes a directory recursive or not */
static int dirrm(const char *name);
/* checks if dir is empty */
static int dirisemp(const char *name);
/* gets the current directory */
static char *dirgetcur(void);
/* sets the current directory */
static int dirsetcur(const char *name);
/* checks if dir exists */
static int direxists(const char *name);
/* rename or move directory */
static int dirmv(const char *name, const char *path);
/* counts directory */
static void dircnt(const char *path, signed long* count, short recursive);
/* counts the directory and all */
static void dircntall(const char* path, signed long* count, short recursive);

/* utils functions */

int _havebar(const char *path) {
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

int validate_param(const void *param) {
  if (!param)
    return DIR_ERR_INVAPARAM;
  if (strlen((char *)param) <= 0)
    return DIR_ERR_INVAPARAM;
  return DIR_OK;
}

/* ------------------------ UNIX --------------------- */

#ifdef __unix__

#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#define PERMIS_DEF 0755

/* util function to recursively delete directory */

int _dir_recdel(const char *name) {

  /* first, checks if the name is null or have any string */

  int res = validate_param(name);
  if (res != DIR_OK)
    return res;

  if (!direxists(name))
    return DIR_ERR_NOEXISTS;
  if (dirisemp(name)) {
    return rmdir(name);
  }

  /* pointer handle to the current directory */

  DIR *dir = opendir(name);
  
  if (!dir)
    return DIR_ERR_SYSMEM;
  
  /* starting the entry */
  struct dirent *entry;
  /* handle to get description about the block*/
  struct stat st;

  while ((entry = readdir(dir)) != NULL) {
    /* checks if the current entry is not the current dir or other*/
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      
      /* creates fullpath that represents the current directory to future recursive calls */
      char *fullpath = (char *)malloc(strlen(name) + strlen(entry->d_name) + 2);
      if (!fullpath) {
        closedir(dir);
        return DIR_ERR_MEM;
      }
      /* create string in fullpath */

      sprintf(fullpath, "%s/%s", name, entry->d_name);
      /* get the props of the current path */ 
      if (stat(fullpath, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
          /* calls itself to change path */
          _dir_recdel(fullpath);
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

void  _dir_listcnt_rec(const char* path, signed long* count)
{
  DIR* dirp;

  struct dirent* entry;
  struct stat st;

  dirp = opendir(path);
  if(!dirp) return;
  while((entry = readdir(dirp)) != NULL)
  {
    if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;


    char* fpath = (char*)malloc(strlen(path) + strlen(entry->d_name) + 2);
    if(!fpath) { closedir(dirp); return;}
    sprintf(fpath, "%s/%s", path, entry->d_name);
    if(stat(fpath, &st) == 0 && S_ISDIR(st.st_mode))
    {
        printf("dir -> %ld \n", *count);
        (*count) ++;
        _dir_listcnt_rec(fpath,&*count);
    }
    free(fpath);
  }
  closedir(dirp);
}

static void dircnt(const char *path, signed long* count, short recursive)
{
  DIR* dirp;
  struct dirent* entry;
  struct stat st;

  dirp = opendir(path);
  if(!dirp) return;
  if(!recursive)
  {
    while((entry = readdir(dirp)) != NULL)
    {
      if(strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name, "."))
        continue;
      char* fpath = (char*)malloc(strlen(path) + strlen(entry->d_name) + 2);
      sprintf(fpath, "%s/%s", fpath, entry->d_name);
      if(!stat(fpath, &st))
      {
        if(S_ISDIR(st.st_mode)) (*count)++;
      }
    }
    closedir(dirp);
    free(entry);
    return;
  }
  return _dir_listcnt_rec(path, count);
}

static void dircntall(const char *path, long *count, short recursive)
{
  /* handle pointer */
  DIR* dirp;
  struct dirent* entry;
  struct stat st;

  dirp = opendir(path);
  if(!dirp) return;
  if(!recursive)
  {
    while((entry = readdir(dirp)) != NULL)
    {
      (*count)++;
    }
    return;
  }


}


int dir_recmake(const char *name) {
  /* default validations */
  int ret = validate_param(name);
  if (ret != DIR_OK)
    return ret;

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
    return DIR_ERR_IO;
  }
  free(_name);
  return DIR_OK;
}

static int dirmk(const char *name) {
  if (_havebar(name)) {
    return dir_recmake(name);
  }
  return (mkdir(name, PERMIS_DEF));
}

static int dirrm(const char *name) {
  if (_havebar(name)) {
    return _dir_recdel(name);
  }
  return rmdir(name);
}

static char *dirgetcur(void) {
  char *_current_dir = getcwd(NULL, 0);
  if (!_current_dir)
    return NULL;
  return _current_dir;
}

static int dirsetcur(const char *name) { return chdir(name); }

static int dirmv(const char *name, const char *path) { return rename(name, path); }

static int direxists(const char *name) {
  struct stat exists;
  if (stat(name, &exists) != 0)
    return 0; /* false */
  return 1;   /* true */
}

static int dirisemp(const char *name) {
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

int dir_recmake(const char *__restrict path) {
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
          return DIR_ERR_UNKNOWN;
        }
      }
      *p = '\\';
    }
  }
  if (!dir_exists(tempPath)) {
    if (dir_make(tempPath) != 0) {
      return DIR_ERR_UNKNOWN;
    }
  }
  return 0;
}

static void dircnt(const char* path, signed long* it, short recursive) {
    WIN32_FIND_DATA fd;
    HANDLE h;
    char search_path[MAX_PATH];

    if (!it) return;

    snprintf(search_path, MAX_PATH, "%s\\*", path);
    h = FindFirstFile(search_path, &fd);
    if (h == INVALID_HANDLE_VALUE) return;

    do {
        if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
            continue;

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            (*it)++;
            if (recursive)
                // monta caminho completo para subdiretório
                char subdir[MAX_PATH];
                snprintf(subdir, MAX_PATH, "%s\\%s", path, fd.cFileName);
                dirlistcnt(subdir, it, recursive);
        }
    } while (FindNextFile(h, &fd) != 0);

    FindClose(h);
}

int dir_recdel(const char *__restrict path) {
  WIN32_FIND_DATAA ffd;
  HANDLE hFind;
  char searchPath[MAX_PATH];
  char itemPath[MAX_PATH];

  snprintf(searchPath, MAX_PATH, "%s\\*", path);

  hFind = FindFirstFileA(searchPath, &ffd);
  if (hFind == INVALID_HANDLE_VALUE) {
    return DIR_ERR_IO;
  }

  do {
    if (strcmp(ffd.cFileName, ".") == 0 || strcmp(ffd.cFileName, "..") == 0)
      continue;

    snprintf(itemPath, MAX_PATH, "%s\\%s", path, ffd.cFileName);

    if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
      if (dir_recdel(itemPath) != 0) {
        FindClose(hFind);
        return DIR_ERR_UNKNOWN;
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
