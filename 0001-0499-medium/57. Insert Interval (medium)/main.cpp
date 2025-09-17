#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Solution {
public:
    static std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        if (intervals.empty())
            return {newInterval};

        int insert_begin_idx = findInsertPosition(intervals, 0, intervals.size()-1,
                                                  newInterval[0]);
        if (insert_begin_idx >= intervals.size()) {
            intervals.push_back(newInterval);
            return intervals;
        }

        int insert_end_idx = findInsertPosition(intervals, 0, intervals.size()-1,
                                                newInterval[1]);
        if (insert_end_idx >= intervals.size())
            --insert_end_idx;

        if (insert_begin_idx == insert_end_idx) {
            if (is_overlapping(newInterval, intervals[insert_begin_idx])) {
                std::vector<int> merged_range = {std::min(newInterval[0], intervals[insert_begin_idx][0]),
                                                 std::max(newInterval[1], intervals[insert_begin_idx][1])};
                intervals[insert_begin_idx] = merged_range;
            } else {
                intervals.insert(intervals.begin()+insert_begin_idx, newInterval);
            }
        } else {
            // merge range of intervals in origin vector
            int merged_range_start = std::min(newInterval[0], intervals[insert_begin_idx][0]);
            int merged_range_end;
            bool erase_end_interval = false;
            if (is_overlapping(newInterval, intervals[insert_end_idx])) {
                merged_range_end = std::max(newInterval[1], intervals[insert_end_idx][1]);
                erase_end_interval = true;
            } else
                merged_range_end = newInterval[1];
            std::vector<int> merged_range = {merged_range_start, merged_range_end};
            if (erase_end_interval)
                intervals.erase(intervals.begin()+insert_begin_idx, intervals.begin()+insert_end_idx+1);
            else
                intervals.erase(intervals.begin()+insert_begin_idx, intervals.begin()+insert_end_idx);
            intervals.insert(intervals.begin()+insert_begin_idx, merged_range);
        }

        return intervals;
    }

    static int findInsertPosition(const std::vector<std::vector<int>>& intervals, const int& begin_idx, const int& end_idx,
                                  const int& insert_time) {
        if (begin_idx == end_idx) {
            if (insert_time <= intervals[begin_idx][0])
                return begin_idx;
            else if (insert_time <= intervals[begin_idx][1])
                return begin_idx;
            else
                return begin_idx + 1;
        }
        // intervals.size() > 1
        int half_len = (end_idx - begin_idx) / 2;

        int left_half_end = begin_idx + half_len;
        if (insert_time >= intervals[left_half_end][0] && insert_time <= intervals[left_half_end][1])
            return left_half_end;
        if (insert_time < intervals[left_half_end][0])
            return findInsertPosition(intervals, begin_idx, left_half_end, insert_time);

        int right_half_begin = begin_idx + half_len + 1;
        if (insert_time >= intervals[right_half_begin][0] && insert_time <= intervals[right_half_begin][1])
            return right_half_begin;
        if (insert_time > intervals[right_half_begin][1])
            return findInsertPosition(intervals, right_half_begin, end_idx, insert_time);

        return right_half_begin;
    }

    static bool is_overlapping(const std::vector<int>& range1, const std::vector<int>& range2) {
        return range1[0] <= range2[1] && range2[0] <= range1[1];
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
    std::vector<std::vector<int>> intervals1 = {{1,3},{6,9}};
    std::vector<int> new_interval1 = {2,5};
    std::vector<std::vector<int>> expected1 = {{1,5},{6,9}};
    auto merged_intervals1 = Solution::insert(intervals1, new_interval1);
    checkAssert(merged_intervals1, expected1);

    std::vector<std::vector<int>> intervals2 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    std::vector<int> new_interval2 = {4,8};
    std::vector<std::vector<int>> expected2 = {{1,2},{3,10},{12,16}};
    auto merged_intervals2 = Solution::insert(intervals2, new_interval2);
    checkAssert(merged_intervals2, expected2);

    std::vector<std::vector<int>> intervals3 = {};
    std::vector<int> new_interval3 = {1,5};
    std::vector<std::vector<int>> expected3 = {{1,5}};
    auto merged_intervals3 = Solution::insert(intervals3, new_interval3);
    checkAssert(merged_intervals3, expected3);

    std::vector<std::vector<int>> intervals4 = {{1,5}};
    std::vector<int> new_interval4 = {2,7};
    std::vector<std::vector<int>> expected4 = {{1,7}};
    auto merged_intervals4 = Solution::insert(intervals4, new_interval4);
    checkAssert(merged_intervals4, expected4);

    std::vector<std::vector<int>> intervals5 = {{1,5}};
    std::vector<int> new_interval5 = {6,8};
    std::vector<std::vector<int>> expected5 = {{1,5},{6,8}};
    auto merged_intervals5 = Solution::insert(intervals5, new_interval5);
    checkAssert(merged_intervals5, expected5);

    std::vector<std::vector<int>> intervals6 = {{1,5},{6,8}};
    std::vector<int> new_interval6 = {0,9};
    std::vector<std::vector<int>> expected6 = {{0,9}};
    auto merged_intervals6 = Solution::insert(intervals6, new_interval6);
    checkAssert(merged_intervals6, expected6);

    return 0;
}
