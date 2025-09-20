#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <tuple>
#include <vector>

class MyCalendar {
public:
    MyCalendar() {
        starts_to_ends = {};
        ends_to_starts = {};
    }

    bool book(int start, int end) {
        // any events beginning <= end?
        auto startsIt = starts_to_ends.lower_bound(end - 1);
        if (startsIt != starts_to_ends.end()) {
            for (auto it = startsIt; it != std::prev(starts_to_ends.begin()); --it) {
                if (it->first >= start && it->first < end)
                    return false;
                if (it->first > start)
                    continue;
                if (it->first == start)
                    return false;
                // iterate over events beginning < start.
                // any events ending > start?
                if (it->second.upper_bound(start) != it->second.end())
                    return false;
            }
        }

        // any events ending > start?
        auto endsIt = ends_to_starts.upper_bound(start);

        while (endsIt != ends_to_starts.end()) {
            if (endsIt->first > start && endsIt->first <= end)
                return false;
            if (endsIt->first <= end) {
                endsIt = std::next(endsIt);
                continue;
            }
            // iterate over events ending > end.
            // any events starting < end?
            for (auto& startIt : endsIt->second) {
                if (startIt < end)
                    return false;
                else
                    break;
            }

            endsIt = std::next(endsIt);
        }

        // book
        starts_to_ends[start].insert(end);
        ends_to_starts[end].insert(start);

        return true;
    }
private:
    std::map<int, std::set<int>> starts_to_ends;
    std::map<int, std::set<int>> ends_to_starts;
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

int main() {
    MyCalendar* cal1 = new MyCalendar();
    std::vector<std::vector<int>> input1 = {{10, 20}, {15, 25}, {20, 30}};
    std::vector<bool> expected1 = {true, false, true};
    for (int i = 0; i < input1.size(); ++i)
        assert(cal1->book(input1[i][0], input1[i][1]) == expected1[i]);
    
    MyCalendar* cal2 = new MyCalendar();
    std::vector<std::vector<int>> input2 = {{47,50},{33,41},{39,45},{33,42},{25,32},{26,35},{19,25},{3,8},{8,13},{18,27}};
    std::vector<bool> expected2 = {true,true,false,false,true,false,true,true,true,false};
    for (int i = 0; i < input2.size(); ++i) {
        bool actual2 = cal2->book(input2[i][0], input2[i][1]);
        std::cout << "start = " << input2[i][0] << ", end = " << input2[i][1] << std::endl;
        std::cout << "expected = " << expected2[i] << ", actual = " << actual2 << std::endl;
        assert(actual2 == expected2[i]);
    }

    return 0;
}
