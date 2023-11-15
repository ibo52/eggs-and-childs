#ifndef HALO_SOCKET_SERVER_TCP
#define HALO_SOCKET_SERVER_TCP

#include<stdint.h>
#include "socket-util.h"

typedef struct __TCPServer_VTable TCPServer_VTable;

typedef struct __TCPServer{
	Socket* super;
	pthread_t starter_thread;
	
	const TCPServer_VTable* vtable;
}TCPServer;

struct __TCPServer_VTable{
	dataBuffer (*receive)(Socket* self);
	dataBuffer (*send)(Socket* self);
};

//Default Virtual functions table
static const TCPServer_VTable TCPServer_VTable__default={
	.receive=socket__receive,
	.send=socket__send
};
/*
*	Create new object (Allocate data on memory)
*/
TCPServer* tcp_server__new(int addr, int port);

/*
*	Destroy the object(free the address that memory points)
*/
void tcp_server__destroy(TCPServer** self);

/*
*	starts the server to listen incoming connections
*/
void tcp_server__start(TCPServer* self);

/*
*	Wait for server. Blocks the caller thread
*/
void tcp_server__join(TCPServer* self);
#endif
