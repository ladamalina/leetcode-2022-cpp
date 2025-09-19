#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vs [[maybe_unused]] = std::vector<std::string>;
using vvs [[maybe_unused]] = std::vector<vs>;
using vc [[maybe_unused]] = std::vector<char>;
using vvc [[maybe_unused]] = std::vector<vc>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define F first
#define S second

std::unordered_map<int, vi> a_ids, b_ids;

class Solution {
 public:
  static int maxChunksToSorted(const vi& a) {
    const auto n = CI(a.size());
    
    a_ids.clear();
    FORD(i, n-1, 0) {
      a_ids[a[i]].push_back(i);
    }
    
    auto b = a;
    SORT(b);
    b_ids.clear();
    FORD(i, n-1, 0) {
      b_ids[b[i]].push_back(i);
    }
    
    int cnt = 0;
    int i = 0;
    while (i < n) {
      auto j = i;
      while (i <= j) {
        auto& a_pos = b_ids[a[i]];
        auto& b_pos = a_ids[b[i]];
        j = std::max(j, std::max(a_pos.back(), b_pos.back()));
        a_pos.pop_back();
        b_pos.pop_back();
        ++i;
      }
      ++cnt;
    }
    
    return cnt;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi a{3,0,1};
    const auto e_out = Solution::maxChunksToSorted(a);
    assert(e_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi a{2,1,3,4,4};
    const auto e_out = Solution::maxChunksToSorted(a);
    assert(e_out == 4);

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
