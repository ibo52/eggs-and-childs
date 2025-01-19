#include "UDPServer.h"
#include <pthread.h>

typedef struct __RTSPServer
{
    UDPServer* super;
    pthread_t listener_thread;
    /* data */
}RTSPServer;


RTSPServer* rtsp_server__new(int address, int port);

void rtsp_server__destroy(RTSPServer** self);

RTSPServer* rtsp_server__start(RTSPServer* self);

RTSPServer* rtsp_server__join(RTSPServer* self);

RTSPServer* rtsp_server__stop(RTSPServer* self);

struct __RTSPServer_VTable
{
    RTSPServer* (*new)(int address, int port);

    void (*destroy)(RTSPServer** self);

    RTSPServer* (*start)(RTSPServer* self);

    RTSPServer* (*join)(RTSPServer* self);

    RTSPServer* (*stop)(RTSPServer* self);

    
};
/*
Virtual table for RTSPServer to easily access functions*/
static const struct __RTSPServer_VTable RTSPServerClass={
    .new=rtsp_server__new,
    .destroy=rtsp_server__destroy,
    .start=rtsp_server__start,
    .join=rtsp_server__join,
    .stop=rtsp_server__stop
};