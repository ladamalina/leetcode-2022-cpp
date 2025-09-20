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
  int robotSim(const vi& commands, const vvi& obstacles) {
    std::set<ii> o_set;
    for (const auto& o : obstacles)
      o_set.emplace(o[0], o[1]);

    ii d{0, 1};

    const auto rotate = [](ii d, int dir) {
      if (d == ii{0, 1})
        return (dir == -1) ? ii{1, 0} : ii{-1, 0};
      if (d == ii{0, -1})
        return (dir == -1) ? ii{-1, 0} : ii{1, 0};
      if (d == ii{1, 0})
        return (dir == -1) ? ii{0, -1} : ii{0, 1};
      return (dir == -1) ? ii{0, 1} : ii{0, -1};
    };

    int max_sq = 0;
    int x = 0, y = 0;
    for (const auto& c : commands) {
      if (c == -1 || c == -2) {
        d = rotate(d, c);
        continue;
      }
      FOR(k, 1, c) {
        const auto nx = x + d.F, ny = y + d.S;
        if (o_set.contains({nx, ny}))
          break;
        x = nx; y = ny;
      }
      max_sq = std::max(max_sq, x*x + y*y);
    }

    return max_sq;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi commands{4,-1,3};
    const vvi obstacles{};
    const auto a_out = Solution().robotSim(commands, obstacles);
    assert(a_out == 25);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi commands{4,-1,4,-2,4};
    const vvi obstacles{{2,4}};
    const auto a_out = Solution().robotSim(commands, obstacles);
    assert(a_out == 65);
  
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
