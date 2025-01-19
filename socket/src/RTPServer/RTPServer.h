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
	
	const struct __UDPServer_VTable* vtable;	//virtual functions table
}RTPServer;

RTPServer* rtp_server__new(int address, int port);

void rtp_server__destroy(RTPServer** self);

void rtp_server__start(RTPServer* self);

dataBuffer rtp_server__recv(RTPServer* self);

dataBuffer rtp_server__sendRTP(RTPServer* self, Socket* toSocket);

dataBuffer rtp_server__send(Socket* toSocket);

struct __RTPServer_VTable{
	RTPServer* (*new)(int address, int port);
	void (*destroy)(RTPServer** self);

	dataBuffer (*receive)(RTPServer* self);
	dataBuffer (*send)(Socket* self);
	dataBuffer (*sendRTP)(RTPServer* self, Socket* toSocket);
	
};

//static table for default virtual functions
//same with UDPServer vtable
static const RTPServer_VTable RTPServerClass={
	.new=rtp_server__new,
	.destroy=rtp_server__destroy,

	.receive=rtp_server__recv,

	.send=rtp_server__send,
	.sendRTP=rtp_server__sendRTP
};


#endif
