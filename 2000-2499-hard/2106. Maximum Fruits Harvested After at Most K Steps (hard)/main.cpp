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

using namespace std;
using ll = long long;
constexpr int MAX_X = 2 * 1e5;
array<int, MAX_X + 1> psum;

class Solution {
public:
  int maxTotalFruits(const vector<vector<int>>& fruits, const int start, const int k) {
    const int fn = fruits.size();
    const auto max_fx = std::max(fruits[fn-1][0], start);
    std::fill(psum.begin(), psum.begin() + max_fx + 1, 0);
    {
      auto fi = 0;
      for (auto x = 0; x <= max_fx; ++x) {
        psum[x] = x > 0 ? psum[x-1] : 0;
        if (fi < fn && fruits[fi][0] == x) {
          psum[x] += fruits[fi][1];
          ++fi;
        }
      }
    }
    
    auto max_res = 0;
    for (auto fi = 0; fi < fn; ++fi) {
      const auto x = fruits[fi][0];
      if (x < start) {
        const auto dl = start - x;
        if (dl <= k) {
          auto res = psum[start] - (x > 0 ? psum[x-1] : 0);
          const auto dr = k - (dl << 1);
          if (dr > 0) {
            const auto rx = std::min(max_fx, start + dr);
            res += psum[rx] - psum[start];
          }
          max_res = max(max_res, res);
        }
      } else if (x > start) {
        const auto dr = x - start;
        if (dr <= k) {
          auto res = psum[x] - (start > 0 ? psum[start-1] : 0);
          const auto dl = k - (dr << 1);
          if (dl > 0) {
            const auto lx = std::max(0, start - dl);
            res += (start > 0 ? psum[start-1] : 0) - (lx > 0 ? psum[lx-1] : 0);
          }
          max_res = max(max_res, res);
        }
      } else { // x == start
        const auto res = psum[start] - (start > 0 ? psum[start-1] : 0);
        max_res = max(max_res, res);
      }
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<vector<int>> fruits{{2,8},{6,3},{8,6}};
    const auto a_out = Solution().maxTotalFruits(fruits, 5, 4);
    assert(a_out == 9);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<vector<int>> fruits{{0,9},{4,1},{5,7},{6,2},{7,4},{10,9}};
    const auto a_out = Solution().maxTotalFruits(fruits, 5, 4);
    assert(a_out == 14);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<vector<int>> fruits{{0,3},{6,4},{8,5}};
    const auto a_out = Solution().maxTotalFruits(fruits, 3, 2);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<vector<int>> fruits{{200000,10000}};
    const auto a_out = Solution().maxTotalFruits(fruits, 200000, 0);
    assert(a_out == 10000);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<vector<int>> fruits{{0,10000}};
    const auto a_out = Solution().maxTotalFruits(fruits, 200000, 200000);
    assert(a_out == 10000);
  
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
