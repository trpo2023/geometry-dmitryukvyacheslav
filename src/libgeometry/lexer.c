typedef enum {
  circle,
  shape,
  polygon
} spType;

const char* names = {"circle", "shape", "polygon"};

typedef struct Point {
  double x;
  double y;
} point;
  
typedef struct Shape {
  double radius;
  spType shapetype;
  int    pointcount;
  point* points;
} shape;

// нижеизложенные функции принимают поток и сами двигаются по потоку
// принимают указатель на строки "что ожидалось" и "что получено"
int* getName(char** expected, char** got)
