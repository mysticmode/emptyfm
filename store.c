#include <stdio.h>
#include "store.h"
#include "dict.c"

void insert_lang()
{
    /* Create a new hash table */
    HashTable *ht = create_table();

    /* Insert the language key-value pairs into the table */
    for (int i = 0; i < LEN(lang); i++)
    {
        insert(ht, lang[i][0], lang[i][1]);
    }

    printf("ta: %s\n", search(ht, "ta"));

    /* Free all memory allocated for the hash table */
    free_table(ht);
}

void insert_country()
{
    /* Create a new hash table */
    HashTable *ht = create_table();

    /* Insert the language key-value pairs into the table */
    for (int i = 0; i < LEN(country); i++)
    {
        insert(ht, country[i][0], country[i][1]);
    }

    printf("IN: %s\n", search(ht, "IN"));

    /* Free all memory allocated for the hash table */
    free_table(ht);
}