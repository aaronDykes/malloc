#ifndef __MEM_H
#define __MEM_H

#include <stdlib.h>

#define INC 2

#define MALLOC(size) \
    _malloc_(size)

#define REALLOC(ptr, old_size, new_size) \
    _realloc_(ptr, old_size, new_size)

#define FREE(ptr) \
    _free_(ptr)

void *_malloc_(size_t size);
void *_realloc_(void *ptr, size_t old_size, size_t size);
void _free_(void *ptr);
int _exit_(int state);

#endif
