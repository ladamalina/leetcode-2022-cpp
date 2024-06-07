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

template <typename T>
class SparseTable {
public:
  explicit SparseTable(const std::vector<T>& a) {
    const auto n = CI(a.size());
    const auto h_max = 31 - __builtin_clz(n);
    rmq_ = std::vector<std::vector<T>>(h_max + 1, std::vector<T>(n));
    rmq_[0] = a;
    FOR(h, 1, h_max) {
      FOR(i, 0, n-(1<<h)) {
        rmq_[h][i] = std::max(rmq_[h - 1][i], rmq_[h - 1][i + (1 << (h - 1))]);
      }
    }
  }

  T GetMax(int l, int r) const {
    const auto len = r - l + 1;
    const auto h = 31 - __builtin_clz(len);
    return std::max(rmq_[h][l], rmq_[h][r - (1 << h) + 1]);
  }

private:
  std::vector<std::vector<T>> rmq_;
};

class Solution {
public:
  int minHeightShelves(const vvi& books, int target_w) {
    const auto n = SZ(books);
    
    vi w_psum(n);
    vi hs(n);
    FOR(i, 0, n-1) {
      w_psum[i] = books[i][0] + (i>0 ? w_psum[i-1] : 0);
      hs[i] = books[i][1];
    }
    SparseTable rmq_max(hs);

    vi dp(n, INT_MAX);
    FOR(i, 0, n-1) {
      if (w_psum[i] <= target_w) {
        const auto shelf_h = rmq_max.GetMax(0, i);
        dp[i] = std::min(dp[i], shelf_h);
      }
      FOR(j, 0, i-1) {
        const auto shelf_w = w_psum[i] - w_psum[j];
        if (shelf_w <= target_w) {
          const auto shelf_h = rmq_max.GetMax(j+1, i);
          dp[i] = std::min(dp[i], dp[j]+shelf_h);
        }
      }
    }
    return dp[n-1];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi books{{1,1},{2,3},{2,3},{1,1},{1,1},{1,1},{1,2}};
    const auto a_out = Solution().minHeightShelves(books, 4);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi books{{1,3},{2,4},{3,2}};
    const auto a_out = Solution().minHeightShelves(books, 6);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi books{{7,3},{8,7},{2,7},{2,5}};
    const auto a_out = Solution().minHeightShelves(books, 10);
    assert(a_out == 15);
  
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
