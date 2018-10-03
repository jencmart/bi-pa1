#include <stdio.h>
#include <math.h>


void findIntersection(const double lineA[],const double lineB[], double prusecik[] ){

	double delenec =  (lineA[0] * lineA[1] ) - (lineB[0]*lineA[1]*lineA[2]);
	double delitel = lineB[0]*lineA[1]*lineA[0] + lineB[1] ;

	if (delenec == 0 || delitel == 0){
		prusecik[1] = 0;
	} else{prusecik[1] = delenec / delitel; }

	delenec =  -1*( prusecik[1] * lineA[1] + lineA[2] );
	delitel = lineA[0];

	if (delenec == 0 || delitel == 0){
		prusecik[0] = 0;
	} else{prusecik[0] = delenec / delitel; }
return;
}


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


int main(){
	double bodA[2];
	double bodB[2];
	double bodC[2];
	double bodX[2];

	double primkaAB[3];
	double primkaBC[3];
	double primkaAC[3];

	double primkaTX[3];
	double prusecik[2];

	printf("Zadej body trojuhelnika (oddeleno whitespace):\n");
	if ( (scanf("%lf %lf", &bodA[0], &bodA[1])!=2) || (scanf("%lf %lf", &bodB[0], &bodB[1])!=2) ||
		(scanf("%lf %lf", &bodC[0], &bodC[1])!=2)){
			printf("Spatny vstup!\n");
			return 1;
	} 

	countLineEQ( bodA, bodB, primkaAB);

	if( pointOnLine(primkaAB, bodC) ){
		printf("Body netvori trojuhelnik!\n");
		return 1;
	}

	printf("Zadej bod X:\n");
	if( scanf("%lf %lf", &bodX[0], &bodX[1]) != 2){
		printf("Spatny vstup!\n");
	}

	countLineEQ( bodB, bodC, primkaBC);
	countLineEQ( bodA, bodC, primkaAC);

	/*POKUD JE BOD UVNIT TROJUHENIKA, POTOM PRIMKA KTERA VEDE Z JEDNOHO BODU TROJ PRES TENHLE
	BOD, PROTINA PROTEJSI PRIMKU . TZN... */


	/*BOD LEZI NA HRANE TROJUHELNIKA*/
	if(pointOnLine(primkaAB,bodX) || pointOnLine(primkaBC,bodX) || pointOnLine(primkaAC,bodX)){
		printf("Bod lezi na hrane trojuhelnika\n");
		return 0;
	}

	/*bod A ; lineBC*/
	countLineEQ(bodA, bodX, primkaTX);
	findIntersection(primkaTX, primkaBC, prusecik);

	printf("prusecik BC: %f %f\n", prusecik[0], prusecik[1]);

	if(pointOnLine(primkaBC, prusecik) != 1 ){
		printf("Bod nelezi v trojuhelniku\n");
		return 0;
	}

	/*bod B ; lineAC*/
	countLineEQ(bodB, bodX, primkaTX);
	findIntersection(primkaTX, primkaAC, prusecik);
	if( ! pointOnLine(primkaAC, prusecik)){
		printf("Bod nelezi v trojuhelniku\n");
		return 0;
	}

	/*bod C ; lineAB*/
	countLineEQ(bodC, bodX, primkaTX);
	findIntersection(primkaTX, primkaAB, prusecik);
	if( ! pointOnLine(primkaAB, prusecik)){
		printf("Bod nelezi v trojuhelniku\n");
		return 0;
	}

	printf("BOD LEZI UVNITR TROJUHELNIKU ! \n");

return 0;
}