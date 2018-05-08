#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
	bool judgeCircle(string moves) {
		pair<int, int> point = make_pair<int, int>(0, 0);
		for (auto &c : moves) {
			switch(c) {
				case 'U': point.first++; break;
				case 'D': point.first--; break;
				case 'L': point.second++; break;
				case 'R': point.second--;break;
			}
			//if (point.first == 0 && point.second == 0) return true;
		}
		//return false;
		return point.first == 0 && point.second == 0;
	}
};

int main() {
	cout << boolalpha << Solution().judgeCircle("LL");
	return 0;
}
