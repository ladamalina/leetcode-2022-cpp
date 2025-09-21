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
class SparseTableMin {
public:
  explicit SparseTableMin(const std::vector<T>& a) {
    const auto n = CI(a.size());
    const auto h_max = 31 - __builtin_clz(n);
    //    const auto h_max = std::ceil(std::log2(n));
    rmq_ = std::vector<std::vector<T>>(h_max + 1, std::vector<T>(n));
    rmq_[0] = a;
    FOR(h, 1, h_max) {
      FOR(i, 0, n-(1<<h)) {
        rmq_[h][i] = std::min(rmq_[h - 1][i], rmq_[h - 1][i + (1 << (h - 1))]);
      }
    }
  }

  T GetMin(int l, int r) const {
    const auto len = r - l + 1;
    const auto h = 31 - __builtin_clz(len);
    return std::min(rmq_[h][l], rmq_[h][r - (1 << h) + 1]);
  }

private:
  std::vector<std::vector<T>> rmq_;
};

template <typename T>
class SparseTableMax {
public:
  explicit SparseTableMax(const std::vector<T>& a) {
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
  ll countSubarrays(const vi& nums, const int min_k, const int max_k) {
    const auto n = SZ(nums);
    vi min_k_ids, max_k_ids;
    FOR(i, 0, n-1) {
      if (nums[i] == min_k)
        min_k_ids.push_back(i);
      if (nums[i] == max_k)
        max_k_ids.push_back(i);
    }
    const SparseTableMin rmq_min(nums);
    const SparseTableMax rmq_max(nums);

    ll res = 0;
    FOR(i, 0, n-1) {
      if (nums[i] < min_k || nums[i] > max_k)
        continue;
      const auto it1 = std::lower_bound(RNG(min_k_ids), i);
      const auto it2 = std::lower_bound(RNG(max_k_ids), i);
      if (it1 == min_k_ids.end() || it2 == max_k_ids.end())
        continue;

      const auto j = std::max(*it1, *it2);
      const auto j_mn = rmq_min.GetMin(i, j);
      const auto j_mx = rmq_max.GetMax(i, j);
      if (j_mn != min_k || j_mx != max_k)
        continue;

      auto lo = j, hi = n-1;
      while (lo < hi) {
        const auto mid = (lo + hi + 1) / 2;
        const auto mn = rmq_min.GetMin(i, mid);
        const auto mx = rmq_max.GetMax(i, mid);
        if (mn < min_k || mx > max_k)
          hi = mid - 1;
        else
          lo = mid;
      }
      res += hi - j + 1;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,3,5,2,7,5};
    const auto a_out = Solution().countSubarrays(nums, 1, 5);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,1,1,1};
    const auto a_out = Solution().countSubarrays(nums, 1, 1);
    assert(a_out == 10);
  
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
