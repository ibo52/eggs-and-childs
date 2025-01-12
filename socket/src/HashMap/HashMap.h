#ifndef HALO__HASHMAP
#define HALO__HASHMAP

#include "Node.h"

typedef struct __HashMap
{
    Node** map;
    int32_t size;
    int8_t TABLE_SIZE;
}HashMap;

HashMap* hashmap__new(int table_size);

void hashmap__destroy(HashMap** self);

HashMap* hashmap__put(HashMap* self, const char* key, void* value);

void* hashmap__get(HashMap* self, const char* key);

#endif