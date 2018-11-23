#include <stdlib.h>
#include <string.h>

#include <hash_table.h>

// Allocates memory to an ht_item and saves key and value
static ht_item* ht_new_item(const char *k, const char*v){
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

// Initialising a new hash table
ht_hash_table* ht_new(){
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));

    ht->size = 53;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

// Deleting items
static void ht_del_item(ht_item* i){
    free(i->key);
    free(i->value);
    free(i);
}

// Function which takes a pointer to a hashtable, iterates,
// and deletes each non NULL item within the hashtable
void ht_del_hash_table(ht_hash_table* ht){
    for(int i = 0; i < ht->size; i++){
        ht_item* item = ht->items[i];
        if (item != NULL){
            ht_del_items(item);
        }
    }
    free(ht->items);
    free(ht);
}

int main(){
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}