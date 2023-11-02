#ifndef HALO_SOCKET_UDPCLIENT
#define HALO_SOCKET_UDPCLIENT

#include<stdint.h>

/*message buffer to use on socket communication*/
typedef struct __UDPClient{
	Socket* super;
}UDPClient;

UDPClient* udp_client__new(int address, int port);

void udp_client__destroy(UDPClient** self);


#endif
