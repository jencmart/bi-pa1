#include <stdio.h>

void factorizeNumber(int cislo){
	int i;

	for(i=2; i <= cislo; i++){

		if(cislo%i == 0){
			int naKolikatou = 1;
			printf("%d^", i);
			cislo = cislo/i;

			while(cislo%i == 0){
				cislo = cislo/i;
				naKolikatou+=1;
			}

			printf("%d", naKolikatou);
			if(cislo == 1)
				     return;

			printf("+");
		}

	}

	return;
}

void nactiCislo( int * cislo){
	char znak;
	while( scanf("%d", cislo) != 1 ){
		printf("Spatny vstup. Zkus to znovu.... :-)\n\n");
		while(scanf("%c", &znak) && znak != '\n' ){ 
		}
		printf("Zadej cislo:\n");

	}
}

int main(void){
		int cislo;


	printf("Zadej cele cislo:\n");
	nactiCislo( &cislo);

	if(cislo == 1 || cislo == -1 || cislo == 0){
		printf("%d = %d\n", cislo, cislo);
		return 0;
	} else if(cislo < 0){
		cislo *= -1;
		printf("-%d = -1*(", cislo);
		factorizeNumber(cislo);
		printf(")");
	} else{
	printf("%d = ", cislo);
	factorizeNumber(cislo);
    }
	printf("\n");

return 0;
}