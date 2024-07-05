#include <stdio.h>

#include "mem.h"
#include "table.h"

static void _strcpy(char *dst, char *src)
{
    char *c = dst;

    while ((*c++ = *src++))
        ;
}

int main(int argc, char **argv)
{

    table *t = _table(1);

    string k1 = _key("dyke");
    object v1 = _string("dykes");
    string k2 = _key("another");
    object v2 = _string("another one");
    string k3 = _key("okay");
    object v3 = _string("sir dyke");

    insert_entry(t, entry(k1, v1));
    insert_entry(t, entry(k2, v2));
    insert_entry(t, entry(k3, v3));

    // delete_entry(&t, k1);
    // delete_entry(&t, k);
    // delete_entry(&t, k2);
    // delete_entry(&t, k3);

    printf("%s\n", find_entry(t, k1).as.c._string);
    printf("%s\n", find_entry(t, k2).as.c._string);
    printf("%s\n", find_entry(t, k3).as.c._string);

    // _free_table(&t);

    return _exit_(EXIT_SUCCESS);
}
