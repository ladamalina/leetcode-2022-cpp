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

class DSU {
public:
  explicit DSU(int n) : p_(vi(n)), r_(vi(n, 1)) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }

  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (a == b) return;
    if (r_[a] == r_[b]) ++r_[a];
    if (r_[a] > r_[b]) p_[b] = a;
    else p_[a] = b;
  }

private:
  vi p_, r_;
};

class Solution {
public:
  vi maxPoints(const vvi& grid, const vi& queries) {
    const auto n = SZ(grid), m = SZ(grid[0]), qn = SZ(queries);
    
    vi q_ord(qn);
    std::iota(RNG(q_ord), 0);
    std::sort(RNG(q_ord), [&](const int a, const int b) { return queries[a] < queries[b]; });

    std::priority_queue<std::pair<int,ii>, std::vector<std::pair<int,ii>>, std::greater<>> pq;
    FOR(i, 0, n-1) FOR(j, 0, m-1) pq.emplace(grid[i][j], ii{i,j});
    
    DSU dsu(n * m);
    vi comp_sz(n * m, 1);
    
    vi ans(qn);
    for (const auto qi : q_ord) {
      const auto lim = queries[qi];
      while (!pq.empty() && pq.top().F < lim) {
        const auto [i, j] = pq.top().S;
        pq.pop();

        for (const auto& [ui,uj] : std::array<ii, 4>{ii{i,j+1},ii{i,j-1},ii{i-1,j},ii{i+1,j}}) {
          if (ui >= 0 && ui < n && uj >= 0 && uj < m && grid[ui][uj] < lim) {
            const auto cv = dsu.Get(i*m+j), cu = dsu.Get(ui*m+uj);
            const auto cv_sz = comp_sz[cv], cu_sz = comp_sz[cu];
            if (cv != cu) {
              dsu.Union(cv, cu);
              const auto cx = dsu.Get(i*m+j);
              comp_sz[cx] = cv_sz + cu_sz;
            }
          }
        }
      }
      ans[qi] = (grid[0][0] < lim) ? comp_sz[dsu.Get(0)] : 0;
    }
    return ans;
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
