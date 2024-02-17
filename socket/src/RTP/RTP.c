/*	Halil Ibrahim MUT
*
*		General implementation for RTP protocol for application layer
*		Reference: https://en.wikipedia.org/wiki/Real-time_Transport_Protocol
*/

#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>	//to randomize RTP sequence number
#include<errno.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "socket-util.h" //dataBuffer
#include "RTP.h"

RTP* rtp__new(void){
	srand(time(NULL));	//seed the random function by current time
	
	RTP* self=calloc(1, sizeof(RTP));
	
	//first 2 bit for the RTP version(curernt version 2)
	//padding:0, extension:0, csrc count:0
	//thus 1000 0000 as binary representation(0x80H)
	self->VPXCC=0x80;
	//skip P, which indicates presence of a padding
	//skip X, which indicates presence of an extension
	
	//payload 26: JPEG image format to send
	//reference: https://en.wikipedia.org/wiki/RTP_payload_formats
	self->MPT=RTP_PAYLOAD_TYPE_JPEG;
	
	self->sequence_number=rand()%65536;//init 16 bit random seqeunce number
	
	////time stamp may be determined by data device of user
	//SSRC ID may be determined by ip of user of this struct
	//CCRC ID may also be determined by ip of user of this struct
	return self;
}

void rtp__destroy(RTP** self){	
	
	free( (*self) );

	(*self)=NULL;
	
	printf("RTP object destructed\n");
}

void rtp__toString(RTP* self){

	printf("RTP Header\n"
		   "\t- 0th byte ----------------\n"
		   "\tVersion:            %25i\n"
		   "\tPadding:            %25s\n"
		   "\tExtension:          %25s\n"
		   "\tContributors count: %25i\n"
		   "\tMarker:             %25s\n"
		   "\tPayload Type:       %25s\n"
		   "\tSequence number:    %25i\n"
		   "\t- 4th byte ----------------\n"
		   "\ttimestamp:               %20x\n"
		   "\tSync. source id(you):    %20i\n"
		   "\tContributing source IDs: %20i\n"
		   ,self->VPXCC>>6&0x2,					//version
		   (self->VPXCC>>5&0x1? "yes":"no"),	//pad
		   (self->VPXCC>>3&0x1? "yes":"no"),	//eXtension
		   self->VPXCC&0x0f,					//CC
		   
		   (self->MPT>>7&0x1? "yes":"no"),		//marker
		   ((self->MPT&0x7f)==RTP_PAYLOAD_TYPE_JPEG? "JPEG":"unknwn/othr"),		//payload type
		   self->sequence_number,
		   
		   self->timestamp,
		   self->ssrc,
		   self->csrc
		   );
}

/*
	@param self	: RTP header to write before message
	@param sock	: sender Socket to forward message to other(which also holds data to send)
	@return		: Bytes sent in total
*/
dataBuffer rtp__send(RTP* self, Socket* sock){

	int sent_size=0;
	int total_data_len=sock->send_buff->size;

	dataBuffer* RTPBuffer=sock_util__alloc_buffer(RTP_BYTES_PER_CHUNK);
	static int RTP_size=sizeof(RTP);

	while(sent_size < total_data_len){
		
		//1. write rtp chunk
		memcpy(RTPBuffer->buffer, self, RTP_size);//write rtp header
		
		//write chunk of data to remaining space of buffer
		memcpy(RTPBuffer->buffer + RTP_size, sock->send_buff->buffer + sent_size, RTP_BYTES_PER_CHUNK-RTP_size);
		RTPBuffer->size=RTP_BYTES_PER_CHUNK;

		//temporary holder for sockets buff
		dataBuffer* temp=sock->send_buff;
		sock->send_buff=RTPBuffer;
		
		sent_size+=socket__send(sock).size-RTP_size;
		printf("sent chunk of seq number %i :",self->sequence_number);
		printf("%x%x\n",
		*(int8_t*)(sock->send_buff->buffer+RTP_size+0),
		*(int8_t*)(sock->send_buff->buffer+RTP_size+1));
		sock->send_buff=temp;
		self->sequence_number++;
	}
	
	sock_util__dealloc_buffer(&RTPBuffer);

	dataBuffer retData={NULL, sent_size, 0};
	return retData;
}

/*	Receive rtp messages from a client
 * @param sock : ocket to receive data from
 * @return : info about received data
*/
dataBuffer rtp__receive(Socket* sock){


	return socket__receive(sock);
}
/*
dataBuffer rtp__receive(dataBuffer buff){
	return NULL;
}*/
