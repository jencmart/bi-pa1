#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */


int IsValidDate(int y, int m, int d, int * leapYear){
	int february = 28;

	if(y<2000)
		return 0;
	
	if(m<1 || m>12)
		return 0;

	if(d<1 || d>31)
		return 0;
	
	/* is leap-year - feb 29*/
	if( IsLeapYear(y) ){
		february = 29;
		*leapYear = 1;
	} else{ *leapYear = 0; }
	
	
	/*test february*/
	if (m == 2 && d>february)
		return 0;

	/*test 30 day long months*/
	if( (m==4 || m==6 || m==9 || m==11) && d>30)
		return 0;

return 1;
}

int IsLeapYear(int y){

	
	int leapYear = 0;

	if(y%4 == 0)
		leapYear = 1;
	if(y%100 == 0)
		leapYear = 0;
	if(y%400 == 0)
		leapYear = 1;
	if(y%4000 == 0)
		leapYear = 0;


	if(leapYear)
		printf("rok je prestupny\n");

	return leapYear;

}

int ToDays(int m, int d, int leap){


	/*pozor v prestupnych letech mi to vraci o den min. proc ?*/
	
	switch (m){
	case 1 : 
		return d;

	case 2 :
		return (31 + d);

	case 3 :
		return (59 + leap + d);
	
	case 4 :
		return (90 + leap + d);

	case 5 :
		return (120 + leap + d);

	case 6 :
		return (151 + leap + d);

	case 7 :
		return (181 + leap + d);

	case 8 :
		return (212 + leap + d);

	case 9 :
		return (243 + leap + d);

	case 10 :
		return (273 + leap + d);

	case 11 :
		return (304 + leap + d);

	case 12 :
		return (334 + leap + d);
	}
}


int IsHolliday(const int nOfDays, const int isLeapYear){
	int numberOfDays = nOfDays;

	if(numberOfDays == 1) /*1.1*/
		return 1;

	if(isLeapYear)
		numberOfDays -= 1;

	printf("pocet dnu od zac roku:%d\n", numberOfDays);
	
	if(  numberOfDays == 120+1 || /*1.5*/
	     numberOfDays == 120+8 || /*8.5*/
	     numberOfDays == 181+5 || /*5.7*/
	     numberOfDays == 181+6 || /*6.7*/
	     numberOfDays == 243+28 || /*28.9*/
	     numberOfDays == 273+28 || /*28.10*/
	     numberOfDays == 304+17 || /*17.11*/
	     numberOfDays == 334+24 || /*24.12*/
	     numberOfDays == 334+25 || /*25.12*/
	     numberOfDays == 334+26 /*26.12*/  ){
	return 1;
	}

	return 0;	
}





int YearsToDaysSince2K(int y, int leap) {
	int yrSince2K = y - 2000;
	
	int n4LY = yrSince2K/4;
	int nNot100LY = yrSince2K/100;
	int n400LY = yrSince2K/400;
	int nNot4000LY = yrSince2K/4000;


	int numberOfDays = (yrSince2K * 365) + n4LY - nNot100LY +  n400LY -  nNot4000LY ;

	/*tohle koriguje nejakou odchylku ale nevim jakou..... !!!!!!!!!!!!!!!!! */
	if(leap)
		numberOfDays -= 1;


	return numberOfDays;

}



int IsWeekend(int y, int numberOfDays, int leap){
	
	int days = YearsToDaysSince2K( y, leap ) + numberOfDays;
	printf("dnu od 1.1. 2000: %d\n", days);

	int daysFromSaturday = days%7;
	printf("dnu od Soboty: %d \n",  daysFromSaturday);

	if( daysFromSaturday == 0 || daysFromSaturday == 1)
		return 1;
	
return 0;
}



