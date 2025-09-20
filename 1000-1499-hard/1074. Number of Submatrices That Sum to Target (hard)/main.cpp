// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define CI(_v) static_cast<int>(_v)

int psum[1000][1000];

class Solution {
 public:
  static int numSubmatrixSumTarget(const vvi& matrix, int target) {
    const auto n = CI(matrix.size());
    const auto m = CI(matrix[0].size());
    
    FOR(i, 0, n-1) {
      psum[i][0] = matrix[i][0];
      FOR(j, 1, m-1) {
        psum[i][j] = psum[i][j-1] + matrix[i][j];
      }
    }
    
    int res = 0;
    
    std::unordered_map<int, int> prev_sums;
    FOR(lj, 0, m-1) {
      FOR(rj, lj, m-1) {
        prev_sums = {{0, 1}};
        int rows_sum = 0;
        FOR(i, 0, n-1) {
          rows_sum += psum[i][rj] - (lj > 0 ? psum[i][lj-1] : 0);
          // rows_sum - prev_sum = target => rows_sum - target = prev_sum
          const auto it = prev_sums.find(rows_sum - target);
          if (it != prev_sums.end())
            res += it->second;
          ++prev_sums[rows_sum];
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi matrix{{0,1,0},{1,1,1},{0,1,0}};
    const auto a_out = Solution::numSubmatrixSumTarget(matrix, 0);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi matrix{{1,-1},{-1,1}};
    const auto a_out = Solution::numSubmatrixSumTarget(matrix, 0);
    assert(a_out == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi matrix{{904}};
    const auto a_out = Solution::numSubmatrixSumTarget(matrix, 0);
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
