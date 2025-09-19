#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vvb [[maybe_unused]] = std::vector<vb>;
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

constexpr ll MOD = 1e9 + 7;

constexpr int MAX_N = 1000;
std::array<vi, 4> s_ids;
int dp[MAX_N+2][MAX_N+2];

ll Rec(int l, int r, int n, const std::string& s) {
  if (l >= r) return 0;
  if (l+1 == r) return 1;
  if (dp[l+1][r+1] != -1) {
    return dp[l+1][r+1];
  }

  ll res = 0;
  if (l != -1) {
    res = (res + 1ll) % MOD; // even
  }

  FOR(chi, 0, 3) {
    const auto& ch_ids = s_ids[chi];

    const auto l_it = std::upper_bound(RNG(ch_ids), l);
    const auto r_it = std::lower_bound(RNG(ch_ids), r);

    if (l_it != ch_ids.end() && *l_it < r) {
      res = (res + 1ll) % MOD; // odd mid
    }

    if (l_it != ch_ids.end() && r_it != ch_ids.begin()) {
      const auto sub_res = Rec(*l_it, *std::prev(r_it), n, s);
      res = (res + sub_res) % MOD;
    }
  }

  dp[l+1][r+1] = res;
  return res;
}

class Solution {
 public:
  static int countPalindromicSubsequences(const std::string& s) {
    const auto n = CI(s.size());
    memset(dp, -1, sizeof(dp));

    std::fill(RNG(s_ids), vi{});
    FOR(i, 0, n-1) {
      s_ids[s[i]-'a'].push_back(i);
    }

    const auto res = Rec(-1, n, n, s);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("bccb");
    const auto a_out = Solution::countPalindromicSubsequences(s);
    assert(a_out == 6);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("a");
    const auto a_out = Solution::countPalindromicSubsequences(s);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba");
    const auto a_out = Solution::countPalindromicSubsequences(s);
    assert(a_out == 104860361);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("bdccbdbdcaacaadbdacaadabbdaababacbdbadaccccbbbccbdbddcacdbbcdaaababddadbbcabaddbbaabcdacdcddcbacdcadddbaadcbbccdcbdcaaabcbddacaccadacdcadacadccabdbadcdabaaccbcabbacdcbbbabddbcccbcbcddacaccabbabccdbbabacadbbdbcccbddaaadcdaddcccddaacbddabddabadbcbaadcaddbdccabaddcccdccbacaccccbcdccacbabddcbcbbbdbbddaabbcaddbddddaacbbccbcdbadacccbadbccdddadcbacbbdcabcbdbbaabcdcbdacabacdccdaabcbbddbdddcacdbdccbbabbaccdcbabcdacdabdddaddacdbddabcbbbdcccacbdadddbbdbcabccadbcbadddcbcddaababcabbbcbbabadaddabcbdacaadcababcbacadcdabcdbddadaadddddbaaacddaacadcdbaaacbacaabdabccbacabbabddacddcdacdcddbacbddbdcadcddabdadcdbcbbcadbcdabbbbdcdadadbbcadbcbbcccccabdaabcdacbdbcadabcdbaaaaacdaaabcdcaabddcacdcacabbaadbdbcbaaabadbdadadaccddacababbdcbaaaccaabbdaddadcabaabbdaadadcabcabbdbbdccbabbbabbcbcbdcacccbdbabdbaadccdaddaddaadadccabdcbbbccacbbaaabccaccdcabbbddbdbbacdaabbdcdacbdddbacbadccabbbdbbbdbdbcadcacddddcdbdcabccdccabaadbcbacaaababdddcbcdaaabaaabddbcabcbbcdddccdcbccbbccadccaaccccbdadcaacdcbcabacacadaabacddaadcccbcabdad");
    const auto a_out = Solution::countPalindromicSubsequences(s);
    assert(a_out == 739921586);

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
