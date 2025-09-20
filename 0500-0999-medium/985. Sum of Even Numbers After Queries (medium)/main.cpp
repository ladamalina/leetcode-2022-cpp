#include <cassert>
#include <iostream>
#include <vector>

class Solution {
 public:
  static std::vector<int> sumEvenAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
    int initial_sum = 0;
    std::for_each(nums.begin(), nums.end(),
                  [&initial_sum](int x){ if (x % 2 == 0) initial_sum += x; });
    std::vector<int> result;
    result.reserve(queries.size());
    for (const auto& upd : queries) {
      if (isSumEven(nums[upd[1]], upd[0])) {
        if (nums[upd[1]] % 2 == 0) {
          result.push_back(initial_sum + upd[0]);
        } else {
          result.push_back(initial_sum + nums[upd[1]] + upd[0]);
        }
      } else {
        if (nums[upd[1]] % 2 == 0) {
          result.push_back(initial_sum - nums[upd[1]]);
        } else {
          result.push_back(initial_sum);
        }
      }
      nums[upd[1]] += upd[0];
      initial_sum = result.back();
    }

    return result;
  }

  static bool isSumEven(int x, int y) {
    return (x + y) % 2 == 0;
  }
};

int main() {
  {
    std::vector<int> nums{1,2,3,4};
    std::vector<std::vector<int>> queries{{1,0},{-3,1},{-4,0},{2,3}};
    std::vector<int> expexted{8,6,2,4};
    std::vector<int> actual = Solution::sumEvenAfterQueries(nums, queries);
    assert(expexted == actual);
  }
  {
    std::vector<int> nums{1};
    std::vector<std::vector<int>> queries{{4,0}};
    std::vector<int> expexted{0};
    std::vector<int> actual = Solution::sumEvenAfterQueries(nums, queries);
    assert(expexted == actual);
  }
}
