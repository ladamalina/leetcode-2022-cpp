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
  int sumImbalanceNumbers(const vi& nums) {
    const auto n = SZ(nums);
    int res = 0;
    FOR(i, 0, n-2) {
      std::set<int> x_set{nums[i]};
      auto i_res = 0;
      FOR(j, i+1, n-1) {
        const auto [it, inserted] = x_set.insert(nums[j]);
        if (inserted) {
          const auto has_bef = (it != x_set.begin());
          const auto has_aft = (it != std::prev(x_set.end()));
          if (has_bef && !has_aft) {
            const auto it_bef = std::prev(it);
            i_res += (*it - *it_bef > 1);
          } else if (!has_bef && has_aft) {
            const auto it_aft = std::next(it);
            i_res += (*it_aft - *it > 1);
          } else { // has_bef && has_aft
            const auto it_bef = std::prev(it), it_aft = std::next(it);
            if (*it_aft - *it_bef > 1)
              --i_res;
            i_res += (*it - *it_bef > 1);
            i_res += (*it_aft - *it > 1);
          }
        }
        res += i_res;
      }
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
