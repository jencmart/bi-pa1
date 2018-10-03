#include <stdio.h>
#define MIN(a,b) (a>b) ? b:a
int main(){
	int a=8;
	int b=7;
	printf("%d ",MIN(a++,b++));
	printf("%d %d\n",a,b);
	return 0;
}

