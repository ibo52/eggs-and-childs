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
};

/**
 * Store new reference of linked list structure on mem
*/
LinkedList* new__LinkedList(void);

/**
 * Clears all Nodes inside linked list,
 * then clears itself.
*/
void LinkedList__destroy(LinkedList** self);

/**
 * Append desired element to end of the list
*/
void LinkedList__append(LinkedList* self, Node* n);

/**
 * remove and return last element from the list
 * NOTE: the data_ptr member of the popped Node have to
 * be free'd manually after done the operations on data_ptr
 * --> free( node.data_ptr );
 * 
*/
Node LinkedList__popLast(LinkedList* self);

/**
 * remove and return first element from the list
 * NOTE: the data_ptr member of the popped Node have to
 * be free'd manually after done the operations on data_ptr
 * --> free( node.data_ptr );
 * 
*/
Node LinkedList__popFirst(LinkedList* self);

/**
 * if there is one, pop the Node at given index
 * NOTE: the data_ptr member of the popped Node have to
 * be free'd manually after done the operations on data_ptr
 * --> free( node.data_ptr );
*/
Node LinkedList__pop(LinkedList* self, int index);

Node LinkedList__getHead(LinkedList* self);

Node LinkedList__getTail(LinkedList* self);

/**
 * Print eleements
*/
void LinkedList__print(LinkedList* self);

/**
 * Default static virtual method table for all Linked Lists
 * 
 * Not: varsayılan statik fonksiyon isimlendirmesi Class içerecek
 * biçimde yapılsaydı daha mantıklı olrdu
 * 
 * örnegin linkedlist fonksiyonlarına erişmek için
 * LinkedList_VTable__default yerine
 * LinkedListClass yazalım
 * 
 * Bu isimlendirme daha açık olduğu için
 * Obje içinde vtable tutmaya gerek kalmaz(bence)
 * 
*/
const static LinkedList_VTable LinkedListClass={
    .destroy=LinkedList__destroy,

    .append=LinkedList__append,
    .push=LinkedList__append,
    //.remove=LinkedList__popLast,
    .pop=LinkedList__popLast,
    .popFirst=LinkedList__popFirst,
    .popLast=LinkedList__popLast,
    
    .getHead=LinkedList__getHead,
    .getTail=LinkedList__getTail,

    .print=LinkedList__print
    };

#endif