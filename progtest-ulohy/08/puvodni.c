#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


typedef struct TResult{
   struct TResult *m_Next;
   int m_ID;
   char *m_Name;
 }TRESULT;

typedef struct TPerson{
	struct TPerson *m_Next;
	int m_ID;
	char *m_Name;
	struct TPerson *m_Parent1;
	struct TPerson *m_Parent2;
}TPERSON;

TPERSON *head;
TPERSON *tail;

void Done(void);
int Register(int ID, const char *name, int ID1, int ID2);
TRESULT *Ancestors(int ID);
TRESULT *CommonAncestors(int ID1, int ID2);
void FreeResult(TRESULT *res);


int main ( int argc, char * argv [] )
 {
   char name[100];
   TRESULT * l;
   TPERSON *iterator;
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
   
   
   assert ( Register ( 1, "Francois", 0, 0 ) == 0 );
   

	
	iterator = head->m_Next;
	printf("Vypisuji databazi:\n");
	while(iterator->m_Next)
	{
		printf("ID: %d Jmeno: %s R1: %s R2: %s\n", iterator->m_ID, iterator->m_Name, iterator->m_Parent1, iterator->m_Parent2);
		iterator = iterator->m_Next;
	}
	Done ();
	return 0;

/*   l = Ancestors ( 11 ); */
   /*
    * ID=1, name="John"
    * ID=2, name="Jane"
    * ID=3, name="Caroline"
    * ID=4, name="Peter"
    * ID=6, name="Martin"
    * ID=8, name="Sandra"
    */
/*   FreeResult ( l ); */

/*   assert ( Ancestors ( 3 ) == NULL );
   assert ( Ancestors ( 13 ) == NULL ); */
/*   l = CommonAncestors ( 11, 12 ); */
   /*
    * ID=1, name="John"
    * ID=2, name="Jane"
    * ID=3, name="Caroline"
    * ID=4, name="Peter"
    * ID=8, name="Sandra"
    */
/*   FreeResult ( l ); */
/*   l = CommonAncestors ( 10, 9 ); */
   /*
    * ID=1, name="John"
    */
/*   FreeResult ( l ); */
/*   assert ( CommonAncestors ( 7, 6 ) == NULL );
   l = CommonAncestors ( 7, 10 ); */
   /*
    * ID=4, name="Peter"
    */
/*  FreeResult ( l );
   assert ( Register ( 13, "Quido", 12, 11 ) == 1 );
   l = Ancestors ( 13 ); */
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
  /* FreeResult ( l );
   l = CommonAncestors ( 9, 12 ); */
   /*
    * ID=1, name="John"
    * ID=2, name="Jane"
    */
/*   FreeResult ( l ); */
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
	
	while (head->m_Next)
	{
		tmp = head->m_Next;
		free(head->m_Name);
		free(head);
		head = tmp;
	}
}

void createFirstNode(int ID, const char *name)
{
	head = (TPERSON*) malloc(sizeof(TPERSON));
	head->m_ID = ID;
	head->m_Name = (char*)malloc(strlen(name)+1);
	strcpy(head->m_Name, name);
	head->m_Parent1 = NULL;
	head->m_Parent2 = NULL;
	head->m_Next = NULL;
	tail = head;
}




TPERSON* findPredacessor(int ID)
{
	TPERSON *previous;
	TPERSON *current;

	current = previous = head;
	while(current->m_ID < ID){	
		previous = current;
		current = current->m_Next;
	}

return previous;
}

void addToHead(int ID, const char *name, TPERSON *parent1, TPERSON *parent2)
{
	TPERSON *tmp = (TPERSON*)malloc(sizeof(TPERSON));

	tmp->m_Next = head;
	head = tmp;
	head->m_ID = ID;
	head->m_Name = (char*)malloc(strlen(name)+1);
	strcpy(head->m_Name, name);
	head->m_Parent1 = parent1;
	head->m_Parent2 = parent2;
}




void addToTail(int ID, const char *name, TPERSON *parent1, TPERSON *parent2)
{
	TPERSON *tmp = (TPERSON*)malloc(sizeof(TPERSON));

	tail->m_Next = tmp;
	tail = tmp;
	tail->m_Next = NULL;
	tail->m_ID = ID;
	tail->m_Name = (char*)malloc(strlen(name)+1);
	strcpy(head->m_Name, name);
	tail->m_Parent1 = parent1;
	tail->m_Parent2 = parent2;
}



void addToMiddle(int ID, const char *name, TPERSON *parent1, TPERSON *parent2)
{
	TPERSON *tmp = (TPERSON*)malloc(sizeof(TPERSON));
	TPERSON *predacessor = findPredacessor(ID);

	tmp->m_Next = predacessor->m_Next;
	predacessor->m_Next = tmp;
	tmp->m_ID = ID;
	tmp->m_Name = (char*)malloc(strlen(name)+1);
	strcpy(tmp->m_Name, name);
	tmp->m_Parent1 = parent1;
	tmp->m_Parent2 = parent2;
}

void addNode(int ID, const char *name, TPERSON *parent1, TPERSON *parent2)
{
	if(head = NULL)
		createFirstNode(ID, name);
	else if(head->m_ID > ID)
		addToHead(ID, name, parent1, parent2);
	else if (tail->m_ID < ID)
		addToTail(ID, name, parent1, parent2);
	else
		addToMiddle(ID, name, parent1, parent2);
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
int Register(int ID, const char *name, int ID1, int ID2)
{
	TPERSON *parent1 = NULL;
	TPERSON *parent2 = NULL;

	if(!ID || !name)
		return 0;

	else if (ID1 == ID2 && ID1 != 0 )
		return 0;

	else if ( findById(ID) )
		return 0;

	else if (ID1 && !(parent1 = findById(ID1)))
		return 0;

	else if (ID2 && !(parent2 = findById(ID2)))
		return 0;

	else
		addNode(ID, name, parent1, parent2);

return 1;
}		

/*
void addToResult(TPERSON *person, TRESULT*resultHead, TRESULT *resultTail)
{
	TRESULT *tmp;

	if(!resultHead){
		resultHead = ;
	}
	else *add to tail
}

void findAncRecursively(TPERSON *person, TRESULT *resultHead, TRESULT *resultTail )
{
	if( !person->m_Parent1 && !person->m_Parent2) 
			return;
	else
	{
		if(person->m_Parent1){
			 addToResult(person->m_Parent1, resultHead, resultTail);
			 findAncRecursively(person->m_Parent1, TRESULT *resultHead, TRESULT *resultTail);
		}

		if(person->m_Parent2){
				addToResult(person->m_Parent2, resultHead, resultTail);
				findAncRecursively(person->m_Parent2, TRESULT *resultHead, TRESULT *resultTail);
		}
		return;
	}
}
*/
TRESULT* Ancestors(int ID)
{
	TRESULT *head = NULL;
	TPERSON *person = findById(ID);

	if (person) /*only if person with this ID exist, try to find some ancestros... */
		/*findAncRecursively(person, head, NULL);*/

return head;
}

void FreeResult(TRESULT* ancestor)
{


}

