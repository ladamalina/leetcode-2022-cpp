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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

std::array<int, 6> res_t, res_b;

class Solution {
public:
  int minDominoRotations(const vi& ts, const vi& bs) {
    std::fill(RNG(res_t), 0);
    std::fill(RNG(res_b), 0);

    const auto n = SZ(ts);
    FOR(i, 0, n-1) {
      FOR(x, 1, 6) {
        if (ts[i] != x && bs[i] != x) {
          res_t[x-1] = INT_MAX;
          res_b[x-1] = INT_MAX;
          continue;
        }
        res_t[x-1] += (res_t[x-1] != INT_MAX && ts[i] != x);
        res_b[x-1] += (res_b[x-1] != INT_MAX && bs[i] != x);
      }
    }
    const auto min_res = std::min(
      *std::min_element(RNG(res_t)),
      *std::min_element(RNG(res_b))
    );
    return min_res == INT_MAX ? -1 : min_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const vi ts{2,1,2,4,2,2};
    const vi bs{5,2,6,2,3,2};
    const auto a_out = Solution().minDominoRotations(ts, bs);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const vi ts{3,5,1,2,3};
    const vi bs{3,6,3,3,4};
    const auto a_out = Solution().minDominoRotations(ts, bs);
    assert(a_out == -1);
  
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
