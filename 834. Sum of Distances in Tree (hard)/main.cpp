//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

void DFS1(int v, int p, const vvi& g, vii& sub_tree) {
  for (const auto u : g[v]) {
    if (u == p) continue;
    DFS1(u, v, g, sub_tree);
    sub_tree[v].F += sub_tree[u].F;
    sub_tree[v].S += sub_tree[u].F + sub_tree[u].S;
  }
  sub_tree[v].F += 1;
}

void DFS2(int v, int p, const vvi& g, const vii& sub_tree, vii& par_tree) {
  if (p != -1) {
    par_tree[v].F += par_tree[p].F;
    par_tree[v].S += par_tree[p].S;

    par_tree[v].F += sub_tree[p].F - sub_tree[v].F - 1;
    par_tree[v].S += sub_tree[p].S - (sub_tree[v].F + sub_tree[v].S);

    par_tree[v].S += par_tree[v].F;
    par_tree[v].F += 1;
  }
  for (const auto u : g[v]) {
    if (u == p) continue;
    DFS2(u, v, g, sub_tree, par_tree);
  }
}

class Solution {
public:
  static vi sumOfDistancesInTree(int n, const vvi& edges) {
    vvi g(n);
    for (const auto& e : edges) {
      g[e[0]].push_back(e[1]);
      g[e[1]].push_back(e[0]);
    }

    vii sub_tree(n);
    DFS1(0, -1, g, sub_tree);

    vii par_tree(n);
    par_tree[0] = {1, 0};
    DFS2(0, -1, g, sub_tree, par_tree);

    vi res(n);
    FOR(i, 0, n-1) {
      res[i] = sub_tree[i].S + par_tree[i].S;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{0,1},{0,2},{2,3},{2,4},{2,5}};
    const auto a_out = Solution::sumOfDistancesInTree(6, edges);
    const vi e_out{8,12,6,10,10,10};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{};
    const auto a_out = Solution::sumOfDistancesInTree(1, edges);
    const vi e_out{0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi edges{{1,0}};
    const auto a_out = Solution::sumOfDistancesInTree(2, edges);
    const vi e_out{1,1};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
