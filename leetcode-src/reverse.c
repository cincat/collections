#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#include <limits.h>

int reverse(int x) {
	char *t = (char *)calloc(64, sizeof(char));
	char *p = t;
	if(x < 0) {
		*(p++) = '-';
		x = -x;
	}

	while(x != 0) {
		int m = x % 10;
		x = x/10;
		if((p == t || *(p - 1) == '-') && m == 0) 
			continue;
		*(p++) = '0' + m;
	}
	
	long r = atol(t);
	return r > INT_MAX || r < INT_MIN ? 0 : atoi(t);
}

int main() {
	printf("%d\n", reverse(1));
	return 0;
}
