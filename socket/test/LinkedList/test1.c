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


    printf("test for linkedlist\n");
    char **s=calloc(10,sizeof(char*));
    for (int i = 0; i < 10; i++)
    {
        s[i]=calloc(8,sizeof(char));
        sprintf(s[i], "deneme%i",i);
        /* code */
    }


    LinkedList* l=new__linked_list();

    for (int16_t i = 0; i < 10; i++)
    {
        Node* n=new__node();
        n->data_ptr=s[i];

        l->vtable->append(l, n);
    }

    printf("element size of LinkedList:%i\n",l->size);
    ll__print(l);

    Node popped=l->vtable->pop(l);

    printf("popped node data:%s\n",(char*)popped.data_ptr);
    free( popped.data_ptr );

    Node pop2=linked_list__pop(l, 4);
    printf("popped 4. Node:%s\n",(char*)pop2.data_ptr);
    free(pop2.data_ptr);

    Node head=linked_list__pop_first(l);
    printf("popped head Node:%s\n",(char*)head.data_ptr);
    free(head.data_ptr);

    printf("\nelement size of LinkedList after popping:%i\n",l->size);
    ll__print(l);

    l->vtable->destroy(&l);
    free(s);
    
    printf("linked list is %s after destroy call\n",l==NULL? "null":"not null");
    
    return 0;
}