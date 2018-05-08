#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _DEBUG 1

char *convert(char *s, int numRows) {
	int n = strlen(s);
	if(n == 0) return "";
	if(numRows == 1) return s;
	char zigzag[numRows][n];
	for(int i = 0; i < numRows; i++) {
		memset(zigzag + i, 0, n);
	}
	
	int nt = 0, ot = -1;
	for(int i = 0; i < n; i++) {
		zigzag[nt][i] = s[i];

		if(nt == numRows - 1) {
			ot = nt; nt--;
		}
		else if(nt == 0) {
			ot = nt; nt++;
		}
		else if(nt > ot) {
			ot = nt; nt++;
		}
		else if(nt < ot) {
			ot = nt; nt--;
		}
	}
	
	char *t = (char *)calloc(n + 1, sizeof(char));
	char *p = t;
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < n; j++) {
			if(zigzag[i][j] != '\0') {
				*(p++) = zigzag[i][j];
			}
		}
	}
	return t;
}

int main() {
	printf("%s\n", convert("ab", 1));
	return 0;
}
