#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
	public:
		int minDistance(string word1, string word2) {
			int m = word1.size();
			int n = word2.size();
			vector<vector<int>> dp(m + 1, vector<int>(n + 1));
			for (int i = 1; i <= m; i++) dp[i][0] = i;
			for (int j = 1; j <= n; j++) dp[0][j] = j;
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= n; j++) {
					int cost = word1[i - 1] == word2[j - 1] ? 0 : 1;
					dp[i][j] = min({
							dp[i][j - 1] + 1, 
							dp[i - 1][j] + 1,
							dp[i - 1][j - 1] + cost
							});
				}
			}

			return dp[m][n];
		}
};

int main() {
	Solution sl;
	cout << sl.minDistance("ate", "bac");
	return 0;
}
