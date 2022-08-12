#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    static int removeDuplicates(std::vector<int>& nums) {
        std::cout << "input: ";
        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        int last_uniq_num = -1000;
        int uniq_nums_idx = -1;

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > last_uniq_num) {
                last_uniq_num = nums[i];
                uniq_nums_idx++;
                nums[uniq_nums_idx] = nums[i];
            }
        }

        std::cout << "updated: ";
        for (auto num : nums) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        std::cout << "uniq_nums_idx = " << uniq_nums_idx << std::endl;

        return uniq_nums_idx+1;
    }
};

int main() {
    std::vector<int> nums1 = {1,1,2}; // Input array
    std::vector<int> expectedNums1 = {1,2}; // The expected answer with correct length
    int k1 = Solution::removeDuplicates(nums1); // Calls your implementation
    assert(k1 == expectedNums1.size());
    for (int i = 0; i < k1; ++i) {
        assert(nums1[i] == expectedNums1[i]);
    }

    std::vector<int> nums2 = {0,0,1,1,1,2,2,3,3,4}; // Input array
    std::vector<int> expectedNums2 = {0,1,2,3,4}; // The expected answer with correct length
    int k2 = Solution::removeDuplicates(nums2); // Calls your implementation
    assert(k2 == expectedNums2.size());
    for (int i = 0; i < k2; ++i) {
        assert(nums2[i] == expectedNums2[i]);
    }
}
