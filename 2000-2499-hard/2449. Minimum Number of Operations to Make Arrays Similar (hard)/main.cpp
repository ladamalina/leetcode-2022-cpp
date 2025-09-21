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

int SortOddsEven(vi& arr) {
  const auto n = SZ(arr);
  int k = 0;
  FOR(i, 0, n-1) {
    if (arr[i] & 1) {
      std::swap(arr[i], arr[k]);
      ++k;
    }
  }
  return k;
}

class Solution {
public:
  ll makeSimilar(vi& arr1, vi& arr2) {
    const auto n = SZ(arr1);
    const auto n_odds = SortOddsEven(arr1);
    SortOddsEven(arr2);
    std::sort(arr1.begin(), arr1.begin() + n_odds);
    std::sort(arr1.begin() + n_odds, arr1.end());
    std::sort(arr2.begin(), arr2.begin() + n_odds);
    std::sort(arr2.begin() + n_odds, arr2.end());

    ll dec_ops = 0, inc_ops = 0;
    FOR(i, 0, n-1) {
      if (arr1[i] >= arr2[i])
        dec_ops += (arr1[i] - arr2[i]) / 2;
      else
        inc_ops += (arr2[i] - arr1[i]) / 2;
    }
    assert(dec_ops == inc_ops);
    return dec_ops;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi arr1{8,12,6};
    vi arr2{2,14,10};
    const auto a_out = Solution().makeSimilar(arr1, arr2);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi arr1{1,2,5};
    vi arr2{4,1,3};
    const auto a_out = Solution().makeSimilar(arr1, arr2);
    assert(a_out == 1);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi arr1{1,1,1,1,1};
    vi arr2{1,1,1,1,1};
    const auto a_out = Solution().makeSimilar(arr1, arr2);
    assert(a_out == 0);
  
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
