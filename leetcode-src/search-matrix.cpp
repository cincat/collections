#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		if (matrix.empty() || matrix[0].empty()) return false;
		int m = matrix.size();
		int n = matrix[0].size();
		int low = 0, high = m * n - 1;

		while (low <= high) {
			int mid = (low + high)/2;
			int i = mid / n, j = mid % n;
			if (matrix[i][j] == target)
				return true;
			else if (target < matrix[i][j]) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		return false;
	}
};

int main() {
	Solution sl;
	//vector<vector<int>> matrix = {
	//	{1, 3, 5, 7},
	//	{10, 11, 16, 20},
	//	{23, 30, 34, 50}		
	//};

	vector<vector<int>> matrix = {{1}};
	cout << boolalpha << sl.searchMatrix(matrix, 2);
	return 0;
}
