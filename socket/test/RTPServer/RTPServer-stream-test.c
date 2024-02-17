/*	Test
 * 
*/
#include<stdio.h>
#include<stdlib.h>

#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close(), sleep
#include<errno.h>
#include<netinet/in.h>
#include<string.h>

#include "RTPServer.h"
#include "Camera.h"

static void start(RTPServer* self){

	Camera* c=CameraClass.new("/dev/video0");

	CameraClass.activate(c);
	//CameraClass.printSpecs(c);

	//recv.buffer: holds *(struct sockaddr_in*) socket data of incoming request,
	//recv.size	 : holds received message length)
	//1. client request came to server
	dataBuffer recvd=RTPServerClass.receive(self);//sock_util__receive__socket(self->super);
	//parse info of client to communicate with socket
	Socket client={ self->super->super->fd, *(struct sockaddr_in *)recvd.buffer, self->super->super->recv_buff, self->super->super->send_buff };

	int addr=client.socket.sin_addr.s_addr;
	
	printf("Received (%i bytes) message: %s | Domain:%s address:%i.%i.%i.%i\n",recvd.size, (char*)self->super->super->recv_buff->buffer, (client.socket.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	(addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);	

	cameraBuffer camBuff=CameraClass.capture(c, V4L2_PIX_FMT_JPEG);
	//prepare acknowledgement data to send back

	sock_util__buffer_write_sizei(client.send_buff, camBuff.address, 2048/*camBuff.length*/);
	RTPServerClass.sendRTP(self,	&client);
	
	sock_util__buffer_write(client.send_buff, "SOCK_CLOSE_REQUEST");
	RTPServerClass.send(/*self->rtp_header,*/ &client);
	//dataBuffer sent=self->vtable->send(&client);//sock_util__send__socket(&client);
	//printf("Sent (%i bytes) message: %s\n", sent.size, (char*)client.send_buff->buffer);
	free(recvd.buffer);
	printf("camera buffer streamed to client\n");
	CameraClass.destroy(&c);
}

//Driver program
int main(int argc, char** argv){
	RTPServer* server=rtp_server__new(INADDR_ANY, UDP_PORT);
	
	printf("RTP Server for Video Stream started. Waiting for a connection.\n");
	
	//dataBuffer_VTable__default.write(server->super->super->send_buff, "sample RTP message to divede to chunks, then send to client over UDP socket");

	//welcomeClient(server);
	start(server);

	rtp_server__destroy(&server);
	
	return 0;
}

