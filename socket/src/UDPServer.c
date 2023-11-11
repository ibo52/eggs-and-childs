#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "socket-util.h"
#include "UDPServer.h"
#include "Socket.h"

UDPServer* udp_server__new(int addr, int port){

	Socket* super = socket__new(addr, port, CONN_TYPE_UDP_SERVER );
	
	UDPServer* self=calloc(1, sizeof(UDPServer));
	self->super=super;
	
	self->vtable=&UDPServer_VTable__default;
	return self;
}

void udp_server__destroy(UDPServer** self){

	socket__destroy( &( (*self)->super ) );
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("UDPServer object destructed\n");
}

void udp_server__start(UDPServer* self){
}
