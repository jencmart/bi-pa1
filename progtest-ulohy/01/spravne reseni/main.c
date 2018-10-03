#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double pocLatekNaStranuPlachty(double strPlachta, double strLatka, double prekryv ) {
        double pocetLatek;
        double tmp = (strPlachta - strLatka)/(strLatka-prekryv);
	/*printf("po vydeleni: %.20f\n", tmp);*/
        pocetLatek = ceil(tmp);
	
        if(pocetLatek-tmp>0.9999999999){
            pocetLatek = floor(tmp);
            }
        pocetLatek += 1;
        return pocetLatek;
    }

int main(int arcg, char** argv) {

	double kLatka, dLatka, kPlachta, dPlachta, prekryv = 0, varAStrA=1, varAStrB=1, varBStrA=1, varBStrB=1, vyslA, vyslB;


	/* ZADANI A OSETRENI VSTUPU */
	printf("Velikost latky:\n");
	if ( scanf("%lf %lf", &kLatka, &dLatka) != 2 || kLatka <= 0 || dLatka <= 0){
        	printf("Nespravny vstup.\n");
        	return 1;
	}

	printf("Velikost plachty:\n");
        if ( (scanf("%lf %lf", &kPlachta, &dPlachta) != 2) || (kPlachta <= 0) || (dPlachta <= 0) ){
        	printf("Nespravny vstup.\n");
        	return 1;
	}

	if(dLatka < kLatka){
		double tmp=kLatka;
		kLatka=dLatka;
		dLatka=tmp;
	}


	if(dPlachta<kPlachta) {
        	double tmp=kPlachta;
        	kPlachta=dPlachta;
        	dPlachta=tmp;
	}


	/* kdyz jsou rozmery stejne  nebo latka vetsi */
	if((kLatka >= kPlachta && dLatka >= dPlachta) || (kLatka >= dPlachta)){
        	printf("Pocet kusu latky: 1\n");
        	return 0;
	}


	 /*NACTI PREKRYV 
	if(kLatka<=dPlachta)*/
       	printf("Prekryv:\n");
        if( scanf ("%lf", &prekryv) != 1 || prekryv<0){
                printf("Nespravny vstup.\n");
                return 1;
	}

    	/* NEJDE VYROBIT*/
	if( (prekryv >= kLatka) && ((kLatka < kPlachta) || (prekryv >= dLatka)) ){
	        printf("Nelze vyrobit.\n");
	        return 1;
	}

    	/* SPECIALNI PRIPAD - pak to jde */
	if(prekryv >= kLatka && prekryv < dLatka && kLatka >= kPlachta){
	        double specialni = pocLatekNaStranuPlachty(dPlachta, dLatka, prekryv);
	        printf("Pocet kusu latky: %.0f\n", specialni);
	        return 0;
        }




	/*var A - plachta na vysku a latka na sirku*/
	/*latek nad sebou*/
	if(dPlachta>kLatka){
        	varAStrA = pocLatekNaStranuPlachty(dPlachta, kLatka, prekryv);
		/*printf("A: na vysku %.0f\n", varAStrA);*/
	}
	/*latek vedle sebe*/
	if(kPlachta>dLatka){
        	varAStrB = pocLatekNaStranuPlachty(kPlachta, dLatka, prekryv);
		/*printf("A: na sirky %.0f\n", varAStrB);*/
	}
	vyslA = varAStrA*varAStrB;



	/*var B - plachta na vysku a latka na vysku*/
	/*latek nad sebou*/
	if(dPlachta-dLatka>0){
        	varBStrA = pocLatekNaStranuPlachty(dPlachta, dLatka, prekryv);
		/*printf("B: na vysku %.0f\n", varBStrA);*/
	}
	/*latek vedle sebe*/
	if(kPlachta-kLatka>0){
        	varBStrB = pocLatekNaStranuPlachty(kPlachta, kLatka, prekryv);
		/*printf("B: na vysku %.0f\n", varBStrB);*/
	}

	vyslB = varBStrA*varBStrB;



	/*porovnani variant*/
	if(vyslA<vyslB)
        printf("Pocet kusu latky: %.0f\n",vyslA);
	
	else
        printf("Pocet kusu latky: %.0f\n", vyslB);
	

return 0;
}



