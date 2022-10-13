#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

class Solution {
 public:
  static std::vector<std::vector<int>> threeSum(const std::vector<int>& nums) {
    std::map<int, uint16_t> count_nums;
    for (const auto n : nums) {
      ++count_nums[n];
    }
    std::vector<std::vector<int>> three_sums;
    three_sums.reserve(count_nums.size());

    auto num1_it = count_nums.begin();
    while (num1_it != count_nums.end()) {
      for (auto num2_it = count_nums.begin(); num2_it != count_nums.end(); ++num2_it) {
        if (num2_it == num1_it && num2_it->second < 2) {
          continue;
        }

        const int target_num3 = -(num1_it->first + num2_it->first);
        const auto num3_it = count_nums.find(target_num3);
        if (num3_it == count_nums.end()) {
          continue;
        }
        if ((num3_it == num2_it || num3_it == num1_it) && num3_it->second < 2) {
          continue;
        }
        if (num3_it == num2_it && num3_it == num1_it && num3_it->second < 3) {
          continue;
        }
        std::vector<int> three_sum{num1_it->first, num2_it->first, num3_it->first};
        std::sort(three_sum.begin(), three_sum.end());
        three_sums.push_back(three_sum);
      }
      count_nums.erase(num1_it);
      num1_it = count_nums.begin();
    }
    std::sort(three_sums.begin(), three_sums.end());
    auto last_it = std::unique(three_sums.begin(), three_sums.end());
    three_sums.erase(last_it, three_sums.end());

    return three_sums;
  }
};

void checkSolution(const std::vector<int>& nums, std::vector<std::vector<int>>& expected) {
  auto actual = Solution::threeSum(nums);
  std::sort(expected.begin(), expected.end());
  std::sort(actual.begin(), actual.end());
  assert(expected == actual);
}

int main() {
  {
    const std::vector<int> nums{-1,0,1,2,-1,-4};
    std::vector<std::vector<int>> expected{{-1,-1,2}, {-1,0,1}};
    checkSolution(nums, expected);
  }
  {
    const std::vector<int> nums{0,1,1};
    std::vector<std::vector<int>> expected{};
    checkSolution(nums, expected);
  }
  {
    const std::vector<int> nums{0,0,0};
    std::vector<std::vector<int>> expected{{0,0,0}};
    checkSolution(nums, expected);
  }
}
