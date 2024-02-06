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
#include "LinkedList.h"
#include "PacketMonitor.h"

static void listener(Socket* self, LinkedList* ll){
   while (1){
      socket__receive(self);

      RTP* rtpPacket=(RTP*)self->recv_buff->buffer;
      
      PacketMonitorClass.rearrangeIncomingRTP(ll, rtpPacket);

      printf("rtp seq num %ui\n", rtpPacket->sequence_number);

      printf("jpeg sof expected:%x%x %x%x\n",*(int8_t* )(self->recv_buff->buffer+17),
      *(int8_t* )(self->recv_buff->buffer+18),
      *(int8_t* )(self->recv_buff->buffer+19),
      *(int8_t* )(self->recv_buff->buffer+20));
      

   }
}

static void start(RTPClient* self){
	
	sock_util__buffer_write(self->super->super->send_buff, "Hello from RTP video stream client.");

   /* Send the message in buf to the server */
   dataBuffer sent=self->vtable->send(self->super->super);
	printf("Sent (%i bytes) message: %s\n", sent.size, (char*)self->super->super->send_buff->buffer);
   
   //wait for a image stream from server
   //dataBuffer recvd=self->vtable->receive(self->super->super);
   LinkedList* l=LinkedListClass.new();
   listener(self->super->super, l);
}

int main(int argc, char** argv){
	
	RTPClient* requester=rtp_client__new(INADDR_ANY, UDP_PORT);
    printf("RTP Client starting to send message to the connection.\n");
	
	start(requester);
   
   rtp_client__destroy(&requester);
   
   return 0;
}

