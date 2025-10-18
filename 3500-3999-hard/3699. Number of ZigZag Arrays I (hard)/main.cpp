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

constexpr int MOD = 1e9 + 7, MAX_M = 2000;
std::array<int, MAX_M> inc_vals, inc_psum, dec_vals, dec_psum;

class Solution {
public:
  int zigZagArrays(const int n, const int l, const int r) {
    const auto m = r - l + 1;
    
    std::fill(inc_vals.begin(), inc_vals.begin() + m, 1);
    std::fill(dec_vals.begin(), dec_vals.begin() + m, 1);
    
    inc_vals[0] = 0;
    FOR(i, 0, m-1) inc_psum[i] = (inc_vals[i] + (i > 0 ? inc_psum[i-1] : 0)) % MOD;
    dec_vals[m-1] = 0;
    FOR(i, 0, m-1) dec_psum[i] = (dec_vals[i] + (i > 0 ? dec_psum[i-1] : 0)) % MOD;

    FOR(i, 1, n-1) {
      FOR(j, 0, m-1) {
        if (j > 0) inc_vals[j] = dec_psum[j-1];
        if (j < m-1) dec_vals[j] = (inc_psum[m-1] - inc_psum[j] + MOD) % MOD;
      }
      FOR(j, 0, m-1) {
        inc_psum[j] = (inc_vals[j] + (j > 0 ? inc_psum[j-1] : 0)) % MOD;
        dec_psum[j] = (dec_vals[j] + (j > 0 ? dec_psum[j-1] : 0)) % MOD;
      }
    }

    const auto res = (inc_psum[m-1] + dec_psum[m-1]) % MOD;
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().zigZagArrays(3, 4, 5);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().zigZagArrays(3, 1, 3);
    assert(a_out == 10);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().zigZagArrays(34, 227, 530);
    assert(a_out == 25249430);
  
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
