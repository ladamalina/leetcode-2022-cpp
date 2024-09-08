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
  vi constructDistancedSequence(const int n) {
    vi used(n+1);
    const auto sn = 2*n-1;
    vi seq(sn);

    const std::function<bool(int)> rec = [&](const int i) {
      if (i == sn)
        return true;
      if (seq[i])
        return rec(i+1);
      FORD(x, n, 2) {
        if (!used[x] && i+x < sn && !seq[i+x]) {
          seq[i] = x;
          seq[i+x] = x;
          used[x] = 1;
          if (rec(i+1))
            return true;
          seq[i] = 0;
          seq[i+x] = 0;
          used[x] = 0;
        }
      }
      // try to use 1
      if (!used[1]) {
        seq[i] = 1;
        used[1] = 1;
        if (rec(i+1))
          return true;
        seq[i] = 0;
        used[1] = 0;
      }
      return false;
    };
    rec(0);

    return seq;
    
    /*FOR(i, 0, 2*n-2) {
      if (seq[i] != 0)
        continue;
      FORD(x, n, 2) {
        if (!used[x] && i+x < 2*n-1 && !seq[i+x]) {
          seq[i] = x;
          seq[i+x] = x;
          used[x] = 1;
          break;
        }
      }
      if (!seq[i])
        seq[i] = 1;
    }
    return seq;*/
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
