#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
public:
	bool find132pattern(vector<int> &nums) {
		int n = nums.size();	
		if (n < 3) return false;

		//int mn = nums[0];	
		//for (int i = 1; i < n; i++) {
		//	mn = min (nums[i], mn);
		//	for (int j = i + 1; j < n; j++) {
		//		if (nums[j] > mn && nums[j] < nums[i])
		//			return true;
		//	}
		//}
		//return false;

		//vector<int> mn(n, INT_MAX);
		//mn[0] = nums[0];
		//for (int i = 1; i < n; i++) mn[i] = min(nums[i], mn[i - 1]);
		//stack<int> kstack;
		//for (int j = n - 1; j >= 0; j--) {
		//	if (nums[j] > mn[j]) {
		//		while (!kstack.empty() && kstack.top() <= mn[j]) kstack.pop();
		//		if (!kstack.empty() && kstack.top() < nums[j]) return true;
		//		kstack.push(nums[j]);
		//	}
		//}

		vector<int> mn(n, INT_MAX);
		mn[0] = nums[0];
		int k = n;
		for (int i = 1; i < n; i++) mn[i] = min(mn[i - 1], nums[i]);
		for (int j = n - 1; j >= 0; j--) {
			if (nums[j] > mn[j]) {
				while (k < n && nums[k] <= mn[j]) ++k;
				if (k < n && nums[k] < nums[j]) return true;
				nums[--k] = nums[j];
			}
		}
		return false;	
	}
};


int main() {
	vector<int> nums = {2, 3, 1, 2};
	cout << boolalpha << Solution().find132pattern(nums);
	return 0;
}
