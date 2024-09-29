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

constexpr int MAX_N = 3*1e5;
constexpr ll MOD = 998'244'353;

template <typename T>
[[maybe_unused]] T ModSub(T a, T b, T m) {
  // a %= m;
  // a = (a >= 0) ? a : a + m;
  // b %= m;
  // b = (b >= 0) ? b : b + m;
  auto c = (a - b) % m;
  return (c >= 0) ? c : c + m;
}

struct [[maybe_unused]] HashPairLL {
  size_t operator()(const std::pair<ll,ll>& x) const {
    return x.F * 37 + x.S * 37 * 37;
  }
};

[[maybe_unused]] constexpr ll X1 = 37, X2 = 43;
std::array<ll, MAX_N> x1_pow, x2_pow;
bool init_x_pow = false;

void InitXPow(std::array<ll, MAX_N>& x_pow, ll x) {
  x_pow[0] = 1;
  for (int i = 1; i < MAX_N; ++i) {
    x_pow[i] = (x_pow[i-1] * x) % MOD;
  }
}

std::array<ll, MAX_N> s_hash1, s_hash2, p_hash1, p_hash2;

void CalcHash(std::array<ll, MAX_N>& h, const std::string& s, ll x) {
  const auto n = CI(s.size());
  h[0] = s[0]-'a'+1;
  for (auto i = 1; i < n; ++i) {
    h[i] = (((h[i-1]*x)%MOD) + CL(s[i]-'a'+1)) % MOD;
  }
}

class Solution {
public:
  int minStartingIndex(const std::string& s, const std::string& p) {
    if (!init_x_pow) {
      InitXPow(x1_pow, X1);
      InitXPow(x2_pow, X2);
      init_x_pow = true;
    }

    const auto sn = SZ(s), pn = SZ(p);

    CalcHash(s_hash1, s, X1);
    CalcHash(s_hash2, s, X2);

    CalcHash(p_hash1, p, X1);
    CalcHash(p_hash2, p, X2);
    
    std::unordered_map<std::pair<ll,ll>, int, HashPairLL> sh_map;
    for (auto si = sn-pn; si >= 0; --si) {
      const auto s_tail1 = s_hash1[si+pn-1];
      const auto s_pref1 = (si > 0) ? (s_hash1[si-1] * x1_pow[pn]) % MOD : 0;
      const auto sh1 = ModSub(s_tail1, s_pref1, MOD);

      const auto s_tail2 = s_hash2[si+pn-1];
      const auto s_pref2 = (si > 0) ? (s_hash2[si-1] * x2_pow[pn]) % MOD : 0;
      const auto sh2 = ModSub(s_tail2, s_pref2, MOD);

      sh_map[{sh1, sh2}] = si;
    }

    const auto sh_map_end = sh_map.end();

    auto min_si = INT_MAX;
    FOR(pi, 0, pn-1) {
      const auto c_pow1 = x1_pow[pn-1-pi];
      const auto c_pow2 = x2_pow[pn-1-pi];
      const auto ph_rem1 = ModSub(p_hash1[pn-1], (p[pi]-'a'+1)*c_pow1, MOD);
      const auto ph_rem2 = ModSub(p_hash2[pn-1], (p[pi]-'a'+1)*c_pow2, MOD);
      FOR(c, 1, 26) {
        const auto ph1 = (ph_rem1 + c*c_pow1) % MOD;
        const auto ph2 = (ph_rem2 + c*c_pow2) % MOD;
        const auto it = sh_map.find({ph1, ph2});
        if (it != sh_map_end && it->S < min_si)
          min_si = it->S;
      }
    }

    return min_si == INT_MAX ? -1 : min_si;
  }
};

[[maybe_unused]] std::stringstream ReadFile(const std::string& path) {
  std::ifstream file(path);
  assert(file);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  return ss;
}

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minStartingIndex("abcdefg"s, "bcdffg"s);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minStartingIndex("ababbababa"s, "bacaba"s);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minStartingIndex("abcd"s, "dba"s);
    assert(a_out == -1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minStartingIndex("dde"s, "d"s);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minStartingIndex("ede"s, "d"s);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minStartingIndex(std::string(MAX_N, 'a'), std::string(MAX_N, 'a'));
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    std::stringstream i_cin = ReadFile("../input1.txt");
    std::stringstream o_cin = ReadFile("../output1.txt");
    std::string s, p; i_cin >> s >> p;
    std::string e_out_str; o_cin >> e_out_str;
    const auto e_out = std::stoi(e_out_str);
    
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().minStartingIndex(s, p);
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
