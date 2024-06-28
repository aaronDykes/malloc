
#include "object.h"
#include "mem.h"
#include <string.h>

static long long int hash(char *str)
{
    long long int index = 2166136261u;

    for (char *s = str; *s; s++)
    {
        index ^= (int)*s;
        index *= 16777619;
    }

    return index;
}

static size_t _strlen(char *c)
{
    int count = 0;
    for (char *s = c; *s; s++)
        count++;
    return count;
}

static void _strcpy(char *dst, char *src)
{
    char *c = dst;

    while ((*c++ = *src++))
        ;
}

object _int(int _int)
{
    object oj;
    oj.as._int = _int;
    oj.type = _TYPE_INT;
    return oj;
}
object _double(double _double)
{
    object oj;
    oj.as._double = _double;
    oj.type = _TYPE_DOUBLE;
    return oj;
}
object _long(long long int _long)
{
    object oj;
    oj.as._long = _long;
    oj.type = _TYPE_LONG;
    return oj;
}

object _null(void)
{
    object oj;
    oj.as._null = NULL;
    oj.type = _TYPE_NULL;
    return oj;
}
object _char(char _char)
{
    object oj;

    oj.as._char = _char;
    oj.type = _TYPE_CHAR;
    return oj;
}
object _string(const char *_string)
{
    object oj;
    size_t size = _strlen((char *)_string);

    oj.as.c._string = MALLOC(size * sizeof(char));
    strcpy((char *)oj.as.c._string, (char *)_string);

    oj.as.c.hash = hash((char *)_string);
    oj.type = _TYPE_STR;
    return oj;
}

string _key(const char *_string)
{
    string oj;

    size_t size = _strlen((char *)_string);

    oj._string = MALLOC(size * sizeof(char));
    strcpy((char *)oj._string, (char *)_string);

    oj.hash = hash((char *)_string);

    return oj;
}

void free_obj(object obj)
{

    if (obj.type != _TYPE_STR)
        return;

    FREE((char *)obj.as.c._string);
    obj.as.c._string = NULL;
}
