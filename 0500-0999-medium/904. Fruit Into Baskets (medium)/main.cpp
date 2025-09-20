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

using namespace std;
using namespace std::literals;

using ii = std::pair<int, int>;

class Solution {
public:
  int totalFruit(vector<int>& fruits) {
    const int n = fruits.size();
    ii f1{-1, -1}, f2{-1, -1}, f3{-1, -1}; // <fruit, max_idx>
    auto max_res = 0;
    for (auto i = 0; i < n; ++i) {
      const auto f = fruits[i];
      if (f != f2.first && f != f3.first) { // new or 3rd fruit
        f1 = f2, f2 = f3, f3 = {f, i};
      } else if (f == f1.first) {
        f1.second = i;
        swap(f1, f2);
        swap(f2, f3);
      } else if (f == f2.first) {
        f2.second = i;
        swap(f2, f3);
      } else if (f == f3.first) {
        f3.second = i;
      }
      const auto res = (f1.second == -1) ? (f3.second + 1) : (f3.second - f1.second);
      max_res = max(max_res, res);
    }
    return max_res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<int> fruits{1,2,1};
    const auto a_out = Solution().totalFruit(fruits);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<int> fruits{0,1,2,2};
    const auto a_out = Solution().totalFruit(fruits);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<int> fruits{1,2,3,2,2};
    const auto a_out = Solution().totalFruit(fruits);
    assert(a_out == 4);
  
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
