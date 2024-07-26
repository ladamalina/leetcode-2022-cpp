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
using vvs [[maybe_unused]] = std::vector<vs>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second

const auto JFK = "JFK"s;

class Solution {
public:
  vs findItinerary(const vvs& tickets) {
    const auto n = CI(tickets.size());

    std::unordered_map<std::string, std::map<std::string, int>> g;
    for (const auto& t : tickets) {
      ++g[t[0]][t[1]];
    }

    vs path{JFK};
    const std::function<bool(const std::string&,int)> dfs = [&](const std::string& src, int len) {
      if (len == n) return true;
      if (g.contains(src)) {
        for (auto& [dst, cnt] : g.at(src)) {
          if (cnt) {
            --cnt;
            path.push_back(dst);
            const auto sub_res = dfs(dst, len+1);
            if (sub_res) return true;
            ++cnt;
            path.pop_back();
          }
        }
      }
      return false;
    };
    dfs(JFK, 0);

    return path;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvs tickets{{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
    const vs e_out{"JFK","MUC","LHR","SFO","SJC"};
    const auto a_out = Solution().findItinerary(tickets);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvs tickets{{"JFK","SFO"},{"JFK","ATL"},{"SFO","ATL"},{"ATL","JFK"},{"ATL","SFO"}};
    const vs e_out{"JFK","ATL","JFK","SFO","ATL","SFO"};
    const auto a_out = Solution().findItinerary(tickets);
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvs tickets{{"JFK","SFO"},{"JFK","ATL"},{"SFO","JFK"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"},{"ATL","AAA"},{"AAA","BBB"},{"BBB","ATL"}};
    // const vs e_out{};
    const auto a_out = Solution().findItinerary(tickets);
    // assert(a_out == e_out);
    assert(!a_out.empty());
  
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
