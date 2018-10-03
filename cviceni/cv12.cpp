#include <stdio.h>
#include <time.h>

clock_t t1, t2;

	t1=clock(); /*pocita v poctu strojovych cyklu*/
	fceNaSpocitani();
	t2=clock();
	cas = (double)(t2-t1)/CLOCKS_PER_SEC;	/*cas v sekunkdach */
