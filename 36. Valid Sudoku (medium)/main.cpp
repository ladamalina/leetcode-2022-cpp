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
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

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

std::array<int, 10> used;

bool CheckRow(const int r, const vvc& g) {
  std::fill(RNG(used), 0);
  FOR(c, 0, 8) {
    if (g[r][c] != '.') {
      const auto d = g[r][c] - '0';
      if (used[d])
        return false;
      used[d] = 1;
    }
  }
  return true;
}

bool CheckCol(const int c, const vvc& g) {
  std::fill(RNG(used), 0);
  FOR(r, 0, 8) {
    if (g[r][c] != '.') {
      const auto d = g[r][c] - '0';
      if (used[d])
        return false;
      used[d] = 1;
    }
  }
  return true;
}

bool CheckCell(const int r0, const int c0, const vvc& g) {
  std::fill(RNG(used), 0);
  FOR(r, r0, r0+2) {
    FOR(c, c0, c0+2) {
      if (g[r][c] != '.') {
        const auto d = g[r][c] - '0';
        if (used[d])
          return false;
        used[d] = 1;
      }
    }
  }
  return true;
}

class Solution {
public:
  bool isValidSudoku(const vvc& g) {
    FOR(i, 0, 8) {
      if (!CheckRow(i, g))
        return false;
      if (!CheckCol(i, g))
        return false;
    }
    for (auto r = 0; r < 9; r += 3) {
      for (auto c = 0; c < 9; c += 3) {
        if (!CheckCell(r, c, g))
          return false;
      }
    }
    return true;
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
