# libmkdir

### The libmkdir library is a library that offers abstraction for manipulation, generation and removal of directories in cross-platform C, completely header-only.

## functions 

>``` c
> static int dir_make(const char*__restrict name);
> ```
> Creates a directory. Returns 0 if successful.
---

> ``` c
> static int dir_recmake(const char*__restrict name);
> ```
> Creates directory recursively, returns 0 on success.
---

> ``` c
> static int dir_exists(const char*__restrict name);
> ```
> Checks if a directory exists. Returns 1 if yes, and 0 if no.
---

> ``` c
> static int dir_remove(const char*__restrict name);
> ```
> Removes an empty directory, returns -2 if the name pointer is invalid. Success only if 0 is returned
---

> ``` c
> static int dir_move(const char*__restrict old_name, const char*__restrict new_name);
> ```
> Function capable of both renaming and moving a directory. Returns 0 if successful.
---

> ``` c
> static char* dir_getcurrent();
> ```
> Returns the absolute path of the default directory.
---

> ``` c
> static int dir_setcurrent(const char*__restrict name);
> ```
> Sets the current directory of the process, returns 0 if successful.
---
