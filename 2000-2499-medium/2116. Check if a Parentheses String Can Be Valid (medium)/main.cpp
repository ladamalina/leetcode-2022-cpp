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
  bool canBeValid(const std::string& s, const std::string& locked) {
    const auto n = SZ(s);
    if (n % 2 == 1)
      return false;
    
    std::stack<int> open_ids, unlocked_ids;
    FOR(i, 0, n-1) {
      if (locked[i] == '1') {
        if (s[i] == '(') {
          open_ids.push(i);
        } else { // ')'
          if (!open_ids.empty()) {
            open_ids.pop();
          } else if (!unlocked_ids.empty()) {
            unlocked_ids.pop();
          } else {
            return false;
          }
        }
      } else {
        unlocked_ids.push(i);
      }
    }

    while (!open_ids.empty() && !unlocked_ids.empty() && open_ids.top() < unlocked_ids.top()) {
      open_ids.pop();
      unlocked_ids.pop();
    }
    if (open_ids.empty() && !unlocked_ids.empty())
      return SZ(unlocked_ids) % 2 == 0;

    return open_ids.empty();
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("))()))"s);
    const std::string locked("010100"s);
    const auto a_out = Solution().canBeValid(s, locked);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("()()"s);
    const std::string locked("0000"s);
    const auto a_out = Solution().canBeValid(s, locked);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s(")"s);
    const std::string locked("0"s);
    const auto a_out = Solution().canBeValid(s, locked);
    assert(!a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("())()))()(()(((())(()()))))((((()())(())"s);
    const std::string locked("1011101100010001001011000000110010100101"s);
    const auto a_out = Solution().canBeValid(s, locked);
    assert(a_out);
  
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
