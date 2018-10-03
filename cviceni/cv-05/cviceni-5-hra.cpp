#include <stdio.h>
#include <stdlib.h>



void splachniVstup(){
	char zahod;	
	while ( scanf("%c", &zahod) != 2 && zahod != '\n' ){ 
		continue;
	}

}


int main(){
	int pokus=1, hrac=-1, number = rand() % 100;
	printf("Myslim si cislo od 0 do 100 vcetne. Uhodni ho:\n");

	
	while(1==1){
	
	if (pokus != -1){
		printf("Zadej cislo:\n");
	}

	if ( scanf("%d", &hrac) != 1 ) {
		printf("Nespravy vstup debilku! Zkus to znovu....\n");
		splachniVstup();
		continue;
	}
	
	if(hrac != number){
		pokus+=1;
	
		if(hrac>number){		

			printf("Ne.Myslim si mensi cislo. Zkus to znovu.\n");	
			
			
		}
		
		else {		
			printf("Ne.Myslim si vetsi cislo. Zkus to znovu.\n");
			
		}
	}
	


	else{
		printf("Je to tak ! Myslel jsem si opravdu cislo: %d\nUhodl si na: %d pokus\n", number, pokus);
		break;
	}
	}
	





	return 0;

}
