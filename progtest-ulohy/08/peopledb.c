#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct TPerson{
	struct TPerson *m_Next;
	int m_ID;
	char *m_Name;
	struct TPerson *m_Parent1;
	struct TPerson *m_Parent2;
}TPERSON;

typedef struct TResult{
   struct TResult *m_Next;
   int m_ID;
   char *m_Name;
}TRESULT;

TPERSON *head;
TPERSON *tail;

void vypisDatabazi()
{
	TPERSON *iterator = head;
	printf("Vypisuji databazi:\n");
	while(1)
	{
		printf("ID: %d Jmeno: %s ", iterator->m_ID, iterator->m_Name);
		if(iterator->m_Parent1)
				printf("P1: %s ", iterator->m_Parent1->m_Name);
		else
				printf("P1: (null) ");
		if(iterator->m_Parent2)
				printf("P2: %s\n", iterator->m_Parent2->m_Name);
		else
				printf("P2: (null)\n");

		iterator = iterator->m_Next;
		if(!iterator)
				break;
	}
}

void Init(void);
void Done(void);
TPERSON* findById(int ID);
TPERSON* findPredacessor(int ID);
void addNode(int ID, const char *name, TPERSON *parent1, TPERSON *parent2);
int Register(int ID, const char *name, int ID1, int ID2);
void FreeResult(TRESULT *res);

void mergeResults(TRESULT **resHead, TRESULT **toAddHead);
void addResultNode(TPERSON *parentToAdd, TRESULT **resultHead, TRESULT **resultTail);
void findRecursively(TPERSON *person, TRESULT **resultHead, TRESULT **resultTail);
TRESULT *Ancestors(int ID);

TRESULT *CommonAncestors(int ID1, int ID2);

void vypisDatabazi();
void vypisSearch(TRESULT *resultHead)
{
	TRESULT *iterator = resultHead;
	printf("Predkove :\n");
	if(iterator == NULL){
			printf("search Head je na NULL \n");
			return;
	}

	while(1)
	{
		printf("ID: %d Jmeno: %s\n", iterator->m_ID, iterator->m_Name);
		if(iterator->m_Next == NULL)
				break;
		iterator = iterator->m_Next;
	}
}


int main ( int argc, char * argv [] )
{
   char name[100];
   TRESULT * l;
   
   Init ();
   assert ( Register ( 1, "John", 0, 0 ) == 1 );
   strncpy ( name, "Jane", sizeof ( name ) );
   assert ( Register ( 2, name, 0, 0 ) == 1 );
   assert ( Register ( 3, "Caroline", 0, 0 ) == 1 );
   assert ( Register ( 4, "Peter", 0, 0 ) == 1 );
   assert ( Register ( 5, "George", 1, 2 ) == 1 );
   assert ( Register ( 6, "Martin", 1, 2 ) == 1 );
   assert ( Register ( 7, "John", 3, 4 ) == 1 );
   assert ( Register ( 8, "Sandra", 3, 4 ) == 1 );
   assert ( Register ( 9, "Eve", 1, 2 ) == 1 );
   assert ( Register ( 10, "Douglas", 1, 4 ) == 1 );
   strncpy ( name, "Phillipe", sizeof ( name ) );
   assert ( Register ( 11, name, 6, 8 ) == 1 );
   strncpy ( name, "Maria", sizeof ( name ) );
   assert ( Register ( 12, name, 5, 8 ) == 1 ); 

   l = Ancestors ( 11 ); 
   /*
    * ID=1, name="John"
    * ID=2, name="Jane"
    * ID=3, name="Caroline"
    * ID=4, name="Peter"
    * ID=6, name="Martin"
    * ID=8, name="Sandra"
    */
	FreeResult ( l ); 

   assert ( Ancestors ( 3 ) == NULL );
   assert ( Ancestors ( 13 ) == NULL ); 

   l = CommonAncestors ( 11, 12 );

   /*
    * ID=1, name="John"
    * ID=2, name="Jane"
    * ID=3, name="Caroline"
    * ID=4, name="Peter"
    * ID=8, name="Sandra"
    */
   FreeResult ( l );



   l = CommonAncestors ( 10, 9 ); 
   printf("Common ancestors: \n");
    vypisSearch(l); 
   /*
    * ID=1, name="John"
    */
   FreeResult ( l ); 



   assert ( CommonAncestors ( 7, 6 ) == NULL );
   l = CommonAncestors ( 7, 10 ); 
   printf("Common ancestors: \n");
    vypisSearch(l); 
   /*
    * ID=4, name="Peter"
    */
  FreeResult ( l );


   assert ( Register ( 13, "Quido", 12, 11 ) == 1 );
   l = Ancestors ( 13 );  
   /*
    * ID=1, name="John"
    * ID=2, name="Jane"
    * ID=3, name="Caroline"
    * ID=4, name="Peter"
    * ID=5, name="George"
    * ID=6, name="Martin"
    * ID=8, name="Sandra"
    * ID=11, name="Phillipe"
    * ID=12, name="Maria"
    */
   FreeResult ( l );


	printf("testuji\n");

	l = Ancestors ( 9 );
	printf("ID1\n");
	vypisSearch(l); 
	FreeResult ( l );

	l = Ancestors ( 1 );
	printf("ID2\n");
	vypisSearch(l); 
	FreeResult ( l );



   l = CommonAncestors (9 , 1);
     printf("testovaci Common ancestors: \n");
    vypisSearch(l); 
   /*
    * ID=1, name="John"
    * ID=2, name="Jane"
    */
   FreeResult ( l ); 

   assert ( Register ( 1, "Francois", 0, 0 ) == 0 );
   Done ();

   Init ();
   assert ( Register ( 10000, "John", 0, 0 ) == 1 );
   assert ( Register ( 10000, "Peter", 0, 0 ) == 0 );
   assert ( Register ( 20000, "Jane", 10000, 0 ) == 1 );
   assert ( Register ( 30000, "Maria", 10000, 10000 ) == 0 );
   assert ( Register ( 40000, "Joe", 10000, 30000 ) == 0 );
   assert ( Register ( 50000, "Carol", 50000, 20000 ) == 0 );


   Done (); 

   return 0;

}

