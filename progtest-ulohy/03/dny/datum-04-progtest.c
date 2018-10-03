#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

typedef struct {
   int    y;
   int    m;
   int    d;
   short  l;
   int    dty;
   int    df2000;
} TDATE;

short IsLeapYear(int y){
	short leapYear = 0;

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

int YrToDaysFrom2K(int y) {  /* tohle bude blbe !! pro velka cisla !! */
	int yrSince2K = y - 2000 -1; /*mimo rok 2000*/

	if(! (yrSince2K+1))
		return 0;
	if(! yrSince2K) 
		return 366;

	/*dni_2K +  dny_roky_mezi + dny%4_Leap - dny%100_Not_Leap + dny%400_Leap - dny%4000_Not_Leap*/
	else{ return 366 + yrSince2K*365 + yrSince2K/4 - yrSince2K/100 + yrSince2K/400 - (y-1)/4000; }
}

int DaysThisYear(TDATE datum){
	int numDaysInMonth[] = {31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
	int pocDni = 0;
	short i;

	for(i = 0; i< (datum.m-1) ; i++)
		pocDni = numDaysInMonth[i];
	
	if(datum.l &&  datum.m>=3 )
		pocDni += datum.d+1;
	else
		pocDni += datum.d;
return pocDni;	
}

/*------------------SUB FUNCTIONS --------------------------------------------------------------*/

int DaysFrom2000(TDATE datum){
	return YrToDaysFrom2K(datum.y) + DaysThisYear(datum); /* vcetne 1.1.2000 */
}

short IsWeekend(TDATE datum){

	int daysFromFriday2K = datum.df2000%7;

	if( daysFromFriday2K == 1 || daysFromFriday2K == 2)
		return 1;
	else{return 0; }
}

short IsWeekendZellerStyle(TDATE datum){
	short day; /*0 saturday -  6friday */

	if(datum.m == 1 || datum.m == 2){
		datum.m += 12;
		datum.y -=1;

	}

	day = (datum.d + 13*(datum.m+1)/5 + datum.y + datum.y/4 - datum.y/100 + datum.y/400 - datum.y/4000) % 7;

	switch (day){

	case 0 : printf("sobota\n"); break;
	case 1 : printf("nedele\n"); break;
	case 2 : printf("pondeli\n"); break;
	case 3 : printf("utery\n"); break;	
	case 4 : printf("streda\n"); break;
	case 5 : printf("ctvrtek\n"); break;
	case 6 : printf("patek\n"); break;
}


	return day;
}

short IsHolliday(TDATE datum){


	if( datum.dty == 1){ /*1.1 */
	return 0;
	}

	if( datum.l )
		datum.dty -= 1;
	if(  
	     datum.dty == 120+1 || /*1.5*/
	     datum.dty == 120+8 || /*8.5*/
	     datum.dty == 181+5 || /*5.7*/
	     datum.dty == 181+6 || /*6.7*/
	     datum.dty == 243+28 || /*28.9*/
	     datum.dty == 273+28 || /*28.10*/
	     datum.dty == 304+17 || /*17.11*/
	     datum.dty == 334+24 || /*24.12*/
	     datum.dty == 334+25 || /*25.12*/
	     datum.dty == 334+26 /*26.12*/  ){
	return 1;} 
	else{return 0; }	
}

short IsValidDate(TDATE datum){
	/*General*/
	if(datum.y<2000)
		return 0;
	if(datum.m<1 || datum.m>12)
		return 0;
	if(datum.d<1 || datum.d>31)
		return 0;
	/*February*/
	if (datum.m == 2 && datum.d> 28 + datum.l)
		return 0;
	/*30 days*/
	if( (datum.m==4 || datum.m==6 || datum.m==9 || datum.m==11) && datum.d>30)
		return 0;
return 1;
}

 /* ----------------------- IS WORK DAY ---------------------------------------------------------*/

int IsWorkDay ( int y, int m, int d ) {
	TDATE datum;
	datum.y = y;
	datum.m = m;
	datum.d = d;
	datum.l = IsLeapYear(datum.y);
	datum.dty = DaysThisYear(datum);
	datum.df2000 = YrToDaysFrom2K(datum.y) + datum.dty;


	IsWeekendZellerStyle(datum);

	if(! IsValidDate(datum)){/*nevola nic dalsiho*/
		return 0;
	}
	if( IsHolliday(datum)){/*nevola nic dalsiho*/
		return 0;
	}
	if(IsWeekend(datum)) {/*nevola nic dalsiho*/
		return 0;
}

	else {return 1; }
}


 /* ---------------------- COUNT WORK DAYS ---------------------------------------------------------*/

int IsWeekday( int daysFrom2000 ) {
	int daysFromFriday2K = daysFrom2000%7;

	if( daysFromFriday2K == 1 || daysFromFriday2K == 2)
		return 0;
	else
		return 1; 
}

int spocSvatOdDo(TDATE datum1, TDATE datum2){
	int pseudoDaysFrom2000 = datum1.df2000 - datum1.dty;
	int pocSvatku = 0;
	
	if(datum1.dty <= 1 && 1 <= datum2.dty) /*1.1*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 1);	
	if(datum1.dty <= 121+datum1.l && 121+datum1.l <= datum2.dty ) /*1.5*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 121 + datum1.l);
	if(datum1.dty <= 128+ datum1.l && 128+ datum1.l <= datum2.dty ) /*8.5*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 128 + datum1.l);	
	if(datum1.dty <= 186+datum1.l && 186+datum1.l <= datum2.dty  )/*5.7*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 186 + datum1.l);	
	if(datum1.dty <= 187+datum1.l && 187+datum1.l <= datum2.dty  )/*6.7*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 187 + datum1.l);	
	if(datum1.dty <= 243+28+datum1.l && 243+28+datum1.l <= datum2.dty ) /*28.9*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 271 + datum1.l);	
	if(datum1.dty <= 273+28+datum1.l && 273+28+datum1.l <= datum2.dty ) /*28.10*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 301 + datum1.l);
	if(datum1.dty <= 304+17+datum1.l && 304+17+datum1.l <= datum2.dty ) /*17.11*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 321 + datum1.l);
	if(datum1.dty <=  334+24+datum1.l &&  334+24+datum1.l <= datum2.dty ) /*24.12*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 358 + datum1.l);
	if(datum1.dty <=  334+25+datum1.l &&  334+25+datum1.l <= datum2.dty)  /*25.12*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 359 + datum1.l);
	if(datum1.dty <=  334+26+datum1.l &&  334+26+datum1.l <= datum2.dty ) /*26.12*/
		pocSvatku += IsWeekday(pseudoDaysFrom2000 + 360 + datum1.l);
return pocSvatku;
}


int CountHolidaysOnWeekdays(TDATE datum1, TDATE datum2){
	int pocetSvatku = 0;
	int iRok;
	TDATE konecRoku;
	TDATE zacatekRokuD2;

	konecRoku.y = datum1.y;
	konecRoku.m = 12;
	konecRoku.d = 31;
	konecRoku.l = datum1.l;
	konecRoku.dty = DaysThisYear(konecRoku);
	konecRoku.df2000 = YrToDaysFrom2K(konecRoku.y) + konecRoku.dty;	
	zacatekRokuD2.y = datum2.y;
	zacatekRokuD2.m = 1;
	zacatekRokuD2.d = 1;
	zacatekRokuD2.l = datum2.l;
	zacatekRokuD2.dty = 1;
	zacatekRokuD2.df2000 = YrToDaysFrom2K(zacatekRokuD2.y) + zacatekRokuD2.dty;	

	if(datum1.y == datum2.y )
		return spocSvatOdDo(datum1, datum2);
	 if(datum2.y - datum1.y == 1){
		pocetSvatku = spocSvatOdDo(datum1, konecRoku);
		pocetSvatku += spocSvatOdDo(zacatekRokuD2, datum2);	
		return pocetSvatku;
	} else{
		pocetSvatku = spocSvatOdDo(datum1, konecRoku);
		if(datum2.m > 1){ /*neres svatek v lednu - postara se o to cyklus*/
			zacatekRokuD2.m += 1;
			zacatekRokuD2.dty += 31;
			zacatekRokuD2.df2000 += 31;
			pocetSvatku += spocSvatOdDo(zacatekRokuD2, datum2); 
		}
		zacatekRokuD2.y =  datum1.y +1;
		zacatekRokuD2.m = 1;
		zacatekRokuD2.d = 1;
		zacatekRokuD2.l = IsLeapYear(zacatekRokuD2.y);
		zacatekRokuD2.dty = 1;
		zacatekRokuD2.df2000 = YrToDaysFrom2K(zacatekRokuD2.y) + zacatekRokuD2.dty;	

		pocetSvatku += spocSvatOdDo(zacatekRokuD2, zacatekRokuD2);/*1.1 nasledujiciho roku*/

		for( iRok = datum1.y+1; iRok < datum2.y; iRok++){ /*prochazej vsechny cele roky v intervalu*/

			/*urci DEN 26.12.iRok a podle to urci svatky na cely rok*/
			int dnuOdPatku = (360 + IsLeapYear(iRok) + YrToDaysFrom2K(iRok))  % 7;

			switch (dnuOdPatku){
				case 0: pocetSvatku += 8;
					break;
				case 1:	pocetSvatku += 9;
					break;
				case 2: pocetSvatku += 6;
					break;
				case 3: pocetSvatku += 6;
					break;
				case 4: pocetSvatku += 9;
					break;
				case 5 :pocetSvatku += 9;
					break;
				case 6 :pocetSvatku += 8;				
					break;
			}	
		}
	return pocetSvatku;
	}
}

int CountWeekdays(TDATE datum1, TDATE datum2){
	int allDays = datum2.df2000 - datum1.df2000 + 1;
	int vsednichDnu = (allDays/7)*5;
	int dnuNavic = allDays%7;

	switch(datum1.df2000 % 7){
	case 0: /*patek*/
		if (dnuNavic <=3 ) /* Pa, So, Ne*/
			vsednichDnu += 1;
		if (dnuNavic > 3) /* Po, Ut, St*/
			vsednichDnu += dnuNavic - 2;
		break;
	case 1: /*sobota*/
		if (dnuNavic > 2) /*tzn Po, Ut, St, Ct*/
			vsednichDnu += dnuNavic - 2;
		break;
	case 2: /*nedele*/
		if(dnuNavic > 1) /*tzn Po, Ut, St, Ct, Pa*/
			vsednichDnu += dnuNavic -1;
		break;
	case 3: /*pondeli*/
		if(dnuNavic < 6) /*tzn Po, Ut, St, Ct, Pa*/
			vsednichDnu += dnuNavic;
		break;
	case 4: /*utery*/
		if(dnuNavic < 5) /*tzn Ut, St, Ct, Pa*/
			vsednichDnu += dnuNavic;
		break;
	case 5: /*streda*/
		if(dnuNavic < 4) /* St, Ct, Pa*/
			vsednichDnu += dnuNavic;
		if(dnuNavic == 4 || dnuNavic == 5) /*So, Ne*/
			vsednichDnu += 3;
		if(dnuNavic == 6) /* Po*/
			vsednichDnu += 4;
		break;
	case 6: /*ctvrtek*/
		if (dnuNavic < 3) /*tzn Ct, Pa*/
			vsednichDnu += dnuNavic;
		if(dnuNavic == 3 || dnuNavic == 4) /*So, Ne*/
			vsednichDnu += 2;
		if (dnuNavic > 4) /*Po, Ut*/
			vsednichDnu += dnuNavic - 2;
		break;
	}
	return vsednichDnu;
}

short IsValidRange(TDATE datum1, TDATE datum2){
	/*Zkontroluje validnost datumu a porovna platnost intervalu*/
	if(! IsValidDate(datum1))
		return 0;

	if(! IsValidDate(datum2))
		return 0;
	if (datum1.df2000 >  datum2.df2000)
		return 0;

	else {return 1;}
}

int CountWorkDays ( int y1, int m1, int d1, int y2, int m2, int d2, int * cnt ) {
	TDATE datum1;
	TDATE datum2;
	int vsednichDnu = 0;
	int svatkuOVsedniDny= 0; 
	*cnt = 0;
	datum1.y = y1;
	datum1.m = m1;
	datum1.d = d1;
	datum1.l = IsLeapYear(datum1.y);
	datum1.dty = DaysThisYear(datum1);
	datum1.df2000 = YrToDaysFrom2K(datum1.y) + datum1.dty;
	datum2.y = y2;
	datum2.m = m2;
	datum2.d = d2;
	datum2.l = IsLeapYear(datum2.y);
	datum2.dty = DaysThisYear(datum2);
	datum2.df2000 = YrToDaysFrom2K(datum2.y) + datum2.dty;
	
	if(! IsValidRange(datum1, datum2) ) /*vola IsValidDate*/
		return 0;
	
	vsednichDnu = CountWeekdays(datum1, datum2);
	svatkuOVsedniDny = CountHolidaysOnWeekdays(datum1, datum2);
	*cnt = vsednichDnu - svatkuOVsedniDny;
return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{


	IsWorkDay ( 4000, 3, 1 );
/*  int cnt;

 assert ( IsWorkDay ( 2008, 1, 2 ) );
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
  assert ( CountWorkDays ( 2001,  1,  1,
                           2015,  2, 29, &cnt ) == 0 );

   assert   ( CountWorkDays ( 2076, 7, 4, 5094763, 6, 3, &cnt ) == 1 && cnt==1288603482);
assert( CountWorkDays ( 2416, 4, 3, 2531, 1, 4, &cnt )  == 1 && cnt==29038);


assert( CountWorkDays ( 2000, 5, 8, 2000, 12, 31, &cnt ) == 1 && cnt == 163 );

assert(CountWorkDays ( 2000, -10, -10, 2200, 10, 1, &cnt ) == 0  );
assert( CountWorkDays ( 2008, 9, 30, 2008, 11, 11, &cnt )  == 1 && cnt==30);


assert (!IsWorkDay(2018, 123, 124));

assert (CountWorkDays(2004, 12, 26, 2004,12,31,&cnt) == 1 && cnt == 5);

assert (CountWorkDays(1999, 12, 31, 2000, 12, 31, &cnt) == 0 && cnt == 0);

assert( CountWorkDays ( 2004, 12, 25, 2004, 12, 31, &cnt )  == 1 && cnt == 5);

*/
  return 0;
}
#endif /* __PROGTEST__ */
