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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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
  int maxFreeTime(int max_t, const vi& st, const vi& en) {
    const auto n = SZ(st);
    if (n == 1)
      return max_t - (en[0] - st[0]);
    // n > 1

    vii gaps; // <len, next_i>
    if (st[0] > 0) gaps.emplace_back(st[0], 0);
    FOR(i, 1, n-1) if (st[i] - en[i-1] > 0) gaps.emplace_back(st[i] - en[i-1], i);
    if (en[n-1] < max_t) gaps.emplace_back(max_t - en[n-1], n);
    if (gaps.empty())
      return 0;
    SORT(gaps);
    const auto gn = SZ(gaps);

    int max_res = gaps.rbegin()->F;
    FOR(i, 0, n-1) {
      const auto i_gap = (i == n-1 ? max_t : st[i+1]) - (i == 0 ? 0 : en[i-1]);
      const auto c_gap = i_gap - (en[i] - st[i]);
      int gi = gn - 1;
      while (gi >= 0 && (gaps[gi].S == i || gaps[gi].S == i+1))
        --gi;
      if (gi >= 0 && en[i] - st[i] <= gaps[gi].F)
        max_res = std::max(max_res, i_gap);
      else
        max_res = std::max(max_res, c_gap);
    }
    return max_res;
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
