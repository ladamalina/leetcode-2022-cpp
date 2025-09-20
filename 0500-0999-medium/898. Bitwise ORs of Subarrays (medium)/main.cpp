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

constexpr int MAX_B = 29;

class Solution {
public:
  int subarrayBitwiseORs(vi& arr) {
    const auto n = SZ(arr);
    vvi b_psum(MAX_B + 1, vi(n));
    FOR(b, 0, MAX_B) {
      auto& psum = b_psum[b];
      FOR(i, 0, n-1) psum[i] = ((arr[i] & (1 << b)) ? 1 : 0) + (i > 0 ? psum[i-1] : 0);
    }
    std::unordered_set<int> or_set;
    std::priority_queue<ii, vii, std::greater<>> pq; // <i, b>
    FOR(i, 0, n-1) {
      FOR(b, 0, MAX_B) {
        const auto& psum = b_psum[b];
        const auto base = i > 0 ? psum[i-1] : 0;
        const auto beg = psum[i] - base, end = psum[n-1] - base;
        if (beg > 0 || end == beg) continue;
        auto lo = i, hi = n-1;
        while (lo < hi) {
          const auto mi = (lo + hi) >> 1;
          const auto msum = psum[mi] - psum[i];
          if (msum > 0) hi = mi;
          else lo = mi + 1;
        }
        pq.emplace(lo, b);
      }
      or_set.insert(arr[i]);
      auto x = arr[i];
      while (!pq.empty()) {
        const auto [j, b] = pq.top();
        pq.pop();
        x |= (1 << b);
        while (!pq.empty() && pq.top().F == j) {
          const auto [k, b] = pq.top();
          pq.pop();
          x |= (1 << b);
        }
        or_set.insert(x);
      }
    }
    return SZ(or_set);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi arr{1,2,4};
    const auto a_out = Solution().subarrayBitwiseORs(arr);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi arr{0};
    const auto a_out = Solution().subarrayBitwiseORs(arr);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi arr{1,1,2};
    const auto a_out = Solution().subarrayBitwiseORs(arr);
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
