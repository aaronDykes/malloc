#include "table.h"

void write_table(table **t, string key, object val)
{

    table en = entry(key, val);

    if (((*t) - 1)->len * TABLE_LOAD_CAPACITY < ((*t) - 1)->count + 1)
    {
        ((*t) - 1)->len = ((*t) - 1)->len * INC;
        (*t) = GROW_TABLE(t, ((*t) - 1)->len);
    }

    ((*t) - 1)->count++;

    insert_entry(*t, en);
}

void insert_entry(table *t, table entry)
{

    int index = entry.key.hash & ((t - 1)->len - 1);

    if (t[index].type == _TYPE_NULL)
    {
        t[index] = entry;
        return;
    }

    if (t[index].key.hash == entry.key.hash)
    {
        t[index] = entry;
        return;
    }

    for (table *ptr = t[index].next; ptr; ptr = ptr->next)
        if (ptr->key.hash == entry.key.hash)
        {
            t[index] = entry;
            return;
        }

    t[index].next = hash_overlap(&t[index].next, entry);
}

object find_entry(table *t, string key)
{

    int index = key.hash & ((t - 1)->len - 1);

    if (t[index].type == _TYPE_NULL)
        return _null();

    if (t[index].key.hash == key.hash)
        return t[index].val;

    table *ptr = NULL;

    for (ptr = t[index].next; ptr && ptr->key.hash != key.hash; ptr = ptr->next)
        ;

    if (!ptr)
        return _null();

    if (ptr->key.hash == key.hash)
        return ptr->val;

    return _null();
}

table *hash_overlap(table **tab, table entry)
{

    table *t = NULL;
    t = MALLOC(sizeof(table));

    *t = entry;

    t->next = NULL;
    t->next = *tab;

    return t;
}

void delete_entry(table **t, string key)
{
    uint16_t index = key.hash & (((*t) - 1)->len - 1);

    if ((*t)[index].type == _TYPE_NULL)
        return;

    if ((*t)[index].key.hash == key.hash)
    {

        _free_entry(&(*t)[index]);

        (*t)[index] = null_entry();

        if ((*t)[index].next)
        {
            table *tmp = (*t)[index].next;

            FREE((*t)[index].next);
            (*t)[index] = entry(tmp->key, tmp->val);
        }

        return;
    }

    table *prev = NULL, *ptr = NULL, *tmp = NULL;

    if (!(*t)[index].next)
        return;

    for (ptr = (*t)[index].next; ptr && ptr->key.hash != key.hash; ptr = ptr->next)
        prev = ptr;

    if (!ptr && !prev)
        return;

    if (!prev)
    {

        table *tmp = ptr->next;
        _free_entry(ptr);
        // FREE(ptr);
        (*t)[index].next = tmp;
        return;
    }

    tmp = ptr->next;

    _free_entry(ptr);
    FREE(ptr);

    prev->next = tmp;
}

void _free_entry(table *entry)
{

    FREE((char *)entry->key._string);
    FREE_OBJ(entry->val);

    entry = NULL;
}

table entry(string key, object val)
{

    table tab;
    tab.key = key;
    tab.val = val;
    tab.type = val.type;
    return tab;
}

table null_entry(void)
{
    table tab;
    tab.type = _TYPE_NULL;
    tab.next = NULL;
    // tab.key = ();
    tab.val = _null();
    return tab;
}

table *_table(size_t size)
{
    table *t = NULL;
    t = MALLOC((sizeof(table) * size) + sizeof(table));

    t->len = size;
    t->count = 0;

    for (size_t i = 1; i < size; i++)
        t[i] = null_entry();

    return t + 1;
}

table *_realloc_table(table **tab, size_t size)
{
    table *t = NULL;
    if (!(*tab))
        return size <= 0 ? NULL : _table(size);

    if (size == 0)
    {
        FREE(*tab);
        tab = NULL;
        return NULL;
    }

    t = _table(size);

    size_t copy_size = ((*tab) - 1)->len < size
                           ? ((*tab) - 1)->len
                           : size;

    for (size_t i = 0; i < copy_size; i++)
        t[i] = (*tab)[i];

    (t - 1)->count = ((*tab) - 1)->count;

    _free_table(tab);

    return t;
}

void _free_table(table **tab)
{

    for (size_t i = 0; i < ((*tab) - 1)->len; i++)
    {

        while ((*tab)[i].next)
        {
            table *tmp = (*tab)[i].next->next;
            FREE((*tab)[i].next);
            (*tab)[i].next = tmp;
        }
    }

    FREE((*tab) - 1);
    tab = NULL;
}
