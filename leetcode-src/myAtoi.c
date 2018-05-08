#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

int myAtoi(char *str) {
	long rslt = 0;
	int minus = 1;
	char *p = str;
	while(*p == ' ') p++;
	
	if(*p == '-') {
		minus = -1; p++;
	}
	else if(*p == '+') {
		minus = 1; p++;
	}

	for(; *p != 0; p++){
		if(!isdigit(*p)) break;
		rslt = rslt * 10 + (*p - '0');
		if(minus * rslt > INT_MAX)
			return INT_MAX;
		if(minus * rslt < INT_MIN)
			return INT_MIN;
	}
	return minus * rslt;
}

int main() {
	printf("%d\n", myAtoi("1"));
	//printf("%d\n", INT_MAX);
	return 0;
}
