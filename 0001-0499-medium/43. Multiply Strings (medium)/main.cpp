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

std::string MultStr(const std::string& s, const int x, const int add_z) {
  if (x == 0 || s == "0"s)
    return "0";
  const auto sn = SZ(s);

  std::string res;
  int over = 0;
  FORD(si, sn-1, 0) {
    const auto k = (s[si]-'0')*x + over;
    res.push_back(char('0'+(k%10)));
    over = k / 10;
  }
  while (over > 0) {
    res.push_back(char('0'+over%10));
    over /= 10;
  }

  while (res.size() > 1 && res.back() == '0')
    res.pop_back();
  std::reverse(RNG(res));
  if (add_z > 0)
    res += std::string(add_z, '0');

  return res;
}

std::string SumStr(std::string s1, std::string s2) {
  if (s1.size() < s2.size()) {
    const auto diff = s2.size() - s1.size();
    s1 = std::string(diff, '0') + s1;
  }
  if (s2.size() < s1.size()) {
    const auto diff = s1.size() - s2.size();
    s2 = std::string(diff, '0') + s2;
  }
  // s2.size() == s1.size()

  const auto sn = SZ(s1);
  std::string res;
  int over = 0;
  FORD(si, sn-1, 0) {
    const auto k = (s1[si]-'0') + (s2[si]-'0') + over;
    res.push_back('0'+(k%10));
    over = k / 10;
  }
  while (over > 0) {
    res.push_back(char('0'+over%10));
    over /= 10;
  }

  while (res.size() > 1 && res.back() == '0')
    res.pop_back();
  std::reverse(RNG(res));

  return res;
}

class Solution {
public:
  std::string multiply(const std::string& num1, const std::string& num2) {
    const auto n1 = SZ(num1)/*, n2 = SZ(num2)*/;
    std::string res = "0"s;
    FOR(i, 0, n1-1) {
      const auto mult = MultStr(num2, num1[i]-'0', n1-1-i);
      // std::cerr << num2 << '\t' << num1[i]-'0' << '\t' << mult << '\n';
      res = SumStr(res, mult);
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().multiply("2", "3");
    assert(a_out == "6");
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().multiply("123", "456");
    assert(a_out == "56088");
  
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
