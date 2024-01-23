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
#define SZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

class Solution {
public:
  vi sortJumbled(const vi& mapping, const vi& nums) {
    const auto n = SZ(nums);
    
    std::vector<std::pair<std::string,int>> str_ids(n);
    FOR(i, 0, n-1) {
      auto& str = str_ids[i].F;
      str_ids[i].S = i;

      auto x = nums[i];
      while (x > 0) {
        const auto d = x%10;
        str.push_back(char('0'+mapping[d]));
        x /= 10;
      }
      while (!str.empty() && str.back()=='0'+mapping[0])
        str.pop_back();
      if (str.empty() && x == 0) {
        str.push_back('0'+mapping[0]);
      }
      while (str.size() < 10)
        str.push_back('0');
      std::reverse(str.begin(), str.end());
    }
    std::sort(str_ids.begin(), str_ids.end());

    vi res(nums.size());
    FOR(i, 0, n-1) res[i] = nums[str_ids[i].S];
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi mapping{8,9,4,0,2,1,3,5,7,6};
    const vi nums{991,338,38};
    const auto a_out = Solution().sortJumbled(mapping, nums);
    const vi e_res{338,38,991};
    assert(a_out == e_res);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi mapping{0,1,2,3,4,5,6,7,8,9};
    const vi nums{789,456,123};
    const auto a_out = Solution().sortJumbled(mapping, nums);
    const vi e_res{123,456,789};
    assert(a_out == e_res);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi mapping{9,8,7,6,5,4,3,2,1,0};
    const vi nums{0,1,2,3,4,5,6,7,8,9};
    const auto a_out = Solution().sortJumbled(mapping, nums);
    const vi e_res{9,8,7,6,5,4,3,2,1,0};
    assert(a_out == e_res);
  
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
