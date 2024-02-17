#ifndef HALO_SOCKET_RTPCLIENT
#define HALO_SOCKET_RTPCLIENT

#include<stdint.h>

//#include "socket-util.h"
#include "UDPClient.h"
#include "RTP.h"
#include "LinkedList.h"

typedef struct __RTPClient_VTable RTPClient_VTable;
/*message buffer to use on socket communication*/
typedef struct __RTPClient{
	UDPClient* super;
	RTP* rtp_header;
	
	const UDPClient_VTable* vtable;
}RTPClient;

RTPClient* rtp_client__new(int address, int port);

void rtp_client__destroy(RTPClient** self);

void rtp_client__listener(RTPClient* self, LinkedList* ll);

dataBuffer rtp_client__recv(RTPClient* self);

dataBuffer rtp_client__send(RTPClient* self);


struct __RTPClient_VTable{
	RTPClient* (*new)(int adress, int port);
	void (*destroy)(RTPClient** self);

	dataBuffer (*receive)(RTPClient* self);
	dataBuffer (*send)(RTPClient* self);

	void (*listener)(RTPClient* self, LinkedList* ll);
	
};

//static table for default virtual functions
//same with udp client vtable
static const RTPClient_VTable RTPClientClass={
	.new=rtp_client__new,
	.destroy=rtp_client__destroy,
	
	.receive=rtp_client__recv,
	.send=rtp_client__send,
	.listener=rtp_client__listener
};

#endif
