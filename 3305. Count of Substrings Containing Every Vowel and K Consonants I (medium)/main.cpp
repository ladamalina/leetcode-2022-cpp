// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

class Solution {
public:
  using Freq = std::array<int, 26>;
  
  ll countOfSubstrings(const std::string& w, const int k) {
    const auto n = SZ(w);
    std::vector<Freq> pref_c_freq(n);
    vi pref_n_con(n);
    FOR(i, 0, n-1) {
      if (i > 0) {
        pref_c_freq[i] = pref_c_freq[i-1];
        pref_n_con[i] = pref_n_con[i-1];
      }
      ++pref_c_freq[i][w[i]-'a'];
      if (!IsVowel(w[i]-'a'))
        ++pref_n_con[i];
    }
    ll res = 0;
    FOR(i, 0, n-1) {
      const auto base = (i == 0) ? Freq{} : pref_c_freq[i-1];
      const auto base_n_con = (i == 0) ? 0 : pref_n_con[i-1];

      const auto last_n_vow = CntVowels(base, pref_c_freq[n-1]);
      const auto last_n_con = pref_n_con[n-1] - base_n_con;
      const auto last_ok = last_n_vow >= 5 && last_n_con >= k;
      if (!last_ok)
        break;

      int k_con_l, k_con_r, vow_5_l;
      {
        auto l = i, r = n-1;
        while (l < r) {
          const auto m = (l+r) / 2;
          const auto m_cnt = pref_n_con[m] - base_n_con;
          if (m_cnt >= k)
            r = m;
          else
            l = m + 1;
        }
        k_con_l = l;
      }
      {
        auto l = i, r = n-1;
        while (l < r) {
          const auto m = (l+r+1) / 2;
          const auto m_cnt = pref_n_con[m] - base_n_con;
          if (m_cnt <= k)
            l = m;
          else
            r = m - 1;
        }
        k_con_r = l;
      }
      {
        auto l = i, r = n-1;
        while (l < r) {
          const auto m = (l+r) / 2;
          const auto m_cnt = CntVowels(base, pref_c_freq[m]);
          if (m_cnt >= 5)
            r = m;
          else
            l = m + 1;
        }
        vow_5_l = l;
      }
      if (vow_5_l <= k_con_r) {
        const auto add = k_con_r - std::max(k_con_l, vow_5_l) + 1;
        res += add;
      }
    }
    return res;
  }

private:
  static bool IsVowel(const int ci) {
    return ci == 'a'-'a' || ci == 'e'-'a' || ci == 'i'-'a' || ci == 'o'-'a' || ci == 'u'-'a';
  }

  static int CntVowels(const Freq& base, const Freq& freq) {
    return (freq['a'-'a'] - base['a'-'a'] > 0)
      + (freq['e'-'a'] - base['e'-'a'] > 0)
      + (freq['i'-'a'] - base['i'-'a'] > 0)
      + (freq['o'-'a'] - base['o'-'a'] > 0)
      + (freq['u'-'a'] - base['u'-'a'] > 0);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().countOfSubstrings("aeioqq", 1);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().countOfSubstrings("aeiou", 0);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().countOfSubstrings("ieaouqqieaouqq", 1);
    assert(a_out == 3);
  
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
