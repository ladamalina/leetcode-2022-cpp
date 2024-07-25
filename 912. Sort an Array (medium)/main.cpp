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

std::random_device rd; // obtain a random number from hardware
std::mt19937 gen(rd()); // seed the generator

template<typename T>
std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>
    Partition(typename std::vector<T>::iterator beg, typename std::vector<T>::iterator end, T x) {
  auto e = beg, g = beg, n = beg;
  while (n != end) {
    if (*n == x) {
      if (g != n) std::swap(*g, *n);
      ++g;
    } else if (*n < x) {
      if (e != g && g != n) {
        std::swap(*g, *n);
        std::swap(*e, *g);
      } else if (e == g && g != n) {
        std::swap(*g, *n);
      } else if (e != g && g == n) {
        std::swap(*e, *n);
      } else { // e == g && g == n
        //
      }
      ++e;
      ++g;
    }
    ++n;
  }
  return {e, g};
}

template<typename It>
void QuickSort(It beg, It end) {
  const auto len = CI(std::distance(beg, end));
  if (len <= 1) return;

  std::uniform_int_distribution<> distr(0, len-1); // define the range
  const auto eg = Partition(beg, end, *(beg+distr(gen)));
  QuickSort(beg, eg.F);
  QuickSort(eg.S, end);
}

class Solution {
public:
  vi sortArray(vi& nums) {
    QuickSort(nums.begin(), nums.end());
    return nums;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi nums{5,2,3,1};
    const auto a_out = Solution().sortArray(nums);
    vi e_out{1,2,3,5};
    assert(a_out == e_out);
  
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
