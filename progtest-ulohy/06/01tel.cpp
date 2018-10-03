#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef struct{
/* store contact informations - number, name and T9 encoded name */
	char *number[21];
	char *sName;
	char *t9Name;
}TITEM;


typedef struct{
/* wrapper for array of TITEMS */
	TITEM *pContacts;
	int size;
	int used;
}TPHONEBOOK;




int isPrefix(char * prefix, char * string){
/* returns +1 / -1 for  possitive/negative match and 0 if strings are same */
	size_t prefLen = strlen(prefix);
	size_t strLen = strlen(string);

	if( prefLen >= strLen ){
			if( ! strcmp(prefix, string) )
				return 0;
			else
				return -1;
	}
	else
		if ( ! strncmp(prefix, string, prefLen) ) 
			return 1;
		return -1;
}


void toT9(char * name){
/* encode given string to T9 ; WARNING: procedure overwrite original string - use with cation */
	*char c = name;

	for( ; *c ; ++c){		
		if(*c == ' ' ){
			*c = '1';
			continue;
		}
		else
			*c = tolower(*c);

		if( *c == 'a' || *c == 'b' || *c == 'c')
			*c = '2';
		else if( *c == 'd' || *c == 'e' || *c == 'f')
			*c = '3';
		else if( *c == 'g' || *c == 'h' || *c == 'i')
			*c = '4';
		else if( *c == 'j' || *c == 'k' || *c == 'l')
			*c = '5';
		else if ( *c == 'm' || *c == 'n' || *c == 'o')
			*c = '6';
		else if  ( *c == 'p' || *c == 'q' || *c == 'r' || *c == 's')
			*c = '7';
		else if ( *c == 't' || *c == 'u' || *c == 'v')
			*c = '8';
		else if  ( *c == 'w' || *c == 'x' || *c == 'y' || *c == 'z')
			*c = '9';
	}
}


	/*-----------------------------------------*/
	/*-------------- ADD CONTACT --------------*/
	/*-----------------------------------------*/

void addContact(TPHONEBOOK *phoneBook, char *number, char *name){
/* in case, that phone book doesn't yet contain given number + name, it will be addad as new contact */ 
/* returns 1/0 on success/failiture and prints status on stdout */
	int i;

	/* check if phoneBook doesn't contain given number + name */
	for(i=0 ; i < phoneBook->used ; i++){
		if( ( !isPrefix(number, phoneBook->pContacts[i]->number) ) && ( ! isPrefix(name , phoneBook->pContacts[i]->name)  ) ){
			printf("Kontakt jiz existuje.\n");
			return 0;
		}
	}

	/* enlarge phonebook if needed */
	if(phoneBook->used == phoneBook->size){ 
		/* ADD FUNCTION ENLARGE PHONE BOOK */
		phoneBook->pContacts = realloc(phoneBook->pContacts, phoneBook->size*2 * sizeof(TITEM) );
		phoneBook->size *= 2;
	}
	
	/* insert phone number */
	strcpy(phoneBook->pContacts[phoneBook->used]->number, number);

	/* insert name*/
	phoneBook->pContacts[phoneBook->used]->name = malloc(  (strlen(name)+1) * sizeof(char) );
	strcpy(phoneBook->pContacts[phoneBook->used]->name, name);

	/* insert T9 encoded name */
	phoneBook->pContacts[phoneBook->used]->t9Name = malloc(  (strlen(name)+1) * sizeof(char) );
	toT9(*name); 
	strcpy(phoneBook->pContacts[phoneBook->used]->t9Name, name);

	printf("OK\n");	

return 1;
}


	/*-----------------------------------------*/
	/*------------- FIND CONTACT --------------*/
	/*-----------------------------------------*/

