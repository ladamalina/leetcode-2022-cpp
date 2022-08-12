#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

class Solution {
public:
    static std::vector<int> addToArrayForm(std::vector<int>& num, int k) {
        int current_sum = 0;
        int over_sum = k;
        std::deque<int> res;
        for (int i = num.size() - 1; i >= 0; i--) {
            current_sum = num[i] + over_sum;
            if (current_sum >= 10) {
                over_sum = current_sum / 10;
                current_sum = current_sum % 10;
            } else {
                over_sum = 0;
            }
            res.push_front(current_sum);
        }
        while (over_sum > 0) {
            current_sum = over_sum % 10;
            over_sum = over_sum / 10;
            res.push_front(current_sum);
        }
        size_t res_size = res.size();
        std::vector<int> res_list(res_size);
        for (int i=0; i < res_size; ++i) {
            int next_val = res.front();
            res_list[i] = next_val;
            res.pop_front();
        }
        return res_list;
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
    std::vector<int> num1 = {1,2,0,0};
    int k1 = 34;
    std::vector<int> res1 = Solution::addToArrayForm(num1, k1);
    std::vector<int> expected_res1 = {1,2,3,4};
    checkAssertion(res1, expected_res1);
    std::cout << ".............................." << std::endl;

    std::vector<int> num2 = {2,7,4};
    int k2 = 181;
    std::vector<int> res2 = Solution::addToArrayForm(num2, k2);
    std::vector<int> expected_res2 = {4,5,5};
    checkAssertion(res2, expected_res2);
    std::cout << ".............................." << std::endl;

    std::vector<int> num3 = {2,1,5};
    int k3 = 806;
    std::vector<int> res3 = Solution::addToArrayForm(num3, k3);
    std::vector<int> expected_res3 = {1,0,2,1};
    checkAssertion(res3, expected_res3);
    std::cout << ".............................." << std::endl;
}
