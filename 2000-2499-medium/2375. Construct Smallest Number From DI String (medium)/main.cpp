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
  std::string smallestNumber(const std::string& pattern) {
    const auto pn = SZ(pattern);
    std::string best_res;
    std::string res;
    std::array<int, 10> used{};
    const std::function<bool(int,int)> rec = [&](int i, int pd) {
      if (i == pn) {
        if (best_res.empty() || res < best_res)
          best_res = res;
        return true;
      }
      if (pattern[i] == 'I') {
        for (auto d = pd + 1; d <= 9; ++d) {
          if (!used[d]) {
            used[d] = 1; res.push_back(static_cast<char>('0' + d));
            const auto sub_res = rec(i + 1, d);
            used[d] = 0; res.pop_back();
            if (sub_res)
              return true;
          }
        }
      } else {
        for (auto d = 1; d <= pd - 1; ++d) {
          if (!used[d]) {
            used[d] = 1; res.push_back(static_cast<char>('0' + d));
            const auto sub_res = rec(i + 1, d);
            used[d] = 0; res.pop_back();
            if (sub_res)
              return true;
          }
        }
      }
      return false;
    };
    for (auto d = 1; d <= 9; ++d) {
      used[d] = 1; res.push_back(static_cast<char>('0' + d));
      const auto sub_res = rec(0, d);
      used[d] = 0; res.pop_back();
      if (sub_res)
        break;
    }
    return best_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().smallestNumber("IIIDIDDD");
    assert(a_out == "123549876");
  
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