void findContact(TPHONEBOOK *phoneBook, char *line, int findOption){
	TITEM results[10];
	int printResults = 1;
	int cnt = 0;
	
	if(findOption == 2){
		/*findByName*/
		for(i=0 ; i<phoneBook->used ; i++ ){
			if( isPrefix(line, phoneBook->pContacts[i]->t9Name) != -1 ){
				if(cnt=>10){
					cnt++;
					printResults = 0;
				}
			}	else
					results[cnt++] = phoneBook->pContacts[i]; /* mam to dobre ? I so much dont know */
		}
	}

	else if(findOption == 3){
		/*findByNumber*/
		for(i=0 ; i<phoneBook->used ; i++ ){
			if( isPrefix(line, phoneBook->pContacts[i]->number) != -1 ){
				if(cnt=>10){
					cnt++;
					printResults = 0;
				}
			}	else
					results[cnt++] = phoneBook->pContacts[i]; /* mam to dobre ? I so much dont know */
		}
		
	}


	else(findOption == 1){
		/*findByBoth*/
		for(i=0 ; i<phoneBook->used ; i++ ){
			if( isPrefix(line, phoneBook->pContacts[i]->t9Name) != -1 ||  isPrefix(line, phoneBook->pContacts[i]->number) != -1 ){
				if(cnt=>10){
					cnt++;
					printResults = 0;
				}
			}	else
					results[cnt++] = phoneBook->pContacts[i]; /* mam to dobre ? I so much dont know */
		}

	}

	if(cnt<=10 ){
		for(i=0; i<cnt; i++)
			printf("%d %s\n", results[i].number, results[i].name)
	}
	printf("Celkem: %d", cnt);
}


	 /* -------------------- PARSE LINE + CHECK VALID STRING ----------------------------*/

	/* ------------------- some sort of parsing MAYHEM. &TLDR -------------------------- */

int checkFindPattern(char *line);
int checkAddPattern(char *line);

int parseLine(TPHONEBOOK *phoneBook, char *line){
	size_t lineLen = strlen(line);
	int res;

	if( line[0] == '+' && lineLen >= 6 && line[1] == ' ' && line[lineLen-2] != ' ' ){
		line[lineLen-1] = '\0';
		
		addContact(line+2, phoneBook);
	}

	if( line[0] == '?' && lineLen >=4 && line[1] == ' ' && line[lineLen-2] != ' '){	
		line[lineLen-1] = '\0'; 
		if ( ! ( res = checkFindPattern(line+2) ) )
			return 0;
		findContact(line+2, phoneBook, res /* 1-both, 2-just_by_number, 3-just_by_name */);
	}
}

int checkAddPattern(char *line){
	/*rv = -1 error*/
	char *c;
	int rv, mezera = 0;	
	int lineLen = strLen(line);
	
	for(c=line; c< line+lineLen ; c++){
		if(mezera == 0 ){
			if( ! isdigit(*c) ){
				if(*c == ' ' && c-line >= 1 && c+1 < line+lineLen ){
					mezera = 1;
					to = c-line; /*delka telefonniho cisla*/
					strfrom = (c-line) + 1; /*pozice stringu --- POZOR ABYCH NEPRETEKL POLE --- TAKTO CHYBNE !!! */
					continue;
				}
				else
					return -1;
			}
		}
		
		if(mezera == 1){
			if(! isalpha(*c) ){
				if(*c != ' ')
					return -1;
				if(strfrom == c-line || (c-line) + 1  == lineLen )
					return -1;
			}

		}

	}

}

int checkFindPattern(char *line){
	/*rv 0 = error ; 1 = find name+number ; 2 = find name ; 3 = find number */
	char *c;
	int rv = 1;
	int lineLen = strLen(line);

	if(*line == '1' || *line[lineLen-1] == '1')
		rv = 2;
		 
	for(c=line ; c < line + lineLen ; c++ ){
		if ( ! isdigit(*c) )
			return 0;
		if( c == '0')
			rv = 2;
	}

	if(rv == 2 && lineLen > 20)
		return 0;

	if(lineLen > 20)
		rv = 3;

	return rv;
}



	/* ----------------- MAIN SUPPORTIVE FUNCTIONS ----------------*/

