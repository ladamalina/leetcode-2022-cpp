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
using vvl [[maybe_unused]] = std::vector<vl>;
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
  bool isItPossible(const std::string& word1, const std::string& word2) {
    std::array<int, 26> freq1{}, freq2{};
    for (const auto c : word1) ++freq1[c-'a'];
    for (const auto c : word2) ++freq2[c-'a'];
    const auto dist1 = CI(std::count_if(RNG(freq1), [](const int f) { return f > 0; }));
    const auto dist2 = CI(std::count_if(RNG(freq2), [](const int f) { return f > 0; }));

    bool ok = false;
    FOR(c1, 0, 25) {
      if (freq1[c1] == 0) continue;
      FOR(c2, 0, 25) {
        if (freq2[c2] == 0) continue;
        if (c1 == c2) {
          ok |= (dist1 == dist2);
        } else {
          const auto upd_dist1 = dist1 - (freq1[c1] == 1 ? 1 : 0) + (freq1[c2] == 0 ? 1 : 0);
          const auto upd_dist2 = dist2 - (freq2[c2] == 1 ? 1 : 0) + (freq2[c1] == 0 ? 1 : 0);
          ok |= (upd_dist1 == upd_dist2);
        }
      }
    }
    return ok;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
