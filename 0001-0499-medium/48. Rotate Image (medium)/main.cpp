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
  void rotate(vvi& g) {
    const auto n = SZ(g);
    auto l = 0;
    while (l+1 <= n/2) {
      const auto cnt = (n - l*2);
      FOR(k, 0, cnt-2) {
        auto tmp = g[l][l+k];
        // std::cerr << l << ',' << l+k << '\t'
        //           << l+k << ',' << n-1-l << '\t'
        //           << n-1-l << ',' << n-1-l-k << '\t'
        //           << n-1-l-k << ',' << l << '\n';
        std::swap(tmp, g[l+k][n-1-l]);
        std::swap(tmp, g[n-1-l][n-1-l-k]);
        std::swap(tmp, g[n-1-l-k][l]);
        std::swap(tmp, g[l][l+k]);
      }
      ++l;
    }
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{1,2,3},{4,5,6},{7,8,9}};
    Solution().rotate(g);
    const vvi e_out{{7,4,1},{8,5,2},{9,6,3}};
    assert(g == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    Solution().rotate(g);
    const vvi e_out{{15,13,2,5},{14,3,4,1},{12,6,8,9},{16,7,10,11}};
    assert(g == e_out);
  
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
