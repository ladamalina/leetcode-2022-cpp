#include <cassert>
#include <numeric>
#include <vector>

class Solution {
public:
    static int pivotIndex(std::vector<int>& nums) {
        int nums_sum = accumulate(nums.begin(), nums.end(), 0);
        int left_sum = 0;
        uint16_t nums_len = nums.size();
        for (uint16_t i = 0; i < nums_len; ++i) {
            if (left_sum == nums_sum - nums[i] - left_sum)
                return i;
            left_sum += nums[i];
        }

        return -1;
    }
};

int main() {
    std::vector<int> v1{2,3,-1,8,4};
    assert(Solution::pivotIndex(v1) == 3);

    std::vector<int> v2{1,-1,4};
    assert(Solution::pivotIndex(v2) == 2);

    std::vector<int> v3{2,5};
    assert(Solution::pivotIndex(v3) == -1);

    std::vector<int> v4{1,7,3,6,5,6};
    assert(Solution::pivotIndex(v4) == 3);

    std::vector<int> v5{2,1,-1};
    assert(Solution::pivotIndex(v5) == 0);

    std::vector<int> v6{1,2,3};
    assert(Solution::pivotIndex(v6) == -1);
}
