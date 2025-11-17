// #pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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

constexpr ll MOD = 1e9 + 7;
constexpr int MAX_N = 1e5;
std::array<ll, MAX_N + 1> pow2;
bool init_pow2 = false;
void InitPow2() {
  if (init_pow2) return;
  pow2[0] = 1;
  FOR(p, 1, MAX_N) pow2[p] = (pow2[p-1] * 2) % MOD;
  init_pow2 = true;
}

struct LCA {
  int n_ = 0;
  const vvi& g_;

  int l_ = 0;
  int timer_ = 0;
  vi tin_, tout_, dist_;
  vvi up_;

  LCA(int n, const vvi& g, int root) : n_(n), g_(g), l_(std::ceil(std::log2(n))) {
    tin_.resize(n);
    tout_.resize(n);
    dist_.resize(n);
    up_.assign(n, vi(l_ + 1));
    DFS(root, root, 0);
  }

  bool IsAncestor(int p, int v) const {
    return tin_[p] <= tin_[v] && tout_[p] >= tout_[v];
  }

  int GetLCA(int u, int v) const {
    if (IsAncestor(u, v)) return u;
    if (IsAncestor(v, u)) return v;
    FORD(i, l_, 0) {
      if (!IsAncestor(up_[u][i], v))
        u = up_[u][i];
    }
    return up_[u][0];
  }

  int GetDist(int u, int v) const {
    const auto p = GetLCA(u, v);
    return dist_[u] + dist_[v] - 2 * dist_[p];
  }

  void DFS(int v, int p, int d) {
    tin_[v] = ++timer_;
    dist_[v] = d;
    up_[v][0] = p;
    FOR(i, 1, l_)
      up_[v][i] = up_[up_[v][i - 1]][i - 1];

    for (const auto u : g_[v]) {
      if (u != p)
        DFS(u, v, d + 1);
    }

    tout_[v] = ++timer_;
  }
};

class Solution {
public:
  vi assignEdgeWeights(const vvi& edges, const vvi& queries) {
    InitPow2();
    
    const auto n = SZ(edges) + 1;
    vvi g(n);
    for (const auto& e : edges) {
      g[e[0]-1].push_back(e[1]-1);
      g[e[1]-1].push_back(e[0]-1);
    }
    LCA lca(n, g, 0);
    vi res(SZ(queries));
    FOR(qi, 0, SZ(queries) - 1) {
      const auto u = queries[qi][0] - 1, v = queries[qi][1] - 1;
      const auto d = lca.GetDist(u, v);
      if (d) res[qi] = pow2[d-1];
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2}};
    const vvi queries{{1,1},{1,2}};
    const auto a_out = Solution().assignEdgeWeights(edges, queries);
    const vi e_out{0,1};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,2},{1,3},{3,4},{3,5}};
    const vvi queries{{1,4},{3,4},{2,5}};
    const auto a_out = Solution().assignEdgeWeights(edges, queries);
    const vi e_out{2,1,4};
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
