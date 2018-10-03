#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

typedef struct {
   int    y;
   int    m;
   int    d;
   short  l;
} TDATE;

short IsLeapYear(int y){
	short leapYear = 0;
	if(y%4 == 0)
		leapYear = 1;
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
short IsHolliday(TDATE datum){
	if(datum.m == 1 && datum.d == 1){ return 1; }
	if(datum.m == 5 && datum.d == 1){ return 1; }
	if(datum.m == 5 && datum.d == 8){ return 1; }
	if(datum.m == 7 && datum.d == 5){ return 1; }
	if(datum.m == 7 && datum.d == 6){ return 1; }
	if(datum.m == 9 && datum.d == 28){ return 1; }
	if(datum.m == 10 && datum.d == 28){ return 1; }
	if(datum.m == 11 && datum.d == 17){ return 1; }
	if(datum.m == 12 && datum.d == 24){ return 1; }
	if(datum.m == 12 && datum.d == 25){ return 1; }
	if(datum.m == 12 && datum.d == 26){ return 1; }
	return 0;
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




short weekDayZellerStyle(y, m, d){
	return (  (d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7   );
}

 /* ----------------------- IS WORK DAY ---------------------------------------------------------*/

int IsWorkDay ( int y, int m, int d ) {
	short denVTydnu;
	TDATE datum;

	datum.y = y;
	datum.m = m;
	datum.d = d;
	datum.l = IsLeapYear(y); /*uzitece pro vic veci */
	
	if(! IsValidDate(datum)){/*nevola nic dalsiho*/
		return 0;
	}
	if( IsHolliday(datum)){/*nevola nic dalsiho*/
		return 0;
	}

	denVTydnu = weekDayZellerStyle(y, m, d);
	if (denVTydnu == 0 || denVTydnu == 6){
		return 0;
}	
	return 1; 
}
/* ---------------------- COUNT WORK DAYS ---------------------------------------------------------*/

int IsWorkDayMinimal ( int y, int m, int d ) {
	short denVTydnu;
	TDATE datum;
	datum.y = y;
	datum.m = m;
	datum.d = d;
	datum.l = IsLeapYear(y);
	if( IsHolliday(datum))
		return 0;	
	denVTydnu = (  (d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7  );
	if (denVTydnu == 0 || denVTydnu == 6){
		return 0;
	}else {return 1;}

}

int StupidCoutWorkdays(TDATE datum1, TDATE datum2){
	int year[12][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} ,  
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} 
	};
	int y = datum1.y, m,r, d, mZac = datum1.m - 1, dZac =  datum1.d - 1, poprve = 1, pracovnichDnu = 0;

	for( ;y <= datum2.y ; y++){
		r=IsLeapYear(y)?1:0;
		
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
	
	if(! IsValidRange(datum1, datum2) )
		return 0;
	
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
