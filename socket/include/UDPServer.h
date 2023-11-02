#ifndef HALO_SOCKET_UDPServer
#define HALO_SOCKET_UDPServer

#include<stdint.h>

/*message buffer to use on socket communication*/
typedef struct __UDPServer{
	Socket* super;
}UDPServer;

UDPServer* udp_server__new(int address, int port);

void udp_server__destroy(UDPServer** self);

void udp_server__start(UDPServer* self);


#endif
