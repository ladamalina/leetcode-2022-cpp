#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    static void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
        if (n == 0) {
            return;
        }
        auto idx1 = m - 1;
        auto idx2 = n - 1;
        auto target_idx = nums1.size() - 1;
        while (idx1 >= 0 && idx2 >= 0) {
            if (nums1[idx1] >= nums2[idx2]) {
                nums1[target_idx] = nums1[idx1];
                idx1--;
            } else {
                nums1[target_idx] = nums2[idx2];
                idx2--;
            }
            target_idx--;
        }
        if (idx2 >= 0) {
            while (idx2 >= 0) {
                nums1[target_idx] = nums2[idx2];
                idx2--;
                target_idx--;
            }
        }
    }
};

int main() {
    // nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    std::vector<int> nums1 = {1,2,3,0,0,0};
    std::vector<int> nums2 = {2,5,6};
    Solution::merge(nums1, 3, nums2, 3);
    std::vector<int> expected_nums1 = {1,2,2,3,5,6};
    assert(expected_nums1 == nums1);

    // nums1 = [1], m = 1, nums2 = [], n = 0
    std::vector<int> nums3 = {1};
    std::vector<int> nums4 = {};
    Solution::merge(nums3, 1, nums4, 0);
    std::vector<int> expected_nums3 = {1};
    assert(expected_nums3 == nums3);

    // nums1 = [0], m = 0, nums2 = [1], n = 1
    std::vector<int> nums5 = {0};
    std::vector<int> nums6 = {1};
    Solution::merge(nums5, 0, nums6, 1);
    std::vector<int> expected_nums5 = {1};
    assert(expected_nums5 == nums5);
}
