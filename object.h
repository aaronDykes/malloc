#ifndef _OBJECT_H
#define _OBJECT_H

#include <stdlib.h>

typedef enum
{

    _TYPE_INT,
    _TYPE_DOUBLE,
    _TYPE_LONG,
    _TYPE_CHAR,
    _TYPE_STR,

} T;

typedef struct object object;
typedef struct string string;
typedef struct vector vector;
typedef union value value;
typedef union _1d_vector _1d_vector;
typedef union _2d_vector _2d_vector;

struct string
{
    long long int hash;
    uint16_t len;
    const char *_string;
};

union _1d_vector
{
    int *_ints;
    long long int *_longs;
    double *_doubles;
};
union _2d_vector
{
    int **_ints;
    long long int **_longs;
    double **_doubles;
    char **_strings;
};

struct vector
{
    uint16_t len;
    uint16_t count;

    uint8_t ndim;

    union
    {
        _1d_vector _1d_;
        _2d_vector _2d_;
    };
};

union value
{
    int _int;
    double _double;
    long long int _long;
    char _char;
    string c;
};

struct object
{

    T type;

    union
    {
        vector listof;
        value as;
    };
};

value _key(const char *key);
object _int(int _int);
object _double(double _double);
object _long(long long int _long);
object _char(char _char);
object _string(const char *_string);

#endif
