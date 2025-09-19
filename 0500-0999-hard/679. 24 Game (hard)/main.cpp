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
using ld = long double;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vvvi = std::vector<vvi>;
using vl = std::vector<ll>;
using vvl = std::vector<vl>;
using vvvl = std::vector<vvl>;
using vii = std::vector<ii>;
using vb = std::vector<bool>;
using vd = std::vector<ld>;
using vs = std::vector<std::string>;
using vc = std::vector<char>;

#define FOR(_i, _a, _b) for (auto _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (auto _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define CC(_v) static_cast<char>(_v)
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second
#define PB push_back

const auto EPS = 1e-6;
template <typename T>
bool Eq(T a, T b) { return std::abs(a - b) < EPS; }

const std::string fs("+-*/"s);
/*
  . . . . + + +
  . . + . . + +
  . . . + + . +
 */
constexpr std::array<std::array<int, 4>, 3> P_IDS = {std::array<int, 4>{0,1,2,3},std::array<int, 4>{0,1,3,4},std::array<int, 4>{0,1,2,5}};
constexpr std::array<std::array<int, 3>, 3> F_IDS = {std::array<int, 3>{4,5,6},std::array<int, 3>{2,5,6},std::array<int, 3>{3,4,6}};
std::string s(7, '_');

double Solve() {
  std::stack<double> st;
  for (const auto& c : s) {
    if ('1' <= c && c <= '9') {
      st.push(c - '0');
    } else {
      const auto num2 = st.top(); st.pop();
      const auto num1 = st.top(); st.pop();
      switch (c) {
        case '+': {
          st.push(num1 + num2);
          break;
        }
        case '-': {
          st.push(num1 - num2);
          break;
        }
        case '*': {
          st.push(num1 * num2);
          break;
        }
        case '/': {
          if (num2 == 0) return 0;
          st.push(num1 / num2);
          break;
        }
        default: break;
      }
    }
  }
  return st.top();
}

class Solution {
 public:
  static bool judgePoint24(const vi& cards) {
    FOR(pf, 0, SZ(P_IDS) - 1) {
      auto ps = P_IDS[pf];
      const auto& f_ids = F_IDS[pf];
      do {
        FOR(i, 0, SZ(cards) - 1) {
          s[ps[i]] = CC('0' + cards[i]);
        }
        FOR(i, 0, SZ(fs) - 1) {
          s[f_ids[0]] = fs[i];
          FOR(j, 0, SZ(fs) - 1) {
            s[f_ids[1]] = fs[j];
            FOR(k, 0, SZ(fs) - 1) {
              s[f_ids[2]] = fs[k];
              const auto res = Solve();
              if (Eq(res, 24.))
                return true;
            }
          }
        }
      } while (std::next_permutation(RNG(ps)));
    }
    return false;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::judgePoint24({4,1,8,7});
    assert(a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::judgePoint24({1,2,1,2});
    assert(!a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const auto a_out = Solution::judgePoint24({1,9,1,2});
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
