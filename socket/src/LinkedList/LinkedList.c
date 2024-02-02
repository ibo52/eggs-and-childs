#include <stdlib.h>
#include "LinkedList.h"
#include <stdio.h>

LinkedList* new__linked_list(void){
    LinkedList * self=calloc(1, sizeof(LinkedList));
    //all values are null at first

    self->vtable=&LinkedListClass;
    return self;
}

void linked_list__destroy(LinkedList** self){

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

void linked_list__append(LinkedList* self, Node* n){

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

void linked_list__append_index(LinkedList* self, Node* n, int index){

    Node* temp=self->head;

    for (int32_t i = 0; i < index; i++){

        if ( temp && temp->next ){
            
            temp=temp->next;
        }else{
            
            linked_list__append(self, n);//if index> len(list); just add to the last
            return;
        }
    }

    /*if the node being popped is between any two nodes
        concat that nodes to each other before popping
    */
   printf("ll append index: temp is %s\n", temp? "not NULL":"NULL");
   
    if(temp->previous){

        temp->previous->next=n;
        n->previous=temp->previous;

    }else{//temp do not have previous(it is head)
        self->head=n;
    }
    n->next=temp;
    temp->previous=n;

    self->size++;
}

Node linked_list__pop(LinkedList* self, int index){

    Node* temp=self->head;
    Node n={0,0,0};

    for (int32_t i = 1;self && i < index; i++){

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

Node linked_list__pop_last(LinkedList* self){
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

Node linked_list__pop_first(LinkedList* self){
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

Node linked_list__get_head(LinkedList* self){
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

Node linked_list__get_tail(LinkedList* self){
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
#include "RTP.h"
void linked_list__print(LinkedList* self){

    if(LinkedListClass.isEmpty(self))
        return;

    Node* temp=self->head;
    
    int c=0;

    while ( temp ){
        printf("%i~",((RTP* )temp->data_ptr)->sequence_number);

        if (++c %10 ==0){
            printf("\n");
        }

        temp=NodeClass.getNext(temp);
        
    }
    
    printf("\n");
    
}

int8_t linked_list__is_empty(LinkedList* self){
    if ( !self->head )//if no head element
        return 1;
    
    return 0;
}

