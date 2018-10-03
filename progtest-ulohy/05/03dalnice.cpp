#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int *pArray;
	int used;
	int size;
} TPOLE2;


int min(int a, int b){
	return a<b?a:b;
}

int findMin(TPOLE2* roadMap, int from, int to){
	int i, min = roadMap->pArray[from];

	if(from == to)
		return min;

	for(i = from ; i <to ; i++)
		min = roadMap->pArray[i+1] < min ? roadMap->pArray[i+1] : min ; 

	return min;
}

void insertArray(TPOLE2 * roadMap, int sloupec, int cislo){
	if(roadMap->used==roadMap->size){
		roadMap->size *= 2;
		roadMap->pArray = (int*) realloc(roadMap->pArray, roadMap->size  * sizeof(int*)); 
	}

	if( sloupec == (roadMap->used ) )
		roadMap->used++;
	
	roadMap->pArray[sloupec] = cislo;

return;
}


int construct( TPOLE2 *roadMap ){
	char znak;
	int nosnost;

	if ( scanf(" %c", &znak) != 1 ||  !(znak == '[') )
		return 1;

	while(1){
		if ( scanf("%d %c", &nosnost, &znak) != 2 || nosnost < 1 || ( znak != ',' && znak != ']') )
			return 1;

		/*vlozeni hodnoty do pole*/
		insertArray(roadMap, roadMap->used, nosnost);

		if(znak == ']')
			return 0;
	}

return 0;
}

int limits(TPOLE2 *roadMap){
	char znak;
	int nosnost, pocPoz;

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
		
		insertArray(roadMap, pocPoz, nosnost);
		pocPoz++;

		if(znak == ']'){
			return 0;
		}
	}

return 0;
}

int load(TPOLE2 *roadMap){
	int from, to;

	if ( scanf("%d%d", &from, &to) != 2 || from<0 || to<from || to>=roadMap->used) {
		return 1;
	}

	else{
	printf("Maximalni naklad: %d\n", findMin( roadMap ,from, to));
	}

return 0;
}

void uvolnit(TPOLE2 * roadMap);
void initArr( TPOLE2 *roadMap, int initSize );
void err(TPOLE2 *roadMap);

int main(void){
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
				printf("%2d ", roadMap.pArray[i][j]);
			}
			printf("\n");
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
	free( (void*)roadMap->pArray);
return;
}

void initArr( TPOLE2 *roadMap, int initSize ){
	roadMap->size=initSize;
	roadMap->used=0;	
	roadMap->pArray = (int *) malloc(roadMap->size * sizeof(int)) ;

return;
}

void err(TPOLE2 *roadMap){
	uvolnit(roadMap);
	printf("Nespravny vstup.\n");

return;
}
