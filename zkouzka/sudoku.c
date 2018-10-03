#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
	int sudoku[9][9];
	char *radek = NULL;
	size_t buffer = 0;
	int kontrolni[9] = {0};
	int i,j,k,l,mensiNez,iDo;
	int pocCisel;
	char c;


	for(i=0; i<9; i++)
	{
		/* getline */
			printf("getlinuji\n");
			printf("no teda\n");

		getline(&radek, &buffer, stdin);

		printf ("nactl jsem radek\n");

		if(!radek || strlen(radek)<18){
			printf("Nespravny vstup.\n");
			return 0;
		}
		
		/* parse line */
		for(j=0, pocCisel=0; i<strlen(radek); i++){	
			printf("parsuji radek\n");
			c = radek[i];
			if( c == ' ' )
				continue;
			else if ( c == '\n')
					break;
			else if( isdigit(c) ){

				if( c - '0' <= 0 || c-'0' >9 || pocCisel == 9){
					printf("Nespravny vstup.\n");
					return 0;
				}
				sudoku[i][pocCisel++] = c;
			}

			else{
				printf("Nespravny vstup.\n");
				return 0;
			}
		}

	}

	/* zkontroluj radky */
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if ( kontrolni[sudoku[i][j]]  == 1){
					printf("Spatne sudoku.\n");
					return 0;
			}
			kontrolni[sudoku[i][j]]  = 1;
		}
		
		for(j=0; j<9; j++){
			if(!kontrolni[j] == 0){
				printf("Spatne sudoku.\n");
			}
			kontrolni[j] = 0;
		}
	}
	/* zkontroluj sloupecky */
	for(i=0; i<9; i++){
		for(j=0; j<9; j++){
			if ( kontrolni[sudoku[j][i]]  == 1){
					printf("Spatne sudoku.\n");
					return 0;
			}
			kontrolni[sudoku[j][i]]  = 1;
		}
		
		for(j=0; j<9; j++){
			if(!kontrolni[j] == 0){
				printf("Spatne sudoku.\n");
			}
			kontrolni[j] = 0;
		}
	}

	for(l=0; l<3; l++){
		i=3*l;
		iDo = i+3;
    
		for(k=0; k<3; k++){
			j=3*k;
	    	mensiNez = j+3;
			for( ; i<iDo; i++){
				for( ; j< mensiNez; j++){
					if ( kontrolni[sudoku[i][j]]  == 1){
							printf("Spatne sudoku.\n");
							return 0;
					}
					kontrolni[sudoku[i][j]]  = 1;
				}
				
				for(j=0; j<9; j++){
					if(!kontrolni[j] == 0){
						printf("Spatne sudoku.\n");
					}
					kontrolni[j] = 0;
				}
			}
		}
	}
    	
return 0;
}

