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
  ll numOfSubsequences(const std::string& s) {
    const auto n = SZ(s), sum_t = CI(std::count(RNG(s), 'T'));

    ll init_res = 0, l_res = 0, t_res = 0;
    {
      auto l_bef = 0, t_aft = sum_t;
      FOR(i, 0, n-1) {
        if (s[i] == 'C') {
          init_res += CL(l_bef) * t_aft; // no insertions
          l_res += CL(l_bef + 1) * t_aft; // insert l before 0
          t_res += CL(l_bef) * (t_aft + 1); // insert t after n-1
        }
        else if (s[i] == 'L') ++l_bef;
        else if (s[i] == 'T') --t_aft;
      }
    }
    auto max_res = std::max(init_res, std::max(l_res, t_res));
    { // insert 'C' before i
      auto l_bef = 0, t_aft = sum_t;
      FOR(i, 0, n-1) {
        const auto c_res = init_res + CL(l_bef) * t_aft;
        max_res = std::max(max_res, c_res);
        if (s[i] == 'L') ++l_bef;
        else if (s[i] == 'T') --t_aft;
      }
    }

    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("LMCT"s);
    const auto a_out = Solution().numOfSubsequences(s);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("LT"s);
    const auto a_out = Solution().numOfSubsequences(s);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("LCCT"s);
    const auto a_out = Solution().numOfSubsequences(s);
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
