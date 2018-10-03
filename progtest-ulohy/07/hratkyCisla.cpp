#include <stdio.h>
#include <string.h>

int scanNumbers(int *numbers, int *cnt);
int solveRec(int *digits, int size, int query, char *printComb, int numberMatches);
void addOperand(char *string, int operand);
int solveString(char *string);

int main(void)
{
	char stringCombination[100];
    int digits[50], size = 0, query, rv;

	printf("Zadej hodnoty:\n");
	if (!scanNumbers(digits, &size))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}

	while ( EOF != (rv=scanf("%d", &query)))
	{
		if(!rv)
		{
			printf("Nespravny vstup.\n");
			return 1;
		}	
		stringCombination[0] = '\0';
		printf("Celkem: %d\n", solveRec(digits, size, query, stringCombination, 0));
	}
	
return 0;
}

int solveString(char *string)
{
	int finalSum  = 0;
	int checkSum1 = 0;
	int checkSum2 = 0;
return finalSum;
}

int solveRec(int *digits, int size, int query, char *printComb, int numberMatches)
{
	int i, len = strlen(printComb);

	if (size == 1)
	{	
		printComb[len+1] = '\0';
		printComb[len++] = '0' + *digits;
		if(solveString(printComb) == 0 /* query */ )
		{
		    numberMatches++;
			printf("%s\n", printComb);
		}
		return numberMatches;		
	}

	printComb[len+1] = '\0';
	printComb[len++] = '0' + *digits;
	for(i=0; i<5; i++)
	{
		addOperand(printComb, i);
		numberMatches = solveRec(digits+1, size-1, query, printComb, numberMatches);
		printComb[len]= '\0'; /* reset string for another branch */
	}

return numberMatches;
}

void addOperand(char *string, int operand)
{
	char operands[] = "+-*/";
	int i;

	if (!operand)
		return;
	for(i=0; i<4; i++)
		if(operand-1 == i )
		{
			string[strlen(string) + 1] = '\0';
			string[strlen(string)] = operands[i];
			return;
		}
}

int scanNumbers(int *digits, int *cnt)
{
	int dig;
	char c;

	if (!scanf(" %c", &c) || c != '[' )
		return 0;
	while (!(scanf("%d %c", &dig, &c) != 2 || (c != ',' && c != ']' && (dig < 10 && dig > -10 ) && *cnt < 50)))
	{
		digits[(*cnt)++] = dig;
		if (c == ']')
			return 1;
	}

return 0;
}

