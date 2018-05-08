#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

class TrieNode {
friend class TrieTree;
public:
	TrieNode() {
		for (auto &x : children) {x = nullptr;}
	}
	~TrieNode() {
		TrieNode::clearNode(this);
	}
private:
	static void clearNode(TrieNode* node) {
		if (node == nullptr) return;
		for (auto &x : node->children) {
			if (x) {
				delete x; 
				x = nullptr;
			}
		}
	}
	static const int ALPHABET_NUM = 26;
	TrieNode *children[ALPHABET_NUM];
};

class TrieTree {
public:
	TrieTree() : root(nullptr) {root = new TrieNode();}
	void insert(const char *word) {
		if (query(word).size()) return;
		TrieNode *node = root;
		for (const char *p = word; *p; p++) {
			if (node->children[*p - 'a'] == nullptr) {
				node->children[*p - 'a'] = new TrieNode();
			}
			node = node->children[*p - 'a'];
		}
		TrieNode::clearNode(node);
	}
	string query(const char *word) {
		TrieNode *node = root;
		const char *p = word;
		for (;*p && node->children[*p - 'a']; p++) {
			node = node->children[*p - 'a'];
		}
		for (auto x : node->children) { if (x) return string(); }
		return string(word, p - word);
	}
	~TrieTree() { if(root) delete root;}
private:
	TrieNode *root;
};

class Solution {
public:
	string replaceWords(vector<string> &dict, string sentence) {
		TrieTree tree;
		for (auto &x : dict) {tree.insert(x.c_str());}
		istringstream in(sentence);
		string retstr;
		for (string s; in >> s; ) {
			string root = tree.query(s.c_str());
			if (root.size()) s = root;
			retstr.append(s + " ");
		}
		retstr.erase(retstr.size() - 1);
		return retstr;
	}
};

int main() {
	//vector<string> dict = {"cat", "bat", "rat"};
	//cout << Solution().replaceWords(dict, "the cattle was rattled by the battery");
	string s;
	ifstream fin("in");
	getline(fin, s);
	vector<string> dict;
	decltype(s.size()) a = 0, b = 0;
	while ((a = s.find("\"", a)) != string::npos) {
		b = s.find("\"", a + 1);
		dict.push_back(string(s.substr(a + 1, b - a - 1)));
		a = b + 1;
	}
	getline(fin, s);
	cout << Solution().replaceWords(dict, s.substr(1, s.size() - 2));
	return 0;
}
