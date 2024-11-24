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

int CountLT(int mult, int m, int n) {
  auto cnt_lt = 0;
  FOR(mi, 1, m) {
    const auto up_ni = (mult + mi - 1) / mi;
    cnt_lt += std::min(n, up_ni - 1);
  }
  return cnt_lt;
}

int CountEQ(int mult, int m, int n) {
  auto cnt_eq = 0;
  FOR(mi, 1, m) {
    cnt_eq += (mult % mi == 0 && mult / mi <= n);
  }
  return cnt_eq;
}

int CountGT(int mult, int m, int n) {
  return m * n - CountLT(mult, m, n) - CountEQ(mult, m, n);
}

bool BinCheck(int mult, int m, int n, int k) {
  return CountLT(mult, m, n) < k;
}

class Solution {
public:
  int findKthNumber(const int m, const int n, const int k) {
    int lo = 1, hi = m * n;
    while (lo < hi) {
      const auto mid = (lo + hi + 1) / 2;
      // const auto check =  BinCheck(mid, m, n, k);
      // std::cerr << lo << '\t' << mid << '\t' << hi << '\t' << check << '\n';
      if (CountLT(mid, m, n) < k)
        lo = mid;
      else
        hi = mid - 1;
    }
    FORD(mult, hi, 1) {
      if (CountEQ(mult, m, n))
        return mult;
    }
    return -1;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findKthNumber(3, 3, 5);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findKthNumber(2, 3, 6);
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
