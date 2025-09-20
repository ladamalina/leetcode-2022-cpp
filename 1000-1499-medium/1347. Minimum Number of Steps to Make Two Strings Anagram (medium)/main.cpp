// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;

int s_freq[26], t_freq[26];

class Solution {
  public:
  static int minSteps(const std::string& s, const std::string& t) {
    memset(s_freq, 0, sizeof(s_freq));
    for (int i = 0; i < s.size(); ++i)
      ++s_freq[s[i]-'a'];
    memset(t_freq, 0, sizeof(t_freq));
    for (int i = 0; i < s.size(); ++i)
      ++t_freq[t[i]-'a'];
    int res = 0;
    for (int i = 0; i < 26; ++i)
      if (t_freq[i] > s_freq[i])
        res += t_freq[i] - s_freq[i];
    return res;
  }
};

/*[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> p{-1,0,0,1,1,2};
    const std::string s{"acaabc"s};
    const auto a_out = Solution::countPalindromePaths(p, s);
    assert(a_out == 8);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<int> p{-1,0,0,0,0};
    const std::string s{"aaaaa"s};
    const auto a_out = Solution::countPalindromePaths(p, s);
    assert(a_out == 10);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}*/

int main() {
#ifndef NDEBUG
  // TestSolution();
#endif
  return 0;
}
