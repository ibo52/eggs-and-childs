#include "HashMap.h"
#include "stdint.h"
#include "stdlib.h"
#include <stdio.h>
// Hash function to generate an index from a key
static uint32_t hash(uint32_t table_size, const char* key) {

    uint32_t hash_value = 0;
    while (*key) {
        hash_value = (hash_value * 31) + *key++;
    }
    return hash_value % table_size;
}

HashMap* hashmap__new(int table_size){

    HashMap* self=calloc(1, sizeof(HashMap));

    self->size=0;
    self->TABLE_SIZE=table_size;

    self->map=calloc(table_size, sizeof(Node*));

    return self;
    
}

void hashmap__destroy(HashMap** self){

    /*for (uint32_t i = 0; i < ((*self)->TABLE_SIZE); i++)
    {
        printf("free %i node\n",i);
        free ( *((*self)->map +i) );
    }*/
    
printf("free node map\n");
    free ( &((*self)->map) );

printf("free self pointer\n");
    free( (*self) );

    (*self)=NULL;
}

HashMap* hashmap__put(HashMap* self, const char* key, void* value){
    
    Node* n=NodeClass.new();

    uint32_t hashIndex = hash(self->TABLE_SIZE, key);

    n->data_ptr=value;
    n->data_size=-1;

    n->next=*(self->map+hashIndex);
    *(self->map+hashIndex)=n;

    self->size++;

    return self;
}


void* hashmap__get(HashMap* self, const char* key){


    uint32_t hashIndex = hash(self->TABLE_SIZE, key);

    Node* value=*(self->map+hashIndex);

    return value;
}

/*
int main(int argc, char** argv){
    
    HashMap* m=hashmap__new(10);

    hashmap__put(m, "a", "deneme");

    Node* v=hashmap__get(m, "a");
    Node* v2=hashmap__get(m, "nonexist");

    printf("value:%s\n",v->data_ptr);

    printf("nonexist value:%s\n",v2==NULL? "NULL":"exist");

    hashmap__destroy(&m);
}*/