#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	template <typename T> void print(T &dp);
	bool isInterleave(string s1, string s2, string s3) {
		int m = s1.size();	
		int n = s2.size();
		if (s3.size() != m + n) return false;
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
		
		dp[0][0] = true;
		for (int i = 1; i <= m; i++) { dp[i][0] = s1.substr(0, i) == s3.substr(0, i); }
		for (int j = 1; j <= n; j++) { dp[0][j] = s2.substr(0, j) == s3.substr(0, j); }

		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <=n; j++) {
				dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1])
						 || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
			}
		}
		return dp[m][n];
	}
	
};

template<typename T> void Solution::print(T &dp) {
	for (auto &x : dp) {
		for (auto y : x) {
			cout << boolalpha << y << " ";
		}
		cout << endl;
	}
}

int main() {
	string s1 = "aabcc";
	string s2 = "dbbca";
	//string s3 = "aadbbcbcac";
	string s3 = "aadbbbaccc";
	cout << boolalpha << Solution().isInterleave(s1, s2, s3);
	return 0;
}
