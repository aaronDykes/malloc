
#ifndef _TABLE_H
#define _TABLE_H

#include "object.h"
#include "mem.h"

#define TABLE_LOAD_CAPACITY 0.75
#define GROW_TABLE(tab, size) \
    _realloc_table(tab, size)

typedef struct table table;

struct table
{

    T type;
    uint16_t len;
    uint16_t count;

    string key;
    object val;

    table *next;
};

table *_table(size_t size);
table *_realloc_table(table **tab, size_t size);
void _free_table(table **tab);

void _free_entry(table *entry);

void write_table(table **t, string key, object val);
void insert_entry(table *t, table entry);
void delete_entry(table **t, string key);
object find_entry(table *t, string key);
table entry(string key, object val);
table null_entry(void);

table *hash_overlap(table **tab, table entry);

#endif
