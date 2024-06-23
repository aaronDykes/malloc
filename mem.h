#ifndef __MEM_H
#define __MEM_H

#include <stdlib.h>

void *malloc_(size_t size);
void free_(void *ptr);
void _destroy_global_mem();
#endif