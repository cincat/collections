#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	bool canJump(vector<int> &nums) {
		//int n = nums.size();	
		//vector<int> cr(n, 0);
		//cr[0] = 1;
		//for (int i = 0; i < n - 1 && cr[i] == 1; i++) {
		//	int t = i;
		//	while (t < n) {
		//		if (nums[t] == 0) break;
		//		for (int j = t + 1; j <= t + nums[t] && j < n; j++) cr[j] = 1;
		//		t += nums[t];
		//	}
		//	if (t >= n - 1) return true;
		//}
		//return n == 1 ? true : false;
		int last = nums.back();

		for (int i = nums.size() - 1; i >= 0; i--) {
			if (nums[i] + i >= last)
				last = i;
		}
		return last == 0;
	}
};

int main() {
	Solution sl;
	vector<int> vec = {2, 0, 0};
	bool can = sl.canJump(vec);
	cout << boolalpha << can << noboolalpha << endl;
	return 0;
}
