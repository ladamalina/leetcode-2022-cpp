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

std::array<int, 26> c2i;
std::array<int, 32> pcodes;

class Solution {
public:
  int findTheLongestSubstring(const std::string& s) {
    std::fill(c2i.begin(), c2i.end(), -1);
    c2i['a'-'a'] = 0;
    c2i['e'-'a'] = 1;
    c2i['i'-'a'] = 2;
    c2i['o'-'a'] = 3;
    c2i['u'-'a'] = 4;

    const auto n = static_cast<int>(s.size());
    std::fill(pcodes.begin(), pcodes.end(), n);

    auto pcode = 0, max_len = 0;
    pcodes[pcode] = -1;
    for (auto i = 0; i < n; ++i) {
      const auto c = s[i] - 'a';
      if (c2i[c] != -1) {
        pcode ^= (1<<(c2i[c]));
        pcodes[pcode] = std::min(pcodes[pcode], i);
      }
      max_len = std::max(max_len, i - pcodes[pcode]);
      // std::cerr << "i = " << i << "\tpcode = " << pcode << "\tpcodes[pcode] = " << pcodes[pcode] << "\tmax_len = " << max_len << "\n";
    }

    return max_len;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findTheLongestSubstring("eleetminicoworoep"s);
    assert(a_out == 13);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findTheLongestSubstring("leetcodeisgreat"s);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().findTheLongestSubstring("bcbcbc"s);
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
