#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class Solution{
public:
	vector<double> averageOfLevels(TreeNode *root) {
		//deque<TreeNode *> queue;
		//deque<TreeNode *> tqueue;
		//vector<double> retvec;
		//if (root == nullptr) return retvec;
		//long long sum = 0;
		//int count = 0;
		//
		//queue.push_back(root);
		//while (queue.size() + tqueue.size()) {
		//	if (!queue.empty()) {
		//		TreeNode *node = queue.back();
		//		queue.pop_back();
		//		sum += node->val;
		//		count += 1;
		//		if (node->left) tqueue.push_back(node->left);
		//		if (node->right) tqueue.push_back(node->right);
		//	}
		//	else {
		//		retvec.push_back((double)sum / count);
		//		sum = 0;
		//		count = 0;
		//		std::swap(queue, tqueue);
		//	}
		//}
		//retvec.push_back((double)sum /count);
		//return retvec;

		deque<TreeNode *> queue;
		vector<double> retvec;
		if (root == nullptr) return retvec;
		long long sum = 0;
		int count = 0;

		queue.push_back(root);
		while (!queue.empty()) {
			deque<TreeNode *> tmpvec;
			while (!queue.empty()) {
				TreeNode *node = queue.front();
				queue.pop_front();
				sum += node->val; ++count;
				if (node->left) tmpvec.push_back(node->left);
				if (node->right) tmpvec.push_back(node->right);
			}
			retvec.push_back((double)sum / count);
			sum = 0; count = 0;
			std::swap(queue, tmpvec);
		}
		return retvec;
	}
};

int main() {
	TreeNode node1(3);
	TreeNode node2(9);
	TreeNode node3(20);
	node1.left = &node2;
	node1.right = &node3;
	TreeNode node4(15);
	TreeNode node5(7);
	node3.left = &node4;
	node3.right = &node5;
	vector<double> vec = Solution().averageOfLevels(&node1);
	for (auto x : vec) cout << x << " ";
	return 0;
}
