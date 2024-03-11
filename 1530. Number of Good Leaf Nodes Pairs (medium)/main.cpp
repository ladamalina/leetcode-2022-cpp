#include <bits/stdc++.h>

/*#include <algorithm>
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>*/

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
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  int countPairs(TreeNode* root, int distance) {
    std::vector<std::vector<int>> pars;

    auto timer = 0;
    std::vector<int> par;
    const std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
      if (!node) return;
      par.push_back(++timer);
      dfs(node->left);
      dfs(node->right);
      if (!node->left && !node->right)
        pars.push_back(par);
      par.pop_back();
    };
    dfs(root);

    auto res = 0;
    const auto pars_n = static_cast<int>(pars.size());
    for (auto i=0; i<pars_n; ++i) {
      const auto ni = static_cast<int>(pars[i].size());
      for (auto j=i+1; j<pars_n; ++j) {
        const auto nj = static_cast<int>(pars[j].size());

        auto ai=0, aj=0;
        while (ai<ni && aj<nj && pars[i][ai]==pars[j][aj]) {
          ++ai; ++aj;
        }
        const auto len = (ni-ai) + (nj-aj);
        res += (len<=distance);
      }
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto root = new TreeNode(1, new TreeNode(2, nullptr, new TreeNode(4)), new TreeNode(3));
    const auto a_out = Solution().countPairs(root, 3);
    assert(a_out == 1);
  
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
