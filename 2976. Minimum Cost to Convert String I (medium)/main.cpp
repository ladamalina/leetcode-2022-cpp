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
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

class Solution {
public:
  long long minimumCost(const std::string& source, const std::string& target,
      const vc& original, const vc& changed, const vi& cost) {

    const auto sn = SZ(source);
    const auto cn = SZ(original);

    vvi d(26, vi(26, INT_MAX));
    FOR(i, 0, 25) d[i][i] = 0;
    FOR(i, 0, cn-1) {
      const auto v = original[i]-'a';
      const auto u = changed[i]-'a';
      d[v][u] = std::min(d[v][u], cost[i]);
    }

    for (int k=0; k<26; ++k)
      for (int i=0; i<26; ++i)
        for (int j=0; j<26; ++j)
          if (d[i][k] < INT_MAX && d[k][j] < INT_MAX)
            d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

    ll res = 0;
    bool ok = true;
    FOR(i, 0, sn-1) {
      const auto v = source[i]-'a';
      const auto u = target[i]-'a';
      if (d[v][u] == INT_MAX) { ok = false; break; }
      res += d[v][u];
    }
    return ok ? res : -1;
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
