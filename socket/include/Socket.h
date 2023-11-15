#ifndef HALO_SOCKET_COMMUNICATOR
#define HALO_SOCKET_COMMUNICATOR

#include<stdint.h>
#include "socket-util.h"
typedef struct __dataBuffer dataBuffer;//forward declaration to socket-util.h
typedef struct __Socket_VTable Socket_VTable;
/*
*	CommunicationObject
*	struct holds socket info and buffers for communication
*/

typedef struct __Socket{
	int fd;						//file descriptor
	struct sockaddr_in socket;	//sockaddr struct
	
	dataBuffer *recv_buff;		//buffer to receive message
	dataBuffer *send_buff;		//buffer to send message
	
	const Socket_VTable* vtable; //virtual functions table
}Socket;

struct __Socket_VTable{
	dataBuffer (*receive)(Socket* self);
	dataBuffer (*send)(Socket* self);
};

/*
*	Create new object (Allocate data on memory)
*/
Socket* socket__new(int address, int port, int type);

/*
*	Destroy the object(free the address that memory points)
*/
void socket__destroy(Socket** self);

/*
*	Send message through Socket object. Common interface for TCP and UDP sockets
*	
*	@param self	: destination Socket to forward message
*	@return		: Bytes sent in total
*/
dataBuffer socket__send(Socket* self);


/*
*	Receive message through Socket object. Common interface for TCP and UDP sockets
*	
*	@param self: Socket to listen for a message receivation from others
*	@return	   : Bytes received in total
*/
dataBuffer socket__receive(Socket* self);
/*
void server__start(Server* self);

static const Server_VTable vtable_server;
vtable_server->start=&server__start;
vtable_server->join=&server__join;
*/

//Default Virtual functions table
static const Socket_VTable Socket_VTable__default={
	.receive=socket__receive,
	.send=socket__send
};

#endif
