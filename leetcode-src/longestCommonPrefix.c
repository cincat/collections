#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longestCommonPrefix(char **strs, int strsSize) {
	char *prefix = (char *)calloc(10000, sizeof(char));
	for(int i = 0; i < strsSize; i++) {
		for(int j = i + 1; j < strsSize; j++) {
			int k = 0;
			for(; strs[i][k] == strs[j][k]; k++);
			if(k > strlen(prefix))
				strncpy(prefix, strs[i], k);
		}
	}
	return prefix;
}

int main() {
	char *arr[] = {"aabb", "aaab", "aab", "aac"};
	printf("%s\n", longestCommonPrefix(arr, 4));
	return 0;
}
