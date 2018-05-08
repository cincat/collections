#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Solution {
public:
	vector<vector<int>> palindromePairs(vector<string> &words) {
		unordered_map<string, int> map;
		set<vector<int>> set;
		for (int i = 0; i < words.size(); i++) {
			map[string(words[i].rbegin(), words[i].rend())] = i;
		}

		for (int i = 0; i < words.size(); i++) {
			auto x = words[i];
			for (int j = 0; j <= x.size(); j++) {
				auto left = x.substr(0, j), right = x.substr(j);
				if (map.find(left) != map.end() && isPalindrome(right) && map[left] != i) {
					set.insert({i, map[left]});
				}
				if (map.find(right) != map.end() && isPalindrome(left) && map[right] != i) {
					set.insert({map[right], i});
				}
			}
		}
		return vector<vector<int>>(set.begin(), set.end());
	}
private:
	bool isPalindrome(const string &s) {
		for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
			if(s[i] != s[j]) return false;
		}
		return true;
	}
};

int main() {
	vector<string> strs = {"abcd", "dcba", "lls", "s", "sssll"};
	vector<vector<int>> vec = Solution().palindromePairs(strs);
	for (auto &x : vec) {
		cout << x[0] << " " << x[1] << endl;
	}
	//cout << string("abce").substr(4) << endl;
	return 0;
}
