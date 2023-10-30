// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
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
#define F first
#define S second
#define PB push_back

class Solution {
public:
  vvi subsets(const vi& nums) {
    const auto n = CI(nums.size());
    const auto max_m = (1<<n)-1;
    vvi res;
    FOR(m, 0, max_m) {
      res.emplace_back();
      auto& curr_res = res.back();
      FOR(i, 0, n-1) {
        if (m&(1<<i)) curr_res.push_back(nums[i]);
      }
    }
    return res;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
// #ifndef NDEBUG
//   TestSolution();
// #endif
// Solution(std::cin, std::cout);
  return 0;
}
