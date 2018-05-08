#include <iostream>
#include <vector>
#include <pair>

using namespace std;

class Solution {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		if (matrix.empty() || matrix[0].empty()) return false;

		int m = matrix.size();
		int n = matrix.size();

		int i = 0, j = n - 1;

		while (i < m && j >= 0) {
			if (matrix[i][j] == target) return true;
			else if (matrix[i][j] > target) j--;
			else i++;
		}
		return false;
	}
}

int main() {

	return 0;
}
