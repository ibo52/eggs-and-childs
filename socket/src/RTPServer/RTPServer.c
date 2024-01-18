/*	Halil Ibrahim MUT
*
*		RTP Server based UDP for data sending
*/
#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "RTPServer.h"

RTPServer* rtp_server__new(int addr, int port){
	
	RTPServer* self=calloc(1, sizeof(RTPServer));
	
	self->super=udp_server__new(addr, port);
	self->rtp_header=rtp__new();
	self->rtp_header->ssrc=addr;	//Synchronization source identiﬁer uniquely identiﬁes the source of a stream
	
	self->vtable=&UDPServer_VTable__default;
	
	return self;
}

void rtp_server__destroy(RTPServer** self){

	udp_server__destroy( &( (*self)->super ) );
	rtp__destroy( &((*self)->rtp_header) );
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("RTPServer object destructed\n");
}

void rtp_server__start(RTPServer* self){
}
