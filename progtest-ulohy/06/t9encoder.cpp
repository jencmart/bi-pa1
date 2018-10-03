#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct{
/* store contact informations - number, name and T9 encoded name */
	char number[21];
	char *name;
}TITEM;


typedef struct{
/* tripple array pointer wrapper pointing to TITEMS */
	TITEM **pContNumSort;
	int size;
	int used;
}TPHONEBOOK;


	/*------------------------ INTERFACE FUNCTIONS ----------------------- */
char charToT9(char c){
/* encode alphabetic character (or space) to T9 and return it */
		if(c == ' ' )
			return '1';
		else
			c = tolower(c);

		if( c == 'a' || c == 'b' || c == 'c')
			return '2';
		else if( c == 'd' || c == 'e' || c == 'f')
			return '3';
		else if( c == 'g' || c == 'h' || c == 'i')
			return '4';
		else if( c == 'j' || c == 'k' || c == 'l')
			return '5';
		else if ( c == 'm' || c == 'n' || c == 'o')
			return '6';
		else if  ( c == 'p' || c == 'q' || c == 'r' || c == 's')
			return '7';
		else if ( c == 't' || c == 'u' || c == 'v')
			return '8';
		else if ( c == 'w' || c == 'x' || c == 'y' || c == 'z')
			return '9';
return 9;
}

int isPrefixT9(char *string){
	char *ps;
	for( ps=string ; *ps ; ++ps ){
		printf("%c", charToT9(*ps));
	}
return 1;
}
 

int isPrefix(char * prefix, char * string){
/* returns +1 / -1 for  possitive/negative match and 0 if strings are same */
	size_t prefLen = strlen(prefix);
	size_t strLen = strlen(string);
	if( prefLen > strLen ){
		return -1;
	}
	else if(prefLen == strLen){
		if( !strcmp(prefix, string) )
				return 0;
		return -1;
	}

	else{
		if ( ! strncmp(prefix, string, prefLen) ){
			return 1;
		}
		return -1;
	}
}

	/*-----------------------------------------*/
	/*------------- FIND CONTACT --------------*/
	/*-----------------------------------------*/

void findInPhoneBook(TPHONEBOOK *phoneBook, char * findPattern){
/* find in phone book brute force way */
	TITEM results[10];
	int cnt = 0;
	int i;


}
	
	/* ----------------- SUPP. FUNCTIONS HEADERS ----------------*/

void initPhoneBook(TPHONEBOOK *phoneBook);
void initItem(TITEM *item);
void freePhoneBook(TPHONEBOOK  *phoneBook);

int parseLine(char **name, char **findPattern, char *phoneNumber);
/* char charToT9(char c); */
void printInputRes(int returnCode);

	/* ----------------- MAIN ----------------*/
int main(void){
/* calling lineParser until it return EOF and based on return value calls add / find interface */
	TPHONEBOOK phoneBook;
	int rv;
	char *name = NULL;
/*	char *t9Name = NULL; */
	char *findPattern = NULL;
	char phoneNumber[21];

	initPhoneBook(&phoneBook);

	while(1){
/* infinite loop calling parseLine. if it returns EOF eg. 0 loop ends, memory is freed and program ends */
		if ( ! (rv = parseLine(&name, &findPattern, phoneNumber)) )
			printInputRes(0);
		else{
			if(rv == 1){
				isPrefixT9(name);
			}
			else
				break;
		}
	}

/* last but not least free all the allocated memory */
	freePhoneBook(&phoneBook); 

return 0;
}
	/*----------------- SUPPORTIVE FUNCTIONS -------------------*/

void initPhoneBook(TPHONEBOOK *phoneBook){
/* inside type TPHONEBOOK struct malloc three array of pointers to pointers to type TITEM 
    next malloc pointers to type TITEM  and all of them point to same structs */
	int i;
	phoneBook->size = 5;	
	phoneBook->used = 0;
	phoneBook->pContNumSort = (TITEM**) malloc(phoneBook->size*sizeof(TITEM*));
	/* phoneBook->pContT9Sort = (TITEM**) malloc(phoneBook->size*sizeof(TITEM*)); */
	/* phoneBook->pContNameSort = (TITEM**) malloc(phoneBook->size*sizeof(TITEM*)); */
 
	for(i=0; i<phoneBook->size; i++){
		phoneBook->pContNumSort[i] = (TITEM*)malloc(phoneBook->size*sizeof(TITEM));
		/* phoneBook->pContT9Sort[i] = phoneBook->pContNumSort[i]; */
		/* phoneBook->pContNameSort[i] = phoneBook->pContNumSort[i]; */
	}
}

void freePhoneBook(TPHONEBOOK *phoneBook){
/* free all allocated memory -> make heap happy -> make progtest happy -> make +30% points out of it -> make me happy -> make my mother happy by seeing me happy -> make better world */
	int i;

	/* free pointers on char inside used TITEM structs */
	for(i=0 ; i < phoneBook->used ; i++){
		free ( (phoneBook->pContNumSort)[i]->name );
		/* free ( (phoneBook->pContNumSort)[i]->t9Name ); */
	}

	/* free pointers to structures */
	for(i=0; i<phoneBook->size; i++){
		free( phoneBook->pContNumSort[i] );
		phoneBook->pContNumSort[i] = NULL;
		/* phoneBook->pContT9Sort[i] = NULL; */
		/* phoneBook->pContT9Sort[i] = NULL; */	
	}

	/* free arrays of pointers on pointers on structs */
	free(phoneBook->pContNumSort);
	/* free (phoneBook->pContT9Sort); */
	/* free(phoneBook->pContNameSort); */
}

