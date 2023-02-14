#include <stdio.h>

#define TT_STRING 	0
#define TT_POINT 	1
#define TT_INT 		2

// todo: enum argtypes and shape types
struct Point{
	float x;
	float y;
}

struct Shape{
	int type;
	int ptscnt;
	struct Point pts[];
	int radius;
}

int getShapeType(char* string, int startColumn){
	// skip all spaces prior to first character
	int i = startColumn;
	while((string[i] == ' ') and (string[i] != '\0')) i++;
	
	// do we even have symbols in given input?
	if (string[i] == '\0') {
		throwError(startColumn, "'circle', 'triangle' or 'polygon'");
		return NULL;
	} 
	
	// get new lowercase string char by char until met by ( or ' '
	char* buf[16];
	int j = 0;
	while((string[i] != ' ') and (string[i] != '\0') and (j < 16)) {
		buf[j] = tolower(string[i]);
		i++;
		j++;
	}
	if (!strcmp(str, "circle")
}


int main(void){
	char* input = "circle(0 0, 1.5)";
}
