#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
	vector<string> restoreIpAddress(string s) {
		vector<string> vec;
		int n = s.size();
		for (int a = 1; a < 4; a++)
		for (int b = 1; b < 4; b++) 
		for (int c = 1; c < 4; c++)
		for (int d = 1; d < 4; d++) {
			if (a + b + c + d == n) {
				int aa = stoi(s.substr(0, a));
				int bb = stoi(s.substr(a, b));
				int cc = stoi(s.substr(a + b, c));
				int dd = stoi(s.substr(a + b + c, d));
				if (aa <= 255 && bb <= 255 && cc <= 255 && dd <= 255) {
					string r = to_string(aa) + "." + to_string(bb)
						+ "." + to_string(cc) + "." + to_string(dd);
					if (r.size() == s.size() + 3) vec.push_back(r);
				}
			}
		}
		return vec;
	}
};

int main() {
	vector<string> vec = Solution().restoreIpAddress("25525511135");
	for (auto s : vec) {
		cout << s << endl;
	}
	return 0;
}
