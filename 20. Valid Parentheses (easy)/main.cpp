#include <cassert>
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Solution {
public:
    static bool isValid(const std::string& s) {
        std::unordered_map<char, char> closing_to_opening = {
                {')', '('},
                {']', '['},
                {'}', '{'}
        };
        std::unordered_set<char> closing = {')', ']', '}'};
        std::unordered_set<char> opening = {'(', '[', '{'};
        std::stack<char> openings;

        for (auto ch : s) {
            if (opening.find(ch) != opening.end()) {
                openings.push(ch);
                continue;
            }
            if (closing.find(ch) != opening.end()) {
                if (openings.empty()) {
                    return false;
                }
                auto last_opening = openings.top();
                auto expected_opening = closing_to_opening[ch];
                if (last_opening == expected_opening)
                    openings.pop();
                else
                    return false;
            }
        }

        return openings.empty();
    }
};

int main() {
    assert(Solution::isValid("()") == true);
    assert(Solution::isValid("()[]{}") == true);
    assert(Solution::isValid("(()]") == false);
    assert(Solution::isValid("(]") == false);
    assert(Solution::isValid("(") == false);
    assert(Solution::isValid("}") == false);
}
