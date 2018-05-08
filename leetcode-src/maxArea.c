#include <stdio.h>
#include <stdlib.h>

int maxArea(int *height, int heightSize) {
	int max_area = 0;
	int high = heightSize - 1, low = 0;
	while(low < high) {
		int h = height[high] < height[low] ? height[high] : height[low];
		int area = (high - low) * h;
		if(area > max_area)
			max_area = area;
		if(height[low] < height[high])
			low++;
		else
			high--;
	}
	return max_area;
}


int trap(int *height, int heightSize) {
	int water = 0;
	int left = 0, right = heightSize - 1;
	int left_max = 0, right_max = 0;

	while(left < right) {
		if(height[left] < height[right]) {
			if(height[left] > left_max) left_max = height[left];
			else water += left_max - height[left];
			left++;
		}
		else {
			if(height[right] > right_max) right_max = height[right];
			else water += right_max - height[right];
			right--;
		}
	}
	return water;
}

int trapII(int *height, int heightSize) {
	int max = 0, water = 0;

	for(int i = 0; i < heightSize; i++) {
		if(height[i] > max) max = height[i];
		else water += max - height[i];
	}
	return water;
}

int trapIII(int *height, int heightSize) {
	int h = 0, index = 0;
	for(int i = 0; i < heightSize; i++) {
		if(height[i] > h) {
			h = height[i];
			index = i;
		}
	}

	int ch = 0, water = 0;
	for(int i = 0; i < index; i++) {
		if(height[i] > ch) ch = height[i];
		else water += ch - height[i];
	}

	for(int i = heightSize - 1, ch = 0; i >= index; i--) {
		if(height[i] > ch) ch = height[i];
		else water += ch - height[i];
	}
	return water;
}
int main() {
	int a[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
	//printf("%d\n", sizeof(a)/sizeof(int));
	printf("%d\n", trapIII(a, sizeof(a)/sizeof(int)));
	return 0;
}
