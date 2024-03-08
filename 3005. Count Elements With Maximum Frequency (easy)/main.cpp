// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vii = std::vector<ii>;

class Solution {
public:
  static int maxFrequencyElements(const std::vector<int>& nums) {
    std::array<int, 101> freq;
    int max_freq = 0;
    int cnt = 0;
    for (const auto num : nums) {
      ++freq[num];
      if (freq[num] > max_freq) {
        max_freq = freq[num];
        cnt = 1;
      } else if (freq[num] == max_freq) {
        ++cnt;
      }
    }
    return max_freq*cnt;
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
