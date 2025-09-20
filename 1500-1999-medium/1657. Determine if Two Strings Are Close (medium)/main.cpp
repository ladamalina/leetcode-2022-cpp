// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

std::array<int, 26> freq1, freq2;

class Solution {
  public:
  static bool closeStrings(const std::string& w1, const std::string& w2) {
    if (w1.size() != w2.size())
      return false;

    int m1 = 0;
    freq1 = {};
    for (const char ch : w1) {
      m1 |= (1<<(ch-'a'));
      ++freq1[ch-'a'];
    }
    std::sort(freq1.begin(), freq1.end());

    int m2 = 0;
    freq2 = {};
    for (const char ch : w2) {
      m2 |= (1<<(ch-'a'));
      ++freq2[ch-'a'];
    }
    std::sort(freq2.begin(), freq2.end());

    return m1 == m2 && freq1 == freq2;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string w1{"abc"s};
    const std::string w2{"bca"s};
    const auto a_out = Solution::closeStrings(w1, w2);
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string w1{"a"s};
    const std::string w2{"aa"s};
    const auto a_out = Solution::closeStrings(w1, w2);
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string w1{"cabbba"s};
    const std::string w2{"abbccc"s};
    const auto a_out = Solution::closeStrings(w1, w2);
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string w1{"abbzzca"s};
    const std::string w2{"babzzcz"s};
    const auto a_out = Solution::closeStrings(w1, w2);
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string w1{"uau"s};
    const std::string w2{"ssx"s};
    const auto a_out = Solution::closeStrings(w1, w2);
    assert(!a_out);

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
