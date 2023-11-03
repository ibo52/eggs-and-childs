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

static void start(UDPServer* self){

	dataBuffer recvd=sock_util__receive__socket(self->super);
	printf("Received (%i bytes) message: %s\n", recvd.size, self->super->recv_buff->buffer);
	
	strcpy((char*)self->super->send_buff->buffer, (char*)self->super->recv_buff->buffer);
	strcat((char*)self->super->send_buff->buffer, "ACKNOWLEDGED.");
	
	dataBuffer sent=sock_util__send__socket(self->super);
	printf("Sent (%i bytes) message: %s\n", sent.size, self->super->recv_buff->buffer);
	
	/*
   int addr=client.sin_addr.s_addr;
   printf("Received message %s from domain %s port %d internet\
 address %i.%i.%i.%i\n",
       self->super->recv_buff->buffer,
       (client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
       ntohs(client.sin_port),
       (addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);*/
	
}

//Driver program
int main(int argc, char** argv){
	UDPServer* server=udp_server__new(INADDR_ANY, UDP_PORT);
	
	printf("UDP Server started. Waiting for a connection.\n");
	
	start(server);
	
	udp_server__destroy(&server);
	
	return 0;
}