char *getLine(void);
void initPhonebook(TPHONEBOOK *phoneBook);
void initItem(TITEM *item);
void freeMemory(TPHONEBOOK  *phoneBook);
void printRes(int returnCode);


	/* ----------------- MAIN ----------------*/
int main(void){
	int i;
	char *line;
	int lineSize = 5;
	TPHONEBOOK phoneBook;

	char *name = NULL;
	char *findPattern = NULL;
	char phoneNumber[21];
/*	initPhoneBook(&phoneBook);*/
	while(1){
			if ( ! (rv = parseLine(&name, &findPattern, &phoneNumber)) )
				printRes(0);
			else{
				if(rv == 1){
					printf("add to phonebook\n");
					free(name);
					name = NULL;
				}
				else if(rv == 2){
					printf("find in phonebook\n");
					free(findPattern);
					findPattern = NULL;
				}
				else
					break;
			}
					
		/*

		if ( (line = getLine()) == NULL)
			break;	
		
		if(line[0] == '+'){
			parseAdd(line);
						
		}

		else if(line[0] == '?'){
			parseFind(line);
		}

		else
			printRes(0);

		free(line);*/

	}

/*	freeMemory(&phoneBook); */
return 0;
}


	/*-------------- SUPPORTIVE FUNCTIONS -----------------*/

int parseLine(char **name, char **findPattern, char *phoneNumber){
/* ubercool line parser */
/* some parsing mayhem involved. better to not read */
/* DISCLAIMER: &TLDR ! */
/* u still here? */
/* ok. i give up.. */

/*	       return values             */
/* val.		 -1   / 0   / 1   /  2   */ 
/* mean.	 EOF / err / add / find  */
/* pointers points to strings/NULLs based on return option */
	int rv;
	char c;
	int size = 5;
	int used = 0;

	if ( (c = fgetc(stdin)) == EOF )
		return -1;

	if (c == '+'){
	/* parse ADD pattern */
		if( fgetc(stdin) != ' ')
			return 0;
	
		for(i=0, i<22; i++){
		/* scan number part */
			c = fgetc(stdin);

			if ( ! isdigit(c) ){
				if( c == ' ' && i>0 )
					break;
				else
					return 0;
			}
			phoneNumber[i] = c;
		}

		if(i>21) /* too long number */
			return 0;
				
		/* must be letter */
		c = fgetc(stdin);
		if(c < 65 || c > 122 ||  (c > 90 && c < 97 ) )
			return 0;	
		
		*name = malloc(size*sizeof(char));
		*name[used++]=c;

		while(1){
		/* scan name part */
			if( ! isalpha(c) && c != ' '){
				if(c == '\n' && *name[used-1] != ' ')
					break;
				else{
					free(*name);
					*name = NULL;
					return 0;
				}	
			}

			if( size == used ){
				size *= 2;
				*name = realloc( *name, size * sizeof(char) );
			}
			*name[used] = c;
			++used;
		}
	return 1;
	}

	else if(c == '?'){
	/* parse FIND pattern */

		if( fgetc(stdin) != ' ')
			return 0;	
			
		/* must be number */
		c = fgetc(stdin);
		if( !isdigit(c) )
			return 0;	
		
		*findPattern = malloc(size*sizeof(char));
		*findPattern[used++]=c;

		while(1){
		/* scan find pattern part */
			if( ! isdigit(c) ){
				if(c == '\n')
					break;
				else{
					free(*findPattern);
					*findPattern = NULL;
					return 0;
				}	
			}

			if( size == used ){
				size *= 2;
				*findPattern = realloc( *findPattern, size * sizeof(char) );
			}
			*findPattern[used] = c;
			++used;
		}
	return 2;
	}
	
	else
		return 0;
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

void printRes(int returnCode){
/*print success/failiture task result on stdout */
	char ok[] = "OK.";
	char err[] = "Nespravny vstup.";

	printf("%s\n", returnCode?ok:err);
}

