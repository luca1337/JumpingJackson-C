#include <dict.h>
#include <error.h>
#include <stdio.h>

// Bernstein classic hash
static unsigned int djb33x_hash(void *key, unsigned int key_len)
{
    unsigned int hash = 5381;
    unsigned int i;

    unsigned char *key_as_num = (unsigned char *)key;

    for (i = 0; i < key_len; i++)
    {
        hash = ((hash << 5) + hash) ^ key_as_num[i];
    }

    return hash;
}

aiv_dict_t *aiv_dict_new(unsigned int hash_map_size, int *err_code)
{
    if (err_code)
        *err_code = AIV_OK;

    if (hash_map_size < 1)
    {
        if (err_code)
            *err_code = AIV_INVALID_SIZE;
        return NULL;
    }

    aiv_dict_t *dict = malloc(sizeof(aiv_dict_t));
    if (!dict)
    {
        if (err_code)
            *err_code = AIV_NO_MEM;
        return NULL;
    }
    memset(dict, 0, sizeof(aiv_dict_t));

    dict->hash_map_size = hash_map_size;

    dict->hash_map = malloc(sizeof(aiv_dict_item_t *) * dict->hash_map_size);
    if (!dict->hash_map)
    {
        if (err_code)
            *err_code = AIV_NO_MEM;
        free(dict);
        return NULL;
    }

    // clear the hash map
    memset(dict->hash_map, 0, sizeof(aiv_dict_item_t *) * dict->hash_map_size);

    return dict;
}

int aiv_dict_add(aiv_dict_t *dict, void *key, unsigned int key_len, void *data)
{
    unsigned int hash = djb33x_hash(key, key_len) % (dict->hash_map_size - 1);

    // fprintf(stdout, "hash of %.*s = %u\n", key_len, key, hash);

    if (!dict->hash_map[hash])
    {
        dict->hash_map[hash] = malloc(sizeof(aiv_dict_item_t));
        if (!dict->hash_map[hash])
        {
            return AIV_NO_MEM;
        }
        memset(dict->hash_map[hash], 0, sizeof(aiv_dict_item_t));
        // fprintf(stdout, "created new hash record at %p\n", dict->hash_map[hash]);
        void *key_copy = malloc(key_len);
        if (!key_copy)
        {
            free(dict->hash_map[hash]);
            dict->hash_map[hash] = NULL;
            return AIV_NO_MEM;
        }
        memcpy(key_copy, key, key_len);
        dict->hash_map[hash]->key = key_copy;
        dict->hash_map[hash]->key_len = key_len;
        dict->hash_map[hash]->data = data;
        dict->count++;
        return 0;
    }
    else
    {
        /*if (dict->current_cost > XXX)
        {
            // resize hashmap
        }*/
        aiv_dict_item_t *item = dict->hash_map[hash];
        aiv_dict_item_t *old_item = NULL;
        while (item)
        {
            old_item = item;
            if (key_len == item->key_len && !memcmp(item->key, key, key_len))
            {
                item->data = data;
                return AIV_OK;
            }
            item = item->next;
        }
        // now old_item points to the last element in the hash_map record
        aiv_dict_item_t *new_item = malloc(sizeof(aiv_dict_item_t));
        if (!new_item)
        {
            return AIV_NO_MEM;
        }
        memset(new_item, 0, sizeof(aiv_dict_item_t));
        // fprintf(stdout, "created new hash record at %p after %p\n", new_item, old_item);
        void *key_copy = malloc(key_len);
        if (!key_copy)
        {
            free(new_item);
            return AIV_NO_MEM;
        }
        memcpy(key_copy, key, key_len);
        new_item->key = key_copy;
        new_item->key_len = key_len;
        new_item->data = data;

        old_item->next = new_item;
        new_item->prev = old_item;
        dict->count++;

        return AIV_OK;
    }

    return 0;
}

void *aiv_dict_get(aiv_dict_t *dict, void *key, unsigned int key_len)
{
    unsigned int hash = djb33x_hash(key, key_len) % (dict->hash_map_size - 1);
    aiv_dict_item_t *item = dict->hash_map[hash];

    unsigned int cost = 0;

    while (item)
    {
        cost++;
        if (key_len == item->key_len && !memcmp(item->key, key, key_len))
        {
            if (cost > dict->current_cost)
                dict->current_cost = cost;
            return item->data;
        }
        item = item->next;
    }

    return NULL;
}

void aiv_dict_destroy(aiv_dict_t *dict)
{
    for(int i = 0; i < dict->hash_map_size; i++)
    {
        aiv_dict_item_t *item = dict->hash_map[i];
        
        while(item)
        {
            free(item->key);
            aiv_dict_item_t *prev_item = item;
            item = item->next;
            free(prev_item);
        }
    }

    free(dict);
}

void *aiv_dict_remove(aiv_dict_t *dict, void *key, unsigned int key_len)
{
    unsigned int hash = djb33x_hash(key, key_len) % (dict->hash_map_size - 1);
    aiv_dict_item_t **head = &dict->hash_map[hash];
    aiv_dict_item_t *item  = *head;
    while(item)
    {
        if(key_len == item->key_len && !memcmp(item->key, key, key_len))
        {
            if(item->prev)
                item->prev->next = item->next;

            if(item->next)
                item->next->prev = item->prev;

            void *result = item->data;

            if(item == *head)
                *head = item->next; 

            free(item->key);
            free(item);
            dict->count--;
            return result;
        }   
        item = item->next;
    }

    return NULL;
}

int aiv_dict_len(aiv_dict_t *dict)
{
    return dict->count;
}

void aiv_dict_iterator_init(aiv_dict_iterator_t *iterator, aiv_dict_t *dict)
{
    iterator->dict = dict;
    iterator->record_context = dict->hash_map[0];
    iterator->map_context = 0;
    iterator->current_key = NULL;
}

int aiv_dict_iterator_move_next(aiv_dict_iterator_t *iterator)
{
    while(!iterator->record_context)
    {
        if(iterator->map_context < iterator->dict->hash_map_size - 1)
            iterator->record_context = iterator->dict->hash_map[++iterator->map_context];
        else
            return -1;
    }
    
    iterator->current_key = iterator->record_context->key;

    iterator->record_context = iterator->record_context->next;

    return 0;
}

void *aiv_dict_iterator_get_current_key(aiv_dict_iterator_t *iterator)
{
    return iterator->current_key;
}

/*aiv_list_t *aiv_dict_keys_to_aiv_list(aiv_dict_t *dict)
{
    aiv_list_t *list = aiv_list_new(NULL);

    if(!list)
        return NULL;

    aiv_dict_iterator_t iter;
    aiv_dict_iterator_init(&iter, dict);

    int ret = 0;

    while(!aiv_dict_iterator_move_next(&iter))
    {
        ret = aiv_list_append(list, aiv_dict_iterator_get_current_key(&iter));
        if(ret)
        {
            aiv_list_destroy(list);
            return NULL;
        }
    }

    return list;
}*/






