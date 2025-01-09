/*	Halil Ibrahim MUT
*
*		RTP client based UDP for data requesting
*/
#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "RTPClient.h"
#include "PacketMonitor.h"

RTPClient* rtp_client__new(int address, int port){
	
	RTPClient* self=calloc(1, sizeof(RTPClient));
	
	self->super=udp_client__new(address, port);
	self->rtp_header=rtp__new();
	self->rtp_header->ssrc=address;	//Synchronization source identiﬁer uniquely identiﬁes the source of a stream
	
	self->vtable=&UDPClient_VTable__default;
	return self;
}

void rtp_client__destroy(RTPClient** self){

	udp_client__destroy( &((*self)->super) );	
	rtp__destroy( &((*self)->rtp_header) );
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("RTPClient object destructed\n");
}

dataBuffer rtp_client__recv(RTPClient* self){
	return socket__receive(self->super->super);
}

dataBuffer rtp_client__send(RTPClient* self){
	return socket__send(self->super->super);
}

/*Thread to isten for messages*/
void rtp_client__listener(RTPClient* self, LinkedList* ll){
   
   int done=0;
   while ( !done ){

      dataBuffer cli=socket__receive(self->super->super);
      free(cli.buffer);
      
      //if sock close signal reaces
      if ( strncmp( sock_util__buffer_get(self->super->super->recv_buff), "SOCK_CLOSE_REQUEST", 18)==0 )
      {
         printf("[REMOTE]:socket close request\n");
         done=1;
         break;
      
      }else{
      
         //copy incoming rtp data to sesrver rtp_header
         memcpy(self->rtp_header, (RTP*)self->super->super->recv_buff->buffer, sizeof(RTP));

         //copy incoming packet on another mem area
         dataBuffer* data=sock_util__alloc_buffer(self->super->super->recv_buff->size);
         memcpy(data->buffer, self->super->super->recv_buff->buffer, data->max_size);
         data->size=data->max_size;

         PacketMonitorClass.rearrangeIncomingRTP(ll, data);
         free(data);
         
         printf("recv size:%i rtp seq num %u |incoming: %x%x\n", self->super->super->recv_buff->size,
         self->rtp_header->sequence_number,
         *(int8_t* )(self->super->super->recv_buff->buffer+16),
         *(int8_t* )(self->super->super->recv_buff->buffer+17));
      
      }
   }
}
