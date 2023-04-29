#include <libgeometry/intersect.h>
#include <libgeometry/lexer.h>
#include <libgeometry/parser.h>
#include <stdio.h>
#include <thirdparty/ctest/ctest.h>

CTEST(parsing, lex_get_type)
{
    shape shapes[5];
    char* strings[5]
            = {"   CirCle(", "circle    (", "circl    (", "circle", " "};
    for (int i = 0; i < 4; i++)
        lex_get_type(&(strings[i]), &(shapes[i]));
    ASSERT_EQUAL(shapes[0].type, Circle);
    ASSERT_EQUAL(shapes[1].type, Circle);
    ASSERT_NOT_EQUAL(shapes[2].type, Circle);
    ASSERT_NOT_EQUAL(shapes[3].type, Circle);
    ASSERT_NOT_EQUAL(shapes[4].type, Circle);
}
CTEST(parsing, parseInputString)
{
    shape object;
    char strings[10][256] = {
            "circle(0.1 1.1, 1.2)",                      // Valid
            "    circle (  0.1   1.1   ,    1.2   )   ", // Valid
            "circle(1 1, 1)",                            // Valid
            "circl(0.1 1.1, 1.2)",                       // Invalid (type)
            "circle(0.1.1 1.1.1, 1.1.2)", // Invalid (double dot in floats)
            "circle",                     // Invalid (missing entry bracket)
            "circle(",                    // Invalid (missing points)
            "circle(0.1 1.1)",            // Invalid (missing , after point)
            "circle(0.1 1.1, 1.1 1.1)",   // Invalid (point instead of double)
            "circle(0.1 1.1, 1.2"         // Invalid (missing closing bracket)
    };
    for (int i = 0; i < 10; i++) {
        if (i < 3)
            ASSERT_FALSE(parseInputString(strings[i], &object));
        else
            ASSERT_TRUE(parseInputString(strings[i], &object));
    }
}
