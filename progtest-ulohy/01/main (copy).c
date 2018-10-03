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

	if(kLatka<=dPlachta){ /*KDZY JE LATKA MENSI NEZ PLACHTA nacti prekryv pro sesivani*/
        printf("Prekryv:\n");
        if( scanf ("%lf", &prekryv) != 1 || prekryv<0){
                printf("Nespravny vstup.\n");
                return 1;
        }

        if(prekryv >= kLatka && prekryv >= dLatka){ /* TAK TADYTO MUSIM OSETRIT LEPE - POMOCI EPSILON*/
            printf("Nelze vyrobit.\n");
            return 1;
        }
        if(prekryv >= kLatka && prekryv < dLatka && kLatka >= kPlachta){ /* Specialni pripad - pak to jde*/
            double tmp = (dPlachta-dLatka)/(dLatka-prekryv);
            double specialni = ceil(tmp);
            if(specialni-tmp>0.99999999999999){ /*kdyz rozdil cisel je vetsi nez max presnost double zaokrouhli dolu*/
                specialni = floor(tmp);
            }
            specialni += 1;
            printf("Pocet kusu latky: %.0f\n", specialni);
            return 0;
        }

        if(prekryv >= kLatka && prekryv < dLatka && kLatka <= kPlachta){
            printf("Nelze vyrobit.\n");
            return 1;
        }
	}

	else{
        printf("Pocet kusu latky: 1\n");
        return 0;
	}

	/*varianta A - plachta na vysku a latka na sirku*/

	if(dPlachta-kLatka>0){
        double tmp = (dPlachta-kLatka)/(kLatka-prekryv);
       /* printf("varianta A stra A tmp je %.20f\n",tmp);*/
        varAStrA = ceil(tmp);
        if(varAStrA-tmp>0.99999999999999){ /*kdyz rozdil cisel je vetsi nez max presnost double zaokrouhli dolu*/
            varAStrA = floor(tmp);
            }
        varAStrA += 1;
	}

	if(kPlachta-dLatka>0){
        double tmp = (kPlachta-dLatka)/(dLatka-prekryv);
        varAStrB = ceil(tmp);
        /*printf("varianta A stra B tmp je %.20f\n",tmp);*/
        if(varAStrB-tmp>0.999999999999999){ /*kdyz rozdil cisel je vetsi nez max presnost double zaokrouhli dolu*/
            varAStrB = floor(tmp);
            }
        varAStrB += 1;
	}

    vyslA = varAStrA*varAStrB;



	/*varianta B - plachta na vysku a latka na vysku*/

	if(dPlachta-dLatka>0){
        double tmp = (dPlachta-dLatka)/(dLatka-prekryv);
        /*printf("varianta B stra A tmp je %.20f\n",tmp);*/
        varBStrA = ceil(tmp);
       /* printf("varianta B stra A ceil je %.20f\n",varBStrA);*/
       /* printf("rozdil je: %.20f\n", varBStrA-tmp);*/
        if(varBStrA-tmp>0.999999999999){ /*kdyz rozdil cisel je vetsi nez max presnost double zaokrouhli dolu*/
            varBStrA = floor(tmp);
            }

        varBStrA += 1;
	}

	if(kPlachta-kLatka>0){
        double tmp = (kPlachta-kLatka)/(kLatka-prekryv);
       /* printf("varianta B stra B tmp je %.20f\n",tmp);*/
        varBStrB = ceil(tmp);
       /* printf("rozdil je: %.20f\n", varBStrB-tmp);*/
        if(varBStrB-tmp>0.999999999999){ /*kdyz rozdil cisel je vetsi nez max presnost double zaokrouhli dolu*/
            varBStrB = floor(tmp);
            }
        varBStrB += 1;
	}
   /* printf("--- varianta B pred snasobenim je %.20f\n %.20f\n",varBStrA, varBStrB);*/
	vyslB = varBStrA*varBStrB;
	/*printf("vysledek b je: %.20f\n",vyslB);*/

	/*porovnani variant*/

	if(vyslA<vyslB){
        printf("Pocet kusu latky: %.0f\n",vyslA);
        return 0;
	}

	else{
        printf("Pocet kusu latky: %.0f\n", vyslB);
        return 0;
	}
}



