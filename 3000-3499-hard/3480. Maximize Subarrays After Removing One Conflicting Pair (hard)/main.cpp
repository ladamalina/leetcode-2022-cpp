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

class Solution {
public:
  ll maxSubarrays(const int n, vvi& ps) {
    const auto n_ps = SZ(ps);
    std::set<ii> ri; // <r, i>
    std::priority_queue<ii, vii, std::greater<>> pq_li; // <l,i>
    FOR(i, 0, n_ps - 1) {
      if (ps[i][0] > ps[i][1]) std::swap(ps[i][0], ps[i][1]);
      ri.emplace(ps[i][1], i);
      pq_li.emplace(ps[i][0], i);
    }
    vl d(n_ps);
    FOR(l, 1, n) {
      while (!pq_li.empty() && pq_li.top().F < l) {
        const auto i = pq_li.top().S;
        pq_li.pop();
        ri.erase({ps[i][1], i});
      }
      if (ri.empty()) {
        const auto len = n + 1 - l;
        d[0] += len;
      } else {
        const auto [mnr, mni] = *ri.begin();
        const auto next_mnr = SZ(ri) == 1 ? n + 1 : std::next(ri.begin())->F;
        if (mnr == next_mnr) {
          const auto len = mnr - l;
          d[0] += len;
        } else {
          const auto len = mnr - l, next_len = next_mnr - l;
          d[0] += len;
          d[mni] += - len + next_len;
          if (mni + 1 < n_ps) d[mni+1] += - next_len + len;
        }
      }
    }
    ll res = 0, max_res = 0;
    FOR(i, 0, n_ps - 1) {
      res += d[i];
      max_res = std::max(max_res, res);
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi pairs{{2,3},{1,4}};
    const auto a_out = Solution().maxSubarrays(4, pairs);
    assert(a_out == 9);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi pairs{{1,2},{2,5},{3,5}};
    const auto a_out = Solution().maxSubarrays(5, pairs);
    assert(a_out == 12);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi pairs{{10,5},{3,8}};
    const auto a_out = Solution().maxSubarrays(10, pairs);
    assert(a_out == 50);
  
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
