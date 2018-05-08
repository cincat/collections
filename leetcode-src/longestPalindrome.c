#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define min(a, b) (a < b ? a : b)
//#define N 1050

//void pldrm(char *s , char *e, char *arr) {
//	int len = e - s + 1;
//	if(len <= strlen(arr)) return;
//	//printf("%s\n", s);
//	//printf("%d\n", len);
//
//	char *ps = s, *pe = e;
//	while(ps <= pe) {
//		if(*ps != *pe) break;
//		ps++; pe--;
//	}
//
//	if(ps > pe) {
//		memcpy(arr, s, len);
//	}
//}

//char *longestPalindrome(char *s) {
//	//int n = strlen(s);
//	int n = s.size();
//	int dp[n][n];
//	memset(dp, 0, n*n);
//	//char *arr = (char*)calloc(n + n, sizeof(char));
//	string arr;
//
//	for(int i = n - 1; i >=0; i--) {
//		for(int j = i; j < n; j++) {
//			dp[i][j] = s[i] == s[j] && (j - i < 3 || dp[i+1][j-1]);
//			if(dp[i][j] && j - i + 1 > arr.size()/*strlen(arr)*/) arr = s.substr(i, j - i + 1); //memcpy(arr, s + i, j - i + 1);
//		}
//	}
//	return arr;
//}

char *longestPalindrome(char *s) {
	int n = strlen(s), mx = 0;
	char *arr = (char*)calloc(1005, sizeof(char));

	for(int i = 0; i < n; i++) {
		int j = 0, k = 0;
		for(; i + j < n && i - j >=0 && s[i + j] == s[i - j]; j++);
		for(; i + k + 1 < n && i - k >=0 && s[i - k] == s[i + 1 + k]; k++);
		int x = 2*(j-1) + 1, y = 2*(k-1) + 2;
		if(x > mx) {
			mx = x;
			memcpy(arr, s + i - j + 1, x);
		}	

		if(y > mx) {
			mx = y;
			memcpy(arr, s + i - k + 1, y);
		}
	}
	return arr;
}

//char *longestPalindrome(char *s) {
//	char *arr = (char*)calloc(N, sizeof(char)), *px;
//
//	for(px = s; *px != '\0'; px++) {
//		char *pe = s + strlen(s) - 1;	
//		for(; pe >= px; pe--) {
//			if(*pe != *px) continue;
//			pldrm(px, pe, arr);
//		}
//	}	
//	return arr;
//}

//char* longestPalindrome(char *s) {
//	char *arr = (char*)calloc(N, sizeof(char));
//	char ss[2*N] = {'\0'};
//	int p[N*2];
//	for(int i = 0; i <= strlen(s); i++) {
//		ss[2*i] = '#';
//		if(i != strlen(s)) ss[2*i + 1] = s[i];
//	}
//
//	int mx = 0, id = 0, mxp = 0, idp = 0;
//	for(int i = 1; ss[i] != '\0'; i++) {
//		p[i] = mx > i ? min(p[2*id - i], mx -i) : 1;
//		while(ss[i + p[i]] == ss[i - p[i]]) p[i]++;
//		if(i + p[i] > mx) {
//			mx = i + p[i];
//			id = i;
//		}
//		if(p[i] > mxp) {
//			mxp = p[i] - 1;
//			idp = i;
//		}
//	}
//	int j = 0;
//	for(int i = idp - mxp; i <= idp + mxp; i += 1) {
//		if(ss[i] != '#') {
//			arr[j++] = ss[i];
//		}
//	}
//	return arr;
//}

int main(int argc, char *argv[]) {
	FILE * f = fopen("test.txt", "r");
	char *str;
	fscanf(f, "%s", str);
	char *p = longestPalindrome(str);
	//printf("%s\n", p);
	//printf("%d\n", strlen(p));
	//char s[] = "This is a simple string";
	//char *pch;
	//pch = strstr(s, "simple");
	//strncpy(pch, "sample", 6);
	//puts(s);
	//int two_dim[][5] = {
	//	{00, 01, 02}, 
	//	{10, 11}, 
	//	{20, 21, 22, 23}
	//};
	//printf("%d\n", two_dim[0][4]);
	system("ls -al");
	return 0;
}
