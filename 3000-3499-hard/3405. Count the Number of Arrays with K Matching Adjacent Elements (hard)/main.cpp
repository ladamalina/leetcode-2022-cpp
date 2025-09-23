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

constexpr ll MOD = 1e9 + 7;
constexpr int MAX_N = 1e5;

template <typename T>
[[maybe_unused]] T ModPow(T a, T x, T m) {
  T ret = 1;
  while (x) {
    if (x & 1) ret = (ret * a) % m;
    x = (x >> 1);
    a = (a * a) % m;
  }
  return ret;
}

std::array<ll, MAX_N+1> f_mod{}, f_inv{};
bool init_f = false;

class Solution {
public:
  int countGoodArrays(int n, int m, int k) {
    if (!init_f) {
      f_mod[0] = 1;
      for (auto i = 1; i <= MAX_N; ++i) {
        f_mod[i] = (f_mod[i-1] * i) % MOD;
      }
      f_inv[MAX_N] = ModPow(f_mod[MAX_N], MOD-2, MOD);
      for (auto i = MAX_N - 1; i >= 0; --i) {
        f_inv[i] = (f_inv[i+1] * (i+1)) % MOD;
      }
      init_f = true;
    }

    const auto comb = [&](int cn, int ck) {
      if (ck < 0 || ck > cn) return 0ll;
      return (((f_mod[cn] * f_inv[ck]) % MOD) * f_inv[cn - ck]) % MOD;
    };

    const auto a = (comb(n - 1, k) * m) % MOD;
    const auto b = ModPow(CL(m - 1), CL(n - k - 1), MOD);
    return (a * b) % MOD;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().countGoodArrays(3, 2, 1);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().countGoodArrays(4, 2, 2);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().countGoodArrays(5, 2, 0);
    assert(a_out == 2);
  
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
