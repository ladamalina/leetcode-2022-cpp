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

template <typename T>
T GCD(T a, T b) {
  while (a > 0 && b > 0) {
    if (a > b) { a = a % b; } else { b = b % a; }
  }
  return (a == 0) ? b : a;
}

template <typename T>
T LCM(T a, T b) {
  if (a > b) return (a / GCD(a, b)) * b;
  else return (b / GCD(a, b)) * a;
}

template <typename T>
struct Fraction {
  T a=0, b=1;
  Fraction(const T a_, const T b_) : a(a_), b(b_) {
    if (b < 0) {
      a *= -1;
      b *= -1;
    }
    if (b == 0) {
      a = (a > 0) ? std::numeric_limits<T>::max() : std::numeric_limits<T>::min();
      // b = 1;
    } else {
      const auto gcd = GCD(std::abs(a), std::abs(b));
      a /= gcd;
      b /= gcd;
    }
  }
  bool operator==(const Fraction& other) const {
    return a == other.a && b == other.b;
  }
};

std::vector<Fraction<int>> Parse(std::string& s) {
  std::vector<Fraction<int>> fs;
  while (!s.empty()) {
    const auto sl_pos = s.find('/');
    const auto num = std::stoi(s.substr(0, sl_pos));
    s = s.substr(sl_pos+1);
    const auto ps_pos = s.find('+');
    const auto ns_pos = s.find('-');
    const auto s_pos = std::min(ps_pos, ns_pos);
    if (s_pos == std::string::npos) {
      const auto den = std::stoi(s);
      s.clear();
      fs.emplace_back(num, den);
    } else {
      const auto den = std::stoi(s.substr(0, s_pos));
      s = s.substr(s_pos);
      fs.emplace_back(num, den);
    }
  }
  return fs;
}

class Solution {
public:
  std::string fractionAddition(std::string expression) {
    const auto fs = Parse(expression);
    auto lcm = 1;
    for (const auto& f : fs) {
      lcm = LCM(lcm, f.b);
    }
    auto num = 0;
    for (const auto& f : fs) {
      num += f.a * (lcm/f.b);
    }
    const Fraction<int> res_f(num, lcm);
    const std::string res = std::to_string(res_f.a) + "/" + std::to_string(res_f.b);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().fractionAddition("-1/2+1/2");
    assert(a_out == "0/1");
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().fractionAddition("-1/2+1/2+1/3");
    assert(a_out == "1/3");
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().fractionAddition("1/3-1/2");
    assert(a_out == "-1/6");
  
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
