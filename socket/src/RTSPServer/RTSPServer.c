#include "RTSPServer.h"
#include <stdlib.h>
#include <stdio.h>
#include "RTSPUtils.h"

RTSPServer* rtsp_server__new(int address, int port){

    RTSPServer* self=calloc( 1, sizeof(RTSPServer) );

    self->super=UDPServerClass.new(address, port);

    return self;
}

void rtsp_server__destroy(RTSPServer** self){

    UDPServerClass.destroy( &( (*self)->super ) );

    free( (*self) );

    (*self)=NULL;
}

static void* rtsp_server__start_hidden(void* arg){

    RTSPServer* self=arg;

    int8_t thread_mutex_continue=1;//common mutext to signal thread
    //TODO: implement
    while ( thread_mutex_continue ){
        
        RTSPUtils* parsed_request=RTSPUtilsClass.new();
        
        dataBuffer recvd=UDPServerClass.receive( self->super->super );

        //parse info of client to communicate with socket
	    Socket client={ self->super->super->fd, *(struct sockaddr_in *)recvd.buffer, self->super->super->recv_buff, self->super->super->send_buff };

        //ipv4 addr of client
        int32_t addr=client.socket.sin_addr.s_addr;
	
	    printf("Received (%i bytes) message: %s | Domain:%s address:%i.%i.%i.%i\n",recvd.size, (char*)self->super->super->recv_buff->buffer, (client.socket.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
	    (addr&0xff), (addr>>8&0xff), (addr>>16&0xff), addr>>24&0xff);	

        RTSPUtilsClass.parse(parsed_request, recvd.buffer, recvd.size);

        printf("tokenized req:\n");
        
        RTSPUtilsClass.print(parsed_request);

        client.send_buff->vtable->write(client.send_buff, "200 OK RTSP");

        UDPServerClass.send(&client);
        break;
    }

    return PTHREAD_CANCELED;
    
}

RTSPServer* rtsp_server__start(RTSPServer* self){

    pthread_create(&self->listener_thread, NULL, rtsp_server__start_hidden, self);

    return self;
    
}

RTSPServer* rtsp_server__join(RTSPServer* self){

    //TODO: implement
    pthread_join(self->listener_thread, NULL); 
    return self;
}

RTSPServer* rtsp_server__stop(RTSPServer* self){

    //TODO: implement
    pthread_cancel(self->listener_thread);
    return self;
}