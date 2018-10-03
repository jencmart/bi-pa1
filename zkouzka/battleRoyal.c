#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct enemyJednotka
{
	int x;
	int y;
} TJEDNOTKA;


int nactiJednotky( TJEDNOTKA **poleJednotek, int *size, int *used);


double countLength(int x1, int y1, int x2, int y2)
{
	int v1 = ( x2 -x1 ) * ( x2 -x1 );
	int v2 = (y2 - y1) * (y2 - y1);
	int v3 = v1+v2;
	
return sqrt(v3);
}

int main()
{
	TJEDNOTKA *poleJednotek = NULL;
	int size = 0;
	int used = 0;
	int i;
	char z1, z2, z3;
	int nacX, nacY, rv;

	double maxVzdalenost, tmp;

   	if( ! nactiJednotky(&poleJednotek, &size, &used)){
		printf("Nespravny vstup.\n");
		return 0;
	}
	

	while(1)
	{
		if(( rv = scanf(" %c%d %c%d %c", &z1,&nacX,&z2,&nacY,&z3) ) != 5)
			break;

		maxVzdalenost = countLength( poleJednotek[0].x, poleJednotek[0].y , nacX , nacY);

		for(i=0; i< used; i++){
			tmp = countLength(poleJednotek[i].x, poleJednotek[i].y, nacX, nacY);
			maxVzdalenost=tmp>maxVzdalenost?tmp:maxVzdalenost;
		}

		printf("max vzdalenost: %lf\n", maxVzdalenost);
	}
	
	if(rv != EOF)
		printf("nespravny vstup.\n");

	free(poleJednotek);
return 1;
}


int nactiJednotky(TJEDNOTKA **poleJednotek, int *size, int *used)
{
	int nactX, nactY, rv;
	char z1,z2,z3,z4;
	
	if(scanf(" %c", &z1) != 1 || z1 != '{')
			return 0;
	
	*size = 1000;

	*poleJednotek = (TJEDNOTKA*) malloc(  (*size) * sizeof(TJEDNOTKA) );
	
	while(1)
	{

		if ( scanf(" %c%d %c%d %c %c",  &z1, &nactX, &z2, &nactY, &z3,  &z4) !=6 || z1!='[' || z2 != ',' || z3 != ']' ||   ( z4!=',' && z4!='}') )
		{
			free(*poleJednotek);
			*poleJednotek = NULL;
			return 0;
		}
	
		if(*size == *used) {
			*size *=2;
			*poleJednotek = (TJEDNOTKA*) realloc(*poleJednotek, *size*sizeof(TJEDNOTKA) );
		}
		
		 (*poleJednotek)[*used].x = nactX;
		 (*poleJednotek)[*used].y = nactY;
		*used += 1;
		
		if(z4 == '}')
				return 1;
	}
return 1;
}
