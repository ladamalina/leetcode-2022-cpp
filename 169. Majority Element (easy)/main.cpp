#include <cassert>
#include <unordered_map>
#include <vector>

class Solution {
public:
    static int majorityElement(std::vector<int>& nums) {
        std::unordered_map<int, int> nums_freq;
        auto half_len = nums.size() / 2;
        for (const auto& num : nums) {
            ++nums_freq[num];
            if (nums_freq[num] > half_len)
                return num;
        }

        return 0;
    }
};

int main() {
    std::vector<int> v1{3,2,3};
    assert(Solution::majorityElement(v1) == 3);

    std::vector<int> v2{2,2,1,1,1,2,2};
    assert(Solution::majorityElement(v2) == 2);

    return 0;
}
