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

constexpr int MAX_M = 1e5;
std::array<ll, MAX_M> lc, rc;

class Solution {
public:
  ll maxPoints(const vvi& g) {
    const auto n = SZ(g);
    const auto m = SZ(g[0]);
    if (n == 1) {
      return *std::max_element(RNG(g[0]));
    } // n >= 2
    if (m == 1) {
      ll res = 0;
      FOR(i, 0, n-1) {
        res += g[i][0];
      }
      return res;
    } // m >= 2

    FOR(j, 0, m-1) {
      lc[j] = -(m-1-j);
      rc[j] = -j;
    }
    
    ll max_res = LLONG_MIN;
    FOR(i, 0, n-1) {
      ll max_lc = LLONG_MIN;
      std::multiset<ll> rc_set(rc.begin(), rc.begin()+m);
      FOR(j, 0, m-1) {
        max_lc = std::max(max_lc, lc[j]);
        rc_set.erase(rc_set.find(rc[j]));
        auto res = max_lc + (m-1-j);
        if (!rc_set.empty())
          res = std::max(res, *rc_set.rbegin()+j);
        lc[j] = g[i][j] + res - (m-1-j);
        rc[j] = g[i][j] + res - j;
        if (i == n-1)
          max_res = std::max(max_res, g[i][j] + res);
      }
    }

    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,2,3},{1,5,1},{3,1,1}};
    const auto a_out = Solution().maxPoints(g);
    assert(a_out == 9);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi g{{1,5},{2,3},{4,2}};
    const auto a_out = Solution().maxPoints(g);
    assert(a_out == 11);
  
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
