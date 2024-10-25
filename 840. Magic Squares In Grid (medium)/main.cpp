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

std::array<int, 10> mp;

bool CheckSq(const int i, const int j, const vvi& g) {
  const auto r = g[i][j]+g[i][j+1]+g[i][j+2];
  if (g[i+1][j]+g[i+1][j+1]+g[i+1][j+2] != r || g[i+2][j]+g[i+2][j+1]+g[i+2][j+2] != r)
    return false;
  const auto c = g[i][j]+g[i+1][j]+g[i+2][j];
  if (g[i][j+1]+g[i+1][j+1]+g[i+2][j+1] != c || g[i][j+2]+g[i+1][j+2]+g[i+2][j+2] != c)
    return false;
  if (g[i][j]+g[i+2][j+2] != g[i+2][j]+g[i][j+2])
    return false;

  std::fill(RNG(mp), 0);
  FOR(i1, i, i+2) {
    FOR(j1, j, j+2) {
      if (1 <= g[i1][j1] && g[i1][j1] <= 9)
        mp[g[i1][j1]] = 1;
      else
        return false;
    }
  }
  const auto s = std::accumulate(RNG(mp), 0);
  
  return s == 9;
}

class Solution {
public:
  int numMagicSquaresInside(const vvi& grid) {
    auto res = 0;
    FOR(i, 0, SZ(grid)-3) {
      FOR(j, 0, SZ(grid[i])-3) {
        res += CheckSq(i, j, grid);
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
