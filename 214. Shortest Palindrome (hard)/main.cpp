//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

const ll MOD = 1e9+7;
const ll X = 37;

template <typename T>
T ModSum(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a + b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

template <typename T>
T ModMult(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a * b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

bool CheckOdd(int n, const std::vector<ll>& x_pow, const std::vector<ll>& hs, const std::vector<ll>& ht,
              int ci, int half_len) {
  const auto si = ci + 1;
  const auto ti = n - ci;

  const auto s_end = si + half_len - 1;
  const auto t_end = ti + half_len - 1;

  const auto s_tail = hs[s_end];
  const auto t_tail = ht[t_end];

  const auto s_pref = (si > 0) ? ModMult(hs[si-1], x_pow[half_len], MOD) : 0;
  const auto t_pref = (ti > 0) ? ModMult(ht[ti-1], x_pow[half_len], MOD) : 0;

  return ModSum(s_tail, t_pref, MOD) == ModSum(t_tail, s_pref, MOD);
}

bool CheckEven(int n, const std::vector<ll>& x_pow, const std::vector<ll>& hs, const std::vector<ll>& ht,
               [[maybe_unused]] int cl, int cr, int half_len) {
  const auto si = cr;
  const auto ti = n - cr;

  const auto s_end = si + half_len - 1;
  const auto t_end = ti + half_len - 1;

  const auto s_tail = hs[s_end];
  const auto t_tail = ht[t_end];

  const auto s_pref = (si > 0) ? ModMult(hs[si-1], x_pow[half_len], MOD) : 0;
  const auto t_pref = (ti > 0) ? ModMult(ht[ti-1], x_pow[half_len], MOD) : 0;

  return ModSum(s_tail, t_pref, MOD) == ModSum(t_tail, s_pref, MOD);
}

class Solution {
  public:
  static std::string shortestPalindrome(const std::string& s) {
    const auto n = CI(s.size());
    if (s.empty() || n == 1) return s;
    if (n == 2 && s[0] == s[1]) return s;

    std::vector<ll> x_pow(n+1);
    x_pow[0] = 1;
    FOR(i, 1, n) {
      x_pow[i] = ModMult(x_pow[i-1], X, MOD);
    }

    std::vector<ll> hs(n);
    hs[0] = CL(s[0]-'a'+1);
    FOR(i, 1, n-1) {
      hs[i] = ModSum(ModMult(hs[i-1], X, MOD), CL(s[i]-'a'+1), MOD);
    }

    auto t = std::string(s.rbegin(), s.rend());
    std::vector<ll> ht(n);
    ht[0] = CL(t[0]-'a'+1);
    FOR(i, 1, n-1) {
      ht[i] = ModSum(ModMult(ht[i-1], X, MOD), CL(t[i]-'a'+1), MOD);
    }

    int max_hl_odd = 0;
    {
      const auto hl_limit = (n%2==1) ? n/2 : n/2-1;
      FOR(hl, 1, hl_limit) {
        const auto ci = hl;
        if (CheckOdd(n, x_pow, hs, ht, ci, hl)) {
          max_hl_odd = std::max(max_hl_odd, hl);
        }
      }
    }
    const auto odd_pal_tail_n = n - 2*max_hl_odd - 1;
    const auto odd_pal_n = n + odd_pal_tail_n;
    
    int max_hl_even = 0;
    {
      const auto hl_limit = n/2;
      FOR(hl, 1, hl_limit) {
        const auto cl = hl-1;
        const auto cr = cl+1;
        if (CheckEven(n, x_pow, hs, ht, cl, cr, hl)) {
          max_hl_even = std::max(max_hl_even, hl);
        }
      }
    }
    const auto even_pal_tail_n = n - 2*max_hl_even;
    const auto even_pal_n = n + even_pal_tail_n;

    if (odd_pal_n <= even_pal_n) {
      FORD(i, odd_pal_tail_n-1, 0) {
        t += t[i];
      }
    } else {
      FORD(i, even_pal_tail_n-1, 0) {
        t += t[i];
      }
    }
    return {t.rbegin(), t.rend()};
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s{"aacecaaa"s};
    const auto a_out = Solution::shortestPalindrome(s);
    const std::string e_out{"aaacecaaa"s};
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const std::string s{"abcd"s};
    const auto a_out = Solution::shortestPalindrome(s);
    const std::string e_out{"dcbabcd"s};
    assert(a_out == e_out);
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