int spocSvatOdDo(int y, int m1, int d1, int m2, int d2){
	/*vrati pocet svatku pripadajicich na vsedni dny v ramci jednoho roku*/
	int pocSvatku = 0;
	int leapYear = IsLeapYear( y );
	int from = ToDays(m1, d1, leapYear);
	int to  = ToDays(m1, d1, leapYear);

	/*zkratka pro jeden den
	if(m1 == m2 && d1 == d2){
		pocSvatku += IsWorkDayReduced(y, m1, d1, leapYear);
		return pocSvatku;
	} */

	if(from <= 1 && 1 >= to) /*1.1*/
		pocSvatku += IsWorkDayReduced(y, 1, 1, leapYear);
	
	/*korekce prestupneho roku*/
	if(leapYear)
		from -= 1;
		 to -= 1;
		
	if(from <= 120+1 && 120+1 >= to) /*1.5*/
		pocSvatku += IsWorkDayReduced(y, 5, 1, leapYear);
	
		
	if(from <= 120+8 && 120+8 >= to) /*8.5*/
		pocSvatku += IsWorkDayReduced(y, 5, 8, leapYear);
	
		
	if(from <= 181+5 && 181+5 >= to) /*5.7*/
		pocSvatku += IsWorkDayReduced(y, 7, 5, leapYear);
	
		
	if(from <= 181+6 && 181+6 >= to) /*6.7*/
		pocSvatku += IsWorkDayReduced(y, 7, 6, leapYear);

	
	if(from <= 243+28 && 243+28 >= to) /*28.9*/
		pocSvatku += IsWorkDayReduced(y, 9, 28, leapYear);


	if(from <= 273+28 && 273+28 >= to) /*28.10*/
		pocSvatku += IsWorkDayReduced(y, 10, 28, leapYear);


	if(from <= 304+17 && 304+17 >= to) /*17.11*/
		pocSvatku += IsWorkDayReduced(y, 11, 17, leapYear);


	if(from <=  334+24 &&  334+24 >= to) /*24.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 24, leapYear);

 
	if(from <=  334+25 &&  334+25 >= to) /*25.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 25, leapYear);

 
	if(from <=  334+26 &&  334+26 >= to) /*26.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 26, leapYear);


return pocSvatku;
}

int IsWorkDayReduced ( int y, int m, int d, int leapYear ) {
	int numberOfDays = ToDays(m, d, leapYear);

	if( IsWeekend( y, numberOfDays, leapYear) )
		return 0;
	return 1;
}




int IsWorkDay ( int y, int m, int d ) {
	int leapYear;
	int numberOfDays;

	if( ! IsValidDate(y, m, d, &leapYear) )
		return 0;
	
	printf("datum je validnii\n leapYear: %d\n", leapYear);
	
	numberOfDays = ToDays(m, d, leapYear);
	

	if( IsHolliday(numberOfDays, leapYear)  )
		return 0;

	if( IsWeekend( y, numberOfDays, leapYear) )
		return 0;
	return 1;
}





int CountWorkDays ( int y1, int m1, int d1, int y2, int m2, int d2, int * cnt ) {
	
	int leapYear1;
	int leapYear2;
	int nDays1;
	int nDays2;

	int diffYear = y2 - y1;
	int diffMonth = m2 - m1;
	int diffDay = d2 - d1;

	int dnuOdSoboty1;
	int dnuOdSoboty2;

	int pracDnuMimoVikendy;
	int rozdilDnu;

	int pocSvatku;
	
	int iRok;


	if( (! IsValidDate(y1, m1, d1, &leapYear1)) || (! IsValidDate(y2, m2, d2, &leapYear2))  )
		return 0;
	
	nDays1 = ToDays(m1, d1, leapYear1) + YearsToDaysSince2K(y1, leapYear1);
	nDays2 = ToDays(m2, d2, leapYear2) + YearsToDaysSince2K(y2, leapYear2);




	/*prevence spatneho vstupu*/
	if( nDays1 > nDays2 )
		return 0;



	/*ABSOLUTNI ROZDIL DNU*/	
	rozdilDnu = nDays2 - nDays1;


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



	/*POCITANI SVATKU*/


	if(y2 - y1 == 0){
		pocSvatku = spocSvatOdDo(y1, m1, d1, m2, d2);
		*cnt = pracDnuMimoVikendy - pocSvatku;
		return 1;
	}

	if(y2 - y1 == 1){
		pocSvatku = spocSvatOdDo(y1, m1, d1, 12, 31);
		pocSvatku += spocSvatOdDo(y2, 1, 1, m2, d2);
		*cnt = pracDnuMimoVikendy - pocSvatku;
		return 1;
	}

	
	
	if(y2 - y1 >= 2){
		pocSvatku = spocSvatOdDo(y1, m1, d1, 12, 31);
		if(   !(m2 == 1 && d2 == 1)     ) /*pokud je to 1. 1. neres to, postara se o to  cyklus*/
			pocSvatku += spocSvatOdDo(y2, 1, 2, m2, d2); /* jinak se o to taky postara cyklus*/
		
		for( iRok = y1+1; iRok< y2 ; iRok++){
			int prestup = IsLeapYear(iRok);

			int dnuOdSoboty = ( 334+26 + prestup + YearsToDaysSince2K(iRok, prestup)  ) % 7;


			switch (dnuOdSoboty1){
				case 0 : /*sobota*/
					pocSvatku += 10;
					break;
				 	
				case 1 : /*nedele*/
					pocSvatku += 6;
					break;
				 
				case 2 : /*pondeli*/
					pocSvatku += 6;
					break;

				case 3 : /*utery*/
					pocSvatku += 8;
					break;

				case 4 : /*streda*/
					pocSvatku += 8;
					break;

				case 5 : /*ctvrtek*/
					pocSvatku += 8;				
					break;

				case 6 : /*patek*/
					pocSvatku += 9;
					break;

			}	
		}

	*cnt = pracDnuMimoVikendy - pocSvatku;
	return 1;
	
	}


	printf("sem se to nesmi NIKDY ! dostat\n");
	return 1;


	


	/*pak muzu spocitat kolik mezi sebou maji svatku*/

	/*ale jak sakra zjistim kolik svatku z toho bylo o vinkendu ???!!! */

	/*pockat pockat. KDYZ DOKAZU SPOCITAT CO JE ZA DEN N1 TAK PRECE DOKAZU SPOCITAT I CO JE ZA DEN DEN SVATKU*/

	/*PAK MUZU PRO KAZDY SVATEK SPOCITAT CO JE TO ZA DEN A A A...... NO A STEJNE JAKO VIM, ZE VIKEND JE KAZDY 5 DEN, TAK VIM, ZE SVATEK JE KAZDY 365 DEN, O PRESTUPNY JE TO 366 PRO SVATKY MIMO 1.1 KTERY JE 366 O ROK POZDEJI*/	

	/*TEORETICKY BYCH MOHL PRO VSECHNY SVATECNI DNY POCITAT KAZDY ROK CO JE TO ZA DEN. ALE TO JE DOBRA SRACKA. TO JE VOLANI 12X KAZDY ROK VOLANE..... */

	/*moza by to slo udelat podobne jako pocitam prestupny rok... spocitam se kolikrat se mi to posune o "2dny" - to je kazdy prestupny rok. a pak to bude neco jako 4*1 + 1*2 + 4*1 + 1*2 kde 1*2 je kazdy leap year

	no a protoze budu vedet ze e e eee . zacinam napr. v pondeli. tak kazdy 5 a sety posun je posun do vikendu ..... hm ? takze  to podelim peti a sesti a zjistim kolikrat se mi to do toho vikendy dostalo a to pak odectu od celkoveho poctu svatecnich dnu. TE O RE TI CKY. MOZNA JE TO UUUUPLA PICOVA ALE PROC TO NEZKUSIT ZE.. HM? */



	




}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  int cnt;

  assert ( ! IsWorkDay ( 3999, 7, 6 ) );
	printf("11.11. Je pracovni den\n\n\n");
	

  assert ( ! IsWorkDay ( 2016, 11, 12 ) );
	printf("11.12. Je vikend\n\n\n");


  assert ( ! IsWorkDay ( 2004,  2, 29 ) );
	printf("2004. 2.29. je vikend\n\n\n");

  assert ( ! IsWorkDay ( 2001,  2, 29 ) );
	printf("2001. 2.29 neni den\n\n\n");

  assert ( ! IsWorkDay ( 1996,  1,  1 ) );
	printf("1.1.1996 je mimo rozsah\n\n\n");

  assert ( ! IsWorkDay ( 2000,  1,  1 ) );
	printf("1.1.2000 Je sobota\n\n\n");


  assert ( IsWorkDay ( 3999,  5, 7 ) );
	printf("Je to pondeli \n\n\n");


  assert( CountWorkDays(2003, 12, 29, 2004, 3, 5, &cnt)  );
  return 0;
}
#endif /* __PROGTEST__ */
