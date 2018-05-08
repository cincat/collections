#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> ps(m, vector<int>(n));
		for (int i = 0; i < n; i++) ps[0][i] = 1;
		for (int i = 0; i < m; i++) ps[i][0] = 1;

		for(int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				ps[i][j] = ps[i - 1][j] + ps[i][j - 1];
			}
		}
		return ps[m - 1][n - 1];
	}

	int uniquePathWithObstacles(vector<vector<int>> &obstacleGrid) {
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();
		vector<vector<int>> ps(m, vector<int>(n));
		for (int i = 0; i < n && obstacleGrid[0][i] == 0; i++) ps[0][i] = 1;
		for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++) ps[i][0] = 1;

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				ps[i][j] = obstacleGrid[i][j] == 1 ? 0 : ps[i][j - 1] + ps[i - 1][j];
			}
		}

		return ps[m - 1][n - 1];
	}

	int minPathSum(vector<vector<int>> &grid) {
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> ms(m, vector<int>(n));
		ms[0][0] = grid[0][0];

		for (int i = 1; i < n; i++) ms[0][i] = grid[0][i] + ms[0][i - 1];
		for (int i = 1; i < m; i++) ms[i][0] = grid[i][0] + ms[i - 1][0];

		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				ms[i][j] = min(ms[i - 1][j], ms[i][j - 1]) + grid[i][j];
			}
		}

		return ms[m - 1][n - 1];
	}
};
int main() {
	vector<vector<int>> vec = {{0, 0}};
	Solution sl; 
	cout << sl.uniquePathWithObstacles(vec);
	return 0;
}
