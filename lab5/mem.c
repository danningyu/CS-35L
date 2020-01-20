#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("\nSTART PROGRAM\n");
	int* intPtr = (int*)(malloc(5*sizeof(int)));

	printf("END MALLOC\n");
	intPtr = (int*)(realloc(intPtr, 100000*sizeof(int)));
	printf("\nEND REALLOC\n");
	free(intPtr);
	printf("\nEND FREE\n");
	int* intPtr2 = (int*)(malloc(100000000*sizeof(int)));
	free(intPtr2);
	return 0;
}