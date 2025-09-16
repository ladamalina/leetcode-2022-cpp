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
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
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
using vc [[maybe_unused]] = std::vector<char>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second

std::array<ll, 10> nums1, nums2;
std::string ops1(9, ' '), ops2(9, ' ');

ll Eval(const std::string& s) {
  auto n1 = 0;
  {
    std::string num;
    for (const auto c : s) {
      if ('0'<=c && c<='9') num += c;
      else {
        if (!num.empty()) {
          if (num[0]=='0' && num.size()!=1) return LLONG_MIN;
          nums1[n1] = std::stoll(num);
          num.clear();
        }
        ops1[n1] = c;
        ++n1;
      }
    }
    if (!num.empty()) {
      if (num[0]=='0' && num.size()!=1) return LLONG_MIN;
      nums1[n1] = std::stoll(num);
      ++n1;
    }
  }
  
  // eval *
  auto n2 = 0;
  {
    ll pnum;
    bool pmult = false;
    FOR(i, 0, n1-1) {
      if (i < n1-1) {
        if (pmult) {
          pnum *= nums1[i];
        } else {
          pnum = nums1[i];
        }
        if (ops1[i]=='*') {
          pmult = true;
        } else {
          pmult = false;
          nums2[n2] = pnum;
          ops2[n2] = ops1[i];
          ++n2;
        }
      } else {
        nums2[n2] = pmult ? pnum*nums1[i] : nums1[i];
        ++n2;
      }
    }
  }
  
  // eval +/-
  ll res = nums2[0];
  {
    FOR(i, 1, n2-1) {
      if (ops2[i-1]=='+') res += nums2[i];
      else res -= nums2[i];
    }
  }
  return res;
}

void Rec(int i, int n, std::string& pref, vs& res, const std::string& num, int target) {
  if (i == n) {
    if (Eval(pref)==target)
      res.push_back(pref);
    return;
  }
  // no sign
  pref.push_back(num[i]);
  Rec(i+1, n, pref, res, num, target);
  pref.pop_back();

  if (i < n-1) {
    { // +
      pref.push_back(num[i]);
      pref.push_back('+');
      Rec(i+1, n, pref, res, num, target);
      pref.pop_back();
      pref.pop_back();
    }
    { // -
      pref.push_back(num[i]);
      pref.push_back('-');
      Rec(i+1, n, pref, res, num, target);
      pref.pop_back();
      pref.pop_back();
    }
    { // *
      pref.push_back(num[i]);
      pref.push_back('*');
      Rec(i+1, n, pref, res, num, target);
      pref.pop_back();
      pref.pop_back();
    }
  }
}

class Solution {
public:
  vs addOperators(const std::string& num, int target) {
    const auto n = CI(num.size());
    std::string pref;
    pref.reserve(20);
    vs res;
    Rec(0, n, pref, res, num, target);
    return res;
  }
};

[[maybe_unused]] void TestEval() {
  const auto a_out1 = Eval("1*2*3");
  assert(a_out1 == 6);
  
  const auto a_out2 = Eval("1+2+3");
  assert(a_out2 == 6);
  
  const auto a_out3 = Eval("1+2*3");
  assert(a_out3 == 7);

  const auto a_out4 = Eval("1*2+3");
  assert(a_out4 == 5);

  const auto a_out5 = Eval("1*2+03");
  assert(a_out5 == LLONG_MIN);

  const auto a_out6 = Eval("1*0+5");
  assert(a_out6 == 5);
  
  std::cerr << "TestEval OK"sv << std::endl;
}

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().addOperators("123", 6);
    assert(a_out.size() == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().addOperators("232", 8);
    assert(a_out.size() == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().addOperators("3456237490", 9191);
    assert(a_out.size() == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestEval();
  TestSolution();
#endif
  return 0;
}
