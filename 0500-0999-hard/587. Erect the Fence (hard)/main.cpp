// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>

using namespace std::literals;

using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

ii operator+(const ii& a, const ii& b) { return {a.first+b.first, a.second+b.second}; }
ii operator-(const ii& a, const ii& b) { return {a.first-b.first, a.second-b.second}; }
int operator*(const ii& a, const ii& b) { return a.first*b.first + b.second*a.second; } // Скалярное произведение
int operator^(const ii& a, const ii& b) { return a.first*b.second - b.first*a.second; } // Векторное произведение

double DistAB(const ii& a, const ii& b) {
  return std::sqrt(((a.first-b.first)*(a.first-b.first)) + ((a.second-b.second)*(a.second-b.second)));
}

double AngleABC(const ii& a, const ii& b, const ii& c) {
  // https://math.stackexchange.com/questions/361412/finding-the-angle-between-three-points
  const auto ba = a - b;
  const auto bc = c - b;
  const auto dot_prod = ba * bc;
  const auto dist_ba = DistAB({0,0}, ba);
  const auto dist_bc = DistAB({0,0}, bc);
  const auto x = dot_prod / (dist_ba * dist_bc);
  const auto round_x = std::round(x / 1e-6) * 1e-6;
  return std::acos(round_x);
}

const auto EPS = 1e-6;
template <typename T>
[[maybe_unused]] bool Eq(T a, T b) { return std::abs(a - b) < EPS; }
template <typename T>
[[maybe_unused]] bool Lt(T a, T b) { return b - a >= EPS; }
template <typename T>
[[maybe_unused]] bool Lte(T a, T b) { return Eq(a, b) || Lt(a, b); }
template <typename T>
[[maybe_unused]] bool Gt(T a, T b) { return a - b >= EPS; }
template <typename T>
[[maybe_unused]] bool Gte(T a, T b) { return Eq(a, b) || Lt(b, a); }

struct [[maybe_unused]] HashPair {
  size_t operator()(const ii& x) const {
    return (x.first) * 37 + (x.second) * 37 * 37;
  }
};

class Solution {
  public:
  static vvi outerTrees(const vvi& trees) {
    const auto n = static_cast<int>(trees.size());
    if (n == 1)
      return trees;

    const auto t0_it = std::min_element(trees.begin(), trees.end(),
      [](const auto& l, const auto& r) { return std::tie(l[1],l[0]) < std::tie(r[1],r[0]); });
    const auto& t0 = *t0_it;
    const ii p0{t0[0], t0[1]};

    std::unordered_set<ii, HashPair> convex_hull{p0};
    auto curr_p = p0;
    ii prev_p{p0.first-1, p0.second};
    while (true) {
      double max_angle = -1e9;
      double min_dist = 1e9;
      ii next_p;
      for (const auto& t : trees) {
        const ii p{t[0], t[1]};
        if (p != curr_p) {
          const auto angle = AngleABC(prev_p, curr_p, p);
          const auto dist = DistAB(curr_p, p);
          if (Gt(angle, max_angle) || (Eq(angle, max_angle) && Lt(dist, min_dist))) {
            max_angle = angle;
            min_dist = dist;
            next_p = p;
          }
        }
      }
      if (next_p == p0) break;
      prev_p = curr_p;
      curr_p = next_p;
      convex_hull.insert(next_p);
    }

    vvi res;
    res.reserve(convex_hull.size());
    for (const auto& p : convex_hull)
      res.emplace_back(vi{p.first, p.second});
    
    return res;
  }
};

