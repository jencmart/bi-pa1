#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

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



	return leapYear;

}


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


	return 0;
}


int IsHolliday(const int nOfDays, const int isLeapYear){
	int numberOfDays = nOfDays;

	if(numberOfDays == 1) /*1.1*/
		return 1;

	if(isLeapYear)
		numberOfDays -= 1;

	
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

	int daysFromSaturday = days%7;

	if( daysFromSaturday == 0 || daysFromSaturday == 1)
		return 1;
	
return 0;
}



int IsWorkDayReduced ( int y, int m, int d, int leapYear ) {
	int numberOfDays = ToDays(m, d, leapYear);

	if( IsWeekend( y, numberOfDays, leapYear) )
		return 0;
	return 1;
}




int spocSvatOdDo(int y, int m1, int d1, int m2, int d2){
	/*vrati pocet svatku pripadajicich na vsedni dny v ramci jednoho roku*/
	int pocSvatku = 0;
	int leapYear = IsLeapYear( y );
	int from = ToDays(m1, d1, leapYear);
	int to  = ToDays(m2, d2, leapYear);


	if(from <= 1 && 1 <= to)/*1.1*/
		pocSvatku += IsWorkDayReduced(y, 1, 1, leapYear);

	/*korekce prestupneho roku*/
	if(leapYear)
		from -= 1;
		 to -= 1;
		
	if(from <= 120+1 && 120+1 <= to) /*1.5*/
		pocSvatku += IsWorkDayReduced(y, 5, 1, leapYear);

	
		
	if(from <= 120+8 && 120+8 <= to) /*8.5*/
		pocSvatku += IsWorkDayReduced(y, 5, 8, leapYear);
	
		
	if(from <= 181+5 && 181+5 <= to) /*5.7*/
		pocSvatku += IsWorkDayReduced(y, 7, 5, leapYear);


		
	if(from <= 181+6 && 181+6 <= to) /*6.7*/
		pocSvatku += IsWorkDayReduced(y, 7, 6, leapYear);

	
	if(from <= 243+28 && 243+28 <= to) /*28.9*/
		pocSvatku += IsWorkDayReduced(y, 9, 28, leapYear);


	if(from <= 273+28 && 273+28 <= to) /*28.10*/
		pocSvatku += IsWorkDayReduced(y, 10, 28, leapYear);



	if(from <= 304+17 && 304+17 <= to) /*17.11*/
		pocSvatku += IsWorkDayReduced(y, 11, 17, leapYear);

	if(from <=  334+24 &&  334+24 <= to) /*24.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 24, leapYear);

 
	if(from <=  334+25 &&  334+25 <= to) /*25.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 25, leapYear);
 

	if(from <=  334+26 &&  334+26 <= to) /*26.12*/
		pocSvatku += IsWorkDayReduced(y, 12, 26, leapYear);

return pocSvatku;
}




