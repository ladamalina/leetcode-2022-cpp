//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ll = long long;

class Solution {
  public:
  struct Event {
    int p, t, id;
    Event() = default;
    Event (int p_, int t_, int id_) : p(p_), t(t_), id(id_) {}
    bool operator<(const Event& other) const { return std::tie(p, t, id) < std::tie(other.p, other.t, other.id); }
  };
  
  static bool isRectangleCover(const std::vector<std::vector<int>>& rectangles) {
    const auto n = static_cast<int>(rectangles.size());

    int min_x = INT_MAX;
    int max_x = INT_MIN;
    int min_y = INT_MAX;
    int max_y = INT_MIN;
    ll sq = 0;
    for (const auto& rec : rectangles) {
      min_x = std::min(min_x, rec[0]);
      min_y = std::min(min_y, rec[1]);
      max_x = std::max(max_x, rec[2]);
      max_y = std::max(max_y, rec[3]);
      sq += static_cast<ll>(rec[2]-rec[0]) * static_cast<ll>(rec[3]-rec[1]);
    }
    const auto target_sq = static_cast<ll>(max_x-min_x) * static_cast<ll>(max_y-min_y);
    if (sq != target_sq)
      return false;

    bool possibly = true;
    std::vector<Event> events(n*2);
    for (int i = 0; i < n; ++i) {
      events[i*2] = {rectangles[i][0], 1, i};
      events[i*2+1] = {rectangles[i][2], -1, i};
    }
    std::sort(events.begin(), events.end());

    std::set<int> o_begins;
    std::set<int> o_ends;
    for (const auto& e : events) {
      const auto& rec = rectangles[e.id];
      if (e.t == 1) { // open new
        const auto beg_it = o_begins.lower_bound(rec[1]);
        if (beg_it != o_begins.end() && *beg_it < rec[3]) {
          possibly = false;
          break;
        }
        const auto end_it = o_ends.upper_bound(rec[1]);
        if (end_it != o_ends.end() && *end_it <= rec[3]) {
          possibly = false;
          break;
        }
        o_begins.emplace(rec[1]);
        o_ends.emplace(rec[3]);
      } else { // close old
        o_begins.erase(rec[1]);
        o_ends.erase(rec[3]);
      }
    }
    return possibly;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> rectangles{{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}};
    const auto e_out = Solution::isRectangleCover(rectangles);
    assert(e_out);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> rectangles{{1,1,2,3},{1,3,2,4},{3,1,4,2},{3,2,4,4}};
    const auto e_out = Solution::isRectangleCover(rectangles);
    assert(!e_out);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const std::vector<std::vector<int>> rectangles{{1,1,3,3},{3,1,4,2},{1,3,2,4},{2,2,4,4}};
    const auto e_out = Solution::isRectangleCover(rectangles);
    assert(!e_out);
    
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
