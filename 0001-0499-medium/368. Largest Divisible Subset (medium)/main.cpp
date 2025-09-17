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

constexpr int MAX_N = 1000;
std::array<int, MAX_N> dp;
std::array<int, MAX_N> dp_next;

class Solution {
 public:
  static vi largestDivisibleSubset(vi& nums) {
    const auto n = CI(nums.size());
    SORT(nums);
    std::fill(dp.begin(), dp.begin()+n, 1);
    std::fill(dp_next.begin(), dp_next.begin()+n, n);
    FORD(i, n-2, 0) {
      FOR(j, i+1, n-1) {
        if (dp[i] < dp[j]+1 && nums[j] % nums[i] == 0) {
          dp[i] = dp[j]+1;
          dp_next[i] = j;
        }
      }
    }
    const auto best_i = CI(std::max_element(dp.begin(), dp.begin()+n) - dp.begin());
    vi res;
    int next_i = best_i;
    while (next_i != n) {
      res.push_back(nums[next_i]);
      next_i = dp_next[next_i];
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,2,3};
    const auto a_out = Solution::largestDivisibleSubset(nums);
    const vi e_out{1, 2};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{1,2,4,8};
    const auto a_out = Solution::largestDivisibleSubset(nums);
    const vi e_out{1,2,4,8};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{5,9,18,54,108,540,90,180,360,720};
    const auto a_out = Solution::largestDivisibleSubset(nums);
    const vi e_out{9,18,90,180,360,720};
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
