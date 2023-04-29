#pragma once

enum ShapeTypes { Circle = 10, Triangle = 11, Polygon = 12 };

typedef struct Point {
    float x;
    float y;
} point;

typedef struct Shape {
    enum ShapeTypes type;
    int ptscnt;
    float radius;
    point* pts;
} shape;

int parseInputString(char* input, shape* object);
void print_shapes(shape* shapes, int count);