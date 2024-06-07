#include <bits/stdc++.h>

/*#include <algorithm>
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
#include <vector>*/

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
#define F first
#define S second

class Solution {
public:
  std::string reverseParentheses(const std::string& s) {
    const auto n = CI(s.size());
    vi lp(n), rp(n);
    std::stack<int> st;
    FOR(i, 0, n-1) {
      if (s[i] == '(') st.push(i);
      else if (s[i] == ')') {
        const auto l = st.top();
        st.pop();
        lp[i] = l;
        rp[l] = i;
      }
    }

    bool dir = true;
    std::string t;
    int i = 0;
    while (i>=0 && i<n) {
      if (dir) {
        if ('a'<=s[i] && s[i]<='z') {
          t += s[i];
          ++i;
        } else if (s[i]=='(') {
          dir = !dir;
          i = rp[i]-1;
        } else {
          dir = !dir;
          i = lp[i]-1;
        }
      } else {
        if ('a'<=s[i] && s[i]<='z') {
          t += s[i];
          --i;
        } else if (s[i]=='(') {
          dir = !dir;
          i = rp[i]+1;
        } else {
          dir = !dir;
          i = lp[i]+1;
        }
      }
    }
    return t;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("(abcd)");
    const auto a_out = Solution().reverseParentheses(s);
    assert(a_out == "dcba");
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("(u(love)i)");
    const auto a_out = Solution().reverseParentheses(s);
    assert(a_out == "iloveu");
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::string s("(ed(et(oc))el)");
    const auto a_out = Solution().reverseParentheses(s);
    assert(a_out == "leetcode");
  
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
