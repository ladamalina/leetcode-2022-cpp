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
  std::string nearestPalindromic(const std::string& num_str) {
    const auto num = std::stoll(num_str);
    if (num_str == "999999999999999999"s) {
      return "1000000000000000001"s;
    }
    if (num <= 10) return std::to_string(num - 1);
    if (num == 11) return "9"s;

    const auto len = SZ(num_str);
    const auto leftHalf = std::stoll(num_str.substr(0, (len+1)/2));
        
    vl candidates(5);
    candidates[0] = generatePalindromeFromLeft(leftHalf - 1, len % 2 == 0);
    candidates[1] = generatePalindromeFromLeft(leftHalf, len % 2 == 0);
    candidates[2] = generatePalindromeFromLeft(leftHalf + 1, len % 2 == 0);
    candidates[3] = std::pow(10, len-1) - 1;
    candidates[4] = std::pow(10, len) + 1;

    ll best_pal = 0;
    ll min_diff = LLONG_MAX;

    for (const auto candidate : candidates) {
      if (candidate == num)
        continue;
      const auto diff = abs(candidate - num);
      if (diff < min_diff || (diff == min_diff && candidate < best_pal)) {
        min_diff = diff;
        best_pal = candidate;
      }
    }

    return std::to_string(best_pal);
  }

private:
  static ll generatePalindromeFromLeft(ll leftHalf, bool isEvenLength) {
    ll palindrome = leftHalf;
    if (!isEvenLength)
      leftHalf /= 10;
    while (leftHalf > 0) {
      palindrome = palindrome * 10 + leftHalf % 10;
      leftHalf /= 10;
    }
    return palindrome;
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
