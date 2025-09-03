#ifndef _BASE_H_
#define _BASE_H_

#include <string.h>

static int dir_make(const char *__restrict name);
static int dir_recmake(const char *__restrict name);
static char *dir_getcurrent();
static int dir_setcurrent(const char *__restrict name);
static int dir_recmake(const char *__restrict name);
static int dir_exists(const char *__restrict name);
static int dir_move(const char *__restrict name, const char *__restrict path);
static int dir_del(const char *__restrict name);

#endif
