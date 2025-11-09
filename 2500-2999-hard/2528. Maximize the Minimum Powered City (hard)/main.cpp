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

constexpr int MAX_N = 1e5;
std::array<ll, MAX_N> d;
std::array<ii, MAX_N> i_add;

bool BinCheck(const int n, const int r, const int k, const ll lim) {
  int ck = k, n_add = 0;
  bool ok = true;
  ll curr = 0;
  FOR(i, 0, n-1) {
    curr += d[i];
    if (curr >= lim) continue;
    const auto add = lim - curr;
    if (ck < add) {
      ok = false;
      break;
    }
    ck -= add;
    const auto j = std::min(i + r, n-1);
    const auto lj = std::max(j - r, 0);
    const auto rj = std::min(j + r, n-1);
    curr += add;
    d[lj] += add;
    if (rj + 1 < n) d[rj + 1] -= add;
    
    i_add[n_add++] = {j, add};
  }
  FOR(j, 0, n_add - 1) {
    const auto [p, add] = i_add[j];
    const auto lj = std::max(p - r, 0);
    const auto rj = std::min(p + r, n-1);
    d[lj] -= add;
    if (rj + 1 < n) d[rj+1] += add;
  }
  return ok;
}

class Solution {
public:
  ll maxPower(const vi& stations, const int r, const int k) {
    const auto n = SZ(stations);
    // SegTree<ll> tree(n);
    std::fill(d.begin(), d.begin() + n, 0);

    FOR(i, 0, n-1) {
      if (stations[i]) {
        const auto li = std::max(i - r, 0);
        const auto ri = std::min(i + r, n-1);
        d[li] += stations[i];
        if (ri + 1 < n) d[ri + 1] -= stations[i];
      }
    }

    ll lo = 0, hi = 1e18;
    while (lo < hi) {
      const auto mid = (lo + hi + 1) >> 1;
      const auto check = BinCheck(n, r, k, mid);
      // std::cerr << lo << '\t' << mid << '\t' << hi << '\t' << check << '\n';
      if (check) lo = mid;
      else hi = mid - 1;
    }
    return lo;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi stations{34,15,8,26,18,23};
    const auto a_out = Solution().maxPower(stations, 0, 25);
    assert(a_out == 22);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi stations{1,2,4,5,0};
    const auto a_out = Solution().maxPower(stations, 1, 2);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi stations{4,4,4,4};
    const auto a_out = Solution().maxPower(stations, 0, 3);
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
