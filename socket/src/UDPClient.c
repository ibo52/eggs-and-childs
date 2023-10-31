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

#include "socket-util.h"
#include "UDPClient.h"


UDPClient* udp_client__new(int address, int port){
	UDPClient* self=calloc(1, sizeof(UDPClient));
	
	self->recv_buff=sock_util__alloc_buffer(1024);
	self->send_buff=sock_util__alloc_buffer(1024);
	
	/* Create a datagram socket in the internet domain and use the
    * default protocol (UDP).
    */
   if ((self->server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket fd could not bound");
       exit(self->server_fd);
   }
   
   /* Set up the server name */
   self->server.sin_family      = AF_INET;            /* Internet Domain    */
   self->server.sin_port        = htons(port);               /* Server Port        */
   self->server.sin_addr.s_addr = htonl(address); /* Server's Address   */
	
	return self;
}

void udp_client__destroy(UDPClient** self){

	sock_util__dealloc_buffer( &( (*self)->recv_buff ) );
	sock_util__dealloc_buffer( &( (*self)->send_buff ) );	
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("UDPClient object destructed\n");
}
