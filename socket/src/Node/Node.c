#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

Node* new__node(void){
    Node * self=calloc(1, sizeof(Node));
    return self;
}

void node__destroy(Node** self){

    free( (*self)->data_ptr );
    free( (*self) );
    *(self)=NULL;
}

Node* node__get_next(Node* self){
    
    return self->next;
}

Node* node__get_prev(Node* self){

    return self->previous;
}

int8_t node__has_prev(Node* self){
    
    if (self->previous){
        return 1;
    }

    return 0;
}

int8_t node__has_next(Node* self){
    
    if (self->next){
        return 1;
    }

    return 0;
}

void node__set_next(Node* self, Node* n){
    self->next=n;
}

void node__set_prev(Node* self, Node* n){
    self->previous=n;
}