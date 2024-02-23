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

constexpr int MAX_N = 1e5;
std::array<int, MAX_N> dist;
std::array<vii, MAX_N> g;

struct QItem {
  int v = 0;
  int t = 0;
  int p = 0;
  bool operator<(const QItem& other) const {
    return std::tie(t, v, p) < std::tie(other.t, other.v, other.p);
  }
  bool operator>(const QItem& other) const {
    return std::tie(t, v, p) > std::tie(other.t, other.v, other.p);
  }
};

class Solution {
 public:
  static vi findAllPeople(int n, const vvi& meetings, int src) {
    std::fill(dist.begin()+1, dist.begin()+n, INT_MAX);
    std::fill(g.begin(), g.begin()+n, vii{});
    g[0].emplace_back(src, 0);
    for (const auto& meet : meetings) {
      g[meet[0]].emplace_back(meet[1], meet[2]);
      g[meet[1]].emplace_back(meet[0], meet[2]);
    }
    
    std::priority_queue<QItem, std::vector<QItem>, std::greater<>> pq;
    for (const auto& [u, t] : g[0]) {
      if (t < dist[u])
        pq.push({u, t, 0});
    }
    
    while (!pq.empty()) {
      const auto top = pq.top();
      pq.pop();
      if (top.t >= dist[top.v])
        continue;
      dist[top.v] = top.t;
      
      for (const auto& [u, t] : g[top.v]) {
        if (u != top.p && t >= top.t && t < dist[u]) {
          pq.push({u, t, top.v});
        }
      }
    }
    
    vi res;
    FOR(v, 0, n-1) {
      if (dist[v] < INT_MAX)
        res.emplace_back(v);
    }
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi meetings{{1,2,5},{2,3,8},{1,5,10}};
    auto a_out = Solution::findAllPeople(6, meetings, 1);
    SORT(a_out);
    const vi e_out{0,1,2,3,5};
    assert(e_out == a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi meetings{{3,1,3},{1,2,2},{0,3,3}};
    auto a_out = Solution::findAllPeople(4, meetings, 3);
    SORT(a_out);
    const vi e_out{0,1,3};
    assert(e_out == a_out);

    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    vvi meetings{{3,4,2},{1,2,1},{2,3,1}};
    auto a_out = Solution::findAllPeople(5, meetings, 1);
    SORT(a_out);
    const vi e_out{0,1,2,3,4};
    assert(e_out == a_out);

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
