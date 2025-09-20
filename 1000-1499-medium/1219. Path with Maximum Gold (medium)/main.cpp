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

constexpr std::array<ii, 4> DIRS{ii{0,1},ii{0,-1},ii{1,0},ii{-1,0}};

int DFS(int i, int j, int m, int n, vvi& g) {
    if (i<0 || i>=m || j<0 || j>=n || g[i][j]==0) return 0;
    const auto ij_res = g[i][j];
    g[i][j] = 0;
    auto max_sub_res = 0;
    for (const auto& d : DIRS) {
        const auto sub_res = DFS(i+d.F,j+d.S,m,n,g);
        max_sub_res = std::max(max_sub_res,sub_res);
    }
    g[i][j] = ij_res;
    return ij_res+max_sub_res;
}

class Solution {
    public:
    static int getMaximumGold(vvi& g) {
        const auto m = CI(g.size());
        const auto n = CI(g[0].size());
        auto max_res = 0;
        FOR(i, 0, m-1) {
            FOR(j, 0, n-1) {
                const auto res = DFS(i,j,m,n,g);
                max_res = std::max(max_res, res);
            }
        }
        return max_res;
    }
};

[[maybe_unused]] void TestSolution() {
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vvi g{{0,6,0},{5,8,7},{0,9,0}};
        const auto a_out = Solution::getMaximumGold(g);
        assert(a_out == 24);

        const auto end_t = std::chrono::high_resolution_clock::now();
        const auto total_t = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
        std::cerr << total_t << " ms"sv << std::endl;
    }
    {
        const auto start_t = std::chrono::high_resolution_clock::now();

        vvi g{{1,0,7},{2,0,6},{3,4,5},{0,3,0},{9,0,20}};
        const auto a_out = Solution::getMaximumGold(g);
        assert(a_out == 28);

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
