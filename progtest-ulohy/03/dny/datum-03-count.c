
int IsWorkDayReduced ( int y, int m, int d, short leapYear ) {
	int numberOfDays = DaysThisYear(m, d, leapYear);

	if( IsWeekend( y, numberOfDays, leapYear) )
		return 0;
	return 1;
}

int spocSvatOdDo(int y, int m1, int d1, int m2, int d2){
	/*vrati pocet svatku pripadajicich na vsedni dny v ramci jednoho roku*/
	int pocSvatku = 0;
	short leapYear = IsLeapYear( y );
	int from = DaysThisYear(m1, d1, leapYear);
	int to  = DaysThisYear(m2, d2, leapYear);
	printf("FROM:%d\nTO:%d\n", from, to);

	/*zkratka pro jeden den
	if(m1 == m2 && d1 == d2){
		pocSvatku += IsWorkDayReduced(y, m1, d1, leapYear);
		return pocSvatku;
	} */

	if(from <= 1 && 1 <= to)/*1.1*/
		pocSvatku += IsWorkDayReduced(y, 1, 1, leapYear);

	/*korekce prestupneho roku*/
	if(leapYear)
		from -= 1;
		 to -= 1;
		
	if(from <= 120+1 && 120+1 <= to) /*1.5*/
		pocSvatku += IsWorkDayReduced(y, 5, 1, leapYear);

	
		
	if(from <= 120+8 && 120+8 <= to){ /*8.5*/
		pocSvatku += IsWorkDayReduced(y, 5, 8, leapYear);
	printf("Svatek 8.5, zatim svatku: %d\n", pocSvatku);
		
}
	
		
	if(from <= 181+5 && 181+5 <= to){ /*5.7*/
		pocSvatku += IsWorkDayReduced(y, 7, 5, leapYear);
	printf("Svatek 5.7, zatim svatku: %d\n", pocSvatku);
		
}	


		
	if(from <= 181+6 && 181+6 <= to){ /*6.7*/
		pocSvatku += IsWorkDayReduced(y, 7, 6, leapYear);
	printf("Svatek 6.7, zatim svatku: %d\n", pocSvatku);
		
}

	
	if(from <= 243+28 && 243+28 <= to){ /*28.9*/
		pocSvatku += IsWorkDayReduced(y, 9, 28, leapYear);
	printf("Svatek 28.9, zatim svatku: %d\n", pocSvatku);
		
}

	if(from <= 273+28 && 273+28 <= to){ /*28.10*/
		pocSvatku += IsWorkDayReduced(y, 10, 28, leapYear);
	printf("Svatek 28.10, zatim svatku: %d\n", pocSvatku);
		
}



	if(from <= 304+17 && 304+17 <= to) { /*17.11*/
		pocSvatku += IsWorkDayReduced(y, 11, 17, leapYear);
		printf("Svatek 11.17, zatim svatku: %d\n", pocSvatku);

		}

	if(from <=  334+24 &&  334+24 <= to) {/*24.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 24, leapYear);
	printf("Svatek 24.12, zatim svatku: %d\n", pocSvatku);
		
}

 
	if(from <=  334+25 &&  334+25 <= to){ /*25.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 25, leapYear);
	printf("Svatek 25.12, zatim svatku: %d\n", pocSvatku);
		
}
 

	if(from <=  334+26 &&  334+26 <= to){ /*26.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 26, leapYear);

	printf("Svatek 26.15, zatim svatku: %d\n", pocSvatku);
		
}


return pocSvatku;
}



















int CountWorkDays ( int y1, int m1, int d1, int y2, int m2, int d2, int * cnt ) {
	short leapYear1 = IsLeapYear(y1);
	short leapYear2 = IsLeapYear(y2);

	int nDays1;
	int nDays2;

	int dnuOdSoboty1;

	int pracDnuMimoVikendy;
	int rozdilDnu;

	int pocSvatku;
	
	int iRok;



	/*ZKONTROLUJ PLATNY VSTUP*/
	printf("------------------------------------------------------\n");

	if( (! IsValidDate(y1, m1, d1, leapYear1)) || (! IsValidDate(y2, m2, d2, leapYear2))  )
		return 0;
	
	nDays1 = DaysThisYear(m1, d1, leapYear1) + YrToDaysFrom2K(y1, leapYear1);
	nDays2 = DaysThisYear(m2, d2, leapYear2) + YrToDaysFrom2K(y2, leapYear2);



	if( nDays1 > nDays2 )
		return 0;






	/*SPOCITEJ POCET VSEDNICH DNU V ROZMEZI*/	
	rozdilDnu = nDays2 - nDays1;
	printf("rozdil dnu je: %d\n", rozdilDnu);

	dnuOdSoboty1 = nDays1%7;

		switch (dnuOdSoboty1){

		case 0 : /*pocatecni datum so*/
			printf("Je to sobota\n");
			if (rozdilDnu == 0 ){
				*cnt = 0;
				return 1;
			}

			pracDnuMimoVikendy = rozdilDnu/7 * 5;
			if( rozdilDnu%7 !=1 && rozdilDnu%7 != 0 )			
				pracDnuMimoVikendy += (rozdilDnu%7) - 1;

			break;

		 	
		case 1 : /*poc datum Nedele*/
			printf("Je to nedele\n");
			if (rozdilDnu == 0   ){
				*cnt = 0;
				return 1;
			}
			pracDnuMimoVikendy = rozdilDnu/7 * 5;
			if( rozdilDnu%7 !=6 && rozdilDnu%7 != 0 )			
				pracDnuMimoVikendy += (rozdilDnu%7);

			break;
		 
		case 2 :
			printf("Je to pondeli\n");
			if (rozdilDnu == 0 ){
				printf("je to pondeli\n");
				pracDnuMimoVikendy = 1;
				break;
			}

			pracDnuMimoVikendy = (rozdilDnu/7 ) * 5 + 1;
			if( rozdilDnu%7 !=5 && rozdilDnu%7 != 6 )			
				pracDnuMimoVikendy += (rozdilDnu%7);
			break;


		case 3 :
			printf("Je to utery\n");

			if (rozdilDnu == 0 ){
				pracDnuMimoVikendy = 1;
				break;
			}

			pracDnuMimoVikendy = (rozdilDnu/7) * 5  + 1;
			if( rozdilDnu%7 !=4 && rozdilDnu%7 != 5 && rozdilDnu%7 != 6 )			
				pracDnuMimoVikendy += (rozdilDnu%7);


			if ( rozdilDnu%7 == 4 || rozdilDnu%7 == 5  )
					pracDnuMimoVikendy += 3;


			if ( rozdilDnu%7 == 6 )
					pracDnuMimoVikendy += 4;
				break;




		case 4 :
			printf("Je to streda\n");


			if (rozdilDnu == 0 ){
					pracDnuMimoVikendy = 1;
					break;
				}

			pracDnuMimoVikendy = (rozdilDnu/7 ) * 5 + 1;

			if( rozdilDnu%7 == 1 || rozdilDnu%7 == 2)			
					pracDnuMimoVikendy += (rozdilDnu%7);
					

			if( rozdilDnu%7 == 3 || rozdilDnu%7 == 4)			
					pracDnuMimoVikendy += 2;
					

			if( rozdilDnu%7 == 5 || rozdilDnu%7 == 6)			
					pracDnuMimoVikendy += (rozdilDnu%7) -2 ;

				break;


		case 5 :
			printf("Je to ctvrtek\n");


			if (rozdilDnu == 0 ){
					pracDnuMimoVikendy = 1;
					break;
				}

			pracDnuMimoVikendy = (rozdilDnu/7 ) * 5 + 1;

			if( rozdilDnu%7 == 1 || rozdilDnu%7 == 2 || rozdilDnu%7 == 3)			
					pracDnuMimoVikendy += 1;

			if( rozdilDnu%7 == 4 || rozdilDnu%7 == 5 || rozdilDnu%7 == 6)			
					pracDnuMimoVikendy += (rozdilDnu%7) -2 ;

				break;

		case 6 :
			printf("Je to patek\n");



			if (rozdilDnu == 0 ){
					pracDnuMimoVikendy = 1;
					break;
				}

			pracDnuMimoVikendy = (rozdilDnu/7  ) * 5 + 1;

			if( rozdilDnu%7 != 0 && rozdilDnu%7 != 1 && rozdilDnu%7 != 2 )			
					pracDnuMimoVikendy += (rozdilDnu%7) -2 ;

				break;

		}	
		
	
	printf("Pracovnich dnu (po, ut ,st ct, pa) Je : %d\n", pracDnuMimoVikendy);



	/*SPOCITEJ MNOZSTVI SVATKU O VSEDNI DNY*/


	if(y2 - y1 == 0){
		printf("rozdil let je 0\n");
		pocSvatku = spocSvatOdDo(y1, m1, d1, m2, d2);
		
		*cnt = pracDnuMimoVikendy - pocSvatku;
		
	}

	if(y2 - y1 == 1){
		printf("rozdil let je 1\n");
		pocSvatku = spocSvatOdDo(y1, m1, d1, 12, 31);
		pocSvatku += spocSvatOdDo(y2, 1, 1, m2, d2);
		*cnt = pracDnuMimoVikendy - pocSvatku;
		
	}

	
	
	if(y2 - y1 >= 2){
		printf("rozdil let je 2 a vice\n");
		pocSvatku = spocSvatOdDo(y1, m1, d1, 12, 31); /*konec prvniho roku*/
		pocSvatku += spocSvatOdDo(y1+1, 1, 1, 1, 1); /*1.1 nasledujiciho roku*/


		if(   !(m2 == 1 && d2 == 1)     ) /*pokud je to 1. 1. neres to, postara se o to  cyklus*/
			pocSvatku += spocSvatOdDo(y2, 1, 2, m2, d2); /* jinak se o to taky postara cyklus*/
		
		for( iRok = y1+1; iRok < y2 ; iRok++){
			int prestup = IsLeapYear(iRok);

			int dnuOdSoboty = ( 334+26 + prestup + YrToDaysFrom2K(iRok, prestup)  ) % 7;
			printf("Cyklus pro rok:%d", iRok);

			switch (dnuOdSoboty){
				case 0 : /*sobota*/
					pocSvatku += 9;
					printf("  sobota -> +9 \n");
					break;
				 	
				case 1 : /*nedele*/
					printf("  sobota -> +6 \n");
					pocSvatku += 6;
					break;
				 
				case 2 : /*pondeli*/
					pocSvatku += 6;
					printf("  pondeli -> +6 \n");
					break;

				case 3 : /*utery*/
					printf("  utery -> +9 \n");
					pocSvatku += 9;
					break;

				case 4 : /*streda*/
					printf("  streda -> +9 \n");
					pocSvatku += 9;
					break;

				case 5 : /*ctvrtek*/
					printf("  ctvrtek -> +8 \n");
					pocSvatku += 8;				
					break;

				case 6 : /*patek*/
					printf("  patek -> +8 \n");
					pocSvatku += 8;
					break;

			}	
		}

	

	*cnt = pracDnuMimoVikendy - pocSvatku;
	
	
	}

	printf("pocet svatku o vsedni dny: %d\n", pocSvatku);
	printf("Realny pocet pracovnich dnu: %d\n", *cnt);
	return 1;
}

