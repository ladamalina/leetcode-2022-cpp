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
  int compress(std::vector<char>& chars) {
    const auto n = SZ(chars);
    auto ii = 1, oi = 0, bi = 0;
    while (ii <= n) {
      if (ii < n && chars[ii] == chars[bi]) {
        // 
      } else {
        auto len = ii - bi;
        chars[oi] = chars[bi]; ++oi;
        if (len == 1) {
          // do nothing
        } else if (len <= 9) {
          chars[oi] = '0'+len; ++oi;
        } else if (len <= 99) {
          chars[oi] = '0'+len/10; ++oi; len %= 10;
          chars[oi] = '0'+len; ++oi;
        } else if (len <= 999) {
          chars[oi] = '0'+len/100; ++oi; len %= 100;
          chars[oi] = '0'+len/10; ++oi; len %= 10;
          chars[oi] = '0'+len; ++oi;
        } else {
          chars[oi] = '0'+len/1000; ++oi; len %= 1000;
          chars[oi] = '0'+len/100; ++oi; len %= 100;
          chars[oi] = '0'+len/10; ++oi; len %= 10;
          chars[oi] = '0'+len; ++oi;
        }
        bi = ii;
      }
      ++ii;
    }
    return oi;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::vector<char> chars{'a','a','b','b','c','c','c'};
    const auto a_out = Solution().compress(chars);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::vector<char> chars{'a'};
    const auto a_out = Solution().compress(chars);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::vector<char> chars{'a','b','b','b','b','b','b','b','b','b','b','b','b'};
    const auto a_out = Solution().compress(chars);
    assert(a_out == 4);
  
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
