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
    //    const auto h_max = std::ceil(std::log2(n));
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
  vi leftmostBuildingQueries(const vi& heights, const vvi& queries) {
    const auto n = SZ(heights), qn = SZ(queries);
    SparseTable rmq(heights);
    vi res(qn);
    FOR(qi, 0, qn-1) {
      const auto a = std::min(queries[qi][0], queries[qi][1]),
        b = std::max(queries[qi][0], queries[qi][1]);
      if (a == b || heights[a] < heights[b]) {
        res[qi] = b;
        continue;
      } // heights[a] >= heights[b]

      auto lo = b, hi = n-1;
      while (lo < hi) {
        const auto mid = (lo + hi) / 2;
        const auto max_h = rmq.GetMax(b, mid);
        if (heights[a] < max_h)
          hi = mid;
        else
          lo = mid + 1;
      }
      const auto max_h = rmq.GetMax(b, hi);
      res[qi] = (heights[a] < max_h) ? hi : -1;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi heights{6,4,8,5,2,7};
    const vvi queries{{0,1},{0,3},{2,4},{3,4},{2,2}};
    const auto a_out = Solution().leftmostBuildingQueries(heights, queries);
    const vi e_out{2,5,-1,5,2};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi heights{5,3,8,2,6,1,4,6};
    const vvi queries{{0,7},{3,5},{5,2},{3,0},{1,6}};
    const auto a_out = Solution().leftmostBuildingQueries(heights, queries);
    const vi e_out{7,6,-1,4,6};
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
