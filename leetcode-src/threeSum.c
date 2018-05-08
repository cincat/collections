#include <stdio.h>
#include <stdlib.h>

int *twoSum(int *nums, int numsSize, int target) {
	int *two = (int *)malloc(2);

	for(int i = 0; i < numsSize; i++) {
		for(int j = i + 1; j < numsSize; j++) {
			if(nums[i] + nums[j] == target) {
				two[0] = i;
				two[1] = j;
				return two;
			}
		}
	}
	return NULL;
}

int **threeSum(int *nums, int numSize, int *returnSize) {

}

int main() {
	int array[3] = {3, 2, 4};
	twoSum(array, 3, 6);
	return 0;
}
