#include <stdio.h>


void tiskni(int azdo, char znak){
	int i;
	for(i=1; i<azdo; i++){
		printf("%c", znak);		
	}
}

int main(){
	int i, sirka, pMezer, pozMasle=0, pocMeziMasli;
	printf("Zadej sirku balika:\n");
	scanf("%d",&sirka);

	if(sirka%2==1){sirka-=1;}
	
	if(sirka%3==0){
	pozMasle=sirka/3;
	}

	if(sirka%3==1){
	pozMasle=sirka/3+1;
	}
	

	if(sirka%3==2){
	pozMasle=sirka/3+1;
	}
	
	pocMeziMasli=sirka-2*pozMasle;

	pMezer=sirka/2 - 1;

	/*tisk prvni radek*/
	tiskni(pozMasle, ' ');
	printf("0");
	tiskni(pocMeziMasli, ' ');
	printf("0");
	printf("\n");	


        /*tisk druhy radek*/
	tiskni(pozMasle, '*');
	printf("/");
	tiskni(pocMeziMasli, '*');
	printf("\\");
	tiskni(pozMasle, '*');
	printf("\n");
	
	
	/*tiskni zbyle radky krom posledni*/
	for(i=1; i<=sirka-2; i++){
		
		if(i==pMezer){
			tiskni(sirka,'*');
			printf("\n");
			continue;			
		}
		
		printf("*");
		tiskni(pMezer,' ');
		printf("*");
		tiskni(pMezer,' ');
		printf("*\n");
		

	}
	
	tiskni(sirka,'*');
	printf("\n");

	
	
	


return 0;
}
