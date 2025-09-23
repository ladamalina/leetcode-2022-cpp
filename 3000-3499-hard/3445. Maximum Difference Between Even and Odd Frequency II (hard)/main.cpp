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

[[maybe_unused]] constexpr char MAX_C = '4';

class Solution {
public:
  int maxDifference(const std::string& s, int k) {
    const auto n = SZ(s);

    const auto get_status = [](int cnt_a, int cnt_b) {
      return ((cnt_a & 1) << 1) | (cnt_b & 1);
    };
    
    auto max_res = INT_MIN;
    for (auto a = '0'; a <= MAX_C; ++a) {
      for (auto b = '0'; b <= MAX_C; ++b) {
        if (a == b) continue;
        std::array<int, 4> best{INT_MAX, INT_MAX, INT_MAX, INT_MAX};
        auto cnt_a = 0, cnt_b = 0;
        auto pre_a = 0, pre_b = 0;
        auto l = -1;
        FOR(r, 0, n-1) {
          cnt_a += (s[r] == a);
          cnt_b += (s[r] == b);
          while (r - l >= k && cnt_b - pre_b >= 2) {
            const auto l_status = get_status(pre_a, pre_b);
            best[l_status] = std::min(best[l_status], pre_a - pre_b);
            ++l;
            pre_a += (s[l] == a);
            pre_b += (s[l] == b);
          }
          const auto r_status = get_status(cnt_a, cnt_b);
          if (best[r_status ^ 0b10] != INT_MAX) {
            max_res = std::max(max_res, (cnt_a - cnt_b) - best[r_status ^ 0b10]);
          }
        }
      }
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
