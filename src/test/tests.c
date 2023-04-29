#include <libgeometry/parser.h>
#include <libgeometry/intersect.h>
#include <libgeometry/lexer.h>
#include <thirdparty/ctest/ctest.h>
#include <stdio.h>
#define CTEST_MAIN

CTEST(parsing, lex_get_type) {
    shape shapes[4];
    char* strings[4] =  {"CirCle(","circle(","circl(", "circle"};
    for (int i = 0; i < 4; i++)
        lex_get_type(&(strings[i]), &(shapes[i]));
    ASSERT_EQUAL(shapes[0].type, Circle);
    ASSERT_EQUAL(shapes[1].type, Circle);
    ASSERT_EQUAL(shapes[2].type, 0);
    ASSERT_EQUAL(shapes[3].type, 0);    
}