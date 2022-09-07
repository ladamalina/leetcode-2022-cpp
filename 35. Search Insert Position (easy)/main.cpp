#include <cassert>
#include <vector>

class Solution {
public:
    static int searchInsert(const std::vector<int>& nums, int target) {
        return Solution::searchInsertInterval(nums, target, 0, static_cast<int>(nums.size()) - 1);
    }

    static int searchInsertInterval(const std::vector<int>& nums, int target, int leftIdx, int rightIdx) {
        int intervalSize = rightIdx - leftIdx + 1;

        if (intervalSize == 1) {
            if (target <= nums[leftIdx])
                return leftIdx;
            else
                return leftIdx + 1;
        }

        int midIdxLeft = leftIdx + intervalSize / 2 - 1;
        int midIdxRight = midIdxLeft + 1;
        if (target <= nums[midIdxLeft])
            return Solution::searchInsertInterval(nums, target, leftIdx, midIdxLeft);
        else if (target < nums[midIdxRight])
            return midIdxRight;
        else
            return Solution::searchInsertInterval(nums, target, midIdxRight, rightIdx);
    }
};

int main() {
    const std::vector v1 = {1,3,5,6};
    assert(Solution::searchInsert(v1, 5) == 2);

    const std::vector v12 = {1,3,5,6,7};
    assert(Solution::searchInsert(v12, 6) == 3);

    const std::vector v13 = {1,3,5,6,7};
    assert(Solution::searchInsert(v13, 7) == 4);

    const std::vector v14 = {1,3,5,6,7};
    assert(Solution::searchInsert(v14, 1) == 0);

    const std::vector v2 = {1,3,5,6};
    assert(Solution::searchInsert(v2, 2) == 1);

    const std::vector v3 = {1,3,5,6};
    assert(Solution::searchInsert(v3, 7) == 4);

    const std::vector v31 = {1,3,5,6};
    assert(Solution::searchInsert(v31, -1) == 0);

    const std::vector v4 = {1};
    assert(Solution::searchInsert(v4, 1) == 0);

    const std::vector v5 = {1};
    assert(Solution::searchInsert(v5, 6) == 1);

    const std::vector v6 = {6};
    assert(Solution::searchInsert(v6, 1) == 0);

    return 0;
}
