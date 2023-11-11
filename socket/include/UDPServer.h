#ifndef HALO_SOCKET_UDPServer
#define HALO_SOCKET_UDPServer

#include<stdint.h>
#include "socket-util.h"
/*message buffer to use on socket communication*/
typedef struct __UDPServer_VTable UDPServer_VTable;

typedef struct __UDPServer{
	Socket* super;
	UDPServer_VTable* vtable;	//virtual functions table
}UDPServer;

struct __UDPServer_VTable{
	dataBuffer (*receive)(Socket* self);
	dataBuffer (*send)(Socket* self);
	
};

//static table for default virtual functions
static UDPServer_VTable UDPServer_VTable__default={
	.receive=sock_util__receive__socket,
	.send=sock_util__send__socket
};

UDPServer* udp_server__new(int address, int port);

void udp_server__destroy(UDPServer** self);

void udp_server__start(UDPServer* self);


#endif
