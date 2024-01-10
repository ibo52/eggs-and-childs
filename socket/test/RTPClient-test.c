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
#include <pthread.h>

#include "socket-util.h"
#include "RTPClient.h"
#include "RTPParser.h"


static void listener(Socket* self){
   while (1){
      socket__receive(self);

      rtp_parser__parse(self->recv_buff);
   }
}

static void start(RTPClient* self){
	
	sock_util__buffer_write(self->super->super->send_buff, "Hello from real time protocol client.");

   /* Send the message in buf to the server */
   dataBuffer sent=self->vtable->send(self->super->super);
	printf("Sent (%i bytes) message: %s\n", sent.size, (char*)self->super->super->send_buff->buffer);
   
   //wait for a message from server
   //dataBuffer recvd=self->vtable->receive(self->super->super);
   
   /*
   *
   */
  /*
   int addr=self->super->super->socket.sin_addr.s_addr;
	
	printf("Received (%i bytes) message: %s | Domain:%s address:%i.%i.%i.%i\n",recvd.size, (char*)self->super->super->recv_buff->buffer+sizeof(RTP), (self->super->super->socket.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	(addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);
   rtp_parser__parse(self->super->super->recv_buff);
	free(recvd.buffer);
   */
  listener(self->super->super);
}

int main(int argc, char** argv){
	
	RTPClient* requester=rtp_client__new(INADDR_ANY, UDP_PORT);
    printf("RTP Client starting to send message to the connection.\n");
	
	start(requester);
   
   rtp_client__destroy(&requester);
   
   return 0;
}

