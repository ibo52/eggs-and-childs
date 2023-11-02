#ifndef HALO_SOCKET_SERVER_TCP
#define HALO_SOCKET_SERVER_TCP

#include<stdint.h>
#include "socket-util.h"

typedef struct __TCPServer{
	Socket* super;
	pthread_t starter_thread;
}TCPServer;

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
