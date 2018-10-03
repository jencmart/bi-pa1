#include <stdio.h>
#include <string.h>
#include <math.h>

int scanNumbers(int *numbers, int *cnt);
double computeFinalResult(double *pRes1, double *pRes2, double *pRes3, int *op1, int *op2, char *printComb, int lastOperand, int lastNumberAdded);
void computePartialResult(double *pRes1, double *pRes2, double *pRes3, int *op1, int *op2, char *printComb, int lastOperand, int lastNumberAdded);
int solveRec(int *digits, int size, int query, char *printComb, int numberMatches, double pRes1, double pRes2, double pRes3, int op1, int op2, int lastOperator);

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
		printf("Celkem: %d\n", solveRec(digits, size, query, printComb, 0, 0, 0, 0, -1, -1, -1));
	}	
return 0;
}

int solveRec(int *digits, int size, int query, char *printComb, int numberMatches, double pRes1, double pRes2, double pRes3, int op1, int op2, int lastOperator)
{
	int i, len = strlen(printComb);
	if (size == 1)
	{	
		double result; 
		double absRozdil;

		result = computeFinalResult(&pRes1, &pRes2, &pRes3, &op1, &op2, printComb, lastOperator, *digits);
		if(result == query){
			numberMatches++;
			printf("%d = %s%d\n",query, printComb, *digits);
			return numberMatches;
		}
		absRozdil = fabs(result - query);
		if (( result == 0 || query == 0) && absRozdil < 10e-10){
			numberMatches++;
			printf("%d = %s%d\n",query, printComb, *digits);
			return numberMatches;
		}
		if ( absRozdil/(fabs(result) + fabs(query)) < 10e-10 ){
		    numberMatches++;
			printf("%d = %s%d\n",query, printComb, *digits);
			return numberMatches;
		} 
		return numberMatches;
	}

	computePartialResult(&pRes1, &pRes2, &pRes3, &op1, &op2,printComb, lastOperator, *digits);
	for(i=0; i<5; i++){		
		if(i==0){
			printComb[len+1] = '\0';
			printComb[len++] = '0' + *digits;
		}
		else if (i == 1){
			printComb[len+1] = '\0';
			printComb[len] = '+';
		}
		else if (i == 2){
			printComb[len+1] = '\0';
			printComb[len] = '-';
		}
		else if (i == 3){
			printComb[len+1] = '\0';
			printComb[len] = '*';
		}
		else{
			printComb[len+1] = '\0';
			printComb[len] = '/';
		}
		numberMatches = solveRec(digits+1, size-1, query, printComb, numberMatches, pRes1, pRes2, pRes3, op1, op2, i);
		printComb[len]= '\0';
	}

return numberMatches;
}

