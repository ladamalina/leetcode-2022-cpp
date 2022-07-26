#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    std::vector<std::string> generateParenthesis(const int n) {
        all_strings = {};
        int init_opened = 0;
        generateTree(INIT_STR, init_opened, init_opened, n, CH_OPEN);
        return all_strings;
    }

    void generateTree(const std::string& init_str, const int& init_opened, int total_opened, const int& max_opened,
                      const std::string& next_ch) {
        if (init_str.size() >= max_opened * 2) {
            all_strings.push_back(init_str);
            return;
        }
        std::string current_str = init_str + next_ch;
        int current_opened;
        if (next_ch == CH_OPEN) {
            current_opened = init_opened + 1;
            total_opened++;
        } else { // ")"
            current_opened = init_opened - 1;
        }

        if (total_opened >= max_opened) { // Stop generate new
            if (current_opened == 0) { // All parenthesis are closed
                all_strings.push_back(current_str);
            } else { // Need to close opened
                generateTree(current_str, current_opened, total_opened, max_opened, CH_CLOSE);
            }
        } else { // Continue to generate
            if (current_opened == 0) {
                generateTree(current_str, current_opened, total_opened, max_opened, CH_OPEN);
            } else {
                generateTree(current_str, current_opened, total_opened, max_opened, CH_CLOSE);
                generateTree(current_str, current_opened, total_opened, max_opened, CH_OPEN);
            }
        }
    }
private:
    std::vector<std::string> all_strings;
    const std::string INIT_STR = "";
    const std::string CH_CLOSE = ")";
    const std::string CH_OPEN = "(";
};

int main() {
    std::vector<std::string> expected1 = {"((()))", "(()())", "(())()", "()(())", "()()()"};
    std::sort(expected1.begin(), expected1.end());
    std::cout << "expected1: ";
    for (auto num : expected1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::vector<std::string> actual1 = Solution().generateParenthesis(3);
    std::sort(actual1.begin(), actual1.end());
    std::cout << "actual1: ";
    for (auto num : actual1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    assert(expected1.size() == actual1.size());
    for (int i = 0; i < expected1.size(); i++) {
        assert(expected1[i] == actual1[i]);
    }

    std::vector<std::string> expected2 = {"()"};
    std::vector<std::string> actual2 = Solution().generateParenthesis(1);
    assert(expected2.size() == actual2.size());
    for (int i = 0; i < expected2.size(); i++) {
        assert(expected2[i] == actual2[i]);
    }
}
