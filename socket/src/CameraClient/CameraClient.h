#ifndef HALO_CAMERA_CLIENT
#define HALO_CAMERA_CLIENT

#include "RTPClient.h"

typedef struct __CameraClient{
    RTPClient* client;

}CameraClient;

CameraClient* camera_client__new();

void camera_client__destroy(CameraClient** self);

void camera_client__start(CameraClient* self);

void camera_client__stop(CameraClient* self);

#endif