void computePartialResult(double *pRes1, double *pRes2, double *pRes3, int *op1, int *op2, char *printComb, int lastOperand, int lastNumberAdded)
{	
	if (strlen(printComb) == 0){
		*pRes1 = lastNumberAdded;
		*op1 = -1;
		*op2 = -1;
		return;
	}

	else if (*op1 == -1){ 
		if (lastOperand == 0){
			*pRes1 = ((*pRes1)*10)+lastNumberAdded;
			return;
		}
		else{
			*op1 = lastOperand;
			*pRes2 = lastNumberAdded;
			return;
		}
	}
	else if (*op2 == -1){
		if (lastOperand == 1 || lastOperand == 2){
			if(*op1 == 1)
				*pRes1 =  (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				*pRes1 =  (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				*pRes1 = (*pRes1)*(*pRes2);
			else					
				*pRes1 =  (*pRes1)/(*pRes2);
			*op1 = lastOperand;
			*pRes2 = lastNumberAdded;	
			return;
		}
		else if (lastOperand == 3 || lastOperand == 4){
			if(*op1 == 1 || *op1 == 2){
				*op2 = lastOperand;
				*pRes3  = lastNumberAdded;
				return;
			}
			else{
				if(*op1 == 1)
					*pRes1 =  (*pRes1)+(*pRes2);
				else if (*op1 == 2)
					*pRes1 =  (*pRes1)-(*pRes2);
				else if (*op1 == 3)
					*pRes1 = (*pRes1)*(*pRes2);
				else					
					*pRes1 =  (*pRes1)/(*pRes2);
				*op1 = lastOperand;
				*pRes2 = lastNumberAdded;
				return;
			}
		}
		else{
			*pRes2 = (*pRes2)*10+lastNumberAdded;
			return;
		}
	}
	else{
		if( lastOperand == 1 || lastOperand == 2){
			if(*op2 == 1)
				*pRes2 =  (*pRes2)+(*pRes3);
			else if (*op2 == 2)
				*pRes2 =  (*pRes2)-(*pRes3);
			else if (*op2 == 3)
				*pRes2 = (*pRes2)*(*pRes3);
			else					
				*pRes2 =  (*pRes2)/(*pRes3);
			if(*op1 == 1)
				*pRes1 =  (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				*pRes1 =  (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				*pRes1 = (*pRes1)*(*pRes2);
			else					
				*pRes1 =  (*pRes1)/(*pRes2);
			*pRes2 = lastNumberAdded;
			*op1 = lastOperand;
			*op2 = -1;
			return;
		}
		else if( lastOperand == 3 || lastOperand == 4){
			if(*op2 == 1)
				*pRes2 =  (*pRes2)+(*pRes3);
			else if (*op2 == 2)
				*pRes2 =  (*pRes2)-(*pRes3);
			else if (*op2 == 3)
				*pRes2 = (*pRes2)*(*pRes3);
			else					
				*pRes2 =  (*pRes2)/(*pRes3);
	
			*pRes3 = lastNumberAdded;
			*op2 = lastOperand;
			return;
		}
		else{
			*pRes3 = (*pRes3)*10+lastNumberAdded;
			return;
		}
	}
}

double computeFinalResult(double *pRes1, double *pRes2, double *pRes3, int *op1, int *op2, char *printComb, int lastOperand, int lastNumberAdded)
{
	if (strlen(printComb) == 0){
		*pRes1 = lastNumberAdded;
		*op1 = -1;
		*op2 = -1;
	}

	else if (*op1 == -1){ 
		if (lastOperand == 0){
			*pRes1 = ((*pRes1)*10)+lastNumberAdded;
		}
		else{
			*op1 = lastOperand;
			*pRes2 = lastNumberAdded;
		}
	}
	else if (*op2 == -1){
		if (lastOperand == 1 || lastOperand == 2){
			if(*op1 == 1)
				*pRes1 =  (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				*pRes1 =  (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				*pRes1 = (*pRes1)*(*pRes2);
			else					
				*pRes1 =  (*pRes1)/(*pRes2);
			*op1 = lastOperand;
			*pRes2 = lastNumberAdded;	
		}
		else if (lastOperand == 3 || lastOperand == 4){
			if(*op1 == 1 || *op1 == 2){
				*op2 = lastOperand;
				*pRes3  = lastNumberAdded;
			}
			else{
				if(*op1 == 1)
					*pRes1 =  (*pRes1)+(*pRes2);
				else if (*op1 == 2)
					*pRes1 =  (*pRes1)-(*pRes2);
				else if (*op1 == 3)
					*pRes1 = (*pRes1)*(*pRes2);
				else					
					*pRes1 =  (*pRes1)/(*pRes2);
				*op1 = lastOperand;
				*pRes2 = lastNumberAdded;
			}
		}
		else{
			*pRes2 = (*pRes2)*10+lastNumberAdded;
		}
	}
	else{
		if( lastOperand == 1 || lastOperand == 2){
			if(*op2 == 1)
				*pRes2 =  (*pRes2)+(*pRes3);
			else if (*op2 == 2)
				*pRes2 =  (*pRes2)-(*pRes3);
			else if (*op2 == 3)
				*pRes2 = (*pRes2)*(*pRes3);
			else					
				*pRes2 =  (*pRes2)/(*pRes3);
			if(*op1 == 1)
				*pRes1 =  (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				*pRes1 =  (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				*pRes1 = (*pRes1)*(*pRes2);
			else					
				*pRes1 =  (*pRes1)/(*pRes2);
			*pRes2 = lastNumberAdded;
			*op1 = lastOperand;
			*op2 = -1;
		}
		else if( lastOperand == 3 || lastOperand == 4){
			if(*op2 == 1)
				*pRes2 =  (*pRes2)+(*pRes3);
			else if (*op2 == 2)
				*pRes2 =  (*pRes2)-(*pRes3);
			else if (*op2 == 3)
				*pRes2 = (*pRes2)*(*pRes3);
			else					
				*pRes2 =  (*pRes2)/(*pRes3);
	
			*pRes3 = lastNumberAdded;
			*op2 = lastOperand;
		}
		else{
			*pRes3 = (*pRes3)*10+lastNumberAdded;

		}
	}	
	
	
	
	if (*op1 == -1)
		  return *pRes1;
	else if (*op2 == -1){
		if(*op1 == 1)
			return (*pRes1)+(*pRes2);
		else if (*op1 == 2)
			return (*pRes1)-(*pRes2);
		else if (*op1 == 3)
			return (*pRes1)*(*pRes2);
		else					
			return (*pRes1)/(*pRes2);
	}	
	else{
		if(*op2 == 1){
			*pRes2 =  (*pRes2)+(*pRes3);
			if(*op1 == 1)
				return (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				return (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				return (*pRes1)*(*pRes2);
			else					
				return (*pRes1)/(*pRes2);
		}

		else if (*op2 == 2){
			*pRes2 =  (*pRes2)-(*pRes3);
			if(*op1 == 1)
				return (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				return (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				return (*pRes1)*(*pRes2);
			else					
				return (*pRes1)/(*pRes2);
		}
		else if (*op2 == 3){
			*pRes2 = (*pRes2)*(*pRes3);
			if(*op1 == 1)
				return (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				return (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				return (*pRes1)*(*pRes2);
			else					
				return (*pRes1)/(*pRes2);
		}
		else{					
			*pRes2 =  (*pRes2)/(*pRes3);
			if(*op1 == 1)
				return (*pRes1)+(*pRes2);
			else if (*op1 == 2)
				return (*pRes1)-(*pRes2);
			else if (*op1 == 3)
				return (*pRes1)*(*pRes2);
			else					
				return (*pRes1)/(*pRes2);
		}
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

