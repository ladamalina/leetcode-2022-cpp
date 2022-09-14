#include <cassert>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  Solution() : freqs_(std::vector<int>(10, 0)) {}

  int pseudoPalindromicPaths (const TreeNode* root) {
    traverse(root);
    return pseudo_palindromic_paths_;
  }
 private:
  std::vector<int> freqs_;
  int odd_count_ = 0;
  int pseudo_palindromic_paths_ = 0;

  void traverse(const TreeNode* root) {
    PushNode(root->val);
    if (!root->left && !root->right) { // leaf
      if (odd_count_ <= 1) {
        ++pseudo_palindromic_paths_;
      }
    }
    if (root->left) {
      traverse(root->left);
    }
    if (root->right) {
      traverse(root->right);
    }
    PopNode(root->val);
  }

  void PushNode(const int value) {
    ++freqs_[value];
    if (freqs_[value] % 2) {
      ++odd_count_;
    } else {
      --odd_count_;
    }
  }

  void PopNode(const int value) {
    --freqs_[value];
    if (freqs_[value] % 2) {
      ++odd_count_;
    } else {
      --odd_count_;
    }
  }
};

int main() {
  return 0;
}
