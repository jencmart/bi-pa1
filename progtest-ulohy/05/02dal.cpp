#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int **pArray;
	int used;
	int size;
} TPOLE2;


int min(int a, int b){
	return a<b?a:b;
}

void insertArray(TPOLE2 * roadMap, int radek, int sloupec, int cislo){
	int i, tmp;	

	if(roadMap->used==roadMap->size){
		tmp = roadMap->size;
		roadMap->size *= 2;
		roadMap->pArray = (int**) realloc(roadMap->pArray, roadMap->size  * sizeof(int*)); /*prodluz pole pointeru*/
		for(i=0; i < tmp ; i++){ /*prodluz puvodni alokovana pole*/
			roadMap->pArray[i] = (int*) realloc( roadMap->pArray[i] , roadMap->size * sizeof(int) );
		}

		for(i=tmp ; i< roadMap->size; i++){ /*alokuj nova pole*/
			roadMap->pArray[i] = (int*) malloc( roadMap->size * sizeof(int));
		} 
	}

	if( sloupec == (roadMap->used ) ){
		roadMap->used++;
	}

	roadMap->pArray[radek][sloupec] = cislo;
/*	printf("Zapsal jsem cislo: %d na pozici %d %d. Pouzito %d\n", roadMap->pArray[radek][sloupec], radek, sloupec, roadMap->used);*/
return;
}


int construct( TPOLE2 *roadMap ){
	char znak;
	int nosnost, i;

	if ( scanf(" %c", &znak) != 1 ||  !(znak == '[') )
		return 1;

	while(1){
		if ( scanf("%d %c", &nosnost, &znak) != 2 || nosnost < 1 || ( znak != ',' && znak != ']') )
			return 1;

		/*vlozeni na prvni radek*/
		if (roadMap->used == 0)
			insertArray(roadMap, 0, 0 , nosnost);
		else
			insertArray(roadMap, 0, roadMap->used, min(nosnost, roadMap->pArray[0][(roadMap->used)-1] ) );


		/*dopocitani sloupecku */
		for ( i=1; i < (roadMap->used)  ; i++ ){
			if ( i == (roadMap->used)-1){
				insertArray(roadMap, i, i, nosnost);
			/*	printf("\nZapsan posledni clen\n"); */
				break;
			}
			insertArray(roadMap,  i, (roadMap->used)-1,  min( nosnost , roadMap->pArray[i][ (roadMap->used) -2 ]) ) ;
		}

		if(znak == ']')
			return 0;
	}

		

return 0;
}




int limits(TPOLE2 *roadMap){
	char znak;
	int nosnost, pocPoz, i;

	if (scanf("%d", &pocPoz) != 1 || pocPoz<0 || pocPoz >= roadMap->used ) {
		return 1;
	}
	
	if ( scanf(" %c", &znak) != 1 ||  !(znak == '[') ){
		return 1;
	}


	while(1){

		if ( scanf("%d %c", &nosnost, &znak) != 2 || nosnost < 1 || ( znak != ',' && znak != ']') )
			return 1;
		if( pocPoz >= roadMap->used) /*prevence moc dlouheho senzamu*/
			return 1;
		
		/* prepocti konkretni sloupecek */
			/* 1. zmenhodnotu v prvnim radku */
		if(pocPoz == 0 ){
			insertArray(roadMap,0, 0, nosnost);
		}
		else{
			insertArray(roadMap, 0, pocPoz, min(nosnost, roadMap->pArray[0][pocPoz-1]) );
		}

		/*dopocitani sloupecku*/

		for(i=1 ; i<=pocPoz ; i++ ){
			if( i == pocPoz){
				insertArray(roadMap, i ,i, nosnost);
				break;
			}
			insertArray(roadMap, i, pocPoz, min(nosnost, roadMap->pArray[i][pocPoz-1]) );
		}
		

		pocPoz++;
		if(znak == ']'){
			/*dopocitej zbyle sloupecky*/
			while(pocPoz < roadMap->used){
				insertArray(roadMap, 0, pocPoz, min(roadMap->pArray[pocPoz][pocPoz]  , roadMap->pArray[0][pocPoz-1]   ) );
				for(i=1; i<=pocPoz; i++){
					if(i == pocPoz){
						continue;
					}
					insertArray(roadMap, i, pocPoz, min(roadMap->pArray[pocPoz][pocPoz] , roadMap->pArray[i][pocPoz-1] )   );

				}
			pocPoz++;
			}
		
	
			return 0;
		}
	}




return 0;
}



int load(TPOLE2 *roadMap){
	int from;
	int to;

	if ( scanf("%d%d", &from, &to) != 2 || from<0 || to<from || to>=roadMap->used) {
		return 1;
	}

	else{
	printf("Maximalni naklad: %d\n", roadMap->pArray[from][to]);
	}

return 0;
}

void uvolnit(TPOLE2 * roadMap);
void initArr( TPOLE2 *roadMap, int initSize );
void err(TPOLE2 *roadMap);

int main(void){
/*	int i,j; */
	TPOLE2 roadMap;
	initArr( &roadMap, 500);
	char prikaz[10];
	printf("Prikazy:\n");

	while (1){
		if( scanf(" %10s", prikaz) == EOF )
			break;
		/*construct*/
		if ( !strcmp( prikaz, "construct") ){
			if ( construct(&roadMap) ) {
				err(&roadMap);
				return 1;
			}
		}
		/*limits*/
		else if ( ! strcmp(prikaz, "limits") ){
			if ( limits(&roadMap) ){
				err(&roadMap);
				return 1;
			}
		}
		/*load*/
		else if (! strcmp(prikaz, "load") ){
			if( load(&roadMap) ){
				err(&roadMap);
				return 1;
			}
		}

/*		else if( !strcmp(prikaz, "tiskni") ){			
			for(i=0; i< roadMap.used ; i++){
				for(j=0; j<roadMap.used ; j++){
					printf("%2d ", roadMap.pArray[i][j]);
				}
				printf("\n");
			}
		} */

		/*bad instruction*/
		else{
			err(&roadMap);
			return 1;
		}
	}


	
	uvolnit(&roadMap);

return 0;
}

void uvolnit(TPOLE2 *roadMap){
	int i;
	for(i=0; i< roadMap->size ; i++)
		free( (void*) roadMap->pArray[i]  );	
	free( (void*)roadMap->pArray);
return;
}

void initArr( TPOLE2 *roadMap, int initSize ){
	int i;
	roadMap->size=initSize;
	roadMap->used=0;	
	roadMap->pArray = (int **) malloc(roadMap->size * sizeof(int*)) ;
	for(i = 0 ; i < roadMap->size ; i++){ 
		roadMap->pArray[i] = (int *) malloc(roadMap->size * sizeof(int));
	}

return;
}

void err(TPOLE2 *roadMap){
	uvolnit(roadMap);
	printf("Nespravny vstup.\n");

return;
}
