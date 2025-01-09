#include<stdio.h>
#include<stdlib.h>
#include "LinkedList.h"

void ll__print(LinkedList* self){

    if(LinkedListClass.isEmpty(self))
        return;

    Node* temp=self->head;
    
    int c=0;

    while ( temp ){
        printf("%s~",((char* )temp->data_ptr));

        if (++c %10 ==0){
            printf("\n");
        }

        temp=NodeClass.getNext(temp);
        
    }
    
    printf("\n");
    
}

int main(int argc, char** argv){


    printf("test2 for linkedlist\n");

    Node* temp=new__node();
    temp->data_ptr=calloc(8,sizeof(char));
    sprintf(temp->data_ptr,"deneme0");

    LinkedList* l=new__linked_list();

    printf("\thead data is %s\n",(char*)LinkedListClass.getHead(l).data_ptr);
    printf("\ttail data is %s\n\n",(char*)LinkedListClass.getTail(l).data_ptr);
    ll__print(l);

    LinkedListClass.append(l, temp);
    printf("Added 1 node to list\n");
    printf("\thead data is %s\n",(char*)l->head->data_ptr);
    printf("\ttail data is %s\n\n",(char*)l->tail->data_ptr);
    ll__print(l);
    printf("element size of LinkedList:%i\n\n",l->size);


    for(int i=1; i<9; i++){
        temp=new__node();
        temp->data_ptr=calloc(8,sizeof(char));
        sprintf(temp->data_ptr,"deneme%i", i);
        LinkedListClass.append(l, temp);
    }
    printf("Added multiple nodes(8) to list\n");
    printf("\thead data is %s\n",(char*)l->head->data_ptr);
    printf("\ttail data is %s\n\n",(char*)l->tail->data_ptr);
    ll__print(l);
    printf("element size of LinkedList:%i\n\n",l->size);

    Node popped=LinkedListClass.pop(l);
    printf("popped tail Node:%s. Remaining size of LinkedList:%i\n\n",(char*)popped.data_ptr, l->size);
    free( popped.data_ptr );

    Node pop4Node=linked_list__pop(l, 4);
    printf("popped 4. Node:%s. Remaining size of LinkedList:%i\n\n",(char*)pop4Node.data_ptr, l->size);
    free(pop4Node.data_ptr);

    Node pop54Node=linked_list__pop(l, 54);
    printf("popped 54. Node:%s. Remaining size of LinkedList:%i\n\n",(char*)pop54Node.data_ptr, l->size);
    free(pop54Node.data_ptr);

    Node head=linked_list__pop_first(l);
    printf("popped head Node:%s. Remaining size of LinkedList:%i\n",(char*)head.data_ptr, l->size);
    free(head.data_ptr);
    
    LinkedListClass.destroy(&l);
    printf("LinkedList Destroyed. Pointer is %s\n\n",l==NULL? "null":"not null");
    
    Node n1=LinkedListClass.pop(l);
    printf("pull Node from NULL LinkedList:%s remaining:\n\n",(char*)n1.data_ptr);

    return 0;
}