#include <iostream>
#include <vector>
#include <climits>
#include <map>

using namespace std;

class Solution {
public:
	int shoppingOffers(vector<int> &price, vector<vector<int>> &special, vector<int> &needs) {
		int retval = 0, n = price.size(), j;
		for (int i = 0; i < n; i++) retval += price[i] * needs[i];
		for (int i = 0; i < special.size(); i++) {
			vector<int> tmpvec = needs;
			for (j = 0; j < n; j++) {
				if (tmpvec[j] < special[i][j]) break;
				tmpvec[j] -= special[i][j];
			}
			if (j == n) retval = min(retval, special[i][n] + shoppingOffers(price, special, tmpvec));
		}
		return retval;
	}
};

int main() {
	vector<int> price = {2, 5};
	vector<vector<int>> special = {{3, 0, 5}, {1, 2, 10}};
	vector<int> needs = {3, 2};
	cout << Solution().shoppingOffers(price, special, needs);
	return 0;
}
