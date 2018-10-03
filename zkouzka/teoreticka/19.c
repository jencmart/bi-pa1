#include <stdio.h>
int main(){
	int sum=0,a;
	printf(" ");
	scanf("%d",&a);
	switch(a){
		default: sum += 3;
		case  0: sum += 2;
		case  1: sum += 2;
		case  3: sum += 2;
	}
	printf("%d\n",sum);
}
	
