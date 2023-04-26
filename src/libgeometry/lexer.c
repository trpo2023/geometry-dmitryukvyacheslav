#include <libgeometry/lexer.h>
#include <string.h>

// strtok special needs edition
// returns -1 if no delim found
// else returns how many chars it had read
int readTokenUntil( char* line,  
                    char delim, 
                    char* output){
    int len = strlen(line);
    for (int i = 0, j = 0; i < len; i++){
        if (line[i] != ' ' && line[i] != delim) {
            output[j] = line[i]; 
            j++;
        }
        if (line[i] == '\0' || line[i] == delim)
            return i; 
    }
    return -1;
}

// read type
// raises error and returns nonzero if failed
int lex_get_type(char line);
