#include <stdio.h>
int rec(unsigned int x, unsigned int y){
	if (!x && !y) return 0;
	printf("x je %d, ",x);
	printf("y je %d\n",y);
	return rec (y>>1,x>>1)+(x&1)+(y&1);
}

int main(void){
	int a=26;
	a=a>>1;
	printf("moje zkouska: %d\n",a);
	printf("%d %d ",rec(26,24),rec(26,28));
	return 0;
}


