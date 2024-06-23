#include "mem.h"
#include "mem_util.h"
#include <sys/mman.h>

static void *request_system_mem(size_t size)
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

static void _init_global_mem()
{
    free_list = request_system_mem(ARM64_PAGE * OFFSET);
    free_list->m.next = NULL;
    free_list->m.size = ARM64_PAGE - OFFSET;
}
void _destroy_global_mem()
{

    _free *tmp = NULL;

    while (free_list)
    {
        tmp = free_list->m.next;
        munmap(free_list, free_list->m.size);
        free_list = tmp;
    }
    free_list = NULL;
    tmp = NULL;
}
static void _merge(_free **ptr)
{

    _free *next = NULL;

    for (next = free_list; next; next = next->m.next)
        if ((next + 1) + next->m.size == next->m.next)
        {
            next->m.size += next->m.next->m.size;
            next->m.next = next->m.next->m.next;
        }
}

static void init_free_ptr(_free **ptr, size_t alloc_size, size_t new_size)
{
    (*ptr)->m.next = request_system_mem(alloc_size * OFFSET);
    (*ptr)->m.next->m.size = alloc_size - OFFSET - new_size;
    (*ptr)->m.next->m.next = NULL;
}

static _free *init_alloced_ptr(_free *ptr, size_t size)
{
    _free *alloced = NULL;
    alloced = ptr;
    alloced->m.next = NULL;
    alloced->m.size = size;
    return alloced;
}

void *malloc_(size_t size)
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
        return 1 + init_alloced_ptr(next + 1 + next->m.size, size - OFFSET);
    }
    else
    {
        size_t s = ARM64_PAGE;

        while (s < size)
            s *= INC;

        init_free_ptr(&prev, s, size);
        return 1 + init_alloced_ptr(prev->m.next + 1 + prev->m.next->m.size, size - OFFSET);
    }
}
void free_(void *ptr)
{
    _free *f = NULL;
    f = PTR(ptr);

    if (!f)
        return;
    if (f->m.size == 0)
        return;

    _free *prev = NULL, *next = NULL;

    for (next = free_list; next && next < f; next = next->m.next)
        prev = next;

    if (next && next < f)
    {
        f->m.next = next->m.next;
        next->m.next = f;
    }
    else if (prev && prev < f)
    {
        f->m.next = prev->m.next;
        prev->m.next = f;
    }
    _merge(&f);

    prev = NULL;
    next = NULL;
    f = NULL;
}
