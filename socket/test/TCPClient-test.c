#include<stdio.h>
#include<stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "TCPClient.h"

// Driver Program
int main (int argc, char** argv){
	TCPClient* cli=tcp_client__new(INADDR_LOOPBACK, TCP_PORT);
	tcp_client__start(cli);
	
	tcp_client__destroy(&cli);
	return 0;
}

