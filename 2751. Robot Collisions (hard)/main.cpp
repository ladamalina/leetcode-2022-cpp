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
  vi survivedRobotsHealths(const vi& positions, vi& hs, const std::string& ds) {
    const auto n = CI(positions.size());
    vi ids(n);
    std::iota(RNG(ids), 0);
    std::sort(RNG(ids), [&](const int l, const int r) { return positions[l] < positions[r]; });

    std::stack<int> st;
    FOR(i, 0, n-1) {
      if (ds[ids[i]] == 'L') {
        while (!st.empty() && hs[ids[st.top()]] != 0 && hs[ids[i]] != 0) {
          if (hs[ids[st.top()]] > hs[ids[i]]) {
            --hs[ids[st.top()]];
            hs[ids[i]] = 0;
          } else if (hs[ids[st.top()]] < hs[ids[i]]) {
            hs[ids[st.top()]] = 0;
            st.pop();
            --hs[ids[i]];
          } else { // ==
            hs[ids[st.top()]] = 0;
            st.pop();
            hs[ids[i]] = 0;
          }
        }
      } else { // R
        st.push(i);
      }
    }

    vi res;
    for (const auto x : hs)
      if (x > 0) res.push_back(x);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi ps{5,4,3,2,1};
    vi hs{2,17,9,15,10};
    const std::string dirs("RRRRR");
    const auto a_out = Solution().survivedRobotsHealths(ps, hs, dirs);
    const vi e_out{2,17,9,15,10};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi ps{3,5,2,6};
    vi hs{10,10,15,12};
    const std::string dirs("RLRL");
    const auto a_out = Solution().survivedRobotsHealths(ps, hs, dirs);
    const vi e_out{14};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi ps{1,2,5,6};
    vi hs{10,10,11,11};
    const std::string dirs("RLRL");
    const auto a_out = Solution().survivedRobotsHealths(ps, hs, dirs);
    const vi e_out;
    assert(a_out == e_out);
  
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
