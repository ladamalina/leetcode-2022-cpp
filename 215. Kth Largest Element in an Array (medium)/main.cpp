#include <cassert>
#include <vector>
#include <set>

class Solution {
 public:
  static int findKthLargest(std::vector<int>& nums, int k) {
    std::multiset<int> nums_set;
    for (auto& val : nums) {
      if (nums_set.size() < k) {
        nums_set.insert(val);
        continue;
      }
      // nums_set.size() == k

      if (val < *nums_set.begin())
        continue;

      // insert new val
      nums_set.insert(val);
      // nums_set.size() == k + 1
      nums_set.erase(nums_set.begin());
    }

    return *nums_set.begin();
  }
};

int main() {
  std::vector<int> nums1{3,2,1,5,6,4};
  assert(Solution::findKthLargest(nums1, 2) == 5);

  std::vector<int> nums2{3,2,3,1,2,4,5,5,6};
  assert(Solution::findKthLargest(nums2, 4) == 4);

  return 0;
}
