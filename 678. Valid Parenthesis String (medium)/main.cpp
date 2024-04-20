#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
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

constexpr int MAX_N = 100;
std::array<std::array<int, MAX_N+1>, MAX_N> dp;

bool Rec(int i, int b, int n, const std::string& s) {
  if (i == n) return b==0;
  if (dp[i][b] != -1)
    return dp[i][b];
  auto& res = dp[i][b];
  res = 0;

  if (s[i] == '(') {
    res |= Rec(i+1, b+1, n, s);
    return res;
  }
  
  if (s[i] == ')') {
    if (b == 0) return false;
    res |= Rec(i+1, b-1, n, s);
    return res;
  }

  // s[i] == '*'
  res |= Rec(i+1, b+1, n, s); // use '('
  if (b > 0) {
    res |= Rec(i+1, b-1, n, s); // use ')'
  }
  res |= Rec(i+1, b, n, s); // use an empty string

  return res;
}

class Solution {
  public:
  static bool checkValidString(const std::string& s) {
    const auto n = CI(s.size());
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), -1);
    const auto res = Rec(0, 0, n, s);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::checkValidString("()"s);
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::checkValidString("(*)"s);
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::checkValidString("(*))"s);
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::checkValidString("****************************************************************************************************"s);
    assert(a_out);

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
