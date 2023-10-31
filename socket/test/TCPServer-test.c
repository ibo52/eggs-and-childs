/*
*		Simple TCP Server to send Video data of camera
*		through socket
*/
#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>

#include "TCPServer.h"
#include "Server.h"

// Driver Program
int main (int argc, char** argv){
	TCPServer* server=tcp_server__new(INADDR_LOOPBACK, TCP_PORT);
    tcp_server__start(server);
    
    tcp_server__join(server);
    tcp_server__destroy(&server);
    
	return 0;
}

