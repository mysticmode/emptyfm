#ifndef DICT_H
#define DICT_H

#define TABLE_SIZE 100

/**
 * Structure to represent an entry in the hash table
 */
typedef struct Entry
{
    char *key;
    char *value;

    /* Pointer to the next entry (for handling collisions) */
    struct Entry *next;
} Entry;

/**
 * Structure to represent the hash table
 */
typedef struct
{
    /* Array of pointers to entries */
    Entry **entries;
} HashTable;

unsigned int hash(const char *key);
HashTable *create_table();
Entry *create_entry(const char *key, const char *value);
void insert(HashTable *table, const char *key, const char *value);
char *search(HashTable *table, const char *key);
void free_table(HashTable *table);

#endif