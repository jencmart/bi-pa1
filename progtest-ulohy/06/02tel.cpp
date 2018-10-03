#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct{
/* store contact informations - number, name and T9 encoded name */
	char number[21];
	char *name;
	char *t9Name;
}TITEM;


typedef struct{
/* tripple array pointer wrapper pointing to TITEMS */
	TITEM **pContNumSort;
	TITEM **pContT9Sort;
	TITEM **pContNameSort;
	int size;
	int used;
}TPHONEBOOK;

	/*------------------------ INTERFACE FUNCTIONS ----------------------- */

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
	/*-------------- ADD CONTACT --------------*/
	/*-----------------------------------------*/

void addToPhoneBook(TPHONEBOOK *phoneBook, char *phoneNumber,char *name, char*t9Name){
/* in case, that phone book doesn't yet contain given number + name, it will be addad as new contact */ 
/* result prints on stdout */
/* brute force way */
	int len = strlen(name) + 1;
	int i = 0;

		/* FIRST OF ALL CHECK IF CONTACT IS NOT ALLREADY IN PHONEBOOK */	
		for(i=0; i < phoneBook->used ; i++){
			if ( ! isPrefix(phoneNumber, phoneBook->pContNumSort[i]->number) && ! isPrefix(name, phoneBook->pContNumSort[i]->name)  ){
				printf("Kontakt jiz existuje.\n");
				return;
			}
		}
		/* NEXT, CHECK IF WE DO HAVE ENOUG SPACE IN OUR PHONEBOOK. IF NOT, SOME SPACE :-) */
		if(phoneBook->used == phoneBook->size){	
			phoneBook->size *= 2;		
			/*reallocni pointery na pointery na struktury */
			phoneBook->pContNumSort = (TITEM**) realloc(phoneBook->pContNumSort, phoneBook->size*sizeof(TITEM*));
			phoneBook->pContT9Sort = (TITEM**) realloc(phoneBook->pContT9Sort, phoneBook->size*sizeof(TITEM*));
			phoneBook->pContNameSort = (TITEM**) realloc(phoneBook->pContNameSort, phoneBook->size*sizeof(TITEM*));			
			/* mallocni nove itemy v poli */
			for(i=phoneBook->used; i<phoneBook->size; i++){
				phoneBook->pContNumSort[i] = (TITEM*)malloc(phoneBook->size*sizeof(TITEM));
				phoneBook->pContT9Sort[i] = phoneBook->pContNumSort[i];
				phoneBook->pContNameSort[i] = phoneBook->pContNumSort[i];
			}	
		}
		
		/* FINALLY ADD CONTACT ! */
		/*mallocni si misto na string jmeno a t9jmeno */
		phoneBook->pContNumSort[phoneBook->used]->name = (char*)malloc(  len * sizeof(char)); /* some shit is happening here */
		phoneBook->pContNumSort[phoneBook->used]->t9Name = (char*)malloc( len * sizeof(char));

		/*a nakopiruj to tam */
		strcpy(	phoneBook->pContNumSort[phoneBook->used]->name, name );
		strcpy(	phoneBook->pContNumSort[phoneBook->used]->t9Name, t9Name );
		strcpy(	phoneBook->pContNumSort[phoneBook->used]->number, phoneNumber ); /* CAUSING SOME SHIT */
		/*a zvets pouziti...*/
		phoneBook->used += 1;

		/* znovu serad pole */
		/*TO JE DEBILNI PRCE KDY UZ NAJDU NEJPODOBNEJSI PREFIX TAK NEMUSIM ZNOVU RADIT WTF... */
		printf("OK\n");
}


	/*-----------------------------------------*/
	/*------------- FIND CONTACT --------------*/
	/*-----------------------------------------*/

void findInPhoneBook(TPHONEBOOK *phoneBook, char * findPattern){
/* find in phone book brute force way */
	TITEM results[10];
	int printResults = 1;
	int cnt = 0;
	int i;
/* PARSE LINE DONT WORK WITH WRONG PATTERNS LIKE. 111111111111111111111111111111111111111111111111111111111 ETC.. OR 5000000000000000000000000000000000000000000000000000005 ETC.. */
/*POKUD PRVNI/POSLEDNI == 1 NEBO OBSAHUJE 0 NESMI BYT FIND PATTERN DELSI 20ti znaku ;  */
		
		for(i=0; i < phoneBook->used ; i++){
			if(1 == isPrefix(findPattern, phoneBook->pContNumSort[i]->number)   ) {
				if(cnt < 10){
					results[cnt].name = (char*)malloc( strlen( phoneBook->pContNumSort[i]->name) + 1 );

					strcpy( results[cnt].name,  phoneBook->pContNumSort[i]->name); 
					strcpy( results[cnt].number,  phoneBook->pContNumSort[i]->number); 
				}
				cnt++;					
			}

			else if(1 == isPrefix(findPattern, phoneBook->pContNumSort[i]->t9Name) ){
				if(cnt < 10){
					results[cnt].name = (char*)malloc( strlen( phoneBook->pContNumSort[i]->name) + 1 );

					strcpy( results[cnt].name,  phoneBook->pContNumSort[i]->name); 
					strcpy( results[cnt].number,  phoneBook->pContNumSort[i]->number); 
				}
				cnt++;						
			}
		}	

		if(cnt < 10){
			for(i=0; i < cnt; i++)	{
				printf("%s %s\n", results[i].number,  results[i].name);
				free(results[i].name);
			}
		}

		printf("Celkem: %d\n", cnt);
}
	



	/* ----------------- SUPP. FUNCTIONS HEADERS ----------------*/

