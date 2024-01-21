// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
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

constexpr ll MOD = 1e9 + 7;

template <typename T>
[[maybe_unused]] T ModSum(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a + b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

template <typename T>
[[maybe_unused]] T ModSub(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a - b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

template <typename T>
[[maybe_unused]] T ModMult(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  b %= m;
  b = (b >= 0) ? b : b + m;
  auto c = (a * b) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

template <typename T>
[[maybe_unused]] T ModPow(T a, T x, T m) {
  T ret = 1;
  while (x) {
    if (x & 1) (ret *= a) %= m;
    x >>= 1;
    (a *= a) %= m;
  }
  return ret;
}

template <typename T>
[[maybe_unused]] T ModDiv(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  auto b_inv = ModPow(b, m-2, m);
  auto c = (a * b_inv) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

constexpr int MAX_N = 5*1e5;
constexpr ll X = 37;

ll x_pow[MAX_N];
bool init_x_pow = false;

void InitXPow() {
  x_pow[0] = 1;
  for (int i = 1; i < MAX_N; ++i) {
    x_pow[i] = ModMult(x_pow[i-1], X, MOD);
  }
}

ll s_hash[MAX_N];
ll t_hash[MAX_N];

void CalcHash(ll (&h)[MAX_N], const std::string& s) {
  const auto n = static_cast<int>(s.size());
  h[0] = s[0]-'a'+1;
  for (int i = 1; i < n; ++i) {
    h[i] = ModSum(ModMult(h[i-1], X, MOD), static_cast<ll>(s[i]-'a'+1), MOD);
  }
}

bool Eq(const ll (&hs)[MAX_N], const ll (&ht)[MAX_N], const int si, const int ti, const int len) {
  const auto s_end = si + len - 1;
  const auto t_end = ti + len - 1;

  const auto s_tail = hs[s_end];
  const auto t_tail = ht[t_end];

  const auto s_pref = (si > 0) ? ModMult(hs[si-1], x_pow[len], MOD) : 0;
  const auto t_pref = (ti > 0) ? ModMult(ht[ti-1], x_pow[len], MOD) : 0;

  // s_tail-s_pref == t_tail-t_pref
  return ModSum(s_tail, t_pref, MOD) == ModSum(t_tail, s_pref, MOD);
}

class Solution {
  public:
  static int numberOfWays(const std::string& s, const std::string& t, ll k) {
    if (!init_x_pow) {
      InitXPow();
      init_x_pow = true;
    }
    const auto n = static_cast<int>(s.size());
    CalcHash(s_hash, s);
    CalcHash(t_hash, t);

    ll res = 0;

    const auto k_pow = CL(k%2==0 ? 1 : -1);
    const auto f0 = ModSum(ModDiv(ModSub(ModPow(CL(n-1), CL(k), MOD), k_pow, MOD), CL(n), MOD), k_pow, MOD);
    const auto fn = ModDiv(ModSub(ModPow(CL(n-1), CL(k), MOD), k_pow, MOD), CL(n), MOD);
    
    FOR(i, 0, n-1) {
      if (i == 0) {
        if (s_hash[n-1] == t_hash[n-1]) {
          res = ModSum(res, f0, MOD);
        }
      } else {
        const auto l_eq = Eq(s_hash, t_hash, 0, n-i, i);
        const auto r_eq = Eq(s_hash, t_hash, i, 0, n-i);
        if (l_eq && r_eq) {
          res = ModSum(res, fn, MOD);
        }
      }
    }
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"abcd"};
    const std::string t{"cdab"};
    const auto a_out = Solution::numberOfWays(s, t, 2);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"ababab"};
    const std::string t{"ababab"};
    const auto a_out = Solution::numberOfWays(s, t, 1);
    assert(a_out == 2);

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
