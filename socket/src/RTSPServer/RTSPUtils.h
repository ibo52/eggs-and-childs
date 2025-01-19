#include <string.h>
#include <stdlib.h>
#include "stdint.h"
#include "stdio.h"

typedef struct __RTSPUtils{
    uint16_t TOKEN_LIST_MEM_SIZE;
    uint16_t NUM_TOKENS;//how many tokens have parsed
    char** TOKEN_LIST;//stores each tokens
    uint16_t TOKEN_MEM_SIZE;
    char* nextToken;//stores chars of current token to be read
    uint16_t nextTokenLength;
} RTSPUtils;


RTSPUtils* rtsp_utils__new(void);

void rtsp_utils__parse(RTSPUtils* self,  const char* request, int);

void rtsp_utils__destroy(RTSPUtils** self);

void rtsp_utils__print(RTSPUtils* self);

struct __RTSPUtils_VTable
{
    RTSPUtils* (*new)(void);
    void (*destroy)(RTSPUtils** self);
    void (*parse)(RTSPUtils* self, const char* request, int size);
    void (*print)(RTSPUtils* self);
};

const static struct __RTSPUtils_VTable RTSPUtilsClass={
    .new=rtsp_utils__new,
    .destroy=rtsp_utils__destroy,
    .parse=rtsp_utils__parse,
    .print=rtsp_utils__print
};
