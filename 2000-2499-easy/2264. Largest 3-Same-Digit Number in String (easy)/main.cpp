#include <bits/stdc++.h>

using namespace std::literals;
using namespace std;

#define CI(_v) static_cast<int>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())

class Solution {
public:
  string largestGoodInteger(const string& s) {
    const auto n = SZ(s);
    auto max_d = -1;
    for (auto i = 0; i <= n-3; ++i) {
      if (s[i] == s[i+1] && s[i] == s[i+2] && s[i] - '0' > max_d)
        max_d = s[i] - '0';
    }
    return max_d == -1 ? ""s : string(3, CC(max_d + '0'));
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
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
