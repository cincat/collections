#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/*
bool isMatch(char *s, char *p) {
	int m = strlen(s), n = strlen(p);
	bool f[m + 1][n + 1];
	f[0][0] = true;

	for(int i = 1; i <= m ;i++) {
		f[i][0] = false;
	}

	for(int j = 1; j <= n; j++) {
		f[0][j] = (j > 1 && '*' == p[j - 1] && f[0][j - 2]);
	}

	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= n; j++) {
			if(p[j - 1] != '*')
				f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1]
						|| '.' == p[j - 1]);
			else 
				f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] 
						|| '.' == p[j - 2]) && f[i - 1][j];
		}
	}

	return f[m][n];
}

bool isMatch(char *s, char *p) {
	if(strlen(p) == 0)
		return strlen(s) == 0;

	if('*' != p[1])
		return strlen(s) 
			&& (*s == *p || *p == '.') 
			&& isMatch(s + 1, p + 1);
	else
		return (isMatch(s, p + 2) || strlen(s) 
				&& (*s == *p || *p == '.') 
				&& isMatch(s + 1, p)); 
}
*/

bool isMatch(char *s, char *p) {
	char *star = NULL;
	char *ss = s;

	while(*s) {
		if(*p == '?' || *p == *s) {
			s++; p++; continue;
		}

		if(*p == '*') {
			star = p++;
			ss = s;
			continue;
		}
		
		if(star) {
			p = star + 1;
			s = ++ss;
			continue;
		}
		return false;
	}
	while('*' == *p)
		p++;
	return !*p;
}

int main() {
	if(isMatch("aaaa", "***a"))
		puts("match");
	else
		puts("dismatch");
	return 0;
}
