#ifndef __MEM_H
#define __MEM_H

#include <stdlib.h>

#define MALLOC(size) \
    _malloc_(size)
#define FREE(ptr) \
    _free_(ptr)

void *_malloc_(size_t size);
void *_realloc_(void *ptr, size_t old_size, size_t size);
void _free_(void *ptr);
int _exit_(int state);

#endif
