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
#define F first
#define S second

constexpr int MIN_N=6, MAX_N=20;

class Solution {
public:
  int strongPasswordChecker(std::string& s) {
    const auto n = CI(s.size());
    auto del_tar = std::max(0, n - MAX_N);
    auto add_tar = std::max(0, MIN_N - n);
    auto to_del=0, to_add=0, to_rep=0, need_l=1, need_u=1, need_d=1;

    for (auto l=0, r=0; r<n; ++r) {
      if (std::islower(s[r])) { need_l = 0; }
      if (std::isupper(s[r])) { need_u = 0; }
      if (std::isdigit(s[r])) { need_d = 0; }

      if (r-l == 2) {
        if (s[l]==s[l+1] && s[l+1]==s[r]) {
          if (to_add < add_tar) { ++to_add; l = r; }
          else { ++to_rep; l = r+1; }
        } else { l++; }
      }
    }
    if (n <= 20)
      return std::max(add_tar+to_rep, need_l+need_u+need_d);

    // n > 20
    
    to_rep = 0;
    std::vector<std::unordered_map<int, int>> len_freq(3);
    for (auto l=0, r=0; r<=n; ++r) {
      if (r==n || s[l]!=s[r]) {
        if (r-l>2) ++len_freq[(r-l)%3][(r-l)];
        l = r;
      }
    }
    
    for (auto i=0; i<3; ++i) {                
      for (auto it = len_freq[i].begin(); it != len_freq[i].end(); ++it) {
        if (i<2) {
          const auto num = i+1;
          const auto dec = std::min(it->S, (del_tar-to_del)/num);
          to_del += dec * num;
          it->S -= dec;
          if (it->F - num > 2)
            len_freq[2][it->F - num] += dec;
        }
        to_rep += it->S * (it->F / 3);
      }
    }

    const auto dec = (del_tar - to_del) / 3;
    to_rep -= dec;
    to_del -= dec*3;
    return del_tar + std::max(to_rep, need_u+need_l+need_d);
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("a");
    const auto a_out = Solution().strongPasswordChecker(s);
    assert(a_out == 5);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("aA1");
    const auto a_out = Solution().strongPasswordChecker(s);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("1337C0d3");
    const auto a_out = Solution().strongPasswordChecker(s);
    assert(a_out == 0);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("aaa111");
    const auto a_out = Solution().strongPasswordChecker(s);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("ABABABABABABABABABAB1");
    const auto a_out = Solution().strongPasswordChecker(s);
    assert(a_out == 2);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s("bbaaaaaaaaaaaaaaacccccc");
    const auto a_out = Solution().strongPasswordChecker(s);
    assert(a_out == 8);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    std::string s(50, 'a'); // aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    const auto a_out = Solution().strongPasswordChecker(s);
    assert(a_out == 36);
  
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
