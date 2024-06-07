#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

/**
 * Hash function to compute an index for a given key
 */
unsigned int hash(const char *key)
{
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; i++)
    {
        value = value * 37 + key[i];
    }

    /* Ensure the value fits within the table size */
    value = value % TABLE_SIZE;
    return value;
}

/**
 * Function to create a new hash table
 */
HashTable *create_table()
{
    HashTable *table = malloc(sizeof(HashTable));
    if (!table)
    {
        fprintf(stderr, "Error: Memory allocation failed for hash table\n");
        return NULL;
    }

    table->entries = malloc(sizeof(Entry *) * TABLE_SIZE);
    if (!table->entries)
    {
        fprintf(stderr, "Error: Memory allocation failed for hash table entries\n");
        free(table);
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table->entries[i] = NULL;
    }
    return table;
}

/**
 * Function to create a new entry with a given key and value
 */
Entry *create_entry(const char *key, const char *value)
{
    Entry *entry = malloc(sizeof(Entry));
    if (!entry)
    {
        fprintf(stderr, "Error: Memory allocation failed for entry\n");
        return NULL;
    }

    entry->key = strdup(key);
    if (!entry->key)
    {
        fprintf(stderr, "Error: Memory allocation failed for entry key\n");
        free(entry);
        return NULL;
    }

    entry->value = strdup(value);
    if (!entry->value)
    {
        fprintf(stderr, "Error: Memory allocation failed for entry value\n");
        free(entry->key);
        free(entry);
        return NULL;
    }

    entry->next = NULL;
    return entry;
}

/**
 * Function to insert a key-value pair into the hash table
 */
void insert(HashTable *table, const char *key, const char *value)
{
    if (!table || !key || !value)
    {
        fprintf(stderr, "Error: Invalid argument to insert function\n");
        return;
    }

    unsigned int slot = hash(key);
    Entry *entry = table->entries[slot];

    /* If the slot is empty, insert the entry directly */
    if (entry == NULL)
    {
        table->entries[slot] = create_entry(key, value);
        if (!table->entries[slot])
        {
            fprintf(stderr, "Error: Failed to create entry\n");
        }
        return;
    }

    Entry *prev;
    /* Traverse the linked list to find the correct position or existing key */
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            free(entry->value);
            entry->value = strdup(value);
            if (!entry->value)
            {
                fprintf(stderr, "Error: Memory allocation failed for updated value\n");
            }
            return;
        }
        prev = entry;
        entry = entry->next;
    }
    /* Insert the new entry at the end of the list */
    prev->next = create_entry(key, value);
    if (!prev->next)
    {
        fprintf(stderr, "Error: Failed to create entry\n");
    }
}

/**
 * Function to search for a value by its key in the hash table
 */
char *search(HashTable *table, const char *key)
{
    if (!table || !key)
    {
        fprintf(stderr, "Error: Invalid argument to search function\n");
        return NULL;
    }

    /* Compute the hash value for the key */
    unsigned int slot = hash(key);
    Entry *entry = table->entries[slot];

    /* Traverse the linked list to find the entry with the matching key */
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            /* Return the value if the key is found */
            return entry->value;
        }
        entry = entry->next;
    }

    /* Return NULL if the key is not found */
    return NULL;
}

/**
 * Function to free all memory allocated for the hash table
 */
void free_table(HashTable *table)
{
    /* Free each entry in the table */
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        Entry *entry = table->entries[i];
        while (entry != NULL)
        {
            Entry *tmp = entry;
            entry = entry->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }
    /* Free the table's entries array and the table itself */
    free(table->entries);
    free(table);
}