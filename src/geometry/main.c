#include "shapes.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("1. ");
    char* buffer = NULL;
    size_t len;
    getline(&buffer, &len, stdin);

    shape* s1 = NULL;
    s1 = parseInputString(buffer, 0);
    if (s1 == NULL)
        return -1;

    switch (s1->type) {
    case Circle:
        if (s1->radius <= 0) {
            printf("\tradius is less or equal to 0: not calculating\n");
        } else {
            printf("\tperimeter = %.4f\n", 2.0 * M_PI * s1->radius);
            printf("\tarea = %.4f\n", M_PI * s1->radius * s1->radius);
        }
        break;
    default:
        printf("not implemented\n");
    }
    return 0;
}
