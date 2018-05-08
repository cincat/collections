#include <iostream>
#include <vector>
#include <deque>
#include <climits>

using namespace std;

class Solution {
public:
	//int findDis(vector<vector<int>> &matrix, int xi, int xj) {
	//	if (matrix[xi][xj] == 0) return 0;

	//	int m = matrix.size();
	//	int n = matrix[1].size();
	//	vector<vector<int>> vis(m, vector<int>(n));
	//	deque<pair<int, int>> queue;
	//	queue.push_back(make_pair(xi, xj));
	//	vis[xi][xj] = 1;
	//	int dis = 0;

	//	while (!queue.empty()) {
	//		int i = queue.front().first;			
	//		int j = queue.front().second;
	//		queue.pop_front();
	//		if (i > 0 && vis[i - 1][j] == 0) {
	//			if (matrix[i - 1][j] == 0) { dis = abs(xi - i + 1) + abs(xj - j); break; } 
	//			else {queue.push_back(make_pair(i - 1, j)); vis[i - 1][j] = 1;}
	//		}
	//		if (i < m - 1 && vis[i + 1][j] == 0) {
	//			if (matrix[i + 1][j] == 0) { dis = abs(xi - i - 1) + abs(xj - j); break; }
	//			else {queue.push_back(make_pair(i + 1, j)); vis[i + 1][j] = 1;}
	//		}
	//		if (j > 0 && vis[i][j - 1] == 0) {
	//			if (matrix[i][j - 1] == 0) { dis = abs(xi - i) + abs(xj - j + 1); break; }
	//			else {queue.push_back(make_pair(i, j - 1)); vis[i][j - 1] = 1;}
	//		}
	//		if (j < n - 1 && vis[i][j + 1] == 0) {
	//			if (matrix[i][j + 1] == 0) { dis = abs(xi - i) + abs(xj - j - 1); break; }
	//			else {queue.push_back(make_pair(i, j + 1)); vis[i][j + 1] = 1;}
	//		}
	//	}
	//	return dis;
	//}
	

	vector<vector<int>> updateMatrix(vector<vector<int>> &matrix) {
		//int m = matrix.size();
		//if (m == 0) return matrix;
		//int n = matrix[0].size();
		//vector<vector<int>> disMatrix(m, vector<int>(n, INT_MAX - 1000));

		//for (int i = 0; i < m; i++) {
		//	for (int j = 0; j < n; j++) {
		//		if (matrix[i][j] == 0) {
		//			disMatrix[i][j] = 0;
		//		}
		//		else {
		//			if (i > 0)
		//				disMatrix[i][j] = min(disMatrix[i][j], disMatrix[i - 1][j] + 1);
		//			if (j > 0)
		//				disMatrix[i][j] = min(disMatrix[i][j], disMatrix[i][j - 1] + 1);
		//		}
		//	}
		//}

		//for (int i = m - 1; i >= 0; i--) {
		//	for (int j = n - 1; j >= 0; j--) {
		//		if (i < m - 1)
		//			disMatrix[i][j] = min(disMatrix[i][j], disMatrix[i + 1][j] + 1);
		//		if (j < n - 1)
		//			disMatrix[i][j] = min(disMatrix[i][j], disMatrix[i][j + 1] + 1);
		//	}
		//}
		//return disMatrix;

		int m = matrix.size();
		if (m == 0) return matrix;
		int n = matrix[0].size();
		vector<vector<int>> distance(m, vector<int>(n, INT_MAX - 1000));

		deque<pair<int, int>> queue;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (matrix[i][j] == 0) {
					queue.push_back(make_pair(i, j));
					distance[i][j] = 0;
				}
			}
		}
		
		int direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		while (!queue.empty()) {
			int i = queue.front().first;
			int j = queue.front().second;
			queue.pop_front();

			for (int k = 0; k < 4; k++) {
				int xi = i + direction[k][0];
				int xj = j + direction[k][1];

				if (xi >= 0 && xi < m && xj >=0 && xj < n) {
					if (distance[xi][xj] > distance[i][j] + 1) {
						distance[xi][xj] = distance[i][j] + 1;
						queue.push_back(make_pair(xi, xj));
					}
				}
			}
		}
		return distance;	
	}
};

template <typename T> void printMatrix(T matrix) {
	for (auto &row : matrix) {
		for (auto &item : row) {
			cout << item << " ";
		}
		cout << endl;
	}
}

int main() {
	vector<vector<int>> matrix = {
		{0, 1, 0}, 
		{0, 1, 0}, 
		{0, 1, 0},
		{0, 1, 0},
		{0, 1, 0}
	};

	vector<vector<int>> disMatrix;
	disMatrix = Solution().updateMatrix(matrix);
	printMatrix(disMatrix); 
	return 0;
}
