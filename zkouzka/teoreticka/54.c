#include <stdio.h>
int main(void){
	char a[]={3,10,4,8,0};
	char * b;
	for (b=a;b<a+5;b++){
		if (b>a) printf (".");
		printf ("*b %d\n",*b);
		printf ("*a %d\n",*a);
		printf ("b %d\n",b);
		printf ("a+5 %d\n",a+5);
	}
	return 0;

}

