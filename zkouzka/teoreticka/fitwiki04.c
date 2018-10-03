#include <stdio.h>
#include <stdlib.h>
int main(){
	int i;
	char * str = (char *) realloc (NULL,71);
	for (i=0;i<75;i++)
		str[i]=1;
	free(str);

}



