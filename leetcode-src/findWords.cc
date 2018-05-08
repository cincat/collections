#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Trie {
public:
	Trie() {
		for (auto &x : children) { x = nullptr; }
		end = false;
	}
	void insert(const string &s) {
		decltype(this) p = this;
		for (const auto &x : s) {
			if (p->children[x - 'a'] == nullptr) {
				p->children[x - 'a'] = new Trie();
			}
			p = p->children[x - 'a'];
		}
		p->end = true;
	}
	~Trie() {
		for (auto &x : children) {
			if (x) { delete x; x = nullptr; }
		}
	}
	static const int N = 26;
	Trie *children[N];
	bool end;
};

class Solution {
public:
	vector<string> findWords(vector<vector<char>> &board, vector<string> word) {
		Trie trie;
		string path;
		vector<string> retvec;
		vis = vector<vector<bool>>(board.size(), vector<bool>(board[0].size(), false));
		for (const auto &x : word) trie.insert(x);
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				walk(board, i, j, path, &trie, retvec);
			}
		}
		return retvec;
	}
private:
	void walk (vector<vector<char>> &board, int i, int j, string &path, Trie *p, vector<string> &retvec) {
		if (i < 0 || i >= board.size()) return;
		if (j < 0 || j >= board[0].size()) return;
		if (vis[i][j] == true) return;
		if (p->children[board[i][j] - 'a'] == nullptr) return;
		static const int direct[][2] = {
			{1, 0}, {-1, 0}, {0, 1}, {0, -1}
		};
		vis[i][j] = true;
		path.push_back(board[i][j]);
		p = p->children[board[i][j] - 'a'];
		if (p->end) {
			for (auto &x : retvec) { if (x == path) goto noinsert; }
			retvec.push_back(path);
		}
noinsert:
		for (const auto &d : direct) {
			walk(board, i + d[0], j + d[1], path, p, retvec);
		}
		path.pop_back();
		vis[i][j] = false;
	}
	static vector<vector<bool>> vis;
};

vector<vector<bool>> Solution::vis;
int main() {
	vector<string> word = {"oath", "pea", "eat", "rain"};
	vector<vector<char>> board = {
		{'o', 'a', 'a', 'n'},
		{'e', 't', 'a', 'e'},
		{'i', 'h', 'k', 'r'},
		{'i', 'f', 'l', 'v'}
	};
	vector<string> retvec = Solution().findWords(board, word);
	for (const auto &x : retvec) {
		cout << x << endl;
	}
	return 0;
}
