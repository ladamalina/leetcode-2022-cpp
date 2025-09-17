#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    static std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
        if (intervals.size() == 1)
            return intervals;

        std::sort(intervals.begin(), intervals.end(),
                  [](const std::vector<int>& a, const std::vector<int>& b) {
                      return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
                  });
        std::vector<std::vector<int>> merged;
        merged.reserve(intervals.size());
        uint16_t first_idx = 0;
        while (first_idx < intervals.size()) {
            uint16_t second_idx = first_idx + 1;
            while (second_idx < intervals.size()) {
                if (is_overlapping(intervals[first_idx], intervals[second_idx])) {
                    merge_to_first(intervals[first_idx], intervals[second_idx]);
                    ++second_idx;
                    continue;
                }
                // non-overlapping
                break;
            }
            merged.push_back(intervals[first_idx]);
            first_idx = second_idx;
        }

        return merged;
    }

    static bool is_overlapping(const std::vector<int>& range1, const std::vector<int>& range2) {
        return range1[0] <= range2[1] && range2[0] <= range1[1];
    }

    static void merge_to_first(std::vector<int>& range1, const std::vector<int>& range2) {
        range1[0] = std::min(range1[0], range2[0]);
        range1[1] = std::max(range1[1], range2[1]);
    }
};

void checkAssert(std::vector<std::vector<int>>& actual, std::vector<std::vector<int>>& expected) {
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
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
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
              [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
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
    std::vector<std::vector<int>> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    std::vector<std::vector<int>> expected1 = {{1,6},{8,10},{15,18}};
    auto merged_intervals1 = Solution::merge(intervals1);
    checkAssert(merged_intervals1, expected1);

    std::vector<std::vector<int>> intervals2 = {{1,4},{4,5}};
    std::vector<std::vector<int>> expected2 = {{1,5}};
    auto merged_intervals2 = Solution::merge(intervals2);
    checkAssert(merged_intervals2, expected2);

    return 0;
}
