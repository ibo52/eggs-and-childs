#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#include "PacketMonitor.h"
#include "socket-util.h"

int main(int argc, char** argv){

    PacketMonitor* p=packet_monitor__new();
    
    int seq[11]={ 3,2,1,4,7,5,9,6,8, 10, 11};
    char datum[11]={'l','e','H','l','W','o','r',' ','o','l','d'};

    for (int i = 0; i < 11; i++)
    {
        printf("%i'th arrived: %i\n---------------------------------------\n",i+1, seq[i]);
        
        dataBuffer* rtp=sock_util__alloc_buffer(sizeof(RTP)+1);

        ((RTP*)rtp->buffer)->sequence_number=seq[i];
        *(int8_t*)(rtp->buffer+16)=datum[i];

        printf("before arrange: ");
        LinkedListClass.print(p->store);

        rearrange_incoming_rtp_packet(p->store, rtp );

        printf("after arrange: ");
        LinkedListClass.print(p->store);
        printf("---------------------------------------\n");
    }
    
    Node* n=p->store->head;
    printf("___data built from rtp packet___:");
    for(int i=0; i< p->store->size; i++){
        
        printf("%c", *(char*)(n->data_ptr+16));

        n=n->next;
    }printf("\n");

    packet_monitor__destroy(&p);
}