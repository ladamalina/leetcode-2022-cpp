// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;

constexpr ll MOD = 1e9 + 7;

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

template <typename T>
T ModPow(T a, T x, T m) {
  T ret = 1;
  while (x) {
    if (x & 1) (ret *= a) %= m;
    x >>= 1;
    (a *= a) %= m;
  }
  return ret;
}

template <typename T>
T ModDiv(T a, T b, T m) {
  a %= m;
  a = (a >= 0) ? a : a + m;
  auto b_inv = ModPow(b, m-2, m);
  auto c = (a * b_inv) % m;
  c = (c >= 0) ? c : c + m;
  return c;
}

constexpr int MAX_N = 100'000;
bool init_f = false;

ll f_mod[MAX_N+1];
void InitFMod() {
  f_mod[0] = 1;
  f_mod[1] = 1;
  for (ll n = 2; n < MAX_N+1; ++n) {
    f_mod[n] = ModMult(f_mod[n-1], n, MOD);
  }
}

ll f_inv[MAX_N+1];
void InitFInv() {
  f_inv[MAX_N] = ModPow(f_mod[MAX_N], MOD-2, MOD);
  for (ll n = MAX_N-1; n >= 0; --n) {
    f_inv[n] = ModMult(f_inv[n+1], n+1, MOD);
  }
}

ll pow_2[MAX_N+1];
void InitPow2() {
  pow_2[0] = 1;
  for (int i = 1; i < MAX_N+1; ++i) {
    pow_2[i] = ModMult(pow_2[i-1], 2ll, MOD);
  }
}

int xs[MAX_N];

class Solution {
  public:
  static int numberOfSequence(const int n, const vi& sick) {
    if (!init_f) {
      InitFMod();
      InitFInv();
      InitPow2();
      init_f = true;
    }
    
    const auto sick_n = static_cast<int>(sick.size());
    const auto healthy_n = n - sick_n;

    int xs_n = 0;
    for (int i = 1; i < sick_n; ++i) {
      const auto len = sick[i] - sick[i-1] - 1;
      if (len > 1) {
        xs[xs_n] = len;
        ++xs_n;
      }
    }
    const auto front_len = sick.front() - 0;
    const auto back_len = n-1 - sick.back();
    
    ll res = f_mod[healthy_n];
    for (int i = 0; i < xs_n; ++i) {
      res = ModMult(res, f_inv[xs[i]], MOD);
      res = ModMult(res, pow_2[xs[i]-1], MOD);
    }
    res = ModMult(res, f_inv[front_len], MOD);
    res = ModMult(res, f_inv[back_len], MOD);
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi sick{0,4};
    const auto a_out = Solution::numberOfSequence(5, sick);
    assert(a_out == 4);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi sick{1};
    const auto a_out = Solution::numberOfSequence(4, sick);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi sick{0,1};
    const auto a_out = Solution::numberOfSequence(5, sick);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi sick{0,2,4};
    const auto a_out = Solution::numberOfSequence(5, sick);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi sick{0,1,3,7};
    const auto a_out = Solution::numberOfSequence(10, sick);
    assert(a_out == 240);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi sick{0,1,2,3,4,5,7,11,13,17};
    const auto a_out = Solution::numberOfSequence(32, sick);
    assert(a_out == 730278365);

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