int IsWorkDay ( int y, int m, int d ) {
	int leapYear;
	int numberOfDays;

	if( ! IsValidDate(y, m, d, &leapYear) )
		return 0;
	
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

	int dnuOdSoboty1;

	int pracDnuMimoVikendy;
	int rozdilDnu;

	int pocSvatku;
	
	int iRok;
	*cnt = 0;

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
			if (rozdilDnu == 0 ){
				*cnt = 0;
				return 1;
			}

			pracDnuMimoVikendy = rozdilDnu/7 * 5;
			if( rozdilDnu%7 !=1 && rozdilDnu%7 != 0 )			
				pracDnuMimoVikendy += (rozdilDnu%7) - 1;

			break;

		 	
		case 1 : /*poc datum Nedele*/
			if (rozdilDnu == 0   ){
				*cnt = 0;
				return 1;
			}
			pracDnuMimoVikendy = rozdilDnu/7 * 5;
			if( rozdilDnu%7 !=6 && rozdilDnu%7 != 0 )			
				pracDnuMimoVikendy += (rozdilDnu%7);

			break;
		 
		case 2 :
			if (rozdilDnu == 0 ){
				pracDnuMimoVikendy = 1;
				break;
			}

			pracDnuMimoVikendy = (rozdilDnu/7 ) * 5 + 1;
			if( rozdilDnu%7 !=5 && rozdilDnu%7 != 6 )			
				pracDnuMimoVikendy += (rozdilDnu%7);
			break;


		case 3 :
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
			if (rozdilDnu == 0 ){
					pracDnuMimoVikendy = 1;
					break;
				}

			pracDnuMimoVikendy = (rozdilDnu/7  ) * 5 + 1;

			if( rozdilDnu%7 != 0 && rozdilDnu%7 != 1 && rozdilDnu%7 != 2 )			
					pracDnuMimoVikendy += (rozdilDnu%7) -2 ;

				break;

		}	
		
	
	/*printf("Pracovnich dnu (po, ut ,st ct, pa) Je : %d\n", pracDnuMimoVikendy);*/



	/*POCITANI SVATKU*/


	if(y2 - y1 == 0){
		pocSvatku = spocSvatOdDo(y1, m1, d1, m2, d2);
		*cnt = pracDnuMimoVikendy - pocSvatku;
		
	}

	if(y2 - y1 == 1){
		pocSvatku = spocSvatOdDo(y1, m1, d1, 12, 31);
		pocSvatku += spocSvatOdDo(y2, 1, 1, m2, d2);
		*cnt = pracDnuMimoVikendy - pocSvatku;
		
	}

	
	
	if(y2 - y1 >= 2){
		pocSvatku = spocSvatOdDo(y1, m1, d1, 12, 31); /*konec prvniho roku*/
		pocSvatku += spocSvatOdDo(y1+1, 1, 1, 1, 1); /*1.1 nasledujiciho roku*/


		if(   !(m2 == 1 && d2 == 1)     ) /*pokud je to 1. 1. neres to, postara se o to  cyklus*/
			pocSvatku += spocSvatOdDo(y2, 1, 2, m2, d2); /* jinak se o to taky postara cyklus*/
		
		for( iRok = y1+1; iRok < y2 ; iRok++){
			int prestup = IsLeapYear(iRok);

			int dnuOdSoboty = ( 334+26 + prestup + YearsToDaysSince2K(iRok, prestup)  ) % 7;

			switch (dnuOdSoboty){
				case 0 : /*sobota*/
					pocSvatku += 9;
					break;
				 	
				case 1 : /*nedele*/
					pocSvatku += 6;
					break;
				 
				case 2 : /*pondeli*/
					pocSvatku += 6;
					break;

				case 3 : /*utery*/
					pocSvatku += 9;
					break;

				case 4 : /*streda*/
					pocSvatku += 9;
					break;

				case 5 : /*ctvrtek*/
					pocSvatku += 8;				
					break;

				case 6 : /*patek*/
					pocSvatku += 8;
					break;

			}	
		}

	*cnt = pracDnuMimoVikendy - pocSvatku;
	
	
	}

	/*printf("pocet svatku o vsedni dny: %d\n", pocSvatku);*/
	/*printf("Realny pocet pracovnich dnu: %d\n", *cnt);*/
	return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  int cnt;

  assert ( IsWorkDay ( 2016, 11, 11 ) );
  assert ( ! IsWorkDay ( 2016, 11, 12 ) );
  assert ( ! IsWorkDay ( 2016, 11, 17 ) );
  assert ( ! IsWorkDay ( 2016, 11, 31 ) );
  assert ( IsWorkDay ( 2016,  2, 29 ) );
  assert ( ! IsWorkDay ( 2004,  2, 29 ) );
  assert ( ! IsWorkDay ( 2001,  2, 29 ) );
  assert ( ! IsWorkDay ( 1996,  1,  1 ) );
  assert ( CountWorkDays ( 2016, 11,  1,
                           2016, 11, 30, &cnt ) == 1
           && cnt == 21 );
  assert ( CountWorkDays ( 2016, 11,  1,
                           2016, 11, 17, &cnt ) == 1
           && cnt == 12 );
  assert ( CountWorkDays ( 2016, 11,  1,
                           2016, 11,  1, &cnt ) == 1
           && cnt == 1 );
  assert ( CountWorkDays ( 2016, 11, 17,
                           2016, 11, 17, &cnt ) == 1
           && cnt == 0 );
  assert ( CountWorkDays ( 2016,  1,  1,
                           2016, 12, 31, &cnt ) == 1
           && cnt == 254 );
  assert ( CountWorkDays ( 2015,  1,  1,
                           2015, 12, 31, &cnt ) == 1
           && cnt == 252 );
  assert ( CountWorkDays ( 2000,  1,  1,
                           2016, 12, 31, &cnt ) == 1
           && cnt == 4302 );
  assert ( CountWorkDays ( 2001,  2,  3,
                           2016,  7, 18, &cnt ) == 1
           && cnt == 3911 );
  assert ( CountWorkDays ( 2014,  3, 27,
                           2016, 11, 12, &cnt ) == 1
           && cnt == 666 );
  assert ( CountWorkDays ( 2001,  1,  1,
                           2000,  1,  1, &cnt ) == 0 );
  assert ( CountWorkDays ( 2001,  1,  1, 2015,  2, 29, &cnt ) == 0 );


/*z fitwikii*/

  assert ( CountWorkDays  ( 2416, 4, 3, 2531, 1, 4, &cnt ) == 1  && cnt == 29038 );




assert (!IsWorkDay(2018, 123, 124));

assert (CountWorkDays(2004, 12, 25, 2004,12,31,&cnt) == 1 && cnt == 5);

assert (CountWorkDays(1999, 12, 31, 2000, 12, 31, &cnt) == 0 && cnt == 0);

assert (  CountWorkDays ( 2004, 12, 26, 2004, 12, 31, &cnt ) == 1 && cnt == 5);





	printf("%d", cnt);



  return 0;
}
#endif /* __PROGTEST__ */
