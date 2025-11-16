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

constexpr int MAX_N = 1000;
std::array<int, MAX_N> p_, r_;

class DSU {
public:
  explicit DSU(const int n) /*: p_(vi(n)), r_(vi(n, 1)), cnt_(n)*/ {
    // std::iota(p_.begin(), p_.end(), 0);
    std::iota(p_.begin(), p_.begin() + n, 0);
    std::fill(r_.begin(), r_.begin() + n, 1);
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
    // --cnt_;
  }

  // [[nodiscard]] int Count() const { return cnt_; }

// private:
  // vi p_, r_;
  // int cnt_ = 0;
};

class Solution {
public:
  vb friendRequests(const int n, const vvi& rs, const vvi& qs) {
    DSU dsu(n);
    vb res(SZ(qs));
    std::set<ii> friends;
    FOR(qi, 0, SZ(qs) - 1) {
      const auto u = qs[qi][0], v = qs[qi][1];
      if (friends.contains({std::min(u, v), std::max(u, v)})) {
        res[qi] = true;
        continue;
      }
      const auto up = dsu.Get(u), vp = dsu.Get(v);
      bool ok = true;
      for (const auto& r : rs) {
        const auto p1 = dsu.Get(r[0]), p2 = dsu.Get(r[1]);
        if ((p1 == up && p2 == vp) || (p1 == vp && p2 == up)) {
          ok = false;
          break;
        }
      }
      if (ok) {
        res[qi] = true;
        dsu.Union(u, v);
        friends.emplace(std::min(u, v), std::max(u, v));
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
