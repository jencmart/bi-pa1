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
   int    df2000; /*asi zrusim*/
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

short DaysThisYear(TDATE datum){
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



short weekDayZellerStyle(y, m, d){
	/*0 saturday -  6friday */

	if(m == 1 || m == 2){
		m += 12;
		y--;
	}
	return ((d + (13*(m+1))/5 + (y%100) + (y%100)/4 + (y/100)/4 + 5*(y/100)) % 7);
}

short IsHolliday(TDATE datum){
	short daysThisYr = DaysThisYear(datum);

	if( daysThisYr == 1){ /*1.1 */
	return 1;
	}

	if( datum.l )
		daysThisYr -= 1;
	if(  
	     daysThisYr == 120+1 || /*1.5*/
	     daysThisYr == 120+8 || /*8.5*/
	     daysThisYr == 181+5 || /*5.7*/
	     daysThisYr == 181+6 || /*6.7*/
	     daysThisYr == 243+28 || /*28.9*/
	     daysThisYr == 273+28 || /*28.10*/
	     daysThisYr == 304+17 || /*17.11*/
	     daysThisYr == 334+24 || /*24.12*/
	     daysThisYr == 334+25 || /*25.12*/
	     daysThisYr == 334+26 /*26.12*/  ){
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

short IsValidRange(TDATE datum1, TDATE datum2){
	/*Zkontroluje validnost datumu a porovna platnost intervalu*/
	if(! IsValidDate(datum1))
		return 0;
	if(! IsValidDate(datum2))
		return 0;
	if(datum2.y > datum1.y) 
		return 1;
	if (datum1.y > datum2.y)
		return 0;
	if (datum1.y == datum2.y){
		if(datum1.m > datum2.m)
			return 0;
		if(datum1.m == datum2.m && datum1.d > datum2.d)
			return 0;
	}
	return 1;
}



 /* ----------------------- IS WORK DAY ---------------------------------------------------------*/

int IsWorkDay ( int y, int m, int d ) {
	short denVTydnu;
	TDATE datum;
	datum.y = y;
	datum.m = m;
	datum.d = d;
	datum.l = IsLeapYear(y); /*uzitece pro vic veci */
	
		
	if(! IsValidDate(datum))/*nevola nic dalsiho*/
		return 0;

	if( IsHolliday(datum))/*nevola nic dalsiho*/
		return 0;
	
	denVTydnu = weekDayZellerStyle(y, m, d);
	if (denVTydnu == 0 || denVTydnu == 1)
		return 0;

	return 1; 
}
/* ---------------------- COUNT WORK DAYS ---------------------------------------------------------*/
int spocSvatOdDo(y, from, to){
	int i;
	int svatMes[] = {1, 5, 5, 7, 7, 9, 10, 11, 12, 12, 12};
	int svatDen[] = {1, 1, 8, 5, 6, 28, 28, 17, 24, 25, 26};
	int denSvat[] = {1, 121, 128, 186, 187, 271, 301, 321, 358, 359, 360};
	int pocSvatku = 0;
	
	/*ochrana prestupneho roku*/
	if(IsLeapYear(y) && to > 59 ){ /*pokud uz pricitame prestupny den...*/
		to -= 1;
		if(from > 59){ /*pokud uz pricitame prestupny den ..*/
		from -= 1;		
		}
	}
	for(i = 0; i<11; i++){
		if(from <= denSvat[i] && denSvat[i] <= to){
			short denSvatku = weekDayZellerStyle(y, svatMes[i], svatDen[i]); 
			if( denSvatku != 0 &&  denSvatku != 1 ) {
				printf("svatek: %d:%d:%d - %d\n",y, svatMes[i], svatDen[i], denSvatku);
				pocSvatku += 1;
				}
		}	
	}
return pocSvatku;
}

int CntHollidays(TDATE datum1, TDATE datum2){
	int pocetSvatku = 0;

	if(datum1.y == datum2.y )
		return spocSvatOdDo(datum1.y, datum1.dty, datum2.dty);

	 if(datum2.y - datum1.y == 1)
		return ( spocSvatOdDo(datum1.y, datum1.dty, 365) + spocSvatOdDo(datum2.y, 1, datum2.dty) ) ;

	/*VICE LET OD SEBE*/
	else{   int iRok; 
		pocetSvatku = spocSvatOdDo(datum1.y, datum1.dty, 365);
		pocetSvatku += spocSvatOdDo(datum1.y+1, 1, 1);/*1.1 roku datum1 + 1*/ 
		if(datum2.m > 1) /*mimo svatek 1.1. od zac roku do datum2 */
			pocetSvatku += spocSvatOdDo(datum2.y, 31, datum2.dty); 

		/*CYKLUS PRO ROKY MEZI ... */
		for( iRok = datum1.y+1; iRok < datum2.y; iRok++){
			int dnuOdSoboty = weekDayZellerStyle(iRok, 12 , 26);
			switch (dnuOdSoboty){
				case 0:	pocetSvatku += 9;
					break;
				case 1: pocetSvatku += 6;
					break;
				case 2: pocetSvatku += 6;
					break;
				case 3: pocetSvatku += 9;
					break;
				case 4: pocetSvatku += 9;
					break;
				case 5: pocetSvatku += 8;				
					break;
				case 6: pocetSvatku += 8;
					break;
			}	
		}
	return pocetSvatku;
	printf("Vsech svatku o vsedni dny: %d\n", pocetSvatku);
	}
}




int CntWeekdays(TDATE datum1, TDATE datum2){
	int dat1 = 365*datum1.y+datum1.y/4-datum1.y/100+datum1.y/400-datum1.y/4000+ 
		   (datum1.m*306+5)/10+(datum1.d-1);
	int dat2 = 365*datum2.y+datum2.y/4-datum2.y/100+datum2.y/400-datum2.y/4000+ 
		   (datum2.m*306+5)/10+(datum2.d-1);

	int vsednichDnu = ( (dat2-dat1+1)/7)*5;
	int dnuNavic = (dat2-dat1 +1)%7 ;



	printf("dnu navic je: %d\n", dnuNavic);
	/*reimplementovat vsedhnich dnu a dnu navic*/
	printf("zeler rika: %d\n",  weekDayZellerStyle(datum1.y, datum1.m, datum1.d) );


	switch(  weekDayZellerStyle(datum1.y, datum1.m, datum1.d)  ){
	case 0: /*sobota*/
		if (dnuNavic > 2) /*tzn Po, Ut, St, Ct*/
			vsednichDnu += dnuNavic - 1;
		break;
	case 1: /*nedele*/
		if(dnuNavic > 1) /*tzn Po, Ut, St, Ct, Pa*/
			vsednichDnu += dnuNavic -1;
		break;
	case 2: /*pondeli*/
		if(dnuNavic < 6) /*tzn Po, Ut, St, Ct, Pa*/
			vsednichDnu += dnuNavic;
		break;
	case 3: /*utery*/
		printf("zaciname v utery\n");
		if(dnuNavic < 5) /*tzn Ut, St, Ct, Pa*/
			vsednichDnu += dnuNavic;
		break;
	case 4: /*streda*/
		if(dnuNavic < 4) /* St, Ct, Pa*/
			vsednichDnu += dnuNavic;
		if(dnuNavic == 4 || dnuNavic == 5) /*So, Ne*/
			vsednichDnu += 3;
		if(dnuNavic == 6) /* Po*/
			vsednichDnu += 4;
		break;
	case 5: /*ctvrtek*/printf("ctvertek\n");
		if (dnuNavic < 3) /*tzn Ct, Pa*/{
			vsednichDnu += dnuNavic;
			printf("dnu navic%d\n", dnuNavic);
		}
		if(dnuNavic == 3 || dnuNavic == 4){ /*So, Ne*/
			vsednichDnu += 2;
				printf("dnu navic%d\n", dnuNavic);
}
		if (dnuNavic > 4) /*Po, Ut*/
			vsednichDnu += dnuNavic - 2;
		break;

	case 6: /*patek*/
		if (dnuNavic <=3 ) /* Pa, So, Ne*/
			vsednichDnu += 1;
		if (dnuNavic > 3) /* Po, Ut, St*/
			vsednichDnu += dnuNavic - 2;
		break;

	}
	printf("Vsech vsednich dnu: %d\n", vsednichDnu);
	return vsednichDnu;
}





int IsWorkDayMinimal ( int y, int m, int d ) {
	short denVTydnu;
	TDATE datum;
	datum.y = y;
	datum.m = m;
	datum.d = d;
	datum.l = IsLeapYear(y); /*uzitece pro vic veci */
	

	if( IsHolliday(datum)) {/*nevola nic dalsiho*/
		return 0;
	}	

	denVTydnu = weekDayZellerStyle(y, m, d);
	if (denVTydnu == 0 || denVTydnu == 1){
		return 0;
	}




	printf("%d:%d:%d pracovni den\n", y, m, d);
	if(denVTydnu == 6){
		printf("\n");
	}

	return 1; 
}



int StupidCoutWorkdays(TDATE datum1, TDATE datum2){
	int year[12][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ,  
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} 
	};

	int y = datum1.y, m,r, d, mZac = datum1.m - 1, dZac =  datum1.d - 1, poprve = 1, pracovnichDnu = 0;

	for( ;y <= datum2.y ; y++){


		if( IsLeapYear(y) ){ r = 1; }
		else {r = 0; }
		
		if(poprve){ poprve = 0;} 
		else {mZac = 0; dZac = 0 ;}

	
		for(m = mZac ; m < 12; m++){ 
				for (d = dZac; d < year[r][m] ; d++ ){
					pracovnichDnu += IsWorkDayMinimal(y, m+1, d+1);

					if( y == datum2.y && m+1 == datum2.m && d+1 == datum2.d ){
						return pracovnichDnu; }
				}
			}
		}
		

return pracovnichDnu;
}


int CountWorkDays ( int y1, int m1, int d1, int y2, int m2, int d2, int * cnt ) {
	TDATE datum1;
	TDATE datum2; 

	datum1.y = y1;
	datum1.m = m1;
	datum1.d = d1;
	datum1.l = IsLeapYear(datum1.y);
	
	datum2.y = y2;
	datum2.m = m2;
	datum2.d = d2;
	datum2.l = IsLeapYear(datum2.y);
	
	if(! IsValidRange(datum1, datum2) ){
		return 0;
	}
	   
	
	/*datum1.dty = DaysThisYear(datum1);
	datum2.dty = DaysThisYear(datum2);

	
	*cnt = CntWeekdays(datum1, datum2) - CntHollidays(datum1, datum2); */
	
	*cnt = StupidCoutWorkdays(datum1, datum2);

	printf("dnu finalne: %d\n", *cnt);

	return 1;


		


}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
 int cnt;

	IsWorkDay ( 4000, 3, 1 );


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



/**/
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

 /**/
  return 0;
}
#endif /* __PROGTEST__ */
