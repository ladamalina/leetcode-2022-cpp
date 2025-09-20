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
using vvl [[maybe_unused]] = std::vector<vl>;
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
  int kthSmallest(const vvi& mat, int k) {
    const auto m = SZ(mat), n = SZ(mat[0]);

    const std::function<int(int,int,int,int)> count_lte_sums = [&](int target_sum, int i, int sum, int curr_k) {
      if (sum > target_sum) return 0;
      if (i == m) return 1; // found a valid array with sum <= targetSum
      auto res = 0;
      for (auto j = 0; j < n; ++j) {
        const auto cnt = count_lte_sums(target_sum, i+1, sum + mat[i][j], curr_k - res);
        if (cnt == 0)
          break;
        res += cnt;
        if (res > curr_k)
          break;
      }
      return res;
    };
    
    auto lo = m, hi = m * 5000;
    while (lo < hi) {
      const auto mid = (lo + hi) / 2;
      const auto cnt = count_lte_sums(mid, 0, 0, k);
      if (cnt >= k)
        hi = mid;
      else
        lo = mid + 1;
    }
    return hi;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{1,3,11},{2,4,6}};
    const auto a_out = Solution().kthSmallest(mat, 5);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{1,3,11},{2,4,6}};
    const auto a_out = Solution().kthSmallest(mat, 9);
    assert(a_out == 17);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi mat{{1,10,10},{1,4,5},{2,3,6}};
    const auto a_out = Solution().kthSmallest(mat, 7);
    assert(a_out == 9);
  
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
