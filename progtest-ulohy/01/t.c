#include <stdio.h>
#include <stdlib.h>

int main(int arcg, char** argv){

	double a, b;
	
	printf("zadej dve desetina na porovnani:\n");
	scanf("%lf %lf", &a, &b);

	if(a == b){
		printf("%.20f se rovna %.20f\n", a, b);
	}

	if(a < b){
		printf("%.20f je mensi nez %.20f\n", a, b);
	}
	
	if(a > b){
		printf("%.20f je vetsi nez %.20f\n", a, b);
	}

	return 0;
}
