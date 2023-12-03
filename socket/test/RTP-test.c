#include<stdlib.h>
#include <stdio.h>

#include "RTP.h"

int main(int argc, char** argv){
	printf("Test for RTP class\n\n");
	
	RTP* self=RTP__new();
	
	RTP__toString(self);
	
	RTP__destroy(&self);
	
	printf("\nTest for RTP class done\n");
	return 0;
}
