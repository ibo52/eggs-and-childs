/*
*	UDP client for data requesting
*/
#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "socket-util.h"
#include "UDPClient.h"


int main(int argc, char** argv){
	
	UDPClient* requester=udp_client__new(INADDR_ANY, UDP_PORT);

   strcpy((char *)requester->send_buff->buffer, "Hello from UDP client.");

   /* Send the message in buf to the server */
   if (sendto(requester->server_fd, requester->send_buff->buffer, strlen((char* )requester->send_buff->buffer), 0,
                 (struct sockaddr *)&requester->server, sizeof(requester->server)) < 0)
   {
       perror("sendto()");
       exit(2);
   }

   /* Deallocate the socket */
   close(requester->server_fd);
   
   udp_client__destroy(&requester);
   
   return 0;
}

