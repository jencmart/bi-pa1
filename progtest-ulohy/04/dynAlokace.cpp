#include <stdio.h>
#include <stdlib.h>

#define MAX_VEL 100000000000000

int main(void){
	int *p_pole;


	if ( (p_pole = (int *)malloc(MAX_VEL*sizeof(int))) == NULL){
		printf("Nedostatek pameti!\n");
		return 0;
	}

free((vodi *) p_pole);

return 0;
}
