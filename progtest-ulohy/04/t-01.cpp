#include <stdio.h>

#define MAX 2000

int seradPole( pole[], velikostPole ){
	int i, j;

	





return 0;
}


int main(void){

	int i, velikostPole, nulaNactena = 0 ;
	int seznamPrefabrikatu[MAX] = {0} ; 

	
	for (i= 0; i<MAX ; i++ ){
		if ( scanf("%d", nactHodnot) != 1 || nactHodnot < 0 ){ /* zaprne cislo | zadny vstup | neni cislo */
			printf("Spatny vstup\n");
			return 1;
		}

		if(nactHodnot == 0){
			if(i == 0){ /* nebyla nactena ani jedna hodnota */
				printf("Spatny vstup\n");
				return 0;
			}

			nulaNactena = 1;
			break;
		}

		else{
			seznamPrefabrikatu[i] = nactHodnot;
		}
	}


	/* bylo nacteno vic jak 2000 hodnot */
	if( ! nulaNactena ){
		printf("Spatny vstup\n");
		return 1;
	}

	velikostPole = i;	

	/*ale pole musi min minimalne dva prvky    */
	if( seradPole(seznamPrefabrikatu, velikostPole) ){
		printf("Spatny vstup\n");
	}
	


	
}
