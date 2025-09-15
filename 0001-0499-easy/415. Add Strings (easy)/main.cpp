#include <cassert>
#include <iostream>
#include <string>

class Solution {
public:
    static std::string addStrings(std::string& num1, std::string& num2) {
        if (num1 == "0")
            return num2;
        if (num2 == "0")
            return num1;

        std::string res;
        std::string add;
        if (num1.size() > num2.size()) {
            res = num1;
            add = num2;
        } else {
            res = num2;
            add = num1;
        }
        // add.size() <= res.size()

        int over_sum_int = 0;

        int i = 0;
        while (i < add.size() || i < res.size()) {
            int res_i = static_cast<int>(res.size()) - i - 1;
            int add_i = static_cast<int>(add.size()) - i - 1;

            std::string res_str = std::string(1, res[res_i]);
            int res_int = std::stoi(res_str);

            int add_int = 0;
            if (i < add.size()) {
                std::string add_str = std::string(1, add[add_i]);
                add_int = std::stoi(add_str);
            }

            int current_sum_int = res_int + add_int + over_sum_int;

            if (current_sum_int >= 10) {
                over_sum_int = current_sum_int / 10;
                current_sum_int = current_sum_int % 10;
            } else { // current_sum_int < 10
                over_sum_int = 0;
            }
            res[res_i] = std::to_string(current_sum_int)[0];
            i++;
        }
        if (over_sum_int > 0) {
            res = std::to_string(over_sum_int) + res;
        }

        return res;
    }
};

int main() {
    std::string num1_1 = "11";
    std::string num1_2 = "123";
    assert(Solution::addStrings(num1_1, num1_2) == "134");
    std::cout << ".............................." << std::endl;

    std::string num2_1 = "456";
    std::string num2_2 = "77";
    assert(Solution::addStrings(num2_1, num2_2) == "533");
    std::cout << ".............................." << std::endl;

    std::string num3_1 = "0";
    std::string num3_2 = "0";
    assert(Solution::addStrings(num3_1, num3_2) == "0");
    std::cout << ".............................." << std::endl;

    // num1 = "0", num2 = "0"
    std::string num4_1 = "999";
    std::string num4_2 = "1";
    assert(Solution().addStrings(num4_1, num4_2) == "1000");
    std::cout << ".............................." << std::endl;
}
