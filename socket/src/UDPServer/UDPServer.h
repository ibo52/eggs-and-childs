#ifndef HALO_SOCKET_UDPServer
#define HALO_SOCKET_UDPServer

#include<stdint.h>
#include "socket-util.h"
/*message buffer to use on socket communication*/


struct __UDPServer_VTable{
	UDPServer* (*new)(int address, int port);
    void (*destroy)(RTSPServer** self);

	dataBuffer (*receive)(Socket* self);
	dataBuffer (*send)(Socket* self);
	
};

typedef struct __UDPServer{
	Socket* super;
	const struct __UDPServer_VTable* vtable;	//virtual functions table
}UDPServer;

//static table for default virtual functions
static const struct __UDPServer_VTable UDPServerClass={
	.new=udp_server__new,
	.destroy=udp_server__destroy,
	.receive=socket__receive,
	.send=socket__send
};

UDPServer* udp_server__new(int address, int port);

void udp_server__destroy(UDPServer** self);

void udp_server__start(UDPServer* self);


#endif
