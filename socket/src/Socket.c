#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>

#include<stdint.h>
#include "Socket.h"

Socket* socket__new(int addr, int port, int type){
	Socket* self=calloc(1, sizeof(Socket));
	
	//self->vtable=&vtable_server;
	
	//initialize socket
	//open server socket file
	
	switch( type ){
		case CONN_TYPE_UDP_SERVER:
		case CONN_TYPE_UDP_CLIENT:
			if ( (self->fd=socket(AF_INET, SOCK_DGRAM, 0))<0){
				perror("datagram socket could not intialized");
				exit(errno);
			}
			break;
			
		case CONN_TYPE_TCP_SERVER:
		case CONN_TYPE_TCP_CLIENT:
			if ( (self->fd=socket(AF_INET, SOCK_STREAM, 0))<0){
				perror("stream socket could not intialized");
				exit(errno);
			}
			break;
			
		default:
			errno=EINVAL;
			perror("wrong parameter for connection type(udp and tcp are supported)");
	}
	
	switch (type){
		case CONN_TYPE_UDP_CLIENT:
			if ( connect(self->fd, (struct sockaddr*)&self->socket, sizeof(self->socket))<0){
				perror("datagram socket could not connect");
				exit(errno);
			}
			break;
			
		case CONN_TYPE_TCP_CLIENT:
			if ( connect(self->fd, (struct sockaddr*)&self->socket, sizeof(self->socket)) <0){
				perror("stream socket could not connect");
				exit(errno);
			}
			break;
			
		default:
			break;
	}
    
	/* Set up the server name */
	self->socket.sin_family      = AF_INET;            /* Internet Domain    */
	self->socket.sin_port        = htons(port);               /* Server Port        */
	self->socket.sin_addr.s_addr = htonl(addr); 		  /* Server's Address   */
	
	self->recv_buff=sock_util__alloc_buffer(1024);
	self->send_buff=sock_util__alloc_buffer(1024);
    
    //bind server to network interface
    if( type==CONN_TYPE_UDP_SERVER || type==CONN_TYPE_TCP_SERVER){
		int bind_retval=bind(self->fd, (struct sockaddr*)&(self->socket), sizeof(self->socket));
		if( bind_retval<0 ){
		    perror("Socket could not bind to server struct");
		    exit(errno);
		}
	}
	return self;
}

void socket__destroy(Socket** self){
	sock_util__dealloc_buffer( &( (*self)->recv_buff ) );
	sock_util__dealloc_buffer( &( (*self)->send_buff ) );
	
	close((*self)->fd);
	
	free( (*self) );
	(*self)=NULL;
	printf("Socket object destructed\n");
}
