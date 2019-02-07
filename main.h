#include <stdio.h>
#include <stdlib.h>

#define TEXT_SIZE 100

typedef struct message {
	char beginTime[8];
	char endTime[8];
	char text[TEXT_SIZE];
} message;
