#ifdef _WIN32

#ifndef _WINMKDIR_H_
#define _WINMKDIR_H_

#include "base.h"
#include <Windows.h>

int dir_make(const char *path) {
    return CreateDirectoryA(path, NULL) ? 0 : -1;
}

int dir_remove(const char *path) {
    return RemoveDirectoryA(path) ? 0 : -1;
}

int dir_exists(const char *path) {
    DWORD dwAttrib = GetFileAttributesA(path);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) ? 1 : 0;
}

int dir_move(const char *oldpath, const char *newpath) {
    return MoveFileA(oldpath, newpath) ? 0 : -1;
}

int dir_del(const char *path) {
    return RemoveDirectoryA(path) ? 0 : -1;
}

#endif

#endif
