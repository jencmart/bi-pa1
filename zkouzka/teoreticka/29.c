#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
	const char * a="Progtest rulez!";
	const char * b=a;
	char *c = strcpy ((char*) malloc(28),b);
	printf("%d %d %d ",!strcmp(a,c),a==b,b==c);
	free(c);
	return 0;
}
	
