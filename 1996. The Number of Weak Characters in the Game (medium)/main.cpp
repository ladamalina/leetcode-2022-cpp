#include <algorithm>
#include <cassert>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  static int numberOfWeakCharacters(std::vector<std::vector<int>>& properties) {
    sort(properties.begin(), properties.end(),
         [](const auto& p1, const auto& p2){
      return std::pair(-p1[0], p1[1]) < std::pair(-p2[0], p2[1]);
    });
    int weak_count = 0;
    int max_defence = 0;
    for (const auto& p : properties) {
      if (p[1] < max_defence)
        ++weak_count;
      else
        max_defence = p[1];
    }

    return weak_count;
  }
};

int main() {
    std::vector<std::vector<int>> v1{{5,5},{6,3},{3,6}};
    assert(Solution::numberOfWeakCharacters(v1) == 0);

    std::vector<std::vector<int>> v2{{2,2},{3,3}};
    assert(Solution::numberOfWeakCharacters(v2) == 1);

    std::vector<std::vector<int>> v3{{1,5},{10,4},{4,3}};
    assert(Solution::numberOfWeakCharacters(v3) == 1);
}
