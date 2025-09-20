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
using namespace std;

class Solution {
public:
  double new21Game(const int n, const int k, const int max_pts) {
    std::vector<double> p(n + 1), d(n + 1);
    d[0] = 1;
    double res = 0;
    for (auto i = 0; i <= n; ++i) {
      p[i] = (i > 1 ? p[i-1] : 0.0) + d[i];
      if (i < k) {
        const auto r = std::min(n, i + max_pts);
        const auto prob = p[i] / max_pts;
        if (i + 1 <= n) d[i+1] += prob;
        if (r + 1 <= n) d[r+1] -= prob;
      } else {
        res += p[i];
      }
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  constexpr auto EPS = 1e-5;
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    constexpr auto e_out = 1.00000;
    const auto a_out = Solution().new21Game(10, 1, 10);
    const auto ok = std::abs(a_out - e_out) < EPS;
    if (!ok) std::cerr << std::setprecision(6) << "e_out=" << e_out << "\na_out=" << a_out << '\n';
    assert(ok);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    constexpr auto e_out = 0.60000;
    const auto a_out = Solution().new21Game(6, 1, 10);
    const auto ok = std::abs(a_out - e_out) < EPS;
    if (!ok) std::cerr << std::setprecision(6) << "e_out=" << e_out << "\na_out=" << a_out << '\n';
    assert(ok);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    constexpr auto e_out = 0.73278;
    const auto a_out = Solution().new21Game(21, 17, 10);
    const auto ok = std::abs(a_out - e_out) < EPS;
    if (!ok) std::cerr << std::setprecision(6) << std::fixed << "e_out=" << e_out << "\na_out=" << a_out << '\n';
    assert(ok);
  
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
