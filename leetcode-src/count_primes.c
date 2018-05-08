#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int count_primes(int n) {
	char *prime = (char *)calloc(n, sizeof(char));
	int c = 0;

	for(int i = 2; i < n; i++) {
		if(prime[i] == 0) {
			c++;
			for(int j = 2; i * j < n; j++) 
				prime[i*j] = 1;
		}
	}
	return c;
}

bool isUgly(int num) {
	if(num <= 0) return false;
	char *array = calloc(num + 1, sizeof(char));
	array[1] = 1, array[2] = 1, array[3] = 1, array[5] = 1;
	int factor[] = {2, 3, 5};
	int nf = 3;

	for(int i = 0; i < 3; i++) {
		for(int j = 2; factor[i] * j <= num; j++) {
			if(array[j])
				array[factor[i]*j] = 1;
		}
	}
	return array[num] == 1;
}

bool isUglyII(int num) {
	if(num <= 0) return false;
	bool prime = true;
	for(int i = 2; i <= sqrt(num); i++) {
		if(num % i == 0) {
			prime = false;
			if(i!= 2 || i != 3 || i != 5) return false;	
		}
	}
	return prime == true ? false : true;
}

int main() {
	//printf("%d\n", count_primes(10));
	if(isUglyII(1641249143))
		puts("true");
	else
		puts("false");
	return 0;
}
