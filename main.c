#include "shapes.h"
#include <stdio.h>

int main(void){
	shape* s1 = NULL;
	char* input = "     circle(    1.1  2 , 1.24   )    ";
	s1 = parseInputString(input, 0);
	

	printf("1. ");
	switch (s1->type)
	{
	case Circle:
		printf("circle(");
		break;
	
	case Triangle:
		printf("triangle(");
		break;

	case Polygon:
		printf("polygon(");
		break;
	}
	for (int i = 0; i < s1->ptscnt; i++) {
		printf("%.2f %.2f", s1->pts[i].x, s1->pts[i].y);
		if (i != s1->ptscnt-1 || s1->type == Circle) printf(", ");  
	}
	

	switch (s1->type)
	{
	case Circle:
		printf("%.2f)\n", s1->radius);
		printf("\tperimeter = %.4f\n", 2.0*3.14*s1->radius);
		printf("\tarea = %.4f\n", 3.14*s1->radius*s1->radius);
		break;
	default:
		printf(")\n");
		printf("not implemented\n");
	}
	return 0;
}