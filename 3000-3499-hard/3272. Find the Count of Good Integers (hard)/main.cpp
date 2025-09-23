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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

vi fac(11);
bool init_fac = false;

class Solution {
public:
  ll countGoodIntegers(int n, int k) {
    if (!init_fac) {
      fac[0] = 1;
      FOR(i, 1, 10) fac[i] = fac[i-1] * i;
      init_fac = true;
    }

    std::unordered_set<std::string> x_str_set;
    const auto hn = (n&1) ? n/2 + 1 : n/2;

    std::string s;
    const std::function<void(int)> rec = [&](const int i){
      if (i == hn) {
        auto x_str = s;
        auto j = (n & 1) ? SZ(s)-2 : SZ(s)-1;
        while (j >= 0) x_str += s[j--];
        const auto x = std::stoll(x_str);
        if (x % k == 0) {
          // std::cerr << x_str << '\n';
          SORT(x_str);
          x_str_set.insert(x_str);
        }
        return;
      }
      const auto min_c = (i == 0) ? '1' : '0';
      for (auto c = min_c; c <= '9'; ++c) {
        s.push_back(c);
        rec(i+1);
        s.pop_back();
      }
    };
    rec(0);

    ll res = 0;
    for (const auto& x_str : x_str_set) {
      std::array<int, 10> d_freq{};
      for (const auto c : x_str) ++d_freq[c-'0'];
      ll x_res = 0;
      FOR(d, 1, 9) {
        if (d_freq[d] == 0) continue;
        ll d_res = fac[n-1];
        FOR(d2, 0, 9) {
          if (d_freq[d2] == 0) continue;
          d_res /= (d == d2) ? fac[d_freq[d2]-1] : fac[d_freq[d2]];
        }
        x_res += d_res;
      }
      res += x_res;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().countGoodIntegers(3, 5);
    assert(a_out == 27);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().countGoodIntegers(1, 4);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution().countGoodIntegers(5, 6);
    assert(a_out == 2468);

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
