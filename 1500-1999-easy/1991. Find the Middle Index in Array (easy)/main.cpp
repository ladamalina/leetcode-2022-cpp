#include <cassert>
#include <numeric>
#include <vector>

class Solution {
public:
    static int findMiddleIndex(std::vector<int>& nums) {
        int nums_sum = accumulate(nums.begin(), nums.end(), 0);
        int left_sum = 0;
        uint8_t nums_len = nums.size();
        for (uint8_t i = 0; i < nums_len; ++i) {
            if (left_sum == nums_sum - nums[i] - left_sum)
                return i;
            left_sum += nums[i];
        }

        return -1;
    }
};

int main() {
    std::vector<int> v1{2,3,-1,8,4};
    assert(Solution::findMiddleIndex(v1) == 3);

    std::vector<int> v2{1,-1,4};
    assert(Solution::findMiddleIndex(v2) == 2);

    std::vector<int> v3{2,5};
    assert(Solution::findMiddleIndex(v3) == -1);
}
