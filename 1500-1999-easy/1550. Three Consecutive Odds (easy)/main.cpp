#include <cassert>
#include <vector>

class Solution {
public:
    static bool threeConsecutiveOdds(std::vector<int>& arr) {
        uint8_t odds_len = 0;
        for (int i = 0; i < arr.size(); ++i) {
            if (arr[i] % 2 == 1) {
                odds_len++;
                if (odds_len >= 3) {
                    return true;
                }
            } else {
                odds_len = 0;
            }
        }
        return false;
    }
};

int main() {
    std::vector<int> arr1 = {2,6,4,1};
    assert(Solution::threeConsecutiveOdds(arr1) == false);

    std::vector<int> arr2 = {1,2,34,3,4,5,7,23,12};
    assert(Solution::threeConsecutiveOdds(arr2) == true);
}
