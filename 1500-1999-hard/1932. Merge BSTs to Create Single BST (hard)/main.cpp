// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

void BuildDFS(TreeNode* root, int i, const std::vector<TreeNode*>& trees,
    const std::unordered_map<int, int>& root_ids, vb& used) {
  used[i] = true;
  if (root->left && root_ids.contains(root->left->val)) {
    const auto next_i = root_ids.at(root->left->val);
    root->left = trees[next_i];
    BuildDFS(root->left, next_i, trees, root_ids, used);
  }
  if (root->right && root_ids.contains(root->right->val)) {
    const auto next_i = root_ids.at(root->right->val);
    root->right = trees[next_i];
    BuildDFS(root->right, next_i, trees, root_ids, used);
  }
}

bool CheckBST(const TreeNode* root, int min_v, int max_v) {
  if (root->val <= min_v || root->val >= max_v)
    return false;
  const auto check_l = !root->left || CheckBST(root->left, min_v, root->val);
  const auto check_r = !root->right || CheckBST(root->right, root->val, max_v);
  return check_l && check_r;
}

class Solution {
public:
  TreeNode* canMerge(const std::vector<TreeNode*>& trees) {
    std::unordered_set<int> init_root_vals;
    std::unordered_map<int, int> root_ids;
    std::unordered_set<int> leaf_vals;
    FOR(i, 0, CI(trees.size())-1) {
      init_root_vals.insert(trees[i]->val);
      root_ids[trees[i]->val] = i;
    }
    for (const auto root : trees) {
      if (root->left) {
        init_root_vals.erase(root->left->val);
        if (leaf_vals.contains(root->left->val))
          return nullptr;
        leaf_vals.insert(root->left->val);
      }
      if (root->right) {
        init_root_vals.erase(root->right->val);
        if (leaf_vals.contains(root->right->val))
          return nullptr;
        leaf_vals.insert(root->right->val);
      }
    }
    if (init_root_vals.size() != 1)
      return nullptr;
    
    vb used(trees.size());
    const auto i0 = root_ids.at(*init_root_vals.begin());
    BuildDFS(trees[i0], i0, trees, root_ids, used);

    const auto unused_cnt = std::count(RNG(used), false);
    if (unused_cnt) return nullptr;
    
    const auto is_valid_bfs = CheckBST(trees[i0], INT_MIN, INT_MAX);
    return is_valid_bfs ? trees[i0] : nullptr;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<TreeNode*> trees{
      new TreeNode(2, nullptr, new TreeNode(3)),
      new TreeNode(1, nullptr, new TreeNode(3)),
      new TreeNode(3, new TreeNode(2), nullptr),
    };
    const auto a_out = Solution().canMerge(trees);
    assert(!a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
