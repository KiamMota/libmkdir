# libmkdir

### The libmkdir library is a library that offers abstraction for manipulation, generation and removal of directories in cross-platform C, completely header-only.

## functions 

>``` c
> static int dirmk(const char* path);
> ```
> Creates a directory (recursively or not). Returns 0 if successful.
---


> ``` c
> static int direxists(const char* path);
> ```
> Checks if a directory exists. Returns 1 if yes, and 0 if no.
---

> ``` c
> static int dirisemp(const char* path);
> ```
> Checks if directory is empty or not, returning 1 or 0 respectively.

> ``` c
> static int dirrm(const char* path);
> ```
> Removes an empty directory (recursively or not), Returns 0 if successful.
---

> ``` c
> static int dirmv(const char* old_name, const char* path);
> ```
> Function capable of both renaming and moving a directory. Returns 0 if successful.
---

> ``` c
> static char* dirgetcur();
> ```
> Returns the absolute path of the default directory.
---

> ``` c
> static int dirsetcurrent(const char* path);
> ```
> Sets the current directory of the process, returns 0 if successful.
---
