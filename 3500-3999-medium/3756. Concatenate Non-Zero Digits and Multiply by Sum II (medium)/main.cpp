// #include <bits/stdc++.h>
// #include <cassert>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfloat>
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
#include <numbers>
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

constexpr int MOD = 1e9+7;
constexpr int MAX_N = 1e5;
int psum[MAX_N], pcnt[MAX_N];
ll pow10[MAX_N+1], pref[MAX_N];

ll ModSum(const ll a, const ll b, const ll m = MOD) { return (a + b) % m; }
ll ModSub(const ll a, const ll b, const ll m = MOD) { return (a - b + m) % m; }
ll ModMult(const ll a, const ll b, const ll m = MOD) { return (a * b) % m; }
ll ModPow(ll a, ll x, const ll m = MOD) {
  ll ret = 1;
  while (x) {
    if (x & 1) ret = (ret * a) % m;
    x = (x >> 1);
    a = (a * a) % m;
  }
  return ret;
}
ll ModInv(const ll a, const ll m = MOD) { return ModPow(a, m - 2, m); }
ll ModDiv(const ll a, const ll b, const ll m = MOD) { return (a * ModInv(b)) % m; }

int init = []() {
  pow10[0] = 1;
  FOR(i, 1, MAX_N) pow10[i] = (pow10[i-1] * 10) % MOD;
  return 0;
}();

class Solution {
public:
  vi sumAndMultiply(std::string& s, vvi& queries) {
    const auto n = SZ(s), qn = SZ(queries);
    FOR(i, 0, n-1) {
      const auto d = CI(s[i] - '0');
      psum[i] = d + (i ? psum[i-1] : 0);
      pcnt[i] = CI(d != 0) + (i ? pcnt[i-1] : 0);
      pref[i] = i ? (d != 0 ? (pref[i-1] * 10 + d) % MOD : pref[i-1]) : d;
    }
    vi res(qn);
    FOR(i, 0, qn-1) {
      const auto l = queries[i][0], r = queries[i][1];
      const auto cnt = pcnt[r] - (l ? pcnt[l-1] : 0);
      if (cnt == 0) continue;
      const auto x = (pref[r] - (l ? pref[l-1] : 0ll) * pow10[cnt] % MOD + MOD) % MOD;
      const auto sum = psum[r] - (l ? psum[l-1] : 0);
      res[i] = (x * sum) % MOD;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s("10203004"s);
    vvi queries{{0,7},{1,3},{4,6}};
    const auto a_out = Solution().sumAndMultiply(s, queries);
    const vi e_out{12340, 4, 9};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s("1000"s);
    vvi queries{{0,3},{1,1}};
    const auto a_out = Solution().sumAndMultiply(s, queries);
    const vi e_out{1, 0};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    std::string s("9876543210"s);
    vvi queries{{0,9}};
    const auto a_out = Solution().sumAndMultiply(s, queries);
    const vi e_out{444444137};
    assert(a_out == e_out);
  
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
