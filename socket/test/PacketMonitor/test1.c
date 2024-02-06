#include "PacketMonitor.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){

    PacketMonitor* p=packet_monitor__new();
    
    int seq[10]={ 3,2,1,4,7,5,9,6,8, 10};
    for (int i = 0; i < 10; i++)
    {
        printf("%i'th arrived: %i\n---------------------------------------\n",i+1, seq[i]);
        
        RTP* rtp=rtp__new();
        rtp->sequence_number=seq[i];
        
        printf("before arrange: ");
        LinkedListClass.print(p->store);

        rearrange_incoming_rtp_packet(p->store, rtp );

        printf("after arrange: ");
        LinkedListClass.print(p->store);
        printf("---------------------------------------\n");
    }
    
    packet_monitor__destroy(&p);
}