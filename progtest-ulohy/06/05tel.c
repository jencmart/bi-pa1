#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct{
	char number[21];
	char *name;
}TITEM;

typedef struct{
	TITEM **pContNumSort;
	int size;
	int used;
}TPHONEBOOK;


void initPhoneBook(TPHONEBOOK *phoneBook);
void freePhoneBook(TPHONEBOOK  *phoneBook);
int parseLine(char **name, char **findPattern, char *phoneNumber);
int parseAddPattern(char **name, char *phoneNumber);
int parseFindPattern(char **findPattern);
int isPrefix(char * prefix, char * string);
int isPrefixT9(char * prefix, char * string);
char charToT9(char c);
void flushLine(char c);
void printInputRes(int returnCode);
void addToPhoneBook(TPHONEBOOK *phoneBook, char *phoneNumber,char *name);
void findInPhoneBook(TPHONEBOOK *phoneBook, char * findPattern);

int main(void){
	TPHONEBOOK phoneBook;
	int rv;
	char *name = NULL;
	char *findPattern = NULL;
	char phoneNumber[21];

	initPhoneBook(&phoneBook);

	while (1){

		if (! (rv = parseLine(&name, &findPattern, phoneNumber)))
			printInputRes(0);

		else if (rv == 1){
			addToPhoneBook(&phoneBook, phoneNumber, name);
			free(name);
			name = NULL;
		}

		else if(rv == 2){
			findInPhoneBook( &phoneBook, findPattern);
			free(findPattern);
			findPattern = NULL;
		} 

		else
			break;
	}

	freePhoneBook(&phoneBook); 

return 0;
}


	/*-----------------------------------------*/
	/*-------------- ADD CONTACT --------------*/
	/*-----------------------------------------*/

void addToPhoneBook(TPHONEBOOK *phoneBook, char *phoneNumber,char *name)
{ 
	int i = 0;

	for(i=0; i < phoneBook->used; i++){
		if (! strcmp(phoneNumber, phoneBook->pContNumSort[i]->number) && ! strcmp(name, phoneBook->pContNumSort[i]->name)){
			printf("Kontakt jiz existuje.\n");
			return;
		}
	}

	if(phoneBook->used == phoneBook->size){	
		phoneBook->size *= 2;		
		phoneBook->pContNumSort = (TITEM**) realloc(phoneBook->pContNumSort, phoneBook->size*sizeof(TITEM*));
	}
		
	/* add contact */
	phoneBook->pContNumSort[phoneBook->used] = (TITEM*)malloc(phoneBook->size*sizeof(TITEM));
	phoneBook->pContNumSort[phoneBook->used]->name = (char*)malloc(strlen(name) + 1);
	strcpy(phoneBook->pContNumSort[phoneBook->used]->name, name);
	strcpy(phoneBook->pContNumSort[phoneBook->used]->number, "99199");
	phoneBook->used = phoneBook->used + 1;
	printf("OK\n");
}

	/*-----------------------------------------*/
	/*------------- FIND CONTACT --------------*/
	/*-----------------------------------------*/

void findInPhoneBook(TPHONEBOOK *phoneBook, char * findPattern)
{
	TITEM results[10];
	int cnt = 0;
	int i;

	for(i=0; i < phoneBook->used ; i++){
		if(isPrefix(findPattern, phoneBook->pContNumSort[i]->number)){
			if(cnt < 10){
				results[cnt].name = (char*)malloc(strlen(phoneBook->pContNumSort[i]->name) + 1);
				strcpy( results[cnt].name,  phoneBook->pContNumSort[i]->name); 
				strcpy( results[cnt].number,  phoneBook->pContNumSort[i]->number); 
			}
			cnt++;					
		}

		else if(isPrefixT9(findPattern, phoneBook->pContNumSort[i]->name) ){
			if(cnt < 10){
				results[cnt].name = (char*)malloc(strlen(phoneBook->pContNumSort[i]->name) + 1);
				strcpy( results[cnt].name,  phoneBook->pContNumSort[i]->name); 
				strcpy( results[cnt].number,  phoneBook->pContNumSort[i]->number); 
			}
			cnt++;						
		}
	}	

	if(cnt <= 10){
		for(i=0; i < cnt; i++){
			printf("%s %s\n", results[i].number,  results[i].name);
			free(results[i].name);
		}
	}
	else{
		for(i=0; i < 10; i++)
			free(results[i].name);
	}

	printf("Celkem: %d\n", cnt);
}


void printInputRes(int returnCode)
{
	char ok[] = "OK.";
	char err[] = "Nespravny vstup.";

	printf("%s\n", returnCode?ok:err);
}


