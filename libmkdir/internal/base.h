#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum LMKD_RES LMKD_RES;

static int dirmk(const char *name);
static int dirrm(const char *name);
static int dirisemp(const char *name);
static char *dirgetcur(void);
static int dirsetcur(const char *name);
static int direxists(const char *name);
static int dirmv(const char *name, const char *path);
#endif
