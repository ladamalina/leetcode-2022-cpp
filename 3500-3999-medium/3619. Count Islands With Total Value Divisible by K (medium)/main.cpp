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

constexpr std::array<ii, 4> DIRS{ii{-1,0}, ii{0,1}, ii{1,0}, ii{0,-1}};

void DFS(const int i, const int j, const vvi& g, vvi& vis, ll& sum) {
  if (i < 0 || j < 0 || i >= SZ(g) || j >= SZ(g[0]) || g[i][j] == 0 || vis[i][j] != 0)
    return;
  vis[i][j] = 1;
  sum += g[i][j];
  for (const auto& [di, dj] : DIRS) {
    DFS(i + di, j + dj, g, vis, sum);
  }
}

class Solution {
public:
  int countIslands(const vvi& g, const int k) {
    const auto m = SZ(g), n = SZ(g[0]);
    vvi vis(m, vi(n));
    int res = 0;
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (g[i][j] != 0 && vis[i][j] == 0) {
          ll sum = 0;
          DFS(i, j, g, vis, sum);
          res += (sum % k == 0);
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{0,1000000}};
    const auto a_out = Solution().countIslands(g, 1000000);
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
