#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    static int removeElement(std::vector<int>& nums, int val) {
        std::cout << "input: ";
        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::cout << "val = " << val << std::endl;

        int result_nums_idx = -1;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] != val) {
                result_nums_idx++;
                nums[result_nums_idx] = nums[i];
            }
        }

        std::cout << "updated: ";
        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::cout << "result_nums_idx = " << result_nums_idx << std::endl;

        return result_nums_idx + 1;
    }
};

int main() {
    std::vector<int> nums1 = {3,2,2,3}; // Input array
    const int val1 = 3;
    std::vector<int> expectedNums1 = {2,2}; // The expected answer with correct length
    const int k1 = Solution::removeElement(nums1, val1); // Calls your implementation
    assert(k1 == expectedNums1.size());
    std::sort(nums1.begin(), nums1.begin() + k1);
    std::cout << "sorted for assertion: ";
    for (auto num : nums1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < k1; ++i) {
        assert(nums1[i] == expectedNums1[i]);
    }
    std::cout << "..........................." << std::endl;

    std::vector<int> nums2 = {0,1,2,2,3,0,4,2}; // Input array
    const int val2 = 2;
    std::vector<int> expectedNums2 = {0, 0, 1, 3, 4}; // The expected answer with correct length
    const int k2 = Solution::removeElement(nums2, val2); // Calls your implementation
    assert(k2 == expectedNums2.size());
    std::sort(nums2.begin(), nums2.begin() + k2);
    std::cout << "sorted for assertion: ";
    for (auto num : nums2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < k2; ++i) {
        assert(nums2[i] == expectedNums2[i]);
    }
    std::cout << "..........................." << std::endl;

    std::vector<int> nums3 = {0,0,0,0,0,0,0,0}; // Input array
    const int val3 = 0;
    std::vector<int> expectedNums3 = {}; // The expected answer with correct length
    const int k3 = Solution::removeElement(nums3, val3); // Calls your implementation
    assert(k3 == expectedNums3.size());
    std::sort(nums3.begin(), nums3.begin() + k3);
    std::cout << "sorted for assertion: ";
    for (auto num : nums3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < k3; ++i) {
        assert(nums3[i] == expectedNums3[i]);
    }
    std::cout << "..........................." << std::endl;
}
