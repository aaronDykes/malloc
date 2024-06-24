#include <stdio.h>

#include "mem.h"

static void _strcpy(char *dst, char *src)
{
    char *c = dst;

    while ((*c++ = *src++))
        ;
}

struct hello
{
    int data;
    struct hello *next;
};

int main(int argc, char **argv)
{

    struct hello *s = NULL;

    s = _malloc_(sizeof(struct hello));

    s->data = 69;
    s->next = NULL;

    printf("%d\n", s->data);

    _free_(s);

    return _exit_(EXIT_SUCCESS);
}
