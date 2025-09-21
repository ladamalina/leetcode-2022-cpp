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
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vvl [[maybe_unused]] = std::vector<vl>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vc [[maybe_unused]] = std::vector<char>;

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

class Solution {
 public:
  int maxTaskAssign(vi& tasks, vi& workers, int pills, int strength) {
    const auto tn = SZ(tasks), wn = SZ(workers);
    SORT(tasks);
    SORT(workers);

    const auto bin_check = [&](const int todo) {
      int ti = 0, wi = wn-todo, has_pills = pills;

//      FOR(i, 0, todo-1) std::cerr << tasks[ti+i] << ' ';
//      std::cerr << '\n';
//      FOR(i, 0, todo-1) std::cerr << workers[wi+i] << ' ';
//      std::cerr << '\n';

      std::priority_queue<int, vi, std::less<>> ts;
      std::multiset<int> ws;
      FOR(i, 0, todo-1) {
        ts.push(tasks[ti+i]);
        ws.insert(workers[wi+i]);
      }

      while (!ts.empty()) {
        const auto t = ts.top();
        ts.pop();
//        std::cerr << "t=" << t << ' ';
        if (t <= *ws.rbegin()) {
//          std::cerr << "w=" << *ws.rbegin() << '\n';
          ws.erase(std::prev(ws.end()));
        } else if (has_pills) {
          const auto w_it = ws.lower_bound(t - strength);
          if (w_it != ws.end()) {
//            std::cerr << "w=" << *w_it << "+" << strength << '\n';
            ws.erase(w_it);
            --has_pills;
          } else {
//            std::cerr << "no workers" << '\n';
            return false;
          }
        } else { // no pills
//          std::cerr << "no pills" << '\n';
          return false;
        }
      }
//      std::cerr << "bin_check = ok" << '\n';
      return true;
    };

    int lo = 0, hi = std::min(tn, wn);
    while (lo < hi) {
      const auto mid = (lo + hi + 1) / 2;
      const auto check = bin_check(mid);
//      std::cerr << "lo=" << lo << "\tmid=" << mid << "\thi=" << hi << "\tcheck=" << check << '\n';
      if (check) lo = mid;
      else hi = mid - 1;
    }
    return hi;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tasks{5,9,8,5,9};
    vi workers{1,6,4,2,6};
    const auto a_out = Solution().maxTaskAssign(tasks, workers, 1, 5);
    assert(a_out == 3);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tasks{3,2,1};
    vi workers{0,3,3};
    const auto a_out = Solution().maxTaskAssign(tasks, workers, 1, 1);
    assert(a_out == 3);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tasks{5,4};
    vi workers{0,0,0};
    const auto a_out = Solution().maxTaskAssign(tasks, workers, 1, 5);
    assert(a_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi tasks{10,15,30};
    vi workers{0,10,10,10,10};
    const auto a_out = Solution().maxTaskAssign(tasks, workers, 3, 10);
    assert(a_out == 2);

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
