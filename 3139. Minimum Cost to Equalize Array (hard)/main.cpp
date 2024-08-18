#include <bits/stdc++.h>

/*#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>*/

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
#define F first
#define S second

constexpr ll MOD = (1e9)+7;

class Solution {
public:
  int minCostToEqualizeArray(vi& nums, ll c1, ll c2) {
    const auto n = CI(nums.size());
    const ll mn = *std::min_element(RNG(nums));
    const ll mx = *std::max_element(RNG(nums));
    const ll nums_sum = std::accumulate(RNG(nums), 0ll);

    auto min_cost = LLONG_MAX;

    for (ll eq = mx; eq<=2*mx; ++eq) {
      auto inc_cnt = eq*n - nums_sum;
      ll cost = 0;

      if (eq*(n-1) - (nums_sum-mn) <= (eq-mn)) {
        auto extra = (eq-mn) - (eq*(n-1) - (nums_sum-mn));
        cost += extra * c1;
        inc_cnt -= extra;
      }

      if (inc_cnt & 1){
        inc_cnt -= 1;
        cost += c1;
      }

      cost += std::min(inc_cnt*c1 , (inc_cnt/2)*c2);
      min_cost = std::min(min_cost, cost);
    }

    return min_cost%MOD;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{4,1};
    const auto a_out = Solution().minCostToEqualizeArray(nums, 5, 2);
    assert(a_out == 15);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{2,3,3,3,5};
    const auto a_out = Solution().minCostToEqualizeArray(nums, 2, 1);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{3,5,3};
    const auto a_out = Solution().minCostToEqualizeArray(nums, 1, 3);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,14,14,15};
    const auto a_out = Solution().minCostToEqualizeArray(nums, 2, 1);
    assert(a_out == 20);
  
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
