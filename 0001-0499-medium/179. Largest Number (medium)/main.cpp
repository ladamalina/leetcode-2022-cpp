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
  std::string largestNumber(const vi& nums) {
    vi arr;
    for (const auto x : nums)
      Insert(arr, x);
    return Arr2Str(arr);
  }

private:
  static std::string Arr2Str(const vi& arr) {
    std::string s;
    for (const auto x : arr)
      s += std::to_string(x);
    while (SZ(s) > 1 && s[0] == '0')
      s.erase(s.begin(), s.begin()+1);
    return s;
  }
  
  static void Insert(vi& arr, int x) {
    if (arr.empty()) {
      arr.push_back(x);
      return;
    }
    const auto n = SZ(arr);
    int max_i;
    std::string max_s;
    FOR(i, 0, n) {
      arr.insert(arr.begin()+i, x);
      const auto s = Arr2Str(arr);
      if (s > max_s) {
        max_i = i;
        max_s = s;
      }
      arr.erase(arr.begin()+i, arr.begin()+i+1);
    }
    arr.insert(arr.begin()+max_i, x);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{10,2};
    const auto a_out = Solution().largestNumber(nums);
    assert(a_out == "210"s);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{3,30,34,5,9};
    const auto a_out = Solution().largestNumber(nums);
    assert(a_out == "9534330"s);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{0,0};
    const auto a_out = Solution().largestNumber(nums);
    assert(a_out == "0"s);
  
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
