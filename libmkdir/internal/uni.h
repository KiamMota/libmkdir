#ifdef __unix__

#ifndef _UNIMKDIR_H_
#define _UNIMKDIR_H_

#include "base.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include <errno.h>

#define PERMIS_DEF 0755

int dir_make(const char *name) {

  if (mkdir(name, PERMIS_DEF)) {
    return -5;
  }
  return 0;
}

char *dir_getcurrent(void) {
  char *_current_dir = getcwd(NULL, 0);
  if (!_current_dir)
    return "noone";
  return _current_dir;
}

int dir_recmake(const char *name) {
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

int dir_setcurrent(const char *name) { return chdir(name); }

int dir_del(const char *name) { return rmdir(name); }

int dir_recdel(const char *name) {

  /* first, check if the name is null or have any string */

  if (strlen(name) <= 0)
    return -4;

  /* first check if the dir is empty before start the recurs */
  if (!dir_exists(name))
    return -1;
  if (dir_isempty(name)) {
    return dir_del(name);
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
          dir_del(fullpath);
        } else {
          return remove(fullpath);
        }
      }
      free(fullpath);
    }
  }
  closedir(dir);
  return dir_del(name);
}

int dir_move(const char *name, const char *path) { return rename(name, path); }

int dir_exists(const char *name) {
  struct stat exists;
  if (stat(name, &exists) != 0)
    return 0;
  return 1;
}

int dir_isempty(const char *name) {
  struct dirent *dr;
  DIR *curdir = opendir(name);
  while ((dr = readdir(curdir)) != NULL) {
    if (strcmp(dr->d_name, ".") != 0 && strcmp(dr->d_name, "..") != 0)
      return 0;
  }
  closedir(curdir);
  return 1;
}

#endif

#endif
