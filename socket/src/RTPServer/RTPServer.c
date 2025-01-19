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
	
	self->vtable=&UDPServerClass;
	
	return self;
}

void rtp_server__destroy(RTPServer** self){

	udp_server__destroy( &( (*self)->super ) );
	rtp__destroy( &((*self)->rtp_header) );
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("RTPServer object destructed\n");
}

dataBuffer rtp_server__recv(RTPServer* self){
	return socket__receive(self->super->super);
}

dataBuffer rtp_server__sendRTP(RTPServer* self, Socket* toSocket){
	return rtp__send(self->rtp_header, toSocket);
}

dataBuffer rtp_server__send(Socket* toSocket){
	return socket__send(toSocket);
}

void rtp_server__start(RTPServer* self){
}
/*
dataBuffer rtp_server__recv(RTPServer* self){

	dataBuffer recvd= socket__receive(self->super->super);

	//parse info of client to communicate with socket
	Socket client={ self->super->super->fd, *(struct sockaddr_in *)recvd.buffer, self->super->super->recv_buff, self->super->super->send_buff };


}*/