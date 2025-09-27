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

constexpr int MAX_X = 9;
std::array<int, MAX_X + 1> f0, f1;

class Solution {
public:
  int score(vs& cards, char x) {
    std::fill(RNG(f0), 0);
    std::fill(RNG(f1), 1);
    auto f2 = 0, res = 0;
    for (const auto& s : cards) {
      f0[s[0]-'a'] += (s[0] != x && s[1] == x);
      f1[s[1]-'a'] += (s[0] == x && s[1] != x);
      f2 += (s[0] == x && s[1] == x);
    }

    std::priority_queue<int, vi, std::less<>> pq0, pq1;
    FOR(i, 0, MAX_X) if (f0[i]) pq0.push(f0[i]);
    FOR(i, 0, MAX_X) if (f1[i]) pq1.push(f1[i]);
    while (SZ(pq0) > 1) {
      const auto a = pq0.top(); pq0.pop();
      const auto b = pq0.top(); pq0.pop();
      ++res;
      if (a > 1) pq0.push(a - 1);
      if (b > 1) pq0.push(b - 1);
    }
    while (SZ(pq1) > 1) {
      const auto a = pq1.top(); pq1.pop();
      const auto b = pq1.top(); pq1.pop();
      ++res;
      if (a > 1) pq1.push(a - 1);
      if (b > 1) pq1.push(b - 1);
    }

    const auto last_f0 = pq0.empty() ? 0 : pq0.top();
    const auto last_f1 = pq1.empty() ? 0 : pq1.top();
    const auto prev_res = res;
    if (f2 && last_f0) {
      const auto add = std::min(f2, last_f0);
      res += add;
      f2 -= add;
    }
    if (f2 && last_f1) {
      const auto add = std::min(f2, last_f1);
      res += add;
      f2 -= add;
    }
    if (f2) {
      res += std::min(prev_res, (f2 >> 1));
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vs cards{"ab"s, "aa"s, "ab"s, "bc"s, "cc"s, "bc"s, "bb"s, "ac"s, "bc"s, "bc"s, "aa"s, "aa"s, "ba"s, "bc"s, "cb"s, "ba"s, "ac"s,
             "bb"s, "cb"s, "ac"s, "cb"s, "cb"s, "ba"s, "bc"s, "ca"s, "ba"s, "bb"s, "cc"s, "cc"s, "ca"s, "ab"s, "bb"s, "bc"s, "ba"s,
             "ac"s, "bc"s, "ac"s, "ac"s, "bc"s, "bb"s, "bc"s, "ac"s, "bc"s, "aa"s, "ba"s, "cc"s, "ac"s, "bb"s, "ba"s, "bb"s};
    const auto a_out = Solution().score(cards, 'b');
    assert(a_out == 16);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vs cards{"aa"s,"ab"s,"ba"s,"ac"s};
    const auto a_out = Solution().score(cards, 'a');
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vs cards{"aa"s,"ab"s,"ba"s};
    const auto a_out = Solution().score(cards, 'a');
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vs cards{"aa"s,"ab"s,"ba"s,"ac"s};
    const auto a_out = Solution().score(cards, 'b');
    assert(a_out == 0);
  
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
