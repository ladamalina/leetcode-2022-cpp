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
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

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

constexpr int MAX_N = 300;
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

ll h_dir[MAX_N];
ll h_rev[MAX_N];

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
  static vvi palindromePairs(const vs& words) {
    if (!init_x_pow) {
      InitXPow();
      init_x_pow = true;
    }
    const auto n = CI(words.size());

    std::unordered_map<std::string, vi> rev_words;
    FOR(i, 0, n-1) {
      const auto& w = words[i];
      auto w_rev = w;
      std::reverse(RNG(w_rev));
      rev_words[w_rev].push_back(i);
    }
    
    vvi res;
    FOR(word_i, 0, n-1) {
      const auto& w = words[word_i];
      CalcHash(h_dir, w);
      auto w_rev = w;
      std::reverse(RNG(w_rev));
      CalcHash(h_rev, w_rev);
      const auto wn = CI(w.size());
      
      // check reverted word
      {
        const auto it = rev_words.find(w);
        if (it != rev_words.end()) {
          for (const auto rev_i : it->S) {
            if (word_i != rev_i) {
              res.push_back({word_i, rev_i});
            }
          }
        }
      }
      
      // 0 1 2 3 4 5 6 7 8 9 (n=10)
      // 9 8 7 6 5 4 3 2 1 0
      // 0 1 2 3 4 5 6 7 8 (n=9)
      
      // check palindrome
      if (wn && Eq(h_dir, h_rev, 0, 0, wn)) {
        const auto it = rev_words.find(""s);
        if (it != rev_words.end()) {
          for (const auto rev_i : it->S) {
            if (word_i != rev_i) {
              res.push_back({word_i, rev_i});
              res.push_back({rev_i, word_i});
            }
          }
        }
      }
      
      FOR(bi, 1, wn-1) {
        const auto ptail_len = wn - bi;
        const auto half_ptail_len = ptail_len / 2;
        if (half_ptail_len == 0 || Eq(h_dir, h_rev, bi, 0, half_ptail_len)) {
          const auto head = w.substr(0, bi);
          const auto it = rev_words.find(head);
          if (it != rev_words.end()) {
            for (const auto rev_i : it->S) {
              if (word_i != rev_i) {
                res.push_back({word_i, rev_i});
              }
            }
          }
        }
      }
      
      FOR(bi, 0, wn-2) {
        const auto phead_len = bi+1;
        const auto half_phead_len = phead_len/2;
        if (half_phead_len == 0 || Eq(h_dir, h_rev, 0, wn-(bi+1), half_phead_len)) {
          const auto tail = w.substr(bi+1, wn-(bi+1));
          const auto it = rev_words.find(tail);
          if (it != rev_words.end()) {
            for (const auto rev_i : it->S) {
              if (word_i != rev_i) {
                res.push_back({rev_i, word_i});
              }
            }
          }
        }
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::palindromePairs({"abcd","dcba","lls","s","sssll"});
    vvi e_out{{0,1},{1,0},{3,2},{2,4}};
    SORT(e_out);
    SORT(a_out);
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::palindromePairs({"bat","tab","cat"});
    vvi e_out{{0,1},{1,0}};
    SORT(e_out);
    SORT(a_out);
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    auto a_out = Solution::palindromePairs({"a",""});
    vvi e_out{{0,1},{1,0}};
    SORT(e_out);
    SORT(a_out);
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
