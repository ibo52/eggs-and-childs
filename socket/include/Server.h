#ifndef HALO_SOCKET_SERVER
#define HALO_SOCKET_SERVER

#include<stdint.h>
#include "socket-util.h"

/*message buffer to use on socket communication*/
typedef struct __Server Server;
typedef struct __Server_VTable Server_VTable;

struct __Server_VTable{
	Server* (*new)(int addr, int type);
	void (*destroy)(Server** self);
};

Server* server__new(int address, int port, int type);

void server__destroy(Server** self);
/*
void server__start(Server* self);

static const Server_VTable vtable_server;
vtable_server->start=&server__start;
vtable_server->join=&server__join;
*/
#endif
