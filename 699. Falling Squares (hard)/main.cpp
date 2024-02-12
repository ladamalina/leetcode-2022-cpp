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

std::set<int> orig_set;
std::unordered_map<int, int> comp;
std::set<ii> curr_open;

class Solution {
 public:
  static vi fallingSquares(const vvi& positions) {
    const auto n = CI(positions.size());

    // compress coordinates
    orig_set.clear();
    for (const auto& pos : positions) {
      orig_set.insert(pos[0]);
      orig_set.insert(pos[0]+pos[1]);
    }
    comp.clear();
    for (const auto x : orig_set) {
      if (!comp.contains(x))
        comp[x] = comp.size();
    }
    const auto max_comp = comp.size() - 1;

    vi res(n);
    vvii open(max_comp+1);
    vvii close(max_comp+1);
    for (int i=0; i<n; ++i) {
      const auto& pos = positions[i];
      const auto comp_l = comp[pos[0]];
      const auto comp_r = comp[pos[0]+pos[1]];
      
      curr_open.clear();
      for (int j=0; j<comp_r; ++j) {
        for (const auto& [h, id] : open[j]) {
          curr_open.emplace(h, id);
        }
        if (j <= comp_l) {
          for (const auto& [h, id] : close[j]) {
            curr_open.erase({h, id});
          }
        }
      }
      const auto max_orig = curr_open.empty() ? 0 : curr_open.rbegin()->first;
      const auto curr_orig = max_orig + pos[1];
      res[i] = (i==0) ? curr_orig : std::max(res[i-1], curr_orig);

      open[comp_l].emplace_back(curr_orig, i);
      close[comp_r].emplace_back(curr_orig, i);
    }
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi positions{{1,2},{2,3},{6,1}};
    const auto a_out = Solution::fallingSquares(positions);
    const vi e_out{2,5,5};
    assert(a_out == e_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi positions{{100,100},{200,100}};
    const auto a_out = Solution::fallingSquares(positions);
    const vi e_out{100,100};
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
