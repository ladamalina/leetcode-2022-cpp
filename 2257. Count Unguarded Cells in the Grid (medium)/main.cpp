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

class Solution {
public:
  int countUnguarded(const int m, const int n, const vvi& guards, const vvi& walls) {
    vvi grid(m, vi(n));
    for (const auto& w : walls) {
      grid[w[0]][w[1]] = -1;
    }
    for (const auto& g : guards) {
      grid[g[0]][g[1]] = -1;
    }
    for (const auto& g : guards) {
      FORD(i, g[0]-1, 0) {
        if (grid[i][g[1]] == -1)
          break;
        grid[i][g[1]] = 1;
      }
      FOR(j, g[1]+1, n-1) {
        if (grid[g[0]][j] == -1)
          break;
        grid[g[0]][j] = 1;
      }
      FOR(i, g[0]+1, m-1) {
        if (grid[i][g[1]] == -1)
          break;
        grid[i][g[1]] = 1;
      }
      FORD(j, g[1]-1, 0) {
        if (grid[g[0]][j] == -1)
          break;
        grid[g[0]][j] = 1;
      }
    }
    int res = 0;
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        res += (grid[i][j] == 0);
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi guards{{0,0},{1,1},{2,3}};
    const vvi walls{{0,1},{2,2},{1,4}};
    const auto a_out = Solution().countUnguarded(4, 6, guards, walls);
    assert(a_out == 7);
  
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
