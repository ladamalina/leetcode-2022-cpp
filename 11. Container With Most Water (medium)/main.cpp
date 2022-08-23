#include <cassert>
#include <iterator>
#include <vector>

class Solution {
public:
  static int maxArea(std::vector<int>& height) {
    auto leftIt = height.begin();
    auto rightIt = height.end() - 1;
    int max_amount = 0;

    while (leftIt < rightIt) {
      int current_amount = (rightIt - leftIt) * std::min(*leftIt, *rightIt);
      max_amount = std::max(max_amount, current_amount);

      // looking for left line higher than height[left_idx] and closer to center
      if (*leftIt < *rightIt) {
        auto it = std::find_if(leftIt, rightIt + 1,
                               [&leftIt](const int& h){ return h > *leftIt; });
        if (it >= rightIt)
          break;
        leftIt = it;
        continue;
      }

      // looking for right line higher than height[right_idx] and closer to center
      if (*leftIt > *rightIt) {
        auto it = findClosesHigherRight(leftIt, rightIt);
        if (it <= leftIt)
          break;
        rightIt = it;
        continue;
      }

      // height[left_idx] == height[right_idx]
      auto closestLeftIt = std::find_if(leftIt, rightIt + 1,
                                        [&leftIt](const int& h){ return h > *leftIt; });
      if (closestLeftIt >= rightIt)
        break;
      auto closestRightIt = findClosesHigherRight(leftIt, rightIt);
      if (closestRightIt <= leftIt)
        break;

      if (*closestLeftIt > *closestRightIt) { // move left line to center
        leftIt = closestLeftIt;
        continue;
      }
      if (*closestLeftIt < *closestRightIt) { // move right line to center
        rightIt = closestRightIt;
        continue;
      }
      // *closestLeftIt == *closestRightIt, so looking for closest line to move
      auto leftDistance = closestLeftIt - leftIt;
      auto rightDistance = closestRightIt - rightIt;
      if (leftDistance > rightDistance) { // move right line to center
        rightIt = closestRightIt;
        continue;
      } else { // move left line to center
        leftIt = closestLeftIt;
        continue;
      }
    }

    return max_amount;
  }

  static std::vector<int>::iterator findClosesHigherRight(const std::vector<int>::iterator& leftIt,
                                                          const std::vector<int>::iterator& rightIt) {
    auto movedRightIt = leftIt - 1;
    for (auto it = rightIt; it >= leftIt; --it) {
      if (*it > *rightIt) {
        movedRightIt = it;
        break;
      }
    }
    return movedRightIt;
  }
};

int main() {
  std::vector<int> nums1{1, 8, 6, 2, 5, 4, 8, 3, 7};
  assert(Solution::maxArea(nums1) == 49);

  std::vector<int> nums2{1, 1};
  assert(Solution::maxArea(nums2) == 1);
}