#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "socket-util.h"
#include "UDPServer.h"
#include "Socket.h"

//Driver program
int main(int argc, char** argv){
	UDPServer* server=udp_server__new(INADDR_ANY, UDP_PORT);
	udp_server__start(server);
	
	printf("UDP Server started. Waiting for a connection.\n");
	
	udp_server__destroy(&server);
	
	return 0;
}

