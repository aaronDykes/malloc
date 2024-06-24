#include <stdio.h>

#include "mem.h"

static void _strcpy(char *dst, char *src)
{
    char *c = dst;

    while ((*c++ = *src++))
        ;
}

int main(int argc, char **argv)
{

    char *s = NULL;
    s = _malloc_(sizeof(char) * 16352);
    _strcpy(s, "Hello world!");

    printf("%s\n", s);

    _free_(s);
    return _exit_(EXIT_SUCCESS);
}
