//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<ld>;

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

int GetMinRes(const vi& rows, int n) {
  std::unordered_map<int, int> rows_freq;
  for (const auto x : rows)
    ++rows_freq[x];
  if (rows_freq.size() != 2)
    return INT_MAX;

  auto r1 = rows_freq.begin()->F;
  auto f1 = rows_freq.begin()->S;
  auto r2 = std::next(rows_freq.begin())->F;
  auto f2 = std::next(rows_freq.begin())->S;

  if (n%2==0 && f1 == f2 && __builtin_popcount(r1) == n/2) {
    int cnt_r1 = 0;
    FOR(i, 0, n-1) {
      if ((i%2==0 && rows[i]!=r1) || (i%2==1 && rows[i]!=r2))
        ++cnt_r1;
    }
    int cnt_r2 = 0;
    FOR(i, 0, n-1) {
      if ((i%2==0 && rows[i]!=r2) || (i%2==1 && rows[i]!=r1))
        ++cnt_r2;
    }
    return std::min(cnt_r1/2, cnt_r2/2);
  }

  if (n%2==1 && std::abs(f1-f2)==1) {
    if (f1 < f2) {
      std::swap(r1, r2);
      std::swap(f1, f2);
    }
    if (!(__builtin_popcount(r1) == n/2+1 && __builtin_popcount(r2) == n/2)
        && !(__builtin_popcount(r1) == n/2 && __builtin_popcount(r2) == n/2+1))
      return INT_MAX;

    int cnt_r1 = 0;
    FOR(i, 0, n-1) {
      if ((i%2==0 && rows[i]!=r1) || (i%2==1 && rows[i]!=r2))
        ++cnt_r1;
    }
    return cnt_r1/2;
  }

  return INT_MAX;
}

class Solution {
public:
  static int movesToChessboard(const vvi& grid) {
    const auto n = CI(grid.size());

    vi rows(n);
    FOR(i, 0, n-1) {
      FOR(j, 0, n-1) {
        if (grid[i][j] == 1) {
          rows[i] |= (1<<j);
        }
      }
    }
    const auto rows_res = GetMinRes(rows, n);

    vi cols(n);
    FOR(j, 0, n-1) {
      FOR(i, 0, n-1) {
        if (grid[i][j] == 1) {
          cols[j] |= (1<<i);
        }
      }
    }
    const auto cols_res = GetMinRes(cols, n);

    if (rows_res != INT_MAX && cols_res != INT_MAX) {
      return rows_res + cols_res;
    }
    return -1;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{0,1,1,0},{0,1,1,0},{1,0,0,1},{1,0,0,1}};
    const auto a_out = Solution::movesToChessboard(grid);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{0,1},{1,0}};
    const auto a_out = Solution::movesToChessboard(grid);
    assert(a_out == 0);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,0},{1,0}};
    const auto a_out = Solution::movesToChessboard(grid);
    assert(a_out == -1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{0,0,1,1},{1,1,0,0},{0,1,0,1},{1,0,1,0}};
    const auto a_out = Solution::movesToChessboard(grid);
    assert(a_out == -1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{0,0,0},{0,0,1},{0,0,0}};
    const auto a_out = Solution::movesToChessboard(grid);
    assert(a_out == -1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,1,0},{0,0,1},{0,0,1}};
    const auto a_out = Solution::movesToChessboard(grid);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi grid{{1,0,0},{0,1,1},{1,0,0}};
    const auto a_out = Solution::movesToChessboard(grid);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
