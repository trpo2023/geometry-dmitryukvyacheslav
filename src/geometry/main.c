#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // parseInputString(" triangle (11.1 3.2, 1.2 3.3, 1.433 2.3, 1.2 22) ");
    FILE* input;
    if (argc == 1)
        input = stdin;
    else
        input = fopen(argv[1], "r");
    char strbuf[512];
    shape* shapes = malloc(sizeof(shapes));
    if (!shapes) {
        printf("Could not allocate memory\n");
    }
    int shapes_index = 0;
    while (!feof(input)) {
        if (!realloc(shapes, sizeof(shapes) * (shapes_index + 1))) {
            printf("Could not allocate memory\n");
            return 0;
        };
        fgets(strbuf, 512, input);
        if (!parseInputString(strbuf, &(shapes[shapes_index])))
            shapes_index++;
        else
            return -1;
    }
    printf("Parsed %d shapes!\n\n", shapes_index);
    print_shapes(shapes, shapes_index);
    return 0;
}
