#include <stdio.h>
#include <string.h>


int isPrefix(char * prefix, char * string){
	/* returns +1 / -1 for  possitive/negative and 0 if it's same string */
	size_t prefLen = strlen(prefix);
	size_t strLen = strlen(string);
	if( prefLen >= strLen ){
			if( ! strcmp(prefix, string) )
				return 0;
			else
				return -1;
	}
	else
		if ( ! strncmp(prefix, string, prefLen) ) 
			return 1;
		return -1;
}
	

int main(){
	int rv;
	char prefix[10];
	char string[10];
	while(1){
		if( scanf(" %s %s", prefix, string) != 2)
			return 0;
		rv = isPrefix(prefix, string);
		

	if(rv>0)
		printf("+\n");
	else if(rv<0)
		printf("-\n");
	else
		printf("=\n");
	}




return 0;
}
