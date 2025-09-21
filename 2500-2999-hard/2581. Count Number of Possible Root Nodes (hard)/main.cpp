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

class Solution {
  public:
  static int rootCount(const vvi& edges, const vvi& guesses, const int k) {
    const auto n = CI(edges.size()+1);
    vvi g(n);
    for (const auto& e : edges) {
      g[e[0]].PB(e[1]);
      g[e[1]].PB(e[0]);
    }
    std::vector<std::unordered_set<int>> guesses_pv(n);
    for (const auto& guess : guesses) {
      guesses_pv[guess[0]].insert(guess[1]);
    }

    vi guesses_cnt(n);
    std::function<void(int, int, int)> dfs1 = [&](int v, int p, int root) {
      for (auto u : g[v]) {
        if (u != p) {
          if (guesses_pv[v].contains(u))
            ++guesses_cnt[root];
          dfs1(u, v, root);
        }
      }
    };
    dfs1(0, -1, 0);

    std::function<void(int, int)> dfs2 = [&](int v, int p) {
      for (auto u : g[v]) {
        if (u != p) {
          guesses_cnt[u] = guesses_cnt[v];
          if (guesses_pv[v].contains(u))
            --guesses_cnt[u];
          if (guesses_pv[u].contains(v))
            ++guesses_cnt[u];
          dfs2(u, v);
        }
      }
    };
    dfs2(0, -1);

    const auto roots_cnt = std::count_if(RNG(guesses_cnt), [&](const int x) { return x >= k; });
    return roots_cnt;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi edges{{0,1},{1,2},{1,3},{4,2}};
    const vvi guesses{{1,3},{0,1},{1,0},{2,4}};
    const int k = 3;
    assert(Solution::rootCount(edges, guesses, k) == 3);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi edges{{0,1},{1,2},{2,3},{3,4}};
    const vvi guesses{{1,0},{3,4},{2,1},{3,2}};
    const int k = 1;
    assert(Solution::rootCount(edges, guesses, k) == 5);
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
