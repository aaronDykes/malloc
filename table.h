
#ifndef _TABLE_H
#define _TABLE_H

#include "object.h"
#include "mem.h"

typedef struct table table;

struct table
{

    T type;
    uint16_t len;
    uint16_t count;

    value key;
    object val;

    table *next;
};

void insert_entry(table *t, table entry);
void delete_entry(table *t, value key);
table entry(value key, object val);

#endif
