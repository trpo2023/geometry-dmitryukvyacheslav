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
