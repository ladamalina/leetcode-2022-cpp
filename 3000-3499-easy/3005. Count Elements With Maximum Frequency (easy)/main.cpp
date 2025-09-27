// #pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>

using namespace std::literals;

constexpr int MAX_X = 100;
std::array<int, MAX_X + 1> freq;

class Solution {
public:
  int maxFrequencyElements(const std::vector<int>& nums) {
    std::fill(freq.begin(), freq.end(), 0);
    auto max_freq = 0, cnt = 0;
    for (const auto x : nums) {
      ++freq[x];
      if (freq[x] > max_freq) {
        max_freq = freq[x];
        cnt = 1;
      } else if (freq[x] == max_freq) {
        ++cnt;
      }
    }
    return max_freq * cnt;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution::countOfPairs(3, 1, 3);
    const vl e_out{6,0,0};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
