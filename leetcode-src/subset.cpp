#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
	vector<vector<int>> subsets(vector<int> &nums) {
		int n = nums.size();	
		vector<vector<int>> subs;
		for (long long i = 0; i < pow(2, n); i++) {
			vector<int> sub;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j))
					sub.push_back(nums[j]);
			}
			subs.push_back(sub);

		}
		return subs;
	}
};

int main() {
	Solution sl;
	vector<int> vec;
	//sl.subsets(vec);
	cout << sizeof(int);
	return 0;
}
