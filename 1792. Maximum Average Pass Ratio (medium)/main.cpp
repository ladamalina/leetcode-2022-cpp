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

class Solution {
public:
  double maxAverageRatio(const vvi& classes, int extraStudents) {
    const auto n = SZ(classes);
    double avg_sum = 0;
    for (const auto& cl : classes)
      avg_sum += CD(cl[0]) / CD(cl[1]);

    std::priority_queue<std::pair<double,ii>, std::vector<std::pair<double,ii>>, std::less<>> pq;
    for (const auto& cl : classes) {
      const auto avg = CD(cl[0]) / CD(cl[1]);
      const auto next_avg = CD(cl[0]+1) / CD(cl[1]+1);
      pq.emplace(next_avg - avg, ii{cl[0], cl[1]});
    }
    
    while (extraStudents > 0) {
      const auto pass = pq.top().S.F, total = pq.top().S.S;
      pq.pop();
      
      const auto avg = CD(pass) / CD(total);
      const auto upd_avg = CD(pass+1) / CD(total+1);
      avg_sum += upd_avg - avg;
      --extraStudents;

      const auto next_avg = CD(pass+2) / CD(total+2);
      pq.emplace(next_avg - upd_avg, ii{pass+1, total+1});
    }
    const auto res = avg_sum / (n + extraStudents);
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  /*{
    const auto start_t = std::chrono::high_resolution_clock::now();
  
    const auto a_out = Solution().solve();
    assert(a_out == 6);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }*/
  std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
  TestSolution();
#endif
  return 0;
}
