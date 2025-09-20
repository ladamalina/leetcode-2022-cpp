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
  int longestSubarray(const vi& nums) {
    const auto n = SZ(nums);
    vi l_cnt(n);
    {
      auto len = 0;
      FOR(i, 0, n-1) {
        if (nums[i]==1) ++len;
        else len = 0;
        l_cnt[i] = len;
      }
    }
    vi r_cnt(n);
    {
      auto len = 0;
      FORD(i, n-1, 0) {
        if (nums[i]==1) ++len;
        else len = 0;
        r_cnt[i] = len;
      }
    }
    auto max_len = 0;
    FOR(i, 0, n-1) {
      if (nums[i]==1) max_len = std::max(max_len, l_cnt[i]-1);
      else {
        const auto l_len = i-1>=0 ? l_cnt[i-1] : 0;
        const auto r_len = i+1<n ? r_cnt[i+1] : 0;
        max_len = std::max(max_len, l_len+r_len);
      }
    }
    return max_len;
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
