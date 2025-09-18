#include <cassert>

class Solution {
public:
    static int fib(int n) {
        if (n == 0)
            return 0;
        if (n == 1)
            return 1;
        int step1 = 0;
        int step2 = 1;
        for (uint8_t i = 2; i <= n; ++i) {
            auto step3 = step1 + step2;
            step1 = step2;
            step2 = step3;
        }

        return step2;
    }
};

int main() {
    assert(Solution::fib(2) == 1);
    assert(Solution::fib(3) == 2);
    assert(Solution::fib(4) == 3);
    assert(Solution::fib(25) == 75025);
}
