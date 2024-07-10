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

std::vector<std::pair<int, std::string>> mp = {
  {1000000000, "Billion"},
  {1000000, "Million"},
  {1000, "Thousand"},
  {100, "Hundred"},
  {90, "Ninety"},
  {80, "Eighty"},
  {70, "Seventy"},
  {60, "Sixty"},
  {50, "Fifty"},
  {40, "Forty"},
  {30, "Thirty"},
  {20, "Twenty"},
  {19, "Nineteen"},
  {18, "Eighteen"},
  {17, "Seventeen"},
  {16, "Sixteen"},
  {15, "Fifteen"},
  {14, "Fourteen"},
  {13, "Thirteen"},
  {12, "Twelve"},
  {11, "Eleven"},
  {10, "Ten"},
  {9, "Nine"},
  {8, "Eight"},
  {7, "Seven"},
  {6, "Six"},
  {5, "Five"},
  {4, "Four"},
  {3, "Three"},
  {2, "Two"},
  {1, "One"}
};

class Solution {
public:
  std::string numberToWords(int num) {
    if (num == 0)
      return "Zero";

    for (const auto& it : mp){
      if (num >= it.first){
        std::string a;
        if (num >= 100)
          a = numberToWords(num / it.F) + " ";

        const auto b = it.S;

        std::string c;
        if (num % it.F != 0)
          c = " " + numberToWords(num % it.F);
        
        return a + b + c;
      }
    }
    return "";
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