void Init(void)
{
	head = NULL;
	tail = NULL;
}

void Done(void)
{
	TPERSON *tmp;
	
	if (head == NULL)
		return;
	while (head->m_Next)
	{
		tmp = head->m_Next;
		free(head->m_Name);
		free(head);
		head = tmp;
	}
	free(head->m_Name);
	free(head);
}

int Register(int ID, const char *name, int ID1, int ID2)
{
	TPERSON *parent1 = NULL;
	TPERSON *parent2 = NULL;

	if(!ID || !name)
		return 0;
	if (ID1 == ID2 && ID1 != 0 )
		return 0;
	if ( findById(ID) )
		return 0;
	if (ID1 && !(parent1 = findById(ID1)))
		return 0;
	if (ID2 && !(parent2 = findById(ID2)))
		return 0;

	addNode(ID, name, parent1, parent2);

return 1;
}

void addNode(int ID, const char *name, TPERSON *parent1, TPERSON *parent2)
{
	TPERSON *tmp, *predacessor;

	if(head == NULL){
		head = (TPERSON*) malloc(sizeof(TPERSON));
		head->m_ID = ID;
		head->m_Name = (char*)malloc(strlen(name)+1);
		strcpy(head->m_Name, name);
		head->m_Parent1 = NULL;
		head->m_Parent2 = NULL;
		head->m_Next = NULL;
		tail = head;
		return;
	}
	
	tmp = (TPERSON*)malloc(sizeof(TPERSON));

	if(head->m_ID > ID){
		tmp->m_Next = head;
		head = tmp;
		head->m_ID = ID;
		head->m_Name = (char*)malloc(strlen(name)+1);
		strcpy(head->m_Name, name);
		head->m_Parent1 = parent1;
		head->m_Parent2 = parent2;
	}

	else if (tail->m_ID < ID){
		tail->m_Next = tmp;
		tail = tmp;
		tail->m_Next = NULL;
		tail->m_ID = ID;
		tail->m_Name = (char*)malloc(strlen(name)+1);
		strcpy(tail->m_Name, name);
		tail->m_Parent1 = parent1;
		tail->m_Parent2 = parent2;
	}

	else{
		predacessor = findPredacessor(ID);
		tmp->m_Next = predacessor->m_Next;
		predacessor->m_Next = tmp;
		tmp->m_ID = ID;
		tmp->m_Name = (char*)malloc(strlen(name)+1);
		strcpy(tmp->m_Name, name);
		tmp->m_Parent1 = parent1;
		tmp->m_Parent2 = parent2;
	}
}

TPERSON* findPredacessor(int ID)
{
	TPERSON *previous, *current;

	current = previous = head;
	while(current->m_ID < ID){	
		previous = current;
		current = current->m_Next;
	}

return previous;
}


TPERSON* findById(int ID)
{
	TPERSON *current;

	if (head == NULL || ID < head->m_ID || ID > tail->m_ID) /* SHORTCUT */
		return NULL;

	current = head;

	while(current->m_ID <= ID)
	{
		if(current->m_ID == ID)
			return current;
		if(!current->m_Next)
			break;
		current = current->m_Next;
	}

return NULL;
}



