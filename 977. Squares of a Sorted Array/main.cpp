#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    static std::vector<int> sortedSquares(std::vector<int>& nums) {
        std::cout << "input: ";
        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        if (nums.empty()) {
            return nums;
        }
        if (nums.size() == 1) {
            return {nums[0]*nums[0]};
        }

        int mid_idx = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            if (nums[i] < 0) {
                mid_idx = i + 1;
            }
            nums[i] = nums[i] * nums[i];
        }
        std::cout << "mid_idx = " << mid_idx << std::endl;

        std::vector<int> result(nums.size());
        size_t result_idx = 0;
        int left_mid_idx = mid_idx - 1;
        while (left_mid_idx >= 0 && mid_idx < nums.size()) {
            if (nums[left_mid_idx] >= nums[mid_idx]) {
                result[result_idx] = nums[mid_idx];
                mid_idx++;
            } else {
                result[result_idx] = nums[left_mid_idx];
                left_mid_idx--;
            }
            result_idx++;
        }
        while (left_mid_idx >= 0) {
            result[result_idx] = nums[left_mid_idx];
            left_mid_idx--;
            result_idx++;
        }
        while (mid_idx < nums.size()) {
            result[result_idx] = nums[mid_idx];
            mid_idx++;
            result_idx++;
        }

        std::cout << "after merge: ";
        for (auto num : result) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        return result;
    }
};

int main() {
    std::vector<int> nums1 = {-4,-1,0,3,10};
    std::vector<int> expected_nums1 = {0,1,9,16,100};
    assert(expected_nums1 == Solution::sortedSquares(nums1));

    std::vector<int> nums2 = {-7,-3,2,3,11};
    std::vector<int> expected_nums2 = {4,9,9,49,121};
    assert(expected_nums2 == Solution::sortedSquares(nums2));

    std::vector<int> nums3 = {-7,-3};
    std::vector<int> expected_nums3 = {9,49};
    assert(expected_nums3 == Solution::sortedSquares(nums3));

    std::vector<int> nums4 = {3,4};
    std::vector<int> expected_nums4 = {9,16};
    assert(expected_nums4 == Solution::sortedSquares(nums4));

    std::vector<int> nums5 = {};
    std::vector<int> expected_nums5 = {};
    assert(expected_nums5 == Solution::sortedSquares(nums5));

    std::vector<int> nums6 = {-3};
    std::vector<int> expected_nums6 = {9};
    assert(expected_nums6 == Solution::sortedSquares(nums6));

    std::vector<int> nums7 = {3};
    std::vector<int> expected_nums7 = {9};
    assert(expected_nums7 == Solution::sortedSquares(nums7));
}
