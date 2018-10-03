#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sTrojuhelnika(double x1, double x2, double x3, double y1, double y2, double y3){
	double u1 = x2-x1;
	double u2 = y2-y1;

	double v1 = x3-x1;
	double v2 = y3-y1;

	double obsah = (u1/2 * v2) - (u2/2 * v1) ;

	if(obsah < 0) {
		obsah*=-1;
	} return obsah;	
}

double vzdalBodu(double x1, double x2, double y1, double y2){
		double a=x2-x1;
		double b=y2-y1;
		double vzdalenost = sqrt( (a*a + b*b) );
		return vzdalenost; 
	}



int zpracujPozemek(double * obvod, double * sobsah ){
	double xZac, yZac, xMinuly, yMinuly, xTento, yTento;

	/*Nacti prvni tri a zkontroluj*/
	if( scanf("%lf%lf%lf%lf%lf%lf",&xZac, &yZac, &xMinuly, &yMinuly, &xTento, &yTento) != 6 || (xZac==xMinuly && 			yZac==yMinuly) || (xZac==xTento && yZac==yTento) ){
		return 0;
	}
	
	/*udelej jejich obvod a obsah*/
	*sobsah=sTrojuhelnika(xZac, xMinuly, xTento, yZac, yMinuly, yTento);
	*obvod=vzdalBodu(xZac, xMinuly, yZac, yMinuly) + vzdalBodu(xMinuly, xTento, yMinuly, yTento);


	while(1==1){

		/*nacti bod -- ukonci se pri EOF ?? ! ! ! ! !*/	
		xMinuly=xTento;
		yMinuly=yTento;

		if(scanf("%lf%lf", &xTento, &yTento) != 2){
			return 0;
						
		}	

		/*kdy je shodny s prvnim bodem je pozemek nacten */
			/*dopocitej vzdalenost posledni bod prvni bod - posledni cast obvodu*/		
		if(xZac == xTento && yZac == yTento){
			*obvod += vzdalBodu(xZac, xMinuly, yZac, yMinuly);
			return 1;
		}

		/*kdyz je jiny --   spocitej vzdalenost od predchoziho bodu
				-- spocitej obsah trojuh. (tento bod, predchozi bod, pocatecni bod)*/	

		else{
			*obvod += vzdalBodu(xMinuly, xTento, yMinuly, yTento);
			*sobsah += sTrojuhelnika(xZac, xMinuly, xTento, yZac, yMinuly, yTento);
			continue; /*to je tu asi zbytecne no.... */
		}
	}
		
}



int porovnejObsah(double prvni, double druhy){

	if(prvni == druhy){
		printf("Pozemky maji stejnou vymeru: %g\n", prvni);
		return 0;
	} else if ( fabs((prvni-druhy)/druhy) < 0.00001){
		printf("Pozemky maji stejnou vymeru: %g\n", prvni);
		return 0;
	} else if( prvni > druhy ){
		printf("Rozloha pozemku #1 (= %g) je vetsi nez rozloha pozemku #2 (= %g).\n", prvni, druhy);
		return 0;

	} else{ 
		printf("Rozloha pozemku #2 (= %g) je vetsi nez rozloha pozemku #1 (= %g).\n", druhy, prvni);
		return 0;
	}
	
	
}

int porovnejObvod(double prvni, double druhy){

	if(prvni == druhy){
		printf("Hranice maji stejnou delku: %g\n", prvni);
		return 0;
	} else if ( fabs((prvni-druhy)/druhy) < 0.00001){
		printf("Hranice maji stejnou delku: %g\n", prvni);
		return 0;
	} else if( prvni > druhy ){
		printf("Hranice #1 (= %g) je delsi nez hranice #2 (= %g).\n", prvni, druhy);
		return 0;

	} else{ 
		printf("Hranice #2 (= %g) je delsi nez hranice #1 (= %g).\n", druhy, prvni);
		return 0;
	}
}

int main(){
	double sPrvni, oPrvni, sDruhy, oDruhy;
	int zpracovano; 

	/*PRVNI POZEMEK*/
	printf("Pozemek #1:\n");

	zpracovano = zpracujPozemek( &oPrvni, &sPrvni);

	if( zpracovano == 0 ){
		printf("Nespravny vstup.\n");
		return 0;
	}



	/*DRUHY POZEMEK*/
	printf("Pozemek #2:\n");
	
	zpracovano = zpracujPozemek( &oDruhy, &sDruhy);

	if( zpracovano == 0 ){
		printf("Nespravny vstup.\n");
		return 0;
	}
	
	/*printf("Rozloha pozemku #1 (= %g)\nRozloha pozemku #2 (= %g)\n", sPrvni, sDruhy);
	printf("Hranice pozemku #1 (= %g)\nHranice pozemku #2 (= %g)\n", oPrvni, oDruhy);*/

	porovnejObsah(sPrvni, sDruhy);
	porovnejObvod(oPrvni, oDruhy);
	return 0;
}
