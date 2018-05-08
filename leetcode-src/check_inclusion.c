#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#define _DEBUG

bool checkInclusion(char* s1, char* s2) {
	if (strlen(s2) < strlen(s1)) return false;
	const int n = 128;
	int *map = calloc(n, sizeof(int));
	for (int i = 0; i < strlen(s1); i++) 
		map[s1[i]] += 1;

#ifdef _DEBUG
	for (int i = 0; i < strlen(s1); i++)
		printf("%c: %d\n", s1[i], map[s1[i]]);
#endif

	for (int i = 0; i <= (strlen(s2) - strlen(s1)); i++) {
		int tmp_map[n];
		for (int k = 0; k < n; k++)
			tmp_map[k] = map[k];

#ifdef _DEBUG
		for (int i = 0; i < strlen(s1); i++) {
			printf("%c: %d\n", s1[i], tmp_map[s1[i]]);
		}
#endif

		int j = 0;
		for (; j < strlen(s1); j++) {
			if (tmp_map[s2[i + j]] == 0)
				break;
			else
				tmp_map[s2[i + j]]--;
		}
		if (j == strlen(s1))
			return true;
	}
	return false;
}

bool allZero(int *array, int n) {
	for (int i = 0; i < n; i++) {
		if (array[i]) return false;
	}
	return true;
}

bool checkInclusionII(char *s1, char *s2) {
	//if (strlen(s2) < strlen(s1)) return false;
	const int n = 128;
	int map[n];
	for (int i = 0; i < n; i++) map[i] = 0;
	
	for (int i = 0; i < strlen(s1); i++) {
		map[s1[i]] += 1;
		map[s2[i]] -= 1;
	}
	if(allZero(map, n)) return true;

	for (int i = strlen(s1); i < strlen(s2); i++) {
		map[s2[i - strlen(s1)]] += 1;
		map[s2[i]] -= 1;
		if (allZero(map, n)) return true;
	}
	return false;

}

int *findAnagrams(char *s, char *p, int *returnSize) {
	//int cs[strlen(s)], n = 0;
	int *cs, n = 0;
	cs = calloc(n, sizeof(int));
	int letter_n = 26;
	int map[letter_n];
	for (int i = 0; i < letter_n; i++) map[letter_n] = 0;

	for (int i = 0; i < strlen(p); i++) {
		map[p[i] - 'a'] += 1;
		map[s[i] - 'a'] -= 1;
	}

	if(allZero(map, letter_n)) cs[n++] = 0;

	for (int i = strlen(p); i < strlen(s); i++) {
		map[s[i]] -= 1;
		map[s[i - strlen(p)]] += 1;
		if (allZero(map, letter_n)) cs[n++] = i;
	}
	*returnSize = n;
	return cs;
}

bool isAnagram(char *s, char *t) {
	if (strlen(s) != strlen(t)) return false;
	int map[26] = {0};
	for (int i = 0; i < strlen(s); i++) {
		map[s[i] - 'a'] += 1;
		map[t[i] - 'a'] -= 1;
	}
	for (int i = 0; i < 26; i++) 
		if(map[i]) return false;
	return true;
}

int main(void) {
	freopen("input.txt", "r", stdin);
	char s[10000], t[10000];
	scanf("%s %s", s, t);
	if (isAnagram(s, t) == true) 
		puts ("true");
	else
		puts ("false");
	return 0;
}
