#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<int> nextGreaterElement(vector<int> &findNums, vector<int> &nums) {
		vector<int> greater(nums.size());
		stack<int> nstack;
		map<int, int> nmap;
		for (int i = nums.size() - 1; i >= 0; i--) {
			if (nstack.empty() || nums[i] < nstack.top()) {
				nstack.empty() ? greater[i] = -1 : greater[i] = nstack.top();
				nstack.push(nums[i]);
			}
			else {
				while (!nstack.empty() && nstack.top() < nums[i]) nstack.pop();
				nstack.empty() ? greater[i] = -1 : greater[i] = nstack.top();
				nstack.push(nums[i]);
			}
			nmap[nums[i]] = i;
		}
		vector<int> retvec;
		for (auto x : findNums) retvec.push_back(greater[nmap[x]]);
		return retvec;
	}
	vector<int> nextGreaterElement(vector<int> &nums) {
		if (nums.empty()) return {};
		vector<int> greater(nums.size());
		stack<int> nstack;
		int nm = INT_MIN, nmi = 0, n = nums.size();
		for (int i = 0; i < n; i++) {
			nm = std::max(nm, nums[i]);
			if (nm == nums[i]) nmi = i;
		}
		for (int i = 0; i < n; i++) {
			int j = (nmi - i + n) % n;
			if (nstack.empty() || nums[j] < nstack.top()) {
				if (nstack.empty()) greater[j] = -1;
				else greater[j] = nstack.top();
				nstack.push(nums[j]);
			}
			else {
				while (nstack.size() && nums[j] >= nstack.top()) nstack.pop();
				if (nstack.empty()) greater[j] = -1;
				else greater[j] = nstack.top();
				nstack.push(nums[j]);
			}
		}
		return greater;
	}

	int nextGreaterElement(int n) {
		string s = to_string(n);
		vector<int> nums;
		for (auto c : s) nums.push_back(c - '0');
		for (int i = nums.size() - 2; i >= 0; i--) {
			int x = INT_MAX, k = i;
			for (int j = i + 1; j < nums.size(); j++) {
				//cannot use std::max because we want strictly max relationship
				if (nums[j] > nums[i] && nums[j] < x) {
					x = nums[j]; k = j;
				}
			}
			if (k != i) {
				std::swap(nums[i], nums[k]);
				sort(nums.begin() + i + 1, nums.end());
				string retstr;
				for (auto x : nums)retstr.insert(retstr.end(), (char)(x + '0'));
				long long t = stol(retstr);
				if (t > INT_MAX) return -1;
				return t;
			}
		}
		return -1;
	}
};

int main() {
	//vector<int> nums = {1, 2, 3, 4, 5};
	//vector<int> vec = Solution().nextGreaterElement(nums);
	//for (auto x : vec) cout << x << " ";
	cout << Solution().nextGreaterElement(12443322);
	return 0;
}
