#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


	/* kdyz jsou rozmery stejne */
	if((kLatka == kPlachta && dLatka == dPlachta) || (kLatka == dPlachta)){
        	printf("Pocet kusu latky: 1\n");
        	return 0;
	}


	/*printf("kLatka = %.20f\ndPlachta = %.20f\n", kLatka, dPlachta);*/

	if(kLatka<=dPlachta){ /*NACTI PREKRYV */
       		printf("Prekryv:\n");
        if( scanf ("%lf", &prekryv) != 1 || prekryv<0){
                printf("Nespravny vstup.\n");
                return 1;
        }
	}

    /* NEJDE VYROBIT*/
    if( (prekryv >= kLatka) && ( (kLatka <= kPlachta) || (prekryv >= dLatka)) ){
        printf("Nelze vyrobit.\n");
        return 1;
    }

    /* Specialni pripad - pak to jde*/
    if(prekryv >= kLatka && prekryv < dLatka && kLatka >= kPlachta){
        double tmp = (dPlachta-dLatka)/(dLatka-prekryv);
        double specialni = ceil(tmp);
        if(specialni-tmp>0.99999999999999){ /*kdyz rozdil cisel je vetsi nez max presnost double zaokrouhli dolu*/
                specialni = floor(tmp);
            }
        specialni += 1;
        printf("Pocet kusu latky: %.0f\n", specialni);
        return 0;
        }

	/*else{



double pocLatekNaStranuPlachty(double strPlachta, double strLatka, double prekryv ) {
        double pocetLatek;
        double tmp = (strPlachta - strLatka)/(strLatka-prekryv);
        pocetLatek = ceil(tmp);
        if(pocetLatek-tmp>0.99999999999999){
            pocetLatek = floor(tmp);
            }
        pocetLatek += 1;
        return pocetLatek;
    }

	/*varianta A - plachta na vysku a latka na sirku*/



	if(dPlachta>kLatka){
        varAStrA = pocLatekNaStranuPlachty(dPlachta, kLatka, prekryv);
	}

    /*pocet potrebny na sirku*/
	if(kPlachta>dLatka){
        varAStrB = pocLatekNaStranuPlachty(kPlachta, dLatka, prekryv);
	}

    vyslA = varAStrA*varAStrB;



	/*varianta B - plachta na vysku a latka na vysku*/

	if(dPlachta-dLatka>0){
        varBStrA = pocLatekNaStranuPlachty(dPlachta, dLatka, prekryv);
	}

	if(kPlachta-kLatka>0){
        varBStrB = pocLatekNaStranuPlachty(kPlachta, kLatka, prekryv);
	}



   /* printf("--- varianta B pred snasobenim je %.20f\n %.20f\n",varBStrA, varBStrB);*/
	vyslB = varBStrA*varBStrB;
	/*printf("vysledek b je: %.20f\n",vyslB);*/



	/*porovnani variant*/

	if(vyslA<vyslB){
        printf("Pocet kusu latky: %.0f\n",vyslA);
	}
	else{
        printf("Pocet kusu latky: %.0f\n", vyslB);
	}

return 0;
}


