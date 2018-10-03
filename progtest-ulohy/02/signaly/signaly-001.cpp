#include <stdio.h>
#include <math.h>


int zpracujSignal(long int * a1, long int * a2){
	char znak;
	int prvni=0, druhy=0, lomitko=0, ctiDoA1=1;
	
	while(1 == 1){



		/*prevence prazdneho vstupu*/
		if(scanf("%c", &znak) !=1){	
			printf("nemam co cist");
			return 1;
		}



		/*konec radky*/
		if(znak == '\n'){
			if( (prvni+druhy) == 0){
				return 1;			
			} 
		
			return 0; 
		}





		/*ZKONTROLUJ ZNAK*/

		/*Kdyz je ve spravnem rozsahu - pricti ho*/
		if( (int)znak>= 97 && (int)znak <=122 ){


			if(ctiDoA1){ 
				prvni=1;
				*a1+= pow(2, (int)znak - 97); 
				continue;
			}
			else { 
				druhy=1;
				*a2 += pow(2, (int)znak - 97);
				continue;
			}
			
		} 

		/*Kdyz je to lomitko a jeste ho nemame, poznac ze ho mame a nastav pricitani do a2*/
		else if(int(znak)==124 && lomitko==0){
			lomitko=1;
			ctiDoA1=0;
			continue;
		
		} 


		/*ve vsech ostatnich pripadech vrat chybu*/
		else{ 
			return 1; 
		}
		
	}

}





int main(){
	long int a1=0, a2=0, b1=0, b2=0 ;
	int neuspech;
	
	neuspech = zpracujSignal(&a1, &a2);
	
	if(neuspech){
		printf("Nespravny vstup.\n");
		return 1;	
	}
	
	

	printf("%ld | %ld", a1, a2);
	/*
	neuspech = zpracujSignal(&b1, &b2);

	if(neuspech){
		printf("Nespravny vstup.\n");
		return 1;	
	}
	spocitejSynchronizaci(a1, a2, b1, b2);

*/

	return 0;
}
