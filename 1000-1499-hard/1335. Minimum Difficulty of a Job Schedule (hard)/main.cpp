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
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;

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

template<typename T>
class SparseTable {
  public:
  explicit SparseTable(const std::vector<T>& a) {
    const auto n = CI(a.size());
    const auto h_max = 31 - __builtin_clz(n);
    rmq_ = std::vector<std::vector<T>>(h_max+1, std::vector<T>(n));
    rmq_[0] = a;
    FOR(h, 1, h_max) {
      FOR(i, 0, n-(1<<h)) {
        rmq_[h][i] = std::max(rmq_[h-1][i], rmq_[h-1][i+(1<<(h-1))]);
      }
    }
  }

  T GetMax(int l, int r) const {
    const auto len = r - l + 1;
    const auto h = 31 - __builtin_clz(len);
    return std::max(rmq_[h][l], rmq_[h][r-(1<<h)+1]);
  }

  private:
  std::vector<std::vector<T>> rmq_;
};

class Solution {
  public:
  static int minDifficulty(const vi& jobs, const int d) {
    const auto n = CI(jobs.size());
    if (d > n) return -1;
    SparseTable rmq(jobs);
    vvi dp(n, vi(d, -1));
    FOR(i, 0, n-1) {
      dp[i][d-1] = rmq.GetMax(0, i);
    }
    FOR(i, 1, n-1) {
      FOR(j, 0, i-1) {
        const auto x = rmq.GetMax(j+1, i);
        FOR(dx, 1, d-1) {
          if (dp[j][dx] != -1) {
            dp[i][dx-1] = (dp[i][dx-1] == -1) ? dp[j][dx]+x : std::min(dp[i][dx-1], dp[j][dx]+x);
          }
        }
      }
    }
    return dp[n-1][0];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi jobs{6,5,4,3,2,1};
    const auto a_out = Solution::minDifficulty(jobs, 2);
    assert(a_out == 7);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi jobs{9,9,9};
    const auto a_out = Solution::minDifficulty(jobs, 4);
    assert(a_out == -1);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vi jobs{1,1,1};
    const auto a_out = Solution::minDifficulty(jobs, 3);
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
