#ifndef HALO_SOCKET_RTPCLIENT
#define HALO_SOCKET_RTPCLIENT

#include<stdint.h>

//#include "socket-util.h"
#include "UDPClient.h"
#include "RTP.h"

typedef struct __RTPClient_VTable RTPClient_VTable;
/*message buffer to use on socket communication*/
typedef struct __RTPClient{
	UDPClient* super;
	RTP* rtp_header;
	
	const UDPClient_VTable* vtable;
}RTPClient;
/*
struct __RTPClient_VTable{
	dataBuffer (*receive)(Socket* self);
	dataBuffer (*send)(Socket* self);
	
};

//static table for default virtual functions
same with udp client vtable
static const RTPClient_VTable RTPClient_VTable__default={
	.receive=socket__receive,
	.send=socket__send
};
*/
RTPClient* rtp_client__new(int address, int port);

void rtp_client__destroy(RTPClient** self);


#endif
