#include<stdio.h>
#include<string.h>
int main(){
	char a[]="abcde";
	char *b=a;
	strcpy (a,"aaaa");
	printf("%s\n",b);
	return 0;


}

