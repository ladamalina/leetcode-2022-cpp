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
using vd = std::vector<double>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

class DSUMin {
public:
  explicit DSUMin(const int n) : p_(vi(n)) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(const int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }

  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (a == b) return;
    if (a > b) p_[a] = b;
    else p_[b] = a;
  }

private:
  vi p_;
};

class DSUMax {
public:
  explicit DSUMax(const int n) : p_(vi(n)) {
    std::iota(p_.begin(), p_.end(), 0);
  }

  int Get(const int a) {
    return p_[a] = (a == p_[a] ? a : Get(p_[a]));
  }

  void Union(int a, int b) {
    a = Get(a);
    b = Get(b);
    if (a == b) return;
    if (a < b) p_[a] = b;
    else p_[b] = a;
  }

private:
  vi p_;
};

class Solution {
public:
  vd getCollisionTimes(const vvi& cars) {
    const auto n = SZ(cars);
    vd res(n, -1);

    DSUMin dsu_min(n);
    DSUMax dsu_max(n);
    
    vd t_idx(n); // when i-th car collides with next car
    std::set<std::pair<double, int>> t_idx_set;
    FOR(i, 0, n - 2) {
      if (cars[i][1] > cars[i + 1][1]) {
        const auto t = CD(cars[i][0] - cars[i + 1][0]) / (cars[i + 1][1] - cars[i][1]);
        t_idx[i] = t;
        t_idx_set.emplace(t, i);
      }
    }
    while (!t_idx_set.empty()) {
      const auto [col_t, i] = *t_idx_set.begin();
      t_idx_set.erase(t_idx_set.begin());
      res[i] = col_t;
      dsu_min.Union(i, i + 1);
      dsu_max.Union(i, i + 1);
      const auto min_i = dsu_min.Get(i);
      if (min_i > 0) {
        const auto next_i = dsu_max.Get(i);
        const auto next_p = cars[next_i][0], next_v = cars[next_i][1];
        const auto prev_i = min_i - 1;
        const auto prev_p = cars[prev_i][0], prev_v = cars[prev_i][1];
        if (prev_v > next_v) {
          t_idx_set.erase({t_idx[prev_i], prev_i});
          const auto prev_t = CD(next_p - prev_p) / (prev_v - next_v);
          t_idx_set.emplace(prev_t, prev_i);
          t_idx[prev_i] = prev_t;
        }
      }
    }
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  constexpr double EPS = 1e-5;
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi cars{{3,4},{5,4},{6,3},{9,1}};
    const auto a_out = Solution().getCollisionTimes(cars);
    const vd e_out{2.00000,1.00000,1.50000,-1.00000};
    assert(SZ(a_out) == SZ(e_out));
    FOR(i, 0, SZ(a_out) - 1) {
      const auto a = a_out[i], e = e_out[i];
      assert(std::abs(a - e) <= EPS);
    }
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi cars{{1,2},{2,1},{4,3},{7,2}};
    const auto a_out = Solution().getCollisionTimes(cars);
    const vd e_out{1.00000,-1.00000,3.00000,-1.00000};
    assert(SZ(a_out) == SZ(e_out));
    FOR(i, 0, SZ(a_out) - 1) {
      const auto a = a_out[i], e = e_out[i];
      assert(std::abs(a - e) <= EPS);
    }
  
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
