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
	}

	return obsah;
		
	}

double vzdalBodu(double x1, double x2, double y1, double y2){
		double a=x2-x1;
		double b=y2-y1;
		double vzdalenost = sqrt( (a*a + b*b) );
		return vzdalenost; 
	}


int main(){
	double xZac, yZac, xMinuly, yMinuly, xTento, yTento, sPrvni, oPrvni, sDruhy, oDruhy;

	/*PRVNI POZEMEK*/
	printf("Pozemek #1:\n");

	/*nacti prvni tri a zkontroluj*/
	if( scanf("%lf%lf%lf%lf%lf%lf",&xZac, &yZac, &xMinuly, &yMinuly, &xTento, &yTento) != 6 || (xZac==xMinuly && 			yZac==yMinuly) || (xZac==xTento && yZac==yTento) ){
		printf("Nespravny vstup.\n");
		return 0;
	}
	
	/*spocitej obvod a obsah prvnich dvou*/
	sPrvni=sTrojuhelnika(xZac, xMinuly, xTento, yZac, yMinuly, yTento);
	oPrvni=vzdalBodu(xZac, xMinuly, yZac, yMinuly) + vzdalBodu(xMinuly, xTento, yMinuly, yTento);

	while(1==1){

		/*nacti souradnice bodu */
			/*kdy ze to nepovede nahlas chybu ?? bude to ok pri EOF ??*/	
		xMinuly=xTento;
		yMinuly=yTento;

		if(scanf("%lf%lf", &xTento, &yTento) != 2){
			
			printf("Nespravny vstup.\n");
			return 0;
						
		}	


	/*kdy je shodny s prvnim bodem je pozemek nacten */
			/*dopocitej vzdalenost posledni bod prvni bod - posledni cast obvodu*/
			/*vyskoc z cyklu a pokracuj na dalsi pozemek*/
		
		if(xZac == xTento && yZac == yTento){
			oPrvni += vzdalBodu(xZac, xMinuly, yZac, yMinuly);
			break; /*NUTNO POKRACOVAT NA DALSI POZEMEK !!!!!!!!!!!!!!!   */
		}



	/*kdyz je jiny --   spocitej vzdalenost od predchoziho bodu

				-- spocitej obsah trojuh. (tento bod, predchozi bod, pocatecni bod)*/	

		else{
			oPrvni += vzdalBodu(xMinuly, xTento, yMinuly, yTento);
			sPrvni += sTrojuhelnika(xZac, xMinuly, xTento, yZac, yMinuly, yTento);
			continue; /*to je tu asi zbytecne no.... */
			
		}

	}
		









		

	printf("O pozemku: %g\nS pozemku: %g\n", oPrvni, sPrvni);
	return 0;


}
