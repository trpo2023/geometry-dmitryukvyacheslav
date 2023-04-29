#include <libgeometry/parser.h>
#pragma once

// int lines_intersect(point line1_start, point line1_end, point line2_start,
// point line2_end);
//  Finding whether line *segment* intersects a cirlce would give me an
//  aneurism, and I'm short on time Circles only for the time being
int circles_instersect(
        point center1, double radius1, point center2, double radius2);
void print_intersections(shape* shapes, int count, int index);