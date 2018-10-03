#include <stdio.h>
unsigned safeSizeof (unsigned int ** x)
{
	if(!x) return 0;
	return sizeof(x);
}
int main(){
	unsigned int * foo[199];
	printf(" %u %u ",(unsigned) sizeof(foo),safeSizeof(foo));
	return 0;


}
