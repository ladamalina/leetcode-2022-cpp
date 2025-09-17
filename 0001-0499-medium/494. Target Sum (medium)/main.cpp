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
  int findTargetSumWays(const vi& nums, int target) {
    const auto n = SZ(nums);
    std::vector<std::unordered_map<int, int>> memo(n);

    const std::function<int(int,int)> rec = [&](const int i, const int psum) {
      if (i == n)
        return CI(psum == target);
      if (memo[i].contains(psum))
        return memo[i][psum];

      const auto res = rec(i+1, psum + nums[i]) + rec(i+1, psum - nums[i]);
      memo[i][psum] = res;
      return res;
    };
    const auto res = rec(0, 0);
    return res;
  }
};

/*class Solution {
public:
  int findTargetSumWays(const vi& nums, int target) {
    const auto n = SZ(nums);
    const auto max_m = (1<<n) - 1;
    int res = 0;
    FOR(m, 0, max_m) {
      int m_res = 0;
      FOR(i, 0, n-1) {
        m_res += (m&(1<<i)) ? nums[i] : -nums[i];
      }
      res += (m_res == target);
    }
    return res;
  }
};*/

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findTargetSumWays({26,15,38,20,40,10,14,35,32,20,7,18,38,6,46,46,20,50,35,41}, 3);
    assert(a_out == 6034);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findTargetSumWays({5,16,45,7,20,5,32,38,43,14,29,11,2,25,36,28,27,26,45,45}, 17);
    assert(a_out == 6333);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findTargetSumWays({11,20,19,3,25,7,30,45,8,11,35,19,29,9,49,14,22,34,12,0}, 34);
    assert(a_out == 7306);
  
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
