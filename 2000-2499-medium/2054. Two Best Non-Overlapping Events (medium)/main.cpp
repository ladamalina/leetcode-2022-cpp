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
  int maxTwoEvents(vvi& events1) {
    const auto n = SZ(events1);
    std::sort(RNG(events1), [](const vi& a, const vi& b) {
      return std::tie(a[1], a[0]) < std::tie(b[1], b[0]);
    });

    auto events2 = events1;
    std::sort(RNG(events2), [](const vi& a, const vi& b) {
      return std::tie(a[0], a[1]) < std::tie(b[0], b[1]);
    });
    vi suff_max(n);
    FORD(i, n-1, 0) {
      suff_max[i] = (i == n-1) ? events2[i][2] : std::max(events2[i][2], suff_max[i+1]);
    }

    int max_res = 0;
    int max1 = 0;
    FOR(i, 0, n-1) {
      max1 = (i == 0) ? events1[i][2] : std::max(max1, events1[i][2]);

      const auto it = std::upper_bound(RNG(events2), events1[i][1], [&](int x, const vi& a) {
        return a[0] > x;
      });
      const auto max2 = (it == events2.end()) ? 0 : suff_max[it - events2.begin()];

      max_res = std::max(max_res, max1 + max2);
    }

    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi events{{1,3,2},{4,5,2},{2,4,3}};
    const auto a_out = Solution().maxTwoEvents(events);
    assert(a_out == 4);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi events{{1,3,2},{4,5,2},{1,5,5}};
    const auto a_out = Solution().maxTwoEvents(events);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi events{{1,5,3},{1,5,1},{6,6,5}};
    const auto a_out = Solution().maxTwoEvents(events);
    assert(a_out == 8);
  
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
