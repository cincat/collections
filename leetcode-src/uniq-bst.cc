#include <iostream>
#include <vector>
#include <stack>

using namespace std;


//   Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 

class Solution {
public:
    int numTrees(int n) {
        if (n== 0 || n == 1) return 1;
        int result = 0;
        for (int i = 0; i < n; i++) {
            result += numTrees(i) * numTrees(n - i - 1);
        }
        return result;
    }

    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return vector<TreeNode*>();
        if (n == 1) return vector<TreeNode*>(1, new TreeNode(1));

        vector<TreeNode*> result;

        for (int i = 0; i < n; i++) {
            vector<TreeNode*> subleft = generateTrees(i);
            vector<TreeNode*> subright = generateTrees(n - i - 1);
            
            if (subleft.empty()) subleft.push_back(nullptr);
            if (subright.empty()) subright.push_back(nullptr);

            for (auto node : subright) {
                stack<TreeNode*> stack;
                if (node) stack.push(node);
                while (stack.empty() == false) {
                    auto tmp = stack.top();
                    if (tmp->left) stack.push(tmp->left);
                    else {
                        tmp->val += (i + 1);
                        stack.pop();
                        if (tmp->right) stack.push(tmp->right);
                    }
                }
            }
            
            for (auto left : subleft) {
                for (auto right : subright) {
                    TreeNode *root = new TreeNode(i + 1);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
            
        }
        return result;
     }
};

int main() {
    std::cout << Solution().numTrees(3) << std::endl;
    auto trees = Solution().generateTrees(3);
    std::cout << trees.size() << std::endl;
}