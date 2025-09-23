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
  int minDifference(const vi& nums) {
    const auto n = SZ(nums);

    {
      // check trivial cases
      std::set<int> x_set(RNG(nums));
      if (!x_set.contains(-1)) {
        auto max_diff = 0;
        FOR(i, 1, n-1) {
          max_diff = std::max(max_diff, std::abs(nums[i] - nums[i - 1]));
        }
        return max_diff;
      } // x_set.contains(-1)
      if (SZ(x_set) == 1)
        return 0;
    }

    int mn = 1e9, mx = 0, curr_mx = 0, cnt = 0;
    vi nums2;
    for (int i = 0; i < n; ++i) {
      if (nums[i] != -1) {
        if (i > 0 && nums[i-1] != -1)
          curr_mx = std::max(curr_mx, std::abs(nums[i] - nums[i-1]));
        if (cnt == 1)
          nums2.push_back(-1);
        if (cnt > 1)
          nums2.push_back(-2);
        cnt = 0;
        if (i == 0 || i+1 == n || nums[i-1] == -1 || nums[i+1] == -1)
          nums2.push_back(nums[i]);
        if ((i > 0 && nums[i-1] == -1) || (i+1 < n && nums[i+1] == -1)) {
          mn = std::min(mn, nums[i]);
          mx = std::max(mx, nums[i]);
        }
      } else {
        ++cnt;
      }
    }
    if (cnt > 0)
      nums2.push_back(-1);
    if (nums2[0] == -2)
      nums2[0] = -1;

    auto lo = curr_mx, hi = mx - mn + 1;
    while (lo < hi) {
      const auto mid = (lo + hi) / 2;
      const auto check = BinCheck(nums2, mn, mx, mid);
      // std::cerr << lo << '\t' << mid << '\t' << hi << '\t' << check << '\n';
      if (check)
        hi = mid;
      else
        lo = mid + 1;
    }
    return lo;
  }

private:
  bool BinCheck(const vi& nums, const int mn, const int mx, const ll diff) {
    const auto n = SZ(nums);
    const auto p1 = mn + diff, p2 = mx - diff;
    
    if (nums[0] == -1 && std::abs(nums[1] - p1) > diff && std::abs(nums[1] - p2) > diff)
      return false;
    if (nums[n-1] == -1 && std::abs(nums[n-2] - p1) > diff && std::abs(nums[n-2] - p2) > diff)
      return false;
    
    for (int i = 1; i+1 < n; ++i)
      if (nums[i] < 0) {
        if (std::abs(nums[i-1] - p1) <= diff && std::abs(nums[i+1] - p1) <= diff)
          continue;
        if (std::abs(nums[i-1] - p2) <= diff && std::abs(nums[i+1] - p2) <= diff)
          continue;
        if (nums[i] == -2) {
          if (std::abs(p2 - p1) <= diff) {
            if (std::abs(nums[i-1] - p1) <= diff && std::abs(nums[i+1] - p2) <= diff)
              continue;
            if (std::abs(nums[i-1] - p2) <= diff && std::abs(nums[i+1] - p1) <= diff)
              continue;
          }
        }
        return false;
      }
    return true;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({1,-1,3,4,5,6,7,8,9,10,-1,12,11,10,9,8,7,6,5,-1});
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({2,-1,4,-1,-1,6});
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({1, 2, -1, 10, 8});
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({-1, -1, -1});
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({-1, 10, -1, 8});
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({21, 18, 16});
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({25, -1, 7});
    assert(a_out == 9);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().minDifference({463, 507, 251, -1, -1, -1, -1, 108, 152, -1, 948});
    assert(a_out == 398);

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