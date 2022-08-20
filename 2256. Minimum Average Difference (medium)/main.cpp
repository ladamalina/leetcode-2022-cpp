#include <cassert>
#include <limits>
#include <vector>

class Solution {
public:
    static int minimumAverageDifference(std::vector<int>& nums) {
        uint32_t nums_len = nums.size();
        if (nums_len == 1)
            return 0;

        uint64_t nums_sum = 0;
        for (const int& num : nums)
            nums_sum += num;
        uint64_t min_avg = std::numeric_limits<uint64_t>::max();
        uint32_t min_avg_idx = 0;
        uint64_t left_sum = 0;

        for (uint32_t i = 0; i < nums_len; ++i) {
            left_sum += nums[i];
            uint64_t left_avg = left_sum / (i+1);
            uint64_t right_avg;
            if (i < nums_len - 1)
                right_avg = (nums_sum - left_sum) / (nums_len - i - 1);
            else
                right_avg = nums_sum - left_sum;
            uint64_t avg_diff;
            if (left_avg >= right_avg)
                avg_diff = left_avg - right_avg;
            else
                avg_diff = right_avg - left_avg;
            if (avg_diff < min_avg) {
                min_avg = avg_diff;
                min_avg_idx = i;
            }
        }

        return min_avg_idx;
    }
};

int main() {
    std::vector<int> v1{2,5,3,9,5,3};
    assert(Solution::minimumAverageDifference(v1) == 3);

    std::vector<int> v2{0};
    assert(Solution::minimumAverageDifference(v2) == 0);

    std::vector<int> v3{1};
    assert(Solution::minimumAverageDifference(v3) == 0);

    std::vector<int> v4{4,2,0};
    assert(Solution::minimumAverageDifference(v4) == 2);
}
