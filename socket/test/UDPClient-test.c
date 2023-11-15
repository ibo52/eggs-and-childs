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
	
	sock_util__buffer_write(self->super->send_buff, "Hello from UDP client.");

   /* Send the message in buf to the server */
   dataBuffer sent=self->vtable->send(self->super);
	printf("Sent (%i bytes) message: %s\n", sent.size, (char*)self->super->send_buff->buffer);
   
   //wait for a message from server
   dataBuffer recvd=self->vtable->receive(self->super);
   /*
   *
   */
   int addr=self->super->socket.sin_addr.s_addr;
	
	printf("Received (%i bytes) message: %s | Domain:%s address:%i.%i.%i.%i\n",recvd.size, (char*)self->super->recv_buff->buffer, (self->super->socket.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	(addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);
	free(recvd.buffer);

}

int main(int argc, char** argv){
	
	UDPClient* requester=udp_client__new(INADDR_ANY, UDP_PORT);
    printf("UDP Client starting to send message to the connection.\n");
	
	start(requester);
   
   udp_client__destroy(&requester);
   
   return 0;
}

