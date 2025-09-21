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

class Solution {
public:
  ll minimumDifference(const vi& nums) {
    const auto n = SZ(nums) / 3;
    std::priority_queue<ii, vii, std::less<>> l_pq;
    ll l_sum = 0, r_sum = 0;
    std::set<ii> r_set, r_add;
    FOR(i, 0, n-1) {
      l_sum += nums[i];
      l_pq.emplace(nums[i], i);
    }
    FOR(i, n, 3*n-1) {
      r_sum += nums[i];
      r_set.emplace(nums[i], i);
      if (SZ(r_set) > n) {
        const auto [x, j] = *r_set.begin();
        r_sum -= x;
        r_set.erase(r_set.begin());
        r_add.emplace(x, j);
      }
    }
    ll min_res = l_sum - r_sum;
    FOR(i, n, 2*n-1) {
      if (r_set.contains({nums[i], i})) {
        r_sum -= nums[i];
        r_set.erase({nums[i], i});

        r_sum += std::prev(r_add.end())->F;
        r_set.insert(*std::prev(r_add.end()));
        r_add.erase(std::prev(r_add.end()));
      } else {
        r_add.erase({nums[i], i});
      }
      
      l_sum += nums[i];
      l_pq.emplace(nums[i], i);
      if (SZ(l_pq) > n) {
        const auto [x, j] = l_pq.top();
        l_pq.pop();
        l_sum -= x;
      }

      min_res = std::min(min_res, l_sum - r_sum);
    }
    return min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
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
