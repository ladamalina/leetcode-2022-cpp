#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back

using Freq = std::array<int, 26>;
using Memo = std::unordered_map<std::string_view, std::unordered_map<std::string_view, bool>>;

bool Rec(std::string_view s1, std::string_view s2, const Freq& f1, const Freq& f2, Memo& memo) {
  if (s1.size() != s2.size() || f1 != f2) return false;
  const auto n = CI(s1.size());
  if (n == 1) return true;
  if (memo.contains(s1) && memo.at(s1).contains(s2))
    return memo.at(s1).at(s2);
  if (memo.contains(s2) && memo.at(s2).contains(s1))
    return memo.at(s2).at(s1);

  Freq f1l{}, f1r=f1; // parts of 1st string
  Freq f2l_dir{}, f2r_dir=f2; // parts of 2st string if split dir
  Freq f2l_rev=f2, f2r_rev{}; // parts of 2st string if split rev
  bool ok = false;
  FOR(i, 0, n-2) {
    ++f1l[s1[i]-'a'];
    --f1r[s1[i]-'a'];
    ++f2l_dir[s2[i]-'a'];
    --f2r_dir[s2[i]-'a'];
    const auto res_dir_l = Rec(s1.substr(0, i+1), s2.substr(0, i+1), f1l, f2l_dir, memo);
    const auto res_dir_r = Rec(s1.substr(i+1, n-1-i), s2.substr(i+1, n-1-i), f1r, f2r_dir, memo);
    if (res_dir_l && res_dir_r) {
      ok = true;
      break;
    }
    
    const auto j = n-1-i;
    --f2l_rev[s2[j]-'a'];
    ++f2r_rev[s2[j]-'a'];
    const auto res_rev_l = Rec(s1.substr(0, i+1), s2.substr(j, n-j), f1l, f2r_rev, memo);
    const auto res_rev_r = Rec(s1.substr(i+1, n-1-i), s2.substr(0, j), f1r, f2l_rev, memo);
    if (res_rev_l && res_rev_r) {
      ok = true;
      break;
    }
  }
  memo[s1][s2] = ok;
  return ok;
}

class Solution {
public:
  bool isScramble(const std::string& s1, const std::string& s2) {
    Freq f1{};
    for (const auto c : s1) ++f1[c-'a'];
    Freq f2{};
    for (const auto c : s2) ++f2[c-'a'];
    Memo memo;
    const auto res = Rec(s1, s2, f1, f2, memo);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s1{"great"};
    const std::string s2{"rgeat"};
    const auto a_out = Solution().isScramble(s1, s2);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s1{"abcde"};
    const std::string s2{"caebd"};
    const auto a_out = Solution().isScramble(s1, s2);
    assert(!a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s1{"a"};
    const std::string s2{"a"};
    const auto a_out = Solution().isScramble(s1, s2);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s1{"eebaacbcbcadaaedceaaacadccd"};
    const std::string s2{"eadcaacabaddaceacbceaabeccd"};
    const auto a_out = Solution().isScramble(s1, s2);
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
