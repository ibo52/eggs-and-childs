#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "TCPClient.h"
#include "Socket.h"

TCPClient* tcp_client__new(int addr, int port){

	Socket* super = socket__new(addr, port, CONN_TYPE_TCP_CLIENT );
	
	TCPClient* self=calloc(1, sizeof(TCPClient));
	
	self->super=super;
	
	self->vtable=&TCPClient_VTable__default;
	return self;
}

void tcp_client__destroy(TCPClient** self){

	socket__destroy( &((*self)->super) );
	
	free( (*self) );
	self=NULL;
	printf("Client object destructed\n");
}

void tcp_client__start(TCPClient* self){
}
