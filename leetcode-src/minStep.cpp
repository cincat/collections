#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int minSteps(int n) {
		int ans = 0;
		for (int i = 2; i <= n; i++) {
			while (n % i == 0) {
				ans += i;
				n = n / i;
			}
		}
		return ans;
	}
};

int main() {
	cout << Solution().minSteps(1000);
	return 0;
}
