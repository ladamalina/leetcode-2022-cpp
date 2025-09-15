#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>

class Solution {
public:
    static std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> umap;
        for (int i = 0; i < nums.size(); ++i) {
            int pair_to_find = target - nums[i];
            if (umap.find(pair_to_find) != umap.end()) {
                return {umap.at(pair_to_find), i};
            } else {
                umap[nums[i]] = i;
            }
        }

        return {};
    }
};

int main() {
    std::vector<int> nums1 = {2,7,11,15};
    int target1 = 9;
    std::vector<int> expected_indices1 = {0,1};
    assert(expected_indices1 == Solution::twoSum(nums1, target1));

    std::vector<int> nums2 = {3,2,4};
    int target2 = 6;
    std::vector<int> expected_indices2 = {1,2};
    assert(expected_indices2 == Solution::twoSum(nums2, target2));

    std::vector<int> nums3 = {3,3};
    int target3 = 6;
    std::vector<int> expected_indices3 = {0,1};
    assert(expected_indices3 == Solution::twoSum(nums3, target3));
}
