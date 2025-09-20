// #include <bits/stdc++.h>

#include <algorithm>
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
#define F first
#define S second
#define PB push_back

int Rec(int i, int used, int n, const vi& nums1, const vi& nums2, vvi& memo) {
  if (i == n) return 0;
  if (memo[i][used] != -1) return memo[i][used];

  auto res = INT_MAX;
  FOR(j, 0, n-1) {
    if (!(used&(1<<j))) {
      res = std::min(res, (nums1[i]^nums2[j]) + Rec(i+1, (used|(1<<j)), n, nums1, nums2, memo));
    }
  }
  memo[i][used] = res;
  return res;
}

class Solution {
public:
  int minimumXORSum(const vi& nums1, const vi& nums2) {
    const auto n = CI(nums1.size());
    
    vvi memo(n, vi((1<<n), -1));
    const auto res = Rec(0, 0, n, nums1, nums2, memo);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{1,2};
    const vi nums2{2,3};
    const auto a_out = Solution().minimumXORSum(nums1, nums2);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{1,0,3};
    const vi nums2{5,3,4};
    const auto a_out = Solution().minimumXORSum(nums1, nums2);
    assert(a_out == 8);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums1{72,97,8,32,15};
    const vi nums2{63,97,57,60,83};
    const auto a_out = Solution().minimumXORSum(nums1, nums2);
    assert(a_out == 152);
  
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
