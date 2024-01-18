/*
*	UDP client for data requesting
*/
#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "UDPClient.h"


UDPClient* udp_client__new(int address, int port){

	Socket* super = socket__new(address, port, CONN_TYPE_UDP_CLIENT );
	
	UDPClient* self=calloc(1, sizeof(UDPClient));
	
	self->super=super;
	
	self->vtable=&UDPClient_VTable__default;
	return self;
}

void udp_client__destroy(UDPClient** self){

	socket__destroy( &((*self)->super) );	
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("UDPClient object destructed\n");
}
