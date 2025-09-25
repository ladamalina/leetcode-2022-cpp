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
  vi solveQueries(const vi& nums, const vi& queries) {
    const auto n = SZ(nums), qn = SZ(queries);
    std::unordered_map<int, vi> x_ids;
    FOR(i, 0, n-1) x_ids[nums[i]].push_back(i);
    vi res(qn);
    FOR(qi, 0, qn-1) {
      const auto i = queries[qi];
      const auto& ids = x_ids[nums[i]];
      auto i_res = INT_MAX;
      const auto l_it = std::lower_bound(RNG(ids), i);
      if (l_it != ids.begin()) {
        i_res = std::min(i_res, i - *std::prev(l_it));
      } else if (ids.back() != i) {
        const auto d = n - (ids.back() - i);
        i_res = std::min(i_res, d);
      }
      const auto u_it = std::upper_bound(RNG(ids), i);
      if (u_it != ids.end()) {
        i_res = std::min(i_res, *u_it - i);
      } else if (ids[0] != i) {
        const auto d = n - (i - ids[0]);
        i_res = std::min(i_res, d);
      }
      res[qi] = (i_res == INT_MAX) ? -1 : i_res;
    }
    return res;
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
