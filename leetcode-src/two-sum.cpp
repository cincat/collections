#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int> nums, int target) {
		map<int, int> map;
		for (int i = 0; i < nums.size(); i++) {
			if (map.find(target - nums[i]) == map.end()) { map[nums[i]] = i; }
			else {return {map[target - nums[i]], i};}
		}
		return {};
	}

	vector<int> findErrorNums(vector<int> &nums) {
		int n = nums.size();
		vector<int> map(n + 1, 0);
		int dup, lost;
		//for (int i = 0; i < n; i++) { ++map[nums[i]]; }
		//for (int i = 1; i <= n; i++) { 
		//	if (map[i] == 0) lost = i;
		//	if (map[i] > 1) dup = i;
		//}

		for (int i = 0; i < n; i++) {
			++map[nums[i]];
			if (i + 1 != nums[i]) lost = i + 1;
			if (map[nums[i]] > 1) dup = nums[i];
		}
		return {dup, lost};
	}

	double findMaxAverage(vector<int> &nums, int k) {
		int n = nums.size();
		double average = 0;
		for (int i = 0; i < k; i++) average += nums[i];
		double ma = average;
		for (int i = 1; i + k <= n; i++) {
			average -= nums[i - 1];
			average += nums[i + k - 1];
			ma = std::max(average, ma);
		}
		return ma
	}

};

int main() {
	return 0;
}
