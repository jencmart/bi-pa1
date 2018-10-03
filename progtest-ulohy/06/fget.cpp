#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){
	char radek[5];
	int i;
	while( fgets(radek, 5, stdin) != NULL){
		printf("---");
		for(i=0; i<5; i++)
			printf("%c", radek[i]);
		printf("\n");

	}
	printf("dostal jsem EOF\n");


return 0;
}
