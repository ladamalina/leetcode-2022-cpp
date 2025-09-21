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
#include <queue>
#include <random>
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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

class Solution {
 public:
  int calc(int part1, int part2, int part3) {
    return std::max(part1, std::max(part2, part3)) - std::min(part1, std::min(part2, part3));
  }
  int minimumScore(const vi& nums, const vvi& edges) {
    int n = nums.size(), cnt = 0;
    vi sum(n), in(n), out(n);
    vvi adj(n);
    for (auto& e : edges) {
      adj[e[0]].push_back(e[1]);
      adj[e[1]].push_back(e[0]);
    }
    const std::function<void(int, int)> dfs = [&](int x, int fa) {
      in[x] = cnt++;
      sum[x] = nums[x];
      for (auto& y : adj[x]) {
        if (y == fa) {
          continue;
        }
        dfs(y, x);
        sum[x] ^= sum[y];
      }
      out[x] = cnt;
    };
    dfs(0, -1);

    int res = INT_MAX;
    for (int u = 1; u < n; u++) {
      for (int v = u + 1; v < n; v++) {
        if (in[v] > in[u] && in[v] < out[u]) {
          res = std::min(res, calc(sum[0] ^ sum[u], sum[u] ^ sum[v], sum[v]));
        } else if (in[u] > in[v] && in[u] < out[v]) {
          res = std::min(res, calc(sum[0] ^ sum[v], sum[v] ^ sum[u], sum[u]));
        } else {
          res = std::min(res, calc(sum[0] ^ sum[u] ^ sum[v], sum[u], sum[v]));
        }
      }
    }
    return res;
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
