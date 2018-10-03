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
			/*printf("nemam co cist");*/
			return 2;
		}

		/*konec radky*/
		if(znak == '\n'){
			/*kdyz jse zprava nulova nebo kdyz nema lomitko*/
			if( (prvni+druhy) == 0 || lomitko==0){
				return 1;			
			} 
			/*printf("%ld | %ld\n", *a1, *a2);*/
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
	long int tmp;
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


int spocitejRovnice(long long int a1,long long int a,long long int b1,long long int b, long long * zaklad, long long * koeficient ){
	long long int c, g, x0, y0, x, y, konstX, konstY, tA, tB;

	printf("pocitam rovnici: %lld + %lld = %lld + %lld\n", a1, a, b1, b);
	/*na tvar ax + by = b1-a1 */
	c=b1-a1;
	b = -1*b;

	/*ROVNICE PRED VYPOCTEM*/
	/*printf("\n%ldx + %ldy = %ld\n", a, b, c);*/
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
	

	/* PARAMETRICKY TVAR X A Y*/
	/*printf("\nX: %ld + %ld*t\nY: %ld + %ld*t\n", x, konstX, y, konstY);*/
	

	/* VYPOCET NEJLEPSIHO PARAMETRU T */
	tA = spocitejNerovnici(x, konstX);
	tB = spocitejNerovnici(y, konstY);
	
	
	/*rovnice v nejjedodusim tvaru */
	/* X = x + kosnstX * tA
	   Y = y + konstY * tB */
	*zaklad = x + konstX* tA;
	*koeficient = konstX; 
	printf("----vysledek:x= %lld + %lld*t\n\n", *zaklad, *koeficient);	
	return 0;
}

int main(){
	
	long long int zaklad, koeficient,koeficientDruhy, zakladDruhy, normujiciParametr ,kDosaz, zDosaz, syncCas, a1, a2, b1, b2, zRce0, kRce0;
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
	if( spocitejRovnice(a1, a1+a2, b1, b1+b2, &zaklad, &koeficient) ){
		printf("Nelze dosahnout.\n");
		return 1;}
		
	zRce0 = a1;
	kRce0 = a2;	

	/*NACITEJ DALSI ZPRAVY*/
	while( 1 == 1){
	nacteno = zpracujSignal(&b1, &b2);
	if( nacteno == 2){
		break;}
	if(nacteno){
		printf("chyba nacteni. Nelze dosahnout.\n");
		return 1;}

	/*VYPOCTI RCI 1. A DALSI ZPRAVY */
	
	
	if( spocitejRovnice(a1, a1+a2, b1, b1+b2,  &zakladDruhy, &koeficientDruhy) ){
		printf("Nelze rce 1. a3. zprava Nelze dosahnout.\n");
		return 1;}

	

	/*VYPOCTI RCI ZE SUB ROVNIC*/
	
	if( spocitejRovnice(zaklad, koeficient, zakladDruhy, koeficientDruhy, &zDosaz, &kDosaz) ){
		printf("Nelze dosahnout.\n");
		return 1;}

	printf("vypoctena rovnice z rovnic: %lldx + %lld*t\n", zDosaz, kDosaz);

	/*DOSAZENI DO ROVNICE A TIM VYTVORENI NOVE ROVNICE*/
	zaklad = zaklad + koeficient*zDosaz; /*jde  vpodstate o roznasobeni zavorky*/
	koeficient = koeficient* kDosaz;

	/*teto rovnici se jeste musi znormovat zaklad*/

	normujiciParametr = spocitejNerovnici(zaklad, koeficient);
	zaklad = zaklad + koeficient* normujiciParametr;


	
	printf("nova rovnice: x= %lld + %lld*t\n", zaklad, koeficient);
	}



	syncCas = zRce0 + (kRce0+zRce0)*zaklad;

	printf("Synchronizace za: %lld\n", syncCas);

	return 0;
}
