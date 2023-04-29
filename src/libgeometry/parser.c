#include <libgeometry/parser.h>
#include <libgeometry/lexer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

shape* parseInputString(char* input)
{
    char* orig_pointer = input;
    shape* object = malloc(sizeof(shape));
    int read;
    int i;
    printf("Parsing '%s'\n", input);
    if (lex_get_type(&input, object) < 0) return NULL;
    if (object->type == Polygon) {
        printf("[!] Polygons are not supported due to budget cuts and time constraints. Sorry!\n");
        return NULL;
    }
    object->pts = malloc(sizeof(point) * object->ptscnt);
    for (int k = 0; k < object->ptscnt-1; k++) {
        lex_get_point(&input, object, k, orig_pointer);
    }
    if (object->type != Circle) lex_get_last_point(&input, object, orig_pointer);
    else {
        lex_get_point(&input, object, object->ptscnt-1, orig_pointer);
        lex_get_radius(&input, object, orig_pointer);
    }
    return object;
}
