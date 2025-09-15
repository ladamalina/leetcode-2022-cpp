#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

class Solution {
public:
    static std::vector<int> plusOne(std::vector<int>& digits) {
        int current_sum = 0;
        int over_sum = 1;
        for (int i = digits.size() - 1; i >= 0; i--) {
            current_sum = digits[i] + over_sum;
            if (current_sum >= 10) {
                over_sum = current_sum / 10;
                current_sum = current_sum % 10;
            } else {
                over_sum = 0;
            }
            digits[i] = current_sum;
        }
        if (over_sum > 0) {
            std::vector<int> res_list(digits.size() + 1);
            res_list[0] = over_sum;
            for (int i = 0; i < digits.size(); ++i) {
                res_list[i+1] = digits[i];
            }
            return res_list;
        }
        return digits;
    }
};

void checkAssertion(const std::vector<int>& actual_res, const std::vector<int>& expected_res) {
    std::cout << "expected_res: ";
    for (auto expected_val: expected_res)
        std::cout << expected_val << ' ';
    std::cout << std::endl;
    std::cout << "actual_res: ";
    for (auto expected_val: actual_res)
        std::cout << expected_val << ' ';
    std::cout << std::endl;
    assert(expected_res.size() == actual_res.size());
    for (int i=0; i < expected_res.size(); ++i) {
        assert(expected_res[i] == actual_res[i]);
    }
}

int main() {
    std::vector<int> num1 = {1,2,3};
    std::vector<int> res1 = Solution::plusOne(num1);
    std::vector<int> expected_res1 = {1,2,4};
    checkAssertion(res1, expected_res1);
    std::cout << ".............................." << std::endl;

    std::vector<int> num2 = {4,3,2,1};
    std::vector<int> res2 = Solution::plusOne(num2);
    std::vector<int> expected_res2 = {4,3,2,2};
    checkAssertion(res2, expected_res2);
    std::cout << ".............................." << std::endl;

    std::vector<int> num3 = {9,9,9};
    std::vector<int> res3 = Solution::plusOne(num3);
    std::vector<int> expected_res3 = {1,0,0,0};
    checkAssertion(res3, expected_res3);
    std::cout << ".............................." << std::endl;
}
