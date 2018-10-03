#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE 2000



int binarySearch( int *array, int arraySize, int hledaneCislo){
	int from = 0;
	int to = arraySize-1;
	int pulka, pozice;
	
/*	printf("binSrch: from: %d to: %d hledame: %d\n", from, to, hledaneCislo);*/
	while(1){
		pulka = (to - from) / 2;
		pozice = from + pulka;
/*		printf("pulka je: %d\n", pulka);*/
		if(pulka == 0){
		/*	printf("pulka je 0, from = %d , array[from] = %d\n", from, array[from]);*/
			if (array[from] == hledaneCislo)
				return hledaneCislo;
			if(from+1 <= arraySize-1){
				if (array[from+1] == hledaneCislo)
					return hledaneCislo;
			}

			return 0;
		}

		if(array[pozice] < hledaneCislo){
			to =pozice-1;
	/*		printf("to : %d\n", to);
			getchar();*/
			continue;
		}
		
		else if(array[pozice] > hledaneCislo){
			from += pulka+1;
/*			printf("from: %d\n", from);
			getchar();*/
			continue;
		}

		else if(array[from+pulka] == hledaneCislo)
			return hledaneCislo;


	}	
	
return 0;
}

void vytvorPotrubi(int *array, int arraySize, int potrub){
	int counter = 0;
	int hodnota, i,j, od;
	
	
	/*delka 1*/
	hodnota = binarySearch(array, arraySize, potrub );
/*	printf("Hodnota = %d\n", hodnota);*/
	if (hodnota){
		counter += 1;
		printf("%d = %d\n", potrub, hodnota);
	}

	
	/*delka 2*/
	for(i=arraySize-1 ; i>= 0 ; i--){	
			if(potrub - array[i] < 1 )
				break;
			hodnota = binarySearch(array, i+1 , potrub - array[i]);
			if(hodnota) {
				counter += 1;
				printf("%d = %d + %d\n", potrub, array[i], hodnota);
			}
		
	}


	/*delka 3*/
/*	printf("jde na delku 3\n\n");*/
	for(i=arraySize-1 ; i>=0 ; i--){
			if(potrub-array[i] < 1)
				break;
			for(j=i ; j>= 0 ; j--){
					if(potrub-array[i]-array[j] < 1)
						break;
					if(j+1 <= i+1)
						od = j+1;
					else
						od = i+1;

					hodnota = binarySearch(array, od, potrub-array[i]-array[j]);
					if(hodnota){
						counter += 1;
						printf("%d = %d + %d + %d\n", potrub, array[i], array[j], hodnota);
					}
				}
	}
printf("Celkem: %d\n", counter);
return;

}


int sortArray(int *array, int arraySize){
	int naZaraz, serazeno, posunovac, i ,tmp;
	serazeno = 0;	

	for(naZaraz=1; naZaraz < arraySize; naZaraz++){
		for(i = serazeno; i >=0 ; i--){
			if(array[i] > array[naZaraz] ){
				
				tmp = array[naZaraz];
				for(posunovac = naZaraz - 1 ; posunovac > i ; posunovac--)
					array[posunovac+1] = array[posunovac];

				array[i+1] = tmp;
				serazeno = naZaraz;
				break;
			}

			if(array[i] == array[naZaraz])
				return 0;

			else if( i == 0){
				tmp = array[naZaraz];
				for(posunovac = naZaraz - 1 ; posunovac >=0 ; posunovac--)
					array[posunovac+1] = array[posunovac];	
				
				array[0] = tmp;
				serazeno = naZaraz;
			}
		}
	}
return 1;
}


int main(void){
	int array[MAX_SIZE];
	int rv, num, numDel, i, nulaZazn = 0, potrubiZazn = 0;

	printf("Delky trubek:\n");	

	/*NACITANI DELEK PREFABRIKATU */
	for(i= 0 ; i<=MAX_SIZE ; i++){
		if ( scanf("%d", &num) != 1)
			break;
		if (num <=0){
			if(num < 0){
				printf("Nespravny vstup.\n");
				return 1;
			}
			if (num == 0 && i == 0){
				printf("Nespravny vstup.\n");
				return 1;
			}
			nulaZazn = 1;
			break;
		}

		if(i==MAX_SIZE){
			printf("Nespravny vstup.\n");
			return 1;
		}	
		array[i] = num ;
	}
	if(! nulaZazn ){
		printf("Nespravny vstup.\n");
		return 1;
	}

	if (i>2){
		if( sortArray(array, i) == 0 ) {
			printf("Nespravny vstup.\n");
			return 1;
		}
	}

	/* NACITANI DELEK POTRUBI */
	printf("Potrubi:\n");
	while(1){
		rv = scanf("%d", &numDel);
		if(rv == EOF)
			break;

		if(rv != 1){
			printf("Nespravny vstup.\n");
			return 1;
		}
		
		if( numDel <=0){
			printf("Nespravny vstup.\n");
			return 1; 
		}
		
		potrubiZazn = 1;	
		vytvorPotrubi(array, i, numDel);
	}	
		if( ! potrubiZazn ){
			printf("Nespravny vstup.\n");
			return 1;
}
return 0;
}


