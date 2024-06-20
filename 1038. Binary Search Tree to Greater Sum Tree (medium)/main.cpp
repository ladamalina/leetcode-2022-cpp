// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
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

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

constexpr int MAX_N = 100;

class Solution {
public:
  TreeNode* bstToGst(TreeNode* root) {
    vi vals(MAX_N+1);
    DFS(root, vals);
    
    vi ssum(MAX_N+1);
    ssum[MAX_N] = vals[MAX_N];
    FORD(i, MAX_N-1, 0) ssum[i] = vals[i] + ssum[i+1];
    Rec(root, ssum);
    
    return root;
  }

private:
  void DFS(TreeNode* root, vi& vals) {
    vals[root->val] = root->val;
    if (root->left) DFS(root->left, vals);
    if (root->right) DFS(root->right, vals);
  }

  void Rec(TreeNode* root, const vi& ssum) {
    root->val = ssum[root->val];
    if (root->left) Rec(root->left, ssum);
    if (root->right) Rec(root->right, ssum);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto root = new TreeNode(0, nullptr, new TreeNode(1));
    const auto a_out = Solution().bstToGst(root);
    assert(a_out->val == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto n8 = new TreeNode(8);
    auto n7 = new TreeNode(7, nullptr, n8);
    auto n5 = new TreeNode(5);
    auto n6 = new TreeNode(6, n5, n7);

    auto n3 = new TreeNode(3);
    auto n2 = new TreeNode(2, nullptr, n3);
    auto n0 = new TreeNode(0);
    auto n1 = new TreeNode(1, n0, n2);

    auto n4 = new TreeNode(4, n1, n6);
    
    const auto a_out = Solution().bstToGst(n4);
    assert(a_out->val == 30);
  
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
