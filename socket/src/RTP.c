/*	Halil Ibrahim MUT
*
*		General implementation for RTP protocol for application layer
*		Reference: https://en.wikipedia.org/wiki/Real-time_Transport_Protocol
*/

#include<stdio.h>
#include<unistd.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>	//to randomize RTP sequence number

#include "RTP.h"

RTP* RTP__new(void){
	srand(time(NULL));	//seed the random function by current time
	
	RTP* self=calloc(1, sizeof(RTP));
	
	//first 2 bit for the RTP version(curernt version 2)
	self->VPXCC=0x2<<6;
	
	//skip P, which indicates presence of a padding
	//skip X, which indicates presence of an extension
	
	//payload 26: JPEG image format to send
	//reference: https://en.wikipedia.org/wiki/RTP_payload_formats
	self->MPT=26;
	
	self->sequence_number=rand()%65536;//init 16 bit random seqeunce number
	
	////time stamp may be determined by data device of user
	//SSRC ID may be determined by ip of user of this struct
	//CCRC ID may also be determined by ip of user of this struct
	return self;
}

void RTP__destroy(RTP** self){	
	
	free( (*self) );
	
	(*self)=NULL;
	
	printf("UDPClient object destructed\n");
}

void RTP__toString(RTP* self){

	printf("RTP Header\n"
		   "\t- 0th byte ----------------\n"
		   "\tVersion:            %24i\n"
		   "\tPadding:            %24s\n"
		   "\tExtension:          %24s\n"
		   "\tContributors count: %24i\n"
		   "\tMarker:             %24s\n"
		   "\tPayload Type:       %24s\n"
		   "\tSequence number:    %24i\n"
		   "\t- 4th byte ----------------\n"
		   "\ttimestamp:               %x\n"
		   "\tSync. source id(you):    %i\n"
		   "\tContributing source IDs: %i\n"
		   ,self->VPXCC>>6&0x2,					//version
		   (self->VPXCC>>5&0x1? "yes":"no"),	//pad
		   (self->VPXCC>>3&0x1? "yes":"no"),	//eXtension
		   self->VPXCC&0x0f,					//CC
		   
		   (self->MPT>>7&0x1? "yes":"no"),		//marker
		   ((self->MPT&0x7f)==26? "JPEG":"unknwn/othr"),		//payload type
		   self->sequence_number,
		   
		   self->timestamp,
		   self->ssrc,
		   self->csrc
		   );
}
