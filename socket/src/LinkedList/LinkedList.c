#include <stdlib.h>
#include "LinkedList.h"
#include <stdio.h>

LinkedList* new__LinkedList(void){
    LinkedList * self=calloc(1, sizeof(LinkedList));
    //all values are null at first

    self->vtable=&LinkedListClass;
    return self;
}

void LinkedList__destroy(LinkedList** self){

    Node *temp=(*self)->head;
    for (int i=0; i < (*self)->size; i++){
        
        //hold next node to avoid losing the reference to it
        Node* next=temp->next;

        //clear from mem
        node__destroy(&temp);

        //continue from next reference
        temp=next;

    }

    free( *self );
    *self=NULL;
    
}

void LinkedList__append(LinkedList* self, Node* n){

    /*if there is tail elmnt (head and tail are points same loc if linked list newly initialized )
        bind node 'n' to next of tail;
    else
        set node 'n' as first element(head)
    */
    if ( self->tail ){
        self->tail->next=n;
        n->previous=self->tail;

        self->tail=n;

        self->size++;
    
    }else{
        self->head=n;
        self->size=1;

        /*tail points to head when there is only one element.
        Thus, when append any second element, the if clause above will run
        */
        self->tail=self->head;
    }

}

Node LinkedList__pop(LinkedList* self, int index){

    Node* temp=self->head;
    Node n={0,0,0};

    for (int32_t i = 1; i < index; i++){

        if (temp!=NULL){
            temp=temp->next;
        }else{
            return n;
        }
    }

    n=*temp;

    /*if the node being popped is between any two nodes
        concat that nodes to each other before popping
    */
    if(temp->next && temp->previous){
        
        temp->next->previous=temp->previous;
        temp->previous->next=temp->next;
    }

    free(temp);
    self->size--;

    return n;
}

Node LinkedList__popLast(LinkedList* self){
    Node n={0,0,0};

    if (self){//if not null

        /*if there is at least one element
        1.copy head element to a stack variable
        2.if head has next node
            a.remove the pointer to new node of this previous node
            b. reference this previous node as new tail node of linked list
        */
        if ( self->tail ){//if there is tail element(tail!=null)
            n=*self->tail;//pop the tail node from the list

            Node* newTail=self->tail->previous;
            free( self->tail );

            if( newTail ){
                newTail->next=NULL;
                self->tail=newTail;
            }

            self->size--;
            
        }
    }

    return n;
}

Node LinkedList__popFirst(LinkedList* self){
    Node n={0,0,0};
    
    if(self){//if not null

        /*if there is at least one element:
        1.copy head element to a stack variable
        2.if head has next node
            a.remove the pointer to previous node of this next node
            b. reference this next node as new head node of linked list
        */
        if (self->head){

            n=*self->head;

            Node* newHead=self->head->next;
            free(self->head);

            if( newHead ){
                newHead->previous=NULL;
                self->head=newHead;
            }  
            self->size--;
        }
    }
    return n;
}

Node LinkedList__getHead(LinkedList* self){
    Node n={0,0,0};
    
    if(self){//if not null

        /*if there is a head element:
            return this head element
          else:
            return empty(null) Node (data pointer is null)

            NOTE: this function does not pop the head
            just returns data hold in head reference
        */
        if (self->head){

            n=*self->head;
        }
    }
    return n;
}

Node LinkedList__getTail(LinkedList* self){
    Node n={0,0,0};
    
    if(self){//if not null

        /*if there is a tail element:
            return this tail element
          else:
            return empty(null) Node (data pointer is null)
            
            NOTE: this function does not pop the tail
            just returns data hold in tail reference
        */
        if (self->tail){

            n=*self->tail;
        }
    }
    return n;
}

void LinkedList__print(LinkedList* self){

    if(!self)
        return;

    Node* temp=self->head;
    
    int c=0;
    for ( ; NodeClass.hasNext(temp); temp=NodeClass.getNext(temp)){
        printf("%s~",(char* )temp->data_ptr);

        if (++c %10 ==0){
            printf("\n");
        }
        
    }printf("\n");
    
}

