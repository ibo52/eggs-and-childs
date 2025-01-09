#include "stddef.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "CameraClient.h"

CameraClient* camera_client__new(int address, int port){

    CameraClient* self=calloc(1, sizeof(CameraClient));

    self->client= RTPClientClass.new(address, port);

    sock_util__dealloc_buffer( &(self->client->super->super->recv_buff) );

    self->client->super->super->recv_buff=sock_util__alloc_buffer(UDP_MAX_BYTES_PER_CHUNK+28);

    return self;
}

void camera_client__destroy(CameraClient** self){

    RTPClientClass.destroy( &((*self)->client) );

    free( (*self) );
    (*self)=NULL;
}

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
   uint32_t TOTAL=0;

   for(int i=1; i<ll->size; i++ ){
      
      size_t ss=fwrite(n->data_ptr+RTP_PACKET_SIZE, 1, n->data_size-RTP_PACKET_SIZE, fd);

      TOTAL+=ss;
      printf("[FILE]: write size %lu, packet size:%u, RTP seq num:%u\n",ss, n->data_size, ((RTP*)(n->data_ptr))->sequence_number );
      n=n->next;
   }

   fclose(fd);
   printf("[FILE]: total image write size %u\n",TOTAL);
   printf("[IMAGE FD]: file saved\n");
}

void camera_client__start(CameraClient* self){

    sock_util__buffer_write(self->client->super->super->send_buff, "Hello from RTP video stream client.");

   /* Send the message in buf to the server */
   dataBuffer sent=RTPClientClass.send(self->client);
	printf("Sent (%i bytes) message: %s\n", sent.size, (char*)self->client->super->super->send_buff->buffer);
   
   //wait for a image stream from server
   //listen until sock close req arrived
   LinkedList* l=LinkedListClass.new();
   
   RTPClientClass.listener(self->client, l);

   saveToFile(l);

   LinkedListClass.destroy(&l);

}