#include <bits/stdc++.h>

using namespace std::literals;

using ll [[maybe_unused]] = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vii [[maybe_unused]] = std::vector<ii>;
using vi [[maybe_unused]] = std::vector<int>;
using vl [[maybe_unused]] = std::vector<ll>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vvii [[maybe_unused]] = std::vector<vii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vvb [[maybe_unused]] = std::vector<vb>;
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

constexpr int MAX_N = 500;
std::array<std::unordered_set<int>, MAX_N> route_stops;
int dist[MAX_N][MAX_N];

class Solution {
 public:
  static int numBusesToDestination(const vvi& routes, int src, int dst) {
    if (src == dst)
      return 0;

    const auto n = CI(routes.size());
    std::fill(route_stops.begin(), route_stops.begin()+n, std::unordered_set<int>{});
    vi src_routes, dst_routes;
    FOR(r, 0, n-1) {
      auto& stops = route_stops[r];
      for (const auto s : routes[r]) {
        stops.insert(s);
        if (s == src) src_routes.push_back(r);
        if (s == dst) dst_routes.push_back(r);
      }
    }

    std::fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), INT_MAX);
    FOR(r1, 0, n-1) {
      dist[r1][r1] = 0;
      const auto& stops1 = route_stops[r1];
      FOR(r2, r1+1, n-1) {
        const auto& stops2 = route_stops[r2];
        const auto has_common = (stops1.size() < stops2.size())
            ? std::any_of(RNG(stops1), [&](const int s) { return stops2.contains(s); })
            : std::any_of(RNG(stops2), [&](const int s) { return stops1.contains(s); });
        if (has_common) {
          dist[r1][r2] = 1;
          dist[r2][r1] = 1;
        }
      }
    }
    for (int k=0; k<n; ++k)
      for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
          if (dist[i][k] < INT_MAX && dist[k][j] < INT_MAX)
            dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);

    int min_dist = INT_MAX;
    for (const auto& r1 : src_routes)
      for (const auto& r2 : dst_routes)
        min_dist = std::min(min_dist, dist[r1][r2]);
    
    return (min_dist == INT_MAX) ? -1 : min_dist+1;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi routes{{1,2,7},{3,6,7}};
    const auto a_out = Solution::numBusesToDestination(routes, 1, 6);
    assert(a_out == 2);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi routes{{7,12},{4,5,15},{6},{15,19},{9,12,13}};
    const auto a_out = Solution::numBusesToDestination(routes, 15, 12);
    assert(a_out == -1);

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
