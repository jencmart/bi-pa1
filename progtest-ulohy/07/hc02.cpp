#include <stdio.h>
#include <string.h>
#include <math.h>

int scanNumbers(int *numbers, int *cnt);
double makeOperation(double a, char operand, double b);
int compare(double a, int b);
double computeFinalResult(double pRes1, double pRes2, double pRes3, char znam1, char znam2);
void computePartialResult(double *pRes1, double *pRes2, double *pRes3, char *op1, char *op2, char * printComb);
int solveRec(int *digits, int size, int query, char *printComb, int numberMatches, double pRes1, double pRes2, double pRes3, char op1, char op2);
void addOperand(char *string, int operand);
int solveString(char *string);

int main(void)
{
	char printComb[100];
    int digits[50], size = 0, query, rv;

	printf("Cislice:\n");
	if (!scanNumbers(digits, &size))
	{
		printf("Nespravny vstup.\n");
		return 1;
	}

	printf("Dotazy:\n");
	while ( EOF != (rv=scanf("%d", &query)))
	{
		if(!rv)
		{
			printf("Nespravny vstup.\n");
			return 1;
		}	
		printComb[0] = '\0';
		printf("Celkem: %d\n", solveRec(digits, size, query, printComb, 0, 0, 0, 0, '?', '?'));
	}
	
return 0;
}

int solveRec(int *digits, int size, int query, char *printComb, int numberMatches, double pRes1, double pRes2, double pRes3, char op1, char op2)
{
	int i, len = strlen(printComb);

	if (size == 1)
	{	
		double result;
		printComb[len+1] = '\0';
		printComb[len++] = '0' + *digits;
		computePartialResult(&pRes1, &pRes2, &pRes3, &op1, &op2, printComb);
		result = computeFinalResult(pRes1, pRes2, pRes3, op1, op2);
		if ( compare( result, query ) )
		{
		    numberMatches++;
			printf("%d = %s\n",query, printComb);
		}
		return numberMatches;		
	}

	printComb[len+1] = '\0';
	printComb[len++] = '0' + *digits;
	computePartialResult(&pRes1, &pRes2, &pRes3, &op1, &op2, printComb);
	for(i=0; i<5; i++)
	{
		addOperand(printComb, i);
		numberMatches = solveRec(digits+1, size-1, query, printComb, numberMatches, pRes1, pRes2, pRes3, op1, op2);
		printComb[len]= '\0'; /* reset string for another branch */
	}

return numberMatches;
}

void computePartialResult(double *pRes1, double *pRes2, double *pRes3, char *op1, char *op2, char * printComb)
{
	double lastNumberAdded = printComb[strlen(printComb)-1] - '0';
	char lastOperand;
	if (strlen(printComb) == 1){
		*pRes1 = lastNumberAdded;
		*op1 = '?';
		*op2 = '?';
		return;
	}
	lastOperand = printComb[strlen(printComb)-2];
	 if (*op1 == '?'){ 
		if (lastOperand >= '0' && lastOperand <= '9')
			*pRes1 = ((*pRes1)*10)+lastNumberAdded;
		else{
			*op1 = lastOperand;
			*pRes2 = lastNumberAdded;
		}
	}
	else if (*op2 == '?'){
		if (lastOperand == '+' || lastOperand == '-'){
			*pRes1 = makeOperation(*pRes1, *op1, *pRes2);
			*op1 = lastOperand;
			*pRes2 = lastNumberAdded;	
		}
		else if (lastOperand == '*' || lastOperand == '/'){
			if(*op1 == '+' || *op1 == '-'){
				*op2 = lastOperand;
				*pRes3  = lastNumberAdded;
			}
			else{
				*pRes1 = makeOperation(*pRes1, *op1, *pRes2);
				*op1 = lastOperand;
				*pRes2 = lastNumberAdded;
			}
		}
		else
			*pRes2 = (*pRes2)*10+lastNumberAdded;
	}
	else{
		if( lastOperand == '+' || lastOperand == '-'){
			*pRes2 = makeOperation(*pRes2, *op2, *pRes3);
			*pRes1 = makeOperation(*pRes1, *op1, *pRes2);
			*pRes2 = lastNumberAdded;
			*op1 = lastOperand;
			*op2 = '?';
		}
		else if( lastOperand == '*' || lastOperand == '/'){
			*pRes2 = makeOperation(*pRes2, *op2, *pRes3);
			*pRes3 = lastNumberAdded;
			*op2 = lastOperand;
		}
		else
			*pRes3 = (*pRes3)*10+lastNumberAdded;
	}
}

double makeOperation(double a, char operand, double b)
{
	if(operand == '+')
		return a+b;
	else if (operand == '-')
		return a-b;
	else if (operand == '*')
		return a*b;
	else					
		return a/b; /* neskodilo by ochranit deleni nullou */
}

double computeFinalResult(double pRes1, double pRes2, double pRes3, char znam1, char znam2)
{
  if (znam1 == '?')
		  return pRes1;
  if (znam2 == '?')
		  return makeOperation(pRes1, znam1, pRes2);
  return makeOperation(pRes1, znam1, makeOperation(pRes2, znam2, pRes3));

}

int compare(double a, int b)
{ /* shitty */
	double rozdil = a-b;
	double absRozdil = fabs(rozdil);

	if(a == b)
		return 1;
	if( a== 0 || b == 0 || absRozdil < 10e-10 )
		return absRozdil < 10e-10;

return absRozdil/(fabs(a) + fabs(b)) < 10e-10;
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
	while ( scanf("%d %c", &dig, &c) == 2 && (c == ',' || c == ']') && dig < 10 && dig >= 0  && *cnt < 50)
	{
		digits[(*cnt)++] = dig;
		if (c == ']')
			return 1;
	}

return 0;
}

