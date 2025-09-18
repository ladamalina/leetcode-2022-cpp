#include <cassert>
#include <vector>

class Solution {
public:
    static int minCostClimbingStairs(std::vector<int>& cost) {
        for (uint16_t i = 2; i < cost.size(); ++i) {
            cost[i] = cost[i] + std::min(cost[i-1], cost[i-2]);
        }
        return std::min(cost.back(), cost[cost.size()-2]);
    }
};

int main() {
    std::vector<int> v1{10,15,20};
    assert(Solution::minCostClimbingStairs(v1) == 15);

    std::vector<int> v2{1,100,1,1,1,100,1,1,100,1};
    assert(Solution::minCostClimbingStairs(v2) == 6);
}
