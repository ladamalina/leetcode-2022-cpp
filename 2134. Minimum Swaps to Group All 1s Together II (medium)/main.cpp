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

class Solution {
public:
  int minSwaps(const vi& nums) {
    const auto n = SZ(nums);
    vi psum(n);
    FOR(i, 0, n-1) {
      psum[i] = nums[i] + (i>0 ? psum[i-1] : 0);
    }
    const auto cnt1 = psum[n-1];
    if (cnt1 == 0)
      return 0;
    auto min_swaps = n;
    FOR(i, 0, n-1) { // pos of 1st 1
      if (n-i >= cnt1) {
        const auto ei = i + cnt1 - 1;
        const auto a_cnt1 = psum[ei] - (i>0 ? psum[i-1] : 0);
        const auto swaps = cnt1 - a_cnt1;
        min_swaps = std::min(min_swaps, swaps);
      } else {
        const auto tail_len = n-i;
        const auto tail_cnt1 = psum[n-1] - (i>0 ? psum[i-1] : 0);
        
        const auto head_len = cnt1 - tail_len;
        const auto head_cnt1 = psum[head_len-1];

        const auto swaps = cnt1 - (tail_cnt1 + head_cnt1);
        min_swaps = std::min(min_swaps, swaps);
      }
    }
    return min_swaps;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{0,1,0,1,1,0,0};
    const auto a_out = Solution().minSwaps(nums);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{0,1,1,1,0,0,1,1,0};
    const auto a_out = Solution().minSwaps(nums);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,0,0,1};
    const auto a_out = Solution().minSwaps(nums);
    assert(a_out == 0);
  
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
