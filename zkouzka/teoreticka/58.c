#include <stdio.h>
int foo (int a[][13],int b[][7]){
	return sizeof(*a)-sizeof(*b);
}
int main(void){
	int a[23][13];
	int b[23][7];
	printf("%d\n",foo(a,b));
	printf("sizeof int: %lu\n",sizeof(int));

}


