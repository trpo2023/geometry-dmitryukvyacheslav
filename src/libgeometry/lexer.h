#include <libgeometry/parser.h>
#pragma once

int lex_get_type(char** line, shape* object);
int lex_get_point(char** line, shape* object, int i, char* origptr);
int lex_get_radius(char** line, shape* object, char* origptr);
int lex_get_last_point(char** line, shape* object, char* origptr);

void expected(int column, char* line, char* expected, char* got);