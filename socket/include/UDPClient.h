#ifndef HALO_SOCKET_UDPCLIENT
#define HALO_SOCKET_UDPCLIENT

#include<stdint.h>
#include "Socket.h"
#include "socket-util.h"

typedef struct __UDPClient_VTable UDPClient_VTable;
/*message buffer to use on socket communication*/
typedef struct __UDPClient{
	Socket* super;
	
	const UDPClient_VTable* vtable;
}UDPClient;

struct __UDPClient_VTable{
	dataBuffer (*receive)(Socket* self);
	dataBuffer (*send)(Socket* self);
	
};

//static table for default virtual functions
static const UDPClient_VTable UDPClient_VTable__default={
	.receive=socket__receive,
	.send=socket__send
};

UDPClient* udp_client__new(int address, int port);

void udp_client__destroy(UDPClient** self);


#endif
