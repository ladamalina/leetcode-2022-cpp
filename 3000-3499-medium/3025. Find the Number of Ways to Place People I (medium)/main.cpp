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
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

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

bool IsLeftCorner(const int pi, const int pj, const vvi& ps) {
  return (ps[pi][0] <= ps[pj][0] && ps[pi][1] >= ps[pj][1]) || (ps[pj][0] <= ps[pi][0] && ps[pj][1] >= ps[pi][1]);
}

bool Check(const int pi, const int pj, const vvi& ps) {
  if (!IsLeftCorner(pi, pj, ps))
    return false;
  const auto pn = SZ(ps);
  const auto min_x = std::min(ps[pi][0], ps[pj][0]), max_x = std::max(ps[pi][0], ps[pj][0]);
  const auto min_y = std::min(ps[pi][1], ps[pj][1]), max_y = std::max(ps[pi][1], ps[pj][1]);
  FOR(pk, 0, pn - 1) {
    if (pk != pi && pk != pj && ps[pk][0] >= min_x && ps[pk][0] <= max_x && ps[pk][1] >= min_y && ps[pk][1] <= max_y)
      return false;
  }
  return true;
}

class Solution {
public:
  int numberOfPairs(const vvi& ps) {
    const auto pn = SZ(ps);
    auto res = 0;
    FOR(pi, 0, pn - 2) {
      FOR(pj, pi + 1, pn - 1) {
        res += Check(pi, pj, ps);
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi ps{{1,1},{2,2},{3,3}};
    const auto a_out = Solution().numberOfPairs(ps);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi ps{{6,2},{4,4},{2,6}};
    const auto a_out = Solution().numberOfPairs(ps);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi ps{{3,1},{1,3},{1,1}};
    const auto a_out = Solution().numberOfPairs(ps);
    assert(a_out == 2);
  
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
