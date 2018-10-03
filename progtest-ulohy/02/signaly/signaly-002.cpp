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

long int spocitejGCD(long int a, long int b){
	long int tmp;
	while(b != 0){
		tmp = a;
		a=b;
		b=tmp%b;
	} 
	return a;
}


long int spocitejLCM(long int a, long int b){
	long int gcd, lcm;
	gcd = spocitejGCD(a, b);
	lcm = (a/gcd) * (b/gcd) ;
	return lcm;
}





int spocitejSynchron(long int a1,long int a2,long int b1,long int b2){
	long int a = a1 + a2;
	long int b = b1 + b2;
	long int c, gcdAB;


	/*zkratka*/	
	if (  (a1 == b1 && a1 == 0) || (a2==b2 && a2==0) ){
		printf("Synchronizace za: 0\n");
		return 0;	
	}
	
	/*udelejme kladne c  nebo nulu  -- dodelat shortcut pro nula*/
	if(a1>b1){
		c=a1-b1;	
	}	
	else{
		c=b1-a1;
	}


	/*v A bude vetsi hodnota...*/
	if (b > a){
		tmp = b;
		b = a;
		a = tmp;
		
		tmp= b1;
		b1 = a1;
		a1 = tmp;
	
		tmp=b2;
		b2=a2;
		a2=tmp;
	}


	/*a*x + b*y = c   */
	gcdAB=spocitejGCD(a,b);
	

	/*nema reseni*/
	if(c%gcdAB != 0){
		return 1;	
	} 

	a=a/gcd;
	b=b/gcd;
	c=c/gcd;

	/*dodelat shortcut pro a=1 b=1*/
	
	/* a*x + b*y = 1  */

	/*euklid - multiplikativni inverze v Telese Za - GCD(a,b) = 1 */
	
	
	
	

	

	


}



int main(){
	long int a1=0, a2=0, b1=0, b2=0 ;
	int neuspech;

	printf("Zpravy:\n");
	
	/*SCAN PRVNI*/
	neuspech = zpracujSignal(&a1, &a2);
	
	if(neuspech){
		printf("Nespravny vstup.\n");
		return 1;	
	}
	

	/*SCAN DRUHOU*/
	neuspech = zpracujSignal(&b1, &b2);

	if(neuspech){
		printf("Nespravny vstup.\n");
		return 1;	
	}



	neuspech = spocitejSynchron(a1, a2, b1, b2);

	if(neuspech){
		printf("Nelze dosahnout.\n");
		return 1;	
	}


	return 0;
}
