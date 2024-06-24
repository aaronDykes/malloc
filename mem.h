#ifndef __MEM_H
#define __MEM_H

#include <stdlib.h>

void *malloc_(size_t size);
void free_(void *ptr);
int exit_(int state);
#endif