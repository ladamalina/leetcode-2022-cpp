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

constexpr int INF = 1e9;

class Solution {
public:
  int minCost(const vvi& g, const int k) {
    m = SZ(g), n = SZ(g[0]);

    vi a;
    std::unordered_map<int, int> x_idx;
    FOR(i, 0, m-1) FOR(j, 0, n-1) a.push_back(g[i][j]);
    SORT(a);
    a.erase(std::unique(RNG(a)), a.end());
    const auto an = SZ(a);
    FOR(i, 0, an-1) x_idx[a[i]] = i;

    vvi prev(m, vi(n, INF)), curr(m, vi(n, INF));

    Solve(prev, g);
    auto ans = prev[m-1][n-1];
    
    FOR(t, 1, k) {
      vi best(an, INF);
      curr.assign(m, vi(n, INF));

      FOR(i, 0, m-1) FOR(j, 0, n-1) // best for exact values
        best[x_idx[g[i][j]]] = std::min(best[x_idx[g[i][j]]], prev[i][j]);
      
      FORD(i, an-2, 0) // Step 2: suffix-min to cover all >= values
        best[i] = std::min(best[i], best[i+1]);
      
      FOR(i, 0, m-1) FOR(j, 0, n-1) // Step 3: update with teleport landing
        curr[i][j] = std::min(prev[i][j], best[x_idx[g[i][j]]]);
      
      Solve(curr, g); // Step 4: spread via normal moves
      
      ans = curr[m-1][n-1];
      std::swap(prev, curr);
    }
    
    return ans;
  }

private:
  int m = 0, n = 0;

  void Solve(vvi& curr, const vvi& grid) const {
    curr[0][0] = 0;
    FOR(i, 0, m-1) FOR(j, 0, n-1) {
      if (i > 0) curr[i][j] = std::min(curr[i][j], curr[i-1][j] + grid[i][j]);
      if (j > 0) curr[i][j] = std::min(curr[i][j], curr[i][j-1] + grid[i][j]);
    }
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,3,3},{2,5,4},{4,3,5}};
    const auto a_out = Solution().minCost(g, 2);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,2},{2,3},{3,4}};
    const auto a_out = Solution().minCost(g, 1);
    assert(a_out == 9);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{3,1},{10,4}};
    const auto a_out = Solution().minCost(g, 7);
    assert(a_out == 4);
  
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
