#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    static void moveZeroes(std::vector<int>& nums) {
        std::cout << "input: ";
        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        int result_nums_idx = -1;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != 0) {
                result_nums_idx++;
                nums[result_nums_idx] = nums[i];
            }
        }

        while (result_nums_idx > -1 && result_nums_idx + 1 < nums.size()) {
            result_nums_idx++;
            if (nums[result_nums_idx] != 0)
                nums[result_nums_idx] = 0;
        }

        std::cout << "updated: ";
        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> nums1 = {0,1,0,3,12};
    std::vector<int> expectedNums1 = {1,3,12,0,0};
    Solution::moveZeroes(nums1);
    assert(nums1 == expectedNums1);
    std::cout << "..........................." << std::endl;

    std::vector<int> nums2 = {0};
    std::vector<int> expectedNums2 = {0};
    Solution::moveZeroes(nums1);
    assert(nums2 == expectedNums2);
    std::cout << "..........................." << std::endl;

    std::vector<int> nums3 = {0,0,0};
    std::vector<int> expectedNums3 = {0,0,0};
    Solution::moveZeroes(nums3);
    assert(nums3 == expectedNums3);
    std::cout << "..........................." << std::endl;
}
