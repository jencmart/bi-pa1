teoreticka/09.c                                                                                     0000640 0001750 0001750 00000000200 12704001373 013051  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
#include <limits.h>
int main(){
	int a=35,b=35,c=35;
	printf ("%s",a==b==c ? "true" : "false");
	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                teoreticka/11.c                                                                                     0000644 0001750 0001750 00000000242 12704001373 013054  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
#include <limits.h>
int main(){
	#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
	int  a=6, b=5;
	printf("%d %d %d ",MIN(a++,b++),a,b);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                              teoreticka/12.c                                                                                     0000640 0001750 0001750 00000000324 12704001373 013052  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
unsigned safeSizeof (unsigned int ** x)
{
	if(!x) return 0;
	return sizeof(x);
}
int main(){
	unsigned int * foo[199];
	printf(" %u %u ",(unsigned) sizeof(foo),safeSizeof(foo));
	return 0;


}
                                                                                                                                                                                                                                                                                                            teoreticka/13.c                                                                                     0000640 0001750 0001750 00000000211 12704001373 013046  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
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

                                                                                                                                                                                                                                                                                                                                                                                       teoreticka/14.c                                                                                     0000640 0001750 0001750 00000000177 12704001373 013062  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
#include <limits.h>
int main(void){
	int a=5,b=5,c=5;
	printf ("%s",a==b==c ? "tru" : "fals");
	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                 teoreticka/19.c                                                                                     0000640 0001750 0001750 00000000310 12704001373 013054  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
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
	
                                                                                                                                                                                                                                                                                                                        teoreticka/25.c                                                                                     0000640 0001750 0001750 00000000223 12704001373 013054  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
#define MIN(a,b) (a>b) ? b:a
int main(){
	int a=8;
	int b=7;
	printf("%d ",MIN(a++,b++));
	printf("%d %d\n",a,b);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                                             teoreticka/27.c                                                                                     0000640 0001750 0001750 00000000134 12704001373 013057  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(){
	unsigned int a=502,b=3708;
	a=a+31*b;
	printf("%d\n",a);
}

                                                                                                                                                                                                                                                                                                                                                                                                                                    teoreticka/28.c                                                                                     0000640 0001750 0001750 00000000134 12704001373 013060  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(void){
	unsigned char y="g";
	printf("%c ",y);
	return 0;



}

                                                                                                                                                                                                                                                                                                                                                                                                                                    teoreticka/29.c                                                                                     0000640 0001750 0001750 00000000361 12704001373 013063  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
	const char * a="Progtest rulez!";
	const char * b=a;
	char *c = strcpy ((char*) malloc(28),b);
	printf("%d %d %d ",!strcmp(a,c),a==b,b==c);
	free(c);
	return 0;
}
	
                                                                                                                                                                                                                                                                               teoreticka/46.c                                                                                     0000644 0001750 0001750 00000000207 12704001373 013065  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include<stdio.h>
#include<string.h>
int main(){
	char a[]="abcde";
	char *b=a;
	strcpy (a,"aaaa");
	printf("%s\n",b);
	return 0;


}

                                                                                                                                                                                                                                                                                                                                                                                         teoreticka/47.c                                                                                     0000644 0001750 0001750 00000000154 12704001373 013067  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(){
	char a[100];
	fgets(a,sizeof(a),stdin);
	printf("%s\n",a);
	return 0;

}



                                                                                                                                                                                                                                                                                                                                                                                                                    teoreticka/53.c                                                                                     0000644 0001750 0001750 00000000452 12704001373 013065  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
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


                                                                                                                                                                                                                      teoreticka/54.c                                                                                     0000644 0001750 0001750 00000000353 12704001373 013066  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
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

                                                                                                                                                                                                                                                                                     teoreticka/58.c                                                                                     0000640 0001750 0001750 00000000316 12704001373 013065  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int foo (int a[][13],int b[][7]){
	return sizeof(*a)-sizeof(*b);
}
int main(void){
	int a[23][13];
	int b[23][7];
	printf("%d\n",foo(a,b));
	printf("sizeof int: %lu\n",sizeof(int));

}


                                                                                                                                                                                                                                                                                                                  teoreticka/59.c                                                                                     0000640 0001750 0001750 00000000364 12704001373 013071  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include<stdio.h>

int rec(int n, int *a,int *b){
	return n==1 ? *a==*b : rec(n/2,b,a) + rec((n+1)/2,a+ n/2, b+ n/2);

}

int main(void){
	int a[]={5,9,9,6,4,0};
	int b[]={1,7,2,9,2,0};
	printf("%d %d\n",rec(5,a,b),rec(6,b,a));
	return 0;

}


                                                                                                                                                                                                                                                                            teoreticka/hl.c                                                                                     0000644 0001750 0001750 00000000026 12704001373 013236  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>



                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          teoreticka/wiki01.c                                                                                 0000644 0001750 0001750 00000000164 12704001373 013742  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include<stdio.h>
int main(){
	int i,n,j=0;
	scanf("%d",&n);
	for (i=0;i<n;i++,n-=i)
		j++;
	printf("%d\n",j);


}

                                                                                                                                                                                                                                                                                                                                                                                                            teoreticka/wiki02.c                                                                                 0000644 0001750 0001750 00000000320 12704001373 013735  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include<stdio.h>
int main()
{
long long * A[53];
long long B[53][53];
long long C[(53,53)];
long long (*D)[53];
//		B[13][1]=1;
//		C[13]=1;
//segfault 		A[13][1]=5;
//error		C[13][1]=1;
//error		A=5;



}

                                                                                                                                                                                                                                                                                                                teoreticka/wiki03.c                                                                                 0000644 0001750 0001750 00000000363 12704001373 013745  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include<stdio.h>
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

                                                                                                                                                                                                                                                                             teoreticka/wiki04.c                                                                                 0000644 0001750 0001750 00000000227 12704001373 013745  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
#include <stdlib.h>
int main(){
	int i;
	char * str = (char *) realloc (NULL,71);
	for (i=0;i<75;i++)
		str[i]=1;
	free(str);

}



                                                                                                                                                                                                                                                                                                                                                                         teoreticka/zz2.c                                                                                    0000640 0001750 0001750 00000000143 12704001373 013354  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(){
	char x='Z';
	double y='Z';
	printf ("%c = %c ",x,y);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                             teoreticka/zz3.c                                                                                    0000640 0001750 0001750 00000000141 12704001373 013353  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(){
	char x='Z';
	char y='Z';
	printf ("%d = %f ",x,y);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                               teoreticka/zz4.c                                                                                    0000640 0001750 0001750 00000000143 12704001373 013356  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(){
	char x='Z';
	double y='Z';
	printf ("%d = %d ",x,y);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                             teoreticka/zz5.c                                                                                    0000640 0001750 0001750 00000000140 12704001373 013354  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(){
	int x='Z';
	char y='Z';
	printf ("%f = %d ",x,y);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                teoreticka/zz6.c                                                                                    0000640 0001750 0001750 00000000141 12704001373 013356  0                                                                                                    ustar   tadeas                          tadeas                                                                                                                                                                                                                 #include <stdio.h>
int main(){
	char x='Z';
	char y='Z';
	printf ("%d = %d ",x,y);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               