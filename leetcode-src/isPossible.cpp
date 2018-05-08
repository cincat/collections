#include <iostream>
#include <vector>
#include <list>

using namespace std;
class Solution {
public:
	bool isPossible(vector<int> &nums) {
		//vector<int> repeat(nums.size(), 0);
		//vector<int> seqlen(nums.size(), 0);
		//vector<int> seqprev(nums.size(), 0);
		//for (int i = 0; i < nums.size(); i++) {
		//	for (int j = 0; i + j < nums.size(); j++) {
		//		if (nums[i] == nums[i + j]) {
		//			repeat[i] += 1;
		//		}
		//		else {
		//			break;
		//		}
		//	}
		//}
		////for (auto &x : repeat) cout << x << " ";
		////cout << endl;
		//int mp = 0;//max repeat num
		//for (int i = 0; i < nums.size(); i++) {
		//	if (repeat[i] > mp) mp = repeat[i];
		//	if (seqlen[repeat[i]] == 0 || nums[i] == seqprev[repeat[i]] + 1) {
		//		seqlen[repeat[i]] += 1;
		//		seqprev[repeat[i]] = nums[i];
		//	}
		//	else if (repeat[i] == 1) {
		//		if (seqprev[mp] + 1 == nums[i]) {
		//			seqlen[mp] += 1;
		//			seqprev[mp] = nums[i];
		//		}
		//	}
		//	else {
		//		if (seqlen[repeat[i]] < 3) 
		//			return false;
		//		else {
		//			seqlen[repeat[i]] = 0;
		//			//seqprev[repeat[i]] = nums[i];
		//		}
		//	}
		//}
		//for (const auto &x : seqlen) {
		//	if (x < 3 && x != 0) return false;
		//}

		//return true;
		vector<int> seqlen;
		vector<int> seqprev;
		seqlen.push_back(1);
		seqprev.push_back(nums[0]);
		for (int i = 1; i < nums.size(); i++) {
			int l = nums.size() + 1, k = -1;
			for (int j = 0; j < seqprev.size(); j++) {
				if (nums[i] == seqprev[j] + 1 && l > seqlen[j]) {
					k = j;
					l = seqlen[j];
				}
			}	
			if (k != -1) {
				seqprev[k] = nums[i];
				seqlen[k] += 1;
			}
			else {
				seqprev.push_back(nums[i]);
				seqlen.push_back(1);
			}
		}
		
		for (auto &x : seqlen) {
			if (x < 3) return false;
		}
		return true;
	}
};

int main() {
	vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 5};
	cout << boolalpha << Solution().isPossible(nums);
	return 0;
}
