//#include <bits/stdc++.h>

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

class Solution {
 public:
  static std::string crackSafe(int n, int k) {
    const auto max_d = static_cast<char>('0'+(k-1));

    if (k==1) {
      return std::string(n, '0');
    }
    if (n==1) {
      std::string res;
      for (auto d='0'; d<=max_d; ++d) {
        res.push_back(d);
      }
      return res;
    }

    const auto vn = CI(std::pow(k, n));
    std::string res(n, '0');
    std::unordered_set<std::string> vis{res};

    const std::function<bool()> dfs = [&]() {
      if (CI(vis.size()) == vn) return true;

      auto v = res.substr(res.size()-(n-1), n-1);
      for (auto d='0'; d<=max_d; ++d) {
        v.push_back(d);
        if (!vis.contains(v)) {
          vis.insert(v);
          res.push_back(d);
          if (dfs()) return true;
          vis.erase(v);
          res.pop_back();
        }
        v.pop_back();
      }
      return false;
    };
    dfs();

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::crackSafe(1, 2);
    assert(e_out.size() == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::crackSafe(2, 2);
    assert(e_out.size() == 5);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto e_out = Solution::crackSafe(2, 3);
    assert(e_out.size() == 10);

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
