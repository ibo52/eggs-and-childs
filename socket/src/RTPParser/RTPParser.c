#include<string.h> //memcpy
#include <stdio.h>

#include "RTPParser.h"

void rtp_parser__parse(dataBuffer* RTPPacket){
    RTP RTPData;
    int RTP_STRUCT_SIZE=sizeof(RTP);

    memcpy(&RTPData, RTPPacket->buffer, RTP_STRUCT_SIZE);//extract rtp packet

    rtp__toString(&RTPData);

    printf("data:%s\n", (char*)RTPPacket->buffer+RTP_STRUCT_SIZE);
}