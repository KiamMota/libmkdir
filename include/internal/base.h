#ifndef _BASE_H_
#define _BASE_H_

int dir_make(const char *__restrict name);
int dir_exists(const char*__restrict name);
int dir_move(const char *__restrict name, const char *__restrict path);
int dir_del(const char *__restrict name);

#endif
