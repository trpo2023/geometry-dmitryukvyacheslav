#include <libgeometry/shapes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    printf("1. ");
    char* buffer = NULL;
    size_t len;
    getline(&buffer, &len, stdin);

    shape* object = NULL;
    object = parseInputString(buffer);
    if (object == NULL)
        return -1;

    switch (object->type) {
    case Circle:
        if (object->radius <= 0) {
            printf("\tradius is less or equal to 0: not calculating\n");
        } else {
            printf("\tperimeter = %.4f\n", 2.0 * M_PI * object->radius);
            printf("\tarea = %.4f\n", M_PI * object->radius * object->radius);
        }
        break;
    default:
        printf("not implemented\n");
    }
    for 
    return 0;
}
