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
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
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
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

constexpr ll MOD = 1e9 + 7;
constexpr int MAX_N = 1e4;

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

vl f_mod(MAX_N+1);
vl f_inv(MAX_N+1);
bool init_f_mod = false;

class Solution {
public:
  int idealArrays(int n, int max_v) {
    if (!init_f_mod) {
      f_mod[0] = 1, f_mod[1] = 1;
      for (auto i = 2; i <= MAX_N; ++i) {
        f_mod[i] = (f_mod[i-1]*i) % MOD;
      }

      f_inv[MAX_N] = ModPow(f_mod[MAX_N], MOD-2, MOD);
      for (auto i = MAX_N-1; i >= 0; --i) {
        f_inv[i] = (f_inv[i+1] * (i+1)) % MOD;
      }

      init_f_mod = true;
    }

    ll res = 0;

    const std::function<void(int,int)> rec = [&](int v, int fn) {
      const auto cn = (fn + 1), ck = n - (fn + 1);
      auto v_res = (f_mod[cn+ck-1] * f_inv[ck]) % MOD;
      v_res = (v_res * f_inv[cn-1]) % MOD;
      // std::cerr << "v=" << v << "\tfn=" << fn << "\tv_res=" << v_res << std::endl;
      res = (res + v_res) % MOD;
      if (v == max_v || fn == n - 1) {
        return;
      }
      for (auto u = v + v; u <= max_v; u += v) {
        rec(u, fn + 1);
      }
    };

    FOR(v, 1, max_v) {
      // std::cerr << "v0=" << v << std::endl;
      rec(v, 0);
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().idealArrays(2, 5);
    assert(a_out == 10);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().idealArrays(5, 3);
    assert(a_out == 11);

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
