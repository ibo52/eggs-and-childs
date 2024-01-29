#ifndef HALO_NODE
#define HALO_NODE

#include<stdint.h>

/**
 * Node structure to store data in linked lists
*/
typedef struct __Node Node;
typedef struct __Node_VTable Node_VTable;


struct __Node
{
    Node* next;
    Node* previous;
    void *data_ptr;     //void pointer to point any type of element
};

/**
 * Virtual methods table to access functions easily
 * through object
*/
struct __Node_VTable{
    Node* (*new)(void);
    void (*destroy)(Node** self);

    void (*setNext)(Node* self, Node* n);
    void (*setPrev)(Node* self, Node* n);

    Node* (*getNext)(Node* self);
    Node* (*getPrev)(Node* self);

    int8_t (*hasNext)(Node* self);
    int8_t (*hasPrev)(Node* self);
};

/**
 * Store new reference of Node structure on mem
*/
Node* new__node(void);

void node__set_next(Node* self, Node* n);

void node__set_prev(Node* self, Node* n);

Node* node__get_next(Node* self);

Node* node__get_prev(Node* self);

int8_t node__has_next(Node* self);

int8_t node__has_prev(Node* self);

/**
 * Clears itself from mem.
*/
void node__destroy(Node** self);


const static Node_VTable NodeClass={
    .new=new__node,
    .destroy=node__destroy,
    .getNext=node__get_next,
    .getPrev=node__get_prev,
    .setNext=node__set_next,
    .setPrev=node__set_prev,
    
    .hasNext=node__has_next,
    .hasPrev=node__has_prev
    };

#endif