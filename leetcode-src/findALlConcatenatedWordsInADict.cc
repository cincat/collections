#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Trie {
public:
	Trie() {
		for (auto &child : children) child = nullptr;
		end = false;
	}
	~Trie() {
		for (auto &child : children) {
			if (child) {
				delete child;
				child = nullptr;
			}
		}
	}
	void insert(const string &s) {
		if (s.empty()) return;
		auto p = this;
		for (const auto &c : s) {
			if (p->children[c - 'a'] == nullptr) {
				p->children[c - 'a'] = new Trie();
			}
			p = p->children[c - 'a'];
		}
		p->end = true;
	}

	static const int N = 26;
	bool end;
	Trie *children[N];
};

class Solution {
public:
	vector<string> findAllConcatenatedWordsInADict(vector<string> &words) {
		vector<string> vec;
		for (const auto &word : words) { trie.insert(word); }
		for (const auto &word : words) {
			if (isConcatenated(word) > 1) {vec.push_back(word);}
		}
		return vec;
	}

	int isConcatenated(const string &s) {
		auto p = &trie;
		for (int i = 0; i < s.size(); i++) {
			if (p->end) {
				int t = isConcatenated(s.substr(i));
				if (t != -1) {
					return 1 + t;
				}
			}
			if (p->children[s[i] - 'a'] == nullptr) {
				return -1;
			}
			p = p->children[s[i] - 'a'];
		}	
		return p->end ? 1 : -1;
	}
	Trie trie;
};

int main() {
	//vector<string> words = {"a", "b", "ab", "abc"};
	vector<string> words;	
	fstream fin("in");

	string s;
	getline(fin, s);
	int a = 0, b = 0;
	while ((b = s.find("\"", a)) != string::npos) {
		a = s.find("\"", ++b);
		string str(s.substr(b, a++ - b));
		words.push_back(str);
		//cout << str << endl;
	}
	for (const auto &x : Solution().findAllConcatenatedWordsInADict(words)) {
		cout << x << endl;
	}
	return 0;
}
