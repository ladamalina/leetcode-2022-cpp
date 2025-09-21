#include <cassert>

class Solution {
public:
    static bool isSameAfterReversals(int num) {
        return num == 0 || num % 10 > 0;
    }
};

int main() {
    assert(Solution::isSameAfterReversals(526) == true);
    assert(Solution::isSameAfterReversals(1800) == false);
    assert(Solution::isSameAfterReversals(0) == true);

    return 0;
}
