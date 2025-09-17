#include <iostream>
#include <queue>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

struct TargetNode {
  TreeNode* node;
  TreeNode* parent;
  bool is_left;
};

class Solution {
 public:

  static TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) {
      return root;
    }
    auto current_target = new TargetNode{root, nullptr, false};
    auto target = FindNodeWithParent(current_target, key);
    if (!target->node) {
      return root;
    }
    DeleteNodeFromBST(target, root);
    return root;
  }

 private:

  static TargetNode* FindNodeWithParent(TargetNode*& root, const int val) {
    if (root->node->val == val) {
      return new TargetNode{root->node, root->parent, root->is_left};
    }
    if (val < root->node->val) {
      if (root->node->left) {
        auto next_target = new TargetNode{root->node->left, root->node, true};
        return FindNodeWithParent(next_target, val);
      }
    } else { // val > root->val
      if (root->node->right) {
        auto next_target = new TargetNode{root->node->right, root->node, false};
        return FindNodeWithParent(next_target, val);
      }
    }
    return new TargetNode{nullptr, nullptr, false};
  }

  static void DeleteNodeFromBST(TargetNode*& target, TreeNode*& origin_root) {
    // Node to be deleted is the leaf: Simply remove from the tree.
    if (!target->node->left && !target->node->right) {
      if (target->node == origin_root) { // target node is the origin root
        origin_root = nullptr;
        return;
      }
      // target node is not the origin root
      if (target->is_left) {
        target->parent->left = nullptr;
        return;
      }
      target->parent->right = nullptr;
      return;
    }

    // if target node has only left child
    if (target->node->left && !target->node->right) {
      if (target->node == origin_root) { // target node is the origin root
        origin_root = target->node->left;
        return;
      }
      // target node is not the origin root
      if (target->is_left) {
        target->parent->left = target->node->left;
      } else {
        target->parent->right = target->node->left;
      }
      target->node = target->node->left;
      return;
    }

    // if target node has only right child
    if (!target->node->left && target->node->right) {
      if (target->node == origin_root) { // target node is the origin root
        origin_root = target->node->right;
        return;
      }
      // target node is not the origin root
      if (target->is_left) {
        target->parent->left = target->node->right;
      } else {
        target->parent->right = target->node->right;
      }
      target->node = target->node->right;
      return;
    }

    // Node to be deleted has two children
    auto right_subtree = new TargetNode{target->node->right, target->node, false};
    auto inorder_successor_val = FindAndRemoveSmallestNodeWithParent(right_subtree);
    target->node->val = inorder_successor_val;
  }

  static int FindAndRemoveSmallestNodeWithParent(TargetNode*& root) {
    if (!root->node->left && !root->node->right) {
      if (root->is_left) {
        root->parent->left = nullptr;
      } else {
        root->parent->right = nullptr;
      }
      return root->node->val;
    }
    if (!root->node->left) {
      if (root->is_left) {
        root->parent->left = root->node->right;
      } else {
        root->parent->right = root->node->right;
      }
      return root->node->val;
    }
    // root->node->left != nullptr
    auto next_target = new TargetNode{root->node->left, root->node, true};
    return FindAndRemoveSmallestNodeWithParent(next_target);
  }
};

std::string tree2str(const TreeNode* root) {
  if (!root) {
    return "";
  }
  std::string node_str = std::to_string(root->val);
  if (!root->left && !root->right)
    return node_str;

  std::string left_str, right_str;
  if (root->left) {
    left_str = tree2str(root->left);
    node_str += "(" + left_str + ")";
  } else {
    node_str += "()";
  }

  if (root->right) {
    right_str = tree2str(root->right);
    node_str += "(" + right_str + ")";
  }

  return node_str;
}

std::ostream& operator<< (std::ostream& out, const TreeNode* node) {
  out << tree2str(node);
  return out;
}

int main() {
  {
    auto t_n2 = TreeNode(2);
    auto t_n4 = TreeNode(4);
    auto t_n3 = TreeNode(3, &t_n2, &t_n4);
    auto t_n7 = TreeNode(7);
    auto t_n6 = TreeNode(6, nullptr, &t_n7);
    auto t_n5 = TreeNode(5, &t_n3, &t_n6);
    std::cout << "T before:\n" << &t_n5 << "\n";
    int key = 3;
    auto t_actual = Solution::deleteNode(&t_n5, key);
    std::cout << "T after deleting " << key << ":\n" << t_actual << "\n\n";
  }
  {
    auto t_n2 = TreeNode(2);
    auto t_n4 = TreeNode(4);
    auto t_n3 = TreeNode(3, &t_n2, &t_n4);
    auto t_n7 = TreeNode(7);
    auto t_n6 = TreeNode(6, nullptr, &t_n7);
    auto t_n5 = TreeNode(5, &t_n3, &t_n6);
    std::cout << "T before:\n" << &t_n5 << "\n";
    int key = 0;
    auto t_actual = Solution::deleteNode(&t_n5, key);
    std::cout << "T after deleting " << key << ":\n" << t_actual << "\n\n";
  }
  {
    auto t_n0 = TreeNode(0);
    std::cout << "T before:\n" << &t_n0 << "\n";
    int key = 0;
    auto t_actual = Solution::deleteNode(&t_n0, key);
    std::cout << "T after deleting " << key << ":\n" << t_actual << "\n\n";
  }
  {
    auto t_n40 = TreeNode(40);
    auto t_n30 = TreeNode(30, nullptr, &t_n40);
    auto t_n60 = TreeNode(60);
    auto t_n80 = TreeNode(80);
    auto t_n70 = TreeNode(70, &t_n60, &t_n80);
    auto t_n50 = TreeNode(50, &t_n30, &t_n70);
    std::cout << "T before:\n" << &t_n50 << "\n";
    int key = 50;
    auto t_actual = Solution::deleteNode(&t_n50, key);
    std::cout << "T after deleting " << key << ":\n" << t_actual << "\n\n";
  }
  {
    auto t_n2 = TreeNode(2);
    auto t_n1 = TreeNode(1, nullptr, &t_n2);
    auto t_n4 = TreeNode(4);
    auto t_n3 = TreeNode(3, &t_n1, &t_n4);
    std::cout << "T before:\n" << &t_n3 << "\n";
    int key = 1;
    auto t_actual = Solution::deleteNode(&t_n3, key);
    std::cout << "T after deleting " << key << ":\n" << t_actual << "\n\n";
  }

  return 0;
}
