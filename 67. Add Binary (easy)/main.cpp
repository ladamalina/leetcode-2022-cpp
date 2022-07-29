#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

class Solution {
public:
    std::string addBinary(std::string& a, std::string& b) {
        if (a == ZERO)
            return b;
        if (b == ZERO)
            return a;

        std::string res = "";
        std::string add = "";
        if (a.size() > b.size()) {
            res = a;
            add = b;
        }
        else {
            res = b;
            add = a;
        }
        // add.size() <= res.size()

        int current_sum_int = 0;
        std::string current_sum_bin = ZERO;
        int over_sum_int = 0;
        std::string over_sum_bin = ZERO;

        int i = 0;
        while (i < add.size() || i < res.size()) {
            int res_i = res.size() - i - 1;
            int add_i = add.size() - i - 1;

            std::string res_str = std::string(1, res[res_i]);
            int res_int = std::stoi(res_str, 0, 2);

            int add_int = 0;
            if (i < add.size()) {
                std::string add_str = std::string(1, add[add_i]);
                add_int = std::stoi(add_str, 0, 2);
            }

            current_sum_int = res_int + add_int + over_sum_int;

            current_sum_bin = std::bitset<2>(current_sum_int).to_string(); //"00000000000000000000000010000000"
            current_sum_bin.erase(0, current_sum_bin.find_first_not_of('0')); //"10000000"
            if (current_sum_bin.empty()) {
                current_sum_bin = ZERO;
            }

            if (current_sum_bin.size() > 1) {
                over_sum_bin = *current_sum_bin.begin();
                over_sum_int = std::stoi(over_sum_bin, 0, 2);
                current_sum_bin.erase(0, 1);
            } else { // current_sum_bin.size() == 1)
                over_sum_bin = ZERO;
                over_sum_int = 0;
            }
            res[res_i] = current_sum_bin[0];
            i++;
        }
        if (over_sum_bin.size() > 0 && over_sum_bin != ZERO) {
            res = over_sum_bin + res;
        }

        return res;
    }
private:
    const std::string ZERO = "0";
    const std::string ONE = "1";
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
    for (int i=0; i < expected_res.size(); i++) {
        assert(expected_res[i] == actual_res[i]);
    }
}

int main() {
    std::string a1 = "11";
    std::string b1 = "1";
    assert(Solution().addBinary(a1, b1) == "100");
    std::cout << ".............................." << std::endl;

    std::string a2 = "1010";
    std::string b2 = "1011";
    assert(Solution().addBinary(a2, b2) == "10101");
    std::cout << ".............................." << std::endl;

    std::string a3 = "0";
    std::string b3 = "0";
    assert(Solution().addBinary(a3, b3) == "0");
    std::cout << ".............................." << std::endl;

    std::string a4 = "100";
    std::string b4 = "110010";
    assert(Solution().addBinary(a4, b4) == "110110");
    std::cout << ".............................." << std::endl;
}
