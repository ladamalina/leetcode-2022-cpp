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
using ld = long double;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

[[maybe_unused]] constexpr ll MOD = 1e9 + 7;
[[maybe_unused]] constexpr int MAX_M = 5, MAX_N = 1000;
[[maybe_unused]] int M, N;

std::array<std::unordered_map<std::string, ll>, MAX_N+1> dp;
std::vector<vs> m_cols(MAX_M+1);
std::string col;

void RecCols(char pc, int i) {
  if (i == M) {
    m_cols[M].push_back(col);
    return;
  }
  for (auto c = '0'; c <= '2'; ++c) {
    if (i == 0 || c != pc) {
      col += c;
      RecCols(c, i + 1);
      col.pop_back();
    }
  }
}

bool ColsOK(const std::string& s, const std::string& t) {
  FOR(i, 0, SZ(s) - 1) {
    if (s[i] == t[i]) return false;
  }
  return true;
}

ll Rec(const std::string& s, int cnt) {
  if (cnt == 0)
    return 1ll;
  if (dp[cnt].contains(s))
    return dp[cnt][s];
  auto& res = dp[cnt][s];
  for (const auto& nx : m_cols[M]) {
    if (ColsOK(s, nx)) {
      res = (res + Rec(nx, cnt-1)) % MOD;
    }
  }
  return res;
}

class Solution {
public:
  int colorTheGrid(int m, int n) {
    M = m, N = n;
    if (m_cols[M].empty()) {
      RecCols('.', 0);
    }
    return Rec(std::string(M, '.'), N);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution().colorTheGrid(1, 1);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution().colorTheGrid(1, 2);
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    
    const auto a_out = Solution().colorTheGrid(5, 5);
    assert(a_out == 580986);
  
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
