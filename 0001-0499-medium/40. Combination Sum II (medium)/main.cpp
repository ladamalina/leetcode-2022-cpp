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
#define CZ(_v) static_cast<int>((_v).size())
#define F first
#define S second

void Rec(int i, int s, vvi& res, vi& sub_res, const vii& nums, int target, int n) {
  if (s == target) {
    res.push_back(sub_res);
    return;
  }
  if (i == n || s > target) return;
  // s < target
  
  // take
  FOR(cnt, 1, nums[i].S) {
    sub_res.push_back(nums[i].F);
    Rec(i+1, s + nums[i].F*cnt, res, sub_res, nums, target, n);
  }
  FOR(cnt, 1, nums[i].S) {
    sub_res.pop_back();
  }

  // skip
  Rec(i+1, s, res, sub_res, nums, target, n);
}

class Solution {
public:
  vvi combinationSum2(const vi& candidates, int target) {
    std::map<int, int> freq;
    for (const auto x : candidates) ++freq[x];

    vii nums;
    for (const auto& [x, f] : freq) nums.emplace_back(x, f);
    const auto n = CZ(nums);
    vvi res;
    vi sub_res;
    Rec(0,0,res,sub_res,nums,target,n);

    SORT(res);
    res.erase(std::unique(RNG(res)), res.end());
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi candidates{10,1,2,7,6,1,5};
    const auto a_out = Solution().combinationSum2(candidates, 8);
    const vvi e_out{{1,1,6},{1,2,5},{1,7},{2,6}};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi candidates{2,5,2,1,2};
    const auto a_out = Solution().combinationSum2(candidates, 5);
    const vvi e_out{{1,2,2},{5}};
    assert(a_out == e_out);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vi candidates{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    const auto a_out = Solution().combinationSum2(candidates, 30);
    const vvi e_out{vi(30,1)};
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
