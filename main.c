#include <stdio.h>
#include <ctype.h>
#include <string.h>

enum ShapeTypes {
	Circle = 10,
	Triangle = 11,
	Polygon = 12
};

typedef struct Point{
	float x;
	float y;
} point;

typedef struct Shape{
	enum ShapeTypes type;
	int ptscnt;
	int radius;
	struct Point pts[];
} shape;


/*
	Вывести ошибку вида:
	
	circlee(1.0 2.0, 3)
	^
	Ошибка в столбце 0: 
		ожидалась строка 'circle', 'triangle' или 'polygon';
		встречена строка 'circlee'.

	Принимает:
		int 	- индекс символа (колонки), на котором произошла ошибка;
		char* 	- номер 
		char* 	- строка с указанием того, что ожидалось встретить;
		char*	- строка с указанием того, что было получено.
	
	Ничего не возвращает.
*/
void throwError(int column, char* line, char* expected, char* got){
	printf("\n");
	if (line != NULL) { 
		printf("%s\n", line);
		for(int i = 0; i < column; i++) printf(" ");
		printf("^\n");
		printf("Ошибка в столбце %d:\n\t%s;\n\t%s.\n", column, expected, got);
	}
	else printf("Ошибка: пустой ввод.\n");
}


/* 	
	Получить первую фигуру из строки, начиная с определённого символа в ней.

	Принимает: 
		char* 	- указатель на строку; 
		int		- её длину; 
		int		- индекс начального символа.

	Возвращает: 
		указатель на переменную составного типа shape.
*/
shape* parseInputString(char* input, int startSymbol){

	/* 	Читаем входную строку до первого непробельного символа.
		Выводим ошибку, если нашли конец строки или не букву на латинице.*/
	int i = 0;	
	while(input[i] == ' ' && input[i] != '\0') i++;
	if (!isalpha(input[i])){
		// Вообще ничего не нашли
		if (input[i] == '\0') {
			throwError(i, NULL, "ожидалась строка 'circle', 'triangle' или 'polygon'", 
			"встречен конец строки");
		}
		// Нашли неалфавитный символ
		else 
			throwError(i, input, "ожидалась строка 'circle', 'triangle' или 'polygon'", 
			"встречен неалфавитный символ");
		return NULL;
	}
	
	/* 	Читаем первый токен до первого пробела или управляющего символа.
		На неалфавитный бред выдаём ошибку.		
		На алфавитные строки сильно длинее наших имён выдаём ошибку.
		На строки, не соответствующие нашим именам выдаём ошибку.		*/
	
	int tempColumnForError = i;
	char token1[16];
	int j = 0;
	while (isalpha(input[i]) && j < 15){
		token1[j] = tolower(input[i]);
		i++;
		j++;
	}
	if (j == 15) {
		char expstr[128];
		sprintf(expstr, "встречена длинная последовательность '%s...'", token1);
		throwError(tempColumnForError, input, "ожидалась строка 'circle', 'triangle' или 'polygon'", 
			expstr);
		return NULL;
	}
	shape s1;
	if (!strcmp(token1, "circle")) {s1.type = Circle; s1.ptscnt = 2;}
	else if	(!strcmp(token1, "triangle")) {s1.type = Triangle; s1.ptscnt = 4;}
	else if	(!strcmp(token1, "polygon")) {s1.type = Polygon; s1.ptscnt = 0;}
	else {
		char expstr[128];
		sprintf(expstr, "встречена строка '%s'", token1);
		throwError(tempColumnForError, input, "ожидалась строка 'circle', 'triangle' или 'polygon'", 
			expstr);
		return NULL;
	}
	
	//printf("[ОТЛАДКА] type %d, ptscnt %d\n\n",	s1.type, s1.ptscnt);

	// Ищем '(', не не находим или находим другое - ошибка
	while(input[i] == ' ' && input[i] != '\0') i++;
	if (input[i] == '\0') {
		throwError(i, input, "ожидалось '('", 
			"встречен конец строки");
		return NULL;
	}
	if (input[i] != '(') {
		char expstr[64];
		sprintf(expstr, "встречено '%c'", input[i]);
		throwError(i, input, "ожидалось '('", 
			expstr);
		return NULL;
	}
	i++;
	/* 	Начинаем записывать аргументы
		Не нашли число или нашли что-то другое - ошибка */
	while(input[i] == ' ' && input[i] != '\0') i++;
	
	if (!isdigit(input[i])) {
		char expstr[64];
		sprintf(expstr, "встречено '%c'", input[i]);
		throwError(i, input, "ожидалась цифра", expstr);
		return NULL;
	}
	
	// Дальше читаем строку из цифр и максимум одной точки до пробела.
	// Но если наш аргумент последний, то не забываем проверять ещё и на ')'.

	// Напоминалочка себе: поместить всё это в цикл по количеству аргументов.
	return 1;
}

int main(void){
	// Между токенами может быть сколько угодно пробелов
	char* input = "    circle   (a  b ";
	shape* temp = parseInputString(input, 0);
	if (temp == NULL) return -1;
	else return 0;
}
