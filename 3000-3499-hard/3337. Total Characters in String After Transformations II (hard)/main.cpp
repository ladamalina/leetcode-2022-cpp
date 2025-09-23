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
using Mt = std::array<std::array<ll, 26>, 26>;

Mt operator*(const Mt& m1, const Mt& m2) {
  Mt res{};
  for (int i = 0; i < SZ(m1); ++i) {
    for (int j = 0; j < SZ(m1); ++j) {
      for (int k = 0; k < SZ(m1); ++k) {
        res[i][j] = (res[i][j] + m1[i][k] * m2[k][j]) % MOD;
      }
    }
  }
  return res;
}

Mt MatrixPow(Mt m, int pow) {
  Mt res{};
  for (int i = 0; i < SZ(m); ++i) {
    res[i][i] = 1;
  }

  while (pow > 0) {
    if (pow % 2 == 1) {
      res = res * m;
    }
    m = m * m;
    pow /= 2;
  }
  return res;
}

class Solution {
public:
  int lengthAfterTransformations(const std::string& s, int t, const vi& nums) {
    std::array<ll, 26> c_freq{};
    for (const auto c : s) ++c_freq[c - 'a'];

    Mt transform{};
    FOR(i, 0, SZ(nums)-1) {
      FOR(j, 1, nums[i]) {
        transform[(i+j)%26][i] = 1;
      }
    }
    const auto transformed = MatrixPow(transform, t);

    std::array<ll, 26> f_freq{};
    for (int i = 0; i < 26; ++i) {
      for (int j = 0; j < 26; ++j) {
        f_freq[i] = (f_freq[i] + transformed[i][j] * c_freq[j]) % MOD;
      }
    }

    ll res = 0;
    for (const auto f : f_freq) {
      res = (res + f) % MOD;
    }
    
    return res;
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
