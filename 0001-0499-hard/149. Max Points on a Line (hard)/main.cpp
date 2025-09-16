//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vdd [[maybe_unused]] = std::vector<pdd>;
using vvdd [[maybe_unused]] = std::vector<vdd>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

const auto EPS = 1e-9;
template <typename T>
[[maybe_unused]] bool Eq(T a, T b) { return std::abs(a - b) < EPS; }
template <typename T>
[[maybe_unused]] bool Eq(const std::pair<T, T>& a, const std::pair<T, T>& b) {
  return std::abs(a.F - b.F) < EPS && std::abs(a.S - b.S) < EPS;
}

class Solution {
  public:
  static int maxPoints(const vvi& points) {
    const auto n = CI(points.size());
    if (n == 1) return 1;
    vvdd abs(n, vdd(n));
    FOR(i, 0, n-1) {
      const ii p1{points[i][0], points[i][1]};
      FOR(j, 0, n-1) {
        if (i == j) continue;
        const ii p2{points[j][0], points[j][1]};
        std::pair<double, double> line;
        if (p1.F == p2.F) {
          line = {DBL_MAX, p1.F};
        } else if (p1.S == p2.S) {
          line = {0, p1.S};
        } else {
          const auto a = double(p1.S-p2.S)/double(p1.F-p2.F);
          const auto b = p1.S - a*p1.F;
          line = {a, b};
        }
        abs[i][j] = line;
      }
    }
    int max_freq = 1;
    FOR(i, 0, n-1) {
      vdd lines;
      lines.reserve(n-1);
      FOR(j, 0, n-1) {
        if (i == j) continue;
        lines.PB(abs[i][j]);
      }
      SORT(lines);
      int i_max_freq = 1;
      int freq = 1;
      FOR(i, 1, n-2) {
        if (Eq(lines[i-1], lines[i])) {
          ++freq;
        } else {
          i_max_freq = std::max(i_max_freq, freq);
          freq = 1;
        }
      }
      i_max_freq = std::max(i_max_freq, freq);
      max_freq = std::max(max_freq, i_max_freq);
    }
    return max_freq+1;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi points{{1,1},{2,2},{3,3}};
    const auto a_out = Solution::maxPoints(points);
    assert(a_out == 3);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi points{{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    const auto a_out = Solution::maxPoints(points);
    assert(a_out == 4);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi points{{-6,-1},{3,1},{12,3}};
    const auto a_out = Solution::maxPoints(points);
    assert(a_out == 3);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi points{{0,0}};
    const auto a_out = Solution::maxPoints(points);
    assert(a_out == 1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi points{{3,3},{1,4},{1,1},{2,1},{2,2}};
    const auto a_out = Solution::maxPoints(points);
    assert(a_out == 3);
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
