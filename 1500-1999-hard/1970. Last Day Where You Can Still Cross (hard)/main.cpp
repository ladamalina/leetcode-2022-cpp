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

class DSU {
public:
  explicit DSU(int n) : p_(vi(n)), r_(vi(n, 1)) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(const int a) {
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
  int latestDayToCross(int n, int m, const vvi& cells) {
    n += 2; ++m;

    const auto encode_pos = [&](const int i, const int j) {
      return i * m + j;
    };

    // const auto decode_bit = [&](const int b) {
    //   return ii{b/m, b%m};
    // };

    vvi g(n, vi(m, 0));
    FOR(i, 0, n-1) g[i][0] = 1;

    for (const auto& c : cells)
      g[c[0]][c[1]] = 1;

    DSU dsu(n*m);
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (g[i][j] == 0) {
          const auto vc = encode_pos(i, j);
          for (const auto& u : vii{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
            if (u.F >= 0 && u.F < n && u.S >= 0 && u.S < m && g[u.F][u.S] == 0) {
              const auto uc = encode_pos(u.F, u.S);
              dsu.Union(vc, uc);
            }
          }
        }
      }
    }

    const auto n_cells = SZ(cells);
    FORD(ci, n_cells-1, 0) {
      if (dsu.Get(encode_pos(0, m-1)) == dsu.Get(encode_pos(n-1, m-1)))
        return ci + 1;

      const auto& c = cells[ci];
      const auto i = c[0], j = c[1];
      g[i][j] = 0;
      const auto vc = encode_pos(i, j);
      for (const auto& u : vii{{i-1,j},{i+1,j},{i,j-1},{i,j+1}}) {
        if (u.F >= 0 && u.F < n && u.S >= 0 && u.S < m && g[u.F][u.S] == 0) {
          const auto uc = encode_pos(u.F, u.S);
          dsu.Union(vc, uc);
        }
      }
    }
    return 0;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi cells{{1,1},{2,1},{1,2},{2,2}};
    const auto a_out = Solution().latestDayToCross(2, 2, cells);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi cells{{1,1},{1,2},{2,1},{2,2}};
    const auto a_out = Solution().latestDayToCross(2, 2, cells);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi cells{{1,2},{2,1},{3,3},{2,2},{1,1},{1,3},{2,3},{3,2},{3,1}};
    const auto a_out = Solution().latestDayToCross(3, 3, cells);
    assert(a_out == 3);
  
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
