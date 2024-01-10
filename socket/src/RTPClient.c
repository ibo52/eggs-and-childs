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
