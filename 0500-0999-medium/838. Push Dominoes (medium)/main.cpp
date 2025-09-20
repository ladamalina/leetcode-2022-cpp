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
#include <string_view>
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

class Solution {
 public:
  std::string pushDominoes(std::string& s) {
    const auto n = SZ(s);

    const std::function<void(int,int)> fill_gap = [&](int i, int j) {
      if (i < 0 && j >= n) return;
      if (i + 1 == j) return;
      if (i < 0) {
        if (s[j] == 'L') {
          FOR(k, i+1, j-1) s[k] = 'L';
        } // s[j] == 'R'
        return;
      } // i >= 0
      if (j >= n) {
        if (s[i] == 'R') {
          FOR(k, i+1, j-1) s[k] = 'R';
        } // s[j] == 'L'
        return;
      } // j < n
      if (s[i] == 'R' && s[j] == 'L') {
        auto l = i + 1, r = j - 1;
        while (l < r) {
          s[l++] = 'R';
          s[r--] = 'L';
        }
      } else if (s[i] == 'R') {
        FOR(k, i+1, j-1) s[k] = 'R';
      } else if (s[j] == 'L') {
        FOR(k, i+1, j-1) s[k] = 'L';
      }
    };

    auto l = -1;
    while (l < n) {
      auto r = l + 1;
      while (r < n && s[r] == '.') ++r;
      fill_gap(l, r);
      l = r;
    }
    return s;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s = "RR.L";
    const auto a_out = Solution().pushDominoes(s);
    assert(a_out == "RR.L"s);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s = ".L.R...LR..L..";
    const auto a_out = Solution().pushDominoes(s);
    assert(a_out == "LL.RR.LLRRLL.."s);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s = "L.LL......";
    const auto a_out = Solution().pushDominoes(s);
    assert(a_out == "LLLL......"s);
  
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
