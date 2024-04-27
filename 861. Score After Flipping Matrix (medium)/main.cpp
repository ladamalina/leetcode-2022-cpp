// #include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::literals;

using ll = long long;
using ii [[maybe_unused]] = std::pair<int, int>;
using vi [[maybe_unused]] = std::vector<int>;
using vvi [[maybe_unused]] = std::vector<vi>;
using vii [[maybe_unused]] = std::vector<ii>;
using vb [[maybe_unused]] = std::vector<bool>;
using vd [[maybe_unused]] = std::vector<double>;
using vs [[maybe_unused]] = std::vector<std::string>;

#define FOR(_i, _a, _b) for (int _i = (_a); _i <= (_b); ++(_i))
#define FORD(_i, _a, _b) for (int _i = (_a); _i >= (_b); --(_i))
#define RNG(_l) (_l).begin(), (_l).end()
#define SORT(_l) std::sort((_l).begin(), (_l).end())
#define CI(_v) static_cast<int>(_v)
#define CL(_v) static_cast<ll>(_v)
#define CD(_v) static_cast<double>(_v)
#define F first
#define S second
#define PB push_back

void FlipRow(int i, int n, vvi& g) {
    FOR(j, 0, n-1) {
        g[i][j] = 1-g[i][j];
    }
}

void FlipCol(int j, int m, vvi& g) {
    FOR(i, 0, m-1) {
        g[i][j] = 1-g[i][j];
    }
}

class Solution {
    public:
    static int matrixScore(vvi& g) {
        const auto m = CI(g.size());
        const auto n = CI(g[0].size());
        FOR(i, 0, m-1) {
            if (!g[i][0]) FlipRow(i, n, g);
        }
        FOR(j, 0, n-1) {
            auto cnt1 = 0;
            FOR(i, 0, m-1) {
                cnt1 += g[i][j];
            }
            if (cnt1 < (m-cnt1)) FlipCol(j, m, g);
        }
        auto res = 0;
        FOR(i, 0, m-1) {
            auto num = 0;
            FOR(j, 0, n-1) {
                if (g[i][j]) {
                    const auto b = n-1-j;
                    num |= (1<<b);
                }
            }
            res += num;
        }
        return res;
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vvi g{{0,0,1,1},{1,0,1,0},{1,1,0,0}};
        const auto a_out = Solution::matrixScore(g);
        assert(a_out == 39);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vvi g{{0}};
        const auto a_out = Solution::matrixScore(g);
        assert(a_out == 1);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    std::cerr << "TestSolution OK"sv << std::endl;
}

int main() {
#ifndef NDEBUG
    TestSolution();
#endif
    return 0;
}
