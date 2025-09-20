#include <cassert>
#include <vector>

class Solution {
 public:
  static int findLength(std::vector<int>& nums1, std::vector<int>& nums2) {
    int nums1_size = static_cast<int>(nums1.size());
    int nums2_size = static_cast<int>(nums2.size());

    std::vector<std::vector<int>> memo(nums1_size);
    for (auto& item : memo) {
      item.resize(nums2_size, 0);
    }

    int ans = 0;
    for (int i = nums1_size-1; i >= 0; --i) {
      for (int j = nums2_size-1; j >= 0; --j) {
        if (nums1[i] == nums2[j]) {
          memo[i][j] = (i == nums1_size-1 || j == nums2_size-1) ? 1 : (memo[i+1][j+1] + 1);
          if (ans < memo[i][j]) {
            ans = memo[i][j];
          };
        }
      }
    }

    return ans;
  }
};

int main() {
  {
    std::vector<int> nums1{1,2,3,2,1};
    std::vector<int> nums2{3,2,1,4,7};
    assert(Solution::findLength(nums1, nums2) == 3);
  }
  {
    std::vector<int> nums1{0,0,0,0,0};
    std::vector<int> nums2{0,0,0,0,0};
    assert(Solution::findLength(nums1, nums2) == 5);
  }
  {
    std::vector<int> nums1{1,0,1,0,0,0,0,0,1,1};
    std::vector<int> nums2{1,1,0,1,1,0,0,0,0,0};
    assert(Solution::findLength(nums1, nums2) == 6);
  }
  return 0;
}
