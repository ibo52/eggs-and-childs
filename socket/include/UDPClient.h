#ifndef HALO_SOCKET_UDPServer
#define HALO_SOCKET_UDPServer

#include<stdint.h>

/*message buffer to use on socket communication*/
typedef struct __UDPClient{
	int server_fd;
	struct sockaddr_in server;
	
	dataBuffer *recv_buff;
	dataBuffer *send_buff;
}UDPClient;

UDPClient* udp_client__new(int address, int port);

void udp_client__destroy(UDPClient** self);


#endif
