#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>

using namespace std;

class Trie {
public:
	Trie() {
		for (auto &x : children) {x = nullptr;}
	}
	~Trie() {
		for (auto &x : children) {
			if (x) {
				delete x;
				x = nullptr;
			}
		}
	}

	void insert(const string &s) {
		auto p = this;
		for (const auto &c : s) {
			if (p->children[c - '0'] == nullptr) {
				p->children[c - '0'] = new Trie();
			}
			p = p->children[c - '0'];
		}
	}
	static const int N = 2;
	Trie *children[N];
};

class Solution {
public:
	int findMaximumXOR(vector<int> &nums) {
		Trie trie;
		const int M = 32;
		for (const auto & num : nums) {
			trie.insert(bitset<M>(num).to_string());
		}
		
		int max = 0;
		for (const auto &num : nums) {
			string bits(bitset<M>(num).to_string()), diff;
			auto p = &trie;
			for (auto c : bits) {
				int bit = c - '0';
				if (p->children[1 - bit]) {
					diff.push_back('1');
					p = p->children[1 - bit];
				}
				else if (p->children[bit]){
					diff.push_back('0');
					p = p->children[bit];
				}
			}
			max = std::max(static_cast<unsigned long>(max), bitset<M>(diff).to_ulong());
		}
		return max;
	}
};

int main() {
	vector<int> nums = {3, 10, 5, 25, 2, 8};
	cout << Solution().findMaximumXOR(nums);
	return 0;
}