void initPhoneBook(TPHONEBOOK *phoneBook){
/*	int i; */
	phoneBook->size = 100;	
	phoneBook->used = 0;
	phoneBook->pContNumSort = (TITEM**) malloc(phoneBook->size*sizeof(TITEM*));
 
/*	for(i=0; i<phoneBook->size; i++){
		phoneBook->pContNumSort[i] = (TITEM*)malloc(phoneBook->size*sizeof(TITEM));
	} */
}

void freePhoneBook(TPHONEBOOK *phoneBook)
{
	int i;

	for(i=0 ; i < phoneBook->used ; i++){
		free ( (phoneBook->pContNumSort)[i]->name );
		free( phoneBook->pContNumSort[i] );
		phoneBook->pContNumSort[i] = NULL;
	}

/*	for(i=0; i<phoneBook->size; i++){
		free( phoneBook->pContNumSort[i] );
		phoneBook->pContNumSort[i] = NULL;
	} */

	free(phoneBook->pContNumSort);
}


int parseLine(char **name, char **findPattern, char *phoneNumber)
{
/*	       return values             
 * val.		 -1   / 0   / 1   /  2    
 * mean.	 EOF / err / add / find  
 */
	char c;

	if ((c = fgetc(stdin)) == EOF)
		return -1;

	if (c == '+')
		return  parseAddPattern(name, phoneNumber);

	if (c == '?')
		return parseFindPattern(findPattern);
	
	flushLine(c);

return 0;
}

int parseAddPattern(char **name, char *phoneNumber)
{
	char c;
	int size = 100;
	int used = 0;
	int i;

	if ((c = fgetc(stdin)) != ' '){
		flushLine(c);
		return 0;
	}

	for(i=0; i<=21; i++){
		if (i == 21){
			flushLine(c);
			return 0;
		}
			
		if (! isdigit((c = fgetc(stdin)))){
			if (c == ' ' && i>0 && i<=20){
				if((c = (fgetc(stdin))) == ' ' && isalpha((c = fgetc(stdin)))) /* last number is followed by space and letter */
				phoneNumber[i] = '\0';
				break;
			}
			flushLine(c);
			return 0;
		}
		phoneNumber[i] = c;
	}
		
	*name = (char*)malloc(size);
	*name[used++] = c;

	while (1){										/* scan name */
		if (! isalpha((c = fgetc(stdin))) && c != ' ' && c != '\n' ){
			flushLine(c);
			free(*name);
			*name = NULL;
			return 0;
		}

		if (size == used){
			size *= 2;
			*name = (char*)realloc(*name, size);
		}
	
		if(c == '\n'){
			if(*((*name)+used-1) == ' '){
				flushLine(c);
				free(*name);
				*name = NULL;
				return 0;
			}
		
			(*name)[used++] = '\0';
			break;
		}
		(*name)[used++] = c;
	}

return 1;
}

int parseFindPattern(char **findPattern)
{	
	char c;
	int size = 100;
	int used = 0;

	if( (c = fgetc(stdin)) != ' '){
		flushLine(c);
		return 0;	
	}
	
	if (! isdigit((c = fgetc(stdin)))){		/* scan first number */
		flushLine(c);
		return 0;
	}

	*findPattern = (char*)malloc(size*sizeof(char));
	(*findPattern)[used++] = c;

	while (1){								/* scan rest of the numbers */
		if (! isdigit((c = fgetc(stdin))) && c != '\n'){
			flushLine(c);
			free(*findPattern);
			*findPattern = NULL;
			return 0;	
		}

		if(size == used){
			size *= 2;
			*findPattern = (char*)realloc(*findPattern, size);
		}
	
		if(c == '\n'){
			(*findPattern)[used] = '\0';
			break;
		}

		(*findPattern)[used++] = c;
	}
	return 2;
}

void flushLine(char c)
{
	if(c != '\n')
		while( fgetc(stdin) != '\n' ){}
}

char charToT9(char c)
{
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
	else if( c == 'w' || c == 'x' || c == 'y' || c == 'z')
		return '9';

return 9;
}

int isPrefixT9(char *prefix, char *string)
{
	char *pp = prefix;
	char *ps = string;

	if(strlen(prefix) > strlen(string))
		return 0;

	for(; *pp; ++pp, ++ps){
		if( charToT9(*ps) != *pp)
			return 0;
	}

return 1;
}
 
int isPrefix(char * prefix, char * string)
{
	int prefLen = strlen(prefix);
	int strLen = strlen(string);

	if(prefLen > strLen)
		return 0;

	if (! strncmp(prefix, string, prefLen))
		return 0;

return 1;
}

