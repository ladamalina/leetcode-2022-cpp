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
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvvvi [[maybe_unused]] = std::vector<vvvi>;
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
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

class Solution {
public:
  bool isInterleave(const std::string& s1, const std::string& s2, const std::string& s3) {
    const auto n1 = SZ(s1), n2 = SZ(s2), n3 = SZ(s3);
    if (n1 + n2 != n3) return false;
    if (n1 == 0) return s2 == s3;
    if (n2 == 0) return s1 == s3;

    vvvi dp(n1, vvi(n2, vi(n3, -1)));
    const std::function<int(int,int,int)> rec = [&](int i1, int i2, int i3) {
      if (i3 == n3) return 1;
      if (i1 == n1) return CI(s2.substr(i2) == s3.substr(i3));
      if (i2 == n2) return CI(s1.substr(i1) == s3.substr(i3));

      auto& res = dp[i1][i2][i3];
      if (res != -1) return res;
      res = 0;

      if (s1[i1] == s3[i3])
        res |= rec(i1+1, i2, i3+1);
      if (s2[i2] == s3[i3])
        res |= rec(i1, i2+1, i3+1);

      return res;
    };
    const auto res = rec(0, 0, 0);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto s1 = "aabcc"s;
    const auto s2 = "dbbca"s;
    const auto s3 = "aadbbcbcac"s;
    const auto a_out = Solution().isInterleave(s1, s2, s3);
    assert(a_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto s1 = "aabcc"s;
    const auto s2 = "dbbca"s;
    const auto s3 = "aadbbbaccc"s;
    const auto a_out = Solution().isInterleave(s1, s2, s3);
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto s1 = ""s;
    const auto s2 = ""s;
    const auto s3 = ""s;
    const auto a_out = Solution().isInterleave(s1, s2, s3);
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
