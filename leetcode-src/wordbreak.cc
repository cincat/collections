#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
	bool wordBreak(string s, vector<string> &wordDict) {
		unordered_set<string> set;
		vector<bool> dp(s.size() + 1, false);
		for (const auto &entry : wordDict) { set.insert(entry); }
		dp[0] = true;
		for (int i = 1; i <= s.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (set.find(s.substr(j, i - j)) != set.end()) {
					dp[i] = dp[j];
					if (dp[i]) break;
				}
			}	
		}
		return dp[s.size()];
		//if (set.find(s.substr(0, 1)) != set.end()) {
		//	dp[0] = true;
		//}

		//for (int i = 1; i < dp.size(); i++) {
		//	if (set.find(s.substr(0, i + 1)) != set.end()) {
		//		dp[i] = true;
		//	}
		//	for (int j = 0; j < i; j++) {
		//		if (dp[j] && set.find(s.substr(j + 1, i - j)) != set.end()) {
		//			dp[i] = true;
		//		}
		//	}
		//}
		//return dp[s.size() - 1];
	}
};

int main() {
	vector<string> vec = {"aaaa", "aaa"};
	cout << boolalpha << Solution().wordBreak("aaaaaaa", vec) << endl;
	return 0;
}
