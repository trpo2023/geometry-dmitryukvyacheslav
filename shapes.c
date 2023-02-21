#include "shapes.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

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
	
	shape* s1 = malloc(sizeof(shape));
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
	if (!strcmp(token1, "circle")) {s1->type = Circle; s1->ptscnt = 1;}
	else if	(!strcmp(token1, "triangle")) {s1->type = Triangle; s1->ptscnt = 4;}
	else if	(!strcmp(token1, "polygon")) {s1->type = Polygon; s1->ptscnt = 0;}
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

	// Дальше читаем строку из цифр и максимум одной точки до пробела.
	// Но если наш аргумент последний, то не забываем проверять ещё и на ')'.

	s1->pts = malloc(sizeof(point)*s1->ptscnt);

	for(int c = 0; c < s1->ptscnt; c++) {
		for (int xy = 0; xy < 2; xy++) {
			while(input[i] == ' ' && input[i] != '\0') i++;
		
			if (!isdigit(input[i])) {
				char expstr[64];
				sprintf(expstr, "встречено '%c'", input[i]);
				throwError(i, input, "ожидалась цифра", expstr);
				return NULL;
			}
			
			char digit[128] = {0};
			int wasThereAPoint = 0;
			j = 0;
			while(isdigit(input[i]) || input[i] == '.') {
				if (input[i] == '.') wasThereAPoint++;
				if (wasThereAPoint > 1) {
					throwError(i, input, "встречена '.'", "ожидалась дробная часть");
					return NULL;
				}
				digit[j] = input[i];
				j++;
				i++;
			}
			if (!xy) s1->pts[c].x = atof(digit);
			else s1->pts[c].y = atof(digit);
		}
		// ожидаем запятую, если круг или точка последняя
        // иначе ожидаем ')'
		if (c != s1->ptscnt-1 || s1->type == Circle) {
			while(input[i] == ' ' && input[i] != '\0') i++;
				if (input[i] == '\0') {
				throwError(i, input, "ожидалось ','", 
					"встречен конец строки");
				return NULL;
			}
			if (input[i] != ','){
				char expstr[64];
					sprintf(expstr, "встречено '%c'", input[i]);
					throwError(i, input, "ожидалось ','", expstr);
					return NULL;
			return NULL;
			}
		}
        i++;
	}
	if (s1->type == Circle) {
		// вычитываем ещё одно число 
		while(input[i] == ' ' && input[i] != '\0') i++;
		
		if (!isdigit(input[i])) {
			char expstr[64];
			sprintf(expstr, "встречено '%c'", input[i]);
			throwError(i, input, "ожидалась цифра", expstr);
			return NULL;
		}
		
		char digit2[128];
		int wasThereAPoint = 0;
		j = 0;
		while(isdigit(input[i]) || input[i] == '.') {
			if (input[i] == '.') wasThereAPoint++;
			if (wasThereAPoint > 1) {
				throwError(i, input, "встречена '.'", "ожидалась дробная часть");
				return NULL;
			}
			digit2[j] = input[i];
			j++;
			i++;
		}
		s1->radius = atof(digit2);
	}
	
	// ожидаем закрывающую скобку
	while(input[i] == ' ' && input[i] != '\0') i++;
		if (input[i] == '\0') {
		throwError(i, input, "ожидалось ')'", 
			"встречен конец строки");
		return NULL;
	}
	if (input[i] != ')'){
		char expstr[64];
			sprintf(expstr, "встречено '%c'", input[i]);
			throwError(i, input, "ожидалось ')'", expstr);
			return NULL;
	return NULL;
	}
	return s1;
}
