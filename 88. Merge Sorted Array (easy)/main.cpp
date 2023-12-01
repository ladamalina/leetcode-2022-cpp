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
#define CZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

class Solution {
public:
  void merge(vi& nums1, int m, vi& nums2, int n) {
    for (auto i=m-1; i>=0; --i) {
      nums1[i+n] = nums1[i];
    }
    auto i1=0, i2=0, i3=0;
    while (i1<m && i2<n) {
      if (nums1[i1+n] <= nums2[i2]) {
        nums1[i3] = nums1[i1+n];
        ++i1;
      } else {
        nums1[i3] = nums2[i2];
        ++i2;
      }
      ++i3;
    }
    while (i1<m) {
      nums1[i3] = nums1[i1+n];
      ++i1;
      ++i3;
    }
    while (i2<n) {
      nums1[i3] = nums2[i2];
      ++i2;
      ++i3;
    }
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    vi nums1{1,2,3,0,0,0};
    vi nums2{2,5,6};
    Solution().merge(nums1, 3, nums2, 3);
    const vi e_out{1,2,2,3,5,6};
    assert(nums1 == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    vi nums1{1};
    vi nums2{};
    Solution().merge(nums1, 1, nums2, 0);
    const vi e_out{1};
    assert(nums1 == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    vi nums1{0};
    vi nums2{1};
    Solution().merge(nums1, 0, nums2, 1);
    const vi e_out{1};
    assert(nums1 == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    vi nums1{1,2,4,5,6,0};
    vi nums2{3};
    Solution().merge(nums1, 5, nums2, 1);
    const vi e_out{1,2,3,4,5,6};
    assert(nums1 == e_out);
  
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
