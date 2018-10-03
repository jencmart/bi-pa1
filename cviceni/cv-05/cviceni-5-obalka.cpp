#include <stdio.h>




int vykresliRadek(int radek, int pocRadek){
	printf("*"); /*prvni hvezda na radku*/


	/*suda obalka*/
	if(pocRadek%2==0){
		int krajniMezery, prostredniMezery, i;


		if(radek <= pocRadek/2){ /*do prvni pulky*/
			krajniMezery = radek-1;
			prostredniMezery= (pocRadek-2)-(radek-1)*2;

			for(i=0; i<krajniMezery; i++){ /* prvni krajni mezery */
				printf(" ");
			}

			printf("*");

			for(i=0; i<prostredniMezery; i++){ /*prostredni mezery*/
				printf(" ");
			}

			printf("*");

			for(i=0; i<krajniMezery; i++){ /* druhe krajni mezery */
				printf(" ");
			}


		}
		else if(radek == (pocRadek/2) + 1){ /* pulka*/
			krajniMezery = radek-2;
			for(i=0; i<krajniMezery; i++){ /* prvni krajni mezery */
				printf(" ");
			}
			printf("**");
			for(i=0; i<krajniMezery; i++){ /* prvni krajni mezery */
				printf(" ");
			}

		}

		else{
			krajniMezery = pocRadek - radek;
			prostredniMezery = (radek-1)*2 - pocRadek;


			for(i=0; i<krajniMezery; i++){ /* prvni krajni mezery */
				printf(" ");
			}

			printf("*");

			for(i=0; i<prostredniMezery; i++){ /*prostredni mezery*/
				printf(" ");
			}

			printf("*");

			for(i=0; i<krajniMezery; i++){ /* druhe krajni mezery */
				printf(" ");
			}


		}


	}







	/*licha obalka*/
	if(pocRadek%2==1){
		int krajniMezery, prostredniMezery, i;


		if(radek < (pocRadek+1)/2){ /*do prvni pulky*/
			krajniMezery = radek-1;
			prostredniMezery= (pocRadek-2)-(radek-1)*2;

			for(i=0; i<krajniMezery; i++){ /* prvni krajni mezery */
				printf(" ");
			}

			printf("*");

			for(i=0; i<prostredniMezery; i++){ /*prostredni mezery*/
				printf(" ");
			}

			printf("*");

			for(i=0; i<krajniMezery; i++){ /* druhe krajni mezery */
				printf(" ");
			}

		}

		else if(radek == ((pocRadek+1)/2)){ /* pulka*/
			krajniMezery = radek-1;
			for(i=0; i<krajniMezery; i++){ /* prvni krajni mezery */
				printf(" ");
			}
			printf("*");
			for(i=0; i<krajniMezery; i++){ /* druhe krajni mezery krajni mezery */
				printf(" ");
			}

		}

		else{
			krajniMezery = pocRadek - radek;
			prostredniMezery = (radek-1)*2 - pocRadek;

			for(i=0; i<krajniMezery; i++){ /* prvni krajni mezery */
				printf(" ");
			}

			printf("*");

			for(i=0; i<prostredniMezery; i++){ /*prostredni mezery*/
				printf(" ");
			}

			printf("*");

			for(i=0; i<krajniMezery; i++){ /* druhe krajni mezery */
				printf(" ");
			}




		}


	}








	printf("*\n"); /* posledni hvezda na radku*/
	

return 0;

}







int main(){
	int radek,pocRadek,vyska, i;


	printf("Zadej velikost obalky: ");
	scanf("%d", &vyska);



	for(i=0; i<vyska; i++){
		printf("*");
	}
	printf("\n");




	pocRadek=vyska-2;


	for(radek=1; radek<=pocRadek; radek++){

	vykresliRadek(radek, pocRadek);
	}





	for(i=0; i<vyska; i++){
		printf("*");
	}
	printf("\n");

return 0;

}

