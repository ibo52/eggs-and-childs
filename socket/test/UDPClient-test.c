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

static void start(UDPClient* self){
	
	strcpy((char *)self->super->send_buff->buffer, "Hello from UDP client.");

   /* Send the message in buf to the server */
   dataBuffer sent=sock_util__send__socket(self->super);
	printf("Sent (%i bytes) message: %s\n", sent.size, self->super->send_buff->buffer);
   
   //wait for a message from server
   dataBuffer recvd=sock_util__receive__socket(self->super);
   printf("Received (%i bytes) message: %s\n", recvd.size, self->super->recv_buff->buffer);
}

int main(int argc, char** argv){
	
	UDPClient* requester=udp_client__new(INADDR_ANY, UDP_PORT);
    printf("UDP Client starting to send message to the connection.\n");
	
	start(requester);
   
   udp_client__destroy(&requester);
   
   return 0;
}

