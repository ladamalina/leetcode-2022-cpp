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

class Solution {
 public:
  static int findLeastNumOfUniqueInts(const vi& arr, int k) {
    std::unordered_map<int, int> freq_map;
    for(const auto x : arr) {
      ++freq_map[x];
    }
    vii freqs;
    for (const auto [x, fx] : freq_map) {
      freqs.emplace_back(fx, x);
    }
    std::sort(freqs.rbegin(), freqs.rend());
    while (!freqs.empty() && freqs.back().F <= k) {
      const auto diff = std::min(freqs.back().F, k);
      k -= diff;
      freqs.back().F -= diff;
      if (freqs.back().F == 0)
        freqs.pop_back();
    }
    return freqs.size();
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi arr{5,5,4};
    const auto e_out = Solution::findLeastNumOfUniqueInts(arr, 1);
    assert(e_out == 1);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vi arr{4,3,1,1,3,3,2};
    const auto e_out = Solution::findLeastNumOfUniqueInts(arr, 3);
    assert(e_out == 2);

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
