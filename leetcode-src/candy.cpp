#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int candy(vector<int> &ratings) {
		//int n = ratings.size();
		//vector<int> candy(n, 1);
		//bool flag = true;
		//while (flag) {
		//	flag = false;
		//	for (int i = 0; i < n; i++) {
		//		if (i != n - 1 && ratings[i] > ratings[i + 1] && candy[i] <= candy[i + 1]) {
		//			candy[i] = candy[i + 1] + 1;
		//			flag = true;
		//		}

		//		if (i != 0 && ratings[i] > ratings[i - 1] && candy[i] <= candy[i - 1]) {
		//			candy[i] = candy[i - 1] + 1;
		//			flag = true;
		//		}
		//	}
		//}
		//int retval = accumulate(candy.begin(), candy.end(), 0);
		//return retval;
		int n = ratings.size();
		vector<int> candy(n, 1);
		for (int i = 1; i < n; i++) {
			if (ratings[i] > ratings[i - 1] && candy[i] <= candy[i - 1]) candy[i] = candy[i - 1] + 1;
		}
		for (int i = n - 2; i >= 0; i--) {
			if (ratings[i] > ratings[i + 1] && candy[i] <= candy[i + 1]) candy[i] = max(candy[i], candy[i + 1] + 1);
		}
		return accumulate(candy.begin(), candy.end(), 0);
	}
};

int main() {
	vector<int> vec = {1, 2, 2};
	cout << Solution().candy(vec);
	return 0;
}
