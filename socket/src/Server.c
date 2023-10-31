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
#include "Server.h"

Server* server__new(int addr, int port, int type){
	Server* self=calloc(1, sizeof(Server));
	
	//self->vtable=&vtable_server;
	
	//initialize socket
	//open server socket file
	
	switch( type ){
		case CONN_TYPE_UDP:
			if ( (self->server_fd=socket(AF_INET, SOCK_DGRAM, 0))<0){
				perror("datagram socket could not intialized");
				exit(errno);
			}
			break;
			
		case CONN_TYPE_TCP:
			if ( (self->server_fd=socket(AF_INET, SOCK_STREAM, 0))<0){
				perror("stream socket could not intialized");
				exit(errno);
			}
			break;
			
		default:
			errno=EINVAL;
			perror("wrong parameter for connection type(udp and tcp are supported)");
	}

    printf("Server socket initialized on fd:%i\n", self->server_fd);
    
	/* Set up the server name */
	self->server.sin_family      = AF_INET;            /* Internet Domain    */
	self->server.sin_port        = htons(port);               /* Server Port        */
	self->server.sin_addr.s_addr = htonl(addr); 		  /* Server's Address   */
	
	self->recv_buff=sock_util__alloc_buffer(1024);
	self->send_buff=sock_util__alloc_buffer(1024);
    
    //bind server to network interface
    int bind_retval=bind(self->server_fd, (struct sockaddr*)&(self->server), sizeof(self->server));
    if( bind_retval<0 ){
        perror("Socket could not bind to server struct");
        exit(errno);
    }
    printf("TCPServer bind val:%i\n", bind_retval);

	return self;
}

void server__destroy(Server** self){
	sock_util__dealloc_buffer( &( (*self)->recv_buff ) );
	sock_util__dealloc_buffer( &( (*self)->send_buff ) );
	
	close((*self)->server_fd);
	
	free( (*self) );
	(*self)=NULL;
	printf("Server object destructed\n");
}
