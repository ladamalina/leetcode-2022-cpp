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

constexpr int MAX_N = 500;
std::array<int, MAX_N*2> us;
std::array<int, MAX_N> l_freq;

bool HasCommon(const vi& a, const vi& b) {
  const auto an = SZ(a), bn = SZ(b);
  auto ai = 0, bi = 0;
  while (ai < an && bi < bn) {
    if (a[ai] < b[bi]) ++ai;
    else if (a[ai] > b[bi]) ++bi;
    else return true;
  }
  return false;
}

class Solution {
public:
  int minimumTeachings(const int n, vvi& ls, vvi& fs) {
    const auto m = SZ(ls);
    for (auto& u_ls : ls) SORT(u_ls);

    auto un = 0;
    for (const auto& p : fs) {
      const auto u = p[0] - 1, v = p[1] - 1;
      if (!HasCommon(ls[u], ls[v])) {
        us[un++] = u;
        us[un++] = v;
      }
    }
    std::sort(us.begin(), us.begin() + un);
    un = std::unique(us.begin(), us.begin() + un) - us.begin();

    std::fill(l_freq.begin(), l_freq.begin() + n, 0);
    for (auto it = us.begin(); it != us.begin() + un; ++it) {
      for (const auto l : ls[*it]) {
        ++l_freq[l-1];
      }
    }
    
    auto res = m;
    FOR(l, 0, n - 1) {
      res = std::min(res, un - l_freq[l]);
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi ls{{1}, {2}, {1, 2}};
    vvi fs{{1, 2}, {1, 3}, {2, 3}};
    const auto a_out = Solution().minimumTeachings(2, ls, fs);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi ls{{2}, {1, 3}, {1, 2}, {3}};
    vvi fs{{1, 4}, {1, 2}, {3, 4}, {2, 3}};
    const auto a_out = Solution().minimumTeachings(3, ls, fs);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi ls{{3, 11, 5, 10, 1, 4, 9, 7, 2, 8, 6},
           {5, 10, 6, 4, 8, 7},
           {6, 11, 7, 9},
           {11, 10, 4},
           {6, 2, 8, 4, 3},
           {9, 2, 8, 4, 6, 1, 5, 7, 3, 10},
           {7, 5, 11, 1, 3, 4},
           {3, 4, 11, 10, 6, 2, 1, 7, 5, 8, 9},
           {8, 6, 10, 2, 3, 1, 11, 5},
           {5, 11, 6, 4, 2}};
    vvi fs{{7, 9}, {3, 7}, {3, 4}, {2, 9}, {1, 8}, {5, 9}, {8, 9}, {6, 9}, {3, 5}, {4, 5},
           {4, 9}, {3, 6}, {1, 7}, {1, 3}, {2, 8}, {2, 6}, {5, 7}, {4, 6}, {5, 8}, {5, 6},
           {2, 7}, {4, 8}, {3, 8}, {6, 8}, {2, 5}, {1, 4}, {1, 9}, {1, 6}, {6, 7}};
    const auto a_out = Solution().minimumTeachings(11, ls, fs);
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
