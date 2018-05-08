#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int removeDuplicates(vector<int> &nums) {
		for (auto px = nums.begin(); px != nums.end();) {
			auto py = px;
			for (; *py == *px && py != nums.end(); py++);
			if (py - px > 2) {
				nums.erase(px, py - 2);
			}
			px = py;
		}	
		return nums.size();
	}
};

int main() {
	Solution sl;
	vector<int> vec = {1, 1, 1, 2, 2, 3};
	cout << sl.removeDuplicates(vec);
	return 0;
}
