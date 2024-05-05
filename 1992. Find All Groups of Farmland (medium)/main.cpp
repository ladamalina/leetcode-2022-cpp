#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

constexpr int MAX_N = 300;
std::array<std::array<int, MAX_N>, MAX_N> b;

class Solution {
  public:
  static vvi findFarmland(const vvi& a) {
    const auto n = CI(a.size());
    const auto m = CI(a[0].size());
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        b[i][j] = a[i][j] + (i-1>=0 ? b[i-1][j] : 0) + (j-1>=0 ? b[i][j-1] : 0) - (i-1>=0&&j-1>=0 ? b[i-1][j-1] : 0);
      }
    }

    const auto check_sq = [&](int i, int j, int i2, int j2) {
      const auto sq_sum = b[i2][j2] - (i-1>=0 ? b[i-1][j2] : 0) - (j-1>=0 ? b[i2][j-1] : 0) + (i-1>=0&&j-1>=0 ? b[i-1][j-1] : 0);
      return sq_sum == (i2-i+1)*(j2-j+1);
    };
    
    vvi res;
    FOR(i, 0, n-1) {
      FOR(j, 0, m-1) {
        if (a[i][j]==1 && (i-1<0 || a[i-1][j]==0) && (j-1<0 || a[i][j-1]==0)) {
          auto sq = 1;
          {
            auto l = 1, r = std::min(n-i, m-j);
            while (l < r) {
              const auto mid = (l+r+1)/2;
              if (check_sq(i, j, i+mid-1, j+mid-1)) l = mid;
              else r = mid-1;
            }
            sq = r;
          }
          auto max_i = i;
          {
            auto l = i, r = n-1;
            while (l < r) {
              const auto mid = (l+r+1)/2;
              if (check_sq(i, j, mid, j+sq-1)) l = mid;
              else r = mid-1;
            }
            max_i = r;
          }
          auto max_j = j;
          {
            auto l = j, r = m-1;
            while (l < r) {
              const auto mid = (l+r+1)/2;
              if (check_sq(i, j, i+sq-1, mid)) l = mid;
              else r = mid-1;
            }
            max_j = r;
          }
          
          res.push_back({i,j,max_i,max_j});
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,0,0},{0,1,1},{0,1,1}};
    auto a_out = Solution::findFarmland(grid);
    SORT(a_out);
    const vvi e_out{{0,0,0,0},{1,1,2,2}};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,1},{1,1}};
    auto a_out = Solution::findFarmland(grid);
    SORT(a_out);
    const vvi e_out{{0,0,1,1}};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{0}};
    auto a_out = Solution::findFarmland(grid);
    SORT(a_out);
    const vvi e_out{};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi grid{{1,1},{0,0}};
    auto a_out = Solution::findFarmland(grid);
    SORT(a_out);
    const vvi e_out{{0,0,0,1}};
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
