#include "table.h"

void insert_entry(table *t, table entry)
{
}
void delete_entry(table *t, value key)
{
}
table entry(value key, object val)
{

    table tab;
    tab.key = key;
    tab.val = val;
    tab.type = val.type;
    return tab;
}
