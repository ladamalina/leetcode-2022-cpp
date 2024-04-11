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

class Solution {
public:
  int equalSubstring(const std::string& s, const std::string& t, int max_c) {
    const auto n = CI(s.size());

    const auto cost = [&](int i) {
      return std::max(s[i],t[i])-std::min(s[i],t[i]);
    };
    
    int max_len = 0;
    auto l = 0, r = 0, c = cost(l);
    while (r+1<n && c+cost(r+1)<=max_c) {
      c += cost(r+1);
      ++r;
    }
    if (c<=max_c) max_len = std::max(max_len, r-l+1);
    while (l+1<n) {
      c -= cost(l);
      ++l;
      if (r < l) {
        c = cost(l);
        r = l;
      }
      while (r+1<n && c+cost(r+1)<=max_c) {
        c += cost(r+1);
        ++r;
      }
      if (c<=max_c) max_len = std::max(max_len, r-l+1);
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
