#include <stdio.h>

int main() {
	int i = 1;
	int array[] = {0, 1, 2, 3};
	if((i) == 1)
		fputs("equal!", stdout);
	else
		fputs("not equal!", stdout);

	printf("%d\n", array[(i++)]);
	return 0;
}
