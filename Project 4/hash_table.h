// Key-value pairs (items)
typedef struct {
    char* key;
    char* value;
} ht_item;

// Hash table details
typedef struct{
    int size;
    int count;
    ht_item** items;
} ht_hash_table;