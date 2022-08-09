#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
    static std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        if (strs.empty())
            return {};
        int sizeSqrt = ceil(std::sqrt(strs.size()));
        std::unordered_map<std::string, size_t> codesToIdx;
        codesToIdx.reserve(sizeSqrt);
        std::vector<std::vector<std::string>> grouped;
        grouped.reserve(sizeSqrt);

        std::string code;
        for (auto& word : strs) {
            code = word;
            std::sort(code.begin(), code.end());

            auto idxIt = codesToIdx.find(code);
            if (idxIt == codesToIdx.end()) {
                codesToIdx[code] = grouped.size();
                grouped.push_back({word});
            } else {
                grouped[idxIt->second].push_back(word);
            }
        }
        return grouped;
    }
};

void checkAssert(std::vector<std::vector<std::string>>& actual, std::vector<std::vector<std::string>>& expected) {
    std::cout << "actual: ";
    for (int i = 0; i < actual.size(); ++i) {
        if (i == 0)
            std::cout << "[";
        std::sort(actual[i].begin(), actual[i].end());
        for (int j = 0; j < actual[i].size(); ++j) {
            if (j == 0)
                std::cout << "[";
            std::cout << actual[i][j] << ", ";
            if (j == actual[i].size() - 1)
                std::cout << "]";
        }
        if (i == actual.size() - 1)
            std::cout << "]";
    }
    std::cout << std::endl;
    std::sort(actual.begin(), actual.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    std::cout << "expected: ";
    for (int i = 0; i < expected.size(); ++i) {
        if (i == 0)
            std::cout << "[";
        std::sort(expected[i].begin(), expected[i].end());
        for (int j = 0; j < expected[i].size(); ++j) {
            if (j == 0)
                std::cout << "[";
            std::cout << expected[i][j] << ", ";
            if (j == expected[i].size() - 1)
                std::cout << "]";
        }
        if (i == expected.size() - 1)
            std::cout << "]";
    }
    std::cout << std::endl;
    std::sort(expected.begin(), expected.end(),
              [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
                  return a[0] < b[0];
              });

    assert(actual.size() == expected.size());
    for (int i = 0; i < expected.size(); ++i) {
        assert(actual[i].size() == expected[i].size());
        for (int j = 0; j < expected[i].size(); ++j) {
            std::cout << "assert: " << actual[i][j] << " == " << expected[i][j] << std::endl;
            assert(actual[i][j] == expected[i][j]);
        }
    }
}

int main() {
    std::vector<std::string> strs1 = {"eat","tea","tan","ate","nat","bat"};
    std::vector<std::vector<std::string>> anagrams1 = Solution::groupAnagrams(strs1);
    std::vector<std::vector<std::string>> expected1 = {{"bat"},{"nat","tan"},{"ate","eat","tea"}};
    checkAssert(anagrams1, expected1);

    std::vector<std::string> strs2 = {"bdddddddddd","bbbbbbbbbbc"};
    std::vector<std::vector<std::string>> anagrams2 = Solution::groupAnagrams(strs2);
    std::vector<std::vector<std::string>> expected2 = {{"bbbbbbbbbbc"},{"bdddddddddd"}};
    checkAssert(anagrams2, expected2);

    return 0;
}
