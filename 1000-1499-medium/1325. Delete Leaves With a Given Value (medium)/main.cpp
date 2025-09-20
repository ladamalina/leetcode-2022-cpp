// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
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

class Solution {
public:
  TreeNode* removeLeafNodes(TreeNode* root, int target) {
    removeLeaves(root, target);
    if (!root->left && !root->right && root->val == target) {
      return nullptr;
    }
    return root;
  }

private:
  bool removeLeaves(TreeNode* root, int target) {
    if (root->left && removeLeaves(root->left, target)) {
      // delete root->left;
      root->left = nullptr;
    }
    if (root->right && removeLeaves(root->right, target)) {
      // delete root->right;
      root->right = nullptr;
    }
    if (!root->left && !root->right) {
      return root->val == target;
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
    /*{
        const auto start_t = std::chrono::high_resolution_clock::now();

        vvi g{{0,6,0},{5,8,7},{0,9,0}};
        const auto a_out = Solution::getMaximumGold(g);
        assert(a_out == 24);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }*/
    std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
    TestSolution();
#endif
    return 0;
}
