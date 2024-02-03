// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std::literals;
using namespace __gnu_pbds;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

typedef tree<std::pair<ll, int>, null_type, std::less<>, rb_tree_tag, tree_order_statistics_node_update> IndexedSet;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define F first
#define S second

constexpr int MAX_N = 1e5;

ll psum[MAX_N];

class Solution {
 public:
  static int countRangeSum(const vi& nums, int lower, int upper) {
    const auto n = CI(nums.size());
    
    psum[0] = nums[0];
    IndexedSet psums{};
    psums.insert({psum[0], 0});
    FOR(i, 1, n-1) {
      psum[i] = psum[i-1] + nums[i];
      psums.insert({psum[i], i});
    }
    
    int res = 0;
    FOR(i, 0, n-1) {
      const auto prev = (i > 0) ? psum[i-1] : 0;
      // psum - prev = lower => psum = prev + lower
      const auto target_lower = prev + lower;
      const auto target_upper = prev + upper;

      const auto l_it = psums.lower_bound({target_lower, 0});
      const int l_id = (l_it != psums.end()) ? CI(psums.order_of_key(*l_it)) : CI(psums.size());
      const auto u_it = psums.upper_bound({target_upper, INT_MAX});
      const int u_id = (u_it != psums.end()) ? CI(psums.order_of_key(*u_it)) : CI(psums.size());
      const auto cnt = u_id - l_id;
      res += cnt;

      psums.erase({psum[i], i});
    }
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::countRangeSum({-2,5,-1}, -2, 2);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::countRangeSum({0}, 0, 0);
    assert(a_out == 1);

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
