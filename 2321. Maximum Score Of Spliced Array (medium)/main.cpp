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

class Solution {
public:
  int maximumsSplicedArray(const vi& nums1, const vi& nums2) {
    const auto n = SZ(nums1);

    vi psum1(n), psum2(n);
    FOR(i, 0, n-1) psum1[i] = (i > 0) ? psum1[i-1] + nums1[i] : nums1[i];
    FOR(i, 0, n-1) psum2[i] = (i > 0) ? psum2[i-1] + nums2[i] : nums2[i];

    vi diff(n);
    std::set<ii> diff_i;
    FOR(i, 0, n-1) {
      diff[i] = psum1[i] - psum2[i];
      diff_i.emplace(diff[i], i);
    }

    auto max_res = std::max(psum1[n-1], psum2[n-1]);
    FOR(i, 0, n-1) {
      const auto pref_diff = (i > 0) ? diff[i-1] : 0;
      const auto min_diff = diff_i.begin()->F - pref_diff;
      const auto max_diff = diff_i.rbegin()->F - pref_diff;
      
      max_res = std::max(max_res, std::max(psum1[n-1] - min_diff, psum2[n-1] + min_diff));
      max_res = std::max(max_res, std::max(psum1[n-1] - max_diff, psum2[n-1] + max_diff));

      // update diff_i
      diff_i.erase({diff[i], i});
    }

    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{60,60,60};
    const vi nums2{10,90,10};
    const auto a_out = Solution().maximumsSplicedArray(nums1, nums2);
    assert(a_out == 210);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{20,40,20,70,30};
    const vi nums2{50,20,50,40,20};
    const auto a_out = Solution().maximumsSplicedArray(nums1, nums2);
    assert(a_out == 220);
  
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
