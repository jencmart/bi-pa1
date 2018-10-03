#include <stdio.h>
#include <string.h>
#include <stdlib.h>




char *getLine(){
	int lastChar=0;
	int size = 5;
	char *line = NULL;
	while( 1 ){
		size *= 2;
		line = (char*)realloc(line , size);
		if ( fgets(line + lastChar, size-lastChar, stdin) == NULL ){
			free(line);
			break;	
		}
		lastChar = strlen(line); 
		if(line[lastChar-1] == '\n')
			return line;
	}
/*EOF*/	
return NULL;		
}

void printLine(char *line){
	char *p; 
	int i;
	for(p = line ; p < line + strlen(line) -1 ;)
		printf("%c ", *p++);
	printf("\n");
}

int main(){
	char *line;
	while(1){
	if( (line=getLine() ) == NULL){
		break;
	}
	printLine(line);
	free(line);
	}

return 0;
}
