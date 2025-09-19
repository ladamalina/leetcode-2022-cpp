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

// Policy based data structures https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<ii, null_type, std::less<>, rb_tree_tag, tree_order_statistics_node_update> IndexedSet;
//IndexedSet s;
//s.insert(2);
//auto it = s.find_by_order(2);
//auto k = s.order_of_key(7);

class Solution {
public:
  int subarraysWithKDistinct(const vi& nums, const int k) {
    const auto n = SZ(nums);
    
    std::unordered_map<int, vi> x_ids;
    FORD(i, n-1, 0) {
      x_ids[nums[i]].push_back(i);
    }
    
    IndexedSet iset;
    for (const auto& [x, ids] : x_ids) {
      iset.insert({ids.back(), x});
    }
    
    int res = 0;
    FOR(i, 0, n-k) {
      if (SZ(iset) < k)
        break;

      const auto it1 = iset.find_by_order(k-1);
      const auto j1 = it1->F;
      if (SZ(iset) == k) {
        res += n - j1;
      } else {
        const auto it2 = iset.find_by_order(k);
        const auto j2 = it2->F;
        res += j2 - j1;
      }
      
      // update iset
      iset.erase(iset.find({i, nums[i]}));
      auto it = x_ids.find(nums[i]);
      if (SZ(it->S) == 1) {
        x_ids.erase(it);
      } else {
        it->S.pop_back();
        iset.insert({it->S.back(), nums[i]});
      }
    }

    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,1,2,3};
    const auto a_out = Solution().subarraysWithKDistinct(nums, 2);
    assert(a_out == 7);
  
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi nums{1,2,1,3,4};
    const auto a_out = Solution().subarraysWithKDistinct(nums, 3);
    assert(a_out == 3);
  
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
