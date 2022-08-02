#include <cassert>
#include <cmath>
#include <iostream>

double factorial(uint64_t x) {
    if (x == 1 || x == 0)
        return 1;

    double res = 1;
    for(int i = 1; i <= x; ++i) {
        res *= i;
    }

    return res;
}

class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 1 || n == 1)
            return 1;
        // m > 1 && n > 1
        int movementsByX = m - 1;
        int movementsByY = n - 1;
        int totalMovemets = movementsByX + movementsByY;

        /*
         * Permutation with Repetitions: How many different letter arrangements can be formed
         * using the letters P E P P E R?
         * In general, there are multinomial coefficients:
         * n! / (n1! n2! n3! ... nr!)
         * different permutations of n objects, of which n1 are alike, n2, are alike, n3 are alike,..... nr are alike.
         * Therefore, the answer is 6! /(3! 2! 1!) = 60 possible arrangements of the letters P E P P E R.
         * https://home.ubalt.edu/ntsbarsh/business-stat/otherapplets/comcount.htm
         */

        double totalMovemetsF = factorial(totalMovemets);
        double movementsByXF = factorial(movementsByX);
        double movementsByYF = factorial(movementsByY);

        std::cout << "totalMovemets = " << totalMovemets << ", movementsByX = " << movementsByX <<
                ", movementsByY = " << movementsByY << std::endl;

        std::cout << "totalMovemetsF = " << totalMovemetsF << ", movementsByXF = " << movementsByXF <<
                  ", movementsByYF = " << movementsByYF << std::endl;

        uint64_t totalPaths = (uint64_t) round(totalMovemetsF / movementsByXF / movementsByYF);

        std::cout << "totalPaths = " << totalPaths << std::endl;

        return totalPaths;
    }
};

int main() {
    assert(Solution().uniquePaths(3, 7) == 28);
    assert(Solution().uniquePaths(3, 2) == 3);
    assert(Solution().uniquePaths(1, 1) == 1);
    Solution().uniquePaths(10, 10);
    assert(Solution().uniquePaths(23, 12) == 193536720);
    assert(Solution().uniquePaths(19, 13) == 86493225);

    return 0;
}
