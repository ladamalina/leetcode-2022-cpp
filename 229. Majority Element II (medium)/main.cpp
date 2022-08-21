#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution {
public:
    static std::vector<int> majorityElement(std::vector<int>& nums) {
        std::unordered_map<int, int> nums_freq;
        std::unordered_set<int> most_freq;
        most_freq.reserve(3);
        auto t_len = nums.size() / 3;
        for (const auto& num : nums) {
            if (most_freq.count(num))
                continue;
            ++nums_freq[num];
            if (nums_freq[num] > t_len)
                most_freq.insert(num);
        }
        std::vector<int> most_freq_v(most_freq.begin(), most_freq.end());

        return most_freq_v;
    }
};

void checkAssertion(std::vector<int>& actual, const std::vector<int>& expected) {
    std::cout << "expected: ";
    for (const auto expected_val: expected)
        std::cout << expected_val << ' ';
    std::cout << std::endl;

    std::sort(actual.begin(), actual.end());
    std::cout << "actual_res: ";
    for (const auto expected_val: actual)
        std::cout << expected_val << ' ';
    std::cout << std::endl;

    assert(expected.size() == actual.size());
    for (int i = 0; i < expected.size(); ++i) {
        assert(expected[i] == actual[i]);
    }
}

int main() {
    std::vector<int> v1{3,2,3};
    std::vector<int> v1_expected{3};
    auto v1_actual = Solution::majorityElement(v1);
    checkAssertion(v1_actual, v1_expected);

    std::vector<int> v2{1};
    std::vector<int> v2_expected{1};
    auto v2_actual = Solution::majorityElement(v2);
    checkAssertion(v2_actual, v2_expected);

    std::vector<int> v3{1,2};
    std::vector<int> v3_expected{1,2};
    auto v3_actual = Solution::majorityElement(v3);
    checkAssertion(v3_actual, v3_expected);

    std::vector<int> v4{2,2};
    std::vector<int> v4_expected{2};
    auto v4_actual = Solution::majorityElement(v4);
    checkAssertion(v4_actual, v4_expected);

    return 0;
}
