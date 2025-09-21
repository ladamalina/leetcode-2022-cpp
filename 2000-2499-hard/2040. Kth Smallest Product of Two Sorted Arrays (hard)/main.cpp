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

constexpr ll MIN_X = -1e5, MAX_X = 1e5;

class Solution {
public:
  ll kthSmallestProduct(const vi& nums1, const vi& nums2, ll k) {
    const auto n2 = SZ(nums2);

    const std::function<int(ll,ll)> count_of_prods = [&](const ll x1, const ll target) {
      if (x1 == 0) {
        return target >= 0 ? n2 : 0;
      } // x != 0
      
      auto res = 0;
      if (x1 > 0) {
        const auto it = std::upper_bound(RNG(nums2), x1,
          [&](const ll x2, const ll val) { return x2 * val > target; });
        res = CI(it - nums2.begin());
      } else { // x1 < 0
        const auto it = std::upper_bound(RNG(nums2), x1,
          [&](const ll x2, const ll val) { return x2 * val <= target; });
        res = CI(nums2.end() - it);
      }
      return res;
    };
    
    const std::function<bool(ll)> bin_check = [&](const ll target) {
      // true if count of (products <= target) is >= k
      ll res = 0;
      for (const auto x1 : nums1) {
        res += count_of_prods(x1, target);
        if (res >= k) return true;
      }
      return false;
    };
    
    ll lo = MIN_X * MAX_X, hi = MAX_X * MAX_X;
    while (lo < hi) {
      const auto mid = (lo + hi) >= 0 ? (lo + hi) / 2 : (lo + hi) / 2 - 1;
      const auto check = bin_check(mid);
      // std::cerr << "lo=" << lo << "\tmid=" << mid << "\thi=" << hi << "\tcheck=" << check << '\n';
      if (check) hi = mid;
      else lo = mid + 1;
    }
    
    return lo;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{2,5};
    const vi nums2{3,4};
    const auto a_out = Solution().kthSmallestProduct(nums1, nums2, 2);
    assert(a_out == 8);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{-4,-2,0,3};
    const vi nums2{2,4};
    const auto a_out = Solution().kthSmallestProduct(nums1, nums2, 6);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{-2,-1,0,1,2};
    const vi nums2{-3,-1,2,4,5};
    const auto a_out = Solution().kthSmallestProduct(nums1, nums2, 3);
    assert(a_out == -6);
  
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
