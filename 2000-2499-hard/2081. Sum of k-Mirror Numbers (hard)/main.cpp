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
using ld = long double;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

bool IsPalindrome(const std::string& s) {
  auto l = 0, r = SZ(s) - 1;
  while (l < r) {
    if (s[l] != s[r])
      return false;
    ++l;
    --r;
  }
  return true;
}

std::string ToBaseK(const std::string& s, int k) {
  if (s == "0") {
    return "0";
  }

  auto x = std::stoll(s);
  std::string res;
  while (x > 0) {
    res.push_back(CC('0' + (x % k)));
    x /= k;
  }

  std::reverse(RNG(res));
  return res;
}

std::string ToOddPal(const ll x) {
  const auto s = std::to_string(x);
  if (SZ(s) == 1)
    return s;
  auto tail = s.substr(0, SZ(s) - 1);
  std::reverse(RNG(tail));
  return s + tail;
}

std::string ToEvenPal(const ll x) {
  const auto s = std::to_string(x);
  const std::string tail(s.rbegin(), s.rend());
  return s + tail;
}

class Solution {
public:
  ll kMirror(int k, int n) {
    ll s_res = 0;
    int n_res = 0, lo_lim = 1, up_lim = 10;
    while (n_res < n) {
      for (auto x = lo_lim; x < up_lim; ++x) {
        const auto pal = ToOddPal(x);
        const auto y = ToBaseK(pal, k);
        if (IsPalindrome(y)) {
          s_res += std::stoll(pal);
          ++n_res;
          // std::cerr << "pal=" << pal << "\ty=" << y << "\tn_res=" << n_res << "\ts_res=" << s_res << "\n";
          if (n_res == n) break;
        }
      }
      if (n_res == n) break;

      for (auto x = lo_lim; x < up_lim; ++x) {
        const auto pal = ToEvenPal(x);
        const auto y = ToBaseK(pal, k);
        if (IsPalindrome(y)) {
          s_res += std::stoll(pal);
          ++n_res;
          // std::cerr << "pal=" << pal << "\ty=" << y << "\tn_res=" << n_res << "\ts_res=" << s_res << "\n";
          if (n_res == n) break;
        }
      }

      lo_lim = up_lim;
      up_lim *= 10;
    }
    return s_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().kMirror(2, 5);
    assert(a_out == 25);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().kMirror(3, 7);
    assert(a_out == 499);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().kMirror(7, 17);
    assert(a_out == 20379000);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().kMirror(2, 30);
    assert(a_out == 20379000);
  
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
