#ifndef __MEM_UTIL_H
#define __MEM_UTIL_H

#include <stdlib.h>

#define ARM64_PAGE 16384
#define INC 2

typedef double align;
typedef union _free _free;

union _free
{
    struct
    {
        _free *next;
        size_t size;
    } m;

    align a;
};

#define OFFSET sizeof(_free)
#define PTR(ptr) \
    (((_free *)ptr) - 1)

static _free *free_list = NULL;
static _free *free_list_head = NULL;

static void *request_system_mem(size_t size);
static void _init_global_mem();
static void _merge(_free **ptr);

#endif
