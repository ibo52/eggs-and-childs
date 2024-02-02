#ifndef HALO_LINKEDLIST
#define HALO_LINKEDLIST

#include<stdint.h>
#include "Node.h"

typedef struct __LinkedList LinkedList;
typedef struct __LinkedList_VTable LinkedList_VTable;

/**
 * Linked list structure
*/
struct __LinkedList{
    Node *head;
    Node *tail;
    int32_t size;       //total size of the elements

    const LinkedList_VTable* vtable;//virtual methods table(No need since there is OOP-static class )
};

/**
 * Virtual methods table to access functions easily
 * through object
*/
struct __LinkedList_VTable{
    LinkedList* (*new)(void);
    void (*destroy)(LinkedList** self);

    void (*append)(LinkedList* self, Node* n);
    void (*push)(LinkedList* self, Node* n);

    Node (*pop)(LinkedList* self);
    Node (*popFirst)(LinkedList* self);
    Node (*popLast)(LinkedList* self);
    //Node (*remove)(LinkedList* self);

    Node (*getHead)(LinkedList* self);
    Node (*getTail)(LinkedList* self);

    void (*print)(LinkedList* self);

    int8_t (*isEmpty)(LinkedList* self);
};

/**
 * Store new reference of linked list structure on mem
*/
LinkedList* new__linked_list(void);

/**
 * Clears all Nodes inside linked list,
 * then clears itself.
*/
void linked_list__destroy(LinkedList** self);

/**
 * Append desired element to end of the list
*/
void linked_list__append(LinkedList* self, Node* n);

/**
 * Add desired element to the given index.

 * concat current element at index to next of Node
 * 'n' if there is an element at that index.

 * append the Node 'n' to the tail if there is
 * no such an index(as well as element)
 * 
 * @param n: Node to be appended to the given index
 * @param index: index to be appended
*/
void linked_list__append_index(LinkedList* self, Node* n, int index);
/**
 * remove and return last element from the list
 * NOTE: the data_ptr member of the popped Node have to
 * be free'd manually after done the operations on data_ptr
 * --> free( node.data_ptr );
 * 
*/
Node linked_list__pop_last(LinkedList* self);

/**
 * remove and return first element from the list
 * NOTE: the data_ptr member of the popped Node have to
 * be free'd manually after done the operations on data_ptr
 * --> free( node.data_ptr );
 * 
*/
Node linked_list__pop_first(LinkedList* self);

/**
 * if there is one, pop the Node at given index
 * NOTE: the data_ptr member of the popped Node have to
 * be free'd manually after done the operations on data_ptr
 * --> free( node.data_ptr );
*/
Node linked_list__pop(LinkedList* self, int index);

Node linked_list__get_head(LinkedList* self);

Node linked_list__get_tail(LinkedList* self);

/**
 * Print eleements
*/
void linked_list__print(LinkedList* self);

int8_t linked_list__is_empty(LinkedList* self);

/**
 * Default static virtual method table for all Linked Lists
*/
const static LinkedList_VTable LinkedListClass={
    .new=new__linked_list,
    .destroy=linked_list__destroy,

    .append=linked_list__append,
    .push=linked_list__append,
    //.remove=linked_list__pop_last,
    .pop=linked_list__pop_last,
    .popFirst=linked_list__pop_first,
    .popLast=linked_list__pop_last,
    
    .getHead=linked_list__get_head,
    .getTail=linked_list__get_tail,

    .print=linked_list__print,

    .isEmpty=linked_list__is_empty
    };

#endif