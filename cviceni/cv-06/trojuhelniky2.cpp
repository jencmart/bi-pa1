#include <stdio.h>
#include <math.h>


void countLineEQ(const double bodA[], const double bodB[], double primka[] ){
	primka[0] = bodA[1] - bodB[1];
	primka[1] = bodB[0] - bodA[0];
	primka[2] = -1*( bodA[0]*primka[0] + bodA[1]*primka[1]);
}


double pointOnLine(const double primka[], const double bod[]){
	if( primka[0]* bod[0] + primka[1]*bod[1] + primka[2] == 0){
		return 1;
	}else{return 0;}
}


int loadPoint(double bod[]){
	if( scanf("%lf %lf", &bod[0], &bod[1]) != 2  ) {
		return 1; 
	} else 
		return 0;
}


int onSamePolorovina(const double primka[],const double bodX[],const double bodB[]){
	double meziX =  primka[0]*bodX[0] + primka[1]*bodX[1] + primka[2];
	double meziB = primka[0]*bodB[0] + primka[1]*bodB[1] + primka[2];

	/* VCETNE */
	if  ( fabs(meziX) <= 1e-10 && meziB ){
		return 1;
	}

	if ( meziX < 0  && meziB < 0 ){
		return 1;
	} 

	else if(meziX > 0 && meziB > 0){
		return 1; 
	} 

	else{
    	return 0; }
}


int main(){
	double bodA[2];
	double bodB[2];
	double bodC[2];
	double bodX[2];

	double primkaAB[3];
	double primkaBC[3];
	double primkaAC[3];

	printf("Zadej souradnice bodu trojuhelnika: (oddel whitespace)\n");
	if(loadPoint( bodA )   ||   loadPoint(bodB )   || loadPoint(bodC)  ){
		printf("Spatny vstup!\n");
		return 1;
	}


	countLineEQ(bodA, bodB, primkaAB);

	if ( pointOnLine(primkaAB, bodC) ){
		printf("Body netvori trojuhelnik!!!!!!!!!!!!!!\n");
		return 1; }


	printf("Zadej souradnice bodu X:(oddel whitespace)\n");
	if(loadPoint(bodX) ){
		printf("Spatny vstup!\n");
	}



	countLineEQ(bodB, bodC, primkaBC);
	countLineEQ(bodA, bodC, primkaAC);

	/*SPOCITEJ ZDA JSOU BODY BE STEJNE POLOROVINE*/

	if ( ! onSamePolorovina(primkaAB, bodX, bodC)  ){
		printf("Bod X[%g,%g] NELEZI v trojuhelniku. C X \n", bodX[0], bodX[1]);
		return 0;
	}

	else if ( ! onSamePolorovina(primkaBC, bodX, bodA)  ){
		printf("Bod X[%g,%g] NELEZI v trojuhelniku. A X\n", bodX[0], bodX[1]);
		return 0;
	}

	else if ( ! onSamePolorovina(primkaAC, bodX, bodB)  ){
		printf("Bod X[%g,%g] NELEZI v trojuhelniku. B X\n", bodX[0], bodX[1]);
		return 0;
	}


	else
		printf("Bod X[%g,%g] LEZI v trojuhelniku\n", bodX[0], bodX[1] );


	return 0;


}