int parseLine(char **name, char **findPattern, char *phoneNumber){
/* ubercool line parser */
/* some hardcore parsing mayhem involved. better to not read */
/* DISCLAIMER: &TLDR ! */
/* I've said Too Long Dont Read ! */
/* u still here? */
/* ok. i give up.. but it's on your responsibility */

/*	       return values             */
/* val.		 -1   / 0   / 1   /  2   */ 
/* mean.	 EOF / err / add / find  */
/* pointers points to strings/NULLs based on return option */
	char c;
	int size = 5;
	int used = 0;
	int i, priznak = 0;

	if ( (c = fgetc(stdin)) == EOF )
		return -1;

	if (c == '+'){
	/* parse ADD pattern */
		/* scan space */
		if( (c = fgetc(stdin)) != ' '){
			if(c != '\n')
				while( fgetc(stdin) != '\n' ){} /* flush line */
			return 0;
		}
		for(i=0; i<20; i++){
		/* scan number part */
			c = fgetc(stdin);

			if ( ! isdigit(c) ){
				if( c == ' ' && i>0 ){
					priznak = 1;
					phoneNumber[i] = '\0';
					break;
				}
				else{
					if(c != '\n')
						while( fgetc(stdin) != '\n' ){} /* flush line */
					return 0;
				}
			}
			phoneNumber[i] = c;
		}
		/* optionally scan space */
		if(! priznak){
			if ( (c = fgetc(stdin)) != ' '){
				if(c != '\n')
					while( fgetc(stdin) != '\n' ){} /* flush line */
				return 0;
			}
		else{
			phoneNumber[i] = '\0'; /*TADY BY TO MOHLO KRAVNOUT */
		}

		}		
		/* scan first letter of name */
		c = fgetc(stdin);
		if(c < 65 || c > 122 ||  (c > 90 && c < 97 ) ){
			if(c != '\n')
				while( fgetc(stdin) != '\n' ){} /* flush line */
			return 0;	
		}

		*name = (char*)malloc(size*sizeof(char));
		*name[used++] = c;

		while(1){
		/* scan rest of the name */
			c = fgetc(stdin);
			if( ! isalpha(c) && c != ' '){
				if(c == '\n' && *((*name)+used-1) != ' '){
					if( size == used ){ /* inser null byte */
						++size;
						*name = (char*)realloc( *name, size * sizeof(char) );
					}
					*((*name)+used++) = '\0';
					break;
				}
				else{
					if(c != '\n')
						while( fgetc(stdin) != '\n' ){} /* flush line */
					free(*name);
					*name = NULL;
					return 0;
				}	
			}
	
			if( size == used ){
				size *= 2;
				*name = (char*)realloc( *name, size * sizeof(char) );
			}
			*((*name)+used++) = c;
		}
	return 1;
	}

	else if(c == '?'){
	/* parse FIND pattern */
		/* scan space */
		int canFindName = 1;
		if( (c = fgetc(stdin)) != ' '){
			if(c != '\n')
				while( fgetc(stdin) != '\n' ){} /* flush line */
			return 0;	
		}
		/* scan first number of find pattern */
		c = fgetc(stdin);
		if( !isdigit(c) ){
			if(c != '\n')
				while( fgetc(stdin) != '\n' ){} /* flush line */
			return 0;	
		}
		if(c == '1')
			canFindName = 0;

		*findPattern = (char*)malloc(size*sizeof(char));
		*((*findPattern)+used++)=c;

		while(1){
		/* scan rest of the find pattern */
			c = fgetc(stdin);
			if( ! isdigit(c) ){

				if(c == '\n'){
					if( size == used ){ /* inser null byte */
						++size;
						*findPattern = (char*)realloc( *findPattern, size * sizeof(char) );
					}
					*((*findPattern)+used) = '\0';

					if(  ( !canFindName || *((*findPattern)+used-1) == '1' ) && ( strlen(*findPattern) > 20)  ){
						free(*findPattern);
						*findPattern = NULL;
						return 0;
					}

					break;
				}
				else{
					if(c != '\n')
						while( fgetc(stdin) != '\n' ){} /* flush line */
					free(*findPattern);
					*findPattern = NULL;
					return 0;
				}	
			}

			if(c == '0')
				canFindName = 0;
			if( size == used ){
				size *= 2;
				*findPattern = (char*)realloc( *findPattern, size * sizeof(char) );
			}
			*((*findPattern)+used++) = c;
		}
	return 2;
	}
	
	else{
		if(c != '\n')
			while( fgetc(stdin) != '\n' ){} /* flush line */
		return 0;
	}
}



char *getLine(void){
/* scan one line from stdin ( removing newline char ) */
/* on success returns pointer to scanned line */
/* on EOF / error returns NULL. --well just on EOF. if realloc dont have enough memory it'll shit the program */
	int lastChar=0;
	int size = 5;
	char *line = NULL;
	
	while( 1 ){
		size *= 2;
		line = (char*)realloc(line , size);
		if ( fgets(line + lastChar, size-lastChar, stdin) == NULL ){
			free(line);
			break;	
		}
		lastChar = strlen(line); 
		if(line[lastChar-1] == '\n'){
			/*odmaz newline*/
			return line;
		}
	}
/*EOF / ERROR */	
return NULL;		
}

void printInputRes(int returnCode){
/*print success/failiture task result on stdout */
	char ok[] = "OK.";
	char err[] = "Nespravny vstup.";

	printf("%s\n", returnCode?ok:err);
}

