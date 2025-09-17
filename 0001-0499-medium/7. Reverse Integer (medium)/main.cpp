#include <cctype>
#include <cmath>
#include <climits>
#include <string>
#include <vector>

class Solution {
public:
    static int reverse(int x) {
        if (x == 0)
            return x;
        bool signIsPos = x > 0;
        uint8_t xLen = std::to_string(x).size();
        if (!signIsPos)
            xLen--;

        int64_t res = 0;
        uint8_t currentPow = 1;
        while (x != 0) {
            auto d = (int8_t) (x % 10);
            res += d * (int64_t) pow(10, xLen - currentPow);
            if (signIsPos && res > std::numeric_limits<int32_t>::max())
                return 0;
            if (!signIsPos && res < std::numeric_limits<int32_t>::min())
                return 0;
            currentPow++;
            x = x / 10;
        }

        return (int32_t) res;
    }
};

int main() {
    assert(Solution::reverse(123) == 321);
    assert(Solution::reverse(-123) == -321);
    assert(Solution::reverse(0) == 0);
    // > 2 147 483 648
    assert(Solution::reverse(1111111119) == 0);
    assert(Solution::reverse(1534236469) == 0);
    assert(Solution::reverse(-1111111119) == 0);

    return 0;
}
