//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))

class Solution {
 public:
  static std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    const auto n = static_cast<int>(nums.size());
    std::vector<int> res(n-k+1);
    std::deque<int> q;
    FOR(i, 0, k-1) {
      while (!q.empty() && q.back() < nums[i]) {
        q.pop_back();
      }
      q.push_back(nums[i]);
    }
    res[0] = q.front();
    FOR(i, k, n-1) {
      if (!q.empty() && q.front() == nums[i-k]) {
        q.pop_front();
      }
      while (!q.empty() && q.back() < nums[i]) {
        q.pop_back();
      }
      q.push_back(nums[i]);
      res[i-k+1] = q.front();
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<int> nums{1,3,-1,-3,5,3,6,7};
    auto k = 3;
    std::vector<int> e_out{3,3,5,5,6,7};
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution::maxSlidingWindow(nums, k);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> nums{1};
    auto k = 1;
    std::vector<int> e_out{1};
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution::maxSlidingWindow(nums, k);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
