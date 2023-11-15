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
			perror("wrong parameter for connection type(UDP/TCP server/client are supported)");
	}
    
	/* Set up the server name */
	self->socket.sin_family      = AF_INET;            /* Internet Domain    */
	self->socket.sin_port        = htons(port);               /* Server Port        */
	self->socket.sin_addr.s_addr = htonl(addr); 		  /* Server's Address   */
	
	self->recv_buff=sock_util__alloc_buffer(1024);
	self->send_buff=sock_util__alloc_buffer(1024);
    
    //if it is client struct, connect client to server
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
	//if it is server struct, bind to network interface
    if( type==CONN_TYPE_UDP_SERVER || type==CONN_TYPE_TCP_SERVER){
		int bind_retval=bind(self->fd, (struct sockaddr*)&(self->socket), sizeof(self->socket));
		if( bind_retval<0 ){
		    perror("Socket could not bind to server struct");
		    exit(errno);
		}
	}
	
	
	//bind virtual function table contents
	self->vtable=&Socket_VTable__default;
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

static int min(int a, int b){
	if(a<b)
		return a;
		
	return b;
}

dataBuffer socket__send(Socket* self){
	/*
	@param self	: sender Socket to forward message to other
	@return		: Bytes sent in total
	*/
	int MAX_BYTES_PER_SEND=65536-28;//28 allocated for is udp protocol headers
	int sent_size=0;
	int length=self->send_buff->size;

	struct sockaddr_in client=self->socket;	//recvfrom will fill this struct destination socket
	socklen_t client_len=sizeof(client);
	
	while( sent_size < length ){
	
		int size;
		int per_send_len=min(MAX_BYTES_PER_SEND, length-sent_size);
		
		if( (size = sendto(self->fd, self->send_buff->buffer + sent_size, per_send_len, 0, (struct sockaddr *)&client, client_len)) <0 ){
			fprintf(stderr, "Error while sending to socket(Totally %i bytes sent): %s\n",sent_size, strerror(errno));
			exit(errno);
		}
		sent_size+=size;
	}//will break safely if equal to 0; will exit if<0
	//printf("sent %i bytes of %s\n",sent_size, (char*)self->send_buff->buffer);
	self->send_buff->size=sent_size;
	dataBuffer retData={NULL, sent_size, 0};
	return retData;
}

dataBuffer socket__receive(Socket* self){
	/*
	@param self: Socket to listen for a message receivation from others
	@return	   : Bytes received in total
	*/
	
		int recv_retval;			//total received size of message from procedure call 
		struct sockaddr_in *client=malloc(1*sizeof(struct sockaddr_in));	//recvfrom will fill this struct
		socklen_t client_address_size = sizeof(*client);
			
		if( (recv_retval= recvfrom(self->fd, self->recv_buff->buffer , self->recv_buff->max_size, 0, (struct sockaddr *)client, &client_address_size)) <0 ){
			perror("Error while receiving from socket");
			exit(recv_retval);
		
		}
		
	self->recv_buff->size=recv_retval;
	
	dataBuffer retData={client, recv_retval, 0};
	/*
	int addr=client->sin_addr.s_addr;
	
	
	printf("Receive SOCKET func:  Domain:%s address:%i.%i.%i.%i\n",(client->sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	(addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);	
	*/
	//Next implementation: If socket type==TCP; then do not malloc struct sockaddr_in *client, return NULL
	return retData;
}
