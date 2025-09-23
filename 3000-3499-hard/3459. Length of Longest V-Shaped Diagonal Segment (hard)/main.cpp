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
using vvvvi = std::vector<vvvi>;
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

const std::array<ii, 4> DIRS{ii{1,1}, ii{1,-1}, ii{-1,-1}, ii{-1,1}};

int NextX (const int x) {
  return x == 1 ? 2 : 2 - x;
}

class Solution {
public:
  int lenOfVDiagonal(const vvi& g) {
    const auto n = SZ(g), m = SZ(g[0]);
    vvvvi dp(2, vvvi(4, vvi(n, vi(m, -1))));
    const std::function<int(int,int,int,int)> rec = [&](int ra, int di, int i, int j) {
      auto& res = dp[ra][di][i][j];
      if (res != -1) return res;
      res = 1;
      const auto nx = NextX(g[i][j]);
      { // go the same dir
        const auto ni = i + DIRS[di].F, nj = j + DIRS[di].S;
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && g[ni][nj] == nx) {
          res = std::max(res, 1 + rec(ra, di, ni, nj));
        }
      }
      if (ra) { // rotate if allowed
        const auto nd = (di + 1) % 4;
        const auto ni = i + DIRS[nd].F, nj = j + DIRS[nd].S;
        if (ni >= 0 && ni < n && nj >= 0 && nj < m && g[ni][nj] == nx) {
          res = std::max(res, 1 + rec(0, nd, ni, nj));
        }
      }
      return res;
    };
    auto max_res = 0;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (g[i][j] == 1) {
          FOR(di, 0, 3) {
            const auto res = rec(1, di, i, j);
            max_res = std::max(max_res, res);
          }
        }
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{2,2,1,2,2},{2,0,2,2,0},{2,0,1,1,0},{1,0,2,2,2},{2,0,0,2,2}};
    const auto a_out = Solution().lenOfVDiagonal(g);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{2,2,2,2,2},{2,0,2,2,0},{2,0,1,1,0},{1,0,2,2,2},{2,0,0,2,2}};
    const auto a_out = Solution().lenOfVDiagonal(g);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{1,2,2,2,2},{2,2,2,2,0},{2,0,0,0,0},{0,0,2,2,2},{2,0,0,2,0}};
    const auto a_out = Solution().lenOfVDiagonal(g);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{1}};
    const auto a_out = Solution().lenOfVDiagonal(g);
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
