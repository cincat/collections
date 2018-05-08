#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int abstractNum(string s, int start) {
		int k = 0;
		for (; start + k < s.size() && isdigit(s[start + k]); k++); 
		return k;
	}
	string solveEquation(string equation) {
		bool left_side = true;
		int left = 0, right = 0;
		int n = equation.size();
		for (int i = 0; i < equation.size();) {
			if (equation[i] == '+') {
				++i;
				int k = abstractNum(equation, i);
				string s(equation.begin() + i, equation.begin() + i + k);
				int num = 1;
				if (s.size()) num = stoi(s);
				if (i + k < n && equation[i + k] == 'x') {
					if (left_side) left += num;
					else left -= num;
					i += k + 1;
				}
				else {
					if (left_side) right -= num;
					else right += num;
					i += k;
				}
			}
			else if (equation[i] == '-') {
				++i;
				int k = abstractNum(equation, i);
				string s(equation.begin() + i, equation.begin() + i + k);
				int num = 1;
				if (s.size()) num = stoi(s);
				if (i + k < n && equation[i + k] == 'x') {
					if (left_side) left -= num;
					else left += num;
					i += k + 1;
				}
				else {
					if (left_side) right += num;
					else right -= num;
					i += k;
				}
			}
			else if (equation[i] == '=') {
				++i;
				left_side = false;
			}
			else {
				int k = abstractNum(equation, i);
				string s(equation.begin() + i, equation.begin() + i + k);
				int num = 1;
				if (s.size()) num = stoi(s);
				if (i + k < n && equation[i + k] == 'x') {
					if (left_side) left += num;
					else left -= num;
					i += k + 1;
				}
				else {
					if (left_side) right -= num;
					else right += num;
					i += k;
				}
			}
		}

		if (left == 0 && right == 0) return "Infinite solution";
		else if (left == 0) return "No solution";
		else return "x="+to_string(right/left);
	}
};

int main() {
	cout << Solution().solveEquation("2x+3x-6x=x+2");
	return 0;
}