[[maybe_unused]] void TestSolution() {
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi trees{{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
    auto a_out = Solution::outerTrees(trees);
    std::sort(a_out.begin(), a_out.end());
    vvi e_out{{1,1},{2,0},{4,2},{3,3},{2,4}};
    std::sort(e_out.begin(), e_out.end());
    assert(a_out == e_out);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi trees{{1,2},{2,2},{4,2}};
    auto a_out = Solution::outerTrees(trees);
    std::sort(a_out.begin(), a_out.end());
    vvi e_out{{1,2},{2,2},{4,2}};
    std::sort(e_out.begin(), e_out.end());
    assert(a_out == e_out);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi trees{{3,3},{2,4},{2,2},{7,4},{3,4}};
    auto a_out = Solution::outerTrees(trees);
    std::sort(a_out.begin(), a_out.end());
    vvi e_out{{2,2},{2,4},{3,4},{7,4}};
    std::sort(e_out.begin(), e_out.end());
    assert(a_out == e_out);
    
    const auto end_t = std::chrono::high_resolution_clock::now();
    const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
    std::cerr << total_t << " ms"sv << std::endl;
  }
  {
    const auto start_t = std::chrono::high_resolution_clock::now();

    const vvi trees{{10,11},{10,19},{10,21},{10,26},{10,30},{10,33},{10,35},{10,41},{10,45},{11,15},{11,22},{11,23},{11,32},{11,36},{11,47},{11,49},{12,20},{12,24},{12,26},{12,31},{12,35},{12,41},{12,42},{12,47},{12,48},{13,17},{13,22},{13,25},{13,27},{14,11},{14,19},{14,30},{14,47},{15,26},{15,27},{16,11},{16,19},{16,20},{16,46},{17,31},{17,34},{17,42},{18,37},{18,46},{18,48},{19,17},{19,18},{19,26},{19,47},{20,26},{20,30},{20,47},{21,42},{21,48},{22,11},{22,35},{23,28},{23,44},{24,26},{24,29},{24,35},{25,13},{25,24},{25,39},{26,22},{26,23},{26,26},{26,31},{26,36},{26,42},{27,15},{27,24},{27,26},{27,28},{27,39},{28,21},{28,24},{29,47},{29,49},{30,17},{30,22},{30,31},{30,32},{30,39},{30,40},{30,45},{31,31},{31,36},{31,43},{31,44},{32,40},{33,23},{33,37},{33,38},{33,49},{34,15},{34,23},{34,24},{34,26},{34,29},{34,37},{35,28},{35,38},{35,41},{35,42},{35,44},{36,22},{36,43},{36,44},{36,46},{37,20},{37,21},{37,28},{37,38},{37,39},{37,43},{38,10},{38,15},{38,36},{39,31},{39,33},{39,44},{40,26},{40,46},{41,11},{41,16},{41,43},{41,45},{41,46},{41,48},{42,16},{42,28},{42,29},{42,35},{42,42},{42,46},{42,49},{43,21},{43,30},{43,33},{43,39},{44,10},{44,39},{44,41},{45,12},{45,29},{45,42},{45,44},{46,18},{46,32},{46,36},{47,17},{47,35},{47,47},{48,21},{48,32},{48,33},{48,38},{48,45},{48,47},{49,17},{49,25},{49,33},{49,35},{50,12},{50,31},{50,45},{51,15},{51,26},{51,40},{51,45},{51,47},{52,15},{52,24},{52,25},{52,31},{52,44},{53,12},{53,17},{54,10},{54,11},{54,29},{54,37},{54,46},{55,11},{55,16},{55,19},{55,26},{55,43},{56,13},{56,29},{56,33},{56,34},{56,36},{56,44},{56,48},{57,21},{57,44},{57,45},{58,23},{58,33},{58,34},{59,32},{59,42},{59,46},{60,12},{60,14},{60,20},{61,35},{61,39},{62,23},{62,24},{62,26},{62,39},{62,45},{63,17},{63,18},{64,10},{64,12},{64,14},{64,25},{64,28},{64,31},{64,44},{65,28},{65,45},{65,49},{66,10},{66,16},{66,45},{66,46},{66,47},{67,23},{67,44},{67,48},{69,12},{69,19},{69,22},{69,38},{69,40},{69,44},{70,29},{70,38},{70,43},{71,14},{71,16},{71,18},{71,31},{71,41},{71,47},{71,48},{72,16},{72,23},{72,31},{72,40},{73,11},{73,25},{73,36},{73,40},{73,47},{74,12},{74,21},{74,25},{74,27},{74,39},{74,49},{75,16},{75,22},{75,29},{75,44},{75,46},{76,17},{76,19},{76,39},{76,45},{77,12},{77,13},{77,16},{77,23},{77,25},{77,34},{77,40},{78,11},{78,25},{78,33},{78,39},{78,46},{78,47},{79,16},{79,28},{79,38},{79,41},{79,43},{80,38},{80,42},{80,44},{81,34},{82,25},{82,29},{82,31},{82,34},{82,35},{82,36},{82,42},{82,43},{83,16},{83,20},{83,35},{83,39},{83,44},{84,21},{84,44},{84,45},{84,48},{85,22},{85,26},{85,38},{85,44},{86,11},{86,17},{86,26},{86,31},{86,33},{86,34},{86,48},{87,15},{87,18},{87,32},{87,44},{88,22},{88,27},{88,33},{89,20},{89,22},{89,24},{89,43},{90,32},{90,39},{91,11},{91,20},{91,37},{91,42},{92,12},{92,33},{92,35},{92,37},{92,41},{92,46},{93,26},{93,29},{93,37},{94,10},{94,15},{94,17},{94,31},{94,33},{94,46},{95,22},{95,40},{95,43},{96,26},{96,33},{97,13},{97,18},{97,19},{97,29},{98,19},{98,24},{98,41},{98,48},{99,25},{99,34},{99,46}};
    auto a_out = Solution::outerTrees(trees);
    std::sort(a_out.begin(), a_out.end());
    vvi e_out{{10,26},{74,49},{11,49},{99,25},{10,33},{29,49},{97,13},{38,10},{99,46},{98,48},{10,21},{42,49},{10,35},{10,41},{66,10},{10,19},{94,10},{98,19},{10,11},{10,30},{64,10},{65,49},{10,45},{54,10},{33,49},{99,34},{44,10}};
    std::sort(e_out.begin(), e_out.end());
    
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
