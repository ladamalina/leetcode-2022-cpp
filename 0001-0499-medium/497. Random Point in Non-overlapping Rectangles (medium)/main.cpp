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

static std::random_device rd;
static std::mt19937 gen(rd());

class Solution {
public:
  explicit Solution(const vvi& rects) : rects_(rects), n_(SZ(rects_)), sq_(n_) {
    auto p = -1;
    FOR(i, 0, n_-1) {
      const auto dx = rects_[i][2] - rects_[i][0], dy = rects_[i][3] - rects_[i][1];
      sq_[i] = {p + 1, p + (dx+1)*(dy+1)};
      p = sq_[i].S;
    }
  }

  [[nodiscard]] vi pick() const {
    std::uniform_int_distribution<> dist_sq(sq_.front().F, sq_.back().S);
    const auto sq_val = dist_sq(gen);
    const auto it = std::lower_bound(RNG(sq_), sq_val,
      [&](const ii& a, const int val) { return a.S < val; });
    const auto i = CI(it - sq_.begin());

    std::uniform_int_distribution<> dist_x(rects_[i][0], rects_[i][2]);
    const auto x = dist_x(gen);
    std::uniform_int_distribution<> dist_y(rects_[i][1], rects_[i][3]);
    const auto y = dist_y(gen);

    return {x, y};
  }

private:
  const vvi& rects_;
  int n_;
  vii sq_;
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi rects{{-2, -2, 1, 1},{2, 2, 4, 6}};
    const Solution solution(rects);
    FOR(_, 1, 100) {
      const auto xy = solution.pick();
      assert(std::any_of(RNG(rects), [&](const vi& r) {
        return r[0] <= xy[0] && xy[0] <= r[2] && r[1] <= xy[1] && xy[1] <= r[3];
      }));
    }
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi rects{{82918473,-57180867,82918476,-57180863},{83793579,18088559,83793580,18088560},
      {66574245,26243152,66574246,26243153},{72983930,11921716,72983934,11921720}};
    const Solution solution(rects);
    FOR(_, 1, 1000) {
      const auto xy = solution.pick();
      assert(std::any_of(RNG(rects), [&](const vi& r) {
        return r[0] <= xy[0] && xy[0] <= r[2] && r[1] <= xy[1] && xy[1] <= r[3];
      }));
    }
  
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
