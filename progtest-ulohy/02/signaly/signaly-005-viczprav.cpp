#include <stdio.h>
#include <math.h>


int zpracujSignal(long long int * a1, long long int * a2){
	char znak;
	int prvni=0, druhy=0, lomitko=0, ctiDoA1=1;
	
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

long long int spocitejGCD(long long int a, long long int b){
	long int tmp;
	while(b != 0){
		tmp = a;
		a=b;
		b=tmp%b;
	} 
	return a;
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

int spocitejSynchron(long long int a1,long long int a2,long long int b1,long long int b2, long long * syncCas){
	long long int a = a1 + a2;
	long long int b = b1 + b2;
	long long int c, g, x0, y0, x, y, konstX, konstY, t1;


	/*zkratka*/	
	if (  (a1 == b1 && a1 == 0) || (a2==b2 && a2==0) ){
		/*printf("Synchronizace za: 0\n");*/
		return 2;}

	/*zkratka*/
	if( (a1 == b2 && a2 == b1) && (a1 == 0 || b1 == 0) ){
		/*printf("Synchronizace za: 0\n");*/
		return 2; }

	/*zkratka*/
	if( a1 == b1 ){
		/*printf("Synchronizace za: %lld\n", a1);*/
		return 3;
	}
	





	 /* -----------ASI ODTUD TO BUDU MUSET CYKLIT --------------------
		TZN ZNOVU ODECTU OD C ZNOVU ODECTU B A ZNOVU UDELAM GCD ATD ATD.... */
	/*na tvar ax + by = b1-a1 */
	c=b1-a1;
	b = -1*b;


	/*ROVNICE PRED VYPOCTEM*/
	/*printf("\n%ldx + %ldy = %ld\n", a, b, c);*/
	



	

	g= spocitejGCD(a,b);
	
	/* neexistuje reseni */
	if(c%g != 0){
		return 1;	
	} 

	
	/* spcitej x0 a y0 */
	spocitejEuklida(a/g, b/g, &x0, &y0);

	x = x0 * c/g;
	y = y0 * c/g;


	/* FINALNI ROVNICE */
	/*printf("\n\n%ld*%ld + %ld *%ld = %ld\n", a, x, b, y, c);*/
	
	
		
	/*parametry znormovane minusama*/
	konstX = b/g;
	if(  (y<0 && b > 0) || (y>0 && b < 0) ){ 
		konstX *= -1; }
	konstY = a/g;
	if(  ( x<0   && a > 0 ) || ( x>0 && a < 0  ) ){ konstY *= -1; }
	


	/* PARAMETRICKY TVAR X A Y*/
	/*printf("\nX: %ld + %ld*t\nY: %ld + %ld*t\n", x, konstX, y, konstY);*/
	

	/* BUDE NASLEDOVAT KOD PRO VYPOCET NEJLEPSIHO PARAMETRU T*/

	t1 = spocitejNerovnici(x, konstX);
	/*t2 = spocitejNerovnici(y, konstY);*/
	/*printf("t1: %ld\n", t1);*/
	
	
	/*printf("X: %ld Y: %ld\n", x + konstX*t1, y + konstY*t1);*/

	*syncCas = a1 + a * (x +  konstX*t1);

	
	return 0;
}


int main(){
	
	long long int syncCas, syncCasOld, a1=0, a2=0, b1=0, b2=0 ;
	int neuspech;


	/*ZPRACUJ SIGNAL PRVNI ZPRAVY*/
	printf("Zpravy:\n");
	neuspech = zpracujSignal(&a1, &a2);

	if(neuspech){
		printf("Nespravny vstup.\n");
		return 1;}

	/*ZPRACUJ SIGNAL DRUHE ZPRAVY*/
	neuspech = zpracujSignal(&b1, &b2);

	if(neuspech){
		printf("Nespravny vstup.\n");
	return 1; }


	/*ZPRACUJ SYNC PRVNICH DVOU*/

	neuspech = spocitejSynchron(a1, a2, b1, b2, &syncCas);

	if(neuspech){
		printf("Nelze dosahnout.\n");
		return 1;	
	}

	
	while( 1 == 1){
	
	/*zkousej nacitat dalsi zpravy*/

	neuspech = zpracujSignal(&b1, &b2);

	/*jsme na konci souboru*/
	if(neuspech==2){
		break;	
	}

	/*ve zprave je chyba*/
	if(neuspech){
		printf("Nelze dosahnout.\n");
		return 1;	
	}


	/*tady vime ze se uspesne nacetl dalsi radek*/
	syncCasOld = syncCas;
		
	neuspech = spocitejSynchron(a1, a2, b1, b2, &syncCas);

	if(neuspech){
		printf("Nelze dosahnout.\n");
		return 1;	
	}
	
	printf("syncCas a,b: %lld\nsyncCas a,c: %lld\n", syncCasOld, syncCas);
	/*syncCas = spocitejNSD(syncCasOld, syncCas);*/

	
	

	}

	printf("Synchronizace za: %lld\n", syncCas);

	return 0;
}
