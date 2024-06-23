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
    s = malloc_(sizeof(char) * 16352);
    _strcpy(s, "Hello world!");

    printf("%s\n", s);

    free_(s);
    _destroy_global_mem();

    return EXIT_SUCCESS;
}