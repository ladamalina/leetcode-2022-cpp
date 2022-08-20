#include <cassert>

class Solution {
public:
    static int tribonacci(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        if (n == 2)
            return 1;
        int step0 = 0;
        int step1 = 1;
        int step2 = 1;
        for (uint8_t i = 3; i <= n; ++i) {
            auto step3 = step0 + step1 + step2;
            step0 = step1;
            step1 = step2;
            step2 = step3;
        }

        return step2;
    }
};

int main() {
    assert(Solution::tribonacci(0) == 0);
    assert(Solution::tribonacci(1) == 1);
    assert(Solution::tribonacci(2) == 1);
    assert(Solution::tribonacci(3) == 2);
    assert(Solution::tribonacci(4) == 4);
    assert(Solution::tribonacci(25) == 1389537);
}
