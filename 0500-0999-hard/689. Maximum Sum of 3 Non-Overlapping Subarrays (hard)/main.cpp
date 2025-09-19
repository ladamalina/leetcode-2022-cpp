#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

struct Triple {
  int l = -1;
  int m = -1;
  int r = -1;
  bool operator<(const Triple& other) const {
    return std::tie(l, m, r) < std::tie(other.l, other.m, other.r);
  }
};

constexpr int MAX_N = 2*1e4;
ll nums_sum[MAX_N];

class Solution {
 public:
  static vi maxSumOfThreeSubarrays(const vi& nums, const int k) {
    const auto n = CI(nums.size());
    
    { // fill nums_sum
      ll curr_sum = std::accumulate(nums.begin(), nums.begin()+k, 0ll);
      nums_sum[0] = curr_sum;
      FOR(r, k, n-1) {
        const auto l = r-k;
        curr_sum += nums[r];
        curr_sum -= nums[l];
        nums_sum[l+1] = curr_sum;
      }
    }
    
    // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 (n=14, k=3)
    
    ll max_sum = 0;
    Triple best_triple{};
    const auto comp = [](const std::pair<ll, int>& lhs, const std::pair<ll, int>& rhs) {
      return std::make_pair(lhs.F, -lhs.S) < std::make_pair(rhs.F, -rhs.S);
    };
    std::set<std::pair<ll, int>, decltype(comp)> ls{{nums_sum[0], 0}};
    std::set<std::pair<ll, int>, decltype(comp)> rs;
    FOR(i, k*2, n-k) {
      rs.emplace(nums_sum[i], i);
    }
    FOR(m, k, n-k*2) {
      const auto max_l = *ls.rbegin();
      const auto max_r = *rs.rbegin();
      const auto curr_sum = max_l.F + nums_sum[m] + max_r.F;
      const Triple curr_triple{max_l.S, m, max_r.S};
      if (curr_sum > max_sum || (curr_sum == max_sum && curr_triple < best_triple)) {
        max_sum = curr_sum;
        best_triple = curr_triple;
      }
      ls.emplace(nums_sum[m-k+1], m-k+1);
      if (m+k < n)
        rs.erase({nums_sum[m+k], m+k});
    }
    return {best_triple.l, best_triple.m, best_triple.r};
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::maxSumOfThreeSubarrays({1,2,1,2,6,7,5,1}, 2);
    const vi e_out{0,3,5};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::maxSumOfThreeSubarrays({1,2,1,2,1,2,1,2,1}, 2);
    const vi e_out{0,2,4};
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
