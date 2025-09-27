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

constexpr int MAX_N = 1e5;
std::array<ll, MAX_N> p_psum, ps_psum;

class Solution {
public:
  ll maxProfit(const vi& p, const vi& s, const int k) {
    const auto n = SZ(p);
    FOR(i, 0, n-1) {
      p_psum[i] = p[i] + (i > 0 ? p_psum[i-1] : 0);
      ps_psum[i] = s[i] * p[i] + (i > 0 ? ps_psum[i-1] : 0);
    }
    auto max_res = ps_psum[n-1];
    FOR(i, 0, n - k) {
      const auto psum = i > 0 ? ps_psum[i-1] : 0;
      const auto msum = p_psum[i+k-1] - p_psum[i+(k>>1)-1];
      const auto ssum = ps_psum[n-1] - ps_psum[i+k-1];
      max_res = std::max(max_res, psum + msum + ssum);
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi p{4,2,8};
    const vi s{-1,0,1};
    const auto a_out = Solution().maxProfit(p, s, 2);
    assert(a_out == 10);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi p{5,4,3};
    const vi s{1,1,0};
    const auto a_out = Solution().maxProfit(p, s, 2);
    assert(a_out == 9);
  
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
