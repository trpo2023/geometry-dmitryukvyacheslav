#include "shapes.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
	printf("1. ");
	char *buffer = NULL;
    //int read;
    size_t len;
    getline(&buffer, &len, stdin);
    //if (-1 != read) puts(buffer);
	
	shape* s1 = NULL;
	s1 = parseInputString(buffer, 0);
	if (s1 == NULL) return -1;

	switch (s1->type)
	{
	case Circle:
		printf("\tperimeter = %.4f\n", 2.0*3.14*s1->radius);
		printf("\tarea = %.4f\n", 3.14*s1->radius*s1->radius);
		break;
	default:
		printf("not implemented\n");
	}
	return 0;
}
