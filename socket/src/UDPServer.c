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
	
	return self;
}

void udp_server__destroy(UDPServer** self){

	socket__destroy( &( (*self)->super ) );
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("UDPServer object destructed\n");
}

void udp_server__start(UDPServer* self){

	struct sockaddr_in client;
	socklen_t client_address_size = sizeof(client);

   if(recvfrom(self->super->fd, self->super->recv_buff->buffer, self->super->recv_buff->size, 0, (struct sockaddr *) &client, &client_address_size) <0){
       perror("recvfrom()");
       exit(4);
   }
   
   int addr=client.sin_addr.s_addr;
   printf("Received message %s from domain %s port %d internet\
 address %i.%i.%i.%i\n",
       self->super->recv_buff->buffer,
       (client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
       ntohs(client.sin_port),
       (addr>>24&0xff), (addr>>16&0xff), (addr>>8&0xff), addr&0xff);
	
}
