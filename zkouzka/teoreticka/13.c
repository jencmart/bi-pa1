#include <stdio.h>
int main(){
	int i;
	int a=0;
	for (i=-256;i<256;i++)
		if(i!=-i){
			printf("# ");
			a++;
		}
	printf(" %d ",a);
}

