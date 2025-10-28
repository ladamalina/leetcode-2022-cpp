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
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

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
  std::string findLexSmallestString(const std::string& s, const int a, const int b) {
    const auto n = SZ(s);
    auto min_res = s;
    FOR(na1, 0, 9) {
      FOR(na2, 0, (b & 1) ? 9 : 0) {
        auto t = s;
        for (auto i = 1; i < n; i += 2) {
          t[i] = CC((((t[i] - '0') + a * na1) % 10) + '0');
        }
        for (auto i = 0; i < n; i += 2) {
          t[i] = CC((((t[i] - '0') + a * na2) % 10) + '0');
        }
        min_res = std::min(min_res, t);
        auto nb = 1;
        while (true) {
          const auto beg = (((n - b * nb) % n) + n) % n;
          if (beg == 0) break;
          const auto u = (beg < n ? t.substr(beg) : ""s) + (beg > 0 ? t.substr(0, beg) : ""s);
          min_res = std::min(min_res, u);
          ++nb;
        }
      }
    }
    return min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("74"s);
    const auto a_out = Solution().findLexSmallestString(s, 5, 1);
    assert(a_out == "24"s);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("5525"s);
    const auto a_out = Solution().findLexSmallestString(s, 9, 2);
    assert(a_out == "2050"s);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("0011"s);
    const auto a_out = Solution().findLexSmallestString(s, 4, 2);
    assert(a_out == "0011"s);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("35212846976840389497819611331735564258265152460043472221614030430727261361594402879448794707"s);
    const auto a_out = Solution().findLexSmallestString(s, 3, 19);
    assert(a_out == "00009964432278560772152208018040129704123117770647994169018392531093435298326200504442313268"s);
  
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
