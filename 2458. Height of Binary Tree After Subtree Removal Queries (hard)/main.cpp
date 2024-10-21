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
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

constexpr int MAX_N = 1e5;
std::array<int, MAX_N+1> t_in{}, t_out{}, dep{};
int t;
std::array<int, MAX_N*2> path{}, pmax_dep{}, smax_dep{};
int n_path;

class Solution {
public:
  vi treeQueries(TreeNode* root, const vi& queries) {
    t = 0;
    n_path = 0;
    DFS(root, 0);

    FOR(i, 0, n_path-1) {
      pmax_dep[i] = (i == 0) ? dep[path[i]] : std::max(pmax_dep[i-1], dep[path[i]]);
    }
    FORD(i, n_path-1, 0) {
      smax_dep[i] = (i == n_path-1) ? dep[path[i]] : std::max(smax_dep[i+1], dep[path[i]]);
    }

    const auto qn = SZ(queries);
    vi res(qn);
    FOR(qi, 0, qn-1) {
      const auto v = queries[qi];
      const auto pmax = (t_in[v] == 0) ? 0 : pmax_dep[t_in[v]-1];
      const auto smax = (t_out[v] == n_path-1) ? 0 : smax_dep[t_out[v]+1];
      res[qi] = std::max(pmax, smax);
    }

    return res;
  }

private:
  void DFS(TreeNode* root, int d) {
    if (!root)
      return;
    dep[root->val] = d;
    t_in[root->val] = t++;
    path[n_path++] = root->val;
    DFS(root->left, d+1);
    DFS(root->right, d+1);
    t_out[root->val] = t++;
    path[n_path++] = root->val;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto root = new TreeNode(5,
      new TreeNode(8,
        new TreeNode(2, new TreeNode(4), new TreeNode(6)),
        new TreeNode(1)
      ),
      new TreeNode(9, new TreeNode(3), new TreeNode(7)
      )
    );
    const vi queries{3,2,4,8};
    const vi e_out{3,2,3,2};
    
    const auto a_out = Solution().treeQueries(root, queries);
    assert(a_out == e_out);
  
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
