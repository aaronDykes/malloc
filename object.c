
#include "object.h"

// long long int hash(object key)
// {
//     long long int index = 2166136261u;

//     switch (key.type)
//     {

//     case _TYPE_STR:
//         for (char *s = (char *)key.as.c._string; *s; s++)
//         {
//             index ^= (int)*s;
//             index *= 16777619;
//         }
//         break;
//     case _TYPE_DOUBLE:
//         index ^= ((long long int)key.as._double);
//         index = (index * 16777420);
//         break;

//     case _TYPE_CHAR:
//         index ^= key.as._char;
//         index = (index * 16742069);
//         break;
//     default:
//         return 0;
//     }
//     return index;
// }

long long int hash(value key)
{
    long long int index = 2166136261u;

    for (char *s = (char *)key.c._string; *s; s++)
    {
        index ^= (int)*s;
        index *= 16777619;
    }

    return index;
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
    oj.as.c._string = _string;
    oj.as.c.hash = hash(oj.as);
    oj.type = _TYPE_STR;
    return oj;
}

value _key(const char *key)
{
    value oj;
    oj.c._string = key;
    oj.c.hash = hash(oj);
    return oj;
}
