#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<vector<int>> subsetsWithDup(vector<int> &nums) {
		sort(nums.begin(), nums.end());
		int n = nums.size();

		vector<vector<int>> r = {{}};
		for (int i = 0; i < n;) {
			int c = 0;
			while (i + c < n && nums[i] == nums[i + c]) c++;

			int rs = r.size();
			for (int j = 0; j < rs; j++) {
				vector<int> t = r[j];
				for (int k = 0; k < c; k++) {
					t.push_back(nums[i]);
					r.push_back(t);
				}
			}
			i += c;
		}
		return r;
	}
};

int main() {
	vector<int> nums = {1, 2, 2};
	vector<vector<int>> r = Solution().subsetsWithDup(nums);
	for (auto & row : r) {
		for (auto & item : row) {
			cout << item << " "; 
		}
		cout << endl;
	}
	return 0;
}
