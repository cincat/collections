#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	vector<vector<int>> generateMatrix(int n) {
		vector<vector<int>> matrix(n, vector<int>(n));
		const int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		int x = 0, i = 0, j = -1, k = 1;

		while (k <= n*n) {
			const int (&dd)[2] = d[x % 4];
			while (i + dd[0] >= 0 && i + dd[0] < n
				&& j + dd[1] >= 0 && j + dd[1] < n
				&& matrix[i + dd[0]][j + dd[1]] == 0) {
				i += dd[0];
				j += dd[1];
				matrix[i][j] = k;
				++k;
			}
			++x;
		}
		return matrix;
	}
	vector<int> spiralOrder(vector<vector<int>> &matrix) {
		if (matrix.empty()) return {};
		int m = matrix.size();
		int n = matrix[0].size();
		vector<int> ra;
		//while (!matrix.empty()) {
		//	ra.insert(ra.cend(), matrix[0].begin(), matrix[0].end());
		//	matrix.erase(matrix.begin());
		//	trans(matrix);
		//}
		//return ra;
		//int vis[m][n] = {};	
		
		vector<vector<int>> vis(m, vector<int>(n));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << vis[i][j] << " ";
			}
			cout << endl;
		}

		const int dd[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		int i = 0, j = -1, k = 0, x = 0;

		while(ra.size() < m * n) {
			const int (&d)[2] = dd[x % 4];
			while (i + d[0] >= 0 && i + d[0] < m
				&& j + d[1] >= 0 && j + d[1] < n
				&& vis[i + d[0]][j + d[1]] == 0) {
				//cout << d[0] << " " << d[1] << endl;
				i += d[0];
				j += d[1];
				ra.push_back(matrix[i][j]);
				vis[i][j] = 1;
				++k;
			}
			++x;
		}
		return ra;
	}
private:
	void trans (vector<vector<int>> &matrix) {
		if (matrix.empty()) return;
		int m = matrix.size();
		int n = matrix[0].size();
		vector<vector<int>> tm(n, vector<int>(m));
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				tm[i][j] = matrix[j][n - 1 - i];
			}
		}

		matrix = tm;
	}
	
	void print_m (vector<vector<int>> &matrix, int n) {
		for (int i = 0; i < n; i++) {
			cout << '[';
			for (int j = 0; j < n; j++) {
				cout << matrix[i][j] << " ";	
			}
			cout << "]" << endl;
		}
		cout << endl;
	}
};

int main() {
	Solution sl;
	vector<vector<int>> vec = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	vector<int> spiral = sl.spiralOrder(vec);
	//for (int i = 0; i < spiral.size(); i++) {
	//	cout << spiral[i] << " ";
	//}
	for (auto x : spiral) {
		cout << x << " ";
	}
	int n = 3;
	//vector<vector<int>> matrix = sl.generateMatrix(n);
	//for (int i = 0; i < n; i++) {
	//	cout << '[';
	//	for (int j = 0; j < n; j++) {
	//		cout << matrix[i][j] << " ";	
	//	}
	//	cout << "]" << endl;
	//}
	return 0;
}
