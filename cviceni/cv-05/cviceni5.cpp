#include <stdio.h>



void vykresliRadek(int radek, int vyska){
	int i,j, pocMezer, pocHvezd;

	pocMezer=vyska-radek;
	pocHvezd=(2*radek)-1;

	/*vypis mezery*/
	for(i=0; i<pocMezer; i++){
		printf(" ");
	}
	
	for(j=0; j<pocHvezd; j++){
		printf("*");
	}
	
	printf("\n");
}


int main (int arcg, char** argv) {
	int vyska, radek;	

	printf("Zadej vysku trojuhlenika:\n");
	scanf("%d", &vyska);
	
	for(radek=1; radek<=vyska; radek++) {
		vykresliRadek(radek, vyska);		
	}
return 0;

}
