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
using vvvi [[maybe_unused]] = std::vector<vvi>;
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

void DFS(int i, int j, int x, int n, const vs& g, vvvi& comp, int ci) {
  if (i < 0 || i >= n || j < 0 || j >= n || comp[i][j][x] == ci)
    return;
  comp[i][j][x] = ci;

  switch (x) {
    case 0: {
      DFS(i-1, j, 2, n, g, comp, ci);
      if (g[i][j] != '/') DFS(i, j, 1, n, g, comp, ci);
      if (g[i][j] != '\\') DFS(i, j, 3, n, g, comp, ci);
      break;
    }
    case 1: {
      DFS(i, j+1, 3, n, g, comp, ci);
      if (g[i][j] != '/') DFS(i, j, 0, n, g, comp, ci);
      if (g[i][j] != '\\') DFS(i, j, 2, n, g, comp, ci);
      break;
    }
    case 2: {
      DFS(i+1, j, 0, n, g, comp, ci);
      if (g[i][j] != '/') DFS(i, j, 3, n, g, comp, ci);
      if (g[i][j] != '\\') DFS(i, j, 1, n, g, comp, ci);
      break;
    }
    case 3: {
      DFS(i, j-1, 1, n, g, comp, ci);
      if (g[i][j] != '/') DFS(i, j, 2, n, g, comp, ci);
      if (g[i][j] != '\\') DFS(i, j, 0, n, g, comp, ci);
      break;
    }
  }
}

class Solution {
public:
  int regionsBySlashes(const vs& g) {
    const auto n = SZ(g);
    vvvi comp(n, vvi(n, vi(4)));
    auto ci = 0;
    
    FOR(i, 0, n-1) {
      FOR(j, 0, n-1) {
        FOR(x, 0, 3) {
          if (comp[i][j][x] == 0)
            DFS(i, j, x, n, g, comp, ++ci);
        }
      }
    }

    return ci;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs grid{" /","/ "};
    const auto a_out = Solution().regionsBySlashes(grid);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs grid{" /","  "};
    const auto a_out = Solution().regionsBySlashes(grid);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs grid{"/\\","\\/"};
    const auto a_out = Solution().regionsBySlashes(grid);
    assert(a_out == 5);
  
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
