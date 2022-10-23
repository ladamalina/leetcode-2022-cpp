#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using Point = std::vector<int>;
using Points = std::vector<std::vector<int>>;

class Solution {
 public:
  static Points kClosest(const Points& points, int k) {
    std::multimap<uint64_t, Point> k_closest;
    for (const auto& p : points) {
      k_closest.insert({p[0]*p[0] + p[1]*p[1], p});
      if (k_closest.size() > static_cast<uint64_t>(k)) {
        k_closest.erase(std::prev(k_closest.end()));
      }
    }
    Points result;
    result.reserve(k_closest.size());
    for (const auto& [_, p] : k_closest) {
      result.push_back(p);
    }

    return result;
  }
};

int main() {
  {
    Points points{{1,3},{-2,2}};
    const int k = 1;
    Points expected{{-2,2}};

    Points actual = Solution::kClosest(points, k);
    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    assert(expected == actual);
  }
  {
    Points points{{3,3},{5,-1},{-2,4}};
    const int k = 2;
    Points expected{{3,3},{-2,4}};

    Points actual = Solution::kClosest(points, k);
    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());
    assert(expected == actual);
  }

  return 0;
}
