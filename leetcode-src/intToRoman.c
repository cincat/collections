#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *intToRoman(int num) {
	char* c[][10] = {
		{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
		{"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
		{"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
		{"", "M", "MM", "MMM"}
	};
	char *roman = (char *)calloc(50, sizeof(char));
	strcat(roman, c[3][num / 1000 % 10]);
	strcat(roman, c[2][num / 100 % 10]);
	strcat(roman, c[1][num / 10 % 10]);
	strcat(roman, c[0][num % 10]);
	return roman;
}

int romanToInt(char *s) {
	int roman[26];
	roman['I' - 'A'] = 1;
	roman['V' - 'A'] = 5;
	roman['X' - 'A'] = 10;
	roman['L' - 'A'] = 50;
	roman['C' - 'A'] = 100;
	roman['D' - 'A'] = 500;
	roman['M' - 'A'] = 1000;

	int n = strlen(s);
	int sum = roman[s[n - 1] - 'A'];

	for(int i = n - 2; i >= 0; i--) {
		if(roman[s[i] - 'A'] < roman[s[i + 1] - 'A'])
			sum -= roman[s[i] - 'A'];
		else
			sum += roman[s[i] - 'A'];
	}
	return sum;
}

int main() {
	printf("%s\n", intToRoman(399));
	printf("%d\n", romanToInt(intToRoman(621)));
	return 0;
}
