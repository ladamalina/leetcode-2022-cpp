// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;

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

constexpr int MAX_N = 5*1e5;
constexpr ll MOD = 1e9+7;
constexpr ll X = 37;

ll x_pow[MAX_N];
bool init_x_pow = false;

void InitXPow() {
  x_pow[0] = 1;
  for (int i = 1; i < MAX_N; ++i) {
    x_pow[i] = ModMult(x_pow[i-1], X, MOD);
  }
}

ll hs[MAX_N];
ll ha[MAX_N];
ll hb[MAX_N];

void CalcHash(ll (&h)[MAX_N], const std::string& s) {
  const auto n = static_cast<int>(s.size());
  h[0] = s[0]-'a'+1;
  for (int i = 1; i < n; ++i) {
    h[i] = ModSum(ModMult(h[i-1], X, MOD), static_cast<ll>(s[i]-'a'+1), MOD);
  }
}

bool Eq(const ll (&hs)[MAX_N], const ll (&ht)[MAX_N], const int i, const int len) {
  const auto s_end = i + len - 1;

  const auto s_tail = hs[s_end];
  const auto t_tail = ht[len-1];

  const auto s_pref = (i > 0) ? ModMult(hs[i-1], x_pow[len], MOD) : 0;
  const auto t_pref = 0ll;

  return ModSum(s_tail, t_pref, MOD) == ModSum(t_tail, s_pref, MOD);
}

class Solution {
public:
  static vi beautifulIndices(const std::string& s, const std::string& a, const std::string& b, const int k) {
    if (!init_x_pow) {
      InitXPow();
      init_x_pow = true;
    }

    const auto s_len = static_cast<int>(s.size());
    const auto a_len = static_cast<int>(a.size());
    const auto b_len = static_cast<int>(b.size());
    CalcHash(hs, s);
    CalcHash(ha, a);
    CalcHash(hb, b);

    vi b_ids;
    for (int i = 0; i <= s_len-b_len; ++i) {
      if (Eq(hs, hb, i, b_len)) {
        b_ids.push_back(i);
      }
    }
    vi res;
    for (int i = 0; i <= s_len-a_len; ++i) {
      if (Eq(hs, ha, i, a_len)) {
        const auto it = std::lower_bound(b_ids.begin(), b_ids.end(), i);
        if ((it != b_ids.end() && *it - i <= k) || (it != b_ids.begin() && i - *std::prev(it) <= k)) {
          res.push_back(i);
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"isawsquirrelnearmysquirrelhouseohmy"s};
    const std::string a{"my"s};
    const std::string b{"squirrel"s};
    const vi e_out{16,33};
    const auto a_out = Solution::beautifulIndices(s, a, b, 15);
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s{"abcd"s};
    const std::string a{"a"s};
    const std::string b{"b"s};
    const vi e_out{0};
    const auto a_out = Solution::beautifulIndices(s, a, b, 4);
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
