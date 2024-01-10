#ifndef HALO_SOCKET_RTPSERVER
#define HALO_SOCKET_RTPSERVER

#include<stdint.h>

#include "UDPServer.h"
#include "RTP.h"
/*message buffer to use on socket communication*/
typedef struct __RTPServer_VTable RTPServer_VTable;

typedef struct __RTPServer{
	UDPServer* super;
	RTP* rtp_header;
	
	const UDPServer_VTable* vtable;	//virtual functions table
}RTPServer;
/*
struct __RTPServer_VTable{
	dataBuffer (*receive)(Socket* self);
	dataBuffer (*send)(Socket* self);
	
};

//static table for default virtual functions
//same with UDPServer vtable
static const RTPServer_VTable RTPServer_VTable__default={
	.receive=socket__receive,
	.send=socket__send
};
*/
RTPServer* rtp_server__new(int address, int port);

void rtp_server__destroy(RTPServer** self);

void rtp_server__start(RTPServer* self);


#endif
