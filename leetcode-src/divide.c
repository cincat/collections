#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int divide(int dividend, int divisor) {
	if(divisor == 0
			|| (dividend == INT_MIN && divisor == -1)) return INT_MAX;
	int neg = (dividend < 0) ^ (divisor < 0) ? -1 : 1;
	int ans = 0;
	long long x = labs(dividend);
	long long y = labs(divisor);
	while (x >= y) {
		long long t = y, m = 1;
		while(x >= (t << 1)) {
			//printf("%d, %d\n", t, m);
			t <<= 1;
			m <<= 1;
		}
		//printf("%d, %d\n", dividend, m);
		x -= t;
		ans += m;
	}
	return neg * ans;
}

int main() {
	printf("%d\n", divide(2147483647, 1));
	return 0;
}
