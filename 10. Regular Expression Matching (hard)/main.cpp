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
#define F first
#define S second

constexpr int MAX_N = 20;
int dp[MAX_N][MAX_N];

bool Rec(int si, int pi, int sn, int pn, const std::string& s, const std::string& p) {
  if (si == sn && pi == pn)
    return true;
  if (si == sn) {
    bool ok = true;
    const auto left = pn - pi;
    if (left % 2 == 1)
      return false;
    for (int i = pi+1; i < pn; i += 2) {
      if (p[i] != '*') {
        ok = false;
        break;
      }
    }
    return ok;
  }
  if (pi == pn)
    return false;
    
  if (dp[si][pi] != -1)
    return dp[si][pi];
  
  bool res = false;
  if (p[pi] == '.' && (pi+1 == pn || p[pi+1] != '*')) {
    auto sub_res = Rec(si+1, pi+1, sn, pn, s, p); // 1
    res |= sub_res;
  } else if (pi+1 < pn && p[pi+1] == '*') {
    auto sub_res = (p[pi] == '.' || s[si] == p[pi]) && Rec(si+1, pi+2, sn, pn, s, p); // 1
    if (!sub_res)
      sub_res = Rec(si, pi+2, sn, pn, s, p); // 0
    if (!sub_res)
      sub_res = (p[pi] == '.' || s[si] == p[pi]) && Rec(si+1, pi, sn, pn, s, p); // 1+
    res |= sub_res;
  } else if (s[si] == p[pi]) {
    const auto sub_res = Rec(si+1, pi+1, sn, pn, s, p);
    res |= sub_res;
  }
  dp[si][pi] = res;
  return res;
}

class Solution {
 public:
  static bool isMatch(const std::string& s, const std::string& p) {
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), -1);
    
    const auto sn = CI(s.size());
    const auto pn = CI(p.size());
    const auto res = Rec(0, 0, sn, pn, s, p);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("aa", "a");
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("aa", "a*");
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("ab", ".*");
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("", ".*");
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("", ".*.*");
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("a", ".*.*");
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("abc", ".*.*");
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("mississippi", "mis*is*p*.");
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("a", "ab*");
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("ab", ".*c");
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::isMatch("aaaaaaaaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*");
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
