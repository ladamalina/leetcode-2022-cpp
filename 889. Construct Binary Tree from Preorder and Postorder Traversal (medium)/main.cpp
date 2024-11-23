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
using vvl [[maybe_unused]] = std::vector<vl>;
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
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

constexpr int MAX_N = 30;
std::array<int, MAX_N+1> freq_pre, freq_post, v_pre, v_post, sub_sz;

class Solution {
public:
  TreeNode* constructFromPrePost(const vi& pre, const vi& post) {
    auto root = new TreeNode(pre[0]);
    if (pre[0] == post[0])
      return root;

    const auto pn = SZ(pre);
    
    std::fill(RNG(v_pre), -1);
    std::fill(RNG(v_post), -1);
    FOR(i, 0, SZ(pre)-1) v_pre[pre[i]] = i;
    FOR(i, 0, SZ(post)-1) v_post[post[i]] = i;

    std::fill(RNG(sub_sz), 0);
    FOR(v, 1, 30) {
      const auto pre_i = v_pre[v], post_i = v_post[v];
      if (pre_i == -1 || post_i == -1) continue;

      FOR(len, 1, 30) {
        if (pre_i+len-1 >= SZ(pre) || post_i-len+1 < 0) continue;
        std::fill(RNG(freq_pre), 0);
        std::fill(RNG(freq_post), 0);
        FOR(i, pre_i, pre_i+len-1) ++freq_pre[pre[i]];
        FOR(i, post_i-len+1, post_i) ++freq_post[post[i]];
        if (freq_pre == freq_post) sub_sz[v] = len;
      }
    }

    const std::function<void(TreeNode*)> dfs = [&](TreeNode* node) {
      if (sub_sz[node->val] == 1)
        return;
      const auto lv = pre[v_pre[node->val] + 1];
      node->left = new TreeNode(lv);
      dfs(node->left);

      if (sub_sz[node->val] > sub_sz[lv] + 1) {
        const auto ri = v_pre[node->val] + sub_sz[lv] + 1;
        node->right = new TreeNode(pre[ri]);
        dfs(node->right);
      }
    };
    dfs(root);

    return root;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
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
