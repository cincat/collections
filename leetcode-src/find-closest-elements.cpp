#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> findClosestElements(vector<int> &arr, int k, int x) {
		int n = arr.size();
		//int low = 0, high = n;
		//while (low <= high) {
		//	int median = (low + high) / 2;
		//	if (arr[median] < x) {
		//		low = median + 1;
		//	}
		//	else if (arr[median] > x) {
		//		high = median - 1;
		//	}
		//	else {
		//		
		//	}
		//}

		int i = 0;
		for (; i < n; i++) if (arr[i] > x) break;
		auto itx = arr.begin();
		//i < k ? itx = arr.begin() : itx = arr.begin() + i - k;
		if (i > k) itx = arr.begin() + i - k;
		vector<int> res(itx, itx + k);
		return res;
	}
};

template <typename T> void printArray(T array) {
	for (auto &x : array) {
		cout << x << " ";
	}
	cout << endl;
}
int main() {
	vector<int> arr = {1, 2, 3, 4, 5};
	printArray(Solution().findClosestElements(arr, 4, -1));	
	return 0;
}
