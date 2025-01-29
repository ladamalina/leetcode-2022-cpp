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

constexpr int MAX_N = 1e5;
std::array<ii, MAX_N> x_id;
std::array<int, MAX_N> ids, xs;

class Solution {
public:
  vi lexicographicallySmallestArray(vi& nums, const int limit) {
    const auto n_nums = SZ(nums);
    FOR(i, 0, n_nums-1) {
      x_id[i] = {nums[i], i};
    }
    std::sort(x_id.begin(), x_id.begin()+n_nums);
    
    auto n_sorted = 0;
    FOR(i, 0, n_nums-1) {
      xs[n_sorted] = x_id[i].F;
      ids[n_sorted] = x_id[i].S;
      ++n_sorted;
      if (i == n_nums-1 || x_id[i].F + limit < x_id[i+1].F) {
        std::sort(ids.begin(), ids.begin() + n_sorted);
        FOR(j, 0, n_sorted-1) {
          nums[ids[j]] = xs[j];
        }
        n_sorted = 0;
      }
    }
    return nums;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,5,3,9,8};
    const vi e_out{1,3,5,8,9};
    const auto a_out = Solution().lexicographicallySmallestArray(nums, 2);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,7,6,18,2,1};
    const vi e_out{1,6,7,18,1,2};
    const auto a_out = Solution().lexicographicallySmallestArray(nums, 3);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,7,28,19,10};
    const vi e_out{1,7,28,19,10};
    const auto a_out = Solution().lexicographicallySmallestArray(nums, 3);
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
