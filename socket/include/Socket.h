#ifndef HALO_SOCKET_COMMUNICATOR
#define HALO_SOCKET_COMMUNICATOR

#include<stdint.h>
#include "socket-util.h"
typedef struct __dataBuffer dataBuffer;//forward declaration to socket-util.h

/*
*	CommunicationObject
*	struct holds socket info and buffers for communication
*/
typedef struct __Socket{
	int fd;						//file descriptor
	struct sockaddr_in socket;	//sockaddr struct
	
	dataBuffer *recv_buff;		//buffer to receive message
	dataBuffer *send_buff;		//buffer to send message
}Socket;
/*
typedef struct __Server_VTable Server_VTable;

struct __Server_VTable{
	Server* (*new)(int addr, int type);
	void (*destroy)(Server** self);
};
*/
Socket* socket__new(int address, int port, int type);

void socket__destroy(Socket** self);
/*
void server__start(Server* self);

static const Server_VTable vtable_server;
vtable_server->start=&server__start;
vtable_server->join=&server__join;
*/
#endif
