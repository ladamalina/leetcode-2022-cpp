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

constexpr int MAX_X = 1000;
constexpr int MAX_P = MAX_X * MAX_X;

std::array<int, MAX_X+1> s_freq{};
std::array<int, MAX_P+1> p_freq{};
std::array<ll, MAX_P+1> p_sum{};

class Solution {
public:
  ll dividePlayers(const vi& skill) {
    const auto n = SZ(skill);

    std::fill(RNG(s_freq), 0);
    for (const auto x : skill)
      ++s_freq[x];

    const std::set<int> s_set(RNG(skill));
    const vi s_vec(RNG(s_set));
    const auto sn = SZ(s_vec);

    std::fill(RNG(p_freq), 0);
    std::fill(RNG(p_sum), 0ll);
    FOR(si, 0, sn-1) {
      const auto s1 = s_vec[si];
      FOR(sj, si, sn-1) {
        const auto s2 = s_vec[sj];
        if (s1 == s2 && s_freq[s1] % 2 == 0) {
          p_freq[s1 + s2] += s_freq[s1] / 2;
          p_sum[s1 + s2] += s1 * s2 * CL(s_freq[s1]/2);
        }
        if (s1 != s2 && s_freq[s1] == s_freq[s2]) {
          p_freq[s1 + s2] += s_freq[s1];
          p_sum[s1 + s2] += s1 * s2 * CL(s_freq[s1]);
        }
      }
    }

    const auto p_it = std::find(RNG(p_freq), n/2);
    if (p_it == p_freq.end())
      return -1;
    
    const auto p = CI(p_it - p_freq.begin());
    return p_sum[p];
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().dividePlayers({3,2,5,1,3,4});
    assert(a_out == 22);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().dividePlayers({3,4});
    assert(a_out == 12);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().dividePlayers({1,1,2,3});
    assert(a_out == -1);
  
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
