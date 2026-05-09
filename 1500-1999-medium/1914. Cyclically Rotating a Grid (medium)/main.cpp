#include <bits/stdc++.h>
#include <cassert>

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

constexpr int MAX_N = 50, MAX_L = MAX_N * 4;
int r[MAX_L], c[MAX_L], val[MAX_L];

class Solution {
 public:
  vvi rotateGrid(vvi& g, const int k) {
    const auto m = SZ(g), n = SZ(g[0]);
    const auto nl = std::min(m >> 1, n >> 1);
    FOR(l, 0, nl - 1) {
      auto len = 0;
      for (auto i = l; i < m - l - 1; ++i) {
        r[len] = i, c[len] = l, val[len] = g[i][l];
        len++;
      }
      for (auto j = l; j < n - l - 1; ++j) {
        r[len] = m - l - 1, c[len] = j, val[len] = g[m - l - 1][j];
        len++;
      }
      for (auto i = m - l - 1; i > l; --i) {
        r[len] = i, c[len] = n - l - 1, val[len] = g[i][n - l - 1];
        len++;
      }
      for (auto j = n - l - 1; j > l; --j) {
        r[len] = l, c[len] = j, val[len] = g[l][j];
        len++;
      }
      const auto kk = k % len;
      FOR(i, 0, len - 1) {
        const auto idx = (i + len - kk) % len;
        g[r[i]][c[i]] = val[idx];
      }
    }
    return g;
  }
};

#ifndef NDEBUG
[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{40, 10}, {30, 20}};
    const vvi e_out{{10, 20}, {40, 30}};
    const auto a_out = Solution().rotateGrid(g, 1);
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi g{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
    const vvi e_out{{3, 4, 8, 12}, {2, 11, 10, 16}, {1, 7, 6, 15}, {5, 9, 13, 14}};
    const auto a_out = Solution().rotateGrid(g, 2);
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}
#endif

int main() {
#ifndef NDEBUG
  TestSolution();
  return 0;
#endif
  return 0;
}
