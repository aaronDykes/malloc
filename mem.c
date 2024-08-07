#include "mem.h"
#include "mem_util.h"
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>

static void *_request_system_mem(size_t size)
{
    return (void *)mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS |
            POSIX_MADV_RANDOM |
            POSIX_MADV_WILLNEED,
        -1, 0);
}

static void _init_global_mem(void)
{
    free_list = _request_system_mem(ARM64_PAGE);
    free_list->m.next = NULL;
    free_list->m.size = ARM64_PAGE - OFFSET;
}
int _exit_(int state)
{
    _destroy_global_mem();
    return state;
}

static void _destroy_global_mem(void)
{

    _merge();
    _free *tmp = NULL;

    // mu
    while (free_list)
    {
        tmp = free_list->m.next;
        munmap(free_list, free_list->m.size);
        free_list = tmp;
    }
    free_list = NULL;
    tmp = NULL;
}

static void _merge(void)
{

    _free *next = NULL, *prev = NULL;

    for (next = free_list; next; next = next->m.next)
    {
        prev = next;

        if ((char *)(next + 1) + next->m.size == (char *)next->m.next)
        {
            prev->m.size += next->m.next->m.size;
            prev->m.next = next->m.next->m.next;
        }
    }
}

static void _init_free_ptr(_free **ptr, size_t alloc_size, size_t new_size)
{
    (*ptr)->m.next = _request_system_mem(alloc_size);
    (*ptr)->m.next->m.size = alloc_size - OFFSET - new_size;
    (*ptr)->m.next->m.next = NULL;
}

static void *_init_alloced_ptr(void *ptr, size_t size)
{
    _free *alloced = NULL;
    alloced = ptr;
    alloced->m.next = NULL;
    alloced->m.size = size - OFFSET;
    return memset((void *)(1 + alloced), 0, size - OFFSET);
}

void *_malloc_(size_t size)
{

    if (!free_list)
        _init_global_mem();

    size += OFFSET;

    _free *prev = NULL,
          *next = NULL;

    for (next = free_list; next && next->m.size < size; next = next->m.next)
        prev = next;

    if (next && next->m.size >= size)
    {
        next->m.size -= size;

        if (prev && next->m.size == 0)
            prev->m.next = next->m.next;
        else if (!prev && next->m.size == 0)
            free_list = next->m.next;

        return _init_alloced_ptr((char *)(next + 1) + next->m.size, size);
    }
    else
    {
        size_t s = ARM64_PAGE;

        while (s < size)
            s *= INC;

        _init_free_ptr(&prev, s, size);
        return _init_alloced_ptr((char *)(prev->m.next + 1) + prev->m.next->m.size, size);
    }
}

void *_realloc_(void *ptr, size_t old_size, size_t size)
{

    if (size <= 0)
    {
        _free_(ptr);
        ptr = NULL;
        return NULL;
    }

    void *new = NULL;
    new = MALLOC(size);

    size_t tmp_size = (old_size < size)
                          ? old_size
                          : size;

    if (!ptr)
        return new;

    memcpy(new, (char *)ptr, tmp_size);

    FREE(ptr);
    ptr = NULL;

    return new;
}

void _free_(void *ptr)
{
    _free *f = NULL;
    f = PTR(ptr);

    if (!f)
        return;
    if (f->m.size == 0)
        return;

    _free *prev = NULL, *next = NULL;

    if (!free_list)
    {
        free_list = f;
        free_list->m.next = NULL;
        return;
    }

    for (next = free_list; next && next < f; next = next->m.next)
        prev = next;

    if (next && next < f)
        f->m.next = next->m.next, next->m.next = f;
    else if (prev && prev < f)
        f->m.next = prev->m.next, prev->m.next = f;

    _merge();

    prev = NULL;
    next = NULL;
    f = NULL;
}
