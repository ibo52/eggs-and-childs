#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "TCPClient.h"

TCPClient* tcp_client__new(int addr, int port){
	TCPClient* self=calloc(1, sizeof(TCPClient));
	
	self->recv_buff=sock_util__alloc_buffer(1024);
	self->send_buff=sock_util__alloc_buffer(1024);
	
	//initialize object
	//open server socket
	if ( (self->server_fd=socket(AF_INET, SOCK_STREAM, 0))<0){
        perror("socket could not intialized");
        exit(errno);
    }
    
	self->server.sin_family = AF_INET;
    self->server.sin_port   = htons(port);
    self->server.sin_addr.s_addr = htonl(addr);
	
	return self;
}

void tcp_client__destroy(TCPClient** self){
	sock_util__dealloc_buffer( &( (*self)->recv_buff) );
	sock_util__dealloc_buffer( &( (*self)->send_buff ) );
	
	free( (*self) );
	self=NULL;
	printf("Client object destructed\n");
}

void tcp_client__start(TCPClient* self){
	//connect to server
	if( connect(self->server_fd, (struct sockaddr*)&self->server, sizeof(self->server))<0 ){
        perror("Socket could not connect to server struct");
        exit(errno);
    }
    
    int i;
	for(i=0; i<1; i++){
		int /*recv_size=0,*/ send_size=0;
		strcpy((char* )self->send_buff->buffer,"hello from client");

		send_size=sock_util__send(self->server_fd, self->send_buff, strlen((char*)self->send_buff->buffer) );
		
    	fprintf(stdout,"sent:%i bytes of %s\n", send_size, self->send_buff->buffer);
    	
    	sock_util__receive(self->server_fd, self->recv_buff, self->recv_buff->size);
    	fprintf(stdout,"incoming from server: %s\n", self->recv_buff->buffer);
	}
	
	close(self->server_fd);
}

// Driver Program
int main (int argc, char** argv){
	TCPClient* cli=tcp_client__new(INADDR_LOOPBACK, TCP_PORT);
	tcp_client__start(cli);
	
	tcp_client__destroy(&cli);
	return 0;
}

