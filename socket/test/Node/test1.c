#include<stdio.h>
#include "Node.h"
#include "LinkedList.h"

int main(int argc, char** argv){

    printf("Node Class test\n");
    Node* n=NodeClass.new();

    printf("has next? %s\n",NodeClass.hasNext(n)? "yes":"no");
    printf("has prev? %s\n",NodeClass.hasPrev(n)? "yes":"no");

    NodeClass.destroy(&n);

    LinkedList* ll=LinkedListClass.new();

    printf("print linkedlist elements");
    LinkedListClass.print(ll);

    LinkedListClass.destroy(&ll);

    return 0;
}