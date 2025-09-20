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

class Solution {
public:
  std::string longestDiverseString(int a, int b, int c) {
    std::priority_queue<std::pair<int, char>> pq;
    if (a > 0) pq.emplace(a, 'a');
    if (b > 0) pq.emplace(b, 'b');
    if (c > 0) pq.emplace(c, 'c');

    std::string s;
    while (!pq.empty()) {
      auto [cnt1, c1] = pq.top();
      pq.pop();

      if (s.size() >= 2 && s.back() == c1 && s[s.size()-2] == c1) {
        if (pq.empty()) break;

        auto [cnt2, c2] = pq.top();
        pq.pop();

        s += c2;
        --cnt2;

        if (cnt2 > 0) pq.emplace(cnt2, c2);

        pq.emplace(cnt1, c1);
      } else {
        s += c1;
        --cnt1;
        if (cnt1 > 0) pq.emplace(cnt1, c1);
      }
    }

    return s;
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
