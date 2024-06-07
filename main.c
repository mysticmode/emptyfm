#include <stdio.h>
#include "dict.c"

int main()
{
    /* Create a new hash table */
    HashTable *ht = create_table();

    /* Insert some key-value pairs into the table */
    insert(ht, "name", "Alice");
    insert(ht, "age", "30");
    insert(ht, "city", "wonderland");

    /* Search for values by their keys */
    printf("name: %s\n", search(ht, "name"));
    printf("age: %s\n", search(ht, "age"));
    printf("city: %s\n", search(ht, "city"));

    /* Free all memory allocated for the hash table */
    free_table(ht);

    return 0;
}