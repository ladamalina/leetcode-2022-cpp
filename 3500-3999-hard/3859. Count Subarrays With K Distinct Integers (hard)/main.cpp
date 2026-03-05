// #pragma GCC optimize("O3,unroll-loops")
// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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

class Solution {
public:
  ll countSubarrays(const vi& nums, const int k, const int m) {
    const auto n = SZ(nums);
    ll res = 0;
    
    std::unordered_map<int, int> l_x_freq, r_x_freq;
    std::set<ii> l_freq_x, r_freq_x;
    
    const auto need_move_l = [&]() -> bool {
      if (SZ(l_x_freq) < k) return true;
      if (l_freq_x.begin()->F < m) return true;
      return false;
    };

    const auto can_move_l = [&](const int i) -> bool {
      if (i + 1 >= n) return false;
      if (SZ(l_x_freq) == k && !l_x_freq.contains(nums[i+1])) return false;
      return true;
    };

    const auto can_move_r = [&](const int i) -> bool {
      if (i + 1 >= n) return false;
      if (SZ(l_x_freq) == k && !l_x_freq.contains(nums[i+1])) return false;
      return true;
    };
    
    const auto move_l = [&](int& i) {
      const auto f = ++l_x_freq[nums[++i]];
      if (f > 1) l_freq_x.erase({f-1, nums[i]});
      l_freq_x.emplace(f, nums[i]);
    };
    
    const auto move_r = [&](int& i) {
      const auto f = ++r_x_freq[nums[++i]];
      if (f > 1) r_freq_x.erase({f-1, nums[i]});
      r_freq_x.emplace(f, nums[i]);
    };
    
    const auto remove_begin = [&](const int i) {
      const auto lf = --l_x_freq[nums[i]];
      if (!lf) l_x_freq.erase(nums[i]);
      l_freq_x.erase({lf+1, nums[i]});
      if (lf) l_freq_x.emplace(lf, nums[i]);
      
      const auto rf = --r_x_freq[nums[i]];
      if (!rf) r_x_freq.erase(nums[i]);
      r_freq_x.erase({rf+1, nums[i]});
      if (rf) r_freq_x.emplace(rf, nums[i]);
    };

    auto l = -1, r = -1;
    FOR(i, 0, n - 1) {
      while (need_move_l() && can_move_l(l)) move_l(l);
      while (can_move_r(r)) move_r(r);
      // check l and r
      if (SZ(l_x_freq) == k && SZ(r_x_freq) == k && l_freq_x.begin()->F >= m && r_freq_x.begin()->F >= m) {
        res += r - l + 1;
      }
      // remove i-th element
      remove_begin(i);
    }
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const vi nums{1,2,1,2,2};
    const auto a_out = Solution().countSubarrays(nums, 2, 2);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const vi nums{3,1,2,4};
    const auto a_out = Solution().countSubarrays(nums, 2, 1);
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
