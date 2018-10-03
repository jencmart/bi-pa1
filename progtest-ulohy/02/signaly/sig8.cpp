#include <stdio.h>
#include <math.h>


int zpracujSignal(long long int * a1, long long int * a2){
	char znak;
	int prvni=0, druhy=0, lomitko=0, ctiDoA1=1;
	*a1 = 0;
	*a2 = 0;
	while(1 == 1){
		/*prevence prazdneho vstupu*/
		if(scanf("%c", &znak) !=1){	
			return 2;
		}

		/*konec radky*/
		if(znak == '\n'){
			/*kdyz jse zprava nulova nebo kdyz nema lomitko*/
			if( (prvni+druhy) == 0 || lomitko==0){
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
				continue;}
		} 

		/*Kdyz je to lomitko a jeste ho nemame, poznac ze ho mame a nastav pricitani do a2*/
		else if(int(znak)==124 && lomitko==0){
			lomitko=1;
			ctiDoA1=0;
			continue;
		} 

		/*ve vsech ostatnich pripadech vrat chybu tj. mimo rozsah nebo vice lomitek*/
		else{ 
			return 1; 
		}
	}
}

long long int gcd(long long int a, long long int b){
	long long int tmp;
	while(b != 0){
		tmp = a;
		a=b;
		b=tmp%b; 
        } return a;
}


// C function for extended Euclidean Algorithm
void spocitejEuklida(long long int a,long long int b,long long int *x,long long int *y){
	long long int x1, y1; // To store results of recursive call
	

	// Base Case
	if (a == 0){
		*x = 0;
		*y = 1;
	        return;
	}
 
    
	spocitejEuklida(b%a, a, &x1, &y1);
	// Update x and y using results of recursive
	// call
	*x = y1 - (b/a) * x1;
	*y = x1;	
}


long long int spocitejNerovnici(long long int a, long long int b){
	long long int t;

	if(a==0){
		if(b<0)
			return -1;
		else
			return 1; }
	if(b<0){
		if(-a/b == 0){
			if(b/-a < 0 )
				return -1;
			else 
				return 0; }

		if(-a/b < 0){
			t = -a/b - 1;	
			return t;	
		}else{
			t = -a/b;
			return t; }
	}else{  if(-a/b == 0){
			if(b/-a < 0)
				return 0;	
			else 
				return 1 ; }		
		if(-a/b < 0){
			t = -a/b;
			return t;
		}else{
			t = -a/b + 1;
			return t;
		}
	}


}


int spocitejRovnice(long long int a1,long long int a,long long int b1,long long int b, long long int* zaklad, long long int* koeficient ){
	long long int c, g, x0, y0, x, y, konstX, konstY, tA;

	/*na tvar ax + by = b1-a1 */
	c=b1-a1;
	b = -1*b;

	/*ROVNICE PRED VYPOCTEM*/
	g= gcd(a,b);

	/* neexistuje reseni */
	if(c%g != 0){
		return 1;} 
	
	/* spcitej x0 a y0 */
	spocitejEuklida(a/g, b/g, &x0, &y0);

	x = x0 * c/g;
	y = y0 * c/g;

	/*parametry znormovane minusama*/
	konstX = b/g;
	if(  (y<0 && b > 0) || (y>0 && b < 0) ){ 
		konstX *= -1; }
	konstY = a/g;
	if(  ( x<0   && a > 0 ) || ( x>0 && a < 0  ) ){ konstY *= -1; }

	/* VYPOCET NEJLEPSIHO PARAMETRU T */
	tA = spocitejNerovnici(x, konstX);
	/*tB = spocitejNerovnici(y, konstY);*/
	
	
	/*rovnice v nejjedodusim tvaru */
	/* X = x + kosnstX * tA
	   Y = y + konstY * tB */
	*zaklad = x + konstX* tA;
	*koeficient = konstX; 
	return 0;
}


void porovnejSpecialniPripady(long long int a1,long long int a2,long long int b1, long long int b2, long long int * zaCas){
	/*zkratka*/	
	if (  (a1 == b1 && a1 == 0) || (a2==b2 && a2==0) ){
		*zaCas = 0;
		return;
	}

	/*zkratka*/
	if( (a1 == b2 && a2 == b1) && (a1 == 0 || b1 == 0) ){
		*zaCas = 0;
		return;
	 }


	/*zkratka*/
	if( a1 == b1 ){
		*zaCas = a1;
	}

	else{*zaCas = -1; return; }
	

}



int main(){
	
	long long int zaklad, koeficient,koeficientDruhy, zakladDruhy, normujiciParametr ,kDosaz, zDosaz, a1, a2, b1, b2, zRce0, kRce0, prepinacSyncZa, tmp;
	int nacteno;

	/*PROCESS 1. MESSAGE*/
	printf("Zpravy:\n");
	if( zpracujSignal(&a1, &a2) ){
		printf("Nespravny vstup.\n");
		return 1;}

	/*PROCESS 2. MESSAGE*/
	if( zpracujSignal(&b1, &b2) ){
		printf("Nespravny vstup.\n");
		return 1; }

	/*VYPOCTI RCI 1. A 2. ZPRAVY */
	if( spocitejRovnice(a1, a1+a2, b1, b1+b2, &zaklad, &koeficient) == 1 ){
		printf("Nelze dosahnout.\n");
		return 1;}
	zRce0 = a1;
	kRce0 = a2; /*ulozeni prvni puvodni rovnice*/	

	/*vnitrni prepinac sync */
	porovnejSpecialniPripady(a1, a2, b1, b2, &prepinacSyncZa);



	/*NACITEJ DALSI ZPRAVY*/
	while( 1 == 1){
	nacteno = zpracujSignal(&b1, &b2);
	if( nacteno == 2){
		break;}
	if(nacteno){
		printf("Nelze dosahnout.\n");
		return 1;}

	/*VYPOCTI RCI 1. A DALSI ZPRAVY */
	if( spocitejRovnice(a1, a1+a2, b1, b1+b2,  &zakladDruhy, &koeficientDruhy) == 1 ){
		printf("Nelze dosahnout.\n");
		return 1;}

	/*VYPOCTI RCI ZE SUB ROVNIC*/
	if( spocitejRovnice(zaklad, koeficient, zakladDruhy, koeficientDruhy, &zDosaz, &kDosaz) ==1 ){
		printf("Nelze dosahnout.\n");
		return 1;}

	/*DOSAZENI VYPOCTU SUB RCI DO 1. RCE A TIM VYTVORENI NOVE 1. ROVNICE*/
	zaklad = zaklad + koeficient*zDosaz; /*jde  vpodstate o roznasobeni zavorky*/
	koeficient = koeficient* kDosaz;
	/*znormovani zakladu*/
	normujiciParametr = spocitejNerovnici(zaklad, koeficient);
	zaklad = zaklad + koeficient* normujiciParametr;

	/*porovnani spec pripadu vuci dalsim rovnicim*/
	tmp = prepinacSyncZa;
	porovnejSpecialniPripady(a1, a2, b1, b2, &prepinacSyncZa);
	
	
	if(prepinacSyncZa != -1 && tmp == prepinacSyncZa){		
		} else{prepinacSyncZa = -1 ; }

	}

	
	if(prepinacSyncZa != -1){
		printf("Synchronizace za: %lld\n", prepinacSyncZa);
		return 0; }


	printf("Synchronizace za: %lld\n", zRce0 + (kRce0+zRce0)*zaklad);
	return 0;
}
