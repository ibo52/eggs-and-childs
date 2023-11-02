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
	
	return self;
}

void tcp_client__destroy(TCPClient** self){

	socket__destroy( &((*self)->super) );
	
	free( (*self) );
	self=NULL;
	printf("Client object destructed\n");
}

void tcp_client__start(TCPClient* self){
	//connect to server
	if( connect(self->super->fd, (struct sockaddr*)&self->super->socket, sizeof(self->super->socket))<0 ){
        perror("Socket could not connect to server struct");
        exit(errno);
    }
    
    int i;
	for(i=0; i<1; i++){
		int /*recv_size=0,*/ send_size=0;
		strcpy((char* )self->super->send_buff->buffer,"hello from client");

		send_size=sock_util__send(self->super->fd, self->super->send_buff, strlen((char*)self->super->send_buff->buffer) );
		
    	fprintf(stdout,"sent:%i bytes of %s\n", send_size, self->super->send_buff->buffer);
    	
    	sock_util__receive(self->super->fd, self->super->recv_buff, self->super->recv_buff->size);
    	fprintf(stdout,"incoming from server: %s\n", self->super->recv_buff->buffer);
	}
}
