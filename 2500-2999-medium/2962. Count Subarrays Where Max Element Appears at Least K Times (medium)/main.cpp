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
  ll countSubarrays(const vi& nums, const int k) {
    const auto n = SZ(nums);
    const auto mx = *std::max_element(RNG(nums));
    ll res = 0;
    int cnt = 0, r = -1;
    FOR(l, 0, n-1) {
      cnt -= (l-1 >= 0 && nums[l-1] == mx);
      while (cnt < k && r+1 < n) {
        cnt += (nums[++r] == mx);
      }
      res += (cnt >= k ? n - r : 0);
    }
    return res;
  }
};

/*class Solution {
public:
  ll countSubarrays(const vi& nums, const int k) {
    const auto n = SZ(nums);
    const auto mx = *std::max_element(RNG(nums));
    vi pcnt(n);
    FOR(i, 0, n-1) pcnt[i] = (nums[i] == mx) + (i == 0 ? 0 : pcnt[i-1]);
    ll res = 0;
    FOR(i, 0, n-1) {
      const auto tail_cnt = pcnt[n-1] - (i == 0 ? 0 : pcnt[i-1]);
      if (tail_cnt >= k) {
        int lo = i, hi = n-1;
        while (lo < hi) {
          const auto mid = (lo + hi) / 2;
          const auto mid_cnt = pcnt[mid] - (i == 0 ? 0 : pcnt[i-1]);
          if (mid_cnt >= k) hi = mid;
          else lo = mid + 1;
        }
        res += n - lo;
      }
    }
    return res;
  }
};*/

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,3,2,3,3};
    const auto a_out = Solution().countSubarrays(nums, 2);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,4,2,1};
    const auto a_out = Solution().countSubarrays(nums, 3);
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{28,5,58,91,24,91,53,9,48,85,16,70,91,91,47,91,61,4,54,61,49};
    const auto a_out = Solution().countSubarrays(nums, 1);
    assert(a_out == 187);

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
