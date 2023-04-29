#include <ctype.h>
#include <libgeometry/lexer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void errorBody(int column, char* line)
{
    if (line != NULL) {
        printf("%s\n", line);
        for (int i = 0; i < column; i++)
            printf(" ");
        printf("^\n");
        printf("Error in column %d:", column);
    }
    /*else
        printf("Error: input is empty.\n");
    */
}
void expected(int column, char* line, char* expected, char* got)
{
    errorBody(column, line);
    printf("\nexpected %s; got '%s'.\n", expected, got);
}
static void expected_char(int column, char* line, char expected, char got)
{
    errorBody(column, line);
    printf("\nexpected '%c'", expected);
    if (got != '\0')
        printf("; got '%c'.\n", got);
    else
        printf("\n");
}

// strtok special needs edition
// returns -1 if no delim found
// else returns how many chars it had read
int readTokenUntil(char** line, char delim, char* output, char* origptr)
{
    int len = strlen(*line);
    int i = 0, j = 0;
    while ((*line)[i] == ' ' && (size_t)i < strlen(*line))
        i++;
    for (; i < len; i++) {
        if ((*line)[i] != ' ' && (*line)[i] != delim) {
            if (!isalpha((*line)[i]) && !isdigit((*line)[i])
                && (*line)[i] != '.') {
                expected_char(
                        (*line - origptr) + i, origptr, delim, (*line)[i]);
                return -1;
            }
            output[j] = tolower((*line)[i]);
            j++;
        }
        if ((*line)[i] == '\0' || (*line)[i] == delim) {
            *line += i + 1;
            return i + 1;
        }
    }
    expected_char((*line - origptr) + i, origptr, delim, '\0');
    return -1;
}

// read type
// raises error and returns nonzero if failed?
// " circle   ( "
int lex_get_type(char** line, shape* object)
{
    char typestr[16] = {'\0'};

    int syms_read = readTokenUntil(line, '(', typestr, *line);
    //*line += syms_read;
    if (syms_read < 0)
        return -1;
    if (!strcmp(typestr, "circle")) {
        object->type = Circle;
        object->ptscnt = 1;
        return syms_read;
    } else if (!strcmp(typestr, "triangle")) {
        object->type = Triangle;
        object->ptscnt = 4;
        return syms_read;
    } else if (!strcmp(typestr, "polygon")) {
        object->type = Polygon;
        object->ptscnt = 0;
        return syms_read;
    }
    expected(
            strlen(typestr),
            *line,
            "'circle',\
'triangle' or 'polygon'",
            typestr);

    return -1;
}

static double
lex_get_double(char** line, char delim, char* origptr, int* errflag)
{
    char buf[64] = {'\0'};
    int read = readTokenUntil(line, delim, buf, origptr);
    char* endptr;
    double d = strtod(buf, &endptr);
    // Evil pointer hack to line up
    // the symbol strod didn't like
    // with corresponding symbol in string.
    if (*endptr != delim && *endptr != '\0') {
        char errstr[] = "[0-9] or '''";
        errstr[10] = delim;
        char errstr2[] = {*(endptr), '\0'};
        expected(
                (*line - origptr) + (endptr - buf) - read + 1,
                origptr,
                errstr,
                errstr2);
        *errflag = 1;
    }
    return d;
}
int lex_get_last_point(char** line, shape* object, char* origptr)
{
    int errflag = 0;
    object->pts[object->ptscnt - 1].x
            = lex_get_double(line, ' ', origptr, &errflag);
    object->pts[object->ptscnt - 1].y
            = lex_get_double(line, ')', origptr, &errflag);
    return errflag;
}
int lex_get_point(char** line, shape* object, int i, char* origptr)
{
    int errflag = 0;
    object->pts[i].x = lex_get_double(line, ' ', origptr, &errflag);
    object->pts[i].y = lex_get_double(line, ',', origptr, &errflag);
    return errflag;
}
int lex_get_radius(char** line, shape* object, char* origptr)
{
    int errflag = 0;
    object->radius = lex_get_double(line, ')', origptr, &errflag);
    return errflag;
}