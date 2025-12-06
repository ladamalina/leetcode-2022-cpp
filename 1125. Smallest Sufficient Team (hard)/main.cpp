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
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;

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

constexpr int MAX_R = 16;
constexpr int MAX_P = 60;

std::array<std::array<int, (1<<MAX_R)>, MAX_P> dp, dp_take;

class Solution {
public:
  vi smallestSufficientTeam(const vs& req_in, const vvs& people_in) {
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), -1);
    
    const auto rn = SZ(req_in), pn = SZ(people_in);

    std::unordered_map<std::string_view, int> str_int;
    for (const auto& r : req_in) {
      if (!str_int.contains(r)) {
        str_int[r] = SZ(str_int);
      }
    }

    vi people(pn);
    FOR(i, 0, pn-1) {
      for (const auto& s : people_in[i]) {
        people[i] |= (1 << str_int.at(s));
      }
    }

    const std::function<int(int,int)> rec = [&](int pi, int rmask) {
      if (__builtin_popcount(rmask) == rn)
        return 0;
      // __builtin_popcount(rmask) < rn

      if (pi == pn)
        return pn;
      // pi < pn

      if (dp[pi][rmask] != -1)
        return dp[pi][rmask];

      // take
      const auto take_res = 1 + rec(pi + 1, (rmask | people[pi]));
      // skip
      const auto skip_res = rec(pi + 1, rmask);
      
      dp[pi][rmask] = std::min(take_res, skip_res);
      dp_take[pi][rmask] = (take_res <= skip_res);

      return dp[pi][rmask];
    };
    [[maybe_unused]] const auto n_res = rec(0, 0);

    vi res;
    int pi = 0, rmask = 0;
    while (pi < pn && __builtin_popcount(rmask) < rn) {
      if (dp_take[pi][rmask]) {
        res.push_back(pi);
        rmask |= people[pi];
      }
      ++pi;
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs req_in{"gvp","jgpzzicdvgxlfix","kqcrfwerywbwi","jzukdzrfgvdbrunw","k"};
    const vvs people_in{{},{},{},{},{"jgpzzicdvgxlfix"},{"jgpzzicdvgxlfix","k"},{"jgpzzicdvgxlfix","kqcrfwerywbwi"},{"gvp"},{"jzukdzrfgvdbrunw"},{"gvp","kqcrfwerywbwi"}};
    const auto a_out = Solution().smallestSufficientTeam(req_in, people_in);
    const vi e_out{5,8,9};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs req_in{"java","nodejs","reactjs"};
    const vvs people_in{{"java"},{"nodejs"},{"nodejs","reactjs"}};
    const auto a_out = Solution().smallestSufficientTeam(req_in, people_in);
    const vi e_out{0,2};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vs req_in{"algorithms","math","java","reactjs","csharp","aws"};
    const vvs people_in{{"algorithms","math","java"},{"algorithms","math","reactjs"},{"java","csharp","aws"},{"reactjs","csharp"},{"csharp","math"},{"aws","java"}};
    const auto a_out = Solution().smallestSufficientTeam(req_in, people_in);
    const vi e_out{1,2};
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
