#include<stdio.h>
int main(){
	int i,n,j=0;
	scanf("%d",&n);
	for (i=0;i<n;i++,n-=i)
		j++;
	printf("%d\n",j);


}

