#include <string.h>
#include <stdlib.h>
// #include <aiv/list.h>

// Trasformazione delle chiavi in una aiv_list

typedef struct aiv_dict_item
{
    struct aiv_dict_item *prev;
    struct aiv_dict_item *next;
    void *key;
    unsigned int key_len;
    void *data;
}aiv_dict_item_t;

typedef struct aiv_dict
{
    struct aiv_dict_item **hash_map;
    unsigned int hash_map_size;
    unsigned int current_cost;
    unsigned int count;
} aiv_dict_t;

typedef struct aiv_dict_iterator
{
    aiv_dict_t *dict;
    aiv_dict_item_t *record_context;
    void *current_key;
    unsigned int map_context;

}aiv_dict_iterator_t;

// create a new dictionary
aiv_dict_t *aiv_dict_new(unsigned int, int *);
// destroy a dict instance
void aiv_dict_destroy(aiv_dict_t  *);
// add an item to a dictionary
int aiv_dict_add(aiv_dict_t *, void *, unsigned int, void *);
// retrieve a value given a key
void *aiv_dict_get(aiv_dict_t *, void *, unsigned int);
// remove item from the dict
void *aiv_dict_remove(aiv_dict_t *, void *, unsigned int);
// destroy the istance of the dictionary
void aiv_dict_destroy(aiv_dict_t *);
// the length of the dictionary, that is the number of records
int aiv_dict_len(aiv_dict_t *);
// makes a list out of the key of the dict
// aiv_list_t *aiv_dict_keys_to_aiv_list(aiv_dict_t *);


//initialize a preallocated iterator to an instance of aiv_dict
void aiv_dict_iterator_init(aiv_dict_iterator_t *, aiv_dict_t *);
//moves the iterator to the first non NULL dict_item, returns -1 if the last dict_item has been reached
int aiv_dict_iterator_move_next(aiv_dict_iterator_t *);
//returns the key at a given step of the iteration
void *aiv_dict_iterator_get_current_key(aiv_dict_iterator_t *);



