# libmkdir

### The libmkdir library is a library that offers abstraction for manipulation, generation and removal of directories in cross-platform C, completely header-only.

## functions 

>``` c
> int dirmk(const char* name);
> ```
> Creates a directory (recursively or not). Returns 0 if successful.
---

> ``` c
> int direxists(const char* name);
> ```
> Checks if a directory exists (recursively or not). Returns 0 if successful.
---

> ``` c
> int dirisemp(const char* name);
> ```
> Checks whether a directory is empty or not, returning 1 or 0 respectively.

> ``` c
> int dirrm(const char* name);
> ```
> Removes an empty directory (recursively or not). Returns 0 if successful.
---


> ``` c
> int dirmv(const char* old_name, const char* new_name);
> ```
> Function capable of both renaming and moving a directory. Returns 0 if successful.
---

> ``` c
> char* dirgetcur();
> ```
> Returns the absolute path of the default directory. Returns 0 if successful.
---

> ``` c
> int dirsetcur(const char* name);
> ```
> Sets the current directory of the process. Returns 0 if successful.
---
