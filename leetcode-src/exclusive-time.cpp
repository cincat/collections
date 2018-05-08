#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	vector<int> exclusiveTime(int n, vector<string> &logs) {
		stack<tuple<int, string, int>> fstack;
		vector<int> retvec(n);
		for (string log : logs) {
			auto pos1 = log.find(":", 0);
			auto pos2 = log.find(":", pos1 + 1);
			int fnum = stoi(log.substr(0, pos1));
			string pred = log.substr(pos1 + 1, pos2 - pos1 - 1);
			int tm = stoi(log.substr(pos2 + 1));
			if (fstack.empty()
					|| get<0>(fstack.top()) != fnum
					|| get<1>(fstack.top()) == pred)
				fstack.push(make_tuple(fnum, pred, tm));
			else {
				int t = tm - get<2>(fstack.top()) + 1;
				retvec[fnum] += t;
				fstack.pop();
				if (!fstack.empty()) retvec[get<0>(fstack.top())] -= t;
			}
		}
		return retvec;
	}
};

int main() {
	vector<int> testvec;
	string teststr("0:start:0");
	testvec = Solution().getContent(teststr);
	return 0;
}