void initPhoneBook(TPHONEBOOK *phoneBook);
void initItem(TITEM *item);
void freePhoneBook(TPHONEBOOK  *phoneBook);

int parseLine(char **name, char **t9Name, char **findPattern, char *phoneNumber);
char charToT9(char c);
void printInputRes(int returnCode);

	/* ----------------- MAIN ----------------*/
int main(void){
/* calling lineParser until it return EOF and based on return value calls add / find interface */
	TPHONEBOOK phoneBook;
	int rv;
	char *name = NULL;
	char *t9Name = NULL;
	char *findPattern = NULL;
	char phoneNumber[21];

	initPhoneBook(&phoneBook);

	while(1){
/* infinite loop calling parseLine. if it returns EOF eg. 0 loop ends, memory is freed and program ends */
		if ( ! (rv = parseLine(&name, &t9Name, &findPattern, phoneNumber)) )
			printInputRes(0);
		else{
			if(rv == 1){
				addToPhoneBook( &phoneBook, phoneNumber, name, t9Name);
				free(name);
				free(t9Name);
				name = NULL;
				t9Name = NULL;
			}
			else if(rv == 2){
				findInPhoneBook( &phoneBook, findPattern);
				free(findPattern);
				findPattern = NULL;
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
	phoneBook->pContT9Sort = (TITEM**) malloc(phoneBook->size*sizeof(TITEM*));
	phoneBook->pContNameSort = (TITEM**) malloc(phoneBook->size*sizeof(TITEM*));

	for(i=0; i<phoneBook->size; i++){
		phoneBook->pContNumSort[i] = (TITEM*)malloc(phoneBook->size*sizeof(TITEM));
		phoneBook->pContT9Sort[i] = phoneBook->pContNumSort[i];
		phoneBook->pContNameSort[i] = phoneBook->pContNumSort[i];
	}
}

void freePhoneBook(TPHONEBOOK *phoneBook){
/* free all allocated memory -> make heap happy -> make progtest happy -> make +30% points out of it -> make me happy -> make my mother happy by seeing me happy -> make better world */
	int i;

	/* free pointers on char inside used TITEM structs */
	for(i=0 ; i < phoneBook->used ; i++){
		free ( (phoneBook->pContNumSort)[i]->name );
		free ( (phoneBook->pContNumSort)[i]->t9Name );
	}

	/* free pointers to structures */
	for(i=0; i<phoneBook->size; i++){
		free( phoneBook->pContNumSort[i] );
		phoneBook->pContNumSort[i] = NULL;
		phoneBook->pContT9Sort[i] = NULL;
		phoneBook->pContT9Sort[i] = NULL;	
	}

	/* free arrays of pointers on pointers on structs */
	free(phoneBook->pContNumSort);
	free (phoneBook->pContT9Sort);
	free(phoneBook->pContNameSort);

}

int parseLine(char **name, char **t9Name, char **findPattern, char *phoneNumber){
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
		*t9Name = (char*)malloc(size*sizeof(char));
		*((*name)+used) = c;
		*((*t9Name)+used++) = charToT9(c);
		while(1){
		/* scan rest of the name */
			c = fgetc(stdin);
			if( ! isalpha(c) && c != ' '){
				if(c == '\n' && *((*name)+used-1) != ' '){
					if( size == used ){ /* inser null byte */
						++size;
						*name = (char*)realloc( *name, size * sizeof(char) );
						*t9Name = (char*)realloc( *t9Name, size * sizeof(char));
					}
					*((*name)+used) = '\0';
					*((*t9Name)+used++) = '\0';
					break;
				}
				else{
					if(c != '\n')
						while( fgetc(stdin) != '\n' ){} /* flush line */
					free(*name);
					free(*t9Name);
					*name = NULL;
					*t9Name = NULL;
					return 0;
				}	
			}
	
			if( size == used ){
				size *= 2;
				*name = (char*)realloc( *name, size * sizeof(char) );
				*t9Name = (char*)realloc( *t9Name, size * sizeof(char));
			}
			*((*name)+used) = c;
			*((*t9Name)+used++) = charToT9(c);
		}
	return 1;
	}

	else if(c == '?'){
	/* parse FIND pattern */
		/* scan space */
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
					*((*findPattern)+used++) = '\0';
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

