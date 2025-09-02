# libmkdir

### The libmkdir library is a library that offers abstraction for manipulation, generation and removal of directories in cross-platform C, completely header-only.

## functions 

``` c
static int makedir(const char*__restrict name);
```

Creates a directory. Returns -2 if the name pointer is null; returns 0 if successful; any other value indicates an error during creation.

``` c
static int havedir(const char*__restrict name);
```

checks if a directory exists. Returns 1 if yes, and 0 if no.

``` c
static int removedir(const char*__restrict name);
```

removes an empty directory, returns -2 if the name pointer is invalid. Success only if 0 is returned

``` c
static int renamedir(const char*__restrict old_name, const char*__restrict new_name);
```
