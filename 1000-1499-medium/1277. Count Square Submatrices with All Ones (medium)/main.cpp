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

constexpr int MAX_N = 300;
std::array<std::array<int, MAX_N>, MAX_N> g;

class Solution {
public:
  int countSquares(const vvi& matrix) {
    const auto m = SZ(matrix), n = SZ(matrix[0]);
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        g[i][j] = matrix[i][j] + (i > 0 ? g[i-1][j] : 0) + (j > 0 ? g[i][j-1] : 0)
          - (i > 0 && j > 0 ? g[i-1][j-1] : 0);
      }
    }
    int res = 0;
    FOR(i, 0, m-1) {
      FOR(j, 0, n-1) {
        if (matrix[i][j] == 1) {
          auto l = 1, r = std::min(m-i, n-j);
          while (l < r) {
            const auto k = (l + r + 1) >> 1;
            const auto i2 = i + k - 1, j2 = j + k - 1;
            const auto k_sum = g[i2][j2] - (i > 0 ? g[i-1][j2] : 0) - (j > 0 ? g[i2][j-1] : 0)
              + (i > 0 && j > 0 ? g[i-1][j-1] : 0);
            if (k_sum == k * k)
              l = k;
            else
              r = k - 1;
          }
          res += r;
        }
      }
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
