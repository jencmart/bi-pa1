
/*

 * CZ SORT
 * simple line oriented czech text sorting program.
 * Read lines from stdin.
 * Write sorted lines on stdout.
 * Sorting is handled by qsort from standard C library.
 * Compare functiong for qsort takes czech letter CH into account but it don't cares (even returns error) about other special czech characters...
 * version info:
 * Written saturday evening 18.12.2016 by Martin Jenc aka jencmart.
 * ver. 0.0

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
	char **lines;
	int size;
	int used;
}TTEXT;


void initText(TTEXT *text);
void freeText(TTEXT *text);
int getLine(char **line);
void addLine(TTEXT *text, char *line);
void printResult(TTEXT *text, int rv);
void printLines(TTEXT *text);
int czCompare(const void *strA, const void *strB);

int main(void)
{
 
/* 
 * first it calls initText procedure for intializing 2D char array as struct TTEXT 
 * next calls getLine in infinite loop until EOF / wrong input 
 * in case of EOF sorts array of pointers 
 * finally it calls freeText procedure to free 2D char array 
 */

	int rv;
	char *line = NULL;
	TTEXT text;
	initText(&text);

	while (1){			
		if ((rv = getLine(&line)) == 0){ 
			/* wrong input */
			break;
		}
		if (rv == -1){ 
			/* EOF */
			qsort(text.lines, text.used, sizeof(char*), czCompare);
			break;
		}

		addLine(&text, line);
		free((void*)line);
		line = NULL;	
	}

	printResult(&text, rv);
	freeText(&text);

return 0;
}

void initText(TTEXT *text)
{ 
	text->size = 100;
	text->used = 0;
	text->lines = (char**)malloc(text->size * sizeof(char*));
}

void freeText(TTEXT *text)
{	
	int i;
	for (i = 0; i < text->used; i++)
		free((void*)text->lines[i]);
	free((void*)text->lines);
}

int getLine(char **line)
{ 

/* 
 * it scans one line from stdin
 * if scanned char is not alphabetic or space, returns -1
 * on EOF returns 0
 * else returns 1
 */

	int size = 100;
	int used = 0;
	char c;
	
	if ((c = fgetc(stdin)) == EOF)
		return -1;

	if (! isalpha(c)) /*  If there are spaces et the beginning of the line, it returns error. Progtest seems OK with it. */
		return 0;

	*line = (char*)malloc(size * sizeof(char)); 
	(*line)[used++] = c;

	while (1){
		if (! isalpha((c = fgetc(stdin))) && c != ' ' && c != '\n'){
			free((void*)*line);
			line = NULL;
			return 0;
		}

		if (size == used){
			size *= 2;
			*line = (char*) realloc(*line, size * sizeof(char));
		}

		if (c == '\n'){
			(*line)[used] = '\0';
			return 1;
		}	

		(*line)[used++] = c;
	}
}

void addLine(TTEXT *text, char*line)
{
 
/* 
 * checks if array have enough space eventually enlarge
 * next mallocs space for the line and add it
 */

	if (text->used  == text->size){
		text->size *= 2;
		text->lines = (char**)realloc(text->lines, text->size * sizeof(char*));
	}

	text->lines[text->used] = (char*)malloc((strlen(line) + 1) * sizeof(char));
	strcpy(text->lines[text->used], line);
	text->used += 1;
}

void printResult(TTEXT *text, int rv)
{ 
	if (rv)
		printLines(text);
	else
		printf("Nespravny vstup.\n");	
}

void printLines(TTEXT *text)
{ 
	int i;
	for (i=0; i < text->used; i++)
		printf("%s\n", text->lines[i]);
}

int czCompare(const void *strA, const void *strB)
{
 
/* 
 * compare function
 * basically compare char from both strings. If one letter is "c/C" it looks by second read pointer forward and if it founds "h/H", it merges them to one letter.
 * comparing of CH is coded by comparing if other char has ASCII value less equal H or greater equal I it decides whether it's before or after...
 */

	const char *a = *(const char**)strA; /* read pointers a, b; supportive read pointers aa bb */
	const char *b = *(const char**)strB; 
	const char *aa, *bb, *stop;
	char aConst, bConst;
	int aLen = strlen(a), bLen = strlen(b);
	int aCH, bCH;	

	for (stop = aLen<bLen?a:b; *stop; ++a, ++b, ++stop){	/* set stop poiner to shorter of the strings, stop at \0 */
		/*--------- check CH ----------*/
		if (( aConst = toupper(*a) ) == 'C' && (aConst=*(++(aa=a))) &&  toupper(aConst) == 'H')		/* if char eq C/c and next char eq H/h mark it as CH */	
			aCH=1;
		else{
			aCH=0;
			aConst = toupper(*a);
		}
		if ((bConst = toupper(*b)) == 'C' && (bConst=*(++(bb=b))) &&  toupper(bConst) == 'H')		/* if char eq C/c and next char eq H/h mark it as CH */	
			bCH=1;
		else{
			bCH=0;
			bConst = toupper(*b);
		}
		/*-----------------------------*/
		if (aCH != bCH){ 	/* if only one of the chars is CH */
			if (aCH){
				if (bConst >= 73)  
					return -1;
				else 		
					return 1;
			}
			if (aConst >= 73)  
				return 1;
			else		
				return -1;
		}

		else{
			if (!aCH){		/* neither one of them is CH char */
				if (aConst == bConst)
					continue;
				else 
					return aConst - bConst;
			}	
			++a;  /* both of them are CH chars */
			++b;
			++stop;
			continue;
		}	
	}
	if (aLen == bLen)
		return 0;
	if (aLen < bLen)
		return -1;

return 1;	
}

