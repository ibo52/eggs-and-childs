#ifndef HALO_CAMERA_SERVER
#define HALO_CAMERA_SERVER

#include <pthread.h>
#include "Camera.h"
#include "RTPServer.h"

typedef struct __CameraServer{
    Camera* camera;
    RTPServer* server;
    pthread_t listenerThread;

}CameraServer;

CameraServer* camera_server__new();

void camera_server__destroy(CameraServer** self);

int camera_server__start(CameraServer* self);

int camera_server__join(CameraServer* self);

int camera_server__stop(CameraServer* self);

//private function
//static int camera_server__streamVideo(CameraServer* self, Socket client);

#endif