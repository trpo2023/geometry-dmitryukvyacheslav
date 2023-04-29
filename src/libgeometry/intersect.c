#include <libgeometry/intersect.h>
#include <math.h>
#include <stdio.h>

double pointDistance(point p1, point p2) {
    return sqrt(pow(p2.x-p1.x, 2)+pow(p2.y-p1.y, 2));
}

int circles_instersect(point center1, double radius1, point center2, double radius2){
    return pointDistance(center1, center2) <= radius1+radius2 ? 1 : 0;
}

void print_intersections(shape* shapes, int count, int index){
    for(int i = 0; i < count; i++){
        if (i == index) continue;
        if (circles_instersect(shapes[index].pts[0], shapes[index].radius,
            shapes[i].pts[0], shapes[i].radius)) {
            printf("\t%d. circle\n", i);
        }
    }
}