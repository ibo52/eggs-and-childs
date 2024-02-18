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

#include <sys/time.h>


static void saveToFile(LinkedList* ll){
   /*
   Assuming first(at least) 16 bytes are RTP packet
   Thus, we need to save the data from (ptr+16)th address at everly Node
   */

   FILE* fd=fopen("RTP_builded.jpg","wb");

   if(!fd){
      perror("file could not created");
      exit(errno);
   }

   Node* n=ll->head;
   int RTP_PACKET_SIZE=sizeof(RTP);

   for(int i=1; i<ll->size; i++ ){

      fwrite(n->data_ptr+RTP_PACKET_SIZE, 1, n->data_size-RTP_PACKET_SIZE, fd);
      n=n->next;
   }

   fclose(fd);

   printf("[IMAGE FD]: file saved\n");
}
static void start(RTPClient* self){
	
	sock_util__buffer_write(self->super->super->send_buff, "Hello from RTP video stream client.");

   /* Send the message in buf to the server */
   dataBuffer sent=RTPClientClass.send(self);
	printf("Sent (%i bytes) message: %s\n", sent.size, (char*)self->super->super->send_buff->buffer);
   
   //wait for a image stream from server
   //listen until sock close req arrived
   LinkedList* l=LinkedListClass.new();
   
   RTPClientClass.listener(self, l);

   saveToFile(l);

   LinkedListClass.destroy(&l);
}

int main(int argc, char** argv){
	
	RTPClient* requester=rtp_client__new(INADDR_ANY, UDP_PORT);
    printf("RTP Client starting to send message to the connection.\n");
	
	start(requester);
   
   rtp_client__destroy(&requester);
   
   return 0;
}

