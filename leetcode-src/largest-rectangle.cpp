#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
	int largestRectangleArea(vector<int> &heights) {
		int m = 0;
		vector<int> stack;
		heights.push_back(0);
		int n = heights.size();

		int i = 0;

		while (i < n) {
			if (stack.empty() || heights[stack.back()]<= heights[i]) {
				stack.push_back(i++);
			}
			else {
				int tp = stack.back();
				stack.pop_back();
				int area = heights[tp] * (stack.empty() ? i : i - stack.back() - 1);
				m = max (m, area);
			}
		}

		return m;
	}

	int maximalRectangle (vector<vector<char>> &matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int m = matrix.size();
		int n = matrix[0].size();
		int marea = 0;

		//for (int i = 0; i < m; i++) {
		//	for (int j = 0; j < n; j++) {
		//		cout << matrix[i][j] << " ";
		//	}
		//	cout << endl;
		//}

		for (int i = 0; i < m; i++) {
			vector<int> his(n);
			for (int j = 0; j < n; j++) {
				for (int k = i; k >= 0 && matrix[k][j] == '1'; k--) {
					his[j] += matrix[k][j] - '0';
				}
			}

			//for (int j = 0; j < n; j++) {
			//	cout << his[j] << " ";
			//}
			//cout << endl;

			int area = largestRectangleArea(his);
			marea = max (area, marea);	
		}
		return marea;
	}
};

int main() {
	vector<vector<char>> vec = {
		{'1', '0', '1', '0', '0'},
		{'1', '0', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '0', '0', '1', '0'}
	};
	Solution sl;

	cout << sl.maximalRectangle(vec) << endl;
	return 0;
}
