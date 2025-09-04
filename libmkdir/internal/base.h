#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int dir_make(const char *name);
static int dir_recmake(const char *name);
static char *dir_getcurrent(void);
static int dir_setcurrent(const char *name);
static int dir_recmake(const char *name);
static int dir_exists(const char *name);
static int dir_isempty(const char *name);
static int dir_move(const char *name, const char *__restrict path);
static int dir_del(const char *name);
static int dir_recdel(const char *name);
#endif
