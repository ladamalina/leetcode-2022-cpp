#include <bits/stdc++.h>

/*#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>*/

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
#define F first
#define S second

class Solution {
public:
  ll countSubarrays(const vi& nums, int k) {
    const auto n = CI(nums.size());
    vvi /*bsum1(31, vi(n)),*/ bcnt0(31, vi(n));
    FOR(b, 0, 30) {
      FOR(i, 0, n-1) {
        const auto is0 = (nums[i]&(1<<b))==0;
        bcnt0[b][i] = (i==0) ? is0 : (is0 + bcnt0[b][i-1]);
      }
    }

    ll res = 0;
    FOR(i, 0, n-1) {
      auto l=i, r=n-1;
      FOR(b, 0, 30) {
        const auto k1 = (k&(1<<b))!=0;
        const auto b1 = (nums[i]&(1<<b))!=0;

        if (k1) {
          if (b1) {
            const auto br = CI(std::upper_bound(RNG(bcnt0[b]), bcnt0[b][i]) - bcnt0[b].begin())-1;
            r = std::min(r, br);
          } else { // b0
            r = l-1;
            break;
          }
        } else { // k0
          if (b1) {
            const auto bl = CI(std::upper_bound(RNG(bcnt0[b]), bcnt0[b][i]) - bcnt0[b].begin());
            l = std::max(l, bl);
          } else { // b0
            // r = std::min(r, n-1);
          }
        }
      }
      if (l<=r) res += (r-l+1);
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,1};
    const auto a_out = Solution().countSubarrays(nums, 1);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,2};
    const auto a_out = Solution().countSubarrays(nums, 1);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,3};
    const auto a_out = Solution().countSubarrays(nums, 2);
    assert(a_out == 2);
  
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
