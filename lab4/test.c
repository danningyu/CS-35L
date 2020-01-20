#include <stdio.h>
#include <limits.h>

int main(){
	int ch = 129;
	signed char c = ch;
	printf("%d, %d, %d, %d\n", ch, c, CHAR_MAX, UCHAR_MAX);
}