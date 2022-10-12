#include <cassert>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  static int singleNumber(const std::vector<int>& nums) {
    std::unordered_set<int> odds;
    for (const auto n : nums) {
      const auto it = odds.find(n);
      if (it == odds.end()) {
        odds.insert(n);
      } else {
        odds.erase(it);
      }
    }

    return *odds.begin();
  }
};

int main() {
  assert(Solution::singleNumber({2,2,1}) == 1);
  assert(Solution::singleNumber({4,1,2,1,2}) == 4);
  assert(Solution::singleNumber({1}) == 1);
  return 0;
}
