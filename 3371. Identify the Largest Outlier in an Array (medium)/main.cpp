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
  int getLargestOutlier(const vi& nums) {
    const auto n = SZ(nums);
    
    vl psum(n);
    std::unordered_map<int, vi> x_ids;
    FOR(i, 0, n-1) {
      psum[i] = nums[i] + (i > 0 ? psum[i-1] : 0);
      x_ids[nums[i]].push_back(i);
    }
    
    auto max_out = INT_MIN;
    FOR(i, 0, n-1) { // nums[i] is the sum of these special numbers
      const auto all_sum = (i > 0 ? psum[i-1] : 0) + (psum[n-1] - psum[i]);
      const auto diff = all_sum - nums[i];
      if (x_ids.contains(diff)) {
        const auto& ids = x_ids.at(diff);
        if (SZ(ids) == 1 && ids[0] != i) {
          const auto out_id = ids[0];
          max_out = std::max(max_out, nums[out_id]);
        } else if (SZ(ids) > 1) {
          const auto out_id = (ids.front() == i) ? ids.back() : ids.front();
          max_out = std::max(max_out, nums[out_id]);
        }
      }
    }

    return max_out;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{2,3,5,10};
    const auto a_out = Solution().getLargestOutlier(nums);
    assert(a_out == 10);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{-2,-1,-3,-6,4};
    const auto a_out = Solution().getLargestOutlier(nums);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,1,1,1,5,5};
    const auto a_out = Solution().getLargestOutlier(nums);
    assert(a_out == 5);
  
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