#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

class Solution {
 public:
  int maximumScore(std::vector<int>& nums, int k) {
    auto n = static_cast<int>(nums.size());
    
    int dp_l[n];
    for (int i = 0; i < n; ++i) {
      if (i == 0) dp_l[i] = -1;
      else if (nums[i-1] < nums[i]) dp_l[i] = i-1;
      else {
        auto j = i-1;
        while (j >= 0 && nums[j] >= nums[i]) {
          j = dp_l[j];
        }
        dp_l[i] = j;
      }
    }
    
    int dp_r[n];
    for (int i = n-1; i >= 0; --i) {
      if (i == n-1) dp_r[i] = n;
      else if (nums[i] > nums[i+1]) dp_r[i] = i+1;
      else {
        auto j = i+1;
        while (j < n && nums[i] <= nums[j]) {
          j = dp_r[j];
        }
        dp_r[i] = j;
      }
    }
    
    int max_score = 0;
    for (int i = 0; i < n; ++i) {
      if (i < k && dp_r[i] <= k) continue;
      if (i > k && k <= dp_l[i]) continue;
      auto l = dp_l[i] + 1;
      auto r = dp_r[i] - 1;
      auto len = r - l + 1;
      auto score = len * nums[i];
      max_score = std::max(score, max_score);
    }
    
    return max_score;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    std::vector<int> input{1,4,3,7,4,5};
    int k = 3;
    auto e_out = 15;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximumScore(input, k);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{5,5,4,5,4,1,1,1};
    int k = 0;
    auto e_out = 20;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximumScore(input, k);
    auto end_t = std::chrono::high_resolution_clock::now();
    auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
    assert(a_out == e_out);
  }
  {
    std::vector<int> input{6569,9667,3148,7698,1622,2194,793,9041,1670,1872};
    int k = 5;
    auto e_out = 9732;
    auto start_t = std::chrono::high_resolution_clock::now();
    auto a_out = Solution().maximumScore(input, k);
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
