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

using namespace std;
using namespace std::literals;

class Solution {
public:
  int earliestFinishTime(vector<int>& lbs, vector<int>& lds, vector<int>& wbs, vector<int>& wds) {
    const int ln = lbs.size(), wn = wbs.size();

    auto min_lb = lbs[0], min_ld = lds[0], min_le = min_lb + min_ld;
    for (auto li = 1; li < ln; ++li) {
      const auto lb = lbs[li], ld = lds[li], le = lb + ld;
      if (tie(le, ld) < tie(min_le, min_ld)) {
        min_lb = lb, min_ld = ld, min_le = le;
      }
    }

    auto min_wb = wbs[0], min_wd = wds[0], min_we = min_wb + min_wd;
    for (auto wi = 1; wi < wn; ++wi) {
      const auto wb = wbs[wi], wd = wds[wi], we = wb + wd;
      if (tie(we, wd) < tie(min_we, min_wd)) {
        min_wb = wb, min_wd = wd, min_we = we;
      }
    }

    auto res = INT_MAX;
    for (auto li = 0; li < ln; ++li) {
      const auto lb = lbs[li], ld = lds[li], le = lb + ld;
      res = min(res, max(le, min_wb) + min_wd);
      res = min(res, max(min_we, lb) + ld);
    }
    for (auto wi = 0; wi < wn; ++wi) {
      const auto wb = wbs[wi], wd = wds[wi], we = wb + wd;
      res = min(res, max(min_le, wb) + wd);
      res = min(res, max(we, min_lb) + min_ld);
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<int> landStartTime{2,8};
    vector<int> landDuration{4,1};
    vector<int> waterStartTime{6};
    vector<int> waterDuration{3};
    const auto a_out = Solution().earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration);
    assert(a_out == 9);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<int> landStartTime{5};
    vector<int> landDuration{3};
    vector<int> waterStartTime{1};
    vector<int> waterDuration{10};
    const auto a_out = Solution().earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration);
    assert(a_out == 14);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<int> landStartTime{8,48};
    vector<int> landDuration{28,63};
    vector<int> waterStartTime{61,87,24,75,64};
    vector<int> waterDuration{31,58,71,67,13};
    const auto a_out = Solution().earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration);
    assert(a_out == 77);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vector<int> landStartTime{100000};
    vector<int> landDuration{100000};
    vector<int> waterStartTime{100000};
    vector<int> waterDuration{100000};
    const auto a_out = Solution().earliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration);
    assert(a_out == 300000);
  
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
