#include <stdio.h>
#include <limits.h>
int main(){
	#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
	int  a=6, b=5;
	printf("%d %d %d ",MIN(a++,b++),a,b);
	return 0;
}

