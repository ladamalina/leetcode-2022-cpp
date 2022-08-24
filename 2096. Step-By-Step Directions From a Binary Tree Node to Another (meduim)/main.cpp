#include <algorithm>
#include <iostream>
#include <list>
#include <string>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

typedef std::list<std::pair<TreeNode*, char>> Path;

class Solution {
public:
  std::string getDirections(TreeNode* root, int startValue, int destValue) {
    findPathToNode(root, startValue, start_val_path, true);
    findPathToNode(root, destValue, dest_val_path, true);

    std::string direction;
    direction.reserve(36);

    // find the lowest common parent
    auto start_val_it = start_val_path.begin();
    auto dest_val_it = dest_val_path.begin();
    while (start_val_it->first->val == dest_val_it->first->val) {
//      std::cout << start_val_it->first->val << " == " << dest_val_it->first->val << "\n";
      start_val_path.erase(start_val_path.begin(), start_val_it);
      dest_val_path.erase(dest_val_path.begin(), dest_val_it);

      start_val_it = std::next(start_val_it);
      dest_val_it = std::next(dest_val_it);
      if (start_val_it == start_val_path.end() || dest_val_it == dest_val_path.end())
        break;
    }
    auto start_common_parent = std::prev(start_val_it);
    auto dest_common_parent = std::prev(dest_val_it);

//    std::cout << "start_common_parent: " << start_common_parent->first->val << "\n";
//    std::cout << "dest_common_parent: " << dest_common_parent->first->val << "\n";

    std::for_each(start_common_parent, std::prev(start_val_path.end()),
                  [&direction](std::pair<TreeNode*, char>& step){ direction += 'U'; });

    std::for_each(std::next(dest_common_parent), dest_val_path.end(),
                  [&direction](std::pair<TreeNode*, char>& step){ direction += step.second; });

    return direction;
  }

  bool findPathToNode(TreeNode* root, int& node_val, Path& path_to_append, bool to_left) {
    if (root->val == node_val) {
      if (to_left)
        path_to_append.push_back({root, 'L'});
      else
        path_to_append.push_back({root, 'R'});
      return true;
    }

    if (root->left != nullptr) {
      auto found_on_left = findPathToNode(root->left, node_val, path_to_append, true);
      if (found_on_left) {
        if (to_left)
          path_to_append.push_front({root, 'L'});
        else
          path_to_append.push_front({root, 'R'});
        return true;
      }
    }

    if (root->right != nullptr) {
      auto found_on_right = findPathToNode(root->right, node_val, path_to_append, false);
      if (found_on_right) {
        if (to_left)
          path_to_append.push_front({root, 'L'});
        else
          path_to_append.push_front({root, 'R'});
        return true;
      }
    }

    // leaf or path not found in subtree
    return false;
  }
private:
  Path start_val_path;
  Path dest_val_path;
};

int main() {
  auto t1_3 = TreeNode(3);
  auto t1_1 = TreeNode(1, &t1_3, nullptr);
  auto t1_6 = TreeNode(6);
  auto t1_4 = TreeNode(4);
  auto t1_2 = TreeNode(2, &t1_6, &t1_4);
  auto t1_5 = TreeNode(5, &t1_1, &t1_2);
  std::string expected_directions1 = "UURL";
  std::string actual_directions1 = Solution().getDirections(&t1_5, 3, 6);
  assert(actual_directions1 == expected_directions1);

  auto t2_1 = TreeNode(1);
  auto t2_2 = TreeNode(2, &t2_1, nullptr);
  std::string expected_directions2 = "L";
  std::string actual_directions2 = Solution().getDirections(&t2_2, 2, 1);
  assert(actual_directions2 == expected_directions2);

  return 0;
}
