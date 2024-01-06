//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using pll [[maybe_unused]] = std::pair<ll, ll>;
using pdd [[maybe_unused]] = std::pair<double, double>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvvi [[maybe_unused]] = std::vector<vvi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<ld>(_v)
#define F first
#define S second
#define PB push_back

struct Event {
  int x, type, h;
  bool operator<(const Event& other) const {
    return std::tie(x, type, h) < std::tie(other.x, other.type, other.h);
  }
};

class Solution {
  public:
  static vvi getSkyline(const vvi& buildings) {
    const auto n = CI(buildings.size());
    
    std::vector<Event> events(n*2);
    FOR(i, 0, n-1) {
      events[i*2] = Event{buildings[i][0], 1, buildings[i][2]};
      events[i*2+1] = Event{buildings[i][1], -1, buildings[i][2]};
    }
    SORT(events);

    std::map<int, int> skyline;
    std::multiset<int> hs;
    FOR(i, 0, n*2-1) {
      const auto& e = events[i];
      if (e.type == -1) {
        hs.erase(hs.find(e.h));
      } else {
        hs.insert(e.h);
      }
      if (hs.empty()) skyline[e.x] = 0;
      else skyline[e.x] = *hs.rbegin();
    }

    vvi b;
    for (const auto& [x, h] : skyline) {
      if (!b.empty() && b.back()[1] == h) continue;
      b.emplace_back(vi{x, h});
    }
    
    return b;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi buildings{{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    const vvi e_out{{2,10},{3,15},{7,12},{12,0},{15,10},{20,8},{24,0}};
    const auto a_out = Solution::getSkyline(buildings);
    assert(a_out == e_out);
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();
    const vvi buildings{{0,2,3},{2,5,3}};
    const vvi e_out{{0,3},{5,0}};
    const auto a_out = Solution::getSkyline(buildings);
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
