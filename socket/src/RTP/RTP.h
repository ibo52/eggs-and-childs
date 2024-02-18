#ifndef HALO_RTP_H
#define HALO_RTP_H

#include<stdint.h>
#include "Socket.h"		//Socket

#define RTP_PAYLOAD_TYPE_JPEG 26
#define RTP_BYTES_PER_CHUNK 1024		//defines chunk size( in bytes) of RTP packets

//The RTP header has a minimum size of 12 bytes which is 96 bits;
//veri yapısını yazarken paketlemeye dikkat et, bellekte boşluk doldurmalar(padding) yapmasın
typedef struct __RTP{
	uint8_t VPXCC;				//'V'ersion: 2 bits, 'P'adding:1 bit, e'X'tension: 1 bit, 'C'SRC count: 4 bits
	uint8_t MPT;  				//'M'arker: 1 bit, 'P'ayload 'T'ype: 7 bits
	uint16_t sequence_number;	//should be randomized to make known-plaintext attacks on S(ecure)RTP more difficult
	uint32_t timestamp;			//Used by the receiver to play back the received samples at appropriate time and interval
	uint32_t ssrc;				//Synchronization source identiﬁer uniquely identiﬁes the source of a stream
	uint32_t csrc;				//Contributing source IDs enumerate contributing sources to a stream that has been generated from multiple sources
}RTP;


RTP* rtp__new(void);
void rtp__destroy(RTP** self);
void rtp__toString(RTP* self);

/*send data by RTP*/
dataBuffer rtp__send(RTP* self, Socket* sock);
#endif
