#include<stdio.h>
int main()
{
	unsigned char * A[57];
	unsigned char * B[57][57];
	unsigned char * C[(57,57)];
	unsigned char (*D)[57];

//segfault	A[53][34]='h';
//warning	D='a';
//warning   C[53]='a';
// D[53][34]='a';
//error	A='5';



}

