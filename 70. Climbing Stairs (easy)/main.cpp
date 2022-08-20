#include <cassert>

class Solution {
public:
    static int climbStairs(int n) {
        if (n == 1)
            return 1;
        if (n == 2)
            return 2;

        uint32_t step1 = 1;
        uint32_t step2 = 2;
        for (int i = 2; i < n; ++i) {
            auto step3 = step1 + step2;
            step1 = step2;
            step2 = step3;
        }

        return step2;
    }
};

int main() {
    assert(Solution::climbStairs(1) == 1);
    assert(Solution::climbStairs(2) == 2);
    assert(Solution::climbStairs(3) == 3);
    assert(Solution::climbStairs(35) == 14930352);
}
