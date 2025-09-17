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
using vvl [[maybe_unused]] = std::vector<vl>;
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

bool BinCheck(const int lim, const vvi& g, const int k) {
  const auto n = SZ(g);
  auto cnt_lt = 0, cnt_eq = 0;
  FOR(i, 0, n-1) {
    const auto lo_it = std::lower_bound(g[i].begin(), g[i].end(), lim);
    const auto up_it = std::upper_bound(lo_it, g[i].end(), lim);
    cnt_lt += CI(lo_it - g[i].begin());
    cnt_eq += CI(up_it - lo_it);
    if (cnt_lt + cnt_eq >= k)
      return true;
  }
  return false;
}

class Solution {
public:
  int kthSmallest(const vvi& g, const int k) {
    ll lo = -1e9, hi = 1e9;
    while (lo < hi) {
      const auto mid = (lo + hi) >= 0 ? (lo + hi) / 2 : (lo + hi) / 2 - 1;
      if (BinCheck(mid, g, k))
        hi = mid;
      else
        lo = mid + 1;
    }
    return lo;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g = {{1,5,9},{10,11,13},{12,13,15}};
    const auto a_out = Solution().kthSmallest(g, 8);
    assert(a_out == 13);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g = {{-5}};
    const auto a_out = Solution().kthSmallest(g, 1);
    assert(a_out == -5);
  
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
