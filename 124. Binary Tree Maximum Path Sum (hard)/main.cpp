//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

//#import <cassert>
//#import <chrono>
//#import <cmath>
//#import <fstream>
//#import <iostream>
//#import <sstream>
//#import <string>
//#import <unordered_set>
//#import <vector>

using namespace std::literals;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int maxPathSum(TreeNode* root) {
    auto res = GetMaxPathSum(root);
    return std::max(res.first, res.second);
  }
  
 private:
  std::pair<int, int> GetMaxPathSum(TreeNode* root) { // <max branch len, max subtree len>
    if (!root->left && !root->right) { // leaf
      return {root->val, root->val};
    }
    std::pair<int, int> l_res{-1e9, -1e9};
    if (root->left) l_res = GetMaxPathSum(root->left);
    std::pair<int, int> r_res{-1e9, -1e9};
    if (root->right) r_res = GetMaxPathSum(root->right);
    auto max_branch_len = std::max(root->val, root->val + std::max(l_res.first, r_res.first));
    
    auto max_subtree_len = std::max(l_res.second, r_res.second);
    max_subtree_len = std::max(root->val + l_res.first + r_res.first, max_subtree_len);
    max_subtree_len = std::max(root->val, max_subtree_len);
    max_subtree_len = std::max(l_res.first, max_subtree_len);
    max_subtree_len = std::max(r_res.first, max_subtree_len);

    return {max_branch_len, max_subtree_len};
  }
};

int main() {
  {
    auto root = new TreeNode(-6, nullptr, new TreeNode(3, new TreeNode(2), nullptr));
    int e_out = 5;
    auto a_out = Solution().maxPathSum(root);
    assert(a_out == e_out);
  }
  
  return 0;
}
