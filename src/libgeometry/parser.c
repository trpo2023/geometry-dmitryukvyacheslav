#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>
#include <libgeometry/intersect.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int parseInputString(char* input, shape* object)
{
    char* orig_pointer = input;
    input[strcspn(input, "\n")] = 0;
    printf("Parsing '%s'\n", input);
    if (lex_get_type(&input, object) < 0) return 1; 
        
    if (object->type == Polygon || object->type == Triangle) {
        printf("[!] Polygons and triangles not supported due to budget cuts and time constraints. Sorry!\n");
        return 1;
    }
    object->pts = malloc(sizeof(point) * object->ptscnt);
    for (int k = 0; k < object->ptscnt-1; k++) {
        if (lex_get_point(&input, object, k, orig_pointer)) return 1;
    }
    if (object->type != Circle) lex_get_last_point(&input, object, orig_pointer);
    else {
        if (lex_get_point(&input, object, object->ptscnt-1, orig_pointer)) return 1;
        if (lex_get_radius(&input, object, orig_pointer)) return 1;
    }
    return 0;
}

void print_shapes(shape* shapes, int count){
    for (int i = 0; i < count; i++) {
        printf("%d. circle(%.4lf %.4lf, %.4lf)\n", i, shapes[i].pts[0].x, shapes[i].pts[0].y, shapes[i].radius);
        printf("\tperimeter = %.4lf\n", 2*3.1412*shapes[i].radius);
        printf("\tarea = %.4lf\n", 3.1412*pow(shapes[i].radius, 2));
        printf("intersects:\n");
        print_intersections(shapes, count, i);
        printf("\n");
    }
}