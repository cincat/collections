#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
	int numDecodings(string s) {
		/*===============================================*/
		//recursive solver
		//if (s.size() == 0) return 0;
		//else if (s.size() == 1) {
		//	if (s[0] == '0') return 0; 
		//	else return 1;
		//}
		//int m = 0;
		//if (s[0] != '0') {
		//	m += numDecodings(s.substr(1));
		//}
		//if (s[0] != '0' && stoi(s.substr(0, 2)) >= 1 && stoi(s.substr(0, 2)) <= 26) {
		//	if (s.size() == 2) m += 1;
		//	else m += numDecodings(s.substr(2));
		//}
		//return m;

		/*===============================================*/

		//dynamic programming solver
		//int n = s.size();
		//if (n == 0) return 0;
		//vector<int> dp(n);
		//if (s[n - 1] != '0') dp[n - 1] = 1;

		//for (int k = n - 2; k >= 0; k--) {
		//	if (s[k] != '0') dp[k] += dp[k + 1];
		//	if (s[k] != '0' && stoi(s.substr(k, 2)) >= 1 && stoi(s.substr(k, 2)) <= 26) {
		//		// if k is the last second item and satisfy the property, we should add the result directly
		//		if (k == n - 2) dp[k] += 1;
		//		else dp[k] += dp[k + 2];
		//	}
		//}
		//return dp[0];
		/*===============================================*/

		const int mod = 1e9 + 7;
		int n = s.size();
		if (n == 0) return 0;
		vector<long long> dp(n);
		if (s[n - 1] != '0') {
			if (s[n - 1] == '*') dp[n - 1] = 9;
			else dp[n - 1] = 1;
		}
		for (int k = n - 2; k >=0; k--) {
			if (s[k] != '0') {
				if (s[k] == '*') dp[k] = (dp[k] + 9 * dp[k + 1]) % mod;
				else dp[k] = (dp[k] + dp[k + 1]) % mod;
			}
			if (s[k] != '0') {
				if (s[k] == '*' && s[k + 1] != '*') {
					if (k == n - 2) dp[k] = (s[k + 1] < '7' ? 2  + dp[k]: 1 + dp[k]);
					else dp[k] = (dp[k] + (s[k + 1] < '7' ? 2 * dp[k + 2]: dp[k + 2])) % mod;
				}
				else if (s[k] != '*' && s[k + 1] == '*') {
					if (s[k] == '2') {
						if (k == n - 2) dp[k] = (dp[k] + 6);
						else dp[k] = (dp[k] + 6 * dp[k + 2]) % mod;

					}
					else if (s[k] == '1') {
						if (k == n - 2) dp[k] = (dp[k] + 9);
						else dp[k] = (dp[k] + 9 * dp[k + 2]) % mod;
					}
				}
				else if (s[k] == '*' && s[k + 1] == '*') {
					if (k == n - 2) dp[k] = (9 * 9 + 15);
					// pay attention to num 15, this is not 96
					else dp[k] = (dp[k] + 15 * dp[k + 2]) % mod;
				}
				else if (stoi(s.substr(k, 2)) >= 1 && stoi(s.substr(k, 2)) <= 26){
					if (k == n - 2) dp[k] += 1;
					else dp[k] = (dp[k + 2] + dp[k]) % mod;
				}
			}
		}
		return dp[0];
	}
};


int main() {
	//cout << Solution().numDecodings("9371597631128776948387197132267188677349946742344217846154932859125134924241649584251978418763151253");
	//cout << Solution().numDecodings("1*");
	return 0;
}
