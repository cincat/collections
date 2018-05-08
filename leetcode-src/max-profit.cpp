#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int> &prices) {
		int n = prices.size();
		if (n == 0) return 0;
		vector<int> minp(n);minp[0] = prices[0];
		vector<int> maxp(n);maxp.back() = prices.back();
		int retval = 0;
		for (int i = 1; i < n; i++)
			minp[i] = std::min(minp[i - 1], prices[i]);
		for (int i = n - 2; i >= 0; i--) 
			maxp[i] = std::max(maxp[i + 1], prices[i]);
		for (int i = 0; i < n; i++) {
			retval = std::max(retval, maxp[i] - minp[i]);
		}
		return retval;
	}
	int maxProfitII(vector<int> &prices) {
		if (prices.empty()) return 0;
		int n = prices.size(), retval = 0;
		//for (int i = 0; i < n - 1;) {
		//	if (prices[i] >= prices[i + 1]) {
		//		++i; continue;
		//	}
		//	int j;
		//	for (j = i + 1; j < n; j++) {
		//		if (prices[j] <= prices[j - 1]) break;
		//	}
		//	retval += prices[j - 1] - prices[i];
		//	i = j;
		//}	

		for (int i = 1; i < n; i++) {
			if (prices[i] > prices[i - 1]) 
				retval += prices[i] - prices[i - 1];
		}
		return retval;
	}
	
	pair<int, int> findMaxInterval(vector<int> &nums, int i, int j) {
		int minval = INT_MAX, max_interval = 0;
		int x, y;
		for (int k = i; k < j; k++) {
			if (nums[k] < minval) {
				minval = nums[k];
				x = k;
			} 
			else {
				if (nums[k] - minval > max_interval) {
					max_interval = nums[k] - minval;
					y = k;
				}
			}
		}
		return pair<int, int>(x, y);
	}

	int maxProfitIII(vector<int> &prices) {
		//if (prices.empty()) return 0;
		//int val = 0;
		//int most_max = 0, second_max = 0;
		//for (int i = 1; i < prices.size(); i++) {
		//	if (prices[i] > prices[i - 1]) {
		//		val += prices[i] - prices[i - 1];
		//		if (i == prices.size() - 1 || prices[i] > prices[i + 1]) {
		//			if (val > most_max) {
		//				second_max = most_max;
		//				most_max = val;
		//			}
		//			else if (val > second_max) {
		//				second_max = val;
		//			}
		//		}	
		//	}
		//	else {
		//		val = 0;
		//	}
		//}
		//return most_max + second_max;
		int n = prices.size();
		if (n == 0) return 0;
		vector<int> dp(n);

		for (int i = 0; i < n; i++) {

		}
	}
};

int main() {
	vector<int> prices = {1, 2, 4};
	cout << Solution().maxProfitIII(prices);
	return 0;
}