void addResultNode(TPERSON *parentToAdd, TRESULT **resultHead, TRESULT **resultTail)
{
	TRESULT *tmp;

	if(*resultHead == NULL){
		*resultHead = (TRESULT*)malloc(sizeof(TRESULT));
		(*resultHead)->m_Name = (char*)malloc(strlen(parentToAdd->m_Name)+1);
		(*resultHead)->m_ID = parentToAdd->m_ID;
		strcpy((*resultHead)->m_Name, parentToAdd->m_Name);
		(*resultHead)->m_Next = NULL;
		*resultTail = *resultHead;
	}
	else{
		tmp = (TRESULT*)malloc(sizeof(TRESULT));
		(*resultTail)->m_Next = tmp;
		*resultTail = tmp;
		(*resultTail)->m_Next = NULL;
		(*resultTail)->m_ID = parentToAdd->m_ID;
		(*resultTail)->m_Name = (char*)malloc(strlen(parentToAdd->m_Name)+1);	
		strcpy((*resultTail)->m_Name, parentToAdd->m_Name);
	}

return;
}


int isInResults(TRESULT *resultHead, int ID)
{
	TRESULT	*iterator = resultHead;
	
	if (iterator == NULL)
			return 0;

	while(iterator->m_Next)
	{
		if(iterator->m_ID == ID)
				return 1;
		iterator = iterator->m_Next;	
	}

	if(iterator->m_ID == ID)
			return 1;

return 0;
}

void findRecursively(TPERSON *person, TRESULT **resultHead, TRESULT **resultTail )
{
	if( !person->m_Parent1 && !person->m_Parent2){
			return;
	}

	if(person->m_Parent1 && !isInResults(*resultHead, person->m_Parent1->m_ID) ){
			/*zkontroluji zda jeste neni */
		 
		 addResultNode(person->m_Parent1, resultHead, resultTail);
		 findRecursively(person->m_Parent1, resultHead, resultTail);
		 
	}

	if(person->m_Parent2 && !isInResults(*resultHead, person->m_Parent2->m_ID)){
			/*zkontroluj zda jeste neni v listu a pokud ne, pridej a pokracuj jinak vynech vetev...  */
			addResultNode(person->m_Parent2, resultHead, resultTail);
			findRecursively(person->m_Parent2, resultHead, resultTail);
	}

return;
}



TRESULT* Ancestors(int ID)
{
	TPERSON *person = findById(ID); /*person which we'll find ancestors */
	TRESULT *resultHead = NULL;
	TRESULT *resultTail = NULL;
	
	if (person)
		findRecursively( person, &resultHead, &resultTail);

return resultHead;
}

TRESULT* CommonAncestors(int ID1, int ID2)
{
	TPERSON *person1 = findById(ID1);
	TPERSON *person2 = findById(ID2);
	TRESULT *resH1 = NULL;
	TRESULT *resT1 = NULL;
	TRESULT *resH2 = NULL;
	TRESULT *resT2 = NULL;
	
	if (person1 && person2 ){
		findRecursively(person1, &resH1, &resT1); 
		findRecursively(person2, &resH2, &resT2);
	}

	else{		/* at least one person don't exist -> no ancestors */
		FreeResult(resH1);
		FreeResult(resH2);
		return NULL;
	}

	if(! resH1 || !resH2  ){
		FreeResult(resH1);
		FreeResult(resH2);	
			return NULL;
	}

/*	vypisSearch(resH1); */
/*	vypisSearch(resH2); */
	mergeResults(&resH1, &resH2); /*ancestors of ID1 and ancestors of ID2 */
	FreeResult(resH2);

return resH1;
}

void mergeResults(TRESULT **resHead, TRESULT **toAddHead)
{
	TRESULT *iterator = *resHead; /*bude prochazet cleny seznamu, aka finalniho seznamu */
	TRESULT *predacessor = NULL;

	while(iterator->m_Next){
		if(! isInResults(*toAddHead, iterator->m_ID)) /* pokud clen neni v druhem seznamu, odeberem ho i z tohoto */
		{
			/*printf("neni u druheho: %s\n", iterator->m_Name); */
			if(iterator == *resHead) /* FIRST NODE */
			{
				iterator = iterator->m_Next;
				free((*resHead)->m_Name);
				free(*resHead);
				*resHead = iterator;
				continue;
			}
			else{
				predacessor->m_Next = iterator->m_Next;
				free(iterator->m_Name);
				free(iterator);
				iterator = predacessor->m_Next;
				continue;
			}
		}

		if(!iterator->m_Next)
			break;

		predacessor = iterator;
		iterator = iterator->m_Next;
	}

	if (! isInResults(*toAddHead, iterator->m_ID)){ /* LAST NODE */
		/* printf("(posledni) :neni u druheho: %s\n", iterator->m_Name); */
		if(iterator == *resHead){
				free((*resHead)->m_Name);
				free(*resHead);
				*resHead = NULL;
			}
		else{
			predacessor->m_Next = NULL;
			free(iterator->m_Name);
			free(iterator);
			iterator = NULL;
		}
	}
}

void FreeResult(TRESULT *resultHead)
{
	TRESULT *tmp;
	
	if(resultHead == NULL)
			return;

	while (resultHead->m_Next){
		tmp = resultHead->m_Next;
		free(resultHead->m_Name);
		free(resultHead);
		resultHead = tmp;
	}
	
	free(resultHead->m_Name);
	free(resultHead);
	resultHead = NULL;
}

